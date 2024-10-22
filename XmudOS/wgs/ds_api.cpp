#include "..\stdafx.h"
#include "DS_API.h"
#include "Common.h"
extern char g_tszPathName[256];
char szDSHostName[32];

BOOL DSAppend(char *user,char *path,char *file,char *buf,int bufsize,int *ret)
{
	//andy_re
	char buff1[256];
	FILE *fp;
	sprintf(buff1, "%s\\%s\\%s",g_tszPathName, path, file);
	if( (fp=fopen( buff1, "a")) != NULL )	{
		fprintf( fp,"%s\n", buf);
		fclose( fp);
		return 1;
	}else	{
		return -1;
	}

}
