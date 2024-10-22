// Nwd_WangKangYu.cpp: implementation of the CNwd_WangKangYu class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Nwd_WangKangYu.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNwd_WangKangYu::CNwd_WangKangYu()
{
    szCName = "谷清道長";
	szEName = "wd_guqing";
	szLong = "他是武當派的道長，掌管各項什物。";
	szXFileName = "pmudxds02";
	szRoom = "wd_lgf";
	szSex = "M";
	nAge =  30;
	nAttitude = NP_apprentice | NP_guard;
	
	nStr = 20;
	nInt = 20;
	nCon = 25;
	nDex = 20;
	
	nMax_qi = 300;
	nMax_jing = 200;
	nShen = 300;
	nEff_force = 300;
	nMax_force = 300;

	nCombat_exp =  5000;
	nScore = 1000;

	SetSkill("BaseForce",	60);
	SetSkill("BaseDodge",	40);
	SetSkill("BaseUnarmed",	40);
	SetSkill("BaseParry",	40,	0,	"Sword_Taiji");
	SetSkill("BaseSword",	40,	0,	"Sword_Taiji");
	SetSkill("Sword_Taiji",	20);
	SetSkill("OtherTaoism",	20);

	szFamily = "武當派";
	nGeneration = 3;
    AddAsk("竹劍",NPCASK_visible,"");
    AddAsk("木刀",NPCASK_visible,"");

	CEquip * lpEquipGoods;
	CWeapon * lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("qingrobe");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("changjian");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);
	lpWeapon = lpWeaponGoods;
}

CNwd_WangKangYu::~CNwd_WangKangYu()
{

}
TRetInfo CNwd_WangKangYu::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	
	if(szName == "竹劍")
	{
		if (who->szFamily != "武當派")
		    TRet_return(GetSpecialName(who, 1) + "與本派素無來往，不知此話從何談起？");
	    if (who->GetGoods("竹劍") != NULL )
		{
		    ri.szRet.Format("谷清道長：%s你現在身上不是有這樣武器嗎，怎麼又來要了？真是貪得無饜！",GetSpecialName(who,1));
		    return ri;
		}
		
	    CWeapon * lpWeapon = GetWeaponClass("zhujian");
		CString szUnit = lpWeapon->lpGoods->szUnit;
	    ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
	
	    ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"竹劍","空",1,szUnit);
		who->SendMsg(ri.szRet);
		ri.szRet.Format("谷清道長：拿去吧。不過要記住，武器只可防身練武，不可憑此做出敗壞門規的事呀!");
	}
	if(szName == "木刀")
	{
		if (who->szFamily != "武當派")
		    TRet_return(GetSpecialName(who, 1) + "與本派素無來往，不知此話從何談起？");
	    if (who->GetGoods("木刀") != NULL )
		{
		    ri.szRet.Format("谷清道長：%s你現在身上不是有這樣武器嗎，怎麼又來要了？真是貪得無饜！",GetSpecialName(who,1));
		    return ri;
		}
		
	    CWeapon * lpWeapon = GetWeaponClass("mudao");
		CString szUnit = lpWeapon->lpGoods->szUnit;
	    ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
	
	    ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"木刀","空",1,szUnit);
		who->SendMsg(ri.szRet);
		ri.szRet.Format("谷清道長：拿去吧。不過要記住，武器只可防身練武，不可憑此做出敗壞門規的事呀!");
	}
	
	ri.bRet = TRUE;
	return ri;
}