#ifndef __ALI_RPC_MCAPI_H
#define __ALI_RPC_MCAPI_H

#include "ali_rpc_type.h"
#include "ali_rpc_cfg.h"
#include "ali_rpc_osdep.h"
#include "ali_rpc_debug.h"
#include "ali_rpc_util.h"
#include "ali_rpc_xdr.h"

#include "mcapi.h"

typedef enum _ConnType ConnType;
enum _ConnType {
	MCAPI_MSG,
	MCAPI_PKTCHAN,
	MCAPI_SCLCHAN
};
#define MCAPI_IN	1
#define MCAPI_OUT	2
#define MCAPI_INOUT	3

/*Redefine the MCAPI definitions in RPC component that we will use.*/
typedef mcapi_domain_t McapiDomain;
typedef mcapi_node_t McapiNode;
typedef mcapi_port_t McapiPort;

/*We abstract each connection instance as below structure based on MCAPI protocols.*/
typedef struct _McapiTuple McapiTuple;
struct _McapiTuple {
	mcapi_node_t node;
	mcapi_port_t port;
};

typedef struct _McapiConn McapiConn;
struct _McapiConn {
	Int32		dir;			/*0->this connection is for sending, 1->for receiving*/
	Bool		block;			/* Block attribute, 0 for non-blocking */
	Int32		prio;			/* Messages priority */
	McapiTuple	local;
	McapiTuple	remote;
	ConnType	conn;
	Mutex           mutex;			/*Mutex for muti-thread parallel access*/
    	/* User data */
    	mcapi_endpoint_t    local_endp;
    	mcapi_endpoint_t    foreign_endp;
    	mcapi_status_t      status;         /* The status of the test. */
	mcapi_request_t     request;        /* The request structure to use to check the status of the open call. */
	union {
		mcapi_sclchan_send_hndl_t   scl_tx_handle;
		mcapi_sclchan_recv_hndl_t   scl_rx_handle;
		mcapi_pktchan_send_hndl_t   pkt_tx_handle;
		mcapi_pktchan_recv_hndl_t   pkt_rx_handle;
	};
};

/*MCAPI protocols initialization procedure.*/
Int32 McapiInit(McapiNode node, mcapi_version_t *version);

/*MCAPI protocols exit.*/
Int32 McapiDeinit();

/*This interface will create the local endpoint, in case of Packet Channels and Scalar Channels it will call the connection process, and all the operations will execute on the given blocking status. The prio is the Messages priority, and it has nothing to do with other two manners.*/
Int32 McapiOpen(McapiConn *conn, Bool block, Int32 prio);

Int32 McapiOpen_Pre(McapiConn *conn, Bool block, Int32 prio);

/*This interface will disconnect the foreign endpoint in case of Packet Channels and Scalar Channels, and delete the local endpoint.*/
Int32 McapiClose(McapiConn *conn);

/*This interface sends out a message specified with buffer to the foreign endpoint, returns -1 if failed.*/
Int32 McapiMsgWrite(McapiConn *conn, void *buffer, Size_t size);

/*This interface receives a message from foreign endpoint, the parameter size is the buffer available length, returns -1 if fails, else the received message size.*/
Int32 McapiMsgRead(McapiConn *conn, void *buffer, Size_t size);
 
/*This interface sends out the message specified with buffer to the foreign endpoint in Packet Channels, returns -1 if failed.*/
Int32 McapiPktWrite(McapiConn *conn, void *buffer, Size_t size);

/*This interface receives the message in Packet Channels, the parameter size is the received message length. It returns -1 if failed.*/
Int32 McapiPktRead(McapiConn *conn, void **buffer, Size_t *size);

/*This interface releases the system buffer, that has been filled in at McapiPktRead, returns -1 if failed*/
Int32 McapiPktFree(void *buffer);

/*This interface sends out the scalar value in Scalar Channels, returns -1 if failed.*/
Int32 McapiSclWrite(McapiConn *conn, void *buffer, Size_t size);

/*This interface receives scalar value in Scalar Channels, returns -1 if failed.*/
Int32 McapiSclRead(McapiConn *conn, void *buffer, Size_t size);

/*This interface is a blocking call that processes all the non-blocking operation to the specified connection. The parameter timeout is the number of milliseconds. It returns -1 if failed.*/
Int32 McapiWait(McapiConn *conn, Uint32 timeout);


Int32 McapiAvail(McapiConn *conn);



#endif



