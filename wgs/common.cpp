#include "stdafx.h"
#include <windows.h>
#include "StreamSocket.h"
#include "Common.h"
#include "wsa_xtra.h"
#include "../Common.h"
#include "../xmudos.h"
extern rmfullglobals myglobs;
PlayerName	*playerStartHead=NULL;
PlayerName	*playerEndHead=NULL;
int			iNumStart=0;
int			iNumEnd=0;

CRITICAL_SECTION csPlayerStart;
CRITICAL_SECTION csPlayerEnd;

extern	int		g_iActiveClientNum;
extern	char	g_tszPathName[256];

StreamSocket sockListen;


void InitPlayer(HWND hwnd)
{
	SetTimer(hwnd,7,1000,NULL);
	InitializeCriticalSection(&csPlayerStart);
	InitializeCriticalSection(&csPlayerEnd);
}

void ReleaseNet()
{
	EnterCriticalSection(&csPlayerStart);
	EnterCriticalSection(&csPlayerEnd);
	sockListen.closeing();
	DeleteStartList();
	DeleteEndList();
	LeaveCriticalSection(&csPlayerEnd);
	LeaveCriticalSection(&csPlayerStart);
}

BOOL Add_UserStart(char *szUser)
{
	int iLen=strlen(szUser)+1;
	if(iLen<=1)
		return TRUE;
	EnterCriticalSection(&csPlayerStart);
	PlayerName	*playerNew;
	if(NULL!=(playerNew=new PlayerName)){
		if(NULL!=(playerNew->lpstrName=new char[iLen])){
			strcpy(playerNew->lpstrName,szUser);
			playerNew->next=NULL;
			if(iNumStart==0)
				playerStartHead=playerNew;
			else{
				playerNew->next=playerStartHead;
				playerStartHead=playerNew;
			}
			iNumStart++;
			LeaveCriticalSection(&csPlayerStart);
			return TRUE;
		}else
			delete playerNew;
	}
	LeaveCriticalSection(&csPlayerStart);
	return FALSE;
}

BOOL Add_UserEnd(char *szUser)
{
	int iLen=strlen(szUser)+1;
	if(iLen<=1)	return TRUE;
	iLen++;
	EnterCriticalSection(&csPlayerEnd);
	PlayerName	*playerNew;
	if(NULL!=(playerNew=new PlayerName)){
		if(NULL!=(playerNew->lpstrName=new char[iLen]))	{
			strcpy(playerNew->lpstrName,szUser);
			playerNew->next=NULL;
			if(iNumEnd==0)
				playerEndHead=playerNew;
			else{
				playerNew->next=playerEndHead;
				playerEndHead=playerNew;
			}
			iNumEnd++;
			LeaveCriticalSection(&csPlayerEnd);
			return TRUE;
		}else
			delete playerNew;
	}
	LeaveCriticalSection(&csPlayerEnd);
	return FALSE;
}

void DeleteStartList()
{
	PlayerName *playerTemp;
	while(playerStartHead){
		playerTemp=playerStartHead->next;
		if(playerStartHead->lpstrName)
			delete[] playerStartHead->lpstrName;
		delete playerStartHead;
		playerStartHead=playerTemp;
	}
}

void DeleteEndList()
{
	PlayerName *playerTemp;
	while(playerEndHead){
		playerTemp=playerEndHead->next;
		if(playerEndHead->lpstrName)
			delete[] playerEndHead->lpstrName;
		delete playerEndHead;
		playerEndHead=playerTemp;
	}
}
