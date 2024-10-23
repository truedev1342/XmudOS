// Nsl_DaoXiang2.h: interface for the CNsl_DaoXiang2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NSL_DAOXIANG2_H__AE96486A_BE97_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NSL_DAOXIANG2_H__AE96486A_BE97_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"
#include "Nsl_Dao.h"

class CNsl_DaoXiang2 : public CNpc  
{
public:
	CNsl_DaoXiang2();
	virtual ~CNsl_DaoXiang2();
	virtual TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NSL_DAOXIANG2_H__AE96486A_BE97_11D3_B83E_0000E8A02173__INCLUDED_)
