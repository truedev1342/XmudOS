// Ngb_Dizi.h: interface for the CNgb_Dizi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NGB_DIZI_H__8CD16103_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_NGB_DIZI_H__8CD16103_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CNgb_Dizi : public CNpc  
{
public:
	CNgb_Dizi();
	virtual ~CNgb_Dizi();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NGB_DIZI_H__8CD16103_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_)
