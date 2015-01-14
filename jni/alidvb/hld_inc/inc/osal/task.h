#ifndef _WDVD_TDS_TASK_HEADER_
#define _WDVD_TDS_TASK_HEADER_

#include <adr_basic_types.h>
#include <osal/osal.h>


#ifdef __cplusplus
extern "C"{
#endif

// Idle Task ID
#define 	TASK_ID_IDLE 		0x0			//idle task
// Task Slot that's reserved for HSR
#define 	TASK_ID_HSR			0x1			//HSR routine	task

//	2003－11－25,Jeff Wu, 增加对dispatch enable/disable的嵌套支持
//  允许同一个线程多次进入，以一个count来计数
//	同时用TASK ID来核对，如果出现一个线程disable dispatch
//	却被另外一个enable，将ASSERT

#define	DISPATCH_NEST_SUPPORT

typedef struct
{
    VP      msg;
    INT32     *p_msgsz;
} WINFO_MBF;

typedef struct
{
    VP      msg;
    INT32     msgsz;
} WINFO_SMBF;

typedef struct
{
    UINT32    waiptn;
    UINT32    wfmode;
    UINT32    *p_flgptn;
} WINFO_FLG;

typedef struct
{  /// added by Eagle
	INT32	blksz;
	VP	*p_blk;
} WINFO_MPL;

typedef struct
{
    UINT32    waiptn;
    UINT32    *p_tflptn;
} WINFO_TFL;

typedef union
{
    WINFO_MBF   mbf;
    WINFO_SMBF  smbf;
    WINFO_FLG   flg;
    WINFO_TFL   tfl;
    WINFO_MPL	mpl; //// added by Eagle
} WINFO;

/* enumeration of Task Status */
typedef enum
{
        RUN,
        READY,
        WAIT_FLAG,
        WAIT_TSKFLG,
        WAIT_SEMAPHORE,
        WAIT_MESSAGE,
        WAIT_TIMER,
        WAIT_MPL,			/*added by eagle*/
        SLEEP,
        NO_EXIST
} TSTAT;


/* Task Contrl Block */
typedef struct task_control_block
{
	QUEUE   tskque;         /* pointer for Dual-direction linked list */
	ID      tskid;          /* task ID */
	short   timeslice;      /*10 value of timeslice */
	FP      task;           /*12 task entry  */

	UINT32	sp;             /*16 Current stack address*/
	UINT32	stackbegin;     /*20 Stack begin address */
	UINT32	stackend;       /*24 Stack end address*/

	TMO		curslice;		/*28 Current time slice value*/
	TSTAT   state;          /* task state */
	WINFO   winfo;          /* wait information */

	TMEB    wtmeb;          /* timer control block */
//    UINT32    actcnt;         /* Active counter for timer handler */
    FP      timhdr;         /* User Cyclic/Alarm handler */
    UINT32    cycact;         /* Cyclic state */
    CYCTIME cyctim;         /* Cyclic time interval */

    ER      *wercd;         /* Return code pointer */
    UINT32    tskflg;         /* Task flag */

    void    *exinf;         /* Extention information, not used */
    UINT32    tskatr;         /* Task attribute, not used */

    char	name[3];	//added by jeff wu 2003-05-27,for debug monitor usage
#ifdef _TDS_TASK_PERFORMANCE
	TMO		cputime;
	TMO		mon_statime;
#endif
#ifdef _TDS_PERFORMANCE
	UINT32	dispatchcount;
#endif
	PRI	priority;
	UINT32	param1;
	UINT32	param2;
	QUEUE * waithead;     /// Eagle

} TCB;


/* pointer of Excuting Task */
extern TCB *g_pTskRun;

/* pointer of Scheduled Task */
extern TCB *g_pTskSch;

extern TCB *g_tcb_table;
//#define IDtoINDEX_TCB(id)   (id-TCB_BASE)
#define IDtoINDEX_TCB(id)   (id-TCB_BASE + 1) // ignore the idle task #0
#define get_tcb(id)         (&g_tcb_table[IDtoINDEX_TCB(id)])

void task_initialize(UINT32 task_num);
ER i_cre_tsk(TCB *, T_CTSK *, INT32);
void make_ready(TCB *);
void make_wait(TMO, CBACK);
void wait_release(TCB *);
void wait_release_ok(TCB *);
void wait_delete(QUEUE *);
ID wait_tskid(QUEUE *);

ID_THREAD look_thdid(void);		// find free id for thread
#define TASK_TYPE_UNKNOWN 0		// used for return of iden_tsk_thd
#define TASK_TYPE_TASK 1
#define TASK_TYPE_THREAD 2
#define OFFSET_STACK 0	// offset of task stack
INT32 iden_tsk_thd(ID tskid);		// identify the id is task or thread

/* this is the old scheduler, by joe also, stupid but simple
 	TCB *schedule(void); */

/* new scheduler routines */
TCB *sched(void);		/* schedule the new task */
void rdy_del(TCB *who);		/* remove one from ready queues, when it is blocked */
void rdy_add(TCB *who);		/* add one to ready queue, when it get ready again */
void sched_init(void);		/* initializing the scheduler data structure, needn't call, bss is clean */
unsigned int get_top_pri(void);
ER chg_pri(TCB * tcb, PRI pri);
ER del_tsk(ID tskid);

//this function will dispatch task immediately
void OS_TaskDispatch(BOOL bEnableDispatch);


#define ter_tsk RequestCloseTask

// Internal Interfaces
ER RequestCloseTask(ID_TASK);
ER DeleteTask(ID_TASK);
ER DeleteThread(ID_THREAD);
//ER set_tsk_pri(ID tskid, PRI tskpri);
INT32 GetTaskState(ID_TASK tsk_id);

//Dynamic priority function support
#ifdef DYNAMIC_PRIORITY
BOOL	increase_task_pri(TCB * who);
BOOL	decrease_task_pri(TCB * who);
ER 		modify_priority(TCB * tcb, PRI pri);
#endif
void	IntDispatch1(void);

ER i_start_thread(ID_THREAD thdid);


#ifdef __cplusplus
}
#endif

#endif /* _TASK_ */
