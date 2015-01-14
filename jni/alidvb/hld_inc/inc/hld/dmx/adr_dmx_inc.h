
#if 1
/****************************************************************************
 *
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2002 Copyright (C)
 *
 *  File: dmx.h
 *
 *  Description: head file for demux device management.
 *
 *  History:
 *      Date        Author         Version   Comment
 *      ====        ======         =======   =======
 *  1.  
 ****************************************************************************/
#ifndef  __ADR_DMX_INC_H_
#define  __ADR_DMX_INC_H_


#include <osal/osal.h>

#include <hld/decv/adr_decv.h>
#include <hld/dmx/adr_dmx.h>

#include <ali_dsc_common.h>
//#include <linux/dvb/ali_dmx.h>
#include <ali_dmx_common.h>
#include <linux/Ali_DmxLibInternal.h>
#include <pthread.h>


#ifdef __cplusplus
extern "C" {
#endif



#define DMX_HLD_PORTING_SEC_SLOT_CNT 		22

#define DMX_HLD_PORTING_PES_SLOT_CNT 		10

#define DMX_HLD_PORTING_REC_SLOT_CNT 		4

#define DMX_HLD_PORTING_CSA_SLOT_CNT 		32	//36

#define DMX_HLD_PORTING_SEC_REQ_DEFAULT_DELAY 6000

#define DMX_HLD_PORTING_PLAYBACK_REQ_LEN 	3008 /* 16 * 188 */
#define FAST_PLAYBACK_SPEED					10
#define NORMAL_PLAYBACK_SPEED				100


#define DMX_HLD_PORTING_MAX_LINUX_DEV_PATH_LEN 128
#define DMX_HLD_PORTING_NEW_SERVICE_SLOT_CNT 16
#define DMX_OTHER_PORTING_CNT (DMX_HLD_PORTING_CSA_SLOT_CNT-6)
#define DMX_HLD_PORTING_NEW_SERVICE_SLOT_CNT 16

#define PVR_DECRYPT_KEY_LEN 128

#define FAST_PLAYBACK_SPEED			10
#define NORMAL_PLAYBACK_SPEED			100

enum DMX_PORTING_AV_STREAM_VALID
{
    DMX_PORTING_AV_V_VALID = 0x1,
    DMX_PORTING_AV_A_VALID = 0x2,
    DMX_PORTING_AV_AD_VALID = 0x4
};


enum DMX_HLD_PORTING_DATA_SRC
{
    DMX_HLD_PORTING_DMX_DATA_SRC_LIVE = 0,
    DMX_HLD_PORTING_DMX_DATA_SRC_PLAYBACK
};



enum DMX_HLD_PORTING_STATUS
{
    DMX_HLD_PORTING_STATUS_IDLE = 0,
    DMX_HLD_PORTING_STATUS_RUN,
    DMX_HLD_PORTING_STATUS_PAUSE
};


enum DMX_HLD_PORTING_AV_STREAM_STATUS
{
    DMX_HLD_PORTING_AV_STREAM_READY = 0,
    DMX_HLD_PORTING_AV_STREAM_RUN
};

enum DMX_HLD_PORTING_SEC_SLOT_STATUS
{
    DMX_HLD_PORTING_SEC_SLOT_IDLE = 0,
    DMX_HLD_PORTING_SEC_SLOT_PAUSE,
    DMX_HLD_PORTING_SEC_SLOT_RUN
};


enum DMX_HLD_PORTING_PES_SLOT_STATUS
{
    DMX_HLD_PORTING_PES_SLOT_IDLE = 0,
    DMX_HLD_PORTING_PES_SLOT_PAUSE,
    DMX_HLD_PORTING_PES_SLOT_RUN
};

enum DMX_HLD_PORTING_REC_SLOT_STATUS
{
    DMX_HLD_PORTING_REC_SLOT_IDLE = 0,
    DMX_HLD_PORTING_REC_SLOT_RUN
};


enum DMX_HLD_PORTING_PLAYBACK_SLOT_STATUS
{
    DMX_HLD_PORTING_PLAYBACK_READY = 0,
    DMX_HLD_PORTING_PLAYBACK_RUN
};

enum DMX_HLD_PORTING_REC_SLOT_FORMAT
{
    DMX_HLD_PORTING_REC_FORMAT_TS_MPEG2,
    DMX_HLD_PORTING_REC_FORMAT_TS_H264,
    DMX_HLD_PORTING_REC_FORMAT_TS_RAW,
    DMX_HLD_PORTING_REC_FORMAT_PS_MPEG2,

    DMX_HLD_PORTING_REC_FORMAT_PES,
    DMX_HLD_PORTING_REC_FORMAT_ES,
};


enum DMX_HLD_PORTING_TIMESHIFT_STATUS
{
    DMX_HLD_PORTING_TIMESHIFT_NONE,
    DMX_HLD_PORTING_TIMESHIFT_FROM_PLAY,
    DMX_HLD_PORTING_TIMESHIFT_FROM_IDLE
};

enum DMX_HLD_PORTING_CSA_SLOT_STATUS
{
    ALI_CSA_SLOT_STATUS_IDLE,
    ALI_CSA_SLOT_STATUS_READY,
    ALI_CSA_SLOT_STATUS_RUN,
};

enum DMX_HLD_PORTING_NEW_SERVICE_SLOT_STATUS
{
    DMX_HLD_PORTING_NEW_SERVICE_SLOT_IDLE = 0,
    DMX_HLD_PORTING_NEW_SERVICE_SLOT_PAUSE,
    DMX_HLD_PORTING_NEW_SERVICE_SLOT_RUN
};


struct dmx_hld_porting_avp_slot
{
    UINT16 pid;
    INT32 linux_fd;
    UINT32 csa_slot_idx;

};


#define PES_HEAD_PTS_LEN	184 //14


struct dmx_hld_porting_sec_slot
{
    enum DMX_HLD_PORTING_SEC_SLOT_STATUS status;

    /* One linux dmx file for one sec slot. */
    INT32 linux_fd;

    UINT32 csa_slot_idx;
    
    struct get_section_param *sec_para;

    UINT32 id;

    /* Point back to parent struct dmx_hld_porting. */
    UINT8 *porting;

	/* Section slot statistics information. */
	struct Ali_DmxSlotSecStatInfo stat_info;
};

#define DMX_REC_PID_LIST_MAX_LEN 32


struct dmx_hld_porting_rec_slot
{
    enum DMX_HLD_PORTING_REC_SLOT_STATUS status;

    UINT16 user_pid_list[DMX_REC_PID_LIST_MAX_LEN];

    UINT32 user_pid_list_len; /* Counted in UINT16 unit. */

    UINT16 orig_pid_list[DMX_REC_PID_LIST_MAX_LEN];

    UINT32 orig_pid_list_len; /* Counted in UINT16 unit. */

    UINT32 dynamic_pid_en;

    UINT16 dynamic_pid_list[DMX_REC_PID_LIST_MAX_LEN];

    UINT32 dynamic_pid_list_len; /* Counted in UINT16 unit. */

    /* Linux dmx file for retrieving data for recording.*/
    INT32 linux_fd;

    /* Rec flags. */
    enum DMX_HLD_PORTING_REC_SLOT_FORMAT out_format;

    UINT32 rec_whole_tp;

    UINT8  *buf;

    UINT8   tail_buf[16];
    UINT32  rec_hdl;

    UINT32  buf_len;

    UINT32  buf_wr;

    UINT16  cur_buf_i_frm_offset;

    UINT16  pri_buf_i_frm_offset;

    /* For i frame seeking. */
    UINT8   last_5_byte_in_pri_ts[5];

    INT32 (*req_buf)(UINT32 hdl, UINT8 **buf, INT32 req_len, INT32 *got_len);

    BOOL (*ret_buf)(UINT32 hdl, UINT32 data_len, UINT16 i_fm_offset);  
    void *enc_para;
};


struct dmx_hld_porting_pes_slot
{
    enum DMX_HLD_PORTING_PES_SLOT_STATUS status;

    /* One linux dmx file for one pes slot. */
    INT32 linux_fd;

    UINT16 filter_id;   //Save the filter_ID from AP usage 
    UINT16 pid;  //Save the PID

    enum DMX_HLD_PORTING_REC_SLOT_FORMAT out_format;

	//Buffer management for PES Data 
    UINT8  *buf;

    UINT32  pes_hdl;
    
    UINT32  buf_len;
    UINT32  buf_wr;
    struct control_block pSDataCtrlBlk;	//Add to compat with TDS API

    /* Point back to parent struct dmx_hld_porting. */
    UINT8 *porting;    

	/* PES slot statistics information. */
	struct Ali_DmxSlotPesStatInfo stat_info;

	INT32 (*pes_req_buf)(void * pdev, UINT32 uSizeRequested,void ** ppuData,UINT32* puSizeGot,struct control_block* pSDataCtrlBlk);
    void (*pes_ret_buf)(void * pdev,UINT32 uDataSize);
};


struct dmx_hld_porting_playback_slot
{
    enum DMX_HLD_PORTING_PLAYBACK_SLOT_STATUS status;

    UINT8 linux_dev_path[DMX_HLD_PORTING_MAX_LINUX_DEV_PATH_LEN];
    
    /* Linux file for write playback stream data into. */
    INT32 linux_fd;

    UINT32 hnd;

    UINT8 h264_flag;

    UINT8 is_scrambled;

    UINT8 rec_type;   //0:TS, 1:PS.

    INT32 (*data_req)(UINT32 hdl, UINT8 **data, INT32 req_len, INT32 *vbu_flag); 

    __u32 need_start;

    __u32 need_stop;

    OSAL_ID pb_run_to_idle_done_sem;

    __u32 pb_task_interval;
    UINT8 is_radio;
};



struct dmx_hld_porting_ttx_slot
{
    //enum DMX_HLD_PORTING_SEC_SLOT_STATUS status;

    /* One linux dmx file for one sec slot. */
    INT32 linux_fd;

    UINT16 pid;
};


struct dmx_hld_porting_subt_slot
{
    //enum DMX_HLD_PORTING_SEC_SLOT_STATUS status;

    /* One linux dmx file for one sec slot. */
    INT32 linux_fd;

    UINT16 pid;
};

struct dmx_hld_porting_hw_ctl_slot
{
    INT32 linux_fd;
};

struct dmx_hld_porting_csa_slot
{
    UINT32 idx;

    enum DMX_HLD_PORTING_CSA_SLOT_STATUS status;

	UINT16 pre_pid;
    
    UINT8 cw_pair[32];

    KEY_PARAM CsaParamList;
};

struct dmx_hld_porting_new_service_slot
{
    UINT16 pid;
    /* One linux dmx file for one sec slot. */
    INT32  linux_fd;
    UINT32 id;
    UINT8  *buf;
    UINT32  buf_len;
    UINT32  buf_wr;
    enum DMX_HLD_PORTING_NEW_SERVICE_SLOT_STATUS status;
    struct register_service_new new_service_param;
    struct control_block ctrl_blk;
};

struct dmx_hld_porting
{
    OSAL_ID ioctl_mutex;

    UINT16 tds_dmx_id;

    enum DMX_HLD_PORTING_DATA_SRC data_src;

    UINT8 linux_dmx_path[DMX_HLD_PORTING_MAX_LINUX_DEV_PATH_LEN];

    enum DMX_HLD_PORTING_STATUS status;

    /* AV play. */
    enum DMX_HLD_PORTING_AV_STREAM_STATUS av_stream_status;

    struct dmx_hld_porting_avp_slot v_slot;
    struct dmx_hld_porting_avp_slot a_slot;
    struct dmx_hld_porting_avp_slot p_slot;
    struct dmx_hld_porting_avp_slot ad_slot;
    struct dmx_hld_porting_avp_slot other_slot[DMX_OTHER_PORTING_CNT];
    struct dmx_hld_porting_new_service_slot new_service_slot[DMX_HLD_PORTING_NEW_SERVICE_SLOT_CNT];

    /* Teletext pid. */
    struct dmx_hld_porting_ttx_slot ttx_slot;

    /* Subtitle pid. */
    struct dmx_hld_porting_subt_slot subt_slot;

    /* PES slots. */
    struct dmx_hld_porting_pes_slot pes_slot[DMX_HLD_PORTING_PES_SLOT_CNT]; 
    OSAL_ID pes_dispatch_task_id;


    /* Section slots. */
    struct dmx_hld_porting_sec_slot sec_slot[DMX_HLD_PORTING_SEC_SLOT_CNT]; 

    struct dmx_hld_porting_csa_slot csa_slot[DMX_HLD_PORTING_CSA_SLOT_CNT];
    OSAL_ID sec_dispatch_task_id;

    OSAL_ID sec_hit_flag;

    /* Rec slots. */
    struct dmx_hld_porting_rec_slot rec_slot[DMX_HLD_PORTING_REC_SLOT_CNT];

    OSAL_ID rec_task_id;

    /* Playback slot. */
    struct dmx_hld_porting_playback_slot playback_slot;

    OSAL_ID playback_task_id;

    INT32 timeshift_status;

    /* HW control slot. */
    struct dmx_hld_porting_hw_ctl_slot hw_ctl_slot;

    /* Linux dmx SEE file discriptor. */
    INT32 see_dev_fd;

    enum dmx_see_av_sync_mode see_av_sync_mode;

     /* CSA related. */
    UINT32	csa_en;
    UINT32	csa_ver;
    UINT32	csa_fir_idx;
    
    pDEEN_CONFIG p_DeEnconfig;
    /* Mutex protection.
	*/
    pthread_t ioctl_mutex_lock_thread_id;

	UINT32 ioctl_mutex_lock_nest_cnt;
	
	UINT32 audio_disable;
    UINT32  fe;
    UINT32 nim_chip_id;	

	OSAL_ID new_service_task_id;
};


#if 0
struct dmx_hld_porting
{
    OSAL_ID ioctl_mutex;

    UINT16 tds_dmx_id;

    enum DMX_HLD_PORTING_DATA_SRC data_src;

    UINT8 linux_dmx_path[DMX_HLD_PORTING_MAX_LINUX_DEV_PATH_LEN];

    enum DMX_HLD_PORTING_STATUS status;

    /* AV play. */
    enum DMX_HLD_PORTING_AV_STREAM_STATUS av_stream_status;

    struct dmx_hld_porting_avp_slot v_slot;
    struct dmx_hld_porting_avp_slot a_slot;
    struct dmx_hld_porting_avp_slot p_slot;
    struct dmx_hld_porting_avp_slot ad_slot;
    struct dmx_hld_porting_avp_slot other_slot[DMX_OTHER_PORTING_CNT];
    struct dmx_hld_porting_new_service_slot new_service_slot[DMX_HLD_PORTING_NEW_SERVICE_SLOT_CNT];

    /* Teletext pid. */
    struct dmx_hld_porting_ttx_slot ttx_slot;

    /* Subtitle pid. */
    struct dmx_hld_porting_subt_slot subt_slot;

    /* Section slots. */
    struct dmx_hld_porting_sec_slot sec_slot[DMX_HLD_PORTING_SEC_SLOT_CNT]; 

    struct dmx_hld_porting_csa_slot csa_slot[DMX_HLD_PORTING_CSA_SLOT_CNT];
    OSAL_ID sec_dispath_task_id;

    OSAL_ID sec_hit_flag;

    /* Rec slots. */
    struct dmx_hld_porting_rec_slot rec_slot[DMX_HLD_PORTING_REC_SLOT_CNT];

    OSAL_ID rec_task_id;

    /* Playback slot. */
    struct dmx_hld_porting_playback_slot playback_slot;

    OSAL_ID playback_task_id;
    
    OSAL_ID new_service_task_id;

    INT32 timeshift_status;

    /* HW control slot. */
    struct dmx_hld_porting_hw_ctl_slot hw_ctl_slot;

    /* Linux dmx SEE file discriptor. */
    INT32 see_dev_fd;

    enum dmx_see_av_sync_mode see_av_sync_mode;

     /* CSA related. */
    UINT32 csa_en;
    UINT32 csa_ver;
    
    pDEEN_CONFIG p_DeEnconfig;
	
	UINT32 audio_disable;
    UINT32  fe;
    UINT32 nim_chip_id;
};
#endif

#ifdef __cplusplus
}
#endif

#endif  /* _ADR_DMX_INC_H_*/
#endif

