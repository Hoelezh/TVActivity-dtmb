/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    osal_sema.h
*
*    Description:    This file contains all functions declare
*		             of OSAL semaphore.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.  Nov.4.2003       Justin Wu       Ver 1.0    Create file.
*													Support OSAL MIS V0.92.
*	2.	Dec.23.2003      Justin Wu       Ver 2.0    Support TDS2 - wDVD TDS.
*****************************************************************************/

#ifndef __OSAL_SEMA_H__
#define __OSAL_SEMA_H__

#include "osal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define osal_semaphore_create				OS_CreateSemaphore
#define osal_semaphore_delete				OS_DelSemaphore
#define osal_semaphore_capture				OS_AcquireSemaphoreTimeOut
#define osal_semaphore_release				OS_FreeSemaphore

#ifdef __cplusplus
}
#endif
#endif /* __OSAL_SEMA_H__ */
