#include "stdafx.h"
#include "XmudOS.h"
#include "CmdPlayerLogon.h"
#include "CommandCheck.h"
#include "map\MapInfo.h"
#include "npc\Npc.h"
#include "Common.h"
#include "Condition.h"
extern rmfullglobals myglobs;

void CCommandCheck::UseProc(LPVOID pvPlayer,char *szWhichItem, int nUseNum,char *Result)
{
	CGoods *lpGoods = NULL;
	CPlayerInfo *lpPlayerInfo;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	EnterCriticalSection(&myglobs.csPlayerData);
	lpGoods = lpPlayerInfo->GetGoods(szWhichItem);
	if(lpGoods == NULL)	{
		wsprintf(Result,"%s FAIL %s並不存在",SZUSE,szWhichItem);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	if( nUseNum > 1000 || nUseNum <=0 )
		nUseNum = 1;
	
	if(lpGoods->lpGoods->nKinds & GK_food)	{
		if(lpPlayerInfo->nStatus != AOS_none)	{
		    wsprintf(Result,"%s FAIL 你正在忙",SZUSE);
			LeaveCriticalSection(&myglobs.csPlayerData);
		    return;	
		}else if(lpPlayerInfo->nEat>=lpPlayerInfo->nMax_Eat)	{
			wsprintf(Result,"%s FAIL 你已經吃的太飽，再也塞不下任何東西了。",SZUSE);
		    LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}
		
		EatProc(lpPlayerInfo,dynamic_cast<CFood*>(lpGoods), nUseNum,Result);
        LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}else if(lpGoods->lpGoods->nKinds & GK_jiudai)	{
		if(lpPlayerInfo->nStatus != AOS_none)	{
		    wsprintf(Result,"%s FAIL 你正在忙",SZUSE);
		    LeaveCriticalSection(&myglobs.csPlayerData);
			return;	
		}else if(lpPlayerInfo->nDrink>=lpPlayerInfo->nMax_Drink)	{
			wsprintf(Result,"%s FAIL 你已經喝的太撐，再也灌不下一滴水了。",SZUSE);
		    LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}
		
		DrinkProc(lpPlayerInfo,dynamic_cast<CJiuDai*>(lpGoods), nUseNum, Result);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}else if(lpGoods->lpGoods->nKinds & GK_drug)	{
		if(lpPlayerInfo->nStatus != AOS_none)	{
			if(lpPlayerInfo->nStatus == AOS_kill)	{
				lpPlayerInfo->nBusy += 4;
			}else	{
		        wsprintf(Result,"%s FAIL 你正在忙",SZUSE);
				LeaveCriticalSection(&myglobs.csPlayerData);
		        return;
			}
		}
		
		DrugUseProc(lpPlayerInfo,dynamic_cast<CDrug*>(lpGoods), nUseNum, Result);
	    LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}else if(lpGoods->lpGoods->nKinds & GK_flag){
        wsprintf(Result,"%s FAIL 你沒有這樣東西呀",SZUSE);
		LeaveCriticalSection(&myglobs.csPlayerData);
        return;
	}

	wsprintf(Result,"%s FAIL %s不能使用",SZUSE,szWhichItem);
	LeaveCriticalSection(&myglobs.csPlayerData);
	return;
}
void CCommandCheck::RentListProc(LPVOID pvPlayer,char *Result)
{
	CGoods *lpEquip = NULL;
	CPlayerInfo *lpPlayerInfo;
	CString tmpMsg = _T("");
	CString tmpMsg2 = _T("");
	lpPlayerInfo = (CPlayerInfo*)pvPlayer;

	EnterCriticalSection(&myglobs.csPlayerData);

	int j = lpPlayerInfo->listrentequip.GetCount();
	for(int i=0;i<j;i++){
		lpEquip = lpPlayerInfo->listrentequip.GetAt(lpPlayerInfo->listrentequip.FindIndex(i));
		if(lpEquip != NULL)	{
			tmpMsg2.Format("%s[%d%s]\t",lpEquip->lpGoods->szCName,lpEquip->nCount,lpEquip->lpGoods->szUnit);
			tmpMsg += tmpMsg2;
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	if(j != 0)
		wsprintf(Result,"%s %s",SZRENTLIST,tmpMsg);
	else
		wsprintf(Result,"%s 您沒有寄放物品\t",SZRENTLIST);

	return;

}

void CCommandCheck::EatProc(CPlayerInfo* lpPlayerInfo,CFood *lpFood, int iUseNum,char *Result)
{
	CString szSend;

	int DelNum = 1;
	if( iUseNum >= ((lpFood->nCount * lpFood->lpFood->nMaxRemain) + lpFood->nRemain))	{
		iUseNum = ((lpFood->nCount * lpFood->lpFood->nMaxRemain) + lpFood->nRemain);
	}
	if( iUseNum == 1 )	{
		iUseNum = 1;
		lpFood->nRemain--;
	}else	{
			if( ((iUseNum * lpFood->lpFood->nSupply) + lpPlayerInfo->nEat) > lpPlayerInfo->nMax_Eat )	{
					iUseNum = (((lpPlayerInfo->nMax_Eat - lpPlayerInfo->nEat) / lpFood->lpFood->nSupply) + 1);
					lpFood->nRemain-= (iUseNum % lpFood->lpFood->nMaxRemain);
					DelNum = (iUseNum / lpFood->lpFood->nMaxRemain);
					lpFood->nCount -= (DelNum - 1);
			}else {
				lpFood->nRemain -= ( iUseNum  % lpFood->lpFood->nMaxRemain);
				DelNum = ( iUseNum / lpFood->lpFood->nMaxRemain);
				lpFood->nCount -= (DelNum - 1);
			}
	}
	lpPlayerInfo->nEat += (lpFood->lpFood->nSupply * iUseNum);
	lpPlayerInfo->nDrink += (lpFood->lpFood->nDrink * iUseNum);
		if(lpPlayerInfo->nEat > lpPlayerInfo->nMax_Eat)
			lpPlayerInfo->nEat = lpPlayerInfo->nMax_Eat;
		if(lpPlayerInfo->nDrink > lpPlayerInfo->nMax_Drink)
			lpPlayerInfo->nDrink = lpPlayerInfo->nMax_Drink;
	if(lpFood->nRemain <= 0)	{
		wsprintf(Result,"%s OK 你把剩下的%s都吃完. %d,%d", SZUSE, lpFood->lpGoods->szCName, lpPlayerInfo->nEat,
		lpPlayerInfo->nDrink);
		szSend.Format("%s %s %s %d %s",	SZSUBGOODS,	lpFood->lpGoods->szCName,"空", DelNum, lpFood->lpGoods->szUnit);
		lpFood->nRemain = lpFood->lpFood->nMaxRemain;
		lpPlayerInfo->SubGoods(lpFood->lpGoods->szEName);
		lpPlayerInfo->SendMsg(szSend);
	}else	{
		wsprintf(Result,"%s OK 你拿出%s咬了幾口. %d,%d", SZUSE,	lpFood->lpGoods->szCName,lpPlayerInfo->nEat,
		lpPlayerInfo->nDrink);
	}
}

void CCommandCheck::DrinkProc( CPlayerInfo *lpPlayerInfo, CJiuDai *lpJiuDai, int iUseNum,char *Result)
{
	CString szSend;

	if(lpJiuDai->nRemain <= 0)	{
		wsprintf(Result,"%s FAIL %s裡面一滴水都沒有了.",SZUSE,lpJiuDai->lpGoods->szCName);
		return;
	}


	if( iUseNum > lpJiuDai->nRemain )	{
		iUseNum = lpJiuDai->nRemain;
	}else if( (lpPlayerInfo->nDrink + ( lpJiuDai->nDrink * iUseNum )) > lpPlayerInfo->nMax_Drink )	{
		iUseNum = (((lpPlayerInfo->nMax_Drink - lpPlayerInfo->nDrink) / lpJiuDai->nDrink) + 1);
	}

	lpJiuDai->nRemain -= iUseNum;
	lpPlayerInfo->nEat += ( lpJiuDai->nSupply * iUseNum );
	lpPlayerInfo->nDrink += ( lpJiuDai->nDrink * iUseNum ); 
	if(lpPlayerInfo->nEat > lpPlayerInfo->nMax_Eat)
		lpPlayerInfo->nEat = lpPlayerInfo->nMax_Eat;
	if(lpPlayerInfo->nDrink > lpPlayerInfo->nMax_Drink)
		lpPlayerInfo->nDrink = lpPlayerInfo->nMax_Drink;

	if(lpJiuDai->nRemain <= 0)	{
		wsprintf(Result,"%s OK 你拿出%s一飲而盡. %d,%d", SZUSE, lpJiuDai->lpGoods->szCName, lpPlayerInfo->nEat,
				lpPlayerInfo->nDrink);

		szSend.Format("%s %s %s %d %s", SZSUBGOODS, lpJiuDai->lpGoods->szCName, lpJiuDai->szLoadName, 1,
			lpJiuDai->lpGoods->szUnit);
		lpPlayerInfo->SendMsg(szSend);
		lpJiuDai->szLoadName = "空";
		szSend.Format("%s %s %s %d %s", SZADDGOODS, lpJiuDai->lpGoods->szCName, lpJiuDai->szLoadName, 1, 
			lpJiuDai->lpGoods->szUnit);
		lpPlayerInfo->SendMsg(szSend);
		return;
	}
	wsprintf(Result,"%s OK 你拿出%s喝了幾口. %d,%d", SZUSE, lpJiuDai->lpGoods->szCName, lpPlayerInfo->nEat,
			lpPlayerInfo->nDrink);
}

void CCommandCheck::DrugUseProc(CPlayerInfo *lpPlayerInfo,CDrug *lpDrug, int dUseNum,char *Result)
{
	CString szSend;
	char szTemp[40];
	szTemp[0] = 0;

	if( dUseNum > lpDrug->nCount )
		dUseNum = lpDrug->nCount;
	else if( dUseNum < 0 )
		dUseNum = 1;
	lpDrug->nCount -= (dUseNum - 1);

	sprintf(Result,"%s OK 你服用了%s後",SZUSE,lpDrug->lpGoods->szCName);
	if(lpDrug->lpDrug->nQi) {
		lpPlayerInfo->nMax_qi += (lpDrug->lpDrug->nQi * dUseNum);
		if(lpPlayerInfo->nMax_qi > lpPlayerInfo->GetMaxQi()) {
			lpPlayerInfo->nMax_qi = lpPlayerInfo->GetMaxQi();
		}
		lpPlayerInfo->nEff_qi += (lpDrug->lpDrug->nQi * dUseNum);
		if(lpPlayerInfo->nEff_qi > lpPlayerInfo->GetMaxQi()) {
			lpPlayerInfo->nEff_qi = lpPlayerInfo->GetMaxQi();
		}
		strcat(Result,szTemp);
	}
	if(lpDrug->lpDrug->nJing) {
		lpPlayerInfo->nMax_jing += (lpDrug->lpDrug->nJing * dUseNum);
		if(lpPlayerInfo->nMax_jing > lpPlayerInfo->GetMaxJing()) {
			lpPlayerInfo->nMax_jing = lpPlayerInfo->GetMaxJing();
		}
		lpPlayerInfo->nEff_jing += (lpDrug->lpDrug->nJing * dUseNum);
		if(lpPlayerInfo->nEff_jing > lpPlayerInfo->GetMaxJing()) {
			lpPlayerInfo->nEff_jing = lpPlayerInfo->GetMaxJing();
		}
		strcat(Result,szTemp);
	}

	szSend.Format("%s %s %s %d %s",SZSUBGOODS,lpDrug->lpGoods->szCName,"空", dUseNum,lpDrug->lpGoods->szUnit);
	lpPlayerInfo->SubGoods(lpDrug->lpGoods->szEName);
	lpPlayerInfo->SendMsg(szSend);
	lpPlayerInfo->SendAllInfo();
}