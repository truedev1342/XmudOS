// InitAllNpc.cpp: 初始化所有的npc
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\npc\Npc.h"
#include "..\hash.h"
#include "..\XmudOS.h"
//Spock Add
#include "map\waei\N_Seller.h"
#include "map\waei\N_XLiumang.h"

// Nuke add
// 襄陽
#include "map\waei\N_OldWoman.h"
#include "map\waei\N_Girl.h"
//#include "map\waei\N_Host.h"
//#include "map\waei\N_Teacher.h"
#include "map\waei\N_OldWoman2.h"
// 少林
//#include "map\waei\N_SweepMonk.h"
//#include "map\waei\N_BigBadMonk.h"
// Nuke end

//峨嵋
//#include "map\emei\Nem_GuoXiang.h"
//#include "map\emei\Nem_JingHua.h"
#include "map\emei\Nem_XiaoNiGu.h"
#include "map\emei\Nem_YiHe.h"

//華山
//#include "map\huashan\Nhs_Feng.h"
//#include "map\huashan\Nhs_LingHu.h"
//#include "map\huashan\Nhs_Ning.h"
//#include "map\huashan\Nhs_YueBuQun.h"
#include "map\huashan\Nhs_Shijie.h"

//公共
#include "map\public\Npub_Bing.h"
#include "map\public\Npub_Boy.h"
#include "map\public\Npub_Child.h"
#include "map\public\Npub_Girl.h"
#include "map\public\Npub_JiaDing.h"
#include "map\public\Npub_JianKe.h"
#include "map\public\Npub_LiuMang.h"
#include "map\public\Npub_LiuMangTou.h"
#include "map\public\Npub_TiaoFu.h"
#include "map\public\Npub_TuFei.h"
#include "map\public\Npub_TuFeiTou.h"
#include "map\public\Npub_WuJiang.h"
#include "map\public\Npub_XiangKe.h"
#include "map\public\Npub_XiaoEr.h"
#include "map\public\Npub_YaYi.h"
#include "map\public\Npub_YouKe.h"

//少林
#include "map\shaolin\Nsl_DaoChen.h"
//#include "map\shaolin\Nsl_DaoCheng.h"
//#include "map\shaolin\Nsl_DaoGuo.h"
//#include "map\shaolin\Nsl_DaoJue.h"
//#include "map\shaolin\Nsl_DaoPin.h"
#include "map\shaolin\Nsl_Daosheng.h"
//#include "map\shaolin\Nsl_DaoXiang.h"
#include "map\shaolin\Nsl_DaoXiang2.h"
//#include "map\shaolin\Nsl_DaoYi.h"
//#include "map\shaolin\Nsl_DaoZheng.h"
//#include "map\shaolin\Nsl_QingWu.h"
#include "map\shaolin\Nsl_SaMi.h"

//武當
#include "map\wudang\Nwd_DaoTong.h"
//#include "map\wudang\Nwd_GuXu.h"
//#include "map\wudang\Nwd_SanFeng.h"
#include "map\wudang\Nwd_Xiaocui.h"
//#include "map\wudang\Nwd_ZhiKe.h"

//星宿
#include "map\xingxiu\Nxx_Dizi.h"
//#include "map\xingxiu\Nxx_TianLang.h"
//#include "map\xingxiu\Nxx_ZhaiXing.h"

//丐幫
//#include "map\gaibang\Ngb_ZuoQuan.h"
//揚州
#include "map\yangzhou\Nyz_AQingSao.h"

//dainty
//#include "map\dainty\Ngb_SmallBegger.h"
#include "map\dainty\N_Disciple.h"
#include "map\guanhua\N_EventNpc.h"
#include "map\dainty\N_BiaoTou.h"
#include "map\dainty\Nsl_KongMin.h"
#include "map\dainty\N_YunBing.h"
#include "map\dainty\N_BankMaster.h"
//#include "map\dainty\Nem_JingYi.h"
#include "map\dainty\Nem_YiLin.h"
#include "map\dainty\Nhs_ChinZuYang.h"
#include "map\dainty\Nwd_WangKangYu.h"
#include "map\dainty\Ngb_Dizi.h"
#include "map\dainty\Nxx_WeaponMgr.h"
#include "map\dainty\N_PawnMaster.h"
#include "map\public\Npub_JiaDing.h"
#include "map\dainty\N_Smith.h"
#include "map\dainty\N_WeaponSeller.h"
#include "map\dainty\Nzm_DiziW.h"

extern char g_tszPathName[256];
//dainty end
void InitAllNpc()
{
	CNpc * lpNpc;

// Nuke Add
// 襄陽
	lpNpc = new CN_Girl;
	lpNpc->AppToMap(lpNpc);

	lpNpc = new CN_OldWoman;
	lpNpc->AppToMap(lpNpc);

//	lpNpc = new CN_Host;
//	lpNpc->AppToMap(lpNpc);

//	lpNpc = new CN_Teacher;
//	lpNpc->AppToMap(lpNpc);

	lpNpc = new CN_OldWoman2;
	lpNpc->AppToMap(lpNpc);
// 少林
/*	lpNpc = new CN_SweepMonk;
	lpNpc->AppToMap(lpNpc);

	lpNpc = new CN_BigBadMonk;
	lpNpc->AppToMap(lpNpc);*/
// Nuke end

// Spock Add
// 小販
	lpNpc = new CN_Seller;
	lpNpc->szRoom = "yz_gc";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_Seller;
	lpNpc->szRoom = "ym_dhjie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_Seller;
	lpNpc->szRoom = "xy_guangchang";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_Seller;
	lpNpc->szRoom = "wd_shanmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_Seller;
	lpNpc->szRoom = "vl_dck";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_Seller;
	lpNpc->szRoom = "ly_center";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_Seller;
	lpNpc->szRoom = "jz_center";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_Seller;
	lpNpc->szRoom = "hs_sj";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_Seller;
	lpNpc->szRoom = "em_bgmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_Seller;
	lpNpc->szRoom = "cd_bgc";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_Seller;
	lpNpc->szRoom = "ca_gc";
	lpNpc->AppToMap(lpNpc);
//-------------------------------------------------------------
// 流氓
// dainty modified
//-------------------------------------------------------------
//--------------------------------------揚州區流氓	
	lpNpc = new CNpub_LiuMangTou;
	lpNpc->szRoom = "yz_lcy";
	lpNpc->AppToMap(lpNpc);
    lpNpc = new CNpub_LiuMangTou;
	lpNpc->szRoom = "yz_ndj";
	lpNpc->AppToMap(lpNpc);
    lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "yz_ndj";
	lpNpc->AppToMap(lpNpc);
    lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "yz_ndj";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "yz_lcy";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "yz_lcy";
	lpNpc->AppToMap(lpNpc);
    lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "yz_ndj";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "yz_ddj";   //No.2 fixed
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "yz_zxlou";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "yz_zxlou";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "yz_lcy";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "yz_lcy";
	lpNpc->AppToMap(lpNpc);
//-------------------------------------荊州區流氓
	lpNpc = new CNpub_LiuMangTou;
	lpNpc->szRoom = "jz_jlou";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "jz_jlou";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "jz_jlou";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "jz_jlou";
	lpNpc->AppToMap(lpNpc);
//-------------------------------------玉門區流氓	
	lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "ym_bdjie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "ym_bdjie";
	lpNpc->AppToMap(lpNpc);
    lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "ym_jl";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "ym_jl";
	lpNpc->AppToMap(lpNpc);
//--------------------------------------襄陽區流氓
	lpNpc = new CNpub_LiuMangTou;
	lpNpc->szRoom = "xy_xdajie";    
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_LiuMang;     
	lpNpc->szRoom = "xy_ddajie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "xy_xdajie";   
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "xy_ddajie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "xy_ddajie";
	lpNpc->AppToMap(lpNpc);
//---------------------------------------洛陽區流氓
	lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "ly_flower";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "ly_flower";
	lpNpc->AppToMap(lpNpc);
    lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "ly_ndjie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "ly_ndjie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "ly_ndjie";
	lpNpc->AppToMap(lpNpc);
//------------------------------------成都區流氓
	lpNpc = new CNpub_LiuMangTou;      
	lpNpc->szRoom = "cd_jlou";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "cd_ndjie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_LiuMang;
	lpNpc->szRoom = "cd_ndjie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;     
	lpNpc->szRoom = "cd_jlou";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "cd_jlou";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "cd_bdjie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "cd_bdjie";
	lpNpc->AppToMap(lpNpc);
//------------------------------------長安區流氓
	lpNpc = new CNpub_LiuMangTou;
	lpNpc->szRoom = "ca_xdjie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;    
	lpNpc->szRoom = "ca_xdjie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;   
	lpNpc->szRoom = "ca_ndjie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;   
	lpNpc->szRoom = "ca_ndjie";
	lpNpc->AppToMap(lpNpc);
//-------------------------------------星宿區流氓
    lpNpc = new CN_XLiuMang;     
	lpNpc->szRoom = "xx_silk";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "xx_silk";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "xx_path01";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "xx_path01";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "xx_path02";
	lpNpc->AppToMap(lpNpc);
//----------------------------------------峨嵋區流氓
    lpNpc = new CN_XLiuMang;         
	lpNpc->szRoom = "em_slub";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "em_slub";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "em_slua";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "em_slua";
	lpNpc->AppToMap(lpNpc);
//----------------------------------------少林區流氓
	lpNpc = new CN_XLiuMang;          
	lpNpc->szRoom = "sl_path08";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "sl_path08";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "sl_path09";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "sl_path14";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "sl_path15";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "sl_path15";
	lpNpc->AppToMap(lpNpc);
//----------------------------------------谷場區流氓
	lpNpc = new CN_XLiuMang;       
	lpNpc->szRoom = "vl_nck";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "vl_nck";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "vl_dck";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "vl_dck";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "vl_xck";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CN_XLiuMang;
	lpNpc->szRoom = "vl_xck";
	lpNpc->AppToMap(lpNpc);

//------------------------------------------------------------
//峨嵋
//	lpNpc = new CNem_GuoXiang;
//	lpNpc->AppToMap(lpNpc);
//	lpNpc = new CNem_JingHua;
//	lpNpc->AppToMap(lpNpc);
//	lpNpc = new CNem_JingYi;
//	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_YiLin;       //給武器
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_YiHe;  //給糧
	lpNpc->AppToMap(lpNpc);

	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_dining";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_dining";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_dlang";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_xlang";
	lpNpc->AppToMap(lpNpc);
	/*lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_gchang";
	lpNpc->AppToMap(lpNpc);
    lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_gchang";
	lpNpc->AppToMap(lpNpc);*/
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_zdian";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_hzan";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_hzan";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_wyun";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_wxan";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_yxsi";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_xfsi";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_wnan";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_qfan";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_ssge";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNem_XiaoNiGu;
	lpNpc->szRoom = "em_roomd";
	lpNpc->AppToMap(lpNpc);

//華山
//	lpNpc = new CNhs_Feng;
//	lpNpc->AppToMap(lpNpc);
//	lpNpc = new CNhs_LingHu;
//	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNhs_ChinZuYang;     //給武器
	lpNpc->AppToMap(lpNpc);
//	lpNpc = new CNhs_Ning;
//	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNhs_ShiJie;         //給食物
	lpNpc->AppToMap(lpNpc);
//	lpNpc = new CNhs_YueBuQun;
//	lpNpc->AppToMap(lpNpc);

//公共
	//武將
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "ym_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "ym_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "ym_jyg";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "xy_chenmenx";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "xy_chenmend";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "xy_chenmenn";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "xy_chenmenb";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "yz_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "yz_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "yz_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "yz_nchengm";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "yz_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "ly_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "ly_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "ly_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "ly_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "jz_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "jz_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "jz_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "jz_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "jz_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "jz_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "cd_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "cd_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "cd_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "cd_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "cd_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "cd_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "ca_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "ca_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "ca_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_WuJiang;
	lpNpc->szRoom = "ca_dcmen";
	lpNpc->AppToMap(lpNpc);

	//官兵
	// Nuke +1
//	SBing.number=0;
//	SBing.count=0;
	
	//官兵
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ca_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ca_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ca_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ca_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ca_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ca_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ca_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ca_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "cd_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "jz_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ly_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ly_ncmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ly_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ly_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ly_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ly_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ly_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ly_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "yz_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "yz_xcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "yz_nchengm";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "yz_nchengm";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "yz_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "yz_dcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "yz_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "yz_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "yz_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "yz_bcmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "xy_chenmenb";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "xy_chenmenb";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "xy_chenmenn";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "xy_chenmenn";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "xy_chenmend";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "xy_chenmend";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "xy_chenmenx";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "xy_chenmenx";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ym_jyg";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ym_jyg";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ym_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ym_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ym_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ym_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ym_by";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Bing;
	lpNpc->szRoom = "ym_by";
	lpNpc->AppToMap(lpNpc);

	// Nuke +1
	Bing *lpBing = dynamic_cast<CNpub_Bing*>(lpNpc)->lpBing;
	lpBing->whoami.Format("guanbing%d",random(lpBing->number)+1);

	//男孩
	lpNpc = new CNpub_Boy;
	lpNpc->szRoom = "ca_gc";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Boy;
	lpNpc->szRoom = "em_bgsxq";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Boy;
	lpNpc->szRoom = "em_bgsxq";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Boy;
	lpNpc->szRoom = "jz_path10";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Boy;
	lpNpc->szRoom = "jz_path10";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Boy;
	lpNpc->szRoom = "vl_nck";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Boy;
	lpNpc->szRoom = "xy_bdajie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Boy;
	lpNpc->szRoom = "xy_xdajie";
	lpNpc->AppToMap(lpNpc);
	//女孩
	lpNpc = new CNpub_Girl;
	lpNpc->szRoom = "xy_mingju";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Girl;
	lpNpc->szRoom = "ca_gc";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Girl;
	lpNpc->szRoom = "vl_nck";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Girl;
	lpNpc->szRoom = "jz_path01";
	lpNpc->AppToMap(lpNpc);
	//小孩
	lpNpc = new CNpub_Child;
	lpNpc->szRoom = "cd_minju";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Child;
	lpNpc->szRoom = "jz_path12";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Child;
	lpNpc->szRoom = "jz_path12";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Child;
	lpNpc->szRoom = "sl_path01";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Child;
	lpNpc->szRoom = "sl_path01";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Child;
	lpNpc->szRoom = "vl_gc";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Child;
	lpNpc->szRoom = "xy_ddajie";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_Child;
	lpNpc->szRoom = "xy_ndajie";
	lpNpc->AppToMap(lpNpc);

	//挑夫
	lpNpc = new CNpub_TiaoFu;
	lpNpc->szRoom = "sl_path03";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_TiaoFu;
	lpNpc->szRoom = "sl_path03";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_TiaoFu;
	lpNpc->szRoom = "ly_center";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_TiaoFu;
	lpNpc->szRoom = "vl_cpeng";
	lpNpc->AppToMap(lpNpc);

	//香客
	lpNpc = new CNpub_XiangKe;
	lpNpc->szRoom = "sl_dxbd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_XiangKe;
	lpNpc->szRoom = "sl_twd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_XiangKe;
	lpNpc->szRoom = "sl_tj";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_XiangKe;
	lpNpc->szRoom = "sl_smd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_XiangKe;
	lpNpc->szRoom = "wd_ypd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_XiangKe;
	lpNpc->szRoom = "wd_shanmen";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_XiangKe;
	lpNpc->szRoom = "wd_shij";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_XiangKe;
	lpNpc->szRoom = "wd_zpd";
	lpNpc->AppToMap(lpNpc);

	//游客
	lpNpc = new CNpub_YouKe;
	lpNpc->szRoom = "ca_xyta";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_YouKe;
	lpNpc->szRoom = "em_12pb";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_YouKe;
	lpNpc->szRoom = "em_12pb";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_YouKe;
	lpNpc->szRoom = "em_mingshan";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_YouKe;
	lpNpc->szRoom = "em_mingshan";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_YouKe;
	lpNpc->szRoom = "hs_ljg";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNpub_YouKe;
	lpNpc->szRoom = "hs_ync";
	lpNpc->AppToMap(lpNpc);

//少林
//	lpNpc = new CNsl_QingWu;
//	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNsl_DaoChen;    //給武器
	lpNpc->AppToMap(lpNpc);
	//lpNpc = new CNsl_DaoCheng;
	//lpNpc->AppToMap(lpNpc);
	//lpNpc = new CNsl_DaoGuo;
	//lpNpc->AppToMap(lpNpc);
//	lpNpc = new CNsl_DaoJue;
//	lpNpc->AppToMap(lpNpc);
//	lpNpc = new CNsl_DaoPin;
//	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNsl_Daosheng;  //給糧
	lpNpc->AppToMap(lpNpc);
	//lpNpc = new CNsl_DaoXiang;
	//lpNpc->AppToMap(lpNpc);
	lpNpc = new CNsl_DaoXiang2; //給藥
	lpNpc->AppToMap(lpNpc);
/*	lpNpc = new CNsl_DaoYi;
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNsl_DaoZheng;
	lpNpc->AppToMap(lpNpc);*/


	lpNpc = new CNsl_SaMi;
	lpNpc->szRoom = "sl_gca";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNsl_SaMi;
	lpNpc->szRoom = "sl_dxbd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNsl_SaMi;
	lpNpc->szRoom = "sl_dcd1";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNsl_SaMi;
	lpNpc->szRoom = "sl_byd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNsl_SaMi;
	lpNpc->szRoom = "sl_zla";
	lpNpc->AppToMap(lpNpc);

//武當
	lpNpc = new CNwd_DaoTong;
	lpNpc->szRoom = "wd_zwd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNwd_DaoTong;
	lpNpc->szRoom = "wd_zwd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNwd_DaoTong;
	lpNpc->szRoom = "wd_zpd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNwd_DaoTong;
	lpNpc->szRoom = "wd_ypd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNwd_DaoTong;
	lpNpc->szRoom = "wd_sqd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNwd_DaoTong;
	lpNpc->szRoom = "wd_sqd";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNwd_DaoTong;
	lpNpc->szRoom = "wd_hy";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNwd_DaoTong;
	lpNpc->szRoom = "wd_dzl";
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNwd_DaoTong;
	lpNpc->szRoom = "wd_cjg2";
	lpNpc->AppToMap(lpNpc);
//武當
//	lpNpc = new CNwd_GuXu;
//	lpNpc->AppToMap(lpNpc);
//	lpNpc = new CNwd_SanFeng;
//	lpNpc->AppToMap(lpNpc);
//	lpNpc = new CNwd_ZhiKe;
//	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNwd_XiaoCui;  //給糧
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNwd_WangKangYu;    //給武器
	lpNpc->AppToMap(lpNpc);


//星宿
/*	lpNpc = new CNxx_TianLang;
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNxx_ZhaiXing;
	lpNpc->AppToMap(lpNpc);  */
	lpNpc = new CNxx_Dizi; //給糧
	lpNpc->AppToMap(lpNpc);
	lpNpc = new CNxx_WeaponMgr;     //給武器
	lpNpc->AppToMap(lpNpc);


//丐幫
//	lpNpc = new CNgb_ZuoQuan;
//	lpNpc->AppToMap(lpNpc);
//dainty
	lpNpc = new CNgb_Dizi;      //給武器
	lpNpc->AppToMap(lpNpc);
//dainty end

//昭明書院
    lpNpc = new CNzm_DiziW;      //給武器
	lpNpc->AppToMap(lpNpc);
//揚州
	lpNpc = new CNyz_AQingSao;
	lpNpc->AppToMap (lpNpc);
	lpNpc = new CNpub_JiaDing;  //家丁
	lpNpc->szRoom = "yz_czhy";
    lpNpc->AppToMap (lpNpc);
	lpNpc = new CNpub_JiaDing;
	lpNpc->szRoom = "yz_czhy";
    lpNpc->AppToMap (lpNpc);
	lpNpc = new CNpub_JiaDing;
	lpNpc->szRoom = "yz_czdt";
    lpNpc->AppToMap (lpNpc);
	lpNpc = new CNpub_JiaDing;
	lpNpc->szRoom = "yz_czdt";
    lpNpc->AppToMap (lpNpc);
	lpNpc = new CNpub_JiaDing;
	lpNpc->szRoom = "yz_czdm";
    lpNpc->AppToMap (lpNpc);
	lpNpc = new CNpub_JiaDing;
	lpNpc->szRoom = "yz_czdm";
    lpNpc->AppToMap (lpNpc);

//dainty 
//讀入npc
	FILE *fp;
	char pathname[50],filename[50],temp1[50],temp2[50],szBuf[256];

	strcpy(pathname, g_tszPathName);
	strcat(pathname,"\\npc\\");
	strcpy(filename,pathname);
	strcat(filename,"_npc.txt");
	fp=fopen(filename,"r");

	if (fp) {
        while(fgets(szBuf, 256, fp)!=NULL)
		{
			if (sscanf(szBuf, "%s %s", temp1, filename) == 2) {
				strcpy(temp2,pathname);
				strcat(temp2,"\\");
				strcat(temp2,temp1);
// guanhua 2000/07/28
 				lpNpc = new CN_EventNpc(temp2,filename);
//				lpNpc = new CN_Disciple(temp2,filename);
				if (lpNpc->szCName != "ERROR")	{
					lpNpc->AppToMap (lpNpc);
				} else {
					delete lpNpc;
				}
			}
		}
		fclose(fp);
	} else {
		AddRecordMsg("NPC Disciple index open fail");
	}
//土匪
	/*
    lpNpc = new CNpub_TuFei;
	lpNpc->szRoom = "ca_path01";
	lpNpc->AppToMap (lpNpc);

	lpNpc = new CNpub_TuFei;
	lpNpc->szRoom = "xy_path02";
	lpNpc->AppToMap (lpNpc);

	lpNpc = new CNpub_TuFei;
	lpNpc->szRoom = "xy_path03";
	lpNpc->AppToMap (lpNpc);

	lpNpc = new CNpub_TuFei;
	lpNpc->szRoom = "xy_path04";
	lpNpc->AppToMap (lpNpc);

	lpNpc = new CNpub_TuFei;
	lpNpc->szRoom = "xy_path08";
	lpNpc->AppToMap (lpNpc);
*/
	lpNpc = new CNpub_TuFeitou;
	lpNpc->szRoom = "xy_path03";
	lpNpc->AppToMap (lpNpc);

	lpNpc = new CNpub_TuFeitou;
	lpNpc->szRoom = "xy_path08";
	lpNpc->AppToMap (lpNpc);
/*
	lpNpc = new CNpub_TuFei;
	lpNpc->szRoom = "sl_path01";
	lpNpc->AppToMap (lpNpc);
	lpNpc = new CNpub_TuFei;
	lpNpc->szRoom = "sl_path02";
	lpNpc->AppToMap (lpNpc);
	lpNpc = new CNpub_TuFei;
	lpNpc->szRoom = "sl_path02";
	lpNpc->AppToMap (lpNpc);
	lpNpc = new CNpub_TuFei;
	lpNpc->szRoom = "vl_nssl";     //No.9 fixed
	lpNpc->AppToMap (lpNpc);
	lpNpc = new CNpub_TuFei;
	lpNpc->szRoom = "vl_nssl";     //No.10 fixed
	lpNpc->AppToMap (lpNpc);
*/

//元兵
	for(int i=9;i>4;i--)
	{
	    lpNpc = new CN_YunBing;
		lpNpc->szRoom.Format("ly_path0%d",i);
	    lpNpc->AppToMap (lpNpc);

		lpNpc = new CN_YunBing;
		lpNpc->szRoom.Format("ly_path0%d",i);
	    lpNpc->AppToMap (lpNpc);
	}
//任務
    lpNpc = new CN_BiaoTou;  //鑣頭
	lpNpc->AppToMap (lpNpc);

	lpNpc = new CNsl_KongMin;  //空明
	lpNpc->AppToMap (lpNpc);
 
//錢莊
    lpNpc = new CN_BankMaster;  //長安
	lpNpc->szRoom = "ca_bank";
	lpNpc->AppToMap (lpNpc);
	lpNpc = new CN_BankMaster;  //成都
	lpNpc->szRoom = "cd_bank";
	lpNpc->AppToMap (lpNpc);
	lpNpc = new CN_BankMaster;  //揚州
	lpNpc->szRoom = "yz_bank";
	lpNpc->AppToMap (lpNpc);

//當鋪
/*    lpNpc = new CN_PawnMaster;  //成都
	lpNpc->szRoom = "cd_pawn";
	lpNpc->AppToMap (lpNpc);
	lpNpc = new CN_PawnMaster;  //玉門
	lpNpc->szRoom = "ym_dp";
	lpNpc->AppToMap (lpNpc);*/
	//lpNpc = new CN_PawnMaster;  //揚州西大街
	//lpNpc->szRoom = "yz_xdj";
	//lpNpc->AppToMap (lpNpc);

//dainty end
//打鐵舖
	/*lpNpc = new CN_Smith;
    lpNpc->szRoom = "cd_smith";
	lpNpc->AppToMap (lpNpc);
	lpNpc = new CN_Smith;
    lpNpc->szRoom = "jz_smith";
	lpNpc->AppToMap (lpNpc);
	lpNpc = new CN_Smith;
    lpNpc->szRoom = "vl_smith";
	lpNpc->AppToMap (lpNpc);
	*/
//兵器舖
	lpNpc = new CN_WeaponSeller;
    lpNpc->szRoom = "yz_bqp";    
	lpNpc->AppToMap (lpNpc);
	
}
