#include "stdafx.h"
#include "XmudOS.h"
#include "MainWnd.h"
#include "CommandCheck.h"
#include "Common.h"
#include "hash.h"
#include "wgs\DS_API.h"
#include "hash.h"

extern rmfullglobals myglobs;
extern CList <TClientConData *,TClientConData* >playersocketlist;
extern CList <TDataUser*,TDataUser*>userlist;
extern int	g_iActiveClientNum;

BOOL CCommandCheck::CheckGM(char* UserName)
{
	if(!strcmp(UserName,"nuke")) return TRUE;
	if(!strcmp(UserName,"ankoo")) return TRUE;
	return FALSE;
}

void CCommandCheck::UserLogonCmdProc(char *UserName,sockaddr_in IPAddr,char *stName,char *stPasswd,char *Result)
{
//	TDataUser* lpDataUser;
	TClientConData *lpClientConData;
//	int i,j;
	BOOL bFindUserCount = FALSE;
	char szTest[256];
	POSITION pos, lastpos;
	char szPath[256], szFile[256], szBuf[DSBUFSIZE];
	int nTest, nPlayer;
	CCmdPlayerLogon m_PlayerLogon;

	// Spock start: Beta test
	if(!CheckGM(stName) && (BETA == 1)) {
		strcpy(Result, "FAIL 此伺服器未開啟，請選其他伺服器");
		AddRecordMsg(Result);
		return;
	}
	// 限制進入人數
	if ((g_iActiveClientNum > myglobs.g_ClientNum) && !CheckGM(stName)) {
		strcpy(Result, "FAIL 此伺服器玩家人數已滿");
		AddRecordMsg(Result);
		return;
	}
	// 檢查相同Server重覆Login
	EnterCriticalSection(&myglobs.csPlayerSocket);
	pos = playersocketlist.GetHeadPosition();
	while (pos) {
		lastpos = pos;
		lpClientConData = playersocketlist.GetNext(pos);
		if (!strcmp(stName, lpClientConData->szUserCountName)) {
			shutdown(lpClientConData->hClientSock,2);
			closesocket(lpClientConData->hClientSock);
			bFindUserCount = TRUE;
			break;
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerSocket);
	if (bFindUserCount) {
		sprintf(szTest,"ERROR (,%s) User ReEnter",stName);
		AddRecordMsg(szTest);
		ReturnResult(szUserAccountReEnterErrMsg)
	}
	// 檢查重覆Login
	nTest = UserStartCheck(stName);
	if (nTest <= 0) {
		sprintf(szTest, "ERROR (%s) Invalid login in UserLogonCmdProc, err=%d",
			stName, nTest);
		AddRecordMsg(szTest);
		if (nTest == INVALIDLOG)
			sprintf(Result, "FAIL 同一使用者已在線上，如果是您上次登入的伺服器已當機，\
				您的帳號將被暫時鎖住，請等%d分鐘後再試", STARTLOGGAP/60+SAFELOGGAP);
		else
			sprintf(Result, "FAIL %s", szSystemErrMsg);
		return;
	}
	nTest = UserStartLog(stName);
	if (nTest <= 0) {
		sprintf(szTest, "ERROR (%s) Send startlog fail in UserLogonCmdProc, err=%d",
			stName, nTest);
		AddRecordMsg(szTest);
		sprintf(Result, "FAIL %s", szSystemErrMsg);
		return;
	}
	strcpy(UserName, stName);
	szHashName(stName, szPath);
	sprintf(szFile, "%s.sav", stName);
	nPlayer = nGetPlayerNumber(stName, szPath, szFile);
	if (nPlayer >= 0) { // File exists
		nTest = GetPlayers(stName, szPath, szFile, szBuf);
		if (nTest <= 0) {
			strcpy(Result,"FAIL ");
			strcat(Result,szPlayerRecordErrMsg);
			sprintf(szTest,"ERROR (,%s) Read %s fail, err=%d",stName,szFile,nTest);
			AddRecordMsg(szTest);
		} else {
			sprintf(Result,"OK %d\t%s ",nPlayer,szBuf);
		}
	} else if (nPlayer == DS_FILE_NOT_EXIST) { // New user
		strcpy(Result,"OK 0\t ");
	} else { // Data server error
		strcpy(Result,"FAIL ");
		strcat(Result,szPlayerRecordErrMsg);
		sprintf(szTest,"ERROR (,%s) Read %s fail, err=%d",stName,szFile,nPlayer);
		AddRecordMsg(szTest);
	}
}

