#ifndef __HDMI_DEV_H__
#define __HDMI_DEV_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <osal/osal.h> // for OSAL_ID

/*! @addtogroup hdmi_dev
 *  @{
 */
 
#define HDMI_ASSERT			ASSERT
//#define HDMI_DEGUB_PRINT	1
//#define S3602A_IC_PATCH	1

#define	PRI_HDCP_DEV_ID	0x74
#define	SND_HDCP_DEV_ID	0x76
#define	EDID_DEV_ID		0xA0

#define	HLD_MAX_NAME_SIZE 	16


/*!@struct ifm_pkt_header
@brief HDMI Infoframe Packet Header structure
*/
struct ifm_pkt_header
{
	UINT8 InfoFram_type;
	UINT8 InfoFram_version;
	UINT8 InfoFram_length;
};

/*!@struct ifm_packet
@brief HDMI Infoframe Packet structure
*/
struct ifm_packet
{
	struct ifm_pkt_header header;
	UINT8 *payload;
};

/*!@struct data_island_pkt
@brief HDMI Data Island Packet structure
*/
struct data_island_pkt
{
	struct ifm_packet	*avi_infoFrame;
	struct ifm_packet	*audio_infoFrame;
	struct ifm_packet	*mpeg_infoFrame;
	struct ifm_packet	*spd_infoFrame;
	struct ifm_packet	*acp_packet;
	struct ifm_packet	*isrc1_packet;
	struct ifm_packet	*isrc2_packet;
};

struct HDMI_NCTS
{
	UINT8 N_data[3];
	UINT8 CTS_data[3];
};

/*!@struct config_hdmi_parm
@brief reserved, app config HDMI parameters
*/
struct config_hdmi_parm
{
	UINT8 *spd_vendor_name;			/**<  reserved */
	UINT8 *spd_product_desc;		/**<  reserved */
	UINT8  cm_scl;					/**<  reserved */
	UINT8  cm_sda;					/**<  reserved */
	UINT8 *cm_password;				/**<  reserved */
	UINT8 *cm_secretseed;			/**<  reserved */
	BOOL   hdcp_disable;			/**<  reserved */
	UINT8 *hdcp_cstm_key;			/**<  reserved */
	BOOL   otp_ce_load_hdcp_key;	/**<  reserved */						
	UINT32 i2c_for_eddc;			/**<  reserved */
};


enum HDMI_IO_CMD_TYPE
{
	HDMI_CMD_REG_CALLBACK = 1,
	HDMI_CMD_DEL_CALLBACK,
	HDMI_CMD_SET_TMDS_DRV_CURRENT,
	HDMI_CMD_INTERFACE_MODE,

	HDMI_CMD_AV_MUTE,
	HDMI_CMD_GET_MUTE_STA,
	HDMI_CMD_SET_HDCP_EN,
	HDMI_CMD_GET_EDID_RES,
	HDMI_CMD_SWITCH_MDI_INT,
	HDMI_CMD_RST_AUD_CH,
	HDMI_CMD_AUD_INTERFACE,
};

enum HDMI_TMDS_DRV_CURRENT   //TMDS driver current 9ma,9.5ma,10ma,10.5ma,11ma,11.5ma.
{
    HDMI_DRV_CUR_8MA = 0,
	HDMI_DRV_CUR_85MA,
    HDMI_DRV_CUR_9MA,   
    HDMI_DRV_CUR_95MA,
    HDMI_DRV_CUR_10MA,
    HDMI_DRV_CUR_105MA,
    HDMI_DRV_CUR_11MA,
    HDMI_DRV_CUR_115MA,
    HDMI_DRV_CUR_12MA,
    HDMI_dRV_CUR_125MA,
    HDMI_DRV_CUR_13MA,
    HDMI_DRV_CUR_135MA,
    HDMI_DRV_CUR_14MA,
    HDMI_DRV_CUR_145MA,
    HDMI_DRV_CUR_15MA,
    HDMI_DRV_CUR_155MA,
    HDMI_DRV_CUR_16MA,
};

enum HDMI_AUD_INTERFACE
{
	HDMI_AUD_AUTO = 0, 	//default value, by EDID, if HDMI Sink support decoder, switch to SPDIF out otherwise switch to LPCM out.
	HDMI_AUD_LPCM,		// Fix LPCM output
	HDMI_AUD_SPDIF,		// Fix output the same with SPDIF interface.
	HDMI_AUD_SNDDRV,
};

enum HDMICBType
{
	HDMI_CB_EDID_READY = 0,
	HDMI_CB_HOT_PLUG_OUT,
	HDMI_CB_HOT_PLUG_IN,
	HDMI_CB_CEC_MESSAGE,
	HDMI_CB_DBG_MSG,
};

/*!@enum HDMIEvent_E
@brief hdmi sink event for call back function
*/
typedef enum
{
    HDMI_RECEIVER_PLUGIN,	/**< HDMI sink plug in */
    HDMI_RECEIVER_PLUGOUT	/**< HDMI sink plug out */
}HDMIEvent_E;


/*!
@brief hdmi call back function for edid access
*/
typedef void (*HDMI_EDID_CBFunc)(void);
/*!
@brief hdmi call back func for hotplug in/out event
*/
typedef void (*HDMI_HTPLG_CBFunc)(void);
/*!
@brief hdmi call back func for cec
*/
typedef void (*HDMI_CEC_CBFunc)(UINT8*, UINT8);	// CEC Feature

/*!
@brief hdmi call back function
@param[in] eEvt: event type. Please refer to enum HDMIEvent_E.
@param[in] nHdmiIndex: hdmi device index.
@param[in] pvEventData: A pointer to event data
@param[in] pvUserData: A pointer to user data
*/
typedef void (*HDMI_CBFunc)(HDMIEvent_E eEvt, int nHdmiIndex, void *pvEventData, void *pvUserData);


/*!@struct hdmi_device
@brief HDMI device structure
*/
struct hdmi_device
{
	struct	hdmi_device   *next;				/**< Next hdmi device structure  */
	UINT32	type;								/**< reserved, Interface hardware type */
	INT8	name[HLD_MAX_NAME_SIZE];			/**< Device name */
	UINT32	flags;								/**< Interface flags, status and ability */
	int 	net_id;								/**< hdmi port id of netlink */
	OSAL_ID hdm_mon_tid;						/**< hdmi task id for monitor hdmi event */
	HDMI_EDID_CBFunc	cb_edid_ready;			/**< hdmi call back func for edid access */
	HDMI_HTPLG_CBFunc	cb_hotplug_out;			/**< hdmi call back func for hotplug in event */
	HDMI_HTPLG_CBFunc	cb_hotplug_in;			/**< hdmi call back func for hotplug out event */
	HDMI_CEC_CBFunc		cb_cec_receive;			/**< hdmi call back func for cec */
	HDMI_CBFunc			cb_fn;					/**< hdmi call back func */
	void 				*cb_fn_data;			/**< hdmi call back func data pointer */
	int		handle;								/**< A handle of hdmi device */
	void	*priv;								/**< reserved, A pointer to private data */
	INT32	(*init)(struct config_hdmi_parm *); /**< reserved, A function pointer for HDMI Device Initialization*/
	INT32	(*open)(struct hdmi_device *);		/**< A function pointer for HDMI Device Open*/
	INT32	(*close)(struct hdmi_device *);		/**< A function pointer for HDMI Device Close*/	
	INT32	(*start_tx)(struct hdmi_device *, struct data_island_pkt *, UINT8, struct HDMI_NCTS *);	/**< reserved, A function pointer for HDMI Device Start Transmit*/
	INT32	(*stop_tx)(struct hdmi_device *);	/**< reserved, A function pointer for HDMI Device Stop Transmit*/
	INT32	(*io_control)(struct hdmi_device *, UINT32 HDMI_IO_CMD_TYPE, UINT32, UINT32); /**< reserved, A function pointer for HDMI Device I/O control*/	
};

/*!
@}
*/

#ifdef __cplusplus
	}
#endif

#endif // end of __HDMI_DEV_H__

