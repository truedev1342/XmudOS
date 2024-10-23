// N_BiaoTou.cpp: implementation of the CN_BiaoTou class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "N_BiaoTou.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CN_BiaoTou::CN_BiaoTou()
{
    szCName = "鏢頭";
	szEName = "biaotou";
	szRoom = "yz_bju";
	nAge =  40;
	szSex = "M";
	szLong = "揚州鏢局總鏢頭。";
	nAttitude = NP_apprentice;
	
	szXFileName = "pmuddh01";//3D模型文件名
	
	nShen = 60;		//神的值
	nStr = 25;		//臂力
	nInt = 5;		//悟性
	nCon = 20;		//根骨
	nDex = 10;		//身法
	nEff_qi = 200;	//有效氣
	nMax_qi = 200;	//最大氣,當前的,受傷後會減少
	nEff_jing = 150;	//有效精
	nMax_jing = 150;	//最大精
	nEff_jingli = 30;//有效精力
	nMax_jingli = 30;//最大精力
	
	nEff_force = 30;	//有效內力
	nMax_force = 30;	//最大內力
	nCombat_exp = 500;//戰斗經驗
	nMoney = 200;
	

	// Nuke +1
	AddAsk("工作",NPCASK_visible|NPCASK_newline,"鏢頭：我手上有一件工作，要把這功德箱送到少林寺，交給空明和尚，不過因人手不夠，閣下〔願意〕接這差事嗎？");
	
	AddAsk("不願意",0,"真是遺憾，那我只好找別人幫忙了。");
	AddAsk("願意",0,"");
	AddAsk("信",0,"");

	SetSkill("BaseUnarmed",	35);
	SetSkill("BaseParry",	30);
    SetSkill("BaseBlade",	35);
	SetSkill("BaseDodge",	35);
	SetSkill("BaseForce",	35);
	
    lpWeapon = GetWeaponClass("dadao");
	lpWeapon->bWield = TRUE;
	listequip.AddTail(lpWeapon);

	CGoods * lpSpecial;
	lpSpecial = GetNormalClass("gongdebox");
	//lpSpecial = GetSpecialClass("gongdebox");
	listequip.AddTail(lpSpecial);
}

CN_BiaoTou::~CN_BiaoTou()
{

}
TRetInfo CN_BiaoTou::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	if( szName == "願意")
	{
		if (who->GetGoods("信") != NULL )
		{
			ri.szRet.Format("鏢頭：你已經完成任務了嗎？");
			return ri;
		}
		if (who->GetGoods("功德箱") != NULL )
		{
			ri.szRet = "鏢頭：一切就拜託你了！";
			return ri;
		}

 		CGoods * lpSpecial= GetNormalClass("gongdebox");
  		//CGoods * lpSpecial= GetSpecialClass("gongdebox");
		CString szUnit = lpSpecial->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpSpecial);
		if (ri.szRet != "OK") {
			delete lpSpecial;
			return ri;
		}
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"功德箱","空",1,szUnit,0);
		who->SendMsg(ri.szRet);
		ri.szRet.Format("%s %s 鑣頭交給%s一個功德箱。",SZOKMSG,szYellowHigt,who->szCName);
		who->SendMsg(ri.szRet);
		ri.szRet = "鏢頭：那就拜託你了，這是功德箱。";
		ri.bRet = TRUE;
		return ri;
	}
	if (szName == "信")
	{
		if (who->GetGoods("信") != NULL )
		{
			//CSpecial * lpLetter = dynamic_cast<CSpecial *> (who->GetGoods((char *)(LPCTSTR)"信"));
		    //if (lpLetter != NULL )
			//{
			//lpLetter->nNew =0;
			//who->CheckGoods();
			// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
			ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,"信","空",1,"封");			
			who->SendMsg(ri.szRet);
			who->SubGoods("letter");
			who->nMoney+=100;
			who->nShen += 100;
			who->SendAllInfo();
			ri.szRet.Format("鏢頭：真是太好了。謝謝你的幫忙，這點錢($100)你就收下吧！");
		}
		else
			ri.szRet.Format("鏢頭：什麼信？我不知道!");

	}
	ri.bRet = TRUE;
	return ri;
}