#include "stdafx.h"
#include "XmudOS.h"
#include "CommandCheck.h"
#include "CmdPlayerLogon.h"
#include "map\MapInfo.h"
#include "condition.h"
#include "skill\skill\Skill.h"

extern rmfullglobals myglobs;

void CCommandCheck::YunGongProc(LPVOID pvPlayer,char *szNumber,char *Result)
{
	CPlayerInfo *lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	CString szForce;
	int nGong = atoi(szNumber), nEffect;

	if(lpPlayerInfo->nStatus != AOS_none) {
		sprintf(Result,"%s 你正在忙",SZFAILMSG);
		return;
	}
	szForce = lpPlayerInfo->GetSkillMap("BaseForce");
	if(szForce.IsEmpty()) {
		sprintf(Result,"%s 你沒有配置特殊的氣功心法，無法運功",SZFAILMSG);
		return;
	}
	if(nGong < 20) {
		sprintf(Result,"%s 一次運功至少要消耗20點內力",SZFAILMSG);
		return;
	}
	if(nGong > lpPlayerInfo->nEff_force) {
		sprintf(Result,"%s 你沒有那麼多內力",SZFAILMSG);
		return;
	}
	if(nGong*3/10 > lpPlayerInfo->nEff_jingli) {
		sprintf(Result,"%s 你的精力不足",SZFAILMSG);
		return;
	}
	
	nEffect = 2 + lpPlayerInfo->GetSkillLevel(szForce) / 25;
	if (nEffect > 8) nEffect = 8;
	lpPlayerInfo->nEff_force -= nGong;
	lpPlayerInfo->nEff_jingli -= nGong * 3 / 10;
	lpPlayerInfo->nMax_qi += nGong * nEffect / 2;
	if(lpPlayerInfo->nMax_qi > lpPlayerInfo->GetMaxQi())
		lpPlayerInfo->nMax_qi = lpPlayerInfo->GetMaxQi();
	lpPlayerInfo->nEff_qi += nGong * nEffect / 2;
	if(lpPlayerInfo->nEff_qi > lpPlayerInfo->nMax_qi)
		lpPlayerInfo->nEff_qi = lpPlayerInfo->nMax_qi;
	lpPlayerInfo->nMax_jing += nGong * nEffect * 3 / 10;
	if(lpPlayerInfo->nMax_jing > lpPlayerInfo->GetMaxJing())
		lpPlayerInfo->nMax_jing = lpPlayerInfo->GetMaxJing();
	lpPlayerInfo->nEff_jing += nGong * nEffect * 3 / 10;
	if(lpPlayerInfo->nEff_jing > lpPlayerInfo->nMax_jing)
		lpPlayerInfo->nEff_jing = lpPlayerInfo->nMax_jing;

	sprintf(Result,"%s 你運起內功，氣息在體內流轉一週，精氣立時恢復",SZOKMSG);
	lpPlayerInfo->SendHeal();
}

void CCommandCheck::MappingProc(LPVOID pvPlayer, char *szSkillBase, char *szSkillMap,char *Result)
{
	CPlayerInfo *lpPlayerInfo = (CPlayerInfo*)pvPlayer;

	TObjectSkill * lpTSkill = lpPlayerInfo->GetTSkill(szSkillBase);
	if(lpTSkill == NULL)
	{
		wsprintf(Result,"%s 你目前沒有%s這種技能!",SZFAILMSG, szSkillBase);
		return;
	}
	if(lpTSkill->lpSkill->nType != ST_base)
	{
		wsprintf(Result,"%s 技能%s不是基本技能!",SZFAILMSG, szSkillBase);
		return;
	}
	if(!strcmp(szSkillBase, szSkillMap)) {
		lpTSkill->szMapping.Empty();
		sprintf(Result,"%s %s %s",SZMAPPING,szSkillBase,szSkillBase);
		return;
	}
	TObjectSkill * lpTSkill2 = lpPlayerInfo->GetTSkill(szSkillMap);
	if(lpTSkill2 == NULL)
	{
		wsprintf(Result,"%s 你目前沒有%s這種技能!",SZFAILMSG, szSkillMap);
		return;
	}
	if(lpTSkill2->lpSkill->nType != ST_special)
	{
		wsprintf(Result,"%s 技能%s不是高級技能!",SZFAILMSG, szSkillMap);
		return;
	}
	if(!(lpTSkill2->lpSkill->nCanMap & lpTSkill->lpSkill->nCanMap))
	{
		wsprintf(Result,"%s 技能%s和技能%s不是同一類技能!",SZFAILMSG, szSkillBase, szSkillMap);
		return;
	}

	lpTSkill->szMapping = lpTSkill2->lpSkill->szEName;
	wsprintf(Result,"%s %s %s",SZMAPPING,szSkillBase,szSkillMap);
}

void CCommandCheck::DazuoProc(LPVOID pvPlayer,char *szTime,char *Result)
{
	CPlayerInfo *lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	EnterCriticalSection(&myglobs.csPlayerData);
	if(lpPlayerInfo->nStatus != 0){
		wsprintf(Result,"%s 你正忙著呢!",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	if(lpPlayerInfo->nMax_qi <= 0 || lpPlayerInfo->nEff_qi <= 0 ){
		wsprintf(Result,"%s 你已經死了!",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	if(lpPlayerInfo->nBusy != 0)	{
		wsprintf(Result,"%s 你的上一個動作還沒有完成!",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}

	if(lpPlayerInfo->nMax_jing < 20) {
		wsprintf(Result,"%s 你現在身體狀況太差了,無法集中精神.",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	if(lpPlayerInfo->nMax_qi < 20)	{
		wsprintf(Result,"%s 你現在太累了,無法集中精神.",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}

	if(lpPlayerInfo->nEff_jing * 100 / lpPlayerInfo->nMax_jing < 20)	{
		wsprintf(Result,"%s 你現在身體狀況太差了，無法集中精神。",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	if(lpPlayerInfo->nEff_qi * 100 / lpPlayerInfo->nMax_qi < 20)	{
		wsprintf(Result,"%s 你現在太累了，無法集中精神。",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	int nCostJin = atoi(szTime);
	if(nCostJin < 20) {
		sprintf(Result,"%s 打坐最少要消耗20點氣",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	if(lpPlayerInfo->nEff_qi <= nCostJin)	{
		wsprintf(Result,"%s 你目前還沒有這麼多的氣。",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}

	CString szRet = lpPlayerInfo->GetSkillMap("BaseForce");
	if(szRet.IsEmpty())	{
		wsprintf(Result,"%s 你還沒有什麼特別氣功心法!",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}

	lpPlayerInfo->ApplyCondition(CK_special, "DaZuo", nCostJin, nCostJin);
	if( lpPlayerInfo->nRefile[0] > 0 )	{
		lpPlayerInfo->nBusy = (((nCostJin + 40) >> 3)* 3 )/ 5 ;
	}else	{
		lpPlayerInfo->nBusy = (nCostJin + 60) >> 3;
	}

	if( lpPlayerInfo->nBusy < 0 )
		lpPlayerInfo->nBusy = 0;
	lpPlayerInfo->nStatus = AOS_dazuo;
	lpPlayerInfo->nEff_qi -= nCostJin;
	
	LeaveCriticalSection(&myglobs.csPlayerData);
	CString szTmp;
	szTmp.Format("%s %s %s %d", SZDAZUO, lpPlayerInfo->szCName, lpPlayerInfo->szEName, lpPlayerInfo->nEff_qi);
	MapMessage(szTmp, lpPlayerInfo);
}

void CCommandCheck::TuNaProc(LPVOID pvPlayer,char *szTime,char *Result)
{
	CPlayerInfo *lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	EnterCriticalSection(&myglobs.csPlayerData);
	if(lpPlayerInfo->nStatus != 0)	{
		wsprintf(Result,"%s 你正忙著呢!",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}

	if(lpPlayerInfo->nMax_qi<=0)	{
		wsprintf(Result,"%s 你已經死了!",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}

	if(lpPlayerInfo->nBusy != 0)	{
		wsprintf(Result,"%s 你的上一個動作還沒有完成!",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}

	if(lpPlayerInfo->nMax_jing < 20) {
		wsprintf(Result,"%s 你現在身體狀況太差了,無法集中精神.",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	if(lpPlayerInfo->nMax_qi < 20)	{
		wsprintf(Result,"%s 你現在太累了,無法集中精神.",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}

	if(lpPlayerInfo->nEff_jing * 100 / lpPlayerInfo->nMax_jing < 20)	{
		wsprintf(Result,"%s 你現在身體狀況太差了,無法集中精神.",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	if(lpPlayerInfo->nEff_qi * 100 / lpPlayerInfo->nMax_qi < 20)	{
		wsprintf(Result,"%s 你現在太累了,無法集中精神.",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}

	int nCostJin = atoi(szTime);
	if(nCostJin < 20) {
		sprintf(Result,"%s 吐納最少要消耗20點精",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}
	if(lpPlayerInfo->nEff_jing <= nCostJin)	{
		wsprintf(Result,"%s 你目前還沒有這麼多的精。",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}

	CString szRet = lpPlayerInfo->GetSkillMap("BaseForce");
	if(szRet.IsEmpty())	{
		wsprintf(Result,"%s 你還沒有什麼特別氣功心法!",SZFAILMSG);
		LeaveCriticalSection(&myglobs.csPlayerData);
		return;
	}

	lpPlayerInfo->ApplyCondition(CK_special, "TuNa", nCostJin, nCostJin);

	if( lpPlayerInfo->nRefile[0] > 0 )
		lpPlayerInfo->nBusy = (((nCostJin + 40) >> 3 )* 3 )/ 5 ;
	else
		lpPlayerInfo->nBusy = (nCostJin + 40) >> 3;

	if( lpPlayerInfo->nBusy < 0 )
		lpPlayerInfo->nBusy = 0;

	lpPlayerInfo->nEff_jing -= nCostJin;
	lpPlayerInfo->nStatus = AOS_tuna;
	LeaveCriticalSection(&myglobs.csPlayerData);
	CString szTmp;
	szTmp.Format("%s %s %s %d", SZTUNA, lpPlayerInfo->szCName,lpPlayerInfo->szEName, lpPlayerInfo->nEff_jing);
	MapMessage(szTmp, lpPlayerInfo);
}
