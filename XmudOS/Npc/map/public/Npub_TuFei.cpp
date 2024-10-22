// Npub_TuFei.cpp: implementation of the CNpub_TuFei class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Npub_TuFei.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static TuFei STuFei;
CNpub_TuFei::CNpub_TuFei()
{
    lpTuFei = &STuFei;
	lpTuFei->number++;

	szCName = "土匪";
	szEName.Format("tufei%d",lpTuFei->number);
	szSex = "M";
	nAge =  30;
	szLong =
		"這家伙滿臉橫肉　一付凶神惡煞的模樣，令人望而生畏。";
	nCombat_exp =  10000;
    nShen	= -1000;
	nAttitude = NP_attack | NP_heroism | NP_apprentice;
	szXFileName.Format("pmuddh0%d", random(5) +1);
/*
	set("apply/attack", 20;
	set("apply/defense", 20;

	set("chat_chance", 30;
	set("chat_msg", ({
		"土匪一聲大喊: 此山是我開，此樹是我栽，若要從此過，留下買路財 !",
	}) ;
*/
	SetSkill("BaseUnarmed", 30);
	SetSkill("BaseSword", 25);
	SetSkill("BaseParry", 25);
	SetSkill("BaseDodge", 25);
	CEquip * lpEquipGoods;
	CWeapon * lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("duanjian");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);	
	lpWeapon = lpWeaponGoods;

//      carry_object("/d/city/obj/duanjian")->wield(;
//      carry_object("/obj/misc/cloth")->wear(;
	nMoney = 500;
}

CNpub_TuFei::~CNpub_TuFei()
{

}
