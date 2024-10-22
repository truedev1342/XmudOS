
#include "..\..\stdafx.h"
#include "FoodClass.h"

CFoodClass::CFoodClass()
{

}

CFoodClass::~CFoodClass()
{

}
void CFoodClass::InitFood(char *szFileName)
{
	FILE *fp;
	char szBuf[100];
	CString szStr;
	int nValue =0;
	TGoods *Goods;
    TFood  *Food;

	Goods = new TGoods;
	Food = new TFood;

	Goods->nKinds = GK_food;		//種類

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
				else {
				}
			}
			else if(szStr=="食用次數")
			{
				fscanf(fp,"%d",&nValue);
				Food->nMaxRemain = nValue;
			}
			else if(szStr=="飽足感")
			{
				fscanf(fp,"%d",&nValue);
				Food->nSupply = nValue;
			}
			else if(szStr=="止渴度")
			{
				fscanf(fp,"%d",&nValue);
				Food->nDrink = nValue;
			}
		}
		fclose(fp);
	}
	else
	{
		strcat(szFileName, " Read food data error");
		AddRecordMsg(szFileName);
	}
	lpFood = Food;
	lpGoods = Goods;
	nNew = lpGoods->nDurable;
	nRemain = lpFood->nMaxRemain;
}