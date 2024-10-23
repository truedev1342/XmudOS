#include "stdafx.h"
#include "XmudOS.h"
#include "CommandCheck.h"
#include "CmdPlayerLogon.h"
#include "map\MapInfo.h"
#include "goods\goods\Goods.h"
#include "Common.h"

extern rmfullglobals myglobs;

void CCommandCheck::ArmProc(LPVOID pvPlayer,char *szWhichItem,char *Result)
{
	CGoods *lpGoods = NULL;
	CEquip *lpEquip = NULL;
	CGoods *lpCheckGoods = NULL;
	CEquip *lpCheckEquip = NULL;
	CWeapon *lpWeapon = NULL;
	CPlayerInfo *lpPlayerInfo;
	CString szRet;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;

	EnterCriticalSection(&myglobs.csPlayerData);
	lpGoods = lpPlayerInfo->GetGoods(szWhichItem);



	if(lpGoods == NULL)
	{
		wsprintf(Result,"%s FAIL %s並不存在",SZARM,szWhichItem);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	if((lpGoods->lpGoods->nKinds == GK_weapon))
	{
		lpWeapon = dynamic_cast<CWeapon *>(lpGoods);

		if(lpWeapon->bWield)
		{
            wsprintf(Result,"%s FAIL %s已經使用中",SZARM,lpWeapon->lpGoods->szCName);
		    LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}

//=================================================================ANDY_NEW 2001.2.26 15:44==
		if(lpWeapon->lpWeapon->nKind == WK_throwing)
		{
			wsprintf(Result,"%s FAIL %s是暗器不能裝備",SZARM,lpWeapon->lpGoods->szCName);
			LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}
//===========================================================================================


		if(lpPlayerInfo->lpWeapon!=NULL)
		{//先卸下原來武器
            lpPlayerInfo->lpWeapon->bWield = FALSE; 
			szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,lpPlayerInfo->lpWeapon->lpGoods->szCName,"使用中",1,lpPlayerInfo->lpWeapon->lpGoods->szUnit,0);
		    lpPlayerInfo->SendMsg(szRet);
		
		    szRet.Format("%s %s %s %d %s %d",SZADDGOODS,lpPlayerInfo->lpWeapon->lpGoods->szCName,"空",1,lpPlayerInfo->lpWeapon->lpGoods->szUnit,0);
		    lpPlayerInfo->SendMsg(szRet);
			lpPlayerInfo->lpWeapon = NULL;
		}
		lpWeapon->bWield = TRUE;
		lpPlayerInfo->lpWeapon = lpWeapon;
	    
		szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,lpWeapon->lpGoods->szCName,"空",1,lpWeapon->lpGoods->szUnit,0);
		lpPlayerInfo->SendMsg(szRet);
		
		szRet.Format("%s %s %s %d %s %d",SZADDGOODS,lpWeapon->lpGoods->szCName,"使用中",1,lpWeapon->lpGoods->szUnit,0);
		lpPlayerInfo->SendMsg(szRet);			
			
		szRet.Format("%s OK %s%s",SZARM,lpPlayerInfo->szCName,lpWeapon->lpWeapon->szWieldMsg);		
	    
		strcpy(Result,szRet);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	
	else if((lpGoods->lpGoods->nKinds == GK_equip))
	{
        lpEquip = dynamic_cast<CEquip *>(lpGoods);

		if(lpEquip->nWearWhere!=0)
		{
			wsprintf(Result,"%s FAIL %s已經裝備",SZARM,szWhichItem);
			LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}
		CString szStatus;
		switch(lpEquip->lpEquip->nWhereWear)
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
		POSITION pos = lpPlayerInfo->listequip.GetHeadPosition();	    
	    while(pos != NULL)
		{
		     lpCheckGoods = lpPlayerInfo->listequip.GetNext(pos);
		     if(lpCheckGoods->lpGoods->nKinds == GK_equip)//如果是裝備
			 {
			     lpCheckEquip = dynamic_cast<CEquip *>(lpCheckGoods);
                 //若有相同部位已裝備,先卸下原裝備
			     if(lpCheckEquip->nWearWhere == lpEquip->lpEquip->nWhereWear)
				 {	 
                     szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,lpCheckEquip->lpGoods->szCName,szStatus,1,lpCheckEquip->lpGoods->szUnit,0);
		             lpPlayerInfo->SendMsg(szRet);
		             szRet.Format("%s %s %s %d %s %d",SZADDGOODS,lpCheckEquip->lpGoods->szCName,"空",1,lpCheckEquip->lpGoods->szUnit,0);
		             lpPlayerInfo->SendMsg(szRet);
		             lpCheckEquip->nWearWhere = 0;
				     break;
				 }
			 }
		}

		szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,lpEquip->lpGoods->szCName,"空",1,lpEquip->lpGoods->szUnit,0);
		lpPlayerInfo->SendMsg(szRet);
		szRet.Format("%s %s %s %d %s %d",SZADDGOODS,lpEquip->lpGoods->szCName,szStatus,1,lpEquip->lpGoods->szUnit,0);
		lpPlayerInfo->SendMsg(szRet);
		lpEquip->nWearWhere = lpEquip->lpEquip->nWhereWear;
		szRet.Format("%s OK %s%s",SZARM,lpPlayerInfo->szCName,lpEquip->lpEquip->szWearMsg);		 
		strcpy(Result,szRet);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	else
	{
		wsprintf(Result,"%s FAIL %s是不能裝備的",SZARM,szWhichItem);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
    
}

void CCommandCheck::UnArmProc(LPVOID pvPlayer,char *szWhichItem,char *Result)
{
	CGoods *lpGoods = NULL;
	CEquip *lpEquip = NULL;
	CWeapon *lpWeapon = NULL;
	CPlayerInfo *lpPlayerInfo;
	CString szRet;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
    
	EnterCriticalSection(&myglobs.csPlayerData);
	lpGoods = lpPlayerInfo->GetGoods(szWhichItem);
	
	if(lpGoods == NULL)
	{
		wsprintf(Result,"%s FAIL %s並不存在",SZUNARM,szWhichItem);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
    
	if((lpGoods->lpGoods->nKinds == GK_weapon))
	{
		lpWeapon = dynamic_cast<CWeapon *>(lpGoods);
		if(!lpWeapon->bWield)
		{
		    wsprintf(Result,"%s FAIL 你並未使用%s",SZUNARM,lpWeapon->lpGoods->szCName);
		    LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}
		
		lpWeapon->bWield = FALSE;
		szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,lpWeapon->lpGoods->szCName,"使用中",1,lpWeapon->lpGoods->szUnit,0);
		lpPlayerInfo->SendMsg(szRet);
		
		szRet.Format("%s %s %s %d %s %d",SZADDGOODS,lpWeapon->lpGoods->szCName,"空",1,lpWeapon->lpGoods->szUnit,0);
		lpPlayerInfo->SendMsg(szRet);
		
		lpPlayerInfo->lpWeapon = NULL;
		szRet.Format("%s OK %s%s",SZUNARM,lpPlayerInfo->szCName,lpWeapon->lpWeapon->szUnWieldMsg);		
	    
		strcpy(Result,szRet);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	else if((lpGoods->lpGoods->nKinds == GK_equip))
	{
        lpEquip = dynamic_cast<CEquip *>(lpGoods);
				
		CString szStatus;
		switch(lpEquip->nWearWhere)
		{
		case 0:
			szStatus = "空";
			break;
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
		if(szStatus!="空")
		{
		    szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,lpEquip->lpGoods->szCName,szStatus,1,lpEquip->lpGoods->szUnit,0);
		    lpPlayerInfo->SendMsg(szRet);
		    szRet.Format("%s %s %s %d %s %d",SZADDGOODS,lpEquip->lpGoods->szCName,"空",1,lpEquip->lpGoods->szUnit,0);
		    lpPlayerInfo->SendMsg(szRet);
		    lpEquip->nWearWhere = 0;
		    szRet.Format("%s OK %s%s",SZUNARM,lpPlayerInfo->szCName,lpEquip->lpEquip->szUnWearMsg);		
	        
			strcpy(Result,szRet);
			LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}
		else 
		{
			wsprintf(Result,"%s FAIL %s並未裝備",SZUNARM,szWhichItem);
			LeaveCriticalSection(&myglobs.csPlayerData);
			return;
		}
	}
	else
	{
		wsprintf(Result,"%s FAIL %s是不能裝備的",SZUNARM,szWhichItem);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
}
