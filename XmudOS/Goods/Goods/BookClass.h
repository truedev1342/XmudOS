// BookClass.h: interface for the CBookClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOKCLASS_H__77BE8AE5_F1BF_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_BOOKCLASS_H__77BE8AE5_F1BF_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Goods.h"

class CBookClass : public CBook  
{
public:
	CBookClass();
	virtual ~CBookClass();
    void InitBook(char *szFileName);
};

#endif // !defined(AFX_BOOKCLASS_H__77BE8AE5_F1BF_11D3_AAFF_0050BA00E0B0__INCLUDED_)
