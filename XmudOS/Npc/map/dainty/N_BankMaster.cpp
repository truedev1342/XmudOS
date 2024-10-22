// N_BankMaster.cpp: implementation of the CN_BankMaster class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "N_BankMaster.h"
#include "..\..\..\config.h"
//#include "..\..\..\common.h"
extern rmfullglobals myglobs;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern char g_tszPathName[256];
CN_BankMaster::CN_BankMaster()
{
    szCName = "錢莊老闆";
	szEName = "bankmaster";
	szNickName = "小氣先生";
	szLong = "這是錢莊老闆，經營錢莊已有幾數年，看起來一副精明的樣子。";
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
   
	AddAsk("查詢存款",NPCASK_visible,"");
	AddAsk("提領",NPCASK_visible,"");
	AddAsk("存入",NPCASK_visible,"");
	
	AddAsk("寄物",NPCASK_visible,"");
	AddAsk("取物",NPCASK_visible,"");
	AddAsk("查看寄放物",NPCASK_visible,"");
	
	AddAsk("提領1000",NPCASK_visible,"");
	AddAsk("提領10000",NPCASK_visible,"");
	AddAsk("存入1000",NPCASK_visible,"");
	AddAsk("存入10000",NPCASK_visible,"");

}

CN_BankMaster::~CN_BankMaster()
{

}
TRetInfo CN_BankMaster::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;

	int nInputMoney = 0;
	if( szName == "查詢存款")
	{
		if(who->nBankMoney<=0)
		{
			ri.szRet = "老闆：不好意思，您在此沒有存款！";
		}
		else
		{
			ri.szRet.Format("老闆笑容滿面地說：您的存款有%d枚銅錢。",who->nBankMoney);
		}
	}
	else if( szName == "提領")
	{
		ri.bRet = TRUE;
		ri.szRet = "請在「提領」的後面輸入金額";
	    return ri;
	}
    else if( szName == "存入")
	{
		ri.bRet = TRUE;
		ri.szRet = "請在「存入」的後面輸入金額";
	    return ri;	
	}
    else if( szName == "寄物")
	{
		ri.bRet = TRUE;
		ri.szRet = "請在「寄物」的後面輸入物品名，每寄放一件物品要5枚銅錢";
	    return ri;	
	}
    else if( szName == "取物")
	{
		ri.bRet = TRUE;
		ri.szRet = "請在「取物」的後面輸入物品名";
	    return ri;	
	}
	else if( szName == "查看寄放物")
	{
		CString tmpMsg;
		CString tmpMsg2;
		CGoods *lpEquip;
		char szTemp[256];
		
		tmpMsg = ("老闆：您目前寄放的物品有....");
		
		EnterCriticalSection(&myglobs.csPlayerData); 
		int j = who->listrentequip.GetCount();
		for(int i=0;i<j;i++)
		{
			lpEquip = who->listrentequip.GetAt(who->listrentequip.FindIndex(i));
			//itoa(lpEquip->nCount,nCount);
			if(lpEquip != NULL)
			{
				tmpMsg2.Format("%s[%d%s]，",lpEquip->lpGoods->szCName,lpEquip->nCount,lpEquip->lpGoods->szUnit);
				tmpMsg += tmpMsg2;
			}
		}
		tmpMsg += ("您也可以隨時用Rent指令查看寄物列表.");
		LeaveCriticalSection(&myglobs.csPlayerData);

		sprintf(szTemp, "(%s,%s) %s 查詢寄物", who->szEName, who->szUserName, who->szCName);
		AddRecordMsg(szTemp);
		//who->SendMsg(tmpMsg);
		ri.szRet = tmpMsg;
		return ri;

	}
	else if( szName == "提領1000")
	{
		ri.bRet = TRUE;
		
		nInputMoney = 1000;
		if(who->nBankMoney==0)
		{
			ri.szRet = "老闆一臉不高興地說：您在此沒有存款！";
		}
		else if(who->nBankMoney<nInputMoney)    //
		{
			ri.szRet = "老闆一臉不高興地說：您的存款沒那麼多！";
		}
		else if(who->nMoney+nInputMoney > MAXMONEY)
		{
			ri.szRet = "你無法帶那麼多錢";
		}
		else
		{
  		    who->nMoney+=nInputMoney;
			who->nBankMoney-=nInputMoney;
		    who->SendAllInfo();
		    ri.szRet = "老闆：這是您的錢，謝謝光臨！";
		}
	}
	else if( szName == "提領10000")
	{
		ri.bRet = TRUE;
		
		nInputMoney = 10000;
		if(who->nBankMoney==0)
		{
			ri.szRet = "老闆一臉不高興地說：您在此沒有存款！";
		}
		else if(who->nBankMoney<nInputMoney)    //
		{
			ri.szRet = "老闆一臉不高興地說：您的存款沒那麼多！";
		}
		else if(who->nMoney+nInputMoney > MAXMONEY)
		{
			ri.szRet = "你無法帶那麼多錢";
		}
		else
		{
  		    who->nMoney+=nInputMoney;
			who->nBankMoney-=nInputMoney;
		    who->SendAllInfo();
		    ri.szRet = "老闆：這是您的錢，謝謝光臨！";
		}
	}
	else if( szName == "存入1000")
	{
		ri.bRet = TRUE;
		nInputMoney = 1000;
		
		if(who->nMoney < nInputMoney)
		{
			ri.szRet = "老闆：對不起，您手上的錢沒那麼多！";
		}
		else if(who->nBankMoney+nInputMoney > MAXMONEY)
		{
			ri.szRet = "老闆：您的存款已經太多了，無法存那麼多錢";
		}
		else
		{
		    who->nMoney -= nInputMoney;
			who->nBankMoney += nInputMoney;
		    who->SendAllInfo();
		    ri.szRet.Format("老闆：您存入了%d枚銅錢。",nInputMoney); 
		}
	}
	else if( szName == "存入10000")
	{
		ri.bRet = TRUE;
		nInputMoney = 10000;
		
		if(who->nMoney < nInputMoney)
		{
			ri.szRet = "老闆：對不起，您手上的錢沒那麼多！";
		}
		else if(who->nBankMoney+nInputMoney > MAXMONEY)
		{
			ri.szRet = "老闆：您的存款已經太多了，無法存那麼多錢";
		}
		else
		{
		    who->nMoney -= nInputMoney;
			who->nBankMoney += nInputMoney;
		    who->SendAllInfo();
		    ri.szRet.Format("老闆：您存入了%d枚銅錢。",nInputMoney);
		}
	}
	ri.bRet = TRUE;
	return ri;
}

TRetInfo CN_BankMaster::DoAsk(CPlayerInfo *who, CString szName, CString szTarget)
{
	char szTemp[256];
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;

	int nInputMoney = 0;

	if( szName == "查詢存款")
	{
		if(who->nBankMoney<=0)
		{
			ri.szRet = "老闆：不好意思，您在此沒有存款！";
		}
		else
		{
			ri.szRet.Format("老闆笑容滿面地說：您的存款有%d枚銅錢。",who->nBankMoney);
		}
	}
    else if( szName == "提領")
	{
		ri.bRet = TRUE;
		if(szTarget=="")
		{
			ri.szRet = "老闆：您要提出多少錢？";        
	        return ri;
		}
		nInputMoney = atoi(szTarget);
		if(nInputMoney>0)
		{
		    if(who->nBankMoney==0)
			{
			    ri.szRet = "老闆一臉不高興地說：您在此沒有存款！";
			}
			else if(who->nBankMoney<nInputMoney)
			{
				ri.szRet = "老闆一臉不高興地說：您的存款沒那麼多！";
			}
			else if(who->nMoney+nInputMoney > MAXMONEY)
			{
				ri.szRet = "你無法帶那麼多錢";
			}
			else
			{
  		        who->nMoney+=nInputMoney;
			    who->nBankMoney-=nInputMoney;
		        who->SendAllInfo();
		        ri.szRet = "老闆：這是您的錢，謝謝光臨！";
			}
		}
		else
		{
			ri.szRet = "老闆：您要提出多少錢？";
		}
	}

    else if( szName == "存入")
	{
		ri.bRet = TRUE;
		if(szTarget=="")
		{
			ri.szRet = "老闆：您要存入多少錢？";
	        return ri;
		}
		nInputMoney = atoi(szTarget);
		if(nInputMoney>0)
		{
			if(who->nMoney < nInputMoney)
			{
				ri.szRet = "老闆：對不起，您手上的錢沒那麼多！";
			}
			else if(who->nBankMoney+nInputMoney > MAXMONEY)
			{
				ri.szRet = "老闆：您的存款已經太多了，無法存那麼多錢";
			}
			else
			{
				who->nMoney -= nInputMoney;
				who->nBankMoney += nInputMoney;
				who->SendAllInfo();
				ri.szRet.Format("老闆：您存入了%d枚銅錢。",nInputMoney);
			}
		}
		else
		{
			ri.szRet = "老闆：您要存入多少錢？";
		}
	}
	
	else if( szName == "寄物")
	{
		POSITION pos, pos2, pos3, pos4;
		CGoods *lpEquip, *lpMyEquip, *lpMyEquip2, *lpDelEquip;
		CGoods *lpRentEquip;
		int bFind = 0, bRented = 0, nWeight = 0;
		
		/*
		if(szTarget=="")
		{
			ri.szRet = "老闆：您要寄放什麼？";
	        return ri;
		}
		*/

		EnterCriticalSection(&myglobs.csPlayerData);

		//尋找有無該物
		pos = who->listequip.GetHeadPosition();
		while(pos != NULL)
		{
			pos2 = pos;
			lpEquip = who->listequip.GetNext(pos);
			if((lpEquip->lpGoods->szCName == szTarget)||(lpEquip->lpGoods->szEName == szTarget))
			{
				if((lpEquip->lpGoods->nKinds == GK_food)||(lpEquip->lpGoods->nKinds == GK_jiudai))
				{
					ri.szRet = "老闆：食物及飲水不能寄放.";
					LeaveCriticalSection(&myglobs.csPlayerData);
					AddRecordMsg("寄物失敗:食物");
					return ri;
				}

				if(lpEquip->lpGoods->nKinds == GK_equip)
				{
					if(dynamic_cast<CEquip *>(lpEquip)->nWearWhere!=0)
					{
						ri.szRet = "老闆：先將這個裝備卸下來吧.";
						LeaveCriticalSection(&myglobs.csPlayerData);
						AddRecordMsg("寄物失敗:未卸下");
						return ri;
					}
				}
				if(lpEquip->lpGoods->nKinds == GK_weapon)
				{
					if(dynamic_cast<CWeapon *>(lpEquip)->bWield)
					{
						ri.szRet = "老闆：先將這個武器放下來吧.";
						LeaveCriticalSection(&myglobs.csPlayerData);
						AddRecordMsg("寄物失敗:未卸下");
						return ri;
					}
				}
				
				//重量檢查
				
				nWeight = 0;
				pos4 = who->listrentequip.GetHeadPosition();
				while (pos4!=NULL)
				{
					lpMyEquip2 = listrentequip.GetNext(pos4);
					nWeight += lpMyEquip2->lpGoods->nWeight * lpMyEquip2->nCount;
				}
				if (nWeight + lpEquip->lpGoods->nWeight > 200000)
				{
					ri.szRet.Format("可寄放重量%d，目前寄放重量%d，%s重量%d，超過重量限制",
								200000, nWeight,lpEquip->lpGoods->szCName, lpEquip->lpGoods->nWeight);
					LeaveCriticalSection(&myglobs.csPlayerData);
					AddRecordMsg("寄物失敗:過重");
					return ri;
				}
				
				if(who->nMoney < 5)
				{
					ri.szRet = "老闆：寄放一件物品要5枚銅錢！你的錢不夠.";
					LeaveCriticalSection(&myglobs.csPlayerData);
					AddRecordMsg("寄物失敗:錢不足");
					return ri;
				}
				else
				{
					ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"temp","空",0,0,-5);
					who->SendMsg(ri.szRet);
					who->nMoney -= 5;
				}

				//lpRentEquip = new CGoods;
				//加入寄物list
				
				pos3 = who->listrentequip.GetHeadPosition();
				while(pos3 != NULL)
				{
					lpMyEquip = who->listrentequip.GetNext(pos3);
					if(lpMyEquip->lpGoods->szCName == lpEquip->lpGoods->szCName)
					{
						lpMyEquip->nCount ++;
						bRented = 1;
						bFind = 1;
						break;
					}
				}
				
				if(!bFind && !bRented)
				{
					
					if(lpEquip->lpGoods->nKinds==GK_equip)
						//lpRentEquip = new CEquip;
						lpRentEquip = GetEquipClass(lpEquip->lpGoods->szCName);
					else if(lpEquip->lpGoods->nKinds==GK_weapon)
						//lpRentEquip = new CWeapon;
						lpRentEquip = GetWeaponClass(lpEquip->lpGoods->szCName);
					else if(lpEquip->lpGoods->nKinds==GK_book)
						//lpRentEquip = new CBook;
						lpRentEquip = GetBookClass(lpEquip->lpGoods->szCName);
					else if(lpEquip->lpGoods->nKinds==GK_drug)
						//lpRentEquip = new CDrug;
						lpRentEquip = GetDrugClass(lpEquip->lpGoods->szCName);
					else if(lpEquip->lpGoods->nKinds==GK_normal)
						//lpRentEquip = new CGoods;
						lpRentEquip = GetNormalClass(lpEquip->lpGoods->szCName);
					else
					{
						ri.szRet = "老闆：這種物品不能寄放";
						LeaveCriticalSection(&myglobs.csPlayerData);
						AddRecordMsg("寄物失敗:種類錯誤");
						return ri;
					}

					//*lpRentEquip = *lpEquip;
					lpRentEquip->nCount = 1;
					lpRentEquip->nRent = 1;
					bFind = 1;
					bRented = 1;
					//who->AddRentGoods(lpEquip);
					who->listrentequip.AddTail(lpRentEquip);
				}
				
				if(bRented)
				{
					ri.szRet.Format("%s %s %s %d %s %d",SZADDRENTGOODS,lpEquip->lpGoods->szCName,"空",1,lpEquip->lpGoods->szUnit,0);
					who->SendMsg(ri.szRet);
					ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,lpEquip->lpGoods->szCName,"空",1,lpEquip->lpGoods->szUnit,0);
					who->SendMsg(ri.szRet);

					if(lpEquip->nCount <= 1)
					{
						//who->listequip.RemoveAt(pos2);
						//delete lpEquip;
						lpDelEquip = who->listequip.GetAt(pos2);
						who->listequip.RemoveAt(pos2);
						delete lpDelEquip;

					}
					else
						lpEquip->nCount --;
					
					ri.szRet = "老闆：謝謝光臨！";
					break;
				}	

			}
		}

		LeaveCriticalSection(&myglobs.csPlayerData);

		//ri.szRet.Format("%s",SZRENTLIST);
		//who->SendMsg(ri.szRet);

		sprintf(szTemp, "(%s,%s) %s 寄物:%s", who->szEName, who->szUserName, who->szCName, szTarget);
		AddRecordMsg(szTemp);

		if(!bFind)
		{
			ri.szRet = "老闆：您沒有這樣東西呀？";
			AddRecordMsg("寄物失敗:無此物");
	        return ri;
		}

	}
	
	else if( szName == "取物")
	{
		POSITION pos, pos2, pos3, pos4;
		CGoods *lpEquip, *lpMyEquip, *lpRentEquip, *lpMyEquip2, *lpDelEquip;
		//CGoods *pGood = NULL;
		int bFind = 0, bRented = 0, nWeight = 0;
		
		/*
		if(szTarget=="")
		{
			ri.szRet = "老闆：您要取回什麼？";
	        return ri;
		}
		*/
	
		EnterCriticalSection(&myglobs.csPlayerData);

		//尋找有無該物
		pos = who->listrentequip.GetHeadPosition();
		while(pos != NULL)
		{
			pos2 = pos;
			lpEquip = who->listrentequip.GetNext(pos);
			if((lpEquip->lpGoods->szCName == szTarget)||(lpEquip->lpGoods->szEName == szTarget))
			{
				//重量檢查
				nWeight = 0;
				pos4 = who->listequip.GetHeadPosition();
				while (pos4!=NULL)	{
					lpMyEquip2 = listequip.GetNext(pos4);
					if( lpMyEquip2->nCount < 0 ) lpMyEquip2->nCount = 1;
					nWeight += lpMyEquip2->lpGoods->nWeight * lpMyEquip2->nCount;
				}

				if( nWeight < 0 || nWeight > who->nStr*1000 ||
					((nWeight + lpEquip->lpGoods->nWeight) > who->nStr*1000 )	)	{

					ri.szRet.Format("%s可攜帶重量%d，目前攜帶重量%d，%s重量%d，超過負重限制",
								who->szCName, who->nStr*1000, nWeight,
								lpEquip->lpGoods->szCName, lpEquip->lpGoods->nWeight);
					LeaveCriticalSection(&myglobs.csPlayerData);
					AddRecordMsg("取物失敗:過重");
					return ri;
				}

				//加入身上list
				pos3 = who->listequip.GetHeadPosition();
				while(pos3 != NULL)
				{
					lpMyEquip = who->listequip.GetNext(pos3);
					if(lpMyEquip->lpGoods->szCName == lpEquip->lpGoods->szCName)
					{
						lpMyEquip->nCount ++;
						bRented = 1;
						bFind = 1;
						break;
					}
				}
				if(!bFind && !bRented)
				{
					if(lpEquip->lpGoods->nKinds==GK_equip)
						//lpRentEquip = new CEquip;
						lpRentEquip = GetEquipClass(lpEquip->lpGoods->szCName);
					else if(lpEquip->lpGoods->nKinds==GK_weapon)
						//lpRentEquip = new CWeapon;
						lpRentEquip = GetWeaponClass(lpEquip->lpGoods->szCName);
					else if(lpEquip->lpGoods->nKinds==GK_book)
						//lpRentEquip = new CBook;
						lpRentEquip = GetBookClass(lpEquip->lpGoods->szCName);
					else if(lpEquip->lpGoods->nKinds==GK_drug)
						//lpRentEquip = new CDrug;
						lpRentEquip = GetDrugClass(lpEquip->lpGoods->szCName);
					else if(lpEquip->lpGoods->nKinds==GK_normal)
						//lpRentEquip = new CGoods;
						lpRentEquip = GetNormalClass(lpEquip->lpGoods->szCName);
					else
						//lpRentEquip = GetGoodsClass(lpEquip->lpGoods->szCName);
					{
						ri.szRet = "老闆：這種物品無法取回";
						LeaveCriticalSection(&myglobs.csPlayerData);
						AddRecordMsg("取物失敗:種類錯誤");
						return ri;
					}

					//*lpRentEquip = *lpEquip;
					lpRentEquip->nCount = 1;
					lpRentEquip->nRent = 0;
					bFind = 1;
					bRented = 1;

					who->listequip.AddTail(lpRentEquip);

				}
				if(bRented)
				{
					ri.szRet.Format("%s %s %s %d %s %d",SZSUBRENTGOODS,lpEquip->lpGoods->szCName,"空",1,lpEquip->lpGoods->szUnit,0);
					who->SendMsg(ri.szRet);
					ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,lpEquip->lpGoods->szCName,"空",1,lpEquip->lpGoods->szUnit,0);
					who->SendMsg(ri.szRet);

					if(lpEquip->nCount <= 1)
					{
						lpDelEquip = who->listrentequip.GetAt(pos2);
						who->listrentequip.RemoveAt(pos2);
						delete lpDelEquip;
					}
					else
						lpEquip->nCount --;

					ri.szRet = "老闆：這是您的東西,謝謝光臨！";
					break;
				}

			}
		}

		LeaveCriticalSection(&myglobs.csPlayerData);

		//ri.szRet.Format("%s",SZRENTLIST);
		//who->SendMsg(ri.szRet);

		sprintf(szTemp, "(%s,%s) %s 取物:%s", who->szEName, who->szUserName, who->szCName, szTarget);
		AddRecordMsg(szTemp);

		if(!bFind)
		{
			ri.szRet = "老闆：您沒有寄放這樣東西呀？";
			AddRecordMsg("取物失敗:無此物");
	        return ri;
		}
	}
	else if( szName == "查看寄放物")
	{
		
		/*
		CString tmpMsg;
		CString tmpMsg2;
		CGoods *lpEquip;
		
		tmpMsg = ("老闆：您目前寄放的物品有....");
		
		EnterCriticalSection(&myglobs.csPlayerData); 
		int j = who->listrentequip.GetCount();
		for(int i=0;i<j;i++)
		{
			lpEquip = who->listrentequip.GetAt(who->listrentequip.FindIndex(i));
			//itoa(lpEquip->nCount,nCount);
			if(lpEquip != NULL)
			{
				tmpMsg2.Format("%s[%d%s].",lpEquip->lpGoods->szCName,lpEquip->nCount,lpEquip->lpGoods->szUnit);
				tmpMsg += tmpMsg2;
			}
		}
		LeaveCriticalSection(&myglobs.csPlayerData);

		sprintf(szTemp, "(%s,%s) %s 查詢寄物", who->szEName, who->szUserName, who->szCName);
		AddRecordMsg(szTemp);

		tmpMsg += (",每寄放一件要10枚銅錢,您也可以隨時用Rent指令查看寄物列表.");
		//who->SendMsg(tmpMsg);
		ri.szRet = tmpMsg;
		return ri;
		*/
	}

	ri.bRet = TRUE;
	return ri;
}
