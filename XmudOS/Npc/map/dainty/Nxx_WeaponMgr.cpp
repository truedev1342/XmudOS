// Nxx_WeaponMgr.cpp: implementation of the CNxx_WeaponMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Nxx_WeaponMgr.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNxx_WeaponMgr::CNxx_WeaponMgr()
{
    szCName = "兵器庫主事";
	szEName = "weaponmgr";
	szSex = "M" ;
	nAge =  25;
	szLong = "這是星宿派的一個普通弟子，在星宿海裡管理兵器庫。";
	nAttitude = NP_friendly | NP_apprentice | NP_guard;
    nShen = -100;

	szXFileName = "pmudznnz03";
	szRoom		= "xx_kfa";
	nStr = 20;
	nInt = 28;
	nCon = 24;
	nDex = 20;
	
	nMax_qi = 150;
	nMax_jing = 100;
	nEff_force = 150;
	nMax_force = 150;
	
	nCombat_exp =  1000+random(800);
	nScore = 1000;

	AddAsk("竹棒",NPCASK_visible,"");
	
	SetSkill("BaseForce", 30);
	SetSkill("BaseDodge", 20);
	SetSkill("BaseUnarmed", 17+random(10));
	SetSkill("BaseParry", 20);
	
	szFamily = "星宿派";
	nGeneration = 4;
	
	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNxx_WeaponMgr::~CNxx_WeaponMgr()
{

}
TRetInfo CNxx_WeaponMgr::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	
	if(szName == "竹棒")
	{
		if (who->szFamily != "星宿派")
		    TRet_return("兵器庫主事：你並不是本派弟子，憑什麼要我給你東西？");
	    if (who->GetGoods("竹棒") != NULL )
		{
		    ri.szRet ="兵器庫主事：你現在身上已經有這樣武器了？怎麼又來要了呢！";
		    return ri;
		}

	    CWeapon * lpWeapon = GetWeaponClass("zhubang");
		CString szUnit = lpWeapon->lpGoods->szUnit;
	    ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
	    ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"竹棒","空",1,szUnit);
	    who->SendMsg(ri.szRet);
	    ri.szRet.Format("兵器庫主事：拿去吧，好好善用啊。");
	}
	ri.bRet = TRUE;
	return ri;
}