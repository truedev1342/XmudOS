// N_Disciple.h: interface for the CN_Disciple class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_DISCIPLE_H__FD6A98A8_D7CF_11D3_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_N_DISCIPLE_H__FD6A98A8_D7CF_11D3_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

#define MAXLIMIT 10

class CN_Disciple : public CNpc  
{
public:
	// Spock start
	CString szLimit[MAXLIMIT];
	int nLimit[MAXLIMIT], nLimitCount;
	// Spock end
	CN_Disciple(char *szPath, char *szFile);
	virtual ~CN_Disciple();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
	TRetInfo DoApprentice(CPlayerInfo *who);
	void Init(char *szBuf);
};

#endif // !defined(AFX_N_DISCIPLE_H__FD6A98A8_D7CF_11D3_AAFF_0050BA00E0B0__INCLUDED_)
