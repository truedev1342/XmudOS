#include "stdafx.h"
#include "Nsl_SaMi.h"

CNsl_SaMi::CNsl_SaMi()
{
	static int number = 0;
	number ++;

	szCName = "小沙彌";
	szEName.Format("shami%d",number);
	szLong = "他是一位未通世故的少年和尚，臉上掛著天真的稚笑。";
	szXFileName.Format("pmudpths03",random(5)+1);
	szSex = "M";
	nAttitude = NP_apprentice;
	szFamily = "少林派";
	nAge =  10;
	nStr = 20;
	nInt = 20;
	nCon = 20;
	nDex = 20;
	nMax_qi = 100;
	nMax_jing = 100;
	nShen = 100+random(200);
	nEff_force = 100;
	nMax_force = 100;
	nCombat_exp =  500;
	nScore = 100;

	SetSkill("BaseForce",	8);
	SetSkill("BaseDodge",	8);
	SetSkill("BaseUnarmed",	8);
	SetSkill("BaseParry",	8);
	
	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("qingsengyi");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNsl_SaMi::~CNsl_SaMi()
{
}
