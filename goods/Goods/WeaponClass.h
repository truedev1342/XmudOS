// WeaponClass.h: interface for the CWeaponClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEAPONCLASS_H__ED9E89E2_EF62_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_WEAPONCLASS_H__ED9E89E2_EF62_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Goods.h"

class CWeaponClass : public CWeapon  
{
public:
	CWeaponClass();
	virtual ~CWeaponClass();
    void InitWeapon(char *szFileName);
};

#endif // !defined(AFX_WEAPONCLASS_H__ED9E89E2_EF62_11D3_AAFF_0050BA00E0B0__INCLUDED_)
