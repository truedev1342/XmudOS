// MapClass.h: interface for the CMapClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPCLASS_H__BE503A81_477D_11D4_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_MAPCLASS_H__BE503A81_477D_11D4_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\MapInfo.h"

class CMapClass : public CBaseMap  
{
public:
	CMapClass();
	virtual ~CMapClass();
    void InitMap(char *szFileName);
};

#endif // !defined(AFX_MAPCLASS_H__BE503A81_477D_11D4_AAFF_0050BA00E0B0__INCLUDED_)
