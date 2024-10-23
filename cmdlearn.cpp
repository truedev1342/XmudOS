#include "stdafx.h"
#include "XmudOS.h"
#include "CommandCheck.h"
#include "CmdPlayerLogon.h"
#include "map\MapInfo.h"
#include "npc\Npc.h"
#include "skill\skill\Skill.h"

extern rmfullglobals myglobs;

/*
void CCommandCheck::LearenProc(LPVOID pvPlayer,char *szWho,char *szWhichSkill,char *Result)
{
	CPlayerInfo *lpPlayerInfo;
	CNpc * lpNpc;
	CBaseMap * lpDataMap;
	BOOL bFindOppNPC = FALSE;
	int i;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	POSITION pMapPosite = lpPlayerInfo->pMapPosite;
    
	EnterCriticalSection(&myglobs.csMaplist);
	EnterCriticalSection(&myglobs.csPlayerData);

	if(lpPlayerInfo->nStatus != 0)
	{
		wsprintf(Result,"%s FAIL 你正忙著呢!",SZLEARNSKILL);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}
	//檢查潛能
	if(lpPlayerInfo->nQianNeng < 1)
	{
		wsprintf(Result,"%s FAIL 你的潛能不夠!",SZLEARNSKILL);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}
	int nNeedJing = 150/lpPlayerInfo->nInt;

	if(lpPlayerInfo->nEff_jing <= nNeedJing)
	{
		wsprintf(Result,"%s FAIL 你的精力不夠!",SZLEARNSKILL);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}


	

	lpDataMap = maplist.GetAt(lpPlayerInfo->pMapPosite);
	for(i=0;i<lpDataMap->listNpc.GetCount();i++)
	{
		lpNpc = lpDataMap->listNpc.GetAt(lpDataMap->listNpc.FindIndex(i));
		if(!stricmp(lpNpc->szEName,szWho) || !strcmp(lpNpc->szCName,szWho))
		{
			if(lpNpc->nStatus != 0)
			{
				wsprintf(Result,"%s FAIL %s正忙著呢!",SZLEARNSKILL,lpNpc->szCName);				
	            LeaveCriticalSection(&myglobs.csPlayerData);
	            LeaveCriticalSection(&myglobs.csMaplist);
				return;
			}
			bFindOppNPC = TRUE;
			break;
		}
	}

	if(!bFindOppNPC)
	{
		wsprintf(Result,"%s FAIL 此人並不在地圖裡面",SZLEARNSKILL);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}

	if(lpNpc->szEName != lpPlayerInfo->szTeacher)
	{
		//處理不是師傅類型學習的指令
		wsprintf(Result,"%s FAIL %s說:\"學習%s這個還是找你的師傅吧!\"",SZLEARNSKILL,lpNpc->szCName,szWhichSkill);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}
	//檢查此NPC是否會這種技能
	TObjectSkill *lpNpcSkill,*lpPlayerSkill;
	lpNpcSkill = lpNpc->GetTSkill(szWhichSkill);
	if(lpNpcSkill == NULL)
	{
		wsprintf(Result,"%s FAIL %s說:\"學習%s這個還是另請高明吧!\"",SZLEARNSKILL,lpNpc->szCName,szWhichSkill);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}
	if(lpNpcSkill->nLevel < lpPlayerInfo->GetSkillLevel(szWhichSkill) )
	{
		wsprintf(Result,"%s FAIL 你的%s這個技能已經不低與%s了",SZLEARNSKILL,szWhichSkill,lpNpc->szCName);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}

	TRetInfo ri;	
	ri = lpNpcSkill->lpSkill->DoLearn(lpPlayerInfo);
	if(ri.bRet == FALSE)
	{
		wsprintf(Result,"%s FAIL %s",SZLEARNSKILL,ri.szRet);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}

	//是否已經會這種技能
	lpPlayerSkill = lpPlayerInfo->GetTSkill(szWhichSkill);
	if(lpPlayerSkill == NULL)
	{
		//以前不會,則增加這個功能
		// Spock start
		lpPlayerInfo->SetSkill(lpNpcSkill->lpSkill->szEName, 0, 0, "");
		lpPlayerSkill = lpPlayerInfo->GetTSkill(szWhichSkill);
		// Spock end
		// Spock deleted
/*		lpPlayerSkill = GetTSkill(lpNpcSkill->lpSkill->szEName,
								lpNpcSkill->lpSkill->nType,
								lpNpcSkill->lpSkill->nCanMap);
		lpPlayerInfo->listskill.AddTail(lpPlayerSkill);
*/
/*
	}
	TRetInfo ret;
	//the event of GivingGoods
	ret = lpNpc->GivingBook(lpPlayerInfo,lpPlayerSkill->lpSkill->szEName);
	if(ret.bRet)
	{
		wsprintf(Result,"%s %s",SZOKMSG,ret.szRet);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}
	if(Improve(lpPlayerInfo, lpPlayerSkill, lpPlayerInfo->nInt/5+1))
	{
		lpPlayerInfo->nQianNeng --;
		lpPlayerInfo->nEff_jing -= nNeedJing;
		wsprintf(Result,"%s OK 你聽了師傅的教誨對%s似乎有些領悟. %s,%s,%d",
			SZLEARNSKILL,lpPlayerSkill->lpSkill->szCName,
			lpPlayerSkill->lpSkill->szCName,
			lpPlayerSkill->lpSkill->szEName,
			lpPlayerInfo->nInt/5+1);
	}
	else
	{
		wsprintf(Result,"%s FAIL %s說:\"你的經驗太少，已經不能領悟更深的%s了!\"",SZLEARNSKILL,lpNpc->szCName,szWhichSkill);
	}
	LeaveCriticalSection(&myglobs.csPlayerData);
	LeaveCriticalSection(&myglobs.csMaplist);
}
*/







// Robin P
// New Learn Proc
void CCommandCheck::LearenProc(LPVOID pvPlayer,char *szWho,char *szWhichSkill,char *szTimes,char *Result)
{
	CPlayerInfo *lpPlayerInfo;
	CNpc * lpNpc;
	CBaseMap * lpDataMap;
	BOOL bFindOppNPC = FALSE;
	int nTimes;
	int i;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	nTimes = atoi(szTimes);

	// guanhua 2000/10/26 start
	if(nTimes <= 0)
	{
		nTimes = 1;
	}
	else if(nTimes > 9999)
	{
		nTimes = 9999;
	}
	// guanhua 2000/10/26 end

	POSITION pMapPosite = lpPlayerInfo->pMapPosite;
    
	EnterCriticalSection(&myglobs.csMaplist);
	EnterCriticalSection(&myglobs.csPlayerData);

	if(lpPlayerInfo->nStatus != 0)
	{
		wsprintf(Result,"%s FAIL 你正忙著呢!",SZLEARNSKILL);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}
	//檢查潛能
	if(lpPlayerInfo->nQianNeng < nTimes)
	{
		wsprintf(Result,"%s FAIL 你的潛能不夠!",SZLEARNSKILL);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}
	int nNeedJing = (150/lpPlayerInfo->nInt) * nTimes;

	if(lpPlayerInfo->nEff_jing <= nNeedJing)
	{
		wsprintf(Result,"%s FAIL 你的精力不夠!",SZLEARNSKILL);
		LeaveCriticalSection(&myglobs.csPlayerData);
		LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}



	lpDataMap = maplist.GetAt(lpPlayerInfo->pMapPosite);
	for(i=0;i<lpDataMap->listNpc.GetCount();i++)
	{
		lpNpc = lpDataMap->listNpc.GetAt(lpDataMap->listNpc.FindIndex(i));
		if(!stricmp(lpNpc->szEName,szWho) || !strcmp(lpNpc->szCName,szWho))
		{
			if(lpNpc->nStatus != 0)
			{
				wsprintf(Result,"%s FAIL %s正忙著呢!",SZLEARNSKILL,lpNpc->szCName);				
	            LeaveCriticalSection(&myglobs.csPlayerData);
	            LeaveCriticalSection(&myglobs.csMaplist);
				return;
			}
			bFindOppNPC = TRUE;
			break;
		}
	}

	if(!bFindOppNPC)
	{
		wsprintf(Result,"%s FAIL 此人並不在地圖裡面",SZLEARNSKILL);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}

	if(lpNpc->szEName != lpPlayerInfo->szTeacher)
	{
		//處理不是師傅類型學習的指令
		wsprintf(Result,"%s FAIL %s說:\"學習%s這個還是找你的師傅吧!\"",SZLEARNSKILL,lpNpc->szCName,szWhichSkill);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}

	//檢查此NPC是否會這種技能
	TObjectSkill *lpNpcSkill,*lpPlayerSkill;
	lpNpcSkill = lpNpc->GetTSkill(szWhichSkill);
	if(lpNpcSkill == NULL)
	{
		wsprintf(Result,"%s FAIL %s說:\"學習%s這個還是另請高明吧!\"",SZLEARNSKILL,lpNpc->szCName,szWhichSkill);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}
	if(lpNpcSkill->nLevel < lpPlayerInfo->GetSkillLevel(szWhichSkill) )
	{
		wsprintf(Result,"%s FAIL 你的%s這個技能已經不低於%s了",SZLEARNSKILL,szWhichSkill,lpNpc->szCName);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}

	TRetInfo ri;

	ri = lpNpcSkill->lpSkill->DoLearn(lpPlayerInfo);
	if(ri.bRet == FALSE)
	{
		wsprintf(Result,"%s FAIL %s",SZLEARNSKILL,ri.szRet);
		LeaveCriticalSection(&myglobs.csPlayerData);
		LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}

	//是否已經會這種技能
	lpPlayerSkill = lpPlayerInfo->GetTSkill(szWhichSkill);
	if(lpPlayerSkill == NULL)
	{
		//以前不會,則增加這個功能
		// Spock start
		lpPlayerInfo->SetSkill(lpNpcSkill->lpSkill->szEName, 1, 1, "");
		lpPlayerSkill = lpPlayerInfo->GetTSkill(szWhichSkill);
		// Spock end
		// Spock deleted
/*		lpPlayerSkill = GetTSkill(lpNpcSkill->lpSkill->szEName,
								lpNpcSkill->lpSkill->nType,
								lpNpcSkill->lpSkill->nCanMap);
		lpPlayerInfo->listskill.AddTail(lpPlayerSkill);
*/
	}
	TRetInfo ret;
	//the event of GivingGoods
	ret = lpNpc->GivingBook(lpPlayerInfo,lpPlayerSkill->lpSkill->szEName);
	if(ret.bRet)
	{
		wsprintf(Result,"%s %s",SZOKMSG,ret.szRet);
		LeaveCriticalSection(&myglobs.csPlayerData);
	    LeaveCriticalSection(&myglobs.csMaplist);
		return;
	}
	//for(t=0;t<nTimes;t++)
	//{
		if(Improve(lpPlayerInfo, lpPlayerSkill, (lpPlayerInfo->nInt/5+1) * (nTimes))){
			lpPlayerInfo->nQianNeng -= nTimes;
			lpPlayerInfo->nEff_jing -= nNeedJing;

			wsprintf(Result,"%s OK 你聽了師傅的教誨對%s似乎有些領悟! %s,%s,%d %d",
			SZLEARNSKILL,
			lpPlayerSkill->lpSkill->szCName,
			lpPlayerSkill->lpSkill->szCName,
			lpPlayerSkill->lpSkill->szEName,
			(lpPlayerInfo->nInt/5+1),
			nTimes	);
		}
		else
		{
			wsprintf(Result,"%s FAIL %s說:\"你的經驗太少，已經不能領悟更深的%s了!\"",SZLEARNSKILL,lpNpc->szCName,szWhichSkill);
			//break;
		}
	//}
	LeaveCriticalSection(&myglobs.csPlayerData);
	LeaveCriticalSection(&myglobs.csMaplist);
}

