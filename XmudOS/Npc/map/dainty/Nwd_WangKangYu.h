// Nwd_WangKangYu.h: interface for the CNwd_WangKangYu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NWD_WANGKANGYU_H__8CD16102_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_NWD_WANGKANGYU_H__8CD16102_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CNwd_WangKangYu : public CNpc  
{
public:
	CNwd_WangKangYu();
	virtual ~CNwd_WangKangYu();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NWD_WANGKANGYU_H__8CD16102_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_)
