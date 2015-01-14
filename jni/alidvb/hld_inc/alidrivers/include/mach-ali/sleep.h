/****************************************************************************(I)(S)
 *  (C)
 *  ALi (Shanghai) Corporation. 2010 Copyright (C)
 *  (C)
 *  File: m36_irq.h
 *  (I)
 *  Description:
 *  (S)
 *  History:(M)
 *      	Date        			Author         	Comment
 *      	====        			======		=======
 * 0.		2010.06.03			Sam			Create
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version
* 2 of the License, or (at your option) any later version.
*

 ****************************************************************************/
#ifndef __ALI_M36_SUSPEND_SLEEP____INCLUDE__
#define __ALI_M36_SUSPEND_SLEEP____INCLUDE__

/*
 * We should use soft link to replace the directory
 * if we want to config different board easily
 */
#include "sleepdep.h"

extern asmlinkage unsigned long  cache_code(unsigned char standby_key, \
                          unsigned long ir_power, \
                          unsigned long time, \
                          unsigned long timeout);

#endif
