#ifndef	__HDMI_API_H__
#define __HDMI_API_H__

#include <adr_retcode.h>
#include <adr_mediatypes.h>
#include <osal/osal.h>
#include <hld/adr_hld_dev.h>
#include <hld/bus/hdmi/m36/hdmi_dev.h>


#ifdef __cplusplus
extern "C" {
#endif
/*! @addtogroup hdmi_api
 *  @{
 */


/*!@enum HDMI_API_RES
@brief An enum define HDMI Resolutions.
*/
enum HDMI_API_RES
{
	HDMI_RES_INVALID = 0,
	HDMI_RES_480I,
	HDMI_RES_480P,
	HDMI_RES_576I,
	HDMI_RES_576P,
	HDMI_RES_720P_50,
	HDMI_RES_720P_60,
	HDMI_RES_1080I_25,
	HDMI_RES_1080I_30,
	HDMI_RES_1080P_24,
	HDMI_RES_1080P_25,
	HDMI_RES_1080P_30,
	HDMI_RES_1080P_50,
	HDMI_RES_1080P_60,
	HDMI_RES_4096X2160_24,
	HDMI_RES_3840X2160_24,
	HDMI_RES_3840X2160_25,
	HDMI_RES_3840X2160_30,
};

/*!@enum EDID_AUD_FMT_CODE
@brief A enum define audio information in EDID
*/
enum EDID_AUD_FMT_CODE
{
	EDID_AUDIO_LPCM 				= 0x0001,
	EDID_AUDIO_AC3					= 0x0002,
	EDID_AUDIO_MPEG1				= 0x0004,
	EDID_AUDIO_MP3					= 0x0008,
	EDID_AUDIO_MPEG2				= 0x0010,
	EDID_AUDIO_AAC					= 0x0020,
	EDID_AUDIO_DTS					= 0x0040,
	EDID_AUDIO_ATRAC				= 0x0080,
	EDID_AUDIO_ONEBITAUDIO			= 0x0100,
	EDID_AUDIO_DD_PLUS				= 0x0200,
	EDID_AUDIO_DTS_HD				= 0x0400,
	EDID_AUDIO_MAT_MLP				= 0x0800,
	EDID_AUDIO_DST					= 0x1000,
	EDID_AUDIO_WMAPRO				= 0x2000,
};

/*!@enum HDMI_API_DEEPCOLOR
@brief An enum define HDMI DeepColor.
*/
enum HDMI_API_DEEPCOLOR
{	
	HDMI_DEEPCOLOR_24 = 0,	
	HDMI_DEEPCOLOR_30,	
	HDMI_DEEPCOLOR_36,	
	HDMI_DEEPCOLOR_48,
};

/*!@enum HDMI_API_COLOR_SPACE
@brief An enum define HDMI ColorSpace.
*/
enum HDMI_API_COLOR_SPACE
{
	HDMI_RGB = 0,
	HDMI_YCBCR_422,
	HDMI_YCBCR_444,
};

/*!@enum HDMILinkStatus_E
@brief A enum define HDMI Link Status
*/
typedef enum
{
	HDMI_STATUS_UNLINK = 0x01,				/**< HDMI not link */
	HDMI_STATUS_LINK_HDCP_SUCCESSED = 0x02,
	HDMI_STATUS_LINK_HDCP_FAILED = 0x04,
	HDMI_STATUS_LINK_HDCP_IGNORED = 0x08,
	HDMI_STATUS_MAX = 0x10,
	HDMI_STATUS_LINK = 0x20,
}HDMILinkStatus_E;

/*!
@brief api function from AP to open hdmi driver.
@param[in] dev: A pointer to hdmi device.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE hdmi_tx_open(struct hdmi_device *dev);

/*!
@brief api function from AP to attach hdmi driver.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE hdmi_tx_attach (void);

/*!
@brief api function from AP to close hdmi driver.
@param[in] dev: A pointer to hdmi device.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE hdmi_tx_close(struct hdmi_device *dev);

/*!
@brief api function from AP to detach hdmi driver.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE hdmi_tx_detach (void);

/*!
@brief api function from AP to get edid support video color format.
@param[in] dev: A pointer to hdmi device.
@param[in] format: A pointer to video color format. Please refer to enum PicFmt.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_get_edid_video_format(struct hdmi_device *dev, enum PicFmt *format);

/*!
@brief api function from AP to get video native resolution.
@param[in] dev: A pointer to hdmi device.
@param[in] res: video reslution. Please refer to enum HDMI_API_RES.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_get_edid_video_resolution(struct hdmi_device *dev, enum HDMI_API_RES *res);

/*!
@brief api function from AP to get edid all video resolution.
@param[in] dev: A pointer to hdmi device.
@param[in] native_res_index: A pointer to native resolution index.
@param[in] video_res: video reslution. Please refer to enum HDMI_API_RES.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_get_edid_all_video_resolution(struct hdmi_device *dev, UINT32 *native_res_index, enum HDMI_API_RES *video_res);

/*!
@brief api function from AP to get edid prefer audio coding.
@param[in] dev: A pointer to hdmi device.
@param[in] aud_fmt: audio format. Please refer to enum EDID_AUD_FMT_CODE.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_get_edid_audio_out(struct hdmi_device *dev, enum EDID_AUD_FMT_CODE *aud_fmt);

/*!
@brief api function from AP to get edid all audio coding.
@param[in] dev: A pointer to hdmi device.
@param[in] aud_fmt: video reslution. Please refer to enum EDID_AUD_FMT_CODE.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_get_edid_all_audio_out(struct hdmi_device *dev, enum EDID_AUD_FMT_CODE *aud_fmt);

/*!
@brief api function from AP to set hdmi switch on or off.
@param[in] dev: A pointer to hdmi device.
@param[in] bOnOff: hdmi turn on if bOnOff = true; hdmi turn off if bOnOff = false;
*/
void api_set_hdmi_sw_onoff(struct hdmi_device *dev, BOOL bOnOff);

/*!
@brief api function from AP to get hdmi on/off status.
@param[in] dev: A pointer to hdmi device.
@return
@retval TRUE: hdmi turn on;
@retval FALSE: hdmi turn off;
*/
BOOL api_get_hdmi_sw_onoff(struct hdmi_device *dev);

/*!
@brief api function from AP to set hdmi hdcp authentication on/off.
@param[in] dev: A pointer to hdmi device.
@param[in] bOnOff: hdmi hdcp turn on if bOnOff = true; hdmi hdcp turn off if bOnOff = false;
*/
void api_set_hdmi_hdcp_onoff(struct hdmi_device *dev, BOOL bOnOff);

/*!
@brief api function from AP to get hdmi hdcp authentication on/off.
@param[in] dev: A pointer to hdmi device.
@return
@retval TRUE: hdmi hdcp on;
@retval FALSE: hdmi hdcp off;
*/
BOOL api_get_hdmi_hdcp_onoff(struct hdmi_device *dev);

/*!
@brief api function from AP to set hdmi hdcp key mem_sel.
@param[in] dev: A pointer to hdmi device.
@param[in] mem_sel: hdmi hdcp ce_load_key if mem_sel = true; hdmi hdcp se_load_key mem_sel = false;
*/
void api_set_hdmi_mem_sel(struct hdmi_device *dev, BOOL mem_sel);//add by ze for ce_load_key or sw_load_key

/*!
@brief api function from AP to set hdmi cec feature on/off.
@param[in] dev: A pointer to hdmi device.
@param[in] bOnOff: hdmi cec turn on if bOnOff = true; hdmi cec turn off if bOnOff = false;
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_set_hdmi_cec_onoff(struct hdmi_device *dev, BOOL bOnOff);

/*!
@brief api function from AP to get hdmi cec status on/off.
@param[in] dev: A pointer to hdmi device.
@return
@retval TRUE: hdmi cec on;
@retval FALSE: hdmi cec off;
*/
BOOL api_get_hdmi_cec_onoff(struct hdmi_device *dev);

/*!
@brief api function from AP to transmit cec message.
@param[in] dev: A pointer to hdmi device.
@param[in] message: A pointer to hdmi cec message;
@param[in] message_length: message length;
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_hdmi_cec_transmit(struct hdmi_device *dev, UINT8* message, UINT8 message_length);

/*!
@brief api function from AP to get the hdmi physical address for cec.
@param[in] dev: A pointer to hdmi device.
@return
@retval physical address of hdmi deivce;
@retval 0xFFFF if fail;
*/
UINT16	api_get_physical_address(struct hdmi_device *dev);

/*!
@brief api function from AP to set the hdmi logical address for cec.
@param[in] dev: A pointer to hdmi device.
@param[in] logical_address: logical address of hdmi device.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_set_logical_address(struct hdmi_device *dev, UINT8 logical_address);

/*!
@brief api function from AP to get the hdmi logical address for cec.
@param[in] dev: A pointer to hdmi device.
@return
@retval logical address of hdmi deivce;
@retval 0xFF if fail;
*/
UINT8 api_get_logical_address(struct hdmi_device *dev);

/*!
@brief api function from AP to get hdmi device counter.
@param[in] dev: A pointer to hdmi device.
@param[in] pnHdmiDeviceCount: A pointer to hdmi device counter.
@return
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_hdmi_get_dev_count(struct hdmi_device *dev, int * pnHdmiDeviceCount);

/*!
@brief api function from AP to set hdmi vendor name.
@param[in] dev: A pointer to hdmi device.
@param[in] vendor_name: A pointer to hdmi vendor name.
@param[in] length: length of vendor name.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_hdmi_set_vendor_name(struct hdmi_device *dev, unsigned char *vendor_name, unsigned char length);

/*!
@brief api function from AP to set hdmi product description.
@param[in] dev: A pointer to hdmi device.
@param[in] product_desc: A pointer to hdmi product description.
@param[in] length: length of product description.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_hdmi_set_product_desc(struct hdmi_device *dev, unsigned char *product_desc, unsigned char length);

/*!
@brief api function from AP to get hdmi vendor name.
@param[in] dev: A pointer to hdmi device.
@param[in] vendor_name: A pointer to hdmi vendor name.
@param[in] length: A pointer to length of vendor name.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_hdmi_get_vendor_name(struct hdmi_device *dev, unsigned char *vendor_name, unsigned char *length);

/*!
@brief api function from AP to get hdmi product description.
@param[in] dev: A pointer to hdmi device.
@param[in] product_desc: A pointer to hdmi product description.
@param[in] length:  A pointer to length of product description.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_hdmi_get_product_desc(struct hdmi_device *dev, unsigned char *product_desc, unsigned char *length);

/*!
@brief api function from AP to get hdmi link status.
@param[in] dev: A pointer to hdmi device.
@param[in] link_status: A pointer to hdmi link_status. Please refer to enum HDMILinkStatus_E
@return
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_hdmi_get_link_status(struct hdmi_device *dev, int *link_status);

/*!
@brief api function from AP to register hdmi call back function.
@param[in] dev: A pointer to hdmi device.
@param[in] cb_func: A pointer to call back function;
@param[in] pvUserData: A pointer to user data.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_hdmi_reg_callback(struct hdmi_device *dev, void *cb_func, void *pvUserData);

/*!
@brief api function from AP to delete hdmi call back function.
@param[in] dev: A pointer to hdmi device.
@param[in] cb_func: A pointer to call back function;
@param[in] pvUserData: A pointer to user data.
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_hdmi_del_callback(struct hdmi_device *dev, void *cb_func, void *pvUserData);

/*!
@brief api function from AP to set hdmi audio on/off.
@param[in] dev: A pointer to hdmi device.
@param[in] bOnOff: hdmi audio turn on if bOnOff = true; hdmi audio turn off if bOnOff = false;
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_hdmi_audio_set_onoff(struct hdmi_device * dev, BOOL bOnOff);

/*!
@brief api function from AP to get hdmi audio on/off status.
@param[in] dev: A pointer to hdmi device.
@return
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/
RET_CODE api_hdmi_audio_get_onoff(struct hdmi_device * dev, int * bOnOff);


/*!
@brief api function from AP to get hdmi 3d present status.
@param[in] dev: A pointer to hdmi device.
@return
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/

RET_CODE api_hdmi_get_3d_present(struct hdmi_device *dev, int *present);

/*!
@brief api function from AP to get hdmi edid manufacturer name.
@param[in] dev: A pointer to hdmi device.
@return
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/

RET_CODE api_hdmi_get_edid_manufacturer(struct hdmi_device *dev, unsigned char * m_name);

/*!
@brief api function from AP to get hdmi edid monitor name.
@param[in] dev: A pointer to hdmi device.
@return
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/

RET_CODE api_hdmi_get_edid_monitor(struct hdmi_device *dev, unsigned char * m_name);

/*!
@brief api function from AP to set hdmi deep color.
@param[in] dev: A pointer to hdmi device.
@return
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/

RET_CODE api_hdmi_set_deep_color(struct hdmi_device *dev, enum HDMI_API_DEEPCOLOR dp_mode);

/*!
@brief api function from AP to get hdmi deep color.
@param[in] dev: A pointer to hdmi device.
@return
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/

RET_CODE api_hdmi_get_deep_color(struct hdmi_device *dev, enum HDMI_API_DEEPCOLOR *dp_mode);

/*!
@brief api function from AP to get hdmi edid block data.
@param[in] dev: A pointer to hdmi device.
@return
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/

RET_CODE api_hdmi_get_edid_block_data(struct hdmi_device *dev, int num, unsigned char *data);

/*!
@brief api function from AP to set hdmi phy clock onoff.
@param[in] dev: A pointer to hdmi device.
@return
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/

RET_CODE api_hdmi_set_phy_clock_onoff(struct hdmi_device *dev, BOOL bOnOff);

/*!
@brief api function from AP to set hdmi color space.
@param[in] dev: A pointer to hdmi device.
@return
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/

RET_CODE api_hdmi_set_color_space(struct hdmi_device *dev, enum HDMI_API_COLOR_SPACE color_space);

/*!
@brief api function from AP to get hdmi color space.
@param[in] dev: A pointer to hdmi device.
@return
@return RET_CODE
@retval RET_SUCCESS;
@retval RET_FAILURE;
*/

RET_CODE api_hdmi_get_color_space(struct hdmi_device *dev, enum HDMI_API_DEEPCOLOR *color_space);
/*!
@}
*/
#ifdef __cplusplus
}
#endif
#endif // end of __HDMI_API_H__
