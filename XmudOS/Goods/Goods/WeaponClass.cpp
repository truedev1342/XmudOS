// WeaponClass.cpp: implementation of the CWeaponClass class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "WeaponClass.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWeaponClass::CWeaponClass()
{
	
}

CWeaponClass::~CWeaponClass()
{
//   delete lpGoods; 
//   delete lpWeapon;
}
void CWeaponClass::InitWeapon(char *szFileName)
{
	FILE *fp;
	char szBuf[100];
	CString szStr;
	int nValue =0;
	TGoods *Goods;
    TWeapon *Weapon;


	Goods = new TGoods;
	Weapon = new TWeapon;
	Goods->nKinds = GK_weapon;		//種類

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
			else if(szStr=="武器種類")
			{	
				fscanf(fp,"%s",szBuf);
				szStr = szBuf;
				if(szStr=="劍")
				    Weapon->nKind = WK_sword;
				else if(szStr=="棍")
				    Weapon->nKind = WK_club;
				else if(szStr=="刀")
				    Weapon->nKind = WK_blade;
				else if(szStr=="短兵")
					Weapon->nKind = WK_short;
				else if(szStr=="暗器")
				    Weapon->nKind = WK_throwing;
				else if(szStr=="鞭")
				    Weapon->nKind = WK_whip;
				else if(szStr=="錘")
				    Weapon->nKind = WK_hammer;
			}
			else if(szStr=="攻擊力")
			{		
				fscanf(fp,"%d",&nValue);
				Weapon->nAttack = nValue;
			}
			else if(szStr=="防御力")
			{	
				fscanf(fp,"%d",&nValue);
				Weapon->nDefance = nValue;
			}
			else if(szStr=="裝備語句")
			{
				fscanf(fp,"%s",szBuf);
				Weapon->szWieldMsg = szBuf;
			}
			else if(szStr=="卸下語句")
			{		
				fscanf(fp,"%s",szBuf);
				Weapon->szUnWieldMsg = szBuf;
			}
		}
		fclose(fp);
	}
	lpGoods = Goods;
	lpWeapon = Weapon;
	nNew = lpGoods->nDurable;
}