// BaseSkillClass.h: interface for the CBaseSkillClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASESKILLCLASS_H__5677B4C1_EAA7_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_BASESKILLCLASS_H__5677B4C1_EAA7_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Skill.h"

class CSkillClass : public CSkill  
{
public:
	CSkillClass();
	virtual ~CSkillClass();
    void Init(char *szFileName);
	virtual TRetInfo DoLearn(CActiveObject *who);
	virtual TRetInfo DoPractice(CActiveObject *who);
};

#endif // !defined(AFX_BASESKILLCLASS_H__5677B4C1_EAA7_11D3_AAFF_0050BA00E0B0__INCLUDED_)
