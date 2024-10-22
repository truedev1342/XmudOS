// Npub_Bing.cpp: implementation of the CNpub_Bing class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Npub_Bing.h"
// Nuke +1
#include "..\..\..\config.h"


static Bing SBing;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpub_Bing::CNpub_Bing()
{
//	static int number = 0;
	lpBing=&SBing;
	lpBing->number ++;

	szCName = "官兵";
	szEName.Format("guanbing%d",lpBing->number);
	nAge =  32;
	szSex = "M";
	szLong = "官兵的武功雖然不高，但是他們講的是人多力量大，武林中人很少去招惹他們。";
	nAttitude = NP_heroism | NP_apprentice | NP_guard;
	nStr = 24;
	nDex = 16;
	nCombat_exp =  random(4000)+3000;
	nShen = random(300)-100;

	szXFileName.Format("pmudws03");

	// Nuke +1
	AddAsk("饅頭",0,"");
	AddAsk("吳遠志",0,"");

	SetSkill("BaseUnarmed",	25);
	SetSkill("BaseDodge",	25);
	SetSkill("BaseParry",	25);
	SetSkill("BaseBlade",	25);
	SetSkill("BaseForce",	25);

	nDamage = 30;

	//"官兵喝道︰大膽刁民，竟敢造反不成？",
	//"官兵喝道︰跑得了和尚跑不了廟，你還是快快束手就擒！",

	CEquip * lpEquipGoods;
	CWeapon * lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("junfu");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("gangdao");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);
    lpWeapon = lpWeaponGoods;
}

CNpub_Bing::~CNpub_Bing()
{
}

/*
int accept_fight(object me)
{
	ri.szRet = "大爺我守邊關累得要死，沒空和" + GetSepcialName(who,1) + "過招玩。";
	return ri;
}
*/

TRetInfo CNpub_Bing::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	if( szName == "饅頭")
	{
		if ((who->nEat > who->nMax_Eat*30/100) && (who->nMoney > 0))
			TRet_return("去！去！你當老子是大善人啊！");

		if (who->GetGoods("饅頭") != NULL )
		{
			ri.szRet.Format("%s你現在身上不是還有饅頭嗎，別這麼貪心！",
				GetSpecialName(who,1));
			return ri;
		}

		CFood * lpFood = GetFoodClass("mantou");
		ri.szRet = who->AddGoods(lpFood);
		if (ri.szRet != "OK") {
			delete lpFood;
			return ri;
		}
//		ri.szRet.Format("官兵給%s一個熱騰騰的饅頭。", who->szCName);
//		who->SendMsgToAll(ri.szRet);

		ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"饅頭","空",1,"個");
		who->SendMsg(ri.szRet);

		ri.szRet = "天啊！餓成這樣，我身邊正好帶著一個饅頭，給了你吧，等一下我再去拿過。";
		ri.bRet = TRUE;
		return ri;
	}
	if (szName == "吳遠志")
	{
		CEquip *lpEquip = dynamic_cast<CEquip *>(who->GetGoods("軍服"));
		if ( lpEquip != NULL)
		{
			
			if (lpBing->whoami == szEName) {
				if (lpBing->count++<1) { // 詢問幾次後才算真的找到

					CString newname;
					newname.Format("guanbing%d",random(lpBing->number)+1);
					while (newname == szEName) {
						newname.Format("guanbing%d",random(lpBing->number)+1);
					}
					lpBing->whoami = newname;
					ri.szRet = "吳遠志？啊！他已經調到其它軍營了！";
					ri.bRet = TRUE;
					return ri;
				} else {
					//dainty modify
			        if(lpEquip->nWearWhere!=0)
					{
                        ri.szRet = "我就是吳遠志！你身上怎會穿著我的軍服啊！？";
				        ri.bRet = TRUE;
				        return ri;
					}
			  		CGoods * lpLetter = GetNormalClass("家書");
					CString szUnit = lpLetter->lpGoods->szUnit;
					ri.szRet = who->AddGoods(lpLetter);
					if (ri.szRet != "OK") {
						delete lpLetter;
						return ri;
					}
					lpBing->count=0;
					// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
					ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,"軍服","空",1,lpEquip->lpGoods->szUnit,0);
					who->SendMsg(ri.szRet);
					who->SubGoods("軍服");
					// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
					ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"家書","空",1,szUnit,0);
					who->SendMsg(ri.szRet);
					ri.szRet = "我就是吳遠志！謝謝你替我帶來的棉襖！"
						"麻煩您帶這個給我的母親，我要請她重金謝謝你！"
						"我馬上就調走了，請多保重！";
					lpBing->whoami.Format("guanbing%d",random(lpBing->number)+1);
					ri.bRet = TRUE;
					return ri;
				}
			} else {
				ri.szRet = "咦？這個名字好像曾聽過！";
				ri.bRet = TRUE;
				return ri;
			}
		} else {
			ri.szRet = "軍隊正忙著！";
			ri.bRet = TRUE;
			return ri;
		}
	}
	ri.bRet = TRUE;
	return ri;
}
