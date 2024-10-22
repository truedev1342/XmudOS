// combat.cpp: 完全是計算一招格斗的程序
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XMudOS.h"
#include "CmdPlayerLogon.h"
#include "skill\skill\Skill.h"
#include "goods\goods\Goods.h"
// Robin P
#include "npc\map\guanhua\N_EventNpc.h"
// Spock +1
#include <math.h>

// guanhua 2000/10/02 start
#include "fight.h"
#include "map\mapinfo.h"
#include <vector>

using namespace std;

extern rmfullglobals myglobs;
// guanhua 2000/10/02 end

static int skill_power(CActiveObject *who, int usage,TObjectSkill *lpTObjSkill);
static int force_hit_ob(CActiveObject *me, CActiveObject *you, CString &strRet, int nWhere);

//////////////////////////////////////////////////////////////////////
#define sp_attack 1
#define sp_dodge  2
#define sp_parry  3

#define action_msg			'1'
#define doage_msg			'2'
#define parry_msg			'3'
#define unarmed_parry_msg	'4'
#define fight_status_msg	'5'
#define kill_status_msg		'6'
#define winner_msg			'7'
#define add_force_msg		'8'
#define guard_msg			'9'
#define damage_msg			'a'
#define catch_hunt_msg		'b'


CString randomlimbs(int &nWhere)
{
	#define MAXLIMB_MAN 9
	CString strRet;

	if(nWhere == -1)
		nWhere = random(MAXLIMB_MAN);
	switch(nWhere)
	{
	//注意,這里和裝備的位置是相關的,請不要隨意修改值和對應的攻擊位置
	case 0:	strRet = "頸部"; break;
	case 1:	strRet = "胸部"; break;
	case 2:	strRet = "腹部"; break;
	case 3:	strRet = "臂";   break;
	case 4:	strRet = "腿";   break;
	case 5:	strRet = "頭部"; break;
	case 6:	strRet = "手";   break;
	case 7: strRet = "腳";   break;
	case 8:	strRet = "肩";   break;
	}
	if((nWhere >= 4)&&(nWhere != 5))
	{
		if(random(2))
			strRet = "左" + strRet;
		else
			strRet = "右" + strRet;
	}
	nWhere = 1<<nWhere;
	if(nWhere < EW_head)
		nWhere |= EW_body;
	return strRet;
}

CString GetKindsMsg(CString type, int n)
{
	CString strRet;
	strRet.Format("%%%s,%d%%", type, n);
	return strRet;
}

CString GetKindsMsg(CString type, CString FileName, int n)
{
	CString strRet;
	strRet.Format("%%%s,%s,%d%%", type, FileName, n);
	return strRet;
}

//返回某人的狀態
CString report_status(CActiveObject *who, BOOL bWound)
{
	CString strRet;
	int n;
	CString status_msg;
	if(!bWound)
	{
		n = who->nEff_qi * 100 /  who->GetMaxQi() ;
		status_msg = fight_status_msg;
	}
	else
	{
		n = who->nMax_qi * 100 /  who->GetMaxQi();
		status_msg = kill_status_msg;
	}

	strRet.Format("($n%%%s,%d%%)%s", status_msg, n, PARM);
	return strRet;
}

// 這個函數計算人物的某種技能的力量(攻擊力\防御力\輕功逃避力)
// usage = 1   attack
// usage = 2   doage
// usage = 3   defance
int skill_power(CActiveObject *who, int usage, TObjectSkill *lpTObjSkill)
{
	int level1, level2, power;
	CString szSkillName,szBaseSkillName;
	TObjectSkill *lpTSkill = NULL;
	//cary add
	int iRet;
	if(who->nEff_jing >0)
		who->nEff_jing-=1;
	//
	switch(usage){
	case sp_attack:
		if (who->nStatus == AOS_fight) {
			szBaseSkillName = "BaseUnarmed";
		} else {
			szBaseSkillName = who->GetAttackBaseSkill();
		}
		break;
	case sp_dodge:
		szBaseSkillName = "BaseDodge";
		break;
	case sp_parry:
		szBaseSkillName = "BaseParry";
		break;
	}
	level1 = who->GetSkillLevel(szBaseSkillName);
	szSkillName = who->GetSkillMap(szBaseSkillName);
	level2 = who->GetSkillLevel(szSkillName);
	if (level2 <= 0) {
		szSkillName = szBaseSkillName;
		level2 = 0;
	}

	lpTSkill = who->GetTSkill(szSkillName);
	// Spock start
	if (lpTSkill == NULL) {
		switch (usage) {
		case sp_attack:
			lpTObjSkill->lpSkill = GetSkillClass("BaseUnarmed");
			break;
		case sp_dodge:
			lpTObjSkill->lpSkill = GetSkillClass("BaseDodge");
			break;
		case sp_parry:
			lpTObjSkill->lpSkill = GetSkillClass("BaseParry");
			break;
		}
		lpTObjSkill->nLevel = 0;
		lpTObjSkill->nScore = 0;
		lpTObjSkill->szMapping = CString("");
	} else {
		lpTObjSkill->lpSkill = lpTSkill->lpSkill;
		lpTObjSkill->nLevel = lpTSkill->nLevel;
		lpTObjSkill->nScore = lpTSkill->nScore;
		lpTObjSkill->szMapping = lpTSkill->szMapping;
	}

	power = (int)exp(log(who->nCombat_exp)/3);
	iRet = power + level1 + level2 + 2;
	if (who->nMax_qi > 0) {
		iRet = (((iRet*3)/4)*who->nMax_qi)/who->GetMaxQi() + (iRet / 4);
	} else {
		iRet = 0;
	}
//cary add
	if(who->nEff_jing <=0)
		iRet>>=2;
	return iRet;
}

//裝備保護玩家,但自身也受損
#define EP_force  1
#define EP_damage 2
void EquipProtect(CActiveObject *you, int nType, int &damage, int nWhere)
{
	int nRet = 0;
	CGoods * lpGoods;
	CEquip * lpEquip;
	char szTxt[128];

	if (you == NULL)
		return;
	if (damage <= 0) {
		damage = 0;
		return;
	}
	POSITION pos = you->listequip.GetHeadPosition();
	while(pos != NULL)	{
		lpGoods = you->listequip.GetNext(pos);
		if(lpGoods->lpGoods->nKinds & GK_equip)	{	//如果是裝備
			lpEquip = dynamic_cast<CEquip *>(lpGoods);
			if(lpEquip->nWearWhere & nWhere)	{	//穿到了挨打的地方
				switch(nType)	{
				case EP_force:
					nRet += lpEquip->lpEquip->nDefanceForce;//防御內力
					if (you->bPlayer && (you->nStatus == AOS_kill)
						&& !(lpEquip->lpGoods->nUsage & GP_noold))
						lpEquip->nNew -= damage >> 6;//裝備受損
					break;
				case EP_damage:
					nRet += lpEquip->lpEquip->nDefance;//一般防御
					if (you->bPlayer && (you->nStatus == AOS_kill)
						&& !(lpEquip->lpGoods->nUsage & GP_noold))
						lpEquip->nNew -= damage >> 5;//裝備受損
					break;
				}

				if (lpEquip->nNew <= 0 && you->bPlayer) {
					sprintf(szTxt, "%s %s %s的%s在戰鬥中被打壞了！", SZOKMSG, szCyanHigt,
						you->szCName, lpEquip->lpGoods->szCName);
					you->SendMsg(szTxt);
					you->SendMsgToAll(szTxt);
					CString szStatus;
					switch(lpEquip->lpEquip->nWhereWear){
					case EW_neck:
						szStatus = "護頸";
						break;
					case EW_chest:
						szStatus = "護胸";
						break;
					case EW_abdomen:
						szStatus = "護腹";
						break;
					case EW_wrist:
						szStatus = "護腕";
						break;
					case EW_knee:
						szStatus = "護膝";
						break;
					case EW_head:
						szStatus = "護頭";
						break;
					case EW_hand:
						szStatus = "護手";
						break;
					case EW_foot:
						szStatus = "護腳";
						break;
					case EW_body:
						szStatus = "護身";
						break;
					}
					sprintf(szTxt, "%s %s %s %d %s", SZSUBGOODS,
						lpEquip->lpGoods->szCName, szStatus, 1, lpEquip->lpGoods->szUnit);
					you->SendMsg(szTxt);
					you->SubGoods(lpEquip->lpGoods->szEName);
				}
			}//if 穿到了挨打的地方
		}//如果是裝備
	}//while
	damage -= nRet;
	if( damage < 0 ) damage = 0; 
//	return nRet;
}

//內力的攻擊效果
int force_hit_ob(CActiveObject *me, CActiveObject *you, CString &strRet, int nWhere)
{
/*	if(me->nEff_force > me->nAdd_force)
		me->nEff_force -= me->nAdd_force;
	else
	{
		me->nAdd_force = 0;
		return;
	}
	
	int damage = me->nEff_force/20 + me->nAdd_force - you->nEff_force/25;
*/
	int damage = 0;

	damage = random( (me->nMax_force / 5)+ me->nAdd_force *60) +
							(me->nMax_force - you->nMax_force) / 20;
	if( damage < 0 )	{
		if(me->lpWeapon == NULL)	{
			damage = - damage;
			me->nEff_qi -= damage * 2 ;
			if (me->nStatus == AOS_kill) me->nMax_qi -= damage ;
//			strRet += GetKindsMsg(add_force_msg, damage);
//			strRet += PARM;
		}
		damage = 0;
	}
//	} else {
	//減去你的裝備的抗內力值
//		EquipProtect(you, EP_force, damage, nWhere);
//	}
/*	if( damage_bonus + damage < 0 ) 
		damage_bonus = 0;
	else
		damage_bonus += damage;
*/
	return damage;
}

//增加一項值(缺省加一)

//ANDY_331
BOOL Improve(CActiveObject *me, TObjectSkill *lpTSkill, int number)
{
	if(lpTSkill->nLevel * lpTSkill->nLevel * lpTSkill->nLevel / 30 > me->nCombat_exp)
	{
		return FALSE;//如果經驗不夠則傳回 FALSE 
	}
	else
		lpTSkill->nScore += number;
	while((lpTSkill->nScore >= lpTSkill->nLevel*lpTSkill->nLevel) &&
			(lpTSkill->nLevel * lpTSkill->nLevel * lpTSkill->nLevel / 30 <= me->nCombat_exp))
	{
		lpTSkill->nScore -= lpTSkill->nLevel*lpTSkill->nLevel;
		lpTSkill->nLevel++;
		if(lpTSkill->lpSkill->szEName == "BaseDodge")	{
			if(lpTSkill->nLevel%10 == 0)
				me->nDex++;	}
		else if(lpTSkill->lpSkill->szEName == "BaseUnarmed")
		{
			if(lpTSkill->nLevel%10 == 0)	{
				me->nStr++;
				if (me->bPlayer)	{
					CPlayerInfo *lpPlayer = (CPlayerInfo*)me;
					lpPlayer->nMax_Drink = lpPlayer->nStr*10;
					lpPlayer->nMax_Eat = lpPlayer->nStr*10;	}	}
		}
		else if(lpTSkill->lpSkill->szEName == "BaseForce")
		{
			if(lpTSkill->nLevel%10 == 0)
			me->nCon++;
		}
		else if(lpTSkill->lpSkill->szEName == "OtherLiterate")
		{
			if(lpTSkill->nLevel%10 == 0)
			me->nInt++;
		}

	}
	return TRUE;
}
/*
BOOL Improve(CActiveObject *me, TObjectSkill *lpTSkill, int number)
{
	lpTSkill->nScore += number;
	if(lpTSkill->nScore >= lpTSkill->nLevel*lpTSkill->nLevel)
	{
		if(lpTSkill->nLevel * lpTSkill->nLevel * lpTSkill->nLevel / 30 <= me->nCombat_exp)
		{
			lpTSkill->nScore -= lpTSkill->nLevel*lpTSkill->nLevel;
			lpTSkill->nLevel++;
			if(lpTSkill->lpSkill->szEName == "BaseDodge")
			{
				if(lpTSkill->nLevel%10 == 0)
					me->nDex++;
			}
			else if(lpTSkill->lpSkill->szEName == "BaseUnarmed")
			{
				if(lpTSkill->nLevel%10 == 0)
				{
					me->nStr++;
					if (me->bPlayer) {
						CPlayerInfo *lpPlayer = (CPlayerInfo*)me;
						lpPlayer->nMax_Drink = lpPlayer->nStr*10;
						lpPlayer->nMax_Eat = lpPlayer->nStr*10;
					}
				}
			}
			else if(lpTSkill->lpSkill->szEName == "BaseForce")
			{
				if(lpTSkill->nLevel%10 == 0)
					me->nCon++;
			}
			else if(lpTSkill->lpSkill->szEName == "OtherLiterate")
			{
				if(lpTSkill->nLevel%10 == 0)
					me->nInt++;
			}
			return TRUE;
		}
		else
		{
			lpTSkill->nScore -= number;
			return FALSE;
		}
	}
	return TRUE;
} */
//ANDY_END
//把待發的字符串加上頭
CString TurnMsgToSend(CActiveObject *me, CActiveObject *you, CString strSend, CString strLimbs)
{	
	CString strRet;
	int len = 0;
	strRet = CString(SZFIGHTMSG) + (" ");
	strRet += PARM;
	//andy_add reEdit Playername 2002/01/20 11:16
	strRet += me->szCName+(".");//$N
	strRet += PARM;
	strRet += you->szCName+(".");//$n
	strRet += PARM;
	strRet += strLimbs;//$l
	strRet += PARM;
	if(you->szSex[0] == 'M')//$p
		strRet += "他";
	else
		strRet += "她";
	strRet += PARM;
	if((me->lpWeapon != NULL) && (me->nStatus == AOS_kill))
		strRet += me->lpWeapon->lpGoods->szCName;//$w
	else
		strRet += "手掌";
	strRet += PARM;
	if((you->lpWeapon != NULL) && (you->nStatus == AOS_kill))
		strRet += you->lpWeapon->lpGoods->szCName;//$v
	else
		strRet += "手掌";
	strRet += PARM;
	return strRet+strSend;
}

// Spock start
int GetExp(CActiveObject *me, CActiveObject *you, int n)
{
	int p1, p2;
	p1 = (int)exp(log(you->nCombat_exp)/3);
	p1 += you->GetSkillLevel(you->GetAttackBaseSkill())
		+ you->GetSkillLevel("BaseDodge") + you->GetSkillLevel("BaseParry")
		+ you->GetSkillLevel("BaseForce");
	p2 = (int)exp(log(me->nCombat_exp)/3);
	p2 += me->GetSkillLevel(me->GetAttackBaseSkill())
		+ me->GetSkillLevel("BaseDodge") + me->GetSkillLevel("BaseParry")
		+ me->GetSkillLevel("BaseForce");
	return n * p1 / p2;
}

int GetQianNeng(CActiveObject *me, CActiveObject *you, int n)
{
	int p1, p2;
	p1 = (int)exp(log(you->nCombat_exp)/3);
	p1 += you->GetSkillLevel(you->GetAttackBaseSkill())
		+ you->GetSkillLevel("BaseDodge") + you->GetSkillLevel("BaseParry")
		+ you->GetSkillLevel("BaseForce");
	p2 = (int)exp(log(me->nCombat_exp)/3);
	p2 += me->GetSkillLevel(me->GetAttackBaseSkill())
		+ me->GetSkillLevel("BaseDodge") + me->GetSkillLevel("BaseParry")
		+ me->GetSkillLevel("BaseForce");
	return n * p1 / p2;
}
// Spock end

// 計算一次攻擊帶來的變化
BOOL DoAttack(CActiveObject *me, CActiveObject *you, CString &strRet, CString &szMsg)
{//我是攻擊者,你是我的攻擊對象
	TRetInfo ri;
	strRet = "";//發送給大家的數據
	CString szTmp,szTmp2;
	TObjectSkill *lpTSattack = new TObjectSkill, 
		*lpTSdodge = new TObjectSkill, *lpTSparry = new TObjectSkill;
	TFeat * lpFeat;
	int Other_dam = 0;
	CString CS_dam;
	int ap, dp, pp;
	int damage = 0, damage_bonus = 0, defense_factor = 0;
	int nWhere;//攻擊的位置
	BOOL bWound = FALSE;//受傷否
	CString szWhere;
	// Spock start
	int nGetMoney, nExp, nQianNeng;
	// Spock end
	//計算格斗的攻擊力,攻擊招數,對手的防御能力,再算出格斗所改變的各項屬性.
	ap = skill_power(me, sp_attack, lpTSattack);
	dp = skill_power(you, sp_dodge, lpTSdodge);

	dp = dp * you->nDex / 20;
	if( you->nBusy )
		dp /= 2;

	pp = skill_power(you, sp_parry, lpTSparry);
	if( (you->lpWeapon != NULL) && (me->lpWeapon==NULL) && (you->nStatus == AOS_kill) )	{
		pp += you->lpWeapon->lpWeapon->nDefance;
		if( me->lpWeapon == NULL ) 
			pp = pp * 9 / 8;
	}
	if ((me->lpWeapon!=NULL) && (you->lpWeapon==NULL) && (me->nStatus==AOS_kill)) {
		pp = pp * 7 / 8;
	}

	if(pp > 0)	{
		if( you->nBusy ) 
			pp /= 2;
	}
	if( ap < 1)  return FALSE;
	// (2) 找到攻擊者要出那一招.

	lpFeat = lpTSattack->lpSkill->GetFeat(me);
	strRet = GetKindsMsg(action_msg, lpTSattack->lpSkill->szEName, lpFeat->nSN);
	strRet += "！";
	strRet += PARM;
	dp = ( dp * lpFeat->nDodge / 100 ) + ( you->nDex *0.25);
	pp = ( pp * lpFeat->nParry / 100 ) + ( you->nCon *0.2);

	if( you->nMax_jing > 0 )	{
		dp = dp * ( ( you->nEff_jing / you->nMax_jing )+0.15 );
	}
	if( you->nMax_qi > 0 )	{
		pp = pp * ( ( you->nEff_qi / you->nMax_qi )+0.1 ) ;
	}

	if( dp < 1 )	dp = 1;
	if( pp < 1 )	pp = 1;

	//攻擊的地方
	nWhere = -1;
	szWhere = randomlimbs(nWhere);
	// (3) Fight! 檢查被攻擊者能否用輕功躲過去(dodge)
	if( random( (ap + dp ) )< dp )	{
		//加入輕功躲避成功的字符串
		strRet += lpTSdodge->lpSkill->GetDodgeMsg(you);
		strRet += PARM;
		// Spock start: 增加經驗值
		if (random(ap + dp) > dp)	{
			if (you->bPlayer) {
				you->nCombat_exp++;
				if (random(3) == 0) {
					Improve(you, you->GetTSkill("BaseDodge"));
				}
			}
			// 增加潛能
			if ( me->bPlayer && (me->nQianNeng < me->GetSkillLevel("OtherLiterate")*3 + 20) ) {
				me->nQianNeng++;
			}
		}
		// Spock end
	}else	{	//      (4) 檢查被打者能否躲過這次攻擊(parry)
		if(random(ap + pp) < pp )	{
			//得到格擋的字符串
			strRet += lpTSparry->lpSkill->GetParryMsg(you);
			strRet += PARM;
			// Spock start: 增加經驗值
			if (random(ap+pp) > pp) {
				if(you->bPlayer) {
					you->nCombat_exp++;
					if ( random(3) == 0 ) {
						Improve(you, you->GetTSkill("BaseParry"));
					}
				}
				// 增加潛能
				if ( me->bPlayer && (me->nQianNeng < me->GetSkillLevel("OtherLiterate")*3 + 20) ) {
					me->nQianNeng++;
				}
			}	// Spock end
		}else	{
			//      (5) 打中了
			// Spock start: 增加經驗值
			if ( me->bPlayer ) {
				me->nCombat_exp++;
				if ( random(3) == 0 ) {
					Improve(me, me->GetTSkill(me->GetAttackBaseSkill()));
				}
			}
			// 臂力及武器
			damage = ( me->nStr * 1.1 )+(me->nCon*0.4)+(me->nDex*0.3)+(me->nInt*0.1) ;
			damage -= ( you->nCon * 0.2 )+( you->nDex * 0.1 );
#define Random( n) ( ( (rand()%n)> 100 )?100:(rand()%n))
			if( (me->nStr-you->nCon) < 5 && (me->nStr-you->nCon) > 0 )
				damage += Random( me->nStr + (me->nStr /3));
			if ((me->lpWeapon != NULL) && (me->nStatus == AOS_kill)) {
				damage += me->lpWeapon->lpWeapon->nAttack;
			}
			// 將高級武術的傷害效果減弱
			if (lpFeat->nDamage > 100)
				damage += damage * (lpFeat->nDamage - 100) / 400;
			else
				damage = damage * lpFeat->nDamage / 100;
			damage = damage - random(damage / 3);
			EquipProtect(you, EP_damage, damage, nWhere);//you的裝備抗攻擊能力
			// 內力效果
			damage_bonus = force_hit_ob(me, you, strRet, nWhere);
			// 將高級武術的內力效果減弱
			if (lpFeat->nForce > 100)
				damage_bonus += damage_bonus * (lpFeat->nForce - 100) / 400;
			else
				damage_bonus = damage_bonus * lpFeat->nForce / 100;
			EquipProtect(you, EP_force, damage_bonus, nWhere);

			damage += damage_bonus;
			if( you->nCon > 0 )	{
				damage = damage * me->nStr / you->nCon;
			}
			if (me->nEff_qi <= 50)
				damage /= 2;
			if( you->nMax_qi < 0 || you->nMax_jing < 0 )	{
				Other_dam = 1;
			}else	{
				Other_dam = (	( ( you->nEff_jing / you->nMax_jing ) + 0.45 ) + 
								( ( you->nEff_qi / you->nMax_qi )+0.35 )	) / 2;
			}
			if( Other_dam <= 0 )
				Other_dam = 1;
			damage = damage * Other_dam;
			// Spock end
			//      (6) 造成傷害
			if(damage > 0)	{	// Spock start: 增加潛能

				if( damage > 500 && you->nEff_jing > 20 )	{
					you->nEff_jing -= 25;
				}else if( damage > 1000 && you->nEff_qi > 1000 && you->nEff_jing > 10 )	{
					you->nEff_jing -= 55;
				}
				if ( you->bPlayer && (you->nQianNeng < you->GetSkillLevel("OtherLiterate")*3 + 20) ) {
					you->nQianNeng++;
				}	// Spock end
				you->nEff_qi -= damage;
				if (me->nStatus == AOS_kill)	{
					you->nMax_qi -= damage;
					bWound = TRUE;
				}
			}
			strRet += GetKindsMsg( damage_msg, lpFeat->szDamageType, damage);
			strRet += PARM;
		}
    }


	if( damage > 1 )	{
		CS_dam.Format("%s 你受到%d的傷害!",SZOKMSG,damage);
		you->SendMsg( CS_dam);
		CS_dam.Format("%s 你損傷了對手%d的傷害!",SZOKMSG,damage);
		me->SendMsg( CS_dam);
	}
	if( damage > 0 ) 
		strRet += report_status(you, bWound);
	if(you->nStatus==AOS_kill)	{
		if(you->nMax_qi <= 0)	{
			you->nMax_qi = 0;
			you->nStatus = AOS_unconcious;
			// Spock start: 殺死對手後改變「錢、神、殺戮」
			nGetMoney = you->nMoney / 2;
			if (nGetMoney<0) nGetMoney = 0;
			if (me->bPlayer) {
				me->nMoney += nGetMoney;
				if (me->nMoney > MAXMONEY) me->nMoney = MAXMONEY;
				if (me->nMoney < 0) me->nMoney = 0;

				if ( dynamic_cast <CPlayerInfo*> (me)->bAttack) { // 主動攻擊者
					double meExp, youExp, youShen;

					if(me->nCombat_exp > 0) {
						meExp = (double)sqrt(me->nCombat_exp);
					} else {
						meExp = 1;
					}
					youExp = (double)sqrt(you->nCombat_exp)/meExp;
					if(youExp > 1) youExp = 1;
					youShen = (double)you->nShen;
					if(fabs(youShen) > (double)me->nCombat_exp) {
						if (youShen > 0) 
							youShen = (double)me->nCombat_exp;
						else 
							youShen = -(double)me->nCombat_exp;
					}

					me->nShen -= (int)(youShen*youExp);
					if(me->nShen > MAXSHEN) me->nShen = MAXSHEN;
					if(me->nShen < -MAXSHEN) me->nShen = -MAXSHEN;
				}
				if (you->bPlayer) {
					dynamic_cast<CPlayerInfo*>(me)->nKillPlayer++;
				} else {
					dynamic_cast<CPlayerInfo*>(me)->nKillNpc++;
				}
				// 增加經驗和潛能
				if (me->bPlayer)	{// Spock +1
					nExp = GetExp(me, you, 4);
					nQianNeng = GetQianNeng(me, you, 4);
					me->nCombat_exp += nExp;
					me->nQianNeng += nQianNeng;
					if(me->nQianNeng > me->GetSkillLevel("OtherLiterate")*3 + 20 )	{
						me->nQianNeng = me->GetSkillLevel("OtherLiterate")*3 + 20;
					}
				}
				me->szPerson = you->szEName; // 記錄打倒的對手
				szMsg.Format("%s %s 你打倒%s後得到銅錢%d",SZOKMSG,szCyanHigt,you->szCName,nGetMoney);

				// Robin P
				// Kill Win
				if(you->g_HasEvent == 1)	{
					ri = dynamic_cast<CN_EventNpc*>(you)->DoAsk(dynamic_cast<CPlayerInfo*>(me),"_killwin");
					//if(ri.szRet != "你去找別人吧，我不知道。")
					if((ri.szRet != "你去找別人吧，我不知道。") && (ri.szRet != ""))	{
						szMsg.Format("%s %s %s",SZOKMSG,szCyanHigt,ri.szRet);
					}
				}
				// Robin E
			}
			if (you->bPlayer) {
				you->nMoney -= nGetMoney;
				if (you->nMoney < 0) you->nMoney = 0;
				dynamic_cast<CPlayerInfo*>(you)->nKilled++; // 被殺次數
				if(me->g_HasEvent == 1)	{	// Kill Lost
					ri = dynamic_cast<CN_EventNpc*>(me)->DoAsk(dynamic_cast<CPlayerInfo*>(you),"_killlost");
					if((ri.szRet != "你去找別人吧，我不知道。") && (ri.szRet != ""))	{
						szMsg.Format("%s %s %s",SZOKMSG,szCyanHigt,ri.szRet);
						you->SendMsg(szMsg);
					}
				}
			}// Spock end
		}
		if(you->nEff_qi < 0)
			you->nEff_qi = 0;
	}else if( you->nEff_qi <= 0 && me->nStatus == AOS_fight && you->nStatus == AOS_fight )	{
		strRet += GetKindsMsg( winner_msg, random(6) );
		me->szPerson = you->szEName; // 記錄打倒的對手
		if(you->g_HasEvent == 1)	{	// Fight Win
			ri = dynamic_cast<CN_EventNpc*>(you)->DoAsk(dynamic_cast<CPlayerInfo*>(me),"_fightwin");
			if((ri.szRet != "你去找別人吧，我不知道。") && (ri.szRet != ""))	{
				szMsg.Format("%s %s %s",SZOKMSG,szCyanHigt,ri.szRet);
			}
		}
		if(me->g_HasEvent == 1)	{	// Fight Lost
			ri = dynamic_cast<CN_EventNpc*>(me)->DoAsk(dynamic_cast<CPlayerInfo*>(you),"_fightlost");
			if((ri.szRet != "你去找別人吧，我不知道。") && (ri.szRet != ""))	{
				szMsg.Format("%s %s %s",SZOKMSG,szCyanHigt,ri.szRet);
				you->SendMsg(szMsg);
			}
		}
	}
	strRet = TurnMsgToSend(me,you,strRet,szWhere);
	delete lpTSattack;
	delete lpTSdodge;
	delete lpTSparry;
	return TRUE;
}
//ANDY_ERROR
BOOL DoErrorLog(CActiveObject *kme, CActiveObject *kyou, int killlive)
{
	FILE *fp;
	fp = fopen( "error.txt", "a+");
	if( fp)	{
		fprintf(fp,"%s %s \t %s %s \t %d \n", kme->szCName, kme->szEName, kyou->szCName, kyou->szEName, killlive);
		fclose( fp);
	}
	return TRUE;
}

// guanhua 2000/10/01 start
bool DoEscape(CActiveObject *me, CString &strMapCName, CString &strMapEName)
{

	if(!(me->bPlayer))	{
		strMapCName = "Error";
		strMapEName = "Error";
		AddRecordMsg("DoEscape() end when Error: Npc Escape");
		return FALSE;
	}
	
	CPlayerInfo* lpEscapePlayer = (CPlayerInfo*) me;
	CString szRet;
	int nMySpeed = 1, nOppSpeed = 1, nMaxOppSpeed = 1;
	CString szResult;
	CString szMsg;

	if( (lpEscapePlayer->nStatus != AOS_kill)	||	// [非死鬥狀態]及忙碌 不可逃走
		(lpEscapePlayer->nBusy > 1) )	{
		strMapCName = "Error";
		strMapEName = "Error";
		return FALSE;
	}
	// 計算逃走是否成功
	int nlevel = 0;
	CString szSkillName;
	CSkill *lpSkill = NULL;

	szSkillName = lpEscapePlayer->GetSkillMap("BaseDodge");
	if(szSkillName != "")	{
		nlevel = lpEscapePlayer->GetSkillLevel(szSkillName);
		lpSkill = GetSkillClass(szSkillName);
		nMySpeed = (lpEscapePlayer->nDex - 20) * 10 + nlevel * (lpSkill->nDodge + 1) / 10;
	}else	{
		nMySpeed = (lpEscapePlayer->nDex - 20) * 10;
	}

	if(nMySpeed < 1)	{
		nMySpeed = 1;
	}

	/*	int		nEff_qi;	//有效氣
	int		nMax_qi;	//最大氣,當前的,受傷後會減少
	int		nEff_jing;	//有效精
	int		nMax_jing;	//最大精
	*/
	if( ( me->nMax_qi < 1 ) || ( me->nMax_jing < 1 ) )	{
		nMaxOppSpeed = 0;
	}else	{
		nMaxOppSpeed = nMySpeed * ((( me->nEff_qi / me->nMax_qi ) + ( me->nEff_jing / me->nMax_jing ))/2);
	}
	if( (random(( nMySpeed + nMaxOppSpeed) ) * 5) < (nMySpeed * 4) )	{	// 2.逃走失敗
		strMapCName = "Cannot";
		strMapEName = "Cannot2";
		return TRUE;
	}
	// 逃走成功 (判定留在原地圖中或逃入其他地圖)
	EnterCriticalSection(&myglobs.csMaplist);
	CBaseMap *lpCurrentMap = NULL, *lpMap = NULL, *lpEscapeMap = NULL;
	CNpc *lpNpc = NULL;
	POSITION posMap, posLastMap, posNpc, posExit;
	TMapExit *lpMapExit = NULL;
	CString szGuardFamily;
	char szGuardAsk[128] = "";
	vector<POSITION> vecEsacpeFamilyMapPos, vecEsacpeNonFamilyMapPos;
	if((lpEscapePlayer->szFamily != "華義國際") && (lpEscapePlayer->pMapPosite != NULL))	{
		lpCurrentMap = maplist.GetAt(lpEscapePlayer->pMapPosite);
		if (lpCurrentMap != NULL)	{	// 取得防衛地圖NPC之門派
			posNpc = lpCurrentMap->listNpc.GetHeadPosition();
			while( posNpc)	{
				lpNpc = lpCurrentMap->listNpc.GetNext(posNpc);
			
				if ((lpNpc->nStatus != AOS_dead)
					&& (lpNpc->szFamily == lpCurrentMap->szFamily)
					&& (lpNpc->szFamily != lpEscapePlayer->szFamily)
					&& (lpNpc->szFamily != "無門派")
					&& (lpNpc->nAttitude & NP_guard))
				{
					szGuardFamily = lpNpc->szFamily;
					break;
				}
			}
			int nMapIndex = 0;
			// 取得可通往之鄰近地圖(NPC不會阻擋之地圖)
			posExit = lpCurrentMap->listexit.GetHeadPosition();
			while(posExit)	{
				lpMapExit = lpCurrentMap->listexit.GetNext(posExit);
				posMap = maplist.GetHeadPosition();
				while(posMap)	{
					posLastMap = posMap;
					lpMap = maplist.GetNext(posMap);
					if( (lpMap->szEName == lpMapExit->szNexeMap) && (lpMap->szFamily != szGuardFamily))	{
						if(lpMap->szFamily == lpEscapePlayer->szFamily)	{
							vecEsacpeFamilyMapPos.push_back(posLastMap);
						}else	{
							vecEsacpeNonFamilyMapPos.push_back(posLastMap);
						}
						break;
					}
				}
			}
		} 
	} 
	int nEsacpeFamilyMap = vecEsacpeFamilyMapPos.size();
	int nEsacpeNonFamilyMap = vecEsacpeNonFamilyMapPos.size();
	lpEscapeMap = NULL;

	if(nEsacpeNonFamilyMap > 0)	{
		if((nEsacpeFamilyMap > 0) && (random(5) < 4))	{
			// 當同門派地圖數與非同門地圖數皆不為零時，有 80% 機率選擇同門派地圖
			lpEscapeMap = maplist.GetAt(vecEsacpeFamilyMapPos[random(nEsacpeFamilyMap)]);
		}else	{
			lpEscapeMap = maplist.GetAt(vecEsacpeNonFamilyMapPos[random(nEsacpeNonFamilyMap)]);
		}
	}else if(nEsacpeFamilyMap > 0)	{
		lpEscapeMap = maplist.GetAt(vecEsacpeFamilyMapPos[random(nEsacpeFamilyMap)]);
	}

	if(lpEscapeMap != NULL)	{
		strMapCName = lpEscapeMap->szCName;
		strMapEName = lpEscapeMap->szEName;
	}else	{
		strMapCName = "StayHere";
		strMapEName = "StayHere2";
	}

	LeaveCriticalSection(&myglobs.csMaplist);
	return TRUE;

// guanhua 2000/10/01 end
}
