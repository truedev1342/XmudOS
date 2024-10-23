// Nsl_KongMin.h: interface for the CNsl_KongMin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NSL_KONGMIN_H__21C421A1_DA35_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_NSL_KONGMIN_H__21C421A1_DA35_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CNsl_KongMin : public CNpc  
{
public:
	CNsl_KongMin();
	virtual ~CNsl_KongMin();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NSL_KONGMIN_H__21C421A1_DA35_11D3_AAFF_0050BA00E0B0__INCLUDED_)
