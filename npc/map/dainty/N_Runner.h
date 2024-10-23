// N_Runner.h: interface for the CN_Runner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_RUNNER_H__8CD16101_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_N_RUNNER_H__8CD16101_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CN_Runner : public CNpc  
{
public:
	CN_Runner();
	virtual ~CN_Runner();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_N_RUNNER_H__8CD16101_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_)
