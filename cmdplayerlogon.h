#if !defined(AFX_CMDPLAYERLOGON_H__96579658_8540_11D3_BA84_0000E8A021D8__INCLUDED_)
#define AFX_CMDPLAYERLOGON_H__96579658_8540_11D3_BA84_0000E8A021D8__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif
#include "Player.h"
#include "XmudOS.h"
void GetXFileName(CPlayerInfo * lpPlayerInfo);
class CCmdPlayerLogon  
{
public:
	void PlayerLogonCmdProc(SOCKET hPlayerSocket,char *UserName,
							char *PlayerName,
							char *stName,char *stPasswd,
							char *Result,
							sockaddr_in IPAddr,
							PCLientConData lpClientConData);
	int LoadPlayerSkill(CPlayerInfo * lpPlayerInfo);
	int LoadPlayerEquip(CPlayerInfo * lpPlayerInfo);
	CString GatherPlayerData(char *Result,CPlayerInfo * lpPlayerInfo);
	CString GatherPlayerSkillData(CPlayerInfo * lpPlayerInfo);
	CString GatherPlayerEquipData(CPlayerInfo * lpPlayerInfo);
	CString GatherMapData(CPlayerInfo * lpPlayerInfo);
	int CreatePlayerSkillFile(char *UserName,char *PlayerName);
	int CreatePlayerEquipFile(char *UserName,char *PlayerName);
	void PlayerCreateCmdProc(char *UserName,char *PlayerName,char *stNewPlayerName,char *stPassword,
			  char *stChineseName,char *sex,char *Strength,
			  char *Int,char *dex,char *con,char *Result);
	void PlayerDeleteCmdProc(char *UserName,char *PlayerName,char *Result);
	void PlayerOffLine(LPVOID pvPLayer,char* PlayerName,CString szUserCount);
	int SavePlayerData(CPlayerInfo * lpPlayerInfo);
	BOOL AppToMap(CPlayerInfo * lpPlayerInfo);
	CCmdPlayerLogon();
	virtual ~CCmdPlayerLogon();
};
#endif
