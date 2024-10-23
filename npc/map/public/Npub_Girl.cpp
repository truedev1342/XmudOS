#include "stdafx.h"
#include "Npub_Girl.h"


CNpub_Girl::CNpub_Girl()
{
	static int number = 0;
	number ++;

	szCName = "女孩";
	szEName.Format("girl%d",number);
	szSex = "F" ;
	nAge =  12;
	szLong = "這是個農家少女，雖然只有十二、三歲，身材已經開始發育。";
	
	nCombat_exp =  50 + random(20);
	nShen = 250+random(250);
	
	nStr = 14;
	nDex = 15;
	nCon = 16;
	nInt = 15;
	nAttitude = NP_friendly | NP_apprentice;
	nMoney = 10;

	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("buqun");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	szXFileName.Format("pmudsnv0%d",random(5)+1);
	//AddAsk("閒聊",NPCASK_visible,"");
}

CNpub_Girl::~CNpub_Girl()
{
}

/*TRetInfo CNpub_Girl::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
//誰要幫我想劇情呀>_<  
	if(szName=="閒聊")
	{
			switch(random(3))
			{
			case 0:
				ri.szRet = "女孩笑嘻嘻地說道：大哥哥，今天我採了朵紅花，您覺得我戴在頭上〔漂亮〕還是〔不漂亮〕？";
				break;
			case 1:
				ri.szRet = "女孩：";
				break;
			case 2:
				ri.szRet = "女孩：";
				break;
			}

	}
	ri.bRet = TRUE;
	return ri;
}
*/