#if !defined(AFX_FIGHT_H__7AA41FC0_9366_11D3_BA84_0000E8A021D8__INCLUDED_)
#define AFX_FIGHT_H__7AA41FC0_9366_11D3_BA84_0000E8A021D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CFight  
{
public:
	CActiveObject *lpActiveObject;
	int	iRound;
	int nDelay;
public:
	CFight();
	virtual ~CFight();
	void DoFightProc();
	void DoKillProc();
};

#endif
