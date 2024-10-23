#include "stdafx.h"
#include "XmudOS.h"
#include "MainWnd.h"
#include "CmdPlayerLogon.h"
#include "CommandCheck.h"
#include "map\MapInfo.h"
#include "skill\skill\Skill.h"
#include "wgs\common.h"
// Nuke +1
#include "hash.h"
// Spock start
#include "Fight.h"

extern CList <CFight*,CFight*>fightlist;
extern CList <CFight*,CFight*>killlist;
// Spock end
extern char g_tszPathName[256];
extern rmfullglobals myglobs;
extern CList <CBaseMap*,CBaseMap*>maplist;
extern CList <TChatChannel*,TChatChannel*>chatchannellist;
extern CList <TDataUser*,TDataUser*>userlist;
extern int g_iActiveClientNum;


// Spock start
int CCmdPlayerLogon::SavePlayerData(CPlayerInfo *lpPlayerInfo)
{
	CString strtmp, sResultMsg, szTemp;
	char szPath[256], szFileName[256];
	int i,j,rn;
	TObjectSkill* lpPlayerSkill;
	CGoods* lpPlayerEquip;
	BOOL bFindHead = FALSE;
	char itmpString[20];
	CString sign = CString("\"");
	CString parm = CString(" ");
	//POSITION pos;

	// Check start
	if (lpPlayerInfo == NULL) {
		AddRecordMsg("NULL player data in SavePlayerData");
		return -4000;
	}
	if (strcmp(lpPlayerInfo->szCheck, SZAOBJCHECK)) {
		AddRecordMsg("Bad player data in SavePlayerData");
		return -5000;
	}
	// Check end
//ANDY_ADD	REPUT ITEM
			POSITION pos,RunPos,lastpos;
			CGoods *lpCheckGoods = NULL;
			CGoods *lpReGoods = NULL;
			//lpPlayerInfo = (CPlayerInfo*)lpClientConData->pvPlayer;
			pos = lpPlayerInfo->listequip.GetHeadPosition();
			RunPos = pos;
			while( RunPos != NULL)	{
				lpReGoods = lpPlayerInfo->listequip.GetNext( RunPos);
				pos = RunPos;
				while( pos != NULL)	{
					lastpos = pos;
					lpCheckGoods = lpPlayerInfo->listequip.GetNext( pos);
						if( !strcmp(lpCheckGoods->lpGoods->szEName, lpReGoods->lpGoods->szEName))	{
							lpReGoods->nCount += lpCheckGoods->nCount;
							lpPlayerInfo->listequip.RemoveAt( lastpos);
							pos = lpPlayerInfo->listequip.GetHeadPosition();
							RunPos = pos;
							break;
						}
				}
			}
//END

	//儲存 .inf 檔
	sResultMsg = lpPlayerInfo->szCName + ("\n");
	sResultMsg += lpPlayerInfo->szEName + ("\n");
	sResultMsg += lpPlayerInfo->szNickName + ("\n");
	sResultMsg += lpPlayerInfo->szTilte + ("\n");
	sResultMsg += lpPlayerInfo->szXFileName + ("\n");
	sResultMsg += lpPlayerInfo->szFamily + ("\n");
	sResultMsg += lpPlayerInfo->szRoom + ("\n");
	sResultMsg += lpPlayerInfo->szSex + ("\n");

	strtmp.Format("%d",lpPlayerInfo->nAge);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nShen);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nStr);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nInt);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nCon);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nDex);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nEff_qi);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nMax_qi);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nEff_jing);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nMax_jing);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nEff_jingli);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nMax_jingli);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nAdd_Jingli);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nEff_force);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nMax_force);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nAdd_force);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nCombat_exp);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nScore);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nGeneration);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nMoney);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nStatus);
	sResultMsg +=  strtmp + ("\n");

	sResultMsg +=  lpPlayerInfo->szTeacher + ("\n");
	sResultMsg +=  lpPlayerInfo->szPerson + ("\n");

	strtmp.Format("%d",lpPlayerInfo->nQianNeng);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nEat);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nMax_Eat);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nDrink);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nMax_Drink);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nKillNpc);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nKillPlayer);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nKilled);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nPlayerStatus);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nBetray);
	sResultMsg +=  strtmp + ("\n");
	strtmp.Format("%d",lpPlayerInfo->nMudTime);
	sResultMsg +=  strtmp + ("\n");

	sResultMsg +=  lpPlayerInfo->szUserName + ("\n");
	sResultMsg +=  lpPlayerInfo->szPassWord + ("\n");

	strtmp.Format("%d",lpPlayerInfo->nBankMoney);
	sResultMsg +=  strtmp + ("\n");

	strtmp.Empty();
	pos = lpPlayerInfo->listBetray.GetHeadPosition();
	if (pos) strtmp = lpPlayerInfo->listBetray.GetNext(pos);
	while (pos) {
		strtmp += CString(",") + lpPlayerInfo->listBetray.GetNext(pos);
	}
	sResultMsg +=  strtmp + ("\n");
	CString ReString;
	for(int y=0; y<10;y++)	{
		if(lpPlayerInfo->nRefile[y] >= 0 )
			ReString.Format("%d",lpPlayerInfo->nRefile[y]);
		else 
			ReString.Format("%d",0);
		sResultMsg +=  ReString + (",");
	}
	sResultMsg +=  ("\n");

	szHashName(lpPlayerInfo->szUserName, szPath);
	strcpy(szFileName,lpPlayerInfo->szEName);
	strcat(szFileName,".inf");
	rn = DSSaveData((char*)(LPCSTR)lpPlayerInfo->szUserName, szPath, szFileName,sResultMsg);
	if (rn <= 0) return rn-1000;

	// 儲存 .skill
	sResultMsg.Empty();
	j = lpPlayerInfo->listskill.GetCount();
	for(i=0;i<j;i++)
	{
		lpPlayerSkill = lpPlayerInfo->listskill.GetAt(lpPlayerInfo->listskill.FindIndex(i));

		sResultMsg += sign + lpPlayerSkill->lpSkill->szEName + sign + parm;

		itoa(lpPlayerSkill->nScore,itmpString,10);
		sResultMsg += itmpString+parm;

		itoa(lpPlayerSkill->nLevel,itmpString,10);
		sResultMsg += itmpString+parm;

		sResultMsg += sign+lpPlayerSkill->szMapping+sign + parm + CString("\n");
		
/*		itoa(lpPlayerSkill->lpSkill->nCanMap,itmpString,10);
		sResultMsg += itmpString+parm;

		itoa(lpPlayerSkill->lpSkill->nType,itmpString,10);
		sResultMsg += itmpString+parm+CString("\n");
*/	}
	lstrcpy(szFileName,lpPlayerInfo->szEName);
	lstrcat(szFileName,".skill");
	rn = DSSaveData((char*)(LPCSTR)lpPlayerInfo->szUserName, szPath, szFileName,sResultMsg);
	if (rn <= 0) return rn-2000;

	// Save player equips
	sResultMsg.Empty();
	j = lpPlayerInfo->listequip.GetCount();
	for(i=0; i<j; i++) {
		lpPlayerEquip = lpPlayerInfo->listequip.GetAt(lpPlayerInfo->listequip.FindIndex(i));
		szTemp = lpPlayerEquip->GetSaveData();
		if (!szTemp.IsEmpty()) {
			sResultMsg += szTemp+CString("\n");
		}
	}

	j = lpPlayerInfo->listrentequip.GetCount();	// 寄物
	for(i=0; i<j; i++) {
		lpPlayerEquip = lpPlayerInfo->listrentequip.GetAt(lpPlayerInfo->listrentequip.FindIndex(i));
		szTemp = lpPlayerEquip->GetSaveData();
		if (!szTemp.IsEmpty()) {
			sResultMsg += szTemp+CString("\n");
		}
	}

//	lstrcpy(szFileName,szHashName(lpPlayerInfo->szUserName));
	lstrcpy(szFileName,lpPlayerInfo->szEName);
	lstrcat(szFileName,".equip");
	rn = DSSaveData((char*)(LPCSTR)lpPlayerInfo->szUserName, szPath, szFileName,sResultMsg);
	if (rn <= 0) return rn-3000;
	return 1;
}
// Spock end

void CCmdPlayerLogon::PlayerOffLine(LPVOID pvPLayer,char* PlayerName,CString szUserCount)
{
	CBaseMap* lpDataMap;
	TChatChannel* lpChatChannel;

	CPlayerInfo* lpPlayerInfo;

	POSITION MapPosite;
	BOOL bFindHead = FALSE;
	
	CString sResultMsg, szTemp;
	CString sign = CString("\"");
	CString parm = CString("\t");
	// Spock start
	POSITION lastpos,pos,opos;
	CFight *lpFight;
	CActiveObject *lpOpp, *lpOpp2;
	CString szFight;
	// Spock end
	// test +1
	char szTest[256];

	lpPlayerInfo = (CPlayerInfo*)pvPLayer;
	MapPosite	=	lpPlayerInfo->pMapPosite;

	// guanhua 2000/09/21 start
	// 玩家斷線(不正常)時若仍在切磋(死鬥)中，則會切磋(死鬥)到結束才離線。
	// PS. 斷線後 5分鐘若切磋(死鬥)仍未結束，則自動離線。
	int nRound = 600; // while 最多執行 600 次 (5分鐘)
	while( ( (lpPlayerInfo->nStatus == AOS_fight) || (lpPlayerInfo->nStatus == AOS_kill) || (lpPlayerInfo->nStatus == AOS_unconcious) ) && (nRound > 0) )
	{
		Sleep(500);
		nRound--;
	}
	// guanhua 2000/09/21 end

	// Spock start
	szFight.Empty();
	EnterCriticalSection(&myglobs.csFightlist);
	EnterCriticalSection(&myglobs.csMaplist);
	EnterCriticalSection(&myglobs.csChatChannel);
	// 在killlist和fightlist中刪除player
	if (lpPlayerInfo->nStatus == AOS_fight) {
		pos = fightlist.GetHeadPosition();
		while (pos != NULL) {
			lastpos = pos;
			lpFight = fightlist.GetNext(pos);
			// Check NULL pointer and bad data
			if (lpFight == NULL) {
				AddRecordMsg("ERROR NULL pointer in PlayerOffline, lpFight");
				fightlist.RemoveAt(lastpos);
				continue;
			}
			if (lpFight->lpActiveObject == NULL) {
				AddRecordMsg("ERROR NULL pointer in PlayerOffline, lpFight->lpActiveObject");
				fightlist.RemoveAt(lastpos);
				delete lpFight;
				continue;
			}
			if (strcmp(lpFight->lpActiveObject->szCheck,SZAOBJCHECK)) {
				AddRecordMsg("ERROR Bad data in PlayerOffline, lpFight->lpActiveObject");
				fightlist.RemoveAt(lastpos);
				delete lpFight;
				continue;
			}
			// Check end
			if ((lpFight->lpActiveObject->szEName == lpPlayerInfo->szEName)
				&& (lpFight->lpActiveObject->szCName == lpPlayerInfo->szCName)) {
				fightlist.RemoveAt(lastpos);
				// test start
				sprintf(szTest, "Delete (%s,%s) from fightlist",
					lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
				AddRecordMsg(szTest);
				// test end
				delete lpFight;
				break;
			}
		}
		pos = lpPlayerInfo->listfightopp.GetHeadPosition();
		while (pos != NULL) {
			lpOpp = lpPlayerInfo->listfightopp.GetNext(pos);
			opos = lpOpp->listfightopp.GetHeadPosition();
			while (opos != NULL) {
				lastpos = opos;
				lpOpp2 = lpOpp->listfightopp.GetNext(opos);
				if ((lpOpp2->szEName == lpPlayerInfo->szEName) &&
					(lpOpp2->szCName == lpPlayerInfo->szCName)) {
					lpOpp->listfightopp.RemoveAt(lastpos);
					break;
				}
			}
		}
		szFight.Format("%s %s %s %s",SZFIGHTOVER,szRedHigt,lpPlayerInfo->szCName,lpPlayerInfo->szEName);
	}
	if ((lpPlayerInfo->nStatus == AOS_kill) || (lpPlayerInfo->nStatus == AOS_unconcious)) {
		pos = killlist.GetHeadPosition();
		while (pos != NULL) {
			lastpos = pos;
			lpFight = killlist.GetNext(pos);
			// Check NULL pointer
			if (lpFight == NULL) {
				AddRecordMsg("ERROR NULL pointer in PlayerOffline, lpFight");
				killlist.RemoveAt(lastpos);
				continue;
			}
			if (lpFight->lpActiveObject == NULL) {
				AddRecordMsg("ERROR NULL pointer in PlayerOffline, lpFight->ActiveObject");
				killlist.RemoveAt(lastpos);
				delete lpFight;
				continue;
			}
			if (strcmp(lpFight->lpActiveObject->szCheck,SZAOBJCHECK)) {
				AddRecordMsg("ERROR Bad data in PlayerOffline, lpFight->ActiveObject");
				killlist.RemoveAt(lastpos);
				delete lpFight;
				continue;
			}
			// Check end
			if ((lpFight->lpActiveObject->szEName == lpPlayerInfo->szEName) &&
				(lpFight->lpActiveObject->szCName == lpPlayerInfo->szCName)) {
				// test start
				sprintf(szTest, "Delete (%s,%s) from killlist",
					lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
				AddRecordMsg(szTest);
				// test end
				killlist.RemoveAt(lastpos);
				delete lpFight;
				break;
			}
		}
		pos = lpPlayerInfo->listfightopp.GetHeadPosition();
		while (pos != NULL) {
			lpOpp = lpPlayerInfo->listfightopp.GetNext(pos);
			opos = lpOpp->listfightopp.GetHeadPosition();
			while (opos != NULL) {
				lastpos = opos;
				lpOpp2 = lpOpp->listfightopp.GetNext(opos);
				if ((lpOpp2->szEName == lpPlayerInfo->szEName) &&
					(lpOpp2->szCName == lpPlayerInfo->szCName)) {
					lpOpp->listfightopp.RemoveAt(lastpos);
					break;
				}
			}
		}
		szFight.Format("%s %s %s %s",SZDEADMSG,szRedHigt,lpPlayerInfo->szCName,lpPlayerInfo->szEName);
//		lpPlayerInfo->SendMsgToAll(szTemp);
	}
	// Spock end

	//在chatchannel中刪除player
	// Spock start
	pos = chatchannellist.GetHeadPosition();
	while (pos != NULL) {
		lastpos = pos;
		lpChatChannel = chatchannellist.GetNext(pos);
		// Check NULL pointer and bad data
		if (lpChatChannel == NULL) {
			AddRecordMsg("ERROR NULL pointer in PlayerOffline, lpChatChannel");
			chatchannellist.RemoveAt(lastpos);
			continue;
		}
		if (lpChatChannel->lpPlayerInfo == NULL) {
			AddRecordMsg("ERROR NULL pointer in PlayerOffline, lpChatChannel->lpPlayerInfo");
			chatchannellist.RemoveAt(lastpos);
			continue;
		}
		if (strcmp(lpChatChannel->lpPlayerInfo->szCheck, SZAOBJCHECK)) {
			AddRecordMsg("ERROR Bad data in PlayerOffline, lpChatChannel->lpPlayerInfo");
			chatchannellist.RemoveAt(lastpos);
			continue;
		}
		// Check end
		if(lpChatChannel->lpPlayerInfo->szUserName == lpPlayerInfo->szUserName) {
			chatchannellist.RemoveAt(lastpos);
			delete lpChatChannel;
			break;
		}
	}
	//在Maplist中刪除Player
	if (MapPosite) {
		CPlayerInfo* lpOtherPlayer;
		lpDataMap = maplist.GetAt(MapPosite);
		pos = lpDataMap->listplayer.GetHeadPosition();
		while (pos) {
			lastpos = pos;
			lpOtherPlayer = lpDataMap->listplayer.GetNext(pos);
			if (strcmp(lpOtherPlayer->szCheck, SZAOBJCHECK)) {
				AddRecordMsg("ERROR Bad data in PlayerOffline, lpDataMap->listplayer");
				lpDataMap->listplayer.RemoveAt(lastpos);
				continue;
			}
			if(lpOtherPlayer->szUserName == lpPlayerInfo->szUserName)
			{
				lpDataMap->listplayer.RemoveAt(lastpos);
				break;
			}
		}
	}
	// Spock start
	LeaveCriticalSection(&myglobs.csChatChannel);
	LeaveCriticalSection(&myglobs.csMaplist);
	LeaveCriticalSection(&myglobs.csFightlist);
	if (!szFight.IsEmpty()) lpPlayerInfo->SendMsgToAll(szFight);
	szFight = CString(szSomeoneQuitMap) + (" ") + lpPlayerInfo->szEName + (" EXIT");
	lpPlayerInfo->SendMsgToAll(szFight);
	// Spock end

	lpPlayerInfo->nStatus = AOS_none;
	int nTest, nRetry = 0;
	while (nRetry < SAVERETRY) {
		nTest = SavePlayerData(lpPlayerInfo);
		nRetry++;
		if (nTest <= 0) {
			sprintf(szTest,"ERROR (%s,%s) Offline SavePlayerData Error=%d Retry=%d",lpPlayerInfo->szEName,lpPlayerInfo->szUserName,nTest,nRetry);
			AddRecordMsg(szTest);
			Sleep(3000);
		} else {
			sprintf(szTest,"(%s) Offline SavePlayerData OK",lpPlayerInfo->szEName);
			AddRecordMsg(szTest);
			break;
		}
	}
	if (lpPlayerInfo->bRun)
		lpPlayerInfo->bRun = FALSE;
	else
		delete lpPlayerInfo;
}

/*void CCmdPlayerLogon::UserOffLine(char * UserName)
{
	TDataUser* lpDataUser;

	int i,j;
	EnterCriticalSection(&myglobs.csUserlist);
	j = userlist.GetCount();
	for ( i=0;i<j;i++)
	{
		lpDataUser = userlist.GetAt(userlist.FindIndex(i));
		if ( !lstrcmp(UserName,lpDataUser->UserAccountName))
		{
			lpDataUser->iEnableStat = 0;
			break;
		}
	}
	LeaveCriticalSection(&myglobs.csUserlist);
}
*/
