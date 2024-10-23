#include "stdafx.h"
#include "XmudOS.h"
#include "MainWnd.h"
#include "CmdPlayerLogon.h"
#include "Map\MapInfo.h"
#include "Common.h"
#include "hash.h"

#include "wgs\DS_API.h"

extern char g_tszPathName[256];
extern rmfullglobals myglobs;
extern CList <TClientConData *,TClientConData* >playersocketlist;
extern CList <TDataUser*,TDataUser*>userlist;

extern void GetXFileName(CPlayerInfo *lpPlayerInfo);
extern void GetPlayerTitle(CPlayerInfo *lpPlayerInfo);

void CCmdPlayerLogon::PlayerCreateCmdProc(char *UserName,char *PlayerName,char *stNewPlayerName,char *stPassword,
			  char *stChineseName,char *sex,char *Strength,
			  char *Int,char *dex,char *con,char *Result)
{
	CPlayerInfo* lpPlayerInfo;
	char szPath[256], szFileName[256];
	int nRet=0, nTest;
	char szTest[256];
	CString sResultMsg;
	int i,sum;
	int istrength,iint,icon,idex,itmp;

	i = 0;
	while(stChineseName[i] != NULL){
		if(((stChineseName[i]>='\xa1')&&(stChineseName[i]<='\xf9'))	&&
			(((stChineseName[i+1]>='\x40')&&(stChineseName[i+1]<='\x7e'))||((stChineseName[i+1]>='\xa1')&&(stChineseName[i+1]<='\xfe'))))
			i += 2;
		else if((stChineseName[i]>='\x21')&&(stChineseName[i]<='\x7e'))
			i++;
		else
			ReturnResult(szPlayerCNameErrMsg)
	}

	istrength=strtol(Strength,'\0',10);
	iint = strtol(Int,'\0',10);
	idex = strtol(con,'\0',10);
	icon = strtol(dex,'\0',10);

	CString strtmp = stNewPlayerName;
	sum = strtmp.GetLength( );
	for(i=0;i<sum;i++)
	{
		if(!isalpha(strtmp.GetAt(i) ) ){
			ReturnResult(szSystemRigged)
		}
	}
	strtmp = stPassword;
	sum = strtmp.GetLength( );
	if ( sum < 5 ){
		ReturnResult(szSystemRigged)
	}
	for(i=0;i<sum;i++){
		if(iscntrl(strtmp.GetAt(i) ) ){
			ReturnResult(szSystemRigged)
		}
	}
	if(istrength<MINATTR||iint<MINATTR||icon<MINATTR||idex<MINATTR){
		ReturnResult(szSystemRigged);
	}
	if(istrength>MAXATTR||iint>MAXATTR||icon>MAXATTR||idex>MAXATTR){
		ReturnResult(szSystemRigged);
	}
	sum = istrength+iint+icon+idex;
	if(sum>BASEATTR){
		ReturnResult(szSystemRigged)
	}
	
	lpPlayerInfo = new CPlayerInfo;
	if( !lpPlayerInfo ){
		sprintf(szTest,"ERROR (%s,%s) New lpPlayerInfo fail",
			stNewPlayerName, UserName);
		AddRecordMsg(szTest);
		ReturnResult(szOutOfMemoryErrMsg)
	}
	szHashName(UserName, szPath);
	strcpy(szFileName,UserName);
	strcat(szFileName,".sav");
	EnterCriticalSection(&myglobs.csUserlist);

	nTest = FindPlayer(UserName,szPath,szFileName,stNewPlayerName);
	if (nTest == 1) {
		LeaveCriticalSection(&myglobs.csUserlist);
		ReturnResult(szPlayerAccountHasExistErrMsg);
	}
	if (nTest <= 0) {
		sprintf(szTest,"ERROR (%s,%s) Find Player, err=%d",
			stNewPlayerName, UserName, nTest);
		AddRecordMsg(szTest);
		LeaveCriticalSection(&myglobs.csUserlist);
		ReturnResult(szDiskReadErrMsg);
	}

	nTest = AddPlayer(UserName,szPath,szFileName,stChineseName,stNewPlayerName,"1");
	LeaveCriticalSection(&myglobs.csUserlist);
	if (nTest <= 0) {
		sprintf(szTest,"ERROR (%s,%s) Add Player, err=%d",
			stNewPlayerName, UserName, nTest);
		AddRecordMsg(szTest);
		ReturnResult(szDiskWriteErrMsg);
	}

	lpPlayerInfo->szCName = stChineseName;
	lpPlayerInfo->szEName = stNewPlayerName;
	lpPlayerInfo->nShen = 0;
	lpPlayerInfo->szSex = sex;
	lpPlayerInfo->nAge = 14;
	lpPlayerInfo->nStr = istrength;
	lpPlayerInfo->nInt = iint;
	lpPlayerInfo->nCon = icon;
	lpPlayerInfo->nDex = idex;
	lpPlayerInfo->nEff_jing = 100;
	lpPlayerInfo->nMax_jing = 100;
	lpPlayerInfo->nEff_qi = 100;
	lpPlayerInfo->nMax_qi = 100;
	lpPlayerInfo->nEff_jingli = 0;
	lpPlayerInfo->nMax_jingli = 0;
	lpPlayerInfo->nAdd_Jingli = 0;
	lpPlayerInfo->nEff_force = 0;
	lpPlayerInfo->nMax_force = 0;
	lpPlayerInfo->nAdd_force = 0;
	lpPlayerInfo->nCombat_exp = 0;
	lpPlayerInfo->nScore = 0;
	lpPlayerInfo->nQianNeng = 99;
	lpPlayerInfo->szFamily = "µLªù¬£";
	lpPlayerInfo->nGeneration = 0;
	itmp = istrength * 10;
	lpPlayerInfo->nEat = itmp;
	lpPlayerInfo->nMax_Eat = itmp;
	lpPlayerInfo->nDrink = itmp;
	lpPlayerInfo->nMax_Drink = itmp;
	lpPlayerInfo->szTeacher = "";
	lpPlayerInfo->szNickName = "";
	lpPlayerInfo->szRoom = "xy_guangchang";
	lpPlayerInfo->nKillNpc = 0;
	lpPlayerInfo->nKillPlayer = 0;
	lpPlayerInfo->nKilled = 0;
	lpPlayerInfo->nPlayerStatus = PS_moneyfixed | PS_attrfixed;
	lpPlayerInfo->nBetray = 0;
	lpPlayerInfo->nStatus = 0;
	lpPlayerInfo->szPerson = "";
	lpPlayerInfo->nMoney = 50;
	lpPlayerInfo->bPlayer = TRUE;
	lpPlayerInfo->szPassWord=stPassword;
	lpPlayerInfo->szUserName=UserName;
	GetXFileName(lpPlayerInfo);
	GetPlayerTitle(lpPlayerInfo);

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
	
	sResultMsg += ("\n");
	sResultMsg += ("\n");

	for(int k=0;k<10;k++)	{
		lpPlayerInfo->nRefile[i]=0;
		strtmp.Format("%d",lpPlayerInfo->nRefile[i]);
		sResultMsg += strtmp + (",");
	}
	sResultMsg += ("\n");

	
	delete lpPlayerInfo;
	strcpy(szFileName,stNewPlayerName);
	strcat(szFileName,".inf");
	nTest = DSSaveData(UserName, szPath, szFileName, sResultMsg);
	if (nTest <= 0) {
		sprintf(szTest, "ERROR (%s,%s) Create .inf fail %d",
			stNewPlayerName, UserName, nTest);
		ReturnResult(szDiskWriteErrMsg)
	}
	
	lstrcpy(PlayerName,stNewPlayerName);
	nTest = CreatePlayerSkillFile(UserName,PlayerName);
	if(nTest <= 0) {
		sprintf(szTest, "ERROR (%S,%s) Create .skill fail %d",
			PlayerName, UserName, nTest);
		AddRecordMsg(szTest);
		ReturnResult(szDiskWriteErrMsg);
	}
	nTest = CreatePlayerEquipFile(UserName,PlayerName);
	if(nTest <= 0) {
		sprintf(szTest, "ERROR (%S,%s) Create .equip fail %d",
			PlayerName, UserName, nTest);
		AddRecordMsg(szTest);
		ReturnResult(szDiskWriteErrMsg);
	}
	ReturnResult("OK");
}

int CCmdPlayerLogon::CreatePlayerSkillFile(char *UserName,char *PlayerName)
{
	char szBuf[DSBUFSIZE], szPath[256], szFileName[256];
	int nTest=-1;
	memset( szBuf, 0, sizeof( szBuf));
	szHashName(UserName, szPath);
	strcpy(szFileName,PlayerName);
	strcat(szFileName,".skill");

	nTest = DSSaveData(UserName, szPath, szFileName, szBuf);

	if( ResetPlayerData( szPath, szFileName, "default.skill" ) == FALSE )
		return -1;
	else
		return nTest;
}

int CCmdPlayerLogon::CreatePlayerEquipFile(char *UserName,char *PlayerName)
{
	char szBuf[DSBUFSIZE], szPath[256], szFileName[256];
	int nTest=-1;
	memset( szBuf, 0, sizeof( szBuf));
	szHashName(UserName, szPath);
	strcpy(szFileName,PlayerName);
	strcat(szFileName,".equip");

	nTest = DSSaveData(UserName, szPath, szFileName, szBuf);

	if( ResetPlayerData( szPath, szFileName, "default.equip" ) == FALSE )
		return -1;
	else
		return nTest;
}


void CCmdPlayerLogon::PlayerDeleteCmdProc(char *UserName,char *PlayerName,char *Result)
{
	char szPathName[256],szInfoFile[256],szSkillFile[256],szEquipFile[256],szPlayerSave[256];
	FILE *fp;
	char buf1[256], buf2[DSBUFSIZE];
	char temp1[80],temp2[80],temp3[80];
	szHashName(UserName, szPathName);
	sprintf(szPlayerSave,"%s\\%s\\%s%s", g_tszPathName, szPathName, UserName, ".sav");
	sprintf(szInfoFile,  "%s\\%s\\%s%s", g_tszPathName, szPathName, PlayerName,".inf");
	sprintf(szSkillFile, "%s\\%s\\%s%s", g_tszPathName, szPathName, PlayerName,".skill");
	sprintf(szEquipFile, "%s\\%s\\%s%s", g_tszPathName, szPathName, PlayerName,".equip");

	DeleteFile( szInfoFile);
	DeleteFile( szSkillFile);
	DeleteFile( szEquipFile);
	memset( buf2, 0, sizeof( buf2));
	if((fp=fopen( szPlayerSave, "r")) != NULL )	{
		while( fgets( buf1, sizeof( buf1), fp) != NULL )	{
			sscanf( buf1,"%s %s %s", temp1 ,temp2 ,temp3 );
			if( strcmp( temp2, PlayerName) )	{
				strcat( buf2, buf1);
			}
		}
		fclose( fp);
	}
	sprintf(szPlayerSave,"%s%s", UserName, ".sav");
	DSSaveData( UserName, szPathName, szPlayerSave, buf2 );
	ReturnResult("OK");
}

BOOL ResetPlayerData( char *szPath, char *szFile, char *temFile)
{
	char Filename1[256];
	char Filename2[256];
	sprintf( Filename1,"%s\\%s", g_tszPathName, temFile);
	sprintf( Filename2,"%s\\%s\\%s", g_tszPathName, szPath, szFile);

	if( CopyFile( Filename1, Filename2, FALSE) == TRUE )
		return TRUE;
	else
		return FALSE;
}
