/******************************************************************************
 * File: srpc.h
 *
 * Description: -
 *     simple rpc module, it use to build remote call.
 * History
 * --------------------
 * 1. 2012-9-3, Dong yun written
 * --------------------
 ******************************************************************************/


#ifndef __SRPC_H__
#define __SRPC_H__

#ifdef __cplusplus
extern "C" {
#endif


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <hld_cfg.h>


#define SRPCID "SRPC.ID"   // it use to identify the packet is a srpc packet
#define SRPCID_LEN 7       // size of SRPCID, don't forget to align.


#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#endif


#define SRPC_PLOAD_SIZE 256        //srpc_param payload size


#define SRPC_DEF_TIMEOUT (10*1000)    // srpc default timeout, unit:ms

enum SOCK_TYPE
{
    SOCK_TYPE_TCP       = 0,
    SOCK_TYPE_UDP       = 1,
};

// srpc flags, max 8bit
enum SRPC_FLAG_BIT
{
    SRPC_FLAG_NOACK             = 0,   // bit 1: needn't ack flag
    SRPC_FLAG_KEEPALIVE         = 1,   // bit 2: keep alive flag
};


#if 1
#define SRPC_DEBUG(fmt, args...) ADR_DBG_PRINT(SRPC, fmt, ##args)
#else
#define SRPC_DEBUG(...)
#endif

/*srpc remote call parameters*/
typedef struct
{
    unsigned char   srpc_id[SRPCID_LEN];        // srpc identification, see SRPCID.
    unsigned char   flag;                       // srpc flags, see enum SRPC_FLAG_BIT.
    unsigned int    service_id;                 // use to find remote call service in service_table.
    unsigned char   pload[SRPC_PLOAD_SIZE];     // srpc payload, use to transfer parameters.
} srpc_param;

typedef void (*srpc_func)(void *req);

/*srpc service,*/
typedef struct
{
    unsigned int    id;
    srpc_func       func;
} srpc_service;


/*srpc some event handles*/
typedef struct
{
    srpc_func   on_send; //before send data event, you can do some actions, such as encrypt.
    srpc_func   on_recv; //after receive data event, you can do some actions, such as dencrypt.
} srpc_event_hdl;


/*srpc server*/ 
typedef struct
{
    int                 sock;        //socket handle.<only used in server point>.
    int                 state;       //srpc server state.<only used in server point>.
    int                 socktype;    //socket type, see enum SOCK_TYPE.
    int                 non_block;   //set socket if use non_block mode.
    struct sockaddr_in  saddr;       //address of srpc server.
    srpc_event_hdl      ehdl;        //srpc event handles.
    srpc_service       *srv_table;   //srpc service table.<only used in server point>.
    unsigned int        srv_count;   //count of srpc service table.<only used in server point>.
} srpc;

/*srpc remote call request*/
typedef struct
{
    int                 sock;      // socket, use to send request.
    struct sockaddr_in  remote;    // remote point address
    srpc               *rpc;       // srpc server
    srpc_param          param;     // remote call parameters.
} srpc_req;

typedef struct ip_local_cfg
{
	unsigned int dhcp_on;					// 1: DHCP on, 0: DHCP off
	unsigned int ip_addr;
	unsigned int subnet_mask;
	unsigned int gateway;
	unsigned int dns;	
	unsigned int dns2;
	
}IP_LOC_CFG, *PIP_LOC_CFG;

/******************************************************************************
 * Function: srpc_get_flag
 * Description: -
 *    get srpc flag, see enum SRPC_FLAG_BIT
 * Input:
 * Output:
 * Returns:
 * History:
 * -------------------------------------------------
 * 1. 2012-9-3, Dong yun Created
 * -------------------------------------------------
 ******************************************************************************/
static inline int srpc_get_flag(srpc_param *param, enum SRPC_FLAG_BIT flagbit)
{
    return (param->flag >> flagbit) & 0x1;
}


/******************************************************************************
 * Function: srpc_set_flag
 * Description: -
 *    set srpc flag, see enum SRPC_FLAG_BIT
 * Input:
 * Output:
 * Returns:
 * History:
 * -------------------------------------------------
 * 1. 2012-9-3, Dong yun Created
 * -------------------------------------------------
 ******************************************************************************/
static inline void srpc_set_flag(srpc_param *param, enum SRPC_FLAG_BIT flagbit, unsigned char val)
{
    if(val)
    {
        param->flag |= (0x1 << flagbit);
    }
    else
    {
        param->flag &= ~(0x1 << flagbit);
    }
}

extern int srpc_send(int sockfd, const void *buf, size_t len, int flags);
extern int srpc_sendto(int sockfd, const void *buf, size_t len, int flags,
                         const struct sockaddr *dest_addr, socklen_t addrlen);
extern int srpc_recv(int sockfd, void *buf, size_t len, int flags, unsigned int timeout_ms);
extern int srpc_recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr,
                           socklen_t *addrlen, unsigned int timeout_ms);

/******************************************************************************
 * Function: srpc_start
 * Description: -
 *    start a srpc server: rpc
 * Input:
 *    rpc: srpc server
 * Output: <NONE>
 * Returns:
 *   1: rpc start successs
 *   0: start faile.
 * History:
 * -------------------------------------------------
 * 1. 2012-9-3, Dong yun Created
 * -------------------------------------------------
 ******************************************************************************/
extern int srpc_start(srpc *rpc);


/******************************************************************************
 * Function: srpc_stop
 * Description: -
 *    stop the srpc server: rpc
 * Input:
 *    rpc: srpc server
 * Output:  <NONE>
 * Returns: <NONE>
 * History:
 * -------------------------------------------------
 * 1. 2012-9-3, Dong yun Created
 * -------------------------------------------------
 ******************************************************************************/
extern void srpc_stop(srpc *rpc);


/******************************************************************************
 * Function: srpc_call
 * Description: -
 *    send a remote call request to the srpc server: rpc.
 * Input:
 *    req        : remote call request
 *    timeout_ms : timeout,unit:ms, it indicate that how many times need used to run 
 *                 this command in server, and not contain the time of build connection.
 * Output:
 * Returns:
 *        1: send remote call success and received the response
 *        0: remote call failed.
 * History:
 * -------------------------------------------------
 * 1. 2012-9-3, Dong yun Created
 * -------------------------------------------------
 ******************************************************************************/
extern int srpc_call(srpc_req *req, unsigned int timeout_ms);

#ifdef __cplusplus
}
#endif

#endif
