// LoadAllNeedFill.cpp: implementation of the CLoadAllNeedFill class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmudOS.h"
#include "MainWnd.h"
#include "LoadAllNeedFill.h"

extern char g_tszPathName[256];
extern CList <TDataUser*,TDataUser*>userlist;

CLoadAllNeedFill::CLoadAllNeedFill()
{

}

CLoadAllNeedFill::~CLoadAllNeedFill()
{

}

BOOL CLoadAllNeedFill::LoadUserInfo()
{
	TDataUser* lpDataUser;

	CStringList strls;
	LPTSTR lpsz;
	CFile file;
	CString buf;
	CString parm;
	char *ps;

	char pFileName[256];
	strcpy(pFileName,g_tszPathName);
	strcat(pFileName,"\\userdata\\userdata.txt");

	if( !file.Open( pFileName, CFile::modeRead ) )
		return FALSE;
	CArchive ar(&file,CArchive::load);
	while(ar.ReadString(buf))
	{
		int i=0;
		lpsz = buf.GetBuffer(buf.GetLength()+1);
		parm=CString("\t");
		ps=strtok(lpsz,(const char*)parm);
		if(ps==NULL)
			return FALSE;
		strls.AddTail(ps);
		for(;;)
		{
			ps=strtok(NULL,(const char*)parm);
			if(ps==NULL) break;
			i++;
			strls.AddTail(ps);
		}
		if (i!=6)return FALSE;	//有6項數據字段

		CString strtmp;
		int itmp;
		lpDataUser = new TDataUser;

		strtmp=strls.GetAt(strls.FindIndex(0));
		lpDataUser->UserAccountName=strtmp.Mid(1,strtmp.GetLength()-2);

		strtmp=strls.GetAt(strls.FindIndex(1));
		lpsz = strtmp.GetBuffer(20);
		itmp=strtol(lpsz, nullptr,10);
		strtmp.ReleaseBuffer();
		lpDataUser->iEnableStat=itmp;
		
		strtmp=strls.GetAt(strls.FindIndex(2));
		lpsz = strtmp.GetBuffer(20);
		itmp=strtol(lpsz, nullptr,10);
		strtmp.ReleaseBuffer();
		lpDataUser->iPlayerNum = itmp;

		strtmp=strls.GetAt(strls.FindIndex(3));
		lpDataUser->szPassWord=strtmp.Mid(1,strtmp.GetLength()-2);

		strls.RemoveAll();
		userlist.AddTail(lpDataUser);
	}
	ar.Close();
	file.Close();
	return TRUE;
}
