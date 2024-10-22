
#include "..\..\stdafx.h"
#include "EquipClass.h"

CEquipClass::CEquipClass()
{
 	
}

CEquipClass::~CEquipClass()
{

}
void CEquipClass::InitEquip(char *szFileName)
{
	FILE *fp;
	char szBuf[100];
	CString szStr;
	int nValue =0;
	TGoods *Goods;
    TEquip *Equip;

	Goods = new TGoods;
	Equip = new TEquip;

	Goods->nKinds = GK_equip;

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
			else if(szStr=="裝備部位")
			{
				fscanf(fp,"%s",szBuf);
				szStr = szBuf;
				if(szStr=="頭")
				    Equip->nWhereWear = EW_head;
				else if(szStr=="身")
                    Equip->nWhereWear = EW_body;
				else if(szStr=="頸")
                    Equip->nWhereWear = EW_neck;
				else if(szStr=="胸")
                    Equip->nWhereWear = EW_chest;
				else if(szStr=="腹")
                    Equip->nWhereWear = EW_abdomen;
				else if(szStr=="腕")
                    Equip->nWhereWear = EW_wrist;
				else if(szStr=="膝")
                    Equip->nWhereWear = EW_knee;
				else if(szStr=="手")
                    Equip->nWhereWear = EW_hand;
				else if(szStr=="腳")
                    Equip->nWhereWear = EW_foot;
			}
			else if(szStr=="增加防御值")
			{
				fscanf(fp,"%d",&nValue);
				Equip->nDefance = nValue;
			}
			else if(szStr=="抗內力值")
			{
				fscanf(fp,"%d",&nValue);
				Equip->nDefanceForce = nValue;
			}
			else if(szStr=="影響輕功")
			{
				fscanf(fp,"%d",&nValue);
				Equip->nDodge = nValue;			
			}
			else if(szStr=="裝備語句")
			{
				fscanf(fp,"%s",szBuf);
				Equip->szWearMsg = szBuf;	
			}
			else if(szStr=="卸下語句")
			{
				fscanf(fp,"%s",szBuf);
				Equip->szUnWearMsg = szBuf;
			}
		}
		fclose(fp);
	}
	else
	{
		strcat(szFileName, " Read equip data error");
		AddRecordMsg(szFileName);
	}
	nWearWhere = 0;
	lpGoods = Goods;
	lpEquip = Equip;
	nNew = lpGoods->nDurable;
}