// Nsl_DaoXiang2.cpp: implementation of the CNsl_DaoXiang2 class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Nsl_DaoXiang2.h"
#include "..\..\..\config.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNsl_DaoXiang2::CNsl_DaoXiang2()
{
	szCName = "道象禪師";
	szEName = "daoxiang2";
	szLong =
		"他是一位身材高大的中年僧人，兩臂粗壯，膀闊腰圓。他手持兵"
		"刃，身穿一襲灰布瓖邊袈裟，似乎有一身武藝。"
	;

	szXFileName = "pmudcjshs04";
	szSex = "M";
	nAttitude = NP_friendly | NP_heroism | NP_guard;
//	set("class", "bonze";

	nAge =  40;
	nShen= 1000;
	nStr = 20;
	nInt = 20;
	nCon = 20;
	nDex = 20;
	nMax_qi = 400;
	nMax_jing = 300;
	nEff_force = 450;
	nMax_force = 450;
	nAdd_force = 40;
	nCombat_exp =  10000;
	nScore = 100;
	szRoom = "sl_kfc";

	AddAsk("金創藥",NPCASK_visible,"");
//	AddAsk("小還丹",NPCASK_visible,"");
//	AddAsk("大還丹",NPCASK_visible,"");

	SetSkill("BaseForce", 50, 0, "Force_Hunyuan");
	SetSkill("Force_Hunyuan", 50);
	SetSkill("BaseDodge", 50, 0, "Step_Shaolin");
	SetSkill("Step_Shaolin", 50);
	SetSkill("BaseUnarmed", 50, 0, "Strike_Banruo");
	SetSkill("Strike_Banruo", 50);
	SetSkill("BaseSword", 50, 0, "Sword_Damo");
	SetSkill("BaseParry", 50, 0, "Strike_Banruo");
	SetSkill("Sword_Damo", 50);
	SetSkill("OtherBuddhism", 50);
	SetSkill("OtherLiterate", 50);

	szFamily = "少林派";
	nGeneration = 39;

	SetTemp ("jin_count", 20);
//	SetTemp ("xiao_count",1);
//	SetTemp ("da_count",  1);

	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("qingsengyi");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);	
}

CNsl_DaoXiang2::~CNsl_DaoXiang2()
{

}
TRetInfo CNsl_DaoXiang2::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;

	if( szName == "金創藥")
	{
		if (who->szFamily != "少林派")
			TRet_return(GetSpecialName(who,1) + "與本派素無來往，不知此話從何談起？");
		if (who->GetGoods("金創藥") != NULL )
			TRet_return(GetSpecialName(who,1) + "你現在身上不是有顆藥丸嗎，怎麼又來要了？ 真是貪得無饜！");
		if (GetTemp("jin_count").nValue < 1)
			TRet_return("對不起，金創藥已經發完了");

		CDrug *lpDrug = GetDrugClass("jinchuangyao");
		CString szUnit = lpDrug->lpGoods->szUnit;
		ri.szRet = who->AddGoods(lpDrug);
		if (ri.szRet != "OK") {
			delete lpDrug;
			return ri;
		}
		AddTemp("jin_count", -1);
//		ri.szRet.Format("道象給%s一%s%s。", who->szCName, 
//			lpDrug->lpGoods->szUnit, lpDrug->lpGoods->szCName);
//		who->SendMsgToAll(ri.szRet);
		ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"金創藥","空",1,szUnit);
		who->SendMsg(ri.szRet);
		ri.szRet.Format("好吧，記住，不到危急關頭不要輕易使用此藥。");
	}
/*	else if( szName == "小還丹")
	{
		if (who->szFamily != "少林派")
			TRet_return(GetSpecialName(who,1) + "與本派素無來往，不知此話從何談起？");
		if (who->GetGoods("小還丹") != NULL )
			TRet_return(GetSpecialName(who,1) + "你現在身上不是有顆藥丸嗎，怎麼又來要了？ 真是貪得無饜！");
		if (GetTemp("xiao_count").nValue < 1)
			TRet_return("對不起，小還丹已經發完了");

		CDrug *lpDrug = GetDrugClass("xiaohuandan");
		CString szUnit = lpDrug->lpGoods->szUnit;
		ri.szRet = who->AddGoods(lpDrug);
		if (ri.szRet != "OK") {
			delete lpDrug;
			return ri;
		}
		AddTemp("xiao_count", -1);
//		ri.szRet.Format("道象給%s一%s%s。", who->szCName, 
//			lpDrug->lpGoods->szUnit, lpDrug->lpGoods->szCName);
//		who->SendMsgToAll(ri.szRet);
		ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"小還丹","空",1,szUnit);
		who->SendMsg(ri.szRet);
		ri.szRet.Format("好吧，記住，不到危急關頭不要輕易使用此藥。");
	}
	else if( szName == "大還丹")
	{
		if (who->szFamily != "少林派")
			TRet_return(GetSpecialName(who,1) + "與本派素無來往，不知此話從何談起？");
		if (who->GetGoods("大還丹") != NULL )
			TRet_return(GetSpecialName(who,1) + "你現在身上不是有顆藥丸嗎，怎麼又來要了？ 真是貪得無饜！");
		if (GetTemp("da_count").nValue < 1)
			TRet_return("對不起，大還丹已經發完了");

		CDrug *lpDrug = GetDrugClass("dahuandan");
		CString szUnit = lpDrug->lpGoods->szUnit;
		ri.szRet = who->AddGoods(lpDrug);
		if (ri.szRet != "OK") {
			delete lpDrug;
			return ri;
		}
		AddTemp("da_count", -1);
//		ri.szRet.Format("道象給%s一%s%s。", who->szCName, 
//			lpDrug->lpGoods->szUnit, lpDrug->lpGoods->szCName);
//		who->SendMsgToAll(ri.szRet);
		ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"大還丹","空",1,szUnit);
		who->SendMsg(ri.szRet);
		ri.szRet.Format("好吧，記住，不到危急關頭不要輕易使用此藥。");
	}*/
	ri.bRet = TRUE;
	return ri;
}