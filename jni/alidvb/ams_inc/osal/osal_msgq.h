/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    osal_msgq.h
*
*    Description:    This file contains all functions declare
*		             of OSAL message queue.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.  Nov.4.2003       Justin Wu       Ver 1.0    Create file.
*													Support OSAL MIS V0.92.
*	2.	Dec.23.2003      Justin Wu       Ver 2.0    Support TDS2 - wDVD TDS.
*****************************************************************************/

#ifndef __OSAL_MSGQ_H__
#define __OSAL_MSGQ_H__

#include "osal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define osal_msgqueue_create				OS_CreateMsgBuffer
#define osal_msgqueue_delete				OS_DelMessageBuffer
#define osal_msgqueue_send					OS_SendMsgTimeOut
#define osal_msgqueue_receive				OS_GetMsgTimeOut

#define OSAL_T_CMBF							T_CMBF

#ifdef __cplusplus
}
#endif
#endif /* __OSAL_MSGQ_H__ */
