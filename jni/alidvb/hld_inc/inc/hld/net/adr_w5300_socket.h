#ifndef __ADR_W5300_SOCKET_H_
#define __ADR_W5300_SOCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SOCK_NUM		8
#define W5300_1_CONNECT_TIMEOUT	25	// second
#define W5300_2_CONNECT_TIMEOUT	20
#define W5300_RX_TIMEOUT	1000 //ms


/* Socket protocol types (TCP/UDP/RAW) */
#define SOCK_STREAM     1
#define SOCK_DGRAM      2
#define SOCK_RAW        3

#define W5300_CLOSE		0
#define W5300_TCP			1
#define W5300_UDP			2
#define W5300_IPRAW		3
//not surported yet.
#define W5300_MACRAW		4
#define W5300_PPPoE		5


#define AF_UNSPEC	0
#define AF_INET		2
#define PF_INET		AF_INET
#define PF_UNSPEC	AF_UNSPEC


/* IP PROTOCOL */
#define IPPROTO_IP         0   /* Dummy for IP */
#define IPPROTO_ICMP       1   /* Control message protocol */
#define IPPROTO_IGMP       2   /* Internet group management protocol */
#define IPPROTO_GGP        3   /* Gateway^2 (deprecated) */
#define IPPROTO_TCP        6   /* TCP */
#define IPPROTO_PUP        12  /* PUP */
#define IPPROTO_UDP        17  /* UDP */
#define IPPROTO_IDP        22  /* XNS idp */
#define IPPROTO_ND         77  /* UNOFFICIAL net disk protocol */
#define IPPROTO_RAW        255 /* Raw IP packet */


/* Definitions for error constants. */
#define ERR_OK          0    /* No error, everything OK. */
#define ERR_MEM        -1    /* Out of memory error.     */
#define ERR_BUF        -2    /* Buffer error.            */
#define ERR_RTE        -3    /* Routing problem.         */
#define ERR_ABRT       -4    /* Connection aborted.      */
#define ERR_RST        -5    /* Connection reset.        */
#define ERR_CLSD       -6    /* Connection closed.       */
#define ERR_CONN       -7    /* Not connected.           */
#define ERR_VAL        -8    /* Illegal value.           */
#define ERR_ARG        -9    /* Illegal argument.        */
#define ERR_USE        -10   /* Address in use.          */
#define ERR_IF         -11   /* Low-level netif error    */
#define ERR_ISCONN     -12   /* Already connected.       */
#define ERR_TIMEOUT    -13   /* Timeout.                 */
#define ERR_INPROGRESS -14   /* Operation in progress    */

#define INADDR_NONE         ((UINT32)0xffffffffUL)  /* 255.255.255.255 */
#define INADDR_LOOPBACK     ((UINT32)0x7f000001UL)  /* 127.0.0.1 */

struct ip_addr {
 UINT32 addr;
};  //__attribute__((packed));

struct in_addr {
  UINT32 s_addr;
};

struct sockaddr_in {
  UINT8 sin_len;
  UINT8 sin_family;
  UINT16 sin_port;
  struct in_addr sin_addr;
  char sin_zero[8];
};

struct sockaddr {
  UINT8 sa_len;
  UINT8 sa_family;
  char sa_data[14];
};


#define U16_F	"u"
#define U32_F	"u"
#define S16_F	"d"
#define S32_F	"d"
#define X16_F	"X"
#define X32_F	"X"

typedef	unsigned char u8_t;
typedef	signed char s8_t;
typedef	unsigned short u16_t;
typedef	signed short s16_t;
typedef	unsigned int u32_t;
typedef	signed int s32_t;


enum w5300_cmd {
	W5300_SET_IP = 0x53000001,
	W5300_GET_IP = 0x53000002,
	W5300_SET_NM = 0x53000003,
	W5300_GET_NM = 0x53000004,
	W5300_SET_GW = 0x53000005,
	W5300_GET_GW = 0x53000006,
	W5300_SET_MAC = 0x53000007,
	W5300_GET_MAC = 0x53000008,
	
	W5300_WINUPDATE_ON = 0x53001001,
	W5300_WINUPDATE_OFF = 0x53001002,
};


int
w5300_socket_init(UINT8 *ip, UINT8 *gw, UINT8 *sn, UINT8 *mac);
int
w5300_socket_fina();


int w5300_accept(int s, struct sockaddr *addr, UINT8 *addrlen);
int w5300_bind(int s, struct sockaddr *name, UINT8 namelen);
int w5300_shutdown(int s, int how);
int w5300_getpeername (int s, struct sockaddr *name, UINT8 *namelen);
int w5300_getsockname (int s, struct sockaddr *name, UINT8 *namelen);
int w5300_getsockopt (int s, int level, int optname, void *optval, UINT8 *optlen);
int w5300_setsockopt (int s, int level, int optname, const void *optval, UINT8 optlen);
int w5300_close(int s);
int w5300_connect(int s, const struct sockaddr *name, UINT8 namelen);
int w5300_listen(int s, int backlog);
int w5300_recv(int s, void *mem, int len, unsigned int flags);
int w5300_read(int s, void *mem, int len);
int w5300_recvfrom(int s, void *mem, int len, unsigned int flags,
	struct sockaddr *from, UINT8 *fromlen);
int w5300_send(int s, const void *dataptr, int size, unsigned int flags);
int w5300_sendto(int s, const void *dataptr, int size, unsigned int flags,
	struct sockaddr *to, UINT8 tolen);
int w5300_socket(int domain, int type, int protocol);
int w5300_write(int s, const void *dataptr, int size);
//int w5300_select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
//	struct timeval *timeout);
int w5300_ioctl(int s, long cmd, void *argp);

#define accept(a,b,c)         w5300_accept(a,b,c)
#define bind(a,b,c)           w5300_bind(a,b,c)
#define shutdown(a,b)         w5300_shutdown(a,b)
#define closesocket(s)        w5300_close(s)
#define connect(a,b,c)        w5300_connect(a,b,c)
#define getsockname(a,b,c)    w5300_getsockname(a,b,c)
#define getpeername(a,b,c)    w5300_getpeername(a,b,c)
#define setsockopt(a,b,c,d,e) w5300_setsockopt(a,b,c,d,e)
#define getsockopt(a,b,c,d,e) w5300_getsockopt(a,b,c,d,e)
#define listen(a,b)           w5300_listen(a,b)
#define recv(a,b,c,d)         w5300_recv(a,b,c,d)
#define recvfrom(a,b,c,d,e,f) w5300_recvfrom(a,b,c,d,e,f)
#define send(a,b,c,d)         w5300_send(a,b,c,d)
#define sendto(a,b,c,d,e,f)   w5300_sendto(a,b,c,d,e,f)
#define socket(a,b,c)         w5300_socket(a,b,c)
#define select(a,b,c,d,e)     w5300_select(a,b,c,d,e)
#define ioctlsocket(a,b,c)    w5300_ioctl(a,b,c)

#define read(a,b,c)           w5300_read(a,b,c)
#define write(a,b,c)          w5300_write(a,b,c)
#define close(s)              w5300_close(s)


#ifdef __cplusplus
}
#endif
#endif //_W5300_SOCKET_H_
