#include "..\..\stdafx.h"
#include "N_OldWoman2.h"
// Nuke +1
#include "..\..\..\config.h"

CN_OldWoman2::CN_OldWoman2()
{
	szCName = "老太太";
	szEName = "oldwoman2";
	szRoom = "xy_mingju";
	nAge =  60;
	szSex = "F";
	szLong = "這個老太太心裡不知在愁苦什麼。";
	nAttitude = NP_apprentice;
	nStr = 24;
	nDex = 16;
	nCombat_exp =  20000;
	nShen = 1000;

	szXFileName.Format("pmudlf02");

	// Nuke +1
	AddAsk("老太太",NPCASK_visible|NPCASK_newline,"老太太：唉！大俠你可否替\
老太婆我分擔憂慮？");
	AddAsk("憂慮",NPCASK_visible|NPCASK_newline,"老太太：我們吳家代代單傳，\
現在家裡唯一的男孩被官府征召去當兵，不知現在在何方，你是否〔願意〕幫我找到他？");
	AddAsk("不願意",0,"老太太聽了你的話掩面而泣。");
	AddAsk("願意",0,"");
	AddAsk("吳遠志",0,"");

	SetSkill("BaseUnarmed",	40);
	SetSkill("BaseParry",	40);

	nDamage = 30;

	CEquip * lpEquipGoods;

	lpEquipGoods = GetEquipClass("oldrobe");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CN_OldWoman2::~CN_OldWoman2()
{
}

TRetInfo CN_OldWoman2::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	if( szName == "願意")
	{
		if (who->GetGoods("老山參") != NULL )
		{
			ri.szRet.Format("老太太：你是不是有我兒子〔吳遠志〕的消息了？");
			return ri;
		}
		if (who->GetGoods("軍服") != NULL )
		{
			ri.szRet.Format("老太太：%s，我兒〔吳遠志〕就拜託你照應了！",GetSpecialName(who,1));
			return ri;
		}
  		CEquip * lpEquip = GetEquipClass("junfu");

		ri.szRet = who->AddGoods(lpEquip);
		CString szUnit = lpEquip->lpGoods->szUnit;
		if (ri.szRet != "OK") {
			delete lpEquip;
			return ri;
		}
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"軍服","空",1,szUnit,0);
		who->SendMsg(ri.szRet);

		ri.szRet = "老太太：這是我替我兒〔吳遠志〕縫製的棉襖，就請你替我送給他了。";
		ri.bRet = TRUE;
		return ri;
	}
	if (szName == "吳遠志")
	{
		if (who->GetGoods("軍服") != NULL )
		{
			ri.szRet.Format("老太太：你有遠志的消息了嗎？");
			return ri;
		}
		CGoods * lpGoods = who->GetGoods("家書");
		if (lpGoods != NULL )
		{
			// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
			ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,"家書","空",1,lpGoods->lpGoods->szUnit,0);
			who->SubGoods("家書");
			who->SendMsg(ri.szRet);
			who->nMoney+=10000;
			who->nShen += 100;
			who->SendAllInfo();
			ri.szRet = "老太太高興地說：得知我兒平安的消息真是太好了。感謝大俠鼎力協助，\
這是給你的禮金，收下吧，別客氣了！";
			ri.bRet = TRUE;
			return ri;
		}
		ri.bRet = TRUE;
		return ri;
	}
	ri.bRet = TRUE;
	return ri;
}
