// Npub_XiaoEr.cpp: implementation of the CNpub_XiaoEr class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Npub_XiaoEr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static XiaoEr SXiaoEr;
CNpub_XiaoEr::CNpub_XiaoEr()
{
	lpXiaoEr = &SXiaoEr;
	lpXiaoEr->number++;

	szCName = "店小二";
	szEName.Format("xiaoer%d",lpXiaoEr->number);
	szSex = "M" ;
	nAge =  22;
	szXFileName.Format("pmudhj01");
	szLong =
		"這位店小二正笑咪咪地忙著，還不時拿起掛在脖子上的抹布擦臉。";
	nCombat_exp =  100;
	nShen = 50;
	nAttitude = NP_friendly | NP_heroism | NP_apprentice;
//	set("rank_info/respect", "小二哥";
}

CNpub_XiaoEr::~CNpub_XiaoEr()
{

}

/*
void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(2) ) {
		case 0:
			say( "店小二笑咪咪地說道︰這位" + RANK_D->query_respect(ob)
				+ "，進來喝杯茶，歇歇腿吧。\n");
			break;
		case 1:
			say( "店小二用脖子上的毛巾抹了抹手，說道︰這位" + RANK_D->query_respect(ob)
				+ "，請進請進。\n");
			break;
	}
}

int accept_object(object who, object ob)
{
	
	if (ob->query("money_id") && ob->value() >= 5000) 
	{
		tell_object(who, "小二一哈腰，說道︰多謝您老，客官請上樓歇息。\n");

		who->set_temp("rent_paid",1);

		return 1;
	}

	return 0;
}
*/