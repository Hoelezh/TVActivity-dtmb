#ifndef __DRIVERS_ALI_RPC_VIDENC_H

#define __DRIVERS_ALI_RPC_VIDENC_H

#include <linux/ali_venc.h>
#include "ali_rpc_hld.h"

enum LIB_VIDEO_ENCODER_FUNC{
	FUNC_VENC_INIT = 0,
	FUNC_VENC_RELEASE,
	FUNC_VENC_STOP,
	FUNC_VENC_ENCODE,
};

int venc_remote_init(void);
int venc_remote_start(struct videnc_see_config *cfg);
int venc_remote_release(void);
int venc_remote_stop(void);
int venc_remote_encode(struct videnc_trigger_para *cfg);


#endif

