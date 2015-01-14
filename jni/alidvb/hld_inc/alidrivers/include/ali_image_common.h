#ifndef __ALI_IMAGE_COMMON_H
#define __ALI_IMAGE_COMMON_H

#include <linux/types.h>
#include <ali_magic.h>

#include "ali_basic_common.h"
#include "ali_video_common.h"

#include "alidefinition/adf_image.h"


/*
#ifndef BOOL
#define BOOL int
#endif
*/


//commad for decoder: init\release\decode\stop 
#define IMAGEDEC_CMD_INIT       _IOW(ALI_IMAGE_MAGIC, 10, struct image_init_config)
#define IMAGEDEC_CMD_RELEASE    _IO(ALI_IMAGE_MAGIC, 11)
#define IMAGEDEC_CMD_DECODE     _IOW(ALI_IMAGE_MAGIC, 12, struct image_engine_config)
#define IMAGEDEC_CMD_STOP       _IO(ALI_IMAGE_MAGIC, 13)
#define IMAGEDEC_GET_MEM_INFO   _IOR(ALI_IMAGE_MAGIC, 14, struct ali_image_mem_info)
#define IMAGEDEC_CMD_ROTATE     _IOW(ALI_IMAGE_MAGIC, 15, unsigned char)
#define IMAGEDEC_CMD_ZOOM       _IOW(ALI_IMAGE_MAGIC, 16, struct ali_image_pars)
#define IMAGEDEC_CMD_DISPLAY    _IOW(ALI_IMAGE_MAGIC, 17, struct image_display_t)
#define IMAGEDEC_CMD_GET_HWINFO _IOR(ALI_IMAGE_MAGIC, 18, struct image_hw_info)
#define IMAGEDEC_CMD_SET_MADDR  _IOW(ALI_IMAGE_MAGIC, 19, unsigned long)
#define IMAGEDEC_CMD_GET_MAP_INFO  _IOR(ALI_IMAGE_MAGIC, 20, struct ali_image_map_info)
#define IMAGEDEC_CMD_GET_IMG_INFO  _IOWR(ALI_IMAGE_MAGIC, 21, struct ali_image_pars)

#define __MM_FB0_Y_LEN			(1920*1088+1024)//(736*576+512)	//for high definition jpg decode
#define __MM_FB1_Y_LEN			__MM_FB0_Y_LEN
#define __MM_FB2_Y_LEN			__MM_FB0_Y_LEN

#define __MM_FB0_C_LEN			(__MM_FB0_Y_LEN/2)
#define __MM_FB1_C_LEN			__MM_FB0_C_LEN
#define __MM_FB2_C_LEN			__MM_FB0_C_LEN

#define __MM_FB3_Y_LEN			(736*576+1024)
#define __MM_FB3_C_LEN			(__MM_FB3_Y_LEN/2)
#define __MM_FB4_Y_LEN			__MM_FB3_Y_LEN
#define __MM_FB4_C_LEN			__MM_FB3_C_LEN
#define __MM_FB5_Y_LEN          		__MM_FB3_Y_LEN
#define __MM_FB5_C_LEN          		__MM_FB3_C_LEN
#define __MM_FB6_Y_LEN         		__MM_FB3_Y_LEN
#define __MM_FB6_C_LEN          		__MM_FB3_C_LEN

#define __MM_FB_LEN			    		0x19c6200

#define MAX_IMG_ARG_NUM		4

#define MAX_IMG_ARG_SIZE		512

struct ali_image_arg
{
	void *arg;
	int arg_size;
	int out;
};

struct ali_image_pars
{
	int type;
	int API_ID;
	struct ali_image_arg arg[MAX_IMG_ARG_NUM];
	int arg_num;
};

struct ali_image_mem_info
{
	void *mem_start;
	unsigned long mem_size;
    void *priv_mem_start;
    unsigned long priv_mem_size;
};

struct ali_image_map_info
{
	void *mem_start;
	unsigned long mem_size;
};

#endif

