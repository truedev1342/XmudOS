#ifndef __NPC_H__
#define __NPC_H__

#include "..\Player.h"
#include "..\common.h"
#include "..\Goods\Goods\Goods.h"
#include "..\Skill\Skill\skill.h"

#define NP_friendly		0x1		//是否友好
#define NP_apprentice	0x2		//是否可以拜師
#define NP_attack		0x4		//是否會主動攻擊
#define NP_nofight		0x8		//是否可以和你fight
#define NP_doquest		0x10	//可否問問題
#define NP_dotask		0x20	//有沒有任務給你
#define NP_acceptsell	0x40	//是否允許玩家賣東西給他
#define NP_acceptbuy	0x80	//是否允許玩家買他的東西
#define NP_heroism		0x100	//只打不逃的傻冒
#define NP_guard		0x200	//保衛所在地圖
#define NP_randomappear	0x400	//NPC會隨機出現在無人的地圖
#define NP_randomwalk	0x800	//NPC會隨機走動
// Nuke start: NPC 的對話
#define NPCASK_visible	0x1		//是否在列表中
#define NPCASK_newline	0x2		//是否在訊息前插入空白行
#define NPCASK_execute	0x4		//是否執行程式
// Nuke end
// Spock +1
#define MAXASK	15


#define TRet_return(str) {	ri.szRet = (str); return ri; }

typedef struct tagGivingCondition{
	CString szSkillEName;
	int nLevel;
    tagGivingCondition(){
		szSkillEName = "";
		nLevel = 0;
	}
}TGivingCondition;

typedef struct tagGiving{
	CString szGoodsEName;    //物品
	int nFlag;               //旗標
	CList <TGivingCondition *,TGivingCondition *> listCondition;  //給物條件
	tagGiving(){
		szGoodsEName = "";
		nFlag = 0;
	}
}TGivingGoods;


class CNpc : public CActiveObject
{
public:
	CString szLong;//NPC的介紹
	int nAttitude;//例如友好,攻擊,等等
	// Spock +1
	int nRecover;
	// Nuke start
	int nAsk;//對話數量
	CString szAsk[MAXASK];//NPC的對話資料,關鍵字
	int nAskAttribute[MAXASK];//屬性,0:不可見,1:可見
	CString szNpcAsk[MAXASK];//NPC回話
	CList <TGivingGoods *,TGivingGoods *> listGiving;
	// Nuke end
public:
	CNpc();
	virtual ~CNpc();
	void Healing();
	void AppToMap(CNpc * lpNpc);
	BOOL AddAsk(const char *key, int attribute,const char *data);
	virtual TRetInfo DoFight(CActiveObject *who);
	virtual TRetInfo DoKill(CActiveObject *who);
	virtual TRetInfo DoLook(CPlayerInfo *who, CString szName);
	
	virtual TRetInfo DoAsk(CPlayerInfo *who, CString szName);
	virtual TRetInfo DoAsk(CPlayerInfo *who, CString szName,CString szTarget);
	virtual TRetInfo GivingBook(CPlayerInfo *who,CString szSkillEName);

	virtual CString DoAskTask(CPlayerInfo *who);
	virtual TRetInfo DoApprentice(CPlayerInfo *who);
	virtual void DoEmote(CPlayerInfo *who, CString szEmote);
	// Spock start
	virtual void FightWin(CPlayerInfo *who);
	virtual void KillWin(CPlayerInfo *who);
	// Spock end
};

//小販
/*class CSellNpc : virtual public CNpc
{
public:
	CSellNpc();
	virtual ~CSellNpc();
	virtual CString DoBuy(CActiveObject *who, CGoods *lpGoods);
	virtual CString DoSell(CActiveObject *who,CGoods *lpGoods);
};
*/
void InitAllNpc();

#endif