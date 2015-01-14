#ifndef _DVB_FRONTEND_COMMON_H_
#define _DVB_FRONTEND_COMMON_H_

#ifndef _KERNEL_
#include <linux/types.h>
#endif
#include <alidefinition/adf_sysdef.h>

/* QAM Mode */
//for DVB-C
#define QAM16	4
#define QAM32	5
#define QAM64	6
#define QAM128	7
#define QAM256	8

#define FAST_TIMECST_AGC	1
#define SLOW_TIMECST_AGC	0


enum nim_dvbc_mode
{
    NIM_DVBC_J83AC_MODE  = 0x00,
	NIM_DVBC_J83B_MODE  = 0x01,
};

/*!@enum nim_sample_clk 
@brief nim sample clock select
*/
enum nim_sample_clk
{
    NIM_SAMPLE_CLK_27M  = 0x00,
    NIM_SAMPLE_CLK_54M  = 0x10,
};


struct ali_nim_m3501_cfg
{
	__u16 recv_freq_low;
	__u16 recv_freq_high;
	
	/*__u16 Ana_Filter_BW;
	__u8 Connection_config;
	__u8 Reserved_byte;
	__u8 AGC_Threshold_1;
	__u8 AGC_Threshold_2;*/
	
	__u16 qpsk_config;/*bit0:QPSK_FREQ_OFFSET,bit1:EXT_ADC,bit2:IQ_AD_SWAP,bit3:I2C_THROUGH,bit4:polar revert bit5:NEW_AGC1,bit6bit7:QPSK bitmode:
	                                00:1bit,01:2bit,10:4bit,11:8bit*/
	__u16 reserved;

	__u32 tuner_i2c_id;
	__u32 tuner_i2c_addr;
	__u32 demod_i2c_id;
	__u32 demod_i2c_addr;
	__u32 tuner_id;         //kent,2013.4.11,for 3501 and 3053
};



#ifndef _NIM_TUNER_H_
struct QAM_TUNER_CONFIG_DATA
{
	__u8 RF_AGC_MAX;//x.y V to xy value, 5.0v to 50v(3.3v to 33v)Qam then use it configue register.
	__u8 RF_AGC_MIN;//x.y V to xy value, 5.0v to 50v(3.3v to 33v)Qam then use it configue register.
	__u8 IF_AGC_MAX;//x.y V to xy value, 5.0v to 50v(3.3v to 33v)Qam then use it configue register.
	__u8 IF_AGC_MIN;//x.y V to xy value, 5.0v to 50v(3.3v to 33v)Qam then use it configue register.
	__u8 AGC_REF; //the average amplitude to full scale of A/D. % percentage rate.
	__u8 cTuner_Tsi_Setting;
};


struct QAM_TUNER_CONFIG_EXT
{
	__u8  c_tuner_crystal;
	__u8  c_tuner_base_addr;		/* Tuner BaseAddress for Write Operation: (BaseAddress + 1) for Read */
	__u8  c_chip;
	__u8  c_tuner_special_config;		/*0x01, RF AGC is disabled*/
	__u8  c_tuner_ref_divratio;
	__u16 w_tuner_if_freq;
	__u8  c_tuner_agc_top;
	__u8  c_tuner_step_freq;
//	int  (*Tuner_Write)(__u32 id, __u8 slv_addr, __u8 *data, int len);		/* Write Tuner Program Register */
//	int  (*Tuner_Read)(__u32 id, __u8 slv_addr, __u8 *data, int len);		/* Read Tuner Status Register */	
	__u32 i2c_type_id;	/*i2c type and dev id select. bit16~bit31: type, I2C_TYPE_SCB/I2C_TYPE_GPIO. bit0~bit15:dev id, 0/1.*/	

	__u8 c_tuner_freq_param; /* RT810_Standard_Type */
	__u16 c_tuner_reopen;
	__u16 w_tuner_if_freq_j83a;
	__u16 w_tuner_if_freq_j83b;
	__u16 w_tuner_if_freq_j83c;
	__u8  w_tuner_if_j83ac_type; //0x00 j83a , 0x01 j83c
		
};



struct QPSK_TUNER_CONFIG_EXT
{
	__u16 							w_tuner_crystal;			/* Tuner Used Crystal: in KHz unit */
	__u8  							c_tuner_base_addr;		/* Tuner BaseAddress for Write Operation: (BaseAddress + 1) for Read */
	__u8  							c_tuner_out_S_d_sel;		/* Tuner Output mode Select: 1 --> Single end, 0 --> Differential */
	__u32 							i2c_type_id;	/*i2c type and dev id select. bit16~bit31: type, I2C_TYPE_SCB/I2C_TYPE_GPIO. bit0~bit15:dev id, 0/1.*/	
};

struct QPSK_TUNER_CONFIG_DATA
{
	__u16 							recv_freq_low;
	__u16 							recv_freq_high;
	__u16 							ana_filter_bw;
	__u8 							connection_config;
	__u8 							reserved_byte;
	__u8 							agc_threshold_1;
	__u8 							agc_threshold_2;
	__u16 							qpsk_config;/*bit0:QPSK_FREQ_OFFSET,bit1:EXT_ADC,bit2:IQ_AD_SWAP,bit3:I2C_THROUGH,bit4:polar revert bit5:NEW_AGC1,bit6bit7:QPSK bitmode:
	                                00:1bit,01:2bit,10:4bit,11:8bit*/
};

struct EXT_DM_CONFIG
{
	__u32 i2c_base_addr;
	__u32 i2c_type_id;
	__u32 dm_crystal;
	__u32 dm_clock;
	__u32 polar_gpio_num;
    __u32 lock_polar_reverse;
};

struct EXT_LNB_CTRL_CONFIG
{
	__u32 param_check_sum; //ext_lnb_control+i2c_base_addr+i2c_type_id = param_check_sum
	int  (*ext_lnb_control) (int, int, int);
	__u32 i2c_base_addr;
	__u32 i2c_type_id;
	__u8 int_gpio_en;
	__u8 int_gpio_polar;
	__u8 int_gpio_num;
};



struct QPSK_TUNER_CONFIG_API
{
	/* struct for QPSK Configuration */
	struct QPSK_TUNER_CONFIG_DATA config_data;
	/* Tuner Initialization Function */
	int (*nim_Tuner_Init) (__u32* tuner_id, struct QPSK_TUNER_CONFIG_EXT * ptrTuner_Config);
	/* Tuner Parameter Configuration Function */
	int (*nim_Tuner_Control) (__u32 tuner_id, __u32 freq, __u32 sym);
	/* Get Tuner Status Function */
	int (*nim_Tuner_Status) (__u32 tuner_id, __u8 *lock);
	/* Extension struct for Tuner Configuration */
	struct QPSK_TUNER_CONFIG_EXT tuner_config;
	struct EXT_DM_CONFIG ext_dm_config;
	struct EXT_LNB_CTRL_CONFIG ext_lnb_config;
	__u32 device_type;	//current chip type. only used for M3501A
    __u32 demod_index;

	__u32 tuner_id;
};






struct COFDM_TUNER_CONFIG_EXT
{
	__u16 c_tuner_crystal;
	__u8  c_tuner_base_addr;		/* Tuner BaseAddress for Write Operation: (BaseAddress + 1) for Read */	
	__u8  c_chip;
	__u8  c_tuner_ref_divratio;
	__u16 w_tuner_if_freq;
	__u8  c_tuner_agc_top;
	__u16 c_tuner_step_freq;
	int  (*tuner_write)(__u32 id, __u8 slv_addr, __u8 *data, int len);		/* Write Tuner Program Register */
	int  (*tuner_read)(__u32 id, __u8 slv_addr, __u8 *data, int len);		/* Read Tuner Status Register */	
	int  (*tuner_write_read)(__u32 id, __u8 slv_addr, __u8 *data, __u8 wlen,int len);
	__u32 i2c_type_id;	/*i2c type and dev id select. bit16~bit31: type, I2C_TYPE_SCB/I2C_TYPE_GPIO. bit0~bit15:dev id, 0/1.*/				
        
        // copy from COFDM_TUNER_CONFIG_DATA struct in order to  let tuner knows whether the RF/IF AGC is enable or not.
	// esp for max3580, which uses this info to turn on/off internal power detection circuit. See max3580 user manual for detail.

	//bit0: IF-AGC enable <0: disable, 1: enalbe>;bit1: IF-AGC slop <0: negtive, 1: positive>
	//bit2: RF-AGC enable <0: disable, 1: enalbe>;bit3: RF-AGC slop <0: negtive, 1: positive>
	//bit4: Low-if/Zero-if.<0: Low-if, 1: Zero-if>
	//bit5: RF-RSSI enable <0: disable, 1: enalbe>;bit6: RF-RSSI slop <0: negtive, 1: positive>
	__u16 cofdm_config;

	int  if_signal_target_intensity;
};
























#endif

struct ali_nim_m3200_cfg
{
	struct QAM_TUNER_CONFIG_DATA tuner_config_data;
	struct QAM_TUNER_CONFIG_EXT  tuner_config_ext;
	struct EXT_DM_CONFIG         ext_dem_config;  
    __u8 qam_mode;
   __u32 tuner_id;         //kent,2013.4.11,for 3501 and 3053
};
struct ali_nim_mxl241_cfg
{
	struct QAM_TUNER_CONFIG_DATA tuner_config_data;
	struct QAM_TUNER_CONFIG_EXT tuner_config_ext;
};
/* Structure for Channel Change parameters */
struct NIM_CHANNEL_CHANGE
{
	__u32 freq;				/* Channel Center Frequency: in MHz unit */
	__u32 sym;				/* Channel Symbol Rate: in KHz unit */
	__u8 fec;				/* Channel FEC rate */
	__u32 bandwidth;		/* Channel Symbol Rate: same as Channel Symbol Rate ? -- for DVB-T */
	__u8 guard_interval;	/* Guard Interval -- for DVB-T */
	__u8 fft_mode;			/* -- for DVB-T */
	__u8 modulation;		/* -- for DVB-T */
	__u8 usage_type;		/* -- for DVB-T */
	__u8 inverse;			/* -- for DVB-T */
};

struct NIM_AUTO_SCAN
{
	__u8 unicable;
	__u16 fub;	    		//Unicable: UB slots centre freq (MHz)
	__u32 sfreq;			//Start Frequency of the Scan procedure: in MHz unit.
	__u32 efreq;			//End Frequency of the Scan procedure: in MHz unit.
	__u32 (*callback)(void *pfun,__u8 status, __u8 polar, __u16 freq, __u32 sym, __u8 fec,__u8 stop);	/* Callback Function pointer */
};

#define DISEQC_CMD_MAX_LEN 16
struct ali_nim_diseqc_cmd
{
	__u32 mode; 						/*Input: Diseqc command mode*/
	__u8 cmd[DISEQC_CMD_MAX_LEN];		/*Input: Diseqc command bytes*/
	__u8 cmd_size;						/*Input: Diseqc command length*/
	__u8 ret_bytes[DISEQC_CMD_MAX_LEN]; /*Output: Diseqc command return bytes*/
	__u8 ret_len; 						/*Output: Diseqc command return bytes length*/
	__u16 diseqc_type;					/*1: Diseqc 1x. 2: Diseqc 2X*/
};



/* DiSEqC mode */
#define NIM_DISEQC_MODE_22KOFF		0	/* 22kHz off */
#define	NIM_DISEQC_MODE_22KON		1	/* 22kHz on */
#define	NIM_DISEQC_MODE_BURST0		2	/* Burst mode, on for 12.5mS = 0 */
#define	NIM_DISEQC_MODE_BURST1		3	/* Burst mode, modulated 1:2 for 12.5mS = 1 */
#define	NIM_DISEQC_MODE_BYTES		4	/* Modulated with bytes from DISEQC INSTR */
#define	NIM_DISEQC_MODE_ENVELOP_ON	5	/* Envelop enable*/
#define	NIM_DISEQC_MODE_ENVELOP_OFF	6	/* Envelop disable, out put 22K wave form*/
#define	NIM_DISEQC_MODE_OTHERS		7	/* Undefined mode */
#define	NIM_DISEQC_MODE_BYTES_EXT_STEP1		8	/*Split NIM_DISEQC_MODE_BYTES to 2 steps to improve the speed,*/
#define	NIM_DISEQC_MODE_BYTES_EXT_STEP2		9	/*(30ms--->17ms) to fit some SPEC */

/* Polarization */
#define NIM_PORLAR_HORIZONTAL	0x00
#define NIM_PORLAR_VERTICAL		0x01
#define NIM_PORLAR_LEFT			0x02
#define NIM_PORLAR_RIGHT		0x03

#define NIM_PORLAR_REVERSE		0x01
#define NIM_PORLAR_SET_BY_22K	0x02

#define DISEQC2X_ERR_NO_REPLY			0x01
#define DISEQC2X_ERR_REPLY_PARITY		0x02
#define DISEQC2X_ERR_REPLY_UNKNOWN	0x03
#define DISEQC2X_ERR_REPLY_BUF_FUL	0x04






#define ALI_NIM_CHANNEL_CHANGE             _IOW('o', 84, struct NIM_CHANNEL_CHANGE)
#define ALI_NIM_SET_POLAR	               _IOW('o', 85, __u32)
#define ALI_NIM_GET_LOCK_STATUS            _IO('o', 86)
#define ALI_NIM_READ_QPSK_BER 	           _IO('o', 87)
#define ALI_NIM_READ_RSUB	               _IO('o', 88)
#define ALI_NIM_READ_AGC	               _IO('o', 89)
#define ALI_NIM_READ_SNR	               _IO('o', 90)
#define ALI_NIM_READ_SYMBOL_RATE	       _IO('o', 91)
#define ALI_NIM_READ_FREQ	               _IO('o', 92)
#define ALI_NIM_READ_CODE_RATE	           _IO('o', 93)
#define ALI_NIM_HARDWARE_INIT_S            _IOW('o', 94, struct ali_nim_m3501_cfg)
#define ALI_NIM_HARDWARE_INIT_C            _IOW('o', 95, struct ali_nim_m3200_cfg)
#define ALI_NIM_HARDWARE_INIT_T            _IOW('o', 96, struct ali_nim_m3501_cfg)   //to be comfirmed
#define ALI_NIM_AUTO_SCAN 	               _IO('o', 97)
#define ALI_NIM_DISEQC_OPERATE 	           _IOWR('o', 98, struct ali_nim_diseqc_cmd)
#define ALI_NIM_GET_RF_LEVEL               _IO('o', 99)
#define ALI_NIM_GET_CN_VALUE 		       _IO('o', 100)
#define ALI_NIM_SET_PERF_LEVEL		       _IOW('o', 101, __u32)
#define ALI_NIM_REG_RW 	                   _IOWR('o', 102, __u32)
#define ALI_NIM_DRIVER_READ_SUMPER         _IOWR('o', 103, __u32)
#define ALI_NIM_DRIVER_SET_MODE            _IOWR('o', 104, __u32)
#define ALI_NIM_REG_RW_EXT                 _IOWR('o', 105, __u32)
#define ALI_SYS_REG_RW                     _IOWR('o', 106, __u32)
#define ALI_NIM_ADC2MEM_START              _IOW('o', 107, __u32)
#define ALI_NIM_ADC2MEM_STOP               _IO('o', 108)
#define ALI_NIM_ADC2MEM_SEEK_SET           _IOW('o', 109, __u32)
#define ALI_NIM_ADC2MEM_READ_8K            _IOR('o', 110, __u32)
#define ALI_NIM_TUNER_SELT_ADAPTION_S      _IOR('o', 111, struct ali_nim_m3501_cfg)
#define ALI_NIM_TUNER_SELT_ADAPTION_C      _IOR('o', 112, struct ali_nim_m3200_cfg)
#define ALI_NIM_TUNER_SELT_ADAPTION_T      _IOR('o', 113, struct ali_nim_m3501_cfg)  //to be comfirmed
#define ALI_NIM_READ_TUNTYPE    	       _IOR('o', 114, __u32)
#define ALI_NIM_RESET_FSM                  _IO('o', 115)
#define ALI_NIM_TUNER_ACTIVE               _IO('o', 116)
#define ALI_NIM_TUNER_STANDBY              _IO('o', 117)
#define ALI_NIM_STOP_AUTOSCAN	           _IOW('o', 118, __u32)
#define ALI_NIM_DRIVER_GET_CUR_FREQ	       _IOW('o', 119, __u32)
#define ALI_NIM_DRIVER_SET_RESET_CALLBACK  _IO('o', 120)
#define NIM_TURNER_SET_STANDBY	           _IO('o', 121)
#define ALI_NIM_DRIVER_GET_ID	           _IO('o', 122)
#define ALI_NIM_AS_SYNC_WITH_LIB           _IOWR('o', 123, __u32)
#define ALI_NIM_SET_NETLINKE_ID            _IOWR('o', 124, __u32)


#endif
