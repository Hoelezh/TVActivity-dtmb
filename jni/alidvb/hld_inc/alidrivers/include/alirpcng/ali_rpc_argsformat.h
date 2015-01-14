#ifndef __ALI_RPC_ARGSFORMAT_H
#define __ALI_RPC_ARGSFORMAT_H

#include "ali_rpc_type.h"
#include "ali_rpc_cfg.h"
#include "ali_rpc_osdep.h"
#include "ali_rpc_debug.h"
#include "ali_rpc_util.h"
#include "ali_rpc_xdr.h"
#include "ali_rpc_mcapi.h"
//#include "ali_rpc_invoker.h"

typedef struct _TaskDesc TaskDesc;
struct _TaskDesc {
        Uint32 used;            /*0->means this task element is free, else being used, Added by tony*/
        Int32  rid;             /*Added by tony*/
        Int32  xflag;           /*1->means nonsynchronous call, 0->means synchronous call*/
        McapiConn *conn; /*Added by tony, /*!!The incoming task that belong to which "McapiConn"*/
        Uint32 funcid;  /*Added by tony*/
        PRpcFunc func;
        Uint8 param1[PARAM1_LEN];
        Uint8 param2[PARAM2_LEN];
        Uint8 param3[PARAM3_LEN];
        Uint8 param4[PARAM4_LEN];
        Uint8 param5[PARAM5_LEN];
        Uint8 param6[PARAM6_LEN];
        Uint8 param7[PARAM7_LEN];
        Uint8 param8[PARAM8_LEN];
};

/*Format the arguments when calling service*/
Int32  FormatCallerArgsEncode(Uint8 *buf, Int32 bufsize, Uint32 funcid, Int32 rid, Int32 xflag, Param *args[]);

/*Format the arguments when returning from service*/
Int32  FormatReturnArgsEncode(Int32 result, Uint8 *buf, Int32 bufsize, Uint32 funcid, Int32 rid, Int32 xflag, Param *args[]);

/*Arguments decode for encoded caller arguments*/
Int32  FormatCallerArgsDecode(Uint8 *buf, Int32 buflen, TaskDesc *task);

/*Arguments decode for encoded return arguments*/
Int32  FormatReturnArgsDecode(Uint8 *buf, Int32 buflen, Uint32 *rid, Int32 *result, Int32 *xflag, Param *args[]);

/* Check the packet type if caller encoded or return packet.*/
Int32  FormatCheckPacketType(Uint8 *buf, Int32 buflen, Uint32 *rid);

#endif


