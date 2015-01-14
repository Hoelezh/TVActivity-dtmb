/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    osal_flag.h
*
*    Description:    This file contains all functions declare
*		             of OSAL flag.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.  Nov.4.2003       Justin Wu       Ver 1.0    Create file.
*													Support OSAL MIS V0.92.
*	2.	Dec.23.2003      Justin Wu       Ver 2.0    Support TDS2 - wDVD TDS.
*****************************************************************************/

#ifndef __OSAL_FLAG_H__
#define __OSAL_FLAG_H__

#include "osal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TWF_ANDW           0x00000001
#define TWF_ORW            0x00000002
#define TWF_CLR            0x00000004

enum
{
	OSAL_TWF_ANDW	= TWF_ANDW,	/* Release task until all specified bits are set */
	OSAL_TWF_ORW	= TWF_ORW,	/* Release task if one of specified bits are set */
	OSAL_TWF_CLR	= TWF_CLR,	/* Clear flag after the first waiting task released */
};

#define osal_flag_create					OS_CreateFlag
#define osal_flag_delete					OS_DelFlag
#define osal_flag_wait						OS_WaitFlagTimeOut
#define osal_flag_set						OS_SetFlag
#define osal_flag_clear						OS_ClearFlag


#ifdef __cplusplus
}
#endif
#endif /* __OSAL_FLAG_H__ */
