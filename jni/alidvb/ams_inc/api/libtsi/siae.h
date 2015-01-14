/*
 * Copyright (C) ALi Shanghai Corp. 2004
 *
 * file name	: siae.h
 * 
 * description	: A simple Service Information async-engine
 * 
 * History:
 *  1. 20041206		0.1	Zhengdao	Create from scratch.
 *  2. 20041211		0.2	Zhengdao	Update to support multi PID.
 *  3. 20041220		0.3	Zhengdao	slot number changes.
 *  4. 20050902		0.31	Zhengdao	code downsize.
 */
#ifndef _SI_AE_H
#define _SI_AE_H

#include <adr_sys_config.h>
#include <osal/osal.h>
#include <hld/adr_hld_dev.h>
#include <hld/dmx/adr_dmx.h>
#include <hld/dmx/adr_dmx_dev.h>

#define SIAE_SLOT_NUMBER	(MAX_FILTER_NUMBER-1)
#define SIAE_SLOT_FULL		0x5F

#if (SYS_SDRAM_SIZE>2) && (!defined(PSI_EPG_SUPPORT))
#define PSI_EPG_SUPPORT
#endif

#define SR_TIMEOUT_UNLIMIT	OSAL_WAIT_FOREVER_TIME

enum {
	SIAE_STAT_IDLE			= 0x00,
	SIAE_STAT_ABORT			= 0x01,
	SIAE_STAT_BUSY			= 0x02,
	SIAE_STAT_READY			= 0x03,
	SIAE_STAT_QUEUED		= 0x04,
	SIAE_STAT_TIMEOUT		= 0x05,
};

/*
 * name		: sr_handler_t <typedef>
 * description	: si request completion/timeout handler
 * parameter	: 2
 *	IN	UINT32 slot	: the slot id.
 *	IN	UINT8 *content	: buffer address. NULL for timeout.
 * return value : void.
 */
struct si_request;

typedef void (*sr_handler_t)(struct si_request *sr, UINT8 *content);

struct si_request{
	struct get_section_param sr_request;
	struct restrict sr_restrict;
	sr_handler_t sr_handler;
	UINT32 sr_timeout;
	UINT8 sr_status;
	UINT8 sr_confined;
	UINT8 sr_filter;
	void *sr_priv;
};


#ifdef __cplusplus
extern "C"{
#endif

INT32 siae_init();

#if (SYS_SDRAM_SIZE>2)
INT32 siae_release();
#endif

/* 
 * name		: siae_open
 * description	: opening a SI async-engine.
 * parameter	: 4
 *	IN	struct dmx_device *dev: the device handle.
 *	IN	UINT8 *buf: the buffer for siae engine internal use.
 *	IN	INT32 buflen: buffer length for siae internal.
 *	IN	UINT8 priority: the task priority level, OSAL_PRI_NORMAL is recommended.
 * return value	: INT32
 *	>0	: the SI async-engine ID.
 *	<0	: the device could not attach any async-engine now.
 */
INT32 siae_open(struct dmx_device *dev, UINT8 *buf, INT32 buflen, UINT8 priority);

/*
 * name		: siae_close
 * description	: close a SI async-engine.
 * parameter	: 1
 *	IN	INT32 siae_id: the engine ID.
 * return value	: INT32
 *	0	: the engine is closed.
 *	other	: failure in somewhere.
 */
void siae_close(INT32 siae_id);

/*
 * name		: siae_request
 * description	: raise a SI request.
 * parameter	: 2
 *	IN	INT32 siae_id: the enigine ID.
 *	IN	struct si_request *sr: the SI request.
 * return value	: INT32
 *	[0~SIAE_SLOT_NUMBER): the assigned slot number.
 *	SIAE_SLOT_NUMBER    : the slot is full.
 *	<0		    : incorrect engine status.	
 */
INT32 siae_request(INT32 siae_id, struct si_request *sr);

#if (SYS_SDRAM_SIZE>2)
/*
 * name		: siae_adjust
 * description	: adjust the on-going request's table_id, table_mask, and mask_len.
 * parameter	: INT32
 *	IN	siae_id:	the engine ID;
 *	IN	slot:		the request slot number;
 *	IN	table_id:	the new table_id;
 *	IN	table_mask:	the new table_mask.
 *	IN	mask_len:	the new mast length.
 */
INT32 siae_adjust(INT32 siae_id, INT32 slot, UINT8 table_id, UINT8 table_mask, INT32 mask_len);
#endif
/*
 * name		: siae_abort
 * description	: abort the SI engine.
 * parameter	: 2
 *	IN	INT32 siae_id
 *	IN	UINT32 mask
 * comment	: this function is blocked until the bitsfield are cleared.
 */
void siae_abort(INT32 siae_id, UINT16 pid, struct restrict *sr_restrict);
#ifdef _MHEG5_ENABLE_
void siae_abort_slot(INT32 siae_id, void* queryRef, BOOL notify);
#endif
#ifdef PSI_EPG_SUPPORT
INT32 siae_acquire_id();
#endif

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _SI_AE_H */

