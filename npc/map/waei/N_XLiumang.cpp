// N_XLiuMang.cpp: implementation of the CN_XLiuMang class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "N_XLiuMang.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CN_XLiuMang::CN_XLiuMang()
{
	static int number = 0;
	number ++;
	szCName = "小流氓";
	szEName.Format("xliumang%d", number);
	szSex	= "M";
	nAge	=  14;
	szLong	= "他是一個成天游手好閑的小流氓。";
	nScore	= -20;
	nCombat_exp	=  random(50)+50;
	nShen = -20-random(60);
	szXFileName.Format("pmudsn04");

	nAttitude	= NP_friendly | NP_heroism | NP_apprentice;
	
	SetSkill("BaseUnarmed", 4);
	SetSkill("BaseDodge", 4);
	SetSkill("BaseParry", 4);

	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
	nMoney = 50;
}

CN_XLiuMang::~CN_XLiuMang()
{

}
