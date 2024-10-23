// Nhs_ShiJie.h: interface for the CNhs_ShiJie class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NHS_SHIJIE_H__6B6E0583_B949_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NHS_SHIJIE_H__6B6E0583_B949_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CNhs_ShiJie : public CNpc  
{
public:
	CNhs_ShiJie();
	virtual ~CNhs_ShiJie();
	virtual TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NHS_SHIJIE_H__6B6E0583_B949_11D3_B83E_0000E8A02173__INCLUDED_)
