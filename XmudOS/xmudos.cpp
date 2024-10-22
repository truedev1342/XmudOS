// XmudOS.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XmudOS.h"
#include "MainWnd.h"
#include "Common.h"
// Spock +1
#include "Player.h"

rmfullglobals myglobs;
char g_tszPathName[256];	//應用程序數據路徑
extern CList <TAdminConData *,TAdminConData* >adminsocketlist;
extern CList <TClientConData *,TClientConData* >playersocketlist;


int Send(SOCKET s, CString str)
{
	str += "\27";			//命令和命令之間分開
	LPCTSTR lpstr=str;
	int	iRet,iLen,iIndex=0;
	iLen=str.GetLength();
	while(iLen>0){
		iRet=send(s, lpstr+iIndex, iLen, 0 );
		if((iRet==0)||(iRet==SOCKET_ERROR))
			break;
		iIndex+=iRet;
		iLen-=iRet;
	}
	return iRet;
}

int Send(SOCKET s, CString str,int iFrom,int iLen)
{
	str += "\27";			//命令和命令之間分開
	LPCTSTR lpstr=str;
	int	iRet,iIndex=iFrom;
	while(iLen>0)
	{
		iRet=send(s, lpstr+iIndex, iLen, 0 );
		if((iRet==0)||(iRet==SOCKET_ERROR))
			break;
		iIndex+=iRet;
		iLen-=iRet;
	}
	return iRet;
}

BEGIN_MESSAGE_MAP(CXmudOSApp, CWinApp)
	//{{AFX_MSG_MAP(CXmudOSApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CXmudOSApp::CXmudOSApp()
{
	// Place all significant initialization in InitInstance
	myglobs.bRun = FALSE;
	myglobs.bShutdown = FALSE;
	myglobs.nPlayerThreadNum = 0;
	myglobs.nRunTimes = 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXmudOSApp object

CXmudOSApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXmudOSApp initialization

BOOL CXmudOSApp::InitInstance()
{
	if(!AlreadyRun())
		return FALSE;
	if(!CheckSystem())
		return FALSE;

	srand( (unsigned)time( NULL ) );

	myglobs.hInstApp = AfxGetInstanceHandle();

	//建立主窗口並顯示
	CMainWnd * win = new CMainWnd;
	if(!win->CreateEx(WS_EX_APPWINDOW,
		
				AfxRegisterWndClass(CS_DBLCLKS,
				::LoadCursor(NULL,IDC_ARROW),
				(HBRUSH)GetStockObject(WHITE_BRUSH), 
				AfxGetApp()->LoadIcon(IDR_MAINFRAME)),
				_T(TITLE), 
				WS_VISIBLE | WS_CAPTION |
				WS_SYSMENU | WS_MINIMIZEBOX | WS_POPUP, 
				0,0,640,480,
				NULL,
				LoadMenu(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)),
				NULL))
			return FALSE;

	m_pMainWnd = win;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	HICON hIcon;
	hIcon = AfxGetApp() -> LoadIcon( IDR_MAINFRAME );

	//填寫相關結構。
	niData.cbSize	= sizeof ( NOTIFYICONDATA ); 
	niData.hWnd		= myglobs.hWndMain;	//所有點擊圖標的消息都送往此窗口。
	niData.uID		= ICON_MSG;			//點擊圖標時，返回的消息中wParam的數值將等于100。
	niData.uFlags	= NIF_ICON | NIF_MESSAGE | NIF_TIP;
	niData.uCallbackMessage = UM_WINICON_MSG;	//定義有關NOtifyIcon的消息標識。與其他消息區別。
	niData.hIcon	= hIcon;
	sprintf ( niData.szTip , TITLE );
	//實現添加圖標。
	Shell_NotifyIcon ( NIM_ADD , & niData );

	//隱藏住窗口。
	AfxGetApp()->m_pMainWnd->ShowWindow( SW_HIDE );

	return TRUE;
}

BOOL AlreadyRun()
{
    HWND FirsthWnd, FirstChildhWnd;

    if((FirsthWnd = FindWindow(NULL, TITLE)) != NULL)
    {
        FirstChildhWnd = GetLastActivePopup(FirsthWnd);
		BringWindowToTop(FirsthWnd);
        if(FirsthWnd != FirstChildhWnd)
        {
            BringWindowToTop(FirstChildhWnd);
        }
        ShowWindow(FirsthWnd, SW_SHOWNORMAL);
        return FALSE;
    }
	return TRUE;
}

int CXmudOSApp::ExitInstance() 
{
	Shell_NotifyIcon (NIM_DELETE,&niData);
	return CWinApp::ExitInstance();
}

BOOL CXmudOSApp::OnIdle(LONG lCount) 
{
/*	TClientConData * lpClientConData;
	TAdminConData * lpAdminConData;
	CPlayerInfo * lpPlayerInfo;
	CString tmpSendMsg;
	int i,j;
	// Spock +1
	POSITION pos, lastpos;

	EnterCriticalSection(&myglobs.csSentCliMsg);
	if(!myglobs.g_SendToClientMsg.IsEmpty())
	{
		tmpSendMsg = myglobs.g_SendToClientMsg.GetHead();
		myglobs.g_SendToClientMsg.RemoveAt(myglobs.g_SendToClientMsg.FindIndex(0));
		LeaveCriticalSection(&myglobs.csSentCliMsg);
	}
	else
	{
		LeaveCriticalSection(&myglobs.csSentCliMsg);
		return TRUE;
	}

	EnterCriticalSection(&myglobs.csPlayerSocket);
	pos = playersocketlist.GetHeadPosition();
	while (pos != NULL)	{
		lastpos = pos;
		lpClientConData = playersocketlist.GetNext(pos);
		if (lpClientConData == NULL) {
			playersocketlist.RemoveAt(lastpos);
			AddRecordMsg("ERROR NULL pointer in OnIdle, lpClientConData");
			continue;
		}
		if (strcmp(lpClientConData->szCheck, SZCONCHECK)) {
			AddRecordMsg("ERROR Bad data in OnIdle, lpClientConData");
			playersocketlist.RemoveAt(lastpos);
			continue;
		}
		lpPlayerInfo = (CPlayerInfo*)lpClientConData->pvPlayer;
		if(lpPlayerInfo == NULL) {
//			AddRecordMsg("ERROR NULL pointer in OnIdle, lpClientConData->pvPlayer");
			continue;
		}
		if(strcmp(lpPlayerInfo->szCheck, SZAOBJCHECK)) {
			AddRecordMsg("ERROR Bad data in OnIdle, lpClientConData->pvPlayer");
			playersocketlist.RemoveAt(lastpos);
			continue;
		}
		if(!lpClientConData->bSockUsed)
			Send(lpClientConData->hClientSock,tmpSendMsg);
	}
	LeaveCriticalSection(&myglobs.csPlayerSocket);

	tmpSendMsg = tmpSendMsg + ("\r\n");
	EnterCriticalSection(&myglobs.csAdminSocket);
	j = adminsocketlist.GetCount();
	for(i=0;i<j;i++)
	{
		lpAdminConData = adminsocketlist.GetAt(adminsocketlist.FindIndex(i));
		if(lpAdminConData->bLogonOK)
			Send(lpAdminConData->hClientSock,tmpSendMsg);
	}
	LeaveCriticalSection(&myglobs.csAdminSocket);*/
	return TRUE;
}

BOOL CXmudOSApp::CheckSystem()
{
	// 查看注冊信息
	HKEY   key;
	LONG   result;
	DWORD  type, size = 512;
	result = RegOpenKeyEx( HKEY_LOCAL_MACHINE, "Software\\WAEI\\PMUDOS",
						   0, KEY_READ, &key );
	if( ERROR_SUCCESS != result )
	{
		AfxMessageBox(_T("PmudOS didn't registed!"));
		return FALSE;
	}

	// Search for the desired registry value, and close the registry
	result = RegQueryValueEx( key, "PmudClientPathName", NULL, &type, 
	                      (LPBYTE)g_tszPathName, &size );
	RegCloseKey( key );
	if( ERROR_SUCCESS != result )
	{
		AfxMessageBox(_T("PmudClinet didn't registed!"));
		return FALSE;
	}
	return TRUE;
}

