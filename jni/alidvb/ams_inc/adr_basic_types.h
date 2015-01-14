/*****************************************************************************
 *
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2004 Copyright (C)
 *
 *  File: adr_basic_types.h
 *
 *  Contents: 	This file define the basic data types which may be used
 *			throughout the project.
 *  History:
 *		Date		Author      		Version 	Comment
 *		==========	==================	========== 	=======
 *  1.  03/09/2004  Tom Gao     		0.1.000 	Initial
 *
 *****************************************************************************/
#ifndef __ADR_BASIC_TYPES_H__
#define __ADR_BASIC_TYPES_H__

/*! @addtogroup OSAL
 *  @{
 */

/* Brief Various commonly used for integer */
typedef signed char			INT8;
typedef unsigned char		UINT8;

typedef signed short		INT16;
typedef unsigned short		UINT16;

typedef signed int			INT32;
typedef unsigned int		UINT32;

typedef unsigned long long	UINT64;
typedef signed long long	INT64;


/* Brief Various commonly used */
typedef unsigned char 	UCHAR;
typedef signed short    WCHAR;
typedef short *         LPWCHAR;
typedef short *         LPWSTR;
typedef char            CHAR;
typedef char *          PCHAR;
typedef char *          LPCHAR;
typedef char *          LPSTR;
typedef void *          PVOID;
typedef void *          LPVOID;


/* Boolean type, possible values are TRUE(1) or FALSE(0) only. */
typedef INT32           BOOL;

#ifndef FALSE
#define	FALSE			(0)
#endif

#ifndef	TRUE
#define	TRUE			(!FALSE)
#endif


/* TODO: the same definition with adr_retcode.h,
 * which will need much time to modify
 */
typedef INT32			RET_CODE;

#define RET_SUCCESS		((INT32)0)
#define	RET_FAILURE		((INT32)1)
#define RET_BUSY        ((INT32)2)
#define RET_STA_ERR     ((INT32)3)


/* AMS other macro define */
#ifndef NULL
#define NULL 			((void *)0)
#endif
typedef UINT32			HANDLE;
#define	INVALID_HANDLE	((HANDLE)0xFFFFFFFF)
typedef void*           VP;

/* SDK version and build time */
#define SDK_VERSION  "ALiSDK5.0"
#define MKSTR(exp)    #exp
#define MKMARCOTOSTR(exp)    MKSTR(exp) 
#define VERSION_STRING    ("SDK_VERSION:["MKMARCOTOSTR(SDK_VERSION)"] Build Time:["__DATE__", "__TIME__"]")

/* brief friendly type Definition */
typedef INT8*   LPINT8;
typedef UINT8*  LPUINT8;
typedef INT16*  LPINT16;
typedef UINT16* LPUINT16;
typedef INT32*  LPINT32;
typedef UINT32* LPUINT32;

#ifndef BYTE
typedef unsigned char   BYTE;
#endif
#ifndef SHORT
typedef unsigned short  SHORT;
#endif
#ifndef USHORT
typedef unsigned short  USHORT;
#endif
#ifndef WORD
typedef unsigned short  WORD;
#endif
#ifndef DWORD
typedef unsigned long   DWORD;
#endif

typedef BYTE*   LPBYTE;
typedef WORD*   LPWORD;
typedef DWORD*  LPDWORD;

typedef DWORD               ID;
typedef ID                 ID_TASK;
typedef ID                 ID_THREAD;
typedef ID                 ID_MODULE;    // Software module ID
typedef ID                 ID_INT;       /* interrupt ID */
typedef ID                 ID_HSR;       /* high service routine ID */
typedef ID                 ID_SIGNAL;
typedef ID                 ID_STRUCTYPE; /* struct type */
typedef short              PRI;
typedef unsigned long      TMO;
typedef long               ER;

#define INVALID_ID         0xFFFF

/* Common Type Definition */
#define INLINE inline

#define INVALID_HANDLE      ((HANDLE)0xFFFFFFFF)
#define MAX_DWORD           0xFFFFFFFF
#define MAX_WORD            0xFFFF

#define C_OFF               0
#define C_ON                1

typedef void (*FP)(DWORD, DWORD);
typedef void (*TP)(UINT32,UINT32);


/* General Time Definition */
typedef struct _T_TIME
{
	UINT16	Year;
	UINT8	Month;
	UINT8	Day;
	UINT8	Hour;
	UINT8	Minute;
	UINT8	Second;
}T_TIME;

/* RECT definition */
typedef struct tagRECT
{
    WORD left;
	WORD top;
	WORD right;
	WORD bottom;
} *LPRECT, RECT;


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


/* System call Error Code */
#define E_OK               0
#define E_FAILURE       (-1)
#define E_TIMEOUT   (-2)

//================================================================================================
//ASSERT defines
#ifdef ASSERT
#undef ASSERT
#endif

#define	ASSERT(expression)				\
	{									\
		if (!(expression))				\
		{								\
			DEBUGPRINTF("assertion(%s) failed: file \"%s\", line %d\n",	\
				#expression, __FILE__, __LINE__);	\
		}								\
	}

#define ASSERTMSG(expression, message)	\
	{									\
		if (!(expression))				\
		{								\
			DEBUGPRINTF("assertion(%s) failed: file \"%s\", line %d, message %s\n", \
				#expression, __FILE__, __LINE__, #message);	\
		}								\
	}

#define	ASSERT_ADDR(address)			\
	{									\
		if((UINT32)(address)<0x010||((UINT32)(address)>=0x0180&&(UINT32)(address)<0x01a0)) \
		{								\
			DEBUGPRINTF("assertion address  failed: [%s]=[0x%08x] in file \"%s\", line %d\n", \
					#address,(address),__FILE__, __LINE__); \
		}								\
	}


/*!
 * @}
 */
 
#endif	//__BASIC_TYPES_H__

