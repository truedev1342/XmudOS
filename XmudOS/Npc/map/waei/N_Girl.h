// N_Girl.h: interface for the CN_Girl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_GIRL_H__5B2115C4_9CCD_11D3_ABF1_0000E8E25C21__INCLUDED_)
#define AFX_N_GIRL_H__5B2115C4_9CCD_11D3_ABF1_0000E8E25C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CN_Girl : public CNpc  
{
public:
	CN_Girl();
	virtual ~CN_Girl();
	// Spock +1
	TRetInfo DoAsk(CPlayerInfo *who, CString szName, CString szTarget);
	TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_N_GIRL_H__5B2115C4_9CCD_11D3_ABF1_0000E8E25C21__INCLUDED_)
