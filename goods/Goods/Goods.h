// Goods.h: interface for the CGoods class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOODS_H__792349E3_8575_11D3_AF1B_0000E8E25C21__INCLUDED_)
#define AFX_GOODS_H__792349E3_8575_11D3_AF1B_0000E8E25C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern void AddRecordMsg(char *szMsg);

//goods kinds
#define GK_food			0x1
#define GK_equip		0x2
#define GK_weapon		0x4
#define GK_book			0x8
#define GK_drug			0x10
//#define GK_container   	0x20
#define GK_jiudai		0x40
#define GK_normal		0x80
#define GK_flag			0x100  

//物品屬性
#define GP_nodrop		0x0001//不能丟
#define GP_dirty		0x0002//對于食物來說是髒的
#define GP_lost			0x0004//只對于容器類,會不會丟小東西
#define GP_nosell		0x0008//不能賣
#define GP_noold		0x0010//不會變舊
#define GP_formale		0x0020//男人專用
#define GP_forfemale	0x0040//女人專用
#define GP_invisible    0x0080//不可視


//物品材質
#define GM_bone		0x1
#define GM_cloth	0x2
#define GM_leather	0x4
#define GM_iron		0x8
#define GM_steel	0x10
#define GM_gold		0x20
#define GM_paper	0x40
#define GM_wood		0x80
#define GM_silver	0x100

//在食物或酒中加入的藥
typedef struct tagAddDurg 
{
	CString szEDurgName;
	int nDurgNum;		//量,擴大了100倍
}TAddDurg;

class CPlayerInfo;

//基本物品類///////////////////////////////////
typedef struct tagGoods
{
	CString szCName;
	CString szEName;
	int nWeight;	//重量
	int nCubage;	//體積
	int nCost;		//價值
	int nUsage;		//屬性
	int nKinds;		//種類
	CString szUnit;			//單位
	CString szdescribe;		//物品描述
	int nDurable;	//耐用程度//開始, 新舊程度=耐用程度
	tagGoods()
	{
		szCName = "";
		szEName = "";
		nWeight = 0;
		nCubage = 0;
		nCost = 0;
		nUsage = 0;
		nKinds = 0;
		szUnit = "";
		szdescribe = "";
	}
}TGoods;

//基本物品類///////////////////////////////////
class CGoods  
{
public:
	TGoods * lpGoods;
	int nNew;	//新舊程度
	int nCount;	//物品個數
	int nRent;	//寄放物
public:
	CGoods();
	virtual ~CGoods();
	// Spock Start
	virtual CString GetSaveData();
	virtual int LoadData(int start, CStringList *data);
	// Spock End
};


//食物類///////////////////////////////////////
typedef struct tagFood
{
	int nSupply;	//飽多少
	int nDrink;		//止渴多少
	int nMaxRemain;	//開始有多少
	tagFood()
	{
		nSupply = 0;
		nDrink = 0;
		nMaxRemain = 0;
	}
}TFood;

//食物類///////////////////////////////////////
class CFood : virtual public CGoods  
{
public:
	TFood * lpFood;
	int nRemain;	//殘留多少 
	CList< TAddDurg *, TAddDurg *>listAddDurg;
public:
	CFood();
	virtual ~CFood();
	virtual void DoEat(CPlayerInfo *who);
	// Spock Start
	virtual CString GetSaveData();
	virtual int LoadData(int start, CStringList *data);
	// Spock End
};

//裝備類////////////////////////////////////////
//注意,這里和攻擊時的位置是相關的,請不要隨意修改值
#define EW_neck			0x0001//頸
#define EW_chest		0x0002//胸
#define EW_abdomen		0x0004//腹
#define EW_wrist		0x0008//腕
#define EW_knee			0x0010//膝
#define EW_head			0x0020//頭
#define EW_hand			0x0040//手
#define EW_foot			0x0080//腳
#define EW_body			0x0100//身

typedef struct tagEquip
{
	int nWhereWear;		//可以裝備那里(頭,頸)
	int nDodge;			//影響輕功
	int nAttack;		//增加攻擊值
	int nDefance;		//增加防御值
	int nDefanceForce;	//抗內力值
	int nMaterial;		//材質
	CString szWearMsg;	//裝備的語句
	CString szUnWearMsg;	//卸下的語句
	tagEquip()
	{
		nWhereWear = 0;
		nDodge = 0;
		nAttack = 0;
		nDefance = 0;
		nDefanceForce = 0;
		nMaterial = 0;
		szWearMsg = "";
		szUnWearMsg = "";
	}
}TEquip;

//裝備類////////////////////////////////////////
class CEquip : virtual public CGoods  
{
public:
	TEquip * lpEquip;
	int nWearWhere;		//穿到了那里
public:
	CEquip();
	virtual ~CEquip();
	//如果敵人打中
	//virtual void HitOb(CPlayerInfo *me, CPlayerInfo *you, int &damage_bonus, CString &strRet);
	// Spock Start
	virtual CString GetSaveData();
	virtual int LoadData(int start, CStringList *data);
	// Spock End
};

//武器類////////////////////////////////////////
#define WK_sword	0x1//劍
#define WK_stick	0x2//棒
#define WK_blade	0x4//刀
#define WK_club		0x8//棍
#define WK_short	0x10//短兵
#define WK_throwing	0x20//暗器
#define WK_whip		0x40//鞭
#define WK_hammer	0x80//錘

typedef struct tagWeapon
{
	int nKind;			//種類,如刀,槍,劍
	int nAttack;		//攻擊力
	int nDefance;		//防御力
	int nMaterial;		//材質
	CString szWieldMsg;	//裝備的語句
	CString szUnWieldMsg;	//卸下的語句
	tagWeapon()
	{
		nKind = 0;
		nAttack = 0;
		nDefance = 0;
		nMaterial = 0;
		szWieldMsg = _T("");
		szUnWieldMsg = _T("");
	}
}TWeapon;

//武器類////////////////////////////////////////
class CActiveObject;
class CWeapon : virtual public CGoods  
{
public:
	TWeapon * lpWeapon;	//指向武器屬性
	BOOL bWield;		//是否裝備
public:
	CWeapon();
	virtual ~CWeapon();
	//virtual void HitOb(CActiveObject *me, CActiveObject *you, int &damage_bonus, CString &strRet, int nWhere);
	// Spock Start
	virtual CString GetSaveData();
	virtual int LoadData(int start, CStringList *data);
	// Spock End
};

//書類//////////////////////////////////////////
class CSkill;

typedef struct tagSkill
{
	CString szNeedSkillEName;  //需武功
	int nNeedSkillLevel;       //等級
}TBookNeedSkill;

typedef struct tagBook
{
	CString szSkillEName;      //可學武功
	int nMaxLevel;             //最大等級
    int nNeedInt;              //需悟性
    int nNeedStr;              //需臂力
    int nNeedCon;              //需根骨
    int nNeedDex;              //需身法 
    int nNeedForce;            //需內力 
	CList <TBookNeedSkill *,TBookNeedSkill *> listNeedSkill;

	tagBook()
	{
		szSkillEName = "";
		nMaxLevel = 0;             //最大等級
        nNeedInt = 0;              //需悟性
        nNeedStr = 0;              //需臂力
        nNeedCon = 0;              //需根骨
        nNeedDex = 0;              //需身法 
        nNeedForce = 0;            //需內力 
	}
}TBook;

//書類//////////////////////////////////////////
class CBook : virtual public CGoods  
{
public:
	//CSkill * lpSkill;	//指向這本書所能學的武功
	TBook * lpBook;
public:
	CBook();
	virtual ~CBook();
	virtual void DoRead(CPlayerInfo *me);
};

//藥類/////////////////////////////////////////////
typedef struct tagDrug
{
	int nPower;		//1份的能力
	int nQi;
	int nJing;
	int nForce;
	int nJingli;
	int nStr;
	int nInt;
	int nCon;
	int nDex;
	tagDrug()
	{
		nPower = 0;
		nQi = 0;
		nJing = 0;
		nForce = 0;
		nJingli = 0;
		nStr = 0;
		nInt = 0;
		nCon = 0;
		nDex = 0;
	}
}TDrug;

//藥類/////////////////////////////////////////////
class CDrug : virtual public CGoods  
{
public:
	TDrug * lpDrug;
public:
	CDrug();
	virtual ~CDrug();
	//virtual void DoEat(CPlayerInfo *who, int nNum = 100);
};

typedef struct tagFlag
{
	tagFlag()
	{

	}
}TFlag;

class CFlag : virtual public CGoods  
{
public:
	TFlag * lpFlag;
public:
	CFlag();
	virtual ~CFlag();
};

/*
//容器類///////////////////////////////////////////
typedef struct tagContainer
{
	int nCanLoad;	//能裝多少個東西
	int nCanWeight;	//能裝最大多重
	int nCanCubage;	//能裝的最大體積
	int nMaterial;	//材質
	int nCanLoadKinds;	//能裝入什麼種類.
	tagContainer()
	{
		nCanLoad = 0;
		nCanWeight = 0;
		nCanCubage = 0;
		nMaterial = 0;
		nCanLoadKinds = 0;
	}
}TContainer;
//容器類///////////////////////////////////////////
class CContainer : virtual public CGoods  
{
public:
	TContainer * lpContainer;
	int nLoadWeight;	//裝的重量
	int nLoaded;	//裝了多少個
	CList< CGoods *, CGoods * >listGoods;
public:
	CContainer();
	virtual ~CContainer();
	virtual void DoLoad(CGoods *goods);
	virtual void DoTake(CGoods *goods);
	// Spock Start
	virtual CString GetSaveData();
	virtual int LoadData(int start, CStringList *data);
	// Spock End
};
*/
//酒袋類//////////////////////////////////////////
typedef struct tagJiuDai
{
	int nMaxRemain;//能裝多少東西
	int nQuality;//質量,品質//到什麼時候開始漏
	tagJiuDai()
	{
		nMaxRemain = 0;
		nQuality = 0;
	}
}TJiuDai;
//酒袋類//////////////////////////////////////////
class CJiuDai : virtual public CGoods  
{
public:
	TJiuDai * lpJiuDai;
	int nRemain;	//現在有多少
	CString szLoadName;	//裝的東西名稱
	int	nDurg;		//喝過之後增加多少酒精
	int nSupply;	//飽多少
	int nDrink;		//Spock Add 止渴多少
	CList< TAddDurg *, TAddDurg *>listAddDurg;
public:
	CJiuDai();
	virtual ~CJiuDai();
//	virtual void DoDrink(CPlayerInfo *who);
	// Spock Start
	virtual CString GetSaveData();
	virtual int LoadData(int start, CStringList *data);
	// Spock End
};

//特殊類(可以加入命令)////////////////////////////
typedef struct tagSpecial TSpecial;

class CSpecial : virtual public CGoods  
{
public:
	//特殊類中的命令鏈表結構
	typedef struct tagSpeclCommand 
	{
		CString szCom;
		CString (CSpecial::*ComFunc)(CActiveObject *, CActiveObject *);
	}TCommand;

public:
	TSpecial * lpSpecial;
	int nMProperty;
	int nMAttr;
	int nNew;
public:
	CSpecial();
	virtual ~CSpecial();
	// Spock Start
	virtual CString GetSaveData();
	virtual int LoadData(int start, CStringList *data);
	// Spock End
};

//特殊類(可以加入命令)////////////////////////////
typedef struct tagSpecial
{
	int nMaterial;		//材質
	CString szPropertiy;
	int nAttr;
	CList<CSpecial::TCommand *, CSpecial::TCommand *>listCom;
	tagSpecial()
	{
		nMaterial = 0;
		szPropertiy = "";
		nAttr = 0;
	}
}TSpecial;
///////////////////

void InitGoods();

//返回要得到的類的指針,輸入基類的地址,要得到的類的類型
//void * GetGoodsCPtr(CGoods * lpGoods, int nGoodsKind);

//下面兩個函數內部使用
//void * GetUnionPointer(CGoods * lpGoods, CString szEName);
//void * MovePointer(LPVOID p, int nMove);

CGoods * GetGoodsClass(CString szEName, int nKinds);
//goods
CFood * GetFoodClass(CString szName);
CEquip * GetEquipClass(CString szName);
CWeapon * GetWeaponClass(CString szName);
CBook * GetBookClass(CString szName);
CDrug * GetDrugClass(CString szName);
CFlag * GetFlagClass(CString szName);
//CContainer * GetContainerClass(CString szEName);
CJiuDai * GetJiuDaiClass(CString szName);
//CSpecial * GetSpecialClass(CString szEName);
//CGoods * GetUnionClass(CString szEName);
CGoods * GetNormalClass(CString szName);

// guanhua start 2000/07/28
int GetGoodWeight(CString szName);
// guanhua end  2000/07/28

void ReleaseGoods();

//CGoods * GetNormalClassByCName(CString szCName);
//CWeapon * GetWeaponClassByCName(CString szCName);
//CEquip * GetEquipClassByCName(CString szCName);
//CDrug * GetDrugClassByCName(CString szCName);
#endif // !defined(AFX_GOODS_H__792349E3_8575_11D3_AF1B_0000E8E25C21__INCLUDED_)
