#ifndef __ALI_RPC_NG_H
#define __ALI_RPC_NG_H

#include "ali_rpc_type.h"
#include "ali_rpc_errno.h"
#include "ali_rpc_cfg.h"
#include "ali_rpc_osdep.h"
#include "ali_rpc_debug.h"
#include "ali_rpc_util.h"
#include "ali_rpc_xdr.h"
#include "ali_rpc_service.h"
#include "ali_rpc_argsformat.h"
#include "ali_rpc_mcapi.h"
#include "ali_rpc_invoker.h"
#include "ali_rpc_servicelisten.h"
#include "ali_rpc_ctrl.h"

#include "ali_minirpc_service.h"


#if 0
typedef struct _Param Param;
struct _Param {
	Long				type;
	Size_t			len;
	void*			pData;
};
#endif

#if 0
typedef enum _ParamType ParamType;
enum _ParamType {
	PARAM_IN            = 1,
	PARAM_INOUT,
	PARAM_OUT,
	PARAM_RET,
	PARAM_CONTINUE,
	PARAM_BUFFER,
	PARAM_INVALID
};
#endif

typedef enum {
	RPC_ACCEPTED,
	RPC_NOT_EXISTED,
	RPC_PARAM_ERR,
	RPC_STATUS_END
}RpcStatusCode;

#if 0
typedef Int32 RpcFunc(Param *, Param *, Param *, Param *, Param *, Param *, Param *, Param *);
typedef Int32 (*PRpcFunc)( Param *, Param *, Param *, Param *, Param *, Param *, Param *, Param *);
#endif

typedef struct _RpcCd {
	ConnType connType;		/*connect type*/
	Int32 connHandle;		/*RPC internal usage handle*/
}RpcCd;

#if defined(__ALI_LINUX__)   /*for x86 64bit CPU debug usage*/
Int32 RpcInit(McapiNode node, McapiNode rnode);
#else
Int32 RpcInit(McapiNode node);
#endif

Int32 RpcDeinit();

Int32 RpcOpen(McapiNode localNode, McapiPort localSendPort, McapiPort localRecvPort,
		McapiNode remoteNode, McapiPort remoteSendPort, McapiPort remoteRecvPort,
	     Int32 connType, RpcCd *cd);

Int32 RpcClose(RpcCd *);


/*The below definitions are to call a RPC service,*/
Int32 __rpc_call(RpcCd *, Uint32, ...);
#define RpcCall( FUNC, ARG...) \
		__rpc_call(NULL, HASH_STR(FUNC), ##ARG);

Int32 __rpc_call_completion(RpcCd *, Uint32, ...);
#define RpcCallCompletion( FUNC, ARG...) \
		__rpc_call_completion(NULL,  HASH_STR(FUNC), ##ARG);

Int32 RpcWait(Int32 rid, Uint32 timeout);

Int32 RpcFreeRetBuf(Int32 rid);

Int32 RpcExtractRet(Int32 rid);

/*EXPORT_RPC macro for register service symbal*/
/*static inline Uint32
  hash(const char* __s)
  {
    Uint32 __h = 0;
    for ( ; *__s; ++__s)
      __h = 5 * __h + *__s;
    return (__h);
  }
*/
#define HASH_STR(x) hash(#x)


#if defined(__ALI_LINUX_KERNEL__)
  #define EXPORT_RPC(sym)                               \
        extern typeof(sym) sym;                                 \
        static const struct _RpcSymbol __rpctab_##sym       \
        __used                                                  \
        __attribute__((section("___rpctab"), unused))       \
	= {  #sym, 0, (unsigned long)sym }
#else
  /*For see linux version compile*/	
  #define EXPORT_RPC(sym) const struct _RpcSymbol __rpctab_##sym __attribute__ ((section(".rpctab.init"))) = {  #sym, 0, (unsigned long)sym }

#endif

/*For RPC Debug Usage Interface*/
typedef struct _RPCDBGINFO{
	Int32	OS;      	   /*linux or TDS*/
	Int32	RunningStatus;  /*Idle, Initializing, stopping, running*/
	Int32	rpcversion;	   /*RPC version*/
        Int32   mcapiversion;      /*Mcapi version*/
	Int32	totalrunningInvoker;    /*Total num of Running invoker*/
	Int32	totalsleepInvoker;      /*Total num of sleeping invoker*/
	Int32	totalserviceQtask;      /*Total task num of Service Q*/
	Int32	totalRegisteredService; /*Total num of local registered Service*/
	Uint32  totalsendmsgcall;
	Uint32  totalsendpktcall;
	Uint32  totalrcvmsgcall;
	Uint32  totalrcvpktcall;
	Uint32  totalrcvmsgret;
	Uint32  totalrcvpktret;
	Uint32  totalrcvbadmsgpacket;
	Uint32  totalrcvbadpktpacket;
	Uint32  totalrcvbadfuncidcall;	
	//maybe other info if needed ...	
}RPCDBGINFO;

Int32 RpcGetDetailInfo(RPCDBGINFO *pinfo, Bool ifremote);

#endif
