#include <adr_sys_config.h>

#include <errno.h>  
#include <fcntl.h>  
#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/stat.h>  
#include <sys/wait.h>  
#include <fcntl.h>

#include <assert.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#include <adr_basic_types.h>
#include <osal/osal_timer.h>
#include <osal/osal.h>
#include <hld/deca/adr_deca_dev.h>
#include <hld/deca/adr_deca.h>
#include <hld/snd/adr_snd_dev.h>
#include <hld/snd/adr_snd.h>
#include <hld/vbi/adr_vbi.h>
#include <hld/sdec/adr_sdec.h>
#include <hld/dis/adr_vpo.h>
#include <hld/decv/adr_vdec_driver.h>
#include <hld/decv/adr_decv_avc.h>
#include <hld/osd/adr_osddrv.h>
#include <hld/rfm/adr_rfm.h>
#include <hld/avsync/adr_avsync.h>
#include <hld/misc/rfk.h>
#include <hld/pan/adr_pan.h>
#include <hld/adr_hld_dev.h>
#include <hld/nim/adr_nim_tuner.h>
#include <hld/dmx/Ali_DmxLib.h>
#include <hld/dis/adr_vpo.h>
#include <hld/pan/adr_pan_dev.h>

#include <api/libc/log.h>
#include <api/libpub/lib_pub.h>
#include <api/libsi/si_monitor.h>
#include <api/libsi/lib_epg.h>
#include <api/libsi/si_tdt.h>
#include <api/libca/udrm.h>
#include <android/log.h>

#include "alidvb_system.h"
#include "epg.h"

#include "board_config_cstm.h"

#include<sys/types.h>   
#include<sys/socket.h>   
#include<stdio.h>   
#include<sys/un.h>   
#include<unistd.h>   
#include<stdlib.h>   
#include <stddef.h>   

#define SERVER_NAME "@server_socket" 


#define LOG_TAG    "ALiDVB_System"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define SYSTEM_DEBUG	LOGD
#define SYSTEM_NOTICE	LOGI
#define SYSTEM_ERROR	LOGE

#ifndef SUPPORT_GOSPELL_BOARD
//#define SUPPORT_YINHE_BOARD
//#define SUPPORT_DTMB
//#define SUPPORT_DEMO_DVBS2  // DEMO_BOARD_04V01
#endif

#ifdef SUPPORT_YINHE_BOARD

#ifdef SUPPORT_DTMB
#define I2C_FOR_TUNER (0x1)
#else
#define I2C_FOR_TUNER (0x0)
#endif

#else
#define I2C_FOR_TUNER (0x1)
#endif


struct vdec_device *g_decv_dev;
struct vdec_device *g_decv_dev2;
struct vdec_device *g_decv_avc_dev;
struct deca_device *g_deca_dev;
struct dmx_device *g_dmx_dev;
struct dmx_device *g_dmx_dev2;
struct dmx_device *g_dmx_dev3;
struct nim_device *g_nim_dev;
struct nim_device *g_nim_dev2;
struct snd_device *g_snd_dev;
struct sdec_device *g_sdec_dev;
struct vbi_device *g_vbi_dev;
//extern struct osd_device *g_osd_dev;
struct sto_device *g_sto_dev;
struct vpo_device *g_vpo_dev;
struct vpo_device *g_sd_vpo_dev;
struct rfm_device *g_rfm_dev;
struct pan_device *g_pan_dev;
struct avsync_device *g_avsync_dev;
struct osd_device *osd_dev;

extern BOOL db_createview_filter(UINT8 node_type, const UINT8 *node, UINT16 filter_mode, UINT32 param);
extern INT32 db_node_packer(UINT8 node_type, const UINT8*src_node, UINT32 src_len,UINT8*packed_node,UINT32 *packed_len);
extern INT32 db_node_unpacker( UINT8 node_type,const UINT8 *src_node,UINT32 src_len, UINT8 *unpack_node, UINT32 unpack_len);
extern BOOL db_same_node_checker(UINT8 n_type, const void* old_node, const void* new_node);
extern BOOL db_node_finder(UINT8 n_type, const void* node, UINT8 *name,UINT32 name_len);

#define DVBS_MAX_NUM 4
#define DVBS_MAX_LEN 16

static char g_HLD_NIM_DVBS_NAME[DVBS_MAX_NUM][DVBS_MAX_LEN]
    = {"NIM_S3501_0","NIM_S3501_1","NIM_S3501_2","NIM_S3501_3"};


//* DVB-S2 *//
static int nim_tuner_attatch_s2(struct QPSK_TUNER_CONFIG_API *qpsk_tuner, unsigned int demod_num)
{
	memset(qpsk_tuner, 0, sizeof(struct QPSK_TUNER_CONFIG_API));
	qpsk_tuner->nim_Tuner_Init                = NULL;	
	qpsk_tuner->nim_Tuner_Control             = NULL;	
	qpsk_tuner->nim_Tuner_Status	          = NULL;	
	qpsk_tuner->config_data.recv_freq_low     = 900;	
	qpsk_tuner->config_data.recv_freq_high    = 2200;        
	qpsk_tuner->tuner_config.i2c_type_id      = I2C_FOR_TUNER;		
	qpsk_tuner->ext_dm_config.i2c_type_id     = I2C_FOR_TUNER;
	qpsk_tuner->tuner_id=AV_2012;
#ifdef SUPPORT_GOSPELL_BOARD
	qpsk_tuner->ext_dm_config.i2c_base_addr   = 0x66;   //3501 board dvbs2 i2c base address
	qpsk_tuner->tuner_config.c_tuner_base_addr = 0xc6;   //SYS_TUN_BASE_ADDR;
/*bit0:QPSK_FREQ_OFFSET,bit1:EXT_ADC,bit2:IQ_AD_SWAP,bit3:I2C_THROUGH,bit4:polar revert bit5:NEW_AGC1,bit6bit7:QPSK bitmode:
	                                00:1bit,01:2bit,10:4bit,11:8bit*/
	qpsk_tuner->config_data.qpsk_config       =  0x29;  
	SYSTEM_DEBUG("qpsk_tuner->config_data.qpsk_config=0x%x\n",qpsk_tuner->config_data.qpsk_config);
#else

    switch(demod_num)
    {
        case 1:
	        qpsk_tuner->ext_dm_config.i2c_base_addr   = 0x06;   //3501 fullnim 1 i2c base address
	        break;
        case 2:
	        qpsk_tuner->ext_dm_config.i2c_base_addr   = 0x46;   //3501 fullnim 2 address
	        break;
        case 3:
	        qpsk_tuner->ext_dm_config.i2c_base_addr   = 0x86;   //3501 fullnim 3 base address
	        break;
        default:
	        qpsk_tuner->ext_dm_config.i2c_base_addr   = 0x66;   //3501 board dvbs2 i2c base address
	        break;            
    }                 
	qpsk_tuner->tuner_config.c_tuner_base_addr = 0xc2;   //SYS_TUN_BASE_ADDR;    
	switch(demod_num)
	{
      case 3:
	    qpsk_tuner->config_data.qpsk_config       = 0x29;
        break;
      default:
        qpsk_tuner->config_data.qpsk_config       = 0x69;
        break;
	}
#endif
    qpsk_tuner->demod_index = demod_num; //
	return 0;
}

int nim_init_s2(unsigned int demod_num)
{
	int ret;
	struct nim_device *nim_dev;
	struct QPSK_TUNER_CONFIG_API QAM_Tuner_Cfg;
	nim_tuner_attatch_s2(&QAM_Tuner_Cfg, demod_num);
	ret = nim_m3501_attach(&QAM_Tuner_Cfg); 
	SYSTEM_DEBUG("nim_m3501_attach = %d!\n", ret);
    nim_dev = (struct nim_device *)dev_get_by_name(g_HLD_NIM_DVBS_NAME[demod_num]);
    SYSTEM_DEBUG("dev_get_by_name = 0x%x!\n",nim_dev);
	//nim_dev = (struct nim_device *)dev_get_by_id(HLD_DEV_TYPE_NIM, 0);
	ret |= nim_open(nim_dev);
	SYSTEM_DEBUG("nim_open = %d!\n",ret);
	return ret;
}

static int qam_tuner_attatch(int demod_index, int tuner_id, enum nim_dvbc_mode is_j83b)
{
	struct QAM_TUNER_CONFIG_API QAM_Tuner_Cfg;
	unsigned char NIM_MODE = 0;
	unsigned char NIM_SAMPLE = 0;

	memset(&QAM_Tuner_Cfg, 0, sizeof(struct QAM_TUNER_CONFIG_API));
	
	if (NIM_DVBC_J83B_MODE == is_j83b)
	{
		NIM_MODE   =  NIM_DVBC_J83B_MODE;
	}
	else
	{
		NIM_MODE   =  NIM_DVBC_J83AC_MODE;
		
	}

	SYSTEM_DEBUG("[%s]line=%d,tuner_id=0x%x\n",__FUNCTION__,__LINE__,tuner_id);
	
	QAM_Tuner_Cfg.tuner_id = tuner_id;
	QAM_Tuner_Cfg.demod_index =	demod_index;
	switch(tuner_id)
	{
		case DCT70701:
			{
				/****************DCT70701****************/
				NIM_SAMPLE                                           = NIM_SAMPLE_CLK_54M;
				QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MAX           = 0xb8;
				QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MIN           = 0x14;
				QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MAX           = 0xFF;
				QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MIN           = 0x00;
				QAM_Tuner_Cfg.tuner_config_data.AGC_REF              = 0x80;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_special_config = 0x01; // RF AGC is disabled
				QAM_Tuner_Cfg.tuner_config_ext.c_chip                 = Tuner_Chip_PHILIPS;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_agc_top        = 1;//7; /*1 for single AGC, 7 for dual AGC */
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_base_addr      = 0xC0;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_crystal        = 4;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_ref_divratio   = 64; 
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_step_freq      = 62.5;
				QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq        = 36000;
				QAM_Tuner_Cfg.qam_mode                               = NIM_MODE | NIM_SAMPLE;
				QAM_Tuner_Cfg.tuner_config_ext.i2c_type_id           = I2C_FOR_TUNER;
                break;
			}

		case RT820:
			{
				/****************RT820C****************/
				NIM_SAMPLE                                           = NIM_SAMPLE_CLK_27M;
				QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MAX           = 0xBA;
				QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MIN           = 0x2A;
				QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MAX           = 0xFE;
				QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MIN           = 0x01;
				QAM_Tuner_Cfg.tuner_config_data.AGC_REF              = 0x80;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_special_config = 0x01; // RF AGC is disabled
				QAM_Tuner_Cfg.tuner_config_ext.c_chip			     = Tuner_Chip_NXP;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_agc_top	     = 1;//7; /*1 for single AGC, 7 for dual AGC */
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_base_addr      = 0x34;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_crystal	     = 4;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_ref_divratio   = 64; 
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_step_freq	     = 62.5;
				QAM_Tuner_Cfg.qam_mode                               = NIM_MODE | NIM_SAMPLE;
				if (NIM_DVBC_J83B_MODE == NIM_MODE)
				{
					QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq    = 4063;
				}
				else
				{
					QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq    = 5070;
				}
				QAM_Tuner_Cfg.tuner_config_ext.i2c_type_id = I2C_FOR_TUNER;
				break;
			}

		case TDA18250:
			{
				if(demod_index<1)   //on board tuner.				
				{
					NIM_SAMPLE                                           = NIM_SAMPLE_CLK_27M;
					QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MAX           = 0xBA;
					QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MIN           = 0x2A;
					QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MAX           = 0xE0;
					QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MIN           = 0x10;
					QAM_Tuner_Cfg.tuner_config_data.AGC_REF              = 0x80;
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_special_config = 0x01; // RF AGC is disabled
					QAM_Tuner_Cfg.tuner_config_ext.c_chip                 = Tuner_Chip_NXP;
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_agc_top        = 3;
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_base_addr      = 0xC4;
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_crystal        = 4;
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_ref_divratio   = 64;
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_step_freq      = 62.5;
					QAM_Tuner_Cfg.qam_mode                               = NIM_MODE | NIM_SAMPLE;
					if (NIM_DVBC_J83B_MODE == NIM_MODE)
					{
						QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq    = 3900;
						QAM_Tuner_Cfg.tuner_config_ext.c_tuner_freq_param  = 0x0C;
					}
					else
					{
						QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq    = 5000;
						QAM_Tuner_Cfg.tuner_config_ext.c_tuner_freq_param  = 0x09;
					}
	                QAM_Tuner_Cfg.tuner_config_ext.i2c_type_id           =  I2C_FOR_TUNER; // I2C_TYPE_GPIO;
				}    
				else             //full nim
				{
					NIM_SAMPLE                                           = NIM_SAMPLE_CLK_27M;
					QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MAX           = 0xBB;
					QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MIN           = 0x2A;
					QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MAX           = 0xFF;
					QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MIN           = 0x86;
					QAM_Tuner_Cfg.tuner_config_data.AGC_REF              = 0x80;
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_special_config = 0x00; // RF AGC is disabled
					QAM_Tuner_Cfg.tuner_config_ext.c_chip                 = Tuner_Chip_NXP;
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_agc_top        = 1;
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_base_addr      = 0xc0;
                    QAM_Tuner_Cfg.tuner_config_ext.i2c_type_id           =  I2C_FOR_TUNER; //I2C_TYPE_GPIO; // I2C_TYPE_GPIO;
					QAM_Tuner_Cfg.ext_dem_config.i2c_base_addr            = 0x18;          //0x18;
					QAM_Tuner_Cfg.ext_dem_config.i2c_type_id              = I2C_FOR_TUNER; //I2C_TYPE_GPIO;
					
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_crystal        = 16;
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_ref_divratio   = 64;
					QAM_Tuner_Cfg.tuner_config_ext.c_tuner_step_freq      = 63;
					QAM_Tuner_Cfg.qam_mode                               = NIM_MODE | NIM_SAMPLE;
					
					if (NIM_DVBC_J83B_MODE == NIM_MODE)
					{
						QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq    = 3900;
						QAM_Tuner_Cfg.tuner_config_ext.c_tuner_freq_param  = 0x0C;
					}
					else
					{
						QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq    = 5000;
						QAM_Tuner_Cfg.tuner_config_ext.c_tuner_freq_param  = 0x09;
					}
	                
				}
                break;
			}

		case ALPSTDAE:
			{
				NIM_SAMPLE                                           = NIM_SAMPLE_CLK_54M;
				QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MAX           = 0xBA;
				QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MIN           = 0x2A;
				QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MAX           = 0xFF;
				QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MIN           = 0x00;
				QAM_Tuner_Cfg.tuner_config_data.AGC_REF              = 0x80;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_special_config = 0x01; // RF AGC is disabled
				QAM_Tuner_Cfg.tuner_config_ext.c_chip                 = Tuner_Chip_ALPS;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_agc_top        = 3;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_base_addr      = 0xC2;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_crystal        = 4;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_ref_divratio   = 64; 
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_step_freq      = 62.5;
				QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq        = 36125;
				QAM_Tuner_Cfg.qam_mode                               = NIM_MODE | NIM_SAMPLE;
				QAM_Tuner_Cfg.tuner_config_ext.i2c_type_id           = I2C_FOR_TUNER;
                break;
			}

		case MXL603:
			{
				NIM_SAMPLE                                           = NIM_SAMPLE_CLK_27M;
				QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MAX           = 0xBA;
				QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MIN           = 0x2A;
				QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MAX           = 0xFE;
				QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MIN           = 0x01;
				QAM_Tuner_Cfg.tuner_config_data.AGC_REF              = 0x80;
#ifdef SUPPORT_DTMB
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_special_config = (0x80|0x04|0x01); // bit7:DTMB/DVBC Mode,bit2:IQ swap,bit0:RF AGC is disabled
#else
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_special_config = 0x01; // RF AGC is disabled
#endif
				QAM_Tuner_Cfg.tuner_config_ext.c_chip                 = Tuner_Chip_NXP;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_agc_top        = 1;//7; /*1 for single AGC, 7 for dual AGC */
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_base_addr      = 0xC0;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_crystal        = 16;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_ref_divratio   = 64;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_step_freq      = 62.5;
				QAM_Tuner_Cfg.qam_mode                               = NIM_MODE | NIM_SAMPLE;
				if (NIM_DVBC_J83B_MODE == NIM_MODE)
				{
#ifdef SUPPORT_DTMB
					QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq    = 36150;
#else
					QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq    = 5000;
#endif
				}
				else
				{
#ifdef SUPPORT_DTMB
					QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq	  = 36150;
#else
					QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq	  = 5000;
#endif
				}
				QAM_Tuner_Cfg.tuner_config_ext.i2c_type_id           = I2C_FOR_TUNER;
				break;
			}

		case MXL203:
			{
				NIM_SAMPLE                                           = NIM_SAMPLE_CLK_27M;
				QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MAX           = 0xba;
				QAM_Tuner_Cfg.tuner_config_data.RF_AGC_MIN           = 0x2a;
				QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MAX           = 0xff;
				QAM_Tuner_Cfg.tuner_config_data.IF_AGC_MIN           = 0x00;
				QAM_Tuner_Cfg.tuner_config_data.AGC_REF              = 0x80;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_special_config = 0x01;// RF AGC is disabled
				QAM_Tuner_Cfg.tuner_config_ext.c_chip                 = Tuner_Chip_ALPS;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_agc_top        = 3;//7; /*1 for single AGC, 7 for dual AGC */
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_base_addr      = 0xC0;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_crystal        = 48;//24;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_ref_divratio   = 64;
				QAM_Tuner_Cfg.tuner_config_ext.c_tuner_step_freq      = 62.5;
				QAM_Tuner_Cfg.tuner_config_ext.w_tuner_if_freq        = 7200;
				QAM_Tuner_Cfg.qam_mode                               = NIM_MODE | NIM_SAMPLE;
				QAM_Tuner_Cfg.tuner_config_ext.i2c_type_id           = I2C_FOR_TUNER;
                break;
			}

		default:
			{
				SYSTEM_DEBUG("[ERR] no tuner available!\n");
				NIM_SAMPLE                                           = NIM_SAMPLE_CLK_27M;
				QAM_Tuner_Cfg.qam_mode                               = NIM_MODE | NIM_SAMPLE;
				break;
			}
	}

	return nim_s3202_attach(&QAM_Tuner_Cfg);

}

int qam_init_tuner(int demod_index)
{
	int ret=0;
	int demod_count = 2;
	int tuner_count = 0;
	int i=0;
	int j=0;
	struct nim_device *nim_dev = NULL;
#ifdef SUPPORT_GOSPELL_BOARD
    int tuner_id[]={
    		         MXL603,
		            TDA18250,
		            DCT70701,
		            RT820,
		            ALPSTDAE,
		            MXL203
		           };
#else
    int tuner_id[]={
		            TDA18250,
		            DCT70701,
		            RT820,
		            ALPSTDAE,
		            MXL603,
		            MXL203
		           };
#endif

    tuner_count =sizeof(tuner_id)/sizeof(int);

	for(j=0;j< tuner_count;j++)
	{
		 qam_tuner_attatch(demod_index,tuner_id[j],NIM_DVBC_J83AC_MODE);	//DCT70701
#ifdef SUPPORT_DTMB
    	 nim_dev = (struct nim_device *)dev_get_by_name("NIM_ATBM");
#else
    	 nim_dev = (struct nim_device *)dev_get_by_name("NIM_QAM_S3202");
#endif
	     ret = nim_tunerself_adaption(nim_dev);
	     if(ret>=0)
	     {
	        //qam_tuner_attatch(demod_index,tuner_id[j],NIM_DVBC_J83AC_MODE);	//DCT70701
            //nim_dev = (struct nim_device *)dev_get_by_name("NIM_QAM_S3202");
            ret = nim_open(nim_dev);
       	    SYSTEM_DEBUG("nim_open ret = 0x%x!\n", ret);
			break;
	     }
	}	 

	return ret;	
}

INT32 channel_change_callback(UINT32 event, struct ft_frontend *ft, struct cc_param *param)
{
	switch(event)
	{
		case CC_EVENT_PRE_STOP:
			amsepg_off();
			break;
		case CC_EVENT_POST_PLAY:
			amsepg_on(0, param->es.sat_id, param->es.tp_id, param->es.service_id, EIT_OTHER_PF_SCH, 0);
			break;
		default:
			break;
	}
	
}

void config_tsi(void)
{
    /* set tsi route */
	struct Ali_DmxSrcCtrlStreamParam  DmxSrcCtrl;
	INT32 DmxSrcCtrlStreamId, Ret;

	/* DMX 0 source	*/
	DmxSrcCtrlStreamId = ALi_DmxSrcCtrlStreamOpen(0);
	if(DmxSrcCtrlStreamId < 0)
	{
		SYSTEM_ERROR("%s,%d,DmxSrcCtrlStreamId:%d\n", __FUNCTION__, __LINE__, DmxSrcCtrlStreamId);
	}

#ifdef SUPPORT_DTMB
	memset(&DmxSrcCtrl, 0, sizeof(struct Ali_DmxSrcCtrlStreamParam));
	DmxSrcCtrl.InPutPortId = ALI_DMX_INPUT_PORT_SSI_1;
	DmxSrcCtrl.InputPortAttr = 0x87;
	DmxSrcCtrl.InputPathId = ALI_DMX_INPUT_PATH_0;

#elif defined(SUPPORT_GOSPELL_BOARD)

	gospell_get_tsi_dmx_config(&DmxSrcCtrl);

#elif defined(SUPPORT_DEMO_DVBS2)
	memset(&DmxSrcCtrl, 0, sizeof(struct Ali_DmxSrcCtrlStreamParam));
	DmxSrcCtrl.InPutPortId = ALI_DMX_INPUT_PORT_SPI2B_0; //ALI_DMX_INPUT_PORT_SPI_0;      
	DmxSrcCtrl.InputPortAttr = 0x15f; //0x5f;
	DmxSrcCtrl.InputPathId = ALI_DMX_INPUT_PATH_0;
#else
	memset(&DmxSrcCtrl, 0, sizeof(struct Ali_DmxSrcCtrlStreamParam));
	DmxSrcCtrl.InPutPortId = ALI_DMX_INPUT_PORT_SPI_0;
	DmxSrcCtrl.InputPortAttr = 0x83;
	DmxSrcCtrl.InputPathId = ALI_DMX_INPUT_PATH_0;
#endif

	Ret = Ali_DmxSrcCtrlStreamWrite(DmxSrcCtrlStreamId, &DmxSrcCtrl);
	if(Ret < 0)
	{
		SYSTEM_ERROR("%s,%d,Ret:%d\n", __FUNCTION__, __LINE__, Ret);
	}

	Ret = Ali_DmxSrcCtrlStreamClose(DmxSrcCtrlStreamId);
	if(Ret < 0)
	{
		SYSTEM_ERROR("%s,%d,Ret:%d\n", __FUNCTION__, __LINE__, Ret);
	}

#ifdef SUPPORT_GOSPELL_BOARD
	change_qam_to_ssi_mode();
#endif

#ifdef SUPPORT_DEMO_DVBS2

		unsigned int reg_adr;
		unsigned int bits_clear;
		unsigned int bits_set;

		/*config pinmux ctrl reg0*/
		reg_adr = PINMUX_CTRL_REG0;
		bits_set = 0;
		bits_clear = 0;
		bits_clear |= (1 << XUART2_SEL1_BIT);
		bits_clear |= (1 << AUD_I2SIO_SEL_BIT);
		bits_clear |= (1 << TVENC_SYNC_SEL3_BIT);
		bits_clear |= (1 << XUART2_SEL2_BIT);
		_soc_reg_bits_set32(reg_adr, bits_clear, bits_set);

		/*config pinmux ctrl reg1*/
		reg_adr = PINMUX_CTRL_REG1;
		bits_set = 0;
		bits_clear = 0;
		bits_set |= (1 << ALISSI_SEL2_BIT);
		bits_clear |= ((1 << QAM_SSI_256_SEL2_BIT) | (1 << USB_DEBUG_SEL_BIT));
		_soc_reg_bits_set32(reg_adr, bits_clear, bits_set);
		
#endif


	
}

static void AVInit(void)
{
    struct snd_output_cfg cfg_param;

    g_deca_dev = (struct deca_device *)dev_get_by_id(HLD_DEV_TYPE_DECA, 0);
    g_snd_dev = (struct snd_device *)dev_get_by_id(HLD_DEV_TYPE_SND, 0);
    g_decv_dev = (struct vdec_device *)dev_get_by_id(HLD_DEV_TYPE_DECV, 0);
    g_nim_dev = (struct nim_device *)dev_get_by_id(HLD_DEV_TYPE_NIM, 0);
    g_vpo_dev = (struct vpo_device *)dev_get_by_id(HLD_DEV_TYPE_DIS, 0);
    g_sd_vpo_dev = (struct vpo_device *)dev_get_by_id(HLD_DEV_TYPE_DIS, 1);
    g_decv_avc_dev = (struct vdec_device *)dev_get_by_name("DECV_AVC_0");
    g_avsync_dev = (struct avsync_device *)dev_get_by_id(HLD_DEV_TYPE_AVSYNC, 0);

    /* Setting: vpo do not zoom to full screen when release. */
    //vpo_ioctl( g_vpo_dev, VPO_IO_SET_ZOOM_FAST_RESUME, 0);

    if(RET_SUCCESS!=deca_open(g_deca_dev, AUDIO_MPEG2, AUDIO_SAMPLE_RATE_48, AUDIO_QWLEN_24, 2, 0))
    {
        SYSTEM_ERROR("deca_open failed!!\n");        
    }
    SYSTEM_DEBUG("deca_open ok!!\n");
    if(RET_SUCCESS!=snd_open(g_snd_dev))
    {
        SYSTEM_ERROR("snd_open failed!!\n");
    }
    SYSTEM_DEBUG("snd_open ok!!\n");

    if(RET_SUCCESS != nim_open(g_nim_dev))
    {
        SYSTEM_ERROR("nim_open failed!!\n");
    }
    SYSTEM_DEBUG("nim_open ok!!\n");
    
    //:FIXME only temporary solution
    open("/dev/ali_pe0", O_RDWR);

    if(RET_SUCCESS!=avsync_open(g_avsync_dev))
    {
        SYSTEM_ERROR("avsync_open failed!!\n");
    }

    avsync_adv_param_t adv_params;
    avsync_get_advance_params(g_avsync_dev, &adv_params);
    adv_params.pts_adjust_threshold = 5000; //4000ms
    avsync_config_advance_params(g_avsync_dev, &adv_params);

    SYSTEM_DEBUG("AV init ok!!\n");

    return;
}

static void ams_log_cb(unsigned char *buf)
{
	int level;
	
	if ('D' == buf[0])
	{
		level = ANDROID_LOG_DEBUG;
	}
	else if ('N' == buf[0])
	{
		level = ANDROID_LOG_INFO;
	}
	else if ('E' == buf[0])
	{
		level = ANDROID_LOG_ERROR;
	}
	else
	{
		level = ANDROID_LOG_VERBOSE;
	}
	
	buf += 1;

	__android_log_print(level, LOG_TAG, "%s", buf);

	return;
}

#ifdef SUPPORT_YINHE_BOARD
#ifdef SUPPORT_DTMB
static void reset_dtmb(void)
{
	unsigned int reg_val = 0x0;
	unsigned int reg_adr = 0x0;

	//Reset DTMB -- 0 reset, 1 work
	reg_adr = 0x18000354;
	if (0 == soc_read32(reg_adr, (unsigned char *)(&reg_val), 1))
	{
		reg_val &= ~(1<<26); //GPIO 122 output low  
		soc_write32(reg_adr, (unsigned char *)(&reg_val), 1);
	}
	else
	{
		SYSTEM_ERROR("soc_read32 dwRegAdr[0x%8x] fail \n", reg_adr);
	}

	usleep(1000);

	reg_adr = 0x18000354;
	if (0 == soc_read32(reg_adr, (unsigned char *)(&reg_val), 1))
	{
		reg_val |= 1<<26; //GPIO 122 output high  
		soc_write32(reg_adr, (unsigned char *)(&reg_val), 1);
	}
	else
	{
		SYSTEM_ERROR("soc_read32 dwRegAdr[0x%8x] fail \n", reg_adr);
	}
}
#endif

static void yinhe_pinmux_config(void)
{
	unsigned int reg_val = 0x0;
	unsigned int reg_adr = 0x0;

	reg_adr = 0x18000088;
	if (0 == soc_read32(reg_adr, (unsigned char *)(&reg_val), 1))
	{
		SYSTEM_DEBUG("reg_adr[0x%x]:value[0x%x]\r\n", reg_adr, reg_val);
	}

	reg_adr = 0x1800008c;
	if (0 == soc_read32(reg_adr, (unsigned char *)(&reg_val), 1))
	{
		SYSTEM_DEBUG("reg_adr[0x%x]:value[0x%x]\r\n", reg_adr, reg_val);
	}

	reg_adr = 0x18000438;
	if (0 == soc_read32(reg_adr, (unsigned char *)(&reg_val), 1))
	{
		SYSTEM_DEBUG("after read:reg_adr[0x%x]:value[0x%x]\r\n", reg_adr, reg_val);
		reg_val |= ((1<<27) | (1<<28)); //GPIO 91,92 Enable
		soc_write32(reg_adr, (unsigned char *)(&reg_val), 1);
		soc_read32(reg_adr, (unsigned char *)(&reg_val), 1);
		SYSTEM_DEBUG("after write:reg_adr[0x%x]:value[0x%x]\r\n", reg_adr, reg_val);
	}

	reg_adr = 0x180000f4;
	if (0 == soc_read32(reg_adr, (unsigned char *)(&reg_val), 1))
	{
		SYSTEM_DEBUG("after read:reg_adr[0x%x]:value[0x%x]\r\n", reg_adr, reg_val);
		reg_val |= ((1<<27) | (1<<28)); //GPIO 91,92 Output High
		soc_write32(reg_adr, (unsigned char *)(&reg_val), 1);
		soc_read32(reg_adr, (unsigned char *)(&reg_val), 1);
		SYSTEM_DEBUG("after write:reg_adr[0x%x]:value[0x%x]\r\n", reg_adr, reg_val);
	}

	reg_adr = 0x180000f8;
	if (0 == soc_read32(reg_adr, (unsigned char *)(&reg_val), 1))
	{
		SYSTEM_DEBUG("after read:reg_adr[0x%x]:value[0x%x]\r\n", reg_adr, reg_val);
		reg_val |= ((1<<27) | (1<<28)); //GPIO 91,92 Output
		soc_write32(reg_adr, (unsigned char *)(&reg_val), 1);
		soc_read32(reg_adr, (unsigned char *)(&reg_val), 1);
		SYSTEM_DEBUG("after write:reg_adr[0x%x]:value[0x%x]\r\n", reg_adr, reg_val);
	}

	reg_adr = 0x18000438;
	if (0 == soc_read32(reg_adr, (unsigned char *)(&reg_val), 1))
	{
		SYSTEM_DEBUG("after read:reg_adr[0x%x]:value[0x%x]\r\n", reg_adr, reg_val);
		reg_val &= ~((1<<27) | (1<<28)); //GPIO 91,92 Disable
		soc_write32(reg_adr, (unsigned char *)(&reg_val), 1);
		soc_read32(reg_adr, (unsigned char *)(&reg_val), 1);
		SYSTEM_DEBUG("after write:reg_adr[0x%x]:value[0x%x]\r\n", reg_adr, reg_val);
	}

	
}
#endif

static void system_devices_init(void)
{
    struct QAM_TUNER_CONFIG_API tuner_config;
    struct deca_feature_config deca_config;
    struct snd_feature_config snd_config;
    struct pan_device *PanDev;
    UINT32 i2c_info = 0;
    int ret = 0;
    
    MG_Setup_CRC_Table();

    rfk_init();
    soc_open();

    /* Init log */
    amslog_init();

    amslog_reg_output(ams_log_cb);
    /* Set APP log level */
    amslog_set_level(LOG_APP, LOG_DEBUG);

#ifdef SUPPORT_YINHE_BOARD
    /* reset dtmb */
#ifdef SUPPORT_DTMB
    reset_dtmb();
#endif

    /* set pinmux，init XI2C_1 CLK/SDA pin status */
    yinhe_pinmux_config();
#endif

#if 0
    /* attach and open pan dev */
    pan_attach();
    
    PanDev = (struct pan_device *)dev_get_by_id(HLD_DEV_TYPE_PAN, 0);
    ret = pan_open(PanDev);;
    if(RET_SUCCESS != ret)
    {
        SYSTEM_DEBUG("%s,%d\n", __FUNCTION__, __LINE__);
		
        return;
    } 

    if (0 != pan_config_key_map(PanDev, 2, NULL, 0, 0))
    {
        SYSTEM_DEBUG("%s,%d\n", __FUNCTION__, __LINE__);
    	
        return;
    }	

    if (0 != pan_config_panel_map(PanDev, 2, NULL, 0, 0))
    {
        SYSTEM_DEBUG("%s,%d\n", __FUNCTION__, __LINE__);
    	
        return;
    }

    pan_config_ir_rep_interval(PanDev, 600, 350);

    i2c_info = 0x00000104;		/* linux gpio i2c */		
    if (0 != pan_io_control(PanDev, PAN_DRIVER_SET_I2C, (UINT32)(&i2c_info)))			
    {			
    	SYSTEM_DEBUG("set i2c info error!\n");		
    }

    pan_display(PanDev,"ABCD", 4);
#endif

    /* attach nim dev */
#ifdef SUPPORT_DTMB
    SYSTEM_DEBUG("Select DTMB Nim\n");
    qam_init_tuner(2);

#elif defined(SUPPORT_DEMO_DVBS2)
	SYSTEM_DEBUG("Select DVBS2 Nim\n");

    nim_init_s2(0);

#elif defined(SUPPORT_GOSPELL_BOARD)
	//extern void lnb_set_h_v(UINT32 h_v);
	
	gospell_board_init();

	gospell_nim_init();

	if(gospell_get_board_type() == BOARD_DVBS2)
	{
		SYSTEM_DEBUG("Select DVBS2 Nim\n");
		set_lnb_power(1);
		//UIChChgSet1318VSetCB(lnb_set_h_v);
	}
    
#else
    SYSTEM_DEBUG("Select DVBC Nim\n");
    qam_init_tuner(0);
#endif

    /* attach deca dev */
    memset(&deca_config, 0, sizeof(struct deca_feature_config));
    deca_m36_attach(&deca_config);

    /* attach snd dev */
    memset(&snd_config, 0, sizeof(struct snd_feature_config));
    snd_m36_attach(&snd_config);

    /* attach dmx dev */
    Ali_DmxLibInit();
	
    /* attach vpo dev */
    HLD_vpo_attach();

    /* attach decv dev */
    HLD_vdec_attach();

    /* attach osd dev */
    HLD_OSDDrv_Attach();

    avsync_attach();

    /* Init and config AV related devices */
    AVInit();

    config_tsi();
#ifdef SUPPORT_GOSPELL_BOARD
	#define UDRM_DEBUG SYSTEM_DEBUG
	unsigned short RegValue;
	unsigned int Reg32Value;
#if 1
	ret = UDRMTestModeInit();
	SYSTEM_DEBUG("UDRMTestModeInit ret = %d!\n", ret);

	//ret = UDRMInit();
	//SYSTEM_DEBUG("UDRMInit ret = %d!\n", ret);
	
#if 0

	UTIDriverWriteRegU16(0x880, 0x181);//
	UTIDriverReadRegU16(0x718, &RegValue);
	UTIDriverWriteRegU16(0x718, RegValue | 0x0004); 
	UTIDriverWriteRegU16(0x812,0x00); 
	UTIDriverWriteRegU32(0x8c0,0xE03ff00);
	UTIDriverWriteRegU16(0x810,0x224);


	UTIDriverReadRegU16(0x880, &RegValue);
	UDRM_DEBUG("Reg 0x880 = 0x%x\n", RegValue);
	UTIDriverReadRegU16(0x718, &RegValue);
	UDRM_DEBUG("Reg 0x718 = 0x%x\n", RegValue);
	UTIDriverReadRegU16(0x812, &RegValue);
	UDRM_DEBUG("Reg 0x812 = 0x%x\n", RegValue);
	UTIDriverReadRegU32(0x8C0, &Reg32Value);
	UDRM_DEBUG("Reg 0x8C0 = 0x%x\n", Reg32Value);
	UTIDriverReadRegU16(0x810, &RegValue);
	UDRM_DEBUG("Reg 0x810 = 0x%x\n", RegValue);
#endif
	

#else //bypass mode
{
	#define UDRM_DEBUG SYSTEM_DEBUG
	unsigned short RegValue;
	unsigned int Reg32Value;
	UTI_I2C_init();
	UTIDriverReadRegU16(0x880, &RegValue);
	UDRM_DEBUG("Reg 0x880 = 0x%x\n", RegValue);
	UTIDriverReadRegU16(0x718, &RegValue);
	UDRM_DEBUG("Reg 0x718 = 0x%x\n", RegValue);
	UTIDriverReadRegU16(0x812, &RegValue);
	UDRM_DEBUG("Reg 0x812 = 0x%x\n", RegValue);
	UTIDriverReadRegU32(0x8C0, &Reg32Value);
	UDRM_DEBUG("Reg 0x8C0 = 0x%x\n", Reg32Value);
	UTIDriverReadRegU16(0x810, &RegValue);
	UDRM_DEBUG("Reg 0x810 = 0x%x\n", RegValue);
	SYSTEM_DEBUG("UTI Bypass mode!\n");

}
#endif
#endif
	SYSTEM_DEBUG("system devices init ok!\n");

	return;
}

void Db_default()
{
	UINT32 db_chunk_id, db_addr, db_len;
	amsdb_param_t db_config;
	db_addr = 0xFFFFFFFF;
    	db_len = 64 *1024*5;
	memset(&db_config, 0, sizeof(db_config));
	db_config.max_sat_cnt = 1;
	db_config.sat_node_len = sizeof(S_NODE);
	db_config.max_tp_cnt = 100;
	db_config.tp_node_len = sizeof(T_NODE);
	db_config.max_prog_cnt = 500;
	db_config.prog_node_len = sizeof(P_NODE);
	db_config.filter_callbak = db_createview_filter;
	db_config.pack_callbak = db_node_packer;
	db_config.unpack_callbak = db_node_unpacker;
	db_config.compare_callbak = db_same_node_checker;
	db_config.find_callbak = db_node_finder;
	if(amsdb_init_db(db_addr,db_len, &db_config) != SUCCESS)
	{
		osal_task_sleep(50);
		SYSTEM_ERROR("amsdb_init_db failed once!\n");
		if(amsdb_init_db(db_addr,db_len, &db_config)!= SUCCESS)
		{
			SYSTEM_ERROR("amsdb_init_db failed twice!\n");
			osal_task_sleep(50);
			amsdb_set_default(DEFAULT_DVBC_PROG,0);
		}
	}
	amsdb_create_view(TYPE_SAT_NODE, VIEW_SINGLE_SAT, 1);
	if(amsdb_get_node_cnt(TYPE_SAT_NODE,VIEW_ALL,0) == 0)
	{
		osal_task_sleep(50);
		if(amsdb_get_node_cnt(TYPE_SAT_NODE,VIEW_ALL,0) == 0)
		{
			osal_task_sleep(50);
			amsdb_set_default(DEFAULT_DVBC_PROG,0);
		}
	}
	amsdb_create_view(TYPE_TP_NODE, VIEW_SINGLE_SAT, 1);
	amsdb_create_view(TYPE_PROG_NODE, VIEW_ALL | PROG_TVRADIO_MODE, 0);
}
static int system_modules_init(void)
{
    struct pub_module_config pub_config;
    UINT32 db_chunk_id, db_addr, db_len;
    amsdb_param_t db_config;
    epg_config_t epg_config;
    int ret = 0;
	unsigned int board_type = gospell_get_board_type();

    /* pub init */
    memset(&pub_config, 0, sizeof(pub_config));
    pub_config.dm_enable = FALSE;

    if (libpub_init(&pub_config) != RET_SUCCESS)
    {
        SYSTEM_ERROR("libpub_init failed!\n");
    }
    SYSTEM_DEBUG("libpub init ok!1111\n");
    amscc_reg_callback(channel_change_callback);

    /* database init */
    amslog_set_level(LOG_DB, LOG_DEBUG/*LOG_ERR*/);
    amslog_set_level(LOG_SIS, LOG_DEBUG);
    amslog_set_level(LOG_PUB, LOG_DEBUG);
    amslog_set_level(LOG_CAS, LOG_DEBUG);

#if 0
    db_chunk_id = 0x04FB0100;
    if (0 == sto_get_chunk_header(db_chunk_id, &chuck_hdr))
    {
        SYSTEM_ERROR("get user db chunk header failed!\n");
        SDBBP();
    }
    db_addr = (UINT32)sto_chunk_goto(&db_chunk_id, 0xFFFFFFFF, 1) + CHUNK_HEADER_SIZE;
    db_len = chuck_hdr.len - CHUNK_HEADER_SIZE + CHUNK_NAME - (64 *1024);//last sector for temp info
#else
    db_addr = 0xFFFFFFFF;
    db_len = 64 *1024*5;
#endif

    memset(&db_config, 0, sizeof(db_config));
    db_config.max_sat_cnt = 50;
    db_config.sat_node_len = sizeof(S_NODE);
    db_config.max_tp_cnt =1000;
    db_config.tp_node_len = sizeof(T_NODE);
    db_config.max_prog_cnt = 5000;
    db_config.prog_node_len = sizeof(P_NODE);
    db_config.filter_callbak = db_createview_filter;
    db_config.pack_callbak = db_node_packer;
    db_config.unpack_callbak = db_node_unpacker;
    db_config.compare_callbak = db_same_node_checker;
    db_config.find_callbak = db_node_finder;
    if(amsdb_init_db(db_addr,db_len, &db_config) != SUCCESS)
    {
        osal_task_sleep(50);
        SYSTEM_ERROR("amsdb_init_db failed once!\n");
        if(amsdb_init_db(db_addr,db_len, &db_config)!= SUCCESS)
        {
        	SYSTEM_ERROR("amsdb_init_db failed twice!\n");
           osal_task_sleep(50);
			if((board_type==BOARD_DVBC)||(board_type ==BOARD_DTMB))
				amsdb_set_default(DEFAULT_DVBC_PROG,0);
			else if( board_type==BOARD_DVBS2)
            	ALiDVB_satellitetest();
        }
    }
    amsdb_create_view(TYPE_SAT_NODE, VIEW_SINGLE_SAT, 1);
    if(amsdb_get_node_cnt(TYPE_SAT_NODE,VIEW_ALL,0) == 0)
    {
        osal_task_sleep(50);
        if(amsdb_get_node_cnt(TYPE_SAT_NODE,VIEW_ALL,0) == 0)
        {
            osal_task_sleep(50);
			if((board_type==BOARD_DVBC)||(board_type ==BOARD_DTMB))
				amsdb_set_default(DEFAULT_DVBC_PROG,0);
			else if( board_type==BOARD_DVBS2)
            	ALiDVB_satellitetest();
        }
    }

  //  amsdb_create_view(TYPE_TP_NODE, VIEW_SINGLE_SAT, 1);
  //  amsdb_create_view(TYPE_PROG_NODE, VIEW_ALL | PROG_TVRADIO_MODE, 0);
  //  SYSTEM_DEBUG("libdb init ok, total prog num %d\n", amsdb_get_node_cnt(TYPE_PROG_NODE, VIEW_ALL | PROG_TVRADIO_MODE, 0));

    /* tdt init */
    start_tdt();
    init_clock(NULL);

    /* epg init */
    memset(&epg_config, 0, sizeof(epg_config));
    epg_config.max_tp_count = 100;
    epg_config.max_service_count = 300;
    epg_config.max_event_count = 8000;
    epg_config.max_view_event_count = 1000;
//    epg_config.call_back = epg_callback;
    //amsepg_init(NULL, 0x100000, &epg_config);
    ALiDVB_EPGInit(&epg_config);

    /* si monitor init */
    //amssim_init();
    //amssim_reg_callback(si_monitor_event);

    SYSTEM_DEBUG("system modules init ok!\n");
}


int ALiDVB_SystemInit(void)
{

	system_devices_init();
	system_modules_init();
	
	
	return 0;
}

int ALiDVB_SystemExit(void)
{
	return 0;
}

int ALiDVB_SystemLoadDefault(void)
{
	unsigned int board_type = gospell_get_board_type();
	if((board_type==BOARD_DVBC)||(board_type ==BOARD_DTMB))
	{
    	SYSTEM_DEBUG("DEFAULT_DVBC_PROG!\n");
		amsdb_set_default(DEFAULT_DVBC_PROG, 0);
	}
	
	return 0;
}

int ALiDVB_LockFreq(UINT32 sat_id,  UINT32 tp_id) {

	int type = 0;
	type = gospell_get_board_type();

	T_NODE t_node;
	S_NODE s_node;

	struct ft_antenna antenna;

	union ft_xpond xponder;
	struct nim_device *nim = dev_get_by_id(HLD_DEV_TYPE_NIM, 0);

	amsdb_get_node_byid(TYPE_TP_NODE, tp_id, (UINT8 *)(&t_node), sizeof(T_NODE));
	amsdb_get_node_byid(TYPE_SAT_NODE, sat_id, (UINT8 *)(&s_node), sizeof(S_NODE));

	memset(&xponder, 0, sizeof(union ft_xpond));

	SYSTEM_DEBUG("ALiDVB_LockFreq sat_id %d , tp_id %d!\n", sat_id, tp_id);




	if(type == BOARD_DVBS2)
	{
		xponder.s_info.type =  t_node.ft_type;
		xponder.s_info.frq = t_node.frq;
		xponder.s_info.sym =  t_node.sym;
		xponder.s_info.pol =  t_node.pol;

		MEMSET(&antenna, 0, sizeof(struct ft_antenna));
		sat2antenna(&s_node, &antenna);	

		
		frontend_set_antenna(nim, &antenna, &xponder, 1);
		frontend_set_nim(nim, &antenna, &xponder, 1);

	}
	else if(type == BOARD_DVBC)
	{
		xponder.c_info.type = FRONTEND_TYPE_C;
		xponder.c_info.frq = t_node.frq;
		xponder.c_info.sym = t_node.sym;
		xponder.c_info.modulation = t_node.modulation;
		frontend_set_nim(nim, NULL,&xponder, 1);

	}
	else if(type == BOARD_DTMB)
	{

		xponder.t_info.tp_id = t_node.tp_id;
		xponder.t_info.type = FRONTEND_TYPE_T;
		xponder.t_info.frq = t_node.frq;
		xponder.t_info.sym = t_node.sym;
		xponder.t_info.modulation = t_node.modulation;
		xponder.t_info.band_width = t_node.bandwidth*1000;
		xponder.t_info.fft_mode = t_node.FFT;
		xponder.t_info.guard_intl = t_node.guard_interval;
		xponder.t_info.fec = t_node.FEC_inner; //ft->xpond.t_info.pol
		xponder.t_info.inverse = t_node.inverse;

		frontend_set_nim(nim, NULL,&xponder, 1);	
	}
	else
	{
		LOGE("%s,%d: unknown board type",__FUNCTION__,__LINE__);
	}

	return 0;


}



/*
 * Class:     com_dvb_DvbSystem
 * Method:    getTunerLock
 * Signature: ()I
 */
int ALiDVB_getTunerLock() {

  	int lock_stat = 0;

	struct nim_device *nim = dev_get_by_id(HLD_DEV_TYPE_NIM, 0);

	if(nim_get_lock(nim, &lock_stat) != 0)
	{
		lock_stat = 0;
		LOGE("%s,%d: get tuner lock fail",__FUNCTION__,__LINE__);
	}

	return lock_stat;
  
}

/*
 * Class:     com_dvb_DvbSystem
 * Method:    getTunerSNR
 * Signature: ()I
 */
int ALiDVB_getTunerSNR() {

    	int snr_stat = 0;

	struct nim_device *nim = dev_get_by_id(HLD_DEV_TYPE_NIM, 0);

	if(nim_get_SNR(nim, &snr_stat) != 0)
	{
		snr_stat = 0;
		LOGE("%s,%d: get tuner SNR fail",__FUNCTION__,__LINE__);
	}

	return snr_stat;
  
}

/*
 * Class:     com_dvb_DvbSystem
 * Method:    getTunerAGC
 * Signature: ()I
 */
int ALiDVB_getTunerAGC() {

	int agc_stat = 0;

	struct nim_device *nim = dev_get_by_id(HLD_DEV_TYPE_NIM, 0);

	if(nim_get_AGC(nim, &agc_stat) != 0)
	{
		agc_stat = 0;
		LOGE("%s,%d: get tuner AGC fail",__FUNCTION__,__LINE__);
	}

	return agc_stat;

}

int makeAddr(const char* name, struct sockaddr_un* pAddr, socklen_t* pSockLen)  
{  
    int nameLen = strlen(name);  
    if (nameLen >= (int) sizeof(pAddr->sun_path) -1)  /* too long? */  
        return -1;  
    pAddr->sun_path[0] = '\0';  /* abstract namespace */  
    strcpy(pAddr->sun_path+1, name);  
    pAddr->sun_family = AF_UNIX;  
    *pSockLen = 1 + nameLen + offsetof(struct sockaddr_un, sun_path);  
    return 0;  
}  


int ALiDVB_PannelShow(char *show_buf , int show_len) {
	int sockfd;  
	socklen_t len;  
	struct sockaddr_un address;  
	int result;  
	char ch[10];  
	int i;

	memset(ch, 0, 10);
	LOGD("ALiDVB_PannelShow: showLen = %d", show_len);  
	if(show_len > 0 && show_len <=10) {
		if(show_len > 9)
			show_len = 9;

		ch[0] = show_len;

		memcpy(ch+1, show_buf, show_len);
	}
	else if(show_len == 11||show_len == 12) {

		ch[0] = 4;

		ch[1] = 27;

		ch[2] = PAN_ESC_CMD_LBD;
		
		ch[3] = PAN_ESC_CMD_LBD_FUNCC;

		if(show_len == 11)
			ch[4] = PAN_ESC_CMD_LBD_ON;
		if(show_len == 12)
			ch[4] = PAN_ESC_CMD_LBD_OFF;
	}
	else {
		LOGD("ALiDVB_PannelShow: return -1 ");  
		return -1;
	}
		
 	LOGD("ALiDVB_PannelShow: pre connect ");  
    //create socket    
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);  
    //name the server socket   
    //makeAddr("server_socket", &address, &len);   
	address.sun_family = AF_UNIX;  
	strcpy(address.sun_path, SERVER_NAME);  
	address.sun_path[0]=0;  
    //len = sizeof(address);   
	len =  strlen(SERVER_NAME)  + offsetof(struct sockaddr_un, sun_path);  
    //connect to server   
	result = connect(sockfd, (struct sockaddr*)&address, len);  
	if(result == -1)  
	{  
        LOGE("opps:client1");  
        return -1;  
	}  
    //communicate with server socket   
	for(i = 0; i < 3; i++) 
	{  
		LOGD("set send content:");  
		write(sockfd,ch,10);  
              
	}   

	return 0;
}




