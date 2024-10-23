// Nwd_XiaoCui.cpp: implementation of the CNwd_XiaoCui class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Nwd_XiaoCui.h"
#include "..\..\..\config.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNwd_XiaoCui::CNwd_XiaoCui()
{
	szCName = "小翠";
	szEName = "xiaocui";
	szNickName = "伺茶道童";
	szSex = "F" ;
	nAge =  12+random(6);
	szLong =
		"這是個年齡不大的小姑娘，但寬鬆的道袍也遮不住她過早發育的身體。"
		"一臉聰明乖巧，滿口伶牙俐齒。";
	nAttitude = NP_friendly | NP_apprentice;
    nShen = 1000;

	szXFileName = "pmudsnv01";
	szRoom		= "wd_hkt";
	
	nStr = 20;
	nInt = 28;
	nCon = 24;
	nDex = 20;
	
	nMax_qi = 150;
	nMax_jing = 100;
	nEff_force = 150;
	nMax_force = 150;
	
	nCombat_exp =  1000+random(800);
	nScore = 1000;
	
	// AddAsk(Item, Attrib, Prompt); 最多加入10項
	// Attrib:	NPCASK_visible = 顯示在物品列表中
	//			NPCASK_newline = 在訊息前加一行空白

	AddAsk("茶",NPCASK_visible,"");
	AddAsk("水蜜桃",NPCASK_visible,"");
	
	SetSkill("BaseForce", 30);
	SetSkill("BaseDodge", 20);
	SetSkill("BaseUnarmed", 15+random(10));
	SetSkill("BaseParry", 20);
/*	set_temp("apply/attack", 10);
	set_temp("apply/defense", 15);
	set_temp("apply/damage", 3);
*/	
	szFamily = "武當派";
	nGeneration = 4;
/*	
	set("inquiry", ([
		"女兒香" : "這「女兒香」珍貴得很，連宋大俠的兒子也不能隨便喝著．"
		+ "不過如果你能從西面茶園老張那里弄些「女兒香」茶葉來，"
		+ "我倒是可以為你沏一壺。他見你從我這兒去，大概不會難為你",
        ]);
	
*/	
	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("qingrobe");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNwd_XiaoCui::~CNwd_XiaoCui()
{

}
TRetInfo CNwd_XiaoCui::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;

	if( szName == "水蜜桃" )
	{
		if (who->szFamily != "武當派") {
			ri.szRet = "閣下與小妹素昧平生，何出此言";
			return ri;
		}
		if (who->GetGoods((char *)(LPCTSTR)"水蜜桃") != NULL )
		{
			ri.szRet.Format("%s你現在身上不是還有水蜜桃嗎，先吃完再說吧。",
				GetSpecialName(who,1));
			return ri;
		}
		if (who->nEat > who->nMax_Eat*85/100)
			TRet_return(GetSpecialName(who,1) + "你好像吃不下了吧，吃飽了就別老在這裡呆著，出去走走也好呀。");
		
		CFood * lpFood = GetFoodClass("shuimitao");
		ri.szRet = who->AddGoods(lpFood);
		if (ri.szRet != "OK") {
			delete lpFood;
			return ri;
		}
//		ri.szRet.Format("小翠給%s一碟新鮮的水蜜桃。", who->szCName);
//		who->SendMsgToAll(ri.szRet);
		
		ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"水蜜桃","空",1,"碟");
		who->SendMsg(ri.szRet);

		ri.szRet = "先吃著吧，吃完了再向我要。";
	}
	else if( szName == "茶" )
	{
		CJiuDai * lpJiuDai = dynamic_cast<CJiuDai *>(who->GetClassGoods(GK_jiudai));
		if (lpJiuDai == NULL)
		{
			if( who->szFamily != "武當派" )
				TRet_return("茶水這裡倒有，你沒有盛水的東西讓我怎麼給你呀？")
			else
			{
				lpJiuDai = GetJiuDaiClass("qinghulu");
				lpJiuDai->nRemain = lpJiuDai->lpJiuDai->nMaxRemain;
				lpJiuDai->szLoadName = "涼茶";
				lpJiuDai->nDurg = 0;
				lpJiuDai->nSupply = 0;
				ri.szRet = who->AddGoods(lpJiuDai);
				if (ri.szRet != "OK") {
					delete lpJiuDai;
					return ri;
				}
//				ri.szRet.Format("小翠給%s一個裝滿涼茶的葫蘆。", who->szCName);
//				who->SendMsgToAll(ri.szRet);

				ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"青葫蘆","涼茶",1,"個");
				who->SendMsg(ri.szRet);
		
				if (who->nDrink <= 100)
					ri.szRet = "怎麼渴得這麼厲害，快歇歇，喝口涼茶吧！";
				else 
					ri.szRet = "好吧，拿去慢慢喝。";
				ri.bRet = TRUE;
				return ri;
			}
		}
		if(lpJiuDai->nRemain == lpJiuDai->lpJiuDai->nMaxRemain)
		{
			TRet_return(GetSpecialName(who,1) + "你就還有茶！老纏著人家幹什麼？");
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
			"涼茶",
			1,
			lpJiuDai->lpGoods->szUnit);
		who->SendMsg(ri.szRet);
		//ri.szRet.Format("小翠把%s的%s裡面裝滿了涼茶。", who->szCName, lpJiuDai->lpGoods->szCName);
		//who->SendMsgToAll(ri.szRet);
		ri.szRet.Format("小翠把你的%s裡面裝滿了涼茶。",lpJiuDai->lpGoods->szCName);
		lpJiuDai->nRemain = lpJiuDai->lpJiuDai->nMaxRemain;
		lpJiuDai->szLoadName = "涼茶";
	}

	ri.bRet = TRUE;
	return ri;
}