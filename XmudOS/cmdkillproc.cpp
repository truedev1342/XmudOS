#include "stdafx.h"
#include "XMudOS.h"
#include "CommandCheck.h"
#include "fight.h"
#include "CmdPlayerLogon.h"
#include "map\MapInfo.h"
#include "npc\Npc.h"
#include "common.h"
#include "hash.h"

extern rmfullglobals myglobs;
extern CList <TClientConData *,TClientConData* >playersocketlist;
extern CList <CBaseMap*,CBaseMap*>maplist;
extern CList <CFight*,CFight*>killlist;
extern CList <CFight*,CFight*>fightlist;

void RemoveFight(CActiveObject *lpAObj)
{
	POSITION pos, opos, lastpos;
	CFight *lpFight;
	CActiveObject *lpOpp;

	pos = fightlist.GetHeadPosition();
	while (pos != NULL) {
		lastpos = pos;
		lpFight = fightlist.GetNext(pos);
		if (lpFight == NULL) {
			AddRecordMsg("ERROR NULL pointer in RemoveFight, lpFight");
			fightlist.RemoveAt(lastpos);
			continue;
		}
		if (lpFight->lpActiveObject == NULL) {
			AddRecordMsg("ERROR NULL pointer in RemoveFight, lpFight->lpActiveObject");
			fightlist.RemoveAt(lastpos);
			delete lpFight;
			continue;
		}
		if (strcmp(lpFight->lpActiveObject->szCheck,SZAOBJCHECK)) {
			AddRecordMsg("ERROR Bad data in RemoveFight, lpFight->lpActiveObject");
			fightlist.RemoveAt(lastpos);
			delete lpFight;
			continue;
		}
		if ((lpFight->lpActiveObject->szEName == lpAObj->szEName)
			&& (lpFight->lpActiveObject->szCName == lpAObj->szCName)) {
			fightlist.RemoveAt(lastpos);
			delete lpFight;
			break;
		}
	}
	pos = lpAObj->listfightopp.GetHeadPosition();
	while (pos != NULL) {
		lpOpp = lpAObj->listfightopp.GetNext(pos);
		lpOpp->listfightopp.RemoveAll();
		lpOpp->nStatus = AOS_none;
		opos = fightlist.GetHeadPosition();
		while (opos != NULL) {
			lastpos = opos;
			lpFight = fightlist.GetNext(opos);
			if ((lpFight->lpActiveObject->szEName == lpOpp->szEName) &&
				(lpFight->lpActiveObject->szCName == lpOpp->szCName)) {
				fightlist.RemoveAt(lastpos);
				break;
			}
		}
	}
	lpAObj->listfightopp.RemoveAll();
}

void CCommandCheck::KillProc(LPVOID pvPlayer,char *playerName,char * szKillOpp,char *Result)
{
	CFight *lpFight;
	CBaseMap * lpDataMap;
	CPlayerInfo *lpPlayerInfo,*lpOtherPlayerInfo;
	CActiveObject *lpOpp;
	CNpc * lpNpc;
	BOOL bFindOppPlayer = FALSE;
	BOOL bFindOppNPC = FALSE;
	CString szRet;
	POSITION pos, lastpos, pos2;

	CString msg, szOppName, szOppEName, szOppSName;
	CStringList listMsg;
	CList <CNpc*, CNpc*> listOpp;
	CCommandCheck m_CommandCheck;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	lpPlayerInfo->nOther = 0;

	
	int bGM = m_CommandCheck.CheckGM((char*)(LPCSTR)lpPlayerInfo->szUserName);

	if (lpPlayerInfo->nStatus != AOS_none) return;
	if(myglobs.bNoKill && !bGM) {
		sprintf(Result,"%s 這個伺服器禁止死鬥！",SZFAILMSG);
		return;
	}

	POSITION pMapPosite = lpPlayerInfo->pMapPosite;
	lpDataMap = maplist.GetAt(lpPlayerInfo->pMapPosite);

	if (!(lpDataMap->bPK) && !bGM) {
		sprintf(Result,"%s %s是不能動武的地方！",SZFAILMSG,lpDataMap->szCName);
		return;
	}

	EnterCriticalSection(&myglobs.csFightlist);
	EnterCriticalSection(&myglobs.csMaplist);
	EnterCriticalSection(&myglobs.csPlayerData);

	pos = lpDataMap->listNpc.GetHeadPosition();
	while(pos != NULL) {
		lpNpc = lpDataMap->listNpc.GetNext(pos);
		if ((lpNpc->nAttitude & NP_guard) && (lpNpc->nStatus != AOS_dead)) {
			if ((lpNpc->szFamily == lpPlayerInfo->szFamily)	&& (lpNpc->szFamily != "無門派"))
				continue;
			bFindOppNPC = TRUE;
			pos2 = lpNpc->listfightopp.GetHeadPosition();
			while (pos2) {
				lpOpp = lpNpc->listfightopp.GetNext(pos2);
				if (!strcmp(lpOpp->szEName, szKillOpp)) {
					bFindOppNPC = FALSE;
					break;
				}
			}
			if (!bFindOppNPC) {
				break;
			}
			if (lpNpc->nStatus == AOS_fight) {
				msg.Format("%s %s %s %s",SZFIGHTOVER,szRedHigt,lpNpc->szCName,lpNpc->szEName);
				listMsg.AddTail(msg);
			}
			listOpp.AddTail(lpNpc);
		}
	}
	if (bFindOppNPC) {
		lpPlayerInfo->nStatus = AOS_kill;
		lpPlayerInfo->DeleteCondition("DaZuo");
		lpPlayerInfo->DeleteCondition("TuNa");
		lpPlayerInfo->bNoHealing=TRUE;
		lpPlayerInfo->bAttack = TRUE;
		pos = listOpp.GetHeadPosition();
		while (pos) {
			lpNpc = listOpp.GetNext(pos);
			lpPlayerInfo->listfightopp.AddTail(lpNpc);
			if (lpNpc->nStatus == AOS_fight) {
				RemoveFight(lpNpc);
			}
			lpNpc->listfightopp.AddTail(lpPlayerInfo);
			lpNpc->nStatus = AOS_kill;
			lpNpc->bNoHealing=TRUE;
			

			if(lpNpc->listfightopp.GetCount()==1){
				lpFight = new CFight;
				lpFight->iRound=130;
				lpFight->lpActiveObject = lpNpc;
				killlist.AddTail(lpFight);
			}
			if(lpPlayerInfo->listfightopp.GetCount()==1)
			{
				lpFight = new CFight;
				lpFight->iRound=130;
				lpFight->lpActiveObject = lpPlayerInfo;
				killlist.AddTail(lpFight);
			}
			if (lpNpc->szFamily == "無門派") {
				msg.Format("%s %s %s對%s怒吼道：大膽狂徒，竟敢在此行兇殺人，饒你不得！", SZOKMSG,
					szRedHigt, lpNpc->szCName, lpPlayerInfo->szCName);
			} else if ((lpNpc->szFamily == "星宿派") || (lpNpc->szFamily == "丐幫")) {
				msg.Format("%s %s %s對%s怒吼道：竟敢在我%s地界內撒野，饒你不得！", SZOKMSG,
					szRedHigt, lpNpc->szCName, lpPlayerInfo->szCName, lpNpc->szFamily);

			} else if((lpNpc->szFamily == "惡人谷")) { //andy_com2  2001.2.21 11:06
				msg.Format("%s %s %s對%s怒吼道：爾等何人竟敢闖入我%s內，饒你不得！", SZOKMSG,
					szRedHigt, lpNpc->szCName, lpPlayerInfo->szCName, lpNpc->szFamily);

			} else {
				msg.Format("%s %s %s對%s怒吼道：我%s乃清淨之地，竟敢在此行兇殺人，饒你不得！", SZOKMSG,
					szRedHigt, lpNpc->szCName, lpPlayerInfo->szCName, lpNpc->szFamily);
			}
			listMsg.AddTail(msg);
			msg.Format("%s %s %s %s %s",SZKILLSB,lpNpc->szCName,lpNpc->szEName,
				lpPlayerInfo->szCName,lpPlayerInfo->szEName);
			listMsg.AddTail(msg);
		}		
		pos = listMsg.GetHeadPosition();
		while(pos) {
			msg = listMsg.GetNext(pos);
			lpPlayerInfo->SendMsg(msg);
			lpPlayerInfo->SendMsgToAll(msg);
		}
		listOpp.RemoveAll();
		listMsg.RemoveAll();
		strcpy(Result, "OK");
		LeaveCriticalSection(&myglobs.csPlayerData);
		LeaveCriticalSection(&myglobs.csMaplist);
		LeaveCriticalSection(&myglobs.csFightlist);
		return;
	}
	listOpp.RemoveAll();
	listMsg.RemoveAll();
	// Spock end
	pos = lpDataMap->listplayer.GetHeadPosition();
	while(pos != NULL)
	{
		lastpos = pos;
		lpOtherPlayerInfo = lpDataMap->listplayer.GetNext(pos);
		// Spock start: Check NULL pointer and bad data
		if (lpOtherPlayerInfo == NULL) {
			AddRecordMsg("ERROR NULL pointer in KillProc, lpOtherPlayerInfo");
			lpDataMap->listplayer.RemoveAt(lastpos);
			continue;
		}
		if (strcmp(lpOtherPlayerInfo->szCheck, SZAOBJCHECK)) {
			AddRecordMsg("ERROR Bad data in KillProc, lpOtherPlayerInfo");
			lpDataMap->listplayer.RemoveAt(lastpos);
			continue;
		}
		// Spock end
		if(!strcmp(lpOtherPlayerInfo->szEName,szKillOpp)
		   && (lpOtherPlayerInfo->nStatus!=AOS_dead)) // Spock fixed
		{
			bFindOppPlayer = TRUE;
			break;
		}
	}
	if(!bFindOppPlayer)
	{
		pos = lpDataMap->listNpc.GetHeadPosition();
		while(pos != NULL)
		{
			lpNpc = lpDataMap->listNpc.GetNext(pos);
			if(!strcmp(lpNpc->szEName,szKillOpp)
				&& (lpNpc->nStatus!=AOS_dead))
			{
				bFindOppNPC = TRUE;
				break;
			}
		}

		if(!bFindOppNPC)
		{
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			LeaveCriticalSection(&myglobs.csFightlist);
			szRet.Format("%s 對手已經不在場內了",SZFAILMSG);
			strcpy(Result,szRet);
			return;
		}else{
			lpOpp = lpNpc;
		}
	}else{

		if( (lpPlayerInfo->szNickName != "充氣娃娃") && (lpOtherPlayerInfo->szNickName == "充氣娃娃") )
		{
			sprintf(Result, "%s 無法與GM人物進行死鬥！", SZFAILMSG);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			LeaveCriticalSection(&myglobs.csFightlist);
			return;
		}

		if( (lpPlayerInfo->szNickName == "充氣娃娃") && (lpOtherPlayerInfo->szNickName != "充氣娃娃") )
		{
			sprintf(Result, "%s GM人物無法與一般人物進行死鬥！", SZFAILMSG);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			LeaveCriticalSection(&myglobs.csFightlist);
			return;
		}

		lpOpp = lpOtherPlayerInfo;
		lpOtherPlayerInfo->DeleteCondition("DaZuo");
		lpOtherPlayerInfo->DeleteCondition("TuNa");
	}
	if (lpOpp->nStatus == AOS_fight) {
		RemoveFight(lpOpp);
		msg.Format("%s %s %s %s",SZFIGHTOVER,szRedHigt,lpOpp->szCName,lpOpp->szEName);
	} else {
		msg.Empty();
	}
	lpOpp->listfightopp.AddTail(lpPlayerInfo);
	lpOpp->nStatus = AOS_kill;
	lpOpp->bNoHealing=TRUE;
	if(lpOpp->listfightopp.GetCount()==1)
	{
		lpFight = new CFight;
		lpFight->lpActiveObject = lpOpp;
		killlist.AddTail(lpFight);
	}
	lpPlayerInfo->listfightopp.AddTail(lpOpp);
	lpPlayerInfo->DeleteCondition("DaZuo");
	lpPlayerInfo->DeleteCondition("TuNa");
	lpPlayerInfo->bNoHealing=TRUE;
	lpPlayerInfo->bAttack = TRUE;
	lpPlayerInfo->nStatus = AOS_kill;
	if(lpPlayerInfo->listfightopp.GetCount()==1)
	{
		lpFight = new CFight;
		lpFight->lpActiveObject = lpPlayerInfo;
		killlist.AddTail(lpFight);
	}
	szOppName = lpOpp->szCName;
	szOppEName = lpOpp->szEName;
	szOppSName = GetSpecialName(lpOpp, SName_mie);

	if (!msg.IsEmpty()) {
		lpOpp->SendMsgToAll(msg);
		lpOpp->SendMsg(msg);
	}
	
		
	switch(random(3))
	{
	case 0:
		msg.Format("%s對%s大聲叫道︰%s,%s今天和你拚了！", lpPlayerInfo->szCName, szOppName,
			szOppSName, GetSpecialName(lpPlayerInfo,SName_da));
		break;
	case 1:
		msg.Format("%s對%s大聲怒斥道︰%s,今天不是你死就是我活！", lpPlayerInfo->szCName, szOppName,
			szOppSName);
		break;
	case 2:
		msg.Format("%s對%s惡狠狠的說︰%s,去死吧！", lpPlayerInfo->szCName, szOppName,
			szOppSName);
		break;
	}
	szRet.Format("%s %s %s",SZOKMSG,szRedHigt,msg);
	lpPlayerInfo->SendMsgToAll(szRet);
	lpPlayerInfo->SendMsg(szRet);
	szRet.Format("%s %s %s看起來要殺死%s。",SZOKMSG,szRedHigt,szOppName,lpPlayerInfo->szCName);
	lpPlayerInfo->SendMsgToAll(szRet);
	lpPlayerInfo->SendMsg(szRet);
	msg.Format("%s %s %s %s %s",SZKILLSB,lpPlayerInfo->szCName,lpPlayerInfo->szEName,
		szOppName,szOppEName);
	lpPlayerInfo->SendMsgToAll(msg);
	strcpy(Result, msg);
	LeaveCriticalSection(&myglobs.csPlayerData);
	LeaveCriticalSection(&myglobs.csMaplist);
	LeaveCriticalSection(&myglobs.csFightlist);
}

void MapMessage(CString msg, CActiveObject *me, CActiveObject *you)
{
	CString szSend;
	szSend = msg;
	szSend.Replace("$N", "你");
	if(you != NULL)
		szSend.Replace("$n", you->szCName);
	me->SendMsg(szSend);
	if(you != NULL){
		szSend = msg;
		szSend.Replace("$N", me->szCName);
		szSend.Replace("$n", "你");

		you->SendMsg(szSend);
	}
	szSend = msg;
	szSend.Replace("$N", me->szCName);
	if(you != NULL)
		szSend.Replace("$n", you->szCName);
	me->SendMsgToAll(szSend, you);
}

void CCommandCheck::FightProc(LPVOID pvPlayer, const char *playerName, const char * szKillOpp, const char *szRound, char *Result)
{
	CFight *lpFight;
	CBaseMap * lpDataMap;
	CPlayerInfo *lpPlayerInfo,*lpOtherPlayerInfo;
	CActiveObject *lpOpp;
	CNpc * lpNpc;
	BOOL bFindOppPlayer = FALSE;
	BOOL bFindOppNPC = FALSE;
	CString szRet;

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	if (lpPlayerInfo->nStatus != AOS_none)
	{
		szRet.Format("%s 你正在忙呢！",SZFAILMSG);
		strcpy(Result,szRet);
		return;
	}
	else if(lpPlayerInfo->nEff_qi<10)
	{
		szRet.Format("%s 你的身體太虛弱了！",SZFAILMSG);
		strcpy(Result,szRet);
		return;
	}
	POSITION pMapPosite = lpPlayerInfo->pMapPosite;
	lpDataMap = maplist.GetAt(lpPlayerInfo->pMapPosite);
	if (!(lpDataMap->bPK)) {
		szRet.Format("%s %s是不能動武的地方！",SZFAILMSG,lpDataMap->szCName);
		strcpy(Result,szRet);
		return;
	}


	EnterCriticalSection(&myglobs.csFightlist);
	EnterCriticalSection(&myglobs.csMaplist);
	EnterCriticalSection(&myglobs.csPlayerData);
	POSITION pos = lpDataMap->listplayer.GetHeadPosition();
	while(pos != NULL)
	{
		lpOtherPlayerInfo = lpDataMap->listplayer.GetNext(pos);
		if(!strcmp(lpOtherPlayerInfo->szEName,szKillOpp) || 
		   !strcmp(lpOtherPlayerInfo->szCName,szKillOpp))
		{
			bFindOppPlayer = TRUE;
			break;
		}
	}
	if(!bFindOppPlayer)
	{
		pos = lpDataMap->listNpc.GetHeadPosition();
		while(pos != NULL)
		{
			lpNpc = lpDataMap->listNpc.GetNext(pos);
			if(!strcmp(lpNpc->szEName,szKillOpp) || 
			   !strcmp(lpNpc->szCName,szKillOpp))
			{
				bFindOppNPC = TRUE;
				break;
			}
		}

		if(!bFindOppNPC)
		{
			szRet.Format("%s 對手已經不在場內了",SZFAILMSG);
			strcpy(Result,szRet);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			LeaveCriticalSection(&myglobs.csFightlist);
			return;
		}
		else if(lpNpc->nStatus!=AOS_none)
		{
			szRet.Format("%s 對手正在忙呢！",SZFAILMSG);
			strcpy(Result,szRet);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			LeaveCriticalSection(&myglobs.csFightlist);
			return;
		}else	{
			lpOpp = lpNpc;
			CString szTemp;
			if ((lpNpc->szEName) != (lpPlayerInfo->szTeacher)) {
				if (lpNpc->nAttitude & NP_nofight) {
					sprintf(Result, "%s %s：我是不隨便和人過招的",SZFAILMSG,lpNpc->szCName);
					LeaveCriticalSection(&myglobs.csPlayerData);
					LeaveCriticalSection(&myglobs.csMaplist);
					LeaveCriticalSection(&myglobs.csFightlist);
					return;
				}
				if ((lpNpc->nShen <= -70) && (lpPlayerInfo->szFamily != lpNpc->szFamily)
					&& (lpPlayerInfo->nShen > 100)) {
						sprintf(Result, "%s %s：滾邊去，老子沒空理你！",SZFAILMSG,lpNpc->szCName);
						LeaveCriticalSection(&myglobs.csPlayerData);
						LeaveCriticalSection(&myglobs.csMaplist);
						LeaveCriticalSection(&myglobs.csFightlist);
						return;
				}
				if ((lpNpc->nShen > 100) && (lpPlayerInfo->nShen < -100) && 
					(lpNpc->nShen - lpPlayerInfo->nShen > 500) && (lpNpc->nCombat_exp > 1000)) {
					szRet.Format("%s %s：像爾等這種邪魔歪道，在下不願與你切磋武藝",SZFAILMSG,lpNpc->szCName);
					strcpy(Result,szRet);
					LeaveCriticalSection(&myglobs.csPlayerData);
					LeaveCriticalSection(&myglobs.csMaplist);
					LeaveCriticalSection(&myglobs.csFightlist);
					return;
				}
			}
			if ((lpNpc->nCombat_exp > 2000) && (lpNpc->nCombat_exp > lpPlayerInfo->nCombat_exp*5)) {
				szRet.Format("%s %s：像你這種身手，還是多磨練磨練再說吧！",SZFAILMSG,lpNpc->szCName);
				strcpy(Result,szRet);
				LeaveCriticalSection(&myglobs.csPlayerData);
				LeaveCriticalSection(&myglobs.csMaplist);
				LeaveCriticalSection(&myglobs.csFightlist);
				return;
			}

			lpPlayerInfo->listfightopp.AddTail(lpNpc);
			lpPlayerInfo->nStatus = AOS_fight;
			lpPlayerInfo->DeleteCondition("DaZuo");
			lpPlayerInfo->DeleteCondition("TuNa");
			lpNpc->listfightopp.AddTail(lpPlayerInfo);
			lpNpc->nStatus = AOS_fight;

			//放入對手到戰斗鏈表
			if(lpPlayerInfo->listfightopp.GetCount()==1)
			{
				lpFight = new CFight;
				lpFight->lpActiveObject = lpPlayerInfo;
				lpFight->iRound = atoi(szRound);
				fightlist.AddTail(lpFight);
			}
			
			if(lpNpc->listfightopp.GetCount()==1)
			{
				lpFight = new CFight;
				lpFight->lpActiveObject = lpNpc;
				lpFight->iRound = atoi(szRound);
				fightlist.AddTail(lpFight);
			}
		}
	}else	{
		lpOpp = lpOtherPlayerInfo;
		if(lpOpp->nStatus!=AOS_none){
			szRet.Format("%s %s正在忙呢！",SZFAILMSG,lpOpp->szCName);
			strcpy(Result,szRet);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			LeaveCriticalSection(&myglobs.csFightlist);
			return;
		}
		if(lpOtherPlayerInfo->nPlayerStatus & PS_nofight){
			szRet.Format("%s %s拒絕和你切磋！",SZFAILMSG,lpOtherPlayerInfo->szCName);
			strcpy(Result,szRet);
			LeaveCriticalSection(&myglobs.csPlayerData);
			LeaveCriticalSection(&myglobs.csMaplist);
			LeaveCriticalSection(&myglobs.csFightlist);
			return;
		}

		lpPlayerInfo->listfightopp.AddTail(lpOtherPlayerInfo);
		
		lpPlayerInfo->nStatus = AOS_fight;
		lpPlayerInfo->DeleteCondition("DaZuo");
		lpPlayerInfo->DeleteCondition("TuNa");
		lpOtherPlayerInfo->listfightopp.AddTail(lpPlayerInfo);
		lpOtherPlayerInfo->nStatus = AOS_fight;
		lpOtherPlayerInfo->DeleteCondition("DaZuo");
		lpOtherPlayerInfo->DeleteCondition("TuNa");

		if(lpPlayerInfo->listfightopp.GetCount()==1){
			lpFight = new CFight;
			lpFight->lpActiveObject = lpPlayerInfo;
			lpFight->iRound = atoi(szRound);
			fightlist.AddTail(lpFight);
		}
		if(lpOtherPlayerInfo->listfightopp.GetCount()==1){
			lpFight = new CFight;
			lpFight->lpActiveObject = lpOtherPlayerInfo;
			lpFight->iRound = atoi(szRound);
			fightlist.AddTail(lpFight);
		}
	}
	lpPlayerInfo->bNoHealing=TRUE;
	lpOpp->bNoHealing=TRUE;
	CString msg, szOppName, szOppEName;
	szOppName = lpOpp->szCName;
	szOppEName = lpOpp->szEName;
	
	szRet.Format("%s %s %s向%s切磋武功。",SZOKMSG,szRedHigt,lpPlayerInfo->szCName,szOppName);
	lpPlayerInfo->SendMsgToAll(szRet);
	lpPlayerInfo->SendMsg(szRet);
	switch(random(2))
	{
	case 0:
		msg.Format("%s對%s說道︰在下%s，領教高招了！", szOppName,lpPlayerInfo->szCName,szOppName);
		break;
	case 1:
		msg.Format("%s對%s說道︰既然賜教，在下%s只好奉陪！", szOppName,lpPlayerInfo->szCName,szOppName);
		break;
	}
	szRet.Format("%s %s %s",SZOKMSG,szRedHigt,msg);
	lpPlayerInfo->SendMsgToAll(szRet);
	lpPlayerInfo->SendMsg(szRet);
	msg.Format("%s %s %s %s %s",SZFIGHTSB,lpPlayerInfo->szCName,lpPlayerInfo->szEName,
		szOppName,szOppEName);
	lpPlayerInfo->SendMsgToAll(msg);
	strcpy(Result, msg);
	LeaveCriticalSection(&myglobs.csPlayerData);
	LeaveCriticalSection(&myglobs.csMaplist);
	LeaveCriticalSection(&myglobs.csFightlist);
	return;
}
void CCommandCheck::ShootProc(CPlayerInfo *lpPlayerInfo,CWeapon *lpDrug,char *Result)
{
	CString szSend;
	int shoint = 0;
	shoint=random(20);

	if(lpPlayerInfo->nOther == 0 && lpDrug->lpWeapon->nKind == WK_throwing){
		if(shoint >= 15){
			lpPlayerInfo->nOther=lpDrug->lpWeapon->nAttack;
			szSend.Format("%s %s %s", SZSHOOT, "OK",lpDrug->lpGoods->szCName);
		}
		else
		szSend.Format("%s %s %s", SZSHOOT, "ERROR",lpDrug->lpGoods->szCName);
		lpPlayerInfo->SendMsg(szSend);
	}
	else
	{
		szSend.Format("%s %s",SZSHOOT,"你感到無力!!");
		lpPlayerInfo->SendMsg(szSend);
		szSend.Format("%s %d",SZSHOOT,lpPlayerInfo->nOther);
		lpPlayerInfo->SendMsg(szSend);



		return;
	}
	szSend.Format("%s %s %s %d %s",SZSUBGOODS,lpDrug->lpGoods->szCName,"空",1,lpDrug->lpGoods->szUnit);
	lpPlayerInfo->SubGoods(lpDrug->lpGoods->szEName);
	lpPlayerInfo->SendMsg(szSend);
	lpPlayerInfo->SendAllInfo();

}

void CCommandCheck::EscapeProc(char* PlayerName,char* Result,LPVOID pvPlayer,sockaddr_in IPAddr)
{
	CPlayerInfo* lpEscapePlayer = (CPlayerInfo*) pvPlayer;
	CString szMsg;

	EnterCriticalSection(&myglobs.csFightlist);
	if((lpEscapePlayer->nStatus != AOS_kill) )
	{
		szMsg.Format("%s %s %s %s %s",SZESCAPE,lpEscapePlayer->szCName,lpEscapePlayer->szEName, "StatusError", "StatusError2");
		lpEscapePlayer->SendMsg(szMsg);
		LeaveCriticalSection(&myglobs.csFightlist);
		return;
	}else{
		lpEscapePlayer->nEscapeNow = 1;
	}
	LeaveCriticalSection(&myglobs.csFightlist);
}

