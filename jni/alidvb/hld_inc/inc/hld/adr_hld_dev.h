/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 Copyright (C)
*
*    File:    hld_dev.h
*
*    Description:    This file contains all functions definations of
*		             HLD device management.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Jan.26.2003      Justin Wu      Ver 0.1    Create file.
*	2.
*****************************************************************************/

#ifndef	__ADR_HLD_DEV_H__
#define __ADR_HLD_DEV_H__

#include <adr_basic_types.h>

#include <alidefinition/adf_hld_dev.h>

/* QJ: define MAP ADDRESS LIST HERE.
For some hw module, we need map the registers to user space with a fixed address value */
#define MAP_GE_BASE_ADDRESS_START	0x60000000  //corresponding to 0xB800A000(GE BASE ADDRESS)
#define MAP_GE_BASE_ADDRESS MAP_GE_BASE_ADDRESS_START+0x0000A000

#endif	/* __ADR_HLD_DEV_H__ */
