/*****************************************************************************
*    Copyright (C)2003 Ali Corporation. All Rights Reserved.
*
*    File:    nim_dev.h
*
*    Description:    This file contains NIM device structure define.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Feb.16.2003      Justin Wu       Ver 0.1    Create file.
*	2.	Jun.12.2003      George jiang    Ver 0.2    Porting NIM.
*   	3.  Aug.22.2003      Justin Wu       Ver 0.3    Update.
*****************************************************************************/

#ifndef __ADR_HLD_NIM_DEV_H__
#define __ADR_HLD_NIM_DEV_H__

#ifdef __cplusplus
extern "C" {
#endif


#include <adr_retcode.h>

#include <hld_cfg.h>
#include <hld/adr_hld_dev.h>

#define EXT_QPSK_MODE_SPI 		0
#define EXT_QPSK_MODE_SSI 		1
#define NIM_CHIP_ID_M3501A		0x350100C0
#define NIM_CHIP_ID_M3501B		0x350100D0
#define NIM_CHIP_SUB_ID_S3501D	0x00
#define NIM_CHIP_SUB_ID_M3501B	0xC0
#define NIM_FREQ_RETURN_REAL	0
#define NIM_FREQ_RETURN_SET		1
//#define SYS_PROJECT_FE			PROJECT_FE_DVBS2

/* NIM Device I/O control command */
enum nim_device_ioctrl_command
{
	NIM_DRIVER_READ_TUNER_STATUS,	/* Read tuner lock status */
	NIM_DRIVER_READ_QPSK_STATUS,  	/* Read QPSK  lock status */
	NIM_DRIVER_READ_FEC_STATUS,   	/* Read FEC lcok status */

	NIM_DRIVER_READ_QPSK_BER,     		/* Read QPSK Bit Error Rate */
	NIM_DRIVER_READ_VIT_BER,      		/* Read Viterbi Bit Error Rate */
	NIM_DRIVER_READ_RSUB,         		/* Read Reed Solomon Uncorrected block */
	NIM_DRIVER_STOP_ATUOSCAN,		/* Stop autoscan */
	NIM_DRIVER_UPDATE_PARAM,			/* Reset current parameters */
	NIM_DRIVER_TS_OUTPUT,				/* Enable NIM output TS*/
	NIM_DRIVER_FFT,
	NIM_DRIVER_GET_CR_NUM,
	NIM_DRIVER_GET_CUR_FREQ,
	NIM_DRIVER_FFT_PARA,	
	NIM_DRIVER_GET_SPECTRUM,
	NIM_FFT_JUMP_STEP,               		/* Get AutoScan FFT frequency jump step */ //huang hao add for m3327 qpsk
	NIM_DRIVER_READ_COFFSET,	   		/* Read Carrier Offset state */ //joey add for stv0297.
	NIM_DRIVER_SEARCH_1ST_CHANNEL,	/* Search channel spot*/ //joey add for stv0297.
	NIM_DRIVER_SET_TS_MODE,			/*Set ts output mode:*/ 
										/*bit0: 1 serial out, 	0 parallel out*/
										/*bit1: 1 clk rising, 	0 clk falling*/
										/*bit2: 1 valid gap,		0 valid no gap*/
	NIM_DRIVER_SET_PARAMETERS,		/* Set the parameters of nim,add by Roman at 060321 */
	NIM_DRIVER_SET_RESET_CALLBACK,	/* When nim device need to be reset, call an callback to notice app */
	NIM_DRIVER_ENABLE_DVBS2_HBCD,	/* For DVB-S2, enable/disable HBCD mode */
	NIM_DRIVER_STOP_CHANSCAN,		/* Stop channel change because some low symbol rate TP too long to be locked */
	NIM_DRIVER_RESET_PRE_CHCHG,	    /* Reset nim device before channel change */

    NIM_ENABLE_IC_SORTING,			/*Enable IC sorting, set IC sorting param*/
	NIM_DRIVER_GET_OSD_FREQ_OFFSET, /*get OSD freq offset. */
	NIM_DRIVER_SET_RF_AD_GAIN,		/* Set RF ad table for RSSI display.*/ 
	NIM_DRIVER_SET_IF_AD_GAIN,		/* Set IF ad table for RSSI display. */ 
	NIM_DRIVER_GET_RF_IF_AD_VAL,        /* get RF IF ad value. */ 
	NIM_DRIVER_GET_REC_PERFORMANCE_INFO,	/* get receiver performance info. */ 
	NIM_DRIVER_ENABLE_DEBUG_LOG,			/* enable nim driver debug infor out.*/
	NIM_DRIVER_DISABLE_DEBUG_LOG,			/* disable nim driver debug infor out.*/
	NIM_DRIVER_GET_FRONTEND_STATE,			/* Read front end state.*/
	NIM_DRIVER_SET_FRONTEND_LOCK_CHECK,			/* Set front end lock check flag.*/
	NIM_DRIVER_LOG_IFFT_RESULT, 
	NIM_DRIVER_CHANGE_TS_GAP,			/* Change ts gap */
	NIM_DRIVER_SET_SSI_CLK,				/* Set SSI Clock */

    //use io control command to instead of function interface for combo soluation
    NIM_DRIVER_SET_POLAR,               /*DVB-S NIM Device set LNB polarization */
    NIM_DRIVER_SET_12V,                 /*DVB-S NIM Device set LNB votage 12V enable or not */
    NIM_DRIVER_GET_SYM,                 /* Get Current NIM Device Channel Symbol Rate */
    NIM_DRIVER_GET_BER,                 /* Get Current NIM Device Channel Bit-Error Rate */
    NIM_DRIVER_GET_AGC,                 /* Get Current NIM Device Channel AGC Value */
    NIM_DRIVER_DISABLED,                 /* Disable Current NIM Device */
    NIM_DRIVER_GET_GUARD_INTERVAL,
    NIM_DRIVER_GET_FFT_MODE, 
    NIM_DRIVER_GET_MODULATION,
    NIM_DRIVER_GET_SPECTRUM_INV,

    // The following code is for tuner io command
    NIM_TUNER_COMMAND = 0x8000, 
    NIM_TUNER_POWER_CONTROL, 
    NIM_TUNER_GET_AGC, 
    NIM_TUNER_GET_RSSI_CAL_VAL,
    NIM_TUNER_RSSI_CAL_ON, //RSSI calibration on
    NIM_TUNER_RSSI_CAL_OFF,
    NIM_TUNER_RSSI_LNA_CTL,//RSSI set LNA
    NIM_TUNER_SET_GPIO,
    NIM_TUNER_CHECK, 

    NIM_DRIVER_SET_BLSCAN_MODE,    // Para = 0, NIM_SCAN_FAST; Para = 1, NIM_SCAN_ACCURATE(slower)
};

/*! @addtogroup nim
 *  @{
 */

/*!@struct nim_device_ioctrl_command_ext 
 * @brief NIM Device I/O control command extension for nim_ioctl_ext
 * */
enum nim_device_ioctrl_command_ext
{
	NIM_DRIVER_AUTO_SCAN		= 0x00FC0000,	    //!<Do AutoScan Procedure[NOT USE]
	NIM_DRIVER_CHANNEL_CHANGE	= 0x00FC0001,	    //!<Do Channel Change
	NIM_DRIVER_CHANNEL_SEARCH	= 0x00FC0002,	    //!<Do Channel Search[NOT USE]
	NIM_DRIVER_GET_RF_LEVEL		= 0x00FC0003,	    //!<Get RF level
	NIM_DRIVER_GET_CN_VALUE		= 0x00FC0004,	    //!<Get CN value
	NIM_DRIVER_GET_BER_VALUE		= 0x00FC0005,	//!<Get BER value
	NIM_DRIVER_QUICK_CHANNEL_CHANGE = 0x00FC0006,   //!<Do Quick Channel Change without waiting lock
	NIM_DRIVER_GET_ID				= 0x00FC0007,   //!<Get 3501 type: M3501A/M3501B[NOT USE]
	NIM_DRIVER_SET_PERF_LEVEL	    = 0x00FC0008,	//!<Set performance level[NOT USE]
	NIM_DRIVER_START_CAPTURE        = 0x00FC0009,	//!<Start capture[NOT USE]
	NIM_DRIVER_GET_I2C_INFO         = 0x00FC000A,	//!<Start capture[NOT USE]

    NIM_DRIVER_GET_FFT_RESULT       = 0x00FC000B,   //!<Get Current NIM Device Channel FFT spectrum result[NOT USE]
    NIM_DRIVER_DISEQC_OPERATION     = 0x00FC000C,   //!<NIM DiSEqC Device Opearation[NOT USE]
    NIM_DRIVER_DISEQC2X_OPERATION   = 0x00FC000D,   //!<NIM DiSEqC2X Device Opearation[NOT USE]

    NIM_DRIVER_RESET_FSM = 0x00FC000E,    
	NIM_DRIVER_READ_TUNTYPE = 0x00FC000F,
};

/* NIM performance level setting */
enum nim_perf_level
{
	NIM_PERF_DEFAULT		= 0,
	NIM_PERF_SAFER		= 1,
	NIM_PERF_RISK			= 2,
};

#if 0
/* FrontEnd Type */
enum fe_type {
	FE_QPSK	= 0x00, 	/* DVB-S */
	FE_QAM 	= 0x01,	/* DVB-C */
	FE_OFDM	= 0x02 	/* DVB-T */
};
#endif

enum nim_cofdm_work_mode
{
    NIM_COFDM_SOC_MODE = 0, 
    NIM_COFDM_ONLY_MODE = 1
};

enum nim_cofdm_ts_mode
{
    NIM_COFDM_TS_SPI_8B = 0, 
    NIM_COFDM_TS_SPI_4B = 1, 
    NIM_COFDM_TS_SPI_2B = 2, 
    NIM_COFDM_TS_SSI = 3
};

/* Structure for NIM Device Status */
struct nim_device_stats
{
	UINT16	temp_num;			/* blank */
};

/* Structure for NIM DiSEqC Device Information parameters */
struct t_diseqc_info
{
	UINT8 sat_or_tp;			/* 0:sat, 1:tp*/
	UINT8 diseqc_type;
	UINT8 diseqc_port;
	UINT8 diseqc11_type;
	UINT8 diseqc11_port;
	UINT8 diseqc_k22;
	UINT8 diseqc_polar;		/* 0: auto,1: H,2: V */
	UINT8 diseqc_toneburst;	/* 0: off, 1: A, 2: B */	

	UINT8 positioner_type;	/*0-no positioner 1-1.2 positioner support, 2-1.3 USALS*/
	UINT8 position;			/*use for DiSEqC1.2 only*/	
	UINT16 wxyz;			/*use for USALS only*/
};

/*!@struct NIM_Channel_Change 
 * @brief Structure for Channel Change parameters
 * */
 #if 0
struct NIM_Channel_Change
{
	UINT32 freq;		    //!<Channel Center Frequency: in 10KHz unit
	UINT32 sym;				//!<Channel Symbol Rate: in KHz unit
	UINT8 fec;				//!<Channel FEC rate
	UINT32 bandwidth;		//!<Channel Symbol Rate: same as Channel Symbol Rate ? -- for DVB-T
	UINT8 guard_interval;	//!<Guard Interval -- for DVB-T
	UINT8 fft_mode;			//!< -- for DVB-T
	UINT8 modulation;		//!< -- for DVB-T
	UINT8 usage_type;		//!< -- for DVB-T
	UINT8 inverse;			//!< -- for DVB-T
    UINT8 priority;         //!< -- for DVB-T
};
#endif

/* Structure for Channel Search parameters */
struct NIM_Channel_Search
{
	UINT32 freq;
	UINT32 bandwidth;
	UINT8 guard_interval;
	UINT8 fft_mode;
	UINT8 modulation;
	UINT8 fec;
	UINT8 usage_type;
	UINT8 inverse;
	UINT16 freq_offset;
    UINT8 priority;
};

/* Structure for Auto Scan parameters */
struct NIM_Auto_Scan
{
  	//>>> Unicable begin
	UINT8 unicable;
//	UINT8 invert;	/* Fub INVERT? */
	UINT16 Fub;	/* Unicable: UB slots centre freq (MHz) */
	//<<< Unicable end
 
	UINT32 sfreq;			/* Start Frequency of the Scan procedure: in MHz unit */
	UINT32 efreq;			/* End Frequency of the Scan procedure: in MHz unit */
	INT32 (*callback)(UINT8 status, UINT8 polar, UINT32 freq, UINT32 sym, UINT8 fec);	/* Callback Function pointer */
};

/*M3328F external QPSK configuration*/
struct EXT_QPSK_Config
{
	UINT8 gpio_28f_reset;	/* External M3328F reset GPIO*/
	UINT8 ext_qpsk_mod; 	/* EXT_QPSK_MODE_SSI / EXT_QPSK_MODE_SPI */
	UINT8 host_uart_id;		/* 1: UART1; 2: UART2; 3: UART3; other value: UART2(default)*/
	UINT8 tsi_mode;			/* Supposed TSI mode. Output parameter from NIM driver.*/
};

/* for NIM_DRIVER_SET_RESET_CALLBACK */
typedef INT32 (*pfn_nim_reset_callback)(UINT32 param);

typedef struct
{
	UINT8 lock;
	BOOL valid;
	UINT32 ber;
	UINT32 per;
}nim_rec_performance_t;

/* Structure for IC sorting parameters */
struct NIM_IC_Soring
{
	BOOL    bEnable;            /* Enable/disable ic sorting*/
	UINT8   *pError_Indicator;  /* pointer to global error indicator */
};

/* structure for RSSI display.*/
#if 1//def NEW_AD_GAIN_T
typedef UINT16 nim_ad_gain_t;
#else
typedef struct
{
	UINT16 ad;
	INT8 gain;
}nim_ad_gain_t;
#endif

typedef struct
{
	nim_ad_gain_t *p_table;
	int count;
}nim_ad_gain_table_t;

typedef struct
{
	UINT16 rf_ad_val;
	UINT16 if_ad_val;
}nim_rf_if_ad_val_t;

struct NIM_I2C_Info
{
	UINT32 i2c_type;
	UINT32 i2c_addr;
};

typedef struct
{
    UINT32 freq;
    UINT32 *start_addr;   
}nim_get_fft_result_t;   //for NIM_DRIVER_GET_FFT_RESULT

typedef struct
{
    UINT32 mode;
    UINT8 *cmd;
    UINT8 *rt_value;
    UINT8 *rt_cnt;
    UINT8 cnt;    
}nim_diseqc_operate_para_t;  //for  NIM_DRIVER_DISEQC_OPERATION
                                                                      //     NIM_DRIVER_DISEQC2X_OPERATION 
/*!@struct nim_device
@brief Structure nim_device, the basic structure between HLD and LLD of demomulator device
*/
struct nim_device
{
	struct nim_device   *next;				//!<Next nim device structure
	UINT32	type;						    //!<Interface hardware type
	INT8	name[HLD_MAX_NAME_SIZE];	    //!<Device name
	UINT32	base_addr;					    //!<Demodulator address
	UINT32  Tuner_select;					//!<I2C TYPE for  TUNER select
	UINT16	flags;						    //!<Interface flags, status and ability
	UINT32	dvb_mode;						//!<dvbc or dvbt or dvbs or dvbs2
	UINT32  demod_index;                      //!which dvbs2 demod
	/* Hardware privative structure */
	void    *priv;	    				    //!<pointer to private data

#if 0
	/* Functions of this dem device */
	INT32	(*init)();									//!<NIM Device Initialization[obsoleting]
	INT32	(*open)(struct nim_device *dev);			//!<NIM Device Open[obsoleting]
	INT32	(*stop)(struct nim_device *dev);			//!<NIM Device Stop[obsoleting]
	INT32	(*do_ioctl)(struct nim_device *dev, INT32 cmd, UINT32 param);		      //!<NIM Device I/O Control[obsoleting]
	INT32 	(*do_ioctl_ext)(struct nim_device *dev, INT32 cmd, void * param_list);    //!<NIM Device I/O Control Extension[obsoleting]
	INT32	(*get_lock)(struct nim_device *dev, UINT8 *lock);					      //!<Get Current NIM Device Channel Lock Status[obsoleting]
	INT32	(*get_freq)(struct nim_device *dev, UINT32 *freq);				          //!<Get Current NIM Device Channel Frequency[obsoleting]
	INT32	(*get_FEC)(struct nim_device *dev, UINT8 *fec);					          //!<Get Current NIM Device Channel FEC Rate[obsoleting]
	INT32	(*get_SNR)(struct nim_device *dev, UINT8 *snr);					          //!<Get Current NIM Device Channel SNR Value[obsoleting]
#if ( SYS_PROJECT_FE == PROJECT_FE_DVBS||SYS_PROJECT_FE == PROJECT_FE_DVBS2)	
	UINT8		diseqc_typex;				    //!< NIM DiSEqC Device Type[obsoleting]
	UINT8		diseqc_portx;				    //!<NIM DiSEqC Device Port[obsoleting]
	struct t_diseqc_info diseqc_info;			//!<NIM DiSEqC Device Information Structure[obsoleting]
	INT32	(*set_polar)(struct nim_device *dev, UINT8 polar);		//!<DVB-S NIM Device set LNB polarization[obsoleting]
	INT32	(*set_12v)(struct nim_device *dev, UINT8 flag);			//!<DVB-S NIM Device set LNB votage 12V enable or not[obsoleting]
	INT32   (*DiSEqC_operate)(struct nim_device *dev, UINT32 mode, UINT8* cmd, UINT8 cnt);	//!<NIM DiSEqC Device Opearation[obsoleting]
	INT32   (*DiSEqC2X_operate)(struct nim_device *dev, UINT32 mode, UINT8* cmd, UINT8 cnt, UINT8 *rt_value, UINT8 *rt_cnt);	//!<NIM DiSEqC2X Device Opearation[obsoleting]
	INT32	(*get_sym)(struct nim_device *dev, UINT32 *sym);		//!<Get Current NIM Device Channel Symbol Rate[obsoleting]
	INT32	(*get_BER)(struct nim_device *dev, UINT32 *ebr);		//!<Get Current NIM Device Channel Bit-Error Rate[obsoleting]
	INT32	(*get_AGC)(struct nim_device *dev, UINT8 *agc);			//!<Get Current NIM Device Channel AGC Value[obsoleting]
	INT32	(*get_fft_result)(struct nim_device *dev, UINT32 freq, UINT32 *start_addr);	//!<Get Current NIM Device Channel FFT spectrum result[obsoleting]
	#if ( SYS_PROJECT_FE == PROJECT_FE_DVBS)
	INT32	(*channel_search)(struct nim_device *dev, UINT32 freq);				        //!<should be opened in DVBS[obsoleting]
	#else
	INT32	(*channel_search)(struct nim_device *dev, UINT32 CRNum);
	#endif
        const char *(*get_ver_infor)(struct nim_device *dev);				            //!<Get Current NIM Device Version Number[obsoleting]
#elif (SYS_PROJECT_FE == PROJECT_FE_DVBT) || (SYS_PROJECT_FE == PROJECT_FE_ATSC) || (SYS_PROJECT_FE == PROJECT_FE_ISDBT)

	INT32	(*channel_change)(struct nim_device *dev, UINT32 freq, UINT32 bandwidth, UINT8 guard_interval, UINT8 fft_mode, UINT8 modulation, UINT8 fec, UINT8 usage_type, UINT8 inverse,UINT8 priority);
	
	INT32	(*channel_search)(struct nim_device *dev, UINT32 freq,UINT32 bandwidth, UINT8 guard_interval, UINT8 fft_mode, UINT8 modulation, UINT8 fec, UINT8 usage_type, UINT8 inverse,UINT16 freq_offset,UINT8 priority);
		
	INT32	(*disable)(struct nim_device *dev);						                    //!<Disable Current NIM Device[obsoleting]

	INT32	(*get_guard_interval)(struct nim_device *dev, UINT8 *gi);

	INT32	(*get_fftmode)(struct nim_device *dev, UINT8 *fftmode);
	
	INT32	(*get_modulation)(struct nim_device *dev, UINT8 *modulation);	
	INT32	(*get_spectrum_inv)(struct nim_device *dev, UINT8 *inv);
	INT32	(*get_AGC)(struct nim_device *dev, UINT16 *agc);
#ifdef SMART_ANT_SUPPORT
	INT32 	(*Set_Smartenna)(struct nim_device *dev, UINT8 position,UINT8 gain,UINT8 pol,UINT8 channel);
	INT32 	(*Get_SmartennaSetting)(struct nim_device *dev,UINT8 *pPosition,UINT8 *pGain,UINT8 *pPol,UINT8 *pChannel);
	INT32 	(*Get_SmartennaMetric)(struct nim_device *dev, UINT8 metric,UINT16 *pMetric);
#endif

	INT32	(*get_VSB_AGC)(struct nim_device *dev, UINT16 *agc);	
        INT32	(*get_VSB_SNR)(struct nim_device *dev, UINT16 *snr);
        INT32	(*get_VSB_PER)(struct nim_device *dev, UINT32 *per);
		
#if ((SYS_PROJECT_FE == PROJECT_FE_ATSC) || (SYS_PROJECT_FE == PROJECT_FE_DVBT) || (SYS_PROJECT_FE == PROJECT_FE_ISDBT))
	INT32	(*get_HIER)(struct nim_device *dev, UINT8*hier);
	INT8		(*get_priority)(struct nim_device *dev, UINT8*priority);

	INT32	(*get_freq_offset)(struct nim_device *dev, INT32 *freq_offset);//051222 yuchun
	INT32	(*get_BER)(struct nim_device *dev, UINT32 *ber);			       //!<Get Current NIM Device Channel Bit-Error Rate[obsoleting]
#endif
#elif ( SYS_PROJECT_FE == PROJECT_FE_DVBC )
	INT32	(*get_sym)(struct nim_device *dev, UINT32 *sym);		           //!<Get Current NIM Device Channel Symbol Rate[obsoleting]
	
	INT32	(*get_BER)(struct nim_device *dev, UINT32 *ber);			       //!<Get Current NIM Device Channel Bit-Error Rate[obsoleting]
	 
	INT32	(*get_AGC)(struct nim_device *dev, UINT8 *agc);			           //!<Get Current NIM Device Channel AGC Value[obsoleting]

	INT32	(*get_fft_result)(struct nim_device *dev, UINT32 freq, UINT32 *start_addr);	//!<Get Current NIM Device Channel FFT spectrum result[obsoleting]
	
	INT32	(*channel_search)(struct nim_device *dev, UINT32 freq);				        //!<Complement channel Search function[obsoleting]
#endif	
#endif
	int net_link_portid;

};

/*!
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __HLD_NIM_DEV_H__ */

