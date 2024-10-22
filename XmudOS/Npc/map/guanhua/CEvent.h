//---------------------------------------------------------------------------
#ifndef _CEVENT_H_
#define _CEVENT_H_
//---------------------------------------------------------------------------
#include <string>
#include <list>
#include "CEventCommon.h"

using namespace std;

class CEventRun
{
public:
    int    EventRunType;
	int    EventRunGoodKind;		// new: 2000/06/23
    string EventRunItemName;
    int    EventRunValue;

    CEventRun();
    ~CEventRun();
};

class CEventLimit
{
public:
    int    LimitType;
	int    LimitGoodKind;		// new: 2000/06/23
    string LimitItemName;
    int    LimitValue;

    // [NO]: When the Limit is not satisfied
    string MsgWhenNo;
    list<CEventRun> EventRunListWhenNo;
    // [YES]: When the Limit is satisfied
    string MsgWhenYes;
    list<CEventRun> EventRunListWhenYes;

    CEventLimit();
    CEventLimit(const CEventLimit &SourceLimit);	

    ~CEventLimit();
};

class CEventAsk
{
public:
    string KeyWord;
    int    AskType;
    int    LimitChoose;

// add 7/24 start
    // [NO]:  Default EventRun When the Limit is not satisfied
    string MsgDefaultWhenNo;
    list<CEventRun> DefaultEventRunListWhenNo;
    // [YES]: Default EventRun When the Limit is satisfied
    string MsgDefaultWhenYes;
    list<CEventRun> DefaultEventRunListWhenYes;
// add 7/24 end

    list<CEventLimit> LimitList;

    CEventAsk();
    CEventAsk(char* szKeyWord, int nAskType, int nLimitChoose = EV_LIMITCHOOSE_All, int nNeedDefaultLimit = 0);
    ~CEventAsk();
};

class CNpcEvent
{
public:
    list<CEventAsk> EventAskList;
    CNpcEvent();
    ~CNpcEvent();
};

#endif
