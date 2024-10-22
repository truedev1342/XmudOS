#ifndef __CONFIG_H__
#define __CONFIG_H__

#define XMUDVER "1.600"
#define CLIENTVER 1150000
#define BETA	0
#define SZAOBJCHECK "EmpAObj"
#define SZCONCHECK "EmpConD"

#define szEndParm		"$END$"
#define szSomeonejoinMap "$101$"
#define szSomeoneQuitMap "$102$"
#define SZJOBO		"$022$"
#define SZSHOOT		"$024$"
#define SZSEP		"$025$"
#define SZRELIFE	"$026$"
#define szChangeMapCmd "$1006$"
#define szSendMapData  "$1014$"
#define szUserLogonCmd "$1009$"
#define szPlayerLogonCmd "$1008$"
#define szPlayerCreateCmd "$1007$"
#define szPlayerDeleteCmd "$1010$"
#define SZRESTART	"$1011$"
#define SZSAVE		"$1012$"
#define SZEXITGAME	"$1013$"

#define SZTELLSOMEONE	"$3001$"
#define SZTALKTOALL		"$3002$"
#define szShoutToAll	"$3003$"
#define szGetChannel	"$3004$"
#define SZJOINCHANNEL	"$3005$"
#define szExitChannel	"$3006$"
#define szSayInMap		"$3007$"
#define szWhoInGame		"$3008$"
#define szALLWhoInGame	"$3009$"
#define szDefendTell	"$3010$"
#define szDefendDel		"$3011$"
#define szDefendList	"$3012$"
#define szGetOut		"$3013$"
#define szShowGM		"$3014$"
#define szKickOut		"$3015$"
#define szGmShout		"$3016$"
#define szGmrun			"$3017$"

#define SZEAT			"$3020$"
#define	SZDRINK			"$3021$"
#define	SZREADBOOK		"$3022$"
#define SZBUY			"$3023$"
#define SZSELL			"$3024$"
#define SZADDGOODS		"$3025$"
#define SZSUBGOODS		"$3026$"
#define SZLOOK			"$3027$"
#define SZUSE           "$3028$"
#define SZADDRENTGOODS	"$3029$"
#define SZSUBRENTGOODS	"$3030$"
#define SZRENTLIST		"$3031$"

#define SZDAZUO			"$3041$"
#define	SZTUNA			"$3042$"
#define	SZPRACTICE		"$3043$"
#define SZMAPPING		"$3044$"
#define SZYUNGONG		"$3045$"
#define SZDAZUOEND		"$3046$"
#define SZTUNAEND		"$3047$"

#define SZAPPRENTICE	"$3050$"
#define SZMASTERSKILL	"$3051$"
#define SZLEARNSKILL	"$3055$"
#define SZASK			"$3053$"

#define SZKILLSOMEBODY	"$3061$"
#define SZKILLEDBYSOME	"$3062$"
#define SZFIGHTSOMEBODY	"$3063$"
#define SZFIGHTEDBYSOME	"$3064$"
#define SZLOOKPLAYER	"$3065$"

#define SZARM			"$3070$"
#define SZUNARM     	"$3071$"
#define SZGIVE          "$3072$"
#define SZDROP          "$3073$"

#define SZEMOTE			"$3080$"
#define SZADDVMESSAGE	"$3081$"
#define SZOKMSG			"$3082$"
#define SZFAILMSG		"$3083$"

#define SZDEADMSG		"$3100$"

#define SZKILLSB		"$7001$"
#define SZKILLOVER		"$7002$"
#define SZFIGHTSB		"$7003$"
#define SZFIGHTOVER		"$7004$"

#define SZACCEPTFIGHT	"$7005$"
#define SZREJECTFIGHT	"$7006$"
#define SZESCAPE		"$7007$"


#define SZFIGHTDATA		"$7098$"
#define SZFIGHTMSG		"$7099$"
#define SZGETMISSBUF	"$901$"
#define SZSENDMISSBUF	"$902$"
#define	SZSENDALLINFO	"$7900$"
#define SZHEALING		"$7901$"
#define SZCANHEALING	"$7902$"
#define szAdminLogonCmd "$6001$"

#define szRedLow		"$501$"
#define szRedHigt		"$502$"
#define szBlueLow		"$503$"
#define szBlueHigt		"$504$"
#define szGreenLow		"$505$"
#define szGreenHigt		"$506$"
#define szYellowLow		"$507$"
#define szYellowHigt	"$508$"
#define szCyanLow		"$509$"
#define szCyanHigt		"$510$"

#define szSystemErrMsg "伺服器發生系統錯誤"
#define szSystemRigged "非法操作"
#define szPlayerRecordErrMsg "儲存記錄出現問題或伺服器已當機"
#define szCommandErrMsg "未知命令"
#define szLogonErrMsg   "帳號不存在或密碼錯誤"
#define szOutOfClientNumErrMsg "伺服器允許上線人數已滿"
#define szOutOfMemoryErrMsg "伺服器記憶體已用盡"
#define szUserAccountDisableErrMsg "用戶帳號已被封鎖"
#define szUserAccountReEnterErrMsg "另外一個同名用戶已上線"
#define szPlayerAccountHasExistErrMsg "此角色英文名已有人使用，請另取別的名字"
#define szPlayerAccountFull "一個用戶只允許登錄5個角色"
#define szPlayerCNameErrMsg "中文名稱錯誤"
#define szDiskWriteErrMsg "伺服器資料儲存發生錯誤"
#define szDiskReadErrMsg "伺服器資料讀取發生錯誤"
#define szVerError "您所執行的人在江湖版本不正確，可能是下載更新失敗，請先移除再重新安裝"
#define szCookieRecvErrMsg "無法連線，可能是人在江湖版本不正確，或是網路連線品質不良"
#define szInvalidLogin "系統檢查到你是重覆登入，你將被強制離線"

#define G_KILLSTATUS_None			0x0000
#define G_KILLSTATUS_WaitForEscape	0x0001
#define ReturnResult(string) {\
			if (!lstrcmp(string,"OK")) {\
			lstrcpy(Result,"OK");\
			return;}\
			else {\
			lstrcpy(Result,"FAIL ");\
			lstrcat(Result,string);\
			return;}}

#endif