// N_Disciple.cpp: implementation of the CN_Disciple class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "N_Disciple.h"
#include "..\..\..\XmudOS.h"
#include "..\..\..\hash.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CN_Disciple::CN_Disciple(char *szPath, char *szFile)
{
	FILE *fp;
	char szFileName[256], szBuf[DSBUFSIZE];
	int nTest;

	nLimitCount = 0;
	g_HasEvent = 0;
	strcpy(szFileName, szPath);
	strcat(szFileName, "\\");
	strcat(szFileName, szFile);
	fp = fopen(szFileName, "r");
	if(fp) {
		nTest = fread(szBuf, sizeof(char), DSBUFSIZE-1, fp);
		if (nTest > 0) {
			szBuf[nTest] = 0;
			Init(szBuf);
		} else {
			szCName = "ERROR";
			sprintf (szBuf, "ERROR NPC (%s) Data is empty", szFile);
			AddRecordMsg(szBuf);
		}
		fclose(fp);
	} else {
		szCName = "ERROR";
		sprintf (szBuf, "ERROR NPC (%s) Open file error", szFile);
		AddRecordMsg(szBuf);
	}
}

CN_Disciple::~CN_Disciple()
{

}
// Spock start
TRetInfo CN_Disciple::DoApprentice(CPlayerInfo *who)
{
	TRetInfo ri;
	int i;
	CSkill *lpSkill;

	ri = CNpc::DoApprentice(who);
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	for (i=0; i<nLimitCount; i++) {
		if (szLimit[i] == "正神") {
			if (who->nShen < nLimit[i]) {
				ri.szRet.Format("%s的德行似乎還不足，是否該多為武林除害",
					GetSpecialName(who,SName_zhun));
				return ri;
			}
		} else if (szLimit[i] == "負神") {
			if (who->nShen > nLimit[i]) {
				ri.szRet.Format("%s！竟敢來找我拜師，%s最討厭你們這些自居名門正派的傢伙",
					GetSpecialName(who,SName_mie), GetSpecialName(this,SName_da));
				return ri;
			}
		} else if (szLimit[i] == "臂力") {
			if (who->nStr < nLimit[i]) {
				ri.szRet.Format("%s的臂力似乎還太差，是否該多鍛練鍛練",
					GetSpecialName(who,SName_zhun));
				return ri;
			}
		} else if (szLimit[i] == "悟性") {
			if (who->nInt < nLimit[i]) {
				ri.szRet.Format("%s的悟性似乎太差，不適合學高深的武術",
					GetSpecialName(who,SName_zhun));
				return ri;
			}
		} else if (szLimit[i] == "根骨") {
			if (who->nCon < nLimit[i]) {
				ri.szRet.Format("%s的根骨不夠，不足以習練本門武術",
					GetSpecialName(who,SName_zhun));
				return ri;
			}
		} else if (szLimit[i] == "身法") {
			if (who->nDex < nLimit[i]) {
				ri.szRet.Format("%s的身法似乎還太差，是否該多磨練磨練",
					GetSpecialName(who,SName_zhun));
				return ri;
			}
		} else if (szLimit[i] == "內力") {
			if (who->nMax_force < nLimit[i]) {
				ri.szRet.Format("%s的內力似乎還不足，多修練些內力再來吧",
					GetSpecialName(who,SName_zhun));
				return ri;
			}
		} else if (szLimit[i] == "經驗") {
			if (who->nCombat_exp < nLimit[i]) {
				ri.szRet.Format("%s的經驗似乎還不足，是否該多磨練磨練",
					GetSpecialName(who,SName_zhun));
				return ri;
			}
		} else {
			lpSkill = GetSkillClass(szLimit[i]);
			if(lpSkill) {
				if (who->GetSkillLevel(szLimit[i]) < nLimit[i]) {
					ri.szRet.Format("依我看，%s的%s修為似乎還不夠",
						GetSpecialName(who,SName_zhun),lpSkill->szCName);
					return ri;
				}
			} else {

				if (nShen > 0) {
					ri.szRet.Format("%s今天心情不佳，不想收徒弟！",GetSpecialName(this,SName_qian));
				} else {
					ri.szRet.Format("%s今天心情不爽，給我滾！",GetSpecialName(this,SName_da));
				}
				return ri;
			}
		}
	}
	ri.bRet = TRUE;
	return ri;
}
// Spock end

TRetInfo CN_Disciple::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;
//	ri.bRet = FALSE;

/*	for(int i=0;i<5;i++)
	{
        if (szName == szdialog[i][0])
		{
	        ri.szRet = szdialog[i][1];
			ri.bRet = TRUE;
		    return ri;
		}	
	}*/
	ri.bRet = TRUE;
	return ri;
}

void CN_Disciple::Init(char *szBuf)
{
	char *ps, stemp1[128],stemp2[128],stemp3[256];
	int ntemp1,ntemp2;
	CString szStr;
	CEquip *lpEquip;
	TGivingGoods *GivingGoods;          //定義在npc.h
	TGivingCondition *GivingCondition;  //定義在npc.h

	ps = strtok(szBuf, "\n");
	while(ps) 
	{
		sscanf(ps,"%s",stemp1);
        szStr = stemp1;
		if(szStr == "中文名字")
		{   
            sscanf(ps,"%s %s",stemp1,stemp2);
			szCName = stemp2;
		}
		if(szStr == "英文名字")
		{   
            sscanf(ps,"%s %s",stemp1,stemp2);
			szEName = stemp2;
		}
		if(szStr == "門派")
		{   
            sscanf(ps,"%s %s",stemp1,stemp2);
			szFamily = stemp2;
		}
		if(szStr == "師父")
		{   
            sscanf(ps,"%s %s",stemp1,stemp2);
			szTeacher = stemp2;
		}
        if(szStr == "外觀描述")
		{   
            sscanf(ps,"%s %s",stemp1,stemp2);
			szLong = stemp2;
		}
		if(szStr == "性別")
		{   
            sscanf(ps,"%s %s",stemp1,stemp2);
			szSex = stemp2;
		}
        if(szStr == "X模型")
		{   
            sscanf(ps,"%s %s",stemp1,stemp2);
			szXFileName = stemp2;
		}
        if(szStr == "所在地")
		{   
            sscanf(ps,"%s %s",stemp1,stemp2);
			szRoom = stemp2;
		}
		if(szStr == "年齡")
		{   
            sscanf(ps,"%s %d",stemp1,&nAge);
		}
		if(szStr == "金錢")
            sscanf(ps,"%s %d",stemp1,&nMoney);
        if(szStr == "屬性") {
            sscanf(ps,"%s %d",stemp1,&ntemp1);
			nAttitude |=ntemp1;
		}
	
		if(szStr == "神值")   
            sscanf(ps,"%s %d",stemp1,&nShen);
	
		if(szStr == "臂力")  {
            sscanf(ps,"%s %d",stemp1,&nStr);
		}
			
		if(szStr == "悟性")   {
            sscanf(ps,"%s %d",stemp1,&nInt);
		}

		if(szStr == "根骨") {
            sscanf(ps,"%s %d",stemp1,&nCon);
		}
		
		if(szStr == "身法")  {
            sscanf(ps,"%s %d",stemp1,&nDex);
		}
		
		if(szStr == "輩份")
			sscanf(ps,"%s %d",stemp1,&nGeneration);
			
		if(szStr == "加內力")   
            sscanf(ps,"%s %d",stemp1,&nAdd_force);

		if(szStr == "加精力")   
            sscanf(ps,"%s %d",stemp1,&nAdd_Jingli);
		
		if(szStr == "經驗值")  
            sscanf(ps,"%s %d",stemp1,&nCombat_exp);
			                 				  
        if(szStr == "詢問")
		{   
            sscanf(ps,"%s %s %s",stemp1,stemp2,stemp3);
			AddAsk(stemp2,NPCASK_visible,stemp3);
		}
		if(szStr == "技能")
		{   
            sscanf(ps,"%s %s %d %d %s",stemp1,stemp2,&ntemp1,&ntemp2,stemp3);
			if(strcmp(stemp3,"空")) {
				SetSkill(stemp2,ntemp1,ntemp2,stemp3);
			} else {
				SetSkill(stemp2,ntemp1);
			}
		}
		// Spock start
		if(szStr == "武器")	{
			sscanf(ps,"%s %s",stemp1,stemp2);
			lpWeapon = GetWeaponClass(stemp2);
			if(lpWeapon) {
				lpWeapon->bWield = TRUE;
				listequip.AddTail(lpWeapon);
			}
		}
		if(szStr == "裝備")	{
			sscanf(ps,"%s %s",stemp1,stemp2);
			lpEquip = GetEquipClass(stemp2);
			if(lpEquip) {
				lpEquip->nWearWhere = lpEquip->lpEquip->nWhereWear;
				listequip.AddTail(lpEquip);
			} 
		}
		if(szStr == "拜師條件")	{
			sscanf(ps,"%s %s %d",stemp1,stemp2,&ntemp1);
			if(nLimitCount < MAXLIMIT) {
				szLimit[nLimitCount] = CString(stemp2);
				nLimit[nLimitCount] = ntemp1;
				nLimitCount++;
			}
		}
		if(szStr =="[給物]")	{
			GivingGoods = new TGivingGoods;
			do{
				ps = strtok(NULL, "\n");
                sscanf(ps,"%s",stemp1);
                szStr = stemp1;
				if(szStr =="物品")
				{
                    sscanf(ps,"%s %s",stemp1,stemp2);
				    GivingGoods->szGoodsEName = stemp2;
				}
				if(szStr =="給物條件")
				{
					sscanf(ps,"%s %s %d",stemp1,stemp2,&ntemp1);
					GivingCondition = new TGivingCondition;
					GivingCondition->szSkillEName = stemp2;
					GivingCondition->nLevel = ntemp1;
                    GivingGoods->listCondition.AddTail(GivingCondition);
				}
				if(szStr =="旗標")
				{
					sscanf(ps,"%s %d",stemp1,&ntemp1);
					GivingGoods->nFlag = ntemp1;
				}
			}while(szStr!="[給物結束]");
			listGiving.AddTail(GivingGoods);
		}
		ps = strtok(NULL, "\n");
		// Spock end
	}
    
}