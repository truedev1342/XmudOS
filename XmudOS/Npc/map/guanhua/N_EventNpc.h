// N_EventNpc.h: interface for the CN_EventNpc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_EVENTNPC_H__3FA01081_485D_11D4_B50B_009027BE9DB6__INCLUDED_)
#define AFX_N_EVENTNPC_H__3FA01081_485D_11D4_B50B_009027BE9DB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\DAINTY\N_Disciple.h"
#include "CEvent.h"

class CN_EventNpc : public CN_Disciple
{
public:
	// int g_HasEvent;
	CNpcEvent* g_pNpcEvent;
	
	CN_EventNpc(char *szPath, char *szNpcFile);
	void LoadNpcEventFile(char *szNpcEventFile);
	TRetInfo DoAsk(CPlayerInfo *who, CString szName);
	TRetInfo DoEventLimit(CPlayerInfo *who, list<CEventAsk>::iterator iterEventAsk);
	TRetInfo DoEventRunWhenYes(CPlayerInfo *who, list<CEventLimit>::iterator iterLimit);
	TRetInfo DoEventRunWhenNo(CPlayerInfo *who, list<CEventLimit>::iterator iterLimit);
	TRetInfo DoDefaultEventRunWhenYes(CPlayerInfo *who, list<CEventAsk>::iterator iterEventAsk);
	TRetInfo DoDefaultEventRunWhenNo(CPlayerInfo *who, list<CEventAsk>::iterator iterEventAsk);
	CGoods* GetNewEventGood(CString szItemName, int nKind, int nCount);
	CString CheckGoodWeight(CPlayerInfo *who, list<CEventRun> &EventRunList);
	TRetInfo DoEventRun(CPlayerInfo *who, list<CEventRun>::iterator iterEventRun,  int &nStatusChange);

	virtual ~CN_EventNpc();
};

#endif // !defined(AFX_N_EVENTNPC_H__3FA01081_485D_11D4_B50B_009027BE9DB6__INCLUDED_)
