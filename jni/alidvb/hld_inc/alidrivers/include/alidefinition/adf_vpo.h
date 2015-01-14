#ifndef	__ADF_VPO_H_
#define	__ADF_VPO_H_

#include "adf_basic.h"
#include "adf_media.h"

#ifdef __cplusplus
extern "C" {
#endif
 
#define	VP_S3601_SOURCE_MAX_NUM 4
#define	VP_S3601_WINDOW_MAX_NUM 4
#define	VP_S3601_VIDEO_MAX_NUM	4

#define	VP_SOURCE_MAX_NUM 4
#define	VP_WINDOW_MAX_NUM 4
#define	VP_VIDEO_MAX_NUM	4

#define PICTURE_WIDTH 720
#define PICTURE_HEIGHT 2880	//2880 is the lease common multiple of screen height of Pal and ntsc 
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 2880

#define	VP_DAC_TYPENUM	23
#define DAC0		0x01
#define DAC1		0x02
#define DAC2		0x04
#define DAC3		0x08
#define DAC4		0x10
#define DAC5		0x20

#define	VPO_MAINWIN					0x01
#define	VPO_PIPWIN					0x02
#define	VPO_PREVIEW					0x04

#define	VPO_IO_SET_BG_COLOR				    0x01
#define	VPO_IO_SET_VBI_OUT				    0x02
#define	VPO_IO_GET_OUT_MODE				    0x03
#define	VPO_IO_REG_DAC					    0x04
#define	VPO_IO_UNREG_DAC		            0x05
#define VPO_IO_GET_SRC_ASPECT	       	    0x06
#define	VPO_IO_REG_CALLBACK	       		    0x07
#define	VPO_IO_REG_CB_SRCMODE_CHANGE	    0x08
#define	VPO_IO_REG_CB_SRCASPECT_CHANGE	    0x09
#define	VPO_IO_REG_CB_GE				    0x0A
#define	VPO_IO_GET_INFO			            0x0B
#define	VPO_IO_SET_PARAMETER	            0x0C
#define	VPO_IO_PRINTF_HW_INFO	            0x0D
#define	VPO_IO_PRINTF_HW_SCALE_INIT	        0x0E
#define	VPO_IO_PREFRAME_DETECT_ONOFF	    0x0F
#define	VPO_IO_DIGITAL_OUTPUT_MODE		    0x10
#define	VPO_IO_REG_CB_HDMI				    0x10
#define	VPO_IO_HDMI_OUT_PIC_FMT			    0x11
#define VPO_IO_VIDEO_ENHANCE			    0x12
#define VPO_IO_WRITE_TTX                    0x13
#define VPO_IO_WRITE_CC                     0x14
#define VPO_IO_WRITE_WSS                    0x15
#define	VPO_IO_GET_REAL_DISPLAY_MODE	    0x16
#define VPO_IO_MHEG_SCENE_AR	            0x17
#define VPO_IO_MHEG_IFRAME_NOTIFY           0x18
#define VPO_IO_DISAUTO_WIN_ONOFF            0x19
#define VPO_IO_ENABLE_VBI                   0x1A
#define VPO_IO_ENABLE_EXTRA_WINDOW          0x1F
#define VPO_IO_GET_TV_ASPECT	            0x20
#define VPO_IO_DIRECT_ZOOM		            0x21
#define	VPO_IO_DROP_LINE	                0x22
#define VPO_IO_FIX_WSS			            0x23
#define VPO_IO_OUPUT_PIC_DIRECTLY	        0x24
#define VPO_IO_PLAYMODE_CHANGE	            0x25
#define VPO_IO_SET_PROGRES_INTERLC	        0x26
#define VPO_IO_SET_LINEMEET_CNT	            0x27
#define VPO_IO_ADJUST_LM_IN_PREVIEW	        0x28
#define	VPO_IO_DIT_CHANGE		            0x29
#define VPO_IO_SWAFD_ENABLE				    0x30
#define VPO_IO_CHANGE_DEINTERL_MODE	        0x31
#define VPO_IO_704_OUTPUT				    0x32
#define VPO_IO_CHANGE_YC_INIT_PHASE		    0x33
#define VPO_IO_COMPENENT_UPSAMP_REPEAT	    0x34
#define VPO_IO_SET_PREVIEW_MODE			    0x35
#define VPO_IO_SET_DIT_LEVEL			    0x36
#define VPO_IO_CHANGE_CHANNEL               0x37
#define VPO_IO_SET_DIGITAL_OUTPUT_601656    0x38
#define VPO_IO_ADJUST_Y_COMP_FREQRESPONSE	0x39
#define VPO_IO_SD_CC_ENABLE                 0x3a
#define VPO_IO_SET_STILL_PIC				0x40
#define VPO_IO_CB_UPDATE_PALLET				0x41
#define VPO_IO_AFD_CONFIG					0x42
#define VPO_IO_SET_MG_APS_INFO		        0x43
#define VPO_IO_SET_CGMS_INFO				0x44
#define VPO_IO_ADJUST_DIGTAL_YC_DELAY		0x45
#define VPO_IO_TVESDHD_SOURCE_SEL			0x46
#define VPO_IO_CB_AVSYNC_MONITOR			0x47
#define VPO_IO_SET_OSD_SHOW_TIME            0x48    // vpo_osd_show_time_t *
#define VPO_IO_GET_OSD0_SHOW_TIME           0x49    // UINT32 *
#define VPO_IO_GET_OSD1_SHOW_TIME           0x4a    // UINT32 *
#define VPO_IO_GET_CURRENT_DISPLAY_INFO     0x4b    // struct vpo_io_get_picture_info *
#define VPO_IO_BACKUP_CURRENT_PICTURE       0x4c    // struct vpo_io_get_picture_info *
#define VPO_IO_GET_DISPLAY_MODE             0x4d    // enum DisplayMode *
#define VPO_IO_ENABLE_DE_AVMUTE_HDMI        0x4e    // BOOL:  TRUE/FALSE
#define VPO_IO_SET_DE_AVMUTE_HDMI           0x4f    // BOOL:  TRUE/FALSE
#define VPO_IO_GET_DE_AVMUTE_HDMI           0x50    // UINT32 * -- output TRUE/FALSE
#define VPO_IO_ALWAYS_OPEN_CGMS_INFO		0x51    // True -- always open; False -- close it
#define VPO_IO_GET_MP_SCREEN_RECT           0x52    // struct Rect *
#define VPO_IO_ENABLE_ICT		            0x53    // True -- enable ict;FALSE -- disable it
#define VPO_IO_SET_WIN_ONOFF_STATUS_MANUALLY		0x54
#define VPO_IO_SET_VBI_STARTLINE					0x55
#define VPO_IO_GET_BEST_DESUB				0x56
#define VPO_IO_SET_DISPLAY_STYLE            0X57
#define VPO_IO_GET_DEO_DELAY                0x58
#define VPO_IO_CLEAN_CURRENT_STILL_PICTURE	0x59
#define VPO_IO_FREE_BACKUP_PICTURE			0x5a
#define VPO_IO_SET_PREVIEW_SAR_MODE			0x5b
#define VPO_FULL_SCREEN_CVBS				0x5c
#define VPO_IO_SET_MULTIVIEW_MODE           0x5d
#define VPO_IO_GET_MP_INFO                  0x5e

#define VPO_IO_SET_SINGLE_OUTPUT            0x5f
#define VPO_IO_SET_TVE_CVBS   		        0x60
#define VPO_IO_VE_IMPROVE                   0x61
#define VPO_IO_IMPROVE_GE                   0x62
#define VPO_IO_GET_PIP_USING_ADDR           0x63
#define VPO_IO_SET_VBI_START_LINE           0x64
#define VPO_IO_SET_HDMI_AR_SD4VS3           0x65  //add by ze, for ar 4:3 when sd
#define VPO_IO_SET_MULTIVIEW_BUF            0x66
#define VPO_IO_FILL_GINGA_BUF               0x67
#define VPO_IO_UPDATE_GINGA                 0x68
#define VPO_IO_ENABLE_VDAC_PLUG_DETECT      0x69
#define VPO_IO_SELECT_SCALE_MODE       		0x6a
#define VPO_IO_SET_VER_ACTIVE_LINE          0x6b
#define VPO_IO_GET_AUX_PIC_DISPLAY_INFO     0x6c
#define VPO_IO_BACKUP_AUX_PICTURE           0x6d
#define VPO_IO_SEL_OSD_SHOW_TIME            0x6e
#define VPO_IO_GET_OSD2_SHOW_TIME           0x6f //only support in m3281
#define VPO_IO_SEL_DUPLICATE_MODE           0x70
#define VPO_IO_ENABLE_ANTIFLICK             0x71
#define VPO_IO_SET_ANTIFLICK_THR            0x72

#define VPO_IO_ELEPHANT_BASE             	0x10000
#define VPO_IO_CHOOSE_HW_LAYER		        (VPO_IO_ELEPHANT_BASE + 0x01)
#define VPO_IO_GLOBAL_ALPHA			        (VPO_IO_ELEPHANT_BASE + 0x02)
#define VPO_IO_SET_MEMMAP_MODE              (VPO_IO_ELEPHANT_BASE + 0x03)
#define VPO_IO_PILLBOX_CUT_FLAG		        (VPO_IO_ELEPHANT_BASE + 0x04)
#define VPO_IO_SET_LAYER_ORDER              (VPO_IO_ELEPHANT_BASE + 0x05) // enum VP_LAYER_ORDER
#define VPO_IO_GET_LAYER_ORDER              (VPO_IO_ELEPHANT_BASE + 0x08) // UINT32 *
#define VPO_IO_SET_ENHANCE_ENABLE           (VPO_IO_ELEPHANT_BASE + 0x07) // TRUE/FALSE, default enable = TRUE
#define VPO_IO_GET_DE2HDMI_INFO             (VPO_IO_ELEPHANT_BASE + 0x06) // struct de2Hdmi_video_infor *
#define VPO_IO_GET_PRE_FB_ADDR              (VPO_IO_ELEPHANT_BASE + 0x09) // UINT32 *
#define VPO_IO_CLOSE_HW_OUTPUT				(VPO_IO_ELEPHANT_BASE + 0x0A)
#define VPO_IO_OTP_SET_VDAC_FS		 		(VPO_IO_ELEPHANT_BASE + 0x0B)
#define VPO_IO_SET_CUTLINE		 			(VPO_IO_ELEPHANT_BASE + 0x0C)
#define VPO_IO_SET_INIT_TV_SYS				(VPO_IO_ELEPHANT_BASE + 0x0D)
#define VPO_IO_DISPLAY_3D_ENABLE		 	(VPO_IO_ELEPHANT_BASE + 0x0E)
#define VPO_IO_SET_3D_ENH               	(VPO_IO_ELEPHANT_BASE + 0x0F)
#define VPO_IO_GET_CURRENT_3D_FB_ADDR		(VPO_IO_ELEPHANT_BASE + 0x10)
#define VPO_IO_DISPLAY_3D_STATUS        	(VPO_IO_ELEPHANT_BASE + 0x11)
#define VPO_IO_BOOT_UP_DONE			 		(VPO_IO_ELEPHANT_BASE + 0x12)
#define VPO_IO_GET_MP_ONOFF					(VPO_IO_ELEPHANT_BASE + 0xFE) // only for SEE CPU
#define VPO_IO_SHOW_VIDEO_SMOOTHLY			(VPO_IO_ELEPHANT_BASE + 0xFF) // only for SEE CPU

#define	VPO_IO_SET_PARA_FETCH_MODE	        0x01
#define	VPO_IO_SET_PARA_DIT_EN		        0x02
#define	VPO_IO_SET_PARA_VT_EN		        0x04
#define	VPO_IO_SET_PARA_V_2TAP		        0x08
#define	VPO_IO_SET_PARA_EDGE_PRESERVE_EN	0x10
#define VPO_IO_SET_ENHANCE_BRIGHTNESS       0x01    // value[0, 100], default 50
#define VPO_IO_SET_ENHANCE_CONTRAST         0x02    // value[0, 100], default 50
#define VPO_IO_SET_ENHANCE_SATURATION	    0x04    // value[0, 100], default 50
#define VPO_IO_SET_ENHANCE_SHARPNESS        0x08    // value[0, 10 ], default 5
#define VPO_IO_SET_ENHANCE_HUE              0x10    // value[0, 100], default 50

#define VPO_CB_HDMI 0x01
#define VPO_CB_SRCASPRATIO_CHANGE 0x02

#ifndef VIDEO_OPEN_PIP_WIN_FLAG
#define VIDEO_OPEN_PIP_WIN_FLAG   0X80
#endif

#define VPO_INDEPENDENT_NONE        0   //share the source with sdhd device and share all api setting
//#define VPO_INDEPENDENT_IN        1   //have its own source and its own api setting except that vpo_tvsys
#define VPO_INDEPENDENT_IN_OUT      2   //have its own source and its own all api setting
#define VPO_AUTO_DUAL_OUTPUT        3   // Enable dual-output for S3602F, must call vcap_m36f_attach() before vpo_open();

#define VPO_CB_HDMI                         0x01
#define VPO_CB_SRCASPRATIO_CHANGE           0x02

#ifndef VIDEO_OPEN_PIP_WIN_FLAG
#define VIDEO_OPEN_PIP_WIN_FLAG             0X80
#endif

//TVEncoder
#define TTX_START_LINE		        7//0x13//7//6
#define TTX_START_PRESENT_LINE      0x01
#define TTX_BUF_DEPTH		        16//18
#define TTX_PRESENT_BYTE_PER_LINE   0x2D
#define TTX_DATA                    0xAA

//tvencoder config bit
#define TVE_CC_BY_VBI               1
#define TVE_TTX_BY_VBI              2
#define TVE_WSS_BY_VBI              4
#define CGMS_WSS_BY_VBI             8
#define YUV_SMPTE                   0x10
#define YUV_BETACAM                 0x20
#define YUV_MII                     0x40
#define TVE_NEW_CONFIG              0x80
#define TVE_FULL_CUR_MODE           0x100
#define TVE_NEW_CONFIG_1            0x200
#define TVE_PLUG_DETECT_ENABLE      0x400

#define	SYS_525_LINE	0
#define	SYS_625_LINE	1

//tvencoder adjustable register define
#define TVE_ADJ_COMPOSITE_Y_DELAY       0
#define TVE_ADJ_COMPOSITE_C_DELAY       1
#define TVE_ADJ_COMPONENT_Y_DELAY       2
#define TVE_ADJ_COMPONENT_CB_DELAY      3
#define TVE_ADJ_COMPONENT_CR_DELAY      4
#define TVE_ADJ_BURST_LEVEL_ENABLE      5
#define TVE_ADJ_BURST_CB_LEVEL          6
#define TVE_ADJ_BURST_CR_LEVEL          7
#define TVE_ADJ_COMPOSITE_LUMA_LEVEL    8
#define TVE_ADJ_COMPOSITE_CHRMA_LEVEL   9
#define TVE_ADJ_PHASE_COMPENSATION      10
#define TVE_ADJ_VIDEO_FREQ_RESPONSE     11
//secam adjust value
#define TVE_ADJ_SECAM_PRE_COEFFA3A2     12
#define TVE_ADJ_SECAM_PRE_COEFFB1A4     13
#define TVE_ADJ_SECAM_PRE_COEFFB3B2     14
#define TVE_ADJ_SECAM_F0CB_CENTER       15
#define TVE_ADJ_SECAM_F0CR_CENTER       16
#define TVE_ADJ_SECAM_FM_KCBCR_AJUST    17
#define TVE_ADJ_SECAM_CONTROL           18
#define TVE_ADJ_SECAM_NOTCH_COEFB1      19
#define TVE_ADJ_SECAM_NOTCH_COEFB2B3    20
#define TVE_ADJ_SECAM_NOTCH_COEFA2A3    21
#define TVE_ADJ_VIDEO_DAC_FS			22
#define TVE_ADJ_C_ROUND_PAR				23

//advance tvencoder adjustable register define
#define TVE_ADJ_ADV_PEDESTAL_ONOFF              0
#define TVE_ADJ_ADV_COMPONENT_LUM_LEVEL         1
#define TVE_ADJ_ADV_COMPONENT_CHRMA_LEVEL       2
#define TVE_ADJ_ADV_COMPONENT_PEDESTAL_LEVEL    3
#define TVE_ADJ_ADV_COMPONENT_SYNC_LEVEL        4
#define TVE_ADJ_ADV_RGB_R_LEVEL                 5
#define TVE_ADJ_ADV_RGB_G_LEVEL                 6
#define TVE_ADJ_ADV_RGB_B_LEVEL                 7
#define TVE_ADJ_ADV_COMPOSITE_PEDESTAL_LEVEL    8
#define TVE_ADJ_ADV_COMPOSITE_SYNC_LEVEL        9
#define TVE_ADJ_ADV_PLUG_OUT_EN                 10
#define TVE_ADJ_ADV_PLUG_DETECT_LINE_CNT_SD     11
#define TVE_ADJ_ADV_PLUG_DETECT_AMP_ADJUST_SD   12
enum vp_display_layer
{
	VPO_LAYER_MAIN = 1,//changed for s3601-6/5
	VPO_LAYER_GMA1 = 2,
	VPO_LAYER_GMA2,
	VPO_LAYER_CUR,
	VPO_LAYER_AUXP = 0x10,     // for Auxiliary Picture Layer
};

enum VP_display_layer_29e
{
	VPO_LAYER_M = 1,
	VPO_LAYER_PIP,
	VPO_LAYER_OSD,
	VPO_LAYER_ST1,  
	VPO_LAYER_ST2,
};

enum VP_LAYER_ORDER
{
    VPO_MP_PIP_OSD_ST1_ST2 = 0x00,
    VPO_MP_PIP_ST1_OSD_ST2 = 0x01,
};

enum VP_AFD_SOLUTION 
{
	VP_AFD_COMMON,
	VP_AFD_MINGDIG,
};

enum VP_LAYER_BLEND_ORDER
{
	MP_GMAS_GMAF_AUXP =0,
	MP_GMAS_AUXP_GMAF, 
	MP_GMAF_GMAS_AUXP, 
	MP_GMAF_AUXP_GMAS,		
	MP_AUXP_GMAS_GMAF, 	
	MP_AUXP_GMAF_GMAS, 
	AUXP_MP_GMAS_GMAF,
	AUXP_MP_GMAF_GMAS,
};

enum VP_TVESDHD_SOURCE
{
	TVESDHD_SRC_DEN,
	TVESDHD_SRC_DEO,
};

/*! @enum VgaMode
@brief 视频接口的VGA类型。
*/
enum VgaMode
{
	VGA_NOT_USE = 0, //!< 关闭VGA接口。
	VGA_640_480, //!< 未实现。
	VGA_800_600 //!< 未实现。
};

/*! @enum DacType
@brief 视频接口的类型。
*/
enum DacType
{
	CVBS_1 = 0,
	CVBS_2,
	CVBS_3,
	CVBS_4,
	CVBS_5,
	CVBS_6,	
	SVIDEO_1,
	SVIDEO_2,
	SVIDEO_3,	
	YUV_1,
	YUV_2,	
	RGB_1,
	RGB_2,
	SVIDEO_Y_1,
	SECAM_CVBS1,
	SECAM_CVBS2,
	SECAM_CVBS3,
	SECAM_CVBS4,
	SECAM_CVBS5,
	SECAM_CVBS6,	
	SECAM_SVIDEO1,
	SECAM_SVIDEO2,
	SECAM_SVIDEO3,
};

enum VPO_DIT_LEVEL
{
	VPO_DIT_LEVEL_HIGH ,
	VPO_DIT_LEVEL_MEDIUM,
	VPO_DIT_LEVEL_LOW,
};

//Add for VE pause/slow/ff play mode, DE change DIT mode to increase display quality
enum VP_PlayMode
{
	NORMAL_PLAY,
	NORMAL_2_ABNOR,
	ABNOR_2_NORMAL
};

struct vpo_status_info
{
	UINT8	case_index;
	UINT8	status_index;
	UINT32	display_frm_step;
};

/*! @struct DacIndex
@brief 视频接口的接口配置信息。
*/
struct DacIndex
{
	UINT8 uDacFirst; //!< 第一组配置接口(CVBS , YC_Y ,YUV_Y,RGB_R)。
	UINT8 uDacSecond;   //!< 第二组配置接口(YC_C ,YUV_U,RGB_G).
	UINT8 uDacThird;   //!< 第三组配置接口(YUV_V,RGB_B)。
};

/*! @struct VP_DacInfo
@brief 视频接口的配置信息。
*/
struct VP_DacInfo
{
	BOOL					bEnable; //!< 使能标志。
	//enum DacType 			eDacType; //for all
	struct DacIndex			tDacIndex; //!< 接口配置信息。
	enum VgaMode			eVGAMode;//! 未实现。
	BOOL					bProgressive;//!< 逐行输出标志。
};

/*! @struct vpo_io_reg_dac_para
@brief VPO_IO_REG_DAC需要的参数定义。注册视频接口。
*/
struct vp_io_reg_dac_para
{
	enum DacType eDacType; //!< 接口的类型。
	struct VP_DacInfo DacInfo; //!< 接口的配置信息。
};

/*! @struct vpo_io_get_info
@brief VPO_IO_GET_INFO需要的参数定义。读取模块信息。
*/
struct vpo_io_get_info
{
	UINT32 display_index; //!< 显示帧数。
	UINT32	api_act; //!< 未实现。
	BOOL	bprogressive; //!< 输出信息的逐行标志。
	enum TVSystem	tvsys; //!< 输出信号的电视制式。
	BOOL	fetch_mode_api_en; //!< 未实现。
	enum DeinterlacingAlg	fetch_mode; //!< 未实现。
	BOOL	dit_enable; //!< dit标志。
	BOOL	vt_enable; //!< vt标志。
	BOOL	vertical_2tap; //!< 未实现。
	BOOL	edge_preserve_enable; //!< 未实现。
	UINT16	source_width; //!< 视频源的宽度。
	UINT16	source_height; //!< 视频源的高度。
	UINT16    des_width; //!< 屏幕的宽度。
	UINT16	des_height; //!< 屏幕的高度。
	BOOL	preframe_enable; //!< 未实现。
	BOOL	gma1_onoff; //!< GMA1打开标志。
	UINT32	reg90; //!< 未实现。
    UINT32  scart_16_9;
    BOOL	mp_onoff;
};

struct vpo_io_set_parameter
{
	UINT8	changed_flag;
	BOOL	fetch_mode_api_en;
	enum DeinterlacingAlg	fetch_mode;
	BOOL	dit_enable;
	BOOL	vt_enable;
	BOOL	vertical_2tap;
	BOOL	edge_preserve_enable;
};

struct pip_pic_info
{
    UINT8 index;
    UINT32 pic_addr;
};

struct vpo_io_get_picture_info
{
    UINT8   de_index; /* it is input parameter    0: DE_N  1: DE_O */
    UINT8   sw_hw;    /* it is input parameter    0: software register  1: hardware register */
    UINT8   status;   /* input value is initialized to 0 
                         output value is 0: this control command is not implemented  
                                         1: this control command is implemented and no picture is displayed  
                                         2: this control command is implemented and one picture is displayed now 
                                            and the following parameters containing the information of this picture */
    UINT32  top_y;
    UINT32  top_c;
    UINT32  bot_y;
    UINT32  bot_c;
    UINT32  maf_buffer;
    UINT32  y_buf_size;
    UINT32  c_buf_size;
    UINT32  maf_buf_size;
    UINT32  reserved[10];
};

/*! @struct vpo_io_video_enhance
@brief VPO_IO_VIDEO_ENHANCE需要的参数定义。设置图像增强信息。
*/
struct vpo_io_video_enhance
{
	UINT8	changed_flag; //!< 图像增强的类型。VPO_IO_SET_ENHANCE_XX表示增强的类型。
	UINT16   grade; //!< 图像增强的量化数值。范围为0 ~ 100。默认50，表示不做增强处理。
};

struct vpo_io_ttx
{
        UINT8 LineAddr;
        UINT8 Addr;
        UINT8 Data;
};

struct vpo_io_cc
{
		UINT8 FieldParity;
		UINT16 Data;
};

/*! @struct vpo_io_global_alpha
@brief VPO_IO_GLOBAL_ALPHA需要的参数定义。设置视频层的全局透明度。
*/
struct vpo_io_global_alpha
{	
	UINT8 value; //!< 透明度的值。范围为0~255。0表示全透明。
	UINT8 valid; //!< 有效标志。
};

struct vpo_io_cgms_info
{
	UINT8 cgms;
	UINT8 aps;
};

struct vp_io_afd_para
{
	BOOL bSwscaleAfd;
	int  afd_solution;
	int  protect_mode_enable;
};

struct vpo_io_cutline_pars
{
    	UINT8 top_bottom;             //0: cut line from top 1: cut line from bottom
    	UINT8 cut_line_number;
};

struct vpo_io_set_ver_active_line
{
   UINT16 odd_start_active_line;
   UINT16 odd_end_active_line;
   UINT16 even_start_active_line;
   UINT16 even_end_active_line;
};

typedef enum InputFormat_e
{
	INPUT_2D = 0x0,
	INPUT_3D,
}InputFormat_t;

enum OutputFormat_e
{
    OUTPUT_2D = 0x0,
    FRAME_PACKING,
    SIDE_BY_SIDE_HALF,
    SIDE_BY_SIDE_FULL,
    TOP_AND_BOTTOM,
    LINE_ALTERNATIVE,
    RED_AND_BLUE,
    FIELD_ALTERNATIVE,
    FRAME_SEQUENTIAL,
    PRGB,
    SRGB,
};
struct alifbio_3d_pars
{
    int display_3d_enable;
    int side_by_side;
    int top_and_bottom;
    int display_2d_to_3d;
    int depth_2d_to_3d;
    int mode_2d_to_3d;
    int red_blue;
//    int mvc_flag;
    InputFormat_t eInputFormat;
};

struct alifbio_3d_enhance_pars
{
    int enable_3d_enhance;
    int use_enhance_default;
    int set_3d_enhance;
    UINT8 eye_protect_shift;
	int user_true3d_enhance;
	int user_true3d_constant_shift;
	int ver_gradient_ratio;
	int hor_gradient_ratio;
	int pop_for_reduction_ratio;
	int parallax_sign_bias;
};


#if 1
typedef struct vpo_osd_show_time_s
{
    UINT8  show_on_off;     // true or false
    UINT8  layer_id;        // 0 or 1
    UINT8  reserved0;
    UINT8  reserved1;
    UINT32 time_in_ms;      // in ms
} vpo_osd_show_time_t, *p_vpo_osd_show_time_t;
#endif

/*! @struct VP_InitInfo
@brief 视频输出的初始化信息。
*/
struct VP_InitInfo
{
	//api set backgound color
	struct  YCbCrColor		tInitColor; //!< 背景层的颜色。
	//set advanced control
	UINT8 					bBrightnessValue;  //!< 未实现。
	BOOL 					fBrightnessValueSign;  //!< 未实现。
	UINT16 					wContrastValue;  //!< 未实现。
	BOOL 					fContrastSign;   //!< 未实现。
	UINT16 					wSaturationValue;  //!< 未实现。
	BOOL					fSaturationValueSign;  //!< 未实现。
	UINT16					wSharpness;  //!< 未实现。
	BOOL 					fSharpnessSign;  //!< 未实现。
	UINT16 					wHueSin;  //!< 未实现。
	BOOL 					fHueSinSign; //!< 未实现。
	UINT16					wHueCos; //!< 未实现。
	BOOL					fHueCosSign; //!< 未实现。

	enum TVMode 			eTVAspect; //!< 长宽比。
	enum DisplayMode 		eDisplayMode; //! 显示模式。
	UINT8 					uNonlinearChangePoint; //!< 未实现。
	UINT8 					uPanScanOffset; //!< 未实现。

	struct VP_DacInfo		pDacConfig[VP_DAC_TYPENUM]; //!< 视频接口配置信息。
	enum TVSystem 			eTVSys; //!< 电视制式。

	//3config win on/off and mode
	BOOL						bWinOnOff; //!< 打开视频层标志。
	UINT8						uWinMode;  //!< 输出屏幕方式。
	struct Rect					tSrcRect;  //!< 输入的矩形信息。
	struct Rect					DstRect;  //!< 输出的矩形信息。

	struct MPSource_CallBack	tMPCallBack;  //!< 未实现。
	struct PIPSource_CallBack	tPIPCallBack; //!< 未实现。
	void *pSrcChange_CallBack;  //!< 未实现。
//	VP_SRCASPECT_CHANGE		pSrcAspectChange_CallBack;
       UINT8						device_priority;  //!< 未实现。
	BOOL bCCIR656Enable; //!< 未实现。	
    /*for vcapture*/
    BOOL                        bEnableVcap;
    UINT32 VcapFbAddr;  // 256 bytes aligned frame buffer address
    UINT32 VcapFbSize;  // (736x576 * 2) *3

};



struct vp_src_dst_rect
{
	struct Rect src_rect;
	struct Rect dst_rect;
};

struct vp_win_config
{
	UINT8	source_index;//changed for s3601-6/5
	enum vp_display_layer	display_layer;
	//UINT8	win_mode;
	
	void * src_module_devide_handle;
	struct source_callback	src_callback;
	
	struct vp_src_dst_rect 	rect;	
};

//changed for s3601-6/5
struct vp_source_info
{
	void * src_module_devide_handle;
	struct source_callback	src_callback;
	UINT8	src_path_index;
	UINT8	attach_source_index;
};

struct vp_win_config_para
{
	UINT8		source_number;
	struct vp_source_info source_info[VP_S3601_SOURCE_MAX_NUM];

	UINT8		control_source_index;
	UINT8		mainwin_source_index;

	UINT8		window_number;
	struct vp_win_config window_parameter[VP_S3601_WINDOW_MAX_NUM];
};

//#ifdef VIDEO_S3601
struct vp_io_reg_callback
{
	UINT8	callback_type;
	void *	callback_func;
};

//#endif

typedef void (* VP_SRCMODE_CHANGE)(enum TVSystem);
typedef void (* VP_SRCASPECT_CHANGE)(enum AspRatio, enum TVMode);
typedef void (* VP_SRCASPRATIO_CHANGE)(UINT8);
typedef BOOL (* VP_MPGetMemInfo)(UINT32 *);
//End
typedef void (*VP_CB_VSYNC_CALLBACK)(UINT32 );

struct VP_Feature_Config
{
	BOOL bOsdMulitLayer;
	BOOL bMHEG5Enable;
	BOOL bAvoidMosaicByFreezScr;
	BOOL bSupportExtraWin;
	BOOL bOvershootSolution;
	BOOL bP2NDisableMAF;
	BOOL bADPCMEnable;
	VP_MPGetMemInfo pMPGetMemInfo;	
	VP_SRCASPRATIO_CHANGE	pSrcAspRatioChange_CallBack;
    BOOL bDisableMultivewFun;
};

struct VP_direct_output
{
	UINT8	direct_output_array_len;
	UINT8 	reserved;
	UINT16	direct_output_array[5];
};

struct VP_mp_info
{
    UINT32 pic_height;
    UINT32 pic_width;
    UINT32 y_buf_addr;
    UINT32 c_buf_addr;
    UINT8  de_map_mode;  
};

void dvi_api_EnableInterrupt(UINT8 uDVIScanMode, UINT8 uInterrupt);

struct vpo_io_init_tv_sys
{
	enum TVSystem tv_sys;
	int progressive;
};



/*! @struct vpo_device
@brief vpo设备类型定义。
*/
struct vpo_device
{
	struct vpo_device  *next; //!< 内部使用。
    	UINT32 type; //!< 内部使用。
	INT8 name[32]; //!< 内部使用。
	void *priv; //!< 内部使用。
	void *priv_pip;
	UINT32 reserved;
	
	RET_CODE	(*open)(struct vpo_device *, struct VP_InitInfo *);
	RET_CODE   	(*close)(struct vpo_device *);
	RET_CODE   	(*ioctl)(struct vpo_device *,UINT32,UINT32);
	RET_CODE   	(*zoom)(struct vpo_device *,struct Rect *, struct Rect *);
	RET_CODE   	(*aspect_mode)(struct vpo_device *,enum TVMode, enum DisplayMode);
	RET_CODE 	(*tvsys)(struct vpo_device *, enum TVSystem, BOOL );
	RET_CODE 	(*win_onoff)(struct vpo_device *, BOOL);
	RET_CODE 	(*win_mode)(struct vpo_device *, BYTE, struct MPSource_CallBack *, struct PIPSource_CallBack *);
	RET_CODE 	(*config_source_window)(struct vpo_device *, struct vp_win_config_para *);
	RET_CODE 	(*set_progres_interl)(struct vpo_device *, BOOL);
    RET_CODE   	(*zoom_ext)(struct vpo_device *,struct Rect *, struct Rect *,enum vp_display_layer);
    RET_CODE 	(*win_onoff_ext)(struct vpo_device *, BOOL, enum vp_display_layer);
};


#if 0
typedef RET_CODE (*OSD_IO_CTL)(HANDLE ,UINT32 ,UINT32 );
typedef RET_CODE (* cb_ge_show_onoff)(struct ge_device *, ge_surface_desc_t *, UINT8 );
typedef RET_CODE (* cb_ge_blt_ex)(struct ge_device *, ge_surface_desc_t *,   ge_surface_desc_t *,  ge_surface_desc_t *, ge_rect_t *, ge_rect_t *, ge_rect_t *, UINT32 );
typedef ge_surface_desc_t * (*cb_ge_create_surface)(struct ge_device * , ge_surface_desc_t * , UINT32, UINT8);
typedef RET_CODE (*cb_ge_create_region)(struct ge_device * , ge_surface_desc_t * , UINT8 , ge_rect_t * , ge_region_t * );
typedef RET_CODE (*GE_DEO_IO_CTL)(HANDLE ,UINT32 ,UINT32 );
#endif

/*!
@brief 初始化vpo 模块。
*/
void HLD_vpo_attach(void);

/*!
@brief 释放vpo 模块。
*/
void HLD_vpo_dettach(void);

/*!
@brief 打开vpo 模块。
@param[in] dev 指向vpo 模块 的指针。
@param[in] pInitInfo 初始化参数。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vpo_open(struct vpo_device *dev,struct VP_InitInfo *pInitInfo);

/*!
@brief 关闭vpo  模块。
@param[in] dev 指向vpo 模块 的指针。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vpo_close(struct vpo_device *dev);

/*!
@brief 开关显示层。
@param[in] dev 指向vpo 模块 的指针。
@param[in] bOn 开关的标志。非0表示打开，0表示关闭。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vpo_win_onoff(struct vpo_device *dev,BOOL bOn);

/*!
@brief 设置vpo 模块的工作模式。
@param[in] dev 指向vpo 模块 的指针。
@param[in] bWinMode 工作模式，包括VPO_MAINWIN和VPO_PREVIEW。
@param[in] pMPCallBack 主图层相关的回调函数。
@param[in] pPIPCallBack  附图层相关的回调函数。目前并未实现。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vpo_win_mode(struct vpo_device *dev, BYTE bWinMode, struct MPSource_CallBack *pMPCallBack,struct PIPSource_CallBack *pPIPCallBack);

/*!
@brief 设置vpo 模块的缩放参数。
@param[in] dev 指向vpo 模块 的指针。
@param[in] pSrcRect 数据源的选择区域参数。
@param[in] pDstRect 显示屏的输出区域参数。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vpo_zoom(struct vpo_device *dev, struct Rect *pSrcRect , struct Rect *pDstRect);

/*!
@brief 设置vpo 模块的长宽比参数。
@param[in] dev 指向vpo 模块 的指针。
@param[in] eTVAspect 长宽比参数。
@param[in] e169DisplayMode 16比9模式的显示方式。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vpo_aspect_mode(struct vpo_device *dev, enum TVMode eTVAspect, enum DisplayMode e169DisplayMode);

/*!
@brief 设置vpo 模块的输出电视制式。
@param[in] dev 指向vpo 模块 的指针。
@param[in] eTVSys 输出电视制式。
@param[in] bprogressive 输出逐行信号的标志。非0表示逐行，0表示隔行
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE vpo_tvsys_ex(struct vpo_device *dev, enum TVSystem eTVSys,BOOL bprogressive);

/*!
@brief vpo 模块的io contorl 操作。
@param[in] dev 指向vpo 模块 的指针。
@param[in] dwCmd 操作 的命令类型。参考VPO_IO_XX定义。
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
    <td>VPO_IO_SET_BG_COLOR</td>    
    <td>struct  YCbCrColor *</td>    
    <td>输入</td>
    <td>设置背景颜色</td>
  </tr>

  <tr align="center">
    <td>VPO_IO_REG_DAC</td>    
    <td>struct vp_io_reg_dac_para *</td>    
    <td>输入</td>
    <td>注册新的视频接口</td>
  </tr>

  <tr align="center">
    <td>VPO_IO_UNREG_DAC</td>    
    <td>enum DacType</td>    
    <td>输入</td>
    <td>撤销视频接口</td>
  </tr>  
  
  <tr align="center">
    <td>VPO_IO_VIDEO_ENHANCE</td>    
    <td>struct  vpo_io_video_enhance *</td>    
    <td>输入</td>
    <td>设置图像增强的参数</td>
  </tr>  

  <tr align="center">
    <td>VPO_IO_GET_OUT_MODE</td>    
    <td>enum TVSystem *</td>    
    <td>输出</td>
    <td>读取输出的电视制式</td>
  </tr>  

  <tr align="center">
    <td>VPO_IO_GET_INFO</td>    
    <td>struct vpo_io_get_info *</td>    
    <td>输出</td>
    <td>读取模块信息</td>
  </tr>  

  <tr align="center">
    <td>VPO_IO_SET_LAYER_ORDER</td>    
    <td>bit6-7 bit4-5 bit2-3 bit0-1 *</td>    
    <td>输入</td>
    <td>设置叠加显示层的顺序</td>
  </tr>  
  <tr align="center">
    <td>VPO_IO_CLOSE_HW_OUTPUT</td>    
    <td>NULL *</td>    
    <td>输入</td>
    <td>在进入standby前，关闭硬件视频输出</td>
  </tr>  
*/
RET_CODE vpo_ioctl(struct vpo_device *dev, UINT32 dwCmd, UINT32 dwParam);

RET_CODE vpo_set_progres_interl(struct vpo_device *dev, BOOL bProgressive);
RET_CODE vpo_win_onoff_ext(struct vpo_device *dev,BOOL bOn,enum vp_display_layer layer);
RET_CODE vpo_zoom_ext(struct vpo_device *dev, struct Rect *pSrcRect , struct Rect *pDstRect,enum vp_display_layer layer);


/*
#define SYS_576I	0
#define SYS_480I	1
#define SYS_576P	2
#define SYS_480P	3
#define SYS_720P_50		4
#define SYS_720P_60		5
#define SYS_1080I_25	6
#define SYS_1080I_30	7
*/
typedef enum _eTV_SYS
{
    SYS_576I	,       
    SYS_480I	,       
    SYS_576P	,       
    SYS_480P	,       
    SYS_720P_50	,       
    SYS_720P_60	,       
    SYS_1080I_25,       
    SYS_1080I_30,       
                        
    SYS_1080P_24,       
    SYS_1080P_25,       
    SYS_1080P_30,       
                        
    SYS_1152I_25,       
    SYS_1080IASS,       
                        
    SYS_1080P_50,       
    SYS_1080P_60,       

    TVE_SYS_NUM,
}T_eTVE_SYS;


struct tve_adjust
{
    UINT8 type;
    UINT8 sys;
    UINT32 value;
};

struct tve_adjust_data
{
	BOOL valid;
	UINT32 value;
};

struct tve_adjust_tbl 
{
	UINT8 type;
	struct tve_adjust_data tve_data[8];  // config data for 8 kind of tv_system.
};



typedef enum eTVE_ADJ_FILED
{
    
	TVE_COMPOSITE_Y_DELAY    ,																																								
	TVE_COMPOSITE_C_DELAY    ,																																								
	TVE_COMPOSITE_LUMA_LEVEL ,																																								
	TVE_COMPOSITE_CHRMA_LEVEL,	
	TVE_COMPOSITE_SYNC_DELAY       ,
	TVE_COMPOSITE_SYNC_LEVEL       ,
	TVE_COMPOSITE_FILTER_C_ENALBE  ,
	TVE_COMPOSITE_FILTER_Y_ENALBE  ,
	TVE_COMPOSITE_PEDESTAL_LEVEL   ,


    TVE_COMPONENT_IS_PAL           ,
    TVE_COMPONENT_PAL_MODE         ,
	TVE_COMPONENT_ALL_SMOOTH_ENABLE,
	TVE_COMPONENT_BTB_ENALBE       ,
	TVE_COMPONENT_INSERT0_ONOFF    ,
	TVE_COMPONENT_DAC_UPSAMPLEN    ,
    TVE_COMPONENT_Y_DELAY    ,																																								
	TVE_COMPONENT_CB_DELAY   ,																																								
	TVE_COMPONENT_CR_DELAY   ,																																								
	TVE_COMPONENT_LUM_LEVEL        ,      																																								          
	TVE_COMPONENT_CHRMA_LEVEL      ,      																																								          																																				          																													
	TVE_COMPONENT_PEDESTAL_LEVEL   ,      			
	TVE_COMPONENT_UV_SYNC_ONOFF    ,
	TVE_COMPONENT_SYNC_DELAY       ,
	TVE_COMPONENT_SYNC_LEVEL       ,	
	TVE_COMPONENT_R_SYNC_ONOFF     ,
	TVE_COMPONENT_G_SYNC_ONOFF     ,
	TVE_COMPONENT_B_SYNC_ONOFF     ,
	TVE_COMPONENT_RGB_R_LEVEL      ,
	TVE_COMPONENT_RGB_G_LEVEL      ,
	TVE_COMPONENT_RGB_B_LEVEL      ,
	TVE_COMPONENT_FILTER_Y_ENALBE  ,
	TVE_COMPONENT_FILTER_C_ENALBE  ,
	TVE_COMPONENT_PEDESTAL_ONOFF   ,
	TVE_COMPONENT_PED_RGB_YPBPR_ENABLE ,
	TVE_COMPONENT_PED_ADJUST       ,
	TVE_COMPONENT_G2Y              ,
	TVE_COMPONENT_G2U              ,
	TVE_COMPONENT_G2V              ,
	TVE_COMPONENT_B2U              ,
	TVE_COMPONENT_R2V              ,

    TVE_BURST_POS_ENABLE     ,
    TVE_BURST_LEVEL_ENABLE   ,																																								
	TVE_BURST_CB_LEVEL       ,																																								
	TVE_BURST_CR_LEVEL       ,																																								
	TVE_BURST_START_POS            ,
	TVE_BURST_END_POS              ,
	TVE_BURST_SET_FREQ_MODE        ,
	TVE_BURST_FREQ_SIGN            ,																																						
	TVE_BURST_PHASE_COMPENSATION   ,																																								
    TVE_BURST_FREQ_RESPONSE  ,																																								

    TVE_ASYNC_FIFO           ,
    TVE_CAV_SYNC_HIGH        ,
    TVE_SYNC_HIGH_WIDTH      ,
    TVE_SYNC_LOW_WIDTH       ,

    TVE_VIDEO_DAC_FS		 ,																																																													

	TVE_SECAM_PRE_COEFFA3A2  ,																																								
	TVE_SECAM_PRE_COEFFB1A4  ,																																								
	TVE_SECAM_PRE_COEFFB3B2  ,																																								
	TVE_SECAM_F0CB_CENTER    ,																																								
	TVE_SECAM_F0CR_CENTER    ,																																								
	TVE_SECAM_FM_KCBCR_AJUST ,
	TVE_SECAM_CONTROL        ,
	TVE_SECAM_NOTCH_COEFB1   ,
	TVE_SECAM_NOTCH_COEFB2B3 ,
	TVE_SECAM_NOTCH_COEFA2A3 ,
    //added
    TVE_COMPONENT_PLUG_OUT_EN,
    TVE_COMPONENT_PLUG_DETECT_LINE_CNT_HD,
    TVE_CB_CR_INSERT_SW      ,
    TVE_VBI_LINE21_EN        ,
    TVE_COMPONENT_PLUG_DETECT_AMP_ADJUST_HD,
    TVE_SCART_PLUG_DETECT_LINE_CNT_HD,
    TVE_SCART_PLUG_DETECT_AMP_ADJUST_HD,
    TVE_COMPONENT_PLUG_DETECT_FRAME_COUNT,
    TVE_COMPONENT_PLUG_DETECT_VCOUNT,
    TVE_COMPONENT_VDAC_ENBUF,
    TVE_ADJ_FIELD_NUM,
                             
}T_eTVE_ADJ_FILED;



typedef struct _TVE_ADJUST_ELEMENT
{
	T_eTVE_ADJ_FILED index;
	unsigned int  value;
}T_TVE_ADJUST_ELEMENT;

typedef struct _TVE_ADJ_ADJUST_TABLE
{
	T_eTVE_SYS index;
	T_TVE_ADJUST_ELEMENT*  pTable;
}T_TVE_ADJUST_TABLE;

struct Tve_Feature_Config
{
	UINT32 config;
	struct tve_adjust *tve_adjust;
	struct tve_adjust_tbl *tve_tbl;
    T_TVE_ADJUST_TABLE *tve_tbl_all;
	struct tve_adjust *tve_adjust_adv;
};




struct tve_device
{
	struct tve_device  *next;  /*next device */
    UINT32 type;
	INT8 name[32];

	void *priv;		/* Used to be 'private' but that upsets C++ */

	RET_CODE (*open)(struct tve_device *);
	RET_CODE (*close)(struct tve_device *);
	RET_CODE (*set_tvsys)(struct tve_device *,enum TVSystem, BOOL );
	RET_CODE (*register_dac)(struct tve_device *,enum DacType, struct VP_DacInfo *);
	RET_CODE (*unregister_dac)(struct tve_device *,enum DacType);
	RET_CODE (*write_wss)(struct tve_device *,UINT16);
	RET_CODE (*write_cc)(struct tve_device *,UINT8, UINT16);
	RET_CODE (*write_ttx)(struct tve_device *,UINT8, UINT8, UINT8);
	RET_CODE (*reset_async_fifo)(struct tve_device *);
	RET_CODE (*set_wss_enable)(struct tve_device *, BOOL );
	BOOL     (*get_wss_status)(struct tve_device *);
	RET_CODE (*set_cc_config)(struct tve_device *, UINT8 , UINT8 , UINT8 );
	RET_CODE (*set_vbi_startline)(struct tve_device *, UINT8 );
    RET_CODE (*set_plug_detect_enable)(struct tve_device *, BOOL );
    RET_CODE (*set_vdac_fs_value)(struct tve_device *, UINT32 );
};

// for S3602F dual-output, need at least 3 extra frame buffers for SD output
typedef struct vcap_attach_s
{
    UINT32 fb_addr;  // 256 bytes aligned frame buffer address
    UINT32 fb_size;  // (736x576 * 2) *3
} vcap_attach_t, *p_vcap_attach_t;

/**************************API SubFunction Begin********************************************/
RET_CODE vpo_tvsys(struct vpo_device *dev, enum TVSystem eTVSys);
RET_CODE vpo_config_source_window(struct vpo_device *dev, struct vp_win_config_para *pwin_para);
// new added to set logo switch flag
RET_CODE vpo_set_logo_switch(BOOL bLogoSwitch);


RET_CODE tvenc_open(struct tve_device *dev);
RET_CODE tvenc_close(struct tve_device *dev);
RET_CODE tvenc_set_tvsys(struct tve_device *dev,enum TVSystem eTVSys);
RET_CODE tvenc_set_tvsys_ex(struct tve_device *dev,enum TVSystem eTVSys, BOOL bProgressive);
RET_CODE tvenc_register_dac(struct tve_device *dev,enum DacType eDacType, struct VP_DacInfo *pInfo);
RET_CODE tvenc_unregister_dac(struct tve_device *dev,enum DacType eDacType);
RET_CODE tvenc_write_wss(struct tve_device *dev,UINT16 Data);
RET_CODE tvenc_write_cc(struct tve_device *dev,UINT8 FieldParity, UINT16 Data);
RET_CODE tvenc_write_ttx(struct tve_device *dev,UINT8 LineAddr, UINT8 Addr, UINT8 Data);
void tve_advance_config(struct tve_adjust *tve_adj_adv);
RET_CODE tvenc_reset_async_fifo(struct tve_device *dev);
RET_CODE tvenc_set_wss_enable(struct tve_device *dev, BOOL bEnable);
BOOL tvenc_get_wss_status(struct tve_device *dev);
RET_CODE tvenc_set_cc_config(struct tve_device *dev, UINT8 TVSysIn ,
                            UINT8 CGMS_A, UINT8 Aps);
RET_CODE tvenc_set_vbi_startline(struct tve_device *dev, UINT8 line);                            
void m36g_tve_hd_attach(struct Tve_Feature_Config *pTVECfg);
RET_CODE tvenc_set_plug_detect_enable(struct tve_device *dev, BOOL bEnable);
RET_CODE tvenc_set_vdac_fs_value(struct tve_device *dev, UINT32 nValue);

void vcap_m36f_attach(const vcap_attach_t *vcap_param);
void vcap_m36f_dettach(void *dev);
void  vpo_m36f_attach(struct VP_Feature_Config * vp_cfg, struct Tve_Feature_Config*tvec_cfg);
void vpo_m36f_sd_attach(struct VP_Feature_Config * vp_cfg, struct Tve_Feature_Config*tvec_cfg);
void m36g_vcap_attach(const vcap_attach_t *vcap_param);
void m36g_vcap_dettach(void *dev);
//void osd_m36f_attach(char *name, OSD_DRIVER_CONFIG *attach_config);

void vpo_register_cb_routine(void);

#ifdef __cplusplus
}
#endif
#endif

