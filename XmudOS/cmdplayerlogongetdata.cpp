#include "stdafx.h"
#include "XmudOS.h"
#include "CmdPlayerLogon.h"
#include "npc\Npc.h"
#include "map\mapinfo.h"

extern rmfullglobals myglobs;
extern CList <TClientConData *,TClientConData* >playersocketlist;
extern CList <CBaseMap*,CBaseMap*>maplist;

CString CCmdPlayerLogon::GatherPlayerData(char *Result,CPlayerInfo * lpPlayerInfo)
{
	CString sResultMsg,parm,sign;
	CString strtmp;
	sign = CString("'");
	parm = CString("'\t");

	sResultMsg = CString("OK\t") + sign + CString("PLAYER") + parm;
	//收集玩家的數據
	sResultMsg += sign + lpPlayerInfo->szCName + parm;
	sResultMsg += sign + lpPlayerInfo->szEName + parm;
	sResultMsg += sign + lpPlayerInfo->szNickName + parm;
	sResultMsg += sign + lpPlayerInfo->szTilte + parm;
	sResultMsg += sign + lpPlayerInfo->szXFileName + parm;
	sResultMsg += sign + lpPlayerInfo->szFamily + parm;
	sResultMsg += sign + lpPlayerInfo->szRoom + parm;
	sResultMsg += sign + lpPlayerInfo->szSex + parm;
	
	strtmp.Format("%d",lpPlayerInfo->nAge);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nShen);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nStr);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nInt);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nCon);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nDex);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nEff_qi);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nMax_qi);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nEff_jing);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nMax_jing);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nEff_jingli);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nMax_jingli);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nAdd_Jingli);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nEff_force);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nMax_force);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nAdd_force);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nCombat_exp);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nScore);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nGeneration);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nMoney);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nStatus);
	sResultMsg += sign + strtmp + parm;

	sResultMsg += sign + lpPlayerInfo->szTeacher + parm;
	sResultMsg += sign + lpPlayerInfo->szPerson + parm;

	strtmp.Format("%d",lpPlayerInfo->nQianNeng);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nEat);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nMax_Eat);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nDrink);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nMax_Drink);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nKillNpc);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nKillPlayer);
	sResultMsg += sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nKilled);
	sResultMsg +=  sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nPlayerStatus);
	sResultMsg +=  sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nBetray);
	sResultMsg +=  sign + strtmp + parm;
	strtmp.Format("%d",lpPlayerInfo->nMudTime);
	sResultMsg +=  sign + strtmp + parm;

	sResultMsg += sign + CString("PLAYEREND") + parm;

	sResultMsg += GatherPlayerSkillData(lpPlayerInfo);
	sResultMsg += GatherPlayerEquipData(lpPlayerInfo);
	sResultMsg += GatherMapData(lpPlayerInfo);
	strcpy(Result, "OK");
	return sResultMsg;
//	strcpy(Result,"OK\t");
//	strcat(Result,sResultMsg);
}

CString CCmdPlayerLogon::GatherPlayerSkillData(CPlayerInfo * lpPlayerInfo)
{
	TObjectSkill *lpPlayerSkill;
	int i,j;
	CString sResultMsg,parm,sign;
	char itmpString[20];
	sign = CString("'");
	parm = CString("'\t");
	sResultMsg = sign+CString("PLAYERSKILL") + parm;
	j = lpPlayerInfo->listskill.GetCount();
	for(i=0;i<j;i++)
	{
		lpPlayerSkill = lpPlayerInfo->listskill.GetAt(lpPlayerInfo->listskill.FindIndex(i));
		sResultMsg += sign+CString("RECORDE")+parm;

		sResultMsg += sign+lpPlayerSkill->lpSkill->szCName+parm;
		sResultMsg += sign+lpPlayerSkill->lpSkill->szEName+parm;

		_itoa(lpPlayerSkill->nScore,itmpString,10);
		sResultMsg += sign+itmpString+parm;
		_itoa(lpPlayerSkill->nLevel,itmpString,10);
		sResultMsg += sign+itmpString+parm;
		sResultMsg += sign+lpPlayerSkill->szMapping+parm;
		sResultMsg += sign+CString("RECORDEEND")+parm;
	}
	sResultMsg += sign+CString("PLAYERSKILLEND")+parm;
	return sResultMsg;
}

CString CCmdPlayerLogon::GatherPlayerEquipData(CPlayerInfo * lpPlayerInfo)
{
	CGoods *lpGoods;
	CString sResultMsg=(""),parm,sign;
	CString szStatus;
	char szTemp[20];
	sign = CString("'");
	parm = CString("'\t");
	POSITION pos;
	// guanhua 2000/09/16 +1
	int nCount = 0;

	sResultMsg = sign+CString("PLAYEREQUIP") + parm;
	if(lpPlayerInfo->listequip.IsEmpty()) {
		return CString("");
	}
	pos = lpPlayerInfo->listequip.GetHeadPosition();
	while (pos != NULL) {
		lpGoods = lpPlayerInfo->listequip.GetNext(pos);
		if (lpGoods->lpGoods->nUsage & GP_invisible) continue;
		// guanhua 2000/09/16 +1
		nCount++;

		sResultMsg += sign+CString("RECORDE")+parm;
		sResultMsg += sign+lpGoods->lpGoods->szCName+parm;
		sResultMsg += sign+lpGoods->lpGoods->szUnit+parm;
		switch (lpGoods->lpGoods->nKinds) {
		case GK_food:
		case GK_book:
		case GK_drug:
		case GK_flag: 
		case GK_normal:
			sResultMsg += sign+"空"+parm;
			break;
		case GK_equip:
			if(dynamic_cast<CEquip*>(lpGoods)->nWearWhere == 0) {
				sResultMsg += sign+"空"+parm;
			} else {
				switch(dynamic_cast<CEquip*>(lpGoods)->nWearWhere)
				{
				case EW_neck:
					szStatus = "護頸";
					break;
				case EW_chest:
					szStatus = "護胸";
					break;
				case EW_abdomen:
					szStatus = "護腹";
					break;
				case EW_wrist:
					szStatus = "護腕";
					break;
				case EW_knee:
					szStatus = "護膝";
					break;
				case EW_head:
					szStatus = "護頭";
					break;
				case EW_hand:
					szStatus = "護手";
					break;
				case EW_foot:
					szStatus = "護腳";
					break;
				case EW_body:
					szStatus = "護身";
					break;
				}
				sResultMsg += sign+szStatus+parm;
			}
			break;
		case GK_weapon:
			if(dynamic_cast<CWeapon*>(lpGoods)->bWield) {
				sResultMsg += sign+"使用中"+parm;
				lpPlayerInfo->lpWeapon = dynamic_cast<CWeapon*>(lpGoods);
			} else {
				sResultMsg += sign+"空"+parm;
			}
			break;
	/*	case GK_container:
			itoa(dynamic_cast<CContainer*>(lpGoods)->nLoaded,szTemp,10);
			sResultMsg += sign+CString(szTemp)+parm;
			break;*/
		case GK_jiudai:
			sResultMsg += sign+dynamic_cast<CJiuDai*>(lpGoods)->szLoadName+parm;
			break;
		default:
			sResultMsg += sign+"空"+parm;
		}
		_itoa(lpGoods->nCount, szTemp, 10);
		sResultMsg += sign+ CString(szTemp) + parm;
		sResultMsg += sign+CString("RECORDEEND")+parm;
	}
	sResultMsg += sign+CString("PLAYEREQUIPEND")+parm;

	// guanhua 2000/09/16 +1
	if(nCount == 0) return CString("");

	return sResultMsg;
}

CString CCmdPlayerLogon::GatherMapData(CPlayerInfo * lpPlayerInfo)
{
	CBaseMap *lpDataMap;
	TMapExit *lpMapExit;
	CPlayerInfo *lpOtherPlayerInfo;
	CNpc *lpNpc;

	CString sResultMsg,parm,sign;
	CString tmpMapName;
	int i;
	BOOL bFindHead = FALSE;

	sign = CString("'");
	parm = CString("'\t");
	sResultMsg = sign+CString("MAPDATA") + parm;

	EnterCriticalSection(&myglobs.csMaplist);
	lpDataMap = maplist.GetAt(lpPlayerInfo->pMapPosite);
	//地圖信息
	sResultMsg += sign+lpDataMap->szCName+parm;
	sResultMsg += sign+lpDataMap->szEName+parm;
	sResultMsg += sign+lpDataMap->szXFileName+parm;
	for(i=0;i<lpDataMap->listexit.GetCount();i++)
	{
		lpMapExit = lpDataMap->listexit.GetAt(lpDataMap->listexit.FindIndex(i));
		sResultMsg += sign + CString("EXITDATA") + parm;
		sResultMsg += sign + lpMapExit->szExitname + parm;
		sResultMsg += sign + lpMapExit->szNexeMap + parm;
		sResultMsg += sign + lpMapExit->szNextMapExitName + parm;
		sResultMsg += sign + lpMapExit->m_fPOSITION_X + parm;
		sResultMsg += sign + lpMapExit->m_fPOSITION_Y + parm;
		sResultMsg += sign+CString("EXITEND")+parm;
	}
	for(i=0;i<lpDataMap->listNpc.GetCount();i++)
	{
		lpNpc = lpDataMap->listNpc.GetAt(lpDataMap->listNpc.FindIndex(i));
		sResultMsg += sign + CString("NPCDATA") + parm;
		sResultMsg += sign + lpNpc->szCName + parm;
		sResultMsg += sign + lpNpc->szEName + parm;
		sResultMsg += sign + lpNpc->szXFileName + parm;
		sResultMsg += sign + lpNpc->szFamily + parm;
		if(lpNpc->nStatus == AOS_dead)
		{
			// Spock start: 檢查是否讓NPC復活
			if (lpNpc->nRecover > 0) lpNpc->nRecover--;
/*			if (lpNpc->nRecover <= 0) {
				lpNpc->nStatus = AOS_none;
				lpNpc->nEff_jing = lpNpc->nMax_jing = lpNpc->GetMaxJing();
				lpNpc->nEff_qi = lpNpc->nMax_qi = lpNpc->GetMaxQi();
				sResultMsg += sign + "" + parm;
				sResultMsg += sign + "" + parm;
			} else {
*/
				sResultMsg += sign + "DEAD" + parm;
				sResultMsg += sign + lpNpc->szPerson + parm;
//			}
			// Spock end
		}
		else
		{
			sResultMsg += sign + "" + parm;
			sResultMsg += sign + "" + parm;
		}
		sResultMsg += sign + CString("NPCEND") + parm;
	}
/*	parm = CString("\t");

	tmpMapName = lpDataMap->szEName;
	tmpMapName = tmpMapName+parm+lpPlayerInfo->szCName
					+parm+lpPlayerInfo->szEName+parm
					+lpPlayerInfo->szTilte+parm
					+(lpPlayerInfo->szFamily.IsEmpty()?"UNKONW":lpPlayerInfo->szFamily)+parm
					+lpPlayerInfo->szXFileName+parm
					+inet_ntoa(lpPlayerInfo->IPAddr.sin_addr)+parm;
	tmpMapName = szSomeonejoinMap + CString(" ") + tmpMapName;
*/
	// Spock +1
	POSITION pos;

	parm = CString("'\t");
/*	for(i=0;i<lpDataMap->listplayer.GetCount();i++)
	{
		lpOtherPlayerInfo = lpDataMap->listplayer.GetAt(lpDataMap->listplayer.FindIndex(i));
*/
// Spock start
	pos = lpDataMap->listplayer.GetHeadPosition();
	while(pos != NULL) {
		lpOtherPlayerInfo = lpDataMap->listplayer.GetNext(pos);
		if (lpOtherPlayerInfo == NULL) {
			AddRecordMsg("ERROR NULL pointer in GatherMapData, lpOtherPlayerInfo");
			continue;
		}
		if (strcmp(lpOtherPlayerInfo->szCheck, SZAOBJCHECK)) {
			AddRecordMsg("ERROR Bad data in GatherMapData, lpOtherPlayerInfo");
			continue;
		}
// Spock end
		sResultMsg += sign + CString("PLAYDATA") + parm;
		sResultMsg += sign + lpOtherPlayerInfo->szCName + parm;
		sResultMsg += sign + lpOtherPlayerInfo->szEName + parm;
		sResultMsg += sign + lpOtherPlayerInfo->szXFileName + parm;
		sResultMsg += sign + lpOtherPlayerInfo->szFamily + parm;
		if(lpOtherPlayerInfo->nStatus == AOS_dead)
		{
			sResultMsg += sign + "DEAD" + parm;
			sResultMsg += sign + lpOtherPlayerInfo->szPerson + parm;
		}
		else
		{
			sResultMsg += sign + "" + parm;
			sResultMsg += sign + "" + parm;
		}
		sResultMsg += sign + inet_ntoa(lpOtherPlayerInfo->IPAddr.sin_addr) + parm;
		// Spock +1 : 傳送玩家的頭銜 
		sResultMsg += sign + lpOtherPlayerInfo->szTilte + parm;
		sResultMsg += sign + CString("PLAYEND") + parm;

		//發送加入地圖數據給其他玩家
/*		if(lpOtherPlayerInfo->szEName != lpPlayerInfo->szEName)
		{
			// Spock +1
			lpOtherPlayerInfo->SendMsg(tmpMapName);
		}
*/
	}
	LeaveCriticalSection(&myglobs.csMaplist);
	sResultMsg += sign+CString("MAPDATAEND")+parm;
	return sResultMsg;
}
