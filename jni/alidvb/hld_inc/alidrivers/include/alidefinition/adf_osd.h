#ifndef __ADF_OSD__
#define __ADF_OSD__

#ifdef __cplusplus
extern "C" {
#endif

#include "adf_basic.h"

/*! @addtogroup osd
 *  @{
 */

/*! @enum OSDSys
@brief 输出的电视制式。和Scale配合使用。
*/
enum OSDSys
{
	OSD_PAL = 0,
	OSD_NTSC
};

/*! @enum OSDColorMode
@brief 颜色格式。
*/
enum OSDColorMode{
	OSD_4_COLOR =	0,
	OSD_16_COLOR,
	OSD_256_COLOR,
	OSD_16_COLOR_PIXEL_ALPHA,
	OSD_HD_ACLUT88,
	OSD_HD_RGB565,
	OSD_HD_RGB888,
	OSD_HD_RGB555,
	OSD_HD_RGB444,
	OSD_HD_ARGB565,
	OSD_HD_ARGB8888,
	OSD_HD_ARGB1555,
	OSD_HD_ARGB4444,
	OSD_HD_AYCbCr8888,
	OSD_HD_YCBCR888,
	OSD_HD_YCBCR422,
	OSD_HD_YCBCR422MB,
	OSD_HD_YCBCR420MB,
	OSD_COLOR_MODE_MAX
};

/*! @enum CLIPMode
@brief CLIP模式。
*/
enum CLIPMode
{
	CLIP_INSIDE_RECT = 0,
	CLIP_OUTSIDE_RECT,
	CLIP_OFF
};

#define	OSDDRV_RGB			0x00   //!< RGB 颜色表。ARGB   byte order is: {B, G , R , A}, A in [0, 255]
#define	OSDDRV_YCBCR			0x01   //!< YUV 颜色表。AYCbCr byte order is: {Y, Cb, Cr, A}, A in [0, 15 ]

#define	OSDDRV_OFF				0x00 //!< 显示层关闭。
#define	OSDDRV_ON					0x01 //!< 显示层打开。


/**************** the position and size of OSD frame buffer********************/
#define	OSD_MIN_TV_X		0x20
#define	OSD_MIN_TV_Y		0x10
#define	OSD_MAX_TV_WIDTH	0x2B0
#define	OSD_MAX_TV_HEIGHT	0x1F0 //old value 0x1E0


#define P2N_SCALE_DOWN  	0x00
#define N2P_SCALE_UP		0x01
#define OSD_SCALE_MODE		P2N_SCALE_DOWN


//#define P2N_SCALE_IN_NORMAL_PLAY
#define P2N_SCALE_IN_SUBTITLE_PLAY

// scaler
#define OSD_VSCALE_OFF          0x00
#define OSD_VSCALE_TTX_SUBT     0x01
#define OSD_VSCALE_GAME         0x02
#define OSD_VSCALE_DVIEW        0x03
#define OSD_HDUPLICATE_ON       0x04
#define OSD_HDUPLICATE_OFF      0x05
#define OSD_OUTPUT_1080         0x06 // 720x576(720x480)->1920x1080
#define OSD_OUTPUT_720          0x07 // 720x576(720x480)->1280x720
#define OSD_HDVSCALE_OFF        0x08 // 1280x720->720x576(720x480)
#define OSD_HDOUTPUT_1080       0x09 // 1280x720->1920x1080
#define OSD_HDOUTPUT_720        0x0A // 1280x720->1280x720
#define OSD_SET_SCALE_MODE      0x0B // filter mode or duplicate mode
#define OSD_SCALE_WITH_PARAM    0x0C // Suitable for any case. see struct osd_scale_param
#define OSD_VSCALE_CC_SUBT	0X0D // ATSC CC for HD output scale

#define OSD_SCALE_WITH_PARAM_DEO    0x1000 // set scale parameter for sd output when dual output is enabled. see struct osd_scale_param

#define   OSD_SOURCE_PAL        0
#define   OSD_SOURCE_NTSC       1

#define   OSD_SCALE_DUPLICATE   0
#define   OSD_SCALE_FILTER      1

#define   OSD_SET_ENHANCE_BRIGHTNESS 0x01    // value[0, 100], default 50
#define   OSD_SET_ENHANCE_CONTRAST   0x02    // value[0, 100], default 50
#define   OSD_SET_ENHANCE_SATURATION	0x04    // value[0, 100], default 50
#define   OSD_SET_ENHANCE_SHARPNESS  0x08    // value[0, 10 ], default 5
#define   OSD_SET_ENHANCE_HUE        0x10    // value[0, 100], default 50

// io command
#define	OSD_IO_UPDATE_PALLETTE	0x00
#define OSD_IO_ADJUST_MEMORY    0x01
#define OSD_IO_SET_VFILTER      0x02
#define OSD_IO_RESPOND_API	 0X03
#define OSD_IO_DIS_STATE	 0X04
#define OSD_IO_SET_BUF_CACHEABLE 0X05
#define OSD_IO_16M_MODE			0X06
#define OSD_IO_SET_TRANS_COLOR  0x07
#define OSD_IO_SET_ANTI_FLICK_THRE  0x0F
#define   OSD_IO_ENABLE_ANTIFLICK		0x10
#define   OSD_IO_DISABLE_ANTIFLICK		0x11

#define   OSD_IO_SWITCH_DEO_LAYER		0x12
#define   OSD_IO_SET_DEO_AUTO_SWITCH	0x13

#define   OSD_IO_GET_RESIZE_PARAMATER   0x14
#define   OSD_IO_SET_RESIZE_PARAMATER   0x15


#define OSD_IO_ELEPHANT_BASE 0x10000
#define OSD_IO_SWITH_DATA_TRANSFER_MODE (OSD_IO_ELEPHANT_BASE + 0x01)
#define OSD_IO_SET_ANTIFLK_PARA         (OSD_IO_ELEPHANT_BASE + 0x02)

#define OSD_IO_SET_GLOBAL_ALPHA         (OSD_IO_ELEPHANT_BASE + 0x03) /* dwParam [0x00, 0xff] */

#define OSD_IO_GET_ON_OFF               (OSD_IO_ELEPHANT_BASE + 0x04) /* OSD layer show or hide(dwParam is UINT32 *) */
#define OSD_IO_SET_AUTO_CLEAR_REGION    (OSD_IO_ELEPHANT_BASE + 0x05) /* Enable/Disable filling transparent color in OSDDrv_CreateRegion().
                                                                         After Open(), default is TRUE. Set it before OSDDrv_CreateRegion().*/
/* Enable/Disable GE ouput YCBCR format to DE when source is CLUT8, clut8->ycbcr, not do color reduction
     only used when output is 576i/p or 480i/p*/
#define OSD_IO_SET_YCBCR_OUTPUT    (OSD_IO_ELEPHANT_BASE + 0x06) 

#define OSD_IO_SET_DISPLAY_ADDR    (OSD_IO_ELEPHANT_BASE + 0x07) 
#define OSD_IO_SET_MAX_PIXEL_PITCH	   (OSD_IO_ELEPHANT_BASE + 0x08)
#define OSD_IO_WRITE2_SUPPORT_HD_OSD   (OSD_IO_ELEPHANT_BASE + 0x09)
#define OSD_IO_SUBT_RESOLUTION     (OSD_IO_ELEPHANT_BASE + 0x0A)
#define OSD_IO_CREATE_REGION            (OSD_IO_ELEPHANT_BASE + 0x0b) /* Create region with external buffer, dwParam is pcosd_region_param */
#define OSD_IO_MOVE_REGION              (OSD_IO_ELEPHANT_BASE + 0x0c) /* Move the region created by OSD_IO_CREATE_REGION, dwParam is pcosd_region_param */
#define OSD_IO_GET_REGION_INFO          (OSD_IO_ELEPHANT_BASE + 0x0d) /* Get the region information , dwParam is posd_region_param */
#define OSD_IO_GET_DISPLAY_RECT         (OSD_IO_ELEPHANT_BASE + 0x0e) /* struct OSDRect * */
#define OSD_IO_SET_DISPLAY_RECT         (OSD_IO_ELEPHANT_BASE + 0x0f) /* struct OSDRect * */
#define OSD_IO_SET_ENHANCE_PAR          (OSD_IO_ELEPHANT_BASE + 0x10)

#define OSD_IO_LINUX_API_BASE		(0xF00000)
#define OSD_IO_NO_CLEAR_BUF		(OSD_IO_LINUX_API_BASE + 0x01)
#define OSD_IO_VIDEO_ENHANCE		(OSD_IO_LINUX_API_BASE + 0x02)
#define OSD_IO_DISABLE_ENHANCE	        (OSD_IO_LINUX_API_BASE + 0x03)
#define OSD_IO_GET_LAYER_INFO		(OSD_IO_LINUX_API_BASE + 0x04)

enum OSD_SUBT_RESOLUTION{
	OSD_SUBT_RESO_720X576 = 1,
	OSD_SUBT_RESO_720X480,
	OSD_SUBT_RESO_1280X720,
	OSD_SUBT_RESO_1920X1080
};

/*! @struct OSDPara
@brief 初始化参数。
*/
struct OSDPara
{
	enum OSDColorMode eMode;//!< 颜色格式。
	UINT8 uGAlphaEnable;//!< 目前未实现。
	UINT8 uGAlpha;//!< 目前未实现。
	UINT8 uPalletteSel;//!< 目前未实现。
};

/*! @struct OSDRect
@brief 矩形尺寸和位置。
*/
struct OSDRect
{
	INT16	uLeft;//!< 左边位置。
	INT16	uTop;//!< 上边位置。
	INT16	uWidth;//!< 宽度。
	INT16	uHeight;//!< 高度。
};

/*! @struct tagVScr
@brief 虚拟区域。
*/
typedef struct tagVScr
{
	struct OSDRect	vR; //!< 矩形。
	UINT8 	*lpbScr;//!< 缓冲区地址。
	UINT8	bBlockID;//!< 目前未实现。
	BOOL	updatePending;//!< 刷新标志。只由APP使用。
    UINT8   bColorMode;//!< 目前未实现。
	UINT8 bDrawMode;//!< 目前未实现。
}VSCR,*lpVSCR;

/*! @struct _osd_scale_param
@brief 缩放参数。
*/
typedef struct _osd_scale_param
{
    UINT16 tv_sys;//!< 目前未实现。
    UINT16 h_div;//!< 水平除系数。
    UINT16 v_div;//!< 垂直除系数。
    UINT16 h_mul;//!< 水平乘系数。
    UINT16 v_mul;//!< 垂直乘系数。
} osd_scale_param, *posd_scale_param;
typedef const osd_scale_param *pcosd_scale_param;

typedef struct _osd_resize_param
{
    INT32 h_mode;
    INT32 v_mode;
} osd_resize_param, *posd_resize_param;

typedef struct 
{
	UINT8 enable;
	UINT8 layer;
	UINT8 no_temp_buf; // not use temp buffer
	UINT8 reserved;
}osd_clut_ycbcr_out; /*output ycbcr to DE, source is clut format*/

typedef struct 
{
	UINT8 region_id; // region id
	UINT8 reserved[3];
	UINT32 disp_addr;  // buffer address to be displayed 
}osd_disp_addr_cfg;

#define OSD_Resize_Param    osd_resize_param
#define POSD_Resize_Param   posd_resize_param

/*! @struct _osd_region_param
@brief 区域参数。
*/
typedef struct _osd_region_param
{
    UINT8   region_id;//!< 区域索引值。
    UINT8   color_format;//!< 颜色格式。
    UINT8   galpha_enable;//!< 目前未实现。
    UINT8   global_alpha;//!< 目前未实现。
    UINT8   pallette_sel;//!< 目前未实现。
    UINT16  region_x;//!< 区域的左边位置。
    UINT16  region_y;//!< 区域的上边位置。
    UINT16  region_w;//!< 区域的宽度。
    UINT16  region_h;//!< 区域的高度。
    UINT32  phy_addr;//!< 区域缓冲区的物理地址。
    UINT32  bitmap_addr;//!< 区域缓冲区的虚拟地址。
    UINT32  pixel_pitch;//!< 区域的行尺寸。单位为字节。
    UINT32  bitmap_x;//!< 目前未实现。
    UINT32  bitmap_y;//!< 目前未实现。
    UINT32  bitmap_w;//!< 目前未实现。
    UINT32  bitmap_h;//!< 目前未实现。
} osd_region_param, *posd_region_param;
typedef const osd_region_param *pcosd_region_param;

/*! @struct _osd_layer_param
@brief 显示层参数。
*/
typedef struct _osd_layer_param
{
	enum OSDColorMode mode;//!< 颜色格式。
	
	void *mem_start;//!< 缓冲区物理地址。
	int mem_size;//!< 缓冲区大小。
	
	void *virtual_mem_start;//!< 缓冲区虚拟地址。
	int virtual_mem_size;//!< 缓冲区虚拟地址。

	int max_logical_width;//!< 最大宽度。
	int max_logical_height;//!< 最大高度。
	int pitch;	//!< 行长度。以字节为单位。
}osd_layer_param, *posd_layer_param;

/*! @struct osd_io_video_enhance
@brief OSD_IO_VIDEO_ENHANCE需要的参数定义。设置图像增强信息。
*/
struct osd_io_video_enhance
{
	UINT8	changed_flag; //!< 图像增强的类型。OSD_IO_SET_ENHANCE_XX表示增强的类型。
	UINT16   grade; //!< 图像增强的量化数值。范围为0 ~ 100。默认50，表示不做增强处理。
};

/*!
@brief 释放osd 模块。
*/
void HLD_OSDDrv_Dettach(void);

/*!
@brief 打开osd 模块。
@param[in] hDev 指向osd 模块 的指针。
@param[in] ptPara 初始化参数。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_Open(HANDLE hDev,struct OSDPara *ptPara);

/*!
@brief 关闭osd  模块。
@param[in] hDev 指向osd 模块 的指针。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_Close(HANDLE hDev);


/*!
@brief 读取初始化参数。
@param[in] hDev 指向osd 模块 的指针。
@param[in] ptPara 初始化参数。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_GetPara(HANDLE hDev,struct OSDPara* ptPara);

/*!
@brief 开关显示层。
@param[in] hDev 指向osd 模块 的指针。
@param[in] uOnOff 打开或者关闭的标志信息。OSDDRV_OFF表示关闭。OSDDRV_ON表示打开。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_ShowOnOff(HANDLE hDev,UINT8 uOnOff);

/*!
@brief 设置颜色表。
@param[in] hDev 指向osd 模块 的指针。
@param[in] puPallette 输入颜色表缓冲区指针。
@param[in] uColorNum 颜色总数。只支持256色。
@param[in] uType 颜色表类型。支持OSDDRV_YCBCR和OSDDRV_RGB。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_SetPallette(HANDLE hDev,UINT8 *puPallette,UINT16 uColorNum,UINT8 uType);

/*!
@brief 读取颜色表。
@param[in] hDev 指向osd 模块 的指针。
@param[out] puPallette 输出颜色表缓冲区指针。
@param[in] uColorNum 颜色总数。只支持256色。
@param[in] uType 颜色表类型。支持OSDDRV_YCBCR和OSDDRV_RGB。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_GetPallette(HANDLE hDev,UINT8 *puPallette,UINT16 uColorNum,UINT8 uType);

/*!
@brief 修改颜色表。
@param[in] hDev 指向osd 模块 的指针。
@param[in] uIndex 颜色表的索引值。
@param[in] uY 亮度值。
@param[in] uCb 蓝色色差值。
@param[in] uCr 红色色差值。
@param[uK] uK 透明度值。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_ModifyPallette(HANDLE hDev,UINT8 uIndex,UINT8 uY,UINT8 uCb,UINT8 uCr,UINT8 uK);

/*!
@brief 建议osd区域。
@param[in] hDev 指向osd 模块 的指针。
@param[in] uRegionId 区域的索引值。
@param[in] rect 区域的尺寸和位置信息。
@param[in] pOpenPara 目前未实现 。可以传入NULL。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_CreateRegion(HANDLE hDev,UINT8 uRegionId,struct OSDRect* rect,struct OSDPara*pOpenPara);

/*!
@brief 删除osd区域。
@param[in] hDev 指向osd 模块 的指针。
@param[in] uRegionId 区域的索引值。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_DeleteRegion(HANDLE hDev,UINT8 uRegionId);

/*!
@brief 设置osd区域的新位置。
@param[in] hDev 指向osd 模块 的指针。
@param[in] uRegionId 区域的索引值。
@param[in] rect 区域的新位置信息。只限于修改位置信息。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_SetRegionPos(HANDLE hDev,UINT8 uRegionId,struct OSDRect* rect);

/*!
@brief 读取osd区域的位置信息。
@param[in] hDev 指向osd 模块 的指针。
@param[in] uRegionId 区域的索引值。
@param[out] rect 区域的位置信息。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_GetRegionPos(HANDLE hDev,UINT8 uRegionId,struct OSDRect* rect);

/*!
@brief 向区域写入数据。
@param[in] hDev 指向osd 模块 的指针。
@param[in] uRegionId 区域的索引值。
@param[in] pVscr 保存写入数据的虚拟区域。
@param[in] rect 写入操作矩形的尺寸和位置信息。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_RegionWrite(HANDLE hDev,UINT8 uRegionId,VSCR *pVscr,struct OSDRect *rect);

/*!
@brief 从区域读取数据。
@param[in] hDev 指向osd 模块 的指针。
@param[in] uRegionId 区域的索引值。
@param[out] pVscr 保存读取数据的虚拟区域。
@param[in] rect 读取操作矩形的尺寸和位置信息。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_RegionRead(HANDLE hDev,UINT8 uRegionId,VSCR *pVscr,struct OSDRect *rect);

/*!
@brief 向区域填写指定颜色。
@param[in] hDev 指向osd 模块 的指针。
@param[in] uRegionId 区域的索引值。
@param[in] rect 写入操作矩形的尺寸和位置信息。
@param[in] uColorData 指定颜色。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE OSDDrv_RegionFill(HANDLE hDev,UINT8 uRegionId,struct OSDRect *rect, UINT32 uColorData);

/*!
@brief 设置缩放参数。
@param[in] hDev 指向osd 模块 的指针。
@param[in] uScaleCmd 缩放的命令。
@param[in] uScaleParam 缩放的参数。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
@note  缩放命令uScaleCmd 介绍:
<table class="doxtable"  width="800" border="1" style="border-collapse:collapse;table-layout:fixed;word-break:break-all;" >
  <tr>
    <th width="200">命令</th>
    <th width="200">参数</th>
    <th width="80">传输特性</th>
    <th width="320">备注</th>
  </tr>

  <tr align="center">
    <td>OSD_VSCALE_OFF</td>    
    <td>空</td>    
    <td>输入</td>
    <td>实现1:1输出</td>
  </tr>

   <tr align="center">
    <td>OSD_SET_SCALE_MODE</td>    
    <td>空</td>    
    <td>输入</td>
    <td>设置缩放模式。只能设为复制模式</td>
  </tr> 

   <tr align="center">
    <td>OSD_SCALE_WITH_PARAM</td>    
    <td>osd_scale_param *</td>    
    <td>输入</td>
    <td>设置缩放比例的参数</td>
  </tr>      
*/
RET_CODE OSDDrv_Scale(HANDLE hDev, UINT32 uScaleCmd,UINT32 uScaleParam);

/*!
@brief osd 模块的io contorl 操作。
@param[in] hDev 指向osd 模块 的指针。
@param[in] dwCmd 操作 的命令类型。参考OSD_IO_XX定义。
@param[in,out] dwParam 操作的参数，根据不同的命令会有不同的参数。
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
    <td>OSD_IO_SET_TRANS_COLOR</td>    
    <td>UINT8</td>    
    <td>输入</td>
    <td>设置透明色索引值。只在颜色格式为CLUT8时有效</td>
  </tr>

  <tr align="center">
    <td>OSD_IO_SET_GLOBAL_ALPHA</td>    
    <td>UINT8</td>    
    <td>输入</td>
    <td>设置显示层的透明度。0xFF表示完全不透明。0表示全透明。</td>
  </tr>

  <tr align="center">
    <td>OSD_IO_GET_REGION_INFO</td>    
    <td>posd_region_param </td>    
    <td>输出</td>
    <td>读取区域的信息</td>
  </tr>  
  
   <tr align="center">
    <td>OSD_IO_GET_LAYER_INFO</td>    
    <td>posd_layer_param</td>    
    <td>输出</td>
    <td>读取显示层的参数</td>
  </tr>    
*/
RET_CODE OSDDrv_IoCtl(HANDLE hDev,UINT32 dwCmd,UINT32 dwParam);

/*!
@}
*/

#ifdef __cplusplus
}
#endif

#endif

