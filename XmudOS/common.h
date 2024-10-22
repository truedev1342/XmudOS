
#if !defined(AFX_COMMON_H__96579658_8540_11D3_BA84_0000E8A021D8__INCLUDED_)
#define AFX_COMMON_H__96579658_8540_11D3_BA84_0000E8A021D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

typedef struct tagRetInfo
{
	union 
	{
		BOOL bRet;
		int	 nRet;
	};
	CString szRet;
	tagRetInfo()
	{
		bRet = FALSE;
		szRet = "";
	}
	tagRetInfo(const tagRetInfo & ri)
	{
		nRet = ri.nRet;
		szRet = ri.szRet;
	}
}TRetInfo;

typedef struct tagrmfullglobals {
	HWND hWndMain;
	HINSTANCE hInstApp;
	RECT rcWinSize;
	WSADATA stWSAData;
	HANDLE hAdminServerThreadHandle;
	HANDLE hPlayerServerThreadHandle;
	HANDLE hHeartBeatThreadHandle;
	HANDLE hMonitorThreadHandle;

	CRITICAL_SECTION csAdminSocket;
	CRITICAL_SECTION csPlayerSocket;
	CRITICAL_SECTION csFightlist;
	CRITICAL_SECTION csMaplist;
	CRITICAL_SECTION csUserlist;
	CRITICAL_SECTION csChatChannel;
	CRITICAL_SECTION csSentCliMsg;
	CRITICAL_SECTION csRecordMsg;
	CRITICAL_SECTION csTalkMsg;
	CRITICAL_SECTION csPlayerData;
	CRITICAL_SECTION csUserLog;
	CRITICAL_SECTION csSockDataLog;
	unsigned int nRunTimes;
	unsigned int nMothRumTimes;
	int nPlayerThreadNum;
	BOOL bNoKill;
	BOOL bRun;
	BOOL bShutdown;
	FILE *flog, *ftalk, *ferr;
	char szID[32];
	CStringList userlist;
	CStringList monsterlist_4;
	CStringList monsterlist_s;
	char szBuffer[256];
	char g_szVer[256];
	int g_ClientNum;
}rmfullglobals;

#define SName_zhun		1
#define SName_mie		2
#define SName_qian		3
#define SName_da		4

class CSkill;
class CActiveObject;
CSkill * GetSkillClass(CString szEName);
CString GetSpecialName(CActiveObject *me, int nType);
int Send(SOCKET s, CString str);
void MapMessage(CString msg, CActiveObject *me, CActiveObject *you = NULL);
void ProcessMessage(void);
BOOL CreateDir( char *Path);
BOOL CreatePlayerDir( CString name );
BOOL CreatePlayerFile( char *filename);
BOOL ResetPlayerLog( char *filename);
BOOL ResetPlayerData( const char *szPath, const char *szFile, const char *temFile);
#endif
