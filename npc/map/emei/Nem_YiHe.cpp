// Nem_YiHe.cpp: implementation of the CNem_YiHe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Nem_YiHe.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNem_YiHe::CNem_YiHe()
{
	szCName = "儀和";
	szEName = "yihe";
	szNickName = "";
	szSex = "F" ;
	nAge =  24+random(6);
	szLong =
		"這是剛入門不久的女弟子，學了幾天武功，進步不大，因為有幾分蠻力，就被指派到廚房打雜。";
	nAttitude = NP_friendly | NP_apprentice;
    nShen = 1000;

	szXFileName = "pmudznng03";
	szRoom		= "em_cwshi";
	nStr = 27;
	nInt = 21;
	nCon = 25;
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
	AddAsk("金創藥",NPCASK_visible,"");
	SetTemp ("jin_count", 30);
	SetSkill("BaseForce", 30);
	SetSkill("BaseDodge", 20);
	SetSkill("BaseUnarmed", 17+random(10));
	SetSkill("BaseParry", 20);
/*	set_temp("apply/attack", 10);
	set_temp("apply/defense", 15);
	set_temp("apply/damage", 3);
*/	

	szFamily = "峨眉派";
	nGeneration = 4;
	
	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("oldrobe");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNem_YiHe::~CNem_YiHe()
{

}

TRetInfo CNem_YiHe::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	if( szName == "饅頭")
	{
		if (who->szFamily != "峨眉派")
			TRet_return("施主真是抱歉，這是供本派弟子食用的，小尼不能自作主張拿給你。");
		if (who->GetGoods("饅頭") != NULL )
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
//		ri.szRet.Format("儀和給%s一個熱騰騰的饅頭。", who->szCName);
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
		CJiuDai * lpJiuDai = dynamic_cast<CJiuDai *>(who->GetClassGoods(GK_jiudai));
		if (lpJiuDai == NULL)
		{
			if( who->szFamily != "峨眉派" )
				TRet_return("清水這裡倒有，你沒有盛水的東西讓我怎麼給你呀？")
			else
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
//				ri.szRet.Format("儀和給%s一個裝滿清水的葫蘆。", who->szCName);
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
//		ri.szRet.Format("儀和把%s的%s裡面裝滿了清水。", who->szCName, lpJiuDai->lpGoods->szCName);
//		who->SendMsgToAll(ri.szRet);
		ri.szRet.Format("儀和把你的%s裡面裝滿了清水。",lpJiuDai->lpGoods->szCName);
		lpJiuDai->nRemain = lpJiuDai->lpJiuDai->nMaxRemain;
		lpJiuDai->szLoadName = "清水";
	}
	else if(szName=="金創藥")
	{
		if (who->szFamily != "峨眉派")
			TRet_return("施主真是抱歉，這是供本派弟子療傷用的，小尼不能自作主張拿給你。");
		if (who->GetGoods("金創藥") != NULL )
		{
			ri.szRet.Format("%s你現在身上不是有金創藥嗎，怎麼又來要了？",GetSpecialName(who,1));
			return ri;
		}
		if (GetTemp("jin_count").nValue < 1)
			TRet_return("對不起，金創藥已經發完了");

		CDrug * lpDrug = GetDrugClass("jinchuangyao");
		ri.szRet = who->AddGoods(lpDrug);
		if (ri.szRet != "OK") {
			delete lpDrug;
			return ri;
		}
		AddTemp("jin_count", -1);
//		ri.szRet.Format("儀和給%s一包金創藥。", who->szCName);
//		who->SendMsgToAll(ri.szRet);

		ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"金創藥","空",1,"包");
		who->SendMsg(ri.szRet);
		ri.szRet = "拿去吧，若不到緊要關頭不要隨便用掉啊！";
	}
	ri.bRet = TRUE;
	return ri;
}