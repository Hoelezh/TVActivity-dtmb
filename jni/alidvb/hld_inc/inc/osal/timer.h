#ifndef _WDVD_TDS_TIMER_HEADER_
#define _WDVD_TDS_TIMER_HEADER_

#include <adr_basic_types.h>


#define OBJ_NONEXIST	0xFFFFFFFF

#ifdef __cplusplus
extern "C"{
#endif

typedef void (*CBACK)(void*);

typedef struct timer_event_block
{
        QUEUE   queue;          /* 8 */
        TMO     time;           /* 4 */
        CBACK   callback;       /* 4 */
        void    *arg;           /* 4 */
} TMEB;
extern UINT32 task_total_num;

#define get_almcb(no)   (&g_tcb_table[no+(task_total_num -2) -TIM_BASE + 1])  //ignore the idle task #0
//#define get_cyccb(no)   (&g_tcb_table[no+NUM_TSKID-CYC_BASE + 1])

extern TMO g_current_time;
extern TMO g_current_second;
extern unsigned int g_cCurSlice;

//////////
#define TMO_NUM 32

#define TMO_ALARM	TIMER_ALARM
#define TMO_CYCLIC	TIMER_CYCLIC

typedef struct tmo_entry_block
{
	QUEUE   queue;          /* 8 */
	ID	tmoid;			/* 4 */
	short     tmotype; 	/* 2 */
	short	cycact;		/* 2 */
	TMO		cyctime;
	short	tmmode;
	TMO     time;           /* 4 */
	CBACK      timhdr;        /* 4 */
	UINT32  para1;           /* 4 */
	UINT32  para2;           /* 4 */
} T_TMOCB;
QUEUE 	g_tmo_queue;
TMO	g_tmo_time;

//////////

typedef struct systime 				/* system clock */
{
    short   utime;                          /* current date/time (upper) */
    UINT32  ltime;                          /* current date/time (lower) */
} SYSTIME;

typedef TMO     CYCTIME;                /* cycle time                       */
typedef SYSTIME ALMTIME;                /* alarm time                       */




typedef struct t_dcyc
{
    FP      cychdr;
    UINT32    cycact;
    CYCTIME cyctim;
    UINT32	para1;
    UINT32	para2;
    char	name[3];	//added by jeff wu 2003-05-27
} T_DCYC;

typedef struct t_dalm
{
    FP      almhdr;
    UINT32    tmmode;
    ALMTIME almtim;
    UINT32	para1;
    UINT32	para2;
    char	name[3];	//added by jeff wu 2003-05-27
} T_DALM;

ER get_tim(SYSTIME *pk_tim);

ID i_cre_alarm(T_DALM* pk_dalm);
ID i_cre_cyclic(T_DCYC *pk_dcyc);
ER i_del_cyclic(ID cycno);
ER i_activate_cyclic(ID, UINT32);
ER i_set_alarm_timer(ID almno, TMO new_interval);
ER i_del_alarm(ID almno);




//void InitTimer(void);
//void timer_insert_abs(TMEB *, TMO, CBACK, void *);
//void timer_insert_rel(TMEB *, TMO, CBACK, void *);
//void timer_delete(TMEB *);
//void SysTimerHdr(void);
//void call_cychdr(UINT para1,UINT32 para2);
//void call_almhdr(UINT para1,UINT32 para2);
//ID i_CreateTimer (T_TIMER* pk_dalm);

//void IntDispatch(void);
//TMO cal_tmout(TMEB* event);

// Internal Interface
ER def_alm(ID, T_DALM *);
ER def_cyc(ID, T_DCYC *);
//ER set_cyc_pri(short cycno, PRI cycpri);
//ER set_alm_pri(short almno, PRI almpri);

#ifdef __cplusplus
}
#endif

#endif /* _TIMER_ */
