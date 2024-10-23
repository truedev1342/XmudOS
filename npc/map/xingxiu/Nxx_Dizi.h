// Nxx_Dizi.h: interface for the CNxx_Dizi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NXX_DIZI_H__CC641402_B9E0_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NXX_DIZI_H__CC641402_B9E0_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CNxx_Dizi : public CNpc  
{
public:
	CNxx_Dizi();
	virtual ~CNxx_Dizi();
	virtual TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NXX_DIZI_H__CC641402_B9E0_11D3_B83E_0000E8A02173__INCLUDED_)
