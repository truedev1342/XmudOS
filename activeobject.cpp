#include "stdafx.h"
#include "XmudOS.h"
#include "ActiveObject.h"
#include "Goods\Goods\Goods.h"
#include "Skill\Skill\Skill.h"
#include "Common.h"
#include "condition.h"
#include "map\mapinfo.h"
#include "npc\npc.h"
#include "player.h"
#include "Fight.h"
#include "CmdPlayerLogon.h"
#include "hash.h"

extern rmfullglobals myglobs;
extern CList <CBaseMap*,CBaseMap*>maplist;
extern CList <CFight*,CFight*>killlist;
extern CList <CFight*,CFight*>fightlist;

TObjectSkill * GetTObjSkill(CString szEName, int level, int score, CString szMapping)
{
	TObjectSkill * lpObjectSkill;
	CSkill * lpSkill;

	lpSkill = GetSkillClass(szEName);
	if (lpSkill == NULL) return NULL;
	lpObjectSkill = new TObjectSkill;
	lpObjectSkill->lpSkill = lpSkill;
	lpObjectSkill->nLevel = level;
	lpObjectSkill->nScore = score;
	lpObjectSkill->szMapping = szMapping;
	return lpObjectSkill;
}

CActiveObject::CActiveObject() 
{ 
	strcpy(szCheck,SZAOBJCHECK);
	szCName = _T("");	
	szEName = _T("");	 
	szNickName = _T("");
	szTilte = _T("");
	szXFileName = _T("");
	szFamily = _T("無門派");	
	szTeacher = _T("");	
	szPerson = _T("");	
	szRoom = _T("");		
	szSex = _T("");	
	
	nAge = 0;
	nShen = 0;
	nStr = 0;		
	nInt = 0;		
	nCon = 0;		
	nDex = 0;		
	nEff_qi = 0;	
	nMax_qi = 0;	
	nEff_jing = 0;	
	nMax_jing = 0;	
	nEff_jingli = 0;
	nMax_jingli = 0;
	nAdd_Jingli = 0;	 
	nEff_force = 0;	
	nMax_force = 0;	 
	nAdd_force = 0;	
	nCombat_exp = 0; 
	nScore = 0;		   
	nGeneration = 0;
	nMoney = 0;
	nStatus = 0;
	lpWeapon = NULL;
	nBusy = 0;
	nTick = 10;
	bPlayer = FALSE;
	nOther = 0;
	bNoHealing = TRUE;
	nEscapeNow = 0;
	g_HasEvent = 0;

	SetSkill("BaseUnarmed",0);
	SetSkill("BaseParry",0); 
	SetSkill("BaseDodge",0);
	SetSkill("BaseForce",0);
	SetSkill("BaseSword",0); 
	SetSkill("BaseBlade",0);
	SetSkill("BaseClub",0);
	SetSkill("BaseShort",0);
}

CActiveObject::~CActiveObject()
{
	POSITION pos;
	void *p;
	CGoods *lpGoods;
	pos = listskill.GetHeadPosition();
	while(pos != NULL){
		p = listskill.GetNext(pos);
		delete p;
	}
	listskill.RemoveAll();
	pos = listequip.GetHeadPosition();
	while(pos != NULL){
		lpGoods = listequip.GetNext(pos);
		delete lpGoods;
	}
	listequip.RemoveAll();
	listfightopp.RemoveAll();
	pos = listtempval.GetHeadPosition();
	while(pos != NULL){
		p = listtempval.GetNext(pos);
		delete p;
	}
	listtempval.RemoveAll();
	pos = listcondition.GetHeadPosition();
	while(pos != NULL){
		p = listcondition.GetNext(pos);
		delete p;
	} 
	listcondition.RemoveAll();
}
CString CActiveObject::AddGoods(CGoods *lpEquip)
{ 
	CGoods *lpMyEquip;
	POSITION pos,lpos;
	BOOL bFind = FALSE;
	int nWeight = 0;
	CString szRet;

	EnterCriticalSection(&myglobs.csPlayerData);
	pos = listequip.GetHeadPosition(); 
	while (pos!=NULL) { 
		lpMyEquip = listequip.GetNext(pos);
		if( lpMyEquip->nCount < 0 )	lpMyEquip->nCount = 1;
		nWeight += (lpMyEquip->lpGoods->nWeight * lpMyEquip->nCount);
	}
	
	if( lpEquip->nCount < 0 ) lpEquip->nCount = 1;
	if( lpEquip->lpGoods->nWeight > 0 )	{
		if( ((nStr*1000) - nWeight)/lpEquip->lpGoods->nWeight < lpEquip->nCount )	{
			lpEquip->nCount=((nStr*1000) - nWeight)/lpEquip->lpGoods->nWeight;
		}
	}

	if( nWeight < 0 || lpEquip->nCount < 1 ||
		(nWeight + ( lpEquip->lpGoods->nWeight * lpEquip->nCount )) > nStr*1000	) {
		szRet.Format("%s可攜帶重量%d，目前攜帶重量%d，%s重量%d，超過負重限制",
			szCName, nStr*1000, nWeight,
			lpEquip->lpGoods->szCName, lpEquip->lpGoods->nWeight);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return szRet; 
	}

	if ((lpEquip->lpGoods->nKinds == GK_food) ||
		(lpEquip->lpGoods->nKinds == GK_drug) ||
		(lpEquip->lpGoods->nKinds == GK_flag) ) {

		pos = listequip.GetHeadPosition();
		bFind = FALSE;
		while (pos!=NULL) {
			lpos = pos;
			lpMyEquip = listequip.GetNext(pos);
			if (lpMyEquip->lpGoods->szEName == lpEquip->lpGoods->szEName) {
				bFind = TRUE;
				lpMyEquip->nCount += lpEquip->nCount;
				delete lpEquip;
				break;
			}
		}
		if (!bFind)	listequip.AddTail(lpEquip);
	} else {
		lpEquip->nCount = 1;
		listequip.AddTail(lpEquip);
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	return CString("OK");
}

CString CActiveObject::SubGoods(CString szName)
{
	POSITION lastpos, pos;
	CGoods * lpGoods;

	EnterCriticalSection(&myglobs.csPlayerData);
	pos = listequip.GetHeadPosition();
	while (pos != NULL) {
		lastpos = pos;
		lpGoods = listequip.GetNext(pos);
		if (lpGoods != NULL) {
			if (lpGoods->lpGoods->szEName == szName ||
				lpGoods->lpGoods->szCName == szName) {
				lpGoods->nCount--;
				lpGoods->nNew = lpGoods->lpGoods->nDurable;
				if (lpGoods->nCount <= 0) {
					listequip.RemoveAt(lastpos);
					delete lpGoods;
				}
				LeaveCriticalSection(&myglobs.csPlayerData);
				return "OK";
			}
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	return "沒有這個物品";
}

CString CActiveObject::SetGoods(CGoods *lpEquip)
{
	CGoods *lpMyEquip; 
	POSITION lastpos,pos;
	BOOL bFind = FALSE;
	int nWeight = 0;
	CString szRet;
	
	EnterCriticalSection(&myglobs.csPlayerData);
	pos = listequip.GetHeadPosition();
	if(lpEquip->lpGoods->nKinds == GK_flag) {
		pos = listequip.GetHeadPosition();
		while (pos!=NULL) {
			lastpos = pos;
			lpMyEquip = listequip.GetNext(pos);
			if (lpMyEquip->lpGoods->szEName == lpEquip->lpGoods->szEName) {
				bFind = TRUE;
				lpMyEquip->nCount = lpEquip->nCount;
				if (lpEquip->nCount <= 0) {
					listequip.RemoveAt(lastpos);
				}

				delete lpEquip;
				break;
			}
		}
		if ( (!bFind) && (lpEquip->nCount > 0) )	listequip.AddTail(lpEquip);
	}else{
		LeaveCriticalSection(&myglobs.csPlayerData);
		return CString("Not Flag");
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	return CString("OK");
}


void CActiveObject::SetSkill(CString szEName, int nLevel, int nScore, CString szMapName)
{
	TObjectSkill * lpObjectSkill;
	char szTest[256];
	int nTotal = 0, i;

	lpObjectSkill = GetTSkill(szEName);
	if ((nScore==0) && (nLevel > 0)) nScore = 1;
	if(lpObjectSkill != NULL){
		for (i=1; i<nLevel; i++) {
			nTotal += i * i;
		}
		lpObjectSkill->nScore += nTotal + nScore;
		while (lpObjectSkill->nScore > lpObjectSkill->nLevel * lpObjectSkill->nLevel) {
			lpObjectSkill->nScore -= lpObjectSkill->nLevel * lpObjectSkill->nLevel;
			lpObjectSkill->nLevel++;
		}
		lpObjectSkill->szMapping = szMapName;
	}
	else
	{
		lpObjectSkill = GetTObjSkill(szEName, nLevel, nScore, szMapName);
		if (lpObjectSkill != NULL) {
			listskill.AddTail(lpObjectSkill);
		} else {
			sprintf(szTest, "ERROR (%s) SetSkill %s error!", this->szEName, szEName);
			AddRecordMsg(szTest);
		}
	}

}


PObjectSkill CActiveObject::GetTSkill(CString SkillName)
{
	int i;
	TObjectSkill *lpPlayerSkill;

	EnterCriticalSection(&myglobs.csPlayerData);
	
	for(i=0; i < listskill.GetCount(); i++){
		lpPlayerSkill = listskill.GetAt(listskill.FindIndex(i));
		if( !lpPlayerSkill->lpSkill )
			return NULL;
		if( stricmp(lpPlayerSkill->lpSkill->szEName, SkillName) == 0 ){
			LeaveCriticalSection(&myglobs.csPlayerData);
			return lpPlayerSkill;
		}else if( strcmp(lpPlayerSkill->lpSkill->szCName, SkillName) == 0 ){
			LeaveCriticalSection(&myglobs.csPlayerData);
			return lpPlayerSkill;
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	return NULL;
}

int CActiveObject::GetSkillLevel(CString SkillName)
{
	TObjectSkill *lpPlayerSkill = GetTSkill(SkillName);
	return (lpPlayerSkill == NULL)? 0 : lpPlayerSkill->nLevel;
}

CString CActiveObject::GetSkillMap(CString SkillName)
{
	TObjectSkill *lpPlayerSkill = GetTSkill(SkillName);
	return (lpPlayerSkill == NULL)? _T("") : lpPlayerSkill->szMapping;
}

CString CActiveObject::GetAttackBaseSkill()
{
	CStringList listBaseSkill;
	CString szRet;
	if(lpWeapon == NULL)
		return "BaseUnarmed";
	switch(lpWeapon->lpWeapon->nKind)
	{
	case 0:
		return "BaseUnarmed";
	case WK_sword:
		return "BaseSword";
	case WK_blade:
		return "BaseBlade";
	case WK_club:
		return "BaseClub";
	case WK_short:
		return "BaseShort";
	default:
		int i,j, level, levelNow;
		CString szSkillName;

		i = lpWeapon->lpWeapon->nKind;
		if(i & WK_sword)
			listBaseSkill.AddTail("BaseSword");
		if(i & WK_blade)
			listBaseSkill.AddTail("BaseBlade");
		if(i & WK_club)
			listBaseSkill.AddTail("BaseClub");
		if(i & WK_short)
			listBaseSkill.AddTail("BaseShort");
		level = 0;
		j = 0;
		for(i=0;i<listBaseSkill.GetCount();i++){
			szSkillName = listBaseSkill.GetAt(listBaseSkill.FindIndex(i));
			levelNow = GetSkillLevel(szSkillName);
			if(levelNow > level){
				level = levelNow;
				j = i;
			}
		}
		szRet = listBaseSkill.GetAt(listBaseSkill.FindIndex(j));
		listBaseSkill.RemoveAll();
		return szRet;
	}
}

TRetInfo CActiveObject::RunSkillCom(CString szSkillName, CString szCom, CActiveObject *lpTarget)
{
	TRetInfo ri;
	TObjectSkill * lpTSkill = GetTSkill(szSkillName);
	if(lpTSkill == NULL) return ri;
	CList <CSkill::TExert *, CSkill::TExert *> * listCom = &(lpTSkill->lpSkill->listCom);
	CSkill::TExert * lpExert;
	POSITION pos = listCom->GetHeadPosition();
	while(pos != NULL){
		lpExert = listCom->GetNext(pos);
		if(lpExert->szCom == szCom){
			ri.szRet = (lpTSkill->lpSkill->*(lpExert->ComFunc))(this,lpTarget);
			ri.bRet = TRUE;
			return ri;
		}
	}
	return ri;
}

void CActiveObject::CheckGoods()
{
	CGoods * lpGoods;
	POSITION pos;
	EnterCriticalSection(&myglobs.csPlayerData);
	pos = listequip.GetHeadPosition();
	while(pos != NULL){
		lpGoods = listequip.GetNext(pos);
		if(lpGoods->nNew <= 0){
			if( lpGoods->lpGoods->nUsage & GP_noold){
				lpGoods->nNew = 10000000;
				continue;
			}
			POSITION pos2;
			pos2 = pos;
			if(pos2 == NULL)
				pos2 = listequip.GetTailPosition();
			else
				listequip.GetPrev(pos2);
			CheckGoods(pos2);
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
}

void CActiveObject::CheckGoods(POSITION pos)
{
	CGoods * lpGoods;

	EnterCriticalSection(&myglobs.csPlayerData);

	lpGoods = listequip.GetAt(pos);
	if(lpGoods == NULL){
		return;
	}
	lpGoods->nCount --;
	if(lpGoods->nCount <= 0) {
		listequip.RemoveAt(pos);
		delete lpGoods;
	} else {
		lpGoods->nNew = lpGoods->lpGoods->nDurable;
		if (lpGoods->lpGoods->nKinds == GK_food) {
			dynamic_cast<CFood*>(lpGoods)->nRemain =
				dynamic_cast<CFood*>(lpGoods)->lpFood->nMaxRemain;
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerData);

}

POSITION CActiveObject::GetGoods(CGoods * lpFGoods)
{
	CGoods * lpGoods;
	POSITION pos;
	EnterCriticalSection(&myglobs.csPlayerData);
	pos = listequip.GetHeadPosition();
	while(pos != NULL){
		lpGoods = listequip.GetNext(pos);
		if( lpFGoods == lpGoods){
			if(pos != NULL)
				listequip.GetPrev(pos);
			else
				pos = listequip.GetTailPosition();
			LeaveCriticalSection(&myglobs.csPlayerData);
			return pos;
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	return NULL;
}

CGoods * CActiveObject::GetGoods(char *szName)
{
	CGoods * lpGoods;
	POSITION pos;
	EnterCriticalSection(&myglobs.csPlayerData);
	pos = listequip.GetHeadPosition();
	while(pos != NULL){
		lpGoods = listequip.GetNext(pos);
		if( !strcmp(lpGoods->lpGoods->szCName,szName) || 
			!stricmp(lpGoods->lpGoods->szEName,szName)) {
			LeaveCriticalSection(&myglobs.csPlayerData);
			return lpGoods;
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	return NULL;
}

CGoods * CActiveObject::GetClassGoods(int nKinds)
{
	CGoods * lpGoods;
	POSITION pos;

	EnterCriticalSection(&myglobs.csPlayerData);
	pos = listequip.GetHeadPosition();
	while(pos != NULL){
		lpGoods = listequip.GetNext(pos);
		if( lpGoods->lpGoods->nKinds & nKinds ) {
			LeaveCriticalSection(&myglobs.csPlayerData);
			return lpGoods;
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	return NULL;
}

TRetInfo CActiveObject::RunGoodsCom(CString szGoodsName, CString szCom, CActiveObject *lpTarget)
{
	TRetInfo ri;
	CGoods * lpGoods = GetGoods((char *)(LPCTSTR)szGoodsName);
	if(lpGoods == NULL)	return ri;
	CSpecial * lpSpecial = dynamic_cast<CSpecial *>(lpGoods);
	if(lpSpecial == NULL) return ri;
	CList<CSpecial::TCommand *, CSpecial::TCommand *> * listCom;
	listCom = &(lpSpecial->lpSpecial->listCom);
	CSpecial::TCommand * lpCommand;
	POSITION pos = listCom->GetHeadPosition();
	while(pos != NULL){
		lpCommand = listCom->GetNext(pos);
		if(lpCommand->szCom == szCom){
			ri.szRet = (lpSpecial->*(lpCommand->ComFunc))(this,lpTarget);
			ri.bRet = TRUE;
			return ri;
		}
	}
	return ri;
}

POSITION CActiveObject::GetTTempPos(CString szName)
{
	POSITION posRet;
	TTempVal * ptempval;

	posRet = listtempval.GetHeadPosition();
	while (posRet != NULL)
	{
		ptempval = listtempval.GetNext(posRet);
		if(ptempval->szName == szName)
		{
			if(posRet != NULL)
				listtempval.GetPrev(posRet);
			else 
				posRet = listtempval.GetTailPosition();
			return posRet;
		}
	}
	return NULL;
}
void CActiveObject::DeleteTemp(CString szName)
{
	POSITION pos;

	EnterCriticalSection(&myglobs.csPlayerData);
	pos = GetTTempPos(szName);
	if(pos != NULL){
		listtempval.RemoveAt(pos);
	}

	LeaveCriticalSection(&myglobs.csPlayerData);
}
void CActiveObject::SetTemp(CString szName, TMixed mixVal)
{
	if ((mixVal.bIsInt == -1) ||
		((mixVal.bIsInt == TRUE) && (mixVal.nValue == 0)) ||
		((mixVal.bIsInt == FALSE) && (mixVal.szValue.IsEmpty()))){
		DeleteTemp(szName);
	}else{
		TTempVal * ptempval;
		EnterCriticalSection(&myglobs.csPlayerData);
		POSITION pos = GetTTempPos(szName);
		if(pos != NULL){
			ptempval = listtempval.GetAt(pos);
			ptempval->bIsInt = mixVal.bIsInt;
			ptempval->nValue = mixVal.nValue;
			ptempval->szValue = mixVal.szValue;
		}else{
			ptempval = new TTempVal;
			ptempval->szName = szName;
			ptempval->bIsInt = mixVal.bIsInt;
			ptempval->nValue = mixVal.nValue;
			ptempval->szValue = mixVal.szValue;
			listtempval.AddHead(ptempval);
		}
		LeaveCriticalSection(&myglobs.csPlayerData); 
	}
} 
void CActiveObject::SetTemp(CString szName, int nValue)
{
	TMixed mixTemp; 
	mixTemp.bIsInt = TRUE;
	mixTemp.nValue = nValue;
	SetTemp(szName, mixTemp);  
}
void CActiveObject::SetTemp(CString szName, CString szValue)
{
	TMixed mixTemp;
	mixTemp.bIsInt = FALSE;
	mixTemp.szValue = szValue;
	SetTemp(szName, mixTemp);
}
TMixed CActiveObject::GetTemp(CString szName)
{
	TMixed mixRet; 
	EnterCriticalSection(&myglobs.csPlayerData);
	POSITION pos = GetTTempPos(szName);
	if(pos != NULL){
		TTempVal * ptempval = listtempval.GetAt(pos);
		mixRet.bIsInt = ptempval->bIsInt;
		mixRet.nValue = ptempval->nValue;
		mixRet.szValue = ptempval->szValue;
	}else {
		mixRet.bIsInt = -1;
		mixRet.nValue = 0;
		mixRet.szValue.Empty();
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	return mixRet;
}

void CActiveObject::AddTemp(CString szName, int nValue)
{
	if(nValue == 0) return;
	EnterCriticalSection(&myglobs.csPlayerData);
	POSITION pos = GetTTempPos(szName);
	TTempVal * ptempval;
	if(pos != NULL){
		ptempval = listtempval.GetAt(pos);
		if(ptempval->bIsInt == TRUE){
			ptempval->nValue += nValue;
			if(ptempval->nValue == 0)
				listtempval.RemoveAt(pos);
		}else
			TRACE("AddTemp for a CString type!");
	}else{
		ptempval = new TTempVal;
		ptempval->bIsInt = TRUE;
		ptempval->nValue = nValue;
		listtempval.AddHead(ptempval);
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
}

void CActiveObject::HitOb(CActiveObject *you, int &damage_bonus, CString &strRet, int nWhere)
{
	return;
}

int CActiveObject::GetMaxQi()
{
	int MAXQI;
	int nLevel, nTaoismLevel;

	MAXQI = 100 + (nAge-14) * nCon;
	if (nAge > 35) MAXQI -= (nAge-35) * 20;
	if (nAge > 60) MAXQI -= (nAge-60) * 20;
	if (nAge > 100) MAXQI -= (nAge-100) * 20;
	if (MAXQI < 40) MAXQI = 40;

	MAXQI += nMax_force >> 2;
	nTaoismLevel = GetSkillLevel("OtherTaoism");
	nLevel = GetSkillLevel("OtherBuddhism");
	if (nLevel > nTaoismLevel) nTaoismLevel = nLevel;
	if(nTaoismLevel > 30)
		MAXQI += (nTaoismLevel - 30) * 3;
	if(nTaoismLevel > 60)
		MAXQI += (nTaoismLevel - 60) * 2;
	if( MAXQI <= 0 )	MAXQI=1;
	return MAXQI;
}

bool CActiveObject::ReceiveCure(int nQi)
{
	int nMax = GetMaxQi();
	if(nMax==nMax_qi)
		return false;
	nMax_qi += nQi;
	if(nMax_qi > nMax) {
		nMax_qi = nMax;
	}
	return true;
}

int CActiveObject::GetMaxJing()
{
	int MAXJING, nLevel;
	int nTaoismLevel = GetSkillLevel("OtherTaoism");
	nLevel = GetSkillLevel("OtherBuddhism");
	if (nLevel > nTaoismLevel) nTaoismLevel = nLevel;
	if(nAge <= 20)
		MAXJING = 100 + (nAge - 14) * 20;
	else if(nAge <= 30)
		MAXJING = 220;

	else if(nAge < 95)
		MAXJING	= 90 + (95 - nAge) * 2;
	else if(nAge < 135)
		MAXJING	= 50 + (135 - nAge);
	else if(nAge < 175)
		MAXJING	= 40 + (175 - nAge) /4;
	else
		MAXJING	= 40;
	MAXJING += nMax_jingli >> 1;
	if(nTaoismLevel > 30)
		MAXJING += (nTaoismLevel - 30) * 2;
	if(nTaoismLevel > 60)
		MAXJING += (nTaoismLevel - 60) * 1;
	return MAXJING;
}

bool CActiveObject::ReceiveJing(int nJing)
{
	int nMax = GetMaxJing();
	if(nMax_jing==nMax)
		return false;
	nMax_jing += nJing;
	if(nMax_jing > nMax) {
		nMax_jing = nMax;
	}
	return true;
}

void CActiveObject::Unconcious(int nTime)
{
	SendMsgToAll(szCName + "的身體搖晃了兩下，昏倒在地上。");
	SendMsg("你的眼前一黑，接著什麼也不知道了....");
	nEff_jing = 0;
	nEff_qi = 0;

	if(nTime = 0) 
		nTime = random(100 - nCon) + 30;
	ApplyCondition(CK_special, "Unconcious", nTime);
}

void CActiveObject::Wake()
{
	MapMessage("$N慢慢地甦醒了過來....", this);
	nEff_jing = nMax_jing/3;
	nEff_qi = nMax_qi/3;
	nStatus = 0;
}

void CActiveObject::Die()
{
	CString szTmp;
	CCmdPlayerLogon m_PlayerLogon;
	int nTest;
	szTmp.Format("%s %s %s %s",SZDEADMSG,szRedHigt,szCName,szEName);
	MapMessage(szTmp, this);
	nStatus = AOS_dead;
	if(bPlayer) {
		if(szNickName != "充氣娃娃") {
			int exploss = (nCombat_exp >> 4);
			if(exploss > 20000)	{
				exploss = 20000;
			}
			nCombat_exp -= exploss;
			nMax_qi = 5;
			nEff_qi = 0;
			nEff_jing = 0;
			if (((CPlayerInfo*)this)->nEat <= 0) 
				((CPlayerInfo*)this)->nEat = 20;
			if (((CPlayerInfo*)this)->nDrink <= 0) 
				((CPlayerInfo*)this)->nDrink = 20;
			if( szRoom == "waei_01" || szRoom == "waei_02" || szRoom == "waei_03")	{
				szRoom = "waei_01";
			}else if (szFamily == "少林派") {
				szRoom = "sl_cf";
			} else if (szFamily == "武當派") {
				szRoom = "wd_hkt";
			} else if (szFamily == "華山派") {
				szRoom = "hs_xzhu";
			} else if (szFamily == "峨眉派") {
				szRoom = "em_cwshi";
			} else if (szFamily == "星宿派") {
				szRoom = "xx_cf";
			} else {
				szRoom = "xy_guangchang";
			}
		}  
		m_PlayerLogon.SavePlayerData((CPlayerInfo*)this);
		nTest = CheckUserLog((char*)(LPCSTR)((CPlayerInfo*)this)->szUserName);
		if (nTest <= 0) {
			szTmp.Format("ERROR (%s,%s) Invalid login in CActiveObject::Die",
				((CPlayerInfo*)this)->szEName, ((CPlayerInfo*)this)->szUserName);
			AddRecordMsg((char*)(LPCSTR)szTmp);
			if (nTest == INVALIDLOG)
				szTmp.Format("FAIL %s", szInvalidLogin);
			else
				szTmp.Format("FAIL %s", szSystemErrMsg);
			((CPlayerInfo*)this)->SendMsg(szTmp);
			Sleep(5000);
			shutdown(((CPlayerInfo*)this)->hPlayerSocket, 2);
			closesocket(((CPlayerInfo*)this)->hPlayerSocket);
		}
	} else {
		((CNpc*)this)->nRecover = 1;
	}
}

void CActiveObject::SendMsgToAll(CString sMsg, CActiveObject *you)
{
	CPlayerInfo *lpPlayerInfo;

	EnterCriticalSection(&myglobs.csMaplist);
	CBaseMap * lpDataMap = maplist.GetAt(pMapPosite);
	POSITION tmpPos = lpDataMap->listplayer.GetHeadPosition(), lastPos;
	while(tmpPos != NULL)
	{
		lastPos = tmpPos;
		lpPlayerInfo = lpDataMap->listplayer.GetNext(tmpPos);
		if(lpPlayerInfo == NULL) { 
			lpDataMap->listplayer.RemoveAt(lastPos);
			continue;
		}
		if(strcmp(lpPlayerInfo->szCheck, SZAOBJCHECK)) {
			lpDataMap->listplayer.RemoveAt(lastPos);
			continue;
		}
		if(lpPlayerInfo->szEName == szEName)continue;
		if(you != NULL) {
			if(strcmp(you->szCheck, SZAOBJCHECK)) {
				continue;
			}
			if(lpPlayerInfo->szEName == you->szEName)continue;
		}
		lpPlayerInfo->SendMsg(sMsg);
	}
	LeaveCriticalSection(&myglobs.csMaplist);
}

void CActiveObject::RemoveAllEnemy()
{
	EnterCriticalSection(&myglobs.csFightlist);
	listfightopp.RemoveAll();
	LeaveCriticalSection(&myglobs.csFightlist);
}

int CActiveObject::SendMsg(CString szMsg)
{
	if(bPlayer)
		return ((CPlayerInfo *)this)->SendMsg(szMsg);
	else return -1;
}

int CActiveObject::GetGoodCount(char *szName)
{
	int nTheCount = 0; 
	POSITION pos; 
	CGoods * lpGood; 

	EnterCriticalSection(&myglobs.csPlayerData);
	pos = listequip.GetHeadPosition();
	while (pos != NULL){
		lpGood = listequip.GetNext(pos);
		if (lpGood != NULL){
			if (lpGood->lpGoods->szEName == szName || lpGood->lpGoods->szCName == szName){
				nTheCount += lpGood->nCount;
			}
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerData);

	return nTheCount;
}

int CActiveObject::GetGoodIsNotArmedCount(char *szName)
{
	int nTheCount = 0;	
	POSITION pos;
	CGoods * lpGood;

	EnterCriticalSection(&myglobs.csPlayerData);
	pos = listequip.GetHeadPosition();
	while (pos != NULL){ 
		lpGood = listequip.GetNext(pos);
		if (lpGood != NULL){ 
			if (lpGood->lpGoods->szEName == szName || lpGood->lpGoods->szCName == szName){
				if(lpGood->lpGoods->nKinds == GK_equip){
					if(dynamic_cast<CEquip*>(lpGood)->nWearWhere == 0)
						nTheCount++;
				}else if(lpGood->lpGoods->nKinds == GK_weapon){
					if(dynamic_cast<CWeapon*>(lpGood)->bWield == FALSE)
						nTheCount++;
				}else{
					nTheCount += lpGood->nCount;
				}
			}
		}
	}

	LeaveCriticalSection(&myglobs.csPlayerData);
	return nTheCount;
}

CGoods* CActiveObject::GetGoodIsNotArmed(char *szName)
{
	POSITION pos;
	CGoods * lpGood;

	EnterCriticalSection(&myglobs.csPlayerData);
	pos = listequip.GetHeadPosition();
	while (pos != NULL){
		lpGood = listequip.GetNext(pos);
		if (lpGood != NULL){
			if (lpGood->lpGoods->szEName == szName || lpGood->lpGoods->szCName == szName){
				if(lpGood->lpGoods->nKinds == GK_equip){
					if(dynamic_cast<CEquip*>(lpGood)->nWearWhere == 0){
						LeaveCriticalSection(&myglobs.csPlayerData);
						return lpGood;
					}
				}else if(lpGood->lpGoods->nKinds == GK_weapon){
					if(dynamic_cast<CWeapon*>(lpGood)->bWield == FALSE){
						LeaveCriticalSection(&myglobs.csPlayerData);
						return lpGood;
					}
				}else{
					LeaveCriticalSection(&myglobs.csPlayerData);
					return lpGood;
				}
			}
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	return NULL;
}

CString CActiveObject::SubGoodWhichIsNotArmed(char *szName)
{
	POSITION lastpos, pos;
	CGoods * lpGood;

	EnterCriticalSection(&myglobs.csPlayerData);
	pos = listequip.GetHeadPosition();
	while (pos != NULL){ 
		lastpos = pos;
		lpGood = listequip.GetNext(pos);
		if(lpGood != NULL){
			if(lpGood->lpGoods->szEName == szName || lpGood->lpGoods->szCName == szName){
				
				if(lpGood->lpGoods->nKinds == GK_equip){
					if(dynamic_cast<CEquip*>(lpGood)->nWearWhere == 0){
						listequip.RemoveAt(lastpos);
						delete lpGood;
						LeaveCriticalSection(&myglobs.csPlayerData);
						return "OK";
					}
				}else if(lpGood->lpGoods->nKinds == GK_weapon){
					if(dynamic_cast<CWeapon*>(lpGood)->bWield == FALSE){
						listequip.RemoveAt(lastpos);
						delete lpGood;
						LeaveCriticalSection(&myglobs.csPlayerData);
						return "OK";
					}
				}else if((lpGood->lpGoods->nKinds == GK_drug) || (lpGood->lpGoods->nKinds == GK_food)){
					lpGood->nCount--;
					lpGood->nNew = lpGood->lpGoods->nDurable;
					if (lpGood->nCount <= 0){
						listequip.RemoveAt(lastpos);
						delete lpGood;
					}
					LeaveCriticalSection(&myglobs.csPlayerData);
					return "OK";
				}else if(lpGood->lpGoods->nKinds == GK_flag){
					lpGood->nCount--;
					lpGood->nNew = lpGood->lpGoods->nDurable;
					if (lpGood->nCount <= 0){
						listequip.RemoveAt(lastpos);
						delete lpGood;
					}
					LeaveCriticalSection(&myglobs.csPlayerData);
					return "OK";
				}else {
					listequip.RemoveAt(lastpos);
					delete lpGood;
					LeaveCriticalSection(&myglobs.csPlayerData);
					return "OK";					
				}
			}
		} 
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	return "沒有這個物品";
}
