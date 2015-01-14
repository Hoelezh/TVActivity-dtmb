/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 Copyright (C)
*
*    File:    hal_gpio.h
*
*    Description:    This file contains all functions about GPIO operations.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Jan.30.2003       Justin Wu       Ver 0.1    Create file.
*	2.	2003.6.26         Liu Lan         Ver 0.2    Exclusive access
*	3.  2005.5.12	      Justin Wu       Ver 0.3    Support M3327/M3327C only.
*	4.  2005.12.9	      Justin Wu       Ver 0.4    Support interrupt setting.
*****************************************************************************/

#ifndef	__HAL_GPIO_H__
#define __HAL_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif


#include <hld_cfg.h>
#include <osal/osal.h>
//#include <adr_sys_config.h>
#include <stdio.h>
#include <asm/unistd.h>
#ifndef ADR_ALIDROID
#include <syscall.h>
#endif
#include <linux/unistd.h>
#include <sys/syscall.h>


#define	SYS_GPIO_GET_VAL	1
#define	SYS_GPIO_SET_VAL	2
#define	SYS_GPIO_DIR_IN	3
#define	SYS_GPIO_DIR_OUT	4

#define 	__NR_gpio 		4330


/* GPIO input/output register in M3327/M3327C, etc:
 * 1 for output enable, 0 for disable.
 */

#define HAL_GPIO_I_DIR		0
#define HAL_GPIO_O_DIR		1

#define HAL_GPIO_INT_EN		0
#define HAL_GPIO_INT_DIS	1
#define HAL_GPIO_EDG_EN		1
#define HAL_GPIO_EDG_DIS	0


#define HAL_GPIO_BIT_GET(pos)				syscall(__NR_gpio, SYS_GPIO_GET_VAL, pos, 0, 0)
#define HAL_GPIO_BIT_DIR_SET(pos, val)		do{if(val) syscall(__NR_gpio, SYS_GPIO_DIR_OUT, pos, 0, 0); \
												else syscall(__NR_gpio, SYS_GPIO_DIR_IN, pos, 0, 0);} while (0)
#define HAL_GPIO_BIT_SET(pos, val)			syscall(__NR_gpio, SYS_GPIO_SET_VAL, pos, val, 0)


#define HAL_GPIO_INT_SET(pos, en)			do{} while (0)
#define HAL_GPIO_INT_REDG_SET(pos, rise)	do{} while (0)
#define HAL_GPIO_INT_FEDG_SET(pos, fall)		do{} while (0)
#define HAL_GPIO_INT_EDG_SET(pos, rise, fall)	do{} while (0)
#define HAL_GPIO_INT_STA_GET(pos)			do{}while(0)
#define HAL_GPIO_INT_CLEAR(pos)			do{}while(0)

#ifdef __cplusplus
}
#endif

#endif	/* __HAL_GPIO_H__ */
