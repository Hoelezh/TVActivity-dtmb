/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    osal_mm.h
*
*    Description:    This file contains all functions declare
*		             of OSAL memory management.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Jul.15.2003      Justin Wu       Ver 0.1    Create file.
*	2.  Nov.3.2003       Justin Wu       Ver 1.0    Support OSAL MIS V0.92.
*	3.	Dec.23.2003      Justin Wu       Ver 2.0    Support TDS2 - wDVD TDS.
*****************************************************************************/

#ifndef __OSAL_MM_H__
#define __OSAL_MM_H__

#include "osal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define osal_memory_allocate		malloc
#define osal_memory_free(...)			free

#define osal_mm_pa_to_va(pa)			(pa)
#define osal_mm_va_to_pa(va)			(va)

#ifdef __cplusplus
}
#endif
#endif /* __OSAL_MM_H__ */
