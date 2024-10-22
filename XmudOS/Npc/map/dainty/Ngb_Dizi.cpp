// Ngb_Dizi.cpp: implementation of the CNgb_Dizi class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Ngb_Dizi.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNgb_Dizi::CNgb_Dizi()
{
    szCName = "丐幫弟子";
	szEName = "gbdizi";
	szXFileName = "pmudqg01";
	szRoom = "gb_sdx";
	szSex = "M";
	nAge =  20;
	szLong = "這是位年輕的丐幫弟子。";
	nAttitude = NP_guard;
	nStr = 20;
	nInt = 20;
	nCon = 20;
	nDex = 26;

	nEff_qi = 360;
	nMax_qi = 360;
	nEff_jing = 300;
	nMax_jing = 300;
	nShen = 400;
	nEff_force = 710;
	nMax_force = 710;
	nAdd_force = 36;

	nCombat_exp =  6800;

	SetSkill("BaseForce",		45,	0,	"Force_Huntian"	);
	SetSkill("BaseUnarmed",		40,	0,	"Unarmed_Xianglong");
	SetSkill("BaseDodge",		40,	0,	"Step_Snow");
	SetSkill("BaseParry",		40);
	SetSkill("Unarmed_Xianglong",30);
	SetSkill("Force_Huntian",	40);
	SetSkill("Step_Snow",		30);

	AddAsk("竹棒",NPCASK_visible,"");
	szFamily = "丐幫";
	nGeneration = 20;
}

CNgb_Dizi::~CNgb_Dizi()
{

}
TRetInfo CNgb_Dizi::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	
	if(szName == "竹棒")
	{
		if (who->szFamily != "丐幫")
		    TRet_return("丐幫弟子：你並不是本派弟子，憑什麼要我給你東西？");
	    if (who->GetGoods("竹棒") != NULL )
		{
		    ri.szRet ="丐幫弟子：你現在身上已經有這樣武器了？怎麼又來要了呢！";
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
	    ri.szRet.Format("丐幫弟子：拿去吧。不過要記住，不可憑此打架滋事！");
	}
	ri.bRet = TRUE;
	return ri;
}