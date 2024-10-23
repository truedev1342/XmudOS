#include "stdafx.h"
#include "XmudOS.h"
#include "CommandCheck.h"
#include "CmdPlayerLogon.h"
#include "map\MapInfo.h"
#include "npc\Npc.h"
#include "skill\skill\Skill.h"

extern rmfullglobals myglobs;

void CCommandCheck::AskProc(LPVOID pvPlayer,char *szWho, char * szSth1, char * szSth2, char *Result)//ask npc
{
	CPlayerInfo *lpPlayerInfo;
	CNpc * lpNpc;
	CBaseMap * lpDataMap;
	BOOL bFindOppNPC = FALSE;
	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	if (lpPlayerInfo->nStatus != AOS_none) return;
	POSITION pMapPosite = lpPlayerInfo->pMapPosite;
	EnterCriticalSection(&myglobs.csMaplist);
	EnterCriticalSection(&myglobs.csPlayerData);	
	lpDataMap = maplist.GetAt(lpPlayerInfo->pMapPosite);
	POSITION pos = lpDataMap->listNpc.GetHeadPosition();
	while(pos != NULL)	{
		lpNpc = lpDataMap->listNpc.GetNext(pos);
		if(!stricmp(lpNpc->szEName,szWho) || !stricmp(lpNpc->szCName,szWho))	{
			if(lpNpc->nStatus != 0)	{
				wsprintf(Result,"%s FAIL %s正忙著呢!", SZASK, lpNpc->szCName);
				LeaveCriticalSection(&myglobs.csPlayerData);
                LeaveCriticalSection(&myglobs.csMaplist);
				return;
			}
			bFindOppNPC = TRUE;
			break;
		}
	}
	if(!bFindOppNPC)	{
		wsprintf(Result,"%s FAIL 此人不在這個地圖中!", SZASK);
		LeaveCriticalSection(&myglobs.csPlayerData);
        LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}
	TRetInfo ri;

	char ch = szSth1[0];
	if( ch == '_')
		strcpy(szSth1, "_CannotAsk_");
	if(!strcmp(szSth2,"$NONE$"))
		ri = lpNpc->DoAsk(lpPlayerInfo, szSth1);
	else
		ri = lpNpc->DoAsk(lpPlayerInfo, szSth1, szSth2);
	
	CString sResultMsg,CTemp;
	CTemp = CString(",'NPCASK'");
	for (int i=0;i<lpNpc->nAsk;i++) {
		if (lpNpc->nAskAttribute[i] & NPCASK_visible) {
			CTemp += CString(",'RC','");
			CTemp += lpNpc->szAsk[i];
			CTemp += CString("','RCEND'");
		}
	}
	//dainty add
	CTemp += CString(",'RC','");
	CTemp += "武功";
	CTemp += CString("','RCEND'");
	//dainty add end 
	CTemp += CString(",'NPCASKEND'");
	sResultMsg = ri.szRet + CTemp;
	wsprintf(Result,"%s %s %s",
		SZASK,ri.bRet?"OK":"FAIL",
		(char*)(LPCSTR)sResultMsg);
	LeaveCriticalSection(&myglobs.csPlayerData);
    LeaveCriticalSection(&myglobs.csMaplist);
	return;
}

BOOL CCommandCheck::GetNames( char *szSth1, char * szSth2 )
{
	FILE *nfp;
	char getname2[256];
	nfp = fopen(szSth2,"a+");
	if( nfp )	{
		while( fscanf(nfp,"%s ",getname2) !=EOF )	{
			if( !strcmp(szSth1 , getname2))	{
				return FALSE;
			}
		}
		fclose( nfp);
	}
	return TRUE;

}

void CCommandCheck::LookProc(LPVOID pvPlayer,char *szSth1, char * szSth2, char *Result)//look npc
{
	CPlayerInfo *lpPlayerInfo;
	CNpc * lpNpc;
	CBaseMap * lpDataMap;
	BOOL bFindOppNPC = FALSE;
	CGoods *lpGoods = NULL;
	CString szStr,szTemp;
	POSITION pos;
	CSkill *lpSkill=NULL;
	TBookNeedSkill *lpBookNeedSkill;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;

	EnterCriticalSection(&myglobs.csMaplist);
	EnterCriticalSection(&myglobs.csPlayerData);
	
	if(!strcmp(szSth2,"$QUERYNPC$"))
	{
		POSITION pMapPosite = lpPlayerInfo->pMapPosite;
		lpDataMap = maplist.GetAt(lpPlayerInfo->pMapPosite);
		pos = lpDataMap->listNpc.GetHeadPosition();
		while(pos != NULL)
		{
			lpNpc = lpDataMap->listNpc.GetNext(pos);
			if(!stricmp(lpNpc->szEName,szSth1) || !stricmp(lpNpc->szCName,szSth1))
			{
				if(lpNpc->nStatus != 0)
				{
					wsprintf(Result,"%s FAIL %s正忙著呢!", SZLOOK, lpNpc->szCName);
				
					LeaveCriticalSection(&myglobs.csPlayerData);
					LeaveCriticalSection(&myglobs.csMaplist);
					return;
				}
				bFindOppNPC = TRUE;
				break;
			}
		}
		if(!bFindOppNPC)
		{
			wsprintf(Result,"%s FAIL 此人不在這個地圖中!", SZLOOK);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
		TRetInfo ri = lpNpc->DoLook(lpPlayerInfo, szSth2);

		CString sResultMsg;
		sResultMsg = ri.szRet; // + CTemp;
		wsprintf(Result,"%s %s %s",
		SZLOOK,ri.bRet?"OK":"FAIL",
		(char*)(LPCSTR)sResultMsg);
		LeaveCriticalSection(&myglobs.csPlayerData);
		LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}else if(!strcmp(szSth2,"$QUERYGOODS$")){

		lpGoods = lpPlayerInfo->GetGoods(szSth1);
		if(lpGoods!=NULL){
			szStr.Format("%s %s %s", SZOKMSG, szGreenHigt, lpGoods->lpGoods->szdescribe);
			lpPlayerInfo->SendMsg(szStr);
			szStr="";
            sprintf(Result,"%s OK ",SZLOOK);
			switch(lpGoods->lpGoods->nKinds){
			case GK_food:
				szStr.Format("可食用%d次，",dynamic_cast<CFood *>(lpGoods)->lpFood->nMaxRemain);
				strcat(Result,szStr);
				break;
			case GK_drug:
				szStr = "服用後";
				if(dynamic_cast<CDrug *>(lpGoods)->lpDrug->nQi>0){
                    szTemp.Format("增加氣%d點，",dynamic_cast<CDrug *>(lpGoods)->lpDrug->nQi);
				    szStr += szTemp;
				}else if(dynamic_cast<CDrug *>(lpGoods)->lpDrug->nJing>0){
				    szTemp.Format("增加精%d點，",dynamic_cast<CDrug *>(lpGoods)->lpDrug->nJing);
				    szStr += szTemp;
				}else if(dynamic_cast<CDrug *>(lpGoods)->lpDrug->nForce>0){
				    szTemp.Format("增加內力%d點，",dynamic_cast<CDrug *>(lpGoods)->lpDrug->nForce);
				    szStr += szTemp;
				}else if(dynamic_cast<CDrug *>(lpGoods)->lpDrug->nJingli>0){
				    szTemp.Format("增加精力%d點，",dynamic_cast<CDrug *>(lpGoods)->lpDrug->nJingli);
				    szStr += szTemp;
				}else if(dynamic_cast<CDrug *>(lpGoods)->lpDrug->nStr>0){
				    szTemp.Format("增加臂力%d點，",dynamic_cast<CDrug *>(lpGoods)->lpDrug->nStr);
				    szStr += szTemp;
				}else if(dynamic_cast<CDrug *>(lpGoods)->lpDrug->nInt>0){
				    szTemp.Format("增加悟性%d點，",dynamic_cast<CDrug *>(lpGoods)->lpDrug->nInt);
                    szStr += szTemp;
				}else if(dynamic_cast<CDrug *>(lpGoods)->lpDrug->nCon>0){
				    szTemp.Format("增加根骨%d點，",dynamic_cast<CDrug *>(lpGoods)->lpDrug->nCon);
                    szStr += szTemp;
				}else if(dynamic_cast<CDrug *>(lpGoods)->lpDrug->nDex>0){
				    szTemp.Format("增加身法%d點，",dynamic_cast<CDrug *>(lpGoods)->lpDrug->nDex);
                    szStr += szTemp;
				}
				strcat(Result,szStr);
				break;
			case GK_book:						
				szStr.Format("最高可練成%d級，",dynamic_cast<CBook *>(lpGoods)->lpBook->nMaxLevel);
				szStr += "欲自行練習必先具有一些武功的基礎，";
				pos = dynamic_cast<CBook *>(lpGoods)->lpBook->listNeedSkill.GetHeadPosition();
				while(pos!=NULL){
					lpBookNeedSkill = dynamic_cast<CBook *>(lpGoods)->lpBook->listNeedSkill.GetNext(pos);
					if(lpBookNeedSkill!=NULL){
						lpSkill = GetSkillClass(lpBookNeedSkill->szNeedSkillEName);
						if(lpSkill!=NULL){
						    szTemp.Format("%s需%d級，",lpSkill->szCName,lpBookNeedSkill->nNeedSkillLevel);
					        szStr += szTemp;
						}
					}
				}
				if(lpSkill) delete lpSkill;
				if(dynamic_cast<CBook *>(lpGoods)->lpBook->nNeedInt>0){
					szTemp.Format("悟性需%d級，",dynamic_cast<CBook *>(lpGoods)->lpBook->nNeedInt);
					szStr += szTemp;
				}
				if(dynamic_cast<CBook *>(lpGoods)->lpBook->nNeedStr>0){
					szTemp.Format("臂力需%d級，",dynamic_cast<CBook *>(lpGoods)->lpBook->nNeedStr);
					szStr += szTemp;
				}
				if(dynamic_cast<CBook *>(lpGoods)->lpBook->nNeedCon>0){
					szTemp.Format("根骨需%d級，",dynamic_cast<CBook *>(lpGoods)->lpBook->nNeedCon);
					szStr += szTemp;
				}
				if(dynamic_cast<CBook *>(lpGoods)->lpBook->nNeedDex>0){
					szTemp.Format("身法需%d級，",dynamic_cast<CBook *>(lpGoods)->lpBook->nNeedDex);
					szStr += szTemp;
				}
				if(dynamic_cast<CBook *>(lpGoods)->lpBook->nNeedForce>0){
				    szTemp.Format("內力需%d級，",dynamic_cast<CBook *>(lpGoods)->lpBook->nNeedForce);
					szStr += szTemp;
				}		
				szStr += "方能自行學習。";                        		
				strcat(Result,szStr);	
				break;
			case GK_weapon:
                szStr.Format("攻擊力%d，防禦力%d，",
					dynamic_cast<CWeapon *>(lpGoods)->lpWeapon->nAttack,
					dynamic_cast<CWeapon *>(lpGoods)->lpWeapon->nDefance);
				strcat(Result,szStr);
				break;
			case GK_equip:
				szStr.Format("防禦力%d，抗內力%d，",
					dynamic_cast<CEquip *>(lpGoods)->lpEquip->nDefance,
					dynamic_cast<CEquip *>(lpGoods)->lpEquip->nDefanceForce);
				strcat(Result,szStr);
				break;
			case GK_jiudai:
				szStr.Format("裝滿可飲用%d次，",dynamic_cast<CJiuDai *>(lpGoods)->lpJiuDai->nMaxRemain);
				strcat(Result,szStr);
				break;
			}
			szTemp.Format("重量%d，價格%d枚銅錢。",lpGoods->lpGoods->nWeight,lpGoods->lpGoods->nCost);
            strcat(Result,szTemp);
			int nWeight=0;
			pos = lpPlayerInfo->listequip.GetHeadPosition();
	        while (pos!=NULL){
		        lpGoods = lpPlayerInfo->listequip.GetNext(pos);
		        nWeight += lpGoods->lpGoods->nWeight * lpGoods->nCount;
			}
			szTemp.Format("你目前攜帶物品總重量為%d，最多可載重%d。",nWeight,lpPlayerInfo->nStr*1000);
			strcat(Result,szTemp);
		}
		else
			wsprintf(Result,"%s FAIL %s",SZLOOK,"你沒有這東西。");
		
		LeaveCriticalSection(&myglobs.csPlayerData);
		LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}else{
        wsprintf(Result,"%s FAIL %s",SZLOOK,"請在look後輸入要查看的物品名稱或叫住NPC再輸入look查看NPC。");
		LeaveCriticalSection(&myglobs.csPlayerData);
		LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}

}
