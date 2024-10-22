//---------------------------------------------------------------------------
#include "..\..\stdafx.h"
#include "CEvent.h"

//---------------------------------------------------------------------------
CEventRun::CEventRun()
{
    EventRunType = 0;
	EventRunGoodKind = 0;
    EventRunItemName = "";
    EventRunValue = 0;
}

CEventRun::~CEventRun()
{

}

CEventLimit::CEventLimit()
{
    LimitType = 0;
    LimitGoodKind = 0;
	LimitItemName = "";
    LimitValue = 0;

    // [NO]: When the Limit is not satisfied
    MsgWhenNo = "";
    EventRunListWhenNo.clear();
    // [YES]: When the Limit is satisfied
    MsgWhenYes = "";
    EventRunListWhenYes.clear();
}

CEventLimit::CEventLimit(const CEventLimit &SourceLimit)
{
    LimitType = SourceLimit.LimitType;
    LimitGoodKind = SourceLimit.LimitGoodKind;
	LimitItemName = SourceLimit.LimitItemName;
    LimitValue = SourceLimit.LimitValue;


    MsgWhenNo = SourceLimit.MsgWhenNo;
    EventRunListWhenNo.assign(SourceLimit.EventRunListWhenNo.begin(), SourceLimit.EventRunListWhenNo.end());

    MsgWhenYes = SourceLimit.MsgWhenYes;
    EventRunListWhenYes.assign(SourceLimit.EventRunListWhenYes.begin(), SourceLimit.EventRunListWhenYes.end());
}


CEventLimit::~CEventLimit()
{

}

//---------------------------------------------------------------------------
CEventAsk::CEventAsk()
{
    KeyWord = "";
    AskType = 0;
    LimitChoose = 0;
    LimitList.clear();

// add 7/24 start
    MsgDefaultWhenNo = "";
    DefaultEventRunListWhenNo.clear();
    MsgDefaultWhenYes = "";
    DefaultEventRunListWhenYes.clear();
// add 7/24 end

}

CEventAsk::CEventAsk(char* szKeyWord, int nAskType, int nLimitChoose, int nNeedDefaultLimit)
{
    KeyWord = szKeyWord;
    AskType = nAskType;
    LimitChoose = nLimitChoose;
    LimitList.clear();

    MsgDefaultWhenNo = "";
    DefaultEventRunListWhenNo.clear();
    MsgDefaultWhenYes = "";
    DefaultEventRunListWhenYes.clear();
}

CEventAsk::~CEventAsk()
{
    LimitList.clear();
}

//---------------------------------------------------------------------------
CNpcEvent::CNpcEvent()
{
    EventAskList.clear();
}

CNpcEvent::~CNpcEvent()
{
    EventAskList.clear();
}

//---------------------------------------------------------------------------
