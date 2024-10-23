#include "stdafx.h"
#include "XmudOS.h"
#include "CmdPlayerLogon.h"
#include "skill\skill\Skill.h"
#include "math.h"
#include "wgs\Common.h"

extern rmfullglobals myglobs;

CPlayerInfo::CPlayerInfo()
{
	nDamage = 20;
	nMudTime = 86400;
	bRun = FALSE;
	bSaved = FALSE;
	nRound = 0;
//	nWaitNext = 0;
}

CPlayerInfo::~CPlayerInfo()
{
	listmsg.RemoveAll();
	listBetray.RemoveAll();
}

void CPlayerInfo::Healing()
{
//	char szTest[128];
	//更新年齡
	nMudTime -= HEALINGGAP;
	if( nMudTime < 0 ) 
	{ 
		//nMudTime += 86400; 
		nMudTime += 100000;
		nAge++;
	}

// guanhua 2000/10/02 remark +1
//	nRound += HEALINGGAP;

	if (szNickName != "充氣娃娃") {
		if( nDrink > 0 )
		{
			nDrink --;
		}
		if( nEat > 0 )
		{
			nEat --;
		}
		if(nDrink <= 0) {
			nEff_qi -= 5;
			nMax_qi -= 5;
		}
		if(nEat <= 0) {
			nEff_qi -= 5;
			nMax_qi -= 5;
		}
	}
	if(nEff_qi < 0) nEff_qi = 0;
	if(nMax_qi < 0) nMax_qi = 0;
	if((nMax_qi <= 0) && (nStatus != AOS_kill) && (nStatus != AOS_fight)) {
		CString szSend;
		szSend.Format("%s %s %s因過度",SZOKMSG,szRedHigt,szCName);
		if (nEat<=0) szSend += CString("饑餓");
		if (nDrink<=0) szSend += CString("口渴");
		szSend += CString("終於不支倒地了！");
		SendMsgToAll(szSend);
		SendMsg(szSend);
		Die();
		SendAllInfo();
		return;
	}
	if(bNoHealing) return;

	// Spock start
	if((nDrink > 0) && (nEat > 0))
	{
		if (nStatus != AOS_tuna) {
			nEff_jing += nCon / 3 + (int)sqrt(nMax_jingli);
			if( nEff_jing >= nMax_jing )
				nEff_jing = nMax_jing;
			ReceiveJing();
		}
		if (nStatus != AOS_dazuo) {
			nEff_qi += nCon / 3 + (int)sqrt(nMax_force);
			if( nEff_qi >= nMax_qi )
				nEff_qi = nMax_qi;
			ReceiveCure();
		}
		if( nEff_force < nMax_force )
		{
			nEff_force += GetSkillLevel("BaseForce") / 2 + 2 + nMax_force/20;
			if((nEff_force > nMax_force) && (nStatus != AOS_dazuo))
				nEff_force = nMax_force;
		}
		if( nEff_jingli < nMax_jingli )
		{
			nEff_jingli += GetSkillLevel("BaseForce") / 2 + 2 + nMax_jingli/20;
			if((nEff_jingli > nMax_jingli) && (nStatus != AOS_tuna))
				nEff_jingli = nMax_jingli;
		}
	}
	// Spock end;
	SendHeal();
}
//cary
void CPlayerInfo::SendAllInfo()
{
	CString szStatus;
	szStatus.Format("%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",
		SZSENDALLINFO,
		" ",
		nAge,
		nShen,
		nStr,
		nInt,
		nCon,
		nDex,
		nEff_qi,
		nMax_qi,
		nEff_jing,
		nMax_jing,
		nEff_jingli,
		nMax_jingli,
		nAdd_Jingli,
		nEff_force,
		nMax_force,
		nAdd_force,
		nCombat_exp,
		nQianNeng,
		nScore,
		nGeneration,
		nMoney,
		nStatus,
		nEat,
		nMax_Eat,
		nDrink,
		nMax_Drink,
		nKillNpc,
		nKillPlayer,
		nKilled,
		nPlayerStatus,
		nBetray,
		nMudTime,
		szTilte);
//cary
	SendMsg(szStatus);
//end
}

void CPlayerInfo::SendHeal()
{
	CString szStatus;
	szStatus.Format("%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d",
		SZHEALING,
		" ",
		nAge,
		nDrink,
		nEat,
		nEff_jing,
		nMax_jing,
		nEff_qi,
		nMax_qi,
		nEff_force,
		nEff_jingli);
//cary
	SendMsg(szStatus);
//end
}
 
int CPlayerInfo::SendMsg(CString szMsg)
{
	int nRet = 0;
	char szTest[512];
	if (bRun)	{
		EnterCriticalSection(&myglobs.csSentCliMsg);
		if (listmsg.GetCount() < 50)	{
			listmsg.AddTail(szMsg);
			nRet = szMsg.GetLength();
		}else	{
			sprintf(szTest, "ERROR (%s,%s) listmsg full", szEName, szUserName);
			AddRecordMsg(szTest);
			nRet = -1;
		}
		LeaveCriticalSection(&myglobs.csSentCliMsg);
	}
	return nRet;
}
