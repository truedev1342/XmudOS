// Nxx_WeaponMgr.h: interface for the CNxx_WeaponMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NXX_WEAPONMGR_H__8CD16104_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_NXX_WEAPONMGR_H__8CD16104_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CNxx_WeaponMgr : public CNpc  
{
public:
	CNxx_WeaponMgr();
	virtual ~CNxx_WeaponMgr();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NXX_WEAPONMGR_H__8CD16104_03D0_11D4_AAFF_0050BA00E0B0__INCLUDED_)
