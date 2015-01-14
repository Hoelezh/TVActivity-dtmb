#ifndef __ADF_AVSYNC__
#define __ADF_AVSYNC__

#include "adf_basic.h"
#include "adf_media.h"


/*! @addtogroup avsync
 *  @{
*/

#ifdef __cplusplus
extern "C" {
#endif

#define AVSYNC_IO_ENABLE_DDP_CERTIFICATION 0x01  //!< 使能 DDP 认证
#define AVSYNC_IO_GET_VIDEO_SMOOTHLY_PLAY_CFG   0x02//!< 配置video 平滑播放
#define AVSYNC_IO_ENABLE_GET_STC 0x03	//!< 用于MAIN CPU 获取stc
#define AVSYNC_IO_SET_PTS_UNIT_HZ   0x04 //!< 设置PTS   单位
#define AVSYNC_IO_UNREG_CALLBACK   0x05	//!< 销毁 callback
#define AVSYNC_IO_REG_CALLBACK   0x06//!< 注册 callback
#define AVSYNC_IO_GET_CURRENT_PLAY_PTS   0x07	//!<获取当前的 PTS
#define AVSYNC_IO_PAUSE   0x08	//!<暂停 avsync  模块
#define AVSYNC_IO_RESUME   0x09	//!<恢复 avsync 模块

/*! @enum LLD_AVSYNC_FUNC
@brief  用于remote call 调用
*/
enum LLD_AVSYNC_FUNC{
    FUNC_AVSYNC_ATTACH = 0,
};

 
 /*! @enum HLD_AVSYNC_FUNC
 @brief  用于remote call 调用
 */
enum HLD_AVSYNC_FUNC{
    FUNC_AVSYNC_OPEN = 0,   
    FUNC_AVSYNC_CLOSE,
    FUNC_AVSYNC_START,   
    FUNC_AVSYNC_STOP,
    FUNC_AVSYNC_RESET,
    FUNC_AVSYNC_IOCTL,
    FUNC_AVSYNC_SET_SYNCMODE,
    FUNC_AVSYNC_GET_SYNCMODE,
    FUNC_AVSYNC_CFG_PARAMS,
    FUNC_AVSYNC_GET_PARAMS,
    FUNC_AVSYNC_CFG_ADV_PARAMS,
    FUNC_AVSYNC_GET_ADV_PARAMS,
    FUNC_AVSYNC_SET_SRCTYPE,
    FUNC_AVSYNC_GET_SRCTYPE,
    FUNC_AVSYNC_GET_STATUS,
    FUNC_AVSYNC_GET_STATISTICS,
    FUNC_AVSYNC_VIDEO_SMOOTHLY_PLAY_ONOFF,
    FUNC_AVSYNC_DBG_SET_PRINT_OPTION,
    FUNC_AVSYNC_DBG_SET_POLL_ONOFF,
    FUNC_AVSYNC_DBG_SET_POLL_OPTION,
    FUNC_AVSYNC_DBG_SET_POLL_INTERVAL,
};

/*! @struct avsync_get_stc_en_t
@brief Main cpu获取STC时钟使用
*/

typedef struct 
{
	void *sharem_addr;
	UINT8 enable;
}avsync_get_stc_en_t;

/*! @enum AVSYNC_PTS_MODE
@brief 当前PTS 是否有效
*/
typedef enum  
{
	AVSYNC_PTS_MODE_FREE, //no PTS 
	AVSYNC_PTS_MODE_CNT,//not used
	AVSYNC_PTS_MODE_VALID,// valid pts
	AVSYNC_PTS_MODE_INVALID,	//non valid pts
}AVSYNC_PTS_MODE;


/*! @enum AVSYNC_FRAME_SYNCFLAG_E
@brief 当前同步标志
*/
typedef enum 
{
	AVSYNC_FRAME_PLAY,	 //play Audio/Video frame
	AVSYNC_FRAME_DROP,  // drop Audio/Video frame
	AVSYNC_FRAME_HOLD, // hold Audio by SW
	AVSYNC_FRAME_FREERUN, // free run frame
	AVSYNC_FRAME_HW_HOLD, //hold Audio frame by HW
}AVSYNC_FRAME_SYNCFLAG_E;

/*! @enum AVSYNC_MODE_E
@brief 音视频同步模式, AVSYNC模块默认配置为AVSYNC_MODE_PCR，AVSYNC_MODE_VIDEO暂不支持
*/
typedef enum 
{
	AVSYNC_MODE_PCR,       //!<以PCR为基准
	AVSYNC_MODE_AUDIO,     //!<以音频为基准
	AVSYNC_MODE_VIDEO,     //!<以视频为基准, 暂不支持
	AVSYNC_MODE_V_FREERUN, //!<视频不作同步,直接播放
	AVSYNC_MODE_A_FREERUN, //!<音频不作同步,直接播放
	AVSYNC_MODE_AV_FREERUN, //!<音视频不作同步,直接播放
}AVSYNC_MODE_E;

/*! @ enum AVSYNC_SRCTYPE_E
@brief 音视频数据源类型，AVSYNC模块默认配置为AVSYNC_SRC_TURNER
*/
typedef enum 
{
	AVSYNC_SRC_TURNER, //!<数据来自turner
	AVSYNC_SRC_SWDMX, //!<数据来自SW DMX
	AVSYNC_SRC_HDD_MP, //!<数据来自本地媒体播放
	AVSYNC_SRC_NETWORK_MP, //!<数据来自网络媒体播放
}AVSYNC_SRCTYPE_E;
typedef enum 
{
	AVSYNC_H264, // decoder is h.264
	AVSYNC_MPEG2, //decoder is MPEG2
	AVSYNC_MPEG4,  //decoder is MPEG4
	AVSYNC_AVS,  //decoder is AVS
}AVSYNC_CODEC_TYPE;

/*! @ enum AVSYNC_DEVICE_STATUS
@brief AVSYNC设备状态
*/
typedef enum 
{
	AVSYNC_ATTACHED, //!<设备已挂接
	AVSYNC_OPENED,    //!<设备已打开
	AVSYNC_CLOSED,    //!<设备已关闭
	AVSYNC_STARTED,  //!<设备已开始工作
	AVSYNC_STOPPED,	//!<设备已停止工作	
}AVSYNC_DEV_STATUS;

/*! @ enum AVSYNC_VIDEO_SMOOTH_LEVEL
@brief 视频平滑播放等级
*/
typedef enum 
{
	AVSYNC_VIDEO_SMOOTH_LEVEL1, 
	AVSYNC_VIDEO_SMOOTH_LEVEL2, 
}AVSYNC_VIDEO_SMOOTH_LEVEL;

/*! @ struct avsync_cfg_param_t
@brief 基本同步参数，AVSYNC模块默认配置参考下面描述。
*/
typedef struct
{
	UINT32 vhold_thres; //!<视频重复门限，默认值为80ms
	UINT32 vdrop_thres; //!<视频丢弃门限，默认值为80ms
	UINT32 ahold_thres; //!<音频重复门限，默认值为40ms
	UINT32 adrop_thres; //!<音频丢弃门限，默认值为64ms
	AVSYNC_MODE_E sync_mode; //!<音视频同步模式，默认值为AVSYNC_MODE_PCR
	AVSYNC_SRCTYPE_E src_type; //!<音视频数据源类型，默认值为AVSYNC_SRC_TURNER
}avsync_cfg_param_t;

/*! @ struct avsync_adv_param_t
@brief 高级同步参数，AVSYNC模块默认配置参考下面描述。
*/
typedef struct
{
	UINT32 afreerun_thres; //!<音频free run 门限，默认值为10s
	UINT32 vfreerun_thres; //!< 视频free run 门限，默认值为10s
	UINT8  disable_monitor; //!< 关闭monitor 功能标志,，默认值为1
	UINT8 disable_first_video_freerun; //!<禁用视频第一帧free run功能标志，默认值为0
	UINT16  dual_output_sd_delay; //!< 视频双输出标清输出延迟
	UINT32  pts_adjust_threshold;
	UINT32 rsvd2; 
	UINT32 rsvd3;
}avsync_adv_param_t;


/*! @ struct avsync_vsync_info_t
@brief  video 的同步信息结构体描述
*/
struct avsync_vsync_info_t
{
	UINT32 vpts;                                   // pts of video frame 
	AVSYNC_PTS_MODE	vpts_mode;    // pts mode of video frame
	UINT32 display_dly;                       // display delay from request avsync flag to real display
	UINT32 remain_esbuf_size;           // remained vbv buffer size
	UINT32 esbuf_size;                         // vbv buffer size
	UINT32 frame_duration;                 // video frame duration
	UINT32 bitrate;                               // video bit rate
	UINT8   stc_id;					//stc id used
	UINT8   bstream_run_back;          //stream run back flag
	UINT8   stc_offset_idx;			//stc offset index used
	UINT8   decode_error;			//decode error flag
	AVSYNC_CODEC_TYPE   CODEC_type;	//video codec used
	BOOL pause_state;				// in pause state
};

 /*! @ struct avsync_vsync_info_t
@brief  audio 的同步信息结构体描述
*/
struct  avsync_async_info_t
{
	UINT32 cur_apts;                           //pts of audio frame
	UINT32 next_apts;                         //next valid audio pts
	UINT32 frm_num_two_pts;            //frame number between_two_pts
	UINT32 remain_esbuf_size;          // remained audio es buffer size
	UINT32 esbuf_size;                       // audio es buffer size
	UINT32 remain_pcm_time;          // play time in pcm buffer
	UINT32 frame_duration;             // audio frame duration
	UINT32 bitrate;                            // video bit rate
	UINT8   stc_id;				//stc id used
	UINT8   bstream_run_back;//stream run back flag
	UINT8   pts_valid;			//pts valid flag
	UINT8   stc_offset_idx;		//stc offset index used
	UINT32 total_remain_pcm_time;	//pcm time remain in buffer
};


/*! @ struct avsync_status_t
@brief 模块状态
*/
typedef struct 
{
	AVSYNC_DEV_STATUS device_status; //!<设备状态
	UINT32 vpts_offset; //!<视频PTS偏移
	UINT32 apts_offset; //!<音频PTS偏移	
	UINT8 v_sync_flg; //!<视频同步标志
	UINT8 a_sync_flg; //!<音频同步标志
	UINT8 rsvd0; //!<预留
	UINT8 rsvd1; //!<预留

	UINT32 cur_vpts;//!< 当前视频PTS
	UINT32 cur_apts;//!< 当前音频PTS	
}avsync_status_t;

/*! @ struct AVSYNC_SRCTYPE_E
@brief 同步统计信息
*/
typedef struct 
{
	UINT32 total_v_play_cnt; //!<同步视频帧数
	UINT32 total_v_drop_cnt; //!<丢弃视频帧数
	UINT32 total_v_hold_cnt; // !<重复视频帧数
	UINT32 total_v_freerun_cnt; // !<free-run 视频帧数
	UINT32 total_a_play_cnt; //!<同步音频帧数
	UINT32 total_a_drop_cnt; //!<视频丢弃帧数
	UINT32 total_a_hold_cnt; // !<视频重复帧数
	UINT32 total_a_freerun_cnt;
}avsync_statistics_t;

/*! @ struct avsync_video_cb_t
@brief  注册给 video  driver的 callback函数
*/
struct avsync_video_cb_t
{
	void *get_vync_flg_cb; //获取video同步标志
	void *vbv_full_cb;// video buffer 满事件通知 
	void *avsync_start;// 用于启动avsync driver
	void *avsync_stop;// 用于停止 avsync driver
};

/*! @ struct avsync_video_cb_t
@brief  注册给 audio  driver的 callback函数
*/

struct avsync_audio_cb_t
{
	void *get_async_flg_cb; // 获取audio 同步标志
};

/*! @ struct avsync_smoothly_play_cfg_t
@brief  用于配置video的平滑播放
*/

struct  avsync_smoothly_play_cfg_t
{
	UINT8 onoff;		// 1打开；0关闭
	UINT8 interval;	//间隔时间
	AVSYNC_VIDEO_SMOOTH_LEVEL level;//级别 
};

#define AVSYNC_CB_MAX_DEV_NUM 4 //avsync设备最大个数

/*! @ struct avsync_cb
@brief  设备指针数组
*/

struct avsync_cb
{
	void *dmx[AVSYNC_CB_MAX_DEV_NUM];//最多AVSYNC_CB_MAX_DEV_NUM个dmx设备指针
	void *decv[AVSYNC_CB_MAX_DEV_NUM];//最多AVSYNC_CB_MAX_DEV_NUM个decv设备指针
	void *deca[AVSYNC_CB_MAX_DEV_NUM];//最多AVSYNC_CB_MAX_DEV_NUM个deca设备指针
	void *snd[AVSYNC_CB_MAX_DEV_NUM];//最多AVSYNC_CB_MAX_DEV_NUM个snd 设备指针
};

/*! @struct avsync_device
@brief 设备类型定义, 包含了成员变量以及提供的操作接口。
*/
struct avsync_device
{
	struct avsync_device  *next;  /*next device */
	/*struct module *owner;*/
	INT32 type;
	INT8 name[32];
	INT32 flags;

	void *priv;		/* Used to be 'private' but that upsets C++ */
	void      (*attach)(void *);
	void      (*detach)(struct avsync_device **);
	RET_CODE	(*open)(struct avsync_device *);
	RET_CODE   	(*close)(struct avsync_device *);
	RET_CODE	(*start)(struct avsync_device *);
	RET_CODE   	(*stop)(struct avsync_device *);
	RET_CODE   	(*ioctl)(struct avsync_device *, UINT32 , UINT32);	
	RET_CODE     (*reset)(struct avsync_device*);
	RET_CODE     (*set_syncmode)(struct avsync_device*, AVSYNC_MODE_E);
	RET_CODE     (*get_syncmode)(struct avsync_device*, AVSYNC_MODE_E *);
	RET_CODE     (*set_sourcetype)(struct avsync_device*, AVSYNC_SRCTYPE_E);
	RET_CODE     (*get_sourcetype)(struct avsync_device*, AVSYNC_SRCTYPE_E *);
	RET_CODE     (*config_params)(struct avsync_device*, avsync_cfg_param_t *);
	RET_CODE     (*get_params)(struct avsync_device*, avsync_cfg_param_t *);
	RET_CODE     (*config_adv_params)(struct avsync_device*, avsync_adv_param_t *);
	RET_CODE     (*get_adv_params)(struct avsync_device*, avsync_adv_param_t *);
	RET_CODE     (*get_status)(struct avsync_device*, avsync_cfg_param_t *);
	RET_CODE     (*get_statistics)(struct avsync_device*, avsync_cfg_param_t *);
	RET_CODE     (*video_smoothly_play_onoff)(struct avsync_device *, UINT8, AVSYNC_VIDEO_SMOOTH_LEVEL, UINT8);
	RET_CODE		(*dbg_set_print_option)(struct avsync_device *, UINT32);
	RET_CODE		(*dbg_poll_onoff)(struct avsync_device *, UINT32);
	RET_CODE		(*dbg_set_poll_option)(struct avsync_device *, UINT32);
	RET_CODE		(*dbg_set_poll_interval)(struct avsync_device *, UINT32);
};

typedef RET_CODE (*AVSYNC_GET_VIDEO_CTRLLK_CB)(struct avsync_device *, UINT32 , struct control_block *);
typedef RET_CODE (*AVSYNC_APTS_EXTRACT_CB)(struct avsync_device *, UINT32 , struct control_block *);
typedef RET_CODE (*AVSYNC_PROCESS_PCR_CB)(struct avsync_device *, UINT32);


/*! @ struct avsync_dmx_cb
@brief  向dmx注册的callback函数
*/
struct avsync_dmx_cb
{
    void *avsync_dev;		// avsync 设备指针
	AVSYNC_GET_VIDEO_CTRLLK_CB pvpts_cb; // video control block callback 函数
	AVSYNC_APTS_EXTRACT_CB papts_cb;//audio control block callback  函数
	AVSYNC_PROCESS_PCR_CB ppcr_cb; //pcr callback函数
};

typedef RET_CODE (*AVSYNC_GET_VSYNC_FLAG)(void *dev, struct avsync_vsync_info_t *, AVSYNC_FRAME_SYNCFLAG_E *, BOOL *);
typedef RET_CODE (*AVSYNC_VBV_BUFF_FULL)(void *dev);
typedef RET_CODE (*AVSYNC_START_CB)(void *dev);
typedef RET_CODE (*AVSYNC_STOP_CB)(void *dev);
typedef RET_CODE (*AVSYNC_GET_ASYNC_FLAG)(void *dev, struct avsync_async_info_t *, AVSYNC_FRAME_SYNCFLAG_E *);
typedef RET_CODE(*AVSYNC_GET_PAUSE_FLAG)(void*dev, UINT32 *, UINT32 *);


/*! @ struct avsync_callback
@brief  avsync模块的callbck函数
*/

struct avsync_callback
{
	struct avsync_device *pavsync_dev; // avsync 设备指针?
	AVSYNC_GET_VSYNC_FLAG pget_vync_flg_cb; // video 同步callback函数
	AVSYNC_VBV_BUFF_FULL pvbv_full_cb;//video buffer 溢出  callback 函数?
	AVSYNC_START_CB pavsync_start;  // 启动 avsync callback 函数
	AVSYNC_STOP_CB pavsync_stop;	// 停止 avsync callback  函数
	AVSYNC_GET_ASYNC_FLAG pget_async_flg_cb;	// audio 同步callback函数
	AVSYNC_GET_PAUSE_FLAG pget_avsync_pause_flag;// audio 暂停callback函数
};

/*!
@brief 注册设备avsync，分配资源等。
@note: 调用其他AVSYNC模块接口函数前，须先调用该函数。
*/
RET_CODE avsync_attach(void);

/*!
@brief 移除设备avsync,销毁资源等。
@param[in] dev 指向设备avsync的指针。
*/
void avsync_dettach(struct avsync_device*dev);

/*!
@brief 打开avsync模块。
@param[in] dev 指向avsync模块的指针。
@return RET_CODE。
@retval  RET_SUCCESS       打开成功。
@retval  !RET_SUCCESS     打开失败，参数错误或状态错误。
*/
RET_CODE avsync_open(struct avsync_device *dev);

/*!
@brief 关闭avsync模块。
@param[in] dev 指向avsync模块的指针。
@return RET_CODE。
@retval  RET_SUCCESS       关闭成功。
@retval  !RET_SUCCESS     关闭失败，参数错误或状态错误。
*/
RET_CODE avsync_close(struct avsync_device *dev);
/*!
@brief 启动avsync模块。
@param[in] dev 指向avsync模块的指针。
@return RET_CODE。
@retval  RET_SUCCESS       启动成功。
@retval  !RET_SUCCESS     启动失败，参数错误或状态错误。
*/

RET_CODE avsync_start(struct avsync_device *dev);

/*!
@brief 停止avsync模块。
@param[in] dev 指向avsync模块的指针。
@return RET_CODE。
@retval  RET_SUCCESS       停止成功。
@retval  !RET_SUCCESS    停止失败，参数错误或状态错误。
*/

RET_CODE avsync_stop(struct avsync_device *dev);

/*!
@brief 设备avsync提供的ioctl函数接口。 
@param[in] dev 指向设备avsync 的指针。
@param[in] io_code 命令类型
@param[in] param 命令参数。
@return RET_CODE。
@retval  RET_SUCCESS       调用成功。
@retval  !RET_SUCCESS     调用失败，参数错误或状态错误。
*/
RET_CODE avsync_ioctl(struct avsync_device *dev, UINT32 io_code, UINT32 param);

/*!
@brief 复位同步模块, 重新同步 
@param[in] dev 指向设备avsync的指针。
@return RET_CODE。
@retval  RET_SUCCESS       复位成功。
@retval  !RET_SUCCESS     复位失败，参数错误或状态错误。
*/RET_CODE avsync_reset(struct avsync_device *dev);

/*!
@brief 设置同步模式 
@param[in] dev 指向设备avsync的指针。
@param[in] mode 同步模式，同步模式参考AVSYNC_MODE_E定义。
@return RET_CODE。
@retval  RET_SUCCESS       设置成功。
@retval  !RET_SUCCESS     设置失败，参数错误或状态错误。
@note: 若应用层不调用该接口，AVSYNC模块内部使用默认配置，详见AVSYNC_MODE_E定义
*/
RET_CODE avsync_set_syncmode(struct avsync_device *dev, AVSYNC_MODE_E mode);

/*!
@brief 获取同步模式 
@param[in] dev 指向设备avsync的指针。
@param[out] pmode 获取到的同步模式。
@return RET_CODE。
@retval  RET_SUCCESS       获取成功。
@retval  !RET_SUCCESS     获取失败，参数错误或状态错误。
*/
RET_CODE avsync_get_syncmode(struct avsync_device *dev, AVSYNC_MODE_E *pmode);

/*!
@brief 设置数据源类型,不同的数据源处理不同 
@param[in] dev 指向设备avsync的指针。
@param[in] type 数据源类型,参考AVSYNC_SRCTYPE_E定义。
@return RET_CODE。
@retval  RET_SUCCESS       设置成功。
@retval  !RET_SUCCESS     设置失败，参数错误或状态错误。
@note: 若应用层不调用该接口，AVSYNC模块内部使用默认配置，详见AVSYNC_SRCTYPE_E定义
*/
RET_CODE avsync_set_sourcetype(struct avsync_device *dev, AVSYNC_SRCTYPE_E type);

/*!
@brief 获取数据源类型 
@param[in] dev 指向设备avsync的指针。
@param[out] ptype 获取到的数据源类型。
@return RET_CODE。
@retval  RET_SUCCESS       获取成功。
@retval  !RET_SUCCESS     获取失败，参数错误或状态错误。
*/
RET_CODE avsync_get_sourcetype(struct avsync_device *dev, AVSYNC_SRCTYPE_E *ptype);

/*!
@brief 设置基本同步参数 
@param[in] dev 指向设备avsync的指针。
@param[in] pcfg_params 基本同步参数配置。
@return RET_CODE。
@retval  RET_SUCCESS       设置成功。
@retval  !RET_SUCCESS     设置失败，参数错误或状态错误。
@note: 若应用层不调用该接口，AVSYNC模块内部使用默认配置，详见avsync_cfg_param_t定义
*/
RET_CODE avsync_config_params(struct avsync_device *dev,  avsync_cfg_param_t *pcfg_params);

/*!
@brief 获取基本同步参数 
@param[in] dev 指向设备avsync的指针。
@param[out] pcfg_params 获取基本同步参数。
@return RET_CODE。
@retval  RET_SUCCESS       获取成功。
@retval  !RET_SUCCESS     获取失败，参数错误或状态错误。
*/
RET_CODE avsync_get_params(struct avsync_device *dev,  avsync_cfg_param_t *pcfg_params);

/*!
@brief 设置高级同步参数 
@param[in] dev 指向设备avsync的指针。
@param[in] pcfg_params 高级同步参数配置。
@return RET_CODE。
@retval  RET_SUCCESS       设置成功。
@retval  !RET_SUCCESS     设置失败，参数错误或状态错误。
@note: 若应用层不调用该接口，AVSYNC模块内部使用默认配置，详见avsync_adv_param_t定义
*/
RET_CODE avsync_config_advance_params(struct avsync_device *dev,  avsync_adv_param_t *pcfg_params);

/*!
@brief 获取高级同步参数 
@param[in] dev 指向设备avsync的指针。
@param[out] pcfg_params 获取高级同步参数。
@return RET_CODE。
@retval  RET_SUCCESS       获取成功。
@retval  !RET_SUCCESS     获取失败，参数错误或状态错误。
*/
RET_CODE avsync_get_advance_params(struct avsync_device *dev,  avsync_adv_param_t *pcfg_params);

/*!
@brief 获取模块状态 
@param[in] dev 指向设备avsync的指针。
@param[out] pstatus 获取到的模块状态。
@return RET_CODE。
@retval  RET_SUCCESS       获取成功。
@retval  !RET_SUCCESS     获取失败，参数错误或状态错误。
*/
RET_CODE avsync_get_status(struct avsync_device *dev, avsync_status_t *pstatus);

/*!
@brief 获取同步统计信息 
@param[in] dev 指向设备avsync的指针。
@param[out] pstatistics 获取到的同步统计信息。
@return RET_CODE。
@retval  RET_SUCCESS       获取成功。
@retval  !RET_SUCCESS     获取失败，参数错误或状态错误。
*/
RET_CODE avsync_get_statistics(struct avsync_device *dev, avsync_statistics_t *pstatistics);

/*!
@brief 开启/关闭视频平滑播放功能 
@param[in] dev 指向设备avsync的指针。
@param[in] onoff 开启/关闭平滑播放功能
@param[in] level 平滑播放等级
@param[in] interval 平滑播放间隔(单位为帧数)
@return RET_CODE。
@retval  RET_SUCCESS       设置成功。
@retval  !RET_SUCCESS     设置失败，参数错误或状态错误。
*/
RET_CODE avsync_video_smoothly_play_onoff(struct avsync_device *dev, UINT8 onoff, AVSYNC_VIDEO_SMOOTH_LEVEL level, UINT8 interval);

/*==========================================
 *  AVSYNC Debug Start
 *==========================================*/
 
//实时打印选项 
#define AVSYNC_DBG_PRINT_DEFAULT 1 //!<打印STC调整及音视频不同步信息
#define AVSYNC_DBG_PRINT_PCR	2  //!<打印PCR及PCR间隔
#define AVSYNC_DBG_PRINT_APTS	4  //!<打印音频PTS及PTS间隔
#define AVSYNC_DBG_PRINT_VPTS 8  //!<打印视频PTS及PTS间隔
#define AVSYNC_DBG_PRINT_A_SYNC 0x10 //!<打印音频帧同步时PTS/STC值
#define AVSYNC_DBG_PRINT_A_UNSYNC_PTS_STC 0x20 //!<打印音频帧不同步时PTS/STC值
#define AVSYNC_DBG_PRINT_A_UNSYNC_STCID_OFFSET 0x40 //!<打印音频帧不同步时STC偏移
#define AVSYNC_DBG_PRINT_A_UNSYNC_ESBUF 0x80 //!<打印音频帧不同步时可用ES buffer长度
#define AVSYNC_DBG_PRINT_V_SYNC 0x100 //!<打印视频帧同步时PTS/STC值
#define AVSYNC_DBG_PRINT_V_UNSYNC_PTS_STC 0x200 //!<打印视频帧不同步时PTS/STC值
#define AVSYNC_DBG_PRINT_V_UNSYNC_STCID_OFFSET 0x400 //!<打印视频帧不同步时STC偏移
#define AVSYNC_DBG_PRINT_V_UNSYNC_VBVBUF 0x800 //!<打印视频帧不同步时可用VBV buffer长度
#define AVSYNC_DBG_PRINT_PTS_OFFSET  0x1000    //!<打印PTS偏移调整信息
#define AVSYNC_DBG_PRINT_STREAM_LOOP 0x2000    //!<检测到流回头时打印

#define AVSYNC_DBG_PRINT_VESBUF_OF_UR 0x4000   //!<打印视频ES buffer空或满
#define AVSYNC_DBG_PRINT_AESBUF_OF_UR 0x8000   //!<打印音频ES buffer空或满

#define AVSYNC_DBG_FORCE_SYNCMODE_FREERUN 0x10000   //!<同步模式强制成AVSYNC_MODE_AV_FREERUN
#define AVSYNC_DBG_FORCE_SYNCMODE_PCR 0x20000   //!<同步模式强制成AVSYNC_MODE_AV_PCR
#define AVSYNC_DBG_FORCE_SYNCMODE_AUDIO 0x40000   //!<同步模式强制成AVSYNC_MODE_AUDIO
#define AVSYNC_DBG_FORCE_SYNCMODE_INVALID 0x80000   //!<调试同步模式无效

#define AVSYNC_DBG_PRINT_API	0x10000000     //!<打印API调用
#define AVSYNC_DBG_PRINT_LOG	0x20000000	//!<LOG  打印
#define AVSYNC_DBG_PRINT_ERR	0x40000000     //!<打印模块出错信息

//轮询调试选项
#define AVSYNC_DBG_POLL_V_SYNC_STATISTICS  0x01	 //!<打开video 统计信息
#define AVSYNC_DBG_POLL_A_SYNC_STATISTICS  0x02  //!<打开audio 统计信息
#define AVSYNC_DBG_POLL_PCR_STATISTICS  0x04//!<打开pcr统计信息
#define AVSYNC_DBG_POLL_VBV_FULL_CNT  0x08 //!<video buffer 溢出次数
#define AVSYNC_DBG_POLL_PTS_OFFSET  0x10	//!<pts offset统计信息
#define AVSYNC_DBG_POLL_SYNC_MODE 0x20	//!<同步模式信息


/*!
@brief 设置实时调试打印选项 
@param[in] dev 指向设备avsync的指针。
@param[out] option 打印选项。
@return RET_CODE。
@retval  RET_SUCCESS       设置成功。
@retval  !RET_SUCCESS     设置失败。
*/
RET_CODE avsync_dbg_set_print_option(struct avsync_device *dev, UINT32 option);

/*!
@brief 开启/关闭轮询调试
@param[in] dev 指向设备avsync的指针。
@param[out] on_off 开启/关闭轮询调试。
@return RET_CODE。
@retval  RET_SUCCESS       设置成功。
@retval  !RET_SUCCESS     设置失败。
*/
RET_CODE avsync_dbg_polling_onoff(struct avsync_device *dev, UINT32 on_off);

/*!
@brief 设置轮询调试选项
@param[in] dev 指向设备avsync的指针。
@param[out] option 轮询调试选项。
@return RET_CODE。
@retval  RET_SUCCESS       设置成功。
@retval  !RET_SUCCESS     设置失败。
*/
RET_CODE avsync_dbg_set_polling_option(struct avsync_device *dev, UINT32 option);

/*!
@brief 设置轮询调试打印间隔
@param[in] dev 指向设备avsync的指针。
@param[out] interval_ms 轮询打印间隔，单位为毫秒
@return RET_CODE。
@retval  RET_SUCCESS       设置成功。
@retval  !RET_SUCCESS     设置失败。
*/
RET_CODE avsync_dbg_set_polling_interval(struct avsync_device *dev, UINT32 interval_ms);


#ifdef __cplusplus
}
#endif

/*!
@}
*/

#endif


