// N_Smith.h: interface for the CN_Smith class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_SMITH_H__9DC67A41_0ECA_11D4_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_N_SMITH_H__9DC67A41_0ECA_11D4_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CN_Smith : public CNpc  
{
public:
	CN_Smith();
	virtual ~CN_Smith();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
	//TRetInfo DoAsk(CPlayerInfo *who, CString szName,CString szTarget);
};

#endif // !defined(AFX_N_SMITH_H__9DC67A41_0ECA_11D4_AAFF_0050BA00E0B0__INCLUDED_)
