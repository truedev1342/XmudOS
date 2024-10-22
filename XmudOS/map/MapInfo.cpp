#include "stdafx.h"
#include "MapInfo.h"
#include "dainty\MapClass.h"
#include "..\hash.h"

extern char g_tszPathName[256];
extern CList <CBaseMap*,CBaseMap*>maplist;
void LoadMap();

CBaseMap::CBaseMap()
{
	bPK = TRUE;
	szFamily.Empty();
}

CBaseMap::~CBaseMap()
{

}
CString CBaseMap::AddGoods(CGoods *lpEquip)
{
	CGoods *lpMyEquip;
	POSITION pos;
	BOOL bFind = FALSE;

	if ((lpEquip->lpGoods->nKinds == GK_food) ||
		(lpEquip->lpGoods->nKinds == GK_drug)) {
		pos = listequip.GetHeadPosition();
		while (pos!=NULL) {
			lpMyEquip = listequip.GetNext(pos);
			if (lpMyEquip->lpGoods->szEName == lpEquip->lpGoods->szEName) {
				bFind = TRUE;
				lpMyEquip->nCount += lpEquip->nCount;
				delete lpEquip;
				break;
			}
		}
		if (!bFind)	listequip.AddTail(lpEquip);
	} else {
		lpEquip->nCount = 1;
		listequip.AddTail(lpEquip);
	}
	return CString("OK");
}

CString CBaseMap::SetGoods(CGoods *lpEquip)
{
	CGoods *lpMyEquip;
	POSITION pos;
	BOOL bFind = FALSE;

	if (lpEquip->lpGoods->nKinds == GK_flag) {
		pos = listequip.GetHeadPosition();
		while (pos!=NULL) {
			lpMyEquip = listequip.GetNext(pos);
			if (lpMyEquip->lpGoods->szEName == lpEquip->lpGoods->szEName) {
				bFind = TRUE;
				lpMyEquip->nCount = lpEquip->nCount;
				delete lpEquip;
				break;
			}
		}
		if (!bFind)	listequip.AddTail(lpEquip);
	}
	else	return CString("Not Flag");
	return CString("OK");
}

CString CBaseMap::SubGoods(CString szName)
{
	POSITION lastpos, pos;
	CGoods * lpGoods;

	pos = listequip.GetHeadPosition();
	while (pos != NULL) {
		lastpos = pos;
		lpGoods = listequip.GetNext(pos);
		if (lpGoods != NULL) {
			if ((lpGoods->lpGoods->szEName == szName) ||
				(lpGoods->lpGoods->szCName == szName)) {
				lpGoods->nCount--;
				if (lpGoods->nCount <= 0) {
					listequip.RemoveAt(lastpos);
					delete lpGoods;
				}
				return "OK";
			}
		}
	}
	return "沒有這個物品";
}

void InitAllMap()
{
	LoadMap();
}

void LoadMap()
{
	CMapClass *lpBaseMap;
	FILE *fp,*fpDir;
	char filename[128],temp[128],szDir[128];
	char pathname[128];
	char szBuf[DSBUFSIZE];

	strcpy(pathname, g_tszPathName);
	strcat(pathname,"\\map\\");
	strcpy(filename,pathname);
	strcat(filename,"dir.txt");
	if((fpDir=fopen(filename,"r"))!=NULL){
		while(fscanf(fpDir,"%s",szDir)!=EOF){
			strcpy(filename,pathname);
			strcat(filename,szDir);
			strcat(filename,"\\_map.txt");
			if((fp=fopen(filename,"r"))!=NULL){
				while(fscanf(fp,"%s",temp)!=EOF){
					strcpy(filename,pathname);
					strcat(filename,szDir);
					strcat(filename,"\\");
					strcat(filename,temp);
					strcat(filename,".txt");
					lpBaseMap = new CMapClass;			
					if(lpBaseMap!=NULL){
						lpBaseMap->InitMap(filename);
						maplist.AddTail(lpBaseMap);
					}else	{
						sprintf (filename, "Map(%s) initialize error",temp);
						AddRecordMsg(filename);
					}
				}
				fclose(fp);
			}else{
				sprintf (szBuf, "Map index(%s) Open file error", filename);
				AddRecordMsg(szBuf);
			}
		}
		fclose(fpDir);
	}else{
		sprintf (szBuf, "%s open file error", filename);
		AddRecordMsg(szBuf);
	}
}