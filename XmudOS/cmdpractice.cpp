#include "stdafx.h"
#include "XmudOS.h"
#include "CommandCheck.h"
#include "CmdPlayerLogon.h"
#include "map\MapInfo.h"
#include "npc\Npc.h"

extern rmfullglobals myglobs;

void CCommandCheck::PracticeProc(LPVOID pvPlayer,char *szSkillBook,char *szTimes,char *Result)
{
	CPlayerInfo *lpPlayerInfo;
	CGoods *lpGoods=NULL;
	CBook *lpBook=NULL;
	int nTimes;

/*	sprintf(Result, "%s 此功能尚未開放", SZFAILMSG);
	return;
*/
	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	//POSITION pMapPosite = lpPlayerInfo->pMapPosite;
	EnterCriticalSection(&myglobs.csMaplist);  
	EnterCriticalSection(&myglobs.csPlayerData);

	lpGoods = lpPlayerInfo->GetGoods(szSkillBook);

	nTimes = atoi(szTimes);
	if(nTimes<1)	nTimes = 1;
	if(nTimes>9999)	nTimes = 9999;

	//----------------------------------------------------------------------
	//Pass1:是否有此物品
	if(lpGoods==NULL){
        wsprintf(Result,"%s FAIL 你並沒有這項物品!",SZPRACTICE);
		LeaveCriticalSection(&myglobs.csPlayerData);
		LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}else{
		if(lpGoods->lpGoods->nKinds!=GK_book){
			wsprintf(Result,"%s FAIL 只有書籍類物品才能練習!",SZPRACTICE);
		    LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
	}
	//----------------------------------------------------------------------
	    //Pass2:狀況是否正常
		if(lpPlayerInfo->nStatus != 0)	{

			wsprintf(Result,"%s FAIL 你正忙著呢!",SZPRACTICE);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
		if(lpPlayerInfo->nQianNeng < nTimes)	{//檢查潛能
			wsprintf(Result,"%s FAIL 你的潛能已經發揮到極限了，沒有辦法再成長了.",SZPRACTICE);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
		int nNeedJing = (150/lpPlayerInfo->nInt) * nTimes;
		if(lpPlayerInfo->nEff_jing < nNeedJing)	{//檢查精力
			wsprintf(Result,"%s FAIL 你現在過於疲倦，無法專心練習.",SZPRACTICE);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
    //----------------------------------------------------------------------
	    lpBook = dynamic_cast<CBook *>(lpGoods);
        
		CSkill *lpSkill=NULL;
		TRetInfo ri;

		//Pass3:技能本身的限制
		lpSkill = GetSkillClass(lpBook->lpBook->szSkillEName);
		if(lpSkill==NULL)	{
            wsprintf(Result,"%s FAIL 沒有這種技能!",SZPRACTICE);
		    LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
	    ri = lpSkill->DoPractice(lpPlayerInfo);
		delete lpSkill; 
	    if(ri.bRet == FALSE)	{
		    wsprintf(Result,"%s FAIL %s",SZPRACTICE,ri.szRet);
		    LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}

		//----------------------------------------------------------------------
		//Pass4:此物品的使用限制
        
		TObjectSkill *lpPlayerSkill=NULL;
		TBookNeedSkill *lpBookNeedSkill=NULL;

		if(lpPlayerInfo->nInt<lpBook->lpBook->nNeedInt)	{//需悟性
			wsprintf(Result,"%s FAIL 你的悟性不足以自行練習%s!",SZPRACTICE,lpBook->lpGoods->szCName);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
		
        if(lpPlayerInfo->nStr<lpBook->lpBook->nNeedStr)	{//需臂力
			wsprintf(Result,"%s FAIL 你的臂力不足以自行練習%s!",SZPRACTICE,lpBook->lpGoods->szCName);
			LeaveCriticalSection(&myglobs.csPlayerData);
	        LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
		
        if(lpPlayerInfo->nCon<lpBook->lpBook->nNeedCon)	{//需根骨
			wsprintf(Result,"%s FAIL 你的根骨不足以自行練習%s!",SZPRACTICE,lpBook->lpGoods->szCName);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
		 
		if(lpPlayerInfo->nDex<lpBook->lpBook->nNeedDex)	{//需身法
			wsprintf(Result,"%s FAIL 你的身法不足以自行練習%s!",SZPRACTICE,lpBook->lpGoods->szCName);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
		
		if(lpPlayerInfo->nMax_force<lpBook->lpBook->nNeedForce)	{//需內力
			wsprintf(Result,"%s FAIL 你的內力不足以自行練習%s!",SZPRACTICE,lpBook->lpGoods->szCName);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}		

		//需具備的技能
		POSITION pos = lpBook->lpBook->listNeedSkill.GetHeadPosition();		
		while(pos!=NULL)	{
            lpBookNeedSkill = lpBook->lpBook->listNeedSkill.GetNext(pos);
			if(lpBookNeedSkill!=NULL){
                lpPlayerSkill = lpPlayerInfo->GetTSkill(lpBookNeedSkill->szNeedSkillEName);
				if(lpPlayerSkill == NULL)	{
					lpSkill = GetSkillClass(lpBookNeedSkill->szNeedSkillEName);
					wsprintf(Result,"%s FAIL 你沒有%s的基礎!",SZPRACTICE,lpSkill->szCName);
					delete lpSkill;
					LeaveCriticalSection(&myglobs.csPlayerData);
					LeaveCriticalSection(&myglobs.csMaplist);
			        return;
				}else if(lpPlayerSkill->nLevel<lpBookNeedSkill->nNeedSkillLevel)	{
					wsprintf(Result,"%s FAIL 你的%s火侯不夠!無法自己練習",SZPRACTICE,lpPlayerSkill->lpSkill->szCName);
			        LeaveCriticalSection(&myglobs.csPlayerData);
					LeaveCriticalSection(&myglobs.csMaplist);
					return;
				}
			}
		}

		//是否已經學完
		
		if((lpBook->lpBook->nMaxLevel) <= lpPlayerInfo->GetSkillLevel(lpBook->lpBook->szSkillEName) )//最大等級
		//if( 999 <= lpPlayerInfo->GetSkillLevel(lpBook->lpBook->szSkillEName) )
		{
		    wsprintf(Result,"%s FAIL 你已經練習完%s中的功夫了",SZPRACTICE,lpBook->lpGoods->szCName);
		    LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
		
	    
	    //是否已經會這種技能
	    lpPlayerSkill = lpPlayerInfo->GetTSkill(lpBook->lpBook->szSkillEName);
	    if(lpPlayerSkill == NULL)	{
		    //以前不會,則增加這個功能
			lpPlayerInfo->SetSkill(lpBook->lpBook->szSkillEName, 1, 1, "");
			lpPlayerSkill = lpPlayerInfo->GetTSkill(lpBook->lpBook->szSkillEName);
		}

		//成功練習
	    if(Improve(lpPlayerInfo, lpPlayerSkill, (lpPlayerInfo->nInt/6) * nTimes ))	{
			lpPlayerInfo->nQianNeng -= nTimes;
			lpPlayerInfo->nEff_jing -= nNeedJing;
			wsprintf(Result,"%s OK 你研讀了%s對%s似乎有些領悟. %s,%s,%d %d",
			SZPRACTICE,lpBook->lpGoods->szCName,lpPlayerSkill->lpSkill->szCName,
			lpPlayerSkill->lpSkill->szCName,
			lpPlayerSkill->lpSkill->szEName,
			lpPlayerInfo->nInt/6,
			nTimes);
		}else	{
			wsprintf(Result,"%s FAIL 你的經驗太少，已經不能領悟更深的%s了!",SZPRACTICE,lpPlayerSkill->lpSkill->szCName);
		}
	LeaveCriticalSection(&myglobs.csPlayerData);
	LeaveCriticalSection(&myglobs.csMaplist);
}
