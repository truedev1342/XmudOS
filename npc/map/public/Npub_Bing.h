// Npub_Bing.h: interface for the CNpub_Bing class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPUB_BING_H__A6EDA8C1_9C31_11D3_ABF1_0000E8E25C21__INCLUDED_)
#define AFX_NPUB_BING_H__A6EDA8C1_9C31_11D3_ABF1_0000E8E25C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

typedef struct BING {
	int number;
	int count;
	CString whoami;
	BING() {
		number=0;
		count=0;
	}
} Bing;


class CNpub_Bing : public CNpc  
{
public:
	Bing *lpBing;
	CNpub_Bing();
	virtual ~CNpub_Bing();
	// Nuke +1
	TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NPUB_BING_H__A6EDA8C1_9C31_11D3_ABF1_0000E8E25C21__INCLUDED_)
