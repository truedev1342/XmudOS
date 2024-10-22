
#include "..\stdafx.h"
#include "BookClass.h"


CBookClass::CBookClass()
{	
}

CBookClass::~CBookClass()
{
}
void CBookClass::InitBook(char *szFileName)
{
	FILE *fp;
	char szBuf[100];
	CString szStr;
	int nValue =0;
	TGoods *Goods;
    TBook  *Book;
	TBookNeedSkill *NeedSkill;

	Goods = new TGoods;
	Book = new TBook;

	Goods->nKinds = GK_book;

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
				else{
				}
			}
			else if(szStr=="可學武功")
			{
				fscanf(fp,"%s",szBuf);
				Book->szSkillEName = szBuf;
			}
			else if(szStr=="最大等級")
			{
				fscanf(fp,"%d",&nValue);
				Book->nMaxLevel = nValue +300;
			}
			else if(szStr=="需悟性")
			{
				fscanf(fp,"%d",&nValue);
				Book->nNeedInt = nValue;
			}
			else if(szStr=="需臂力")
			{
				fscanf(fp,"%d",&nValue);
				Book->nNeedStr = nValue;
			}
			else if(szStr=="需根骨")
			{
				fscanf(fp,"%d",&nValue);
				Book->nNeedCon = nValue;
			}
			else if(szStr=="需身法")
			{
				fscanf(fp,"%d",&nValue);
				Book->nNeedDex = nValue;
			}
			else if(szStr=="需內力")
			{
				fscanf(fp,"%d",&nValue);
				Book->nNeedForce = nValue;
			}
			else if(szStr=="需武功")
			{
				fscanf(fp,"%s %d",szBuf,&nValue);
				NeedSkill = new TBookNeedSkill;
                NeedSkill->szNeedSkillEName = szBuf;
				NeedSkill->nNeedSkillLevel = nValue;
				Book->listNeedSkill.AddTail(NeedSkill);
			}
		}
		fclose(fp);
	}
	else
	{
		strcat(szFileName, " Read book data error");
		AddRecordMsg(szFileName);
	}
	
	lpGoods = Goods;
    lpBook  = Book;
	nNew = lpGoods->nDurable;
}