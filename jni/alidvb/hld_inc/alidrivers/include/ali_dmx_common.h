
#ifndef _ALI_DMX_COMMON_H_
#define _ALI_DMX_COMMON_H_

#include <linux/types.h>
#include "ali_basic_common.h"





#define DMX_SEC_MASK_MAX_LEN     32
#define DMX_REC_PID_LIST_MAX_LEN 32

enum dmx_channel_output_space
{
    DMX_OUTPUT_SPACE_USER,
    DMX_OUTPUT_SPACE_KERNEL,
    DMX_OUTPUT_SPACE_USER_EX,
};


enum dmx_channel_output_format
{
    DMX_CHANNEL_OUTPUT_FORMAT_TS,
    DMX_CHANNEL_OUTPUT_FORMAT_PES,
    DMX_CHANNEL_OUTPUT_FORMAT_SEC,
    DMX_CHANNEL_OUTPUT_FORMAT_PCR
};


enum dmx_see_av_sync_mode
{
    DMX_SEE_AV_SYNC_MODE_LIVE = 0,
    DMX_SEE_AV_SYNC_MODE_PLAYBACK = 1,
    DMX_SEE_AV_SYNC_MODE_TSG_TIMESHIT = 2,
    DMX_SEE_AV_SYNC_MODE_TSG_LIVE = 3,  
};

struct dmx_sec_channel_param
{
    __u16 pid;
    __u8  mask[DMX_SEC_MASK_MAX_LEN];
    __u8  value[DMX_SEC_MASK_MAX_LEN];
    __u32 mask_len;
    __u32 timeout;
    __u32 option;
};

struct dmx_pes_channel_param
{
    __u16 pid;
    __u32 timeout;

    /* For kernel space only. */
    struct ali_dec_input_callback_routine_pars callback_para;
};


struct dmx_pcr_channel_param
{
    __u16 pid;
};



struct dmx_ts_kern_recv_info
{
    __u32 kern_recv_routine;
    
    __u32 kern_recv_routine_para;
};


struct dmx_ts_channel_param
{  
    __u32 pid_list_len;
    __u16 pid_list[DMX_REC_PID_LIST_MAX_LEN];

    /* Kernel space only. */
    struct dmx_ts_kern_recv_info kern_recv_info;
};


struct dmx_channel_param
{
    enum dmx_channel_output_format output_format;

    enum dmx_channel_output_space output_space;

    struct dmx_ts_channel_param ts_param;

    struct dmx_sec_channel_param sec_param;

    struct dmx_pes_channel_param pes_param;

	struct dmx_pcr_channel_param pcr_param;

	
    __u32 enc_para;
    __u32 rec_whole_tp;
    
    __s32 fst_cpy_slot;
    
    __u32 buf_size;
    
    __u32  fe;
    __u32 nim_chip_id;
};


struct dmx_see_av_pid_info
{
    __u16 v_pid;
    __u16 a_pid;
    __u16 p_pid;
    __u16 ad_pid;
};



struct dmx_see_av_scram_info
{
     __u16 pid[2];
     __u8 scram_status;
};

struct dmx_fast_copy_param
{
#ifdef __CHECKER__
    const char __user  *data;
#else
	const char *data;
#endif
    __s32 len;
};


#define ALI_DMX_IOC_MAGIC  0xA1


/* Legacy IO control command, handled by device "ali_m36_dmx_0".
 */
#define ALI_DMX_CHANNEL_START _IOW(ALI_DMX_IOC_MAGIC, 11, struct dmx_channel_param)
#define ALI_DMX_CHANNEL_STOP  _IO(ALI_DMX_IOC_MAGIC, 12)

#define ALI_DMX_CHANNEL_GET_CUR_PKT_LEN  _IOR(ALI_DMX_IOC_MAGIC, 13, __u32)
#define ALI_DMX_CHANNEL_GET_PKT_LEN  ALI_DMX_CHANNEL_GET_CUR_PKT_LEN//_IOR(ALI_DMX_IOC_MAGIC, 15, __u32)

#define ALI_DMX_CHANNEL_FLUSH_BUF  _IO(ALI_DMX_IOC_MAGIC, 14)

#define ALI_DMX_CHANNEL_GET_STARTCODE_OFFSET  _IOR(ALI_DMX_IOC_MAGIC, 15, __u32)
#define ALI_DMX_CHANNEL_FLUSH_STARTCODE_OFFSET  _IOR(ALI_DMX_IOC_MAGIC, 16, __u32)

#define ALI_DMX_HW_GET_FREE_BUF_LEN  _IOR(ALI_DMX_IOC_MAGIC, 17, __u32)

#define ALI_DMX_GET_PROG_BITRATE  _IOR(ALI_DMX_IOC_MAGIC, 18, __u32)

#define ALI_DMX_PLAYBACK_FSTCPY   _IOW(ALI_DMX_IOC_MAGIC, 19, __u32)


#define ALI_DMX_IO_SET_BYPASS_MODE  _IOW(ALI_DMX_IOC_MAGIC, 40, __u32)
#define ALI_DMX_IO_BYPASS_GETDATA  _IOW(ALI_DMX_IOC_MAGIC, 41, __u32)
#define ALI_DMX_IO_CLS_BYPASS_MODE  _IOW(ALI_DMX_IOC_MAGIC, 42, __u32)

#define ALI_DMX_IO_SET_PLAYBACK_SRC_TYPE  _IOW(ALI_DMX_IOC_MAGIC, 43, __u32)

#define ALI_DMX_BYPASS_ALL  _IOW(ALI_DMX_IOC_MAGIC, 44, __u32)
#define ALI_DMX_RESET_BITRATE_DETECT  _IOW(ALI_DMX_IOC_MAGIC, 45, __u32)

#define ALI_DMX_SEE_AV_START _IOW(ALI_DMX_IOC_MAGIC, 70, struct dmx_see_av_pid_info)
#define ALI_DMX_SEE_AV_STOP  _IO(ALI_DMX_IOC_MAGIC, 71)

#define ALI_DMX_SEE_A_CHANGE_PID _IOW(ALI_DMX_IOC_MAGIC, 72, struct dmx_see_av_pid_info)

#define ALI_DMX_SEE_TELETXT_START _IOW(ALI_DMX_IOC_MAGIC, 73, __u16)
#define ALI_DMX_SEE_SUBTITLE_START _IOW(ALI_DMX_IOC_MAGIC, 74, __u16)

#define ALI_DMX_SEE_AV_SYNC_MODE_SET _IOW(ALI_DMX_IOC_MAGIC, 75, enum dmx_see_av_sync_mode)


#define ALI_DMX_SEE_CRYPTO_TYPE_SET  _IOW(ALI_DMX_IOC_MAGIC, 76, struct dec_parse_param)
#define ALI_DMX_SEE_CRYPTO_START _IO(ALI_DMX_IOC_MAGIC, 77)
#define ALI_DMX_SEE_CRYPTO_STOP _IO(ALI_DMX_IOC_MAGIC, 78)

#define ALI_DMX_SEE_AV_SCRAMBLE_STATUS _IOR(ALI_DMX_IOC_MAGIC, 79, __u8)
#define ALI_DMX_SEE_GET_DISCONTINUE_COUNT   _IOR(ALI_DMX_IOC_MAGIC, 80, __u32)
#define ALI_DMX_SEE_GET_MAIN2SEEBUF_REAMIN_DATA_LEN   _IOR(ALI_DMX_IOC_MAGIC, 81, __u32)

#define ALI_DMX_SEE_AV_SCRAMBLE_STATUS_EXT _IOWR(ALI_DMX_IOC_MAGIC, 90, struct dmx_see_av_scram_info)

#define ALI_DMX_SEE_SET_PLAYBACK_SPEED _IOW(ALI_DMX_IOC_MAGIC, 91, __u32)
#define ALI_DMX_SEE_SET_UPDATE_REMAIN _IOW(ALI_DMX_IOC_MAGIC, 92, __u32)

#define ALI_DMX_SEE_GET_TS_INPUT_ROUTINE _IOR(ALI_DMX_IOC_MAGIC, 93, struct dmx_ts_kern_recv_info)

#define ALI_DMX_GET_LATEST_PCR _IOR(ALI_DMX_IOC_MAGIC, 94, __u32)
#define ALI_DMX_SEE_PLAYBACK_PAUSE          _IOW(ALI_DMX_IOC_MAGIC, 95, __u32)
#define ALI_DMX_SEE_PLAYBACK_PRE_PAUSE      _IOW(ALI_DMX_IOC_MAGIC, 96, __u32)
#define ALI_DMX_SEE_CLEAR_DISCONTINUE_COUNT _IOW(ALI_DMX_IOC_MAGIC, 97, __u32)
#define ALI_DMX_SEE_DO_DDP_CERTIFICATION    _IOW(ALI_DMX_IOC_MAGIC, 98, __u32)
#define ALI_DMX_SET_HW_INFO                 _IO(ALI_DMX_IOC_MAGIC, 99)

//#define ALI_DMX_CHANNEL_SET_TO_PES     _IOW(ALI_DMX_IOC_MAGIC, 44, struct dmx_pes_channel_params)
//#define ALI_DMX_CHANNEL_GET_TEST_PES_PARAM   _IOR(ALI_DMX_IOC_MAGIC, 45, struct ali_video_input_callback_routine_pars)
#define ALI_DMX_CHANNEL_ADD_PID         _IOW(ALI_DMX_IOC_MAGIC, 100, struct dmx_channel_param)
#define ALI_DMX_CHANNEL_DEL_PID         _IOW(ALI_DMX_IOC_MAGIC, 101, struct dmx_channel_param)
#define ALI_DMX_SEE_SET_SAT2IP          _IOW(ALI_DMX_IOC_MAGIC, 102, __u32)

/* New DMX IO control commands.
*/
#define ALI_DMX_SEE_GET_STATISTICS _IOR(ALI_DMX_IOC_MAGIC, 1085, struct Ali_DmxSeeStatistics)
#define ALI_DMX_CHAN_SEC_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1086, struct Ali_DmxDrvSecStrmStatInfo)
#define ALI_DMX_CHAN_SEC_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1087, struct Ali_DmxDrvSecFltStatInfo)
#define ALI_DMX_CHAN_TS_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1088, struct Ali_DmxDrvTsStrmStatInfo)
#define ALI_DMX_CHAN_TS_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1089, struct Ali_DmxDrvTsFltStatInfo)

//Used in the Section
#define ALI_DMX_CHAN_SEC_TS_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1090, struct Ali_DmxDrvTsFltStatInfo)
#define ALI_DMX_CHAN_AUDIO_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1091, struct Ali_DmxDrvAudioStrmStatInfo)
#define ALI_DMX_CHAN_AUDIO_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1092, struct Ali_DmxDrvTsFltStatInfo)
#define ALI_DMX_CHAN_AUDIO_SEE_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1093, struct Ali_DmxSeePlyChStatInfo)

#define ALI_DMX_CHAN_VIDEO_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1094, struct Ali_DmxDrvVideoStrmStatInfo)
#define ALI_DMX_CHAN_VIDEO_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1095, struct Ali_DmxDrvTsFltStatInfo)
#define ALI_DMX_CHAN_VIDEO_SEE_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1096, struct Ali_DmxSeePlyChStatInfo)

#define ALI_DMX_CHAN_PCR_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1097, struct Ali_DmxDrvPcrStrmStatInfo)
#define ALI_DMX_CHAN_PCR_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1098, struct Ali_DmxDrvTsFltStatInfo)
#define ALI_DMX_CHAN_TS_IN_RAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 1099, struct Ali_DmxDrvTsInRamStrmStatInfo)

#define ALI_DMX_CHAN_HW_REG_CFG 		_IO(ALI_DMX_IOC_MAGIC, 2000)
#define ALI_DMX_CHAN_HW_REG_START 		_IO(ALI_DMX_IOC_MAGIC, 2001)
#define ALI_DMX_CHAN_HW_REG_STOP 		_IO(ALI_DMX_IOC_MAGIC, 2002)
#define ALI_DMX_CHAN_HW_REG_INFO_GET 	_IOR(ALI_DMX_IOC_MAGIC, 2003, __u32)
#define ALI_DMX_CHAN_KERN_GLB_CFG 		_IO(ALI_DMX_IOC_MAGIC, 2010)
#define ALI_DMX_CHAN_KERN_GLB_START 	_IO(ALI_DMX_IOC_MAGIC, 2011)
#define ALI_DMX_CHAN_KERN_GLB_STOP 		_IO(ALI_DMX_IOC_MAGIC, 2012)
#define ALI_DMX_CHAN_KERN_GLB_INFO_GET 	_IOR(ALI_DMX_IOC_MAGIC, 2013, struct Ali_DmxKernGlobalStatInfo)
#define ALI_DMX_CHAN_KERN_GLB_REALTIME_SET 	_IOW(ALI_DMX_IOC_MAGIC, 2014, struct Ali_DmxKernGlobalStatInfo)

#define ALI_DMX_CHAN_SEE_GLB_CFG 		_IO(ALI_DMX_IOC_MAGIC, 2020)
#define ALI_DMX_CHAN_SEE_GLB_START 		_IO(ALI_DMX_IOC_MAGIC, 2021)
#define ALI_DMX_CHAN_SEE_GLB_STOP 		_IO(ALI_DMX_IOC_MAGIC, 2022)
#define ALI_DMX_CHAN_SEE_GLB_INFO_GET 	_IOR(ALI_DMX_IOC_MAGIC, 2023, struct Ali_DmxSeeGlobalStatInfo)
#define ALI_DMX_CHAN_SEE_GLB_REALTIME_SET 	_IOW(ALI_DMX_IOC_MAGIC, 2024, struct Ali_DmxSeeGlobalStatInfo)

#define ALI_DMX_CHAN_TP_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 2030, struct Ali_DmxDrvTpStrmStatInfo)
#define ALI_DMX_CHAN_PES_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 2040, struct Ali_DmxDrvPesStrmStatInfo)
#define ALI_DMX_CHAN_PES_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 2041, struct Ali_DmxDrvPesFltStatInfo)
#define ALI_DMX_CHAN_PES_TS_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 2042, struct Ali_DmxDrvTsFltStatInfo)

#endif


