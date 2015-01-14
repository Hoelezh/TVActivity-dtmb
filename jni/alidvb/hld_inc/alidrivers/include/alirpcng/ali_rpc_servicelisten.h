#ifndef __ALI_RPC_SERVICELISTEN_H
#define __ALI_RPC_SERVICELISTEN_H

#include "ali_rpc_type.h"
#include "ali_rpc_cfg.h"
#include "ali_rpc_osdep.h"
#include "ali_rpc_errno.h"
#include "ali_rpc_debug.h"
#include "ali_rpc_util.h"
#include "ali_rpc_xdr.h"
#include "ali_rpc_argsformat.h"
#include "ali_rpc_mcapi.h"
//#include "ali_rpc_invoker.h"


#define RPC_CHANNEL_MAX		2
#define RPC_MAX_RCV_BUF   		8*1024


typedef Int32 SvcListenHandle;

typedef struct _SvcListenDesc SvcListenDesc;
struct _SvcListenDesc{
	mcapi_node_t node;
	mcapi_port_t port;
	Int32 connHandle;	/*this is g_mcapiconn[] array index for using related McapiConn*/
	ConnType conn;
	Thread tid;
};

SvcListenHandle SvcListenCreate(mcapi_node_t localNode, mcapi_port_t localRecvPort, ConnType conn);

Int32 SvcListenDestroy(SvcListenHandle handle);

/*This interface dynamically adds the given symbol into the RPC look up table. PLEASE note, users take care of the symbol memory management*/
Int32 RpcAddService(RpcSymbol *symbol);

Int32 RpcRemoveService(Uint32 hash);

PRpcFunc RpcLookup(Uint32 hash);



#endif

