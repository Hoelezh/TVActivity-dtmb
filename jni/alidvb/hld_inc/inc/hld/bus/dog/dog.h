/****************************************************************************
 *
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2006 Copyright (C)
 *
 *  File: dog.h
 *
 *  Description: This file provide common watchdog interface.
 *
 *  History:
 *      Date        Author      Version  Comment
 *      ====        ======      =======  =======
 *  1.  2006.6.13   Justin Wu   0.1.000  Initial
 ****************************************************************************/

#ifndef	__LLD_DOG_H__
#define __LLD_DOG_H__

#ifdef __cplusplus
extern "C" {
#endif

//#include <adr_sys_config.h>


void api_watchdog_reboot(void);
#define dog_mode_set(id, mode, duration, callback)	api_dog_set_timeout(id, duration)
#define dog_set_time(id, us)						api_dog_keep_live(id)

#define dog_set_timeout(id, timeout_us)			    api_dog_set_timeout(id,timeout_us)
#define dog_get_time(id)							api_dog_get_time(id)
#define dog_keep_live(id)							api_dog_keep_live(id)
#define dog_pause(id, en)							api_dog_pause(id, en)
#define dog_stop(id)								api_dog_stop(id)
#define dog_start(id)								api_dog_start(id)

#ifdef __cplusplus
}
#endif

#endif	/* __LLD_DOG_H__ */
