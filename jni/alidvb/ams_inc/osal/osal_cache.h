/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    osal_cache.h
*
*    Description:    This file contains all functions declare
*		             of OSAL cache management.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.  Nov.4.2003       Justin Wu       Ver 1.0    Create file.
*													Support OSAL MIS V0.92.
*	2.	Dec.23.2003      Justin Wu       Ver 2.0    Support TDS2 - wDVD TDS.
*****************************************************************************/

#ifndef __OSAL_CACHE_H__
#define __OSAL_CACHE_H__

#include "osal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define osal_cache_flush_all(...)		do{}while(0)
#define osal_cache_invalidate_all(...)	do{}while(0)
#define osal_cache_flush(...)			do{}while(0)
#define osal_cache_invalidate(...)		do{}while(0)


#ifdef __cplusplus
}
#endif
#endif /* __OSAL_CACHE_H__ */
