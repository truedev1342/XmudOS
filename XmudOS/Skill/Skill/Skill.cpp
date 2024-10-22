
#include "..\..\stdafx.h"
#include "Skill.h"


//計算選的招數
int NewRandom(int n,int base,int d)
{
 	int i=1;
	int randum = random(sum(n,base,d));
	if( sum(6,base,d) < randum) 
	{
		i=7;
		while(sum(i,base,d) < randum )
		i++;
	}
	else
	{
		while(sum(i,base,d) < randum)
		i++;
	}
	return (i-1);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkill::CSkill()
{
	szEName = "";
	szCName = "";
	szPerform = "";
	nUsage = 0;			//這種技能都可以用來干什麼
	nType = ST_other;	//這種技能的種類
	nCanMap = 0;		//都可以映射成什麼
	
	nDodge = 0;			//映射成輕功的時候,有幾招
	nParry = 0;			//映射成招架的時候,有幾招
	nUnarmedParry = 0;	//敵方沒有兵器時的招架招數

	nNeedMax_force = 0;	
	nNeedMax_jingli = 0;
	nNeedWeapon = 0; 
}

CSkill::~CSkill()
{
/*	while(listFeat.GetCount()!=0)
	{
	    listFeat.RemoveTail();
	}
	while(listNeedSkill.GetCount()!=0)
	{
	    listNeedSkill.RemoveTail();
	}*/
	listFeat.RemoveAll();
	listNeedSkill.RemoveAll();
}

TFeat * CSkill::GetFeat(CActiveObject *who)
{
	int n,i,nLevel;
	TFeat *Feat=NULL,*lpFeat=NULL;

	nLevel = who->GetSkillLevel(szEName);	
	n = listFeat.GetCount();
	i = 0;
	while (i < n) {
		Feat = listFeat.GetAt(listFeat.FindIndex(i));
		if (Feat->nLevel > nLevel) break;
		i++;
	}
	int index = random(i*2-1) / 2;
	lpFeat = listFeat.GetAt(listFeat.FindIndex(index));
	
	if(lpFeat!=NULL) return  lpFeat;// 最後一式出招機率為其他的1/2
	else return NULL;
}

CString CSkill::GetDodgeMsg(CActiveObject *who)
{
	CString strRet;
	if(nDodge<=0)
		strRet.Format("但是被%s躲開了", who->szCName);
//		return ("得到輕功信息錯誤,請與巫師聯系.");
	else 
		strRet.Format("%%%d,%s,%d%%",2,szEName,random(nDodge));
	return strRet;
}

CString CSkill::GetParryMsg(CActiveObject *you)
{
	CString strRet;
	if(nParry<=0)
		// Spock +1
		strRet.Format("但是被%s擋開了", you->szCName);
//		return ("得到招架信息錯誤,請與巫師聯系.");
	else if(you->lpWeapon != NULL)
		strRet.Format("%%%d,%s,%d%%",3,szEName,random(nParry));
	else
		strRet.Format("%%%d,%s,%d%%",4,szEName,random(nParry));
//	else
//		strRet.Format("%%%d,%s,%d%%",4,"BaseParry",random(2));
	return strRet;
}

/*TRetInfo CSkill::DoLearn(CActiveObject *who)
{
	TRetInfo tRet;
	tRet.bRet = TRUE;
	return tRet;
}*/


CString CSkill::GetMaxName(CActiveObject *who)
{
	int i;
	int level;
	if(nType == ST_base)
		return("%s只要你會,就會使用所有的招式.", szCName);
	level = who->GetSkillLevel(szEName);
	if( level == -1 )
		return ("你現在還不會這項武功.");
	for(i = listFeat.GetCount()-1; i >= 0; i--)
		if(level >= listFeat.GetAt(listFeat.FindIndex(i))->nLevel)
			return listFeat.GetAt(listFeat.FindIndex(i))->szName;
	return listFeat.GetHead()->szName;
}
/*
void CSkill::HitOb(CActiveObject *me, CActiveObject *you, int &damage_bonus, CString &strRet, int nWhere)
{
	return;
}*/