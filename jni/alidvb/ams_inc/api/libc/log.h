#ifndef	__UTIL_LOG_H
#define __UTIL_LOG_H

/*
 * Notice: 如果需要添加新的模块，需要同时修改本文件中的两个地方:
 * 1) 'enum amslog_mod_e'中的'add here'前一行
 * 2) 'static amslog_t amslog[LOG_NUM+1] ='中的'add here'前一行
 */

#ifndef SYS_OS_MODULE
#define SYS_OS_MODULE	OS_LINUX
#endif

#if	(SYS_OS_MODULE != OS_ALI_TDS2)
//#include <sys/syslog.h>
#endif
#include <adr_basic_types.h>


/* temp for open log macro */
#define AMS_LOG 1

/* Default log level is error messages only. */
#define DEFAULT_LOG_LEVEL        LOG_ERR
/* Default log destination is standard error */
#if	(SYS_OS_MODULE != OS_ALI_TDS2)
#define DEFAULT_LOG_DESTINATION  LOG_DEST_STDERR
#else
#define DEFAULT_LOG_DESTINATION  LOG_DEST_TDS
#endif

/* Maxmimu length of a single log line. */
#define MAX_LOG_LINE_LENGTH      512

/* Maxmimu length of a single log name. */
#define MAX_LOG_NAME_LENGTH      12

#if	1//(SYS_OS_MODULE == OS_ALI_TDS2)
#define LOG_EMERG       0       /* system is unusable */
#define LOG_ALERT       1       /* action must be taken immediately */
#define LOG_CRIT        2       /* critical conditions */
#define LOG_ERR         3       /* error conditions */
#define LOG_WARNING     4       /* warning conditions */
#define LOG_NOTICE      5       /* normal but significant condition */
#define LOG_INFO        6       /* informational */
#define LOG_DEBUG       7       /* debug-level messages */
#endif

typedef enum
{
#if	(SYS_OS_MODULE == OS_LINUX)
	LOG_DEST_STDERR  = 1,  /**< Message output to stderr. */
	LOG_DEST_SYSLOG  = 2,  /**< Message output to syslog. */
	LOG_DEST_TELNET  = 3,  /**< Message output to telnet clients. */
#else
	LOG_DEST_TDS     = 4   /**< Message output to TDS. */
#endif
} amslog_dest_e;

typedef struct
{
	char mod_name[MAX_LOG_NAME_LENGTH];
	UINT8 log_level;
} amslog_t;

typedef enum
{
	LOG_APP = 0, /* Log for application */
	LOG_AMS,     /* Log for AMS(other modules) */
	LOG_EPG,     /* Log for EPG module */
	LOG_DB,      /* Log for DB module */
	LOG_PUB,     /* Log for pub module */
	LOG_SIS,     /* Log for SI search module */	
	LOG_SIP,     /* Log for SI parser module */
	LOG_SIM,     /* Log for SI monitor module */
	LOG_NVOD,    /* Log for NVOD module */	
	LOG_PVR,	 /* Log for PVR module */
	LOG_AMP,	     /* Log for AMP module */
	LOG_OTA,	 /* Log for OTA module */
	LOG_VOD,	 /* Log for VOD module */	
	LOG_STBINFO,	 /* Log for STBINFO module */	
	LOG_ASH,	 /* Log for ASH module */
	LOG_SURFACE2D, /*Log for Surface2d module*/
	LOG_BLC,	 /* Log for blcPlugin module */
	LOG_NRC,	 /* Log for libnrc module */
    LOG_CAS,     	/* Log for libcas module*/
	LOG_IMAGE,	 	/*Log for image module*/
	LOG_IMGDEC,	 /*Log for imgdec module*/

	LOG_DDK_BASE,	/*Log base for DDK modules*/

	// add above
	LOG_NUM = 64
} amslog_mod_e;

static amslog_t amslog[LOG_NUM+1] =
{
	{"APP", 0},
	{"AMS", 0},
	{"EPG", 0},
	{"DB", 0},
	{"PUB", 0},
	{"SIS", 0},	
	{"SIP", 0},
	{"SIM", 0},
	{"NVOD", 0},
	{"PVR", 0},
	{"AMP", 0},
	{"OTA", 0},
	{"VOD", 0},	
	{"STBINFO", 0},
	{"ASH", 0},
	{"SURFACE2D",0},
	{"BLC", 0},
	{"NRC", 0},
	{"CAS", 0},
	{"IMAGE", 0},
	{"IMGDEC", 0},
	// add above
	{"NULL", 0},
};

typedef void (*amslog_output)(unsigned char *buf);
static UINT8 amslog_dest;


#ifdef AMS_LOG
#define amslog_error(args...)	amslog_log(LOG_ERR, __FUNCTION__, __LINE__, args)
#define amslog_notice(args...)	amslog_log(LOG_NOTICE, __FUNCTION__, __LINE__, args)
#define amslog_debug(args...)	amslog_log(LOG_DEBUG, __FUNCTION__, __LINE__, args)
#define amslog_printf(args...)	amslog_log2(LOG_DEBUG, args)
#define amslog_dump(log_mod,addr,len)	amslog_dumpm(LOG_DEBUG, log_mod,addr, len)
#else
#define amslog_error(args...)
#define amslog_notice(args...)
#define amslog_debug(args...)
#define amslog_printf(args...)
#define amslog_dump(log_mod,addr,len)
#endif

void amslog_log(UINT8 level, const char *func, UINT32 line_num,
		amslog_mod_e log_mod, const char *pFmt, ... );
void amslog_log2(UINT8 level, amslog_mod_e log_mod, const char *pFmt, ...);
void amslog_init(void);
void amslog_cleanup(void);
void amslog_set_level(amslog_mod_e log_mod, UINT8 log_level);
UINT8 amslog_get_level(amslog_mod_e log_mod);
void amslog_set_dest(amslog_dest_e dest);
amslog_dest_e amslog_get_dest(void);

void amslog_reg(amslog_t *log_mod_ar);

void amslog_reg_output(amslog_output cb);

#endif	/* __UTIL_LOG_H */

