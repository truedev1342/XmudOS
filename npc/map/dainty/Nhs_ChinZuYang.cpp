// Nhs_LaoDeNo.cpp: implementation of the CNhs_LaoDeNo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Nhs_ChinZuYang.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNhs_ChinZuYang::CNhs_ChinZuYang()
{
    szCName = "勞德諾";
	szEName = "laodeno";
	szLong = "他是華山派的弟子，是令狐沖的同輩師弟。";
	szXFileName = "pmudnqn05";
	szRoom = "hs_ynf";
	szSex = "M";
	nAge =  25;
	nAttitude = NP_friendly | NP_guard;
	
	nStr = 30;
	nInt = 40;
	nCon = 30;
	nDex = 30;

	nEff_qi = 2800;
	nMax_qi = 2800;
	nEff_jing = 1600;
	nMax_jing = 1600;
	nShen = 950;
	nEff_force = 2400;
	nMax_force = 2400;
	nAdd_force = 60;

	nCombat_exp = 500000;
	nScore = 80000;

	SetSkill("BaseUnarmed",		90,	0,	"Strike_Hunyuan");
	SetSkill("BaseForce",		80,	0,	"Force_Zixia");
	SetSkill("BaseDodge",		80,	0,	"Step_Huashan");
	SetSkill("BaseParry",		80,	0,	"Sword_Huashan");
	SetSkill("BaseSword",		80,	0,	"Sword_Huashan");
	SetSkill("Force_Zixia",		80);
	SetSkill("Strike_Hunyuan",	70);
	SetSkill("Sword_Huashan",	90);
	SetSkill("Step_Huashan",	80);
	SetSkill("OtherLiterate",	50);

	szFamily = "華山派";
	nGeneration = 14;

    AddAsk("竹劍",NPCASK_visible,"");
    AddAsk("木刀",NPCASK_visible,"");

	CEquip * lpEquipGoods;
	CWeapon * lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("changjian");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);
	lpWeapon = lpWeaponGoods;
}

CNhs_ChinZuYang::~CNhs_ChinZuYang()
{

}
TRetInfo CNhs_ChinZuYang::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	
	if(szName == "竹劍")
	{
		if (who->szFamily != "華山派") {
		    ri.szRet = GetSpecialName(who, 1) + "與本派素無來往，不知此話從何談起？";
			return ri;
		}
	    if (who->GetGoods((char *)(LPCSTR)szName) != NULL )
		{
		    ri.szRet.Format("勞德諾：%s你現在身上不是有這樣武器嗎，怎麼又來要了？真是貪得無饜！",who->szCName);
		    return ri;
		}
		
	    CWeapon * lpWeapon = GetWeaponClass("zhujian");
		CString szUnit = lpWeapon->lpGoods->szUnit;
	    ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
	
	    ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,szName,"空",1,szUnit);
		who->SendMsg(ri.szRet);
		ri.szRet.Format("勞德諾：拿去吧。不過要記住，武器只可防身練武，不可憑此做出敗壞門規的事呀!");
	}
	if(szName == "木刀")
	{
		if (who->szFamily != "華山派") {
		    ri.szRet = GetSpecialName(who, 1) + "與本派素無來往，不知此話從何談起？";
			return ri;
		}
	    if (who->GetGoods((char *)(LPCSTR)szName) != NULL )
		{
		    ri.szRet.Format("勞德諾：%s你現在身上不是有這樣武器嗎，怎麼又來要了？真是貪得無饜！",who->szCName);
		    return ri;
		}
		
	    CWeapon * lpWeapon = GetWeaponClass("mudao");
		CString szUnit = lpWeapon->lpGoods->szUnit;
	    ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
	
	    ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,szName,"空",1,szUnit);
		who->SendMsg(ri.szRet);
		ri.szRet.Format("勞德諾：拿去吧。不過要記住，武器只可防身練武，不可憑此做出敗壞門規的事呀!");
	}
	
	ri.bRet = TRUE;
	return ri;
}