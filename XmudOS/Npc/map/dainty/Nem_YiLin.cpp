// Nem_YiLin.cpp: implementation of the CNem_YiLin class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\StdAfx.h"
#include "Nem_YiLin.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNem_YiLin::CNem_YiLin()
{
    szCName = "儀霖";
	szEName = "yilin";
	szNickName = "";
	szSex = "F" ;
	nAge =  23;
	szLong ="這是峨眉的女弟子，因為天生聰穎，心地又善良，頗受師父的喜愛。";
	nAttitude = NP_friendly | NP_apprentice | NP_guard;
    nShen = 2000;

	szXFileName = "pmudznng01";
	szRoom		= "em_cdiana";
	nStr = 27;
	nInt = 21;
	nCon = 25;
	nDex = 20;
	
	nMax_qi = 150;
	nMax_jing = 100;
	nEff_force = 150;
	nMax_force = 150;
	
	nCombat_exp =  50000;
	nScore = 30000;

	// AddAsk(Item, Attrib, Prompt); 最多加入10項
	// Attrib:	NPCASK_visible = 顯示在物品列表中
	//			NPCASK_newline = 在訊息前加一行空白

	AddAsk(const_cast<char*>("竹劍"),NPCASK_visible, const_cast<char*>(""));
	
	SetSkill("BaseDodge",		40,0,"Step_Lingbo"	);
	SetSkill("BaseParry",		30);
	SetSkill("BaseForce",		40,0,"Force_Emei"	);
	SetSkill("BaseSword",		50,0,"Sword_Emei"	);
	SetSkill("Force_Emei",		30);
	SetSkill("Sword_Emei",		30);
	SetSkill("BaseUnarmed",		30,0,"Unarmed_Meihua");
	SetSkill("Unarmed_Meihua",	30);
	SetSkill("Step_Lingbo",		50);
	SetSkill("OtherLiterate",	10);


	szFamily = "峨眉派";
	nGeneration = 4;
	
	CEquip * lpEquipGoods;
	CWeapon * lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("oldrobe");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("changjian");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);
	lpWeapon = lpWeaponGoods;
}

CNem_YiLin::~CNem_YiLin()
{

}
TRetInfo CNem_YiLin::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	
	if(szName == "竹劍")
	{
		if (who->szFamily != "峨眉派")
		    TRet_return("儀霖：施主並非本派弟子，不知此話從何談起？");
	    if (who->GetGoods(const_cast<char*>("竹劍")) != NULL )
		{
		    ri.szRet ="儀霖：你現在身上已經有這樣武器了？我無法再給你了！";
		    return ri;
		}

	    CWeapon * lpWeapon = GetWeaponClass("zhujian");
		CString szUnit = lpWeapon->lpGoods->szUnit;
	    ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
	    ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"竹劍","空",1,szUnit);
	    who->SendMsg(ri.szRet);
	    ri.szRet.Format("儀霖：拿去吧。不過要記住，武器只可防身練武，切不可憑此濫殺生靈！");
	}
	ri.bRet = TRUE;
	return ri;
}