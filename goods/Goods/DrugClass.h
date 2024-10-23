#if !defined(AFX_DRUGCLASS_H__ED9E89E1_EF62_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_DRUGCLASS_H__ED9E89E1_EF62_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Goods.h"

class CDrugClass : public CDrug  
{
public:
	CDrugClass();
	virtual ~CDrugClass();
    void InitDrug(char *szFileName);
};

#endif
