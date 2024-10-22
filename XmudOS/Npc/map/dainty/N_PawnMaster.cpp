// N_PawnMaster.cpp: implementation of the CN_PawnMaster class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "N_PawnMaster.h"
#include "..\..\..\config.h"
//#include "..\..\..\hash.h"
//#include "..\..\..\CmdPlayerLogon.h"
//#include "..\..\..\XmudOS.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//extern char g_tszPathName[256];
CN_PawnMaster::CN_PawnMaster()
{
    szCName = "當鋪老闆";
	szEName = "pawnmaster";
	szLong = "這是當鋪老闆，經營當鋪已有幾數年，看起來一副精明的樣子。";
	szSex = "M";
	szXFileName.Format("pmudznnz0%d",random(5) +1);

	nAge =  100;
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
	nCombat_exp =  2000000;

	//和張三豐差不多
	SetSkill("BaseForce",		200);
	SetSkill("BaseDodge",		180);
	SetSkill("BaseUnarmed",		200);
	SetSkill("BaseParry",		180);
	SetSkill("BaseSword",		200);
	SetSkill("BaseBlade",		200);
	SetSkill("Blade_Taiji",		200);
	SetSkill("Unarmed_Taiji",	230);
	SetSkill("Step_Tiyunzhong",	200);
	SetSkill("Force_Taiji",		230);
	SetSkill("Sword_Taiji",		200);
	SetSkill("OtherTaoism",		150);
	SetSkill("OtherLiterate",	130);
	nGeneration = 1;

	nDamage = 40;
   
	AddAsk("查詢典當物品",NPCASK_visible,"");
	AddAsk("典當",NPCASK_visible,"");
	AddAsk("贖回",NPCASK_visible,"");
	AddAsk("賣",NPCASK_visible,"");

	CEquip * lpEquipGoods;
	CWeapon * lpWeaponGoods;
	
	lpEquipGoods = GetEquipClass("oldrobe");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	lpWeaponGoods = GetWeaponClass("changjian");
	lpWeaponGoods->bWield = TRUE;
	listequip.AddTail(lpWeaponGoods);
	lpWeapon = lpWeaponGoods;
}

CN_PawnMaster::~CN_PawnMaster()
{

}

TRetInfo CN_PawnMaster::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;

	ri = CNpc::DoAsk(who, szName);
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;

	if( szName == "查詢典當物品")
	{
		ri.bRet = TRUE;
	    /*listgoods = QueryPawnGoods(who);
		if (listgoods == NULL) {
			ri.szRet = CString(szDiskReadErrMsg);
			return ri;
		}*/
		//檢查流當(2天為限)
		for(int i=0;i<who->listpawngoods.GetCount();i++)
		{
		    if(CheckOverdue(who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nYear,
				who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nMonth,
				who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nDay))
				who->listpawngoods.RemoveAt(who->listpawngoods.FindIndex(i));
		}
		if(who->listpawngoods.GetCount()>0)
		{
			

            ri.szRet = "您曾經典當的物品有：";
		    for(int i=0;i<who->listpawngoods.GetCount();i++)
			{
	            ri.szRet += who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->szCName;
			    ri.szRet += "，";
			}
		    ri.szRet += "還需要什麼服務嗎？";	
		}
		else
            ri.szRet = "您在此無任何抵押物。";
//		RemovePawnGoods(listgoods);
//		listgoods->RemoveAll();
//		delete listgoods;
        return ri;
	}
	else if( szName == "典當")
	{
		ri.bRet = TRUE;
		ri.szRet = "老闆：您要典當什麼？";        
	    return ri;
	}
	else if( szName == "贖回")
	{
		ri.bRet = TRUE;
		ri.szRet = "老闆：您要贖回什麼？";        
	    return ri;
	}
	else if( szName == "賣")
	{
		ri.bRet = TRUE;
		ri.szRet = "老闆：您要賣什麼？";        
	    return ri;
	}
	
	ri.bRet = TRUE;
	return ri;
}

TRetInfo CN_PawnMaster::DoAsk(CPlayerInfo *who, CString szName, CString szTarget)
{
	TRetInfo ri;
//	int nTest;
    BOOL hasGoods = FALSE;
	int nKind;
	int nCost;
	CString szEName;
	CString szUnit;
	CGoods *lpGoods;
    TPawn *lpPawnGoods;

	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
  
	
	if( szName == "查詢典當物品")
	{
		ri.bRet = TRUE;
	    /*listgoods = QueryPawnGoods(who);
		if (listgoods == NULL) {
			ri.szRet = CString(szDiskReadErrMsg);
			return ri;
		}*/
		//檢查流當(2天為限)
		for(int i=0;i<who->listpawngoods.GetCount();i++)
		{
		    if(CheckOverdue(who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nYear,
				who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nMonth,
				who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nDay))
				who->listpawngoods.RemoveAt(who->listpawngoods.FindIndex(i));
		}
		if(who->listpawngoods.GetCount()>0)
		{
            ri.szRet = "您曾經典當的物品有：";
		    for(int i=0;i<who->listpawngoods.GetCount();i++)
			{
	            ri.szRet += who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->szCName;
			    ri.szRet += "，";
			}
		    ri.szRet += "還需要什麼服務嗎？";
			
		}
		else
            ri.szRet = "您在此無任何抵押物。";
//		RemovePawnGoods(listgoods);
//		listgoods->RemoveAll();
//		delete listgoods;
        return ri;
	}
    else if( szName == "贖回")
	{
		ri.bRet = TRUE;
		if(szTarget=="")
		{
			ri.szRet = "老闆：您要贖回什麼？";        
	        return ri;
		}/*	
		listgoods = QueryPawnGoods(who);
		if (listgoods == NULL) {
			ri.szRet = CString(szDiskReadErrMsg);
			return ri;
		}*/
		//檢查流當(2天為限)
		for(int i=0;i<who->listpawngoods.GetCount();i++)
		{
		    if(CheckOverdue(who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nYear,
				who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nMonth,
				who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nDay))
				who->listpawngoods.RemoveAt(who->listpawngoods.FindIndex(i));
		}
		if(who->listpawngoods.GetCount()>0)
		{   
			for(int k=0;k<who->listpawngoods.GetCount();k++)
			{ 
				if(!strcmp(who->listpawngoods.GetAt(who->listpawngoods.FindIndex(k))->szCName,szTarget))
				{
					CGoods *lpGoods;
				
//					hasGoods = TRUE;
					switch(who->listpawngoods.GetAt(who->listpawngoods.FindIndex(k))->nKind)
					{
					case GK_normal:
						lpGoods = GetNormalClass(szTarget);	
						break;
					case GK_weapon:
						lpGoods = GetWeaponClass(szTarget);
					    break;
					case GK_equip:
						lpGoods = GetEquipClass(szTarget);
					    break;
					case GK_drug:
						lpGoods = GetDrugClass(szTarget);
					    break;	
					}
					
			        if(lpGoods!=NULL)
					{
						if(who->nMoney < lpGoods->lpGoods->nCost)
						{
							//RemovePawnGoods(listgoods);
//							listgoods->RemoveAll();	
//			                delete listgoods;
							delete lpGoods;
							ri.szRet= "老闆：你身上的錢不夠。";
							return ri;
						}
						nCost = lpGoods->lpGoods->nCost;
						szUnit = lpGoods->lpGoods->szUnit;
						ri.szRet = who->AddGoods(lpGoods);				
						if(ri.szRet!="OK")
						{
							//RemovePawnGoods(listgoods);
//							listgoods->RemoveAll();	
//			                delete listgoods;
//							delete lpGoods;
							return ri;
						}
						
				        ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,szTarget,"空",1,szUnit,-nCost);
			            who->nMoney -= nCost;
						who->SendMsg(ri.szRet);
						who->listpawngoods.RemoveAt(who->listpawngoods.FindIndex(k));
					    //nTest = RefreshPawnGoods(who,listgoods);
						//if (nTest > 0) {
				        ri.szRet.Format("老闆：這是你的東西，收你%d枚銅錢。",nCost);
						//} else {
						//	ri.szRet = CString(szDiskWriteErrMsg);
						//}
					}
			        else
                        ri.szRet = "老闆：真是抱歉，前些日子遭小偷，這東西大概已經不見了。";	        

					//RemovePawnGoods(listgoods);
					return ri;
				}
			}
//			if(!hasGoods)
//			{
				ri.szRet.Format("老闆：您沒有抵押過%s。",szTarget); 
				//RemovePawnGoods(listgoods);
//				listgoods->RemoveAll();	
//	            delete listgoods;
	            return ri;
//			}
		}
		else
		{
            ri.szRet = "您在此無任何抵押物。";
			//RemovePawnGoods(listgoods);
//			listgoods->RemoveAll();	
//		    delete listgoods;
			return ri;
		}
	}
    else if( szName == "典當")
	{
		ri.bRet = TRUE;
		if(szTarget=="")
		{
			ri.szRet = "老闆：您要典當什麼？";        
	        return ri;
		}
		//檢查流當(2天為限)
		for(int i=0;i<who->listpawngoods.GetCount();i++)
		{
		    if(CheckOverdue(who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nYear,
				who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nMonth,
				who->listpawngoods.GetAt(who->listpawngoods.FindIndex(i))->nDay))
				who->listpawngoods.RemoveAt(who->listpawngoods.FindIndex(i));
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
			case GK_normal:
			case GK_drug:
			case GK_weapon:
			case GK_equip:
				
				if(nCost<100)
                    ri.szRet = "老闆：這是便宜貨嘛！我是不收的。";
				else
				{
					//listgoods = QueryPawnGoods(who);
					//if (listgoods == NULL) {
					//	ri.szRet = CString(szDiskReadErrMsg);
					//	return ri;
					//}
					if (who->listpawngoods.GetCount() >= 10) {
						ri.szRet = "老闆：你已經當太多東西了，不收！不收！";
						return ri;
					}
					lpPawnGoods = new TPawn;
                    CTime t = CTime::GetCurrentTime();
					
					lpPawnGoods->szCName = szTarget;
					lpPawnGoods->szEName = szEName;
					lpPawnGoods->nYear = t.GetYear();
					lpPawnGoods->nMonth = t.GetMonth();
					lpPawnGoods->nDay = t.GetDay();
					lpPawnGoods->nKind = nKind;
					who->listpawngoods.AddTail(lpPawnGoods);
					//nTest = RefreshPawnGoods(who,listgoods);
					//RemovePawnGoods(listgoods);
//					listgoods->RemoveAll();
//					delete listgoods;	
//					if (nTest > 0) {
						nCost = (int)(nCost*0.8);
				        who->SubGoods(szEName);
					    who->nMoney+=nCost;
				        ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,szTarget,"空",1,szUnit,nCost);			
				        who->SendMsg(ri.szRet);
					
						if(nCost>1000)
							ri.szRet.Format("老闆：唷！這可是個好東西呢！算你%d枚銅錢好了。",nCost);
						else if(nCost>500)
							ri.szRet.Format("老闆：這貨看起來還不錯！算你%d枚銅錢好了。",nCost);
						else
							ri.szRet.Format("老闆：這東西看起來不怎麼值錢，算你%d枚銅錢好了。",nCost);
					
				//} else {
				//		ri.szRet = CString(szDiskWriteErrMsg);
				//	}
				}
				break;
			case GK_food:
			case GK_jiudai:
			case GK_book:
				ri.szRet = "老闆：我是不收這個的。";
				break;
			}
		}
		else
			ri.szRet.Format("老闆：你身上沒有%s。",szTarget);        
	  
		return ri;
	}
	else if( szName == "賣")
	{
		ri.bRet = TRUE;
		if(szTarget=="")
		{
			ri.szRet = "老闆：您要賣什麼？";        
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
				ri.szRet = "老闆：沒有人會收這個的！";
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
			case GK_normal:
			case GK_drug:
			case GK_weapon:
			case GK_equip:
				
				
				if(nCost<100)
                    ri.szRet = "老闆：這是便宜貨嘛！我是不收的。";
				else
				{
					nCost = (int)(nCost*0.8);
			        ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,szTarget,"空",1,szUnit,nCost);			
			        who->SendMsg(ri.szRet);
			        who->SubGoods(szEName);
			        who->nMoney+=nCost;
					if(nCost>1000)
					    ri.szRet.Format("老闆：唷！這可是個好東西呢！算你%d枚銅錢好了。",nCost);
					else if(nCost>500)
						ri.szRet.Format("老闆：這貨看起來還不錯！算你%d枚銅錢好了。",nCost);
					else
						ri.szRet.Format("老闆：這東西看起來不怎麼值錢，算你%d枚銅錢好了。",nCost);
				}
				break;
			case GK_food:
			case GK_jiudai:
			case GK_book:
				ri.szRet = "老闆：我是不收這個的。";
				break;
			}
		}
		else
		{
			ri.szRet.Format("老闆：你身上沒有%s。",szTarget);       
	        return ri;
		}
	}	

	ri.bRet = TRUE;
	return ri;
}

BOOL CheckOverdue(int year,int month,int day)
{
	CTime t = CTime::GetCurrentTime();

	if(year<t.GetYear()) return TRUE;
	else if(month<t.GetMonth()) return TRUE;
	else if(day<t.GetDay()-2) return TRUE;
    else return FALSE;
}
