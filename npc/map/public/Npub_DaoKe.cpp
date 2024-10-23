// CNpub_DaoKe.cpp: implementation of the CNpub_DaoKe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Npub_DaoKe.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpub_DaoKe::CNpub_DaoKe()
{
	static int number = 0;
	number ++;
	szCName = "刀客";
	szEName.Format("daoke%d",number);
	szSex = "M";
	nAge =  random(30) + 20;
	nStr = 25;
	nDex = 18;
	szLong = "這是一位身懷絕藝的江湖刀客，滿臉風塵，顯然見過不少世面。";
	szXFileName = "pmudws01";
	nCombat_exp =  50000;
	nAttitude = NP_friendly | NP_heroism | NP_apprentice;

	SetSkill("BaseUnarmed",	random(10)+35);
	SetSkill("BaseForce",	random(10)+35);
	SetSkill("BaseBlade",	random(10)+35);
	SetSkill("BaseDodge",	random(10)+35);
	SetSkill("BaseParry",	random(10)+35);
	//set_temp("apply/attack", 55;
	nDamage = 20;

	nShen = random(100)-50;
	nEff_force = 300; 
	nMax_force = 300;
	nAdd_force = 10;
	nMoney += 100*nAge;

	CEquip * lpEquipGoods;
	CWeapon * lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("gangdao");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);
	lpWeapon = lpWeaponGoods;
}

CNpub_DaoKe::~CNpub_DaoKe()
{

}
