// N_BiaoTou.h: interface for the CN_BiaoTou class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_BIAOTOU_H__3665E8C1_D9B6_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_N_BIAOTOU_H__3665E8C1_D9B6_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CN_BiaoTou : public CNpc  
{
public:
	CN_BiaoTou();
	virtual ~CN_BiaoTou();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_N_BIAOTOU_H__3665E8C1_D9B6_11D3_AAFF_0050BA00E0B0__INCLUDED_)
