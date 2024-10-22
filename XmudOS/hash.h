#define DSWAIT	100
#define DSRETRY	1
#define DSFAIL		-100
#define DSTIMEOUT	-200
#define DSLONGDATA	-300
#define INVALIDLOG	-400
#define DSBUFSIZE	8192
#define DS_FILE_NOT_EXIST	-13
#define SZDSSYS	"@sys"

void szHashName(CString name, char *buf);
int nGetPlayerNumber(char *szUser, char *szPath,char *szFile);
int AddPlayer(const char* szUser, const char* szPath, const char* szFile, const char* CName, const char* EName, const char* Password);
int GetPlayers(char *szUser, char *szPath,char *szFile,char *szBuf);
int FindPlayer(char *szUser, char *szPath,char *szFile,char *szBuf);
int DSWait(int *nRet);
int DSSaveData(char *szUser, char *szPath, char *szFile, CString cSaveData);
int DSLoadData(char *szUser, char *szPath, char *szFile, char *szBuf);
int UserStartLog(char *szUser);
int UserEndLog(char *szUser, BOOL bNormal);
int UserStartCheck(char *szUser);
int CheckUserLog(char *szUser);
void ClearUserLog();
