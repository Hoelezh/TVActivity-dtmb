#ifndef __ADF_GMA__
#define __ADF_GMA__

#include "adf_basic.h"

#define MAX_GMA_NUM				2
#define MAX_GMA_REGION_NUM		2
#define MAX_GMA_REGION_WIDTH		4095
#define MAX_GMA_REGION_HEIGHT	4095

enum GMA_FORMAT
{
    GMA_FORMAT_RGB888 = 0x00,
    GMA_FORMAT_ARGB8888 = 0x01,
    GMA_FORMAT_RGB444 = 0x02,
    GMA_FORMAT_ARGB4444 = 0x03,
    GMA_FORMAT_RGB555 = 0x04,
    GMA_FORMAT_ARGB1555 = 0x05,
    GMA_FORMAT_RGB565 = 0x06,
    GMA_FORMAT_RESERVED0 = 0x07,
    GMA_FORMAT_CLUT2 = 0x08,
    GMA_FORMAT_RESERVED1 = 0x09,
    GMA_FORMAT_CLUT4 = 0x0A,
    GMA_FORMAT_ACLUT44 = 0x0B,
    GMA_FORMAT_CLUT8 = 0x0C,
    GMA_FORMAT_RESERVED2 = 0x0D,
    GMA_FORMAT_ACLUT88 = 0x0E,
    GMA_FORMAT_RESERVED3 = 0x0F,

    GMA_FORMAT_YCbCr444 = 0x10,
    GMA_FORMAT_YCbCr422 = 0x11,
    GMA_FORMAT_YCbCr420 = 0x12,
    GMA_FORMAT_AYCbCr8888 = 0x13,

    GMA_FORMAT_MASK_A1 = 0x1C,    // Only for 1bpp MASK
    GMA_FORMAT_MASK_A8 = 0x1D,    // Only for 8bpp MAS
    
    GMA_FORMAT_MAX_VALUE
};


enum GMA_SCALE_TYPE
{
	GMA_SCALE_DUPLICATE,
	GMA_SCALE_FILTER,
};

enum GMA_PLT_TYPE
{
	GMA_PLT_RGB, //  0~7 : B; 8 ~ 15 : G; 16 ~ 23 : R; 24 ~ 31 : Alpha
	GMA_PLT_YUV, // 0~7 : V; 8 ~ 15 : Y 16 ~ 23 : U; ; 24 ~ 31 : Alpha
};

enum GMA_PLT_ALPHA_LEVEL
{
	GMA_PLT_ALPHA_16,
	GMA_PLT_ALPHA_128,
	GMA_PLT_ALPHA_256,
};

typedef struct gma_rect
{
	int x;
	int y;
	int w;
	int h;
}GMA_RECT;

typedef struct gma_size
{
	int w;
	int h;
}GMA_SIZE;

typedef struct layer_pars
{
	/* format of this layer */
	enum GMA_FORMAT format;
	
	/* maximum resolution of this layer */
	GMA_SIZE max_size;

	/* global alpha parameters */
	INT8 global_alpha_enable;
	INT8 global_alpha_value;	
}GMA_LAYER_PARS;

typedef struct region_pars
{
	/* rect definition of this region */
	struct gma_rect rect;

	/* start address of the display memory */ 
	UINT32 dmem_start;
	UINT32 dmem_len;
	
	/* length of one line */
	UINT32 line_length;

	/* global alpha parameters */
	INT8 global_alpha_enable;
	INT8 global_alpha_value;
}GMA_REGION_PARS;

typedef struct scale_pars
{
	enum GMA_SCALE_TYPE scale_type;
		
	/* scale parameters */
	int h_dst;
	int h_src;
	
	int v_dst;
	int v_src;	
}GMA_SCALE_PARS;

typedef struct pallette_pars
{
	enum GMA_PLT_TYPE type;
	enum GMA_PLT_ALPHA_LEVEL alpha_level;

	UINT32 pallette_buf;
	int color_num;	
}GMA_PAL_PARS;

#define GMA_ENHANCE_BRIGHTNESS		0x01
#define GMA_ENHANCE_CONTRAST			0x02
#define GMA_ENHANCE_SATURATION		0x04
#define GMA_ENHANCE_SHARPNESS		0x08
#define GMA_ENHANCE_HUE				0x10

typedef struct gma_enhance_pars
{
	UINT8 enhance_flag;
	UINT16 enhance_grade;
}GMA_ENH_PARS;

enum gma_blending_layer
{
	GMA_BLENDING_LAYER1,
	GMA_BLENDING_LAYER2,
};

struct gma_blending_order_pars
{
	// from top to bottom
		
};

typedef struct gma_dmem_pars_t
{
	UINT32 dmem_start[MAX_GMA_NUM];
	UINT32 dmem_size[MAX_GMA_NUM];
}GMA_DMEM_PARS;

#define GMA_DBG_FLAG_ERR					(0x00000001)
#define GMA_DBG_FLAG_DEFAULT				(0x00000002)


/* io command */
#define GMA_IO_SET_GLOBAL_ALPHA				0x00000001
#define GMA_IO_SET_ENHANCE_PAR				0x00000002
#define GMA_IO_SET_BLENDING_ORDER			0x00000003
#define GMA_IO_SET_REGION_BY				       0x00000004
#define GMA_IO_SET_DMEM_PAR					0x00000005

#define GMA_IO_SET_DBG_FLAG					0x00010001

struct gma_device
{
	struct gma_device  *next;  /*next device */
    	UINT32 type;
	INT8 name[32];
	UINT8  flags;

	void *private; /* private information */

	/* layer operation */
	RET_CODE (*open)(struct gma_device *dev, struct layer_pars *pars);
	void (*close)(struct gma_device *dev);
	RET_CODE (*io_control)(struct gma_device *dev, UINT32 cmd, UINT32 arg);
	RET_CODE (*show)(struct gma_device *dev, int on);
	RET_CODE (*scale)(struct gma_device *dev, struct scale_pars *pars);
	RET_CODE (*set_pallette)(struct gma_device *dev, struct pallette_pars *pars);
	RET_CODE (*get_pallette)(struct gma_device *dev, struct pallette_pars *pars);
	
	/* region operation */
	RET_CODE (*create_region)(struct gma_device *dev, int reg_id, struct region_pars *pars);
	void (*delete_region)(struct gma_device *dev, int reg_id);
	RET_CODE (*get_region_info)(struct gma_device *dev, int reg_id, struct region_pars *pars);
	RET_CODE (*set_region_info)(struct gma_device *dev, int reg_id, struct region_pars *pars);
	RET_CODE (*region_show)(struct gma_device *dev, int reg_id, int on);
};

RET_CODE gma_open(struct gma_device *dev, struct layer_pars *pars);
void gma_close(struct gma_device *dev);
RET_CODE gma_io_control(struct gma_device *dev, UINT32 cmd, UINT32 arg);
RET_CODE gma_show(struct gma_device *dev, int on);
RET_CODE gma_scale(struct gma_device *dev, struct scale_pars *pars);
RET_CODE gma_set_pallette(struct gma_device *dev, struct pallette_pars *pars);
RET_CODE gma_get_pallette(struct gma_device *dev, struct pallette_pars *pars);
RET_CODE gma_create_region(struct gma_device *dev, int reg_id, struct region_pars *pars);
void gma_delete_region(struct gma_device *dev, int reg_id);
RET_CODE gma_get_region_info(struct gma_device *dev, int reg_id, struct region_pars *pars);
RET_CODE gma_set_region_info(struct gma_device *dev, int reg_id, struct region_pars *pars);
RET_CODE gma_region_show(struct gma_device *dev, int reg_id, int on);

int gma_attach_m36f(int layer_num);
#endif

