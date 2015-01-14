#ifndef __ADR_SYS_CONFIG_H
#define __ADR_SYS_CONFIG_H

#include <adr_sys_define.h>


/***********************************************************************
 OS object number maro define
*************************************************************************/
#define SYS_OS_MODULE			OS_LINUX

/***********************************************************************
 IC chip
*************************************************************************/
#define SYS_CHIP_ID			S3701C

/***********************************************************************
S.W module configration related marco define
*************************************************************************/
#define FE_DVBC_SUPPORT
#define SYS_PROJECT				SYS_DEFINE_NULL
#define SYS_PROJECT_FE			PROJECT_FE_DVBC
#define SYS_PROJECT_SM          PROJECT_SM_CA//PROJECT_SM_CI
#define SYS_MW_MODULE			SYS_DEFINE_NULL
#define SYS_CA_MODULE			SYS_DEFINE_NULL
#define NAND_FLASH_ONLY
//#define SUPPORT_REMOVE_OSD_UI
/*
define IC SORTING board type as flow:

1 : BGA292
2 : QFP144NMP
3 : QFP144QAM
4 : QFP256
*/
#define IC_SORTING_BOARD		3

/***********************************************************************
 System Hardware related marco define
*************************************************************************/
/*==========Main Hardware Feature==========*/
/*SOC Devices*/
#define SYS_CHIP_MODULE ALI_S3602 // ALI_S3601
#define SYS_CPU_MODULE  CPU_MIPS24KE
#define SYS_CPU_ENDIAN	ENDIAN_LITTLE
#define SYS_GPIO_MODULE	M3602F_GPIO
#define SYS_I2C_MODULE	M6303I2C
#define SYS_SCI_MODULE	GPIO_SCI//UART16550
#define SYS_TSI_MODULE  M3327TSI
#define SYS_DMX_MODULE  M3327DMX
#define SYS_IRP_MOUDLE	ALI25C01//ROCK00//ALI25C00//UM_ZJ//
/*Clock*/
#define SYS_CHIP_CLOCK	27000000
#define SYS_CPU_CLOCK 	396000000
/*Memory*/
#define SYS_SDRAM_SIZE 	256//128
#define SYS_MAIN_BOARD	BOARD_DB_M3701C_01V03
/*Flash*/
#define SYS_FLASH_BASE_ADDR 0xafc00000	// 0xaf000000
#define SYS_FLASH_SIZE      0xe00000
#define ENABLE_SERIAL_FLASH
#define STO_PROTECT_BY_MUTEX	//protocting flashw wirte/erase by mutex

/*==========Peripheral Devices==========*/
/*IIC*/
#if (IC_SORTING_BOARD == 1)
#define I2C_FOR_TUNER           I2C_TYPE_SCB2
#elif (IC_SORTING_BOARD == 2)
#define I2C_FOR_TUNER           I2C_TYPE_SCB0
#elif (IC_SORTING_BOARD == 3)
#define I2C_FOR_TUNER           I2C_TYPE_SCB2
#elif (IC_SORTING_BOARD == 4)
#define I2C_FOR_TUNER           I2C_TYPE_SCB1
#endif

#define I2C_FOR_DEM             I2C_TYPE_SCB0
#define I2C_FOR_SCART           I2C_TYPE_SCB1
#define I2C_FOR_RFM             I2C_TYPE_GPIO0
#define I2C_FOR_EDDC            I2C_TYPE_GPIO1
#define I2C_FOR_HDCP            I2C_TYPE_GPIO2
#define I2C_FOR_EEPROM          I2C_TYPE_GPIO0

/*RFM*/
#define SYS_RFM_MODULE			SYS_DEFINE_NULL//MCBS373
#define SYS_RFM_BASE_ADDR		0xca

/*Tuner*/
//#define SYS_TUNER_MODULE 		ALPSTDAE//DCT7044//TDCCG0X1F//ALPSTDQE
//#define GPIO_I2C_CONTROL_TUNER

/*Scart switcher*/
//#define SCART_AK4707

/*EEPROM*/
#define SYS_EEPROM_BASE_ADDR	0xA0			/* EEPROM base address */
#define SYS_EEPROM_SIZE (8192)
#define TWO_BYTE_WORD_ADDRESS

/*==========Hardware Function switch==========*/
/*HDMI*/
#define HDTV_SUPPORT
#define HDMI_ENABLE     //  enable HDMI in vpo driver because sabbat ui cannot disable it.
#define HDCP_DISABLE 0
/*Network*/
#define NETWORK_SUPPORT

/*Smartcard Controller(CA)*/
#define MULTI_CAS
#define CARD_DETECT_INVERT  1
#define CAS_TYPE	CAS_MG//CAS_NONE//CAS_CONAX//CAS_CRYPTON
//macro define for eeprom
#ifdef MULTI_CAS
//macro DSC_SUPPORT is only needed by CI+
//#define DSC_SUPPORT
#if(CAS_TYPE==CAS_IRDETO)
//#define	IRD_OTA_SUPPORT
#define IRD_FLSH_SIZE	2 //2/4/8

#define IRCA_PS_BY_E2P

#elif(CAS_TYPE==CAS_CONAX)
#define CONAX_NEW_PUB
#define CONAX_AUDIO_LAN_USE
#endif
#endif

/*CI*/
#if (SYS_PROJECT_SM ==PROJECT_SM_CI)
    #define CI_SUPPORT
    #define CONFIG_SLOT_NUM	1
    #define CI_SLOT_NS		CONFIG_SLOT_NUM
#endif

/*==========GPIO Configuration==========*/
#define GPIO_NULL                   255

#define SYS_I2C_SDA     17
#define SYS_I2C_SCL     18
#define SYS_I2C_SDA1    10
#define SYS_I2C_SCL1    11
#define SYS_I2C_SDA2    GPIO_NULL
#define SYS_I2C_SCL2    GPIO_NULL

#define SYS_LNB_POWER_CUT           GPIO_NULL
#define SYS_POWER_GPIO_NUM          24
#define DEMO_RST_GPIO_NUM           42
//#define DEMO_RST_GPIO_NUM2          41
#define POS_SCART_POWER             GPIO_NULL
#define ATA2LAN_CS_GPIO_NUM			GPIO_NULL
#define MUTE_GPIO_NUM               37
#define MUTE_GPIO_POL               0
#define MUTE_GPIO_EXIST             1

/*Front panel*/
#define DB_M3701

#define PAN_LBD_A	0 
#define PAN_LBD_B	1
#define PAN_LBD_C	2 
#define PAN_LBD_D	3 

#define FP_LOCK_FUNC	PAN_LBD_A

/*IR standby wakeup key*/
#define IR_HKEY_POWER1	0x60df708f	// STB ir power key
#define IR_HKEY_POWER2	0x10efeb14	// nmp ir power key
#define IR_HKEY_POWER3	0	
#define IR_HKEY_POWER4	0
#define IR_HKEY_POWER5	0
#define IR_HKEY_POWER6	0
#define IR_HKEY_POWER7	0
#define IR_HKEY_POWER8	0

#define SLOT_SCAN                   0
#define SHADOW_SCAN                 1
#define FP_SCAN_TYPE                SHADOW_SCAN
#define STANDBY_LED_POS             68//74//86
#define FP_LOCK_GPIO_NUM            GPIO_NULL//89
#define FP_LOCK_GPIO_NUM2           GPIO_NULL//88
#define FP_STANDBY_GPIO_NUM         68// 74
#define FP_STB_GPIO_NUM				70
#define FP_CLOCK_GPIO_NUM           17//60
#define FP_DATA_GPIO_NUM            18//61
#define FP_KEY1_GPIO_NUM            GPIO_NULL//57
#define FP_KEY2_GPIO_NUM            GPIO_NULL
#define FP_COM1_GPIO_NUM            GPIO_NULL//59
#define FP_COM2_GPIO_NUM            GPIO_NULL//58
#define FP_COM3_GPIO_NUM            GPIO_NULL//63
#define FP_COM4_GPIO_NUM            GPIO_NULL//62

/*==========Video DAC==========*/
#define VDAC_USE_CVBS_TYPE      CVBS_1
//#define VDAC_USE_RGB_TYPE       RGB_1
#define VDAC_USE_YUV_TYPE       YUV_1
//#define VDAC_USE_SVIDEO_TYPE       SVIDEO_1

#define CVBS_DAC                DAC3

#define SVIDEO_DAC_Y            DAC2
#define SVIDEO_DAC_C            DAC1

#define YUV_DAC_Y               DAC2
#define YUV_DAC_U               DAC1
#define YUV_DAC_V               DAC0

#define RGB_DAC_R               DAC0
#define RGB_DAC_G               DAC2
#define RGB_DAC_B               DAC1


/***********************************************************************
Chunk ID marco define
*************************************************************************/
#define	LOGO_ID					0x02FD0100
#define	RADIO_LOGO_ID			LOGO_ID//0x02FD0200
#define	BOOT_LOGO_ID			LOGO_ID
#define	MENU_LOGO_ID			LOGO_ID//0x02FD0200//0x02FD0300
#define	MAINCODE_ID				0x01FE0100
#define	CADATA_ID				0x08F70100
#define	MEDIA_LOGO_ID			LOGO_ID
#define HDCPKEY_CHUNK_ID (HDCPKEY_CHUNID_TYPE |0x0100)


/***********************************************************************
Video related marco define
***********************************************************************/
#define VIDEO_DEBLOCKING_SUPPORT  //to improve video quality
#define VIDEO_SUPPORT_EXTRA_DVIEW_WINDOW
#define Enable_108MHz_Video_Sample_Rate
#define VDEC_AV_SYNC
#define VIDEO_OUTPUT_BETTER_VISION
#define VDEC27_SUPPORT_COLORBAR
//#define VIDEO_OVERSHOOT_SOLUTION
#define VIDEO_SYNC_ISSUE
//#define SUPPORT_CVBS_PAL
#define NEW_AVSYNC

/***********************************************************************
Audio related marco define
*************************************************************************/
#define AUDIO_SPECIAL_EFFECT	/* play mpeg audio file*/
#define MULTI_AUDIO_PID
//#define AUDIO_DESCRIPTION_SUPPORT
#define DVBT_BEE_TONE
#define CODEC_I2S					(0x0<<1)
#define CODEC_LEFT					(0x1<<1)
#define CODEC_RIGHT					(0x2<<1)
#define AC3DEC						0


/***********************************************************************
OSD related marco define
*************************************************************************/
//set CLUT8 for osd layer2
#define COLOR_N						256//(0xFFFFFFFF+1)
#define OSD_MAX_WIDTH				(1280)//720
#define OSD_MAX_HEIGHT				(720)//576
#define OSD_STARTCOL ((1280 - OSD_MAX_WIDTH)>>1)
#define OSD_STARTROW_N ((720 - OSD_MAX_HEIGHT)>>1)
#define OSD_STARTROW_P ((720 - OSD_MAX_HEIGHT)>>1)

#define	BIT_PER_PIXEL				32
#define OSD_TRANSPARENT_COLOR			0//0xFF
#define OSD_TRANSPARENT_COLOR_BYTE 		0//0xFF
#define	IF_GLOBAL_ALPHA				FALSE
#define	FACTOR						0


/***********************************************************************
SI & search related macro define
*************************************************************************/
//SI constant define
#define AMSSIP_MAX_PROG_NUM		500         //max program count
#define AMSSIP_TP_MAX_PROG_NUM	128		//max channel count, one TP for PAT/PMT/SDT/NIT
#define AMSSIP_CAT_EMM_MAX_CNT		32		//MAX EMM Count
#define AMSSIP_PMT_MAX_AUDIO_NUM	8		//max audio count, one channel
#define AMSSIP_PMT_MAX_CA_NUM		16		//max CA Count
#define AMSSIP_PMT_MAX_ES_CNT		16		//PMT max element ts count
#if 1	//only support actual
#define AMSSIP_NIT_MAX_NETWORK_NUM	1		//max network count, for NIT, if need support NIT other, maybe need inc it
#else	//support other
#define AMSSIP_NIT_MAX_NETWORK_NUM	16		//NIT other, how much???
#endif
#define AMSSIP_NIT_MAX_TS_NUM	128		//max TS count, one Network
#if 1	//only support actual
#define AMSSIP_SDT_MAX_TS_NUM	1		//max TS count, for SDT, if need support SDT other, then inc it
#else	//support other
//#define AMSSIP_SDT_MAX_TS_NUM	128		//SDT other
#endif
#define AMSSIP_NET_NAME_MAX_LEN	32
#define AMSSIP_BAT_MAX_BQT_NUM		16		//mas Bouquet Count
#define AMSSIP_BAT_BQT_MAX_PROG_NUM AMSSIP_MAX_PROG_NUM		//max channel count, one Bouquet
#define AMSSIP_PMT_AUDIO_639LANG_MAX_CNT 8	//Audio 639 lang max count
#define AMSSIP_BQT_NAME_MAX_LEN	32		//Bouquet name max length
#define AMSSIP_SERVICE_NAME_MAX_LEN	 32          //Service name max length
#define AMSSIP_SDT_NAME_BUF_LEN    (AMSSIP_MAX_PROG_NUM*AMSSIP_SERVICE_NAME_MAX_LEN*2)  //servier name and provider name total max length
#define AMSSIP_SDT_MAX_REF_NUM	16		//service reference channel max count, one service
#define AS_BAND_MAX_CNT 128 				//search tp freq band count
#define AMSSIP_PRIV_DESC_MAX_CNT	16          //max private descriptors count
#define AMSSIS_PRIV_DATA_POOL_SIZE      (32*1024)      //max private descriptors data in one ts

/***********************************************************************
DB related marco define
*************************************************************************/
#define DB_CAS_SUPPORT
#define DB_RAM_BACKUP
#define DB_USE_UNICODE_STRING
#define DB_VERSION					40
#define MAX_PROG_NUM				500
#define MAX_TP_NUM					250
#define MAX_SAT_NUM					1
#define SUPPORT_DB_FS    /* support DB data is saved as a file in filesystem */


/***********************************************************************
EPG related marco define
*************************************************************************/
#define SYS_EPG_MODULE SYS_DEFINE_NULL
#define EPG_MULTI_TP
#define EPG_OTH_SUPPORT
//#define EPG_UPDATE_BY_CRC
#define EPG_NIBBLE2_SUPPORT
#define EPG_PARENTAL_SUPPORT
//#define EPG_COMPONENT_SUPPORT
#define EPG_SCHEDULE_TABLE_ID_NUM	2
#define EPG_LANGUAGE_COUNT			3
#define EPG_ACTIVE_SERVICE_CNT		5


/***********************************************************************
NVOD related marco define
*************************************************************************/
#define NVOD_FEATURE


/***********************************************************************
Character set related marco define
*************************************************************************/
#define GB2312_SUPPORT
#define ISO8859_SUPPORT
#define ISO_5937_SUPPORT


/***********************************************************************
OTA related marco define for data backup
*************************************************************************/
//#define _BUILD_OTA_E_
//#define OTA_POWEROFF_SAFE
#define OTA_START_BACKUP_FLAG			0xFF
#define OTA_START_END_FLAG				0xFE
#define RESTORE_DATA_ADDR				0xAFD20000
#define BACKUP_START_FLAG				0x55aa5a5a

#define MAIN_FREQ_DEFAULT				29900
#define MAIN_SYM_DEFAULT				6875
#define MAIN_QAM_DEFAULT				6

#define OTA_SWAP_BUF_LEN           		(256*1024)

#define OTA_COMPRESSED_BUF_LEN     			0x500000
#define OTA_UNCOMPRESSED_BUF_LEN   			0xA00000
#define OTA_UNCOMPRESSED_BUF_ADDR   		(__MM_FB_TOP_ADDR-OTA_UNCOMPRESSED_BUF_LEN)//0XA1600000
#define OTA_COMPRESSED_BUF_ADDR    			(OTA_UNCOMPRESSED_BUF_ADDR-OTA_COMPRESSED_BUF_LEN)

#define USB_UPG_DVBC


/***********************************************************************
PVR related marco define for data backup
*************************************************************************/
#ifndef _BUILD_OTA_E_
#define DVR_PVR_SUPPORT
#define RECORD_SUPPORT
#define USB_SAFELY_REMOVE_SUPPORT
#define USB_UPGRADE_SUPPORT_LONG_FILENAME
#define DVR_PVR_SUPPORT_SUBTITLE    1
//#define USB_SUPPORT_HUB
#define PVR_MULTI_VOLUME_SUPPORT
#define H264_SUPPORT
#define PVR_SUPPORT
//#define PVR_TMS_SUPPORT
#endif


/***********************************************************************
SI/PSI and program search related marco define
*************************************************************************/
#define LIB_TSI3_FULL
#define PSI_MONITOR_SUPPORT
#define SEARCH_DEFAULT_FTAONLY			0
#define SYS_PSEARCH_SCAN_TP_ALL			SYS_FUNC_ON
#define DUPLICATE_PID_SUPPORT // for monitor
#define SI_SUPPORT_MUTI_DMX

#define SI_FILTER_ONDMX
//#define SI_FILTER_ONSIE


/***********************************************************************
PUB related marco define
************************************************************************/
#define NEW_DEMO_FRAME		// for libpub
#define CHANCHG_VIDEOTYPE_SUPPORT


/***********************************************************************
TDT related marco define
************************************************************************/
#define _SYNC_TIME_ENABLE_


/***********************************************************************
TELETEXT/SUBTITILE related marco define
************************************************************************/
//#define SUBTITLE_ON


/***********************************************************************
Miscellaneous marco define
*************************************************************************/
#define EASY_DM_SWITCH
#define SELECT_SAT_ONLY
#define ENABLE_FEED_POWER
//#define REFACTOR_PRINTF// this macro for sprintf() bug

//#define NEW_CLIB_FUNCTION
#define WANT_FLOATING_POINT_IN_PRINTF

#define DVR_PVR_SUPPORT
#define PVR3_SUPPORT
#define USBUPG_MODE_UNZIP

#define SYS_NETWORK_MODULE 	NET_ALIETHMAC

//#define AVC_SUPPORT_UNIFY_MEM
#define NOT_MONITOR_NIM

//#define SUPPORT_64M_MEM
#ifdef SUPPORT_64M_MEM
#define ONE_RECODER_PVR
#endif

#define DUAL_ENABLE

//#define SHOW_ALI_DEMO_ON_SCREEN

//#define HDMI_TV_TEST
#define DUAL_VIDEO_OUTPUT_USE_VCAP
#define HDMI_1080P_SUPPORT

//#define SHOW_TWO_TUNER_LOCK_STATUS

/***********************************************************************
 AP feature support  maro define
*************************************************************************/

//#define DATA_BROADCAST  

/*==========AP and UI  use GPIO configure==========*/
#define EXTERNAL_PULL_HIGH		TRUE    // for I2C_gpio.c

#if(SYS_MAIN_BOARD == BOARD_DB_M3701C_01V03)
#define SYS_12V_SWITCH      SYS_FUNC_OFF
#define SYS_LNB_POWER_OFF   SYS_FUNC_ON

#define SYS_LNB_SHORT_DET   SYS_FUNC_OFF
#define SYS_12V_SHORT_DET   SYS_FUNC_OFF
//#define SYS_12V_SHORT_DET_GPIO

#define FRONT_PANEL_TYPE        1
#endif

/*==========other ui and ap use macro==========*/
// for video decoder
#define SYSTEM_BUF_BLOCK_SIZE		2324
#define SYSTEM_BUF_MAX_BLOCK		4

#ifdef CI_PLUS_SUPPORT //CI+ begin
//#define FS_STDIO_SUPPORT

//porting openssl
//#define OPENSSL_NO_FP_API

//#define OPENSSL_NO_BIO
//#define OPENSSL_NO_ENGINE

#define CI_TEST
//#define CI_PLUS_SUPPORT
//#define DSC_SUPPORT
//#define CI_PLUS_SERVICESHUNNING
//#define NETWORK_ID_ENABLE
#endif  //CI+ end

// for ChChg TSG player
//ifndef CI_PLUS_SUPPORT
//#define CC_USE_TSG_PLAYER
//#define CI_SLOT_DYNAMIC_DETECT
//#define CI_SEND_CAPMT_OK_TO_APP
//#endif

//#define OGG_36

#ifdef _BUILD_OTA_E_
	#undef CI_SLOT_DYNAMIC_DETECT
	#define DMX_XFER_V_ES_BY_DMA 	//added for s3601. transfer video ES by DMA, others by CPU copy
	#undef CI_SUPPORT
	#undef CC_USE_TSG_PLAYER
	#undef MP2_0_SUPPORT
    #undef MULTI_VOLUME_SUPPORT
	#undef PS_TS_SUPPORT
	#undef DYNAMIC_PID_SUPPORT
    #undef NETWORK_SUPPORT
#endif

//#define SMALL_FIFO_3602		// for 3602/3381 smart card driver, it must be defined.

#ifdef ALI_SHUTTLE_MODIFY
#define SUPPORT_SCRAMBLE_TTX_SUBT
#endif

#define QAM_ONLY_USAGE          SYS_FUNC_ON
#define TUNER_I2C_BYPASS
#define TTX_COLOR_NUMBER 256

#define VEGA_SUPPORT

#define HDCP_IN_FLASH

#define OTA_SUPPORT

#define TEST_COMMAND
#ifdef TEST_COMMAND
//#define TC_SFU
#define TC_OSD2
#define TC_TASK
#define TC_FW
#define TC_DUMP
#define TC_COMTEST
#define TC_STANDBY
#endif

//#define OSD_USE_ALISURFACE2D
//#define PART_USE_SURFACE2D
//#define OVG_MMU_VER

//#define TEST_ITEM_OPEN
//#define PVR_HINT_HIDE
//#define FOCUS_SLIDE_DISABLE
//#define FIRST_VIDEO_FASTSHOW

//define the font render mode
#define FONT_RENDER_MONO
//#define FONT_RENDER_4BITS
//#define FONT_RENDER_8BITS

#define FAST_FREE_PLAY
//#define NIM_REG_ENABLE
#define BOOTLOADER_SHOW_LOGO
#define MIRACAST_SUPPORT
#define DLNA_SUPPORT
//#define DEO_VIDEO_QUALITY_IMPROVE  /*temporary close*/

//#define SFU_AUTO_TEST
//#define AD_TEST
//#define IC_VERIFY_TEST

#define NEW_DMX_LIB

#endif	// __ADR_SYS_CONFIG_H
