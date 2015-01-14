/*========================================================================================
 *
 * Copyright (C) 2011 ALi Shanghai Corp.
 *
 * Description:
 *
 * History
 *
 *   Date	    Author		Comment
 *   ========	===========	========================================
 *
 *=========================================================================================*/
 
#ifndef _LIB_PUB_H_
#define _LIB_PUB_H_

#include <adr_basic_types.h>
#include <adr_mediatypes.h>
#include <adr_sys_config.h>
#include <osal/osal.h>
#include <api/libpub/lib_as.h>
#include <hld/nim/adr_nim_dev.h>
#include <api/libpub/lib_frontend.h>

/*! @addtogroup ALi中间件
 *  @{
 */

/*! @addtogroup AMSCC
 *  @{
 */

/********************************************/
/*      libpub channel change notify        */
/********************************************/
#define CC_EVENT_PRE_PLAY	1
#define CC_EVENT_POST_PLAY	2
#define CC_EVENT_PRE_TUNER	3
#define CC_EVENT_POST_TUNER	4
#define CC_EVENT_PRE_STOP	5
#define CC_EVENT_POST_STOP	6

/********************************************/
/*        libpub cmd bit pattern            */
/********************************************/
#define LIBPUB_CMD_MAIN_TYPE_MASK	0xFF00
#define LIBPUB_CMD_SUB_TYPE_MASK	0x00FF

#define LIBPUB_CMD_NULL				0x0000
#define LIBPUB_CMD_CC				0x0100
#define LIBPUB_CMD_AS				0x0300


/****!! NOTE: 0x01xx is reserved for channel change!!***/
#define LIBPUB_CMD_CC_PLAY			0x0101
#define LIBPUB_CMD_CC_RESET			0x0102
#define LIBPUB_CMD_CC_STOP			0x0103
#define LIBPUB_CMD_CC_PAUSE_VIDEO	0x0104
#define LIBPUB_CMD_CC_RESUME_VIDEO	0x0105
#define LIBPUB_CMD_CC_SWITCH_APID	0x0106
#define LIBPUB_CMD_CC_SWITCH_ACH	0x0107
#define LIBPUB_CMD_CC_SHOW_LOGO		0x0108
#define LIBPUB_CMD_CC_SET_FRONTEND	0x0109
#define LIBPUB_CMD_CC_RESUME_LOGO	0x010A


/****!! NOTE: 0x03xx is reserved for channel scan!!*****/
#define LIBPUB_CMD_AS_START		0x0301
#define LIBPUB_CMD_AS_STOP		0x0302


/****!!channel change cmd bit!!****/
#define CC_CMD_NULL					0x00000000
#define CC_CMD_CLOSE_VPO			0x00000001
#define CC_CMD_STOP_AUDIO			0x00000002
#define CC_CMD_STOP_VIDEO			0x00000004
#define CC_CMD_STOP_DMX				0x00000008
#define CC_CMD_FILL_FB				0x00000010
#define CC_CMD_START_AUDIO			0x00000020
#define CC_CMD_START_VIDEO			0x00000040
#define CC_CMD_START_DMX			0x00000080
#define CC_CMD_DMX_CHG_APID			0x00000100
#define CC_CMD_AUDIO_SWITCH_CHAN	0x00000200
#define CC_CMD_SET_FRONTEND			0x00000400
#define CC_CMD_PAUSE_VIDEO			0x00000800
#define CC_CMD_RESUME_VIDEO			0x00001000
#define CC_CMD_SET_ANTENNA			0x00002000
#define CC_CMD_SET_XPOND			0x00004000
#define CC_CMD_START_SI_MONITOR		0x00008000
#define CC_CMD_INFO_VPO_CHANCHNG	0x00100000
#define CC_CMD_STOP_MCAS_SERVICE	0x00200000
#define CC_CMD_CHANNEL_CHANGE		0x00400000


/********************************************/
/*          libpub flag bit patterns        */
/********************************************/
/* change channel related flag bit pattern */
#define LIBPUB_FLG_CC_PLAY_BIT			0x00000001
#define LIBPUB_FLG_CC_STOP_BIT			0x00000002
#define LIBPUB_FLG_CC_PAUSE_BIT			0x00000004
#define LIBPUB_FLG_CC_SWITCH_APID_BIT	0x00000008
#define LIBPUB_FLG_CC_SWITCH_ACH_BIT	0x00000010
#define LIBPUB_FLG_CC_LOGO_BIT			0x00000020

#define LIBPUB_CMD_DATA_SIZE				80

//! @struct libpub_cmd
//! @brief libpub传递消息。
struct libpub_cmd
{
    UINT16 cmd_type;
    UINT8 sync;
    UINT8 reserve;
    UINT32 cmd_bit;
    UINT32 para1;	
    UINT32 para2;
    UINT8 data1[LIBPUB_CMD_DATA_SIZE];
    UINT8 data2[LIBPUB_CMD_DATA_SIZE];
};

//! @struct pub_module_config
//! @brief libpub模块配置。
struct pub_module_config
{
	BOOL dm_enable;
};


#ifdef __cplusplus
extern "C" {
#endif 

//! @typedef libpub_cmd_handler
//! @brief libpub消息处理函数。
typedef void(*libpub_cmd_handler)(struct libpub_cmd *);

BOOL libpub_cmd_handler_register(UINT16 cmd_main_type, libpub_cmd_handler handler);
BOOL libpub_overlay_cmd_register(UINT16 repeat_cmd);

/*!
@brief libpub初始化。
@details 初始化PUB(CC及AS)模块，创建PUB task，注册CC、AS的播台、搜台等命令类型和处理函数等。在系统初始化的时候，如果是SDK模式，需要调用该函数初始化中间层的PUB(CC&AS)模块。如果是DDK模式，则不需要使用中间层的PUB模块。
@param[in] config config
@retval SUCCESS 总是成功
@retval ERR_XXX	失败
*/
RET_CODE libpub_init(struct pub_module_config *config);

INT32 libpub_send_cmd(struct libpub_cmd* cmd,UINT32 tmout);
INT32 libpub_wait_cmd_finish(UINT32 cmd_bit,UINT32 tmout);
void libpub_declare_cmd_finish(UINT32 cmd_bit);

void  chchg_init(void);

/*!
@brief 播放节目。
@details 异步方式播放一个节目。包括设置NIM、DMX、AV decoder等等。该函数向CC task发送一个消息，并将所有参数通过消息传给CC之后立刻返回。
@param[in] ft 参考lib_frontend.h中struct ft_frontend的定义：<br>
struct ft_frontend
{
    struct nim_device *nim;
    struct ft_antenna antenna;
    union ft_xpond xpond;
    struct ft_ts_route ts_route;
};<br>
其中，Cable使用到的参数有：<br>
	- nim：IN，所操作的前端NIM的设备句柄。一般Cable都只有1个NIM，可以通过dev_get_by_id(HLD_DEV_TYPE_NIM, 0(nim_id))获取NIM设备的句柄。
	- xpond：IN，参考frontend_set_nim()的介绍。
@param[in] param 这个结构里面的大多数参数都是和节目数据库的P_NODE对应的，但是有些参数可能需要转换一下。而其它参数则是播放节目的时候的控制参数，比如换台的时候，背景正在PVR录制节目，则不能停掉DMX等等。灰色部分表示有定义，但是Cable市场用不到的参数。
@param[in] blk_scrn 换台是否显示黑屏。<br>
	- TRUE - 显示黑屏
	- FALSE - 不显示黑屏，保留上一个节目的最后一帧画面。
@retval SUCCESS 总是成功
@retval ERR_XXX	失败
@note chchg_play_channel
*/
INT32 chchg_play_channel(struct ft_frontend *ft, struct cc_param *param, BOOL blk_scrn);

/*!
@brief 停止节目。
@details 停止播放一个节目，比如在进menu的时候，需要完全停止播放节目。该函数是一个同步的接口函数，向CC task发送停止播放节目的消息之后，会等到CC task处理完这个消息，并置一个flag之后，才会返回。
@param[in] es 参考chchg_play_channel()的介绍。
@param[in] dev_list 参考chchg_play_channel()的介绍。
@param[in] blk_scrn 停止播放时是否显示黑屏。<br>
		TRUE - 显示黑屏
		FALSE - 不显示黑屏，保留节目的最后一帧画面。
@retval SUCCESS 总是成功
@retval ERR_XXX	失败
*/
INT32 chchg_stop_channel(struct cc_es_info *es, struct cc_device_list *dev_list, BOOL blk_scrn);

/*!
@brief 暂停节目。
@details 暂停播放节目，Video画面暂停，但是Audio仍然还在播放和输出。
@param[in] vdec Video decoder句柄，正在播放的节目使用的Video decoder，可以是DECV0、DECV1或AVC Video DEC等。
@retval SUCCESS 总是成功
@retval ERR_XXX	失败
*/
INT32 chchg_pause_video(struct vdec_device *vdec);

/*!
@brief 恢复节目。
@details 恢复播放Video画面。对于直播节目来说，虽然暂停了播放节目，但实时节目码流仍然在发送，所以在恢复播放的时候，实际已经是当时的实时的画面了，不可能是从暂停点继续播放的画面。
@param[in] vdec Video decoder句柄，正在播放的节目使用的Video decoder，可以是DECV0、DECV1或AVC Video DEC等。
@retval SUCCESS 总是成功
@retval ERR_XXX	失败
*/
INT32 chchg_resume_video(struct vdec_device *vdec);

/*!
@brief 切换Audio码流。
@details 切换当前节目播放的Audio码流。一般如果一个节目有多个配音的话，就会有多个Audio ES流，用户可以选择切换不同语言的配音。底层只需要更改DMX的Audio Channel，和重置Audio DEC即可，其它Video/VPO等等都不需要动作。
@param[in] es 参考chchg_play_channel()的介绍。
@param[in] dev_list 参考chchg_play_channel()的介绍。<br>
    这两个参数，在切换Audio码流的时候，实际只用得到Audio DEC、Sound和DMX设备，Audio的PID、type、channel、volume等等，其它Video DEC等等是不需要的。
@retval SUCCESS 总是成功
@retval ERR_XXX	失败
*/
INT32 chchg_switch_audio_pid(struct cc_es_info *es, struct cc_device_list *dev_list);

/*!
@brief 切换Audio左右声道。
@details 切换音频的左右声道。
@param[in] snd Sound设备句柄。可以按如下代码获取：<br>
struct snd_device *snd = dev_get_by_id(HLD_DEV_TYPE_SND, 0)。
@param[in] audio_chan 可以取db_node.h定义的如下4个值：<br>
	- #define AUDIO_CH_L			0x00
	- #define AUDIO_CH_R			0x01
	- #define AUDIO_CH_STEREO		0x02
	- #define AUDIO_CH_MONO			0x03
@retval SUCCESS 总是成功
@retval ERR_XXX	失败
*/
INT32 chchg_switch_audio_chan(struct snd_device *snd, UINT8 audio_chan);

/*!
@brief 显示Logo。
@details 通过Videc DEC显示一个MPEG I帧的Logo图片。该函数也是一个同步显示logo的函数，即会等到CC收到消息并解码显示logo成功之后才会返回。
@param[in] plogo logo的地址和大小参数。struct cc_logo_info在lib_frondend.h有如下定义：<br>
struct cc_logo_info
{
    UINT8 *addr;
    UINT32 size;
};<br>
需要注意的是Logo的数据必须先load到memory，再调用该函数来显示logo，CC模块不会从flash上读取logo等数据。
@param[in] dev_list 参考chchg_play_channel()的介绍。Show Logo的时候会用到Video DEC、Audio DEC、DMX、VPO等设备。
@retval SUCCESS 总是成功
@retval ERR_XXX	失败
*/
INT32 chchg_show_logo(struct cc_logo_info *plogo, struct cc_device_list *dev_list);

typedef INT32 (*amscc_play_event)(UINT32 event, struct ft_frontend *ft, struct cc_param *param);
void amscc_reg_callback(amscc_play_event handle);

//to be deleted
#define DM_NIMCHECK_ON	6	
#define dm_set_onoff(a) do{PRINTF("DM (%d):________ <%s>\n", a, __FUNCTION__);}while(0)
 
#ifdef __cplusplus
}
#endif 

/*!
 * @}
 */

/*!
@}
*/

#endif


