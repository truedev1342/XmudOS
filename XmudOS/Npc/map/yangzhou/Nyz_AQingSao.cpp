// Nyz_AQingSao.cpp: implementation of the CNyz_AQingSao class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Nyz_AQingSao.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNyz_AQingSao::CNyz_AQingSao()
{
	szCName		= "阿慶嫂";
	szEName		= "aqingsao";
//	set("title", "茶館老板娘";
	szNickName	= "揚州一支花";
	nShen		= 50;
	szXFileName	= "pmudgf01";
	szRoom		= "yz_cguan";

	nStr		= 30;
	szSex		= "F";
	nAge		=  25;
	szLong		=
		"阿慶嫂是揚州城里有名的大美人，因為爺兒們總喜歡往她這兒逛，"
		"所以她對城里的一舉一動都了如執掌。";
	nCombat_exp	= 500;
	nAttitude	= NP_friendly | NP_apprentice;
/*
	set("inquiry", ([
		"阿慶" : "我們家阿慶去北邊做生意去了耶。",
		"生意" : "這個麼……。",
	]);
	
	set("vendor_goods", ([
		"huasheng":__DIR__"obj/peanut",
		"tofu":__DIR__"obj/tofu",
	]);

*/	
	CEquip * lpEquipGoods;

	lpEquipGoods = GetEquipClass("pinkcloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);
}

CNyz_AQingSao::~CNyz_AQingSao()
{

}

/*

void init()
{
	CPlayerInfo *who;
	::init(;
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting";
		call_out("greeting", 1, ob;
	}
        add_action("do_vendor_list", "list";
}

void greeting(CPlayerInfo *who)
{
	if (!ob || environment(ob) != environment())
		return;
	switch(random(2)) {
	case 0 :
		say("阿慶嫂笑眯眯地說道︰這位" + GetSepcialName(who,1) +
			"，快請進來喝杯熱茶。";
		break;
	case 1 :
		say("阿慶嫂說道︰喲！這位" + GetSepcialName(who,1) + 
			"您來了啊！本店有剛炸好的五香花生出售。";
		break;
	}
}
*/