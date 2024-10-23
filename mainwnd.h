#if !defined(AFX_MAINWND_H__96579652_8540_11D3_BA84_0000E8A021D8__INCLUDED_)
#define AFX_MAINWND_H__96579652_8540_11D3_BA84_0000E8A021D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

typedef struct _TDataUser
{
	CString	UserAccountName;
	int		iEnableStat;
	int		iPlayerNum;
	CString	szPassWord;
}TDataUser,*PDataUser;

class CMainWnd : public CWnd
{
public:
	void ShowIconMenu();
	BOOL DoLoadGameFile();
	BOOL CreateAdminThread();
	BOOL CreatePlayerThread();
	BOOL CreateHeartBeatThread();
	CMainWnd();

public:


public:
	//{{AFX_VIRTUAL(CMainWnd)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
public:
	virtual ~CMainWnd();

protected:
	//{{AFX_MSG(CMainWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAppExit();
	afx_msg void OnAppShutdown();
	afx_msg void OnAppAbout();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
