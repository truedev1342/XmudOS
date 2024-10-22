// Nsl_KongMin.cpp: implementation of the CNsl_KongMin class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Nsl_KongMin.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNsl_KongMin::CNsl_KongMin()
{
    szCName = "空明和尚";
	szEName = "kongmin";
	szRoom = "sl_waigc";
	//szRoom = "yz_bju";
	szFamily = "少林派";
	nAge =  20;
	szSex = "M";
	szLong = "這是一個少林弟子。";
	nAttitude = NP_apprentice | NP_guard;
	
	szXFileName = "pmudpths02";//3D模型文件名
	
	nShen = 80;		//神的值
	nStr = 25;		//臂力
	nInt = 25;		//悟性
	nCon = 25;		//根骨
	nDex = 25;		//身法
	nEff_qi = 110;	//有效氣
	nMax_qi = 110;	//最大氣,當前的,受傷後會減少
	nEff_jing = 110;	//有效精
	nMax_jing = 110;	//最大精
	nEff_jingli = 5;//有效精力
	nMax_jingli = 5;//最大精力
	
	nEff_force = 6;	//有效內力
	nMax_force = 6;	//最大內力
	nCombat_exp = 1500;//戰斗經驗
	

	// Nuke +1
	AddAsk("功德箱",NPCASK_visible,"");

	SetSkill("BaseUnarmed",	15);
	SetSkill("BaseParry", 16);
	SetSkill("BaseDodge", 40);
	SetSkill("BaseForce", 40);

//	CGoods * lpSpecial;
//	lpSpecial = GetNormalClass("letter");
//	listequip.AddTail(lpSpecial);
}

CNsl_KongMin::~CNsl_KongMin()
{

}

TRetInfo CNsl_KongMin::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	
	if (szName == "功德箱")
	{
		if (who->GetGoods("功德箱") != NULL)
		{		
			CGoods *lpSpecial = dynamic_cast<CGoods *>(who->GetGoods("功德箱"));
			
            ri.szRet.Format("%s %s %s交給空明和尚功德箱。",SZOKMSG,szYellowHigt,who->szCName);
			who->SendMsg(ri.szRet);
			// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
			ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,"功德箱","空",1,lpSpecial->lpGoods->szUnit,0);
			who->SendMsg(ri.szRet);
			who->SubGoods("gongdebox");

			CGoods * lpLetter = GetNormalClass("letter");
			//CGoods * lpLetter = GetSpecialClass("letter");
			CString szUnit = lpLetter->lpGoods->szUnit;
			ri.szRet = who->AddGoods(lpLetter);
			if (ri.szRet != "OK") {
				delete lpLetter;
				return ri;
			}
            
			ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"信","空",1,szUnit,0);
			who->SendMsg(ri.szRet);
			ri.szRet.Format("%s %s 空明和尚：哦！我們等這很久了，謝謝你把它帶來，也請你幫我們把這封信交給揚州鏢頭。",SZOKMSG,szGreenHigt);
			who->SendMsg(ri.szRet);
			
			CFood * lpFood = GetFoodClass("mantou");
			lpFood->nCount = 5;
			szUnit = lpFood->lpGoods->szUnit;
			ri.szRet = who->AddGoods(lpFood);
			if (ri.szRet != "OK") {
				delete lpFood;
				return ri;
			}
			ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"饅頭","空",5,szUnit,0);
			who->SendMsg(ri.szRet);
			ri.szRet.Format("%s %s 空明和尚：善哉，一點薄禮請笑納！",SZOKMSG,szGreenHigt);
			who->SendMsg(ri.szRet);
			ri.szRet.Format("空明和尚給%s五個熱騰騰的饅頭和一封信。",who->szCName);
		}	
		else
		{
			ri.szRet.Format("你手上沒有功德箱!");
            ri.bRet = TRUE;
	        return ri;
		}
		
	}
	ri.bRet = TRUE;
	return ri;
}