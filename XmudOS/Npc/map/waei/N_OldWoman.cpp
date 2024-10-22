
#include "..\..\stdafx.h"
#include "N_OldWoman.h"
// Nuke +1
#include "..\..\..\config.h"

CN_OldWoman::CN_OldWoman()
{


	szCName = "老婆婆";
	szEName = "oldwoman1";
	szRoom = "xy_guangchang";
	nAge =  85;
	szSex = "F";
	szLong = "她是一個老婦人，用著慈詳的面容看著你。";
	nAttitude = NP_apprentice;
	nStr = 24;
	nDex = 16;
	nCombat_exp =  10000;
	nShen = 10000;

	szXFileName.Format("pmudlf01");

	// Nuke +1
	AddAsk("老婆婆",NPCASK_visible|NPCASK_newline,"老婆婆：年輕人啊，江湖風險多，\
若你願意耐心聽老婆婆一言，對你會有幫助的。");
	AddAsk("人在江湖",NPCASK_visible|NPCASK_newline,"老婆婆：人在江湖啊．．．是個\
〔網路多人線上遊戲〕，你只要加入這個世界，就可以和許多朋友一同在這個世界裡冒險，\
相互幫助。至於要成為大俠或是大魔王，就看你們自身的修為與造化了．．．");
	AddAsk("新手入門",NPCASK_visible|NPCASK_newline,"老婆婆：要在這險惡的江湖中生存，\
第一要務就是去追隨一個值得信賴的〔師父〕，勤練武藝。");
	AddAsk("師父",NPCASK_visible|NPCASK_newline,"老婆婆：這些武功高強的大師，大多隱居山林，\
想見他們也許並不容易．．．一切就隨緣吧。");
	AddAsk("幫助",NPCASK_visible,"");

	SetSkill("BaseUnarmed",	40);
	SetSkill("BaseDodge",	40);
	SetSkill("BaseParry",	40);
	SetSkill("BaseBlade",	40);
	SetSkill("BaseForce",	40);

	nDamage = 30;

	CEquip * lpEquipGoods;

	lpEquipGoods = GetEquipClass("oldrobe");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CN_OldWoman::~CN_OldWoman()
{
}

TRetInfo CN_OldWoman::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	if( szName == "幫助")
	{
		if (((who->nMoney <10) && (who->nDrink < 40 )) || 
			((who->nMoney < 1) && (who->nEat < 40)) ) {
			who->nMoney+=20;
			if(who->szFamily != "丐幫") who->nShen -= 10;
			who->SendAllInfo();
			ri.szRet = "老婆婆：唉呀，振作點！這兒有點盤纏，你先拿去用吧！";
			ri.bRet = TRUE;
			return ri;
		} else {
			ri.szRet.Format("老婆婆笑說：呵呵，真的有困難時再來找我吧！");
			ri.bRet = TRUE;
			return ri;
		}
	}
	ri.bRet = TRUE;
	return ri;
}
