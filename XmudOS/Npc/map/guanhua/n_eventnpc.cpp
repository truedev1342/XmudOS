// N_EventNpc.cpp: implementation of the CN_EventNpc class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "..\..\..\goods\Goods\Goods.h"
#include "..\..\Npc.h"
#include "..\..\..\Common.h"
#include "N_EventNpc.h"
#include "..\..\..\config.h"
#include "..\..\..\commandcheck.h"

extern char g_tszPathName[256];
extern rmfullglobals myglobs;

extern void GetXFileName(CPlayerInfo * lpPlayerInfo);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CN_EventNpc::CN_EventNpc(char *szPath, char *szNpcFile):CN_Disciple(szPath, szNpcFile)
{
	FILE *pFile = NULL;
	char szFileName[512], szBuf1[512], szBuf2[512];

	int nAskType = 0;
	g_HasEvent = 0;
	g_pNpcEvent = NULL;
	list<CEventAsk>::iterator iterEventAsk;
	char szKeyWord[128] = "NULL";

	nLimitCount = 0;
	strcpy(szFileName, szPath);
	strcat(szFileName, "\\");
	strcat(szFileName, szNpcFile);

    pFile = fopen(szFileName,"r");
	if(pFile != NULL)
	{
        while(fscanf(pFile,"%s",szBuf1)!=EOF)
		{
            if(strcmp(szBuf1,"事件") == 0)
			{
				fscanf(pFile,"%s",szBuf1);

				if(strcmp(szBuf1,"無") != 0)
				{
					strcpy(szBuf2, g_tszPathName);
					strcat(szBuf2, "\\Event\\");
					strcat(szBuf2, szBuf1);
					LoadNpcEventFile(szBuf2);

					for(iterEventAsk = (g_pNpcEvent->EventAskList).begin(); iterEventAsk != (g_pNpcEvent->EventAskList).end(); iterEventAsk++)
					{

						switch(iterEventAsk->AskType)
						{
							case EV_KEYWORD_Visible		:
									nAskType = NPCASK_visible;
									break;
							case EV_KEYWORD_Invisible	:
									nAskType = 0;
									break;
							default						:
									nAskType = 0;
									break;
						}

						strcpy(szKeyWord,(iterEventAsk->KeyWord).c_str());
						AddAsk(szKeyWord, nAskType, "");
					}
				}
			}else if(!strcmp(szBuf1,"買賣"))	{
				FILE *sfp=NULL;
				int kp=0;
				fscanf(pFile,"%s",szBuf1);

				if(strcmp(szBuf1,"無") != 0)	{
					strcpy(szBuf2, g_tszPathName);
					strcat(szBuf2, "\\Event\\");
					strcat(szBuf2, szBuf1);
					sfp = fopen(szBuf2,"r");
					nAsk = 0;	
					 while(fscanf(sfp,"%s",szBuf1)!=EOF)	{
						 //AssSale(szBuf1, 0,"");
					 }
				}

			}
		}	// while
		fclose(pFile);

	}else{
	}
}

CN_EventNpc::~CN_EventNpc()
{

}

void CN_EventNpc::LoadNpcEventFile(char *szNpcEventFile)
{

    // Load NPC Event File
    FILE *pFile;
    CString szStr;

    //char szBuf1[64], szBuf2[64], szBuf3[64], szBuf4[64];
	char szBuf1[512], szBuf2[512], szBuf3[512], szBuf4[512];

    int nBuf1 = 0, nBuf2 = 0, nBuf3 = 0, nBuf4 = 0;

    CEventAsk*   pEventAsk = NULL;
    CEventLimit* pEventLimit = NULL;
    CEventRun*   pEventRun = NULL;

// initialize g_pNpcEvent start

    pFile = fopen(szNpcEventFile,"r");
	if(pFile != NULL)
	{
		g_pNpcEvent = new CNpcEvent;
		g_HasEvent = 1;

        (g_pNpcEvent->EventAskList).clear();

        while(fscanf(pFile,"%s",szBuf1)!=EOF)     //while [AskItem]
		{
            szStr = szBuf1;
            if(szStr == "[AskEnd]")
            {
                continue;
            }
            else if(szStr == "[AskItem]")
            {
                if(fscanf(pFile, "%s %s %s", szBuf1, szBuf2, szBuf3) == 3)
                {
                    nBuf1 = atoi(szBuf2);
                    nBuf2 = atoi(szBuf3);
                    pEventAsk = new CEventAsk(szBuf1, nBuf1, nBuf2);
                    while(fscanf(pFile,"%s",szBuf1)!=EOF)     //while [Default]
                    {
                        szStr = szBuf1;
                        if(szStr == "[AskEnd]")
                        {
                            break;
                        }
                        else if(szStr == "[DefaultEnd]")
                        {
                            break;
                        }
                        else if(szStr == "[Default]")
                        {
// Read Default EventRun data

                            fscanf(pFile,"%s",szBuf1);
                            szStr = szBuf1;

                            if(szStr == "[No]")
                            {
                                fscanf(pFile,"%s",szBuf1);

                                if(strcmp(szBuf1, "NULLMSG") == 0)
                                {
                                    strcpy(szBuf1, "");
                                }

                                pEventAsk->MsgDefaultWhenNo = szBuf1;
                                while(fscanf(pFile,"%s",szBuf1)!=EOF)     //while [Event] when [No]
                                {
                                    szStr = szBuf1;
                                    if(szStr == "[NoEnd]")
                                    {
                                        break;
                                    }
                                    if(szStr == "[EventRun]")
                                    {
                                        if(fscanf(pFile, "%s %s %s %s", szBuf1, szBuf2, szBuf3, szBuf4) == 4)
                                        {
                                            pEventRun = new CEventRun;
                                            nBuf1 = atoi(szBuf1);
                                            pEventRun->EventRunType = nBuf1;
                                            pEventRun->EventRunItemName = szBuf2;
                                             nBuf3 = atoi(szBuf3);
                                            pEventRun->EventRunValue = nBuf3;
    		                                nBuf4 = atoi(szBuf4);
              				                pEventRun->EventRunGoodKind = nBuf4;
                                        }
                                        (pEventAsk->DefaultEventRunListWhenNo).push_back(*pEventRun);
                                        delete pEventRun;
                                    }
                                }    //while [Default Event] when [No]
                            }    //if [Default No]
                            fscanf(pFile,"%s",szBuf1);
                            szStr = szBuf1;

                            if(szStr == "[Yes]")
                            {
                                fscanf(pFile,"%s",szBuf1);
                                if(strcmp(szBuf1, "NULLMSG") == 0)
                                {
                                    strcpy(szBuf1, "");
                                }
                                pEventAsk->MsgDefaultWhenYes = szBuf1;
                                while(fscanf(pFile,"%s",szBuf1)!=EOF)     //while [Event] when [Yes]
                                {
                                    szStr = szBuf1;
                                    if(szStr == "[YesEnd]")
                                    {
                                        break;
                                    }
                                    else if(szStr == "[EventRun]")
                                    {
                                        if(fscanf(pFile, "%s %s %s %s", szBuf1, szBuf2, szBuf3, szBuf4) == 4)
                                        {
                                            pEventRun = new CEventRun;
                                            nBuf1 = atoi(szBuf1);
                                            pEventRun->EventRunType = nBuf1;

                                            pEventRun->EventRunItemName = szBuf2;
                                            nBuf3 = atoi(szBuf3);   
                                            pEventRun->EventRunValue = nBuf3;

			                                nBuf4 = atoi(szBuf4);
              				                pEventRun->EventRunGoodKind = nBuf4;
                                        }
                                        (pEventAsk->DefaultEventRunListWhenYes).push_back(*pEventRun);
                                        delete pEventRun;
                                    }
                                }    //while [Default Event] when [Yes]
                            }    // if [DefaultYes]
                        }
                    }    //while [Default]

// Read EventRun after checking limits
                    while(fscanf(pFile,"%s",szBuf1)!=EOF)     //while [Limit]
                    {
                        szStr = szBuf1;
                        if(szStr == "[AskEnd]")
                        {
                            break;
                        }
                        else if(szStr == "[LimitEnd]")
                        {
                            continue;
                        }
                        else if(szStr == "[Limit]")
                        {
                            if(fscanf(pFile, "%s %s %s %s", szBuf1, szBuf2, szBuf3, szBuf4) == 4)
                            {
                                pEventLimit = new CEventLimit;

                                nBuf1 = atoi(szBuf1);
                                pEventLimit->LimitType = nBuf1;

                                pEventLimit->LimitItemName = szBuf2;

                                nBuf3 = atoi(szBuf3);
                                pEventLimit->LimitValue = nBuf3;

                                nBuf4 = atoi(szBuf4);
                                pEventLimit->LimitGoodKind = nBuf4;

                                fscanf(pFile,"%s",szBuf1);
                                szStr = szBuf1;

                                if(szStr == "[No]")
                                {
                                    fscanf(pFile,"%s",szBuf1);

                                    if(strcmp(szBuf1, "NULLMSG") == 0)
                                    {
                                        strcpy(szBuf1, "");
                                    }

                                    pEventLimit->MsgWhenNo = szBuf1;
                                    while(fscanf(pFile,"%s",szBuf1)!=EOF)     //while [Event] when [No]
                                    {
                                        szStr = szBuf1;
                                        if(szStr == "[NoEnd]")
                                        {
                                            break;
                                        }
                                        if(szStr == "[EventRun]")
                                        {
                                            if(fscanf(pFile, "%s %s %s %s", szBuf1, szBuf2, szBuf3, szBuf4) == 4)
                                            {
                                                pEventRun = new CEventRun;

                                                nBuf1 = atoi(szBuf1);
                                                pEventRun->EventRunType = nBuf1;

                                                pEventRun->EventRunItemName = szBuf2;

                                                nBuf3 = atoi(szBuf3);
                                                pEventRun->EventRunValue = nBuf3;

				                                nBuf4 = atoi(szBuf4);
                				                pEventRun->EventRunGoodKind = nBuf4;

                                            }
                                            (pEventLimit->EventRunListWhenNo).push_back(*pEventRun);
                                            delete pEventRun;
                                        }
                                    }    //while [Event] when [No]
                                }    //if [No]

                                fscanf(pFile,"%s",szBuf1);
                                szStr = szBuf1;

                                if(szStr == "[Yes]")
                                {
                                    fscanf(pFile,"%s",szBuf1);

                                    if(strcmp(szBuf1, "NULLMSG") == 0)
                                    {
                                        strcpy(szBuf1, "");
                                    }

                                    pEventLimit->MsgWhenYes = szBuf1;
                                    while(fscanf(pFile,"%s",szBuf1)!=EOF)     //while [Event] when [Yes]
                                    {
                                        szStr = szBuf1;
                                        if(szStr == "[YesEnd]")
                                        {
                                            break;
                                        }
                                        else if(szStr == "[EventRun]")
                                        {
                                            if(fscanf(pFile, "%s %s %s %s", szBuf1, szBuf2, szBuf3, szBuf4) == 4)
                                            {
                                                pEventRun = new CEventRun;

                                                nBuf1 = atoi(szBuf1);
                                                pEventRun->EventRunType = nBuf1;

                                                pEventRun->EventRunItemName = szBuf2;

                                                nBuf3 = atoi(szBuf3);
                                                pEventRun->EventRunValue = nBuf3;

				                                nBuf4 = atoi(szBuf4);
                				                pEventRun->EventRunGoodKind = nBuf4;
                                            }
                                            (pEventLimit->EventRunListWhenYes).push_back(*pEventRun);
                                            delete pEventRun;
                                        }
                                    }    //while [Event] when [Yes]
                                }    // if [Yes]
                            }
                            (pEventAsk->LimitList).push_back(*pEventLimit);
                            delete pEventLimit;
                        }
                    }    //while [Limit]
                }
                (g_pNpcEvent->EventAskList).push_back(*pEventAsk);
                delete pEventAsk;
            }
        }    //while [AskItem]

        fclose(pFile);
    }
}

TRetInfo CN_EventNpc::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	list<CEventAsk>::iterator iterEventAsk;

	ri = CNpc::DoAsk(who, szName,"$NONE$");
	if (!ri.bRet) return ri;

    if(g_HasEvent == 1){
		for(iterEventAsk = (g_pNpcEvent->EventAskList).begin(); iterEventAsk != (g_pNpcEvent->EventAskList).end(); iterEventAsk++)
		{
			if ( !strcmp(szName, (iterEventAsk->KeyWord).c_str() ) ){
				ri = DoEventLimit(who, iterEventAsk);
				return ri;
			}
		}
	}
	ri.bRet = TRUE;
	return ri;
}

TRetInfo CN_EventNpc::DoEventLimit(CPlayerInfo *who, list<CEventAsk>::iterator iterEventAsk)
{
	int IsYes = -1;
	TRetInfo ri;
    list<CEventLimit>::iterator iterLimit, iterEndLimit;
	char szLimitItemName[64] = "NULL";
	CGoods *pGood = NULL;
	POSITION pos;

	switch(iterEventAsk->LimitChoose)
	{
		case EV_LIMITCHOOSE_All		:
				IsYes = 1;
				for(iterLimit = (iterEventAsk->LimitList).begin(); iterLimit != (iterEventAsk->LimitList).end(); iterLimit++)
        		{
					strcpy(szLimitItemName, (iterLimit->LimitItemName).c_str());

					switch(iterLimit->LimitType){
                        case EV_LIMIT_NotDefine:
								ri.szRet = "iterEventAsk->LimitType=LIMIT_NotDefine";
                                break;
                        case EV_LIMIT_GoodHasGot:
								if(who->GetGoods(szLimitItemName) == NULL)
								{
									IsYes = 0;
								}
                                break;
                        case EV_LIMIT_GoodHasNotGot:
								if(who->GetGoods(szLimitItemName) != NULL)
								{
									IsYes = 0;
								}
            	                break;
                        case EV_LIMIT_GoodCountMore:
								if(who->GetGoodCount(szLimitItemName) <= iterLimit->LimitValue){
									IsYes = 0;
								}
			                    break;
                        case EV_LIMIT_GoodCountEqual:
								if(who->GetGoodCount(szLimitItemName) != iterLimit->LimitValue)
								{
									IsYes = 0;
								}
                                break;
                        case EV_LIMIT_GoodCountLess:
								if(who->GetGoodCount(szLimitItemName) >= iterLimit->LimitValue)
								{
									IsYes = 0;
								}
                                break;
                        case EV_LIMIT_MoneyMore:
								if(who->nMoney <= iterLimit->LimitValue){
									IsYes = 0;
								}
                                break;
                        case EV_LIMIT_MoneyLess:
								if(who->nMoney >= iterLimit->LimitValue){
									IsYes = 0;
								}
                                break;
                        case EV_LIMIT_StatusPointMore:									
								if( strcmp("年齡", szLimitItemName) == 0){
									if(who->nAge <= iterLimit->LimitValue){
										IsYes = 0;
									}
								}else if( strcmp("神值", szLimitItemName) == 0){
									if(who->nShen <= iterLimit->LimitValue){
										IsYes = 0;
									}
								}
								else if( strcmp("臂力", szLimitItemName) == 0){
									if(who->nStr <= iterLimit->LimitValue){
										IsYes = 0;
									}
								}else if( strcmp("悟性", szLimitItemName) == 0){								
									if(who->nInt <= iterLimit->LimitValue){
										IsYes = 0;
									}
								}else if( strcmp("根骨", szLimitItemName) == 0){
									if(who->nCon <= iterLimit->LimitValue){
										IsYes = 0;
									}
								}else if( strcmp("身法", szLimitItemName) == 0){
									if(who->nDex <= iterLimit->LimitValue){
										IsYes = 0;
									}
								}else if( strcmp("戰鬥經驗", szLimitItemName) == 0){
									if(who->nCombat_exp <= iterLimit->LimitValue){
										IsYes = 0;
									}
								}else if( strcmp("潛能", szLimitItemName) == 0){
									if(who->nQianNeng <= iterLimit->LimitValue){
										IsYes = 0;
									}
								}else	{
									AddRecordMsg("LIMIT_StatusPointMore error");
									ri.szRet = "LIMIT_StatusPointMore Error";
									return ri;
								}
                                break;
						case EV_LIMIT_StatusPointLess :
								if( strcmp("年齡", szLimitItemName) == 0)
								{
									if(who->nAge >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("神值", szLimitItemName) == 0)
								{
									if(who->nShen >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("臂力", szLimitItemName) == 0)
								{
									if(who->nStr >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("悟性", szLimitItemName) == 0)
								{								
									if(who->nInt >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("根骨", szLimitItemName) == 0)
								{
									if(who->nCon >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("身法", szLimitItemName) == 0)
								{
									if(who->nDex >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("戰鬥經驗", szLimitItemName) == 0)
								{
									if(who->nCombat_exp >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("潛能", szLimitItemName) == 0)
								{
									if(who->nQianNeng >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else
								{
									AddRecordMsg("LIMIT_StatusPointLess error");
									ri.szRet = "LIMIT_StatusPointLess Error";
									return ri;
								}
                                break;
                        case EV_LIMIT_StatusPointEqual:
								if( strcmp("年齡", szLimitItemName) == 0)
								{
									if(who->nAge != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("神值", szLimitItemName) == 0)
								{
									if(who->nShen != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("臂力", szLimitItemName) == 0)
								{
									if(who->nStr != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("悟性", szLimitItemName) == 0)
								{								
									if(who->nInt != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("根骨", szLimitItemName) == 0)
								{
									if(who->nCon != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("身法", szLimitItemName) == 0)
								{
									if(who->nDex != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("戰鬥經驗", szLimitItemName) == 0)
								{
									if(who->nCombat_exp != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("潛能", szLimitItemName) == 0)
								{
									if(who->nQianNeng != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else
								{
									AddRecordMsg("LIMIT_StatusPointEqual error");
									ri.szRet = "LIMIT_StatusPointEqual Error";
									return ri;
								}
                                break;
						case EV_LIMIT_SexEqual:
								if(strcmp(who->szSex,szLimitItemName) != 0)
								{
									IsYes = 0;
								}
								break;
						case EV_LIMIT_FamilyEqual:
								if(strcmp(who->szFamily,szLimitItemName) != 0)
								{
									IsYes = 0;
								}
								break;
						case EV_LIMIT_FamilyNotEqual:
								if(strcmp(who->szFamily,szLimitItemName) == 0)
								{
									IsYes = 0;
								}
								break;
						case EV_LIMIT_BetrayFamily :
								IsYes = 0;
								pos = who->listBetray.GetHeadPosition();
								while (pos)
								{
									if (szLimitItemName == who->listBetray.GetNext(pos))
									{
										IsYes = 1;
									}
								}
								break;
						case EV_LIMIT_NotBetrayFamily :
								pos = who->listBetray.GetHeadPosition();
								while (pos)
								{
									if (szLimitItemName == who->listBetray.GetNext(pos))
									{
										IsYes = 0;
									}
								}
								break;
						default:    AddRecordMsg("LimitType = default");
								break;
        			}  // switch loop
				}	// for loop

				if(IsYes == 1)
				{
					ri = DoDefaultEventRunWhenYes(who, iterEventAsk);
				}
				else
				{
					ri = DoDefaultEventRunWhenNo(who, iterEventAsk);
				}
				break;

		case EV_LIMITCHOOSE_One		:
				for(iterLimit = (iterEventAsk->LimitList).begin(); iterLimit != (iterEventAsk->LimitList).end(); iterLimit++)
        		{
            		IsYes = 1;
					strcpy(szLimitItemName, (iterLimit->LimitItemName).c_str());
					switch(iterLimit->LimitType)
            		{
                        case EV_LIMIT_NotDefine:
								ri.szRet = "iterEventAsk->LimitType=LIMIT_NotDefine";
                                break;
                        case EV_LIMIT_GoodHasGot:
								if(who->GetGoods(szLimitItemName) == NULL)
								{
									IsYes = 0;
								}
                                break;
                        case EV_LIMIT_GoodHasNotGot:
								if(who->GetGoods(szLimitItemName) != NULL)
								{
									IsYes = 0;
								}
            	                break;
                        case EV_LIMIT_GoodCountMore:
								if(who->GetGoodCount(szLimitItemName) <= iterLimit->LimitValue)
								{
									IsYes = 0;
								}
			                    break;
                        case EV_LIMIT_GoodCountEqual:
								if(who->GetGoodCount(szLimitItemName) != iterLimit->LimitValue)
								{
									IsYes = 0;
								}
                       			break;
                        case EV_LIMIT_GoodCountLess:
								if(who->GetGoodCount(szLimitItemName) >= iterLimit->LimitValue)
								{
									IsYes = 0;
								}
                       			break;
                        case EV_LIMIT_MoneyMore:
								if(who->nMoney <= iterLimit->LimitValue)
								{
									IsYes = 0;
								}
                                break;
                        case EV_LIMIT_MoneyLess:;
								if(who->nMoney >= iterLimit->LimitValue)
								{
									IsYes = 0;
								}
                                break;
                        case EV_LIMIT_StatusPointMore:										
								if( strcmp("年齡", szLimitItemName) == 0)
								{
									if(who->nAge <= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("神值", szLimitItemName) == 0)
								{
									if(who->nShen <= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("臂力", szLimitItemName) == 0)
								{
									if(who->nStr <= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("悟性", szLimitItemName) == 0)
								{								
									if(who->nInt <= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("根骨", szLimitItemName) == 0)
								{
									if(who->nCon <= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("身法", szLimitItemName) == 0)
								{
									if(who->nDex <= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("戰鬥經驗", szLimitItemName) == 0)
								{
									if(who->nCombat_exp <= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("潛能", szLimitItemName) == 0)
								{
									if(who->nQianNeng <= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else
								{
									AddRecordMsg("status set error");
									ri.szRet = "WhenNo:StatusSetError";
									return ri;
								}
                          		break;
						case EV_LIMIT_StatusPointLess :
								if( strcmp("年齡", szLimitItemName) == 0)
								{
									if(who->nAge >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("神值", szLimitItemName) == 0)
								{
									if(who->nShen >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("臂力", szLimitItemName) == 0)
								{
									if(who->nStr >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("悟性", szLimitItemName) == 0)
								{								
									if(who->nInt >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("根骨", szLimitItemName) == 0)
								{
									if(who->nCon >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("身法", szLimitItemName) == 0)
								{
									if(who->nDex >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("戰鬥經驗", szLimitItemName) == 0)
								{
									if(who->nCombat_exp >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("潛能", szLimitItemName) == 0)
								{
									if(who->nQianNeng >= iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}else{
									AddRecordMsg("status set error");
									ri.szRet = "WhenNo:StatusSetError";
									return ri;
								}
                                break;

						case EV_LIMIT_StatusPointEqual:										
								if( strcmp("年齡", szLimitItemName) == 0){
									if(who->nAge != iterLimit->LimitValue){
										IsYes = 0;
									}
								}
								else if( strcmp("神值", szLimitItemName) == 0)
								{
									if(who->nShen != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("臂力", szLimitItemName) == 0)
								{
									if(who->nStr != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("悟性", szLimitItemName) == 0)
								{								
									if(who->nInt != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("根骨", szLimitItemName) == 0)
								{
									if(who->nCon != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("身法", szLimitItemName) == 0)
								{
									if(who->nDex != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("戰鬥經驗", szLimitItemName) == 0)
								{
									if(who->nCombat_exp != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else if( strcmp("潛能", szLimitItemName) == 0)
								{
									if(who->nQianNeng != iterLimit->LimitValue)
									{
										IsYes = 0;
									}
								}
								else
								{
									AddRecordMsg("LIMIT_StatusPointEqual error");
									ri.szRet = "LIMIT_StatusPointEqual Error";
									return ri;
								}
                                break;
						case EV_LIMIT_SexEqual:
								if(strcmp(who->szSex,szLimitItemName) != 0)
								{
									IsYes = 0;
								}
								break;
						case EV_LIMIT_FamilyEqual:
								if(strcmp(who->szFamily,szLimitItemName) != 0)
								{
									IsYes = 0;
								}
								break;
						case EV_LIMIT_FamilyNotEqual:
								if(strcmp(who->szFamily,szLimitItemName) == 0)
								{
									IsYes = 0;
								}
								break;
						case EV_LIMIT_BetrayFamily :
								IsYes = 0;
								pos = who->listBetray.GetHeadPosition();
								while (pos)
								{
									if (szLimitItemName == who->listBetray.GetNext(pos))
									{
										IsYes = 1;
									}
								}
								break;
						case EV_LIMIT_NotBetrayFamily :
								pos = who->listBetray.GetHeadPosition();
								while (pos)
								{
									if (szLimitItemName == who->listBetray.GetNext(pos))
									{
										IsYes = 0;
									}
								}
								break;
						default:	AddRecordMsg("LimitType = default");
								break;
					}  // switch loop

					if(IsYes == 0){
						ri = DoEventRunWhenNo(who, iterLimit);
						return ri;
					}
				}
				if(IsYes == 1){
					ri = DoDefaultEventRunWhenYes(who, iterEventAsk);
				}
				break;
		default:
				ri.szRet = "iterEventAsk->LimitChoose=default";
				break;
	}
	return ri;
}

CGoods* CN_EventNpc::GetNewEventGood(CString szItemName, int nKind, int nCount)
{
	CGoods *pGood = NULL;
	switch(nKind)	{
		case EV_GOODKIND_NotDefine	:
				pGood = GetNormalClass(szItemName);	
				break;
		case EV_GOODKIND_IsNotGood	:
				pGood = GetWeaponClass(szItemName);
		    	break;
		case EV_GOODKIND_Food		:
				pGood = GetFoodClass(szItemName);
				if(pGood != NULL){
					pGood->nCount = nCount;
				}
				break;
		case EV_GOODKIND_Equip		:
				pGood = GetEquipClass(szItemName);
		    	break;
		case EV_GOODKIND_Weapon		:
				pGood = GetWeaponClass(szItemName);
		    	break;
		case EV_GOODKIND_Book		:
				pGood = GetBookClass(szItemName);
		    	break;	
		case EV_GOODKIND_Drug		:
				pGood = GetDrugClass(szItemName);
				if(pGood != NULL)
				{
					pGood->nCount = nCount;
				}
		    	break;
		case EV_GOODKIND_Normal:
				pGood = GetNormalClass(szItemName);	
				break;
		case EV_GOODKIND_Flag		:	
				pGood = GetFlagClass(szItemName);
				if(pGood != NULL){
					pGood->nCount = nCount;
				}
				break;
		default						:
				pGood = NULL;
				break;
	}

	if(pGood == NULL){
		return pGood;
	}
	return pGood;
}


TRetInfo CN_EventNpc::DoEventRun(CPlayerInfo *who, list<CEventRun>::iterator iterEventRun, int &nStatusChange)
{
	int i = 0, DoNothing = 1;;
	TRetInfo ri;
	char szEventRunItemName[64] = "NULL", szChangeItemUnit[64] = "NULL", szTemp[128] = "NULL";
	CString szStr;
	CGoods *pGood = NULL;
	int nOrgCount=0;
	char szkill[4][128] = {"BaseUnarmed","BaseDodge","BaseForce","BaseParry"};
	char szTest[512] = "";
	strcpy(szEventRunItemName, (iterEventRun->EventRunItemName).c_str());
        switch(iterEventRun->EventRunType)	{
            case EV_TYPE_NotDefine :
					ri.szRet = "WhenYes:TYPE_NotDefine";
                 	break;
            case EV_TYPE_ShowMessage :
					ri.szRet = "TYPE_ShowMessage";
                 	break;
			case EV_TYPE_GoodCountIncrease :
					if((iterEventRun->EventRunGoodKind == EV_GOODKIND_Food) || (iterEventRun->EventRunGoodKind == EV_GOODKIND_Drug) || (iterEventRun->EventRunGoodKind == EV_GOODKIND_Flag))
					{

						if((pGood = GetNewEventGood(szEventRunItemName, iterEventRun->EventRunGoodKind, iterEventRun->EventRunValue)) == NULL )
						{
							ri.szRet = "ERROR:WhenYes:TYPE_GoodCountIncrease";
							return ri;
						}

						strcpy(szChangeItemUnit, pGood->lpGoods->szUnit);

						if((ri.szRet = who->AddGoods(pGood)) != "OK")
						{
							delete pGood;
							return ri;
						}
						else
						{
							if(iterEventRun->EventRunGoodKind != EV_GOODKIND_Flag)
							{
								// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
								ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,szEventRunItemName,"空",iterEventRun->EventRunValue,szChangeItemUnit,0);
								who->SendMsg(ri.szRet);
							}
						}
					}
					else
					{
						// Increase good unless good and drug
						DoNothing = 1;
						for(i = 0; i < iterEventRun->EventRunValue; i++)
						{
							if((pGood = GetNewEventGood(szEventRunItemName, iterEventRun->EventRunGoodKind, 1)) == NULL )
							{
								ri.szRet = "ERROR:WhenYes:TYPE_GoodCountIncrease";
								return ri;
							}
							else if((ri.szRet = who->AddGoods(pGood)) != "OK")
							{
								delete pGood;
								return ri;
							}
							else
							{
								DoNothing = 0;
								szStr = pGood->lpGoods->szUnit;
							}
						}
						// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
						if(DoNothing == 0){
							ri.szRet.Format("%s %s %s %d %s %d", SZADDGOODS,szEventRunItemName, "空", iterEventRun->EventRunValue, szStr, 0);
							who->SendMsg(ri.szRet);
						}
					}
                    break;
			case EV_TYPE_GoodCountDecrease :
					if((pGood = who->GetGoods(szEventRunItemName)) != NULL ){
						strcpy(szChangeItemUnit,pGood->lpGoods->szUnit);
						if( ((who->GetGoodCount(szEventRunItemName)) < iterEventRun->EventRunValue) && (iterEventRun->EventRunGoodKind != EV_GOODKIND_Flag))
						{
							//  the good counts are not enough
							strcpy(szTemp, "你現在身上的");
							strcat(szTemp, szEventRunItemName);
							strcat(szTemp, "不夠哦!");
							ri.szRet = szTemp;
							return ri;
						}else if( ((who->GetGoodIsNotArmedCount(szEventRunItemName)) < iterEventRun->EventRunValue) && (iterEventRun->EventRunGoodKind != EV_GOODKIND_Flag))
						{
							// the good counts are equal to the change value but one of the goood is equiped
							strcpy(szTemp, "先卸下你現在身上裝備的");
							strcat(szTemp, szEventRunItemName);
							strcat(szTemp, "吧");
							ri.szRet = szTemp;
							return ri;
						}
						else
						{
							// OK: has enough good to sub
							for(i = 0; i < iterEventRun->EventRunValue; i++)
							{
								//pGood = who->GetGoods(szEventRunItemName);
								ri.szRet = who->SubGoodWhichIsNotArmed(szEventRunItemName);
								if(ri.szRet == "OK")
								{
									if(iterEventRun->EventRunGoodKind != EV_GOODKIND_Flag)
									{
										ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,szEventRunItemName,"空",1,szChangeItemUnit,0);
										who->SendMsg(ri.szRet);
									}
								}
								else
								{
									ri.szRet = "ERROR:WhenYes:TYPE_GoodCountDecrease";
									return ri;
								}
							}
						}
					}
					else
					{
						// has no the same kind of good
						strcpy(szTemp, "你身上並沒有帶著");
						strcat(szTemp, szEventRunItemName);
						strcat(szTemp, "啊!");
						ri.szRet = szTemp;
						return ri;
					}
                 	break;

			case EV_TYPE_GoodCountSet :	
					if(iterEventRun->EventRunGoodKind == EV_GOODKIND_Flag)
					{
						int nOrgCount=0;
						if((pGood = GetNewEventGood(szEventRunItemName, iterEventRun->EventRunGoodKind, iterEventRun->EventRunValue)) == NULL )
						{
							ri.szRet = "ERROR:WhenYes:TYPE_GoodCountSet";
							return ri;
						}
						
						strcpy(szChangeItemUnit, pGood->lpGoods->szUnit);
						
						if((ri.szRet = who->SetGoods(pGood)) != "OK")
						{
							delete pGood;
							return ri;
						}
						else
						{	
							if(iterEventRun->EventRunGoodKind != EV_GOODKIND_Flag)
							{
								// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
								// nOrgCount -= iterEventRun->EventRunValue;
								ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,szEventRunItemName,"空",0,szChangeItemUnit,0);
								who->SendMsg(ri.szRet);
							}
						}
					}
					break;

			case EV_TYPE_MoneySet :
					nStatusChange = 1;
					if( strcmp("金錢", szEventRunItemName) == 0)
					{
						//nMoney 金錢
						who->nMoney = iterEventRun->EventRunValue;
					}
					break;
			case EV_TYPE_MoneyIncrease :
					//nStatusChange = 1;
					if( strcmp("金錢", szEventRunItemName) == 0)
					{
						//nMoney 金錢
						
						who->nMoney += iterEventRun->EventRunValue;
						if(who->nMoney > 99999999)
						{
							who->nMoney = 99999999;
						}
						
						// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
						ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"temp","空",0,0,iterEventRun->EventRunValue);
						who->SendMsg(ri.szRet);
						//ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,0,"空",0,0,0);			
						//who->SendMsg(ri.szRet);

					}
					break;
			case EV_TYPE_MoneyDecrease :
					//nStatusChange = 1;
					if( strcmp("金錢", szEventRunItemName) == 0)
					{
						//nMoney 金錢
						
						who->nMoney -= iterEventRun->EventRunValue;
						if(who->nMoney < 0)
						{
							who->nMoney = 0;
						}
						
						// 回傳物品改變 1:代號 2:品名 3:物品現在狀態 4:數量 5:單位 6:金錢變化
						// nOrgCount -= iterEventRun->EventRunValue;

						ri.szRet.Format("%s %s %s %d %s %d",SZADDGOODS,"temp","空",0,0,-iterEventRun->EventRunValue);
						who->SendMsg(ri.szRet);
						//ri.szRet.Format("%s %s %s %d %s %d",SZSUBGOODS,0,"空",0,0,0);			
						//who->SendMsg(ri.szRet);
					}
					break;

			case EV_TYPE_StatusPointSet :
					nStatusChange = 1;
					if( strcmp("神值", szEventRunItemName) == 0)
					{
						who->nShen = iterEventRun->EventRunValue;						
						//who->SendAllInfo();
					}
					else if( strcmp("戰鬥經驗", szEventRunItemName) == 0)
					{
						who->nCombat_exp = iterEventRun->EventRunValue;
					}
					else if( strcmp("臂力", szEventRunItemName) == 0)
					{
						who->nStr = iterEventRun->EventRunValue;
					}
					else if( strcmp("悟性", szEventRunItemName) == 0)
					{
						who->nInt = iterEventRun->EventRunValue;
					}
					else if( strcmp("根骨", szEventRunItemName) == 0)
					{
						who->nCon = iterEventRun->EventRunValue;
					}
					else if( strcmp("身法", szEventRunItemName) == 0)
					{
						who->nDex = iterEventRun->EventRunValue;
					}
					else if( strcmp("潛能", szEventRunItemName) == 0)
					{
						who->nQianNeng = iterEventRun->EventRunValue;
					}
					else if( strcmp("年齡", szEventRunItemName) == 0)
					{
						who->nAge = iterEventRun->EventRunValue;
					}
					else if( strcmp("有效氣", szEventRunItemName) == 0)
					{
						who->nEff_qi = iterEventRun->EventRunValue;
					}
					else if( strcmp("有效精", szEventRunItemName) == 0)
					{
						who->nEff_jing = iterEventRun->EventRunValue;
					}
					break;
			case EV_TYPE_StatusPointIncrease :
					nStatusChange = 1;
					if( strcmp("神值", szEventRunItemName) == 0)
					{
						who->nShen += iterEventRun->EventRunValue;
					}
					else if( strcmp("戰鬥經驗", szEventRunItemName) == 0)
					{
						who->nCombat_exp += iterEventRun->EventRunValue;
					}
					else if( strcmp("臂力", szEventRunItemName) == 0)
					{
						who->nStr += iterEventRun->EventRunValue;
					}
					else if( strcmp("悟性", szEventRunItemName) == 0)
					{
						who->nInt += iterEventRun->EventRunValue;
					}
					else if( strcmp("根骨", szEventRunItemName) == 0)
					{
						who->nCon += iterEventRun->EventRunValue;
					}
					else if( strcmp("身法", szEventRunItemName) == 0)
					{
						who->nDex += iterEventRun->EventRunValue;
					}
					else if( strcmp("潛能", szEventRunItemName) == 0)
					{
						who->nQianNeng += iterEventRun->EventRunValue;
					}
					else if( strcmp("有效氣", szEventRunItemName) == 0)
					{
						who->nEff_qi += iterEventRun->EventRunValue;
					}
					else if( strcmp("有效精", szEventRunItemName) == 0)
					{
						who->nEff_jing += iterEventRun->EventRunValue;
					}
					break;
			case EV_TYPE_StatusPointDecrease :
					nStatusChange = 1;
					if( strcmp("神值", szEventRunItemName) == 0)
					{
						who->nShen -= iterEventRun->EventRunValue;
					}
					else if( strcmp("戰鬥經驗", szEventRunItemName) == 0)
					{
						who->nCombat_exp -= iterEventRun->EventRunValue;
						if(who->nCombat_exp < 0)
							who->nCombat_exp = 0;
					}
					else if( strcmp("臂力", szEventRunItemName) == 0)
					{
						who->nStr -= iterEventRun->EventRunValue;
						if(who->nStr < 0)
							who->nStr = 0;
					}
					else if( strcmp("悟性", szEventRunItemName) == 0)
					{
						who->nInt -= iterEventRun->EventRunValue;
						if(who->nInt < 0)
							who->nInt = 0;
					}
					else if( strcmp("根骨", szEventRunItemName) == 0)
					{
						who->nCon -= iterEventRun->EventRunValue;
						if(who->nCon < 0)
							who->nCon = 0;
					}
					else if( strcmp("身法", szEventRunItemName) == 0)
					{
						who->nDex -= iterEventRun->EventRunValue;
						if(who->nDex < 0)
							who->nDex = 0;
					}
					else if( strcmp("潛能", szEventRunItemName) == 0)
					{
						who->nQianNeng -= iterEventRun->EventRunValue;
						if(who->nQianNeng < 0)
							who->nQianNeng = 0;
					}
					else if( strcmp("有效氣", szEventRunItemName) == 0)
					{
						who->nEff_qi -= iterEventRun->EventRunValue;
						if(who->nEff_qi < 0)
							who->nEff_qi = 0;
					}
					else if( strcmp("有效精", szEventRunItemName) == 0)
					{
						who->nEff_jing -= iterEventRun->EventRunValue;
						if(who->nEff_jing < 0)
							who->nEff_jing = 0;
					}
					break;
			case EV_TYPE_ClearBetray :
					//nStatusChange=1;
					{
						POSITION pos1,pos2;
						//CObject* pos;
						EnterCriticalSection(&myglobs.csPlayerData);
						pos1 = who->listBetray.GetHeadPosition();
						while(pos2 = pos1)
						{	
							if(szEventRunItemName == who->listBetray.GetNext(pos1))
							{
								//pos = who->listBetray.GetAt(pos2);
								who->listBetray.RemoveAt(pos2);
								//delete pos;
								AddRecordMsg("Forgive You!");
							}
						}
						LeaveCriticalSection(&myglobs.csPlayerData);
					}
					break;
			case EV_TYPE_SetFamily :
					//nStatusChange = 1;
					{
						EnterCriticalSection(&myglobs.csPlayerData);
						if(strcmp("拜對方為師",szEventRunItemName) == 0)
						{
							if((who->szFamily != "無門派")&&(who->szFamily != this->szFamily))
							{
								who->listBetray.AddTail(who->szFamily);
							}
							who->szFamily = this->szFamily;
							who->szTeacher = this->szEName;
							who->nGeneration = this->nGeneration + 1;
							GetXFileName(who);
						}
						else
						{
							if((who->szFamily != "無門派")&&(who->szFamily != szEventRunItemName))
							{
								who->listBetray.AddTail(who->szFamily);
							}
							
							who->szFamily = szEventRunItemName;
							who->szTeacher = "";
							who->nGeneration = 99;
							GetXFileName(who);
						}

						ri.szRet.Format("%s OK \n %s,%s,%d,%s",
							SZAPPRENTICE,
							// ri.szRet,	// ?
							who->szFamily,
							who->szTeacher,
							who->nGeneration,
							who->szXFileName);

						LeaveCriticalSection(&myglobs.csPlayerData);

						who->SendMsg(ri.szRet);

					}
					break;

			case EV_TYPE_GoKill :
				{
					// Robin P
					char ri2[256] = "OK";
					CCommandCheck ev_CommandCheck;
					ev_CommandCheck.KillProc(who,(char *)LPCTSTR(who->szEName),(char *)LPCTSTR(this->szEName),ri2);
					who->SendMsg(ri2);
				}
				break;

			case EV_TYPE_GoFight :
				{
					// Robin P
					char ri2[256] = "OK";
					CCommandCheck ev_CommandCheck;
					ev_CommandCheck.FightProc(who,(char *)LPCTSTR(who->szEName),(char *)LPCTSTR(this->szEName),"25",ri2);
					who->SendMsg(ri2);
				}
				break;

//=========================================================andy_command_map 2001.2.16 5:44
			case EV_TYPE_JoboMap :
				{
					CString EscapeMapCName,EscapeMapEName;
					EscapeMapEName=((iterEventRun->EventRunItemName).c_str());
					EscapeMapCName=("OK");
					CString szTemp2;
					szTemp2.Format("%s %s %s",SZJOBO,EscapeMapCName,EscapeMapEName);
					who->SendMsg(szTemp2);
				}
				break;
//============================================================================andy_end 
			case EV_TYPE_ReLifenew :  //轉生
					nStatusChange = 1;
					int lk;
					if( !strcmp(szEventRunItemName,"repower") )	{
						//NULL
					}else if( !strcmp("relife",szEventRunItemName) )	{
						if( who->nRefile[0] < 1 )	{
							who->nEff_force=0;
							who->nEff_jing = 0;
							if( who->nMax_jingli > 300 )	{
								who->nAdd_Jingli = (who->nMax_jingli / 2000) + (who->nAge/100);
							}
								who->nMax_jingli = 0;
							if( who->nMax_force > 300)	{
								who->nAdd_force = (who->nMax_force / 2000) + (who->nAge/100) + (nQianNeng/2000);
							}
								who->nMax_force = 0;

							if( who->nAdd_Jingli < 0 ) who->nMax_jingli = 0;
							if( who->nAdd_force < 0 ) who->nAdd_force = 0;

							who->nCombat_exp = 100; //戰斗經驗
							nQianNeng = 0 ;
							who->nRefile[0] = 1; //轉生值
							who->nAge = 20;
							TObjectSkill *lpPlayerSkill;
							who->listskill.RemoveAll();

							CString szTemp2;
							szTemp2.Format("%s %s",SZRELIFE,"OK");
							who->SendMsg(szTemp2);

							for(lk=0;lk<4;lk++)	{
								lpPlayerSkill = who->GetTSkill(szkill[i]);
								if(lpPlayerSkill == NULL)	{
									who->SetSkill(szkill[i], 1, 1, "");
									lpPlayerSkill = who->GetTSkill(szkill[i]);
								}
							}
							CCmdPlayerLogon m_CmdPlayerLogon;

		int nTest = m_CmdPlayerLogon.SavePlayerData( who);
					//andy_add 清判師
						who->listBetray.RemoveAll();
					//andy_end

						}
					}
				break;
			default:							
					AddRecordMsg("WhenYes:default");
					ri.szRet = "WhenYes:default";
					return ri;
                 	break;
    	}	// switch loop
	ri.szRet = "EventRun_OK";
	return ri;
}

TRetInfo CN_EventNpc::DoEventRunWhenYes(CPlayerInfo *who, list<CEventLimit>::iterator iterLimit)
{
	int i = 0, nStatusChange = 0;
	TRetInfo ri;
	list<CEventRun>::iterator iterEventRun;
	char szEventRunItemName[64] = "NULL", szChangeItemUnit[64] = "NULL", szTemp[128] = "NULL";
	CGoods *pGood = NULL;

	if( (ri.szRet = CheckGoodWeight(who, iterLimit->EventRunListWhenYes)) != "OK"){
		return ri;
	}

	ri.szRet = "EventRun_OK";
    for(iterEventRun = (iterLimit->EventRunListWhenYes).begin(); iterEventRun != (iterLimit->EventRunListWhenYes).end(); iterEventRun++)
    {
		ri = DoEventRun(who, iterEventRun, nStatusChange);
	}	// for loop

	if( nStatusChange == 1){
		who->SendAllInfo();
	}
	if(ri.szRet == "EventRun_OK"){
		ri.szRet = (iterLimit->MsgWhenYes).c_str();
	}
	return ri;
}

TRetInfo CN_EventNpc::DoEventRunWhenNo(CPlayerInfo *who, list<CEventLimit>::iterator iterLimit)
{
	int i = 0, nStatusChange = 0;
	TRetInfo ri;
	list<CEventRun>::iterator iterEventRun;
 	char szEventRunItemName[64] = "NULL", szChangeItemUnit[64] = "NULL", szTemp[128] = "NULL";
	CGoods *pGood = NULL;
	if( (ri.szRet = CheckGoodWeight(who, iterLimit->EventRunListWhenNo)) != "OK"){
		return ri;
	}

	ri.szRet = "EventRun_OK";
    for(iterEventRun = (iterLimit->EventRunListWhenNo).begin(); iterEventRun != (iterLimit->EventRunListWhenNo).end(); iterEventRun++)
    {
		ri = DoEventRun(who, iterEventRun, nStatusChange);
	}

	if( nStatusChange == 1){
		who->SendAllInfo();
	}

	if(ri.szRet == "EventRun_OK"){
		ri.szRet = (iterLimit->MsgWhenNo).c_str();
	}
	return ri;
}

TRetInfo CN_EventNpc::DoDefaultEventRunWhenYes(CPlayerInfo *who, list<CEventAsk>::iterator iterEventAsk)
{
	int i = 0, nStatusChange = 0;
	TRetInfo ri;
	list<CEventRun>::iterator iterEventRun;
	char szEventRunItemName[64] = "NULL", szChangeItemUnit[64] = "NULL", szTemp[128] = "NULL";
	CGoods *pGood = NULL;
	if( (ri.szRet = CheckGoodWeight(who, iterEventAsk->DefaultEventRunListWhenYes)) != "OK")
	{
		return ri;
	}

	ri.szRet = "EventRun_OK";
    for(iterEventRun = (iterEventAsk->DefaultEventRunListWhenYes).begin(); iterEventRun != (iterEventAsk->DefaultEventRunListWhenYes).end(); iterEventRun++)
    {
		ri = DoEventRun(who, iterEventRun, nStatusChange);
	}	// for loop

	if( nStatusChange == 1){
		who->SendAllInfo();
	}
	
	if(ri.szRet == "EventRun_OK"){
		ri.szRet = (iterEventAsk->MsgDefaultWhenYes).c_str();
	}
	return ri;
}

TRetInfo CN_EventNpc::DoDefaultEventRunWhenNo(CPlayerInfo *who, list<CEventAsk>::iterator iterEventAsk)
{
	int i = 0, nStatusChange = 0;
	TRetInfo ri;
	list<CEventRun>::iterator iterEventRun;
	char szEventRunItemName[64] = "NULL", szChangeItemUnit[64] = "NULL", szTemp[128] = "NULL";
	CGoods *pGood = NULL;
	if( (ri.szRet = CheckGoodWeight(who, iterEventAsk->DefaultEventRunListWhenNo)) != "OK"){
		return ri;
	}

	ri.szRet = "EventRun_OK";
    for(iterEventRun = (iterEventAsk->DefaultEventRunListWhenNo).begin(); iterEventRun != (iterEventAsk->DefaultEventRunListWhenNo).end(); iterEventRun++)
    {
		ri = DoEventRun(who, iterEventRun, nStatusChange);
	}	// for loop

	if( nStatusChange == 1){
		who->SendAllInfo();
	}

	if(ri.szRet == "EventRun_OK"){	
		ri.szRet = (iterEventAsk->MsgDefaultWhenNo).c_str();
	}
	return ri;
}


CString CN_EventNpc::CheckGoodWeight(CPlayerInfo *who, list<CEventRun> &EventRunList)
{
	CGoods *lpMyEquip = NULL;
	list<CEventRun>::iterator iterEventRun;
	POSITION pos;
	int nWeight = 0, nEventGoodWeight = 0;

	//char szTemp[64] = "";
	char szTemp[512] = "";

	CString szItem = "";
	CString szRet = "ERROR";

    for(iterEventRun = EventRunList.begin(); iterEventRun != EventRunList.end(); iterEventRun++)	{
		if((iterEventRun->EventRunType == EV_TYPE_GoodCountIncrease) ||
			(iterEventRun->EventRunType == EV_TYPE_GoodCountSet))	{
			strcpy(szTemp, (iterEventRun->EventRunItemName).c_str());
			nEventGoodWeight += GetGoodWeight(szTemp) * (iterEventRun->EventRunValue);
			szItem += (iterEventRun->EventRunItemName + "、").c_str();
		}else if(iterEventRun->EventRunType == EV_TYPE_GoodCountDecrease)	{
			strcpy(szTemp, (iterEventRun->EventRunItemName).c_str());
			nEventGoodWeight -= GetGoodWeight(szTemp) * (iterEventRun->EventRunValue);
		}
	}

	pos = (who->listequip).GetHeadPosition();
	while (pos!=NULL)	{
		lpMyEquip = who->listequip.GetNext(pos);
		if( lpMyEquip->nCount < 0 )	lpMyEquip->nCount = 0;
		nWeight += lpMyEquip->lpGoods->nWeight * lpMyEquip->nCount;
	}
	
	if( nWeight < 0 || (nWeight + nEventGoodWeight) > (who->nStr * 1000) )	{
		szRet.Format("%s可攜帶重量%d，目前攜帶重量%d，%s等物品總重量約%d，超過負重限制",
			who->szCName, who->nStr*1000, nWeight, szItem, nEventGoodWeight);
		return szRet;
	}	
	return "OK";
}
