#include "stdafx.h"
#include "XmudOS.h"
#include "ActiveObject.h"
#include "CmdEmote.h"
#include "skill\skill\skill.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static CList<TEmote *, TEmote *> listEmote;
extern char g_tszPathName[256];
extern rmfullglobals myglobs;
extern CList <TClientConData *,TClientConData* >playersocketlist;

static inline CString GetHe(CActiveObject *he);
static void ChangeEmote(CString &szEmote, CActiveObject *me, CActiveObject *you);
static BOOL GetEmote3(TEmote * lpEmote, CActiveObject *me, CActiveObject *you, CString &strRet1, CString &strRet2, CString &strRet3);
static BOOL GetEmoteSpace(TEmote * lpEmote, CActiveObject *me, CString &strRet1, CString &strRet2);
static BOOL GetEmoteMe(TEmote * lpEmote, CActiveObject *me, CString &strRet1, CString &strRet2);
void DeleteEmote()
{
	POSITION pos;
	TEmote * lpEmote;
	pos = listEmote.GetHeadPosition();
	while(pos != NULL){
		lpEmote = listEmote.GetNext(pos);
		delete lpEmote;
	}
	listEmote.RemoveAll();
}

BOOL InitEmote()
{
	CStdioFile fEmote;
	CString szTmp;
	TEmote * lpEmote;

	szTmp =  g_tszPathName;
	szTmp += "\\Emoted.dat";
	if(!fEmote.Open(szTmp, CFile::modeRead)){
		AddRecordMsg("ERROR Open Emoted.dat fail");
		return FALSE;
	}else{
		while (fEmote.ReadString(szTmp)){
			lpEmote = new TEmote;
			lpEmote->nKind = szTmp[0]-'0';
			fEmote.ReadString(lpEmote->szCEmote);
			fEmote.ReadString(lpEmote->szEmote);
			fEmote.ReadString(szTmp);
			lpEmote->nType = szTmp[0]-'0';

			if(lpEmote->nType & EMT_HAVE_TARGET){
				fEmote.ReadString(lpEmote->szTarget);
				fEmote.ReadString(lpEmote->szMeTo);
				fEmote.ReadString(lpEmote->szOthersTo);
			}
			if(lpEmote->nType & EMT_HAVE_NONAME)
			{
				fEmote.ReadString(lpEmote->szMe);
				fEmote.ReadString(lpEmote->szOthers);
			}
			if(lpEmote->nType & EMT_HAVE_SELF)
			{
				fEmote.ReadString(lpEmote->szMyself);
				fEmote.ReadString(lpEmote->szOtherself);
			}
			listEmote.AddTail(lpEmote);
		}
	}

	fEmote.Close();

	return TRUE;
}

inline CString GetHe(CActiveObject *he)
{
	return (he->szSex[0] == 'F')?"她":"他";
}

CString GetSpecialName(CActiveObject *me, int nType)
{
	CString strRet;
	if(!strcmp(me->szFamily,"少林"))
	{
		if(me->nAge >=50 )
			switch(nType)
			{
			case 1:
				switch(random(3))
				{
				case 0:
					strRet = "大師";
					break;
				case 1:
					strRet = "老師父";
					break;
				case 2:
					strRet = "高僧";
					break;
				}
				break;
				
			case 2:
				switch(random(3))
				{
				case 0:
					strRet = "老賊禿";
					break;
				case 1:
					strRet = "老禿驢";
					break;
				case 2:
					strRet = "臭和尚";
					break;
				}
				break;
			case 3:
				switch(random(2))
				{
				case 0:
					strRet = "貧僧";
					break;
				case 1:
					strRet = "老衲";
					break;
				}
				break;
			case 4:
				switch(random(2))
				{
				case 0:
					strRet = "本大和尚";
				case 1:
					strRet = "老和尚";
				}
				break;
			}
		else if (me->nAge >= 20)
			switch(nType)
			{
			case 1:
				switch(random(2))
				{
				case 0:
					strRet = "大師";
					break;
				case 1:
					strRet = "尊者";
					break;
				}
				break;
			case 2:
				switch(random(3))
				{
				case 0:
					strRet = "賊禿";
					break;
				case 1:
					strRet = "禿驢";
					break;
				case 2:
					strRet = "臭和尚";
					break;
				}
				break;
			case 3:
				strRet = "貧僧";
				break;
			case 4:
				switch(random(2))
				{
				case 0:
					strRet = "本大和尚";
				case 1:
					strRet = "佛爺我";
				}
				break;
			}//switch
		else//if(me->nAge < 20)
		{
			switch(nType)
			{
			case 1:
				strRet = "小師父";
				break;
			case 2:
				switch(random(3))
				{
				case 0:
					strRet = "小賊禿";
					break;
				case 1:
					strRet = "小禿驢";
					break;
				case 2:
					strRet = "臭和尚";
					break;
				}
				break;
			case 3:
				strRet = "貧僧";
				break;
			case 4:
				switch(random(2))
				{
				case 0:
					strRet = "本大和尚";
				case 1:
					strRet = "佛爺我";
				}
				break;
			}
		}
	}else if(!strcmp(me->szFamily,"武當")){
		if(me->nAge >= 50){
			switch(nType){
			case 1:
				switch(random(2)){
				case 0:
					strRet = (me->szSex[0] =='F')?"仙姑":"老道長";
					break;
				case 1:
					strRet = (me->szSex[0] =='F')?"女神仙":"老神仙";
					break;
				}
				break;
			case 2:
				switch(random(3))
				{
				case 0:
					strRet = (me->szSex[0] =='F')?"老妖精":"老牛鼻子";
					break;
				case 1:
					strRet = (me->szSex[0] =='F')?"老妖精":"老雜毛";
					break;
				case 2:
					strRet = (me->szSex[0] =='F')?"老妖精":"老妖道";
					break;
				}
				break;
			case 3:
				strRet = "貧道";
				break;
			case 4:
				switch(random(2)){
				case 0:
					strRet = (me->szSex[0] =='F')?"本仙姑":"老道";
					break;
				case 1:
					strRet = (me->szSex[0] =='F')?"本仙姑":"本道長";
					break;
				}
				break;
			}
		}else if (me->nAge < 20){
			switch(nType){
			case 1:
				strRet = (me->szSex[0] =='F')?"小仙姑":"小道長";
				break;
			case 2:
				switch(random(3)){
				case 0:
					strRet = (me->szSex[0] =='F')?"小妖精":"小牛鼻子";
					break;
				case 1:
					strRet = (me->szSex[0] =='F')?"小妖精":"小雜毛";
					break;
				case 2:
					strRet = (me->szSex[0] =='F')?"小妖女":"臭道士";
					break;
				}
				break;
			case 3:
				strRet = "貧道";
				break;
			case 4:
				switch(random(2))
				{
				case 0:
					strRet = (me->szSex[0] =='F')?"本仙子":"小道士";
					break;
				case 1:
					strRet = (me->szSex[0] =='F')?"本仙子":"本道長";
					break;
				}
				break;
			}
		}else{
			switch(nType){
			case 1:
				strRet = (me->szSex[0] =='F')?"仙姑":"道長";
				break;
			case 2:
				switch(random(3)){
				case 0:
					strRet = (me->szSex[0] =='F')?"妖女":"死牛鼻子";
					break;
				case 1:
					strRet = (me->szSex[0] =='F')?"妖女":"妖道";
					break;
				case 2:
					strRet = (me->szSex[0] =='F')?"妖女":"臭道士";
					break;
				}
				break;
			case 3:
				strRet = "貧道";
				break;
			case 4:
				strRet = (me->szSex[0] =='F')?"本仙子":"本道長";
				break;
			}
		}
	}
	else if(!strcmp(me->szFamily,"峨嵋")){
		if(me->nAge >= 50){
			switch(nType){
			case 1:
				strRet = "老師太";
				break;
			case 2:
				switch(random(3)){
				case 0:
					strRet = "臭尼姑";
					break;
				case 1:
					strRet = "賊尼姑";
					break;
				case 2:
					strRet = "老賊尼";
					break;
				}
				break;
			case 3:
				strRet = "貧尼";
				break;
			case 4:
				strRet = "老尼";
				break;
			}
		}else if (me->nAge <20){
			switch(nType){
			case 1:
				strRet = "小師太";
				break;
			case 2:
				switch(random(3)){
				case 0:
					strRet = "臭尼姑";
					break;
				case 1:
					strRet = "賊尼姑";
					break;
				case 2:
					strRet = "小賤尼";
					break;
				}
				break;
			case 3:
				strRet = "貧尼";
				break;
			case 4:
				strRet = "本尼姑";
				break;
			}
		}else{
			switch (nType){
			case 1:
				strRet = "師太";
				break;
			case 2:
				switch(random(3)){
				case 0:
					strRet = "臭尼姑";
					break;
				case 1:
					strRet = "賊尼姑";
					break;
				case 2:
					strRet = "賤尼";
					break;
				}
				break;
			case 3:
				strRet = "貧尼";
				break;
			case 4:
				strRet = "本尼姑";
				break;
			}
		}
	}else if(!strcmp(me->szFamily,"丐幫")){
		if(me->nAge >= 50){
			switch(nType){
			case 1:
				if(me->szSex[0] == 'M')
					strRet = "老先生";
				else
					strRet = "老婆婆";
				break;
			case 2:
				switch(random(3)){
				case 0:
					strRet = "臭要飯的";
					break;
				case 1:
					strRet = (me->szSex[0] == 'F')?"死老太婆":"老匹夫";
					break;
				case 2:
					strRet =(me->szSex[0] == 'F')?"老乞婆": "老乞丐";
					break;
				}
				break;
			case 3:
				strRet = (me->szSex[0] == 'F')?"老婆子":"老叫化";
				break;
			case 4:
				strRet = (me->szSex[0] == 'F')?"老婆子":"老叫化";
				break;
			}
		}else if (me->nAge < 20){
			switch(nType){
			case 1:
				if(me->szSex[0] == 'M')
					strRet = "小兄弟";
				else
					strRet = "小姑娘";
				break;
			case 2:
				switch(random(2)){
				case 0:
					strRet = "臭要飯的";
					break;
				case 1:
					strRet = (me->szSex[0] == 'F')?"小狐狸精":"小王八蛋";
					break;
				}
				break;
			case 3:
				strRet = (me->szSex[0] == 'M')?"小子":"小女子";
				break;
			case 4:
				strRet = (me->szSex[0] == 'F')?"本小姐":"小爺";
				break;
			}
		}else{
			switch(nType){
			case 1:
				if(me->szSex[0] == 'M')
					strRet = "壯士";
				else
					strRet = "姑娘";
				break;
			case 2:
				switch(random(2))
				{
				case 0:
					strRet = "臭要飯的";
					break;
				case 1:
					strRet = (me->szSex[0] == 'F')?"賤人":"臭賊";
					break;
				}
				break;
			case 3:
				strRet = (me->szSex[0] == 'M')?"在下":"奴家";
				break;
			case 4:
				strRet = (me->szSex[0] == 'F')?"本姑奶奶":"本大爺";
				break;
			}
		}
	}else if(!strcmp(me->szFamily,"星宿")){
		CString szNickName;
		int nSh		= -me->nShen / 100;
		int nGrade	= 0;
		if(me->nShen < 0)
			while (nSh){
				nSh /= 10;
				nGrade ++;
			}
		switch (nGrade){
		case 0:
			szNickName = "惡人";
			break;
		case 1:
			szNickName = "惡棍";
			break;
		case 2:
			szNickName = "惡魔";
			break;
		case 3:
			szNickName = "魔頭";
			break;
		case 4:
		default:
			szNickName = "妖魔";
			break;
		}
		if(me->nAge >= 50)
		{
			switch(nType)
			{
			case 1:
				strRet = (me->szSex[0] == 'F')?"婆婆":"老先生";
				break;
			case 2:
				switch(random(2))
				{
				case 0:
					strRet = "老" + szNickName;
					break;
				case 1:
					strRet = (me->szSex[0] == 'F')?"死老太婆":"老匹夫";
					break;
				}
				break;
			case 3:
				strRet = (me->szSex[0] == 'F')?"老身":"老頭子";
				break;
			case 4:
				strRet = (me->szSex[0] == 'F')?"老婆子":"老夫";
				break;
			}
		}
		else if (me->nAge < 20)
		{
			switch(nType)
			{
			case 1:
				if(me->szSex[0] == 'M')
					strRet = "小兄弟";
				else
					strRet = "小姑娘";
				break;
			case 2:
				switch(random(2))
				{
				case 0:
					strRet = "小" + szNickName;
					break;
				case 1:
					strRet = (me->szSex[0] == 'F')?"小狐狸精":"小王八蛋";
					break;
				}
				break;
			case 3:
				strRet = (me->szSex[0] == 'M')?"小子":"小女子";
				break;
			case 4:
				strRet = (me->szSex[0] == 'F')?"本大小姐":"本少爺";
				break;
			}
		}
		else
		{
			switch(nType)
			{
			case 1:
				if(me->szSex[0] == 'M')
					strRet = "壯士";
				else
					strRet = "姑娘";
				break;
			case 2:
				switch(random(2))
				{
				case 0:
					strRet = szNickName;
					break;
				case 1:
					strRet = (me->szSex[0] == 'F')?"賤人":"臭賊";
					break;
				}
				break;
			case 3:
				strRet = (me->szSex[0] == 'M')?"在下":"奴家";
				break;
			case 4:
				strRet = (me->szSex[0] == 'F')?"本姑奶奶":"本大爺";
				break;
			}
		}
	}else{
		if(me->szSex[0] == 'F')	{
			if(me->nAge >= 50){
				switch(nType){
				case 1:
					strRet = "婆婆";
					break;
				case 2:
					switch(random(2)){
					case 0:
						strRet = "死老太婆";
						break;
					case 1:
						strRet = "老賤人";
						break;
					}
					break;
				case 3:
					strRet = "老婆子";
					break;
				case 4:
					strRet = "老婆子";
					break;
				}
			}else if (me->nAge < 20){
				switch(nType){			
				case 1:
					switch(random(2)){
					case 0:
						strRet = "小姑娘";
						break;
					case 1:
						strRet = "小妹妹";
						break;
					}
					break;
				case 2:
					switch(random(3)){
					case 0:
						strRet = "小丫頭片子";
						break;
					case 1:
						strRet = "小賤人";
						break;
					case 2:
						strRet = "小狐狸精";
						break;
					}
					break;
				case 3:
					switch(random(2))
					{
					case 0:
						strRet = "奴家";
						break;
					case 1:
						strRet = "小女子";
						break;
					}
					break;
				case 4:
					strRet = "本小姐";
					break;
				}
			}
			else //20-50歲
			{
				switch(nType)
				{
				case 1:
					strRet = "姑娘";
					break;
				case 2:
					switch(random(2))
					{
					case 0:
						strRet = "潑婦";
						break;
					case 1:
						strRet = "賤人";
						break;
					}
					break;
				case 3:
					switch(random(2))
					{
					case 0:
						strRet = "妾身";
						break;
					case 1:
						strRet = "小女子";
						break;
					}
					break;
				case 4:
					strRet = "本姑奶奶";
					break;
				}
			}
		}else{
			if(me->nAge >= 50){
				switch(nType){
				case 1:
					strRet = "老爺子";
					break;
				case 2:
					switch(random(3)){
					case 0:
						strRet = "老東西";
						break;
					case 1:
						strRet = "老混蛋";
						break;
					case 2:
						strRet = "老匹夫";
						break;
					}
					break;
				case 3:
					strRet = "老頭子";
					break;
				case 4:
					strRet = "老夫";
					break;
				}
			}
			else if (me->nAge < 20) // 小于20歲
			{
				switch(nType)
				{
				case 1:
					switch(random(2))
					{
					case 0:
						strRet = "小兄弟";
						break;
					case 1:
						strRet = "小哥";
						break;
					}
					break;
					case 2:
						switch(random(3))
						{
						case 0:
							strRet = "小兔崽子";
							break;
						case 1:
							strRet = "臭小子";
							break;
						case 2:
							strRet = "小王八蛋";
							break;
						}
						break;
					case 3:
						strRet = "小子";
						break;
					case 4:
						strRet = "小爺";
						break;
				}
			}
			else // 20-50歲
			{
				switch(nType)
				{
				case 1:
					strRet = "壯士";
					break;
				case 2:
					strRet = "臭賊";
					break;
				case 3:
					strRet = "在下";
					break;
				case 4:
					switch (random(2))
					{
					case 0:
						strRet = "老子";
						break;
					case 1:
						strRet = "大爺";
					}
					break;
				}
			}
		}
	}
	return strRet;
}


void ChangeEmote(CString &szEmote, CActiveObject *me, CActiveObject *you)
{
	szEmote.Replace("$N",me->szCName);
	szEmote.Replace("$n",you->szCName);
	szEmote.Replace("$R",GetSpecialName(you,SName_zhun));
	szEmote.Replace("$r",GetSpecialName(you,SName_mie));
	szEmote.Replace("$S",GetSpecialName(me,SName_qian));
	szEmote.Replace("$s",GetSpecialName(me,SName_da));
}

BOOL GetEmote3(TEmote * lpEmote, CActiveObject *me, CActiveObject *you, CString &strRet1, CString &strRet2, CString &strRet3)
{
	if(!(lpEmote->nType & EMT_HAVE_TARGET))
		return FALSE;
	strRet1 = lpEmote->szTarget;
	strRet2 = lpEmote->szMeTo;
	strRet3 = lpEmote->szOthersTo;
	ChangeEmote(strRet1, me, you);
	ChangeEmote(strRet2, me, you);
	ChangeEmote(strRet3, me, you);

	strRet1.Replace("$P",GetHe(me));
	strRet1.Replace("$p","你");

	strRet2.Replace("$P","你");
	strRet2.Replace("$p",GetHe(you));

	strRet3.Replace("$P",me->szCName);
	strRet3.Replace("$p",GetHe(you));
	return TRUE;
}

BOOL GetEmoteSpace(TEmote * lpEmote, CActiveObject *me, CString &strRet1, CString &strRet2)
{
	if(!(lpEmote->nType & EMT_HAVE_NONAME))
		return FALSE;
	strRet1 = lpEmote->szMe;
	strRet2 = lpEmote->szOthers;
	ChangeEmote(strRet1, me, me);
	ChangeEmote(strRet2, me, me);

	strRet1.Replace("$P","你");
	strRet1.Replace("$p","你");
	strRet2.Replace("$P",GetHe(me));
	strRet2.Replace("$p",GetHe(me));
	return TRUE;
}

BOOL GetEmoteMe(TEmote * lpEmote, CActiveObject *me, CString &strRet1, CString &strRet2)
{
	if(!(lpEmote->nType & EMT_HAVE_SELF))
		return FALSE;
	strRet1 = lpEmote->szMyself;
	strRet2 = lpEmote->szOtherself;
	ChangeEmote(strRet1, me, me);
	ChangeEmote(strRet2, me, me);

	strRet1.Replace("$P","你");
	strRet1.Replace("$p","你");
	strRet2.Replace("$P",GetHe(me));
	strRet2.Replace("$p",GetHe(me));
	return TRUE;
}

BOOL GetEmote(CString szEmote, CActiveObject *me, CActiveObject *you, CString &strRet1, CString &strRet2, CString &strRet3)
{
	POSITION pos;
	TEmote * lpEmote;
	pos = listEmote.GetHeadPosition();
	while (pos != NULL)
	{
		lpEmote = listEmote.GetNext(pos);
		if(lpEmote->szEmote == szEmote)
		{
			pos = listEmote.GetHeadPosition();
			break;
		}
	}
	if(pos == NULL)
		return FALSE;
	if(you == NULL)
		return GetEmoteSpace(lpEmote, me, strRet1, strRet3);
	if(you == me)
		return GetEmoteMe(lpEmote, me, strRet1, strRet3);
	return GetEmote3(lpEmote, me, you, strRet2, strRet1, strRet3);
}