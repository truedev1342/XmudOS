#ifndef _CEVENTCOMMON_H_
#define _CEVENTCOMMON_H_

//CEventCommon.h
///////////////////////////////////////////////////

//goods kinds
#define EV_GOODKIND_NotDefine		0
#define EV_GOODKIND_IsNotGood		1
#define EV_GOODKIND_Food			2
#define EV_GOODKIND_Equip			4
#define EV_GOODKIND_Weapon			8
#define EV_GOODKIND_Book			10
#define EV_GOODKIND_Drug			20
#define EV_GOODKIND_Jiudai			80
#define EV_GOODKIND_Normal			100
#define EV_GOODKIND_Flag			200

// Event Run type : parameter of function EventRun()
#define	EV_TYPE_NotDefine            1
#define EV_TYPE_ShowMessage          2
#define EV_TYPE_GoodGet			     4
#define EV_TYPE_GoodDelete           8
#define EV_TYPE_GoodCountIncrease    10
#define EV_TYPE_GoodCountDecrease    20
#define EV_TYPE_StatusPointSet       40
#define EV_TYPE_StatusPointIncrease  80
#define EV_TYPE_StatusPointDecrease  100
#define EV_TYPE_MoneySet			 901
#define EV_TYPE_MoneyIncrease		 902
#define EV_TYPE_MoneyDecrease	     903
#define EV_TYPE_GoodCountSet		 904
#define EV_TYPE_ClearBetray			 905
#define EV_TYPE_ClearAllBetray		 906
#define EV_TYPE_SetFamily			 907
#define EV_TYPE_GoKill               908
#define EV_TYPE_GoFight              909

#define EV_TYPE_JoboMap				 910        //地圖跳躍
#define EV_TYPE_ReLifenew			 911		//轉世	


// Event limit before running  : parameter of function CheckEventLimit()
#define	EV_LIMIT_NotDefine           1
#define EV_LIMIT_GoodHasGot          2
#define EV_LIMIT_GoodHasNotGot	     4
#define EV_LIMIT_GoodCountMore       8
#define EV_LIMIT_GoodCountEqual      10
#define EV_LIMIT_GoodCountLess       20
#define EV_LIMIT_StatusPointMore     40
#define EV_LIMIT_StatusPointEqual    80
#define EV_LIMIT_StatusPointLess     100
#define EV_LIMIT_MoneyMore			 901
#define EV_LIMIT_MoneyLess		     903
#define EV_LIMIT_SexEqual			 904
#define EV_LIMIT_FamilyEqual		 905
#define EV_LIMIT_FamilyNotEqual		 906
#define EV_LIMIT_BetrayFamily		 907
#define EV_LIMIT_NotBetrayFamily	 908

// Key word type
#define EV_KEYWORD_None              0
#define EV_KEYWORD_Visible           1
#define EV_KEYWORD_Invisible         2

// LimitChoose
#define EV_LIMITCHOOSE_One           1
#define EV_LIMITCHOOSE_All           2

#endif