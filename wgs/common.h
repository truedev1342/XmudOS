#ifndef __COMMON
#define __COMMON
#include <ddraw.h>
#include "wsa_xtra.h"
#define IPPORT_GS		7878

struct PlayerName
{
	char		*lpstrName;
	PlayerName	*next;
};

void	InitPlayer(HWND hwnd);
void	ReleaseNet();
BOOL	Add_UserStart(char *szUser);
BOOL	Add_UserEnd(char *szUser);
void	DeleteStartList();
void	DeleteEndList();

#endif