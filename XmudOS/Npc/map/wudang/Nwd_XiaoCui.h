// Nwd_XiaoCui.h: interface for the CNwd_XiaoCui class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NWD_XIAOCUI_H__6B6E0582_B949_11D3_B83E_0000E8A02173__INCLUDED_)
#define AFX_NWD_XIAOCUI_H__6B6E0582_B949_11D3_B83E_0000E8A02173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CNwd_XiaoCui : public CNpc  
{
public:
	CNwd_XiaoCui();
	virtual ~CNwd_XiaoCui();
	virtual TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_NWD_XIAOCUI_H__6B6E0582_B949_11D3_B83E_0000E8A02173__INCLUDED_)
