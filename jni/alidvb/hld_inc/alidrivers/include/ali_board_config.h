
#ifndef _ALIDRIVERS_BOARD_CONFIG_H_

#define _ALIDRIVERS_BOARD_CONFIG_H_

#define ALI_FB_FORMART_ARGB8888			1
#define ALI_FB_FORMART_RGBA8888			2

#define ALI_FB_FORMART_RGB565				10
#define ALI_FB_FORMART_ARGB1555			11

#define ALI_FB_FORMAT_CLUT8				20

#define ALI_PINMUX_CTRL1	0x18000088
#define ALI_PINMUX_CTRL2	0x1800008c

#define ALI_PINMUX_CTRL_BIT0	(1<<0)
#define ALI_PINMUX_CTRL_BIT1	(1<<1)
#define ALI_PINMUX_CTRL_BIT2	(1<<2)
#define ALI_PINMUX_CTRL_BIT3	(1<<3)
#define ALI_PINMUX_CTRL_BIT4	(1<<4)
#define ALI_PINMUX_CTRL_BIT5	(1<<5)
#define ALI_PINMUX_CTRL_BIT6	(1<<6)
#define ALI_PINMUX_CTRL_BIT7	(1<<7)
#define ALI_PINMUX_CTRL_BIT8	(1<<8)
#define ALI_PINMUX_CTRL_BIT9	(1<<9)
#define ALI_PINMUX_CTRL_BIT10	(1<<10)
#define ALI_PINMUX_CTRL_BIT11	(1<<11)
#define ALI_PINMUX_CTRL_BIT12	(1<<12)
#define ALI_PINMUX_CTRL_BIT13	(1<<13)
#define ALI_PINMUX_CTRL_BIT14	(1<<14)
#define ALI_PINMUX_CTRL_BIT15	(1<<15)
#define ALI_PINMUX_CTRL_BIT16	(1<<16)
#define ALI_PINMUX_CTRL_BIT17	(1<<17)
#define ALI_PINMUX_CTRL_BIT18	(1<<18)
#define ALI_PINMUX_CTRL_BIT19	(1<<19)
#define ALI_PINMUX_CTRL_BIT20	(1<<20)
#define ALI_PINMUX_CTRL_BIT21	(1<<21)
#define ALI_PINMUX_CTRL_BIT22	(1<<22)
#define ALI_PINMUX_CTRL_BIT23	(1<<23)
#define ALI_PINMUX_CTRL_BIT24	(1<<24)
#define ALI_PINMUX_CTRL_BIT25	(1<<25)
#define ALI_PINMUX_CTRL_BIT26	(1<<26)
#define ALI_PINMUX_CTRL_BIT27	(1<<27)
#define ALI_PINMUX_CTRL_BIT28	(1<<28)
#define ALI_PINMUX_CTRL_BIT29	(1<<29)
#define ALI_PINMUX_CTRL_BIT30	(1<<30)
#define ALI_PINMUX_CTRL_BIT31	(1<<31)


#ifndef DEFINE_BORAD_VARIABLES

/* chip type and version definition start*/

/* this area is decided by the ali's chipset.
it is updated with the new chipset.

	chip types description :
		name 			value
		M3602			0
		M3603			1
		M3701C			2
		M3921(ARM)		3

	chip version description :
		version		value
		invalid            -1
		ver0			0
		ver1   		1
		...
		vern			n
*/

extern unsigned long __G_ALI_CHIP_TYPE;
extern long __G_ALI_CHIP_VERSION; 

/* chip type and version definition end*/

/* hardware board definition start */

extern unsigned long __G_ALI_BOARD_TYPE;
extern long __G_ALI_BOARD_VERSION;

/* hardware board name definition end */

/* memory mapping configuration start */

extern unsigned long __G_ALI_MM_TOP_ADDR;

extern unsigned long __G_ALI_MM_VIDEO_SIZE;
extern unsigned long __G_ALI_MM_VIDEO_START_ADDR;

extern unsigned long __G_ALI_MM_VCAP_FB_SIZE;
extern unsigned long __G_ALI_MM_VCAP_FB_START_ADDR;

extern unsigned long __G_ALI_MM_STILL_FRAME_SIZE;
extern unsigned long __G_ALI_MM_STILL_FRAME_START_ADDR;

/* shared memory area reserved for the RPC driver*/
extern unsigned long __G_ALI_MM_SHARED_MEM_SIZE;
extern unsigned long __G_ALI_MM_SHARED_MEM_START_ADDR;

/* private memory area reserved for the SEE CPU */
extern unsigned long __G_ALI_MM_PRIVATE_AREA_SIZE;
extern unsigned long __G_ALI_MM_PRIVATE_AREA_START_ADDR;

extern unsigned long __G_ALI_MM_VDEC_VBV_SIZE;
extern unsigned long __G_ALI_MM_VDEC_VBV_START_ADDR;

extern unsigned long __G_ALI_MM_VDEC_RAW_DATA_SIZE;
extern unsigned long __G_ALI_MM_VDEC_RAW_DATA_START_ADDR;

extern unsigned long g_fb2_max_width;
extern unsigned long g_fb2_max_height;
extern unsigned long g_fb2_width;
extern unsigned long g_fb2_height;
extern unsigned long g_fb2_pitch;
extern unsigned long g_fb2_bpp;
extern unsigned long g_fb2_type;
extern unsigned long __G_ALI_MM_FB2_SIZE;
extern unsigned long __G_ALI_MM_FB2_START_ADDR;

extern unsigned long __G_ALI_MM_FB2_CMAP_SIZE;
extern unsigned long __G_ALI_MM_FB2_CMAP_START_ADDR;


#if 0
extern unsigned long __G_ALI_MM_TTX_BS_SIZE;
extern unsigned long __G_ALI_MM_TTX_BS_START_ADDR;

extern unsigned long __G_ALI_MM_TTX_PB_SIZE;
extern unsigned long __G_ALI_MM_TTX_PB_START_ADDR;

extern unsigned long __G_ALI_MM_TTX_SUB_PAGE_SIZE;
extern unsigned long __G_ALI_MM_TTX_SUB_PAGE_START_ADDR;

extern unsigned long __G_ALI_MM_TTX_P26_NATION_SIZE;
extern unsigned long __G_ALI_MM_TTX_P26_NATION_START_ADDR;

extern unsigned long __G_ALI_MM_TTX_P26_DATA_SIZE;
extern unsigned long __G_ALI_MM_TTX_P26_DATA_START_ADDR;

extern unsigned long __G_ALI_MM_SUB_BS_SIZE;
extern unsigned long __G_ALI_MM_SUB_BS_START_ADDR;

extern unsigned long __G_ALI_MM_SUB_HW_SIZE;
extern unsigned long __G_ALI_MM_SUB_HW_START_ADDR;

extern unsigned long __G_ALI_MM_SUB_PB_SIZE;
extern unsigned long __G_ALI_MM_SUB_PB_START_ADDR ;
#else
extern unsigned long __G_ALI_MM_SUBT_START_ADDR;
extern unsigned long __G_ALI_MM_TTX_START_ADDR;
#endif

/* user data memory area reserved for bootloader -> kenerl */
extern unsigned long __G_ALI_MM_USER_DATA_SIZE;
extern unsigned long __G_ALI_MM_USER_DATA_START_ADDR;

extern unsigned long __G_ALI_MM_SPECIAL_RESERVED0_SIZE;
extern unsigned long __G_ALI_MM_SPECIAL_RESERVED0_START_ADDR;

extern unsigned long __G_ALI_MM_SPECIAL_RESERVED1_SIZE;
extern unsigned long __G_ALI_MM_SPECIAL_RESERVED1_START_ADDR;

extern unsigned long __G_ALI_MM_BOOT_COMMAND_SIZE;
extern unsigned long __G_ALI_MM_BOOT_COMMAND_START_ADDR;

extern unsigned long __G_ALI_MM_SGDMA_MEM_SIZE;
extern unsigned long __G_ALI_MM_SGDMA_MEM_START_ADDR;

extern unsigned long __G_ALI_MM_DMX_MEM_SIZE;
extern unsigned long __G_ALI_MM_DMX_MEM_START_ADDR;

extern unsigned long __G_ALI_MM_TSG_BUF_SIZE;
extern unsigned long __G_ALI_MM_TSG_BUF_START_ADDR;

extern unsigned long __G_ALI_MM_APE_MEM_SIZE;
extern unsigned long __G_ALI_MM_APE_MEM_START_ADDR;

extern unsigned long g_fb0_max_width;
extern unsigned long g_fb0_max_height;
extern unsigned long g_fb0_width;
extern unsigned long g_fb0_height;
extern unsigned long g_fb0_pitch;
extern unsigned long g_fb0_bpp;
extern unsigned long g_fb0_type;
extern unsigned long __G_ALI_MM_FB0_SIZE;
extern unsigned long __G_ALI_MM_FB0_START_ADDR;

extern unsigned long __G_ALI_MM_FB0_CMAP_SIZE;
extern unsigned long __G_ALI_MM_FB0_CMAP_START_ADDR;

extern unsigned long __G_ALI_MM_GE_CMD_SIZE;
extern unsigned long __G_ALI_MM_GE_CMD_START_ADDR;

extern unsigned long __G_ALI_MM_NIM_J83B_MEM_SIZE;
extern unsigned long __G_ALI_MM_NIM_J83B_MEM_START_ADDR;
	
extern unsigned long __G_ALI_MM_IMAGE_DECODER_MEM_SIZE;
extern unsigned long __G_ALI_MM_IMAGE_DECODER_MEM_START_ADDR;

extern unsigned long __G_ALI_MM_MCAPI_MEM_SIZE;
extern unsigned long __G_ALI_MM_MCAPI_MEM_START_ADDR;

extern unsigned long __G_ALI_MM_AUDIO_DEC_MEM_SIZE;
extern unsigned long __G_ALI_MM_AUDIO_DEC_MEM_START_ADDR;

/* DECA
*/
extern unsigned long __G_ALI_MM_DECA_MEM_SIZE;
extern unsigned long __G_ALI_MM_DECA_MEM_START_ADDR;

/*
** VENC added_by_VicZhang_on_20131111.
*/
extern unsigned long __G_ALI_MM_VENC_MEM_SIZE;
extern unsigned long __G_ALI_MM_VENC_MEM_START_ADDR;

/* OVG memory */
extern unsigned long __G_ALI_MM_OVG_MEM_SIZE; 
extern unsigned long __G_ALI_MM_OVG_MEM_START_ADDR;

/* Mali dedicated memory */
extern unsigned long __G_ALI_MM_MALI_DEDICATED_MEM_SIZE;
extern unsigned long __G_ALI_MM_MALI_DEDICATED_MEM_START_ADDR;

/* Mali UMP memory */
extern unsigned long __G_ALI_MM_MALI_UMP_MEM_SIZE;
extern unsigned long __G_ALI_MM_MALI_UMP_MEM_START_ADDR;

/* DSC 
*/ 
extern unsigned long __G_ALI_MM_DSC_MEM_SIZE;
extern unsigned long __G_ALI_MM_DSC_MEM_START_ADDR;

/* the top address of the MAIN CPU */
#define MAX_MEM_REGION	8
extern unsigned long __G_ALI_MM_MAIN_MEM_NUM;
extern unsigned long __G_ALI_MM_MAIN_MEM[MAX_MEM_REGION][2];

/* memory mapping configuration end */

/* heap top address of the see cpu */
extern unsigned long g_see_heap_top_addr;

/* tv encoder parameters setting start*/

/* default scart output 
       0 : CVBS
	1 : RGB
	2 : SVIDEO
	3 : YUV
*/
extern long g_tve_default_scart_output;

/* default tv mode */
extern long g_tve_hd_default_tv_mode;
extern long g_tve_sd_default_tv_mode;

/* whether use the CVBS output. the invalid value is -1 */
extern long g_tve_dac_use_cvbs_type;

/* whether use the SVIDEO output. the invalid value is -1 */
extern long g_tve_dac_use_svideo_type;

/* whether use the RGB output. the invalid value is -1 */
extern long g_tve_dac_use_rgb_type;

/* whether use the YUV output. the invalie value is -1 */
extern long g_tve_dac_use_yuv_type;

/* CVBS dac definition */
extern long g_tve_dac_cvbs;

/* SVIDEO dac definition */
extern long g_tve_dac_svideo_y;
extern long g_tve_dac_svideo_c;

/* RGB dac definition */
extern long g_tve_dac_rgb_r;
extern long g_tve_dac_rgb_g;
extern long g_tve_dac_rgb_b;

/* YUV dac definition */
extern long g_tve_dac_yuv_y;
extern long g_tve_dac_yuv_u;
extern long g_tve_dac_yuv_v;

/* tv encoder parameters setting end*/

/* GPIO definition start */

extern unsigned long g_snd_mute_gpio;//3
extern unsigned long g_snd_chip_type;

extern unsigned long g_usb_device_5v_detect_gpio;
extern unsigned long g_usb_p0_host_5v_gpio;

/* GPIO definition end */

/* PDK Freautes start */

/* select the standard FB drvier */
extern unsigned long g_support_standard_fb;

extern unsigned long g_support_isdbt_cc;

//hdmi hdcp on/off
extern unsigned long g_hdmi_hdcp_enable;

extern unsigned int g_otp_set_vdac_fs;

// nand flash pinmux select
extern unsigned long g_nand_pm1_pin_sel;
extern unsigned long g_nand_pm2_strapin_sel_en;

extern unsigned long g_enet_speed_gpio;
extern unsigned long g_enet_link_gpio;

/* PDK Freautes end */

#else

/* chip type and version definition start*/

/* this area is decided by the ali's chipset.
it is updated with the new chipset.

	chip types description :
		name 			value
		M3602			0
		M3603			1
		M3701C			2
		M3921(ARM)		3

	chip version description :
		version		value
		invalid            -1
		ver0			0
		ver1   		1
		...
		vern			n
*/

unsigned long __G_ALI_CHIP_TYPE = 0;
long __G_ALI_CHIP_VERSION = 0; 

/* chip type and version definition end*/

/* hardware board definition start */

unsigned long __G_ALI_BOARD_TYPE = 0;
long __G_ALI_BOARD_VERSION = 0;

/* hardware board name definition end */

/* memory mapping configuration start */

unsigned long __G_ALI_MM_TOP_ADDR = 0;

unsigned long __G_ALI_MM_VIDEO_SIZE = 0;
unsigned long __G_ALI_MM_VIDEO_START_ADDR = 0;

unsigned long __G_ALI_MM_VCAP_FB_SIZE = 0;
unsigned long __G_ALI_MM_VCAP_FB_START_ADDR = 0;

unsigned long __G_ALI_MM_STILL_FRAME_SIZE = 0;
unsigned long __G_ALI_MM_STILL_FRAME_START_ADDR = 0;

/* shared memory area reserved for the RPC driver*/
unsigned long __G_ALI_MM_SHARED_MEM_SIZE = 0;
unsigned long __G_ALI_MM_SHARED_MEM_START_ADDR = 0;

/* private memory area reserved for the SEE CPU */
unsigned long __G_ALI_MM_PRIVATE_AREA_SIZE = 0;
unsigned long __G_ALI_MM_PRIVATE_AREA_START_ADDR = 0;

unsigned long __G_ALI_MM_VDEC_VBV_SIZE = 0;
unsigned long __G_ALI_MM_VDEC_VBV_START_ADDR;

unsigned long __G_ALI_MM_VDEC_RAW_DATA_SIZE = 0;
unsigned long __G_ALI_MM_VDEC_RAW_DATA_START_ADDR = 0;

unsigned long g_fb2_max_width = 0;
unsigned long g_fb2_max_height = 0;
unsigned long g_fb2_width = 0;
unsigned long g_fb2_height = 0;
unsigned long g_fb2_pitch = 0;
unsigned long g_fb2_bpp = 0;
unsigned long g_fb2_type = 0;
unsigned long __G_ALI_MM_FB2_SIZE = 0;
unsigned long __G_ALI_MM_FB2_START_ADDR = 0;

unsigned long __G_ALI_MM_FB2_CMAP_SIZE = 0;
unsigned long __G_ALI_MM_FB2_CMAP_START_ADDR = 0;


#if 0
unsigned long __G_ALI_MM_TTX_BS_SIZE = 0;
unsigned long __G_ALI_MM_TTX_BS_START_ADDR = 0;

unsigned long __G_ALI_MM_TTX_PB_SIZE = 0;
unsigned long __G_ALI_MM_TTX_PB_START_ADDR = 0;

unsigned long __G_ALI_MM_TTX_SUB_PAGE_SIZE = 0;
unsigned long __G_ALI_MM_TTX_SUB_PAGE_START_ADDR = 0;

unsigned long __G_ALI_MM_TTX_P26_NATION_SIZE = 0;
unsigned long __G_ALI_MM_TTX_P26_NATION_START_ADDR = 0;

unsigned long __G_ALI_MM_TTX_P26_DATA_SIZE = 0;
unsigned long __G_ALI_MM_TTX_P26_DATA_START_ADDR = 0;

unsigned long __G_ALI_MM_SUB_BS_SIZE = 0;
unsigned long __G_ALI_MM_SUB_BS_START_ADDR = 0;

unsigned long __G_ALI_MM_SUB_HW_SIZE = 0;
unsigned long __G_ALI_MM_SUB_HW_START_ADDR = 0;

unsigned long __G_ALI_MM_SUB_PB_SIZE = 0;
unsigned long __G_ALI_MM_SUB_PB_START_ADDR  = 0;
#else
unsigned long __G_ALI_MM_SUBT_START_ADDR = 0;
unsigned long __G_ALI_MM_TTX_START_ADDR = 0;
#endif

/* user data memory area reserved for bootloader -> kenerl */
unsigned long __G_ALI_MM_USER_DATA_SIZE = 0;
unsigned long __G_ALI_MM_USER_DATA_START_ADDR = 0;

unsigned long __G_ALI_MM_SPECIAL_RESERVED0_SIZE = 0;
unsigned long __G_ALI_MM_SPECIAL_RESERVED0_START_ADDR = 0;

unsigned long __G_ALI_MM_SPECIAL_RESERVED1_SIZE = 0;
unsigned long __G_ALI_MM_SPECIAL_RESERVED1_START_ADDR = 0;

unsigned long __G_ALI_MM_BOOT_COMMAND_SIZE = 0;
unsigned long __G_ALI_MM_BOOT_COMMAND_START_ADDR = 0;

unsigned long __G_ALI_MM_SGDMA_MEM_SIZE = 0;
unsigned long __G_ALI_MM_SGDMA_MEM_START_ADDR = 0;

unsigned long __G_ALI_MM_DMX_MEM_SIZE = 0;
unsigned long __G_ALI_MM_DMX_MEM_START_ADDR = 0;

unsigned long __G_ALI_MM_TSG_BUF_SIZE = 0;
unsigned long __G_ALI_MM_TSG_BUF_START_ADDR = 0;

unsigned long __G_ALI_MM_APE_MEM_SIZE = 0;
unsigned long __G_ALI_MM_APE_MEM_START_ADDR = 0;

unsigned long g_fb0_max_width = 0;
unsigned long g_fb0_max_height = 0;
unsigned long g_fb0_width = 0;
unsigned long g_fb0_height = 0;
unsigned long g_fb0_pitch = 0;
unsigned long g_fb0_bpp = 0;
unsigned long g_fb0_type = 0;
unsigned long __G_ALI_MM_FB0_SIZE = 0;
unsigned long __G_ALI_MM_FB0_START_ADDR = 0;

unsigned long __G_ALI_MM_FB0_CMAP_SIZE = 0;
unsigned long __G_ALI_MM_FB0_CMAP_START_ADDR = 0;

unsigned long __G_ALI_MM_GE_CMD_SIZE = 0;
unsigned long __G_ALI_MM_GE_CMD_START_ADDR = 0;

unsigned long __G_ALI_MM_NIM_J83B_MEM_SIZE = 0;
unsigned long __G_ALI_MM_NIM_J83B_MEM_START_ADDR = 0;
	
unsigned long __G_ALI_MM_IMAGE_DECODER_MEM_SIZE = 0;
unsigned long __G_ALI_MM_IMAGE_DECODER_MEM_START_ADDR = 0;

unsigned long __G_ALI_MM_MCAPI_MEM_SIZE = 0;
unsigned long __G_ALI_MM_MCAPI_MEM_START_ADDR = 0;

unsigned long __G_ALI_MM_AUDIO_DEC_MEM_SIZE = 0;
unsigned long __G_ALI_MM_AUDIO_DEC_MEM_START_ADDR = 0;

/* DECA
*/
unsigned long __G_ALI_MM_DECA_MEM_SIZE = 0;
unsigned long __G_ALI_MM_DECA_MEM_START_ADDR = 0;


/*
** VENC added_by_VicZhang_on_20131111.
*/
unsigned long __G_ALI_MM_VENC_MEM_SIZE = 0;
unsigned long __G_ALI_MM_VENC_MEM_START_ADDR = 0;

/* OVG memory */
unsigned long __G_ALI_MM_OVG_MEM_SIZE = 0; 
unsigned long __G_ALI_MM_OVG_MEM_START_ADDR = 0;

/* Mali dedicated memory */
unsigned long __G_ALI_MM_MALI_DEDICATED_MEM_SIZE = 0;
unsigned long __G_ALI_MM_MALI_DEDICATED_MEM_START_ADDR = 0;

/* Mali UMP memory */
unsigned long __G_ALI_MM_MALI_UMP_MEM_SIZE = 0;
unsigned long __G_ALI_MM_MALI_UMP_MEM_START_ADDR = 0;

/* DSC , 
*/ 
unsigned long __G_ALI_MM_DSC_MEM_SIZE = 0;
unsigned long __G_ALI_MM_DSC_MEM_START_ADDR = 0;

/* the top address of the MAIN CPU */
#define MAX_MEM_REGION	8
unsigned long __G_ALI_MM_MAIN_MEM_NUM;
unsigned long __G_ALI_MM_MAIN_MEM[MAX_MEM_REGION][2];

/* memory mapping configuration end */

/* heap top address of the see cpu */
unsigned long g_see_heap_top_addr = 0;

/* tv encoder parameters setting start*/

/* default scart output 
       0 : CVBS
	1 : RGB
	2 : SVIDEO
	3 : YUV
*/
long g_tve_default_scart_output = -1;

/* default tv mode */
long g_tve_hd_default_tv_mode = -1;
long g_tve_sd_default_tv_mode = -1;

/* whether use the CVBS output. the invalid value is -1 */
long g_tve_dac_use_cvbs_type = -1;

/* whether use the SVIDEO output. the invalid value is -1 */
long g_tve_dac_use_svideo_type = -1;

/* whether use the RGB output. the invalid value is -1 */
long g_tve_dac_use_rgb_type = -1;

/* whether use the YUV output. the invalie value is -1 */
long g_tve_dac_use_yuv_type = -1;

/* CVBS dac definition */
long g_tve_dac_cvbs = -1;

/* SVIDEO dac definition */
long g_tve_dac_svideo_y = -1;
long g_tve_dac_svideo_c = -1;

/* RGB dac definition */
long g_tve_dac_rgb_r = -1;
long g_tve_dac_rgb_g = -1;
long g_tve_dac_rgb_b = -1;

/* YUV dac definition */
long g_tve_dac_yuv_y = -1;
long g_tve_dac_yuv_u = -1;
long g_tve_dac_yuv_v = -1;

/* tv encoder parameters setting end*/

/* GPIO definition start */

long g_snd_mute_gpio = -1;
long g_snd_chip_type = 0;

long g_usb_device_5v_detect_gpio = -1;
long g_usb_p0_host_5v_gpio = -1;

/* GPIO definition end */

/* PDK Freautes start */

/* select the standard FB drvier */
unsigned long g_support_standard_fb = 0;

unsigned long g_support_isdbt_cc = 0;

//hdmi hdcp on/off
unsigned long g_hdmi_hdcp_enable = 0;

unsigned int g_otp_set_vdac_fs = 0;

// nand flash pinmux select
unsigned long g_nand_pm1_pin_sel = 0;
unsigned long g_nand_pm2_strapin_sel_en = 0;

unsigned long g_enet_speed_gpio = 1;
unsigned long g_enet_link_gpio = 1;

/* PDK Freautes end */

#endif

void customize_board_setting(void);

#endif

