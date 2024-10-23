// Npub_YaYi.h: interface for the CNpub_YaYi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPUB_YAYI_H__63B0160B_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NPUB_YAYI_H__63B0160B_BA0A_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

typedef struct YAYI {
	int number;
	int count;
	CString whoami;
	YAYI() {
		number=0;
		count=0;
	}
} YaYi;

class CNpub_YaYi : public CNpc  
{
public:
	YaYi *lpYaYi;
	CNpub_YaYi();
	virtual ~CNpub_YaYi();

};

#endif // !defined(AFX_NPUB_YAYI_H__63B0160B_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
