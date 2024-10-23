// FoodClass.h: interface for the CFoodClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOODCLASS_H__AD77C7A1_F0ED_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_FOODCLASS_H__AD77C7A1_F0ED_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Goods.h"

class CFoodClass : public CFood  
{
public:
	CFoodClass();
	virtual ~CFoodClass();
    void InitFood(char *szFileName);
};

#endif // !defined(AFX_FOODCLASS_H__AD77C7A1_F0ED_11D3_AAFF_0050BA00E0B0__INCLUDED_)
