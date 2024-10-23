// Npub_TuFeitou.h: interface for the CNpub_TuFeitou class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPUB_TUFEITOU_H__63B0160A_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NPUB_TUFEITOU_H__63B0160A_BA0A_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

typedef struct TUFEITOU {
	int number;
	int count;
	CString whoami;
	TUFEITOU() {
		number=0;
		count=0;
	}
} TuFeiTou;

class CNpub_TuFeitou : public CNpc  
{
public:
	TuFeiTou *lpTuFeiTou;
	CNpub_TuFeitou();
	virtual ~CNpub_TuFeitou();

};

#endif // !defined(AFX_NPUB_TUFEITOU_H__63B0160A_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
