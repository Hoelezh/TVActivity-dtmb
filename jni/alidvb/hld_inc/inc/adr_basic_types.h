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

#define PDKAPI_INTERNAL

#include <linux/ioctl.h>
#include <alidefinition/adf_basic.h>

#ifdef __cplusplus
extern "C" {
#endif

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
			printf("assertion(%s) failed: file \"%s\", line %d\n",	\
				#expression, __FILE__, __LINE__);	\
		}								\
	}

#define ASSERTMSG(expression, message)	\
	{									\
		if (!(expression))				\
		{								\
			printf("assertion(%s) failed: file \"%s\", line %d, message %s\n", \
				#expression, __FILE__, __LINE__, #message);	\
		}								\
	}

#define	ASSERT_ADDR(address)			\
	{									\
		if((UINT32)(address)<0x010||((UINT32)(address)>=0x0180&&(UINT32)(address)<0x01a0)) \
		{								\
			printf("assertion address  failed: [%s]=[0x%08x] in file \"%s\", line %d\n", \
					#address,(address),__FILE__, __LINE__); \
		}								\
	}


/*!
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif	//__BASIC_TYPES_H__

