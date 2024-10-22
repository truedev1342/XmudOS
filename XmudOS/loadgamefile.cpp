#include "stdafx.h"
#include "XmudOS.h"
#include "MainWnd.h"
#include "ShowMsg.h"
#include "LoadAllNeedFill.h"
#include "map\MapInfo.h"
#include "Common.h"

extern ShowMsg m_ShowMsg;
extern rmfullglobals myglobs;
extern int	g_iActiveClientNum;
extern char g_tszPathName[256];

#include < time.h >
#include < stdio.h >
#include < sys/types.h >
#include < sys/timeb.h >
#include < string.h >

void AddRecordMsg(const char * szMsg)
{
	static char msg1 [128*256] = "";
	static char msg2 [128*256] = "";
	static char msg3 [128*256] = "";
	static char err[256] = "", num[256] = "";
	EnterCriticalSection(&myglobs.csRecordMsg);
	CTime CurrentTime=CTime::GetCurrentTime();
	if(strlen(msg1) > 2000 || strlen(msg2) > 2000)	{
		msg1[0] = 0;
		msg2[0] = 0;
	}
	if (!strncmp(szMsg,"ERROR",5)) {
		strcpy(err, "Last Error: ");
		strcat(err, szMsg);
		strcat(err, "\r\n�ССССССССССССССССССССССССССССС�\r\n");
	}
		if (strncmp(szMsg,"Heart",5)) {
			fprintf(myglobs.flog, "%s %s\n",CurrentTime.Format("%Y/%m/%d %H:%M:%S"), szMsg);
				strcpy(msg1,szMsg);
				strcat(msg1,"\r\n");
		} else {
			sprintf(num,"v%s  Players %d  Threads %d  %s\r\n",XMUDVER,
				g_iActiveClientNum,myglobs.nPlayerThreadNum,szMsg);
			msg1[0] = 0;
		}
		strcat(msg1,msg2);
		strcpy(msg3,num);
		strcat(msg3,err);
		strcat(msg3,msg1);
		strcpy( msg2, msg1);

	if (myglobs.nRunTimes >= 0) m_ShowMsg.SetWindowText (msg3);
	LeaveCriticalSection(&myglobs.csRecordMsg);
}

void ProcessMessage(void)
{
	MSG Msg;
	if(PeekMessage(&Msg,NULL,0,0,PM_REMOVE)){
		if(Msg.message==WM_DESTROY){
			AfxMessageBox(_T("Quit La!"));
			exit(1);
		}else	{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
}

