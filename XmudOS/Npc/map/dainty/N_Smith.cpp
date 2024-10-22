// N_Smith.cpp: implementation of the CN_Smith class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "N_Smith.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CN_Smith::CN_Smith()
{
    static int number = 0;
	number ++;

	szCName = "鐵匠";
	szEName.Format("smith%d",number); // 英文名
	szNickName = "鐵匠";
	nAge =  32;								
	szSex = "M";
	szLong = "這是一個鐵匠，販售各種兵器防具。";
	nAttitude = NP_heroism | NP_apprentice | NP_nofight;
	nStr = 24;
	nDex = 16;
	nCombat_exp =  2000;
	nShen = 500;

	szXFileName = "pmudsn02";

	// AddAsk(Item, Attrib, Prompt); 最多加入10項
	// Attrib:	NPCASK_visible = 顯示在物品列表中
	//			NPCASK_newline = 在訊息前加一行空白
	CWeapon * lpWeapon1 = GetWeaponClass("長劍");
	CWeapon * lpWeapon2 = GetWeaponClass("大刀");
	CWeapon * lpWeapon3 = GetWeaponClass("單刀");
	CWeapon * lpWeapon4 = GetWeaponClass("短劍");
	CWeapon * lpWeapon5 = GetWeaponClass("鋼杖");
	CWeapon * lpWeapon6 = GetWeaponClass("鐵扇");
	CEquip * lpEquip = GetEquipClass("鐵甲");
    
    char szTemp[256];
	sprintf(szTemp,"長劍%d枚銅錢，大刀%d枚銅錢，單刀%d枚銅錢，短劍%d枚銅錢，鋼杖%d枚銅錢，鐵甲%d枚銅錢，鐵扇%d枚銅錢",
		lpWeapon1->lpGoods->nCost,lpWeapon2->lpGoods->nCost,lpWeapon3->lpGoods->nCost,
		lpWeapon4->lpGoods->nCost,lpWeapon5->lpGoods->nCost,lpEquip->lpGoods->nCost,lpWeapon6->lpGoods->nCost);
	delete lpWeapon1; 
	delete lpWeapon2;
	delete lpWeapon3;
	delete lpWeapon4;
	delete lpWeapon5;
	delete lpWeapon6;
	delete lpEquip;

	AddAsk("價錢",NPCASK_visible,szTemp);
	AddAsk("買長劍",NPCASK_visible,"");
	AddAsk("買大刀",NPCASK_visible,"");
	AddAsk("買單刀",NPCASK_visible,"");
	AddAsk("買短劍",NPCASK_visible,"");
	AddAsk("買鋼杖",NPCASK_visible,"");
	AddAsk("買鐵甲",NPCASK_visible,"");
	AddAsk("買鐵扇",NPCASK_visible,"");
    //AddAsk("賣",NPCASK_visible,"");
	

	SetSkill("BaseDodge",		15);
	SetSkill("BaseParry",		15);
	SetSkill("BaseUnarmed",		15);

	nDamage = 20;
	nMoney = 500;
}

CN_Smith::~CN_Smith()
{

}
TRetInfo CN_Smith::DoAsk(CPlayerInfo *who, CString szName)
{
	CWeapon *lpWeapon;
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
    
	if( szName == "買長劍")
	{
		ri.bRet = TRUE;
  		lpWeapon = GetWeaponClass("長劍");
		if (who->nMoney<lpWeapon->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpWeapon;
			return ri;
		}
		int nCost = lpWeapon->lpGoods->nCost;
		CString szUnit = lpWeapon->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
		who->nMoney-=nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"長劍","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "鐵匠：來！這是您的長劍。";
	}
	else if( szName == "買大刀")
	{
		ri.bRet = TRUE;
  		lpWeapon = GetWeaponClass("大刀");
		if (who->nMoney<lpWeapon->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpWeapon;
			return ri;
		}
		int nCost = lpWeapon->lpGoods->nCost;
		CString szUnit = lpWeapon->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
		who->nMoney-=nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"大刀","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "鐵匠：來！這是您的大刀。";
	}
	else if( szName == "買單刀")
	{
		ri.bRet = TRUE;
  		lpWeapon = GetWeaponClass("單刀");
		if (who->nMoney<lpWeapon->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpWeapon;
			return ri;
		}
		int nCost = lpWeapon->lpGoods->nCost;
		CString szUnit = lpWeapon->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
		who->nMoney-=nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"單刀","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "鐵匠：來！這是您的單刀。";
	}
	else if( szName == "買短劍")
	{
		ri.bRet = TRUE;
  		lpWeapon = GetWeaponClass("短劍");
		if (who->nMoney<lpWeapon->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpWeapon;
			return ri;
		}
		int nCost = lpWeapon->lpGoods->nCost;
		CString szUnit = lpWeapon->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
		who->nMoney-=nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"短劍","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "鐵匠：來！這是您的短劍。";
	}
	else if( szName == "買鋼杖")
	{
		ri.bRet = TRUE;
  		lpWeapon = GetWeaponClass("鋼杖");
		if (who->nMoney<lpWeapon->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpWeapon;
			return ri;
		}
		int nCost = lpWeapon->lpGoods->nCost;
		CString szUnit = lpWeapon->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
		who->nMoney-=nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"鋼杖","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "鐵匠：來！這是您的鋼杖。";
	}
	else if( szName == "買鐵甲")
	{
		ri.bRet = TRUE;
  		CEquip *lpEquip = GetEquipClass("鐵甲");
		if (who->nMoney<lpEquip->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpEquip;
			return ri;
		}
		int nCost = lpEquip->lpGoods->nCost;
		CString szUnit = lpEquip->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpEquip);
		if (ri.szRet != "OK") {
			delete lpEquip;
			return ri;
		}
		who->nMoney-=nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"鐵甲","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "鐵匠：來！這是您的鐵甲。";
	}
	else if( szName == "買鐵扇")
	{
		ri.bRet = TRUE;
  		lpWeapon = GetWeaponClass("鐵扇");
		if (who->nMoney<lpWeapon->lpGoods->nCost)
		{
			ri.szRet="你現在身上錢不夠";
			delete lpWeapon;
			return ri;
		}
		int nCost = lpWeapon->lpGoods->nCost;
		CString szUnit = lpWeapon->lpGoods->szUnit;
        ri.szRet = who->AddGoods(lpWeapon);
		if (ri.szRet != "OK") {
			delete lpWeapon;
			return ri;
		}
		who->nMoney-=nCost;
		// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"鐵扇","空",1,szUnit,-nCost);
		who->SendMsg(ri.szRet);
		ri.szRet = "鐵匠：來！這是您的鐵扇。";
	}
/*	else if( szName == "賣")
	{
		ri.bRet = TRUE;
		ri.szRet = "鐵匠：您要賣什麼？";        
	    return ri;
	}*/

	return ri;
}
/*
TRetInfo CN_Smith::DoAsk(CPlayerInfo *who, CString szName,CString szTarget)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;

	CGoods *lpGoods;
	BOOL hasGoods = FALSE;
	int nKind;
	int nCost;
	CString szEName,szUnit;

	if( szName == "賣")
	{
		ri.bRet = TRUE;
		if(szTarget=="")
		{
			ri.szRet = "鐵匠：您要賣什麼？";        
	        return ri;
		}	
		for(int j=0;j<who->listequip.GetCount();j++)
		{
		    if(who->listequip.GetAt(who->listequip.FindIndex(j))->lpGoods->szCName == szTarget)
			{
				hasGoods = TRUE;
				lpGoods = who->listequip.GetAt(who->listequip.FindIndex(j));
				nKind = who->listequip.GetAt(who->listequip.FindIndex(j))->lpGoods->nKinds;
			    nCost = who->listequip.GetAt(who->listequip.FindIndex(j))->lpGoods->nCost;
				szEName = who->listequip.GetAt(who->listequip.FindIndex(j))->lpGoods->szEName;
				szUnit = who->listequip.GetAt(who->listequip.FindIndex(j))->lpGoods->szUnit;
				break;
			}
		}
		if(hasGoods)
		{
			if(lpGoods->lpGoods->nUsage & GP_nosell)
			{
				ri.szRet = "鐵匠：沒有人會收這個的！";
				return ri;
			}
			if(nKind ==GK_equip && dynamic_cast<CEquip *>(lpGoods)->nWearWhere!=0)
			{
				ri.szRet ="這項物品正在使用中。";
				return ri;
			}
			if(nKind ==GK_weapon && dynamic_cast<CWeapon *>(lpGoods)->bWield)
			{
				ri.szRet ="這項物品正在使用中。";
				return ri;
			}
			switch(nKind)
			{
			case GK_weapon:
			case GK_equip:
				if(nCost<100)
                    ri.szRet = "鐵匠：這是便宜貨嘛！我是不收的。";
				else
				{
					nCost = (int)(nCost*0.8);
			        ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,szTarget,"空",1,szUnit,nCost);			
			        who->SendMsg(ri.szRet);
			        who->SubGoods(szEName);
			        who->nMoney+=nCost;
					if(nCost>1000)
					    ri.szRet.Format("鐵匠：唷！這可是個好東西呢！算你%d枚銅錢好了。",nCost);
					else if(nCost>500)
						ri.szRet.Format("鐵匠：這貨看起來還不錯！算你%d枚銅錢好了。",nCost);
					else
						ri.szRet.Format("鐵匠：這東西看起來不怎麼值錢，算你%d枚銅錢好了。",nCost);
				}
				break;
			case GK_normal:
			case GK_drug:
			case GK_food:
			case GK_jiudai:
			case GK_book:
				ri.szRet = "鐵匠：我是不收這個的。";
				break;
			}
		}
		else
		{
			ri.szRet.Format("鐵匠：你身上沒有%s。",szTarget);       
	        return ri;
		}
	}	

	return ri;
}
*/