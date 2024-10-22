// Npub_JianKe.cpp: implementation of the CNpub_JianKe class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Npub_JianKe.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static JianKe SJianKe;
CNpub_JianKe::CNpub_JianKe()
{
	lpJianKe = &SJianKe;
	lpJianKe->number++;
	szCName = "劍客";
	szEName.Format("jianke%d",lpJianKe->number);
	szSex = "M";
	nAge =  random(30) + 20;
	nStr = 25;
	nDex = 18;
	szLong = "這是一位身懷絕藝的江湖劍客，臉上風塵樸樸，顯然走過了不少地方。";
	szXFileName = "pmudws01";
	nCombat_exp =  50000;
	nAttitude = NP_friendly | NP_heroism | NP_apprentice;

	SetSkill("BaseUnarmed",	random(10)+35);
	SetSkill("BaseForce",	random(10)+35);
	SetSkill("BaseSword",	random(10)+35);
	SetSkill("BaseDodge",	random(10)+35);
	SetSkill("BaseParry",	random(10)+35);
	//set_temp("apply/attack", 55;
	nDamage = 20;

	nShen = random(100)-50;
	nEff_force = 300; 
	nMax_force = 300;
	nAdd_force = 10;
	nMoney += 100 * nAge;

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

CNpub_JianKe::~CNpub_JianKe()
{

}
