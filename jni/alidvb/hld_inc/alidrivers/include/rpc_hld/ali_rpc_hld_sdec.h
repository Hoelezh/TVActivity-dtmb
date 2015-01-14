#ifndef __DRIVERS_ALI_RPC_HLD_SDEC_H
#define __DRIVERS_ALI_RPC_HLD_SDEC_H

#include "ali_rpc_hld.h"


#define SDEC_CALL						0x00010000

#define CALL_SDEC_START				(SDEC_CALL+1)
#define CALL_SDEC_STOP					(SDEC_CALL+2)
#define CALL_SDEC_PAUSE				(SDEC_CALL+3)
#define CALL_LIB_SUBT_ATTACH			(SDEC_CALL+4)
#define CALL_OSD_SUBT_ENTER			(SDEC_CALL+5)
#define CALL_OSD_SUBT_LEAVE			(SDEC_CALL+6)

#define CALL_LIB_ISDBT_CC_INIT		(SDEC_CALL + 7)
#define CALL_OSD_ISDBT_CC_ENTER		(SDEC_CALL + 8)
#define CALL_OSD_ISDBT_CC_LEASE		(SDEC_CALL + 9)
#define CALL_LIB_ISDBT_CC_ATTACH	(SDEC_CALL + 10)

#define CALL_ISDBT_CC_DEC_ATTACH	(SDEC_CALL + 11)
#define CALL_ISDBT_CC_DISPLAY_INIT	(SDEC_CALL + 12)
#define CALL_ISDBT_CC_GET_CUR_LANG_BY_PID (SDEC_CALL + 13)

#define CALL_SUBT_ATSC_SET_BUF			(SDEC_CALL + 14)
#define CALL_SUBT_ATSC_STREAM_IDENTIFY	(SDEC_CALL + 15)
#define CALL_SUBT_ATSC_CREATE_TASK		(SDEC_CALL + 16)
#define CALL_SUBT_ATSC_TERMINATE_TASK	(SDEC_CALL + 17)
#define CALL_SUBT_ATSC_CLEAN_UP			(SDEC_CALL + 18)
#define CALL_SUBT_ATSC_DEL_TIMER		(SDEC_CALL + 19)
#define CALL_SUBT_ATSC_SHOW_ONOFF		(SDEC_CALL + 20)

struct OSDRect
{
	INT16	uLeft;
	INT16	uTop;
	INT16	uWidth;
	INT16	uHeight;
};

struct sdec_display_config
{
	UINT8 dds_version_number;
	UINT8 display_window_flag;
	UINT16 display_width;
	UINT16 display_height;
	UINT16 display_window_hor_min;
	UINT16 display_window_hor_max;
	UINT16 display_window_ver_min;
	UINT16 display_window_ver_max;
};

struct sdec_feature_config
{
	UINT8 * temp_buf;/*buffer for temp info storage, user can alloc 
					memory for this buffer or assign 0 to this buffer
					address and sdec driver will alloc memory for it.*/
	UINT32 temp_buf_len;//recommended value is 0x2000 in byte unit
	UINT8 * bs_buf;/*bitstream buffer for subtitle data, user can alloc 
					memory for this buffer or assign 0 to this buffer
					address and sdec driver will alloc memory for it.*/
	UINT32 bs_buf_len;//recommended value is 0X5000 in byte unit
	UINT32 bs_hdr_buf;//MUST be 0
	UINT32 bs_hdr_buf_len;//MUST be100
	UINT8 * pixel_buf;/*pixel buffer for display, user can alloc 
					memory for this buffer or assign 0 to this buffer
					address and sdec driver will alloc memory for it.*/
	UINT32 pixel_buf_len;//recommended value is 0X19000 in byte unit
	UINT8 tsk_qtm;//task quantum for sdec decoder, recommended value is 10
	UINT8 tsk_pri;//task priority for sdec decoder, recommended value is OSAL_PRI_NORMAL
	UINT8 transparent_color;//depends on solution requirements.
	UINT8 support_hw_decode;// 1,support;0,no
	UINT8 *sdec_hw_buf;
	UINT16 sdec_hw_buf_len;
	void (*subt_draw_pixelmap)(struct OSDRect, UINT8 *);
	INT32 (*subt_draw_pixel)(UINT8, UINT16, UINT16, UINT8);
	BOOL (*region_is_created)(UINT8);
	INT32 (*subt_create_region)(UINT8, struct OSDRect *);
	INT32 (*subt_region_show)(UINT8, UINT8);
	INT32 (*subt_delete_region)(UINT8);
	INT32 (*subt_get_region_addr)(UINT8 ,UINT16 , UINT32 *);
	void (*draw_obj_hardware)(UINT8 *, UINT16, UINT8, UINT8,UINT16, UINT8, UINT16, UINT16);
	INT32 (*subt_display_define)(struct sdec_display_config *);
};


//vicky20110322  buffer address for section data receiver, send to lib_subt_atsc_stream_identify() as 2nd para (Dual CPU Case)
struct atsc_subt_config_par
{
   UINT8 *bs_buf_addr;
   UINT16 bs_buf_len;
   UINT8 *sec_buf_addr;
   UINT16 sec_buf_len;
   UINT8 Outline_thickness_from_stream;
   UINT8 DropShadow_right_from_stream;   
   UINT8 DropShadow_bottom_from_stream;      
   UINT8 Outline_thickness;
   UINT8 DropShadow_right;
   UINT8 DropShadow_bottom;   
};

struct sdec_device
{
	struct sdec_device  *next;  /*next device */
       INT32  type;
	INT8  name[32];
	INT32  flags;

	INT32 busy;
	
	void *priv;		/* Used to be 'private' but that upsets C++ */
	
	INT32 (*init) (void);
	INT32 (*open) (struct sdec_device *);
	INT32 (*close) (struct sdec_device *);
	INT32 (*start) (struct sdec_device *,UINT16,UINT16);
	INT32 (*stop) (struct sdec_device *);
	INT32 (*pause) (struct sdec_device *);
	INT32 (*showonoff) (struct sdec_device *,BOOL );
	INT32 (*ioctl)(struct sdec_device *, UINT32 , UINT32);
	INT32 (*request_write)(struct sdec_device *, UINT32 ,struct control_block*, UINT8**, UINT32*);
	void (*update_write)(struct sdec_device *, UINT32);
		
};


struct subt_config_par
{
   UINT8 cc_by_vbi;
   UINT8 cc_by_osd;
   UINT8 osd_blocklink_enable;
   UINT8 *g_ps_buf_addr;
   UINT32 g_ps_buf_len;
   UINT8 sys_sdram_size;//2:2M,8:8M.....
   UINT16 max_subt_height;
   UINT8 speed_up_subt_enable;
   UINT8 osd_layer_id;
   UINT8 hd_subtitle_support;
   UINT16 subt_width;
   UINT16 subt_height;
   UINT16 subt_hor_offset;
   UINT16 subt_ver_offset;

   void (*osd_subt_enter)(void);
   void (*osd_subt_leave)(void);
//#if 0   
#ifndef  SUBT_FUNC_POINTER_ENABLE
   void (*osd_subt_set_clut)(UINT8 entry_id,UINT8 y,UINT8 cb,UINT8 cr,UINT8 t);
   void (*osd_subt_clear_page)(void);
   INT32 (*osd_subt_create_region)(UINT8 region_idx,struct OSDRect *rect);
   INT32 (*osd_subt_delete_region)(UINT8 region_idx);
   INT32 (*osd_subt_region_show)(UINT8 region_idx,UINT8 on);
   INT32 (*osd_subt_draw_pixel)(UINT8 region_idx,UINT16 x,UINT16 y,UINT8 data);
   BOOL (*osd_region_is_created)(UINT8 region_idx);
   void (*osd_subt_draw_pixelmap)(struct OSDRect rect, UINT8* data);
   INT32 (*osd_subt_get_region_addr)(UINT8 region_idx,UINT16 y, UINT32 *addr);
   void (*osd_subt_update_clut)(void);
   INT32 (*osd_subt_display_define)(struct sdec_display_config *cfg);
#endif
   UINT32     (*osd_get_scale_para)(enum TVSystem tvsys,INT32 scr_width);
};


INT32 sdec_open(struct sdec_device *dev);
INT32 sdec_close(struct sdec_device *dev);
INT32  sdec_start(struct sdec_device *dev,UINT16 composition_page_id,UINT16 ancillary_page_id);
INT32  sdec_stop(struct sdec_device *dev);
INT32  sdec_pause(struct sdec_device *dev);
INT32 sdec_ioctl(struct sdec_device *dev, UINT32 cmd, UINT32 param);
INT32 sdec_request_write(void * pdev, UINT32 uSizeRequested,void ** ppuData,UINT32* puSizeGot,struct control_block* pSDataCtrlBlk);
void sdec_update_write(void *dev,UINT32 uDataSize);
void draw_object_hardware(UINT8 * data, UINT16 len, UINT8 CLUT_id, UINT8 region_idx,UINT16 stride, UINT8 field_polar, UINT16 x, UINT16 y);


INT32 sdec_m33_attach(struct sdec_feature_config * cfg_param);
void subt_disply_bl_init(struct sdec_device *dev);

void lib_subt_attach(struct subt_config_par *psubt_config_par);
void osd_subt_enter(void);
void osd_subt_leave(void);

#define ISDBTCC_WIDTH	640//640//608//608//720
#define ISDBTCC_HEIGHT 520//520//480//416//576
#define ISDBTCC_HOR_OFFSET ((720-SUBT_WIDTH)/2)
#define ISDBTCC_VER_OFFSET ((576-SUBT_HEIGHT)/2)

#define ISDBTCC_TRANSPARENT_COLOR	0xFF//OSD_TRANSPARENT_COLOR//0//0xff

struct isdbtcc_config_par
{
	UINT8 *g_buf_addr;
	UINT32 g_buf_len;
	
	UINT16 max_isdbtcc_height;
	UINT8 isdbtcc_osd_layer_id;
	UINT16 isdbtcc_width;
	UINT16 isdbtcc_height;
	UINT16 isdbtcc_hor_offset;
	UINT16 isdbtcc_ver_offset;

	void (*osd_isdbtcc_enter)(void);
	void (*osd_isdbtcc_leave)(void);
};

struct isdbt_get_lang_by_pid
{
	int pid;
	unsigned int para;
};

struct subt_atsc_stream_identify {
	unsigned short length;
	UINT8 *data;
};


void osd_isdbtcc_enter(void);
void osd_isdbtcc_leave(void);
void lib_isdbtcc_init(void);
void lib_isdbtcc_attach(struct isdbtcc_config_par *pcc_config_par);

INT32 isdbtcc_dec_attach(struct sdec_feature_config * cfg_param);
void isdbtcc_disply_init(struct sdec_device *dev);
void isdbtcc_get_cur_lang_by_pid(UINT16 pid, UINT32 lang);

void lib_subt_atsc_set_buf(struct atsc_subt_config_par* p_config);
UINT16 lib_subt_atsc_stream_identify(UINT16 length,UINT8 *data);
BOOL lib_subt_atsc_create_task(void);
BOOL lib_subt_atsc_terminate_task(void);
void lib_subt_atsc_clean_up(void);
void lib_subt_atsc_delete_timer(void);
void lib_subt_atsc_show_onoff(BOOL onoff);


#endif //__DRIVERS_ALI_RPC_HLD_SDEC_H

