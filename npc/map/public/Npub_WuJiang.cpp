#include "stdafx.h"
#include "Npub_WuJiang.h"

CNpub_WuJiang::CNpub_WuJiang()
{
	static int number = 0;
	number ++;
	szCName = "武將";
	szEName.Format("wujiang%d",number);
	szSex = "M";
	nAge =  random(10) + 30;
	nStr = 25;
	nDex = 16;
	szLong = "他是這裡的守將，負責這個地區的安全。";
	szXFileName = "pmudws02";
	nCombat_exp =  75000;
	nAttitude = NP_apprentice | NP_guard;
	nShen = random(200)-50;

	SetSkill("BaseUnarmed", 50);
	SetSkill("BaseForce",	50);
	SetSkill("BaseSword",	50);
	SetSkill("BaseDodge",	50);
	SetSkill("BaseParry",	50);
	//set_temp("apply/attack", 55;
	nDamage = 30;

	nEff_force = 300; 
	nMax_force = 300;
	nAdd_force = 10;

	CEquip * lpEquipGoods;
	CWeapon * lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("tiejia");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("gangjian");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);
	lpWeapon = lpWeaponGoods;
}

CNpub_WuJiang::~CNpub_WuJiang()
{
}
