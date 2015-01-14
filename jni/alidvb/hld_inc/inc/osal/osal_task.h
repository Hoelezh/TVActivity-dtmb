/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    osal_task.h
*
*    Description:    This file contains all functions declare
*		             of OSAL task management.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Jun.5.2003       Justin Wu       Ver 0.1    Create file.
*	2.  Nov.3.2003       Justin Wu       Ver 1.0    Support OSAL MIS V0.92.
*	3.	Dec.23.2003      Justin Wu       Ver 2.0    Support TDS2 - wDVD TDS.
*****************************************************************************/

#ifndef __OSAL_TASK_H__
#define __OSAL_TASK_H__

#include <osal/osal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* task priority config */
#define LOW_PRI             31    // Min number, but the highest level
#define HIGH_PRI            0     // Max number,but the lowest level
#define DEF_PRI             20    // default level for normal thread
#define HSR_PRI             10    // HSR level, higher than normal
#define DYN_PRI             18    // Dynamic level, only  once.

typedef struct t_ctsk
{
    FP      task;
    PRI     itskpri;
    INT32   stksz;
    UINT32  quantum;
    UINT32  para1;
    UINT32  para2;
    char    name[3];    //added by jeff wu 2003-05-27
} T_CTSK;

#define T_CTHD  T_CTSK

ID_THREAD OS_CreateThread(T_CTHD *);
void OS_Exit(ER ExitCode);
ER OS_DeleteThread(ID_THREAD);
ID OS_GetCurrentThreadID(void);


/* Type define for task priority */
enum
{
	OSAL_PRI_LOW		= LOW_PRI,			/* Lowest,  for idle task */
	OSAL_PRI_NORMAL		= DEF_PRI,			/* Normal,  for user task */
	OSAL_PRI_HIGH		= 17,				/* High,    for system task */
	OSAL_PRI_CRITICL	= HSR_PRI,			/* Highest, for HSR scheduler */
};

#define	OSAL_TICK_SIZE		10

#define osal_task_get_current_id			OS_GetCurrentThreadID
#define osal_task_create					OS_CreateThread
#define osal_task_sleep						OS_TaskSleep
#define osal_task_exit						OS_Exit
#define osal_task_delete					OS_DeleteThread
#define osal_task_dispatch_off(...)				do{}while(0)
#define osal_task_dispatch_on(...)				do{}while(0)

#define osal_task_save_thread_info          OS_SaveThreadInfo
#define osal_task_get_process_pid           OS_GetProcessPID
#define osal_task_get_thread_pid            OS_GetThreadPID
#define osal_task_get_thread_name           OS_GetThreadName
#define osal_task_get_thread_state          OS_GetThreadState
#define osal_task_get_thread_priority       OS_GetThreadPriority
#define osal_task_set_thread_priority       OS_SetThreadPriority
#define osal_task_get_thread_CPUTime        OS_GetThreadCPUTime
#define osal_task_show_thread_info          OS_ShowThreadInfo

#define OSAL_T_TASK_FUNC_PTR				FP
#define OSAL_T_CTSK							T_CTSK

#ifdef __cplusplus
}
#endif
#endif /* __OSAL_TASK_H__ */

