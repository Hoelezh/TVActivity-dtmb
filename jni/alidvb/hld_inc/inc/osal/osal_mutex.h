/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    osal_mutex.h
*
*    Description:    This file contains all functions declare
*		             of OSAL mutex.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Dec.15.2005      Goliath Peng  Ver 1.0    Create.
*****************************************************************************/

#ifndef __OSAL_MUTEX_H__
#define __OSAL_MUTEX_H__

#include "osal.h"

#ifdef __cplusplus
extern "C" {
#endif

ID OS_CreateMutex(void);
ER OS_DeleteMutex(ID meid);
ER OS_LockMutex(ID meid,TMO tmout);
ER OS_UnlockMutex(ID meid);

#define osal_mutex_create			OS_CreateMutex
#define osal_mutex_delete			OS_DeleteMutex
#define osal_mutex_lock				OS_LockMutex
#define osal_mutex_unlock			OS_UnlockMutex

#ifdef __cplusplus
}
#endif
#endif /* __OSAL_MUTEX_H__ */

