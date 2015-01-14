/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    osal_int.h
*
*    Description:    This file contains all functions declare
*		             of OSAL interrupt management.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Jun.5.2003       Justin Wu       Ver 0.1    Create file.
*	2.  Nov.4.2003       Justin Wu       Ver 1.0    Support OSAL MIS V0.92.
*	3.	Dec.23.2003      Justin Wu       Ver 2.0    Support TDS2 - wDVD TDS.
*****************************************************************************/

#ifndef __OSAL_INT_H__
#define __OSAL_INT_H__

#include "osal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define osal_interrupt_register_lsr(...)	OSAL_E_FAIL
#define osal_interrupt_unregister_lsr(...)	OSAL_E_FAIL
#define osal_interrupt_register_hsr(...)	OSAL_E_FAIL
#define osal_interrupt_disable(...)			do{}while(0)
#define osal_interrupt_enable(...)			do{}while(0)

typedef void (*OSAL_T_LSR_PROC_FUNC_PTR)(UINT32);
typedef void (*OSAL_T_HSR_PROC_FUNC_PTR)(UINT32);


#ifdef __cplusplus
}
#endif
#endif /* __OSAL_INT_H__ */
