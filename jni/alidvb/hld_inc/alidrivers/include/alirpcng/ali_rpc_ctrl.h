#ifndef __ALI_RPC_CTRL_H
#define __ALI_RPC_CTRL_H

#include "ali_rpc_type.h"
#include "ali_rpc_errno.h"
#include "ali_rpc_cfg.h"
#include "ali_rpc_osdep.h"
#include "ali_rpc_debug.h"
#include "ali_rpc_util.h"
#include "ali_rpc_xdr.h"
#include "ali_rpc_argsformat.h"
#include "ali_rpc_mcapi.h"
#include "ali_rpc_invoker.h"
#include "ali_rpc_servicelisten.h"

#define RPCCALL_TIMEOUT_VALUE  2000  /*2s*/
#define XFLG_SYN        0
#define XFLG_NONSYN  1

/*Return buffer management*/
#define RETRUN_BITMAP_LEN		((RETURN_BUFFER_MAX + BITS_CPU - 1)/BITS_PER_BYTE)

#define BITS_PER_RETMAP 	 RETURN_BUFFER_MAX
#define BITS_PER_RETMAP_MASK  (BITS_PER_RETMAP - 1)

typedef struct _ReturnBuffer ReturnBuffer;
struct _ReturnBuffer {
	char		retMap[RETRUN_BITMAP_LEN];
	Int32	retBuff[RETURN_BUFFER_MAX];
	CondVar retCond[RETURN_BUFFER_MAX];
	Mutex	mutex;				/* ReturnBuffer mutex */
	//Mutex	retMutex;			/* Return condition variable mutex */
	Mutex	retMutex[RETURN_BUFFER_MAX];	/* Changed by tony, Return condition variable mutex */
	Int32	nrFree;
	Int32	lastRid;
};

#if defined(__ALI_TDS__) && defined(CONFIG_ALI_RPCNG) && defined(CONFIG_ALI_MINIRPC)
enum _Ctrl_Msg_Type_E
{
   CONNECT_REQ_E,
   CONNECT_RES_E,
   DISCONN_REQ_E,
   DISCONN_RES_E,
};

typedef enum _Ctrl_Msg_Type_E Ctrl_Msg_Type;

#define  MSG_CLASS_TYPE_OFFSET           0
#define  MSG_CURRENT_INDEX_OFFSET        8
#define  MSG_TOTAL_INDEX_OFFSET         16
#define  MSG_LEN_OFFSET                 24

#define  CTRLMSG_CLASS    0xA0
#define  RPCMSG_CLASS     0xA1
#endif


Int32 RetInit(void);

Int32 RetDeinit(void);

Int32 RetAlloc(void);

void RetFree(Int32 rid);

Int32 ProcessReturnPacket(Uint8 *buf, Int32 buflen, Uint32 rid);

/*Set returned arguments address to g_pParams for blocking rpccall*/
void  SetRetArgsAddress(Uint32 rid, Param *pargs[]);

#endif


