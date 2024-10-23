#if !defined(AFX_ACTIVEOBJECT_H__E2D1FB60_8797_11D3_BA84_0000E8A021D8__INCLUDED_)
#define AFX_ACTIVEOBJECT_H__E2D1FB60_8797_11D3_BA84_0000E8A021D8__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif
#include "common.h"
class CSkill;
class CWeapon;
class CGoods;
class CCondition;
#define HEALINGGAP	15
#define AOS_none		0
#define AOS_act_wait		0x100
#define AOS_act_sleep		0x200
#define AOS_act_dead		0x400
#define AOS_act_fight		0x1000
#define AOS_act_facesb		0x2000
#define AOS_act_changemap	0x4000
#define AOS_facesb		((AOS_act_facesb)|1)
#define AOS_changemap	((AOS_act_changemap)|2)
#define AOS_hit			((AOS_act_fight)|10)
#define AOS_fight		((AOS_act_fight)|11)
#define AOS_kill		((AOS_act_fight)|12)
#define AOS_escape		((AOS_act_fight)|13)
#define AOS_dazuo		((AOS_act_wait)|20)
#define AOS_tuna		((AOS_act_wait)|21)
#define AOS_unconcious	(AOS_act_sleep|AOS_act_wait|50)
#define AOS_sleep		(AOS_act_sleep|AOS_act_wait|51)
#define AOS_dead		(AOS_act_dead|AOS_act_sleep|AOS_act_wait|100)

typedef struct tagObjectSkill
{
	int		nScore;
	int		nLevel;
	CString szMapping;
	CSkill * lpSkill;
	tagObjectSkill()
	{
		nScore = 0;
		nLevel = 0;
		szMapping = "";
		lpSkill = NULL;
	}
}TObjectSkill,*PObjectSkill;

TObjectSkill * GetTObjSkill(CString szEName, int nType, int nCanMap, 
						 int level = 0, int score = 0, CString szMapping = "");
typedef struct tagPawn{
	CString szCName;
	CString szEName;
	int nKind;
	int  nYear;
	int  nMonth;
	int  nDay;
}TPawn;

typedef struct tagMixed
{
	BOOL bIsInt;
	int nValue;
	CString szValue;
	tagMixed()
	{
		bIsInt = -1;
	}
}TMixed;

typedef struct tagTempVal
{
	CString szName;
	BOOL bIsInt;
	int		nValue;
	CString	szValue;
	tagTempVal(){
		szName = "";
		bIsInt = -1;
	}
}TTempVal;

class CActiveObject  
{
public:
	char szCheck[8];
	CString szCName;
	CString szEName;
	CString szNickName;
	CString szTilte;
	CString szXFileName;
	CString szFamily;
	CString	szTeacher;
	CString	szPerson;
	CString szRoom;
	CString szSex;

	int		nAge;
	int		nShen;
	int		nDamage;
	int		nStr;
	int		nInt;
	int		nCon;
	int		nDex;
	int		nEff_qi;
	int		nMax_qi;
	int		nEff_jing;
	int		nMax_jing;
	int		nEff_jingli;
	int		nMax_jingli;
	int		nAdd_Jingli;
	int		nEff_force;
	int		nMax_force;
	int		nAdd_force;
	int		nCombat_exp;
	int		nQianNeng;
	int		nScore;
	int		nGeneration;
	int		nMoney;
	int		nStatus;
	int		nRefile[10];
	CWeapon *lpWeapon;
	int		nBusy;
	int		nOther;
	int g_HasEvent;
	int		nEscapeNow;
	int		nShootint;
	BOOL	bPlayer;
	CTime	timeDead;
	BOOL	bNoHealing;
	POSITION pMapPosite;
	CList <TObjectSkill *,TObjectSkill *>listskill;
	CList <CGoods *,CGoods *>listequip;
	CList <CGoods *,CGoods *>listrentequip;
	CList <TPawn *,TPawn *> listpawngoods;
	CList <CActiveObject *,CActiveObject *>listfightopp;

public:

	CActiveObject();
	virtual ~CActiveObject();
	void SetSkill(CString szEName, int nLevel = 0, int nScore = 0, CString szMapName = "");
	PObjectSkill GetTSkill(CString SkillName);
	int GetSkillLevel(CString SkillName);
	CString GetSkillMap(CString SkillName);
	CString GetAttackBaseSkill();
	TRetInfo RunSkillCom(CString szSkill, CString szCom, CActiveObject * lpTarget);

	void CheckGoods();
	void CheckGoods(POSITION pos);
	CGoods * GetGoods(char *szName);
	POSITION GetGoods(CGoods * lpFGoods);
	CGoods * GetClassGoods(int nKinds);
	TRetInfo RunGoodsCom(CString szGoods, CString szCom, CActiveObject * lpTarget);

	CString AddGoods(CGoods *lpEquip);
	CString SubGoods(CString szName);
	CString SetGoods(CGoods *lpEquip);
	int GetGoodCount(char *szName);
	int GetGoodIsNotArmedCount(char *szName);
	CGoods* GetGoodIsNotArmed(char *szName);
	CString SubGoodWhichIsNotArmed(char *szName);
	void DeleteTemp(CString szName);
	void SetTemp(CString szName, TMixed mixVal);
	void SetTemp(CString szName, int nValue);
	void SetTemp(CString szName, CString szValue);
	TMixed GetTemp(CString szName);
	void AddTemp(CString szName, int nValue);
	virtual void HitOb(CActiveObject *you, int &damage_bonus, CString &strRet, int nWhere);
	void SendMsgToAll(CString sMsg, CActiveObject *you = NULL);
	int  SendMsg(CString szMsg);
	virtual void DoHeartBeat();

	void ApplyCondition(CCondition * lpCondition);
	void ApplyCondition(int nKind, CString szName, int nVal, int nPower = 0);
	int  QueryCondition(CString szName);
	BOOL DeleteCondition(CString szName);

	int  GetMaxQi();
	bool ReceiveCure(int nQi=1);
	int  GetMaxJing();
	bool ReceiveJing(int nJing=1);
	void Unconcious(int nTime = 0);
	void Wake(void);
	void Die(void);
	void ReportStatusNum();
private:
	POSITION GetTTempPos(CString szName);
	CList <TTempVal *, TTempVal *>listtempval;
	POSITION GetConditionPos(CString szName);
	void DoAction();
	void UpdataCondition(CCondition * lpCondition);
	int UpdataPoison(CCondition * lpCondition);
	CList <CCondition *, CCondition *>listcondition;
	int nTick;
private:
	void RemoveAllEnemy();
};
BOOL DoAttack(CActiveObject *me, CActiveObject *you, CString &strRet, CString &szMsg);
BOOL Improve(CActiveObject *me, PObjectSkill lpTSkill, int number=1);
BOOL DoErrorLog(CActiveObject *kme, CActiveObject *kyou,int killlive);
bool DoEscape(CActiveObject *me, CString &strMapCName, CString &strMapEName);

#endif
