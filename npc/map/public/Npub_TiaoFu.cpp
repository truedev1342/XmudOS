#include "stdafx.h"
#include "Npub_TiaoFu.h"


CNpub_TiaoFu::CNpub_TiaoFu()
{
	static int number = 0;
	number ++;

	szCName = "挑夫";
	szEName.Format("tiaofu%d",number);
	szXFileName.Format("pmuddh0%d",random(5)+1);
	szSex = "M" ;
	nAge =  20+random(15);
	szLong = "這是個老實的窮挑夫，長得膀闊腰圓，一身肌肉。";
	nCombat_exp =  500 + random(1500);
	nStr = 25;
	nDex = 22;
	nCon = 20;
	nInt = 15;
	nShen = 120+random(80);
	nAttitude = NP_friendly | NP_heroism | NP_apprentice;

	CEquip * lpEquipGoods;
	
	SetSkill("BaseDodge",		25);
	SetSkill("BaseParry",		25);
	SetSkill("BaseUnarmed",		15);

	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNpub_TiaoFu::~CNpub_TiaoFu()
{
}
