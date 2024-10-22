// BaseSkillClass.cpp: implementation of the CBaseSkillClass class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Skill.h"
//#include "..\..\xMudOs.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*CSkillClass::CSkillClass()
{
	
}

CSkillClass::~CSkillClass()
{

}*/
void CSkill::Init(char *szFileName)
{
	char szBuf[100];
	CString szStr;
	int nValue =0;
	TFeat *newFeat;
    TNeedSkill *lpNeedSkill;
	
	FILE *file;

	if((file = fopen(szFileName,"r"))!=NULL)
	{
	while(fscanf(file,"%s",szBuf)!=EOF)
	{
		szStr = szBuf;
		if(szStr=="中文名")
		{
			fscanf(file,"%s",szBuf);
			szCName = szBuf;
		}else if(szStr=="英文名")	{
			fscanf(file,"%s",szBuf);
			szEName = szBuf;
		}else if(szStr=="類別")	{
			fscanf(file,"%s",szBuf);
			szStr = szBuf;
			if(szStr=="基本")
			    nType = ST_base;
			else if(szStr=="特殊")
			    nType = ST_special;
			else if(szStr=="其他")
			    nType = ST_other;
		}else if(szStr=="配置")	{
			fscanf(file,"%s",szBuf);
			szStr = szBuf;
            if(szStr=="拳腳")
				nCanMap |=SCM_unarmed;
			else if(szStr=="招架")
				nCanMap |=SCM_parry;
			else if(szStr=="輕功")
				nCanMap |=SCM_dodge;
			else if(szStr=="內功")
				nCanMap |=SCM_force;
			else if(szStr=="劍法")
				nCanMap |=SCM_sword;
			else if(szStr=="刀法")
				nCanMap |=SCM_blade;
			else if(szStr=="棍法")
				nCanMap |=SCM_club;
			else if(szStr=="短兵")
				nCanMap |=SCM_short;
            else if(szStr=="暗器")
				nCanMap |=SCM_throwing; 
            else if(szStr=="鞭法")
				nCanMap |=SCM_whip;	
	        else if(szStr=="錘法")
				nCanMap |=SCM_hammer;
		}else if(szStr=="輕功數")	{    
			fscanf(file,"%d",&nDodge);			//映射成輕功的時候,有幾招
		}else if(szStr=="招架數")	{
			fscanf(file,"%d",&nParry);			//映射成招架的時候,有幾招	
		}else if(szStr=="[學習條件]")	{	//int nUnarmedParry;	//敵方沒有兵器時的招架招數
			do	{
			    fscanf(file,"%s",szBuf);
			    szStr = szBuf;
				if(szStr=="內力")	{
				    fscanf(file,"%d",&nNeedMax_force);
				}else if(szStr=="精力")	{
				    fscanf(file,"%d",&nNeedMax_jingli);
				}else if(szStr=="武功等級")	{
					lpNeedSkill = new TNeedSkill;
					fscanf(file,"%s",szBuf);
					lpNeedSkill->szEName = szBuf;
					fscanf(file,"%d",&nValue);
					lpNeedSkill->nLevel = nValue;
					listNeedSkill.AddTail(lpNeedSkill);
				}else if(szStr=="武器")	{
					fscanf(file,"%s",szBuf);
					szStr = szBuf;          
					if(szStr=="劍")
					    nNeedWeapon = WK_sword;
					else if(szStr=="刀")
					    nNeedWeapon = WK_blade;
					else if(szStr=="棍")
					    nNeedWeapon = WK_club;
					else if(szStr=="短兵")
						nNeedWeapon = WK_short;
					else if(szStr=="暗器")
					    nNeedWeapon = WK_throwing;
					else if(szStr=="鞭")
					    nNeedWeapon = WK_whip;
					else if(szStr=="錘")
					    nNeedWeapon = WK_hammer;
				}		
			}while(szStr!="[學習條件結束]");
		}
		else if(szStr=="[招式]")
		{
			newFeat = new TFeat;

			do{
			    fscanf(file,"%s",szBuf);
			    szStr = szBuf;
				
				if(szStr=="序號")
				{
					fscanf(file,"%d",&nValue);
					newFeat->nSN = nValue;
				}
				else if(szStr=="名稱")
				{
					fscanf(file,"%s",szBuf);
					newFeat->szName = szBuf;
				}
				else if(szStr=="內力")
				{
					fscanf(file,"%d",&nValue);
					newFeat->nForce = nValue;
				}
				else if(szStr=="傷害")
				{
					fscanf(file,"%d",&nValue);
					newFeat->nDamage = nValue;
				}
				else if(szStr=="輕功")
				{
					fscanf(file,"%d",&nValue);
					newFeat->nDodge = nValue;
				}
				else if(szStr=="招架")
				{
					fscanf(file,"%d",&nValue);
					newFeat->nParry = nValue;
				}
				else if(szStr=="類型")
				{
					fscanf(file,"%s",szBuf);
					newFeat->szDamageType = szBuf;
				}
				else if(szStr=="等級")
				{
					fscanf(file,"%d",&nValue);
					newFeat->nLevel = nValue;
				}		
			}while(szStr!="[招式結束]");
			listFeat.AddTail(newFeat);
		}
	}
	fclose(file);
	}
}

TRetInfo CSkill::DoLearn(CActiveObject *who)
{
	CSkill *lpSkill;
	TRetInfo tRet;
	tRet.bRet = FALSE;

	//學習門檻
	if (who->nMax_force < nNeedMax_force)
	{
		tRet.szRet.Format("你的內力還不夠不能練%s。",szCName);
		return tRet;
	}
	if (who->nMax_jingli < nNeedMax_jingli)
	{
		tRet.szRet.Format("你的精力還不夠不能練%s。",szCName);
		return tRet;
	}
	for(int i=0;i<listNeedSkill.GetCount();i++)
	{
	    if (who->GetSkillLevel(listNeedSkill.GetAt(listNeedSkill.FindIndex(i))->szEName) < listNeedSkill.GetAt(listNeedSkill.FindIndex(i))->nLevel)
		{
		    lpSkill = GetSkillClass(listNeedSkill.GetAt(listNeedSkill.FindIndex(i))->szEName);
		    tRet.szRet.Format("你的%s火候太淺不能練%s。",lpSkill->szCName,szCName);
		    return tRet;
		}
	}

	if(who->lpWeapon != NULL)
	{
		if(nNeedWeapon==0)
		{
			if(nCanMap & SCM_unarmed) {
			    tRet.szRet.Format("%s必須空手才能練習。",szCName);
			    return tRet;
			}
		}
		else if(!(who->lpWeapon->lpWeapon->nKind & nNeedWeapon))
		{
		    tRet.szRet = "你使用的武器不對。";
		    return tRet;
		}
	}
	else
	{
		if (nNeedWeapon!=0)
		{
		    tRet.szRet = ("你必須使用適當的武器。");
		    return tRet;
		}
	}

	tRet.bRet = TRUE;
	return tRet;
}
TRetInfo CSkill::DoPractice(CActiveObject *who)
{
	TRetInfo ri;
	ri = DoLearn(who);
	return ri;
}