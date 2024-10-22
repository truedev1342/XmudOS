#include "..\..\stdafx.h"
#include "N_Girl.h"
#include "../../../config.h"
#include "../../../CommandCheck.h"


extern rmfullglobals myglobs;

CN_Girl::CN_Girl()
{

	szCName = "小女孩";
	szEName = "HuaYi";
	szRoom = "xy_guangchang";
	szSex = "F" ;
	nAge =  12;
	szLong = "她是個面貌清秀的小女孩，隨伺在老婆婆身邊。";
	
	nCombat_exp =  2000;
	nShen = 1000;
	
	nStr = 14;
	nDex = 15;
	nCon = 16;
	nInt = 15;
	nAttitude = NP_friendly | NP_apprentice;
	nMoney = 0;

	// 跟郭襄一樣強
	SetSkill("BaseDodge",		180,0,"Step_Lingbo"	);
	SetSkill("BaseParry",		170);
	SetSkill("BaseForce",		160,0,"Force_Emei"	);
	SetSkill("BaseSword",		170,0,"Sword_Emei"	);
	SetSkill("BaseUnarmed",		150,0,"Unarmed_Meihua");
	SetSkill("Force_Emei",		160);
	SetSkill("Sword_Emei",		170);
	SetSkill("Unarmed_Meihua",	130);
	SetSkill("Step_Lingbo",		200);
	SetSkill("OtherTaoism",		100);
	SetSkill("OtherLiterate",	100);

	AddAsk("小女孩",NPCASK_visible,"華翼：嘻！我叫華翼，正陪著奶奶出來散心，\
別小看我，我的功夫很強的喔！");
	AddAsk("人在江湖",NPCASK_visible,"華翼：嗯，有什麼遊戲中的問題問我就對啦！");
	AddAsk("基本操作",NPCASK_visible|NPCASK_newline,"華翼：要移動的話，就在地圖上按滑鼠左鍵選\
目標。嘻！按住Ctrl再按左滑鼠鍵可以瞬間移動喔。在人物身上按滑鼠右鍵可以叫住人物\
，這時才可以開始下詢問或戰鬥等指令．．．哈！這個您應該已經會了:p");
	AddAsk("鏡頭操作",NPCASK_visible|NPCASK_newline,"華翼：按住Ctrl鍵不放，配合左右方向鍵\
可以轉動畫面，配合上下方向鍵可以放大縮小畫面，PageUp與PageDown鍵則是用來\
改變畫面角度的，多試試喔！");
	AddAsk("饑餓與口渴",NPCASK_visible|NPCASK_newline,"華翼：肚子餓到極點\
或是口很渴的時候，氣就會逐漸下降，如果你還不吃東西或喝水的話，最後會死翹翹喔！\
這些事都要多注意些才行耶！必要的時候啊，來找奶奶，她是可以幫你一把的！");
	AddAsk("防止耳語",NPCASK_visible|NPCASK_newline,"華翼：如果有討厭的人一直對你講語\
，你可以輸入DefindTell[人名]來拒絕聽他說話，想要取消的話輸入DefindDel[人名]就行了！");
	AddAsk("頻道主踢人",NPCASK_visible|NPCASK_newline,"華翼：開新頻道的人即為該頻道的頻道主\
，頻道主可以輸入GetOut[人名]來刪除頻道中其他的玩家，頻道主離頻的話由第二位入頻的人繼任頻道主！");
	AddAsk("查詢寄放物",NPCASK_visible|NPCASK_newline,"華翼：如果你有在錢莊寄放物品的話\
，可以隨時使用Rent指令來查看！");

//	AddAsk("饅頭",0,"華翼：我沒有饅頭啦，你得要花錢去跟小販買！");
//	AddAsk("水",0,"華翼：找小販買吧～～～～");
//	AddAsk("錢",0,"華翼：你要借我錢啊？");
	AddAsk("reboot",0,"");
	AddAsk("shutdown",0,"");

	CEquip * lpEquipGoods;
	
	lpEquipGoods = GetEquipClass("buqun");
	lpEquipGoods->nWearWhere = EW_body;
	listequip.AddTail(lpEquipGoods);

	szXFileName.Format("pmudsnv0%d",1);
}

CN_Girl::~CN_Girl()
{
}
// Spock start
TRetInfo CN_Girl::DoAsk(CPlayerInfo *who, CString szName)
{
	TRetInfo ri;
	CCommandCheck m_CommandCheck;
	CString szShout;
	ri = CNpc::DoAsk(who, szName, "$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	if((szName == "reboot") && (m_CommandCheck.CheckGM((char*)(LPCSTR)who->szUserName))) {
/*		EnterCriticalSection(&myglobs.csSentCliMsg);
		if(myglobs.g_SendToClientMsg.GetCount() < 100)
		{
			myglobs.g_SendToClientMsg.AddTail(CString(szShoutToAll) + 
				(" 系統公告：系統即將在一分鐘內重新啟動，請先行離線，稍侯再試。"));
		}
		LeaveCriticalSection(&myglobs.csSentCliMsg);*/
		szShout = "系統公告：系統即將在一分鐘內重新啟動，請先行離線，稍侯再試。";
		m_CommandCheck.ShoutProc(who, szShout, TRUE);
		ri.szRet = "華翼：系統公告已經發出！";
	}
	if((szName == "shutdown") && (m_CommandCheck.CheckGM((char*)(LPCSTR)who->szUserName))
		&& !myglobs.bShutdown) {
		myglobs.nRunTimes = 90;
		myglobs.bShutdown = TRUE;
		ri.szRet = "華翼：關機訊息已經發出！";
	}
	ri.bRet = TRUE;
	return ri;
}
TRetInfo CN_Girl::DoAsk(CPlayerInfo *who, CString szName, CString szTarget)
{
	TRetInfo ri;
	CCommandCheck m_CommandCheck;
	CString szShout;
	ri = CNpc::DoAsk(who, szName, "$NONE$");
	if (!ri.bRet) return ri;
	ri.bRet = FALSE;
	if((szName == "reboot") && (m_CommandCheck.CheckGM((char*)(LPCSTR)who->szUserName))) {
/*		EnterCriticalSection(&myglobs.csSentCliMsg);
		if(myglobs.g_SendToClientMsg.GetCount() < 100)
		{
			myglobs.g_SendToClientMsg.AddTail(CString(szShoutToAll) + (" 系統公告：") + szTarget);
		}
		LeaveCriticalSection(&myglobs.csSentCliMsg);*/
		szShout = CString("系統公告：") + szTarget;
		m_CommandCheck.ShoutProc(who, szShout, TRUE);
		ri.szRet = "華翼：系統公告已經發出！";
	}
	ri.bRet = TRUE;
	return ri;
}// Spock end