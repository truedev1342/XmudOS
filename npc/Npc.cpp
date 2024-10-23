// Npc.cpp: implementation of the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\npc\Npc.h"
#include "..\map\MapInfo.h"
#include "..\config.h"
// test
#include "..\XmudOS.h"

extern rmfullglobals myglobs;
extern CList <CBaseMap*,CBaseMap*>maplist;

////////////////////////////////////////////////////

CNpc::CNpc()
{
	nDamage = 20;
	nQianNeng = 0;
	bPlayer = FALSE;
	nCon = 20;
	nDex = 20;
	nEff_force = 0;
	nEff_jing = 100;
	nEff_jingli = 100;
	nEff_qi = 100;
	nInt = 20;
	nMax_force = 0;
	nMax_jing = 100;
	nMax_jingli = 100;
	nMax_qi = 100;
	nStr = 20;
	nAsk=0;
	nAttitude = 0;
	// Robin P
	g_HasEvent = 0;
}

CNpc::~CNpc()
{
}


//小販
/*CSellNpc::CSellNpc()
{

}

CSellNpc::~CSellNpc()
{
}
*/
void CNpc::AppToMap(CNpc * lpNpc)
{
	CBaseMap *lpDataMap;
	int i,j;
	char szTest[256];
	if(lpNpc->szRoom == "") {
		sprintf(szTest,"NPC(%s,%s) szRoom is empty",lpNpc->szCName,lpNpc->szEName);
		AddRecordMsg(szTest);
		return;
	}
	// Spock start: 設定NPC初始能力
	lpNpc->nEff_force = lpNpc->nMax_force = lpNpc->GetSkillLevel("BaseForce") * 10;
	lpNpc->nEff_jingli = lpNpc->nMax_jingli = lpNpc->GetSkillLevel("BaseForce") * 3;
	lpNpc->nEff_qi = lpNpc->nMax_qi = lpNpc->GetMaxQi();
	lpNpc->nEff_jing = lpNpc->nMax_jing = lpNpc->GetMaxJing();
	// Spock end
	EnterCriticalSection(&myglobs.csMaplist);
	j = maplist.GetCount();
	for(i=0;i<j;i++)
	{
		lpDataMap = maplist.GetAt(maplist.FindIndex(i));
		if(!strcmp(lpDataMap->szEName,lpNpc->szRoom))
		{
			lpNpc->pMapPosite = maplist.FindIndex(i);
			lpDataMap->listNpc.AddTail(lpNpc);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
	}
	LeaveCriticalSection(&myglobs.csMaplist);
	sprintf(szTest,"NPC(%s,%s) map not found",lpNpc->szCName,lpNpc->szEName);
	AddRecordMsg(szTest);
}


TRetInfo CNpc::DoFight(CActiveObject *who)
{
	TRetInfo ri;
	ri.szRet = "";
	ri.bRet = TRUE;
	return ri;
}
TRetInfo CNpc::DoKill(CActiveObject *who)
{
	TRetInfo ri;
	ri.szRet = "";
	ri.bRet = TRUE;
	return ri;
}
TRetInfo CNpc::DoLook(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;

	ri.bRet = FALSE;
	/* Nuke start for 'Look' */
//	if (!stricmp(szName,"$QUERY$")) {
		ri.bRet = TRUE;
		TRet_return(szLong);
//	}
//	return ri;
}
TRetInfo CNpc::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	CString szTemp;

	ri.bRet = FALSE;
	/* Nuke start for 'Ask' */
	if (!stricmp(szName,"$QUERY$")) { // Ask 無參數為查詢
		ri.bRet = TRUE;
		TRet_return("你想問什麼事？");
	}

	// guanhua 2000/08/21 start
	// 防止玩家使用 "ask _guard" 指令
	// PS. "_guard" 關鍵字對應至防衛地圖時之回答訊息
	if(strcmp(szName, "_guard") == 0)
	{
		TRet_return("你去找別人吧，我不知道。");
	}
	// guanhua 2000/08/21 end
	
	for (int i=0;i<nAsk;i++) 
	{
		if (!strcmp(szName,szAsk[i])) 
		{
			ri.bRet =TRUE;
			if (nAskAttribute[i]&NPCASK_newline) 
			{
				szTemp.Format("%s %s",SZFAILMSG,"　"); //全型空白
				who->SendMsg(szTemp);
			}
			TRet_return(szNpcAsk[i]);
		}
	}

    if (!strcmp(szName,"武功")) 
	{
		ri.bRet =TRUE;
		if(nAttitude & NP_apprentice) 
		{
			if(szFamily!="無門派")
		        ri.szRet = "你想學武功？去問問我師父吧!";
			else
                ri.szRet = "我會不會武功似乎不關閣下的事。";
		}
		else
		{
			TObjectSkill *lpNpcSkill;
			int i;
			CString szTemp="我所修練的功夫有";
			int j = listskill.GetCount();
	        for(i=0;i<j;i++)
			{
		        lpNpcSkill = listskill.GetAt(listskill.FindIndex(i));
		        if(lpNpcSkill->nLevel == 0) continue;
				//if(lpNpcSkill->nType == ST_special || lpNpcSkill->nType == ST_other)
				//{
					szTemp += lpNpcSkill->lpSkill->szCName;
					szTemp += "，";
				//}
			}
            szTemp += "還有其他問題嗎？";
		    ri.szRet.Format("%s：%s",szCName,szTemp);	
		}
		return ri;
	}
	/* Nuke end */
	if( GetTemp("Have/" + szName).nValue < 1 ) {
		TRet_return("你去找別人吧，我不知道。");
	}
	else if ( who->GetGoods((char *)(LPCTSTR)szName) != NULL )
	{
		ri.szRet.Format("%s你現在身上不是有%s嗎，怎麼又來要了？真是貪得無饜！",GetSpecialName(who,1),szName);
		return ri;
	}
	else 
		ri.bRet = TRUE;
	return ri;
}
TRetInfo CNpc::DoAsk(CPlayerInfo *who, CString szName,CString szTarget)
{
	TRetInfo ri;
	CString szTemp;

	ri.bRet = FALSE;

	/* Nuke start for 'Ask' */
	if (!stricmp(szName,"$QUERY$")) { // Ask 無參數為查詢
		ri.bRet = TRUE;
		TRet_return("你想問什麼事？");
	}

	// guanhua 2000/09/25 start
	// 防止玩家詢問第一字元為 "_" 者之關鍵字
	if(!stricmp(szName,"_CannotAsk_"))
	{
		TRet_return("你去找別人吧，我不知道。");
	}
	// guanhua 2000/09/25 end

	for (int i=0;i<nAsk;i++) 
	{
		if (!strcmp(szName,szAsk[i])) 
		{
			ri.bRet =TRUE;
			if (nAskAttribute[i]&NPCASK_newline) 
			{
				szTemp.Format("%s %s",SZFAILMSG,"　"); //全型空白
				who->SendMsg(szTemp);
			}
			TRet_return(szNpcAsk[i]);
		}
	}

    if (!strcmp(szName,"武功")) 
	{
		ri.bRet =TRUE;
		if(nAttitude & NP_apprentice) 
		{	
			if(szFamily!="無門派")
		        ri.szRet = "你想學武功？去問問我師父吧!";
			else
                ri.szRet = "我會不會武功似乎不關閣下的事。";
		}
		else
		{
			TObjectSkill *lpNpcSkill;
			int i;
			CString szTemp="我所修練的功夫有";
			int j = listskill.GetCount();
	        for(i=0;i<j;i++)
			{
		        lpNpcSkill = listskill.GetAt(listskill.FindIndex(i));
		        if(lpNpcSkill->nLevel == 0) continue;
				//if(lpNpcSkill->nType == ST_special || lpNpcSkill->nType == ST_other)
				//{
					szTemp += lpNpcSkill->lpSkill->szCName;
					szTemp += "，";
				//}
			}
            szTemp += "還有其他問題嗎？";
		    ri.szRet.Format("%s：%s",szCName,szTemp);	
		}
		return ri;
	}
	/* Nuke end */
	if( GetTemp("Have/" + szName).nValue < 1 ) {
		TRet_return("你去找別人吧，我不知道。");
	}
	else if ( who->GetGoods((char *)(LPCTSTR)szName) != NULL )
	{
		ri.szRet.Format("%s你現在身上不是有%s嗎，怎麼又來要了？真是貪得無饜！",GetSpecialName(who,1),szName);
		return ri;
	}
	else 
		ri.bRet = TRUE;
	return ri;
}
CString CNpc::DoAskTask(CPlayerInfo *who)
{
	return _T("");
}
TRetInfo CNpc::DoApprentice(CPlayerInfo *who)
{
	TRetInfo ri;
	POSITION pos;

	ri.szRet = "好吧！我就收下你了。";
	ri.bRet = FALSE;
	if(nAttitude & NP_apprentice) {
		ri.szRet = "我是不收徒弟的。";
		return ri;
	}
//	if(strcmp(who->szFamily, szFamily)==0)
//		ri.bRet = TRUE;
	if ((who->szFamily == szFamily) && ( who->nGeneration <= nGeneration ) )
	{
		ri.szRet = GetSpecialName(who,1) + "言重了，在下哪裡敢當！";
		return ri;
	}
/*	if((who->nBetray > 3) && (szFamily != who->szFamily)) {
		ri.szRet = szCName + "神色間似乎對你不是十分信任，也許是想起你從前背叛師門的事情......";
		return ri;
	}
*/
	pos = who->listBetray.GetHeadPosition();
	while (pos) {
		if (szFamily == who->listBetray.GetNext(pos)) {
			ri.szRet = "你這個叛師逆徒，竟然還敢回來！";
			return ri;
		}
	}
	if((szFamily == "少林派") && (who->szSex == "F")) {
		ri.szRet = "阿彌陀佛！女施主呀，貧僧可不敢開這等玩笑啊。";
		return ri;
	}
	if((szFamily == "峨眉派") && (who->szSex == "M")) {
		ri.szRet = "我峨眉派只收女徒，您請回吧。";
		return ri;
	}
	ri.bRet = TRUE;
	return ri;
}

void CNpc::DoEmote(CPlayerInfo *who, CString szEmote)
{
}

void CNpc::Healing()
{
	if(bNoHealing)
		return;

	nEff_jing += nCon / 3 + 5;
	if( nEff_jing >= nMax_jing ) nEff_jing = nMax_jing;
	ReceiveJing();

	nEff_qi += nCon / 3 + nEff_force / 10;
	if( nEff_qi >= nMax_qi ) nEff_qi = nMax_qi;
	ReceiveCure();

	if( nEff_force < nMax_force )
	{
		nEff_force += GetSkillLevel("BaseForce") / 2 + 2 + nMax_force/20;
		if( nEff_force > nMax_force ) nEff_force = nMax_force;
	}
	if( nEff_jingli < nMax_jingli )
	{
		nEff_jingli += GetSkillLevel("BaseForce") / 2 + 2 + nMax_jingli/20;
		if( nEff_jingli > nMax_jingli ) nEff_jingli = nMax_jingli;
	}
}

/*CString CSellNpc::DoBuy(CActiveObject *who, CGoods *lpGoods)
{
	return _T("");
}

CString CSellNpc::DoSell(CActiveObject *who, CGoods *lpGoods)
{
	return _T("");
}
*/
BOOL CNpc::AddAsk(char *key, int attribute,char *data)
{
	// guanhua 2000/09/21 start
	// 將關鍵字第一字元為 "_" 者之屬性設定成隱藏
	char ch = key[0];
	if( ch == '_')
	{
		attribute = 0;
	}
	// guanhua 2000/09/21 end

	if ((nAsk>=0) && (nAsk<MAXASK)) {
		szAsk[nAsk] = CString(key);
		nAskAttribute[nAsk] = attribute;
		szNpcAsk[nAsk] = CString(data);
		nAsk ++;
		return TRUE;
	} else return FALSE;
}

//dainty 觸發給秘笈的事件
TRetInfo CNpc::GivingBook(CPlayerInfo *who,CString szSkillEName)
{
	CString szTemp;
	POSITION pos1,pos2;
	TGivingGoods *lpGivingGoods;
	TGivingCondition *lpGivingCondition;
	CBook *lpBook = NULL;
	CGoods *lpRecGoods = NULL;
	int nFlag=0;
	BOOL bPass = TRUE;
	BOOL bHasGet = FALSE; 
	TRetInfo ri;
	CString szBookName,szUnit;

	ri.bRet = FALSE;
	if(listGiving.GetCount()>0) 
	{
		pos1 = listGiving.GetHeadPosition();
		while(pos1!=NULL)
		{
			bPass = TRUE;
            bHasGet = FALSE; 
			lpGivingGoods = listGiving.GetNext(pos1);
			if(lpGivingGoods!=NULL)  //一本秘笈
			{
				lpBook = GetBookClass(lpGivingGoods->szGoodsEName);
				if(lpBook==NULL) bPass = FALSE;
				//要符合目前學的技能
				else if(lpBook->lpBook->szSkillEName!=szSkillEName)
				{
					delete lpBook; 
					bPass = FALSE;
				}
				pos2 = lpGivingGoods->listCondition.GetHeadPosition();
				while(pos2!=NULL)
				{
                    lpGivingCondition = lpGivingGoods->listCondition.GetNext(pos2);
					if(lpGivingCondition!=NULL)
					{
                        if(who->GetSkillLevel(lpGivingCondition->szSkillEName)< lpGivingCondition->nLevel)   
						{
							bPass = FALSE;
							break;
						}
					}
				}
				
				//-------------------------------------------------------------------
				if(bPass)
				{
					if((lpRecGoods = who->GetGoods("RecBooks"))==NULL)
					{			    
						lpRecGoods = GetNormalClass("RecBooks");
					    if(lpRecGoods!=NULL)   //給認證物
						{
							lpRecGoods->nCount = 0;
							lpRecGoods->nNew = 0;
			                who->AddGoods(lpRecGoods);
						}
						else return ri;																		
					}
					else   //檢查旗標
					{
						//check the marker of book whether it had given
						if(lpGivingGoods->nFlag < 32)
						{
							nFlag = 1 << lpGivingGoods->nFlag;
							if(lpRecGoods->nCount & nFlag)
							{ 
								bHasGet = TRUE;
							}
						}
					    else
						{
						    nFlag = 1 << (lpGivingGoods->nFlag - 32);
						    if(lpRecGoods->nNew & nFlag)
							{
								bHasGet = TRUE;
							}
						}
					}
	                //條件都成立才給予物品
					if(!bHasGet)
					{
		                szBookName = lpBook->lpGoods->szCName;
						szUnit = lpBook->lpGoods->szUnit;
						if(who->AddGoods(lpBook)!="OK") return ri;	
						else
						{
							if(lpGivingGoods->nFlag < 32)
								lpRecGoods->nCount |= 1 << lpGivingGoods->nFlag;
							else
							  lpRecGoods->nNew |= 1 << (lpGivingGoods->nFlag - 32);
	    
							ri.szRet.Format("%s:為師的見徒兒毫不懈怠地修練本派武學,感到欣慰萬分,今日贈予%s,望愛徒能藉此悟出更高深的武學精髓!",szCName,szBookName);
							szTemp.Format("%s %s %s %d %s %d",SZADDGOODS,szBookName,"空",1,szUnit,0);
							who->SendMsg(szTemp);
							ri.bRet = TRUE;
							return ri;	
						}
					}
				}
			}
		}
	}

	
	return ri;
}

// Spock start
void CNpc::FightWin(CPlayerInfo *who)
{
}

void CNpc::KillWin(CPlayerInfo *who)
{
}
// Spock end