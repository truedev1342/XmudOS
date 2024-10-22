// Nsl_DaoChen.cpp: implementation of the CNsl_DaoChen class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Nsl_DaoChen.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNsl_DaoChen::CNsl_DaoChen()
{
	szCName = "道塵禪師";
	szEName = "daochen";
	szLong =
		"他是一位身材高大的中年僧人，兩臂粗壯，膀闊腰圓。他手持兵"
		"刃，身穿一襲灰布瓖邊袈裟，似乎有一身武藝。"
	;

	szXFileName = "pmudcjshs04";
	szSex = "M";
	nAttitude = NP_friendly | NP_heroism | NP_guard;

	nAge	=  40;
	nShen	= 1000;
	nStr	= 20;
	nInt	= 20;
	nCon	= 20;
	nDex	= 20;
	nMax_qi = 400;
	nMax_jing	= 300;
	nEff_force	= 450;
	nMax_force	= 450;
	nAdd_force	= 40;
	nCombat_exp = 10000;
	nScore = 100;
	szRoom = "sl_kfa";

	SetSkill("BaseForce", 50, 0, "Force_Hunyuan");
	SetSkill("Force_Hunyuan", 50);
	SetSkill("BaseDodge", 50, 0, "Step_Shaolin");
	SetSkill("Step_Shaolin", 50);
	SetSkill("BaseUnarmed", 50, 0, "Strike_Banruo");
	SetSkill("Strike_Banruo", 50);
	SetSkill("BaseParry", 50, 0, "Sword_Damo");
	SetSkill("Sword_Damo", 50);
	SetSkill("OtherBuddhism", 50);
	SetSkill("OtherLiterate", 50);

	szFamily = "少林派";
	nGeneration = 39;

	// AddAsk(Item, Attrib, Prompt); 最多加入10項
	// Attrib:	NPCASK_visible = 顯示在物品列表中
	//			NPCASK_newline = 在訊息前加一行空白
/*
	AddAsk("齊眉棍",NPCASK_visible,"");
	AddAsk("戒刀",NPCASK_visible,"");
	AddAsk("禪杖",NPCASK_visible,"");
	AddAsk("長劍",NPCASK_visible,"");
	AddAsk("皮鞭",NPCASK_visible,"");
*/
    AddAsk("竹棒",NPCASK_visible,"");
    AddAsk("竹劍",NPCASK_visible,"");
    AddAsk("木刀",NPCASK_visible,"");
	
//	this->SetTemp ("wuqi_count", 15);

	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("qingsengyi");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNsl_DaoChen::~CNsl_DaoChen()
{

}

TRetInfo CNsl_DaoChen::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	
	if(szName == "竹棒")
	{
		if (who->szFamily != "少林派")
		    TRet_return("道塵：施主並非本派弟子，不知此話從何談起？");
	    if (who->GetGoods("竹棒") != NULL )
		{
		    ri.szRet ="道塵：你現在身上已經有這樣武器了？我無法再給你了！";
		    return ri;
		}

	    CWeapon * lpWeapon = GetWeaponClass("zhubang");
		CString szUnit = lpWeapon->lpGoods->szUnit;
	    ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
	    ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"竹棒","空",1,szUnit);
	    who->SendMsg(ri.szRet);
	    ri.szRet.Format("道塵：拿去吧。不過要記住，武器只可防身練武，切不可憑此濫殺生靈！");
	}
	if(szName == "竹劍")
	{
		if (who->szFamily != "少林派")
		    TRet_return("道塵：施主並非本派弟子，不知此話從何談起？");
	    if (who->GetGoods("竹劍") != NULL )
		{
		    ri.szRet ="道塵：你現在身上已經有這樣武器了？我無法再給你了！";
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
	    ri.szRet.Format("道塵：拿去吧。不過要記住，武器只可防身練武，切不可憑此濫殺生靈！");
	}
	if(szName == "木刀")
	{
		if (who->szFamily != "少林派")
		    TRet_return("道塵：施主並非本派弟子，不知此話從何談起？");
	    if (who->GetGoods("木刀") != NULL )
		{
		    ri.szRet ="道塵：你現在身上已經有這樣武器了？我無法再給你了！";
		    return ri;
		}

	    CWeapon * lpWeapon = GetWeaponClass("mudao");
		CString szUnit = lpWeapon->lpGoods->szUnit;
	    ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
	    ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"木刀","空",1,szUnit);
	    who->SendMsg(ri.szRet);
	    ri.szRet.Format("道塵：拿去吧。不過要記住，武器只可防身練武，切不可憑此濫殺生靈！");
	}
/*	if (who->szFamily != "少林派")
		TRet_return(GetSpecialName(who, 1) + "與本派素無來往，不知此話從何談起？");
	if (who->GetGoods((char*)(LPCSTR)szName) != NULL )
	{
		ri.szRet.Format("%s你現在身上不是有這樣武器嗎，怎麼又來要了？真是貪得無饜！",GetSpecialName(who,1));
		return ri;
	}

	
	if (this->GetTemp ("wuqi_count").nValue < 1)
		TRet_return(GetSpecialName(who, 1) + "，你來晚了，武器已經發完了。");
	CString szWeapon;

	if (szName == "齊眉棍")
		szWeapon = "qimeigun";
	else if(szName == "戒刀")
		szWeapon = "jiedao";
	else if(szName == "禪杖")
		szWeapon = "chanzhang";
	else if(szName == "長劍")
		szWeapon = "changjian";
	else if(szName == "皮鞭")
		szWeapon = "changbian";
	else
		TRet_return("你有什麼事嗎？");

	AddTemp("wuqi_count", -1);
	CWeapon * lpWeapon = GetWeaponClass(szWeapon);
	CString szUnit = lpWeapon->lpGoods->szUnit;
	ri.szRet = who->AddGoods(lpWeapon);
	if (ri.szRet != "OK") {
		delete lpWeapon;
		return ri;
	}
//	ri.szRet.Format("道塵給%s一%s%s。", who->szCName, 
//		lpWeapon->lpGoods->szUnit, lpWeapon->lpGoods->szCName);
//	who->SendMsgToAll(ri.szRet);
	
	ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,szName,"空",1,szUnit);
	who->SendMsg(ri.szRet);
	ri.szRet.Format("拿去吧。不過要記住，武器只可防身練武，不可憑此殺害生靈。");
*/
	ri.bRet = TRUE;
	return ri;
}