// Nem_XiaoNiGu.cpp: implementation of the CNem_XiaoNiGu class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Nem_XiaoNiGu.h"

CNem_XiaoNiGu::CNem_XiaoNiGu()
{
	static int number = 0;

	number++;
	szCName = "小尼姑";
	szEName.Format("xiaonigu%d",number);
	szXFileName.Format("pmudnqng0%d",random(2)+1);
	szSex = "F";
	szLong ="一個小時候被遺棄的孩子，從小被峨眉派收養，並教了她一些基本武功。";
	nAttitude = NP_friendly | NP_apprentice | NP_guard;
	nShen = 250+random(50);
	szFamily = "峨眉派";
	
	nAge = 14;
	//set("kar",20;
	SetSkill("BaseDodge",	35);
	SetSkill("BaseParry",	30);
	SetSkill("BaseForce",	20);
	SetSkill("BaseUnarmed",	20);
	SetSkill("BaseSword",	20);
	nCombat_exp = 2000;

	CEquip * lpEquipGoods;
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNem_XiaoNiGu::~CNem_XiaoNiGu()
{

}
