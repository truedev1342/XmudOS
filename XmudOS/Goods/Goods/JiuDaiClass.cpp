// JiuDaiClass.cpp: implementation of the CJiuDaiClass class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "JiuDaiClass.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJiuDaiClass::CJiuDaiClass()
{
	
}

CJiuDaiClass::~CJiuDaiClass()
{
//	delete lpGoods; 
//	delete lpJiuDai;
}
void CJiuDaiClass::InitJiuDai(char *szFileName)
{
	FILE *fp;
	char szBuf[100];
	CString szStr;
	int nValue =0;
	TGoods *Goods;
    TJiuDai *JiuDai;

	Goods = new TGoods;
	JiuDai = new TJiuDai;

	Goods->nKinds = GK_jiudai;		//種類

	fp = fopen(szFileName,"r");
	if(fp!=NULL)
	{
		while(fscanf(fp,"%s",szBuf)!=EOF)
		{
			szStr = szBuf;
			if(szStr=="中文名")
			{
				fscanf(fp,"%s",szBuf);
			    Goods->szCName = szBuf;
			}
			else if(szStr=="英文名")
			{
				fscanf(fp,"%s",szBuf);
				Goods->szEName = szBuf;
			}
			else if(szStr=="單位")
			{
				fscanf(fp,"%s",szBuf);
				Goods->szUnit = szBuf;
			}
			else if(szStr=="外觀")
			{
				fscanf(fp,"%s",szBuf);
				Goods->szdescribe = szBuf;
			}
			else if(szStr=="重量")
			{
				fscanf(fp,"%d",&nValue);
				Goods->nWeight = nValue;
			}
			else if(szStr=="價格")
			{
				fscanf(fp,"%d",&nValue);
				Goods->nCost = nValue;
			}
			else if(szStr=="耐用度")
			{
				fscanf(fp,"%d",&nValue);
				Goods->nDurable = nValue;
			}
			else if(szStr=="屬性")
			{
				fscanf(fp,"%s",szBuf);
				szStr = szBuf;
				if(szStr == "不能賣")
                    Goods->nUsage |= GP_nosell;
				else if(szStr == "不能丟")
                    Goods->nUsage |= GP_nodrop;
                else if(szStr == "不會變舊")
					Goods->nUsage |= GP_noold;
				else if(szStr == "女人用")
                    Goods->nUsage |= GP_forfemale;
				else if(szStr == "男人用")
                    Goods->nUsage |= GP_formale;
				else if(szStr == "不可視")
                    Goods->nUsage |= GP_invisible;
				else 
				{
					strcpy(szBuf,szFileName);
					strcat(szBuf,szStr);
					strcat(szBuf," error!");
                    AddRecordMsg(szBuf);
				}
			}
			else if(szStr=="可飲次數")
			{
				fscanf(fp,"%d",&nValue);
				JiuDai->nMaxRemain = nValue;
			}
			else if(szStr=="止渴度")
			{
				fscanf(fp,"%d",&nValue);
				nDrink = nValue;
			}
		}
		fclose(fp);
	}
	else
	{
		strcat(szFileName, " Read jiudai data error");
		AddRecordMsg(szFileName);
	}
	lpGoods = Goods;
	lpJiuDai = JiuDai;
	nNew = lpGoods->nDurable;
}