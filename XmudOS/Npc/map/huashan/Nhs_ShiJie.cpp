// Nhs_ShiJie.cpp: implementation of the CNhs_ShiJie class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Nhs_ShiJie.h"
#include "..\..\..\config.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNhs_ShiJie::CNhs_ShiJie()
{
	szCName = "小倩";
	szEName = "shijie";
	szNickName = "管茶師姐";
	szSex = "F" ;
	nAge =  18+random(6);
	szLong =
		"這是山上專管廚房的年輕女弟子，雖然年齡不大，門內弟子從上到下人人都親熱地稱她為師姐。";
	nAttitude = NP_friendly | NP_apprentice;
    nShen = 1000;

	szXFileName = "pmudnx01";
	szRoom		= "hs_xzhu";
	
	nStr = 20;
	nInt = 28;
	nCon = 24;
	nDex = 20;
	
	nMax_qi = 150;
	nMax_jing = 100;
	nEff_force = 150;
	nMax_force = 150;
	
	nCombat_exp =  1800;
	nScore = 1000;
	
	// AddAsk(Item, Attrib, Prompt); 最多加入10項
	// Attrib:	NPCASK_visible = 顯示在物品列表中
	//			NPCASK_newline = 在訊息前加一行空白

	AddAsk("水",NPCASK_visible,"");
	AddAsk("饅頭",NPCASK_visible,"");
	
	SetSkill("BaseForce", 30);
	SetSkill("BaseDodge", 20);
	SetSkill("BaseUnarmed", 17+random(10));
	SetSkill("BaseParry", 20);
/*	set_temp("apply/attack", 10);
	set_temp("apply/defense", 15);
	set_temp("apply/damage", 3);
*/	
	szFamily = "華山派";
	nGeneration = 15;
	
	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("qingshaqun");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNhs_ShiJie::~CNhs_ShiJie()
{

}
TRetInfo CNhs_ShiJie::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	if( szName == "饅頭")
	{
		if (who->szFamily != "華山派")
			TRet_return(GetSpecialName(who,1) + "不是本派弟子，不能在此用餐。");
		if (who->GetGoods((char *)(LPCTSTR)"饅頭") != NULL )
		{
			ri.szRet.Format("%s你現在身上不是有饅頭嗎，怎麼又來要了？",GetSpecialName(who,1));
			return ri;
		}
		CFood * lpFood = GetFoodClass("mantou");
		ri.szRet = who->AddGoods(lpFood);
		if (ri.szRet != "OK") {
			delete lpFood;
			return ri;
		}
//		ri.szRet.Format("小倩給%s一個熱騰騰的饅頭。", who->szCName);
//		who->SendMsgToAll(ri.szRet);

		ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"饅頭","空",1,"個");
		who->SendMsg(ri.szRet);

		if (who->nEat <= 100)
			ri.szRet = "怎麼餓得這麼慘，拿著，快吃吧！";
		else 
			ri.szRet = "拿去吧，若吃得不夠再找我拿。";
	}
	else if( szName == "水" )
	{
		if (who->szFamily != "華山派")
			TRet_return(GetSpecialName(who,1) + "不是本派弟子，不能在此用餐。");
		CJiuDai * lpJiuDai = dynamic_cast<CJiuDai *>(who->GetClassGoods(GK_jiudai));
		if (lpJiuDai == NULL)
		{
			lpJiuDai = GetJiuDaiClass("qingshuihu");
			lpJiuDai->nRemain = lpJiuDai->lpJiuDai->nMaxRemain;
			lpJiuDai->szLoadName = "清水";
				lpJiuDai->nDurg = 0;
				lpJiuDai->nSupply = 0;
				ri.szRet = who->AddGoods(lpJiuDai);
				if (ri.szRet != "OK") {
					delete lpJiuDai;
					return ri;
				}
//				ri.szRet.Format("小倩給%s一個裝滿清水的葫蘆。", who->szCName);
//				who->SendMsgToAll(ri.szRet);

				ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"清水葫蘆","清水",1,"個");
				who->SendMsg(ri.szRet);
		
				if (who->nDrink <= 100)
					ri.szRet = "怎麼渴得這麼厲害，趕快喝一口吧！";
				else 
					ri.szRet = "拿去吧，如果不夠喝再來這兒裝水。";
				ri.bRet = TRUE;
				return ri;
		}
		if(lpJiuDai->nRemain == lpJiuDai->lpJiuDai->nMaxRemain)
		{
			ri.szRet.Format("你的%s裡面不是裝的有滿滿的%s嗎？",
				lpJiuDai->lpGoods->szCName,
				lpJiuDai->szLoadName);
			return ri;
		}
		ri.szRet.Format("%s %s %s %d %s",
			SZSUBGOODS,
			lpJiuDai->lpGoods->szCName,
			lpJiuDai->szLoadName,
			1,
			lpJiuDai->lpGoods->szUnit);
		who->SendMsg(ri.szRet);

		ri.szRet.Format("%s %s %s %d %s",
			SZADDGOODS,
			lpJiuDai->lpGoods->szCName,
			"清水",
			1,
			lpJiuDai->lpGoods->szUnit);
		who->SendMsg(ri.szRet);
		//ri.szRet.Format("小倩把%s的%s裡面裝滿了清水。", who->szCName, lpJiuDai->lpGoods->szCName);
		//who->SendMsgToAll(ri.szRet);
		ri.szRet.Format("小倩把你的%s裡面裝滿了清水。",lpJiuDai->lpGoods->szCName);
		lpJiuDai->nRemain = lpJiuDai->lpJiuDai->nMaxRemain;
		lpJiuDai->szLoadName = "清水";
	}
	ri.bRet = TRUE;
	return ri;
}