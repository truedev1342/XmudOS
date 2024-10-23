// Nxx_Dizi.cpp: implementation of the CNxx_Dizi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Nxx_Dizi.h"
#include "..\..\..\config.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNxx_Dizi::CNxx_Dizi()
{
	szCName = "星宿派弟子";
	szEName = "xingxudizi";
	szSex = "M" ;
	nAge =  30+random(6);
	szLong =
		"這是星宿派的一個普通弟子，在星宿海裡管眾人的用膳。";
	nAttitude = NP_friendly | NP_apprentice;
    nShen = -100;

	szXFileName = "pmudznnz03";
	szRoom		= "xx_cf";
	
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

	AddAsk("羊肉串",NPCASK_visible,"");
	AddAsk("馬奶酒",NPCASK_visible,"");
	
	SetSkill("BaseForce", 30);
	SetSkill("BaseDodge", 20);
	SetSkill("BaseUnarmed", 17+random(10));
	SetSkill("BaseParry", 20);
/*	set_temp("apply/attack", 10);
	set_temp("apply/defense", 15);
	set_temp("apply/damage", 3);
*/	
	szFamily = "星宿派";
	nGeneration = 4;
	
	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNxx_Dizi::~CNxx_Dizi()
{

}
TRetInfo CNxx_Dizi::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	if (who->szFamily != "星宿派")
		TRet_return(GetSpecialName(who,1) + "不是本派弟子，不能在此用餐。");
	if( szName == "羊肉串" )
	{
		if (who->nEat > who->nMax_Eat*85/100)
			TRet_return(GetSpecialName(who,1) + "你現在不是很飽嗎？等一下再來吧。");
		if (who->GetGoods((char *)(LPCTSTR)"羊肉串") != NULL )
		{
			ri.szRet.Format("%s你現在身上不是還有羊肉串嗎，先吃完再說吧。",
				GetSpecialName(who,1));
			return ri;
		}

		CFood * lpFood = GetFoodClass("yangrouchuan");
		ri.szRet = who->AddGoods(lpFood);
		if (ri.szRet != "OK") {
			delete lpFood;
			return ri;
		}
//		ri.szRet.Format("星宿派弟子給%s一串烤得香噴噴的羊肉串。", who->szCName);
//		who->SendMsgToAll(ri.szRet);

		ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"羊肉串","空",1,"串");
		who->SendMsg(ri.szRet);

		ri.szRet = "不是我吹牛，我烤的羊肉串可是天下最好吃的了。";
	}
	else if( szName == "馬奶酒")
	{
		CJiuDai * lpJiuDai = dynamic_cast<CJiuDai *>(who->GetClassGoods(GK_jiudai));
		if (lpJiuDai == NULL) {
			if (who->nDrink > who->nMax_Drink*85/100)
				TRet_return(GetSpecialName(who,1) + "你都不渴！喝那麼多想干什麼？");
			lpJiuDai = GetJiuDaiClass("manaihu");
			lpJiuDai->nRemain = lpJiuDai->lpJiuDai->nMaxRemain;
			lpJiuDai->szLoadName = "馬奶酒";
			lpJiuDai->nDurg = 10;
			lpJiuDai->nSupply = 0;
			lpJiuDai->nDrink = 25;
			CString szUnit = lpJiuDai->lpGoods->szUnit;
			ri.szRet = who->AddGoods(lpJiuDai);
			if (ri.szRet != "OK") {
				delete lpJiuDai;
				return ri;
			}
//			ri.szRet.Format("星宿派弟子給%s一個馬奶酒壺。", who->szCName);
//			who->SendMsgToAll(ri.szRet);

			ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"馬奶酒壺","馬奶酒",1,szUnit);
			who->SendMsg(ri.szRet);
			ri.szRet = "拿去慢慢喝，別喝醉了。";
		} else {
			if(lpJiuDai->nRemain != 0)
			{
				ri.szRet.Format("你的%s里不是還有%s嗎？你都要光了，別人喝什麼？",
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
				"馬奶酒",
				1,
				lpJiuDai->lpGoods->szUnit);
			who->SendMsg(ri.szRet);

			lpJiuDai->nRemain = lpJiuDai->lpJiuDai->nMaxRemain;
			lpJiuDai->nDurg = 10;
			lpJiuDai->nSupply = 0;
			lpJiuDai->nDrink = 25;
			lpJiuDai->szLoadName = "馬奶酒";

			//ri.szRet.Format("星宿派弟子把%s的%s裡面裝滿了馬奶酒。", who->szCName, lpJiuDai->lpGoods->szCName);
			//who->SendMsgToAll(ri.szRet);
			ri.szRet.Format("星宿派弟子把你的%s裡面裝滿了馬奶酒。",lpJiuDai->lpGoods->szCName);
		}
	}
	ri.bRet = TRUE;
	return ri;
}