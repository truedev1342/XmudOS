// N_YunBing.h: interface for the CN_YunBing class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_YUNBING_H__D1ADECA1_D994_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_N_YUNBING_H__D1ADECA1_D994_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

typedef struct YUNBING {
	int number;
	int count;
	CString whoami;
	YUNBING() {
		number=0;
		count=0;
	}
} YunBing;

class CN_YunBing : public CNpc  
{
public:
	YunBing *lpYunBing;
	CN_YunBing();
	virtual ~CN_YunBing();

};

#endif // !defined(AFX_N_YUNBING_H__D1ADECA1_D994_11D3_AAFF_0050BA00E0B0__INCLUDED_)
