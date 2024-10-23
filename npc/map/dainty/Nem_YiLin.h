// Nem_YiLin.h: interface for the CNem_YiLin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEM_YILIN_H__44944484_E91C_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_NEM_YILIN_H__44944484_E91C_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CNem_YiLin : public CNpc  
{
public:
	CNem_YiLin();
	virtual ~CNem_YiLin();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);

};

#endif // !defined(AFX_NEM_YILIN_H__44944484_E91C_11D3_AAFF_0050BA00E0B0__INCLUDED_)
