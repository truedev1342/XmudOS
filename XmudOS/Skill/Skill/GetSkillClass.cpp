#include "..\..\stdafx.h"
#include "Skill.h"
//#include "SkillClass.h"
/*
//基本武功
#include "Base\SBaseBlade.h"
#include "Base\SBaseClaw.h"
#include "Base\SBaseClub.h"
#include "Base\SBaseCuff.h"
#include "Base\SBaseDodge.h"
#include "Base\SBaseFinger.h"
#include "Base\SBaseForce.h"
#include "Base\SBaseHammer.h"
#include "Base\SBaseHand.h"
#include "Base\SBaseParry.h"
#include "Base\SBaseStaff.h"
#include "Base\SBaseStick.h"
#include "Base\SBaseStrike.h"
#include "Base\SBaseSword.h"
#include "Base\SBaseThrowing.h"
#include "Base\SBaseUnarmed.h"
#include "Base\SBaseWhip.h"
//其他武功
#include "Other\SOtherBuddhism.h"
#include "Other\SOtherLiterate.h"
#include "Other\SOtherPoison.h"
#include "Other\SOtherTaoism.h"
#include "Other\SOtherThieve.h"
*/
/*
//特殊專用武功
//Blade,刀法
#include "Blade\SBlade_Xiuluo.h"
#include "Blade\SBlade_FanLiangyi.h"
#include "Blade\SBlade_Taiji.h"
#include "Blade\SBlade_Cibei.h"
//claw,爪法
#include "Claw\SClaw_Longzhua.h"
#include "Claw\SClaw_Yingzhua.h"
#include "Claw\SClaw_Jiuyin.h"
//Club,棒法
#include "Club\SClub_Dagou.h"
#include "Club\SClub_Zui.h"
#include "Club\SClub_Weituo.h"
//Cuff,拳法
#include "Cuff\SCuff_Luohan.h"
#include "Cuff\SCuff_Poyu.h"
#include "Cuff\SCuff_Jingang.h"

//Finger, 指法
#include "Finger\SFinger_Nianhua.h"
#include "Finger\SFinger_yizhichan.h"
*/
//Force,內功
/*
#include "Force\SForce_Hunyuan.h"
#include "Force\SForce_Emei.h"
#include "Force\SForce_Huntian.h"
#include "Force\SForce_Taiji.h"
#include "Force\SForce_Zixia.h"
#include "Force\SForce_Huagong.h"
*/
/*
//Hand, 手法
#include "Hand\SHand_Fengyun.h"
#include "Hand\SHand_Qianye.h"
//Staff,杖法
#include "Staff\SStaff_Tianshan.h"
#include "Staff\SStaff_Pudu.h"
#include "Staff\SStaff_Wuchang.h"
*/
//Step,輕功
/*
#include "Dodge\SStep_Lingbo.h"
#include "Dodge\SStep_Jiuyin.h"
#include "Dodge\SStep_Qixing.h"
#include "Dodge\SStep_Zhaixing.h"
#include "Dodge\SStep_Anxiangfuying.h"
#include "Dodge\SStep_Qiankun.h"
#include "Dodge\SStep_Qibaotianfeng.h"
#include "Dodge\SStep_Snow.h"
#include "Dodge\SStep_Tiyunzhong.h"
#include "Dodge\SStep_Xingyi.h"
#include "Dodge\SStep_Yanshuangfei.h"
#include "Dodge\SStep_Shaolin.h"
#include "Dodge\SStep_Huashan.h"
*/
/*
//Strike,掌法
#include "Strike\SStrike_Hunyuan.h"
#include "Strike\SStrike_Banruo.h"
#include "Strike\SStrike_Sanhua.h"
#include "Strike\SStrike_Hanbing.h"
//Sword,劍法
#include "Sword\SSword_Pixie.h"
#include "Sword\SSword_Dugu.h"
#include "Sword\SSword_Damo.h"
#include "Sword\SSword_Emei.h"
#include "Sword\SSword_Huashan.h"
#include "Sword\SSword_Taiji.h"
#include "Sword\SSword_Fumo.h"
//Unarmed,拳腳
#include "Unarmed\SUnarmed_Yijianmei.h"
#include "Unarmed\SUnarmed_Mizhong.h"
#include "Unarmed\SUnarmed_Xianglong.h"
#include "Unarmed\SUnarmed_Meihua.h"
#include "Unarmed\SUnarmed_Huashan.h"
#include "Unarmed\SUnarmed_Taiji.h"
#include "Unarmed\SUnarmed_XingXiu.h"
#include "Unarmed\SUnarmed_Hou.h"
#include "Unarmed\SUnarmed_Kongming.h"
//Whip,鞭法
#include "Whip\SWhip_Riyue.h"

  */
//基本武功
/*
CBaseBlade	BaseBlade;
CBaseClaw	BaseClaw;
CBaseClub	BaseClub;
CBaseCuff	BaseCuff;
CBaseDodge	BaseDodge;
CBaseFinger	BaseFinger;
CBaseForce	BaseForce;
CBaseHammer	BaseHammer;
CBaseHand	BaseHand;
CBaseParry	BaseParry;
CBaseStaff	BaseStaff;
CBaseStick	BaseStick;
CBaseStrike	BaseStrike;
CBaseSword	BaseSword;
CBaseThrowing	BaseThrowing;
CBaseUnarmed	BaseUnarmed;
CBaseWhip		BaseWhip;
//其他武功
COtherBuddhism	OtherBuddhism;
COtherLiterate	OtherLiterate;
COtherPoison	OtherPoison;
COtherTaoism	OtherTaoism;
COtherThieve	OtherThieve;
*/
/*
//Blade,刀法
CBlade_Xiuluo		Blade_Xiuluo;
CBlade_Fanliangyi	Blade_Fanliangyi;
CBlade_Taiji		Blade_Taiji;
CBlade_Cibei		Blade_Cibei;
//claw,爪法
CClaw_Longzhua		Claw_Longzhua;
CClaw_Yingzhua		Claw_Yingzhua;
CClaw_Jiuyin		Claw_Jiuyin;

//Cuff,拳法
CCuff_Luohan	Cuff_Luohan;
CCuff_Poyu		Cuff_Poyu;
CCuff_Jingang	Cuff_Jingang;
//Club,棒法
CClub_Dagou		Club_Dagou;
CClub_Zui		Club_Zui;
CClub_Weituo	Club_Weituo;
//Finger, 指法
CFinger_Nianhua		Finger_Nianhua;
CFinger_Yizhichan	Finger_Yizhichan;
*/
//Force,內功
/*
CForce_Hunyuan	Force_Hunyuan;
CForce_Emei		Force_Emei;
CForce_Huntian	Force_Huntian;
CForce_Taiji	Force_Taiji;
CForce_Zixia	Force_Zixia;
CForce_Huagong	Force_Huagong;
*/
/*
//Hand, 手法
CHand_Fengyun	Hand_Fengyun;
CHand_Qianye	Hand_Qianye;
//Staff,杖法
CStaff_Tianshan	Staff_Tianshan;
CStaff_Pudu		Staff_Pudu;
CStaff_Wuchang	Staff_Wuchang;
*/
//Step,輕功
/*
CStep_Lingbo	Step_Lingbo;
CStep_Jiuyin	Step_Jiuyin;
CStep_Qixing	Step_Qixing;
CStep_Zhaixing	Step_Zhaixing;
CStep_Anxiangfuying	Step_Anxiangfuying;
CStep_Qiankun		Step_Qiankun;
CStep_Qibaotianfeng	Step_Qibaotianfeng;
CStep_Snow			Step_Snow;
CStep_Tiyunzhong	Step_Tiyunzhong;
CStep_Xingyi		Step_Xingyi;
CStep_Yanshuangfei	Step_Yanshuangfei;
CStep_Shaolin		Step_Shaolin;
CStep_Huashan		Step_Huashan;
*/
/*
//Strike,掌法
CStrike_Hunyuan		Strike_Hunyuan;
CStrike_Banruo		Strike_Banruo;
CStrike_Sanhua		Strike_Sanhua;
CStrike_Hanbing		Strike_Hanbing;
//Sword,劍法
CSword_Pixie	Sword_Pixie;
CSword_Dugu		Sword_Dugu;
CSword_Damo		Sword_Damo;
CSword_Emei		Sword_Emei;
CSword_Huashan	Sword_Huashan;
CSword_Taiji	Sword_Taiji;
CSword_Fumo		Sword_Fumo;
//Unarmed,拳腳
CUnarmed_Yijianmei	Unarmed_Yijianmei;
CUnarmed_Mizhong	Unarmed_Mizhong;
CUnarmed_Xianglong	Unarmed_Xianglong;
CUnarmed_Meihua		Unarmed_Meihua;
CUnarmed_Huashan	Unarmed_Huashan;
CUnarmed_Taiji		Unarmed_Taiji;
CUnarmed_Xingxiu	Unarmed_Xingxiu;
CUnarmed_Hou		Unarmed_Hou;
CUnarmed_Kongming	Unarmed_Kongming;
//Whip,鞭法
CWhip_Riyue	Whip_Riyue;
*/
//私有函數
/*
static CSkill * GetBaseSkill(CString szEName);
static CSkill * GetOtherSkill(CString szEName);
static CSkill * GetDodgeSkill(CString szEName);
static CSkill * GetForceSkill(CString szEName);
*/
/*static CSkill * GetUnarmedSkill(CString szEName);

static CSkill * GetParrySkill(CString szEName);

static CSkill * GetBladeSkill(CString szEName);
static CSkill * GetSwordSkill(CString szEName);
static CSkill * GetClubSkill(CString szEName);
static CSkill * GetStickSkill(CString szEName);
static CSkill * GetStaffSkill(CString szEName);
static CSkill * GetThrowingSkill(CString szEName);
static CSkill * GetWhipSkill(CString szEName);
static CSkill * GetHammerSkill(CString szEName);
static CSkill * GetCuffSkill(CString szEName);
static CSkill * GetStrikeSkill(CString szEName);
static CSkill * GetHandSkill(CString szEName);
static CSkill * GetClawSkill(CString szEName);
static CSkill * GetFingerSkill(CString szEName);
static CSkill * GetComboSkill(CString szEName);

*/
//CSkill * GetSkillClass(CString szEName, int nType, int nCanMap)
extern char g_tszPathName[256];
static CList<CSkill *,CSkill *> listSkill;
void InitAllSkill()
{
	CSkill * lpSkill;
    char szPath[128],szFileName[256],szBuf[128];

	strcpy(szPath,g_tszPathName);
	strcat(szPath,"\\skill\\");
	strcpy(szFileName,szPath);
 	strcat(szFileName,"_skill.txt");
	FILE *fp;

	if((fopen_s(&fp, szFileName,"r")) == 0)
	{
		while(fscanf(fp,"%s",szBuf)!=EOF)
		{
			strcpy(szFileName,szPath);
 	        strcat(szFileName,szBuf);
            lpSkill = new CSkill;
			lpSkill->Init(szFileName);
			if(lpSkill!=NULL) listSkill.AddTail(lpSkill);
		}
		fclose(fp);
	}
}
CSkill *GetSkillClass(CString szEName)
{
	
	CSkill *lpSkill = NULL,*lpNewSkill;

    for(int i=0;i<listSkill.GetCount();i++)
	{
		if(listSkill.GetAt(listSkill.FindIndex(i))->szEName==szEName)
		{
			lpSkill = listSkill.GetAt(listSkill.FindIndex(i));
			break;
		}
	}
	if(lpSkill!=NULL)
	{
		lpNewSkill = new CSkill;
		//lpNewSkill->listCom = lpSkill->listCom;
		for(int feat=0;feat<lpSkill->listFeat.GetCount();feat++)
		    lpNewSkill->listFeat.AddTail(lpSkill->listFeat.GetAt(lpSkill->listFeat.FindIndex(feat)));
		for(int skill=0;skill<lpSkill->listNeedSkill.GetCount();skill++)
		    lpNewSkill->listNeedSkill.AddTail(lpSkill->listNeedSkill.GetAt(lpSkill->listNeedSkill.FindIndex(skill)));
		lpNewSkill->nCanMap = lpSkill->nCanMap;
		lpNewSkill->nDodge = lpSkill->nDodge;
		lpNewSkill->nNeedMax_force = lpSkill->nNeedMax_force;
		lpNewSkill->nNeedMax_jingli = lpSkill->nNeedMax_jingli;
        lpNewSkill->nNeedWeapon = lpSkill->nNeedWeapon;
		lpNewSkill->nParry = lpSkill->nParry;
		lpNewSkill->nType = lpSkill->nType;
		lpNewSkill->nUnarmedParry = lpSkill->nUnarmedParry;
		lpNewSkill->nUsage = lpSkill->nUsage;
		lpNewSkill->szCName = lpSkill->szCName;
		lpNewSkill->szEName = lpSkill->szEName;
	
		return lpNewSkill;
	}
	return NULL;
/*		lpSkill = GetUnarmedSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		
		lpSkill = GetParrySkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		
		lpSkill = GetBladeSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetSwordSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetClubSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetStickSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetStaffSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetThrowingSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetWhipSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetHammerSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetCuffSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetStrikeSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetHandSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetClawSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetFingerSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		lpSkill = GetComboSkill(szEName);
		if (lpSkill != NULL) return lpSkill;
		return NULL;
		// Spock end
	*/
}

void ReleaseSkill()
{
	listSkill.RemoveAll();
}
/*
CSkill * GetBaseSkill(CString szEName)
{
	CSkill * lpSkill;
	if( stricmp(szEName, "BaseBlade") == 0 )
	{
		lpSkill = &BaseBlade;
	}
	else if( stricmp(szEName, "BaseClaw") == 0 )
	{
		lpSkill = &BaseClaw;
	}
	else if( stricmp(szEName, "BaseClub") == 0 )
	{
		lpSkill = &BaseClub;
	}
	else if( stricmp(szEName, "BaseCuff") == 0 )
	{
		lpSkill = &BaseCuff;
	}
	else if( stricmp(szEName, "BaseDodge") == 0 )
	{
		lpSkill = &BaseDodge;
	}
	else if( stricmp(szEName, "BaseFinger") == 0 )
	{
		lpSkill = &BaseFinger;
	}
	else if( stricmp(szEName, "BaseForce") == 0 )
	{
		lpSkill = &BaseForce;
	}
	else if( stricmp(szEName, "BaseHammer") == 0 )
	{
		lpSkill = &BaseHammer;
	}
	else if( stricmp(szEName, "BaseHand") == 0 )
	{
		lpSkill = &BaseHand;
	}
	else if( stricmp(szEName, "BaseParry") == 0 )
	{
		lpSkill = &BaseParry;
	}
	else if( stricmp(szEName, "BaseStaff") == 0 )
	{
		lpSkill = &BaseStaff;
	}
	else if( stricmp(szEName, "BaseStick") == 0 )
	{
		lpSkill = &BaseStick;
	}
	else if( stricmp(szEName, "BaseStrike") == 0 )
	{
		lpSkill = &BaseStrike;
	}
	else if( stricmp(szEName, "BaseSword") == 0 )
	{
		lpSkill = &BaseSword;
	}
	else if( stricmp(szEName, "BaseThrowing") == 0 )
	{
		lpSkill = &BaseThrowing;
	}
	else if( stricmp(szEName, "BaseUnarmed") == 0 )
	{
		lpSkill = &BaseUnarmed;
	}
	else if( stricmp(szEName, "BaseWhip") == 0 )
	{
		lpSkill = &BaseWhip;
	}
	else lpSkill = NULL;
	return lpSkill;
}

CSkill * GetOtherSkill(CString szEName)
{
	CSkill * lpSkill;
	if( stricmp(szEName, "OtherBuddhism") == 0 )
	{
		lpSkill = &OtherBuddhism;
	}
	else if( stricmp(szEName, "OtherLiterate") == 0 )
	{
		lpSkill = &OtherLiterate;
	}
	else if( stricmp(szEName, "OtherPoison") == 0 )
	{
		lpSkill = &OtherPoison;
	}
	else if( stricmp(szEName, "OtherTaoism") == 0 )
	{
		lpSkill = &OtherTaoism;
	}
	else if( stricmp(szEName, "OtherThieve") == 0 )
	{
		lpSkill = &OtherThieve;
	}
	else 
		lpSkill = NULL;
	return lpSkill;
}*/
/*
CSkill * GetBladeSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Blade_Xiuluo"))
	{
		lpSkill = &Blade_Xiuluo;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Blade_FanLiangyi"))
	{
		lpSkill = &Blade_Fanliangyi;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Blade_Taiji"))
	{
		lpSkill = &Blade_Taiji;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Blade_Cibei"))
	{
		lpSkill = &Blade_Cibei;
		return lpSkill;
	}
	return NULL;
}
*/
/*
CSkill * GetClawSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Claw_Longzhua"))
	{
		lpSkill = &Claw_Longzhua;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Claw_Yingzhua"))
	{
		lpSkill = &Claw_Yingzhua;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Claw_Jiuyin"))
	{
		lpSkill = &Claw_Jiuyin;
		return lpSkill;
	}
	return NULL;
}
*/
/*
CSkill * GetClubSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Club_Dagou"))
	{
		lpSkill = &Club_Dagou;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Club_Zui"))
	{
		lpSkill = &Club_Zui;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Club_Weituo"))
	{
		lpSkill = &Club_Weituo;
		return lpSkill;
	}
	return NULL;
}
*/
/*
CSkill * GetCuffSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Cuff_Luohan"))
	{
		lpSkill = &Cuff_Luohan;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Cuff_Poyu"))
	{
		lpSkill = &Cuff_Poyu;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Cuff_Jingang"))
	{
		lpSkill = &Cuff_Jingang;
		return lpSkill;
	}
	
	return NULL;
}
*/
/*
CSkill * GetFingerSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Finger_Yizhichan"))
	{
		lpSkill = &Finger_Yizhichan;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Finger_Nianhua"))
	{		lpSkill = &Finger_Nianhua;
		return lpSkill;
	}
	return NULL;
}
*/
/*
CSkill * GetForceSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Force_Hunyuan"))
	{
		lpSkill = &Force_Hunyuan;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Force_Emei"))
	{
		lpSkill = &Force_Emei;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Force_Huntian"))
	{
		lpSkill = &Force_Huntian;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Force_Taiji"))
	{
		lpSkill = &Force_Taiji;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Force_Zixia"))
	{
		lpSkill = &Force_Zixia;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Force_Huagong"))
	{
		lpSkill = &Force_Huagong;
		return lpSkill;
	}
	return NULL;
}
*/
/*
CSkill * GetHammerSkill(CString szEName)
{
	//CSkill * lpSkill;
	return NULL;
}
*/
/*
CSkill * GetHandSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Hand_Fengyun"))
	{
		lpSkill = &Hand_Fengyun;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Hand_Qianye"))
	{
		lpSkill = &Hand_Qianye;
		return lpSkill;
	}

	return NULL;
}
*/
/*
CSkill * GetParrySkill(CString szEName)
{
	//CSkill * lpSkill;
	//所有功夫中沒有只含parry的
	return NULL;
}
*/
/*
CSkill * GetStaffSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Staff_Tianshan"))
	{
		lpSkill = &Staff_Tianshan;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Staff_Pudu"))
	{
		lpSkill = &Staff_Pudu;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Staff_Wuchang"))
	{
		lpSkill = &Staff_Wuchang;
		return lpSkill;
	}

	return NULL;
}
*/
/*
CSkill * GetDodgeSkill(CString szEName)//step
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Step_Lingbo"))
	{
		lpSkill = &Step_Lingbo;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Jiuyin"))
	{
		lpSkill = &Step_Jiuyin;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Qixing"))
	{
		lpSkill = &Step_Qixing;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Zhaixing"))
	{
		lpSkill = &Step_Zhaixing;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Anxiangfuying"))
	{
		lpSkill = &Step_Anxiangfuying;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Qiankun"))
	{
		lpSkill = &Step_Qiankun;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Qibaotianfeng"))
	{
		lpSkill = &Step_Qibaotianfeng;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Snow"))
	{
		lpSkill = &Step_Snow;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Tiyunzhong"))
	{
		lpSkill = &Step_Tiyunzhong;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Xingyi"))
	{
		lpSkill = &Step_Xingyi;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Yanshuangfei"))
	{
		lpSkill = &Step_Yanshuangfei;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Shaolin"))
	{
		lpSkill = &Step_Shaolin;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Step_Huashan"))
	{
		lpSkill = &Step_Huashan;
		return lpSkill;
	}
	return NULL;
}
*/
/*
CSkill * GetStickSkill(CString szEName)
{
	//CSkill * lpSkill;
	return NULL;
}
*/
/*
CSkill * GetStrikeSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Strike_Hunyuan"))
	{
		lpSkill = &Strike_Hunyuan;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Strike_Banruo"))
	{
		lpSkill = &Strike_Banruo;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Strike_Sanhua"))
	{
		lpSkill = &Strike_Sanhua;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Strike_Hanbing"))
	{
		lpSkill = &Strike_Hanbing;
		return lpSkill;
	}

	return NULL;
}
*/
/*
CSkill * GetSwordSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Sword_Damo"))
	{
		lpSkill = &Sword_Damo;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Sword_Emei"))
	{
		lpSkill = &Sword_Emei;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Sword_Pixie"))
	{
		lpSkill = &Sword_Pixie;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Sword_Dugu"))
	{
		lpSkill = &Sword_Dugu;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Sword_Huashan"))
	{
		lpSkill = &Sword_Huashan;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Sword_Taiji"))
	{
		lpSkill = &Sword_Taiji;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Sword_Fumo"))
	{
		lpSkill = &Sword_Fumo;
		return lpSkill;
	}
	return NULL;
}
*/
/*
CSkill * GetThrowingSkill(CString szEName)
{
	//CSkill * lpSkill;
	return NULL;
}
*/
/*
CSkill * GetUnarmedSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Unarmed_Meihua"))
	{
		lpSkill = &Unarmed_Meihua;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Unarmed_Xianglong"))
	{
		lpSkill = &Unarmed_Xianglong;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Unarmed_Yijianmei"))
	{
		lpSkill = &Unarmed_Yijianmei;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Unarmed_Mizhong"))
	{
		lpSkill = &Unarmed_Mizhong;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Unarmed_Huashan"))
	{
		lpSkill = &Unarmed_Huashan;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Unarmed_Taiji"))
	{
		lpSkill = &Unarmed_Taiji;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Unarmed_Xingxiu"))
	{
		lpSkill = &Unarmed_Xingxiu;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Unarmed_Hou"))
	{
		lpSkill = &Unarmed_Hou;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Unarmed_Kongming"))
	{
		lpSkill = &Unarmed_Kongming;
		return lpSkill;
	}
// Spock start
	else if(!stricmp(szEName, "Cuff_Luohan"))
	{
		lpSkill = &Cuff_Luohan;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Cuff_Poyu"))
	{
		lpSkill = &Cuff_Poyu;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Cuff_Jingang"))
	{
		lpSkill = &Cuff_Jingang;
		return lpSkill;
	}
// Spock end
	return NULL;
}
*/
/*
CSkill * GetWhipSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Whip_Riyue"))
	{
		lpSkill = &Whip_Riyue;
		return lpSkill;
	}
	return NULL;
}
*/
/*
CSkill * GetComboSkill(CString szEName)
{
	CSkill * lpSkill;
	if(!stricmp(szEName, "Sword_Pixie"))
	{
		lpSkill = &Sword_Pixie;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Sword_Dugu"))
	{
		lpSkill = &Sword_Dugu;
		return lpSkill;
	}
	else if(!stricmp(szEName, "Strike_Hunyuan"))
	{
		lpSkill = &Strike_Hunyuan;
		return lpSkill;
	}
	return NULL;
}

*/