#include "stdafx.h"
#include "Goods.h"

//dainty start
#include "NormalClass.h"
#include "FoodClass.h"
#include "DrugClass.h"
#include "JiuDaiClass.h"
#include "WeaponClass.h"
#include "EquipClass.h"
#include "BookClass.h"
#include "FlagClass.h" 

//dainty end
/*
//基本物品類
#include "Good\GGfire.h"
#include "Good\GGgoldleaf.h"
#include "Good\GGtongbo.h"
#include "Good\GGtonggu.h"
#include "Good\GGtonghao.h"
//食品類
#include "Food\GFbaicai.h"
#include "Food\GFbaozi.h"
#include "Food\GFbingtanghulu.h"
#include "Food\GFcake.h"
#include "Food\GFdoufu.h"
#include "Food\GFgourou.h"
#include "Food\GFhamigua.h"
#include "Food\GFhuasheng.h"
#include "Food\GFjiaohuaji.h"
#include "Food\GFkaoya.h"
#include "Food\GFmantou.h"
#include "Food\GFmianbing.h"
#include "Food\GFmiantiao.h"
#include "Food\GFnverxiang.h"
#include "Food\GFputao.h"
#include "Food\GFshuimitao.h"
#include "Food\GFyangrouchuan.h"
#include "Food\GFzongzi.h"
//裝備類型
#include "Equip\GEbaojia.h"
#include "Equip\GEbosirobe.h"
#include "Equip\GEbuqun.h"
#include "Equip\GEcaoxie.h"
#include "Equip\GEchangrobe.h"
#include "Equip\GEdudai.h"
#include "Equip\GEgraycloth.h"
#include "Equip\GEhuwan.h"
#include "Equip\GEhuyao.h"
#include "Equip\GEjiasha.h"
#include "Equip\GEjiezhi.h"
#include "Equip\GEjingangzhao.h"
#include "Equip\GEjinneck.h"
#include "Equip\GEjunfu.h"
#include "Equip\GElupixiaoxue.h"
#include "Equip\GElvluoqun.h"
#include "Equip\GEmianqun.h"
#include "Equip\GEniupidun.h"
#include "Equip\GEoldrobe.h"
#include "Equip\GEpibeixin.h"
#include "Equip\GEpinkcloth.h"
#include "Equip\GEpishoutao.h"
#include "Equip\GEpixue.h"
#include "Equip\GEqingrobe.h"
#include "Equip\GEqingsengyi.h"
#include "Equip\GEqingshaqun.h"
#include "Equip\GEruanjia.h"
#include "Equip\GEsengxie.h"
#include "Equip\GEshouzhuo.h"
#include "Equip\GEsilkcloth.h"
#include "Equip\GEtiebeixin.h"
#include "Equip\GEtiejia.h"
#include "Equip\GEtieshouzhang.h"
#include "Equip\GEtoukui.h"
#include "Equip\GEweibo.h"
#include "Equip\GEweiwuerrobe.h"
#include "Equip\GEwuzheneck.h"
#include "Equip\GExiuhuaxie.h"
#include "Equip\GEyayifu.h"
#include "Equip\GEyellowcloth.h"
#include "Equip\GEzhankui.h"
#include "Equip\GEzhanxue.h"
#include "Equip\GEzhitao.h"
//武器類型
#include "Weapon\GWbajiaochui.h"
#include "Weapon\GWchangbian.h"
#include "Weapon\GWchangjian.h"
#include "Weapon\GWchanzhang.h"
#include "Weapon\GWcommonbishou.h"
#include "Weapon\GWdadao.h"
#include "Weapon\GWdandao.h"
#include "Weapon\GWduanfu.h"
#include "Weapon\GWduanjian.h"
#include "Weapon\GWduoqingdao.h"
#include "Weapon\GWfeibiao.h"
#include "Weapon\GWfeidao.h"
#include "Weapon\GWfeihuangshi.h"
#include "Weapon\GWfuchen.h"
#include "Weapon\GWgangdao.h"
#include "Weapon\GWgangjian.h"
#include "Weapon\GWgangzhang.h"
#include "Weapon\GWheilongbian.h"
#include "Weapon\GWhuaban.h"
#include "Weapon\GWhudao.h"
#include "Weapon\GWjiedao.h"
#include "Weapon\GWlangyabang.h"
#include "Weapon\GWmuchui.h"
#include "Weapon\GWmudao.h"
#include "Weapon\GWmuyuchui.h"
#include "Weapon\GWnodropbishou.h"
#include "Weapon\GWqimeigun.h"
#include "Weapon\GWshigu.h"
#include "Weapon\GWthinjian.h"
#include "Weapon\GWtianmobang.h"
#include "Weapon\GWtiechui.h"
#include "Weapon\GWtiegun.h"
#include "Weapon\GWtielianzi.h"
#include "Weapon\GWtudao.h"
#include "Weapon\GWwandao.h"
#include "Weapon\GWwuqingjian.h"
#include "Weapon\GWxuantiejian.h"
#include "Weapon\GWyangbian.h"
#include "Weapon\GWyanyubian.h"
#include "Weapon\GWyaochu.h"
#include "Weapon\GWyitianjian.h"
#include "Weapon\GWzhubang.h"
#include "Weapon\GWzhujian.h"
#include "Weapon\GWzhuzhi.h"
//藥類
#include "Durg\GDdahuandan.h"
#include "Durg\GDdaliwan.h"
#include "Durg\GDguiyuandan.h"
#include "Durg\GDheshouwu.h"
#include "Durg\GDhuishenwan.h"
#include "Durg\GDjinchuangyao.h"
#include "Durg\GDlaoshanshen.h"
#include "Durg\GDmenghanyao.h"
#include "Durg\GDputizi.h"
#include "Durg\GDqingxinsan.h"
#include "Durg\GDxiaohuandan.h"
#include "Durg\GDxuelian.h"
#include "Durg\GDyangjingdan.h"
#include "Durg\GDzaishengwan.h"
//容器類型
//#include "Container\GCmabubag.h"
//其他類型
#include "Special\GSdongbula.h"
#include "Special\GSgongdebox.h"
#include "Special\GShorse.h"
#include "Special\GSkey.h"
#include "Special\GSmarrycard.h"
#include "Special\GSmianju.h"
#include "Special\GSmingbook.h"
//dainty
#include "Special\GSletter.h"
//酒袋類型
#include "JiuDai\GJDcuwan.h"
#include "JiuDai\GJDhuadiaobag.h"
#include "JiuDai\GJDmanaihu.h"
#include "JiuDai\GJDniupibag.h"
#include "JiuDai\GJDqinghulu.h"
#include "JiuDai\GJDqingshuihu.h"
#include "JiuDai\GJDzhuangyuanhong.h"
//聯合類型
#include "Union\GEWgoldhairpin.h"
#include "Union\GFWjitui.h"
*/


//static void * GetUnionPointer(CGoods * lpGoods, int nKind);
//static void * MovePointer(LPVOID p, int nMove);

void InitAllNormal(char *szGlobalPath);
void InitAllFlag(char *szGlobalPath); 
void InitAllFood(char *szGlobalPath);
void InitAllJiudai(char *szGlobalPath);
void InitAllDrug(char *szGlobalPath);
void InitAllWeapon(char *szGlobalPath);
void InitAllEquip(char *szGlobalPath);
void InitAllBook(char *szGlobalPath);

static CList<CFood *,CFood *> listFood;
static CList<CGoods *,CGoods *> listNormal;
static CList<CJiuDai *,CJiuDai *> listJiuDai;
static CList<CDrug *,CDrug *> listDrug;
static CList<CWeapon *,CWeapon *> listWeapon;
static CList<CEquip *,CEquip *> listEquip;
static CList<CBook *,CBook *> listBook;
static CList<CFlag *,CFlag *> listFlag;

extern char g_tszPathName[256];
void InitGoods()
{
	char pathname[50];

	strcpy(pathname, g_tszPathName);
	strcat(pathname,"\\goods");
	InitAllFood(pathname);
	InitAllNormal(pathname);
	InitAllJiudai(pathname);
	InitAllDrug(pathname);
	InitAllWeapon(pathname);
	InitAllEquip(pathname);
	InitAllBook(pathname);
	InitAllFlag(pathname);
/*
	//初始化基本物品類
	InitFire();
	InitGoldLeaf();
	InitTongBo();
	InitTongGu();
	InitTongHao();
	//初始化食品類
	InitBaiCai();
	InitBaoZi();
	InitBingTangHuLu();
	InitCake();
	InitDouFu();
	InitGouRou();
	InitHaMiGua();
	InitHuaSheng();
	InitJiaoHuaJi();
	InitKaoYa();
	InitManTou();
	InitMianBing();
	InitMianTiao();
	InitNvErXiang();
	InitPuTao();
	InitShuiMiTao();
	InitYangRouChuan();
	InitZongZi();
	//初始化裝備類
	InitBaoJia();
	InitBoSiRobe();
	InitBuQun();
	InitCaoXie();
	InitChangRobe();
	InitDuDai();
	InitGrayCloth();
	InitHuWan();
	InitHuYao();
	InitJiaSha();
	InitJieZhi();
	InitJinGangZhao();
	InitJinNeck();
	InitJunFu();
	InitLuPiXiaoXue();
	InitLvLuoQun();
	InitMianQun();
	InitNiuPiDun();
	InitOldRobe();
	InitPiBeiXin();
	InitPinkCloth();
	InitPiShouTao();
	InitPiXue();
	InitQingRobe();
	InitQingSengYi();
	InitQingShaQun();
	InitRuanJia();
	InitSengXie();
	InitShouZhuo();
	InitSilkCloth();
	InitTieBeiXin();
	InitTieJia();
	InitTieShouZhang();
	InitTouKui();
	InitWeiBo();
	InitWeiWuErRobe();
	InitWuZheNeck();
	InitXiuHuaXie();
	InitYaYiFu();
	InitYellowCloth();
	InitZhanKui();
	InitZhanXue();
	InitZhiTao();
	//初始化武器類
	InitBaJiaoChui();
	InitChangBian();
	InitChangJian();
	InitChanZhang();
	InitCommonBiShou();
	InitDaDao();
	InitDanDao();
	InitDuanFu();
	InitDuanJian();
	InitDuoQingDao();
	InitFeiBiao();
	InitFeiDao();
	InitFeiHuangShi();
	InitFuChen();
	InitGangDao();
	InitGangJian();
	InitGangZhang();
	InitHeiLongBian();
	InitHuaBan();
	InitHuDao();
	InitJieDao();
	InitLangYaBang();
	InitMuChui();
	InitMuDao();
	InitMuYuChui();
	InitNoDropBiShou();
	InitQiMeiGun();
	InitShiGu();
	InitThinJian();
	InitTianMoBang();
	InitTieChui();
	InitTieGun();
	InitTieLianZi();
	InitTuDao();
	InitWanDao();
	InitWuQingJian();
	InitXuanTieJian();
	InitYangBian();
	InitYanYuBian();
	InitYaoChu();
	InitYiTianJian();
	InitZhuBang();
	InitZhuJian();
	InitZhuZhi();
	//初始化容器類		
//	InitMaBuBag();
	//初始化特殊類
	InitDongBuLa();
	InitGongDeBox();
	InitHorse();
	InitKey();
	InitMarryCard();
	InitMianJu();
	InitMingBook();
//dainty
	InitLetter();
//dainty end
	//初始化酒袋類
	InitCuWan();
	InitHuaDiaoBag();
	InitMaNaiHu();
	InitNiuPiBag();
	InitQingHuLu();
	InitQingShuiHu();
	InitZhuangYuanHong();
	//初始化藥類
	InitDaHuanDan();
	InitDaLiWan();
	InitGuiYuanDan();
	InitHeShouWu();
	InitHuiShenWan();
	InitJinChuangYao();
	InitLaoShanShen();
	InitMengHanYao();
	InitPuTiZi();
	InitQingXinSan();
	InitXiaoHuanDan();
	InitXueLian();
	InitYangJingDan();
	InitZaiShengWan();
	//初始化聯合類
	InitGoldHairpin();
	InitJiTui();
	*/
}
void ReleaseGoods()
{
	listFood.RemoveAll();
    listNormal.RemoveAll();
	listJiuDai.RemoveAll();
	listDrug.RemoveAll();
	listWeapon.RemoveAll();
	listEquip.RemoveAll();
	listFlag.RemoveAll();
	//listBook.RemoveAll();
}
CGoods * GetGoodsClass(CString szEName, int nKinds)
{
	CGoods *lpGoods;
	switch(nKinds)
	{
	case GK_food:
		lpGoods = GetFoodClass(szEName);
		break;
	case GK_equip:
		lpGoods = GetEquipClass(szEName);
		break;
	case GK_weapon:
		lpGoods = GetWeaponClass(szEName);
		break;
	case GK_book:
		lpGoods = GetBookClass(szEName);
		break;
	case GK_drug:
		lpGoods = GetDrugClass(szEName);
		break;
	case GK_jiudai:
		lpGoods = GetJiuDaiClass(szEName);
		break;
	case GK_normal:
		lpGoods = GetNormalClass(szEName);
		break;
	case GK_flag:
		lpGoods = GetFlagClass(szEName);
		break;
	default:
		lpGoods = GetNormalClass(szEName);
		break;
	}
	return lpGoods;
}

CGoods * GetNormalClass(CString szName)
{
	CGoods *lpGoods=NULL,*lpNewGoods=NULL;

	for(int i=0;i<listNormal.GetCount();i++)
	{
		if(listNormal.GetAt(listNormal.FindIndex(i))->lpGoods->szEName==szName ||
			listNormal.GetAt(listNormal.FindIndex(i))->lpGoods->szCName==szName)
		{
			lpGoods = listNormal.GetAt(listNormal.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{
		lpNewGoods = new CGoods;
		lpNewGoods->lpGoods = lpGoods->lpGoods; 
        lpNewGoods->nNew = lpGoods->nNew;
		return lpNewGoods;
	}
	/*
	if(!stricmp(szEName,"fire"))
	{
		lpGoods = new CGGfire;
		return lpGoods;
	}
	else if(!stricmp(szEName,"goldleaf"))
	{
		lpGoods = new CGGgoldleaf;
		return lpGoods;
	}
	else if(!stricmp(szEName,"tongbo"))
	{
		lpGoods = new CGGtongbo;
		return lpGoods;
	}
	else if(!stricmp(szEName,"tonggu"))
	{
		lpGoods = new CGGtonggu;
		return lpGoods;
	}
	else if(!stricmp(szEName,"tonghao"))
	{
		lpGoods = new CGGtonghao;
		return lpGoods;
	}
	*/
	return NULL;

}


CFood * GetFoodClass(CString szName)
{
	CFood *lpGoods=NULL,*lpNewGoods=NULL;

	for(int i=0;i<listFood.GetCount();i++)
	{
		if(listFood.GetAt(listFood.FindIndex(i))->lpGoods->szEName==szName ||
			listFood.GetAt(listFood.FindIndex(i))->lpGoods->szCName==szName)
		{
			lpGoods = listFood.GetAt(listFood.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{
		lpNewGoods = new CFood;
		lpNewGoods->lpGoods = lpGoods->lpGoods;
		lpNewGoods->lpFood = lpGoods->lpFood;
        lpNewGoods->nNew = lpGoods->nNew;
		lpNewGoods->nRemain = lpGoods->nRemain;
		return lpNewGoods;
	}
	/*
	if(!stricmp(szEName,"baicai"))
	{
		lpGoods = new CGFbaicai;
		return lpGoods;
	}
	else if(!stricmp(szEName,"baozi"))
	{
		lpGoods = new CGFbaozi;
		return lpGoods;
	}
	else if(!stricmp(szEName,"bingtanghulu"))
	{
		lpGoods = new CGFbingtanghulu;
		return lpGoods;
	}

	else if(!stricmp(szEName,"cake"))
	{
		lpGoods = new CGFcake;
		return lpGoods;
	}
	else if(!stricmp(szEName,"doufu"))
	{
		lpGoods = new CGFdoufu;
		return lpGoods;
	}
	else if(!stricmp(szEName,"gourou"))
	{
		lpGoods = new CGFgourou;
		return lpGoods;
	}
	else if(!stricmp(szEName,"hamigua"))
	{
		lpGoods = new CGFhamigua;
		return lpGoods;
	}
	else if(!stricmp(szEName,"huasheng"))
	{
		lpGoods = new CGFhuasheng;
		return lpGoods;
	}
	else if(!stricmp(szEName,"jiaohuaji"))
	{
		lpGoods = new CGFjiaohuaji;
		return lpGoods;
	}
	else if(!stricmp(szEName,"kaoya"))
	{
		lpGoods = new CGFkaoya;
		return lpGoods;
	}
	else if(!stricmp(szEName,"mantou"))
	{
		lpGoods = new CGFmantou;
		return lpGoods;
	}
	else if(!stricmp(szEName,"mianbing"))
	{
		lpGoods = new CGFmianbing;
		return lpGoods;
	}
	else if(!stricmp(szEName,"miantiao"))
	{
		lpGoods = new CGFmiantiao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"shuimitao"))
	{
		lpGoods = new CGFshuimitao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"nverxiang"))
	{
		lpGoods = new CGFnverxiang;
		return lpGoods;
	}
	else if(!stricmp(szEName,"putao"))
	{
		lpGoods = new CGFputao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"yangrouchuan"))
	{
		lpGoods = new CGFyangrouchuan;
		return lpGoods;
	}
	else if(!stricmp(szEName,"zongzi"))
	{
		lpGoods = new CGFzongzi;
		return lpGoods;
	}*/
	return NULL;
	
}

CEquip * GetEquipClass(CString szName)
{
	CEquip *lpGoods=NULL,*lpNewGoods=NULL;

	for(int i=0;i<listEquip.GetCount();i++)
	{
		if(listEquip.GetAt(listEquip.FindIndex(i))->lpGoods->szEName ==szName ||
			listEquip.GetAt(listEquip.FindIndex(i))->lpGoods->szCName ==szName)
		{
			lpGoods = listEquip.GetAt(listEquip.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{
		lpNewGoods = new CEquip;
		lpNewGoods->lpGoods = lpGoods->lpGoods;
		lpNewGoods->lpEquip = lpGoods->lpEquip;
        lpNewGoods->nNew = lpGoods->nNew;
		return lpNewGoods;
	}
	/*
	if(!stricmp(szEName,"baojia"))
	{
		lpGoods = new CGEbaojia;
		return lpGoods;
	}
	else if(!stricmp(szEName,"bosirobe"))
	{
		lpGoods = new CGEbosirobe;
		return lpGoods;
	}
	else if(!stricmp(szEName,"buqun"))
	{
		lpGoods = new CGEbuqun;
		return lpGoods;
	}
	else if(!stricmp(szEName,"caoxie"))
	{
		lpGoods = new CGEcaoxie;
		return lpGoods;
	}
	else if(!stricmp(szEName,"changrobe"))
	{
		lpGoods = new CGEchangrobe;
		return lpGoods;
	}
	else if(!stricmp(szEName,"dudai"))
	{
		lpGoods = new CGEdudai;
		return lpGoods;
	}
	else if(!stricmp(szEName,"graycloth"))
	{
		lpGoods = new CGEgraycloth;
		return lpGoods;
	}
	else if(!stricmp(szEName,"huwan"))
	{
		lpGoods = new CGEhuwan;
		return lpGoods;
	}
	else if(!stricmp(szEName,"huyao"))
	{
		lpGoods = new CGEhuyao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"jiasha"))
	{
		lpGoods = new CGEjiasha;
		return lpGoods;
	}
	else if(!stricmp(szEName,"jiezhi"))
	{
		lpGoods = new CGEbuqun;
		return lpGoods;
	}
	else if(!stricmp(szEName,"jingangzhao"))
	{
		lpGoods = new CGEjingangzhao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"jinneck"))
	{
		lpGoods = new CGEjinneck;
		return lpGoods;
	}
	else if(!stricmp(szEName,"junfu"))
	{
		lpGoods = new CGEjunfu;
		return lpGoods;
	}
	else if(!stricmp(szEName,"lupixiaoxue"))
	{
		lpGoods = new CGElupixiaoxue;
		return lpGoods;
	}
	else if(!stricmp(szEName,"lvluoqun"))
	{
		lpGoods = new CGElvluoqun;
		return lpGoods;
	}
	else if(!stricmp(szEName,"mianqun"))
	{
		lpGoods = new CGEmianqun;
		return lpGoods;
	}
	else if(!stricmp(szEName,"niupidun"))
	{
		lpGoods = new CGEniupidun;
		return lpGoods;
	}
	else if(!stricmp(szEName,"oldrobe"))
	{
		lpGoods = new CGEoldrobe;
		return lpGoods;
	}
	else if(!stricmp(szEName,"pibeixin"))
	{
		lpGoods = new CGEpibeixin;
		return lpGoods;
	}
	else if(!stricmp(szEName,"pinkcloth"))
	{
		lpGoods = new CGEpinkcloth;
		return lpGoods;
	}
	else if(!stricmp(szEName,"pishoutao"))
	{
		lpGoods = new CGEpishoutao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"pixue"))
	{
		lpGoods = new CGEpixue;
		return lpGoods;
	}
	else if(!stricmp(szEName,"qingrobe"))
	{
		lpGoods = new CGEqingrobe;
		return lpGoods;
	}
	else if(!stricmp(szEName,"qingsengyi"))
	{
		lpGoods = new CGEqingsengyi;
		return lpGoods;
	}
	else if(!stricmp(szEName,"qingshaqun"))
	{
		lpGoods = new CGEqingshaqun;
		return lpGoods;
	}
	else if(!stricmp(szEName,"ruanjia"))
	{
		lpGoods = new CGEruanjia;
		return lpGoods;
	}
	else if(!stricmp(szEName,"sengxie"))
	{
		lpGoods = new CGEsengxie;
		return lpGoods;
	}
	else if(!stricmp(szEName,"shouzhuo"))
	{
		lpGoods = new CGEshouzhuo;
		return lpGoods;
	}
	else if(!stricmp(szEName,"silkcloth"))
	{
		lpGoods = new CGEsilkcloth;
		return lpGoods;
	}
	else if(!stricmp(szEName,"tiebeixin"))
	{
		lpGoods = new CGEtiebeixin;
		return lpGoods;
	}
	else if(!stricmp(szEName,"tiejia"))
	{
		lpGoods = new CGEtiejia;
		return lpGoods;
	}
	else if(!stricmp(szEName,"tieshouzhang"))
	{
		lpGoods = new CGEtieshouzhang;
		return lpGoods;
	}
	else if(!stricmp(szEName,"toukui"))
	{
		lpGoods = new CGEtoukui;
		return lpGoods;
	}
	else if(!stricmp(szEName,"weibo"))
	{
		lpGoods = new CGEweibo;
		return lpGoods;
	}
	else if(!stricmp(szEName,"weiwueirobe"))
	{
		lpGoods = new CGEweiwuerrobe;
		return lpGoods;
	}
	else if(!stricmp(szEName,"wuzheneck"))
	{
		lpGoods = new CGEwuzheneck;
		return lpGoods;
	}
	else if(!stricmp(szEName,"xiuhuaxie"))
	{
		lpGoods = new CGExiuhuaxie;
		return lpGoods;
	}
	else if(!stricmp(szEName,"yayifu"))
	{
		lpGoods = new CGEyayifu;
		return lpGoods;
	}
	else if(!stricmp(szEName,"yellowcloth"))
	{
		lpGoods = new CGEyellowcloth;
		return lpGoods;
	}
	else if(!stricmp(szEName,"zhankui"))
	{
		lpGoods = new CGEzhankui;
		return lpGoods;
	}
	else if(!stricmp(szEName,"zhanxue"))
	{
		lpGoods = new CGEzhanxue;
		return lpGoods;
	}
	else if(!stricmp(szEName,"zhitao"))
	{
		lpGoods = new CGEzhitao;
		return lpGoods;
	}*/
	return NULL;
}

CWeapon * GetWeaponClass(CString szName)
{
	CWeapon *lpGoods=NULL,*lpNewGoods=NULL;

    for(int i=0;i<listWeapon.GetCount();i++)
	{
		if(listWeapon.GetAt(listWeapon.FindIndex(i))->lpGoods->szEName==szName ||
			listWeapon.GetAt(listWeapon.FindIndex(i))->lpGoods->szCName==szName)
		{
			lpGoods = listWeapon.GetAt(listWeapon.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{
		lpNewGoods = new CWeapon;
		lpNewGoods->lpGoods = lpGoods->lpGoods; 
        lpNewGoods->lpWeapon = lpGoods->lpWeapon;
        lpNewGoods->nNew = lpGoods->nNew;
		return lpNewGoods;
	}
	/*
	if(!stricmp(szEName,"bajiaochui"))
	{
		lpGoods = new CGWbajiaochui;
		return lpGoods;
	}
	else if(!stricmp(szEName,"changbian"))
	{
		lpGoods = new CGWchangbian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"changjian"))
	{
		lpGoods = new CGWchangjian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"chanzhang"))
	{
		lpGoods = new CGWchanzhang;
		return lpGoods;
	}
	else if(!stricmp(szEName,"commonbishou"))
	{
		lpGoods = new CGWcommonbishou;
		return lpGoods;
	}
	else if(!stricmp(szEName,"dadao"))
	{
		lpGoods = new CGWdadao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"dandao"))
	{
		lpGoods = new CGWdandao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"duanfu"))
	{
		lpGoods = new CGWduanfu;
		return lpGoods;
	}
	else if(!stricmp(szEName,"duanjian"))
	{
		lpGoods = new CGWduanjian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"duoqingdao"))
	{
		lpGoods = new CGWduoqingdao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"feibiao"))
	{
		lpGoods = new CGWfeibiao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"feidao"))
	{
		lpGoods = new CGWfeidao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"feihuangshi"))
	{
		lpGoods = new CGWfeihuangshi;
		return lpGoods;
	}
	else if(!stricmp(szEName,"fuchen"))
	{
		lpGoods = new CGWfuchen;
		return lpGoods;
	}
	else if(!stricmp(szEName,"gangdao"))
	{
		lpGoods = new CGWgangdao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"gangjian"))
	{
		lpGoods = new CGWgangjian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"gangzhang"))
	{
		lpGoods = new CGWgangzhang;
		return lpGoods;
	}
	else if(!stricmp(szEName,"heilongbian"))
	{
		lpGoods = new CGWheilongbian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"huaban"))
	{
		lpGoods = new CGWhuaban;
		return lpGoods;
	}
	else if(!stricmp(szEName,"hudao"))
	{
		lpGoods = new CGWhudao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"jiedao"))
	{
		lpGoods = new CGWjiedao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"langyabang"))
	{
		lpGoods = new CGWlangyabang;
		return lpGoods;
	}
	else if(!stricmp(szEName,"muchui"))
	{
		lpGoods = new CGWmuchui;
		return lpGoods;
	}
	else if(!stricmp(szEName,"mudao"))
	{
		lpGoods = new CGWmudao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"muyuchui"))
	{
		lpGoods = new CGWmuyuchui;
		return lpGoods;
	}
	else if(!stricmp(szEName,"nodropbishou"))
	{
		lpGoods = new CGWnodropbishou;
		return lpGoods;
	}
	else if(!stricmp(szEName,"qimeigun"))
	{
		lpGoods = new CGWqimeigun;
		return lpGoods;
	}
	else if(!stricmp(szEName,"shigu"))
	{
		lpGoods = new CGWshigu;
		return lpGoods;
	}
	else if(!stricmp(szEName,"thinjian"))
	{
		lpGoods = new CGWthinjian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"tianmobang"))
	{
		lpGoods = new CGWtianmobang;
		return lpGoods;
	}
	else if(!stricmp(szEName,"tiechui"))
	{
		lpGoods = new CGWtiechui;
		return lpGoods;
	}
	else if(!stricmp(szEName,"tiegun"))
	{
		lpGoods = new CGWtiegun;
		return lpGoods;
	}
	else if(!stricmp(szEName,"tielianzi"))
	{
		lpGoods = new CGWtielianzi;
		return lpGoods;
	}
	else if(!stricmp(szEName,"tudao"))
	{
		lpGoods = new CGWtudao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"wandao"))
	{
		lpGoods = new CGWwandao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"wuqingjian"))
	{
		lpGoods = new CGWwuqingjian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"xuantiejian"))
	{
		lpGoods = new CGWxuantiejian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"yangbian"))
	{
		lpGoods = new CGWdandao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"yanyubian"))
	{
		lpGoods = new CGWyanyubian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"yaochu"))
	{
		lpGoods = new CGWyaochu;
		return lpGoods;
	}
	else if(!stricmp(szEName,"yitianjian"))
	{
		lpGoods = new CGWyitianjian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"zhubang"))
	{
		lpGoods = new CGWzhubang;
		return lpGoods;
	}
	else if(!stricmp(szEName,"zhujian"))
	{
		lpGoods = new CGWzhujian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"zhuzhi"))
	{
		lpGoods = new CGWzhuzhi;
		return lpGoods;
	}*/
	return NULL;
}

CBook * GetBookClass(CString szName)
{
	CBook * lpGoods=NULL,*lpNewGoods=NULL;

	for(int i=0;i<listBook.GetCount();i++)
	{
		if(listBook.GetAt(listBook.FindIndex(i))->lpGoods->szEName==szName ||
			listBook.GetAt(listBook.FindIndex(i))->lpGoods->szCName==szName)
		{
			lpGoods = listBook.GetAt(listBook.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{
		lpNewGoods = new CBook;
		lpNewGoods->lpGoods = lpGoods->lpGoods;
		lpNewGoods->lpBook = lpGoods->lpBook;
        lpNewGoods->nNew = lpGoods->nNew;
		return lpNewGoods;
	}
	return NULL;
}

CDrug * GetDrugClass(CString szName)
{
	CDrug * lpGoods=NULL,*lpNewGoods=NULL;

    for(int i=0;i<listDrug.GetCount();i++)
	{
		if(listDrug.GetAt(listDrug.FindIndex(i))->lpGoods->szEName==szName ||
			listDrug.GetAt(listDrug.FindIndex(i))->lpGoods->szCName==szName)
		{
			lpGoods = listDrug.GetAt(listDrug.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{
		lpNewGoods = new CDrug;
		lpNewGoods->lpGoods = lpGoods->lpGoods;
		lpNewGoods->lpDrug = lpGoods->lpDrug;
        lpNewGoods->nNew = lpGoods->nNew;
		return lpNewGoods;
	}
	/*
	if(!stricmp(szEName,"dahuandan"))
	{
		lpGoods = new CGDdahuandan;
		return lpGoods;
	}
	else if(!stricmp(szEName,"daliwan"))
	{
		lpGoods = new CGDdaliwan;
		return lpGoods;
	}
	else if(!stricmp(szEName,"guiyuandan"))
	{
		lpGoods = new CGDguiyuandan;
		return lpGoods;
	}
	else if(!stricmp(szEName,"heshouwu"))
	{
		lpGoods = new CGDheshouwu;
		return lpGoods;
	}
	else if(!stricmp(szEName,"huishenwan"))
	{
		lpGoods = new CGDhuishenwan;
		return lpGoods;
	}
	else if(!stricmp(szEName,"jinchuangyao"))
	{
		lpGoods = new CGDjinchuangyao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"laoshanshen"))
	{
		lpGoods = new CGDlaoshanshen;
		return lpGoods;
	}
	else if(!stricmp(szEName,"menghanyao"))
	{
		lpGoods = new CGDmenghanyao;
		return lpGoods;
	}
	else if(!stricmp(szEName,"putizi"))
	{
		lpGoods = new CGDputizi;
		return lpGoods;
	}
	else if(!stricmp(szEName,"qingxinsan"))
	{
		lpGoods = new CGDqingxinsan;
		return lpGoods;
	}
	else if(!stricmp(szEName,"xiaohuandan"))
	{
		lpGoods = new CGDxiaohuandan;
		return lpGoods;
	}
	else if(!stricmp(szEName,"xuelian"))
	{
		lpGoods = new CGDxuelian;
		return lpGoods;
	}
	else if(!stricmp(szEName,"yangjingdan"))
	{
		lpGoods = new CGDyangjingdan;
		return lpGoods;
	}
	else if(!stricmp(szEName,"zaishengwan"))
	{
		lpGoods = new CGDzaishengwan;
		return lpGoods;
	}*/
	return NULL;
}


CFlag * GetFlagClass(CString szName)
{
	CFlag * lpGoods=NULL,*lpNewGoods=NULL;

    for(int i=0;i<listFlag.GetCount();i++)
	{
		if(listFlag.GetAt(listFlag.FindIndex(i))->lpGoods->szEName==szName ||
			listFlag.GetAt(listFlag.FindIndex(i))->lpGoods->szCName==szName)
		{
			lpGoods = listFlag.GetAt(listFlag.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{	
		lpNewGoods = new CFlag;
		lpNewGoods->lpGoods = lpGoods->lpGoods;
		lpNewGoods->lpFlag = lpGoods->lpFlag;
        lpNewGoods->nNew = lpGoods->nNew;
		return lpNewGoods;
	}

	return NULL;
}

/*CContainer * GetContainerClass(CString szEName)
{
	CContainer * lpGoods;
	if(!stricmp(szEName,"mabubag"))
	{
		lpGoods = new CGCmabubag;
		return lpGoods;
	}
	return NULL;
}*/

CJiuDai * GetJiuDaiClass(CString szName)
{
	CJiuDai *lpGoods=NULL,*lpNewGoods=NULL;

    for(int i=0;i<listJiuDai.GetCount();i++)
	{
		if(listJiuDai.GetAt(listJiuDai.FindIndex(i))->lpGoods->szEName==szName ||
			listJiuDai.GetAt(listJiuDai.FindIndex(i))->lpGoods->szCName==szName)
		{
			lpGoods = listJiuDai.GetAt(listJiuDai.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{
		lpNewGoods = new CJiuDai;
		lpNewGoods->lpGoods = lpGoods->lpGoods;
		lpNewGoods->lpJiuDai = lpGoods->lpJiuDai;
        lpNewGoods->nNew = lpGoods->nNew;
		lpNewGoods->nDrink = lpGoods->nDrink;
		return lpNewGoods;
	}
	/*
	if(!stricmp(szEName,"cuwan"))
	{
		lpGoods = new CGJDcuwan;
		return lpGoods;
	}
	else if(!stricmp(szEName,"huadiaobag"))
	{
		lpGoods = new CGJDhuadiaobag;
		return lpGoods;
	}
	else if(!stricmp(szEName,"manaihu"))
	{
		lpGoods = new CGJDmanaihu;
		return lpGoods;
	}
	else if(!stricmp(szEName,"niupibag"))
	{
		lpGoods = new CGJDniupibag;
		return lpGoods;
	}
	else if(!stricmp(szEName,"qinghulu"))
	{
		lpGoods = new CGJDqinghulu;
		return lpGoods;
	}
	else if(!stricmp(szEName,"qingshuihu"))
	{
		lpGoods = new CGJDqingshuihu;
		return lpGoods;
	}
	else if(!stricmp(szEName,"zhuangyuanhong"))
	{
		lpGoods = new CGJDzhuangyuanhong;
		return lpGoods;
	}
*/
	return NULL;
}
/*
CSpecial * GetSpecialClass(CString szEName)
{
	CSpecial * lpGoods;
	if(!stricmp(szEName,"dongbula"))
	{
		lpGoods = new CGSdongbula;
		return lpGoods;
	}
	else if(!stricmp(szEName,"gongdebox"))
	{
		lpGoods = new CGSgongdebox;
		return lpGoods;
	}
	else if(!stricmp(szEName,"horse"))
	{
		lpGoods = new CGShorse;
		return lpGoods;
	}
	else if(!stricmp(szEName,"DoorKey"))
	{
		lpGoods = new CGSkey;
		return lpGoods;
	}
	else if(!stricmp(szEName,"marrycard"))
	{
		lpGoods = new CGSmarrycard;
		return lpGoods;
	}
	else if(!stricmp(szEName,"mianju"))
	{
		lpGoods = new CGSmianju;
		return lpGoods;
	}
	else if(!stricmp(szEName,"mingbook"))
	{
		lpGoods = new CGSmingbook;
		return lpGoods;
	}
	else if(!stricmp(szEName,"letter"))
	{
		lpGoods = new CGSletter;
		return lpGoods;
	}

	return NULL;
}

CGoods * GetUnionClass(CString szEName)
{
	CGoods * lpGoods;
	if(!stricmp(szEName,"GoldHairpin"))
	{
		void * lpvoid;
		lpvoid = new CGEWgoldhairpin;
		lpGoods = (CGEWgoldhairpin *)lpvoid;
		return lpGoods;
	}
	else if(!stricmp(szEName,"jitui"))
	{
		lpGoods = new CGFWjitui;
		return lpGoods;
	}

	return NULL;
}
*/
//返回要得到的類的指針,輸入基類的地址,要得到的類的類型
/*void * GetGoodsCPtr(CGoods * lpGoods, int nGoodsKind)
{
	if( lpGoods == NULL )
	{
		return NULL;
	}
	if(!(nGoodsKind & 0xff))
	{
		TRACE("輸入的類型錯誤,沒有這種類型");
		return NULL;
	}
	if(!(lpGoods->lpGoods->nKinds & nGoodsKind))
	{
		TRACE("這個基類不包含所需的類型.");
		return NULL;
	}
	if(lpGoods->lpGoods->nKinds = nGoodsKind)
	{
		switch(lpGoods->lpGoods->nKinds)
		{
		case GK_food:
			return MovePointer((void *)lpGoods, -0x2c);
		case GK_jiudai:
			return MovePointer((void *)lpGoods, -0x38);
		case GK_equip:
			return MovePointer((void *)lpGoods, -0x10);
		case GK_weapon:
			return MovePointer((void *)lpGoods, -0x10);
		default:
			return MovePointer((void *)lpGoods, -0x10);
		}
	}
	//else
		//return GetUnionPointer(lpGoods, nGoodsKind);
}

void * MovePointer(LPVOID p, int nMove)
{
	unsigned char *lpTmp;
	lpTmp = (unsigned char *)p;
	lpTmp += nMove;
	return (void *)lpTmp;
}*/
/*
void * GetUnionPointer(CGoods * lpGoods, int nKind)
{
	unsigned char *pBase = NULL, *pOff = NULL;
	unsigned char *pOrg;
	if(!stricmp(lpGoods->lpGoods->szEName, "GoldHairpin"))
	{
		CGEWgoldhairpin * lpGoldHairpin;
		lpGoldHairpin = new CGEWgoldhairpin;
		pBase = (unsigned char *)(CGoods *)lpGoldHairpin;
		if(nKind == GK_weapon)
		{
			pOff = (unsigned char *)(CWeapon *)lpGoldHairpin;
		}
		else if(nKind == GK_equip)
		{
			pOff = (unsigned char *)(CEquip *)lpGoldHairpin;
		}
		else 
		{
			TRACE("要得到的類的類型錯誤![%x]",nKind);
			return NULL;
		}
		delete lpGoldHairpin;
	}
	else if(!stricmp(lpGoods->lpGoods->szEName, "jitui"))
	{
		CGFWjitui * lpJiTui;
		lpJiTui = new CGFWjitui;
		pBase = (unsigned char *)(CGoods *)lpJiTui;
		if(nKind == GK_weapon)
		{
			pOff = (unsigned char *)(CWeapon *)lpJiTui;
		}
		else if(nKind == GK_food)
		{
			pOff = (unsigned char *)(CFood *)lpJiTui;
		}
		else 
		{
			TRACE("要得到的類的類型錯誤![%x]",nKind);
			return NULL;
		}
		delete lpJiTui;
	}
	else
	{
		TRACE("不認識這種聯合類型[%s]",lpGoods->lpGoods->szEName);
		return NULL;
	}
	if((pOff == NULL)||(pBase == NULL))
	{
		TRACE("得到類地址時內存出錯!");
		return NULL;
	}
	pOrg = (unsigned char *)lpGoods;
	pOrg += pOff - pBase;
	return pOrg;
}*/
void InitAllNormal(char *szGlobalPath)
{
	CNormalClass *lpNormal;
	FILE *fp;
	char szLocalPath[100],filename[100],temp[30];
	
	strcpy(szLocalPath,szGlobalPath);
	strcat(szLocalPath,"\\normal\\");
	strcpy(filename,szLocalPath);
	strcat(filename,"_normal.txt");
	if((fp=fopen(filename,"r"))!=NULL)
	{
        while(fscanf(fp,"%s",temp)!=EOF)
		{
		    strcpy(filename,szLocalPath);
			strcat(filename,temp);
			lpNormal = new CNormalClass;
            lpNormal->InitNormal(filename);	
			listNormal.AddTail(lpNormal);
		}
		fclose(fp);
	}
}
void InitAllFood(char *szGlobalPath)
{
	FILE *fp;
	CFoodClass *lpFood; 
	char szLocalPath[100],filename[100],temp[30];
	
	strcpy(szLocalPath,szGlobalPath);
	strcat(szLocalPath,"\\food\\");
	strcpy(filename,szLocalPath);
	strcat(filename,"_food.txt");
	if((fp=fopen(filename,"r"))!=NULL)
	{
        while(fscanf(fp,"%s",temp)!=EOF)
		{
		    strcpy(filename,szLocalPath);
			strcat(filename,temp);
            lpFood = new CFoodClass;
			lpFood->InitFood(filename);
			if(lpFood!=NULL) listFood.AddTail(lpFood);
		}
		fclose(fp);
	}
}
void InitAllJiudai(char *szGlobalPath)
{
	CJiuDaiClass *lpJiuDai;
	FILE *fp;
	char szLocalPath[100],filename[100],temp[30];
	
	strcpy(szLocalPath,szGlobalPath);
	strcat(szLocalPath,"\\jiudai\\");
	strcpy(filename,szLocalPath);
	strcat(filename,"_jiudai.txt");
	if((fp=fopen(filename,"r"))!=NULL)
	{
        while(fscanf(fp,"%s",temp)!=EOF)
		{
		    strcpy(filename,szLocalPath);
			strcat(filename,temp);
            lpJiuDai = new CJiuDaiClass;	
			lpJiuDai->InitJiuDai(filename);
			if(lpJiuDai!=NULL) listJiuDai.AddTail(lpJiuDai);
		}
		fclose(fp);
	}
}
void InitAllDrug(char *szGlobalPath)
{
	CDrugClass *lpDrug;
	FILE *fp;
	char szLocalPath[100],filename[100],temp[30];
	
	strcpy(szLocalPath,szGlobalPath);
	strcat(szLocalPath,"\\drug\\");
	strcpy(filename,szLocalPath);
	strcat(filename,"_drug.txt");
	if((fp=fopen(filename,"r"))!=NULL)
	{
        while(fscanf(fp,"%s",temp)!=EOF)
		{
		    strcpy(filename,szLocalPath);
			strcat(filename,temp);
            lpDrug = new CDrugClass;
			lpDrug->InitDrug(filename);
			if(lpDrug!=NULL) listDrug.AddTail(lpDrug);
		}
		fclose(fp);
	}
}


void InitAllFlag(char *szGlobalPath)
{
	CFlagClass *lpFlag;
	FILE *fp;
	char szLocalPath[100],filename[100],temp[30];
	
	strcpy(szLocalPath,szGlobalPath);
	strcat(szLocalPath,"\\flag\\");
	strcpy(filename,szLocalPath);
	strcat(filename,"_flag.txt");
	if((fp=fopen(filename,"r"))!=NULL)
	{
        while(fscanf(fp,"%s",temp)!=EOF)
		{
		    strcpy(filename,szLocalPath);
			strcat(filename,temp);
            lpFlag = new CFlagClass;
			lpFlag->InitFlag(filename);
			if(lpFlag!=NULL) listFlag.AddTail(lpFlag);
		}
		fclose(fp);
	}
}

void InitAllWeapon(char *szGlobalPath)
{
	CWeaponClass *lpWeapon;
	FILE *fp;
	char szLocalPath[100],filename[100],temp[30];
	
	strcpy(szLocalPath,szGlobalPath);
	strcat(szLocalPath,"\\weapon\\");
	strcpy(filename,szLocalPath);
	strcat(filename,"_weapon.txt");
	if((fp=fopen(filename,"r"))!=NULL)
	{
        while(fscanf(fp,"%s",temp)!=EOF)
		{
		    strcpy(filename,szLocalPath);
			strcat(filename,temp);
            lpWeapon = new CWeaponClass;
			lpWeapon->InitWeapon(filename);
			if(lpWeapon!=NULL) listWeapon.AddTail(lpWeapon);
		}
		fclose(fp);
	}
}
void InitAllEquip(char *szGlobalPath)
{
	CEquipClass *lpEquip;
	FILE *fp;
	char szLocalPath[100],filename[100],temp[30];
	
	strcpy(szLocalPath,szGlobalPath);
	strcat(szLocalPath,"\\equip\\");
	strcpy(filename,szLocalPath);
	strcat(filename,"_equip.txt");
	if((fp=fopen(filename,"r"))!=NULL)
	{
        while(fscanf(fp,"%s",temp)!=EOF)
		{
		    strcpy(filename,szLocalPath);
			strcat(filename,temp);
            lpEquip = new CEquipClass;
			lpEquip->InitEquip(filename);
			if(lpEquip!=NULL) listEquip.AddTail(lpEquip);
		}
		fclose(fp);
	}
}
void InitAllBook(char *szGlobalPath)
{
	CBookClass *lpBook;
	FILE *fp;
	char szLocalPath[100],filename[100],temp[30];
	
	strcpy(szLocalPath,szGlobalPath);
	strcat(szLocalPath,"\\book\\");
	strcpy(filename,szLocalPath);
	strcat(filename,"_book.txt");
	if((fp=fopen(filename,"r"))!=NULL)
	{
        while(fscanf(fp,"%s",temp)!=EOF)
		{
		    strcpy(filename,szLocalPath);
			strcat(filename,temp);
            lpBook = new CBookClass;
			lpBook->InitBook(filename);
			if(lpBook!=NULL) listBook.AddTail(lpBook);
		}
		fclose(fp);
	}
}
/*
CEquip * GetEquipClassByCName(CString szCName)
{
	CEquip *lpGoods=NULL,*lpNewGoods=NULL;

	for(int i=0;i<listEquip.GetCount();i++)
	{
		if(listEquip.GetAt(listEquip.FindIndex(i))->lpGoods->szCName==szCName)
		{
			lpGoods = listEquip.GetAt(listEquip.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{
		lpNewGoods = new CEquip;
		lpNewGoods->lpGoods = lpGoods->lpGoods; 
		lpNewGoods->lpEquip = lpGoods->lpEquip;
        lpNewGoods->nNew = lpGoods->nNew;
		return lpNewGoods;
	}
	return NULL;
}
CWeapon * GetWeaponClassByCName(CString szCName)
{
	CWeapon * lpGoods=NULL,*lpNewGoods=NULL;

    for(int i=0;i<listWeapon.GetCount();i++)
	{
		if(listWeapon.GetAt(listWeapon.FindIndex(i))->lpGoods->szCName==szCName)
		{
			lpGoods = listWeapon.GetAt(listWeapon.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{
		lpNewGoods = new CWeapon;
		lpNewGoods->lpGoods = lpGoods->lpGoods; 
        lpNewGoods->lpWeapon = lpGoods->lpWeapon;
        lpNewGoods->nNew = lpGoods->nNew;
		return lpNewGoods;
	}
	return NULL;
}
CGoods * GetNormalClassByCName(CString szCName)
{
	CGoods *lpGoods=NULL,*lpNewGoods=NULL;

	for(int i=0;i<listNormal.GetCount();i++)
	{
		if(listNormal.GetAt(listNormal.FindIndex(i))->lpGoods->szCName==szCName)
		{
			lpGoods = listNormal.GetAt(listNormal.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{
		lpNewGoods = new CGoods;
		lpNewGoods->lpGoods = lpGoods->lpGoods; 
        lpNewGoods->nNew = lpGoods->nNew;
		return lpNewGoods;
	}
	return NULL;
}
CDrug * GetDrugClassByCName(CString szCName)
{
	CDrug *lpGoods,*lpNewGoods;

    for(int i=0;i<listDrug.GetCount();i++)
	{
		if(listDrug.GetAt(listDrug.FindIndex(i))->lpGoods->szCName==szCName)
		{
			lpGoods = listDrug.GetAt(listDrug.FindIndex(i));
			break;
		}
	}
	if(lpGoods!=NULL)
	{ 
		lpNewGoods = new CDrug;
		lpNewGoods->lpGoods = lpGoods->lpGoods; 
		lpNewGoods->lpDrug = lpGoods->lpDrug;
        lpNewGoods->nNew = lpGoods->nNew;
		return lpNewGoods;
	}
	return NULL;
}
*/

// guanhua start 2000/07/28
int GetGoodWeight(CString szName)
{
	// return the weight of Good per unit after giving Chinese name or English name
	// return 0 if Giving a invalid name

	int i = 0;

	// Food
	for(i = 0; i < listFood.GetCount(); i++)
	{
		if(listFood.GetAt(listFood.FindIndex(i))->lpGoods->szEName == szName ||
			listFood.GetAt(listFood.FindIndex(i))->lpGoods->szCName == szName)
		{
			return listFood.GetAt(listFood.FindIndex(i))->lpGoods->nWeight;
		}
	}

	// Normal
	for(i = 0; i < listNormal.GetCount(); i++)
	{
		if(listNormal.GetAt(listNormal.FindIndex(i))->lpGoods->szEName == szName ||
			listNormal.GetAt(listNormal.FindIndex(i))->lpGoods->szCName == szName)
		{
			return listNormal.GetAt(listNormal.FindIndex(i))->lpGoods->nWeight;
		}
	}

	// JiuDai
	for(i = 0; i < listJiuDai.GetCount(); i++)
	{
		if(listJiuDai.GetAt(listJiuDai.FindIndex(i))->lpGoods->szEName == szName ||
			listJiuDai.GetAt(listJiuDai.FindIndex(i))->lpGoods->szCName == szName)
		{
			return listJiuDai.GetAt(listJiuDai.FindIndex(i))->lpGoods->nWeight;
		}
	}

	// Drug
	for(i = 0; i < listDrug.GetCount(); i++)
	{
		if(listDrug.GetAt(listDrug.FindIndex(i))->lpGoods->szEName == szName ||
			listDrug.GetAt(listDrug.FindIndex(i))->lpGoods->szCName == szName)
		{
			return listDrug.GetAt(listDrug.FindIndex(i))->lpGoods->nWeight;
		}
	}

	// Weapon
	for(i = 0; i < listWeapon.GetCount(); i++)
	{
		if(listWeapon.GetAt(listWeapon.FindIndex(i))->lpGoods->szEName == szName ||
			listWeapon.GetAt(listWeapon.FindIndex(i))->lpGoods->szCName == szName)
		{
			return listWeapon.GetAt(listWeapon.FindIndex(i))->lpGoods->nWeight;
		}
	}

	// Equip
	for(i = 0; i < listEquip.GetCount(); i++)
	{
		if(listEquip.GetAt(listEquip.FindIndex(i))->lpGoods->szEName == szName ||
			listEquip.GetAt(listEquip.FindIndex(i))->lpGoods->szCName == szName)
		{
			return listEquip.GetAt(listEquip.FindIndex(i))->lpGoods->nWeight;
		}
	}

	// Book
	for(i = 0; i < listBook.GetCount(); i++)
	{
		if(listBook.GetAt(listBook.FindIndex(i))->lpGoods->szEName == szName ||
			listBook.GetAt(listBook.FindIndex(i))->lpGoods->szCName == szName)
		{
			return listBook.GetAt(listBook.FindIndex(i))->lpGoods->nWeight;
		}
	}

	return 0;
}
// guanhua end 2000/07/28