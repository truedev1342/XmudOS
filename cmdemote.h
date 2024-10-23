#ifndef _COMMAND_EMOTE_H_
#define _COMMAND_EMOTE_H_

#define EMT_HAVE_TARGET 0x1
#define EMT_HAVE_NONAME 0x2
#define EMT_HAVE_SELF   0x4

	typedef struct tagEmote
	{
		int nKind;
		CString szEmote;
		CString szCEmote;
		int nType;
		CString szTarget;
		CString szMeTo;
		CString szOthersTo;
		CString szMe;
		CString szOthers;
		CString szMyself;
		CString szOtherself;
		tagEmote()
		{
			nKind = 0;
			szEmote = "";
			szCEmote = "";
			nType = 0;
			szTarget = "";
			szMeTo = "";
			szOthersTo = "";
			szMe = "";
			szOthers = "";
			szMyself = "";
			szOtherself = "";
		}
	}TEmote;
BOOL InitEmote();
void DeleteEmote();
BOOL GetEmote(CString , CActiveObject *, CActiveObject *, CString &, CString &, CString &);

#endif