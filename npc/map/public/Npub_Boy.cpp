#include "stdafx.h"
#include "Npub_Boy.h"

CNpub_Boy::CNpub_Boy()
{
	static int number = 0;
	number ++;

	szCName = "男孩";
	szEName.Format("boy%d", number) ;
	szSex = "M" ;
	nAge =  13;
	szLong = "這是個農家少年，大概因從小務農，雖然年紀不大，可已長的很粗壯了。";
	szXFileName.Format("pmudsn0%d",random(4)+1);

	nStr = 17;
	nDex = 16;
	nCon = 15;
	nInt = 17;
	nShen = 200+random(200);
	nCombat_exp =  100+ random(20);
	nAttitude = NP_apprentice;

	nMoney = 10;

	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

}

CNpub_Boy::~CNpub_Boy()
{

}
