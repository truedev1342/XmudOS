// Npub_LiuMangTou.cpp: implementation of the CNpub_LiuMangTou class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Npub_LiuMangTou.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpub_LiuMangTou::CNpub_LiuMangTou()
{
	static int number = 0;
	number++;
	szCName		= "流氓頭";
	szEName.Format("liumangtou%d", number);
	szSex		= "M";
	nAge		=  25;
	szXFileName.Format("pmudnqn0%d", random(2) + 4);
	szLong		= "他長得奸嘴猴腮的，一看就不像是個好人。";
	nStr = 30;
	nInt = 20;
	nCon = 30;
	nDex = 25;
	
	nCombat_exp =  7000;
	nAttitude	= NP_friendly | NP_heroism | NP_apprentice;
	nShen		= -120-random(80);
	SetSkill("BaseUnarmed", 15);
	SetSkill("BaseDodge", 15);
	SetSkill("BaseParry", 15);

//	set_temp("apply/attack", 20);
//	set_temp("apply/defense", 20);

	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
	nMoney += 1000;
}

CNpub_LiuMangTou::~CNpub_LiuMangTou()
{

}
