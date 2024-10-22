#include "stdafx.h"
#include "XMudOS.h"
#include "CommandCheck.h"

#include "CmdPlayerLogon.h"
#include "map\MapInfo.h"
#include "npc\Npc.h"
#include "common.h"
#include "hash.h"

extern rmfullglobals myglobs;
extern CList <TClientConData *,TClientConData* >playersocketlist;
extern CList <CBaseMap*,CBaseMap*>maplist;

void CCommandCheck::GiveProc(LPVOID pvPlayer,char *szWho,char * szGoods,char *szAmount,char *Result)
{
	CBaseMap * lpDataMap;
	CPlayerInfo *lpPlayerInfo,*lpOtherPlayerInfo;
	CNpc * lpNpc;
	CGoods *lpGoods = NULL,*lpGiveGoods=NULL,*lpOppEquip=NULL;
	BOOL bFindOppPlayer = FALSE;
	BOOL bFindOppNPC = FALSE;
	CString szRet;
	CString szStatus;
	int nAmount = 0;
	int nWeight=0;
	POSITION pos,lastpos;
	BOOL bFindGoods = FALSE;
	BOOL bmore = FALSE;
	char szTemp[256];

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	if (lpPlayerInfo->nStatus != AOS_none) return;
	POSITION pMapPosite = lpPlayerInfo->pMapPosite;
	lpDataMap = maplist.GetAt(lpPlayerInfo->pMapPosite);
	EnterCriticalSection(&myglobs.csMaplist);
	EnterCriticalSection(&myglobs.csPlayerData);
	pos = lpDataMap->listplayer.GetHeadPosition();
	while(pos != NULL){
		lastpos = pos;
		lpOtherPlayerInfo = lpDataMap->listplayer.GetNext(pos);
		if (lpOtherPlayerInfo == NULL) {
			sprintf(szTemp, "ERROR NULL pointer in GiveProc, lpOtherPlayerInfo");
			AddRecordMsg(szTemp);
			lpDataMap->listplayer.RemoveAt(lastpos);
			continue;
		}
		if (strcmp(lpOtherPlayerInfo->szCheck, SZAOBJCHECK)) {
			sprintf(szTemp, "ERROR Bad data in GiveProc, lpOtherPlayerInfo");
			AddRecordMsg(szTemp);
			lpDataMap->listplayer.RemoveAt(lastpos);
			continue;
		}
		if((!strcmp(lpOtherPlayerInfo->szEName,szWho) || 
		   !strcmp(lpOtherPlayerInfo->szCName,szWho)) &&
			(lpOtherPlayerInfo->nStatus != AOS_dead)){
			bFindOppPlayer = TRUE;
			break;
		}
	}

	if(!bFindOppPlayer){
		pos = lpDataMap->listNpc.GetHeadPosition();
		while(pos != NULL){
			lpNpc = lpDataMap->listNpc.GetNext(pos);
			if((!strcmp(lpNpc->szEName,szWho) || 
			   !strcmp(lpNpc->szCName,szWho))
				&& (lpNpc->nStatus!=AOS_dead)){
				bFindOppNPC = TRUE;
				break;
			}
		}
		if(!bFindOppNPC){
			szRet.Format("%s FAIL 對方已經不在場內了!",SZGIVE);
			strcpy(Result,szRet);
		    LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
		    return;
		}else{
			wsprintf(Result,"%s FAIL 給予指令只能用於其他玩家，請使用Ask指令與NPC交談",SZGIVE);
		    LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
	}else	{
		if (lpOtherPlayerInfo->nStatus != AOS_none) {
			sprintf(Result, "%s FAIL 對方正在忙!", SZGIVE);
		    LeaveCriticalSection(&myglobs.csPlayerData);   
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}

		if(!strcmp(szGoods,"錢") || !_stricmp(szGoods,"money")){
			nAmount = atoi(szAmount);
			if(nAmount<1) nAmount=1;
			if(nAmount>MAXMONEY) nAmount=MAXMONEY;
			if(lpPlayerInfo->nMoney >= nAmount){
				if (lpOtherPlayerInfo->nMoney+nAmount <= MAXMONEY) {
					lpPlayerInfo->nMoney -= nAmount;
					lpOtherPlayerInfo->nMoney +=nAmount;
					lpPlayerInfo->SendAllInfo();
					lpOtherPlayerInfo->SendAllInfo();
					szRet.Format("%s OK %s給你%d枚銅錢。",SZGIVE,lpPlayerInfo->szCName,nAmount);
					lpOtherPlayerInfo->SendMsg(szRet);
					sprintf(Result,"%s OK 你給%s%d枚銅錢。",SZGIVE,lpOtherPlayerInfo->szCName,nAmount);
				} else {
					sprintf(Result, "%s FAIL 對方無法帶這麼多錢", SZGIVE);
				}
			}else
			    sprintf(Result,"%s FAIL 你的錢不夠!",SZGIVE);
						
		    LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}

		//若給物品
		pos = lpPlayerInfo->listequip.GetHeadPosition();
		while (pos != NULL) {
			lastpos = pos;
			lpGoods = lpPlayerInfo->listequip.GetNext(pos);
			if (lpGoods != NULL) {
				if (lpGoods->lpGoods->szEName == szGoods || lpGoods->lpGoods->szCName == szGoods){
					bFindGoods = TRUE;
					break;	 
				}
			}
		}

		if(bFindGoods){
			nAmount = atoi(szAmount);
			if( nAmount > 100000 ) nAmount = 100000;
			if(nAmount<1) nAmount=1;

			if(lpGoods->nCount<nAmount){
				szRet.Format("%s FAIL 這項物品數量不足。",SZGIVE);
				strcpy(Result, szRet);
		        LeaveCriticalSection(&myglobs.csPlayerData);
			    LeaveCriticalSection(&myglobs.csMaplist);
				return;
			}
			if(lpGoods->lpGoods->nKinds==GK_equip){
				if(dynamic_cast<CEquip *>(lpGoods)->nWearWhere!=0){
					szRet.Format("%s FAIL 這項物品正在使用中。",SZGIVE);
					strcpy(Result, szRet);
		            LeaveCriticalSection(&myglobs.csPlayerData);
			        LeaveCriticalSection(&myglobs.csMaplist);
					return;
				}
			}
			if(lpGoods->lpGoods->nKinds==GK_weapon){
				if(dynamic_cast<CWeapon *>(lpGoods)->bWield){
					szRet.Format("%s FAIL 這項物品正在使用中。",SZGIVE);
					strcpy(Result, szRet);
		            LeaveCriticalSection(&myglobs.csPlayerData);
			        LeaveCriticalSection(&myglobs.csMaplist);
					return;
				}
			}

			pos = lpOtherPlayerInfo->listequip.GetHeadPosition();
	        while (pos!=NULL)	{
		        lpOppEquip = lpOtherPlayerInfo->listequip.GetNext(pos);
				if( lpOppEquip->nCount < 0 ) lpOppEquip->nCount = 1;
				nWeight += lpOppEquip->lpGoods->nWeight * lpOppEquip->nCount;
			}
			if( nAmount < 0 ) nAmount = 1;
			if( lpGoods->lpGoods->nWeight > 0 )	{
				if( nAmount > ((lpOtherPlayerInfo->nStr*1000) - nWeight )/lpGoods->lpGoods->nWeight )	{
					bmore = TRUE;
				}
			}
			if( nWeight <= 0 || bmore == TRUE ||
				(nWeight + (lpGoods->lpGoods->nWeight*nAmount))> (lpOtherPlayerInfo->nStr*1000) )	{
				szRet.Format("%s FAIL %s可攜帶重量%d，目前攜帶重量%d，%s重量%dx%d=%d，超過負重限制，無法接受%s的贈品!",
			                  SZGIVE,lpOtherPlayerInfo->szCName, lpOtherPlayerInfo->nStr*1000, nWeight,
			                  lpGoods->lpGoods->szCName, lpGoods->lpGoods->nWeight,
							  nAmount,lpGoods->lpGoods->nWeight*nAmount,lpPlayerInfo->szCName);
                lpOtherPlayerInfo->SendMsg(szRet);
				sprintf(Result,"%s FAIL 對方負荷不了重量!",SZGIVE);
		        LeaveCriticalSection(&myglobs.csPlayerData);
			    LeaveCriticalSection(&myglobs.csMaplist);
				return;
			}

			if(lpGoods->lpGoods->nKinds==GK_jiudai)
				szStatus = dynamic_cast<CJiuDai *>(lpGoods)->szLoadName;
			else
				szStatus="空";


            lpGiveGoods = lpOtherPlayerInfo->GetGoods(szGoods);
						
			if(lpGiveGoods==NULL)	{
				lpGiveGoods = GetGoodsClass(lpGoods->lpGoods->szEName,lpGoods->lpGoods->nKinds);
				if(lpGiveGoods!=NULL)	{
					lpGiveGoods->nNew = lpGoods->nNew;
					lpGiveGoods->nCount = nAmount;
                    lpOtherPlayerInfo->listequip.AddTail(lpGiveGoods);
				}else	{
					sprintf(szTemp, "give fail! GetGoodsClass return null");
					AddRecordMsg(szTemp);
				    szRet.Format("%s FAIL 給予失敗。",SZGIVE);
					strcpy(Result, szRet);
		            LeaveCriticalSection(&myglobs.csPlayerData);
			        LeaveCriticalSection(&myglobs.csMaplist);
					return;
				}
			}else	{
			    lpGiveGoods->nCount+=nAmount;
                lpGiveGoods->nNew = lpGoods->nNew; 
			}
			lpGoods->nCount-=nAmount;
            lpGoods->nNew = lpGoods->lpGoods->nDurable;
			if (lpGoods->nCount <= 0) lpPlayerInfo->listequip.RemoveAt(lastpos);
            szRet.Format("%s OK %s交給你%d%s%s。",SZGIVE,lpPlayerInfo->szCName,nAmount,lpGoods->lpGoods->szUnit,lpGoods->lpGoods->szCName);
			lpOtherPlayerInfo->SendMsg(szRet);
			szRet.Format("%s %s %s %d %s %d",SZADDGOODS,lpGoods->lpGoods->szCName,szStatus,nAmount,lpGoods->lpGoods->szUnit,0);
			lpOtherPlayerInfo->SendMsg(szRet);
			szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,lpGoods->lpGoods->szCName,szStatus,nAmount,lpGoods->lpGoods->szUnit,0);
			lpPlayerInfo->SendMsg(szRet);
			szRet.Format("%s OK 你交給%s%d%s%s。",SZGIVE,lpOtherPlayerInfo->szCName,nAmount,lpGoods->lpGoods->szUnit,lpGoods->lpGoods->szCName);
			      
		}else{
			szRet.Format("%s FAIL 你沒有這個東西。",SZGIVE);
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	LeaveCriticalSection(&myglobs.csMaplist);
	strcpy(Result, szRet);
}

void CCommandCheck::DropProc(LPVOID pvPlayer,char * szDropGoods,char *Result)
{
	CPlayerInfo *lpPlayerInfo;
    CString szRet;
    CGoods *lpGoods;
	CString szStatus;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	if (lpPlayerInfo->nStatus != AOS_none) return;
	EnterCriticalSection(&myglobs.csPlayerData);
	lpGoods = lpPlayerInfo->GetGoods(szDropGoods);
     
	if(lpGoods!=NULL){
		if(lpGoods->lpGoods->nUsage & GP_invisible)	{
            szRet.Format("%s FAIL 你沒有這樣東西。",SZDROP);
			strcpy(Result, szRet);
			LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}
		if(lpGoods->lpGoods->nUsage & GP_nodrop){
            szRet.Format("%s FAIL 這項物品是不能丟棄的。",SZDROP);
			strcpy(Result, szRet);
			LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}
		
		if(lpGoods->lpGoods->nKinds==GK_equip){
			if(dynamic_cast<CEquip *>(lpGoods)->nWearWhere!=0){
				szRet.Format("%s FAIL 這項物品正在使用中。",SZDROP);
				strcpy(Result, szRet);
				LeaveCriticalSection(&myglobs.csPlayerData);
				return;
			}
		}
		if(lpGoods->lpGoods->nKinds==GK_weapon){
			if(dynamic_cast<CWeapon *>(lpGoods)->bWield){
				szRet.Format("%s FAIL 這項物品正在使用中。",SZDROP);
				strcpy(Result, szRet);
				LeaveCriticalSection(&myglobs.csPlayerData);
				return;
			}
		}
	    if(lpGoods->lpGoods->nKinds==GK_jiudai)
			szStatus = dynamic_cast<CJiuDai *>(lpGoods)->szLoadName;
		else
		    szStatus="空";
		szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,lpGoods->lpGoods->szCName,szStatus,1,lpGoods->lpGoods->szUnit,0);
		lpPlayerInfo->SendMsg(szRet);
		szRet.Format("%s OK %s將%s丟到地上。",SZDROP,lpPlayerInfo->szCName,szDropGoods);
		lpPlayerInfo->SubGoods(lpGoods->lpGoods->szEName);
	}
	else
		szRet.Format("%s FAIL 你沒有這個東西。",SZDROP);
	
	LeaveCriticalSection(&myglobs.csPlayerData);
    strcpy(Result, szRet);
}

void CCommandCheck::RentProc(LPVOID pvPlayer,char * szRentGoods,char *Result)
{
	CPlayerInfo *lpPlayerInfo;
    CString szRet;
    CGoods *lpGoods;
	CString szStatus;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	if (lpPlayerInfo->nStatus != AOS_none) return;
	EnterCriticalSection(&myglobs.csPlayerData);
	lpGoods = lpPlayerInfo->GetGoods(szRentGoods);
	if(lpGoods!=NULL){
		if(lpGoods->lpGoods->nUsage & GP_invisible){
            szRet.Format("%s FAIL 你沒有這樣東西。",SZDROP);
			strcpy(Result, szRet);
			LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}
		if(lpGoods->lpGoods->nUsage & GP_nodrop){
            szRet.Format("%s FAIL 這項物品是不能丟棄的。",SZDROP);
			strcpy(Result, szRet);
			LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}
		if(lpGoods->lpGoods->nKinds==GK_equip){
			if(dynamic_cast<CEquip *>(lpGoods)->nWearWhere!=0)
			{
				szRet.Format("%s FAIL 這項物品正在使用中。",SZDROP);
				strcpy(Result, szRet);
				LeaveCriticalSection(&myglobs.csPlayerData);
				return;
			}
		}
		if(lpGoods->lpGoods->nKinds==GK_weapon){
			if(dynamic_cast<CWeapon *>(lpGoods)->bWield){
				szRet.Format("%s FAIL 這項物品正在使用中。",SZDROP);
				strcpy(Result, szRet);
				LeaveCriticalSection(&myglobs.csPlayerData);
				return;
			}
		}
	    if(lpGoods->lpGoods->nKinds==GK_jiudai)
			szStatus = dynamic_cast<CJiuDai *>(lpGoods)->szLoadName;
		else
		    szStatus="空";
		szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,lpGoods->lpGoods->szCName,szStatus,1,lpGoods->lpGoods->szUnit,0);
		lpPlayerInfo->SendMsg(szRet);
		szRet.Format("%s OK %s將%s寄放出去。",SZDROP,lpPlayerInfo->szCName,szRentGoods);
		lpPlayerInfo->SubGoods(lpGoods->lpGoods->szEName);
	}else
		szRet.Format("%s FAIL 你沒有這個東西。",SZDROP);
	LeaveCriticalSection(&myglobs.csPlayerData);
    strcpy(Result, szRet);
}

