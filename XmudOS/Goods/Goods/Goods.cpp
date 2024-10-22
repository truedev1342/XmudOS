#include "..\..\stdafx.h"
#include "Goods.h"

CGoods::CGoods()
{
	nNew = 0;
	nCount = 1;
	nRent = 0;
}

CGoods::~CGoods()
{

}

CString CGoods::GetSaveData()
{
	CString szTemp;
	if(nRent != 1)
		szTemp.Format("%s %d %d %d ",  lpGoods->szEName, lpGoods->nKinds,
			nNew, nCount);
	else
		szTemp.Format("rent %s %d %d %d ",  lpGoods->szEName, lpGoods->nKinds,
			nNew, nCount);
	return szTemp;
}

int CGoods::LoadData(int start, CStringList *data)
{
	if (data->FindIndex(start) == NULL) {
		nNew = 0;
	} else {
		nNew = atoi(data->GetAt(data->FindIndex(start)));
	}
	if (data->FindIndex(start+1) == NULL) {
		nCount = 0;
	} else {
		nCount = atoi(data->GetAt(data->FindIndex(start+1)));
	}
	return start+2;
}

CFood::CFood()
{
	nRemain = 1;
}

CFood::~CFood()
{

}

void CFood::DoEat(CPlayerInfo *who)
{
	return;
}

CString CFood::GetSaveData()
{
	CString szTemp;
	szTemp.Format("%d ", nRemain);
	return CGoods::GetSaveData() + szTemp;
}

int CFood::LoadData(int start, CStringList *data)
{
	start = CGoods::LoadData(start, data);
	if (data->FindIndex(start) == NULL) {
		nRemain = 0;
	} else {
		nRemain = atoi(data->GetAt(data->FindIndex(start)));
	}
	return start+1;
}

CEquip::CEquip()
{
	nWearWhere = 0;
}

CEquip::~CEquip()
{

}

CString CEquip::GetSaveData()
{
	CString szTemp;
	szTemp.Format("%d ", nWearWhere);
	return CGoods::GetSaveData() + szTemp;
}

int CEquip::LoadData(int start, CStringList *data)
{
	start = CGoods::LoadData(start, data);
	if (data->FindIndex(start) == NULL) {
		nWearWhere = 0;
	} else {
		nWearWhere = atoi(data->GetAt(data->FindIndex(start)));
	}
	return start+1;
}

CWeapon::CWeapon()
{
	bWield = FALSE;
}

CWeapon::~CWeapon()
{

}

CString CWeapon::GetSaveData()
{
	CString szTemp;
	int nTemp;
	if (bWield) {
		nTemp=1; 
	} else {
		nTemp=0;
	}
	szTemp.Format("%d ", nTemp);
	return CGoods::GetSaveData() + szTemp;
}

int CWeapon::LoadData(int start, CStringList *data)
{
	int nTemp;
	start = CGoods::LoadData(start, data);
	if (data->FindIndex(start) == NULL) {
		nTemp = 0;
	} else {
		nTemp = atoi(data->GetAt(data->FindIndex(start)));
	}
	if(nTemp==0) {
		bWield=FALSE;
	} else {
		bWield=TRUE;
	}
	return start+1;
}

CBook::CBook()
{
	
}

CBook::~CBook()
{

}

void CBook::DoRead(CPlayerInfo *me)
{
	return;
}

CDrug::CDrug()
{

}

CDrug::~CDrug()
{

}


CFlag::CFlag()
{

}

CFlag::~CFlag()
{

}


CJiuDai::CJiuDai()
{
	nRemain = 0;
	szLoadName = "ªÅ";
	nDurg = 0;
	nSupply = 0;
	nDrink = 30;
}

CJiuDai::~CJiuDai()
{
  listAddDurg.RemoveAll();
}

// Spock start
CString CJiuDai::GetSaveData()
{
	CString szTemp, szDrug;
	TAddDurg *lpDrug;
	int i;
	szTemp.Format("%s %d %d %d %d ", szLoadName, nRemain, nDurg, nSupply, nDrink);
	for (i=0; i<listAddDurg.GetCount(); i++) {
		lpDrug = listAddDurg.GetAt(listAddDurg.FindIndex(i));
		szDrug.Format("%s %d ", lpDrug->szEDurgName, lpDrug->nDurgNum);
		szTemp += szDrug;
	}
	return CGoods::GetSaveData() + szTemp;
}

int CJiuDai::LoadData(int start, CStringList *data)
{
	TAddDurg *lpDrug;
	start = CGoods::LoadData(start, data);
	if (data->GetCount() < start+5) {
		return 0;
	} else {
		szLoadName = data->GetAt(data->FindIndex(start));
		nRemain = atoi(data->GetAt(data->FindIndex(start+1)));
		nDurg = atoi(data->GetAt(data->FindIndex(start+2)));
		nSupply = atoi(data->GetAt(data->FindIndex(start+3)));
		nDrink = atoi(data->GetAt(data->FindIndex(start+4)));
		start +=5;
		while (data->GetCount() > start+2) {
			lpDrug = new TAddDurg;
			if (lpDrug == NULL) break;
			lpDrug->szEDurgName = data->GetAt(data->FindIndex(start));
			lpDrug->nDurgNum = atoi(data->GetAt(data->FindIndex(start+1)));
			start += 2;
		}
	}
	return start;
}

CSpecial::CSpecial()
{
	nMProperty = 0;
	nMAttr = 0;
	nNew = 0;
}

CSpecial::~CSpecial()
{

}


CString CSpecial::GetSaveData()
{
	CString szTemp;
	szTemp.Format("%d %d %d ", nMProperty, nMAttr, nNew);
	return CGoods::GetSaveData() + szTemp;
}

int CSpecial::LoadData(int start, CStringList *data)
{
	start = CGoods::LoadData(start, data);
	if (data->FindIndex(start) == NULL) {
		nMProperty = 0;
	} else {
		nMProperty = atoi(data->GetAt(data->FindIndex(start)));
	}
	if (data->FindIndex(start+1) == NULL) {
		nMAttr = 0;
	} else {
		nMAttr = atoi(data->GetAt(data->FindIndex(start+1)));
	}
	if (data->FindIndex(start+2) == NULL) {
		nNew = 0;
	} else {
		nNew = atoi(data->GetAt(data->FindIndex(start+2)));
	}
	return start+3;
}
// Spock end