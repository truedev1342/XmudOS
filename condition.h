#if !defined(AFX_CONDITION_H__41E53661_AA2C_11D3_ABF1_0000E8E25C21__INCLUDED_)
#define AFX_CONDITION_H__41E53661_AA2C_11D3_ABF1_0000E8E25C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CActiveObject;

#define CK_
#define CK_normal	1
#define CK_poison	2
#define CK_yungong	3
#define CK_special	4

class CCondition  
{
public:
	int nKind;
	CString szName;
	int nTime;
	int nPower;
public:
	CCondition();
	virtual ~CCondition();
	int UpdataPoison(CActiveObject * lpMan);
};

int UpdataDrink(CCondition * lpCondition, CActiveObject * lpMan);
int UpdataIce(CCondition * lpCondition, CActiveObject * lpMan);
int UpdataYihan(CCondition * lpCondition, CActiveObject * lpMan);
int UpdataDuanchanghua(CCondition * lpCondition, CActiveObject * lpMan);
int UpdataRose(CCondition * lpCondition, CActiveObject * lpMan);
int UpdataSleepdurg(CCondition * lpCondition, CActiveObject * lpMan);
int UpdataSnake(CCondition * lpCondition, CActiveObject * lpMan);
int UpdataShengshifu(CCondition * lpCondition, CActiveObject * lpMan);
int UpdataXingxiustrike(CCondition * lpCondition, CActiveObject * lpMan);
int UpdataFreezeblood(CCondition * lpCondition, CActiveObject * lpMan);
int UpdataBandaged(CCondition * lpCondition, CActiveObject * lpMan);


void SpecialActEnd(CCondition * lpCondition, CActiveObject * lpMan);

#endif
