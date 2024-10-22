
#include "stdafx.h"
#include "XmudOS.h"
#include "ActiveObject.h"
#include "Condition.h"
#include "Player.h"
#include "npc\npc.h"

extern rmfullglobals myglobs;

void CActiveObject::DoHeartBeat()
{
	if(bPlayer) {
		((CPlayerInfo *)this)->nRound += 1;
	}

	if(nStatus == AOS_dead)	return;
	if( nBusy > 0 )	{ 
		nBusy--; 
		if(nBusy <= 0)	DoAction();
	}
	nTick--;
	if( nTick > 0  ) return;
	nTick = HEALINGGAP;

	if(bPlayer) {
		((CPlayerInfo *)this)->Healing();
	}
}

void CActiveObject::DoAction()
{
	CString sResult;
	POSITION pos;
	int nLevel;

	sResult.Empty();
	if(nStatus == AOS_dazuo){
		nStatus = AOS_none;
		EnterCriticalSection(&myglobs.csPlayerData);
		pos = GetConditionPos("DaZuo");
		if (pos != NULL) {
			nEff_force += listcondition.GetAt(pos)->nPower/5;
			if(nEff_force > nMax_force*2)	{
				nLevel = GetSkillLevel("BaseForce");
				if(nMax_force >= nLevel * 10)	{
					nEff_force = nMax_force*2;
					sResult.Format("%s 你覺得真氣練到這里後繼無力了。",SZFAILMSG);
					SendMsg(sResult);
				}else{
					nEff_force -= nMax_force*2;
					nMax_force ++;
				}
			}
			sResult.Format("%s %s %s %d,%d", SZDAZUOEND,szCName,szEName, nEff_force,nMax_force);
			DeleteCondition("DaZuo");
		}
		LeaveCriticalSection(&myglobs.csPlayerData);
	}else if(nStatus == AOS_tuna){
		nStatus = AOS_none;
		EnterCriticalSection(&myglobs.csPlayerData);
		pos = GetConditionPos("TuNa");
		if (pos != NULL) {
			nEff_jingli += listcondition.GetAt(pos)->nPower/5;
			if(nEff_jingli > nMax_jingli*2){
				nLevel = GetSkillLevel("BaseForce");
				if(nMax_jingli >= nLevel * 3){
					nEff_jingli = nMax_jingli*2;
					sResult.Format("%s 你覺得真氣練到這里後繼無力了。",SZFAILMSG);
					SendMsg(sResult);
				}else{
					nEff_jingli -= nMax_jingli*2;
					nMax_jingli ++;
				}
			}
			sResult.Format("%s %s %s %d,%d", SZTUNAEND,szCName,szEName, nEff_jingli,nMax_jingli);
			DeleteCondition("TuNa");
		}
		LeaveCriticalSection(&myglobs.csPlayerData);
	}
	if (!sResult.IsEmpty())
		MapMessage(sResult, this);
}

POSITION CActiveObject::GetConditionPos(CString szName)
{
	CCondition * lpCondition;
	POSITION pos;
	pos = listcondition.GetHeadPosition();
	while(pos != NULL)
	{
		lpCondition = listcondition.GetNext(pos);
		if(lpCondition->szName == szName)
		{
			if(pos == NULL)
				pos = listcondition.GetTailPosition();
			else
				listcondition.GetPrev(pos);
			break;
		}
	}
	return pos;
}

void CActiveObject::ApplyCondition(int nKind, CString szName, int nVal, int nPower)
{
	CCondition * lpCondition;
	POSITION pos;
	pos = GetConditionPos(szName);
	if(pos != NULL)
	{
		lpCondition = listcondition.GetAt(pos);
		lpCondition->nTime += nVal;
		lpCondition->nPower += nPower;
	}
	else
	{
		lpCondition = new CCondition;
		lpCondition->nKind = nKind;
		lpCondition->szName = szName;
		lpCondition->nTime = nVal;
		lpCondition->nPower = nPower;
		listcondition.AddTail(lpCondition);
	}
}

int CActiveObject::QueryCondition(CString szName)
{
	POSITION pos;
	pos = GetConditionPos(szName);
	if(pos != NULL)
	{
		return listcondition.GetAt(pos)->nTime;
	}
	return 0;
}

BOOL CActiveObject::DeleteCondition(CString szName)
{
	POSITION pos;
	pos = GetConditionPos(szName);
	if(pos != NULL)
	{
		listcondition.RemoveAt(pos);
		return TRUE;
	}
	return FALSE;
}

void CActiveObject::UpdataCondition(CCondition * lpCondition)
{
	switch(lpCondition->nKind)
	{
	case CK_normal:
		if(lpCondition->nTime-- <= 0)
		{
			listcondition.RemoveAt(GetConditionPos(lpCondition->szName));
			delete lpCondition;
		}
		break;
	case CK_poison:
		if(lpCondition->UpdataPoison(this) <= 0)
		{
			listcondition.RemoveAt(GetConditionPos(lpCondition->szName));
			delete lpCondition;
		}
		break;
	case CK_yungong:
		if(lpCondition->nTime-- <= 0)
		{
			RunSkillCom(lpCondition->szName, "PerformEnd", NULL);
			listcondition.RemoveAt(GetConditionPos(lpCondition->szName));
			delete lpCondition;
		}
		break;
	case CK_special:
		if(lpCondition->nTime-- <= 0)
		{
			SpecialActEnd(lpCondition, this);
			listcondition.RemoveAt(GetConditionPos(lpCondition->szName));
			delete lpCondition;
		}
		break;
	default:
		listcondition.RemoveAt(GetConditionPos(lpCondition->szName));
		delete lpCondition;
		break;
	}
}