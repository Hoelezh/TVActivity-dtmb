/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2003 Copyright (C)
*
*    File:    printf.h
*
*    Description:    This file contains all functions definition
*		             of LIBC printf.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	2002.??.??      Justin Wu       Ver 0.1     Create file.
*   2.  2003.12.05      Justin Wu       Ver 0.2     Support wDVD Standard TDS
*													-- Common Service:
*													.ERRMSG & DEBUGPRINTF
*													.ASSERTMSG & ASSERT_ADDR
*****************************************************************************/


#ifndef _LIB_C_PRINTF_H
#define _LIB_C_PRINTF_H

//#include <osal/osal.h>
//#include <hal/machine.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif


//================================================================================================
//printf group functions
#define soc_printf	printf
#define libc_printf	printf


struct arg_printf
{
	void *data;
	int (*put)(void*, unsigned int, void*);
};



//================================================================================================
//macro define for the printf functons
#define FIXED_PRINTF			libc_printf
#define ERRMSG					DEBUGPRINTF


#if 0
#define PRINTF					libc_printf
#define DEBUGPRINTF				libc_printf
#else
#define PRINTF(...)					do{}while(0)
#define DEBUGPRINTF(...)				do{}while(0)
#endif
#define DEBUGLINE()		do{PRINTF("%s: %d\n", __FUNCTION__, __LINE__);}while(0)

#define ENTER_FUNCTION	DEBUGPRINTF("Function %s: Begin.\n",__FUNCTION__)
#define LEAVE_FUNCTION	DEBUGPRINTF("Function %s: End From %d line. \n", __FUNCTION__, __LINE__)

#ifdef __cplusplus
}
#endif
#endif /* _LIB_C_PRINTF_H */

