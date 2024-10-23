// Npub_TuFei.h: interface for the CNpub_TuFei class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPUB_TUFEI_H__63B01609_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NPUB_TUFEI_H__63B01609_BA0A_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

typedef struct TUFEI {
	int number;
	int count;
	CString whoami;
	TUFEI() {
		number=0;
		count=0;
	}
} TuFei;

class CNpub_TuFei : public CNpc  
{
public:
	TuFei *lpTuFei;
	CNpub_TuFei();
	virtual ~CNpub_TuFei();

};

#endif // !defined(AFX_NPUB_TUFEI_H__63B01609_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
