#ifndef __DRIVERS_ALI_RPC_HLD_H
#define __DRIVERS_ALI_RPC_HLD_H

#define RPC_HLD_INTERNAL

#include <alidefinition/adf_basic.h>
#include <alidefinition/adf_ret.h>
#include <alidefinition/adf_media.h>
#include <alidefinition/adf_hld_dev.h>

#include <ali_video_common.h>

typedef void (*OSAL_T_LSR_PROC_FUNC_PTR)(UINT32);
typedef void (*OSAL_T_HSR_PROC_FUNC_PTR)(UINT32);

#define LOW_PRI             31    // Min number, but the highest level
#define HIGH_PRI            0     // Max number,but the lowest level
#define DEF_PRI             20    // default level for normal thread
#define HSR_PRI             10    // HSR level, higher than normal
#define DYN_PRI             18    // Dynamic level, only  once.

enum
{
	OSAL_PRI_LOW		= LOW_PRI,			/* Lowest,  for idle task */
	OSAL_PRI_NORMAL		= DEF_PRI,			/* Normal,  for user task */
	OSAL_PRI_HIGH		= 17,				/* High,    for system task */
	OSAL_PRI_CRITICL	= HSR_PRI,			/* Highest, for HSR scheduler */
};

enum ALI_RPC_CB_TYPE
{
	ALI_RPC_CB_VDEC,
	ALI_RPC_CB_VPO,
	ALI_RPC_CB_VPO_HDMI,
	ALI_RPC_CB_SND_HDMI,
	ALI_RPC_CB_SNC_SPC,
	ALI_RPC_CB_IMG,
	ALI_RPC_CB_VDE,
	ALI_RPC_CB_MUS,
};

typedef void (*ali_rpc_cb_routine)(UINT32 type, UINT32 para);

void *hld_dev_get_by_name(INT8 *name);
void *hld_dev_get_by_type(void *sdev, UINT32 type);
void *hld_dev_get_by_id(UINT32 type, UINT16 id);
void ali_rpc_hld_base_callee(UINT8 *msg);
INT32 hld_dev_add_remote(struct hld_device *dev, UINT32 dev_addr);
INT32 hld_dev_remove_remote(struct hld_device *dev);
void hld_dev_memcpy(void *dest, const void *src, unsigned int len);
void hld_dev_see_init(void *addr);

void ali_rpc_register_callback(enum ALI_RPC_CB_TYPE type, void *cb_func);
UINT32 hld_get_see_version(UINT8 *dest);
void hld_disable_see_printf(unsigned long disable);
void hld_hit_see_heart(void);
void hld_enable_see_exception(void);
void hld_show_see_plugin_info(void);
#endif

