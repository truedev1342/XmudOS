#ifndef _WSA_XTRA_
#define _WSA_XTRA_ 
 
#include <winsock.h>
#undef  IPROTO_GGP
#define IPROTO_GGP  3
#ifndef IPROTO_IGMP
#define IPROTO_IGMP 2
#endif

#define MAXADDRSTR    16
#define SOCKADDR_LEN sizeof(struct sockaddr)
#ifndef MAKEWORD
#define MAKEWORD(l,h) ((WORD)(((BYTE)(l))|(((WORD)(BYTE)(h))<<8)))
#endif
#define WSA_MAJOR_VERSION 1
#define WSA_MINOR_VERSION 1
#define WSA_VERSION MAKEWORD(WSA_MAJOR_VERSION, WSA_MINOR_VERSION)
#define bcopy(s,d,n)   _fmemcpy((d),(s),(n))
#define bcmp(s1,s2,n)  _fmemcmp((s1),(s2),(n))
#define bzero(s,n)     _fmemset(((s),0,(n))

#define MAX_TTL	255
#define ICMP_ECHOREPLY	0
#define ICMP_ECHOREQ	8
typedef struct icmp_hdr {
	u_char	icmp_type;
	u_char	icmp_code;
	u_short icmp_cksum;
	u_short	icmp_id;
	u_short	icmp_seq;
	char	icmp_data[1];
} ICMP_HDR, *PICMPHDR, FAR *LPICMPHDR;
#define ICMP_HDR_LEN	sizeof(ICMP_HDR)
#define	IPVERSION	4
typedef struct ip_hdr {
	u_char	ip_hl;
	u_char	ip_v;
	u_char	ip_tos;
	short	ip_len;
	u_short	ip_id;
	short	ip_off;
	u_char	ip_ttl;
	u_char	ip_p;
	u_short	ip_cksum;
	struct	in_addr ip_src;
	struct	in_addr ip_dst;
} IP_HDR, *PIP_HDR, *LPIP_HDR;
#define IP_HDR_LEN sizeof(IP_HDR)

#define DEERING_OFFSET      7
#endif
