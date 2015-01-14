#ifndef __ADF_DECV__
#define __ADF_DECV__

/*! @addtogroup decv
 *  @{
*/

#include "adf_basic.h"
#include "adf_media.h"






















#define	VDEC_SYNC_PTS				0x00 //!< 打开音视频同步功能。
#define	VDEC_SYNC_FREERUN		0x01//!<关闭音视频同步功能。

#define	VDEC_SYNC_FIRSTFREERUN	0x01 //!< 自由播放视频第一帧。
#define	VDEC_SYNC_I				0x02 //!< 未实现。
#define	VDEC_SYNC_P				0x04 //!< 未实现。
#define	VDEC_SYNC_B				0x08 //!< 未实现。
#define   VDEC_SYNC_HIGH_LEVEL    	0x10 //!< 未实现。


#define VDEC_IO_FILL_FRM					0x03
#define VDEC_IO_REG_CALLBACK				0x04//!<注册回调函数
#define VDEC_IO_GET_STATUS					0x05 //!<读取vdec模块的状态信息
#define VDEC_IO_GET_MODE					0x06//!<读取视频源的制式
#define VDEC_IO_GET_FRM					0x07
#define VDEC_IO_WHY_IDLE					0x08
#define VDEC_IO_SMLBUF						0x09
#define VDEC_IO_GET_FREEBUF				0x0A
#define VDEC_IO_FILLRECT_INBG				0x0B
#define VDEC_IO_PRIORITY_STOP_SML   		0x0C
#define VDEC_IO_GET_FRM_ADVANCE			0x0D
#define VDEC_IO_DVIEW_EXTRA_MODE			0x0F
#define VDEC_IO_FILL_FRM2					0x10
#define VDEC_IO_ADPCM_CMD					0x13
#define VDEC_IO_ABS_CMD					0x0E
#define VDEC_IO_ERR_CONCEAL_CMD			0x0F
#define VDEC_IO_PULLDOWN_ONOFF			0x11
#define VDEC_IO_DVIEW_CMD					0x12
#define VDEC_IO_COLORBAR            			0x14
#define VDEC_IO_ENABLE_MPDVIEW			0x15
#define VDEC_IO_GET_VDEC_CONFIG     		0x16
#define VDEC_IO_SET_SCALE_MODE			0x17
#define VDEC_IO_ENABLE_PREVIEW_PIP		0x18
#define VDEC_IO_FILL_PREVIEW_PIP			0x19
#define VDEC_IO_REG_SYNC_STATUS 			0x1a
#define VDEC_IO_STOP_COPY_TASK      			0x20
#define VDEC_IO_GET_OUTPUT_FORMAT 		0x21
#define VDEC_IO_MAF_CMD					0x22
#define VDEC_IO_RESET_VE_HW 				0x23
#define VDEC_SET_DMA_CHANNEL  			0x24
#define VDEC_IO_SWITCH 						0x25
#define VDEC_IO_GET_FRAME_STATISTIC      	0x26
#define VDEC_IO_SET_DVIEW_PRECISION		0x27
#define VDEC_VBV_BUFFER_OVERFLOW_RESET  	0x28
#define VDEC_IO_GET_I_FRAME_CNT      		0x29
#define VDEC_IO_FIRST_I_FREERUN      		0x2A
#define VDEC_IO_DISCARD_HD_SERVICE      	0x2B
#define VDEC_IO_DONT_RESET_SEQ_HEADER   	0x2C
#define VDEC_IO_SET_DROP_FRM         			0x2D
#define VDEC_IO_MULTIVIEW_HWPIP         		0x2E
#define VDEC_DTVCC_PARSING_ENABLE		0x2f
#define VDEC_CLOSECAPTION_UDMODE        	0x30  
#define VDEC_IO_PLAYBACK_PS                  		0x31
#define VDEC_IO_PLAY_FROM_STORAGE     		0x32
#define VDEC_IO_CHANCHG_STILL_PIC     		0x33
#define VDEC_IO_SET_SYNC_DELAY        		0x34
#define VDEC_IO_SAR_ENABLE			  		0x35
#define VDEC_IO_FAST_CHANNEL_CHANGE         0x36
#define VDEC_IO_DROP_FRAME_VBVFULL     	0x37
#define VDEC_IO_SEAMLESS_SWITCH_ENABLE  	0x38
#define VDEC_IO_PAUSE_VIDEO	            		0x39
#define VDEC_IO_CONTINUE_ON_ERROR       	0x3a
#define VDEC_IO_SET_DECODER_MODE        		0x40
#define VDEC_IO_SET_FREERUN_THRESHOLD   	0x41
#define VDEC_IO_SET_OUTPUT_RECT         		0x42
#define VDEC_IO_SET_AVSYNC_GRADUALLY		0x43
#define VDEC_IO_DBLOCK_ENABLE           		0x44  
#define VDEC_IO_EN_MUTE_FIRST				0x45
#define VDEC_IO_GET_DECORE_STATUS       	0x46
#define VDEC_IO_SET_DEC_FRM_TYPE        		0x47
#define VDEC_IO_SET_DMA_CHANNEL_NUMBER	0x48
#define VDEC_IO_SET_BOOTLOGO_ADDR      		0x49
#define VDEC_IO_SET_SMOOTH_PREVIEW           0x4a
#define VDEC_IO_SET_DEC_ONLY_ONE_FRAME	0x4b
#define VDEC_IO_CLEAN_STILL_FRAME               0x4c


#define VDEC_IO_ELE_BASE						0x10000
#define VDEC_IO_PLAYBACK_STR					(VDEC_IO_ELE_BASE + 0x01)
#define VDEC_IO_REG_DROP_FUN					(VDEC_IO_ELE_BASE + 0x02)
#define VDEC_IO_REST_VBV_BUF					(VDEC_IO_ELE_BASE + 0x03)
#define VDEC_IO_KEEP_INPUT_PATH_INFO			(VDEC_IO_ELE_BASE + 0x04)
#define VDEC_IO_PLAY_MEDIA_STR				(VDEC_IO_ELE_BASE + 0x05)
#define VDEC_IO_LIVE_STR_MON					(VDEC_IO_ELE_BASE + 0x06)
#define VDEC_IO_DROP_BEF_FIRT_SHOW			(VDEC_IO_ELE_BASE + 0x07)
#define VDEC_IO_ENABLE_SW_MONITOR			(VDEC_IO_ELE_BASE + 0x08)
#define VDEC_IO_CAPTURE_DISPLAYING_FRAME	(VDEC_IO_ELE_BASE + 0x09)
#define VDEC_IO_PVR_STREAM_INDICATOR               (VDEC_IO_ELE_BASE + 0x0A)
#define VDEC_IO_SHOW_MOSAIC_LEVEL			(VDEC_IO_ELE_BASE + 0x0B)
#define VDEC_IO_REG_GET_SYNC_FLAG_CB			(VDEC_IO_ELE_BASE + 0x0C)
#define VDEC_IO_SET_QUICK_PLAY_MODE			(VDEC_IO_ELE_BASE + 0x0D)
#define VDEC_IO_SET_STILL_FRAME_MODE			(VDEC_IO_ELE_BASE + 0x0E)
#define VDEC_IO_SET_FB_COST_DOWN_NUM		(VDEC_IO_ELE_BASE + 0x0F)
#define VDEC_IO_SET_MODULE_INFO                 		(VDEC_IO_ELE_BASE + 0x10)

#define VDEC_IO_SET_ROTATION_ANGLE			(VDEC_IO_ELE_BASE + 0x100)//!<设置旋转的角度
#define VDEC_IO_SET_RGB_OUTPUT_FLAG			(VDEC_IO_ELE_BASE + 0x101)//!<设置RGB输出

#define	VDEC_DETACH		10
#define	VDEC_CLOSED		11
#define	VDEC_DECODING		VDEC27_STARTED
#define	VDEC_REVERSING	12
#define	VDEC_PAUSED		VDEC27_PAUSED
#define	VDEC_STOPPED		VDEC27_STOPPED	


/*! @enum VDecCBType
@brief vdec 模块的回调函数类型。
*/
enum VDecCBType
{
	VDEC_CB_SETTING_CHG = 0, //!< 未实现。
	VDEC_CB_REQ_DATA, //!< 未实现。
	VDEC_CB_STOP, //!< 未实现。
	VDEC_CB_FINISH_CUR_PIC, //!< 未实现。
	VDEC_CB_FINISH_I_FRAME, //!< 未实现。
	VDEC_CB_FINISH_TARGET_FRAME, //!< 未实现。
	VDEC_CB_FIRST_SHOWED, //!< 成功显示第一帧
	VDEC_CB_MODE_SWITCH_OK, //!< 未实现。
	VDEC_CB_BACKWARD_RESTART_GOP, //!< 在DVR 回退应用中重传视频数据
	VDEC_CB_OUTPUT_MODE_CHECK, //!< 未实现。
	VDEC_CB_FIRST_HEAD_PARSED, //!< 解析到第一个头信息。
	VDEC_CB_MONITOR_FRAME_VBV, //!< 未实现。
	VDEC_CB_FF_FB_SHOW,
	VDEC_CB_FIRST_I_DECODED,
	VDEC_CB_MONITOR_VDEC_START,
	VDEC_CB_MONITOR_VDEC_STOP,
};

/*! @enum VDecRotationAngle
@brief vdec 模块的旋转角度。
*/
enum VDecRotationAngle
{
	VDEC_ANGLE_0,
	VDEC_ANGLE_90,
	VDEC_ANGLE_180,
	VDEC_ANGLE_270,

	VDEC_ANGLE_MAX,
};

//! @typedef VDecCBFunc
//! @brief video模块的回调函数类型。
typedef void (*VDecCBFunc)(UINT32 uParam1, UINT32 uParam2);

/*! @struct vdec_io_reg_callback_para
@brief VDEC_IO_REG_CALLBACK注册回调函数相关的参数定义。
*/
struct vdec_io_reg_callback_para
{
	enum VDecCBType eCBType;//!< 待注册回调函数的类型。
	VDecCBFunc pCB; //!< 待注册的回调函数指针。
	UINT32 monitor_rate;
};

/*! @struct vdec_frm_output_format
@brief decv输出格式。
*/
struct vdec_frm_output_format
{
	// VE config
	BOOL h_scale_enable;
	UINT32 h_scale_factor;//0:reserved, 1: Y h_scale only, 2: Y,C h_scale

	BOOL dview_enable;
	UINT32 dv_h_scale_factor;//0:no dview, 1: 1/2 dview, 2: 1/4 dview, 3: 1/8 dview
	UINT32 dv_v_scale_factor;//0:no dview, 1: 1/2 dview, 2: 1/4 dview, 3: 1/8 dview
	
	UINT32 dv_mode; 

	//DE config
	UINT32 field_src;//0: both fields, 1:top only field
	UINT32 scaler_src;//0: frame base, 1: field base
	UINT32 vpp_effort;//0:high, 1: middle, 2: low, 3:very low
};

typedef void (* VDEC_BEYOND_LEVEL)(void);

/*! @struct vdec_device
@brief decv设备类型定义。
*/
struct vdec_device
{
	struct vdec_device  *next;  //!< 内部使用。
    	UINT32 type;  //!< 内部使用。
	INT8 name[32]; //!< 内部使用。
	UINT8  flags; //!< 内部使用。

	UINT8 index; //!< 内部使用。
	void *top_info; //!< 内部使用。
	void *priv; //!< 内部使用。

	RET_CODE	(*open)(struct vdec_device *);
	RET_CODE   	(*close)(struct vdec_device *);
	RET_CODE   	(*start)(struct vdec_device *);
	RET_CODE   	(*stop)(struct vdec_device *,BOOL,BOOL);
	RET_CODE 	(*vbv_request)(struct vdec_device *, UINT32, void **, UINT32 *, struct control_block *);
	void 		(*vbv_update)(struct vdec_device *, UINT32);
	RET_CODE 	(*set_output)(struct vdec_device *,  enum VDecOutputMode, struct VDecPIPInfo *, struct MPSource_CallBack *, struct PIPSource_CallBack *);
	RET_CODE 	(*switch_pip)(struct vdec_device *, struct Position *);
	RET_CODE 	(*switch_pip_ext)(struct vdec_device *, struct Rect*);
	RET_CODE 	(*sync_mode)(struct vdec_device *,  UINT8,UINT8);
	RET_CODE   	(*extrawin_store_last_pic)(struct vdec_device *, struct Rect *);
	RET_CODE   	(*ioctl)(struct vdec_device *, UINT32 , UINT32);
	/* for advanced play */
	RET_CODE 	(*playmode)(struct vdec_device *, enum VDecDirection , enum VDecSpeed );
	RET_CODE 	(*step)(struct vdec_device *);
	RET_CODE 	(*dvr_pause)(struct vdec_device *);
	RET_CODE 	(*dvr_resume)(struct vdec_device *);
	RET_CODE 	(*profile_level)(struct vdec_device *,  UINT8,VDEC_BEYOND_LEVEL);	
	RET_CODE 	(*dvr_set_param)(struct vdec_device *, struct VDec_DvrConfigParam );
        /* end */
	RET_CODE	(*internal_set_output)(struct vdec_device *,  enum VDecOutputMode, struct VDecPIPInfo *, struct MPSource_CallBack *, struct PIPSource_CallBack *);
	RET_CODE	(*internal_set_frm_output_format)(struct vdec_frm_output_format *);
	void 		(*de_hw_using)(struct vdec_device *, UINT8, UINT8, UINT8);

};


/*! @enum video_decoder_type
@brief vdec 解码器类型。
*/
enum video_decoder_type
{
	MPEG2_DECODER = 0,
	H264_DECODER,
	AVS_DECODER
};




/*!
@brief 打开vdec 模块。
@param[in] dev 指向vdec模块 的指针。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_open(struct vdec_device *dev);

/*!
@brief 关闭vdec 模块。
@param[in] dev 指向vdec模块 的指针。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_close(struct vdec_device *dev);

/*!
@brief 启动vdec 模块的解码工作。
@param[in] dev 指向vdec模块 的指针。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_start(struct vdec_device *dev);

/*!
@brief 停止vdec 模块的解码工作。
@param[in] dev 指向vdec 模块 的指针。
@param[in] bclosevp 关闭dis 模块的标志。非0 表示关闭，反之则不关闭。
@param[in] bfillblack 填黑dis 内存的标志。非0 表示填黑，反之则不填黑。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_stop(struct vdec_device *dev,BOOL bclosevp,BOOL bfillblack);

/*!
@brief 向vdec 模块申请写入的内存区域。
@param[in] dev 指向vdec模块 的指针。
@param[in] uSizeRequested 期望申请到的内存区域 长度。
@param[out] ppVData  申请到的内存区域的地址。
@param[out] puSizeGot 实际申请到的内存 长度。
@param[in] ctrl_blk 和写入数据相关的控制信息，包括同步信息等。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_vbv_request(void *dev, UINT32 uSizeRequested, void ** ppVData, UINT32 * puSizeGot, struct control_block * ctrl_blk);

/*!
@brief 更新vdec模块的写入数据指针。
@param[in] dev 指向vdec模块 的指针。
@param[in] uDataSize 成功写入数据的长度。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
void vdec_vbv_update(void *dev, UINT32 uDataSize);

/*!
@brief 设置vdec 模块 的屏幕输出模式，包括全屏和预览模式。
@param[in] dev 指向vdec模块 的指针。
@param[in] eMode vdec 模块的工作模式。
@param[in] pInitInfo 工作模式的初始化信息。
@param[out] pMPCallBack 主图层相关的回调函数。
@param[out] pPIPCallBack 附图层相关的回调函数。目前并未实现。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_set_output(struct vdec_device *dev, enum VDecOutputMode eMode,struct VDecPIPInfo *pInitInfo, struct MPSource_CallBack *pMPCallBack, struct PIPSource_CallBack *pPIPCallBack);

/*!
@brief 设置vdec 模块的音视频同步模式。
@param[in] dev 指向vdec模块 的指针。
@param[in] uSyncMode 同步模式，包括VDEC_SYNC_PTS 和VDEC_SYNC_FREERUN 。
@param[in] uSyncLevel  同步级别。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_sync_mode(struct vdec_device *dev, UINT8 uSyncMode,UINT8 uSyncLevel);

/*!
@brief vdec 模块的io contorl 操作。
@param[in] dev 指向vdec模块 的指针。
@param[in] io_code 操作 的命令类型。参考VDEC_IO_XX定义。
@param[in,out] param 操作的参数，根据不同的命令会有不同的参数。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
@note  IO命令dwCmd 介绍:
<table class="doxtable"  width="800" border="1" style="border-collapse:collapse;table-layout:fixed;word-break:break-all;" >
  <tr>
    <th width="200">命令</th>
    <th width="200">参数</th>
    <th width="80">传输特性</th>
    <th width="320">备注</th>
  </tr>

  <tr align="center">
    <td>VDEC_IO_GET_STATUS</td>    
    <td>struct VDec_StatusInfo *</td>    
    <td>输出</td>
    <td>读取状态信息</td>
  </tr>

  <tr align="center">
    <td>VDEC_IO_GET_MODE</td>    
    <td>enum TVSystem *</td>    
    <td>输出</td>
    <td>读取视频源的模式</td>
  </tr>

  <tr align="center">
    <td>VDEC_IO_GET_OUTPUT_FORMAT</td>    
    <td>BOOL *</td>    
    <td>输出</td>
    <td>读取视频源的行扫描信息，隔行或者逐行</td>
  </tr>  

  <tr align="center">
    <td>VDEC_IO_FILL_FRM</td>    
    <td>struct YCbCrColor *</td>    
    <td>输入</td>
    <td>向视频缓冲区写入特定颜色</td>
  </tr>  

  <tr align="center">
    <td>VDEC_IO_REG_CALLBACK</td>    
    <td>struct vdec_io_reg_callback_para *</td>    
    <td>输入</td>
    <td>注册回调函数</td>
  </tr>  

  <tr align="center">
    <td>VDEC_IO_SET_OUTPUT_RECT</td>    
    <td>struct VDecPIPInfo *</td>    
    <td>输入</td>
    <td>设置预览模式相关的参数</td>
  </tr>  

 <tr align="center">
    <td>VDEC_IO_COLORBAR</td>    
    <td>空</td>    
    <td>输入</td>
    <td>向视频缓冲区写入彩条信号</td>
  </tr>  
*/
RET_CODE vdec_io_control(struct vdec_device *dev, UINT32 io_code, UINT32 param);

/*!
@brief 检查当前运行的视频解码器的类型。
@return BOOL 。
@retval  0 当前的视频解码类型为MPEG2。
@retval  !0 当前的视频解码类型为H.264。
*/
BOOL is_cur_decoder_avc(void);

/*!
@brief 得到当前运行的视频解码器的设备指针。
@return struct vdec_device *。
@retval  !NULL 获得的vdec 模块指针。 
@retval  NULL 申请 失败，参数错误或状态错误。
*/
struct vdec_device * get_selected_decoder(void);

/*!
@brief 设置视频解码器的类型。
@param[in] select 类型标志。非0表示MPEG2, 0表示H.264
@param[in] in_preview vdec模式的工作模式。非0表示预览模式，0 表示全拼模式。
*/
void h264_decoder_select(int select, BOOL in_preview);

/*!
@brief 设置视频解码器的类型新接口，支持MPEG2，H.264，AVS。
@param[in] select 类型标志。0表示MPEG2, 1表示H.264，2表示AVS。
@param[in] in_preview vdec模式的工作模式。非0表示预览模式，0 表示全拼模式。
*/
void video_decoder_select(enum video_decoder_type select, BOOL in_preview);

/*!
@brief 检查当前运行的视频解码器的类型。
@return enum 。
@retval  0 当前的视频解码类型为MPEG2。
@retval  1 当前的视频解码类型为H.264。
@retval  2 当前的视频解码类型为AVS。
*/
enum video_decoder_type get_current_decoder(void);


/*!
@brief 在DVR 应用中播放加密码流。
@param[in] dev 指向vdec模块 的指针。
@param[in] param 加密码流的标志。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_dvr_set_param(struct vdec_device *dev, struct VDec_DvrConfigParam param);
	
/*!
@brief 在DVR 应用中暂停vdec 模块的解码工作。
@param[in] dev 指向vdec模块 的指针。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_dvr_pause(struct vdec_device *dev);

/*!
@brief 在DVR 应用中恢复vdec 模块的解码工作。
@param[in] dev 指向vdec模块 的指针。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_dvr_resume(struct vdec_device *dev);

/*!
@brief 在DVR 应用中设置vdec 模块的工作模式。
@param[in] dev 指向vdec模块 的指针。
@param[in] direction 视频播放的方向，选择前进或者后退方式。
@param[in] speed 视频播放的速度。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_playmode(struct vdec_device *dev, enum VDecDirection direction, enum VDecSpeed speed);

/*!
@brief 在DVR 应用中按照步进的方式播放视频。
@param[in] dev 指向vdec模块 的指针。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vdec_step(struct vdec_device *dev);

/*!
@}
*/


#endif

