// CommandCheck.cpp: implementation of the CCommandCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmudOS.h"
#include "CommandCheck.h"
#include "CmdPlayerLogon.h"
#include "Common.h"

extern rmfullglobals myglobs;
extern CList <TClientConData *,TClientConData* >playersocketlist;
extern char g_tszPathName[256];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommandCheck::CCommandCheck()
{

}

CCommandCheck::~CCommandCheck()
{

}

void AddTalkMsg(CPlayerInfo *who, CString szMsg)
{
	char szFile[256];
	EnterCriticalSection(&myglobs.csTalkMsg);
	CTime CurrentTime=CTime::GetCurrentTime();
	sprintf(szFile,"[%s,%s,%s] %s\n",//CurrentTime.Format("%Y/%m/%d %H:%M:%S"),
		who->szCName, who->szEName, who->szUserName, szMsg);
	AddRecordMsg( szFile);
	LeaveCriticalSection(&myglobs.csTalkMsg);
}

void CCommandCheck::ProcessPlayerCommand(SOCKET hPlayerSocket,
										 CStringList *Command,
										 char * Result,
										 sockaddr_in IPAddr,
										 char * UserName,
										 char * PlayerName,
										 LPVOID &pvPlayer,
										 PCLientConData lpConData)
{
	CCmdPlayerLogon m_CmdPlayerLogon;
	CPlayerInfo *lpPlayerInfo;
	TClientConData * lpClientConData;
	int i,j;
	CString tmpMsg = _T("");
	strcpy(Result,"OK");
	// test +1
	char szTest[256];
	if (!lstrcmp(Command->GetHead(),szUserLogonCmd)){//合法用戶簽到
		if(Command->GetCount()>2){
			UserLogonCmdProc(UserName,IPAddr,
					(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(1)),
					(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(2)),
					Result);
		}
	}else if(!lstrcmp(Command->GetHead(),szPlayerLogonCmd)){//玩家簽到
		// test start
		sprintf(szTest, "(%s)%s Enter player logon procedure", UserName, inet_ntoa(IPAddr.sin_addr));
		AddRecordMsg(szTest);
		// test end
		if(Command->GetCount()>2){
			m_CmdPlayerLogon.PlayerLogonCmdProc(hPlayerSocket,
					UserName,PlayerName,
					(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(1)),
					(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(2)),
					Result,IPAddr,lpConData);
		}
	}else if (!lstrcmp(Command->GetHead(),szPlayerDeleteCmd))	{// Player Delete
		if (Command->GetCount()>0){
			m_CmdPlayerLogon.PlayerDeleteCmdProc(UserName,
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(1)),
				Result);
		}
	}else if(!lstrcmp(Command->GetHead(),szPlayerCreateCmd))	{//Player Create
		if(Command->GetCount()>8){
			m_CmdPlayerLogon.PlayerCreateCmdProc(UserName,PlayerName,
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(1)),
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(2)),
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(3)),
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(4)),
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(5)),
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(6)),
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(7)),
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(8)),
				Result);
			if(!lstrcmp(Result,"OK")){
				m_CmdPlayerLogon.PlayerLogonCmdProc(hPlayerSocket,
						UserName,PlayerName,
						(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(1)),
						(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(2)),
						Result,
						IPAddr,
						lpConData);
			}
		}
	}else if(!lstrcmp(Command->GetHead(),szChangeMapCmd))	{//changemap
		if(Command->GetCount()>1)	{
			ChangeMapProc(PlayerName,
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(1)),
				Result,pvPlayer,IPAddr);
		}
	}else if(!lstrcmp(Command->GetHead(),szSendMapData))	{//start send map data
		if(Command->GetCount()>1){
			SendMapDataProc(PlayerName,
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(1)),
				Result,pvPlayer,IPAddr);
		}
	}else if(!lstrcmp(Command->GetHead(),SZRESTART))	{// Restart
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		CString szMsg;
		if(lpPlayerInfo->nStatus == AOS_dead ){
			sprintf(szTest,"%s,%s,%s SZRESTART|復活", PlayerName,
				lpPlayerInfo->szCName, lpPlayerInfo->szEName );
			AddRecordMsg( szTest);
			EnterCriticalSection(&myglobs.csSentCliMsg);
			szMsg.Format("%s OK %s",SZRESTART,lpPlayerInfo->szRoom);
			lpPlayerInfo->bNoHealing = TRUE;
			lpPlayerInfo->nStatus = AOS_changemap;
			strcpy(Result,"OK");
			lpPlayerInfo->listmsg.AddHead(szMsg);
			LeaveCriticalSection(&myglobs.csSentCliMsg);
		}else {
			strcpy(Result,"OK");
			szMsg.Format("%s FAIL 你還沒死！",SZRESTART);
			lpPlayerInfo->SendMsg(szMsg);
		}
	}else if(!lstrcmp(Command->GetHead(),szALLWhoInGame))	{//查看所有的在線玩家
		//ANDY_ADD 928
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		if( (GetTickCount() - ((CPlayerInfo*)pvPlayer)->nWaitNext) < 1000 )	{
			//~~防堵玩家不斷重複查詢線上人數
			((CPlayerInfo*)pvPlayer)->nWaitNext = GetTickCount();
			return;
		}
		//ANDY_END
			((CPlayerInfo*)pvPlayer)->nWaitNext = GetTickCount();

		lstrcpy(Result,"OK");
		EnterCriticalSection(&myglobs.csPlayerSocket);
		tmpMsg = szALLWhoInGame + CString(" ");
		j = playersocketlist.GetCount();
		for(i=0;i<j;i++){
			lpClientConData = playersocketlist.GetAt(playersocketlist.FindIndex(i));
			lpPlayerInfo = (CPlayerInfo*)lpClientConData->pvPlayer;
			if(lpPlayerInfo == NULL) continue;
			if(strcmp(lpPlayerInfo->szCheck, SZAOBJCHECK))
				continue;
			tmpMsg += lpPlayerInfo->szCName + ("[") + lpPlayerInfo->szEName + ("]")
					+ lpPlayerInfo->szFamily + lpPlayerInfo->szTilte + ("\t");
		}
		LeaveCriticalSection(&myglobs.csPlayerSocket);
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		lpPlayerInfo->SendMsg(tmpMsg);
	}else if(!lstrcmp(Command->GetHead(),szShoutToAll))	{	//對在線所有的用戶大喊
		//在發送信息鏈表中追加發送信息
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		if( (GetTickCount() - ((CPlayerInfo*)pvPlayer)->nWaitNext) > 1000 )	{
			if( Command->GetCount() > 1 )	{
				if(ShoutProc(lpPlayerInfo, Command->GetTail(), FALSE)) {
					AddTalkMsg(lpPlayerInfo, /*CString("大喊: ") +*/ Command->GetTail());
					strcpy(Result, "OK");
				}else	{
					sprintf(Result, "%s 你的精不夠,無法大喊!",SZFAILMSG);
				}
			}
		}else	{
			sprintf(Result, "%s 請勿重複發言!",SZFAILMSG);
		}
		((CPlayerInfo*)pvPlayer)->nWaitNext = GetTickCount();
	}else if(!lstrcmp(Command->GetHead(),SZSEP)) {	//消精
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		if( lpPlayerInfo->nEff_jing > 0 )	{
			lpPlayerInfo->nEff_jing = 0;
			lpPlayerInfo->SendHeal();
		}
	}else if(!lstrcmp(Command->GetHead(),szGmShout))	{	//對在線所有的用戶大喊
		if(Command->GetCount()>1)	{
			lpPlayerInfo = (CPlayerInfo*)pvPlayer;
			if(GmShoutProc(lpPlayerInfo, Command->GetTail(), FALSE)) {
				AddTalkMsg(lpPlayerInfo, CString("GM廣播: ") + Command->GetTail());
				strcpy(Result, "OK");
			}else	{
				sprintf(Result, "%s 你的精不夠,無法大喊!",SZFAILMSG);
			}
		}
	}else if(!lstrcmp(Command->GetHead(),szGmrun))	{	//GM傳送
		CCommandCheck m_CommandCheck;
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		if(m_CommandCheck.CheckGM((char*)(LPCSTR)lpPlayerInfo->szUserName)) {
			if(Command->GetCount() > 2)	{
					GmRunSomeOne( lpPlayerInfo, PlayerName,
						(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)), //聊天組名稱
						(char *)(LPCSTR)Command->GetAt(Command->FindIndex(2)) );
			}else if(Command->GetCount() > 1)	{
					GmRunSomeOne( lpPlayerInfo, PlayerName,
						(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)), //聊天組名稱
						(" ") );
			}
		}
	}else if(!lstrcmp(Command->GetHead(),szShowGM))	{

	}
	else if(!lstrcmp(Command->GetHead(),szGetChannel))	{//得到所有的聊天頻道
		GetChannelCmdProc((CPlayerInfo*)pvPlayer);
	}else if(!lstrcmp(Command->GetHead(),SZJOINCHANNEL))	{//加入或者建立聊天頻道
		if(Command->GetCount()>1){
			lpPlayerInfo = (CPlayerInfo*)pvPlayer;
			sprintf(szTest,"%s,%s,%s SZJOINCHANNEL|加入或者建立聊天頻道 %s ..",PlayerName,
				lpPlayerInfo->szCName, lpPlayerInfo->szEName,
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)));
			AddRecordMsg( szTest);

			if(Command->GetAt(Command->FindIndex(1)).GetLength() > 16){
				ReturnResult(szCommandErrMsg);
			}
			CreateOrJoinChannel( hPlayerSocket, PlayerName,
				(char *)(LPCTSTR)Command->GetAt(Command->FindIndex(1)), Result, pvPlayer);
			if(!lstrcmp(Result,"OK")){
				tmpMsg = CString(" ") + SZJOINCHANNEL + (" ") + Command->GetAt(Command->FindIndex(1));
				lstrcat(Result,tmpMsg);
			}
		}
	}else if(!lstrcmp(Command->GetHead(),szWhoInGame))	{//查看頻道中的所有人員信息
		if(Command->GetCount()>1){
			tmpMsg = szWhoInGame + CString(" ");
			tmpMsg += JoinChannelCmdProc((char *)(LPCTSTR)Command->GetAt(Command->FindIndex(1)));
			strcpy(Result,tmpMsg);
		}
	}else if(!lstrcmp(Command->GetHead(),SZTALKTOALL))	{//對頻道里所有的人說
		if( (GetTickCount() - ((CPlayerInfo*)pvPlayer)->nWaitNext) > 1000 ){
			if(Command->GetCount()>2){
				lpPlayerInfo = (CPlayerInfo*)pvPlayer;
				CString szTalk;
				AddTalkMsg(lpPlayerInfo, CString("[") + Command->GetAt(Command->FindIndex(1))+CString("]")
					+ (" ") + Command->GetAt(Command->FindIndex(2)));
				szTalk = lpPlayerInfo->szEName+Command->GetAt(Command->FindIndex(2));
				ChannelTalkProc((char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),//聊天組名稱
								(char *)(LPCSTR)szTalk);
			}
			((CPlayerInfo*)pvPlayer)->nWaitNext = GetTickCount();
		}
	}else if(!lstrcmp(Command->GetHead(),SZTELLSOMEONE))	{//告訴特定的人
		if( (GetTickCount() - ((CPlayerInfo*)pvPlayer)->nWaitNext) > 1000 )	{
			if(Command->GetCount()>2)	{
				lpPlayerInfo = (CPlayerInfo*)pvPlayer;
				AddTalkMsg(lpPlayerInfo, CString("Tell: ") + Command->GetAt(Command->FindIndex(1))
					+ (" ") + Command->GetAt(Command->FindIndex(2)));
				TellToSomeOne(lpPlayerInfo,
								PlayerName,
								(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),//聊天組名稱
								(char *)(LPCSTR)Command->GetAt(Command->FindIndex(2)));
			}
			((CPlayerInfo*)pvPlayer)->nWaitNext = GetTickCount();
		}
	}
	else if(!lstrcmp(Command->GetHead(),SZEMOTE))	{//emote信息
	  if( (GetTickCount() - ((CPlayerInfo*)pvPlayer)->nWaitNext) > 1000 )	{
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		if(Command->GetCount()>3)	{
//			AddTalkMsg(lpPlayerInfo, CString("Emote: ") + Command->GetAt(Command->FindIndex(1))
			//	+ (" ") + Command->GetAt(Command->FindIndex(2))
			//	+ (" ") + Command->GetAt(Command->FindIndex(3)));
			EmoteProc(pvPlayer,
					PlayerName,
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(2)),
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(3)));
		}else if(Command->GetCount()>2)	{
//			AddTalkMsg(lpPlayerInfo, CString("Emote: ") + Command->GetAt(Command->FindIndex(1))
			//	+ (" ") + Command->GetAt(Command->FindIndex(2)));
			EmoteProc(pvPlayer,
					PlayerName,
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(2)),
					"");
		}else if(Command->GetCount()==2){
//			AddTalkMsg(lpPlayerInfo, CString("Emote: ") + Command->GetAt(Command->FindIndex(1)));
			EmoteProc(pvPlayer,
					PlayerName,
					"",
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
					"");
		}

		((CPlayerInfo*)pvPlayer)->nWaitNext = GetTickCount();
	  }
	}else if(!lstrcmp(Command->GetHead(),szExitChannel))	{//離開頻道
		ExitChannelProc((CPlayerInfo*)pvPlayer, Result);
	}else if(!lstrcmp(Command->GetHead(),szDefendTell))	{//建防耳語清單
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		DefendTellProc(lpPlayerInfo,PlayerName,
		(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)));
	}else if(!lstrcmp(Command->GetHead(),szDefendDel))	{//刪防耳語清單
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		DefendDelProc(lpPlayerInfo,PlayerName,
		(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)));
	}else if(!lstrcmp(Command->GetHead(),szGetOut)){
		if(Command->GetCount()>2){
			lpPlayerInfo = (CPlayerInfo*)pvPlayer;
			GetOutProc(lpPlayerInfo,
						(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),//聊天組名稱
						(char *)(LPCSTR)Command->GetAt(Command->FindIndex(2)));
		}
	}else if(!lstrcmp(Command->GetHead(),SZKILLSB))	{//Kill信息
		if(Command->GetCount()>1)	{
			lpPlayerInfo = (CPlayerInfo*)pvPlayer;
			sprintf(szTest, "%s,%s,%s DoKill|SZKILLSB %s",PlayerName,
				lpPlayerInfo->szCName, lpPlayerInfo->szEName,
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)));
			AddRecordMsg( szTest);

			KillProc(pvPlayer,PlayerName,
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
				Result);

		}
	}else if(!lstrcmp(Command->GetHead(),SZFIGHTSB))	{//Fight信息
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		sprintf(szTest, "%s,%s,%s Cout= %d DoFight|SZFIGHTSB",PlayerName,
			lpPlayerInfo->szCName, lpPlayerInfo->szEName,
			Command->GetCount(), (char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)));
		AddRecordMsg( szTest);

		if(Command->GetCount()==2)	{
			FightProc(pvPlayer,PlayerName,
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
				"25",
				Result);
		}else if(Command->GetCount()>2)	{
			FightProc(pvPlayer,PlayerName,
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(2)),
				Result);
		}
	}
/*
	else if(!lstrcmp(Command->GetHead(),szKickOut))// gm踢人
	{
		//if(CheckGM((char*)(LPCSTR)pvPlayer->szUserName)
		if(Command->GetCount()>1)
		{
			KickOutProc((char*)(LPCSTR)who->szUserName,PlayerName,
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
				Result);
		}

	}
*/
	else if(!lstrcmp(Command->GetHead(),SZESCAPE))	{// Escape 訊息
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		sprintf(szTest, "%s,%s,%s Cout= %d Get Escape(逃跑) Command",PlayerName,
			lpPlayerInfo->szCName, lpPlayerInfo->szEName, Command->GetCount());
		AddRecordMsg( szTest);
		EscapeProc(PlayerName, Result,pvPlayer, IPAddr);
	}else if(!strcmp(Command->GetHead(),SZACCEPTFIGHT))	{//接受切磋
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		if (lpPlayerInfo->nPlayerStatus & PS_nofight) {
			lpPlayerInfo->nPlayerStatus &= ~PS_nofight;
			strcpy(Result, SZACCEPTFIGHT);
		}
	}else if(!strcmp(Command->GetHead(),SZREJECTFIGHT))	{//拒絕切磋
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		if (!(lpPlayerInfo->nPlayerStatus & PS_nofight)) {
			lpPlayerInfo->nPlayerStatus |= PS_nofight;
			strcpy(Result, SZREJECTFIGHT);
		}
	}else if(!strcmp(Command->GetHead(),SZMAPPING))	{//準備技能
		if(Command->GetCount()>2)	{
			MappingProc(pvPlayer,
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(2)),
					Result);
		}
	}else if(!strcmp(Command->GetHead(),SZDAZUO))	{//打坐
		if(Command->GetCount()>1){
			lpPlayerInfo = (CPlayerInfo*)pvPlayer;
			sprintf(szTest,"%s,%s,%s SZDAZUO|打坐 %s ..",PlayerName,
				lpPlayerInfo->szCName, lpPlayerInfo->szEName,
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)));
			AddRecordMsg( szTest);
			DazuoProc(pvPlayer,
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
					Result);
		}
	}else if(!strcmp(Command->GetHead(),SZTUNA))	{//吐納
		if(Command->GetCount()>1)	{
			lpPlayerInfo = (CPlayerInfo*)pvPlayer;
			sprintf(szTest,"%s,%s,%s SZTUNA|吐納 %s ..",PlayerName,
				lpPlayerInfo->szCName, lpPlayerInfo->szEName,
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)));
			AddRecordMsg( szTest);

			TuNaProc(pvPlayer,
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
					Result);
		}
	}else if(!strcmp(Command->GetHead(),SZAPPRENTICE))	{//拜師指令
		if(Command->GetCount()>1)	{
			lpPlayerInfo = (CPlayerInfo*)pvPlayer;
			sprintf(szTest,"%s,%s,%s SZAPPRENTICE|拜師 %s ..",PlayerName,
				lpPlayerInfo->szCName, lpPlayerInfo->szEName,
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)));
			AddRecordMsg( szTest);

			ApprenticeProc(pvPlayer,
						(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
						Result);
		}
	}else if(!strcmp(Command->GetHead(),SZLEARNSKILL))	{//學習指令
		if(Command->GetCount() > 3){
			LearenProc(pvPlayer,
						(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
						(char *)(LPCSTR)Command->GetAt(Command->FindIndex(2)),
						(char *)(LPCSTR)Command->GetAt(Command->FindIndex(3)),
						Result);
		}
	}else if(!strcmp(Command->GetHead(),SZPRACTICE))	{//練習指令
		if(Command->GetCount() > 2)	{
			PracticeProc(pvPlayer,
						(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
						(char *)(LPCSTR)Command->GetAt(Command->FindIndex(2)),
						Result);
		}
	}else if(!strcmp(Command->GetHead(),SZASK))	{//ask指令
        if(Command->GetCount() > 2)	{
			AskProc(pvPlayer,
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(2)),
					(char *)(LPCSTR)Command->GetTail(),
					Result);
		}
	}else if(!lstrcmp(Command->GetHead(),SZLOOK))	{	//看
		if(Command->GetCount() > 2){
			LookProc(pvPlayer,
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
					(char *)(LPCSTR)Command->GetTail(),
					Result);
		}
	}else if(!lstrcmp(Command->GetHead(),SZRENTLIST))	{//查詢寄物
		RentListProc((CPlayerInfo*)pvPlayer, Result);
	}else if(!strcmp(Command->GetHead(),SZUSE))	{//使用的指令
		if(Command->GetCount() > 2)	{
			UseProc(pvPlayer,
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
				atoi(Command->GetAt(Command->FindIndex(2))),
					Result);
		}else if(Command->GetCount() > 1)	{
			UseProc(pvPlayer,(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),1, Result);
		}
	}
/*	else if(!strcmp(Command->GetHead(),SZDRINK))//喝的指令
	{
		if(Command->GetCount() > 1)
		{
			DrinkProc(pvPlayer,
					(char *)(LPCSTR)Command->GetTail(),
					Result);
		}
	}

	else if(!strcmp(Command->GetHead(),SZEAT))//吃的指令
	{
		if(Command->GetCount() > 1)
		{
			EatProc(pvPlayer,
					(char *)(LPCSTR)Command->GetTail(),
					Result);
		}
	}*/
	else if(!strcmp(Command->GetHead(),SZARM)){
		if(Command->GetCount() > 1)
		{
			ArmProc(pvPlayer,
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
					Result);
		}
	}else if(!strcmp(Command->GetHead(),SZUNARM)){
		if(Command->GetCount() > 1){
			UnArmProc(pvPlayer,
					(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
					Result);
		}
	}else if(!strcmp(Command->GetHead(),SZDROP)){
		if(Command->GetCount() > 1){
		    DropProc(pvPlayer,
				(char *)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
				Result);
		}
	}
	else if(!strcmp(Command->GetHead(),SZGIVE)){
		if(Command->GetCount() > 2){
		    GiveProc(pvPlayer,
				(char*)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
				(char*)(LPCSTR)Command->GetAt(Command->FindIndex(2)),
				(char *)(LPCSTR)Command->GetTail(),
				Result);
		}
	}else if(!strcmp(Command->GetHead(),SZMASTERSKILL)){
		if(Command->GetCount() > 1){
			GetMasterSkill(pvPlayer,
					(char *)(LPCSTR)Command->GetTail(),
					Result);
		}
	}else if(!strcmp(Command->GetHead(),SZYUNGONG))	{
		if(Command->GetCount() > 1){
			YunGongProc(pvPlayer,
					(char*)(LPCSTR)Command->GetAt(Command->FindIndex(1)),
					Result);
		}
	}else if(!strcmp(Command->GetHead(),SZEXITGAME))	{
		lpPlayerInfo = (CPlayerInfo*)pvPlayer;
		if(lpPlayerInfo->nStatus == AOS_none) {
			sprintf(szTest,"(%s,%s) Player normal exit",
				lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
			AddRecordMsg(szTest);
		} else {
			sprintf(szTest,"(%s,%s) Player exit in busy",
				lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
			AddRecordMsg(szTest);
		}
	}else{
		lstrcpy(Result,"OK");
	}
}
