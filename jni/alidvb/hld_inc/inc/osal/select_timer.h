#ifndef THREAD_TIMER_H
#define THREAD_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>
//typedef Int32 int;
//typedef UInt32 unsigned int;
//typedef  int (*TimerCallback)(void *param);
typedef void                (*TimerCallback)(unsigned long);
#define BOOL int

/*
int timer_init(void);
void timer_exit(void);
int  add_timer(int timer_id, int interval, TimerCallback callback, void *param);
int remove_timer(int timer_id);
*/
typedef struct timer {
	int  running; /*Timer state*/
	unsigned long interval;
	unsigned long atr;
	
	unsigned int starttime; /*Timer start time*/
	TimerCallback cb; /*Timer callback function*/
	unsigned long param;  /*callback function param*/
	pthread_t timer_id;
	unsigned short type;
	int status; // 0 : running 1 : callback 2 : to be stopped

	unsigned long left_time;
}Timer;
#define TIMER_ID_COUNT 64

//int SetTimer(int tmr_id, unsigned int interval);
//int ActTimer(int timer_id, BOOL bVal);
int StartTimer(unsigned short timer_id, Timer *tmr_cb);
int StartTimerAlarm(unsigned short timer_id, Timer *tmr_cb);
int StopTimer(Timer *tmc_cb);
void delay_time(unsigned short us);
#ifdef __cplusplus
}
#endif

#endif
