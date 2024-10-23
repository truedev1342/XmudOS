#include "stdafx.h"
#include "N_Seller.h"
// Nuke +1
#include "..\..\..\config.h"

CN_Seller::CN_Seller()
{
	static int number = 0;
	number ++;

	szCName = "小販";
	szEName.Format("seller%d",number); // 英文名
	szNickName = "小販";
	nAge =  32;								
	szSex = "M";
	szLong = "這是一個小販";
	nAttitude = NP_heroism | NP_apprentice | NP_nofight;
	nStr = 24;
	nDex = 16;
	nCombat_exp =  2000;
	nShen = 500+random(300);

	szXFileName = "pmudznnz01";
	szRoom = "xy_guangchang";

	// AddAsk(Item, Attrib, Prompt); 最多加入10項
	// Attrib:	NPCASK_visible = 顯示在物品列表中
	//			NPCASK_newline = 在訊息前加一行空白
	CFood * lpFood1 = GetFoodClass("mantou");
    CFood * lpFood2 = GetFoodClass("zongzi");
	CFood * lpFood3 = GetFoodClass("yangrouchuan");
	CFood * lpFood4 = GetFoodClass("kaoya");
	CFood * lpFood5 = GetFoodClass("baozi");
	CJiuDai *lpJiuDai = GetJiuDaiClass("qingshuihu");
	CDrug * lpDrug = GetDrugClass("jinchuangyao");
    char szTemp[256];
	sprintf(szTemp,"金創藥%d枚銅錢，饅頭%d枚銅錢，清水葫蘆%d枚銅錢，粽子%d枚銅錢，羊肉串%d枚銅錢，烤鴨%d枚銅錢，包子%d枚銅錢",
		lpDrug->lpGoods->nCost,lpFood1->lpGoods->nCost,lpJiuDai->lpGoods->nCost,lpFood2->lpGoods->nCost,lpFood3->lpGoods->nCost,lpFood4->lpGoods->nCost,lpFood5->lpGoods->nCost);
	delete lpFood1; 
	delete lpFood2;
	delete lpFood3;
	delete lpFood4;
	delete lpFood5;
	delete lpJiuDai;
	delete lpDrug;

	AddAsk("價錢",NPCASK_visible,szTemp);
	AddAsk("水",NPCASK_visible,"");
	AddAsk("買金創藥",NPCASK_visible,"");
	AddAsk("買饅頭",NPCASK_visible,"");
	AddAsk("買清水葫蘆",NPCASK_visible,"");
	AddAsk("買粽子",NPCASK_visible,"");
	AddAsk("買羊肉串",NPCASK_visible,"");
	AddAsk("買烤鴨",NPCASK_visible,"");
	AddAsk("買包子",NPCASK_visible,"");
	

	SetSkill("BaseDodge",		15);
	SetSkill("BaseParry",		15);
	SetSkill("BaseUnarmed",		15);

	nDamage = 20;
	nMoney = 500;
}

CN_Seller::~CN_Seller()
{
}


TRetInfo CN_Seller::DoAsk(CPlayerInfo *who, CString szName)
{
	CFood * lpFood;
	CDrug * lpDrug;
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	if( szName == "買金創藥")
	{
  		lpDrug = GetDrugClass("jinchuangyao");
		if (who->nMoney < lpDrug->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpDrug;
			return ri;
		}
		int nCost = lpDrug->lpGoods->nCost;
		CString szUnit = lpDrug->lpGoods->szUnit;
		ri.szRet = who->AddGoods(lpDrug);
		if (ri.szRet != "OK") {
			delete lpDrug;
			return ri;
		}
		who->nMoney -= nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"金創藥","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "小販：來！這是您的金創藥。";
	}
	else if( szName == "買饅頭")
	{
  		lpFood = GetFoodClass("mantou");
		if (who->nMoney<lpFood->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpFood;
			return ri;
		}
		int nCost = lpFood->lpGoods->nCost;
		CString szUnit = lpFood->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpFood);
		if (ri.szRet != "OK") {
			delete lpFood;
			return ri;
		}
//		ri.szRet.Format("%s向小販買%s", who->szCName,lpFood->lpGoods->szdescribe);
//		who->SendMsgToAll(ri.szRet);
		who->nMoney -= nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"饅頭","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "小販：來！這是您的饅頭。";
	}
	else if( szName == "買清水葫蘆" )
	{
		if (who->GetGoods("清水葫蘆") != NULL) {
			ri.szRet.Format("小販：%s你已經有清水葫蘆了，多帶無益",GetSpecialName(who, SName_zhun));
			return ri;
		}
		CJiuDai * lpJiuDai = GetJiuDaiClass("qingshuihu");
		if (who->nMoney<lpJiuDai->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpJiuDai;
			return ri;
		}
		int nCost = lpJiuDai->lpGoods->nCost;
		CString szUnit = lpJiuDai->lpGoods->szUnit;
		ri.szRet = who->AddGoods(lpJiuDai);
		if (ri.szRet != "OK") {
			delete lpJiuDai;
			return ri;
		}
//		ri.szRet.Format("%s向小販買一個清水葫蘆。", who->szCName);
//		who->SendMsgToAll(ri.szRet);
		who->nMoney-=nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"清水葫蘆","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);

		lpJiuDai->nRemain = 0;
		lpJiuDai->szLoadName = "空";
		ri.szRet = "小販：來！這是您的清水葫蘆。";
	}
	else if( szName == "水" )
	{
		CJiuDai * lpJiuDai = dynamic_cast<CJiuDai *>(who->GetClassGoods(GK_jiudai));
		if (lpJiuDai == NULL)
		{
			TRet_return("小販：清水倒是可以給你，只是你總得先買個盛水的東西吧！")
		}
		if(lpJiuDai->nRemain == lpJiuDai->lpJiuDai->nMaxRemain)
		{
			ri.szRet.Format("你的%s里面不是裝的有滿滿的%s嗎？",
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
		ri.szRet.Format("小販把你的%s里面裝滿了清水。",lpJiuDai->lpGoods->szCName);
		lpJiuDai->nRemain = lpJiuDai->lpJiuDai->nMaxRemain;
		lpJiuDai->szLoadName = "清水";
	}
	else if( szName == "買粽子")
	{
  		lpFood = GetFoodClass("zongzi");
		if (who->nMoney<lpFood->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpFood;
			return ri;
		}
		int nCost = lpFood->lpGoods->nCost;
		CString szUnit = lpFood->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpFood);
		if (ri.szRet != "OK") {
			delete lpFood;
			return ri;
		}
//		ri.szRet.Format("%s向小販買%s", who->szCName,lpFood->lpGoods->szdescribe);
//		who->SendMsgToAll(ri.szRet);
		who->nMoney-=nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"粽子","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "小販：來！這是您的粽子。";
	}
	else if( szName == "買羊肉串")
	{
  		lpFood = GetFoodClass("yangrouchuan");
		if (who->nMoney<lpFood->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpFood;
			return ri;
		}
		int nCost = lpFood->lpGoods->nCost;
		CString szUnit = lpFood->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpFood);
		if (ri.szRet != "OK") {
			delete lpFood;
			return ri;
		}
//		ri.szRet.Format("%s向小販買%s", who->szCName,lpFood->lpGoods->szdescribe);
//		who->SendMsgToAll(ri.szRet);
		who->nMoney	-= nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"羊肉串","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "小販：來！這是您的羊肉串。";
	}
	else if( szName == "買烤鴨")
	{
  		lpFood = GetFoodClass("kaoya");
		if (who->nMoney<lpFood->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpFood;
			return ri;
		}

		int nCost = lpFood->lpGoods->nCost;
		CString szUnit = lpFood->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpFood);
		if (ri.szRet != "OK") {
			delete lpFood;
			return ri;
		}
//		ri.szRet.Format("%s向小販買%s", who->szCName,lpFood->lpGoods->szdescribe);
//		who->SendMsgToAll(ri.szRet);
		who->nMoney-=nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"烤鴨","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "小販：來！這是您的烤鴨。";
	}
	else if( szName == "買包子")
	{
  		lpFood = GetFoodClass("baozi");
		if (who->nMoney<lpFood->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpFood;
			return ri;
		}

		int nCost = lpFood->lpGoods->nCost;
		CString szUnit = lpFood->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpFood);
		if (ri.szRet != "OK") {
			delete lpFood;
			return ri;
		}
//		ri.szRet.Format("%s向小販買%s", who->szCName,lpFood->lpGoods->szdescribe);
//		who->SendMsgToAll(ri.szRet);
		who->nMoney-=nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"包子","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "小販：來！這是您的包子。";
	}
	ri.bRet = TRUE;
	return ri;
}
