/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    osal_timer.h
*
*    Description:    This file contains all functions declare
*		             of OSAL timer.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Jun.5.2003       Justin Wu       Ver 0.1    Create file.
*	2.  Nov.4.2003       Justin Wu       Ver 1.0    Support OSAL MIS V0.92.
*	3.	Dec.23.2003      Justin Wu       Ver 2.0    Support TDS2 - wDVD TDS.
*****************************************************************************/

#ifndef __OSAL_TIMER_H__
#define __OSAL_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "osal.h"

#define TIMER_ALARM         0x01
#define TIMER_CYCLIC        0x02

#define TMO_POL             0
#define TMO_FEVR            (DWORD)(-1)

typedef void                (*TMR_PROC)(UINT32);

typedef struct t_timer
{
    TMR_PROC            callback;
    UINT16              type;
    TMO             time;
    UINT32              param;
    char                name[3];    //added by jeff wu 2003-05-27
} T_TIMER;

DWORD OS_GetTickCount(void);
void OS_Delay(WORD us);
ID OS_CreateTimer (T_TIMER* pTimerInfo);
ER OS_DeleteTimer(ID);
ER OS_SetTimer(ID,UINT32);
ER OS_ActivateTimer(ID,BOOL);

#define TCY_OFF         0x00000000          /* Not use */
#define TCY_ON          0x00000001
#define TCY_INI         0x00000002          /* Not use */

#define TTM_ABS         0x00000000
#define TTM_REL         0x00000001


enum
{
	OSAL_TIMER_ALARM	= TIMER_ALARM,		/* Alarm, run only once */
	OSAL_TIMER_CYCLE	= TIMER_CYCLIC,		/* Cycle */
};

#define osal_timer_create					OS_CreateTimer
#define osal_timer_delete					OS_DeleteTimer
#define osal_timer_set						OS_SetTimer
#define osal_timer_activate					OS_ActivateTimer
#define osal_get_tick						OS_GetTickCount
#define osal_get_time						OS_GetTime
#define osal_delay							OS_Delay

#define OSAL_T_TIMER_FUNC_PTR				TMR_PROC
#define OSAL_T_CTIM							T_TIMER

#ifdef __cplusplus
}
#endif


#endif /* __OSAL_TIMER_H__ */
