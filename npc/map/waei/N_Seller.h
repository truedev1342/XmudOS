
#if !defined(AFX_N_SELLER_H__A6EDA8C1_9C31_11D3_ABF1_0000E8E25C21__INCLUDED_)
#define AFX_N_SELLER_H__A6EDA8C1_9C31_11D3_ABF1_0000E8E25C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "..\..\Npc.h"

class CN_Seller : public CNpc  
{
public:
	CN_Seller();
	virtual ~CN_Seller();
	TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif
