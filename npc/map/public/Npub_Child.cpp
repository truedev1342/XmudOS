#include "stdafx.h"
#include "Npub_Child.h"



CNpub_Child::CNpub_Child()
{
	static int number = 0;
	number ++;

	szCName = "小孩";
	szEName.Format("xiaohai%d",number);
	szXFileName.Format("pmudxnh0%d",random(2)+1);
    szSex = "M" ;
    nAge =  11;
    szLong = "這是個農家小孩子。不知為何跑出來玩耍。";
    nCombat_exp =  20+ random(30);
    nShen = 300+random(300);
	nStr = 11;
	nDex = 11;
	nCon = 11;
	nInt = 11;
    nAttitude = NP_heroism | NP_apprentice;
	AddAsk("閒聊",NPCASK_visible,"小孩：我想吃糖葫蘆。");
}

CNpub_Child::~CNpub_Child()
{

}
