// N_YunBing.cpp: implementation of the CN_YunBing class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "N_YunBing.h"

static YunBing SYunBing;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CN_YunBing::CN_YunBing()
{
    lpYunBing=&SYunBing;
	lpYunBing->number ++;

	szCName = "Å¶¤l§L";
	szEName.Format("yunbing%d",lpYunBing->number);
	nAge =  32;
	szSex = "M";
	szLong = "»X¥j±Úªº§L¤h¡C";
	nAttitude = NP_attack | NP_heroism | NP_apprentice;
	nStr = 15;
	nDex = 15;
	nCombat_exp =  random(3500)+3500;
	nShen = -100 - random(100);
    nMoney = 100 + random(100);
	szXFileName.Format("pmudws01");


	SetSkill("BaseUnarmed",	25);
	SetSkill("BaseDodge",	25);
	SetSkill("BaseParry",	25);
	SetSkill("BaseBlade",	25);
	SetSkill("BaseForce",	25);

	nDamage = 30;


	CEquip * lpEquipGoods;
	CWeapon * lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("junfu");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("gangdao");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);
	lpWeapon = lpWeaponGoods;
}

CN_YunBing::~CN_YunBing()
{

}
