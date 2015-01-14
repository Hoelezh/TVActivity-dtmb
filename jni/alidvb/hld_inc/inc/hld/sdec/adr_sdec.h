#ifndef	__ADR_HLD_SDEC_H__
#define __ADR_HLD_SDEC_H__

#include <adr_basic_types.h>
#include <hld/osd/adr_osddrv.h>
#include <hld/sdec/adr_sdec_dev.h>

#define MAX_REGION_IN_PAGE 8
#define MAX_OBJECT_IN_REGION 8
#define MAX_ENTRY_IN_CLUT 16

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

struct OSDRect;
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
	UINT8 support_hw_decode;//1,support;0,no
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

struct isdbt_get_lang_by_pid
{
	int pid;
	unsigned int para;
};

struct subt_atsc_stream_identify {
	unsigned short length;
	UINT8 *data;
};

#ifdef __cplusplus
extern "C"
{
#endif

INT32 sdec_open(struct sdec_device *dev);
INT32 sdec_close(struct sdec_device *dev);
INT32  sdec_start(struct sdec_device *dev,UINT16 composition_page_id,UINT16 ancillary_page_id);
INT32  sdec_stop(struct sdec_device *dev);
INT32  sdec_pause(struct sdec_device *dev);
INT32 sdec_ioctl(struct sdec_device *dev, UINT32 cmd, UINT32 param);
INT32 sdec_request_write(void * pdev, UINT32 uSizeRequested,void ** ppuData,UINT32* puSizeGot,struct control_block* pSDataCtrlBlk);
void sdec_update_write(void *dev,UINT32 uDataSize);
void draw_object_hardware(UINT8 * data, UINT16 len, UINT8 CLUT_id, UINT8 region_idx,UINT16 stride, UINT8 field_polar, UINT16 x, UINT16 y);
void sdec_m36_attach(void);

#ifdef __cplusplus
}
#endif

#endif /*__HLD_SDEC_H__*/






