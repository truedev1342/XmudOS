// N_WeaponSeller.h: interface for the CN_WeaponSeller class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_WEAPONSELLER_H__2A563961_0ECF_11D4_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_N_WEAPONSELLER_H__2A563961_0ECF_11D4_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CN_WeaponSeller : public CNpc  
{
public:
	CN_WeaponSeller();
	virtual ~CN_WeaponSeller();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
	//TRetInfo DoAsk(CPlayerInfo *who, CString szName,CString szTarget);
};

#endif // !defined(AFX_N_WEAPONSELLER_H__2A563961_0ECF_11D4_AAFF_0050BA00E0B0__INCLUDED_)
