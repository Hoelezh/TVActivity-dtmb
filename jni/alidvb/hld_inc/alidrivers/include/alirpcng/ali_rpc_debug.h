#ifndef __ALI_RPC_DEBUG_H
#define __ALI_RPC_DEBUG_H

#include "ali_rpc_type.h"
#include "ali_rpc_cfg.h"
#include "ali_rpc_osdep.h"

extern Int32	g_dbglevel;

#if defined(__ALI_LINUX_KERNEL__)
	#define _dbgdump printk
#else
	#if defined(__ALI_TDS__)
		#define _dbgdump libc_printf	
	#else
		#define _dbgdump printf
	#endif
#endif

//void Log(Int32 level, const char *fmt, ...);

#define DRIVER_PREFIX   "ALI-RPC: "

#if     defined (_dbgdump)
        #undef  Log
        #define Log(level, fmt, arg...)     \
        do {\
                if (level <= g_dbglevel) {\
                        if (level == LOG_EMERG) \
                                _dbgdump(DRIVER_PREFIX"EMERG " fmt, ##arg);\
                        else if (level == LOG_ERR) \
                                _dbgdump(DRIVER_PREFIX"ERR " fmt, ##arg);\
                        else if (level == LOG_INFO) \
                                _dbgdump(DRIVER_PREFIX"INFO " fmt, ##arg);\
                        else \
                                _dbgdump(DRIVER_PREFIX"DEBUG " fmt, ##arg);\
                }\
        }while(0)
#endif



#endif
