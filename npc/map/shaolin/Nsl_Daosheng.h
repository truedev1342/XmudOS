// Nsl_Daosheng.h: interface for the CNsl_Daosheng class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NSL_DAOSHENG_H__C42E5161_B48B_11D3_ABF1_0000E8E25C21__INCLUDED_)
#define AFX_NSL_DAOSHENG_H__C42E5161_B48B_11D3_ABF1_0000E8E25C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"
#include "Nsl_Dao.h"

class CNsl_Daosheng : public CNpc  
{
public:
	CNsl_Daosheng();
	virtual ~CNsl_Daosheng();
	virtual TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NSL_DAOSHENG_H__C42E5161_B48B_11D3_ABF1_0000E8E25C21__INCLUDED_)
