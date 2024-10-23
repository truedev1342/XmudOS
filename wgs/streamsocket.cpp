#include "stdafx.h"
#include "StreamSocket.h"

BOOL	StreamSocket::bInitStartup=FALSE;
WSADATA	StreamSocket::stWSAData;
int		StreamSocket::nUseObjects=0;

void StreamSocket::InitialSocket()
{
	nUseObjects++;
	if(!bInitStartup)
	{
		int nRet;
		if(0==(nRet=WSAStartup(WSA_VERSION,&stWSAData)))
			bInitStartup=TRUE;
	}
}

void StreamSocket::ReleaseSocket()
{
	closeing();
	if(!(nUseObjects-=1))
	{
		if(SOCKET_ERROR!=WSACleanup())
			bInitStartup=FALSE;
	}
}

DWORD StreamSocket::GetHostIP(LPSTR szHost)
{
	DWORD dwAddr=INADDR_ANY;
	if(szHost)
	{
		if((INADDR_NONE==(dwAddr=inet_addr(szHost)))&&(strcmp(szHost,"255.255.255.255")))
		{
			LPHOSTENT lpstHost;
			if((lpstHost=gethostbyname(szHost)))
				return *((DWORD*)(lpstHost->h_addr));
			else
				return INADDR_ANY;
		}
	}
	return dwAddr;
}

DWORD StreamSocket::GetLocalIP()
{
	char		szLclHost[MAXHOSTNAME];
	LPHOSTENT	lpstHostent;
	if(SOCKET_ERROR!=gethostname(szLclHost,MAXHOSTNAME))
	{
		if(lpstHostent=gethostbyname((LPSTR)szLclHost))
			return *((DWORD*)lpstHostent->h_addr);
    }
	SOCKADDR_IN	stLclAddr;
	SOCKET		hSockTemp;
	SOCKADDR_IN	stRmtAddr;
    stLclAddr.sin_addr.s_addr=INADDR_ANY;
	if(INVALID_SOCKET!=(hSockTemp=socket(AF_INET,SOCK_DGRAM,0)))
	{
		stRmtAddr.sin_family=AF_INET;
		stRmtAddr.sin_port=htons(IPPORT_ECHO);
		stRmtAddr.sin_addr.s_addr=inet_addr(CALLWGS);
		
		int nAddrSize=sizeof(SOCKADDR);
		if(SOCKET_ERROR!=connect(hSockTemp,(LPSOCKADDR)&stRmtAddr,sizeof(SOCKADDR)))	{

			getsockname(hSockTemp,(LPSOCKADDR)&stLclAddr,(int *)&nAddrSize);
		}
		closesocket(hSockTemp);
	}
	return stLclAddr.sin_addr.s_addr;
}

WORD StreamSocket::GetPort(LPSTR szService)
{
	CHAR		c;
	c=*szService;
	if((c>='1')&&(c<='9'))
		return htons((WORD)atoi(szService));
	else
	{
		LPSERVENT	lpServent;
		lpServent=getservbyname(szService,0);
		if(lpServent)
			return lpServent->s_port;
	}
	return 0;
}

int StreamSocket::SetLargestBuf(int nBigBufSize,int nOptval)
{
	int nRet,nTrySize,nFinalSize=0;
	if(CONNECTED==state)
	{
		for(nTrySize=nBigBufSize;nTrySize>MTU_SIZE;nTrySize>>=1)
		{
			if(SOCKET_ERROR==setsockopt(hSock,SOL_SOCKET,nOptval,(char*)&nTrySize,sizeof(int)))
			{
				int WSAErr=WSAGetLastError();
				if((WSAErr==WSAENOPROTOOPT)||(WSAErr==WSAEINVAL))
					break;
			}
			else
			{
				nRet=sizeof(int);
				getsockopt(hSock,SOL_SOCKET,nOptval,(char*)&nFinalSize,&nRet);
				return nFinalSize;
			}
		}
	}
	return 0;
}

DWORD StreamSocket::listening(WORD wPort,HWND hWnd,DWORD dwAsyncMsg)
{
	if(hwnd=hWnd)
	{
		if(NO_USED==state)
		{
			stName.sin_family=PF_INET;
			stName.sin_port=htons(wPort);
			if(INVALID_SOCKET!=(hSock=socket(AF_INET,SOCK_STREAM,0)))
			{
				int nLen=SOCKADDR_LEN;
				if(SOCKET_ERROR!=WSAAsyncSelect(hSock,hWnd,dwAsyncMsg,(FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE)))
				{
					if(SOCKET_ERROR!=bind(hSock,(LPSOCKADDR)&stName,SOCKADDR_LEN))
					{
						if(SOCKET_ERROR!=getsockname(hSock,(LPSOCKADDR)&stName,&nLen))
						{
							if(SOCKET_ERROR!=listen(hSock,5))
							{
								state=LISTENING;
								return WS_OK;
							}
						}
					}
				}
				closesocket(hSock);
				hSock=INVALID_SOCKET;
			}
		}
	}
	return WS_ERROR;
}

DWORD StreamSocket::accepting(StreamSocket &stmSock,HWND hWnd,DWORD dwAsyncMsg)
{
	if(LISTENING==state)
	{
		int		nLen=SOCKADDR_LEN;
		HWND	hwndNew=hWnd?hWnd:hwnd;
		SOCKET sock;
		if(SOCKET_ERROR!=(sock=accept(hSock,stmSock.GetSOCKADDR(),&nLen)))
			return stmSock.accepted(sock,hwndNew,dwAsyncMsg);
		else
		{
			int	WSAErr;
			if(WSAEWOULDBLOCK==(WSAErr=WSAGetLastError()))
				return stmSock.accepted(sock,hwndNew,dwAsyncMsg);
		}
	}
	return WS_ERROR;
}

DWORD StreamSocket::accepted(SOCKET sock,HWND hWnd,DWORD dwAsyncMsg)
{
	if(NO_USED==state)
	{
		int nOptval;
		if(SOCKET_ERROR!=WSAAsyncSelect(hSock=sock,hwnd=hWnd,dwAsyncMsg,(FD_READ | FD_WRITE | FD_CLOSE)))
		{
			state=CONNECTED;
			nOptval=SO_SNDBUF;
			SetLargestBuf(INPUT_SIZE*2,nOptval);
			nOptval=SO_RCVBUF;
			nRecvBufSize=((nRecvBufSize=SetLargestBuf(INPUT_SIZE*2,nOptval))>INPUT_SIZE)?INPUT_SIZE:nRecvBufSize;
			setsockopt(hSock,IPPROTO_TCP,TCP_NODELAY,(char *)&bNoDelay,sizeof(BOOL));
			return WS_OK;
		}
	}
	return WS_ERROR;
}

DWORD StreamSocket::connecting(char *lpstrHostName,WORD wPort,HWND hWnd,DWORD dwAsyncMsg)
{
	if(INVALID_SOCKET==hSock){
		if(hwnd=hWnd){
			if(NO_USED==state){
				stName.sin_addr.s_addr=GetHostIP(lpstrHostName);
				stName.sin_family=PF_INET;
				stName.sin_port=htons(wPort);
				if(INVALID_SOCKET!=(hSock=socket(AF_INET,SOCK_STREAM,0))){
					if(SOCKET_ERROR!=WSAAsyncSelect(hSock,hWnd,dwAsyncMsg,(FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE))){
						if(SOCKET_ERROR!=connect(hSock,(LPSOCKADDR)&stName,SOCKADDR_LEN))
							return WS_OK;
						else{
							int WSAErr;
							if(WSAEWOULDBLOCK==(WSAErr=WSAGetLastError()))
								return WS_WAIT;
						}
					}
					closesocket(hSock);
					hSock=INVALID_SOCKET;
				}
			}
		}
	}
	else
		return WS_WAIT;
	return WS_ERROR;
}

void StreamSocket::connected()
{
	int nOptval;
	state=CONNECTED;
	nOptval=SO_SNDBUF;
	SetLargestBuf(INPUT_SIZE*2,nOptval);
	nOptval=SO_RCVBUF;
	nRecvBufSize=((nRecvBufSize=SetLargestBuf(INPUT_SIZE*2,nOptval))>INPUT_SIZE)?INPUT_SIZE:nRecvBufSize;
	setsockopt(hSock,IPPROTO_TCP,TCP_NODELAY,(char *)&bNoDelay,sizeof(BOOL));
}

void StreamSocket::closeing()
{
	static	char	achDiscard[BUF_SIZE];
	if(CONNECTED==state)
	{
		if(SOCKET_ERROR!=WSAAsyncSelect(hSock,hwnd,0,0))
		{
			shutdown(hSock,1);
			for(int nRet=1;(nRet&&(nRet!=SOCKET_ERROR));)
			{
				nRet=recv(hSock,(LPSTR)achDiscard,BUF_SIZE,0);
				closesocket(hSock);
			}
		}
		else
			closesocket(hSock);
	}
	else if(LISTENING==state)
		closesocket(hSock);
	hSock=INVALID_SOCKET;
	state=NO_USED;
}
