// Npub_JianKe.h: interface for the CNpub_JianKe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPUB_JIANKE_H__63B01604_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NPUB_JIANKE_H__63B01604_BA0A_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

typedef struct JIANKE {
	int number;
	int count;
	CString whoami;
	JIANKE() {
		number=0;
		count=0;
	}
} JianKe;

class CNpub_JianKe : public CNpc  
{
public:
	JianKe *lpJianKe;
	CNpub_JianKe();
	virtual ~CNpub_JianKe();

};

#endif // !defined(AFX_NPUB_JIANKE_H__63B01604_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
