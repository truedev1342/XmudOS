// Nzm_DiziW.h: interface for the CNzm_DiziW class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NZM_DIZIW_H__C2B86462_21D2_11D4_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_NZM_DIZIW_H__C2B86462_21D2_11D4_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CNzm_DiziW : public CNpc  
{
public:
	CNzm_DiziW();
	virtual ~CNzm_DiziW();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NZM_DIZIW_H__C2B86462_21D2_11D4_AAFF_0050BA00E0B0__INCLUDED_)
