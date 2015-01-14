#ifndef	__OSAL_SYSDBG_H__
#define	__OSAL_SYSDBG_H__

#ifdef __cplusplus
extern "C" {
#endif


#define TSK_EXTRA_DURA				(0x1<<0)	/*Task running time*/
#define TSK_EXTRA_STACK			(0x1<<1)	/*Task stack start, end and pointer*/
#define TSK_EXTRA_PC				(0x1<<2)	/*Task current PC address*/
#define TSK_EXTRA_STATE			(0x1<<3)	/*Task status*/
#define TSK_EXTRA_ALCMEM			(0x1<<4)

#define MSG_EXTRA_WRCV			(0x1<<0)	/*List all tasks wait for receive message*/
#define MSG_EXTRA_WSND			(0x1<<1)	/*List all tasks wait for send message*/

typedef	void(* SYSDBG_PRINT_CB)(const char *fmt, ...);

void sysdbg_output_set(SYSDBG_PRINT_CB cb);
void sysdbg_display_interval_set(unsigned long interval);
void sysdbg_task_info_enable(unsigned char enable, unsigned long tsk_extra_info);
void sysdbg_interrupt_info_enable(unsigned char enable,  unsigned long int_extra_info);
void sysdbg_heap_info(unsigned char cyclic, unsigned long heap_extra_info);
void sysdbg_msg_info(unsigned char cyclic, unsigned long msg_extra_info);
void sysdbg_semaphore_info(unsigned char cyclic, unsigned long sema_extra_info);
void sysdbg_flag_info(unsigned char cyclic, unsigned long flag_extra_info);
#ifdef __cplusplus
}
#endif

#endif	/*__OSAL_SYSDBG_H__*/

