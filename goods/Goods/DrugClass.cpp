// DrugClass.cpp: implementation of the CDrugClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrugClass.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrugClass::CDrugClass()
{
	
		
}

CDrugClass::~CDrugClass()
{
//	delete lpGoods;  
//	delete lpDrug;
}
void CDrugClass::InitDrug(char *szFileName)
{
	FILE *fp;
	char szBuf[100];
	CString szStr;
	int nValue =0;
	TGoods *Goods;
    TDrug *Drug;

	Goods = new TGoods;
	Drug = new TDrug;

	Goods->nKinds = GK_drug;		//種類

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
			else if(szStr=="增加氣"){
				fscanf(fp,"%d",&nValue);
				Drug->nQi = nValue;
			}else if(szStr=="增加精"){
				fscanf(fp,"%d",&nValue);
				Drug->nJing = nValue;
			}else if(szStr=="增加內力"){
				fscanf(fp,"%d",&nValue);
				Drug->nForce = nValue;
			}else if(szStr=="增加精力"){
				fscanf(fp,"%d",&nValue);
				Drug->nJingli = nValue;
			}else if(szStr=="增加臂力"){
				fscanf(fp,"%d",&nValue);
				Drug->nStr = nValue;
			}else if(szStr=="增加悟性"){
				fscanf(fp,"%d",&nValue);
				Drug->nInt = nValue;
			}else if(szStr=="增加根骨"){
				fscanf(fp,"%d",&nValue);
				Drug->nCon = nValue;
			}else if(szStr=="增加身法"){
				fscanf(fp,"%d",&nValue);
				Drug->nDex = nValue;
			}
		}
		fclose(fp);
	}else{
		strcat(szFileName, " Read drug data error");
		AddRecordMsg(szFileName);
	}
	lpGoods = Goods;
	lpDrug = Drug;
	nNew = lpGoods->nDurable;
}