#ifndef __ALI_AVSYNC_H__
#define __ALI_AVSYNC_H__

#include <linux/types.h>
#include <ali_magic.h>

#include "ali_basic_common.h"
#include "alidefinition/adf_avsync.h"

#define ALI_AVSYNC_RESET 							_IO(ALI_AVSYNC_MAGIC, 10)
#define ALI_AVSYNC_START  							_IO(ALI_AVSYNC_MAGIC, 11)
#define ALI_AVSYNC_STOP    							_IO(ALI_AVSYNC_MAGIC, 12)
#define ALI_AVSYNC_SET_SYNC_MODE  					_IOW(ALI_AVSYNC_MAGIC, 13, unsigned long)
#define ALI_AVSYNC_GET_SYNC_MODE   					_IOR(ALI_AVSYNC_MAGIC, 14, unsigned long)
#define ALI_AVSYNC_SET_SOURCE_TYPE					_IOW(ALI_AVSYNC_MAGIC, 15, unsigned long)
#define ALI_AVSYNC_GET_SOURCE_TYPE					_IOR(ALI_AVSYNC_MAGIC, 16, AVSYNC_SRCTYPE_E)
#define ALI_AVSYNC_CONFIG_PARAMS					_IOW(ALI_AVSYNC_MAGIC, 17, avsync_cfg_param_t)
#define ALI_AVSYNC_GET_PARAMS						_IOR(ALI_AVSYNC_MAGIC, 18, avsync_cfg_param_t)
#define ALI_AVSYNC_CONFIG_ADVANCE_PARAMS			_IOW(ALI_AVSYNC_MAGIC, 19, avsync_adv_param_t)
#define ALI_AVSYNC_GET_ADVANCE_PARAMS				_IOR(ALI_AVSYNC_MAGIC, 20, avsync_adv_param_t)
#define ALI_AVSYNC_GET_STATUS						_IOR(ALI_AVSYNC_MAGIC, 21, avsync_status_t)
#define ALI_AVSYNC_GET_STATISTICS					_IOR(ALI_AVSYNC_MAGIC, 22, avsync_statistics_t)
#define ALI_AVSYNC_VIDEO_SMOOTHLY_PLAY_ONOFF	_IOW(ALI_AVSYNC_MAGIC, 23, struct ali_avsync_rpc_pars)
#define ALI_AVSYNC_GET_STC							_IOR(ALI_AVSYNC_MAGIC, 24, struct ali_avsync_rpc_pars)
#define ALI_AVSYNC_GET_CONTROL_BLOCK_OTHERS	 	_IOR(ALI_AVSYNC_MAGIC, 25, struct ali_avsync_rpc_pars)

#if 0
#define ALI_AVSYNC_IO_ENABLE_DDP_CERTIFICATION		128
#define ALI_AVSYNC_IO_GET_VIDEO_SMOOTHLY_PLAY_CFG 		129
#define ALI_AVSYNC_IO_ENABLE_GET_STC 		130
#define ALI_AVSYNC_IO_SET_PTS_UNIT_HZ   131
#define ALI_AVSYNC_IO_UNREG_CALLBACK   132
#define ALI_AVSYNC_IO_REG_CALLBACK   133
#endif

#define ALI_AVSYNC_IO_COMMAND		128

#define ALI_AVSYNC_SET_DBG_PRINT_OPTION		240
#define ALI_AVSYNC_SET_DBG_POLL_ONOFF		241
#define ALI_AVSYNC_SET_DBG_POLL_OPTION		242
#define ALI_AVSYNC_SET_DBG_POLL_INTERVAL		243

struct ali_avsync_rpc_arg
{
	void *arg;
	int arg_size;
	int out;
};

struct ali_avsync_rpc_pars
{
	int API_ID;
	struct ali_avsync_rpc_arg arg[4];
	int arg_num;
};

struct ali_avsync_ioctl_command
{
	unsigned long ioctl_cmd;
	unsigned long param;
};

#endif
