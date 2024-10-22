// Skill.h: interface for the CSkill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKILL_H__6DB87100_86D0_11D3_BA84_0000E8A021D8__INCLUDED_)
#define AFX_SKILL_H__6DB87100_86D0_11D3_BA84_0000E8A021D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\ActiveObject.h"
#include "..\..\Goods\Goods\Goods.h"
#include "..\..\Common.h"


#define PARM ""

#define SCM_unarmed	0x1			//基本拳腳
#define SCM_dodge	0x2			//基本輕功
#define SCM_parry	0x4			//基本招架
#define SCM_force	0x8			//基本內功

#define SCM_blade	0x10		//基本刀法
#define SCM_sword	0x20		//基本劍法

#define SCM_club	0x40		//基本棒法,一般的是棒,短小而輕
#define SCM_short	0x80		//基本短兵，扇、峨嵋刺、短鉤之類
//#define SCM_stick	0x80		//基本棍法,只有尸體,骸骨等才是棍,很重
//#define SCM_staff	0x100		//基本杖法,長而輕

#define SCM_throwing 0x200		//基本暗器
#define SCM_whip	0x400		//基本鞭法
#define SCM_hammer	0x800		//基本錘法

//#define SCM_cuff	0x1000		//基本拳法
//#define SCM_strike	0x2000		//基本掌法
//#define SCM_hand	0x4000		//基本手法
//#define SCM_claw	0x8000		//基本爪法
//#define SCM_finger	0x10000		//基本指法

//no bit
#define ST_base		1			//基本技能,其他技能基礎,不用學可以練出來
#define ST_special  2			//特殊技能,可用于映射基本武功
#define ST_other	3			//其他技能,和其他武功沒有關系
//讀書寫字,道學心法,禪宗心法,溜須拍馬神功,基本毒技,妙手空空


#define SU_attack		0X0001		//這種技能能否攻擊
#define SU_dodge		0x0002
#define SU_parry		0x0004

#define random(n) ((n==0)?0:(rand()%(n)))
#define sum(base,n,d) ((n)*( 2*(base) + ( (n)-1 ) * (d) ) / 2 )
int NewRandom(int n,int base,int d);

typedef struct tagFeat
{
	int nSN;	//招式序號
	int nForce;
	int nDodge;
	int nParry;
	int nLevel;
	int nDamage;
	CString szDamageType;//受傷類型
	CString szName;		//這一招的名稱
	tagFeat()
	{
		nSN = 0;
		nForce = 0;
		nDodge = 0;
		nParry = 0;
		nLevel = 0;
		nDamage = 0;
		szDamageType = "";
		szName = "";
	}
}TFeat;

typedef struct NeedSkill{
	CString szEName;
	int nLevel;
	NeedSkill(){
		szEName = "";
		nLevel = 0;
	}
}TNeedSkill;

class CSkill  
{
public:
	typedef struct tagExert
	{
		CString szCom;
		CString (CSkill::*ComFunc)(CActiveObject *,CActiveObject *);
	}TExert;
public:
	CString szEName;
	CString szCName;
	CString szPerform;
	int nUsage;			//這種技能都可以用來干什麼
	int nType;			//這種技能的種類
	int nCanMap;		//都可以映射成什麼

	int		nNeedMax_force;	//內力
	int		nNeedMax_jingli;//精力
	int     nNeedWeapon;    //所需武器
    CList<TNeedSkill *,TNeedSkill *> listNeedSkill; //所需武功等級
	CList<TFeat *, TFeat *> listFeat; //每一招
	CList<TExert *, TExert*> listCom;
	int nDodge;			//映射成輕功的時候,有幾招
	int nParry;			//映射成招架的時候,有幾招
	int nUnarmedParry;	//敵方沒有兵器時的招架招數
public:
	CSkill();
	virtual ~CSkill();
    void Init(char *szFileName);
	virtual TRetInfo DoLearn(CActiveObject *who);
	virtual TRetInfo DoPractice(CActiveObject *who);
	virtual TFeat *	GetFeat(CActiveObject *who);
	virtual CString GetParryMsg(CActiveObject *you);
	virtual CString GetDodgeMsg(CActiveObject *who);
	virtual CString GetMaxName(CActiveObject *who);
	//virtual void HitOb(CActiveObject *me, CActiveObject *you, int &damage_bonus, CString &strRet, int nWhere);
};
void InitAllSkill();
void ReleaseSkill();
#endif // !defined(AFX_SKILL_H__6DB87100_86D0_11D3_BA84_0000E8A021D8__INCLUDED_)
