#if !defined(AFX_XMUDOS_H__96579646_8540_11D3_BA84_0000E8A021D8__INCLUDED_)
#define AFX_XMUDOS_H__96579646_8540_11D3_BA84_0000E8A021D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include "config.h"

#define SERVERUSER "華義國際有限公司出品"
#define TITLE	"X-MudServer"
#define PMUD_KEY (TEXT("Software\\Vicsun\\PMUD"))
#define MAX_PATH_NAME_LENGTH 256
#define MAX_TYPE_LENGTH 20
#define MAX_CLIENT_NUM 700
#define MAXHOSTNAME 128
#define ENGLISHNAMELENGTH 64

#define SZSYSLOG_RETMSG " 測試版1.38 http://www.gameking.net.cn/download/patch_pac/xmud138.zip "

#define PlayerPort	6678
#define DataPort    6679
#define AdminPort   7678

#define PLAYERBUFFERSIZE  1024
#define DATABUFFERSIZE    8192
#define ADMINBUFFERSIZE   1024
#define PlayerCommandParaNum 10
#define PlayerCommandParaLen 8192
#define NULLUSERNAME "@User"
#define NULLPLAYERNAME "@Player"
#define szTOKPARM " "

#define UM_WINICON_MSG			WM_USER

typedef struct tagSendBufBySock{
	CString szSendBuf;
	SOCKET hClientSock;
}TSendBySock,*PSendBySock;
typedef struct tagAdminConData
{
	SOCKET hClientSock;
	sockaddr_in stRemoteName;
	CString szRecBuf;
	CString szSendBuf;
	POSITION pAdminPosite;
	CString szAdminCountName;
	POSITION pPosite;
	BOOL bLogonOK;
}TAdminConData,*PAdminConData;


typedef struct _TClientConData
{
	SOCKET hClientSock;
	sockaddr_in stRemoteName;
	CString szSendBuf;
	POSITION pMyselfPosite;
	CString szPlayerCountName;
	CString szUserCountName;
	CTime	LastConnectTime;
	LPVOID pvPlayer;
	BOOL	bFirstLogin;
	char szCheck[8];
	int nVer;
	BOOL bRun;
}TClientConData,*PCLientConData;

class CXmudOSApp : public CWinApp
{
public:
	NOTIFYICONDATA niData;
	BOOL CheckSystem();
	CXmudOSApp();

	//{{AFX_VIRTUAL(CXmudOSApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

public:
	DECLARE_MESSAGE_MAP()
};

void AddRecordMsg(char *szMsg);
BOOL AlreadyRun();
LONG GetHostID ();
DWORD WINAPI AdminServerThread( LPVOID WorkContext); 
DWORD WINAPI AdminThread (LPVOID WorkContext);
DWORD WINAPI PlayerServerThread (LPVOID WorkContext);
DWORD WINAPI PlayerThread (LPVOID WorkContext);

DWORD WINAPI HeartBeatThread (LPVOID WorkContext);
DWORD WINAPI MonitorThread (LPVOID WorkContext);
DWORD WINAPI SendBySocket( LPVOID pv );
int Send(SOCKET s, CString str);
int Send(SOCKET s, CString str,int iFrom,int iLen);
#endif
