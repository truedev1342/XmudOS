#include "stdafx.h"
#include "XmudOS.h"
#include "config.h"
#include "MainWnd.h"
#include "CommandCheck.h"
#include "map\MapInfo.h"
#include "Common.h"
#include "wgs\common.h"
#include <winsock.h>
// Nuke +2
#include <direct.h>
#include "hash.h"

// Spock start
#define PROBETIME 200  // 單位：100ms
//#define SENDSTARTTIME 1800
// Spock end

extern char g_tszPathName[256];
extern int	g_iActiveClientNum;

extern rmfullglobals myglobs;
extern CList <TClientConData *,TClientConData* >playersocketlist;
extern CList <CBaseMap*,CBaseMap*>maplist;
SOCKET hPlayerServerSock = INVALID_SOCKET; //Listening socket

BOOL CMainWnd::CreatePlayerThread()
{
	AddRecordMsg("Begin Player Server Thread...");
	DWORD ThreadId;
	myglobs.hPlayerServerThreadHandle = CreateThread (NULL,0,PlayerServerThread,NULL,0,&ThreadId);
	if (!myglobs.hPlayerServerThreadHandle)
	{
		AfxMessageBox(_T("Create Player Server Thread Failed"));
		return FALSE;
	}
	return TRUE;
}

DWORD WINAPI PlayerServerThread (LPVOID WorkContext)
{
	SOCKADDR_IN stLocalName;           // Local address and port number
	TClientConData * lpClientConData;
	int Ret, nLen;
	DWORD ThreadId;
	HANDLE ThreadHandle;
	
	SetThreadPriority (GetCurrentThread(), THREAD_PRIORITY_NORMAL);
	// Spock +1
	srand((unsigned)time(NULL));

	ClearUserLog();
	hPlayerServerSock = socket (AF_INET, SOCK_STREAM, 0);
	if (hPlayerServerSock == INVALID_SOCKET) 
	{
		AfxMessageBox(_T("Player Server socket() Failed!"));
		exit(1);
	}

	ZeroMemory (&stLocalName, sizeof (stLocalName));
	stLocalName.sin_family = PF_INET;
	stLocalName.sin_port   = (u_short) htons((u_short)PlayerPort);  
 
	Ret = bind(hPlayerServerSock,(sockaddr *)&stLocalName,sizeof(stLocalName));
	if (Ret == SOCKET_ERROR) 
	{
		AfxMessageBox(_T("Player Server bind() Failed!"));
		closesocket(hPlayerServerSock); 
		exit(1);
	}
	Ret = listen(hPlayerServerSock, 5);
	if (Ret == SOCKET_ERROR)
	{
		AfxMessageBox(_T("Player Server listen() Failed!"));
		closesocket(hPlayerServerSock); 
		exit(1);
	}
	//開始玩家接收線程
	myglobs.bRun = TRUE;
	while(myglobs.bRun)
	{
		lpClientConData = new TClientConData;
		if( lpClientConData != NULL )
		{
			// Spock start
			strcpy(lpClientConData->szCheck, SZCONCHECK);
			// Spock end
			nLen = sizeof(sockaddr);
			///accept()
			lpClientConData->hClientSock = accept(hPlayerServerSock,(sockaddr *)&(lpClientConData->stRemoteName),&nLen);
			if (lpClientConData->hClientSock == INVALID_SOCKET)
			{
				delete (lpClientConData);
				Ret = WSAGetLastError();
				if(Ret == WSAENOTSOCK)
				{
//					AfxMessageBox(_T("Player Server accept() Failed!"));
					AddRecordMsg("ERROR Player Server: Stop!");
					PostMessage(myglobs.hWndMain,WM_CLOSE,0,0);
					return 1;
				}
			}
			else
			{
				//cary
				BOOL bNoDelay=TRUE;
				int nRet=setsockopt(lpClientConData->hClientSock,IPPROTO_TCP,TCP_NODELAY,(char *)&bNoDelay,sizeof(BOOL));
				//end
				CTime CurrentTime=CTime::GetCurrentTime();
				lpClientConData->LastConnectTime = CurrentTime;
				CString sCurrenttime = CurrentTime.Format( "%H:%M:%S" );

				wsprintf(myglobs.szBuffer,"Player Server: %s (%s) client connected!",
					inet_ntoa(lpClientConData->stRemoteName.sin_addr),sCurrenttime);
				AddRecordMsg(myglobs.szBuffer);

				// Spock +1
				lpClientConData->nVer = rand()%9999999;
				//開始新的玩家線程
				ThreadHandle = CreateThread (
										NULL,
										0,
										PlayerThread,
										lpClientConData,
										0,
										&ThreadId);
				if (ThreadHandle) {
					SetThreadPriority(ThreadHandle, THREAD_PRIORITY_NORMAL);
					CloseHandle (ThreadHandle);
				} else {
					AddRecordMsg("ERROR Create Player Thread Failed");
				}
			}//end of accept
		}//end of GlobalAlloc
	}//<End of for(;;) >
	AddRecordMsg("PlayerServer Thread End");
	return (0);
}

DWORD WINAPI PlayerSendThread (LPVOID WorkContext)
{
	CCmdPlayerLogon m_CmdPlayerLogon;
	CPlayerInfo *lpPlayerInfo;
	CStringList listSendMsg;
	POSITION pos;
	CString szMsg;
	int nRet, nRunTimes=0;
	int nLogCount=0, nLogCountOld=0, nSaveCount=0, nSaveCountOld=0, nRetry=0;
	BOOL bEmptyMsg = FALSE;
	char szTest[256];

	lpPlayerInfo = (CPlayerInfo*)WorkContext;
	szMsg.Format("(%s,%s) PlayerSendThread start",
		lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
	AddRecordMsg((char*)(LPCSTR)szMsg);
	while(lpPlayerInfo->bRun){
		Sleep(100);
		if (!myglobs.bRun && (nRunTimes >= 0)) {
			szMsg.Format("(%s,%s) Shutdown socket while closing server",
				lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
			AddRecordMsg((char*)(LPCSTR)szMsg);
			shutdown(lpPlayerInfo->hPlayerSocket,2);
			closesocket(lpPlayerInfo->hPlayerSocket);
			nRunTimes = -1;
			continue;
		}
		if (nRunTimes >= 0) {
			nLogCount = lpPlayerInfo->nRound/STARTLOGGAP;
			nSaveCount = lpPlayerInfo->nRound/SAVEGAP;

			if (nLogCount > nLogCountOld) {
				nLogCountOld = nLogCount;
				nRet = CheckUserLog((char*)(LPCSTR)lpPlayerInfo->szUserName);
				if (nRet <= 0) {
					szMsg.Format("ERROR (%s,%s) Invalid login in PlayerSendThread, err=%d",
						lpPlayerInfo->szEName, lpPlayerInfo->szUserName, nRet);
					AddRecordMsg((char*)(LPCSTR)szMsg);
					if (nRet == INVALIDLOG)
						szMsg.Format("FAIL %s", szInvalidLogin);
					else
						szMsg.Format("FAIL %s", szSystemErrMsg);
					Send(lpPlayerInfo->hPlayerSocket, szMsg);
					Sleep(5000);
					shutdown(lpPlayerInfo->hPlayerSocket,2);
					closesocket(lpPlayerInfo->hPlayerSocket);
					nRunTimes = -1;
				} else {
					nRet = UserStartLog((char*)(LPCSTR)lpPlayerInfo->szUserName);
					if (nRet <= 0) {
						szMsg.Format("ERROR (%s,%s) Send startlog fail in PlayerSendThread, err=%d",
							lpPlayerInfo->szEName, lpPlayerInfo->szUserName, nRet);
						AddRecordMsg((char*)(LPCSTR)szMsg);
						szMsg.Format("FAIL %s", szSystemErrMsg);
						Send(lpPlayerInfo->hPlayerSocket, szMsg);
						Sleep(5000);
						shutdown(lpPlayerInfo->hPlayerSocket,2);
						closesocket(lpPlayerInfo->hPlayerSocket);
						nRunTimes = -1;
					} else {
						szMsg.Format("(%s,%s) Send startlog OK",
							lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
						AddRecordMsg((char*)(LPCSTR)szMsg);
					}
				}
			}
			// 儲存玩家資料
			if((lpPlayerInfo->nRound > SAVEWAIT) && lpPlayerInfo->bSaved
				&& !lpPlayerInfo->bNoHealing && (nRunTimes >= 0)) {
				sprintf(szTest,"%s AUTO",SZSAVE);
				lpPlayerInfo->SendMsg(szTest);
				lpPlayerInfo->bSaved = FALSE;
			}
			if((nSaveCount > nSaveCountOld) && (nRunTimes >= 0)) {
				nRet = m_CmdPlayerLogon.SavePlayerData(lpPlayerInfo);
				if (nRet <= 0) {
					nRetry++;
					if (nRetry > SAVERETRY) {
						sprintf(szTest,"ERROR (%s,%s) SavePlayerData Error=%d, aborted!"
							,lpPlayerInfo->szEName, lpPlayerInfo->szUserName,
							nRet, nRetry);
						AddRecordMsg(szTest);
						sprintf(szTest,"FAIL %s", szDiskWriteErrMsg);
						Send(lpPlayerInfo->hPlayerSocket, szTest);
						Sleep(5000);
						shutdown(lpPlayerInfo->hPlayerSocket,2);
						closesocket(lpPlayerInfo->hPlayerSocket);
						nRunTimes = -1;
						continue;
					} else {
						lpPlayerInfo->nRound -= RETRYGAP;
						sprintf(szTest,"ERROR (%s,%s) SavePlayerData Error=%d Retry=%d"
							,lpPlayerInfo->szEName, lpPlayerInfo->szUserName,
							nRet, nRetry);
						AddRecordMsg(szTest);
					}
				} else {
					nRetry = 0;
					nSaveCountOld = nSaveCount;
					sprintf(szTest,"(%s,%s) SavePlayerData OK!",
						lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
					AddRecordMsg(szTest);
					sprintf(szTest,"%s MANUAL",SZSAVE);
					lpPlayerInfo->SendMsg(szTest);
					lpPlayerInfo->bSaved = TRUE;
				}
			}
		}
		if(nRunTimes >= 0){
			EnterCriticalSection(&myglobs.csSentCliMsg);
			if(lpPlayerInfo->nStatus == AOS_changemap){
				if(lpPlayerInfo->listmsg.GetCount() > 0){							
					listSendMsg.AddHead(lpPlayerInfo->listmsg.GetHead());
					lpPlayerInfo->nStatus = AOS_changemapok;
					nRunTimes = 0;	
					lpPlayerInfo->listmsg.RemoveHead();
					bEmptyMsg = FALSE;
				}else{
					szMsg.Format("ERROR (%s,%s) Empty message in change map",
						lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
					AddRecordMsg((char*)(LPCSTR)szMsg);
					bEmptyMsg = TRUE;
				}
			}else if(lpPlayerInfo->nStatus == AOS_sendmap){
				if(lpPlayerInfo->listmsg.GetCount() > 0){
					listSendMsg.AddHead(lpPlayerInfo->listmsg.GetHead());
					lpPlayerInfo->nStatus = AOS_sendmapok;
					nRunTimes = 0;	
					lpPlayerInfo->listmsg.RemoveHead();
					bEmptyMsg = FALSE;
				}else {
					szMsg.Format("ERROR (%s,%s) Empty message in send map",
						lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
					AddRecordMsg((char*)(LPCSTR)szMsg);
					bEmptyMsg = TRUE;
				}
			}
			else if((lpPlayerInfo->nStatus != AOS_changemapok) &&
					(lpPlayerInfo->nStatus != AOS_sendmapok)){
				if(lpPlayerInfo->listmsg.GetCount() > 0){
					pos = lpPlayerInfo->listmsg.GetHeadPosition();
					while (pos){			
						listSendMsg.AddTail(lpPlayerInfo->listmsg.GetNext(pos));
					}
					lpPlayerInfo->listmsg.RemoveAll();
					nRunTimes = 0;	
					bEmptyMsg = FALSE;
				}
			}
			LeaveCriticalSection(&myglobs.csSentCliMsg);
			if(bEmptyMsg){
				szMsg.Format("ERROR (%s,%s) Shutdown socket in PlayerSendThread",
					lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
				AddRecordMsg((char*)(LPCSTR)szMsg);
				shutdown(lpPlayerInfo->hPlayerSocket,2);
				closesocket(lpPlayerInfo->hPlayerSocket);
				nRunTimes = -1;
			}else{
				if(listSendMsg.GetCount() == 0){
					nRunTimes++;
					if (nRunTimes > PROBETIME){
						listSendMsg.AddTail("$");
						szMsg.Format("(%s,%s) Send probe message",
							lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
						AddRecordMsg((char*)(LPCSTR)szMsg);
						nRunTimes = 0;
					}
				}
			
				pos = listSendMsg.GetHeadPosition();
				while (pos){
					szMsg = listSendMsg.GetNext(pos);
					nRet = Send(lpPlayerInfo->hPlayerSocket, szMsg);
					if ((nRet==0)||(nRet==SOCKET_ERROR)) 
					{
						szMsg.Format("ERROR (%s,%s) Shutdown socket in PlayerSendThread",
							lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
						AddRecordMsg((char*)(LPCSTR)szMsg);
						shutdown(lpPlayerInfo->hPlayerSocket,2);
						closesocket(lpPlayerInfo->hPlayerSocket);
						nRunTimes = -1;
						break;
					}
				}
				listSendMsg.RemoveAll();
			}
			
		}
	}
	//dainty end 2000/7/20
	szMsg.Format("(%s,%s) PlayerSendThread end",
		lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
	AddRecordMsg((char*)(LPCSTR)szMsg);
	delete lpPlayerInfo;
	listSendMsg.RemoveAll();
	return 0;
}


int ProcessOneCom(BOOL &bUserLogon, BOOL &bPlayerLogon, TClientConData * lpClientConData, char * UserName, char * PlayerName, char * Buf2);

DWORD WINAPI PlayerThread (LPVOID WorkContext)
{
	TClientConData * lpClientConData;
	CCmdPlayerLogon m_CmdPlayerLogon;

	char			Buf[PLAYERBUFFERSIZE];
	char			*Buf2;
	int				RetR,RetS,comlen;
	char			UserName[ENGLISHNAMELENGTH];
	char			PlayerName[ENGLISHNAMELENGTH];
	BOOL			bUserLogon = FALSE;
	BOOL			bPlayerLogon = FALSE;
	char			szCOMPARM[2] = "\27";
	char			szTest[256];
	CString			szMsg;

	myglobs.nPlayerThreadNum++;
	lstrcpy(UserName,NULLUSERNAME);//used in UserLogon & PlayerLogon,client must process UserLogon before PlayerLogon
	lstrcpy(PlayerName,NULLPLAYERNAME);

	lpClientConData = (PCLientConData)WorkContext;
	// test start
	sprintf(szTest, "%s Player thread start", inet_ntoa(lpClientConData->stRemoteName.sin_addr));
	AddRecordMsg(szTest);
	// test end
// cary start
	srand((unsigned int)lpClientConData->nVer);
	char szTemp[20];
	int nRet, iRandom=rand()%9999999;
	//for(nRet=0;nRet<8;nRet++) szTemp[nRet]=(char)(rand()%256);
	sprintf( szTemp, "%d", iRandom);

//	ecb_crypt();
	nRet=send(lpClientConData->hClientSock,szTemp,8,0);
	if((nRet==0)||(nRet==SOCKET_ERROR))	{

		sprintf(szTest, "ERROR (%s,%s)%s Send check message error", PlayerName, UserName,
			inet_ntoa(lpClientConData->stRemoteName.sin_addr));
		AddRecordMsg(szTest);
		shutdown(lpClientConData->hClientSock,2);
		closesocket(lpClientConData->hClientSock);
		delete lpClientConData;
		myglobs.nPlayerThreadNum--;
		return (0);
	}
	nRet=recv(lpClientConData->hClientSock,szTemp,20,0);
	if(nRet!=16)	{
		sprintf(szTest, "ERROR (%s,%s)%s Receive check message error", PlayerName, UserName,
			inet_ntoa(lpClientConData->stRemoteName.sin_addr));
		AddRecordMsg(szTest);
		sprintf(szTest, "FAIL %s", szCookieRecvErrMsg);
		Send(lpClientConData->hClientSock, szTest);
		Sleep(5000);	
		shutdown(lpClientConData->hClientSock,2);
		closesocket(lpClientConData->hClientSock);
		delete lpClientConData;
		myglobs.nPlayerThreadNum--;
		return (0);
	}
//	ecb_crypt();
	szTemp[7] = 0;
	szTemp[15] = 0;
	int iTemp=atoi(szTemp), iVer = atoi(szTemp+8);
	//andy_re
	if (iRandom > 5000)
		iVer = (iRandom-iVer)*1000;
	else
		iVer = (iVer - iRandom)*1000;

	if((iVer < CLIENTVER) || (iVer > CLIENTVER + 10000)) {

		sprintf(szTest, "ERROR (%s,%s)%s Incorrect Client Version %d", PlayerName, UserName,
			inet_ntoa(lpClientConData->stRemoteName.sin_addr),iVer);
		AddRecordMsg(szTest);

		sprintf(szTest, "FAIL %s", szVerError);
		Send(lpClientConData->hClientSock, szTest);
		Sleep(5000);	
		shutdown(lpClientConData->hClientSock,2);
		closesocket(lpClientConData->hClientSock);
		delete lpClientConData;
		myglobs.nPlayerThreadNum--;
		return (0);
	}
	iRandom++;
	if(iRandom>9999999)
		iRandom=0;
	if(iTemp!=iRandom) {
		// test start
		sprintf(szTest, "ERROR (%s,%s)%s Invalid value in check message", PlayerName, UserName,
			inet_ntoa(lpClientConData->stRemoteName.sin_addr));
		AddRecordMsg(szTest);
		// test end
		shutdown(lpClientConData->hClientSock,2);
		closesocket(lpClientConData->hClientSock);
		delete lpClientConData;
		myglobs.nPlayerThreadNum--;
		return (0);
	}
	iRandom++;
	if(iRandom>9999999)
		iRandom=0;
	sprintf(szTemp,"%d",iRandom);
//	ecb_crypt();
	nRet=send(lpClientConData->hClientSock,szTemp,8,0);
	if(nRet!=8)	{
		// test start
		sprintf(szTest, "ERROR (%s,%s)%s Send OK message to client fail", PlayerName, UserName,
			inet_ntoa(lpClientConData->stRemoteName.sin_addr));
		AddRecordMsg(szTest);
		// test end
		shutdown(lpClientConData->hClientSock,2);
		closesocket(lpClientConData->hClientSock);
		delete lpClientConData;
		myglobs.nPlayerThreadNum--;
		return (0);
	}
// cary end
	lpClientConData->pMyselfPosite = NULL;
	lpClientConData->szSendBuf.Empty();
	lpClientConData->szPlayerCountName.Empty();
	lpClientConData->szUserCountName.Empty();
	lpClientConData->pvPlayer = NULL;
	lpClientConData->bFirstLogin = TRUE;
	lpClientConData->nVer = iVer;
	lpClientConData->bRun = TRUE;

	while(myglobs.bRun && lpClientConData->bRun){
		RetR = recv(lpClientConData->hClientSock,Buf,sizeof(Buf)-1,0);
		if(RetR == SOCKET_ERROR || RetR==0 || !lpClientConData->bRun || !myglobs.bRun)
			break;
		Buf[RetR]='\0';

		//ANDY_log 訊息
		//szMsg.Format("(%s,%s)%s %s",PlayerName,UserName,
		//	inet_ntoa(lpClientConData->stRemoteName.sin_addr), Buf);
		//AddRecordMsg((char*)(LPCSTR)szMsg);

		Buf2 = strtok(Buf, szCOMPARM);
		lpClientConData->LastConnectTime = CTime::GetCurrentTime();
		while(Buf2 != NULL){
			comlen = strlen(Buf2);
			RetS = ProcessOneCom(bUserLogon, bPlayerLogon, lpClientConData, UserName, PlayerName, Buf2);
			if( RetS == 0 || RetS == SOCKET_ERROR){
				wsprintf(myglobs.szBuffer,"Error Sent to Client %s: %s",
					inet_ntoa(lpClientConData->stRemoteName.sin_addr),Buf);
				AddRecordMsg(myglobs.szBuffer);
				break;
			}
			Buf2 = strtok(Buf2 + comlen + 1,(const char*)szCOMPARM);
		}
		if( RetS == 0 || RetS == SOCKET_ERROR)
			break;
	}

	sprintf(myglobs.szBuffer,"(%s,%s)%s Socket Closed!", PlayerName, UserName, 
		inet_ntoa(lpClientConData->stRemoteName.sin_addr));
	AddRecordMsg(myglobs.szBuffer);

	if (bPlayerLogon)	{//玩家已Login才做Offline處理
		if (((CPlayerInfo*)lpClientConData->pvPlayer)->bRun) {
			EnterCriticalSection(&myglobs.csPlayerSocket);
			playersocketlist.RemoveAt(lpClientConData->pMyselfPosite);
			LeaveCriticalSection(&myglobs.csPlayerSocket);
		}
		m_CmdPlayerLogon.PlayerOffLine(lpClientConData->pvPlayer,PlayerName,lpClientConData->szUserCountName);
	}
	shutdown(lpClientConData->hClientSock,2);
	closesocket(lpClientConData->hClientSock);
	lpClientConData->szSendBuf.Empty();
	delete lpClientConData;
	if (strcmp(UserName, NULLUSERNAME)) {
		Add_UserEnd(UserName);
		if (CheckUserLog(UserName)==INVALIDLOG) {
			sprintf(szTest, "(%s,%s) Invalid login in PlayerThread offline",
				PlayerName, UserName);
			AddRecordMsg(szTest);	
			UserEndLog(UserName, TRUE);
		} else {
			UserEndLog(UserName, TRUE);
		}
	}
	// test start
	sprintf(szTest, "(%s,%s) Player thread end", PlayerName, UserName);
	AddRecordMsg(szTest);
	// test end
	EnterCriticalSection(&myglobs.csPlayerSocket);
	g_iActiveClientNum = playersocketlist.GetCount();
	LeaveCriticalSection(&myglobs.csPlayerSocket);
	myglobs.nPlayerThreadNum--;
	return (0);
}

int ProcessOneCom(BOOL &bUserLogon, BOOL &bPlayerLogon, TClientConData * lpClientConData, char * UserName, char * PlayerName, char * Buf2)
{
	CStringList strCommandList;
	char *ps;
	int RetS;
	int				nLenBuf;
	char			Result[16384];
	CCommandCheck	m_CommandCheck;
	int				nFailSend = 0;
	// Spock start
	char szTest[256];
	CCmdPlayerLogon m_CmdPlayerLogon;
	HANDLE	ThreadHandle;
	DWORD	ThreadId;
	CPlayerInfo *lpPlayerInfo;
	int nTest;
	// Spock end

	strcpy(Result,"OK");
	ps=strtok(Buf2,(const char*)szTOKPARM);
	// Spock start
	if (ps == NULL) {
		AddRecordMsg("ERROR Bad player command!");
		return 1;
	}
	while (ps != NULL) {
		strCommandList.AddTail(ps);
		ps=strtok(NULL,(const char*)szTOKPARM);
	}
	if(!bUserLogon)	{//當用戶還沒有簽到成功,收到其他信息,一律退出.
		if(lstrcmp(strCommandList.GetHead(),szUserLogonCmd)){
			sprintf(szTest, "ERROR %s 用戶還沒有簽到成功,收到其他信息",
				inet_ntoa(lpClientConData->stRemoteName.sin_addr));
			AddRecordMsg(szTest);
			return 0;
		}
		m_CommandCheck.ProcessPlayerCommand(lpClientConData->hClientSock,
												&strCommandList,
												Result,
												lpClientConData->stRemoteName,
												UserName,
												PlayerName,
												lpClientConData->pvPlayer,
												lpClientConData);
		sprintf(szTest, "(%s) User logon", inet_ntoa(lpClientConData->stRemoteName.sin_addr));
		AddRecordMsg(szTest);
		if (strncmp(Result,"FAIL",4)){
			lpClientConData->szUserCountName = UserName;
			bUserLogon = TRUE;
		}
	}else if(!bPlayerLogon)	{//預防有人蓄意破壞,反復簽到開銷服務器內存
		// Nuke +1 for delete user
		if(lstrcmp(strCommandList.GetHead(),szPlayerDeleteCmd))
			if(lstrcmp(strCommandList.GetHead(),szPlayerLogonCmd)){
				if(lstrcmp(strCommandList.GetHead(),szPlayerCreateCmd))
					return 0;
			}
		RetS = CheckUserLog(UserName);
		if(RetS <= 0) {
			sprintf(szTest, "ERROR (%s,%s) Invalid login in ProcessOneCom, err=%d",
				PlayerName, UserName, RetS);
			AddRecordMsg(szTest);
			if (RetS == INVALIDLOG)
				sprintf(szTest, "FAIL %s", szInvalidLogin);
			else
				sprintf(szTest, "FAIL %s", szSystemErrMsg);
			Send(lpClientConData->hClientSock, szTest);
			Sleep(5000);
			return 0;
		}
		m_CommandCheck.ProcessPlayerCommand(lpClientConData->hClientSock,
											&strCommandList,
											Result,
											lpClientConData->stRemoteName,
											UserName,
											PlayerName,
											lpClientConData->pvPlayer,
											lpClientConData);
		if(!strcmp(Result, "LOGON")){
			lpClientConData->szPlayerCountName = PlayerName;
			bPlayerLogon = TRUE;
			// test start
			sprintf(szTest, "(%s,%s) Player logon", PlayerName, UserName);
			AddRecordMsg(szTest);
			// test end
			RetS = Send(lpClientConData->hClientSock, lpClientConData->szSendBuf);
			lpClientConData->szSendBuf.Empty();
			if((RetS == 0) || (RetS == SOCKET_ERROR)) {
				strCommandList.RemoveAll();
				return RetS;
			}
			ThreadHandle = CreateThread (
									NULL,
									0,
									PlayerSendThread,
									(CPlayerInfo*)lpClientConData->pvPlayer,
									0,
									&ThreadId);
			if (ThreadHandle) {
				SetThreadPriority(ThreadHandle, THREAD_PRIORITY_NORMAL);
				CloseHandle (ThreadHandle);
				((CPlayerInfo*)lpClientConData->pvPlayer)->bRun = TRUE;
				((CPlayerInfo*)lpClientConData->pvPlayer)->nStatus = AOS_sendmapok;
				EnterCriticalSection(&myglobs.csPlayerSocket);
				lpClientConData->pMyselfPosite = playersocketlist.AddTail(lpClientConData);
				g_iActiveClientNum = playersocketlist.GetCount();
				LeaveCriticalSection(&myglobs.csPlayerSocket);
			} else {
				// test start
				sprintf(szTest, "ERROR (%s,%s) Create PlayerSendThread Failed",
					PlayerName, UserName);
				AddRecordMsg(szTest);
				// test end
				return 0;
			}
			strCommandList.RemoveAll();
			return RetS;
		}
	}else{
		if(!lstrcmp(strCommandList.GetHead(),szPlayerLogonCmd))
			return 0;
		if(!lstrcmp(strCommandList.GetHead(),szPlayerCreateCmd))
			return 0;
		if(!lstrcmp(strCommandList.GetHead(),SZGETMISSBUF))	{//處理發送不穩定
			if(strCommandList.GetCount() > 1){
				nFailSend ++;
				if(nFailSend>100) return 0;//發送一百次還沒有發完,認為失敗
				//檢查Buf,發送剩下的Buf
				nLenBuf = atoi((char *)(LPCSTR)strCommandList.GetTail());
				if(nLenBuf > lpClientConData->szSendBuf.GetLength()){
					strcpy(Result,"FAIL 非法操作");
				}else{
					lpClientConData->szSendBuf = lpClientConData->szSendBuf.Right(lpClientConData->szSendBuf.GetLength() - nLenBuf);
					strcpy(Result,SZSENDMISSBUF);
					strcat(Result,lpClientConData->szSendBuf);
				}
			}else
				strcpy(Result,"FAIL 非法操作");
		}else if(!lstrcmp(strCommandList.GetHead(),SZCANHEALING)){
			lpPlayerInfo = (CPlayerInfo*)lpClientConData->pvPlayer;
			if(lpClientConData->bFirstLogin){
				Add_UserStart((char*)(LPCSTR)lpPlayerInfo->szUserName);
				lpClientConData->bFirstLogin = FALSE;
				// Spock start: 系統公告
				CString szAnnouce;
				char szTxt[1024], szFileName[128];
				FILE *af;
				
				strcpy(szFileName, g_tszPathName);
				strcat(szFileName,"\\annouce");
				strcat(szFileName,XMUDVER);
				strcat(szFileName,".txt");
				szAnnouce.Format("%s %s 人在江湖　Server-v%s　Client-v%1.3f",
					SZOKMSG, szCyanHigt, XMUDVER, (double)(lpClientConData->nVer)/1000000);
				if (myglobs.bNoKill) szAnnouce += CString("　此伺服器禁止死鬥");
				lpPlayerInfo->SendMsg(szAnnouce);
				af = fopen(szFileName, "r");
				if (af != NULL) {
					while (fgets(szTxt, 1024, af)!=NULL) {
						szAnnouce.Format("%s %s %s",SZOKMSG, szCyanHigt, szTxt);
						lpPlayerInfo->SendMsg(szAnnouce);
					}
					fclose(af);
				}
			}
			CString parm = CString("\t");
			CString tmpMapName = lpPlayerInfo->szRoom;
			tmpMapName = tmpMapName+parm+lpPlayerInfo->szCName
				+parm+lpPlayerInfo->szEName+parm
				+lpPlayerInfo->szTilte+parm
				+lpPlayerInfo->szFamily+parm
				+lpPlayerInfo->szXFileName+parm
				+inet_ntoa(lpPlayerInfo->IPAddr.sin_addr)+parm;
			tmpMapName = szSomeonejoinMap + CString(" ") + tmpMapName;
			lpPlayerInfo->SendMsgToAll(tmpMapName);
			((CActiveObject*)lpClientConData->pvPlayer)->bNoHealing=FALSE;
			//dainty +1
			lpPlayerInfo->nStatus = AOS_none;
			//dainty end
			strcpy(Result,"OK");
		}else if(!lstrcmp(strCommandList.GetHead(),SZSAVE))	{

			nTest = m_CmdPlayerLogon.SavePlayerData((CPlayerInfo*)lpClientConData->pvPlayer);
			if (nTest <= 0) {
				sprintf(szTest,"ERROR (%s,%s) SavePlayerData Error=%d!"
					,lpClientConData->szPlayerCountName
					,lpClientConData->szUserCountName,nTest);
				AddRecordMsg(szTest);
				sprintf(szTest,"%s %s %s",SZOKMSG,szRedHigt,szDiskWriteErrMsg);
				((CPlayerInfo*)lpClientConData->pvPlayer)->SendMsg(szTest);
			} else {
				sprintf(szTest,"(%s,%s) SavePlayerData OK!",
					lpClientConData->szPlayerCountName, lpClientConData->szUserCountName);
				AddRecordMsg(szTest);
				sprintf(Result,"%s MANUAL",SZSAVE);
				((CPlayerInfo*)lpClientConData->pvPlayer)->nRound = 0;
				((CPlayerInfo*)lpClientConData->pvPlayer)->bSaved = TRUE;
			}
		}else	{
			if(!lpClientConData->szSendBuf.IsEmpty())	{
				nFailSend = 0;
				lpClientConData->szSendBuf.Empty();
			}
			m_CommandCheck.ProcessPlayerCommand(lpClientConData->hClientSock,
				&strCommandList,
				Result,
				lpClientConData->stRemoteName,
				UserName,
				PlayerName,
				lpClientConData->pvPlayer,
				lpClientConData);
		}
	}
	if (!strncmp(Result,"FAIL",4)){
		Send(lpClientConData->hClientSock,Result);
		Sleep(5000);
		return 0;
	}
	if(!lstrcmp(strCommandList.GetHead(),szSendMapData)){
		lpClientConData->szSendBuf = Result;
	}
	if(strcmp(Result,"OK"))	{
		if (bPlayerLogon) {
			((CPlayerInfo*)lpClientConData->pvPlayer)->SendMsg(Result);
			RetS = 1;
		} else {
			RetS = Send(lpClientConData->hClientSock,Result);
		}
	}else {
		RetS = 1;
	}
	strCommandList.RemoveAll();
	return RetS;
}