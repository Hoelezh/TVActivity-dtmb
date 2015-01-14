#ifndef __ADF_BASIC__
#define __ADF_BASIC__

#ifdef __cplusplus
extern "C" {
#endif

/*! @addtogroup OSAL
 *  @{
 */
//Support defintion for fault tolerance 
#ifdef CONFIG_MIPS 
//Limit 512M
#define ALI_PHYS(x) (((x)&0x1fffffff)|0xa0000000)
#define ALI_VIRT(x) (((x)&0x1fffffff)|0x80000000)
#define ALI_DMAR(x) ((x)&0x1fffffff)
#define ALI_IOAR(x) (((x)&0x18ffffff)|0xb8000000)
#endif

#ifdef CONFIG_ARM
//Limit 2G
#include <mach/ali-s3921.h>
#define ALI_PHYS(x) ((x)|0x80000000)
#define ALI_VIRT(x) phys_to_virt(ALI_PHYS(x))
#define ALI_DMAR(x) ((x)&0x7fffffff)
#define ALI_IOAR(x) (((x)&0x18ffffff) - PHYS_SYSTEM + VIRT_SYSTEM)
#endif
/* Brief Various commonly used for integer */
typedef char			INT8;
typedef unsigned char	UINT8;

typedef short			INT16;
typedef unsigned short	UINT16;

typedef long			INT32;
typedef unsigned long	UINT32;

typedef unsigned long long UINT64;
typedef long long INT64;

/* Brief Various commonly used */
typedef unsigned char 	UCHAR;
typedef short           WCHAR;
typedef short *         LPWCHAR;
typedef short *         LPWSTR;
typedef char            CHAR;
typedef char *          PCHAR;
typedef char *          LPCHAR;
typedef char *          LPSTR;
typedef void *          PVOID;
typedef void *          LPVOID;

/* Boolean type, possible values are TRUE(1) or FALSE(0) only. */
/* Boolean type, possible values are TRUE(1) or FALSE(0) only. */
typedef int					_BOOL;
typedef void				VOID;
typedef VOID*				VOID_POINTER;

#ifndef BOOL
typedef _BOOL						BOOL;
#endif

#ifndef BYTE
typedef unsigned char 					BYTE;
#endif

#ifndef WORD
typedef unsigned short int 				WORD;
#endif

#ifndef DWORD
typedef unsigned int 					DWORD;
#endif

typedef char 							SBYTE;
typedef short int 						SWORD;
typedef int 							SDWORD;

typedef volatile _BOOL 	*				PBOOL;
typedef volatile unsigned char	*		PBYTE;
typedef volatile unsigned short int  *	PWORD;
typedef volatile unsigned int	*		PDWORD;
typedef volatile char  *				PSBYTE;
typedef volatile short int   *			PSWORD;
typedef volatile int *					PSDWORD;

typedef volatile _BOOL 					VBOOL;
typedef volatile unsigned char 			VBYTE;
typedef volatile unsigned short int 	VWORD;
typedef volatile unsigned int 			VDWORD;
typedef volatile char 					VSBYTE;
typedef volatile short int 				VSWORD;
typedef volatile int 					VSDWORD;

typedef volatile _BOOL 	*				VPBOOL;
typedef volatile unsigned char	*		VPBYTE;
typedef volatile unsigned short int  *	VPWORD;
typedef volatile unsigned int	*		VPDWORD;
typedef volatile char  *				VPSBYTE;
typedef volatile short int   *			VPSWORD;
typedef volatile int *					VPSDWORD;

typedef const unsigned char 			CBYTE;
typedef const unsigned short int 		CWORD;
typedef const unsigned int 				CDWORD;
typedef const char 						CSBYTE;
typedef const short int 				CSWORD;
typedef const int 						CSDWORD;

typedef const unsigned char	*			CPBYTE;
typedef const unsigned short int  *		CPWORD;
typedef const unsigned int	*			CPDWORD;
typedef const char  *					CPSBYTE;
typedef const short int   *				CPSWORD;
typedef const int *						CPSDWORD;

#define CODE		BYTE
#define XBYTE	BYTE
#define XWORD	WORD
#define XDWORD	DWORD

typedef int             BOOLEAN;

#ifndef FALSE
#define	FALSE			(0)
#endif

#ifndef	TRUE
#define	TRUE			(!FALSE)
#endif


#ifndef RET_SUCCESS

/* TODO: the same definition with adr_retcode.h,
 * which will need much time to modify
 */
typedef INT32			RET_CODE;
#define RET_SUCCESS		((INT32)0)
#define	RET_FAILURE		((INT32)1)
#define RET_BUSY		((INT32)2)
#define	RET_STA_ERR	((INT32)3)
#define	RET_STA_PLUGIN_NOT_EXIST  ((INT32)(4))
#ifndef NULL
#define NULL 			((void *)0)
#endif

#endif

typedef UINT32			HANDLE;
#define	INVALID_HANDLE	((HANDLE)0xFFFFFFFF)
typedef void*              VP;

#ifndef WIN32
#ifndef INT64
#define INT64_MAX 0x7fffffffffffffffLL
#endif
#else
#ifndef INT64
#define INT64_MAX 9223372036854775807L
#endif
#endif

#if defined(WIN32) && !defined(__GNUC__)
//  typedef __int64   int64;
#ifndef INT64_MIN
# define INT64_MIN        (-9223372036854775807i64 - 1i64)
#endif
#else
//  typedef long long int64;
#ifndef INT64_MIN
# define INT64_MIN        (-9223372036854775807LL - 1LL)
#endif
#endif

#ifndef UINT_MAX
#define UINT_MAX 0xffffffff
#endif

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

/* Common driver error constants */
#define INNO_DRIVER_ID   0
#define INNO_DRIVER_BASE (INNO_DRIVER_ID << 16)
enum
{
    INNO_NO_ERROR = INNO_DRIVER_BASE,       /* 0 */
    INNO_ERROR_BAD_PARAMETER,             /* 1 Bad parameter passed       */
    INNO_ERROR_NO_MEMORY,                 /* 2 Memory allocation failed   */
    INNO_ERROR_UNKNOWN_DEVICE,            /* 3 Unknown device name        */
    INNO_ERROR_ALREADY_INITIALIZED,       /* 4 Device already initialized */
    INNO_ERROR_NO_FREE_HANDLES,           /* 5 Cannot open device again   */
    INNO_ERROR_OPEN_HANDLE,               /* 6 At least one open handle   */
    INNO_ERROR_INVALID_HANDLE,            /* 7 Handle is not valid        */
    INNO_ERROR_FEATURE_NOT_SUPPORTED,     /* 8 Feature unavailable        */
    INNO_ERROR_INTERRUPT_INSTALL,         /* 9 Interrupt install failed   */
    INNO_ERROR_INTERRUPT_UNINSTALL,       /* 10 Interrupt uninstall failed */
    INNO_ERROR_TIMEOUT,                   /* 11 Timeout occured            */
    INNO_ERROR_DEVICE_BUSY,               /* 12 Device is currently busy   */
    INNO_ERROR_SUSPENDED,                  /* 13 Device is in D1 or D2 state */
    INNO_ERROR_DEVICE_DISABLED,        /* 14 Device is in disabled state */
    INNO_ERROR_OTHERS,                          /* 15 Others error */
};

typedef UINT32 INNO_ErrorCode_t;

/*
 * union which converts two 8bit values into 16bit value.
 */
typedef	union
{
	UINT16	uint_16;
	struct
	{
		UINT8	uint80;	/* LSB */
		UINT8	uint81; /* MSB */
    } uint_8;
} UINT16TO8;

/*
 * union which converts two 16bit values into 32bit value.
 */
typedef	union
{
	UINT32	uint_32;
	struct
	{
		UINT16	low_16;
		UINT16	hi_16;
    } uint_16;
} UINT32TO16;

/* Support macros */
#define itemsof(a)      (sizeof(a) / sizeof(a[0]))

/*!
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif

