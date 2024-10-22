// Npub_LiuMang.cpp: implementation of the CNpub_LiuMang class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Npub_LiuMang.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpub_LiuMang::CNpub_LiuMang()
{
	static int number = 0;
	number ++;
	szCName = "流氓";
	szEName.Format("liumang%d", number);
	szSex	= "M";
	nAge	=  19;
	szLong	= "他是一個成天游手好閑的流氓，長得倒是白白胖胖的，也許以前有過錢。";
	nScore	= -20;
	nCombat_exp	=  random(250)+250;
	nShen = -50-random(50);
	szXFileName.Format("pmuddh0%d", random(5) +1);

	nAttitude	= NP_friendly | NP_heroism | NP_apprentice;
	
	SetSkill("BaseUnarmed", 7);
	SetSkill("BaseDodge", 7);
	SetSkill("BaseParry", 7);
//	set_temp("apply/attack", 10;
//	set_temp("apply/defense", 10;

	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
	nMoney += 200;
}

CNpub_LiuMang::~CNpub_LiuMang()
{

}
