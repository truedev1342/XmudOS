
#include "stdafx.h"
#include "Nwd_DaoTong.h"


CNwd_DaoTong::CNwd_DaoTong()
{
	static int number = 0;
	number ++;
	szCName = "道童";
	szEName.Format("daotong%d",number);
	szLong = "他是武當山的小道童。";
	szXFileName.Format("pmudxds01");
	szSex = "M";
	nAge =  16;
	nAttitude = NP_apprentice | NP_guard;
	nStr = 20;
	nInt = 20;
	nCon = 22;
	nDex = 25;
	
	nMax_qi = 300;
	nMax_jing = 200;
	nShen = 150+random(150);
	nEff_force = 200;
	nMax_force = 200;

	nCombat_exp =  2000;
	nScore = 50;

	SetSkill("BaseForce",	30);
	SetSkill("BaseDodge",	20);
	SetSkill("BaseUnarmed",	20);
	SetSkill("BaseParry",	20);
	nDamage = 10;

	szFamily = "武當派";
	nGeneration = 5;

	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("qingrobe");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNwd_DaoTong::~CNwd_DaoTong()
{
}
