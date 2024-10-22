// MainWnd.cpp : implementation file
//

#include "stdafx.h"
#include "XmudOS.h"
#include "MainWnd.h"
#include "ShowMsg.h"
#include "CmdPlayerLogon.h"
#include "map\MapInfo.h"
#include "CommandCheck.h"
#include "CmdEmote.h"
#include "Fight.h"
#include "goods\goods\Goods.h"
#include "npc\Npc.h"
#include "wgs\common.h"
#include "wgs\DS_API.h"
#include "skill\skill\skill.h"
#include "hash.h"

extern rmfullglobals myglobs;
extern char g_tszPathName[256];
extern char szDSHostName[32];
extern int g_iActiveClientNum;
extern SOCKET hPlayerServerSock;
ShowMsg m_ShowMsg;

CList <CBaseMap*,CBaseMap*>maplist;
CList <TAdminConData *,TAdminConData* >adminsocketlist;
CList <TClientConData *,TClientConData* >playersocketlist;
CList <TDataUser*,TDataUser*>userlist;
CList <TChatChannel*,TChatChannel*>chatchannellist;
CList <CFight*,CFight*>killlist;
CList <CFight*,CFight*>fightlist;

/////////////////////////////////////////////////////////////////////////////
// CMainWnd

CMainWnd::CMainWnd()
{
}

CMainWnd::~CMainWnd()
{
}


BEGIN_MESSAGE_MAP(CMainWnd, CWnd)
	//{{AFX_MSG_MAP(CMainWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_APP_SHUTDOWN, OnAppShutdown)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainWnd message handlers

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	myglobs.hWndMain = m_hWnd;
	srand( (unsigned)time( NULL ) );
/*
	CIPAddressCtrl m_IPAddressCtrl;
	RECT rcTmp;
	SetRect(&rcTmp,0,0,0,0);
	m_IPAddressCtrl.Create(WS_CHILD,rcTmp,this,9999);
	m_IPAddressCtrl.SetAddress(192,168,0,251);
*/
	InitializeCriticalSection(&myglobs.csAdminSocket);
	InitializeCriticalSection(&myglobs.csPlayerSocket);
	InitializeCriticalSection(&myglobs.csSentCliMsg);
	InitializeCriticalSection(&myglobs.csUserlist);
	InitializeCriticalSection(&myglobs.csMaplist);
	InitializeCriticalSection(&myglobs.csChatChannel);
	InitializeCriticalSection(&myglobs.csFightlist);
	InitializeCriticalSection(&myglobs.csRecordMsg);
	InitializeCriticalSection(&myglobs.csTalkMsg);
	InitializeCriticalSection(&myglobs.csPlayerData);
	InitializeCriticalSection(&myglobs.csUserLog);
	InitializeCriticalSection(&myglobs.csSockDataLog);

	GetClientRect(&myglobs.rcWinSize);
	m_ShowMsg.Create(ES_AUTOHSCROLL|ES_AUTOVSCROLL
					|ES_MULTILINE
					|ES_READONLY
					|ES_LEFT
					|WS_CHILD
					|WS_BORDER
					|WS_VSCROLL
					|WS_HSCROLL,
					myglobs.rcWinSize,	
					this,
					IDC_EDIT_SHOWINFO);
	m_ShowMsg.ShowWindow(SW_SHOW);
	m_ShowMsg.UpdateWindow();

	FILE * cfg;
	char szFile[256];
	CTime Now=CTime::GetCurrentTime();

	sprintf(szFile,"%s\\log\\Info%s.log", g_tszPathName, Now.Format("%Y%m%d%H"));
	myglobs.flog = fopen(szFile,"a");
	if (myglobs.flog == NULL) {
		AfxMessageBox(_T("Open Infolog file fail"));
		exit(1);
	}else
		fprintf(myglobs.flog, "Emprise Server Started!\n");
	
	//andy_re
	{
		char buf1[256];
		sprintf( buf1, "%s\\playersave", g_tszPathName);
		if( CreateDir( buf1)  == FALSE )
			return -1;
	}

	//讀取人數限制
	myglobs.g_ClientNum = 60;
	strcpy(szFile, g_tszPathName);
	strcat(szFile, "\\PmudOS.cfg");
	cfg = fopen(szFile, "r");
	if (cfg) {
		fscanf(cfg, "%d %s %d %s", &myglobs.g_ClientNum, szDSHostName,
			&myglobs.bNoKill, myglobs.szID);
		fclose(cfg);
	}
//	if (myglobs.g_ClientNum <= 0) myglobs.g_ClientNum = 30;
	if (myglobs.g_ClientNum > 700) myglobs.g_ClientNum = 700;
	sprintf(szFile, "Max Player %d", myglobs.g_ClientNum);
	AddRecordMsg(szFile);
	sprintf(szFile, "Data Server: %s", szDSHostName);
	AddRecordMsg(szFile);
	// 檢查是否可以死鬥
	if(myglobs.bNoKill) {
		AddRecordMsg("禁止死鬥");
	} else {
		AddRecordMsg("可死鬥");
	}
	// Spock end

	InitPlayer(m_hWnd);
	InitGoods();
	InitAllSkill();
	InitAllMap();
	InitEmote();
	InitAllNpc();

	if(!CreateHeartBeatThread())
		return -1;
	if(!CreatePlayerThread())
		return -1;
	srand( (unsigned)time( NULL ) );
	//SetTimer(1,10000,NULL);//每一分鐘做一次檢查(變化人物、NPC、地圖等等)
	return 0;
}

void CMainWnd::OnClose()
{
	myglobs.bRun = FALSE;
	myglobs.nRunTimes = -1;
	closesocket(hPlayerServerSock);
	TerminateThread(myglobs.hHeartBeatThreadHandle, 0);
	CloseHandle(myglobs.hHeartBeatThreadHandle);
	if (g_iActiveClientNum > 0)
		fprintf(myglobs.flog,"Player not cleared %d\n",g_iActiveClientNum);
	if (myglobs.nPlayerThreadNum > 0)
		fprintf(myglobs.flog,"PlayerThread not closed %d\n",myglobs.nPlayerThreadNum);
	fprintf(myglobs.flog,"Emprise server closed!\n");
	CWnd::OnClose();
}

void CMainWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	ReleaseGoods();
	ReleaseSkill();
	ReleaseNet();
	DeleteEmote();
	//fclose(myglobs.ferr);
	fclose(myglobs.flog);
	//fclose(myglobs.ftalk);
}

void CMainWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	switch(nType)
	{
	case SIZE_MINIMIZED:
		{
			AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);
		}
		break;
	default:
		break;
	}
}

//顯示圖標說明
void CMainWnd::ShowIconMenu()
{
	CMenu	ContextMenu ;
	CPoint  CursorPos ;

	//取得鼠標的坐標。
	GetCursorPos ( & CursorPos ) ;

	ContextMenu.CreatePopupMenu () ;
	ContextMenu.AppendMenu ( MF_STRING , ID_APP_ABOUT, "幫助" ) ;
	ContextMenu.AppendMenu ( MF_SEPARATOR);
	ContextMenu.AppendMenu ( MF_STRING , ID_APP_EXIT , "離開" ) ;
	ContextMenu.AppendMenu ( MF_STRING , ID_APP_SHUTDOWN , "關機" ) ;
	
	//必須添加的一句；解決當鼠標點擊在菜單外面的問題。
	SetForegroundWindow () ;
	ContextMenu.TrackPopupMenu ( TPM_RIGHTALIGN | TPM_RIGHTBUTTON , 
		                         CursorPos.x ,
								 CursorPos.y ,
								 this ,
								 NULL ) ;

	return ;
}

//退出服務器程序
void CMainWnd::OnAppExit()
{
	AddRecordMsg("Exit server!");
	TerminateThread(myglobs.hPlayerServerThreadHandle, 0);
	CloseHandle(myglobs.hPlayerServerThreadHandle);
	myglobs.bRun = FALSE;
}

void CMainWnd::OnAppShutdown()
{
	AddRecordMsg("Shutdown server in 90 seconds!");
	TerminateThread(myglobs.hPlayerServerThreadHandle, 0);
	CloseHandle(myglobs.hPlayerServerThreadHandle);
	myglobs.nRunTimes = 90;
	myglobs.bShutdown = TRUE;
//	PostMessage(WM_CLOSE,0,0);
}

LRESULT CMainWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message){
	case UM_WINICON_MSG:
		{
			switch(lParam){
			case WM_LBUTTONDBLCLK:
				{	//顯示住窗口
					AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
				}
				break ;
			case WM_RBUTTONDOWN:
				{
					ShowIconMenu();//顯示圖標說明
				}
				break;
			}
		}
		break;
	default:
		break;
	}
	return CWnd::WindowProc(message, wParam, lParam);
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMainWnd::OnAppAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void CMainWnd::OnTimer(UINT_PTR nIDEvent) 
{

	if(nIDEvent==7){
	}
	CWnd::OnTimer(nIDEvent);
}
