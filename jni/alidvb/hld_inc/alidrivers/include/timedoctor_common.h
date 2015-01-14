#ifndef _TIMEDOCTOR_COMMON_H
#define _TIMEDOCTOR_COMMON_H

/* cmd:
 */
#define TDI_DSC     6
#define TDI_VAL     5
#define TDI_DELETE  4
#define TDI_CREATE  3
#define TDI_GENERIC 2
#define TDI_START   1
#define TDI_STOP    0

/* type:
 */
#define TDI_TASK   0
#define TDI_ISR    1
#define TDI_SEM    2
#define TDI_QUEUE  3
#define TDI_EVENT  4
#define TDI_VALUE  5
#define TDI_CYCLES 6
#define TDI_NOTE   7
#define TDI_AGENT  8
#define TDI_MEMORY 9
#define TDI_PORT   11
#define TDI_MAX_TYPES  12

/* Below types below to cmd TDI_DSC:
 */
#define TDI_DSC_STRING  0
#define TDI_DSC_NUMBER  1
#define TDI_DSC_TIME    2
#define TDI_DSC_COLOR   3

#define TDI_COMMAND(cmd, type) (cmd << 24 | type << 16)

#ifdef CONFIG_TIMEDOCTOR
/* interfaces to log data */
#define td_task_create(id)      td_Info(TDI_COMMAND(TDI_CREATE, TDI_TASK) | (id))
#define td_isr_create(id)       td_Info(TDI_COMMAND(TDI_CREATE, TDI_ISR) | (id))
#define td_queue_create(id)     td_Info(TDI_COMMAND(TDI_CREATE, TDI_QUEUE) | (id))
#define td_port_create(id, prod, cons) td_3Info((TDI_COMMAND(TDI_CREATE, TDI_PORT) | (id)), prod, cons)

#define td_task_delete(id)      td_Info(TDI_COMMAND(TDI_DELETE, TDI_TASK) | (id))
#define td_isr_delete(id)       td_Info(TDI_COMMAND(TDI_DELETE, TDI_ISR) | (id))
#define td_queue_delete(id)     td_Info(TDI_COMMAND(TDI_DELETE, TDI_QUEUE) | (id))
#define td_port_delete(id)      td_Info(TDI_COMMAND(TDI_DELETE, TDI_PORT) | (id))

#define td_task_start(id)       td_Info(TDI_COMMAND(TDI_START, TDI_TASK) | (id))
#define td_isr_enter(id)        td_Info(TDI_COMMAND(TDI_START, TDI_ISR) | (id))
#define td_sem_acquire(id)      td_Info(TDI_COMMAND(TDI_START, TDI_SEM) | (id))
#define td_queue_send(id, size) td_3Info((TDI_COMMAND(TDI_START, TDI_QUEUE) | (id)), size, 0)
#define td_event_send(id)       td_Info(TDI_COMMAND(TDI_START, TDI_EVENT) | (id))
#define td_agent_start(id)      td_Info(TDI_COMMAND(TDI_START, TDI_AGENT) | (id))
#define td_port_send(id, size)  td_3Info((TDI_COMMAND(TDI_START, TDI_PORT) | (id)), size, 0)

#define td_task_stop(id)        td_Info(TDI_COMMAND(TDI_STOP, TDI_TASK) | (id))
#define td_isr_exit(id)         td_Info(TDI_COMMAND(TDI_STOP, TDI_ISR) | (id))
#define td_sem_release(id)      td_Info(TDI_COMMAND(TDI_STOP, TDI_SEM) | (id))
#define td_queue_receive(id, size)  td_3Info((TDI_COMMAND(TDI_STOP, TDI_QUEUE) | (id)), size, 0)
#define td_event_receive(id)    td_Info(TDI_COMMAND(TDI_STOP, TDI_EVENT) | (id))
#define td_agent_stop(id)       td_Info(TDI_COMMAND(TDI_STOP, TDI_AGENT) | (id))
#define td_port_receive(id, size)   td_3Info((TDI_COMMAND(TDI_STOP, TDI_PORT) | (id)), size, 0)

#define td_setVal(id, value)    td_3Info((TDI_COMMAND(TDI_VAL, TDI_VALUE) | (id)), value, 0)

/* below is use combined to show values
 * we use td_genericEvent(id) to indicate a generic event. Following the td_description() can be 
 * used to describe a value for this event. td_setDscName() can be used to set name of the 
 * description. To well understand, can refer the sample.tdi
 */
#define td_genericEvent(id) td_Info(TDI_COMMAND(TDI_GENERIC, TDI_NOTE) | (id))
#define td_dscription(id, type, value) td_2Info(value, TDI_COMMAND(TDI_DSC, type) | (id))



#define TD_DEFAULT_TDILOG_MEM       (8*1024)
#define TD_DEFAULT_DATALOG_MEM		(128*1024)

/* interfaces to control timedoctor */
struct tdLogCtl
{
    unsigned int loglevel;  //see below
    unsigned char wrapper; //0 ¨C wrapper disabled, 1 ¨C wrapper enabled
    unsigned int memsize;  //
};

#define TD_LOG_NONE     0x0
#define TD_LOG_TASK     0x01
#define TD_LOG_ISR      0x02
#define TD_LOG_ALL      0xffffffff
/* stop timedoctor: TD_LOG_NONE
 * start timedoctor: TD_LOG_ALL
 * start timedoctor but no isr: TD_LOG_ALL & (~TD_LOG_ISR)
 */

struct tdTagName
{
    int type;
    int id;
    char * name;
    int nameLen;
};

/* ioctl for timedoctor device */
#define TD_IOCTL_INFO               _IO( 'T', 11)
#define TD_IOCTL_2INFO              _IO( 'T', 12)
#define TD_IOCTL_3INFO              _IO( 'T', 13)
#define TD_IOCTL_NAME               _IO('T', 14)
#define TD_IOCTL_DSCNAME               _IO('T', 15)
#define TD_IOCTL_LOG                _IO( 'T', 16)
#define TD_IOCTL_RESET              _IO( 'T', 17)

/* Module usage context: when we enable timedoctor module, timedoctor device is registered, and 
* td_setName() or * td_setDscName() will log to timedoctor memory. But not data log.
* when timedoctor start, ioctl ¡°TD_IOCTL_LOG¡± is called, and loglevel is not 0, memory for data 
* log is allocated.
* when timedoctor stop, ioctl ¡°TD_IOCTL_LOG¡± is called, and loglevel is 0. ¡°tdLogCtl.wrapper 
* and tdLogCtl.memsize¡± are not used..
* when timedoctor start, and previous action is not stopped. This will stop previous action, and 
* change memsize according tdLogCtl.memsize if necessary, and change wrapper setting, then 
* restart. */
#ifndef CONFIG_TIMEDOCTOR
//#define TD_IN_MODULE        /* this is enabled when develop this module in a ko file */
#endif

#ifdef TD_IN_MODULE
typedef void (* timedoctor_info)(unsigned int data);
#endif

/* generic event id definition, to avoid conflicts */
#define GE_ID_DATALOG           (1)  //event to indicate the log of start, stop, wrap
#define GE_ID_IR                (2)  //event to indicate the remote key
#define GE_ID_PAGEFAULT         (3)
#define GE_ID_PVRWRITE_SLOW     (4) //write is too slow for pvr
#define GE_ID_PVRREAD_SLOW      (5) //read is too slow for pvr

#define TD_LOG_STREAM_EVT  //
#ifdef TD_LOG_STREAM_EVT
// 1bit:(hw: 0, playback 1) - 13 bits (pid)
// 00 pcr
// 01 pcr discontinuity
// 10 ts discontinuity
#define GE_ID_PCR               0x0       //check pcr interval
#define GE_PCR_DISCONTI         0x4000
#define GE_TS_DISCONTI          0x8000    //check ts packet continuity

#endif

/* agent id definition */
#define TD_AGENT_ID_FCPREAD     (1)
#define TD_AGENT_ID_FCPWRITE    (2)

#else
/* generic event id definition, to avoid conflicts */
#define GE_ID_DATALOG           (1)  //event to indicate the log of start, stop, wrap
#define GE_ID_IR                (2)  //event to indicate the remote key
#define GE_ID_PAGEFAULT         (3)
#define GE_ID_PVRWRITE_SLOW     (4) //write is too slow for pvr
#define GE_ID_PVRREAD_SLOW      (5) //read is too slow for pvr

// 1bit:(hw: 0, playback 1) - 13 bits (pid)
// 00 pcr
// 01 pcr discontinuity
// 10 ts discontinuity
#define GE_ID_PCR               0x0       //check pcr interval
#define GE_PCR_DISCONTI         0x4000
#define GE_TS_DISCONTI          0x8000    //check ts packet continuity
#define td_setVal(id, value)    do{}while(0)

#define td_genericEvent(id)		do{}while(0)
#endif //CONFIG_TIMEDOCTOR
#endif //_TIMEDOCTOR_H

