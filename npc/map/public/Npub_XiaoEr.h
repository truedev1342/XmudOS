// Npub_XiaoEr.h: interface for the CNpub_XiaoEr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPUB_XIAOER_H__63B0160C_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NPUB_XIAOER_H__63B0160C_BA0A_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

typedef struct XIAOER {
	int number;
	int count;
	CString whoami;
	XIAOER() {
		number=0;
		count=0;
	}
} XiaoEr;

class CNpub_XiaoEr : public CNpc  
{
public:
	XiaoEr *lpXiaoEr;
	CNpub_XiaoEr();
	virtual ~CNpub_XiaoEr();

};

#endif // !defined(AFX_NPUB_XIAOER_H__63B0160C_BA0A_11D3_B83E_0000E8A02173__INCLUDED_)
