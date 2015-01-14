/****************************************************************************
 *
 *  ALi (Zhuhai) Corporation, All Rights Reserved. 2011 Copyright (C)
 *
 *  File: ali_pm.h
 *
 *  Description: This file contains all globe micros and functions declare
 *		             of power management ioctl commands.
 *
 *  History:
 *      Date            Author            Version   Comment
 *      ====        ======      =======  =======
 *     
 ****************************************************************************/

#ifndef _ALI_POWER_MANAGEMENT_COMMON__H_
#define _ALI_POWER_MANAGEMENT_COMMON__H_

/*
 * Accept the key
 */
typedef struct pm_key {
    unsigned char standby_key;
    unsigned long ir_power;
}pm_key_t;

/*
 * Accept the param
 */
typedef struct pm_param {
    unsigned int board_power_gpio;
    unsigned long timeout;
	unsigned long reboot;
}pm_param_t;

/* Encode I/O command */
#define PM_CMD_SET_RESUME_KEY     _IOW('o', 501, pm_key_t)      /* set the resume key */
#define PM_CMD_SET_STANDBY_PARAM  _IOW('o', 502, pm_param_t)      /* set the standby parameter */

/* To debug the suspend status */
// #define PM_SUSPEND_STATUS_DEBUG

typedef enum __PM_STATE{
    PM_TASK_FREEZE,
    PM_DEVICE_SUSPEND,
    PM_IRQ_DISABLE,
    PM_ENTER_CACHE,
    PM_LEAVE_CACHE,
    PM_IRQ_ENABLE,
    PM_DEVICE_RESUME,
    PM_TASK_THAW
}e_pm_state;

#endif
