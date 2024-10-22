#if !defined(AFX_EQUIPCLASS_H__77BE8AE4_F1BF_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_EQUIPCLASS_H__77BE8AE4_F1BF_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Goods.h"

class CEquipClass : public CEquip  
{
public:
	CEquipClass();
	virtual ~CEquipClass();
    void InitEquip(char *szFileName);
};

#endif
