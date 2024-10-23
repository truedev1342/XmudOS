// Nhs_LaoDeNo.h: interface for the CNhs_LaoDeNo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NHS_LAODENO_H__44944483_E91C_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_NHS_LAODENO_H__44944483_E91C_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CNhs_ChinZuYang : public CNpc  
{
public:
	CNhs_ChinZuYang();
	virtual ~CNhs_ChinZuYang();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NHS_LAODENO_H__44944483_E91C_11D3_AAFF_0050BA00E0B0__INCLUDED_)
