#ifndef __DRIVERS_ALI_RPC_IMAGE_H

#define __DRIVERS_ALI_RPC_IMAGE_H

#include "ali_rpc_hld.h"
#include <ali_image_common.h>

enum LIB_IMAGE_ENGINE_FUNC{
	FUNC_IMAGE_INIT = 0,
	FUNC_IMAGE_RELEASE,
	FUNC_IMAGE_STOP,
	FUNC_IMAGE_DECODE,
	FUNC_IMAGE_ROTATE,
	FUNC_IMAGE_DISPLAY,
	FUNC_IMAGE_ZOOM,
	FUNC_IMAGE_GET_HWADDR,
	FUNC_IMAGE_GET_INFO,
};

int image_init(struct image_init_config *cfg);
int image_release(void);
int image_stop(void);
int image_decode(int sw_hw, struct image_engine_config *cfg);
int image_rotate(unsigned char rotate_angle);
int image_zoom(struct Rect *dstRect, struct Rect *srcRect);
int image_display(int sw_hw, struct image_display_t *cfg);
int image_get_hw_addr(int flag_nused, struct image_hw_info *hw_info);
int image_get_info(int format, struct image_info *info);
//int ali_rpc_image_decode(struct image_engine_config cfg);

#endif

