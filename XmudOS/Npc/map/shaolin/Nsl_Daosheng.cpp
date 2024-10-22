// Nsl_Daosheng.cpp: implementation of the CNsl_Daosheng class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Nsl_Daosheng.h"
#include "..\..\..\config.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNsl_Daosheng::CNsl_Daosheng()
{
	szCName = "道生禪師";
	szEName = "daosheng";
	szLong = "他是一位身材高大的中年僧人，兩臂粗壯，膀闊腰圓。他看起來正忙著給大伙做飯，\
身穿一襲灰布鑲邊袈裟，似乎有一身武藝。";

	szXFileName = "pmudcjshs04";
	szSex = "M";
	nAttitude = NP_friendly;
	szFamily = "少林派";
	szRoom = "sl_cf";

	nAge =  40;
	nStr = 20;
	nInt = 20;
	nCon = 20;
	nDex = 20;
	nMax_qi = 400;
	nMax_jing = 300;
	nShen = 700;
	nEff_force = 450;
	nMax_force = 450;
	nAdd_force = 40;
	nCombat_exp =  10000;
	nScore = 100;

	AddAsk("饅頭",NPCASK_visible,"");
	AddAsk("水",NPCASK_visible,"");

	SetSkill("BaseUnarmed", 50, 0, "Strike_Banruo");
	SetSkill("BaseSword",50,0,"Sword_Damo");
	SetSkill("BaseForce", 50,0,"Force_Hunyuan");
	SetSkill("Force_Hunyuan", 50);
	SetSkill("BaseDodge", 50,0,"Step_Shaolin");
	SetSkill("Step_Shaolin", 50);
	SetSkill("Strike_Banruo", 50);
	SetSkill("BaseParry", 50,0,"Sword_Damo");
	SetSkill("Sword_Damo", 50);
	SetSkill("OtherBuddhism", 50);
	SetSkill("OtherLiterate", 50);

//prepare_skill("BaseStrike",	ST_base,	SCM_strike,	 "banruo-zhang";

	nGeneration = 39;

	CEquip * lpEquipGoods;
	CWeapon * lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("qingsengyi");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("changjian");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);
	lpWeapon = lpWeaponGoods;
}

CNsl_Daosheng::~CNsl_Daosheng()
{
}

TRetInfo CNsl_Daosheng::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;

	if( szName == "饅頭")
	{
		if ((who->nEat > 100) && (who->szFamily != "少林派"))
			TRet_return(GetSpecialName(who,1) + "與本派素無來往，不知此話從何談起？");
		if (who->GetGoods((char *)(LPCTSTR)"饅頭") != NULL )
		{
			ri.szRet.Format("%s你現在身上不是有饅頭嗎，怎麼又來要了？真是貪得無饜！",GetSpecialName(who,1));
			return ri;
		}
		CFood * lpFood = GetFoodClass("mantou");
		ri.szRet = who->AddGoods(lpFood);
		if (ri.szRet != "OK") {
			delete lpFood;
			return ri;
		}
//		ri.szRet.Format("道生給%s一個熱騰騰的饅頭。", who->szCName);
//		who->SendMsgToAll(ri.szRet);

		ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"饅頭","空",1,"個");
		who->SendMsg(ri.szRet);

		if (who->nEat <= 100)
			ri.szRet = "怎麼餓得這麼慘，拿著，快吃吧！";
		else 
			ri.szRet = "拿去吧，別忘了勤加修煉本寺佛法。";
	}
	else if( szName == "水" )
	{
		CJiuDai * lpJiuDai = dynamic_cast<CJiuDai *>(who->GetClassGoods(GK_jiudai));
		if (lpJiuDai == NULL)
		{
			if( who->szFamily != "少林派" )
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
//				ri.szRet.Format("道生給%s一個裝滿清水的用葫蘆製成的水壺。", who->szCName);
//				who->SendMsgToAll(ri.szRet);

				ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"清水葫蘆","清水",1,"個");
				who->SendMsg(ri.szRet);
		
				if (who->nDrink <= 100)
					ri.szRet = "怎麼渴得這麼厲害，趕快喝一口吧！";
				else 
					ri.szRet = "拿去吧，別忘了好好練本寺的功夫。";
				ri.bRet = TRUE;
				return ri;
			}
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
		if(lpJiuDai->nRemain > 0)
		{
			//ri.szRet.Format("道生把%s的%s裡面的%s倒出來，又重新裝滿了清水。", who->szCName, lpJiuDai->lpGoods->szCName, lpJiuDai->szLoadName);
			//who->SendMsgToAll(ri.szRet);
			ri.szRet.Format("道生把你的%s裡面的%s倒出來，又重新裝滿了清水。",lpJiuDai->lpGoods->szCName,lpJiuDai->szLoadName);
		}
		else
		{
			//ri.szRet.Format("道生把%s的%s裡面裝滿了清水。", who->szCName, lpJiuDai->lpGoods->szCName);
			//who->SendMsgToAll(ri.szRet);
			ri.szRet.Format("道生把你的%s裡面裝滿了清水。",lpJiuDai->lpGoods->szCName);
		}
		lpJiuDai->nRemain = lpJiuDai->lpJiuDai->nMaxRemain;
		lpJiuDai->szLoadName = "清水";
	}
	ri.bRet = TRUE;
	return ri;
}