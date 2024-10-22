// N_ChinYunWai.h: interface for the CN_ChinYunWai class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_N_CHINYUNWAI_H__0E646A85_018F_11D4_AAFF_0050BA00E0B0__INCLUDED_)
#define AFX_N_CHINYUNWAI_H__0E646A85_018F_11D4_AAFF_0050BA00E0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Npc.h"

class CN_ChinYunWai : public CNpc  
{
public:
	CN_ChinYunWai();
	virtual ~CN_ChinYunWai();
    TRetInfo DoAsk(CPlayerInfo *who, CString szName);
};

#endif // !defined(AFX_N_CHINYUNWAI_H__0E646A85_018F_11D4_AAFF_0050BA00E0B0__INCLUDED_)
