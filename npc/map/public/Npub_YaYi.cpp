// Npub_YaYi.cpp: implementation of the CNpub_YaYi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Npub_YaYi.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static YaYi SYaYi;
CNpub_YaYi::CNpub_YaYi()
{
	lpYaYi = &SYaYi;
	lpYaYi->number++;

	szCName = "衙役";
	szEName.Format("yayi%d",lpYaYi->number);
	szSex	= "M";
	nAge	= 25;
	szXFileName.Format("pmuddh03");
	
	szLong	= "一個高大威猛的漢子，因為久在官府做事，臉上已經磨煉得毫無表情。";
	nCombat_exp = 7500;
	nShen		= 750;
	nAttitude	= NP_friendly | NP_heroism | NP_apprentice | NP_guard;
	SetSkill("BaseUnarmed", 30);
	SetSkill("BaseDodge", 30);
	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("yayicloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNpub_YaYi::~CNpub_YaYi()
{

}
