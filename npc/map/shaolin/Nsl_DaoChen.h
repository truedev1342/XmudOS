// Nsl_DaoChen.h: interface for the CNsl_DaoChen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NSL_DAOCHEN_H__AE964862_BE97_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NSL_DAOCHEN_H__AE964862_BE97_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"
#include "Nsl_Dao.h"

class CNsl_DaoChen : public CNpc  
{
public:
	CNsl_DaoChen();
	virtual ~CNsl_DaoChen();
	virtual TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NSL_DAOCHEN_H__AE964862_BE97_11D3_B83E_0000E8A02173__INCLUDED_)
