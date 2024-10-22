// JiuDaiClass.h: interface for the CJiuDaiClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JIUDAICLASS_H__AD77C7A2_F0ED_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_JIUDAICLASS_H__AD77C7A2_F0ED_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Goods.h"

class CJiuDaiClass : public CJiuDai  
{
public:
	CJiuDaiClass();
	virtual ~CJiuDaiClass();
    void InitJiuDai(char *szFileName);
};

#endif // !defined(AFX_JIUDAICLASS_H__AD77C7A2_F0ED_11D3_AAFF_0050BA00E0B0__INCLUDED_)
