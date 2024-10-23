// N_OldWoman2.h: interface for the CNpub_Bing class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_OLDWOMAN2_H__A6EDA8C1_9C31_11D3_ABF1_0000E8E25C21__INCLUDED_)
#define AFX_N_OLDWOMAN2_H__A6EDA8C1_9C31_11D3_ABF1_0000E8E25C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CN_OldWoman2 : public CNpc  
{
public:
	CN_OldWoman2();
	virtual ~CN_OldWoman2();
	// Nuke +1
	TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_N_OLDWOMAN2_H__A6EDA8C1_9C31_11D3_ABF1_0000E8E25C21__INCLUDED_)
