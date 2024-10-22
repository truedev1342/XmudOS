// Condition.cpp: implementation of the CCondition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Condition.h"
#include "ActiveObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCondition::CCondition()
{
	nKind = 0;
	szName = "";
	nTime = 0;
	nPower = 0;
}

CCondition::~CCondition()
{
}

int CCondition::UpdataPoison(CActiveObject * lpMan)
{
	if(szName == "wine")
		return UpdataDrink(this,lpMan);
	if(szName == "ice")
		return UpdataIce(this,lpMan);
	if(szName == "Yihan")
		return UpdataYihan(this,lpMan);
	if(szName == "Duanchanghua")
		return UpdataDuanchanghua(this,lpMan);
	if(szName == "Rose")
		return UpdataRose(this,lpMan);
	if(szName == "Sleepdrug")
		return UpdataSleepdurg(this,lpMan);
	if(szName == "Snake")
		return UpdataSnake(this,lpMan);
	if(szName == "Shengshifu")
		return UpdataShengshifu(this,lpMan);
	if(szName == "Xingxiustrike")
		return UpdataXingxiustrike(this,lpMan);
	if(szName == "Freezeblood")
		return UpdataFreezeblood(this,lpMan);
	if(szName == "Bandaged")
		return UpdataBandaged(this,lpMan);
	return 0;
}

int UpdataDrink(CCondition * lpCondition, CActiveObject * lpMan)
{
	int nlimit;
	nlimit = lpMan->nCon * 2 + lpMan->nMax_force / 20;

	//if( lpCondition->nTime > nlimit && living(me) ) 
	{
		lpMan->Unconcious();
		return 0;
	} 
/*	else if( !living(me) ) 
	{
		message("vision", me->name() + "打了個隔，不過依然爛醉如泥。\n",
			environment(me), me);
	} 
	else if( lpCondition->nTime > limit/2 ) 
	{
		tell_object(me, "你覺得腦中昏昏沉沉，身子輕飄飄地，大概是醉了。\n");
		message("vision", me->name() + "搖頭晃腦地站都站不穩，顯然是喝醉了。\n",
			environment(me), me);
		me->receive_damage("gin", 10);
	} 
	else if( lpCondition->nTime > limit/4 ) 
	{
		tell_object(me, "你覺得一陣酒意上沖，眼皮有些沉重了。\n");
		message("vision", me->name() + "臉上已經略顯酒意了。\n",
			environment(me), me);
		me->receive_healing("gin", 10);
		me->receive_healing("kee", 15);
	}
*/
	return --(lpCondition->nTime);
}
int UpdataIce(CCondition * lpCondition, CActiveObject * lpMan)
{
	return 0;
}
int UpdataYihan(CCondition * lpCondition, CActiveObject * lpMan)
{
	return 0;
}
int UpdataDuanchanghua(CCondition * lpCondition, CActiveObject * lpMan)
{
	return 0;
}
int UpdataRose(CCondition * lpCondition, CActiveObject * lpMan)
{
	return 0;
}
int UpdataSleepdurg(CCondition * lpCondition, CActiveObject * lpMan)
{
	return 0;
}
int UpdataSnake(CCondition * lpCondition, CActiveObject * lpMan)
{
	return 0;
}
int UpdataShengshifu(CCondition * lpCondition, CActiveObject * lpMan)
{
	return 0;
}
int UpdataXingxiustrike(CCondition * lpCondition, CActiveObject * lpMan)
{
	return 0;
}
int UpdataFreezeblood(CCondition * lpCondition, CActiveObject * lpMan)
{
	return 0;
}
int UpdataBandaged(CCondition * lpCondition, CActiveObject * lpMan)
{
	lpMan->ReceiveCure(3);
	return --(lpCondition->nTime);
}
