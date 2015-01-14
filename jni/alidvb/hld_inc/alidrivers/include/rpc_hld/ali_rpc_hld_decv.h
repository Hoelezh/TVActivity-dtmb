#ifndef __DRIVERS_ALI_RPC_HLD_DECV_H
#define __DRIVERS_ALI_RPC_HLD_DECV_H

#include <alidefinition/adf_decv.h>
#include "ali_rpc_hld.h"

//add by phil for boot-media
enum LIB_BOOT_MEDIA_FUNC{
    FUNC_BOOT_MEDIA_START = 0,
};

enum LLD_DECV_M36_FUNC{
    FUNC_VDEC_M36_ATTACH = 0,
    FUNC_VDEC_S3601_DE_RELEASE,
    FUNC_VDEC_S3601_DE_REQUEST,
    FUNC_VDEC_ENABLE_ADVANCE_PLAY,   
    FUNC_VDEC_MPEG2_DECODE,
    FUNC_VDEC_DISABLE_DVIEW,    
};

enum LLD_DECV_AVC_FUNC{
    FUNC_VDEC_AVC_ATTACH = 0,   
    FUNC_VDEC_AVC_DECODE = 1,
};
enum LIB_MP4DEC_FUNC{
    FUNC_VDEC_MPEG4_DECODE = 0,
    FUNC_VDEC_MPEG4_PLUS_DECODE = 1,
};

enum LIB_MJPGDEC_FUNC{
    FUNC_VDEC_MJPG_DECODE = 0,
};

enum LIB_RVDEC_FUNC{
    FUNC_VDEC_RV_DECODE = 0,
};

enum LIB_VP8DEC_FUNC{
    FUNC_VDEC_VP8_DECODE = 0,
};
//add by phil for vc1
enum LIB_VC1DEC_FUNC{
    FUNC_VDEC_VC1_DECODE = 0,
};

enum HLD_DECV_FUNC{
    FUNC_VDEC_OPEN = 0,   
    FUNC_VDEC_CLOSE,
    FUNC_VDEC_START,
    FUNC_VDEC_STOP,
    FUNC_VDEC_VBV_REQUEST,
    FUNC_VDEC_VBV_UPDATE,
    FUNC_VDEC_SET_OUTPUT,
    FUNC_VDEC_SWITCH_PIP,
    FUNC_VDEC_SWITCH_PIP_EXT,
    FUNC_VDEC_SYNC_MODE,
    FUNC_VDEC_EXTRAWIN_STORE_LAST_PIC,
    FUNC_VDEC_PROFILE_LEVEL,
    FUNC_VDEC_IO_CONTROL,
    FUNC_VDEC_PLAYMODE,
    FUNC_VDEC_DVR_SET_PARAM,
    FUNC_VDEC_DVR_PAUSE,
    FUNC_VDEC_DVR_RESUME,
    FUNC_VDEC_STEP,
    FUNC_H264_DECODER_SELECT,
    FUNC_GET_SELECTED_DECODER,
    FUNC_IS_CUR_DECODER_AVC,
    FUNC_SET_AVC_OUTPUT_MODE_CHECK_CB,
    FUNC_VIDEO_DECODER_SELECT,
    FUNC_GET_CURRENT_DECODER,
};

struct vdec_avc_memmap
{
    BOOL support_multi_bank;

    UINT32 frame_buffer_base;
    UINT32 frame_buffer_len;

    UINT32 dv_frame_buffer_base;
    UINT32 dv_frame_buffer_len;

    UINT32 mv_buffer_base;
    UINT32 mv_buffer_len;

    UINT32 mb_col_buffer_base;
    UINT32 mb_col_buffer_len;

    UINT32 mb_neighbour_buffer_base;
    UINT32 mb_neighbour_buffer_len;

    UINT32 cmd_queue_buffer_base;
    UINT32 cmd_queue_buffer_len;

    UINT32 vbv_buffer_base;
    UINT32 vbv_buffer_len;

    UINT32 laf_rw_buf;
    UINT32 laf_rw_buffer_len;

    UINT32 laf_flag_buf;
    UINT32 laf_flag_buffer_len;

	BOOL   support_conti_memory;
	UINT32 avc_mem_addr;
	UINT32 avc_mem_len;
    
    UINT32 auxp_addr;
};

struct vdec_avc_config_par
{	
	struct vdec_avc_memmap memmap;
    UINT32 max_additional_fb_num;
#ifdef VIDEO_SEAMLESS_SWITCHING
	UINT8 seamless_enable;
#endif
	UINT8 dtg_afd_parsing;
};
struct vdec_avs_memmap
{
	BOOL support_multi_bank;

	UINT32 frame_buffer_base;
	UINT32 frame_buffer_len;

	UINT32 dv_frame_buffer_base;
	UINT32 dv_frame_buffer_len;

	UINT32 mv_buffer_base;
	UINT32 mv_buffer_len;

	UINT32 mb_col_buffer_base;
	UINT32 mb_col_buffer_len;

	UINT32 mb_neighbour_buffer_base;
	UINT32 mb_neighbour_buffer_len;

	UINT32 cmd_queue_buffer_base;
	UINT32 cmd_queue_buffer_len;

	UINT32 vbv_buffer_base;
	UINT32 vbv_buffer_len;

	UINT32 laf_rw_buf;
	UINT32 laf_rw_buffer_len;

	UINT32 laf_flag_buf;
	UINT32 laf_flag_buffer_len;

	BOOL   support_conti_memory;
	UINT32 avs_mem_addr;
	UINT32 avs_mem_len;
	UINT32 auxp_addr;
};

struct vdec_avs_config_par
{	
	struct vdec_avs_memmap memmap;
};

#if 1
//#define TEST_VE_TIME_INFO
#define TEST_TOTAL_TIME (5)


//8/17
#ifdef DGS_AVSYNC_METHOD	//only for the project of dongqi
#define	VDEC27_LM_SHIFTTHRESHOLD			4	
#else
#define	VDEC27_LM_SHIFTTHRESHOLD			2	
#endif

//#define	VDEC27_SDRAM_SIZE		SYS_SDRAM_SIZE

//#define	VDEC27_SUPPORT_DROPPIC_AFTER_ERROR





#define	VDEC27_DVIEW_MAP_2M			0
#define	VDEC27_DVIEW_MAP_N2M		1


#define	VDEC27_DVIEW_V_MP_HEIGHT			288

//3module config

#define VDEC27_SML_FRM_ON   0x01
#define VDEC27_SML_FRM_OFF   0x02

#define VDEC27_H_PRECISION_2    (0x02<<16)
#define VDEC27_H_PRECISION_4    (0x04<<16)
#define VDEC27_H_PRECISION_8    (0x08<<16)

#define VDEC27_V_PRECISION_2    0x02
#define VDEC27_V_PRECISION_4    0x04
#define VDEC27_V_PRECISION_8    0x08


#define VDEC27_DVIEW_OPT_2   2
#define VDEC27_DVIEW_OPT_4   4
#define VDEC27_DVIEW_OPT_8   8
#define VDEC27_DVIEW_OPT_H2_V4  12
#define VDEC27_DVIEW_OPT_H4_V2  13
#endif

#define	VDEC27_PREVIEW_VE_SCALE	0x01
#define	VDEC27_PREVIEW_DE_SCALE	0x02

#if 1



#ifdef DVR_PVR_SUPPORT
#define	VDEC_ADVANCE_PLAY_MODE
#endif





#ifndef __ATTRIBUTE_REUSE_
#define	__ATTRIBUTE_REUSE_ __attribute__((section(".reuse")))
#endif

#ifdef SYS_ADJUST_PREVIEW_ACCORD_SRC_RATE
//pelease open this macrodefinition for M3327+2M project+120M memory clock to remove the tear at the bottom of preview window when P->N or P->P 
#define	VDEC27_ADJUST_PREVIEW_ACCORD_SRC_RATE
#endif

#ifdef	HDT_M3329_MODEL1
#define	VDEC27_DROP_FREERUN_BEFORE_FIRSTSHOW
#endif
#define VDEC27_DROP_THRESHOLD 20


#define VDEC27_SUPPORT_HW_COMSUME_RUBBISH
#ifdef VDEC27_SUPPORT_HW_COMSUME_RUBBISH
#define	VDEC27_HEADER_FL_MAX	1
#define	VDEC27_LITTERBIN_ADDR	((__MM_MAF_START_ADDR+0x400-0xFF)&0xFFFFFFF0)
#endif
 
#define VIDEO_ADPCM_ONOFF           VIDEO_ADPCM_OFF   
#define VDEC27_SML_FRM_ONOFF        VDEC27_SML_FRM_OFF
#define	VDEC27_SML_FRM_SIZE		0
#define VDEC27_DVIEW_PRECISION      (VDEC27_H_PRECISION_4|VDEC27_V_PRECISION_4)
//#define VDEC27_DVIEW_ADJUST_2
//#define	VDEC27_USE_RE_ADPCM
#define VDEC27_PREVIEW_PRECISION    (VDEC27_H_PRECISION_2|VDEC27_V_PRECISION_2)


//SDK config parameter
#define VDEC_VALID_USR_DATA 				 (1<<0)
#define VDEC_VALID_DROP_FIRST_FREE_PIC 	 (1<<1)
#define VDEC_VALID_RESET_HW_D_WHEN_STOP 	 (1<<2)
#define VDEC_VALID_SHOW_HD_SERVICE		 (1<<3)
#define VDEC_VALID_STILL_FRM_IN_CC          	 (1<<4)
#define VDEC_VALID_EXTRA_DV_WINDOW             (1<<5)
#define VDEC_VALID_NOT_SHOW_MOSAIC		 (1<<6)
#define VDEC_VALID_ADPCM					 (1<<7)
#define VDEC_VALID_SML_FRM 					 (1<<8)
#define VDEC_VALID_LM_SHIFTTHRESHOLD				 (1<<9)
#define VDEC_VALID_VP_INIT_PHASE					 (1<<10)
#define VDEC_VALID_PREV_SOLUTION					 (1<<11)
#define VDEC_VALID_MEM_ADDR						 (1<<12)

//num of features
#define VDEC_MAX_NUM_OF_FEATURES			  (13)
#endif
//3API parameter

//4vdec_m3327_get_frm
#define 	VDEC_DISPLAY		0x01
#define	VDEC_UN_DISPLAY	0x02
#define   VDEC_FRM_REF		0x03

#define VIDEO_OPEN_PIP_WIN_FLAG   0X80 

//changed for s3601-6/5
//4vdec_set_profile_level
#define	SP_ML				0x58
#define	MP_LL				0x4A
#define	MP_ML				0x48
#define	MP_H14				0x46
#define	MP_HL				0x44	
#define	SNR_LL				0x3A
#define	SNR_ML				0x38
#define	Spatial_H14			0x26
#define	HP_ML				0x18
#define	HP_H14				0x16
#define	HP_HL				0x14
//- changed end
//4Set_Output

enum VDECDecoderMode
{
	VDEC_FULL_MODE,
	VDEC_QUICK_MODE
};

struct vdec_callback
{
    VDecCBFunc	pcb_first_showed;
	VDecCBFunc	pcb_mode_switch_ok;
    VDecCBFunc	pcb_backward_restart_gop;
    VDecCBFunc pcb_first_head_parsed;
    VDecCBFunc pcb_ff_fb_showed;
    VDecCBFunc  pcb_first_i_decoded;
};

//4Get_frm
struct vdec_frm_info_api
{
	UINT32 uY_Addr;
	UINT32 uC_Addr;
	UINT16 uWidth;
	UINT16 uHeight;
	UINT32 uY_Size;//rachel:support_return_multi_freebuffer
	UINT32 uC_Size;//rachel:support_return_multi_freebuffer
};


//4Set_Output	to be removed
/*
typedef enum Output_Frame_Ret_Code (* VDecMPRequest)(struct Display_Info *);
typedef BOOL (* VDecMPRelease)(UINT8, UINT8 );
typedef enum Output_Frame_Ret_Code (* VDecPIPRequest)(struct PIP_Dislay_Info *);
typedef BOOL (* VDecPIPRelease)(UINT8);

struct VDec_MP_CallBack
{
	VDecMPRequest	RequestCallback;
	VDecMPRelease	ReleaseCallback;
};

struct VDec_PIP_CallBack
{
	VDecPIPRequest	RequestCallback;
	VDecPIPRelease	ReleaseCallback;
};
*/

#define	VDec_MP_CallBack MPSource_CallBack		//for compatible with application that had used the VDec_MP_Callback
#define	VDec_PIP_CallBack PIPSource_CallBack

typedef void (* VDec_PullDown_Func)(UINT32);
struct VDec_PullDown_Opr
{
	VDec_PullDown_Func	OpenDeinterlace;
	VDec_PullDown_Func	CloseDeinterlace;
};
struct vdec_start_para
{
	enum VDecOutputMode eMode;
	BOOL hd_support;
	void* reserved;
};
 
struct vdec_mem_map
{
	//frm addr
	UINT32	frm0_Y_size;
	UINT32	frm0_C_size;
	UINT32	frm1_Y_size;
	UINT32	frm1_C_size;
	UINT32	frm2_Y_size;
	UINT32	frm2_C_size;
	
	UINT32	frm0_Y_start_addr;
	UINT32	frm0_C_start_addr;
	UINT32	frm1_Y_start_addr;
	UINT32	frm1_C_start_addr;
	UINT32	frm2_Y_start_addr;
	UINT32	frm2_C_start_addr;

	UINT32	dvw_frm_size;
	UINT32	dvw_frm_start_addr;

	//MAF addr
	UINT32	maf_size;
	UINT32	maf_start_addr;

	//VBV addr
	UINT32	vbv_size;
	UINT32	vbv_start_addr;
	UINT32	vbv_end_addr;

	//frame buffer 3 allocated for pip application
	UINT32	frm3_Y_size;
	UINT32 	frm3_C_size;
	UINT32 	frm3_Y_start_addr;
	UINT32 	frm3_C_start_addr;

	UINT32   frm_num;//3 // 3 or 4 frames can be choosed for the main device. It is unactive for the second device
	UINT32   res_bits;
	UINT32  *res_pointer;
};

struct vdec_adpcm
{
	UINT8 adpcm_mode;
	UINT8 adpcm_ratio;
};

struct vdec_sml_frm
{
	UINT8 sml_frm_mode;
	UINT32 sml_frm_size;
};

enum vdec_nonshow_mosaic_threshold
{
	MOST_NON_SHOW,
	MORE_NON_SHOW,
	COMMON_NON_SHOW,
	SOME_MOSAIC_SHOW,
	MANY_MOSAIC_SHOW
};

struct vdec_config_par
{	
	//feature entrys
	UINT8 user_data_parsing;
	UINT8 dtg_afd_parsing;
	UINT8 drop_freerun_pic_before_firstpic_show;
	UINT8 reset_hw_directly_when_stop;
	UINT8 show_hd_service;
	UINT8 still_frm_in_cc;//only work in 2M mode
	UINT8 extra_dview_window;
	UINT8 not_show_mosaic;// now's feature just work rightly at Dview & MP mode
	UINT8 return_multi_freebuf;
	UINT8 advance_play;
	
	struct vdec_adpcm adpcm;
	struct vdec_sml_frm sml_frm;
	
	UINT8 lm_shiftthreshold;////only for the project of dongqi( digisat)
	UINT8 vp_init_phase;//according to macro DEFAULT_MP_FILTER_ENABLE
	UINT8 preview_solution;
	
	struct vdec_mem_map mem_map;
	UINT32 res_bits;
	UINT32 *res_pointer;
};


#if 0
//#ifdef USE_NEW_VDEC
static char decv_m3327_name[] = {"DECV_M3327"};
#endif

struct vdec_io_get_frm_para
{
	UINT8 ufrm_mode;
	struct vdec_frm_info_api tFrmInfo;
};
//rachel:support_return_multi_freebuffer
#define	VDEC_GET_FRM_MAX_NUM 3
struct vdec_io_get_frm_para_advance
{
	UINT8 ufrm_mode;
	UINT8 request_frm_number;
	struct vdec_frm_info_api tFrmInfo[VDEC_GET_FRM_MAX_NUM];
	UINT8 return_frm_number;
};

#define	VDEC_FREEBUF_USER_DB			0x01
#define	VDEC_FREEBUF_USER_OSD		0x02
#define VDEC_HIGH_PRIORITY_STOP 0x01
#define VDEC_HIGH_PRIORITY_SML  0x02
struct vdec_io_get_freebuf_para
{
	UINT8	request_user_id;
	UINT32	request_size;
	UINT32	got_free_addr;
	UINT32	got_free_size;
};

enum vdec_io_decode_speed
{
	VDEC_SPEED_NORMAL = 0,
	VDEC_SPEED_FORWARD_2,
	VDEC_SPEED_FORWARD_4
};
struct vdec_io_get_frm_statistic
{
	UINT16    conti_drop_cnt;
	UINT16    conti_hold_cnt;
	UINT16    conti_freerun_cnt;
	UINT16	reserved16;
};
//changed for s3601-6/5
struct vdec_adpcm_cmd
{
	BOOL onoff;
	UINT8 ratio;
};
struct vdec_maf_cmd
{
	BOOL onoff;	
};
struct vdec_dview_cmd
{
	BOOL 	adaptive_precision;
    	UINT8   	h_precision;
    	UINT8   	v_precision;
};
struct vdec_err_conceal_cmd
{
	BOOL onoff;
	UINT8 method;
	UINT8 threshold;
	UINT8 next_mb_x;
	UINT8 next_mb_y;
};
struct vdec_abs_cmd
{
	BOOL onoff;
	BOOL adaptive_threshold;
	UINT8 threshold;
};

struct vdec_io_extra_dview_info
{
	BOOL	bonoff;
	struct Rect	extra_dview_win_rect;
	UINT8		smooth_zoom_vector;
	UINT8		step_max_num;	//from 1,....
	
};

#define VDEC_IO_FILL_BG_VIDEO           0x70
#define VDEC_IO_BG_FILL_BLACK           0x71
#define VDEC_IO_RESERVE_MEMORY          0x72    // reserve memory for some feature, i.e. capture displaying frame
#define VDEC_IO_GET_MULTIVIEW_BUF       0x73
#define VDEC_IO_SET_MULTIVIEW_WIN       0x74

#define CONTAINER_IO_CONTROL_BASE 				0xffff
#define CONTAINER_IO_CONTROL_GET_TIME_MS		(CONTAINER_IO_CONTROL_BASE+1)
#define CONTAINER_IO_CONTROL_EN_AC3_BS_MODE     (CONTAINER_IO_CONTROL_BASE+2)
#define CONTAINER_IO_CONTROL_GET_CHAPTER_INFO   (CONTAINER_IO_CONTROL_BASE+3)
#define CONTAINER_IO_CONTROL_GET_TOTALTIME_MS   (CONTAINER_IO_CONTROL_BASE+4)
#define CONTAINER_IO_CONTROL_SET_AVSYNC_DELAY   (CONTAINER_IO_CONTROL_BASE+5)

enum VDEC_DBG_FLAG
{
	VDEC_DBG_NONE,
	VDEC_DBG_DEFAULT,	
};

struct vdec_io_dbg_flag_info
{
	enum VDEC_DBG_FLAG dbg_flag;
	int active_flag;
	int unique_flag;
};

#define VDEC_IO_DBG_BASE				0xF0000000
#define VDEC_IO_SET_DBG_FLAG			(VDEC_IO_DBG_BASE + 0x0001)

#if 0
void vdec_m3327_attach(void);
void vdec_m3327_dettach(struct vdec_device *dev);
#else
void vdec_m36_attach(struct vdec_config_par *pconfig_par);
RET_CODE vdec_enable_advance_play(struct vdec_device *dev);
void vdec_avc_attach(struct vdec_avc_config_par *pconfig_par);

void vdec_avs_attach(struct vdec_avs_config_par *pconfig_par);
#endif

void vdec_disable_dview(struct vdec_device *dev);

#if 0
RET_CODE vdec_pause(struct vdec_device *dev);
RET_CODE vdec_resume(struct vdec_device *dev);
#endif

RET_CODE vdec_switch_pip(struct vdec_device *dev, struct Position *pPIPPos);
RET_CODE vdec_switch_pip_ext(struct vdec_device *dev, struct Rect *pPIPWin);
RET_CODE vdec_extrawin_store_last_pic(struct vdec_device *dev, struct Rect *pPIPWin);
/* for advanced play */
RET_CODE vdec_enable_advance_play(struct vdec_device *dev);
RET_CODE vdec_profile_level(struct vdec_device *dev, UINT8 uProfileLevel,VDEC_BEYOND_LEVEL cb_beyond_level);
void set_avc_output_mode_check_cb(VDecCBFunc pCB);
/* end */

RET_CODE vdec_decore_ioctl(void *phandle, int cmd, void *param1, void *param2);

//add by phil for boot-media
void boot_media_start(UINT32 addr, UINT32 len);

#if 0
/*
void decv_sync_level(struct vdec_device *dev, UINT8 uSyncLevel);
void decv_fill_all_frm(struct vdec_device *dev, struct YCbCrColor *pcolor);
RET_CODE decv_register_cb(struct vdec_device *dev, enum VDecCBType eCBType,VDecCBFunc pCB);
void decv_get_status(struct vdec_device *dev, struct VDec_StatusInfo *pCurStatus);
void decv_dbg_why_idle(struct vdec_device *dev);
RET_CODE decv_get_src_mode(struct vdec_device *dev, enum TVSystem *peTVSys);
void decv_get_frm(struct vdec_device *dev, UINT8 ufrm_mode,struct vdec_frm_info_api *pFrmInfo);
*/



//#define	VDec_Attach(x) 		vdec_m3327_attach()
//#define	VDec_Detach(x1)		vdec_m3327_dettach(x1)

//#define	VDec_Open(x1, x2) 	vdec_open(x1)
//#define	VDec_Close(x1)		vdec_close(x1)

//#define	VDec_Decode(x1,x2,x3,x4,x5,x6,x7) vdec_start(x1)
//#define	VDec_Stop(x1,x2,x3,x4,x5) vdec_stop(x1)
//#define	VDec_Pause(x1)		vdec_pause(x1)
//#define	VDec_Resume(x1)		vdec_resume(x1)

//#define	VDec_SetOutput(x1,x2,x3,x4,x5,x6) vdec_set_output(x1,x2,x3,x4)
//#define	VDec_SwitchPIPWin(x1)		vdec_switch_pip(0,x1)

//#define	VDec_Set_Sync_Mode(x1, x2) vdec_sync_mode(x1, x2)
//#define	VDec_Set_Sync_Level(x1, x2) decv_sync_level(x1, x2)

//#define	VDec_FillDisplayFrm(x1,x2) 	decv_fill_all_frm(x1, x2)
//#define	VDec_RegisterCB(x1,x2,x3)	decv_register_cb(x1,x2,x3)
//#define	VDec_GetStatusInfo(x1,x2)	decv_get_status(x1,x2)	
//#define	VDec_Dbg_WhyUIdle()		decv_dbg_why_idle(0)
//#define	VDec_GetSourceMode(x1,x2)	decv_get_src_mode(x1,x2)
//#define	VDec_Get_Frm(x1,x2)			decv_get_frm(0,x1,x2)

//show logo call this function 
//#define	decv_request_write(x1,x2,x3,x4,x5) 		vdec_vbv_request(x1,x2,x3,x4,x5)
//#define	decv_update_write(x1,x2)					vdec_vbv_update(x1,x2)

/*
#define	VDec_SetOutput(x1,x2,x3,x4,x5,x6) vdec_set_output(x1,x2,x3,x4)
#define	VDec_SwitchPIPWin(x1)		vdec_switch_pip(0,x1)

#define	VDec_Set_Sync_Mode(x1, x2) vdec_sync_mode(x1, x2)
#define	VDec_Set_Sync_Level(x1, x2) decv_sync_level(x1, x2)

#define	VDec_FillDisplayFrm(x1,x2) 	decv_fill_all_frm(x1, x2)
#define	VDec_RegisterCB(x1,x2,x3)	decv_register_cb(x1,x2,x3)
#define	VDec_GetStatusInfo(x1,x2)	decv_get_status(x1,x2)	
#define	VDec_Dbg_WhyUIdle()		decv_dbg_why_idle(0)
#define	VDec_GetSourceMode(x1,x2)	decv_get_src_mode(x1,x2)
#define	VDec_Get_Frm(x1,x2)		decv_get_frm(x1,x2)

//show logo call this function 
#define	decv_request_write(x1,x2,x3,x4,x5) 		vdec_vbv_request(x1,x2,x3,x4,x5)
#define	decv_update_write(x1,x2)				vdec_vbv_update(x1,x2)
*/
//#endif
#endif
enum LLD_DECV_AVS_FUNC{
    FUNC_VDEC_AVS_ATTACH = 0,   
};
#endif
