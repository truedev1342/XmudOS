// Nem_YiHe.h: interface for the CNem_YiHe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEM_YIHE_H__CC641403_B9E0_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NEM_YIHE_H__CC641403_B9E0_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CNem_YiHe : public CNpc  
{
public:
	CNem_YiHe();
	virtual ~CNem_YiHe();
	virtual TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NEM_YIHE_H__CC641403_B9E0_11D3_B83E_0000E8A02173__INCLUDED_)
