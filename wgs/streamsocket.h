/*---------------------------------------------------------
   StreamSocket.h -- Handling stream socket's APIs
               (c) ³\¦Ê³ÓCary Hsu, 2000.3.3
---------------------------------------------------------*/
#ifndef __STREAMSOCKET
#define __STREAMSOCKET

#include <windows.h>
#include "Wsa_xtra.h"

#define CALLWGS "0.0.0.0"
#define MTU_SIZE	1460
#define INPUT_SIZE	8192
#define BUF_SIZE	1024
#define MAXHOSTNAME	128


enum{
	WS_ERROR=0,
	WS_OK	=1,
	WS_WAIT	=2
};


enum
{
	NO_USED=0,
	CONNECTED,
	LISTENING
};

class StreamSocket
{
private:
	HWND	hwnd;
	SOCKET	hSock;
	SOCKADDR_IN
			stName;
	char	szRecvBuf[INPUT_SIZE];
	int		nRecvBufSize;
	BOOL	bNoDelay;
	static BOOL		bInitStartup;
	static WSADATA	stWSAData;
	static int		nUseObjects;
protected:
	DWORD	state;
private:
public:
	StreamSocket():nRecvBufSize(INPUT_SIZE),state(NO_USED),hSock(INVALID_SOCKET),bNoDelay(TRUE){InitialSocket();}
	StreamSocket(BOOL NoDelay):nRecvBufSize(INPUT_SIZE),state(NO_USED),hSock(INVALID_SOCKET){
		bNoDelay=NoDelay;
		InitialSocket();}
	~StreamSocket(){ReleaseSocket();}
	void	InitialSocket();
	void	ReleaseSocket();
	DWORD	GetHostIP(LPSTR szHost);
	DWORD	GetLocalIP();
	WORD	GetPort(LPSTR szService);
	int		SetLargestBuf(int nBigBufSize,int nOptval);
	DWORD	listening(WORD wPort,HWND hWnd,DWORD dwAsyncMsg);
	DWORD	accepting(StreamSocket &stmSock,HWND hWnd,DWORD dwAsyncMsg);
	DWORD	accepted(SOCKET sock,HWND hWnd,DWORD dwAsyncMsg);
	DWORD	connecting(char *lpstrHostName,WORD wPort,HWND hWnd,DWORD dwAsyncMsg);
	void	connected();
	void	closeing();
	void	closed(){
		closesocket(hSock);
		hSock=INVALID_SOCKET;
		state=NO_USED;}
	LPSOCKADDR
			GetSOCKADDR(){return (LPSOCKADDR)&stName;}
	BOOL	equal(SOCKET sock){
		return hSock==sock;}
	BOOL	IsNotUsed(){return (NO_USED==state && INVALID_SOCKET==hSock);}
};

#endif
