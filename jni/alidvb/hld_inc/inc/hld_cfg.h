#ifndef __ADR_HLD_CONFIG_H
#define __ADR_HLD_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif

#include <adr_sys_define.h>

//Android: enable it,
//Linux: disable it.
#ifndef ADR_ALIDROID
#define ADR_ALIDROID
#endif


#ifdef ADR_ALIDROID
//#define LOG_TAG	"Adr_hld"
//#include <cutils/log.h>
#define ADR_DBG_PRINT(module, fmt, args...)	\
	do { \
		 //ALOGI(fmt, ##args); \
	} while(0)
#else
#define ADR_IPC_ENABLE    // hld ipc operation enhance
//#define HLD_DBG_ENABLE  // hld enable debug print output
//#define HLD_DBG_CONSOLE // hld special printf for nmp product

/* APE module */
//#define HLD_APE_DUMP_FILE	"/mnt/sda1/ali_ape_es_001.ts"	 // always dump ape input data

#ifdef HLD_DBG_CONSOLE
#define ADR_DBG_PRINT(module, fmt, args...)	\
	do { \
			if (NULL != freopen("/dev/console", "a+", stdout)) \
				printf(fmt, ##args); \
	} while(0)
#else	
#define ADR_DBG_PRINT(module, fmt, args...)	\
	do { \
		 printf(fmt, ##args); \
	} while(0)
#endif

#endif	//ADR_ALIDROID

#ifdef __cplusplus
}
#endif

#endif	// __ADR_HLD_CONFIG_H

