
#if !defined(AFX_FLAGCLASS_H__A2F230C2_7D94_11D4_8111_0050BAED7201__INCLUDED_)
#define AFX_FLAGCLASS_H__A2F230C2_7D94_11D4_8111_0050BAED7201__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "Goods.h"

class CFlagClass : public CFlag  
{
public:
	CFlagClass();
	virtual ~CFlagClass();
	void InitFlag(char *szFileName);
};

#endif
