// Fight.cpp: implementation of the CFight class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmudOS.h"
#include "MainWnd.h"
#include "CmdPlayerLogon.h"
#include "Fight.h"
#include "map\MapInfo.h"
#include "npc\Npc.h"
#include "Common.h"
#include "hash.h"

extern rmfullglobals myglobs;
extern char g_tszPathName[256];
extern int	g_iActiveClientNum;
extern CList <TClientConData *,TClientConData* >playersocketlist;
extern CList <CBaseMap*,CBaseMap*>maplist;
extern CList <CFight*,CFight*>killlist;
extern CList <CFight*,CFight*>fightlist;
// Spock start
extern void GetPlayerTitle(CPlayerInfo *lpPlayerInfo);
#define CSWAIT 2
#define HBWAIT 5
// Spock end

//////////////////////////////////////////////////////////////////////
static void DoHeartBeat();
//////////////////////////////////////////////////////////////////////

BOOL CMainWnd::CreateHeartBeatThread()
{
	char szTemp[256];
	sprintf(szTemp, "Begin Fight Thread...");
	AddRecordMsg(szTemp);
	DWORD ThreadId;
	myglobs.hHeartBeatThreadHandle = CreateThread (NULL,0,HeartBeatThread,NULL,0,&ThreadId);
	if (!myglobs.hHeartBeatThreadHandle)
	{
		AfxMessageBox(_T("Create Fight Thread Failed"));
		return FALSE;
	}
	return TRUE;
}

// Spock start
DWORD WINAPI HeartBeatThread (LPVOID WorkContext)
{
	CFight m_Fight;
	unsigned int timeStart;
	int time = 0;
	char szT[256], szFile[256];
	static char StartTime[256]={""};
	CTime Now;
	Now=CTime::GetCurrentTime();
	sprintf( StartTime,"%s", Now.Format("%m/%d/%H"));
	//優先權非常高!
	SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_TIME_CRITICAL);
	//在系統啟動後,等待完成各種初始化後,直到玩家(& Npc)需要心跳的時候再開始這個線程
	while(!myglobs.bRun) Sleep(1000);
	while(myglobs.bRun)	{
		timeStart = GetTickCount();
		if( myglobs.nRunTimes > 100000 && myglobs.bShutdown == FALSE)	{ //andy_add
			myglobs.nRunTimes=0;
			myglobs.nMothRumTimes ++;
			if( myglobs.nMothRumTimes > 1000000 )	{
				myglobs.nMothRumTimes = 0;
				myglobs.bShutdown = TRUE;
				myglobs.nRunTimes=20;
			}
		}
		sprintf(szT,"HeartBeat %d|%d=%d Start %s",
			myglobs.nMothRumTimes, myglobs.nRunTimes, time-100, StartTime);
		AddRecordMsg(szT);
		DoHeartBeat();
		Sleep(100);

		m_Fight.DoKillProc();
		m_Fight.DoFightProc();

		if (myglobs.bShutdown) {
			myglobs.nRunTimes--;
			if (myglobs.nRunTimes <= 0) {
				myglobs.bRun = FALSE;
				myglobs.nRunTimes = 0;
				break;
			}
		} else {
			myglobs.nRunTimes++;
			if ((myglobs.nRunTimes%3600 == 0)) {
				Now=CTime::GetCurrentTime();
				EnterCriticalSection(&myglobs.csRecordMsg);
				fclose(myglobs.flog);
				sprintf(szFile,"%s\\log\\Info%s.log", g_tszPathName, Now.Format("%Y%m%d%H"));
				myglobs.flog = fopen(szFile,"a");
				if (myglobs.flog == NULL) {
					AfxMessageBox(_T("Open Infolog file fail"));
					break;
				} else fprintf(myglobs.flog, "Emprise Server Continued!\n");
				LeaveCriticalSection(&myglobs.csRecordMsg);
			}

		}
		time = GetTickCount() - timeStart;
		if(time < 0) time = 0;
		if(time > 800) time = 800; // 至少Sleep(200)
		Sleep(1000 - time);
	}
	time = 0;
	while ((g_iActiveClientNum > 0) && (time < 300)) {
		sprintf(szT, "HeartBeat Paused, Closing server!");
		AddRecordMsg(szT);
		Sleep(1000);
		time++;
	}
	sprintf(szT, "HeartBeat Stopped!");
	AddRecordMsg(szT);
	Sleep(1000);

	sprintf(szT, "Emprise HeartBeat Thread End");
	AddRecordMsg(szT);
	PostMessage(myglobs.hWndMain,WM_CLOSE,0,0);
	return 0;
}
// Spock end

void DoHeartBeat()
{
	TClientConData * lpCurData;
	CPlayerInfo * lpPlayer;
	POSITION pos, lastpos;
	char szTxt[256];
/*
	char Times[256];
	CTime Now;
	Now=CTime::GetCurrentTime();
	sprintf( Times,"SYSTEM DoHeartBeat Time");
	AddRecordMsg(Times);
*/
	EnterCriticalSection(&myglobs.csPlayerSocket);
	pos = playersocketlist.GetHeadPosition();
	while(pos != NULL)	{
		lastpos = pos;
		lpCurData = playersocketlist.GetNext(pos);
		// Spock start
		if(lpCurData == NULL) {
			playersocketlist.RemoveAt(lastpos);
			sprintf(szTxt, "ERROR NULL pointer in DoHeartBeat, lpCurData");
			AddRecordMsg(szTxt);
			continue;
		}
		if(strcmp(lpCurData->szCheck, SZCONCHECK)) {
			playersocketlist.RemoveAt(lastpos);
			sprintf(szTxt, "ERROR Bad data in DoHeartBeat, lpCurData");
			AddRecordMsg(szTxt);
			continue;
		}
		lpPlayer = (CPlayerInfo *)lpCurData->pvPlayer;
		if(lpPlayer == NULL) {
			continue;
		}
		if(strcmp(lpPlayer->szCheck, SZAOBJCHECK)) {
			playersocketlist.RemoveAt(lastpos);
			sprintf(szTxt, "ERROR Bad data in DoHeartBeat, lpCurData->lpPlayer");
			AddRecordMsg(szTxt);
			continue;
		}
		// Spock end
		if (myglobs.bShutdown ) {
			sprintf(szTxt, "%s (255,255,255)系統公告：伺服器將於%d秒內關機，請迅速離線，以免進度流失",
				szShoutToAll, myglobs.nRunTimes);
			if( myglobs.nRunTimes == 80 || myglobs.nRunTimes == 60 || myglobs.nRunTimes < 30 )	{
				if( myglobs.nRunTimes % 5 == 0 )
					lpPlayer->SendMsg(szTxt);
			}
		}
		lpPlayer->DoHeartBeat();
	}
	LeaveCriticalSection(&myglobs.csPlayerSocket);
	return;
}

CFight::CFight()
{
	lpActiveObject = NULL;
	iRound = 25;
	nDelay = 1;
}

CFight::~CFight()
{
}

//報告某人的狀態的各項變化值
void CActiveObject::ReportStatusNum()
{
	CString szStatus;
	TObjectSkill * lpTSAttack = GetTSkill(GetAttackBaseSkill());
	TObjectSkill * lpTSDodge = GetTSkill("BaseDodge");
	TObjectSkill * lpTSParry = GetTSkill("BaseParry");

	szStatus.Format("%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%s,%d,%d,%s,%d,%d",
		nCombat_exp,
		nQianNeng,
		nEff_qi,
		nMax_qi,
		nEff_jing,
		nEff_force,
		nEff_jingli,
		lpTSAttack->lpSkill->szEName,
		lpTSAttack->nScore,
		lpTSAttack->nLevel,

		lpTSDodge->lpSkill->szEName,
		lpTSDodge->nScore,
		lpTSDodge->nLevel,

		lpTSParry->lpSkill->szEName,
		lpTSParry->nScore,
		lpTSParry->nLevel);
	szStatus = CString(SZFIGHTDATA) + (" ") + szStatus;
/*	while(1)
	{
		ProcessMessage();
		if(SendMsg(szStatus))
			break;
	}
*/
	SendMsg(szStatus);
}

void FightMsg(CString msg, CActiveObject *me, CActiveObject *you)
{
	POSITION pos;
	CActiveObject * lpAObj;
	CString szSend;
	szSend = msg;
	szSend.Replace("$N",me->szCName);
	szSend.Replace("$n",you->szCName);
	pos = me->listfightopp.GetHeadPosition();
	while (pos != NULL) {
		lpAObj = me->listfightopp.GetNext(pos);
		lpAObj->SendMsg(szSend);
	}
	pos = you->listfightopp.GetHeadPosition();
	while (pos != NULL) {
		lpAObj = you->listfightopp.GetNext(pos);
		lpAObj->SendMsg(szSend);
	}
}

void CFight::DoKillProc()
{
	CActiveObject *lpActiveOppObject;
	CActiveObject *lpAOThis;
	CFight *lpFight;
	int nCount,nRet;
	CString szResult;
	POSITION FightPos, LastFightPos;
	POSITION oppPos, lastOppPos, oppPos2, lastOppPos2;
	// Spock +1
	CString szMsg;

	EnterCriticalSection(&myglobs.csFightlist);
	FightPos = killlist.GetHeadPosition();
	while(FightPos != NULL)
	{
		LastFightPos = FightPos;
		lpFight = killlist.GetNext(FightPos);
		// Spock start: 檢查 NULL pointer and bad data
		if(lpFight == NULL) {
			killlist.RemoveAt(LastFightPos);
			AddRecordMsg("ERROR NULL pointer, DoKillProc, killlist.lpFight");
			break;
		}
		if (lpFight->lpActiveObject == NULL) {
			killlist.RemoveAt(LastFightPos);
			delete lpFight;
			AddRecordMsg("ERROR NULL pointer, DoKillProc, killlist.lpFight->lpActiveObject");
			break;
		}
		if (strcmp(lpFight->lpActiveObject->szCheck,SZAOBJCHECK)) {
			killlist.RemoveAt(LastFightPos);
			delete lpFight;
			AddRecordMsg("ERROR Bad data, DoKillProc, killlist.lpFight->lpActiveObject");
			break;
		}
		// Spock end
		if (lpFight->nDelay > 0) {
			lpFight->nDelay--;
			continue;
		}
		nCount = lpFight->lpActiveObject->listfightopp.GetCount();
		//刪除停止格斗中的人物
		if((nCount==0) || (lpFight->lpActiveObject->nMax_qi <= 0 )|| ((lpFight->iRound-=1) <=0))
		{
			//刪除這個人的格斗對象鏈表
			if(lpFight->lpActiveObject->nMax_qi <= 0 ) {
				oppPos = lpFight->lpActiveObject->listfightopp.GetHeadPosition();
				while(oppPos != NULL) {//找到和他格斗的所有的人
					// Spock +1
					lastOppPos = oppPos;
					lpActiveOppObject = lpFight->lpActiveObject->listfightopp.GetNext(oppPos);
					// Spock start: Check NULL and bad data
					if (lpActiveOppObject == NULL) {
						lpFight->lpActiveObject->listfightopp.RemoveAt(lastOppPos);
						AddRecordMsg("ERROR NULL pointer, DoKillProc, lpActiveOppObject");
						continue;
					}
					if (strcmp(lpActiveOppObject->szCheck,SZAOBJCHECK)) {
						lpFight->lpActiveObject->listfightopp.RemoveAt(lastOppPos);
						AddRecordMsg("ERROR Bad data, DoKillProc, lpActiveOppObject");
						break;
					}
					// Spock end
					oppPos2 = lpActiveOppObject->listfightopp.GetHeadPosition();
					while(oppPos2 != NULL) {
						lastOppPos2 = oppPos2;
						lpAOThis = lpActiveOppObject->listfightopp.GetNext(oppPos2);
						// 檢查 NULL pointer
						if (lpAOThis == NULL) {
							lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
							AddRecordMsg("ERROR NULL pointer, DoKillProc, listfightopp.lpAOThis");
							continue;
						}
						if (strcmp(lpAOThis->szCheck,SZAOBJCHECK)) {
							lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
							AddRecordMsg("ERROR Bad data, DoKillProc, listfightopp.lpAOThis");
							continue;
						}
						// Check end
						if (lpAOThis == lpFight->lpActiveObject) {
							//把這個人的對象鏈表中的"我"刪除
							lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
							break;
						}
					}
				}
				lpFight->lpActiveObject->listfightopp.RemoveAll();
				lpFight->lpActiveObject->Die();

			}
//cary
			else if(lpFight->iRound <=0)
			{
				oppPos = lpFight->lpActiveObject->listfightopp.GetHeadPosition();
				while(oppPos != NULL)
				{//找到和他格斗的所有的人
					lastOppPos=oppPos;
					lpActiveOppObject = lpFight->lpActiveObject->listfightopp.GetNext(oppPos);
					// Spock start: Check NULL and bad data
					if (lpActiveOppObject == NULL) {
						lpFight->lpActiveObject->listfightopp.RemoveAt(lastOppPos);
						AddRecordMsg("ERROR NULL pointer, DoKillProc, lpActiveOppObject");
						continue;
					}
					if (strcmp(lpActiveOppObject->szCheck,SZAOBJCHECK)) {
						lpFight->lpActiveObject->listfightopp.RemoveAt(lastOppPos);
						AddRecordMsg("ERROR Bad data, DoKillProc, lpActiveOppObject");
						continue;
					}
					// Spock end
					oppPos2 = lpActiveOppObject->listfightopp.GetHeadPosition();
					while(oppPos2 != NULL)
					{
						lastOppPos2 = oppPos2;
						lpAOThis = lpActiveOppObject->listfightopp.GetNext(oppPos2);
						// 檢查 NULL pointer
						if (lpAOThis == NULL) {
							lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
							AddRecordMsg("ERROR NULL pointer, DoKillProc, listfightopp.lpAOThis");
							continue;
						}
						if (strcmp(lpAOThis->szCheck,SZAOBJCHECK)) {
							lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
							AddRecordMsg("ERROR Bad data, DoKillProc, listfightopp.lpAOThis");
							continue;
						}
						// Check end
						if(lpAOThis == lpFight->lpActiveObject)
						{
							//把這個人的對象鏈表中的"我"刪除
							lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
							break;
						}
					}
				}
				CString szTmp;
				szTmp.Format("%s %s %s %s",SZKILLOVER,szRedHigt,lpFight->lpActiveObject->szCName,lpFight->lpActiveObject->szEName);
				MapMessage(szTmp, lpFight->lpActiveObject);
				lpFight->lpActiveObject->listfightopp.RemoveAll();
				lpFight->lpActiveObject->bNoHealing=FALSE;
				lpFight->lpActiveObject->nStatus = AOS_none;
			}
			else
			{
				lpFight->lpActiveObject->bNoHealing=FALSE;
				lpFight->lpActiveObject->nStatus = AOS_none;
//				lpFight->lpActiveObject->ReportStatusNum();
			}
			// Spock start
			if (lpFight->lpActiveObject->bPlayer) {
				if(lpFight->lpActiveObject->szNickName == "充氣娃娃") {
					lpFight->lpActiveObject->nEff_qi = lpFight->lpActiveObject->nMax_qi
						= lpFight->lpActiveObject->GetMaxQi();
					lpFight->lpActiveObject->nEff_jing = lpFight->lpActiveObject->nMax_jing
						= lpFight->lpActiveObject->GetMaxJing();
				}
				GetPlayerTitle(dynamic_cast<CPlayerInfo*>(lpFight->lpActiveObject));
				dynamic_cast<CPlayerInfo*>(lpFight->lpActiveObject)->bAttack = FALSE;
				dynamic_cast<CPlayerInfo*>(lpFight->lpActiveObject)->SendAllInfo();
			} else {
				lpFight->lpActiveObject->nEff_qi = lpFight->lpActiveObject->nMax_qi
					= lpFight->lpActiveObject->GetMaxQi();
				lpFight->lpActiveObject->nEff_jing = lpFight->lpActiveObject->nMax_jing
					= lpFight->lpActiveObject->GetMaxJing();
			}
			// Spock end
			//在鏈表中刪除這個人
			killlist.RemoveAt(LastFightPos);
			delete lpFight;
			continue;
		}
		if(lpFight->lpActiveObject->nBusy != 0)
			continue;

// guanhua 2000/10/01 start
		CString szTmp2;
		if((lpFight->lpActiveObject->nEscapeNow) == 1){
			CString EscapeMapCName, EscapeMapEName;
			int bRet = DoEscape(lpFight->lpActiveObject, EscapeMapCName, EscapeMapEName);
			if(bRet){
				if(EscapeMapCName == "Cannot"){
					// 逃走失敗

					szMsg.Format("%s %s %s %s %s",SZESCAPE,lpFight->lpActiveObject->szCName,lpFight->lpActiveObject->szEName, "Cannot", "Cannot2");
					lpFight->lpActiveObject->SendMsg(szMsg);
					lpFight->lpActiveObject->SendMsgToAll(szMsg);

					lpFight->lpActiveObject->nBusy += 2;

					lpFight->lpActiveObject->nEscapeNow = 0;
					continue;
				}else{
					// 逃走成功
					oppPos = lpFight->lpActiveObject->listfightopp.GetHeadPosition();
					while(oppPos != NULL){//找到和他格斗的所有的人
						lastOppPos=oppPos;
						lpActiveOppObject = lpFight->lpActiveObject->listfightopp.GetNext(oppPos);
						// Spock start: Check NULL and bad data
						if (lpActiveOppObject == NULL){
							lpFight->lpActiveObject->listfightopp.RemoveAt(lastOppPos);
							AddRecordMsg("ERROR NULL pointer, DoKillProc, lpActiveOppObject");
							continue;
						}
						if (strcmp(lpActiveOppObject->szCheck,SZAOBJCHECK)){
							lpFight->lpActiveObject->listfightopp.RemoveAt(lastOppPos);
							AddRecordMsg("ERROR Bad data, DoKillProc, lpActiveOppObject");
							continue;
						}
							// Spock end
						oppPos2 = lpActiveOppObject->listfightopp.GetHeadPosition();
						while(oppPos2 != NULL)
						{
							lastOppPos2 = oppPos2;
							lpAOThis = lpActiveOppObject->listfightopp.GetNext(oppPos2);
							// 檢查 NULL pointer
							if (lpAOThis == NULL) 
							{
								lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
								AddRecordMsg("ERROR NULL pointer, DoKillProc, listfightopp.lpAOThis");
								continue;
							}
							if (strcmp(lpAOThis->szCheck,SZAOBJCHECK)) {
								lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
								AddRecordMsg("ERROR Bad data, DoKillProc, listfightopp.lpAOThis");
								continue;
							}
							// Check end
							if(lpAOThis == lpFight->lpActiveObject){//把這個人的對象鏈表中的"我"刪除
								lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
								break;
							}
						}
					}
					if(EscapeMapCName == "StayHere"){
						szTmp2.Format("%s %s %s %s %s",SZESCAPE,lpFight->lpActiveObject->szCName,lpFight->lpActiveObject->szEName, "StayHere", "StayHere2");
					}else{
						szTmp2.Format("%s %s %s %s %s",SZESCAPE,lpFight->lpActiveObject->szCName,lpFight->lpActiveObject->szEName, EscapeMapCName, EscapeMapEName);
					}
	
					lpFight->lpActiveObject->listfightopp.RemoveAll();
					lpFight->lpActiveObject->bNoHealing=FALSE;
					lpFight->lpActiveObject->nStatus = AOS_none;
				}
				lpFight->lpActiveObject->SendMsg(szTmp2);
				lpFight->lpActiveObject->SendMsgToAll(szTmp2);
				lpFight->lpActiveObject->nEscapeNow = 0;
				//在鏈表中刪除這個人
				killlist.RemoveAt(LastFightPos);
				delete lpFight;
				continue;
			}
		}
// guanhua 2000/10/01 end
		
		nCount = rand()%nCount;
		lpActiveOppObject = lpFight->lpActiveObject->listfightopp.GetAt(lpFight->lpActiveObject->listfightopp.FindIndex(nCount));
		if(lpActiveOppObject == NULL) {
			AddRecordMsg("ERROR NULL pointer in DoKillProc, lpActiveOppObject");
			continue;
		}
		if(strcmp(lpActiveOppObject->szCheck, SZAOBJCHECK)) {
			AddRecordMsg("ERROR Bad data in DoKillProc, lpActiveOppObject");
			continue;
		}
		if((lpActiveOppObject->nStatus == AOS_dead) || (lpActiveOppObject->nMax_qi <= 0))
			continue;
		//計算格斗
		szMsg.Empty(); // Spock +1
			nRet = DoAttack(lpFight->lpActiveObject, lpActiveOppObject, szResult, szMsg);
		
		if(lpActiveOppObject->bPlayer)
			lpActiveOppObject->ReportStatusNum();
		MapMessage(szResult, lpFight->lpActiveObject, lpActiveOppObject);
//		FightMsg(szResult, lpFight->lpActiveObject, lpActiveOppObject);
		// Spock +1 : 回傳打倒對手所獲金錢
		if (!szMsg.IsEmpty()) lpFight->lpActiveObject->SendMsg(szMsg);
	}
	LeaveCriticalSection(&myglobs.csFightlist);
}
//cary
void CFight::DoFightProc()
{
	CActiveObject *lpActiveOppObject;
	CActiveObject *lpAOThis;
	CFight *lpFight;
	int nCount;
	BOOL bRet;
	CString szResult;
	POSITION FightPos, LastFightPos;
	POSITION oppPos, lastOppPos, oppPos2, lastOppPos2;
	CString szMsg;
	char szTemp[256];

	EnterCriticalSection(&myglobs.csFightlist);
	FightPos = fightlist.GetHeadPosition();
	while(FightPos != NULL)
	{
		LastFightPos = FightPos;
		lpFight = fightlist.GetNext(FightPos);
		// Spock start: 檢查 NULL pointer and bad data
		if(lpFight == NULL) {
			fightlist.RemoveAt(LastFightPos);
			sprintf(szTemp, "ERROR NULL pointer in DoFightProc, lpFight");
			AddRecordMsg(szTemp);
			break;
		}
		if (lpFight->lpActiveObject == NULL) {
			fightlist.RemoveAt(LastFightPos);
			delete lpFight;
			sprintf(szTemp, "ERROR NULL pointer in DoFightProc, lpFight->lpActiveObject");
			AddRecordMsg(szTemp);
			break;
		}
		if (strcmp(lpFight->lpActiveObject->szCheck,SZAOBJCHECK)) {
			fightlist.RemoveAt(LastFightPos);
			delete lpFight;
			sprintf(szTemp, "ERROR Bad data, DoFightProc, fightlist.lpFight->lpActiveObject");
			AddRecordMsg(szTemp);
			break;
		}
		// Spock end
		if (lpFight->nDelay > 0) {
			lpFight->nDelay--;
			continue;
		}
		nCount = lpFight->lpActiveObject->listfightopp.GetCount();
		//刪除停止格斗中的人物
		if((nCount==0) || (lpFight->lpActiveObject->nEff_qi <= 0 ) || ((lpFight->iRound-=1) <=0))
		{
			//刪除這個人的格斗對象鏈表
			if((lpFight->lpActiveObject->nEff_qi <= 0 )||(lpFight->iRound <=0))
			{
				if(lpFight->lpActiveObject->nEff_qi<=0)
				{
					lpFight->lpActiveObject->nEff_qi=1;
				}
				oppPos = lpFight->lpActiveObject->listfightopp.GetHeadPosition();
				while(oppPos != NULL)
				{//找到和他格斗的所有的人
					lastOppPos = oppPos;
					lpActiveOppObject = lpFight->lpActiveObject->listfightopp.GetNext(oppPos);
					// Spock start: Check NULL and bad data
					if (lpActiveOppObject == NULL) {
						lpFight->lpActiveObject->listfightopp.RemoveAt(lastOppPos);
						sprintf(szTemp, "ERROR NULL pointer, DoFightProc, lpActiveOppObject");
						AddRecordMsg(szTemp);
						continue;
					}
					if (strcmp(lpActiveOppObject->szCheck,SZAOBJCHECK)) {
						lpFight->lpActiveObject->listfightopp.RemoveAt(lastOppPos);
						sprintf(szTemp, "ERROR Bad data, DoFightProc, lpActiveOppObject");
						AddRecordMsg(szTemp);
						continue;
					}
					// Spock end
					oppPos2 = lpActiveOppObject->listfightopp.GetHeadPosition();
					while(oppPos2 != NULL)
					{
						lastOppPos2 = oppPos2;
						lpAOThis = lpActiveOppObject->listfightopp.GetNext(oppPos2);
						// 檢查 NULL pointer
						if (lpAOThis == NULL) {
							lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
							sprintf(szTemp, "ERROR NULL pointer, DoFightProc, listfightopp.lpAOThis");
							AddRecordMsg(szTemp);
							continue;
						}
						if (strcmp(lpAOThis->szCheck,SZAOBJCHECK)) {
							lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
							AddRecordMsg("ERROR Bad data, DoFightProc, listfightopp.lpAOThis");
							continue;
						}
						// Check end
						if(lpAOThis == lpFight->lpActiveObject)
						{
							//把這個人的對象鏈表中的"我"刪除
							lpActiveOppObject->listfightopp.RemoveAt(lastOppPos2);
							break;
						}
					}
				}
				CString szTmp;
				szTmp.Format("%s %s %s %s",SZFIGHTOVER,szRedHigt,lpFight->lpActiveObject->szCName,lpFight->lpActiveObject->szEName);
				MapMessage(szTmp, lpFight->lpActiveObject);
				lpFight->lpActiveObject->listfightopp.RemoveAll();
			}
			lpFight->lpActiveObject->bNoHealing=FALSE;
			lpFight->lpActiveObject->nStatus = AOS_none;
			if (lpFight->lpActiveObject->bPlayer) {
				if(lpFight->lpActiveObject->szNickName == "充氣娃娃") {
					lpFight->lpActiveObject->nEff_qi = lpFight->lpActiveObject->nMax_qi;
					lpFight->lpActiveObject->nEff_jing = lpFight->lpActiveObject->nMax_jing;
				}
				GetPlayerTitle(dynamic_cast<CPlayerInfo*>(lpFight->lpActiveObject));
				dynamic_cast<CPlayerInfo*>(lpFight->lpActiveObject)->SendAllInfo();
			} else {
				lpFight->lpActiveObject->nEff_qi = lpFight->lpActiveObject->nMax_qi;
				lpFight->lpActiveObject->nEff_jing = lpFight->lpActiveObject->nMax_jing;
			}
			//在鏈表中刪除這個人
			fightlist.RemoveAt(LastFightPos);
			delete lpFight;
			continue;
		}
		if(lpFight->lpActiveObject->nBusy != 0)
			continue;
		nCount = rand()%nCount;
		lpActiveOppObject = lpFight->lpActiveObject->listfightopp.GetAt(lpFight->lpActiveObject->listfightopp.FindIndex(nCount));
		if(lpActiveOppObject->nEff_qi <= 0)
			continue;
		//計算格斗
		szMsg.Empty(); // Spock +1
		bRet = DoAttack(lpFight->lpActiveObject, lpActiveOppObject, szResult, szMsg);
		if(lpActiveOppObject->bPlayer)
			lpActiveOppObject->ReportStatusNum();
		if(bRet) MapMessage(szResult, lpFight->lpActiveObject, lpActiveOppObject);
//		FightMsg(szResult, lpFight->lpActiveObject, lpActiveOppObject);
		// Spock +1 : 回傳打倒對手所獲金錢
		if (!szMsg.IsEmpty()) lpFight->lpActiveObject->SendMsg(szMsg);
	}
	LeaveCriticalSection(&myglobs.csFightlist);
}
