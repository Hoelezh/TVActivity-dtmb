/****************************************************************************(I)(S)
 *  (C)
 *  ALi (Shanghai) Corporation. 2010 Copyright (C)
 *  (C)
 *  File: typedef.h
 *  (I)
 *  Description:
 *  (S)
 *  History:(M)
 *      	Date        			Author         	Comment
 *      	====        			======		=======
 * 0.		2010.06.03			Sam			Create
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version
* 2 of the License, or (at your option) any later version.
*
*****************************************************************************/
 
#ifndef __M36_TYPEDEF_H
#define __M36_TYPEDEF_H

#if 1
#include <alidefinition/adf_basic.h>
#else
typedef int					_BOOL;
typedef void				VOID;
typedef VOID*				VOID_POINTER;
//-----------------------------------------------
//
//Define data type mode
//
//-----------------------------------------------
#define _DATA_TYPE_SEL_	2



#if (_DATA_TYPE_SEL_==1)
//-----------------------------------------------
//
// data type (1)
//
//-----------------------------------------------
typedef _BOOL 							BOOL;
typedef unsigned char 					BYTE;
typedef unsigned short int 				WORD;
typedef unsigned int 					DWORD;
typedef char 							SBYTE;
typedef short int 						SWORD;
typedef int 							SDWORD;

typedef _BOOL 	*						PBOOL;
typedef unsigned char	*				PBYTE;
typedef unsigned short int  *			PWORD;
typedef unsigned int	*				PDWORD;
typedef char  *							PSBYTE;
typedef short int   *					PSWORD;
typedef int *							PSDWORD;

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


#elif (_DATA_TYPE_SEL_==2)
//-----------------------------------------------
//
// data type (2)	Force pointer use volatile, that is, PBYTE = VPBYTE
//
//-----------------------------------------------
typedef _BOOL 							BOOL;
typedef unsigned char 					BYTE;
typedef unsigned short int 				WORD;
typedef unsigned int 					DWORD;
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

#else
//-----------------------------------------------
//
// data type (3)	Force every variable use volatile
//
//-----------------------------------------------
typedef volatile _BOOL 					BOOL;
typedef volatile unsigned char 			BYTE;
typedef volatile unsigned short int 	WORD;
typedef volatile unsigned int 			DWORD;
typedef volatile char 					SBYTE;
typedef volatile short int 				SWORD;
typedef volatile int 					SDWORD;

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

#endif

#define	FALSE							(0)
#define	TRUE							(!FALSE)

//RET for return code, you mey define your privte RET_??? code from
//0x80000000 to 0xFFFFFFFF.
typedef SDWORD							RET_CODE;
#define RET_SUCCESS						((SDWORD)0)
#define	RET_FAILURE						((SDWORD)1)
#define RET_BUSY						((SDWORD)2)
#define	RET_STA_ERR						((SDWORD)3)

#define RET_PASS						((SDWORD)0)	// do nothing
#define RET_DONE						((SDWORD)4)	// done

#define CODE	BYTE
#define XBYTE	BYTE
#define XWORD	WORD
#define XDWORD	DWORD

//#define NULL							((VOID *)0)

typedef DWORD							HANDLE;
#define	INVALID_HANDLE				((HANDLE)0xFFFFFFFF)
typedef WORD							UNICHAR;
//typedef DWORD							size_t;
//typedef	SDWORD							time_t;

//????? what's VP???
typedef VOID*							VP;

// ****************************************************************************
// union which converts two 8bit values into 16bit value.
// ****************************************************************************
typedef	union
{
	WORD	uint_16;
	struct
	{
		BYTE	uint80;		// LSB
		BYTE	uint81;		// MSB
	} uint_8;
} UINT16TO8;

// ****************************************************************************
// union which converts two 16bit values into 32bit value.
// ****************************************************************************
typedef	union
{
	DWORD	uint_32;
	struct
	{
		WORD	low_16;
		WORD	hi_16;
	} uint_16;
} UINT32TO16;

typedef struct
{
	//b[0] b[1] b[2] b[3] b[4] b[5] b[6] b[7]
	//dw[0] = b[3] b[2] b[1] b[0]	dw[1] = b[7] b[6] b[5] b[4]
	//ull[0] = b[7] b[6] b[5] b[4] b[3] b[2] b[1] b[0]
	union
	{
    	unsigned long long int	ull[1];
	    DWORD 					dw[2];
	    BYTE					b[8];
	}value;
}ULL_t;


// Support macros
#define itemsof(a)      (sizeof(a) / sizeof(a[0]))

//#include "retcode.h"
#endif

#endif // end of __TYPEDEF_H
