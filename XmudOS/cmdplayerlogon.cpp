#include "stdafx.h"
#include "XmudOS.h"
#include "CmdPlayerLogon.h"
#include "map\MapInfo.h"
#include "goods\goods\Goods.h"
#include "skill\skill\Skill.h"
#include "wgs\common.h"

#include "hash.h"

#include "wgs\DS_API.h"

extern char g_tszPathName[256];
extern rmfullglobals myglobs;
extern CList <TClientConData *,TClientConData* >playersocketlist;
extern CList <CBaseMap*,CBaseMap*>maplist;
int g_iActiveClientNum = 0;

CCmdPlayerLogon::CCmdPlayerLogon()
{

}

CCmdPlayerLogon::~CCmdPlayerLogon()
{

}


void FixPlayerAttr(CPlayerInfo *lpPlayerInfo)
{
	int nStr, nInt, nCon, nDex, nBase, nTotal, i = 0;
	if (lpPlayerInfo->szNickName == "充氣娃娃") return;
	if (!(lpPlayerInfo->nPlayerStatus & PS_attrfixed)) {
		lpPlayerInfo->nPlayerStatus |= PS_attrfixed;
		lpPlayerInfo->nBetray = 0;
		nStr = lpPlayerInfo->GetSkillLevel("BaseUnarmed")/10 + MINATTR;
		nInt = lpPlayerInfo->GetSkillLevel("OtherLiterate")/10 + MINATTR;
		nCon = lpPlayerInfo->GetSkillLevel("BaseForce")/10 + MINATTR;
		nDex = lpPlayerInfo->GetSkillLevel("BaseDodge")/10 + MINATTR;
		nBase = nStr + nInt + nCon + nDex + BASEATTR - MINATTR*4;
		nTotal = lpPlayerInfo->nStr + lpPlayerInfo->nInt + lpPlayerInfo->nCon 
			+ lpPlayerInfo->nDex;
		while (nTotal > nBase) {
			switch (i) {
			case 0:
				if (lpPlayerInfo->nStr > nStr) {
					lpPlayerInfo->nStr--;
					nTotal--;
				}
				break;
			case 1:
				if (lpPlayerInfo->nInt > nInt) {
					lpPlayerInfo->nInt--;
					nTotal--;
				}
				break;
			case 2:
				if (lpPlayerInfo->nCon > nCon) {
					lpPlayerInfo->nCon--;
					nTotal--;
				}
				break;
			case 3:
				if (lpPlayerInfo->nDex > nDex) {
					lpPlayerInfo->nDex--;
					nTotal--;
				}
				break;
			}
			if (i>=3) i=0; else i++;
		}
		while (nTotal < nBase) {
			switch (i) {
			case 0:
				lpPlayerInfo->nStr++;
				nTotal++;
				break;
			case 1:
				lpPlayerInfo->nInt++;
				nTotal++;
				break;
			case 2:
				lpPlayerInfo->nCon++;
				nTotal++;
				break;
			case 3:
				lpPlayerInfo->nDex++;
				nTotal++;
				break;
			}
			if (i>=3) i=0; else i++;
		}
	}
}

void GetPlayerTitle(CPlayerInfo *lpPlayerInfo)
{
	if (lpPlayerInfo->szNickName == "充氣娃娃") return;
	if ((lpPlayerInfo->nShen >= 5000000) && (lpPlayerInfo->nCombat_exp >=2500000)) {
		lpPlayerInfo->szTilte = "武林至尊";
	} else if ((lpPlayerInfo->nShen >= 1000000) && (lpPlayerInfo->nCombat_exp >= 500000)) {
		lpPlayerInfo->szTilte = "武聖";
	} else if ((lpPlayerInfo->nShen >= 250000) && (lpPlayerInfo->nCombat_exp >= 125000)) {
		lpPlayerInfo->szTilte = (lpPlayerInfo->szSex == "M")?"英雄":"巾幗英雄";
	} else if ((lpPlayerInfo->nShen >= 50000) && (lpPlayerInfo->nCombat_exp >= 25000)) {
		lpPlayerInfo->szTilte = (lpPlayerInfo->szSex == "M")?"豪傑":"女英豪";
	} else if ((lpPlayerInfo->nShen >= 10000) && (lpPlayerInfo->nCombat_exp >= 5000)) {
		lpPlayerInfo->szTilte = "大俠";
	} else if (lpPlayerInfo->nShen >= 2500) {
		if (lpPlayerInfo->nCombat_exp >= 5000) {
			lpPlayerInfo->szTilte = "俠客";
		} else if (lpPlayerInfo->nCombat_exp >= 1250) {
			lpPlayerInfo->szTilte = (lpPlayerInfo->szSex == "M")?"少俠":"俠女";
		} else if (lpPlayerInfo->nCombat_exp >= 250) {
			lpPlayerInfo->szTilte = (lpPlayerInfo->szSex == "M")?"好漢":"鐵娘子";
		} else if (lpPlayerInfo->nCombat_exp >= 50) {
			lpPlayerInfo->szTilte = "善人";
		} else {
			lpPlayerInfo->szTilte = "良民";
		}
	} else if (lpPlayerInfo->nShen >= 500) {
		if (lpPlayerInfo->nCombat_exp >= 5000) {
			lpPlayerInfo->szTilte = "名士";
		} else if (lpPlayerInfo->nCombat_exp >= 250) {
			lpPlayerInfo->szTilte = (lpPlayerInfo->szSex == "M")?"好漢":"鐵娘子";
		} else if (lpPlayerInfo->nCombat_exp >= 50) {
			lpPlayerInfo->szTilte = "善人";
		} else {
			lpPlayerInfo->szTilte = "良民";
		}
	} else if (lpPlayerInfo->nShen >= 100) {
		if (lpPlayerInfo->nCombat_exp >= 5000) {
			lpPlayerInfo->szTilte = "名士";
		} else if (lpPlayerInfo->nCombat_exp >= 50) {
			lpPlayerInfo->szTilte = "善人";
		} else {
			lpPlayerInfo->szTilte = "良民";
		}
	} else if ((lpPlayerInfo->nShen <= -5000000) && (lpPlayerInfo->nCombat_exp >= 2500000)) {
		lpPlayerInfo->szTilte = "混世魔王";
	} else if ((lpPlayerInfo->nShen <= -1000000) && (lpPlayerInfo->nCombat_exp >= 500000)) {
		lpPlayerInfo->szTilte = "大邪神";
	} else if ((lpPlayerInfo->nShen <= -250000) && (lpPlayerInfo->nCombat_exp >= 125000)) {
		lpPlayerInfo->szTilte = (lpPlayerInfo->szSex == "M")?"魔頭":"魔女";
	} else if ((lpPlayerInfo->nShen <= -50000) && (lpPlayerInfo->nCombat_exp >= 25000)) {
		lpPlayerInfo->szTilte = (lpPlayerInfo->szSex == "M")?"煞星":"女煞星";
	} else if ((lpPlayerInfo->nShen <= -10000) && (lpPlayerInfo->nCombat_exp >= 5000)) {
		lpPlayerInfo->szTilte = (lpPlayerInfo->szSex == "M")?"惡霸":"母夜叉";
	} else if (lpPlayerInfo->nShen <= -2500) {
		if (lpPlayerInfo->nCombat_exp >= 5000) {
			lpPlayerInfo->szTilte = "強豪";
		} else if (lpPlayerInfo->nCombat_exp >= 1250) {
			lpPlayerInfo->szTilte = "惡徒";
		} else if (lpPlayerInfo->nCombat_exp >= 250) {
			lpPlayerInfo->szTilte = "流氓";
		} else if (lpPlayerInfo->nCombat_exp >= 50) {
			lpPlayerInfo->szTilte = "地痞";
		} else {
			lpPlayerInfo->szTilte = "混混";
		}
	} else if (lpPlayerInfo->nShen <= -500) {
		if (lpPlayerInfo->nCombat_exp >= 5000) {
			lpPlayerInfo->szTilte = "霸者";
		} else if (lpPlayerInfo->nCombat_exp >= 250) {
			lpPlayerInfo->szTilte = "流氓";
		} else if (lpPlayerInfo->nCombat_exp >= 50) {
			lpPlayerInfo->szTilte = "地痞";
		} else {
			lpPlayerInfo->szTilte = "混混";
		}
	} else if (lpPlayerInfo->nShen <= -100) {
		if (lpPlayerInfo->nCombat_exp >= 5000) {
			lpPlayerInfo->szTilte = "霸者";
		} else if (lpPlayerInfo->nCombat_exp >= 50) {
			lpPlayerInfo->szTilte = "地痞";
		} else {
			lpPlayerInfo->szTilte = "混混";
		}
	} else {
		if (lpPlayerInfo->nCombat_exp >= 125000) {
			lpPlayerInfo->szTilte = "隱士";
		} else if (lpPlayerInfo->nCombat_exp >= 5000) {
			lpPlayerInfo->szTilte = "武者";
		} else {
			lpPlayerInfo->szTilte = "庶民";
		}
	}
}

void GetXFileName(CPlayerInfo * lpPlayerInfo)
{
	if (lpPlayerInfo->szNickName == "充氣娃娃") return;
	if (lpPlayerInfo->szFamily == "武當派") {
		if (lpPlayerInfo->szSex == "M") {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudnqn01.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudxds02.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudld01.x";
			}
		} else {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudsnv01.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudnx04.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudznng03.x";
			}
		}
	} else if (lpPlayerInfo->szFamily == "少林派") {
		if (lpPlayerInfo->szSex == "M") {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudpths01.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudpths02.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudcjshs01.x";
			}
		}
	} else if (lpPlayerInfo->szFamily == "丐幫") {
		if (lpPlayerInfo->szSex == "M") {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudnqn03.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudznnz03.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudqg02.x";
			}
		} else {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudnqnz02.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudgf01.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudlf01.x";
			}
		}
	} else if (lpPlayerInfo->szFamily == "華山派") {
		if (lpPlayerInfo->szSex == "M") {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudsn01.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudjk01.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudlt03.x";
			}
		} else {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudyh01.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudnx01.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudznfn01.x";
			}
		}
	} else if (lpPlayerInfo->szFamily == "星宿派") {
		if (lpPlayerInfo->szSex == "M") {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudnqn02.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmuddh01.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudhj01.x";
			}
		} else {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudnqnz01.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudnx02.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudznfn02.x";
			}
		}
	} else if (lpPlayerInfo->szFamily == "峨眉派") {
		if (lpPlayerInfo->szSex == "F") {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudnqng01.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudznng01.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudznng02.x";
			}
		}
	} else if (lpPlayerInfo->szFamily == "無門派") { // 無門派
		if (lpPlayerInfo->szSex == "M") {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudsn02.x";
				AddRecordMsg("Change Close in GetX");
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudznnz02.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudlt02.x";
			}
		} else {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudsnv02.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudnx03.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudlf02.x";
			}
		}
	} else { // 其他門派
		if (lpPlayerInfo->szSex == "M") {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudsn03.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudznnz02.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudlt02.x";
			}
		} else {
			if (lpPlayerInfo->nAge < 30) {
				lpPlayerInfo->szXFileName = "pmudsnv03.x";
			} else if (lpPlayerInfo->nAge < 60) {
				lpPlayerInfo->szXFileName = "pmudnx03.x";
			} else {
				lpPlayerInfo->szXFileName = "pmudlf02.x";
			}
		}
	}
}

void CCmdPlayerLogon::PlayerLogonCmdProc(SOCKET hPlayerSocket,
						char *UserName,
						char *PlayerName,
						char *stName,
						char *stPasswd,
						char *Result,
						sockaddr_in IPAddr,
						PCLientConData lpClientConData)
//						LPVOID &pvPlayer)
{
	CPlayerInfo* lpPlayerInfo;
	char szPath[256],szFile[256],szTest[256],buf[256];
	char *ps, szBuf[DSBUFSIZE];
	char testn[128];
	int nTest, nLen;
//	FILE *fs;
	CStringList strls;
	CString strtmp;

//	Add_UserStart(UserName);

	szHashName(UserName,szPath);
	strcpy(szFile,stName);
	strcat(szFile,".inf");

	nTest = DSLoadData(UserName, szPath, szFile, szBuf);
	if (nTest <= 0) {
		strcpy(Result,"FAIL ");
		strcat(Result,szPlayerRecordErrMsg);
		sprintf(szTest,"ERROR (%s,%s) Open %s fail, err=%d",stName,UserName,szFile,nTest);
		AddRecordMsg(szTest);
		return;
	}
	ps = szBuf; nTest = 0; nLen = strlen(szBuf);
	while (nTest < nLen) {
		while ((nTest < nLen) && (szBuf[nTest] != '\n')) nTest++;
		szBuf[nTest] = 0;
		buf[0] = 0;
		sscanf(ps,"%s",buf);
		strls.AddTail(buf);
		ps = szBuf + nTest + 1;
	}

/*	fs = fopen(szFileName,"r");
	if (fs == NULL) {
		strcpy(Result,"FAIL ");
		strcat(Result,szLogonErrMsg);
		sprintf(szTest,"ERROR (%s,%s) Open %s fail",stName,UserName,szFileName);
		AddRecordMsg(szTest);
		return;
	}
	while (fgets(buf,256,fs)) {
		buf1[0] = 0;
		sscanf(buf,"%s",buf1);
		strls.AddTail(buf1);
	}
	fclose(fs);
*/
	if(strls.GetCount() < 45)
	{
		strcpy(Result,"FAIL ");
		strcat(Result,szPlayerRecordErrMsg);
		sprintf(szTest,"ERROR (%s,%s) Read %s fail",stName,UserName,szFile);
		AddRecordMsg(szTest);
		return;
	}
	if(lstrcmp( UserName,strls.GetAt(strls.FindIndex(42))))
	{
		strcpy(Result,"FAIL ");
		strcat(Result,szLogonErrMsg);
		sprintf(szTest,"ERROR (%s,%s) Bad username in %s",stName,UserName,szFile);
		AddRecordMsg(szTest);
		return;
	}

	POSITION	pos;
	pos = strls.GetHeadPosition();
	lpPlayerInfo = new CPlayerInfo;
	if( !lpPlayerInfo ){
		strcpy(Result,"FAIL ");
		strcat(Result,szOutOfMemoryErrMsg);
		sprintf(szTest,"ERROR (%s,%s) Alloc playerinfo memory fail",stName,UserName);
		AddRecordMsg(szTest);
		return;
	}
	lpPlayerInfo->szCName =		strls.GetNext(pos);
	//andy_add rePlayername 2002/01/20 11:16
	{
		int i = 0;
		char username[128];
		strcpy( username, lpPlayerInfo->szCName);
		while(username[i] != NULL){
			if(((username[i]>='\xa1')&&(username[i]<='\xf9'))	&&
				(((username[i+1]>='\x40')&&(username[i+1]<='\x7e'))||((username[i+1]>='\xa1')&&
				(username[i+1]<='\xfe'))))
				i += 2;
			else if((username[i]>='\x21')&&(username[i]<='\x7e'))
				i++;
			else
				ReturnResult(szPlayerCNameErrMsg)
		}
	}

	lpPlayerInfo->szEName =		strls.GetNext(pos);
	strcpy( testn, lpPlayerInfo->szEName);
	lpPlayerInfo->szNickName =	strls.GetNext(pos);
	lpPlayerInfo->szTilte =		strls.GetNext(pos);
	lpPlayerInfo->szXFileName = strls.GetNext(pos);
	lpPlayerInfo->szFamily =	strls.GetNext(pos);
	if (lpPlayerInfo->szFamily.IsEmpty()) lpPlayerInfo->szFamily = "無門派";
	lpPlayerInfo->szRoom =		strls.GetNext(pos);
	lpPlayerInfo->szSex =		strls.GetNext(pos);
	
	lpPlayerInfo->nAge =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nShen =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	
	lpPlayerInfo->nStr =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nInt =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nCon =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nDex =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	
	lpPlayerInfo->nEff_qi =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nMax_qi =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nEff_jing =	atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nMax_jing =	atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nEff_jingli = atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nMax_jingli = atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nAdd_Jingli =	atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nEff_force =	atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nMax_force =	atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nAdd_force =	atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nCombat_exp = atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nScore =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nGeneration = atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nMoney =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nStatus =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	// Spock +1
	lpPlayerInfo->nStatus = AOS_none;
	
	lpPlayerInfo->szTeacher =	strls.GetNext(pos);
	lpPlayerInfo->szPerson =	strls.GetNext(pos);
	lpPlayerInfo->szPerson = ""; // 清除上次打倒的對手資料

	lpPlayerInfo->nQianNeng =	atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nEat =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nMax_Eat =	atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nDrink =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nMax_Drink =	atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nKillNpc =	atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nKillPlayer = atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nKilled =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nPlayerStatus =	atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nBetray =		atoi((char *)(LPCSTR)strls.GetNext(pos));
	lpPlayerInfo->nMudTime =	atoi((char *)(LPCSTR)strls.GetNext(pos));

	lpPlayerInfo->szUserName =	strls.GetNext(pos);
	lpPlayerInfo->szPassWord =	strls.GetNext(pos);
	lpPlayerInfo->nBankMoney = atoi((char*)(LPCSTR)strls.GetNext(pos));

	if(pos) {
		strtmp = strls.GetNext(pos);
		strcpy(buf, (char*)(LPCSTR)strtmp);
		ps = strtok(buf, ",");
		while (ps) {
			lpPlayerInfo->listBetray.AddTail(ps);
			ps = strtok(NULL, ",");
		}
	}
	int y=0;
	if(pos) {
		strtmp = strls.GetNext(pos);
		strcpy(buf, (char*)(LPCSTR)strtmp);
		ps = strtok(buf, ",");
		while (ps && y < 10) {
			if( atoi(ps) < 0 || atoi(ps) > 1 )
				lpPlayerInfo->nRefile[y] = 0;
			else
				lpPlayerInfo->nRefile[y] = atoi(ps);
				ps = strtok(NULL, ",");
				y++;
			
		}
	}
	if( lpPlayerInfo->nStr < 0 ) lpPlayerInfo->nStr = 0;
	if( lpPlayerInfo->nStr > 1000 ) lpPlayerInfo->nStr = 1000;
	if( lpPlayerInfo->nInt < 0 ) lpPlayerInfo->nInt = 0;
	if( lpPlayerInfo->nInt > 1000 ) lpPlayerInfo->nInt = 1000;
	if( lpPlayerInfo->nCon < 0 ) lpPlayerInfo->nCon = 0;
	if( lpPlayerInfo->nCon > 1000 ) lpPlayerInfo->nCon = 1000;
	if( lpPlayerInfo->nDex < 0 ) lpPlayerInfo->nDex = 0;
	if( lpPlayerInfo->nDex > 1000 ) lpPlayerInfo->nDex = 1000;


	if((lpPlayerInfo->nAge>30)&&(myglobs.bNoKill)){
		strcpy(Result,"FAIL 超過三十歲之人物不能到初入江湖");
		sprintf(szTest,"ERROR (%s,%s) Can't join No-kill server after age 30",lpPlayerInfo->szEName,lpPlayerInfo->szUserName);
		AddRecordMsg(szTest);
		return;
	}
	strls.RemoveAll();
	lpPlayerInfo->bPlayer	 =	TRUE;
	GetPlayerTitle(lpPlayerInfo);
	GetXFileName(lpPlayerInfo);
	lpPlayerInfo->hPlayerSocket = hPlayerSocket;
	lpPlayerInfo->IPAddr = IPAddr;
	strls.RemoveAll();
	nTest = LoadPlayerSkill(lpPlayerInfo);
	if(nTest <= 0)	{
		if(!lpPlayerInfo->listskill.IsEmpty())	{
			lpPlayerInfo->listskill.RemoveAll();
		}
		strcpy(Result, "FAIL 載入技能數據錯誤");
		sprintf(szTest,"ERROR (%s,%s) Read skill file error=%d",lpPlayerInfo->szEName,lpPlayerInfo->szUserName,nTest);
		AddRecordMsg(szTest);
		return;
	}
	nTest = LoadPlayerEquip(lpPlayerInfo);
	if(nTest <= 0)
	{
		lpPlayerInfo->listskill.RemoveAll();
		if(!lpPlayerInfo->listequip.IsEmpty())
		{
			lpPlayerInfo->listequip.RemoveAll();
		}
		strcpy(Result, "FAIL 載入裝備數據錯誤");
		sprintf(szTest,"ERROR (%s,%s) Read equip file error=%d",lpPlayerInfo->szEName,lpPlayerInfo->szUserName,nTest);
		AddRecordMsg(szTest);
		return;
	}

	FixPlayerAttr(lpPlayerInfo);
	if(lpPlayerInfo->szFamily == "峨嵋派") {
		if(lpPlayerInfo->szSex == "M") {
			lpPlayerInfo->szFamily = "無門派";
		} else {
			lpPlayerInfo->szFamily = "峨眉派";
			if (lpPlayerInfo->nBetray > 0) {
				TObjectSkill *lpSkill;
				POSITION pos;
				lpPlayerInfo->nBetray--;
				lpPlayerInfo->nCombat_exp += lpPlayerInfo->nCombat_exp >> 3;
				pos = lpPlayerInfo->listskill.GetHeadPosition();
				while(pos) {
					lpSkill = lpPlayerInfo->listskill.GetNext(pos);
					if (lpSkill->nLevel > 0) {
						lpSkill->nLevel++;
						if(lpSkill->nScore < lpSkill->nLevel*lpSkill->nLevel/2)
							lpSkill->nScore = lpSkill->nLevel*lpSkill->nLevel/2;
					}
				}
			}
		}
		GetXFileName(lpPlayerInfo);
	}
	if (!(lpPlayerInfo->nPlayerStatus & PS_moneyfixed) && (lpPlayerInfo->szNickName != "充氣娃娃")) {
		lpPlayerInfo->nPlayerStatus |= PS_moneyfixed;
		nTest = (lpPlayerInfo->nKillNpc + lpPlayerInfo->nKillPlayer) * 500;
		if (nTest < 50000) nTest = 50000;
		if (lpPlayerInfo->nMoney + lpPlayerInfo->nBankMoney > nTest) {
			sprintf(szTest,"ERROR (%s,%s)Money too much m=%d b=%d kn=%d kp=%d",
				lpPlayerInfo->szEName, lpPlayerInfo->szUserName,
				lpPlayerInfo->nMoney, lpPlayerInfo->nBankMoney,
				lpPlayerInfo->nKillNpc, lpPlayerInfo->nKillPlayer);
			AddRecordMsg(szTest);
			if(lpPlayerInfo->nMoney > nTest) {
				lpPlayerInfo->nMoney = nTest;
				lpPlayerInfo->nBankMoney = 0;
			} else {
				lpPlayerInfo->nBankMoney = nTest - lpPlayerInfo->nMoney;
			}
		}
	}
	if(lpPlayerInfo->nMoney > MAXMONEY) lpPlayerInfo->nMoney = MAXMONEY;
	if(lpPlayerInfo->nMoney < 0) lpPlayerInfo->nMoney = 0;

	if(lpPlayerInfo->nCombat_exp > MAXEXP ) {
		lpPlayerInfo->nCombat_exp = MAXEXP;
	}
	if(lpPlayerInfo->nShen > MAXSHEN) lpPlayerInfo->nShen = MAXSHEN;
	if(lpPlayerInfo->nShen < -MAXSHEN) lpPlayerInfo->nShen = -MAXSHEN;

	if(lpPlayerInfo->nMax_qi > lpPlayerInfo->GetMaxQi()) {
		lpPlayerInfo->nMax_qi = lpPlayerInfo->GetMaxQi();
	}
	if(lpPlayerInfo->nEff_qi > lpPlayerInfo->nMax_qi) {
		lpPlayerInfo->nEff_qi = lpPlayerInfo->nMax_qi;
	}
	if(lpPlayerInfo->nMax_jing > lpPlayerInfo->GetMaxJing()) {
		lpPlayerInfo->nMax_jing = lpPlayerInfo->GetMaxJing();
	}
	if(lpPlayerInfo->nEff_jing > lpPlayerInfo->nMax_jing) {
		lpPlayerInfo->nEff_jing = lpPlayerInfo->nMax_jing;
	}
	if(lpPlayerInfo->nMax_force > lpPlayerInfo->GetSkillLevel("BaseForce")*10) {
		lpPlayerInfo->nMax_force = lpPlayerInfo->GetSkillLevel("BaseForce")*10;
	}
	if(lpPlayerInfo->nEff_force > lpPlayerInfo->nMax_force*2) {
		lpPlayerInfo->nEff_force = lpPlayerInfo->nMax_force*2;
	}
	if(lpPlayerInfo->nMax_jingli > lpPlayerInfo->GetSkillLevel("BaseForce")*3) {
		lpPlayerInfo->nMax_jingli = lpPlayerInfo->GetSkillLevel("BaseForce")*3;
	}
	if(lpPlayerInfo->nEff_jingli > lpPlayerInfo->nMax_jingli*2) {
		lpPlayerInfo->nEff_jingli = lpPlayerInfo->nMax_jingli*2;
	}
	if(lpPlayerInfo->nAdd_force > MAXADDFORCE) {
		lpPlayerInfo->nAdd_force = MAXADDFORCE;
	}
	if(lpPlayerInfo->nAdd_Jingli > MAXADDJINGLI) {
		lpPlayerInfo->nAdd_Jingli = MAXADDJINGLI;
	}
	lpPlayerInfo->nMax_Eat = lpPlayerInfo->nStr * 10;
	lpPlayerInfo->nMax_Drink = lpPlayerInfo->nMax_Eat;
	lpPlayerInfo->bAttack = FALSE;

	if(lpPlayerInfo->szNickName == "充氣娃娃") {
		lpPlayerInfo->nEff_qi = lpPlayerInfo->nMax_qi = lpPlayerInfo->GetMaxQi();
		lpPlayerInfo->nEff_jing = lpPlayerInfo->nMax_jing = lpPlayerInfo->GetMaxJing();
		lpPlayerInfo->nMax_force = lpPlayerInfo->GetSkillLevel("BaseForce") * 10;
		lpPlayerInfo->nMax_jingli = lpPlayerInfo->GetSkillLevel("BaseForce") * 3;
	}

	if(!AppToMap(lpPlayerInfo)){
		strcpy(Result,"FAIL 加入到地圖數據錯誤");
		sprintf(szTest,"ERROR (%s,%s) Can't add player to map",lpPlayerInfo->szEName,lpPlayerInfo->szUserName);
		AddRecordMsg(szTest);
		return;
	}

	lpClientConData->szSendBuf = GatherPlayerData(Result,lpPlayerInfo);

	strcpy(PlayerName,lpPlayerInfo->szEName);

	lpClientConData->pvPlayer = lpPlayerInfo;
	strcpy(Result, "LOGON");

}

int CCmdPlayerLogon::LoadPlayerSkill(CPlayerInfo *lpPlayerInfo)
{
	char szPath[256], szFile[256], tmp1[256], tmp2[256];
	char *ps, szBuf[DSBUFSIZE];
	CString szSkillEName, szMapName, strtmp;
	int nTest, nScore, nLevel;
	CSkill *lpSkill;

	szHashName(lpPlayerInfo->szUserName, szPath);
	sprintf(szFile, "%s.skill", lpPlayerInfo->szEName);
	nTest = DSLoadData((char*)(LPCSTR)lpPlayerInfo->szUserName, szPath, szFile, szBuf);
	if (nTest <= 0) return nTest;
	ps = strtok(szBuf, "\n");
	if( ps == NULL )
		return -1;
	while (ps) {
		nTest = sscanf(ps,"%s %d %d %s",tmp1,&nScore,&nLevel,tmp2);
		ps = strtok(NULL, "\n");
		if (nTest == 0) {
			continue;
		}
		if(nTest < 4) return -1000;
		strtmp = CString(tmp1);
		szSkillEName = strtmp.Mid(1,strtmp.GetLength()-2);
		strtmp = CString(tmp2);
		szMapName=strtmp.Mid(1,strtmp.GetLength()-2);
		lpSkill = GetSkillClass(szMapName);
		if (lpSkill == NULL) szMapName.Empty();

		if (szSkillEName == "BaseCuff") szSkillEName = "BaseUnarmed";
		if (szSkillEName == "BaseFinger") szSkillEName = "BaseUnarmed";
		if (szSkillEName == "BaseHand") szSkillEName = "BaseUnarmed";
		if (szSkillEName == "BaseStrike") szSkillEName = "BaseUnarmed";
		if (szSkillEName == "BaseClaw") szSkillEName = "BaseUnarmed";
		if (szSkillEName == "BaseStick") szSkillEName = "BaseClub";
		if (szSkillEName == "BaseStaff") szSkillEName = "BaseClub";

		if( nLevel < 0 ) nLevel = 0;
		if( nScore < 0 ) nScore = 0;
		lpPlayerInfo->SetSkill(szSkillEName, nLevel, nScore, szMapName);
	}
	return 1;
}

int CCmdPlayerLogon::LoadPlayerEquip(CPlayerInfo * lpPlayerInfo)
{
	char szPath[256], szFile[256], szBuf[DSBUFSIZE];
	char *ps, *psBuf;
	CGoods *lpEquip, *lpMyEquip;
	POSITION pos,pos1;
	BOOL bFind=FALSE;
	CStringList strls;
	CString szEquip, szTemp;
	int nKind, n, nTest, nLen;
	int nWeight=0;
	int nStr = lpPlayerInfo->nStr;
	szHashName(lpPlayerInfo->szUserName, szPath);
	sprintf(szFile, "%s.equip", lpPlayerInfo->szEName);
	
	nTest = DSLoadData((char*)(LPCSTR)lpPlayerInfo->szUserName, szPath, szFile, szBuf);
	if (nTest <=0) return nTest;
	psBuf = szBuf;
	nTest = 0;
	nLen = strlen(szBuf);

	while (nTest < nLen)	{
		while ((nTest < nLen) && (szBuf[nTest] != '\n')) nTest++;
		szBuf[nTest] = 0;
		ps = strtok(psBuf, " \t");
		while(ps != NULL) {
			strls.AddTail(ps);
			ps = strtok(NULL, " \t");
		}
		psBuf = szBuf + nTest + 1;

		if (strls.GetCount()>2)
			szEquip = strls.GetAt(strls.FindIndex(0));

		if(szEquip != "rent")	{

		if (strls.GetCount()>2) {
			szEquip = strls.GetAt(strls.FindIndex(0));
			szTemp = strls.GetAt(strls.FindIndex(1));
			nKind = atoi((char*)(LPCSTR)szTemp);
			lpEquip = GetGoodsClass(szEquip, nKind);
			n = 0;
			if (lpEquip != NULL) {
				lpEquip->nRent = 0;
				n = lpEquip->LoadData(2, &strls);
				if ( n > 0) {
						pos1 = lpPlayerInfo->listequip.GetHeadPosition();
						nWeight = 0;
						while (pos1!=NULL)	{ 
							lpMyEquip = lpPlayerInfo->listequip.GetNext(pos1);
							if( lpMyEquip->nCount < 0 ) lpMyEquip->nCount = 1;
							nWeight += ( lpMyEquip->lpGoods->nWeight * lpMyEquip->nCount );
						}
						if( lpEquip->nCount < 0 ) lpEquip->nCount = 1;
						if( lpEquip->lpGoods->nWeight > 0 )	{
							if( lpEquip->nCount > (nStr*1000 - nWeight) / lpEquip->lpGoods->nWeight )	{
								lpEquip->nCount = (nStr*1000 - nWeight) / lpEquip->lpGoods->nWeight;
							}
						}
						if( nWeight >= 0 && lpEquip->nCount > 0 && 
							( nWeight + (lpEquip->lpGoods->nWeight*lpEquip->nCount)) <= nStr*1000)	{
							pos = lpPlayerInfo->listequip.GetHeadPosition();
							bFind = FALSE;
							while (pos!=NULL) {
								lpMyEquip = lpPlayerInfo->listequip.GetNext(pos);
								if (lpMyEquip->lpGoods->szEName == lpEquip->lpGoods->szEName) {
									bFind = TRUE;
									lpMyEquip->nCount += lpEquip->nCount;
									delete lpEquip;
									break;
								}
							}
							if (!bFind)
								lpPlayerInfo->listequip.AddTail(lpEquip);
						}
				} else {
					delete lpEquip;
				}
			}
		}
		}else	{
		   
		if (strls.GetCount()>3) {
			szEquip = strls.GetAt(strls.FindIndex(1));
			szTemp = strls.GetAt(strls.FindIndex(2));
			nKind = atoi((char*)(LPCSTR)szTemp);
			lpEquip = GetGoodsClass(szEquip, nKind);
			n = 0;
			if (lpEquip != NULL) {
				lpEquip->nRent = 1;
				n = lpEquip->LoadData(3, &strls);
				if ( n > 0) {
					if ((nKind == GK_food) || (nKind == GK_drug) || (nKind == GK_flag)) {
						pos = lpPlayerInfo->listrentequip.GetHeadPosition();
						while (pos!=NULL) {
							lpMyEquip = lpPlayerInfo->listrentequip.GetNext(pos);
							if (lpMyEquip->lpGoods->szEName == lpEquip->lpGoods->szEName) {
								bFind = TRUE;
								lpMyEquip->nCount += lpEquip->nCount;
								delete lpEquip;
								break;
							}
						}
						if (!bFind)	lpPlayerInfo->listrentequip.AddTail(lpEquip);
					} else {
						lpPlayerInfo->listrentequip.AddTail(lpEquip);
					}
				} else {
					delete lpEquip;
				}
			}
		}
	   }
		strls.RemoveAll();
	}

	return 1;
}


BOOL CCmdPlayerLogon::AppToMap(CPlayerInfo * lpPlayerInfo)
{
	CBaseMap *lpDataMap;
	int i,j;
	BOOL bFindMap = FALSE;
	EnterCriticalSection(&myglobs.csMaplist);
	j = maplist.GetCount();
	for(i=0;i<j;i++) 
	{
		lpDataMap = maplist.GetAt(maplist.FindIndex(i));
		if(lpDataMap->szEName == lpPlayerInfo->szRoom)
		{
			lpPlayerInfo->pMapPosite = maplist.FindIndex(i);
			lpDataMap->listplayer.AddTail(lpPlayerInfo);
			bFindMap = TRUE;
			break;
		}
	}
	LeaveCriticalSection(&myglobs.csMaplist);
	return bFindMap;
}
