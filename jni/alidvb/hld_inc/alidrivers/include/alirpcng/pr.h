/****************************************************************************
 *
 *  ALi (shenzhen) Corporation, All Rights Reserved. 2012 Copyright (C)
 *
 *  File: pr.h
 *
 *  Description: Portable runtime OS header file.
 *
 *  History:
 *      Date            Author          Version         Comment
 *      ====            ======          =======         =======
 *  1.  2013.01.25      David.L         0.1.000         Initial
 ****************************************************************************/

#ifndef  __PR_H__
#define  __PR_H__

#include "pr_types.h"

#define PR_OS_OK                0
#define PR_OS_ERR               -1
#define PR_OS_TIMEOUT           62

#define PR_TIMEOUT_INFINITE     (~0)

#if defined(__ALI_TDS__)

#include <osal/osal.h>
#include <api/libc/printf.h>

typedef OSAL_ID                 Thread;
typedef void (*ThreadFunc)(void *arg);

typedef OSAL_ID                 Mutex;

typedef struct _CondVar         CondVar;
struct _CondVar {
    Mutex *mutex;
    OSAL_ID cv;
    Int32 flag;          /*Added by tony for enhance this designation*/
};

typedef OSAL_ID                 Semaphore;

#define PR_LOG                  libc_printf

#elif defined(__ALI_LINUX__)

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef pthread_t               Thread;
typedef void (*ThreadFunc)(void *arg);

typedef pthread_mutex_t         Mutex;

typedef struct _CondVar         CondVar;
struct _CondVar {
    Mutex *mutex;
    pthread_cond_t cv;
    Int32 flag;          /*Added by tony for enhance this designation*/
};

typedef sem_t                   Semaphore;

#define PR_LOG                  printf

#elif defined(__ALI_LINUX_KERNEL__)

#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/completion.h>
#include <linux/errno.h>
#include <linux/delay.h>

/** Please be noted, the Thread is a pointer, struct task_struct *.
 */
typedef struct task_struct *    Thread;

typedef void (*ThreadFunc)(void *arg);

typedef struct semaphore        Mutex;

typedef struct _CondVar         CondVar;
struct _CondVar {
    Mutex *mutex;
    struct completion cv;
    Int32 flag;          /*Added by tony for enhance this designation*/
};

typedef struct semaphore        Semaphore;

#define PR_LOG                  printk

#else
#error "Wrong OS type setting."
#endif

/*----------------------------------------------------------------------------*/

void *PR_Malloc(Size_t n);
void PR_Free(void *ptr);

void PR_uSleep(Uint32 usec);
void PR_Sleep(Uint32 sec);

Int32 PR_ThreadCreate(Thread *tid, ThreadFunc thread, void *arg, Int32 prio, Uint32 stacksize, Int8 *name);
Int32 PR_ThreadDestroy(Thread *tid);
Bool PR_ThreadTestCancel(void);

Int32 PR_MutexInit(Mutex *mutex);
Int32 PR_MutexDestroy(Mutex *mutex);
Int32 PR_Lock(Mutex *mutex);
Int32 PR_Unlock(Mutex *mutex);

Int32 PR_CondVarInit(CondVar *cvar, Mutex *mutex);
Int32 PR_CondVarDestroy(CondVar *cvar);
Int32 PR_CondVarWait(CondVar *cvar, Uint32 timeout);
Int32 PR_CondVarNotify(CondVar *cvar);

Int32 PR_SemInit(Semaphore *sem, Uint32 value);
Int32 PR_SemDestroy(Semaphore *sem);
Int32 PR_SemWait(Semaphore *sem, Int32 timeoutms);
Int32 PR_SemPost(Semaphore *sem);

#endif // __PR_H__

