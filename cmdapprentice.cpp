#include "stdafx.h"
#include "XmudOS.h"
#include "CommandCheck.h"
#include "CmdPlayerLogon.h"
#include "npc\Npc.h"
#include "map\mapinfo.h"

extern rmfullglobals myglobs;
extern void GetXFileName(CPlayerInfo * lpPlayerInfo);
void CCommandCheck::ApprenticeProc(LPVOID pvPlayer,char *szWho,char *Result)
{
	CPlayerInfo *lpPlayerInfo;
	CNpc * lpNpc;
	CBaseMap * lpDataMap;
	BOOL bFindOppNPC = FALSE;
	int i;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	POSITION pMapPosite = lpPlayerInfo->pMapPosite;

	if(lpPlayerInfo->szNickName == "充氣娃娃") {
		sprintf(Result,"%s FAIL 特殊人物不能拜師",SZAPPRENTICE);
		return;
	}
	EnterCriticalSection(&myglobs.csMaplist);
	lpDataMap = maplist.GetAt(lpPlayerInfo->pMapPosite);
	for(i=0;i<lpDataMap->listNpc.GetCount();i++)	{
		lpNpc = lpDataMap->listNpc.GetAt(lpDataMap->listNpc.FindIndex(i));
		if(!stricmp(lpNpc->szEName,szWho) || !strcmp(lpNpc->szCName,szWho))	{
			if(lpNpc->nStatus != 0)	{
				wsprintf(Result,"%s FAIL %s正忙著呢!",SZAPPRENTICE,lpNpc->szCName);
				LeaveCriticalSection(&myglobs.csMaplist);
				return;
			}
			bFindOppNPC = TRUE;
			break;
		}
	}
	if(!bFindOppNPC)	{
		LeaveCriticalSection(&myglobs.csMaplist);
		wsprintf(Result,"%s FAIL 此人並不在地圖裡面",SZAPPRENTICE);
		return;
	}
	if(lpPlayerInfo->szTeacher == lpNpc->szEName)
	{
		LeaveCriticalSection(&myglobs.csMaplist);
		wsprintf(Result,"%s FAIL 你恭恭敬敬的向師傅(%s)磕頭請安",SZAPPRENTICE,lpNpc->szCName);
		return;
	}
	LeaveCriticalSection(&myglobs.csMaplist);

	TRetInfo tRet = lpNpc->DoApprentice(lpPlayerInfo);
	BOOL bBetray = FALSE;
	if(tRet.bRet)	{
		if((lpPlayerInfo->szFamily != "崑崙武館")	&&(lpPlayerInfo->szFamily != "天道武館")
			&&(lpPlayerInfo->szFamily != "鎮遠武館")&&(lpPlayerInfo->szFamily != "揚威武館")
			&&(lpPlayerInfo->szFamily != "無門派")	&&(lpPlayerInfo->szFamily != lpNpc->szFamily)
			&&(lpPlayerInfo->szFamily != "昭明書院")	){
			lpPlayerInfo->listBetray.RemoveAll();
			lpPlayerInfo->listBetray.AddTail(lpPlayerInfo->szFamily);
			bBetray = TRUE;
			lpPlayerInfo->nBetray ++;
			lpPlayerInfo->nShen -= 1000;

			lpPlayerInfo->nCombat_exp *= 3/4;
			lpPlayerInfo->nCombat_exp -= lpPlayerInfo->nCombat_exp >> 3;
			if( lpPlayerInfo->nCombat_exp < 0 ) lpPlayerInfo->nCombat_exp=0;
			TObjectSkill *lpPlayerSkill;
			for(i=0; i < lpPlayerInfo->listskill.GetCount(); i++)	{
				lpPlayerSkill = lpPlayerInfo->listskill.GetAt(lpPlayerInfo->listskill.FindIndex(i));
				lpPlayerSkill->nScore = 0;

				if( !strstr( lpPlayerSkill->lpSkill->szEName , "Base") &&
					!strstr( lpPlayerSkill->lpSkill->szEName , "OtherLi")	)	{
					if (lpPlayerSkill->nLevel >= 51)	{
						lpPlayerSkill->nScore = 0;
						lpPlayerSkill->nLevel-=50;
						if( lpPlayerSkill->nLevel < 0 ) lpPlayerSkill->nLevel = 0;

					}

				}
			}
		}

		lpPlayerInfo->szFamily = lpNpc->szFamily;
		lpPlayerInfo->szTeacher = lpNpc->szEName;
		lpPlayerInfo->nGeneration = lpNpc->nGeneration + 1;
		GetXFileName(lpPlayerInfo);
		if(!bBetray)
			wsprintf(Result,"%s OK %s %s,%s,%d,%s",  
					SZAPPRENTICE,				tRet.szRet,
					lpPlayerInfo->szFamily,		lpPlayerInfo->szTeacher,
					lpPlayerInfo->nGeneration,	lpPlayerInfo->szXFileName);
		else
			wsprintf(Result,"%s BETRAY %s %s,%s,%d,%d,%d,%s,%d",
					SZAPPRENTICE,					tRet.szRet,
					lpPlayerInfo->szFamily,			lpPlayerInfo->szTeacher,
					lpPlayerInfo->nGeneration,		lpPlayerInfo->nBetray,
					lpPlayerInfo->nCombat_exp,		lpPlayerInfo->szXFileName,
					1);

	}else	{
		wsprintf(Result,"%s FAIL %s",SZAPPRENTICE,tRet.szRet);
		return;
	}
}

void CCommandCheck::GetMasterSkill(LPVOID pvPlayer,char *szWho,char *Result)
{
	CPlayerInfo *lpPlayerInfo;
	CNpc * lpNpc;
	CBaseMap * lpDataMap;
	BOOL bFindOppNPC = FALSE;
	int i;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	POSITION pMapPosite = lpPlayerInfo->pMapPosite;

	EnterCriticalSection(&myglobs.csMaplist);
	lpDataMap = maplist.GetAt(lpPlayerInfo->pMapPosite);
	for(i=0;i<lpDataMap->listNpc.GetCount();i++)	{
		lpNpc = lpDataMap->listNpc.GetAt(lpDataMap->listNpc.FindIndex(i));
		if(!stricmp(lpNpc->szEName,szWho) || !strcmp(lpNpc->szCName,szWho))	{
			if(lpPlayerInfo->szTeacher != lpNpc->szEName)	{
				LeaveCriticalSection(&myglobs.csMaplist);
				wsprintf(Result,"%s FAIL Skill指令只能查看師傅的技能!",SZMASTERSKILL);
				return;
			}
			if(lpNpc->nStatus != 0)	{
				wsprintf(Result,"%s FAIL %s正忙著呢!",SZMASTERSKILL,lpNpc->szCName);
				LeaveCriticalSection(&myglobs.csMaplist);
				return;
			}
			bFindOppNPC = TRUE;
			break;
		}
	}
	if(!bFindOppNPC)	{
		LeaveCriticalSection(&myglobs.csMaplist);
		wsprintf(Result,"%s FAIL 此人並不在地圖裡面",SZMASTERSKILL);
		return;
	}
	LeaveCriticalSection(&myglobs.csMaplist);

	CString sResultMsg,parm,sign;
	char itmpString[20];
	sign = CString("'");
	parm = CString("',");
	sResultMsg = sign+CString("NPCSKILL") + parm;
	TObjectSkill *lpNpcSkill;
	int j = lpNpc->listskill.GetCount();
	sResultMsg += sign+CString("RC")+parm;
	sResultMsg += sign+lpNpc->szCName+parm;
	itoa(10,itmpString,10);
	sResultMsg += sign+itmpString+parm;
	sResultMsg += sign+CString("RCEND")+parm;
	for(i=0;i<j;i++)	{
		lpNpcSkill = lpNpc->listskill.GetAt(lpNpc->listskill.FindIndex(i));
		if(lpNpcSkill->nLevel == 0)continue;
		sResultMsg += sign+CString("RC")+parm;
		sResultMsg += sign+lpNpcSkill->lpSkill->szCName+parm;
		itoa(lpNpcSkill->nLevel,itmpString,10);
		sResultMsg += sign+itmpString+parm;
		sResultMsg += sign+CString("RCEND")+parm;
	}
	sResultMsg += sign+CString("NPCSKILLEND")+parm;
	wsprintf(Result,"%s OK %s", SZMASTERSKILL, (char*)(LPCSTR)sResultMsg);
}
