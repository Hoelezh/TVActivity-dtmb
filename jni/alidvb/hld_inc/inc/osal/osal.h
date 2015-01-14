/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    osal.h
*
*    Description:    This file contains all functions and structure declare
*		             of OSAL.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Nov.3.2003       Justin Wu       Ver 0.1    Create file.
*	2.	Dec.23.2003      Justin Wu       Ver 0.2    Support TDS2 - wDVD TDS.
*****************************************************************************/


#ifndef __OSAL_H__
#define __OSAL_H__

#include <adr_basic_types.h>
#include <adr_retcode.h>
#include "osal_task.h"
#include "osal_int.h"
#include "osal_timer.h"
#include "osal_msgq.h"
#include "osal_sema.h"
#include "osal_flag.h"
#include "osal_mm.h"
#include "osal_cache.h"
#include "osal_mutex.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OSAL_E_OK					E_OK
#define OSAL_E_FAIL					E_FAILURE
#define OSAL_E_TIMEOUT				E_TIMEOUT

#define OSAL_INVALID_ID				INVALID_ID
#define OSAL_WAIT_FOREVER_TIME		0xFFFFFFFF

typedef INT32  OSAL_ER;
typedef UINT32 OSAL_ID;

typedef TMO                DLYTIME;        /* delay time */

#define OS_ThreadSleep  dly_tsk
#define OS_TaskSleep OS_ThreadSleep

#define TA_TFIFO           0          /* FIFO wait queue */
#define TA_WSGL            0x00000000
#define TA_WMUL            0x00000008

// Mask to clear all flag
#define TDS_FLAG_ALL       0xFFFFFFFF

///////////////////////////////////////////////////////
//      Part II     memory pool interface               //
///////////////////////////////////////////////////////
ID OS_CreateFlag(UINT32 flgptn);
ER OS_DelFlag(const ID flgid);
ER OS_SetFlag(ID, UINT32);
ER OS_ClearFlag(ID, UINT32);
ER OS_WaitFlagTimeOut(UINT32 *, ID, UINT32, UINT32, TMO);

#define OS_WaitFlag(A,B,C,D)        OS_WaitFlagTimeOut(A,B,C,D,TMO_FEVR)
#define OS_TestFlag(A,B,C,D)        OS_WaitFlagTimeOut(A,B,C,D,TMO_POL)


///////////////////////////////////////////////////////
//      Part IV  Semaphore interface                    //
//////////////////////////////////////////////////////
ID OS_CreateSemaphore(INT32 semcnt);
ER OS_DelSemaphore(ID);
ER OS_FreeSemaphore(ID);
ER OS_AcquireSemaphoreTimeOut(ID semid, TMO tmout);


#define OS_AcquireSemaphore(A)      OS_AcquireSemaphoreTimeOut(A,TMO_FEVR)

typedef enum{
    MSG_TYPE_INPUT,
    MSG_TYPE_SIGNAL,
    MSG_TYPE_DEVSTA,
    MSG_TYPE_NVINFO,
    MSG_TYPE_PAUSE,
    MSG_TYPE_RESUME,
    MSG_TYPE_UPDATE,
    MSG_TYPE_CLOSEWIN,//add by sunny 0818
    MSG_TYPE_REDRAWWIN,//add by sunny 0818
    MSG_TYPE_HSR,           //add by jeff 0820
    MSG_TYPE_EXIT,//add by sunny 1029
    MSG_TYPE_SYSTEM,    // Singer for System Message
    MSG_TYPE_ATAPI_INFO,    // tom for atapi tray-closed message
}MSG_TYPE;

typedef struct t_cmbf
{
    INT32     bufsz;
    INT32     maxmsz;
    char    name[3];    //added by jeff wu 2003-05-27
} T_CMBF;

typedef struct tagMSG_HEAD
{
    MSG_TYPE    bMsgType;       // Message type
    ID_MODULE   bModuleID;      // Module ID of the sender
}MSG_HEAD, *PMSG_HEAD;

typedef struct
{
    ID_MODULE   ModID;          //sender module ID
    MSG_TYPE    MsgType;        //sender message Type
    DWORD       dPara;          // info 1
    DWORD       wPara;          // info 2,should be dPara2
    WORD        wID;            //ext ID info
    TMO         SysTime;        //current time,ms based
}TMSG,*LPTMSG;

ID OS_CreateMsgBuffer (T_CMBF *pk_cmbf);
ER OS_SendMsgTimeOut(ID, VP, INT32, TMO);
ER OS_GetMsgTimeOut(VP, INT32 *, ID, TMO);
ER OS_DelMessageBuffer(ID);

ER OS_GetMessage(VP, INT32 *, ID);
ER OS_PeekMessage(VP, INT32 *, ID);
ER OS_SendMessage(ID, VP, INT32);
ER OS_PostMessage(ID, VP, INT32);

///////////////////////////////////////////////////////
//      Part VI     Timer interface                     //
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//  Mutex Interface
///////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif
#endif /* __OSAL_H__ */
