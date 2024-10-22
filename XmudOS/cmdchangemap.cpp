#include "stdafx.h"
#include "XmudOS.h"
#include "CommandCheck.h"
#include "CmdPlayerLogon.h"
#include "Map\MapInfo.h"
#include "common.h"
#include "Npc\Npc.h"

extern rmfullglobals myglobs;
extern CList <TClientConData *,TClientConData* >playersocketlist;
extern CList <CBaseMap*,CBaseMap*>maplist;

void CCommandCheck::ChangeMapProc(char* PlayerName,char* sMapName,char* Result,
								  LPVOID pvPlayer,sockaddr_in IPAddr)
{
	CPlayerInfo *lpPlayerInfo;
	char szTemp[256];

	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	if (lpPlayerInfo == NULL) {
		sprintf(szTemp, "ERROR NULL pointer in ChangeMapProc, lpPlayerInfo");
		AddRecordMsg(szTemp);
		return;
	}

	if(lpPlayerInfo->nStatus != AOS_none){
		sprintf(szTemp,"%s FAIL 你正在忙,目前無法切換地圖!",szChangeMapCmd);
		lpPlayerInfo->SendMsg(szTemp);
		sprintf(szTemp,"(%s,%s) Fail returned by ChangeMapProc ", lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
		return;
	}
	CBaseMap *lpCurrentMap,*lpNextMap;
	CNpc *lpNpc;
	POSITION pos,mappos;
	BOOL bFindMap = FALSE;
	int j=0,i=0;
	EnterCriticalSection(&myglobs.csMaplist);
	j = maplist.GetCount();
	for(i=0;i<j;i++){
		lpNextMap = maplist.GetAt(maplist.FindIndex(i));
		if(lpNextMap!=NULL){
			if (!_stricmp(lpNextMap->szEName,sMapName)){
				mappos = maplist.FindIndex(i);
				bFindMap = TRUE;
				break;
			}
		}
	}
	if(!bFindMap) {
		LeaveCriticalSection(&myglobs.csMaplist);
		sprintf(szTemp,"%s FAIL 通往的地圖不存在!",szChangeMapCmd);
		lpPlayerInfo->SendMsg(szTemp);
		sprintf(szTemp,"(%s,%s) The next map (%s) didn't exist ", lpPlayerInfo->szEName, lpPlayerInfo->szUserName,sMapName);
	    AddRecordMsg(szTemp);
		return;
	}
	if (lpPlayerInfo->pMapPosite != NULL){
		lpCurrentMap = maplist.GetAt(lpPlayerInfo->pMapPosite);
		if (lpCurrentMap == NULL){
			LeaveCriticalSection(&myglobs.csMaplist);
			sprintf(Result,"FAIL %s",szSystemErrMsg);
			sprintf(szTemp,"(%s,%s) ERROR NULL pointer in ChangeMapProc, lpDataMap ", lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
			AddRecordMsg(szTemp);
			return;
		}
	}
	pos = lpCurrentMap->listNpc.GetHeadPosition();
	while (pos != NULL){
		lpNpc = lpCurrentMap->listNpc.GetNext(pos);
		if ((lpNpc->nStatus != AOS_dead) 
			&& (lpNpc->szFamily == lpNextMap->szFamily)
			&& (lpNpc->szFamily == lpCurrentMap->szFamily) 
			&& (lpNextMap->szFamily != "無門派")
			&& (lpNpc->nAttitude & NP_guard) 
			&& (lpPlayerInfo->szFamily != "華義國際")
			&& (lpNextMap->szFamily != lpPlayerInfo->szFamily)){
			LeaveCriticalSection(&myglobs.csMaplist);
			strcpy(szTemp, "_Without_guard_ask_");
			for (int i = 0; i < lpNpc->nAsk; i++){
				if (strcmp("_guard", lpNpc->szAsk[i]) == 0){
					sprintf(szTemp,"%s FAIL %s", szChangeMapCmd, lpNpc->szNpcAsk[i]);
					break;
				}
			}
			if(strcmp(szTemp, "_Without_guard_ask_") == 0){
				if(lpNpc->nShen >= 0){
					sprintf(szTemp,"%s FAIL %s：此路通往我%s重地，非本派人不得擅自進入，%s請止步！", szChangeMapCmd, lpNpc->szCName, lpNpc->szFamily, GetSpecialName(lpPlayerInfo,1));
				}else{
					sprintf(szTemp,"%s FAIL %s：沒有我的同意，誰都別想過去！", szChangeMapCmd, lpNpc->szCName);
				}
			}

			lpPlayerInfo->SendMsg(szTemp);
			sprintf(szTemp,"(%s,%s) Blocked by NPC:%s in ChangeMapProc ",
				lpPlayerInfo->szEName, lpPlayerInfo->szUserName, lpNpc->szEName);
			return;
		}
	}
	LeaveCriticalSection(&myglobs.csMaplist);
	EnterCriticalSection(&myglobs.csSentCliMsg);
	lpPlayerInfo->bNoHealing = TRUE;
	lpPlayerInfo->nStatus = AOS_changemap;

	sprintf(szTemp,"%s OK %s",szChangeMapCmd,sMapName);
	lpPlayerInfo->listmsg.AddHead(szTemp);
	LeaveCriticalSection(&myglobs.csSentCliMsg);
	
	sprintf(szTemp,"(%s,%s) Ask server for changing map", lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
	AddRecordMsg(szTemp);
}

void CCommandCheck::SendMapDataProc(char* PlayerName,char* sMapName,char* Result,
								  LPVOID pvPlayer,sockaddr_in IPAddr)
{
	CBaseMap * lpDataMap;
	CPlayerInfo *lpPlayerInfo,*lpOtherPlayerInfo;
	int i,j;
	POSITION tmppos = NULL;
	CNpc *lpNpc;
	POSITION pos, lastpos, mappos;
	CString NewMap;
	char szTemp[256];
	lpPlayerInfo = (CPlayerInfo*)pvPlayer;
	if (lpPlayerInfo == NULL) {
		sprintf(szTemp, "ERROR NULL pointer in SendMapDataProc, lpPlayerInfo");
		AddRecordMsg(szTemp);
		return;
	}
	if (strcmp(lpPlayerInfo->szCheck, SZAOBJCHECK)) {
		sprintf(szTemp, "ERROR Bad data in SendMapDataProc, lpPlayerInfo");
		AddRecordMsg(szTemp);
		return;
	}
	if(lpPlayerInfo->nStatus != AOS_changemapok){
		sprintf(szTemp,"%s %s 你目前無法切換地圖!",SZFAILMSG,szGreenHigt);
		lpPlayerInfo->SendMsg(szTemp);
		sprintf(szTemp,"(%s,%s) Fail returned by SendMapDataProc ", lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
		return;
	}
	POSITION pMapPosite = lpPlayerInfo->pMapPosite;
	EnterCriticalSection(&myglobs.csMaplist);
	BOOL bFindMap = FALSE;
	j = maplist.GetCount();
	for(i=0;i<j;i++){
		lpDataMap = maplist.GetAt(maplist.FindIndex(i));
		if(lpDataMap!=NULL){
			if(!_stricmp(lpDataMap->szEName,sMapName)){
				mappos = maplist.FindIndex(i);
				NewMap = lpDataMap->szCName;
				bFindMap = TRUE;
				break;
			}
		}
	}
	if(!bFindMap) {
		LeaveCriticalSection(&myglobs.csMaplist);
		ReturnResult(szSystemRigged);
		return;
	}
	if (lpPlayerInfo->pMapPosite != NULL) {
		lpDataMap = maplist.GetAt(lpPlayerInfo->pMapPosite);
		if (lpDataMap == NULL) {
			LeaveCriticalSection(&myglobs.csMaplist);
			return;
		}
		CString parm = CString("\t");
		CString strtmp = szSomeoneQuitMap 
						+ CString(" ") + lpPlayerInfo->szEName
						+ (" ") + NewMap;

		pos = lpDataMap->listplayer.GetHeadPosition();
		while (pos != NULL) {
			lastpos = pos;
			lpOtherPlayerInfo = lpDataMap->listplayer.GetNext(pos);
			if (lpOtherPlayerInfo == NULL) {
				lpDataMap->listplayer.RemoveAt(lastpos);
				sprintf(szTemp, "ERROR NULL pointer in ChangeMapProc, lpOtherPlayerInfo");
				AddRecordMsg(szTemp);
				continue;
			}
			if (strcmp(lpOtherPlayerInfo->szCheck, SZAOBJCHECK)) {
				sprintf(szTemp, "ERROR Bad data in ChangeMapProc, lpOtherPlayerInfo");
				AddRecordMsg(szTemp);
				lpDataMap->listplayer.RemoveAt(lastpos);
				continue;
			}
			if(lpOtherPlayerInfo->szEName != lpPlayerInfo->szEName){

				lpOtherPlayerInfo->SendMsg(strtmp);

			}else{
				tmppos = lastpos;
			}
		}
		if(tmppos != NULL)
			lpDataMap->listplayer.RemoveAt(tmppos);
		if (lpDataMap->listplayer.GetCount() == 0) {
			pos = lpDataMap->listNpc.GetHeadPosition();
			while (pos != NULL) {
				lpNpc = lpDataMap->listNpc.GetNext(pos);
				if ((lpNpc->nStatus == AOS_dead) && (lpNpc->nRecover <= 0)) {
					lpNpc->nEff_force = lpNpc->nMax_force = lpNpc->GetSkillLevel("BaseForce") * 10;
					lpNpc->nEff_jingli = lpNpc->nMax_jingli = lpNpc->GetSkillLevel("BaseForce") * 3;
					lpNpc->nEff_qi = lpNpc->nMax_qi = lpNpc->GetMaxQi();
					lpNpc->nEff_jing = lpNpc->nMax_jing = lpNpc->GetMaxJing();
					lpNpc->nStatus = AOS_none;
				}
			}
		}
	}
	lpPlayerInfo->pMapPosite = mappos;
	lpDataMap = maplist.GetAt(mappos);
	lpPlayerInfo->szRoom = lpDataMap->szEName;
	lpDataMap->listplayer.AddTail(lpPlayerInfo);
	LeaveCriticalSection(&myglobs.csMaplist);
	CString tmpMsg = _T("");
	CCmdPlayerLogon m_CmdPlayerLogon;
	tmpMsg = CString("OK\t") + m_CmdPlayerLogon.GatherMapData(lpPlayerInfo);
	EnterCriticalSection(&myglobs.csSentCliMsg);
	lpPlayerInfo->nStatus = AOS_sendmap;
	lpPlayerInfo->listmsg.AddHead(tmpMsg);	
	LeaveCriticalSection(&myglobs.csSentCliMsg);
	lpPlayerInfo->nEscapeNow = 0;
	sprintf(szTemp, "(%s,%s) Leave sendmap procedure", lpPlayerInfo->szEName, lpPlayerInfo->szUserName);
	ReturnResult("OK");
}