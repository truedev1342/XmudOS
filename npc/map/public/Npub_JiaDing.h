// Npub_JiaDing.h: interface for the CNpub_JiaDing class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPUB_JIADING_H__63B0160D_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NPUB_JIADING_H__63B0160D_BA0A_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

typedef struct JIADING {
	int number;
	int count;
	CString whoami;
	JIADING() {
		number=0;
		count=0;
	}
} JiaDing;


class CNpub_JiaDing : public CNpc  
{
public:
	JiaDing *lpJiaDing;
	CNpub_JiaDing();
	virtual ~CNpub_JiaDing();

};

#endif // !defined(AFX_NPUB_JIADING_H__63B0160D_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
