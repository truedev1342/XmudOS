// MapInfo.h: interface for the CMapInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPINFO_H__E87DDFA1_8569_11D3_BA84_0000E8A021D8__INCLUDED_)
#define AFX_MAPINFO_H__E87DDFA1_8569_11D3_BA84_0000E8A021D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\goods\goods\goods.h"

typedef struct tatMapExit
{
	CString szExitname;//出口的名稱
	CString szNexeMap;//對應的下個地圖的名稱
	CString szNextMapExitName;//對應的下個地圖的出口;
	CString	m_fPOSITION_X;//記錄地圖出口的位置
	CString	m_fPOSITION_Y;
}TMapExit;

class CNpc;
class CPlayerInfo;

class CBaseMap
{
public:
	CString szCName;
	CString szEName;
	CString szXFileName;
	// Spock start
	BOOL bPK;
	CString szFamily;
	int nStatus;
	CList <CGoods*,CGoods*> listequip;
	// Spock end
	CList <TMapExit*,TMapExit*> listexit;
	CList <CNpc*,CNpc*> listNpc;
	CList <CPlayerInfo*, CPlayerInfo*> listplayer;
public:
	CBaseMap();
	virtual ~CBaseMap();
	CString AddGoods(CGoods *lpEquip);
	CString SubGoods(CString szEName);
	CString SetGoods(CGoods *lpEquip);
};

extern CList <CBaseMap*,CBaseMap*>maplist;
void InitAllMap();

#endif // !defined(AFX_MAPINFO_H__E87DDFA1_8569_11D3_BA84_0000E8A021D8__INCLUDED_)
