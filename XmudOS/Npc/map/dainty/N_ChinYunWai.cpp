// N_ChinYunWai.cpp: implementation of the CN_ChinYunWai class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "N_ChinYunWai.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CN_ChinYunWai::CN_ChinYunWai()
{
    szCName = "秦員外";
	szEName = "chinyunwai";
	szLong = "這是一個衣衫華麗的中年男子。";
	szSex = "M";
	szXFileName ="pmudznnz02";
	szRoom = "yz_czdt";

	nAge =  50;
	nAttitude = NP_heroism | NP_apprentice;
	nShen = 10000;
	nStr = 30;
	nInt = 30;
	nCon = 30;
	nDex = 30;
	
	nMax_qi = 5000;
	nMax_jing = 3000;
	nEff_force = 10000;
	nMax_force = 10000;
	nAdd_force = 100;
	nCombat_exp =  20000;

	SetSkill("BaseForce",		200);
	SetSkill("BaseDodge",		180);
	SetSkill("BaseUnarmed",		200);
	SetSkill("BaseParry",		180);
	SetSkill("BaseSword",		200);
	SetSkill("BaseBlade",		200);

	nGeneration = 1;

	nDamage = 40;
   
	AddAsk("憂慮",NPCASK_visible,"秦員外：前些日子我掉了一件非常重要的東西，不曉得大俠您能〔幫助〕我嗎？");
    AddAsk("幫助",0,"秦員外：那東西是一本〔帳簿〕，我深怕這東西落入敵商的手中，洩漏了商機。");
    AddAsk("家丁",0,"");
	AddAsk("帳簿",0,"");
}

CN_ChinYunWai::~CN_ChinYunWai()
{

}
TRetInfo CN_ChinYunWai::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;

    if(szName=="家丁")
	{
		ri.bRet = TRUE;
		if(who->GetGoods("畫像")!=NULL)
		{
			ri.szRet = "秦員外：一切就拜託你了！";
			return ri;
		}
		CGoods * lpPic= GetNormalClass("畫像");
		ri.szRet = who->AddGoods(lpPic);
		if (ri.szRet != "OK") {
			delete lpPic;
			return ri;
		}
		ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"畫像","空",1,"張",0);
		who->SendMsg(ri.szRet);
		ri.szRet = "秦員外：這是他的畫像，但我恐怕他會喬裝成別的樣子，大俠你要多加注意啊！";	
	}
	else if(szName=="帳簿")
	{
		ri.bRet = TRUE;
	    if(who->GetGoods("帳簿") != NULL)
		{
			if(who->GetGoods("畫像")==NULL)
			{
			    ri.szRet = "秦員外：我並沒有委託過你，怎知這是真的還是假的！";
			    return ri;
			}
			ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,"帳簿","空",1,"本",0);			
			who->SendMsg(ri.szRet);
			who->SubGoods("accountbook");
			CDrug * lpDrug= GetDrugClass("小還丹");
		    ri.szRet = who->AddGoods(lpDrug);
			if (ri.szRet != "OK") {
			    delete lpDrug;
			    return ri;
			}
		    ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"小還丹","空",1,"顆",0);
		    who->SendMsg(ri.szRet);
			who->nMoney+=10000;
			who->SendAllInfo();
			ri.szRet ="秦員外：真是太好了！這裡有10000枚銅錢和一顆上好的藥材就送你當做報酬吧！";
		}
		else
		{
			if(who->GetGoods("畫像")!=NULL)
			    ri.szRet = "秦員外：一切就拜託你了！";
			else
				ri.szRet = "秦員外：我懷疑是我府中一個失蹤的〔家丁〕偷走的，麻煩你幫我找到這個人，追回我失去的東西，我會好好報酬你的。";
			return ri;
		}
	}
	ri.bRet = TRUE;
	return ri;
}