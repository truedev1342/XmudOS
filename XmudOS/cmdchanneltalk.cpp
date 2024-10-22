#include "stdafx.h"
#include "XmudOS.h"
#include "CommandCheck.h"
#include "CmdPlayerLogon.h"
#include "CmdEmote.h"
#include "Common.h"
#include "npc\npc.h"
#include "map\mapinfo.h"

extern rmfullglobals myglobs;
extern CList <TChatChannel*,TChatChannel*>chatchannellist;
extern CList <TClientConData *,TClientConData* >playersocketlist;
extern CList <TAdminConData *,TAdminConData* >adminsocketlist;

void CCommandCheck::ExitChannelProc(CPlayerInfo *lpPlayerInfo, char *Result)
{
	TChatChannel* lpChatChannel;
	EnterCriticalSection(&myglobs.csChatChannel);
	POSITION pos, lastpos;
	pos = chatchannellist.GetHeadPosition();
	while(pos) {
		lastpos = pos;
		lpChatChannel = chatchannellist.GetNext(pos);
		if (lpChatChannel->lpPlayerInfo->szUserName == lpPlayerInfo->szUserName) {
			chatchannellist.RemoveAt(lastpos);
			delete lpChatChannel;
			LeaveCriticalSection(&myglobs.csChatChannel);
			sprintf(Result, "%s 你已成功離開頻道",SZOKMSG);
			return;
		}
	}
	LeaveCriticalSection(&myglobs.csChatChannel);
	sprintf(Result, "%s 你沒有加入任何頻道！",SZFAILMSG);
}

BOOL CCommandCheck::ShoutProc(CPlayerInfo *lpPlayerInfo, CString szShout, BOOL bGM)
{
	POSITION pos;
	TClientConData *lpClientConData;
	CString szShoutTxt;

	if((lpPlayerInfo->nEff_jing >= 60) || bGM) {
		if (bGM) {
			szShoutTxt = CString(szShoutToAll) + (" (255,255,255)") + szShout;
		} else {
			lpPlayerInfo->nEff_jing -= 60;
			lpPlayerInfo->SendHeal();
			if (szShout.GetLength() > 80)
				szShoutTxt = CString(szShoutToAll) + (" (255,50,50)") + lpPlayerInfo->szEName + szShout.Left(80);
			else
				szShoutTxt = CString(szShoutToAll) + (" (255,50,50)") + lpPlayerInfo->szEName + szShout;
		}
		EnterCriticalSection(&myglobs.csPlayerSocket);
		pos = playersocketlist.GetHeadPosition();
		while (pos) {
			lpClientConData = playersocketlist.GetNext(pos);
			if(lpClientConData->pvPlayer) {
				((CPlayerInfo*)lpClientConData->pvPlayer)->SendMsg(szShoutTxt);
			}
		}
		LeaveCriticalSection(&myglobs.csPlayerSocket);
		return TRUE;
	} else {
		return FALSE;
	}
}

BOOL CCommandCheck::GmShoutProc(CPlayerInfo *lpPlayerInfo, CString szShout, BOOL bGM)
{
	POSITION pos;
	TClientConData *lpClientConData;
	CCommandCheck m_CommandCheck;
	CString szShoutTxt;
 
	char chrUserName[256];
	strcpy(chrUserName, LPCSTR(lpPlayerInfo->szUserName));
	if(m_CommandCheck.CheckGM(chrUserName)) {

		szShoutTxt = CString(szShoutToAll) + (" (255,255,255)") + szShout;
		 
		EnterCriticalSection(&myglobs.csPlayerSocket);
		pos = playersocketlist.GetHeadPosition();
		while (pos) {
			lpClientConData = playersocketlist.GetNext(pos);
			if(lpClientConData->pvPlayer) {
				((CPlayerInfo*)lpClientConData->pvPlayer)->SendMsg(szShoutTxt);
			}
		}
		LeaveCriticalSection(&myglobs.csPlayerSocket);
		return TRUE;
	} else {
		return FALSE;
	}
}

void CCommandCheck::GetChannelCmdProc(CPlayerInfo *lpPlayerInfo)
{
	TChatChannel* lpChatChannel;
	CString strtmp = _T("");
	CString szChannelMsg = CString(szGetChannel)+CString(" ");
	int i,j;

	EnterCriticalSection(&myglobs.csChatChannel);
	j = chatchannellist.GetCount();
	for(i=0;i<j;i++)
	{
		lpChatChannel = chatchannellist.GetAt(chatchannellist.FindIndex(i));
		if(strcmp(strtmp,lpChatChannel->m_sTITLE))
		{
			szChannelMsg += lpChatChannel->m_sTITLE + ("\t");
		}
		strtmp = lpChatChannel->m_sTITLE;
	}
	LeaveCriticalSection(&myglobs.csChatChannel);
	lpPlayerInfo->SendMsg(szChannelMsg);
}

void CCommandCheck::CreateOrJoinChannel(SOCKET hPlayerSocket,
											char * PlayerName, 
											char * Title, 
											char * Result,
											LPVOID pvPlayer)
{
	TChatChannel* lpChatChannel;
	CPlayerInfo *lpPlayerInfo;
	int i,j;
	CString strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6;
	BOOL bAllready = FALSE;

	EnterCriticalSection(&myglobs.csChatChannel);
	j = chatchannellist.GetCount();
	for(i=0;i<j;i++){
		lpChatChannel = chatchannellist.GetAt(chatchannellist.FindIndex(i));
		if(!lstrcmp(PlayerName,lpChatChannel->lpPlayerInfo->szEName)){
			chatchannellist.RemoveAt(chatchannellist.FindIndex(i));
			delete lpChatChannel;
			break;
		}
	}
	LeaveCriticalSection(&myglobs.csChatChannel);
	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	EnterCriticalSection(&myglobs.csChatChannel);
	j = chatchannellist.GetCount();
	for(i=0;i<j;i++){
		lpChatChannel = chatchannellist.GetAt(chatchannellist.FindIndex(i));
		if(!strcmp(Title,lpChatChannel->m_sTITLE)){
			strcpy(Title,lpChatChannel->m_sTITLE);
			lpChatChannel = new TChatChannel;
			if(!lpChatChannel){
				LeaveCriticalSection(&myglobs.csChatChannel);
				ReturnResult(szOutOfMemoryErrMsg)
			}
			lpChatChannel->m_sTITLE = Title;
			lpChatChannel->lpPlayerInfo = lpPlayerInfo;

			chatchannellist.InsertBefore(chatchannellist.FindIndex(i),lpChatChannel);
			bAllready = TRUE;
			LeaveCriticalSection(&myglobs.csChatChannel);
			ReturnResult("OK")
		}
	}
	if(!bAllready){
		lpChatChannel = new TChatChannel;
		if(!lpChatChannel)
		{
			LeaveCriticalSection(&myglobs.csChatChannel);
			ReturnResult(szOutOfMemoryErrMsg)
		}
		lpChatChannel->m_sTITLE = Title;
		lpChatChannel->lpPlayerInfo = lpPlayerInfo;
		chatchannellist.AddTail(lpChatChannel);
		LeaveCriticalSection(&myglobs.csChatChannel);
		ReturnResult("OK")
	}
	LeaveCriticalSection(&myglobs.csChatChannel);
	ReturnResult(szOutOfMemoryErrMsg)
}

CString CCommandCheck::JoinChannelCmdProc(char * szWhichTitle)
{
	TChatChannel* lpChatChannel;
	CString sResultMsg;
	CString parm,sign;
	int i,j;

	BOOL bFindHead = FALSE;
	parm = CString("\t");
	sResultMsg = parm+CString("CHANNELDATA") + parm;
	EnterCriticalSection(&myglobs.csChatChannel);
	j = chatchannellist.GetCount();
	for(i=0;i<j;i++){
		if(!bFindHead){
			lpChatChannel = chatchannellist.GetAt(chatchannellist.FindIndex(i));
			if(!lstrcmp(szWhichTitle,lpChatChannel->m_sTITLE)){
				sResultMsg += CString("RECORDE")+parm;
				sResultMsg += lpChatChannel->m_sTITLE+parm;
				sResultMsg += lpChatChannel->lpPlayerInfo->szCName+parm;
				sResultMsg += lpChatChannel->lpPlayerInfo->szEName+parm;
				sResultMsg += lpChatChannel->lpPlayerInfo->szSex+parm;
				if(lpChatChannel->lpPlayerInfo->szTilte.IsEmpty())
					sResultMsg += CString("NULL") + parm;
				else
					sResultMsg += lpChatChannel->lpPlayerInfo->szTilte+parm;
				if(lpChatChannel->lpPlayerInfo->szFamily.IsEmpty())
					sResultMsg += CString("NULL") + parm;
				else
					sResultMsg += lpChatChannel->lpPlayerInfo->szFamily+parm;
				sResultMsg += sign+CString("RECORDEEND")+parm;
				bFindHead = TRUE;
			}
		}else	{
			lpChatChannel = chatchannellist.GetAt(chatchannellist.FindIndex(i));
			if(lstrcmp(szWhichTitle,lpChatChannel->m_sTITLE))break;
			sResultMsg += CString("RECORDE")+parm;

				if(lpChatChannel->m_sTITLE.IsEmpty())
					sResultMsg += CString("NULL") + parm;
				else
					sResultMsg += lpChatChannel->m_sTITLE+parm;
				sResultMsg += lpChatChannel->lpPlayerInfo->szCName+parm;
				sResultMsg += lpChatChannel->lpPlayerInfo->szEName+parm;
				sResultMsg += lpChatChannel->lpPlayerInfo->szSex+parm;
				if(lpChatChannel->lpPlayerInfo->szTilte.IsEmpty())
					sResultMsg += CString("NULL") + parm;
				else
					sResultMsg += lpChatChannel->lpPlayerInfo->szTilte+parm;
				if(lpChatChannel->lpPlayerInfo->szFamily.IsEmpty())
					sResultMsg += CString("NULL") + parm;
				else
					sResultMsg += lpChatChannel->lpPlayerInfo->szFamily+parm;
				sResultMsg += sign+CString("RECORDEEND")+parm;
		}
	}
	LeaveCriticalSection(&myglobs.csChatChannel);
	if(!bFindHead)
		sResultMsg.Empty();
	else	
		sResultMsg += CString("CHANNELDATAEND")+parm;
	return sResultMsg;
}

void CCommandCheck::ChannelTalkProc(char *szWhichTitle,char *szTalkSome)
{
	TChatChannel* lpChatChannel;
	CString szMsgToChannl;
	char szTemp[256];
	BOOL bFindHead = FALSE;
	int i,j;

	szMsgToChannl = CString(szTalkSome);
	if (szMsgToChannl.GetLength() > 60) szMsgToChannl = szMsgToChannl.Left(60);
	szMsgToChannl = SZTALKTOALL + CString(" ") + szMsgToChannl;
	EnterCriticalSection(&myglobs.csChatChannel);
	j = chatchannellist.GetCount();
	for(i=0;i<j;i++){
		if(!bFindHead){
			lpChatChannel = chatchannellist.GetAt(chatchannellist.FindIndex(i));
			if(!lstrcmp(szWhichTitle,lpChatChannel->m_sTITLE)){
				bFindHead = TRUE;
				if (lpChatChannel->lpPlayerInfo == NULL) {
					sprintf(szTemp, "ERROR NULL pointer in ChannelTalkProc, lpPlayerInfo");
					AddRecordMsg(szTemp);
					continue;
				}
				if (strcmp(lpChatChannel->lpPlayerInfo->szCheck, SZAOBJCHECK)) {
					sprintf(szTemp, "ERROR Bad data in ChannelTalkProc, lpPlayerInfo");
					AddRecordMsg(szTemp);
					continue;
				}
				lpChatChannel->lpPlayerInfo->SendMsg(szMsgToChannl);
			}
		}else{
			lpChatChannel = chatchannellist.GetAt(chatchannellist.FindIndex(i));
			if(lstrcmp(szWhichTitle,lpChatChannel->m_sTITLE))break;
			if (lpChatChannel->lpPlayerInfo == NULL) {
				sprintf(szTemp, "ERROR NULL pointer in ChannelTalkProc, lpPlayerInfo");
				AddRecordMsg(szTemp);
				continue;
			}
			if (strcmp(lpChatChannel->lpPlayerInfo->szCheck, SZAOBJCHECK)) {
				sprintf(szTemp, "ERROR Bad data in ChannelTalkProc, lpPlayerInfo");
				AddRecordMsg(szTemp);
				continue;
			}
			lpChatChannel->lpPlayerInfo->SendMsg(szMsgToChannl);
		}
	}
	LeaveCriticalSection(&myglobs.csChatChannel);
	szMsgToChannl = szMsgToChannl + ("\r\n");
}

void CCommandCheck::TellToSomeOne(CPlayerInfo *me,char *playerName,char *szWhichOne,char *szTalkSome)
{
	CPlayerInfo* lpPlayerInfo;
	CString szMsgToChannl;
	CString szTalk;
	CString szDefName;
	BOOL bFindHead = FALSE;
	BOOL bDefendTell = FALSE;
 
	szTalk = CString(szTalkSome);
	if (szTalk.GetLength() > 50) szTalk = szTalk.Left(50);
	EnterCriticalSection(&myglobs.csPlayerSocket);
	POSITION pos = playersocketlist.GetHeadPosition();
	while(pos != NULL){
		lpPlayerInfo = (CPlayerInfo*)playersocketlist.GetNext(pos)->pvPlayer;
		if(lpPlayerInfo == NULL) {
			continue;
		}
		if(strcmp(lpPlayerInfo->szCheck, SZAOBJCHECK)) {
			AddRecordMsg("ERROR Bad data in TellToSomeOne, lpPlayerInfo");
			continue;
		}
		if( !strcmp(szWhichOne,lpPlayerInfo->szEName) || 
			!strcmp(szWhichOne,lpPlayerInfo->szCName)){
			bFindHead = TRUE;
			EnterCriticalSection(&myglobs.csPlayerData);
			POSITION pos2 = lpPlayerInfo->DefTellList.GetHeadPosition();
			while(pos2 != NULL){
				szDefName = lpPlayerInfo->DefTellList.GetNext(pos2);
				if( !strcmp(szDefName,me->szEName) || 
					!strcmp(szDefName,me->szCName)){
					bDefendTell = TRUE;
				}
			}
			LeaveCriticalSection(&myglobs.csPlayerData);
			if(!bDefendTell){
				szMsgToChannl.Format("%s [%s]對你說道:%s",SZTELLSOMEONE,playerName,szTalk);
				lpPlayerInfo->SendMsg(szMsgToChannl);
			}
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerSocket);
	if(bFindHead){
		if(!bDefendTell)
			szMsgToChannl.Format("%s 你對[%s]說道:%s",SZTELLSOMEONE,szWhichOne,szTalk);
		else
			szMsgToChannl.Format("%s [%s]不想聽你說話",SZTELLSOMEONE,szWhichOne);
	}else
		szMsgToChannl.Format("%s %s已經斷線了",SZTELLSOMEONE,szWhichOne);
	me->SendMsg(szMsgToChannl);
	Sleep(250);
}

void CCommandCheck::GmRunSomeOne(CPlayerInfo *me,char *playerName,char *szWhichOne,const char *szTalkSome)
{
	CPlayerInfo* lpPlayerInfo;
	CString szMsgToChannl;
	CString szTalk;
	CString szDefName;
	BOOL bFindHead = FALSE;
	BOOL bDefendTell = FALSE;
 
	szTalk = CString(szTalkSome);
	if (szTalk.GetLength() > 50) szTalk = szTalk.Left(50);
	EnterCriticalSection(&myglobs.csPlayerSocket);
	POSITION pos = playersocketlist.GetHeadPosition();

	while(pos != NULL)	{	
		lpPlayerInfo = (CPlayerInfo*)playersocketlist.GetNext(pos)->pvPlayer;
		if(lpPlayerInfo == NULL) continue;
		if( !strcmp(szWhichOne,lpPlayerInfo->szEName) || 
			!strcmp(szWhichOne,lpPlayerInfo->szCName)){
			bFindHead = TRUE;
			EnterCriticalSection(&myglobs.csPlayerData);
			POSITION pos2 = lpPlayerInfo->DefTellList.GetHeadPosition();
			while(pos2 != NULL)	{
				szDefName = lpPlayerInfo->DefTellList.GetNext(pos2);
				if( !strcmp(szDefName,me->szEName) || 
					!strcmp(szDefName,me->szCName))		{
					bDefendTell = TRUE;
				}
			}
			LeaveCriticalSection(&myglobs.csPlayerData);
			szMsgToChannl.Format("%s [%s]已將你傳送!!%s",SZTELLSOMEONE,"小人物","ok");
			lpPlayerInfo->SendMsg(szMsgToChannl);
			CString szTemp2;
			szTemp2.Format("%s %s %s",SZJOBO,"監獄",szTalkSome);
			lpPlayerInfo->SendMsg(szTemp2);
		}
	}
	LeaveCriticalSection(&myglobs.csPlayerSocket);

	if(!bFindHead)	{
		szMsgToChannl.Format("%s %s已經斷線了",SZTELLSOMEONE,szWhichOne);
		me->SendMsg(szMsgToChannl);
		Sleep(250);
	}
}

void CCommandCheck::EmoteProc(LPVOID pvPlayer,
							const char *playerName,
							const char *szWhichTitle,
							const char * szEmote,
							const char * szWho)
{
	TChatChannel* lpChatChannel;
	CPlayerInfo * me = (CPlayerInfo *)pvPlayer;
	CActiveObject * you = NULL;
	CPlayerInfo *lpPlayerInfo;
	CNpc	* lpNpc;
	CBaseMap *lpDataMap;
	POSITION pos, lastpos;

	CString strRet1,strRet2,strRet3;
	int i,j;
	BOOL bFindHead = FALSE;
	char szTemp[256];

	if(!_stricmp(szWho,"me"))
		you = me;
	else if(strcmp(szWho,"")){
		EnterCriticalSection(&myglobs.csChatChannel);
		pos = chatchannellist.GetHeadPosition();
		while(pos != NULL){
			lpChatChannel = chatchannellist.GetNext(pos);
			if(!strcmp(szWhichTitle,lpChatChannel->m_sTITLE))
				bFindHead = TRUE;
			else if(bFindHead) break;
			if(bFindHead){
				if(lpChatChannel->lpPlayerInfo == NULL) {
					sprintf(szTemp, "ERROR NULL pointer in EmoteProc, lpPlayerInfo");
					AddRecordMsg(szTemp);
					continue;
				}
				if(strcmp(lpChatChannel->lpPlayerInfo->szCheck, SZAOBJCHECK)) {
					sprintf(szTemp, "ERROR Bad data in ChannelTalkProc, lpPlayerInfo");
					AddRecordMsg(szTemp);
					continue;
				}
				if(!strcmp(lpChatChannel->lpPlayerInfo->szEName,szWho))
				{	you = lpChatChannel->lpPlayerInfo;	break;	}
			}
		}
		LeaveCriticalSection(&myglobs.csChatChannel);
		if(you == NULL){
			lpDataMap = maplist.GetAt(me->pMapPosite);
			if(lpDataMap != NULL){
				EnterCriticalSection(&myglobs.csMaplist);
				pos = lpDataMap->listplayer.GetHeadPosition();
				while(pos != NULL){
					lastpos = pos;
					lpPlayerInfo = lpDataMap->listplayer.GetNext(pos);
					if(lpPlayerInfo == NULL) {
						lpDataMap->listplayer.RemoveAt(lastpos);
						sprintf(szTemp, "ERROR NULL pointer in EmoteProc, lpPlayerInfo");
 						AddRecordMsg(szTemp);
						continue;
					}
					if(strcmp(lpPlayerInfo->szCheck, SZAOBJCHECK)) {
						sprintf(szTemp, "ERROR Bad data in EmoteProc, lpPlayerInfo");
						AddRecordMsg(szTemp);
						lpDataMap->listplayer.RemoveAt(lastpos);
						continue;
					}
					if(!strcmp(lpPlayerInfo->szEName, szWho)){
						you = lpPlayerInfo;
						break;
					}
				}
				if(you == NULL){
					pos = lpDataMap->listNpc.GetHeadPosition();
					while(pos != NULL){
						lastpos = pos;
						lpNpc = lpDataMap->listNpc.GetNext(pos);
						if(lpNpc == NULL) {
							lpDataMap->listNpc.RemoveAt(lastpos);
							continue;
						}
						if(strcmp(lpNpc->szCheck, SZAOBJCHECK)) {
							lpDataMap->listNpc.RemoveAt(lastpos);
							continue;
						}
						if(!_stricmp(lpNpc->szEName, szWho)){
							you = lpNpc;
							break;
						}
					}
				}
				LeaveCriticalSection(&myglobs.csMaplist);
			}
		}
		if(you == NULL){
			strRet1.Format("%s 在頻道和地圖中[%s]人物或NPC不存在.",SZEMOTE,szWho);
			me->SendMsg(strRet1);
			return;
		}
	}
	if(!GetEmote(szEmote, me, you, strRet1, strRet2, strRet3))
	{
		strRet1 = SZEMOTE;
		strRet1 += CString(" [") + szEmote + "]emote不存在或者用法錯誤!";
		me->SendMsg(strRet1);
		return;
	}
	if(you == me) you = NULL;
	if((you != NULL)&&(you->bPlayer == FALSE))
	{
		((CNpc *)you)->DoEmote(me, szEmote);
		you = NULL;
	}

	strRet1 = CString(SZEMOTE) + (" ") + strRet1;
	strRet2 = CString(SZEMOTE) + (" ") + strRet2;
	strRet3 = CString(SZEMOTE) + (" ") + strRet3;
	BOOL bMeSend = FALSE,bYouSend = FALSE;
	bFindHead = FALSE;
	EnterCriticalSection(&myglobs.csChatChannel);
	j = chatchannellist.GetCount();
	for(i=0;i<j;i++)
	{
		lpChatChannel = chatchannellist.GetAt(chatchannellist.FindIndex(i));
		if(!strcmp(szWhichTitle,lpChatChannel->m_sTITLE))
			bFindHead = TRUE;
		else if(bFindHead)
			break;
		if(bFindHead){
			if(lpChatChannel->lpPlayerInfo == NULL) continue;
			if(lpChatChannel->lpPlayerInfo == me){
				me->SendMsg(strRet1);
				bMeSend = TRUE;
			}
			else if(lpChatChannel->lpPlayerInfo == you)
			{
				you->SendMsg(strRet2);
				bYouSend = TRUE;
			}
			else {
				lpChatChannel->lpPlayerInfo->SendMsg(strRet3);
			}
		}
	}
	LeaveCriticalSection(&myglobs.csChatChannel);

	lpDataMap = maplist.GetAt(me->pMapPosite);
	if((lpDataMap != NULL)&&
	   ((!bMeSend)||
	   (!bYouSend && you != NULL))){
		EnterCriticalSection(&myglobs.csMaplist);
		POSITION tmpPos = lpDataMap->listplayer.GetHeadPosition();
		while(tmpPos != NULL){
			lastpos = tmpPos;
			lpPlayerInfo = lpDataMap->listplayer.GetNext(tmpPos);
			if(lpPlayerInfo == NULL) {
				lpDataMap->listplayer.RemoveAt(lastpos);
				continue;
			}
			if(strcmp(lpPlayerInfo->szCheck, SZAOBJCHECK)) {
				lpDataMap->listplayer.RemoveAt(lastpos);
				continue;
			}
			if((lpPlayerInfo == me)&& !bMeSend)
				me->SendMsg(strRet1);
			if((lpPlayerInfo == you)&& !bYouSend)
				you->SendMsg(strRet2);
		}
		LeaveCriticalSection(&myglobs.csMaplist);
	}
}

void CCommandCheck::DefendTellProc(CPlayerInfo *me,char *playerName,char *szWhichOne)
{
	CString szMsg;
	CString szWho;
	CString	strtmp;
	BOOL	bFindHead = FALSE;

	EnterCriticalSection(&myglobs.csPlayerData);
	szWho = CString(szWhichOne);
	POSITION pos = me->DefTellList.GetHeadPosition();
	if(pos) 
		strtmp = me->DefTellList.GetNext(pos);
	while (pos) {
		if(!strcmp(strtmp,szWho)){
			bFindHead = TRUE;
			break;
		}
		strtmp = me->DefTellList.GetNext(pos);
	}
	
	if(!bFindHead){   
		me->DefTellList.AddTail(szWho);
		szMsg.Format("%s 將%s加入防耳語清單",SZOKMSG,szWho);
	}else{
		szMsg.Format("%s %S已經在防耳語清單上了",SZOKMSG,szWho);
	}
	LeaveCriticalSection(&myglobs.csPlayerData);  

	me->SendMsg(szMsg);
}

void CCommandCheck::DefendDelProc(CPlayerInfo *me,char *playerName,char *szWhichOne)
{
	CString szMsg; 
	CString szWho;
	CString	strtmp;
	BOOL	bFindHead = FALSE;
	POSITION pos2;
 
	EnterCriticalSection(&myglobs.csPlayerData);

	szWho = CString(szWhichOne);
	POSITION pos = me->DefTellList.GetHeadPosition();
	while (pos) {
		pos2 = pos;
		strtmp = me->DefTellList.GetNext(pos);
		if(!strcmp(strtmp,szWho)){
			bFindHead = TRUE;
			break;
		}
	}

	if(bFindHead){
		me->DefTellList.RemoveAt(pos2);
		delete pos2;
		szMsg.Format("%s 將[%s]從防耳語清單刪除",SZOKMSG,szWho);
	}else
		szMsg.Format("%s [%S]不在防耳語清單上",SZOKMSG,szWho);
	LeaveCriticalSection(&myglobs.csPlayerData);
	me->SendMsg(szMsg);
}

void CCommandCheck::GetOutProc(CPlayerInfo *me,char *szWhichTitle,char *szWhichOne)
{

	TChatChannel* lpChatChannel;
	POSITION pos,pos2;
	BOOL	bFindHead = FALSE;
	BOOL	bFindMaster = FALSE;
	CString szMsgToChannel;
	CString szWho;
	CString szChannelMaster;
	char szTemp[256];
	int i,j;

	EnterCriticalSection(&myglobs.csChatChannel);	
	szWho = CString(szWhichOne);
	j = chatchannellist.GetCount();
	for(i=j-1;i>=0;i--){
		if(!bFindMaster){
			lpChatChannel = chatchannellist.GetAt(chatchannellist.FindIndex(i));
			if(!lstrcmp(szWhichTitle,lpChatChannel->m_sTITLE)){
				if (lpChatChannel->lpPlayerInfo == NULL){
					sprintf(szTemp, "");
					AddRecordMsg("ERROR NULL pointer in ChannelTalkProc, lpPlayerInfo");
					continue;
				}else{
					bFindMaster = TRUE;
					break;
				}
			}
		}
	}
	if(bFindMaster){
		if(strcmp(me->szEName,lpChatChannel->lpPlayerInfo->szEName)){
			LeaveCriticalSection(&myglobs.csChatChannel);
			szMsgToChannel = SZTALKTOALL + CString(" ") + CString("必須是頻道主才能使用這個功能");
			me->SendMsg(szMsgToChannel);
			return;
		}
	}  

	for(i=0;i<j;i++){
		if(!bFindHead){
			lpChatChannel = chatchannellist.GetAt(chatchannellist.FindIndex(i));
			if(!lstrcmp(szWhichTitle,lpChatChannel->m_sTITLE)){
				if (lpChatChannel->lpPlayerInfo == NULL){
					sprintf(szTemp, "ERROR NULL pointer in ChannelTalkProc, lpPlayerInfo");
					AddRecordMsg(szTemp);
					continue;
				}else if(!strcmp(lpChatChannel->lpPlayerInfo->szEName,szWho) || 
						!strcmp(lpChatChannel->lpPlayerInfo->szCName,szWho)	){
					bFindHead = TRUE;
					pos = chatchannellist.FindIndex(i);
					break;
				}
			} 
		}
	}

	if(bFindHead){
		lpChatChannel->lpPlayerInfo->SendMsg(szGetOut);
		pos2 = pos;
		chatchannellist.RemoveAt(pos2);
		delete pos2;
		szMsgToChannel = SZOKMSG + CString(" ") + CString("你已經將") + 
							szWho + CString("從頻道中刪除");
		me->SendMsg(szMsgToChannel);
	}else {
		szMsgToChannel = SZOKMSG + CString(" ") + CString("找不到你要刪除的人");
		me->SendMsg(szMsgToChannel);
	}
	LeaveCriticalSection(&myglobs.csChatChannel);

}
