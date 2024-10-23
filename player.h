#ifndef __PLAYER_H__
#define __PLAYER_H__

#define FIRSTSTARTTIME	10
#define SAVEGAP			3600
#define SAVEWAIT		300
#define STARTLOGGAP		600
#define RETRYGAP		60
#define SAFELOGGAP		35
#define SAVERETRY		3
#define MAXSHEN			5000000
#define MAXEXP			99999999
#define MAXADDFORCE		99
#define MAXADDJINGLI	99
#define MAXMONEY		99999999
#define BASEATTR		100
#define MINATTR			10
#define MAXATTR			35
#define PS_moneyfixed	0x01
#define PS_nofight		0x02
#define PS_attrfixed	0x04
#include "ActiveObject.h"

#define AOS_changemapok	((AOS_act_changemap)|3)
#define AOS_sendmap		((AOS_act_changemap)|4)
#define AOS_sendmapok	((AOS_act_changemap)|5)


class CPlayerInfo : public CActiveObject
{
public:
	int		nEat;
	int		nMax_Eat;
	int		nDrink;
	int		nMax_Drink;
	int		nKillNpc;
	int		nKillPlayer;
	int		nKilled;
	int		nPlayerStatus;
	int		nBetray;
	int		nMudTime;
	
	int		nWaitNext;
	
	CString	szUserName;
	CString	szPassWord;

	BOOL	bAttack;
	int		nBankMoney;
	CStringList	listmsg;
	BOOL	bRun;
	CStringList listBetray;
	BOOL	bSaved;
	int		nRound;
	CStringList	DefTellList;
	sockaddr_in IPAddr;
	SOCKET hPlayerSocket;
public:
	CPlayerInfo();
	virtual ~CPlayerInfo();
	void Healing();
	void SendAllInfo();
	void SendHeal();
	int  SendMsg(CString szMsg);
};
#endif