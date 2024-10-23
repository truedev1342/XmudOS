// MapClass.cpp: implementation of the CMapClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapClass.h"
#include "..\..\hash.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapClass::CMapClass()
{

}

CMapClass::~CMapClass()
{

}
void CMapClass::InitMap(char *szFileName)
{
	char *ps;
	char stemp1[256],stemp2[256];
	CString szStr;
	FILE *fp;
	char szBuf[DSBUFSIZE];
	int nTest,ntemp;
	TMapExit * lpMapExit;

	//strcpy(szFileName, szPath);
	//strcat(szFileName, "\\");
	//strcat(szFileName, szFile);
	fp = fopen(szFileName, "r");
	if(fp) {
		nTest = fread(szBuf, sizeof(char), DSBUFSIZE-1, fp);
		if (nTest > 0) {
			szBuf[nTest] = 0;
			
		} else {
			szCName = "ERROR";
			sprintf (szBuf, "Map (%s) Data is empty", szFileName);
			AddRecordMsg(szBuf);
			return;
		}
		fclose(fp);
	} else {
		szCName = "ERROR";
		sprintf (szBuf, "Map(%s) Open file error", szFileName);
		AddRecordMsg(szBuf);
		return;
	}

	ps = strtok(szBuf, "\n");
	while(ps) 
	{
		sscanf(ps,"%s",stemp1);
        szStr = stemp1;
		if(szStr == "中文名")
		{   
            sscanf(ps,"%s %s",stemp1,stemp2);
			szCName = stemp2;
		}
		else if(szStr == "英文名")
		{
			sscanf(ps,"%s %s",stemp1,stemp2);
			szEName = stemp2;
		}
		else if(szStr == "X模型")
		{
			sscanf(ps,"%s %s",stemp1,stemp2);
			szXFileName = stemp2;
		}
		else if(szStr == "所屬門派")
		{
			sscanf(ps,"%s %s",stemp1,stemp2);
			szFamily = stemp2;
		}
		else if(szStr == "狀態")
		{
			sscanf(ps,"%s %d",stemp1,&ntemp);
			nStatus = ntemp;
		}
		else if(szStr == "可動武")
		{
			sscanf(ps,"%s %d",stemp1,&ntemp);
			if(ntemp==1)
				bPK = TRUE;
			else
				bPK = FALSE;
		}
		else if(szStr == "[出口]")
		{
			lpMapExit = new TMapExit;
			do{
				ps = strtok(NULL, "\n");
				sscanf(ps,"%s",stemp1);
				szStr = stemp1;
				if(szStr == "出口名稱")
				{
					sscanf(ps,"%s %s",stemp1,stemp2);
					lpMapExit->szExitname = stemp2;
				}
				if(szStr == "通往地圖")
				{
					sscanf(ps,"%s %s",stemp1,stemp2);
					lpMapExit->szNexeMap = stemp2;
				}
				if(szStr == "相對出口")
				{
					sscanf(ps,"%s %s",stemp1,stemp2);
					lpMapExit->szNextMapExitName = stemp2;
				}
				if(szStr == "X座標")
				{
					sscanf(ps,"%s %s",stemp1,stemp2);
					lpMapExit->m_fPOSITION_X = stemp2;
				}
				if(szStr == "Y座標")
				{
					sscanf(ps,"%s %s",stemp1,stemp2);
					lpMapExit->m_fPOSITION_Y = stemp2;
				}
			}while(szStr!="[出口結束]");
			listexit.AddTail(lpMapExit);
		}
		ps = strtok(NULL, "\n");
	}
}
