// Nzm_DiziW.cpp: implementation of the CNzm_DiziW class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Nzm_DiziW.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNzm_DiziW::CNzm_DiziW()
{
    szCName = "書僮";
	szEName = "diziw";
	szSex = "M" ;
	nAge =  25;
	szLong = "這是書院的一個小書僮，在書院裡整理雜物。";
	nAttitude = NP_friendly | NP_apprentice | NP_guard;
    nShen = 100;

	szXFileName = "pmudsn04";
	szRoom		= "xy_zhaomingtai";
	nStr = 20;
	nInt = 28;
	nCon = 24;
	nDex = 20;
	
	nMax_qi = 150;
	nMax_jing = 100;
	nEff_force = 150;
	nMax_force = 150;
	
	nCombat_exp =  1000;
	nScore = 1000;

	AddAsk("紙扇",NPCASK_visible,"");
	
	SetSkill("BaseForce", 30);
	SetSkill("BaseDodge", 20);
	SetSkill("BaseUnarmed", 25);
	SetSkill("BaseParry", 20);
	
	szFamily = "昭明書院";
	nGeneration = 2;
	
	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNzm_DiziW::~CNzm_DiziW()
{

}
TRetInfo CNzm_DiziW::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	
	if(szName == "紙扇")
	{
		if (who->szFamily != "昭明書院")
		    TRet_return("書童：你並不是本院學生，憑什麼要我給你東西？");
	    if (who->GetGoods("紙扇") != NULL )
		{
		    ri.szRet ="書童：你現在身上已經有紙扇了？怎麼又來要了呢！";
		    return ri;
		}

	    CWeapon * lpWeapon = GetWeaponClass("紙扇");
		CString szUnit = lpWeapon->lpGoods->szUnit;
	    ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
	    ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"紙扇","空",1,szUnit);
	    who->SendMsg(ri.szRet);
	    ri.szRet.Format("書童：拿去吧，好好善用啊。");
	}
	ri.bRet = TRUE;
	return ri;
}