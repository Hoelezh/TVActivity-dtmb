/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 Copyright (C)
*
*    File:    rfm_dev.h
*    
*    Description:    This file contains all functions definition 
*		             of RF modulator driver.
*    History: 
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Aug.14.2003      Justin Wu       Ver 0.1    Create file.
*****************************************************************************/

#ifndef __ADR_HLD_RFM_H__
#define __ADR_HLD_RFM_H__

#include <hld/rfm/adr_rfm_dev.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RFM_SYSTEM_L			0
#define RFM_SYSTEM_NTSC_M		1
#define RFM_SYSTEM_PAL_BG		2
#define RFM_SYSTEM_PAL_I		3
#define RFM_SYSTEM_PAL_DK		4
#define RFM_SYSTEM_PAL_L		5

INT32 rfm_open(struct rfm_device *dev);
INT32 rfm_close(struct rfm_device *dev);
INT32 rfm_io_control(struct rfm_device *dev, INT32 cmd, UINT32 param);
INT32 rfm_system_set(struct rfm_device *dev, UINT32 system);
INT32 rfm_channel_set(struct rfm_device *dev, UINT16 channel);

#ifdef __cplusplus
}
#endif
#endif /* __HLD_RFM_H__ */
