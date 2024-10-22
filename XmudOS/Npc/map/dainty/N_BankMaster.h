// N_BankMaster.h: interface for the CN_BankMaster class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_BANKMASTER_H__14376F61_E5F2_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_N_BANKMASTER_H__14376F61_E5F2_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CN_BankMaster : public CNpc  
{
public:
	CN_BankMaster();
	virtual ~CN_BankMaster();
	TRetInfo DoAsk(CPlayerInfo *who, CString szName);
    TRetInfo DoAsk(CPlayerInfo *who, CString szName, CString szTarget);
};
//int QueryBankMoney(CPlayerInfo *who);
//int RefreshBankMoney(CPlayerInfo *who,int nMoney);

#endif // !defined(AFX_N_BANKMASTER_H__14376F61_E5F2_11D3_AAFF_0050BA00E0B0__INCLUDED_)
