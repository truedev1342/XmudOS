// N_Runner.cpp: implementation of the CN_Runner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "N_Runner.h"
#include "..\..\..\config.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
typedef struct tagIdentity{
	CString szCName;
	CString szLong;
	CString szXFileName;
	CString szRoom;
}TIdentity;
/*TIdentity Id[10] = {
	{"cd_path03"},
	{"ca_dyta"},
	{"jz_path07"},
	{"vl_minf"},
	{"ly_dpu"},
	{"xy_path05"},
	{"em_mla"},
	{"cd_path08"},
	{"ym_silk"},
	{"yz_zhd"}};*/
CN_Runner::CN_Runner()
{

    szCName = "遊客";
	szLong = "這是路過的遊客。";
	//szRoom = szLocation[random(10)];
	
	szXFileName.Format("pmudznnz0%d",random(5)+1);   
	szEName= "runner";
	szSex = "M";
	nAge =  25;

	nAttitude = NP_friendly | NP_apprentice;
	nCombat_exp =  4000;
     
	SetSkill("BaseUnarmed",	25);
	SetSkill("BaseDodge",	25);
	SetSkill("BaseParry",	25);
	SetSkill("BaseBlade",	25);
	SetSkill("BaseForce",	25);

	nShen = -200;
	

	CEquip *lpEquipGoods;
	CWeapon *lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("graycloth");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("duanjian");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);
	lpWeapon = lpWeaponGoods;
	AddAsk("帳簿",0,"");
}

CN_Runner::~CN_Runner()
{

}
TRetInfo CN_Runner::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	if(szName=="帳簿")
	{
		if(who->GetGoods("畫像")!=NULL)
		{
			ri.bRet = TRUE;
			if(who->szPerson == szEName)
			{
				CGoods * lpAccountBook= GetNormalClass("accountbook");
		        ri.szRet = who->AddGoods(lpAccountBook);
		        if (ri.szRet != "OK") {
			    delete lpAccountBook;
			    return ri;
				}
		        ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"帳簿","空",1,"本",0);
		        who->SendMsg(ri.szRet);
				ri.szRet = "逃亡的家丁：大俠請手下留情！我交出東西就是了。";
			    who->SendMsg(ri.szRet);
				ri.szRet.Format("%s %s %s得到一本帳簿。",SZOKMSG,szYellowHigt,who->szCName);
				who->SendMsg(ri.szRet);
				//TO DO:切換地圖
				return ri;
			}
			ri.szRet = "逃亡的家丁：既然你苦苦逼問，就別怪我不客氣了！";
			who->SendMsg(ri.szRet);
			//進入打鬥程序
			//to do:
			return ri;
		}
	}
	return ri;
}
