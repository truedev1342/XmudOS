// CommandCheck.h: interface for the CCommandCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDCHECK_H__96579656_8540_11D3_BA84_0000E8A021D8__INCLUDED_)
#define AFX_COMMANDCHECK_H__96579656_8540_11D3_BA84_0000E8A021D8__INCLUDED_

#include "CmdPlayerLogon.h"
#include "Goods\Goods\Goods.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _TChatChannel
{
	CString m_sTITLE;
	CPlayerInfo *lpPlayerInfo;
	//BOOL bMaster;
	/*
	CString m_sCNAME;
	CString m_sENAME;
	CString	m_sSEX;
	CString m_sNICKNAME;
	CString	m_sFAMILY;
	CString m_iIPAddr;
	SOCKET hPlayerSocket;
	*/
}TChatChannel,*PChatChannel;

class CCommandCheck
{
public:
	// Spock start
	BOOL CheckGM(char* UserName);
	// Spock end
	void UserLogonCmdProc(char *UserName,sockaddr_in IPAddr,char *stName,char *stPasswd,char *Result);
	void ProcessPlayerCommand(SOCKET hPlayerSocket,	CStringList *Command, char *Result,
							sockaddr_in IPAddr,	char *UserName,	char *PlayerName, LPVOID &pvPlayer,
							PCLientConData lpConData);
	void ChangeMapProc(char* PlayerName,char* sMapName,char* Result,LPVOID pvPlayer,sockaddr_in IPAddr);
	void SendMapDataProc(char* PlayerName,char* sMapName,char* Result,
				LPVOID pvPlayer,sockaddr_in IPAddr);
	//頻道和聊天
	CString JoinChannelCmdProc(char * szWhichTitle);
	void CreateOrJoinChannel(SOCKET hPlayerSocket,char* PlayerName,char* Title,	char *Result,LPVOID pvPlayer);
//	void GetChannelCmdProc(SOCKET hPlayerSocket);
	void GetChannelCmdProc(CPlayerInfo *lpPlayerInfo);
	void ChannelTalkProc(char *szWhichTitle,char *szTalkSome);
//	void TellToSomeOne(SOCKET hPlayerSocket,char *playerName,char *szWhichOne,char *szTalkSome);

	void GmRunSomeOne(CPlayerInfo *me,char *playerName,char *szWhichOne, const char *szTalkSome);

	void TellToSomeOne(CPlayerInfo *me,char *playerName,char *szWhichOne,char *szTalkSome);
	void EmoteProc(LPVOID pvPlayer, const char *playerName, const char *szWhichTitle, const char * szEmote, const char *szWho);
	void DefendTellProc(CPlayerInfo *me,char *playerName,char *szWhichOne);
	void DefendDelProc(CPlayerInfo *me,char *playerName,char *szWhichOne);
	void GetOutProc(CPlayerInfo *me,char *playerName,char *szWhichOne);
 
	// Spock start
	void ExitChannelProc(CPlayerInfo *lpPlayerInfo,char *Result);
	BOOL ShoutProc(CPlayerInfo *lpPlayerInfo, CString szShout, BOOL bGM);
	BOOL GmShoutProc(CPlayerInfo *lpPlayerInfo, CString szShout, BOOL bGM);
	// Spock end
	//動作指令
	void KillProc(LPVOID pvPlayer,char *playerName,char * szKillOpp,char *Result);
	void FightProc(LPVOID pvPlayer, const char* playerName, const char* szKillOpp, const char* szRound, char* Result);
	void DazuoProc(LPVOID pvPlayer,char *szTime,char *Result);//打坐
	void TuNaProc(LPVOID pvPlayer,char *szTime,char *Result);//吐納
	void MappingProc(LPVOID pvPlayer, char *szSkillBase, char *szSkillMap, char *Result);//準備
	void PracticeProc(LPVOID pvPlayer,char *szSkillBook,char *szTimes,char *Result);//練習技能
	void YunGongProc(LPVOID pvPlayer,char *szNumber,char *Result);//運功

	void ApprenticeProc(LPVOID pvPlayer,char *szWho,char *Result);//拜師
	void LearenProc(LPVOID pvPlayer,char *szWho,char *szWhichSkill,char *nTimes,char *Result);//學習技能
	void GetMasterSkill(LPVOID pvPlayer,char *szWho,char *Result);//得到師傅的技能
	//void AskProc(LPVOID pvPlayer,char *szWho, char * szSth, char *Result);//ask npc
	void AskProc(LPVOID pvPlayer,char *szWho, char * szSth1,char * szSth2, char *Result);//ask npc
	void LookProc(LPVOID pvPlayer,char *szSth1, char * szSth2, char *Result);//look npc


	BOOL GetNames( char *szSth1, char * szSth2 );
//dainty	
	//void UseProc(LPVOID pvPlayer,char *szWhichItem,char *Result);
	void UseProc(LPVOID pvPlayer,char *szWhichItem,int nUseNum,char *Result);

	void RentListProc(LPVOID pvPlayer,char *Result);
	//void EatProc(CPlayerInfo *lpPlayerInfo,CFood *lpFood,char *Result);
	void EatProc(CPlayerInfo *lpPlayerInfo,CFood *lpFood , int iUseNum,char *Result);

	//void DrinkProc(CPlayerInfo *lpPlayerInfo,CJiuDai *lpJiuDai,char *Result);
	void DrinkProc(CPlayerInfo *lpPlayerInfo,CJiuDai *lpJiuDai, int iUseNum, char *Result);
	
	void DrugUseProc(CPlayerInfo *lpPlayerInfo,CDrug *lpDrug, int dUseNum, char *Result);

	void ShootProc(CPlayerInfo *lpPlayerInfo,CWeapon *lpDrug,char *Result); //ANDY_NEW 2001.2.26 10:18
	void ArmProc(LPVOID pvPlayer,char *szWhichItem,char *Result);//裝備
	void UnArmProc(LPVOID pvPlayer,char *szWhichItem,char *Result);//解除裝備
    void GiveProc(LPVOID pvPlayer,char *szWho,char * szGoods,char *szAmount,char *Result);
	void DropProc(LPVOID pvPlayer,char * szDropGoods,char *Result);
	void RentProc(LPVOID pvPlayer,char * szRentGoods,char *Result);
//dainty end

// guanhua 2000/09/07 +1
	void EscapeProc(char* PlayerName,char* Result,LPVOID pvPlayer,sockaddr_in IPAddr);
	
	CCommandCheck();
	virtual ~CCommandCheck();

};

#endif // !defined(AFX_COMMANDCHECK_H__96579656_8540_11D3_BA84_0000E8A021D8__INCLUDED_)
