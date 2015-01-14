#ifndef __ALI_RPC_INVOKER_H
#define __ALI_RPC_INVOKER_H

#include "ali_rpc_type.h"
#include "ali_rpc_errno.h"
#include "ali_rpc_cfg.h"
#include "ali_rpc_osdep.h"
#include "ali_rpc_debug.h"
#include "ali_rpc_util.h"
#include "ali_rpc_xdr.h"
#include "ali_rpc_argsformat.h"
#include "ali_rpc_mcapi.h"


#if defined(__ALI_TDS__) && defined(CONFIG_ALI_RPCNG) && defined(CONFIG_ALI_MINIRPC)
#define RPC_MAX_SEND_BUF   		16*1024

//typedef void (*ThreadFunc)(void *arg);

#define ARG_MAX_LEN      2048
#else
#define RPC_MAX_SEND_BUF   		8*1024

//typedef void (*ThreadFunc)(void *arg);

#define ARG_MAX_LEN      512
#endif

#define ARG1_LEN	ARG_MAX_LEN 
#define ARG2_LEN	ARG_MAX_LEN 
#define ARG3_LEN	ARG_MAX_LEN 
#define ARG4_LEN	ARG_MAX_LEN 
#define ARG5_LEN	ARG_MAX_LEN 
#define ARG6_LEN	ARG_MAX_LEN
#define ARG7_LEN	ARG_MAX_LEN
#define ARG8_LEN	ARG_MAX_LEN 


#define PARAM1_LEN	(ARG1_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM2_LEN	(ARG2_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM3_LEN	(ARG3_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM4_LEN	(ARG4_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM5_LEN	(ARG5_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM6_LEN	(ARG6_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM7_LEN	(ARG7_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM8_LEN	(ARG8_LEN + sizeof(Long) + sizeof(Size_t))

#if 0
typedef struct _TaskDesc TaskDesc;
struct _TaskDesc {
	Uint32 used;		/*0->means this task element is free, else being used, Added by tony*/
	Int32  rid;		/*Added by tony*/
	Int32  xflag;		/*1->means nonsynchronous call, 0->means synchronous call*/
	McapiConn *conn; /*Added by tony, /*!!The incoming task that belong to which "McapiConn"*/
	Uint32 funcid;	/*Added by tony*/
	PRpcFunc func;
	Uint8 param1[PARAM1_LEN];
	Uint8 param2[PARAM2_LEN];
	Uint8 param3[PARAM2_LEN];
	Uint8 param4[PARAM2_LEN];
	Uint8 param5[PARAM2_LEN];
	Uint8 param6[PARAM2_LEN];
	Uint8 param7[PARAM2_LEN];
	Uint8 param8[PARAM2_LEN];
};
#endif

typedef struct _Invoker Invoker;
struct _Invoker {
	CList list;		/*!!Changed by tony from "*list" to "list"*/
	Thread tid;
	Int32  rid;		/*!!seems meaningless, we can extract rid from Task arg*/
	Mutex suspendMutex;
	CondVar suspendCv;
	ThreadFunc thread;
	TaskDesc *task;	  /*will point to the element of "svcQtask[]"*/
	Mutex  mutex;     /*Lock invoker other resouce pararrel access*/
};

typedef struct _InvokerManager InvokerManager;
struct _InvokerManager {
	Invoker invoker[RPC_INVOKER_MAX];
	Invoker service;
	CList running;      /*!!Changed by tony from "*list" to "list"*/
	CList sleep;		/*!!Changed by tony from "*list" to "list"*/
	Queue svcQueue;
	Mutex mutex;	/*This mutex is used to Lock "running" and "sleep" and "svcQueue" of InvokerManager and static global variables "svcQtask[]"*/
};

Int32 InvokerManagerInit();

Int32 InvokerManagerDeinit();

Invoker *InvokerManagerAlloc();

void InvokerManagerFree(Invoker *invoker);

Int32 InvokerManagerAssignTask(Invoker *invoker, void *arg);

Int32 InvokerManagerEnqueue(Uint8 *arg, Int32 len, McapiConn *conn);


#if 0

InvokerHandle RpcAllocInvoker(Uint32 func);

Int32 RpcFreeInvoker(Uint32 func);

#endif

#endif

