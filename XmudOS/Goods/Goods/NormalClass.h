// NormalClass.h: interface for the CNormalClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NORMALCLASS_H__AD77C7A3_F0ED_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_NORMALCLASS_H__AD77C7A3_F0ED_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Goods.h"

class CNormalClass : public CGoods  
{
public:
	CNormalClass();
	virtual ~CNormalClass();
    void InitNormal(char *szFileName);
};

#endif // !defined(AFX_NORMALCLASS_H__AD77C7A3_F0ED_11D3_AAFF_0050BA00E0B0__INCLUDED_)
