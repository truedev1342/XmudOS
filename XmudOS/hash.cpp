#include "stdafx.h"
#include "hash.h"
#include "Config.h"
#include "wgs\DS_API.h"
#include "wgs\Common.h"
#include "Common.h"
#include "XmudOS.h"
#include "Player.h"

extern rmfullglobals myglobs;
extern char g_tszPathName[256];

static BOOL DSOK = TRUE;
static int DSFailCount = 0;

int DSWait(int *lpnRet)
{
	return *lpnRet;
}

void szHashName(CString name, char *buf)
{
	char temp[21], temp2[10], userdir[60];
	unsigned int all,i;

	userdir[0] = 0;
	strncpy(temp,name,20);
	for (all=0,i=0;i<strlen(temp);i++) {
		all+=temp[i];
		sprintf(temp2,"%02X",temp[i]);
		strcat(userdir, temp2);
	}

	sprintf(buf,"playersave\\%02X\\_%s",all%256,userdir);

}

void szHash2(CString name, char *buf)
{
	char temp[21];
	CString szTemp;
	unsigned int all,i;

	szTemp = name;
	szTemp.MakeLower();
	strncpy(temp,szTemp,20);
	for (all=0,i=0;i<strlen(temp);i++) {
		all+=temp[i];
	}
	sprintf(buf,"%02X",all%256);
}

int nGetPlayerNumber(char *szUser, char *szPath, char *szFile)
{
	FILE *fp;
	char filebuf1[256], buf1[256];
	int nRet=-1;
	sprintf( filebuf1,"%s\\%s\\%s", g_tszPathName, szPath, szFile);
	fp = fopen( filebuf1, "r");
	if( fp )	{
		nRet = 0;
		while( fgets( buf1,sizeof( buf1), fp) != NULL )	{
			nRet++;
		}
		fclose( fp);
	}else	{
		fp = fopen( filebuf1, "w+");
		if( fp)	{
			nRet=0;
			fclose(fp);
		}
	}
	return nRet;
}

int AddPlayer(const char *szUser, const char *szPath, const char *szFile, const char *CName, const char *EName, const char *Password)
{
	char buffer[1024],filebuf1[256];
	int nRet = 0;
	FILE *fp;

	sprintf(buffer,"%s %s %s",CName,EName,Password);
	
	sprintf( filebuf1,"%s\\%s\\%s", g_tszPathName, szPath, szFile);
	if( (fp=fopen( filebuf1,"r")) != NULL)	{	//先建檔
		fclose( fp);
	}else	{
		return -1;
	}
	if (!DSAppend(szUser, szPath, szFile, buffer, strlen(buffer), &nRet)) return DSFAIL;
	return 1;
}

int GetPlayers(char *szUser, char *szPath, char *szFile, char *szBuf)
{
	char *ps, szTemp[DSBUFSIZE];
	int nSize=0, nRet=0;
	FILE *fp;
	char filebuf1[256], buf1[256];
	szBuf[0] = 0;
	memset( szTemp, 0, sizeof( szTemp));

	sprintf( filebuf1,"%s\\%s\\%s", g_tszPathName, szPath, szFile);
	if((fp = fopen( filebuf1, "r")) != NULL)	{
		while( fgets( buf1, sizeof( buf1), fp) != NULL )	{
			strcat( szTemp, buf1);
		}
		fclose( fp);
	}else	{
		return -1;
	}
	ps = strtok(szTemp, " \t\r\n");
	while (ps) {
		strcat(szBuf,ps);
		strcat(szBuf,"\t");
		ps = strtok(NULL, " \t\r\n");
	}
	return 1;
}

int FindPlayer(char *szUser, char *szPath, char *szFile, char *szPlayer)
{
	FILE *fp;
	char filebuf1[256], buf1[256], Ename[256], Cname[256];

	memset( Ename, 0, sizeof( Ename));
	memset( Cname, 0, sizeof( Cname));

	sprintf( filebuf1,"%s\\%s\\%s", g_tszPathName, szPath, szFile);
	if( (fp=fopen(filebuf1,"r")) != NULL)	{
		while( fgets( buf1, sizeof( buf1), fp) != NULL )	{
			sscanf( buf1,"%s %s", Cname, Ename);
			if( !strcmp( szPlayer, Cname) || !strcmp( szPlayer, Ename) )
				return 1;
		}
		fclose( fp);

	}else	{
		return -1;
	}
	return 2;
}

int DSLoadData(char *szUser, char *szPath, char *szFile, char *szBuf)
{
	FILE *fp;
	char filebuf1[256], buf1[256];
	szBuf[0]=0;

	sprintf( filebuf1,"%s\\%s\\%s", g_tszPathName, szPath, szFile);
	if((fp=fopen( filebuf1,"r")) != NULL )		{
		while( fgets( buf1, sizeof( buf1), fp) != NULL )	{
			strcat( szBuf, buf1);
		}
		fclose( fp);
	}else	{
		return -1;
	}

	return 1;
}

int DSSaveData(char *szUser, char *szPath, char *szFile, CString cSaveData)
{
	FILE *fp;
	char filebuf1[256];
	memset( filebuf1, 0, sizeof( filebuf1));
	//andy_re
	sprintf( filebuf1,"%s\\%s\\%s", g_tszPathName, szPath, szFile);
	fp = fopen( filebuf1, "w+");
	if( fp)	{
		fprintf( fp,"%s", cSaveData);
		fclose( fp);
	}else
		return -1;
	return 1;

}

int UserStartLog(char *szUser)
{
	char szPath[256], szFile[256], szBuf[256];
	int nRet, nTest, nRetry;
	CTime CurrentTime = CTime::GetCurrentTime(), BaseTime(1999,1,1,0,0,0);
	CTimeSpan TimeSpan;
	CString szTmp;

	szHashName(szUser, szPath);
	szTmp = szUser;
	szTmp.MakeLower();
	strcpy(szFile, szTmp);
	strcat(szFile, ".log");
	TimeSpan = CurrentTime - BaseTime;
	sprintf(szBuf, "%s %d\n", myglobs.szID, TimeSpan.GetTotalMinutes());
	nTest = -1; nRetry = 0;
	while ((nTest <= 0) && (nRetry < 3)) {
		nRetry++;
		if (!DSAppend(szUser, szPath, szFile, szBuf, strlen(szBuf), &nRet))	{
			return DSFAIL;
		}else
			nTest = 1;
	}

	return nTest;
}

int UserEndLog(char *szUser, BOOL bNormal)
{
	FILE *fl;
	char szPath[256], szFile[256], szBuf[256];
	CString szStr;
	POSITION pos, lastpos;
	int nTest, nRetry;

	szHashName(szUser, szPath);
	strcpy(szFile, szUser);
	strcat(szFile, ".log");
	if (bNormal)
		strcpy(szBuf, "@ 1\n");
	else
		strcpy(szBuf, "Invalid 99999999\n");
	nTest = -1; nRetry = 0;
	while ((nTest <= 0) && (nRetry < 4)) {
		nRetry++;
		nTest = DSSaveData(szUser, szPath, szFile, szBuf);
	}
	if (nTest <= 0) {
		sprintf(szBuf, "ERROR (%s) Send endlog fail, err=%d", szUser, nTest);
		AddRecordMsg(szUser);
	}

	EnterCriticalSection(&myglobs.csUserLog);
	strcpy(szFile, g_tszPathName);
	strcat(szFile, "\\user.log");
	fl = fopen(szFile, "w");
	if (fl) {
		pos = myglobs.userlist.GetHeadPosition();
		while (pos) {
			lastpos = pos;
			szStr = myglobs.userlist.GetNext(pos);
			if (strcmp(szStr, szUser)) {
				fprintf(fl, "%s\n", szStr);
			} else {
				myglobs.userlist.RemoveAt(lastpos);
			}
		}
		fclose(fl);
	} else {
		LeaveCriticalSection(&myglobs.csUserLog);
		AddRecordMsg("ERROR could not open user.log for writing");
		PostMessage(myglobs.hWndMain,WM_CLOSE,0,0);
		return -10000;
	}
	szStr.Empty();
	LeaveCriticalSection(&myglobs.csUserLog);
	return 1;
}

//ANDY_CHECK_LOG
void EndCheck_PlayerLog( char *szUser , BOOL Check_n )
{
	FILE *fl;
	char szPath[256], szFile[256], szBuf[256];
	CString szStr;
	int nTest, nRetry;

	szHashName(szUser, szPath);
	strcpy(szFile, szUser);
	strcat(szFile, ".log");
	if (Check_n)
		strcpy(szBuf, "@ 1\n");
	else
		strcpy(szBuf, "Invalid 99999999\n");
	nTest = -1; nRetry = 0;
	while ((nTest <= 0) && (nRetry < 4)) {
		nRetry++;
		nTest = DSSaveData(szUser, szPath, szFile, szBuf);
		if (nTest <= 0)
			Sleep(3000);
	}
	if (nTest <= 0) {
		sprintf(szBuf, "ERROR (%s) NEW WRITE LOGFILE(DS) fail, err=%d", szUser, nTest);
		AddRecordMsg(szBuf);

		strcpy(szFile, g_tszPathName);
		strcat(szFile, "\\checklog.log");
		fl = fopen(szFile, "a+");
		if( fl)	{
			fprintf(fl,"%s\t%s	\n",szUser, "無法建檔!");
			fclose( fl);
		}
	}
	
	return;

}
//==========================================

int UserStartCheck(char *szUser)
{
	FILE *fl;
	char szPath[256], szFile[256], szBuf[DSBUFSIZE], szTest[64], szID[64];
	char *ps;
	int nTest, nRetry, nMin;
	CTime CurrentTime = CTime::GetCurrentTime(), BaseTime(1999,1,1,0,0,0);
	CTimeSpan TimeSpan;
	POSITION pos;

	szHashName(szUser, szPath);
	strcpy(szFile, szUser);
	strcat(szFile, ".log");
	nTest = -1; nRetry = 0;

	//andy_re
	memset( szBuf, 0, sizeof( szBuf));
	memset( szTest, 0, sizeof( szTest));
	memset( szID, 0, sizeof( szID));
	if( szPath != NULL && strcmp( szPath, "\0")){
		char filebuf1[256], buf1[256], buff1[256];
		FILE *filePath;
		sprintf( filebuf1,"%s\\%s\\%s", g_tszPathName, szPath, szFile);
		if( (filePath = fopen( filebuf1, "r+")) != NULL )	{
			while( fgets( buf1,sizeof(buf1), filePath) != NULL )	{
				strcat( szBuf,  buf1);
			}
			fclose( filePath);
			if( buff1 != NULL )	{
			}
		}else	{	//玩家檔案不存在
			if( CreatePlayerDir( szUser) == TRUE )	{
				AddRecordMsg("Create Player Dir...");
				sprintf( filebuf1,"%s\\%s\\%s", g_tszPathName, szPath, szFile);
				if( CreatePlayerFile( filebuf1) == TRUE )	{
					ResetPlayerLog( filebuf1);
				}
				return 0;
			}else
				return 0;
		}
	}

	ps = strtok(szBuf, "\n");
	while (ps) {
		strcpy(szTest, ps);
		ps = strtok(NULL, "\n");
	}
	szID[0] = 0; nMin = 99999999;
	sscanf(szTest, "%s %d", szID, &nMin);
	if ( strcmp(szID, "@") ) {
		if( !strcmp(szID, "\0") || nMin >= 99999999 || nMin <= 0 )	{
			EndCheck_PlayerLog(  szUser, TRUE);
			//UserEndLog( szUser, TRUE);
			return INVALIDLOG;
		}	else	{
			TimeSpan = CurrentTime - BaseTime;
			if ( (TimeSpan.GetTotalMinutes() - nMin) < ( STARTLOGGAP/60 + SAFELOGGAP) ) 
				return INVALIDLOG;
		}
	}

	EnterCriticalSection(&myglobs.csUserLog);
	pos = myglobs.userlist.GetHeadPosition();
	while (pos) {
		strcpy(szTest, myglobs.userlist.GetNext(pos));
		if (!strcmp(szTest, szUser)) {
			LeaveCriticalSection(&myglobs.csUserLog);
			return INVALIDLOG;
		}
	}
	myglobs.userlist.AddTail(szUser);
	strcpy(szFile, g_tszPathName);
	strcat(szFile, "\\user.log");
	fl = fopen(szFile, "a");
	if (fl) {
		fprintf(fl, "%s\n", szUser);
		fclose(fl);
	} else {
		LeaveCriticalSection(&myglobs.csUserLog);
		AddRecordMsg("ERROR could not open user.log for reading");
		PostMessage(myglobs.hWndMain,WM_CLOSE,0,0);
		return -10000;
	}
	LeaveCriticalSection(&myglobs.csUserLog);
	return 1;
}

int CheckUserLog(char *szUser)
{
	char szPath[256], szFile[256], szBuf[DSBUFSIZE], szTest[64], szID[64];
	char *ps;
	FILE *fp;
	char filebuf1[256], buf1[256];

	szHashName(szUser, szPath);
	strcpy(szFile, szUser);
	strcat(szFile, ".log");
	memset( szBuf, 0, sizeof( szBuf));
	sprintf( filebuf1,"%s\\%s\\%s", g_tszPathName, szPath, szFile);
	fp = fopen( filebuf1, "r");
	if( fp)	{
		while( fgets( buf1, sizeof( buf1), fp) != NULL )	{
			strcat( szBuf, buf1);
		}
		fclose( fp);
	}else	{
		return -1;
	}

	ps = strtok(szBuf, "\n");
	while (ps) {
		strcpy(szTest, ps);
		ps = strtok(NULL, "\n");
	}
	szID[0] = 0;
	sscanf(szTest, "%s", szID);
	if (strcmp(szID, myglobs.szID)) 
		return INVALIDLOG;
	return 1;
}

void ClearUserLog()
{
	FILE *fl;
	char szFile[256], szBuf[256];

	EnterCriticalSection(&myglobs.csUserLog);
	strcpy(szFile, g_tszPathName);
	strcat(szFile, "\\user.log");
	fl = fopen(szFile, "r");
	if (fl) {
		while (fscanf(fl, "%s", szBuf) != EOF) {
			if (CheckUserLog(szBuf) > 0) UserEndLog(szBuf, TRUE);
		}
		fclose(fl);
	}
	fl = fopen(szFile, "w");
	if (fl) fclose(fl);
	LeaveCriticalSection(&myglobs.csUserLog);
}

BOOL CreateDir( char *Path)	{
	if( CreateDirectory( Path, NULL) == FALSE )	{
		DWORD errMsg = GetLastError();
		if( errMsg == ERROR_ALREADY_EXISTS )	{
		}else if( errMsg == ERROR_DISK_FULL) {
			AddRecordMsg("空間已滿!!");
			return FALSE;
		}else
			return FALSE;
	}else	{
		AddRecordMsg("Creat Path...");
	}
	return TRUE;
}

BOOL CreatePlayerDir( CString name)
{

	char temp[21], temp2[10], userdir[60];
	unsigned int all,i;
	char buf1[256];
	userdir[0] = 0;
	strncpy(temp,name,20);
	for (all=0,i=0;i<strlen(temp);i++) {
		all+=temp[i];
		sprintf(temp2,"%02X",temp[i]);
		strcat(userdir, temp2);
	}
	sprintf(buf1, "%s\\playersave\\%02X",g_tszPathName, all%256);
	if( CreateDir( buf1) == FALSE )
		return FALSE;
	strcat( buf1, "\\_");
	strcat( buf1, userdir);
	if( CreateDir( buf1) == FALSE )
		return FALSE;
	return TRUE;
}

BOOL CreatePlayerFile( char *filename)
{
	HANDLE CFILE;
	CFILE = CreateFile( filename, 0, FILE_SHARE_DELETE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL );
	if( CloseHandle( CFILE) == FALSE )
		return FALSE;
	else
		return TRUE;
}

BOOL ResetPlayerLog( char *filename)
{
	FILE *fp;
	fp = fopen( filename, "w");

	if( fp != NULL )	{
		fputs( "@ 1\n", fp);
		fclose( fp);
	}else
		return FALSE;
	return TRUE;
}