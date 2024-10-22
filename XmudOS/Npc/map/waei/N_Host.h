// N_Host.h: interface for the CN_Host class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_HOST_H__5B2115D3_9CCD_11D3_ABF1_0000E8E25C21__INCLUDED_)
#define AFX_N_HOST_H__5B2115D3_9CCD_11D3_ABF1_0000E8E25C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CN_Host : public CNpc  
{
public:
	CN_Host();
	virtual ~CN_Host();
	virtual TRetInfo DoApprentice(CPlayerInfo *who);
};

#endif // !defined(AFX_N_HOST_H__5B2115D3_9CCD_11D3_ABF1_0000E8E25C21__INCLUDED_)
