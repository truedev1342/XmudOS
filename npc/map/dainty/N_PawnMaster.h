// N_PawnMaster.h: interface for the CN_PawnMaster class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_PAWNMASTER_H__44944482_E91C_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_N_PAWNMASTER_H__44944482_E91C_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"


class CN_PawnMaster : public CNpc  
{
public:
	CN_PawnMaster();
	virtual ~CN_PawnMaster();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
    TRetInfo DoAsk(CPlayerInfo *who, CString szName, CString szTarget);
};
//CList<TPawn *,TPawn *> * QueryPawnGoods(CPlayerInfo *who);
//int RefreshPawnGoods(CPlayerInfo *who,CList<TPawn *,TPawn *> *listgoods);
BOOL CheckOverdue(int year,int month,int day);
//void RemovePawnGoods(CList<TPawn *,TPawn *> *listgoods);
#endif // !defined(AFX_N_PAWNMASTER_H__44944482_E91C_11D3_AAFF_0050BA00E0B0__INCLUDED_)
