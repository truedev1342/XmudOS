// Npub_JiaDing.cpp: implementation of the CNpub_JiaDing class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Npub_JiaDing.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static JiaDing SJiaDing;
CNpub_JiaDing::CNpub_JiaDing()
{
	lpJiaDing = &SJiaDing;
	lpJiaDing->number++;

	szCName = "家丁";
	szEName.Format("jiading%d",lpJiaDing->number);
	szLong = "大財主府中的家丁，負責保護他們的主人並聽候主人差遣。";
	szSex = "M";
	nAge =  25;

	nAttitude = NP_friendly | NP_apprentice;
	nCombat_exp =  4000;
     
	SetSkill("BaseUnarmed",	25);
	SetSkill("BaseDodge",	25);
	SetSkill("BaseParry",	25);
	SetSkill("BaseBlade",	25);
	SetSkill("BaseForce",	25);

	nShen = 50;
	nMoney = 10;
	szXFileName= "pmudsn02";

	CEquip *lpEquipGoods;
	CWeapon *lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("zhubang");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);
	lpWeapon = lpWeaponGoods;
}

CNpub_JiaDing::~CNpub_JiaDing()
{

}
