// Npub_TuFeitou.cpp: implementation of the CNpub_TuFeitou class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Npub_TuFeitou.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static TuFeiTou STuFeiTou;
CNpub_TuFeitou::CNpub_TuFeitou()
{
	lpTuFeiTou = &STuFeiTou;
	lpTuFeiTou->number++;

	szCName = "土匪頭";
	szEName.Format("tufeitou%d",lpTuFeiTou->number);
	szSex = "M";
	nAge =  45;
	szLong = "這傢伙滿臉殺氣，一付凶神惡煞的模樣，令人望而生畏。";
	nCombat_exp =  20000;
    nShen		= -2000;
	nAttitude	= NP_attack | NP_heroism | NP_apprentice;
	szXFileName.Format("pmuddh0%d", random(5) +1);
/*
	set("apply/attack",  30;
	set("apply/defense", 30;

	set("chat_chance", 5;
	set("chat_msg", ({
		"土匪頭嘿嘿地冷笑著: 今天你就別想從這里活著出去了!",
	}) ;
*/
	SetSkill("BaseSword", 20);
	SetSkill("BaseUnarmed", 30);
	SetSkill("BaseParry", 30);
	SetSkill("BaseDodge", 30);

	nMoney = 1000;

	CEquip * lpEquipGoods;
	CWeapon * lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("duanjian");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);	
	lpWeapon = lpWeaponGoods;
}

CNpub_TuFeitou::~CNpub_TuFeitou()
{
}
