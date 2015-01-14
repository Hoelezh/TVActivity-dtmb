/****************************************************************************
 *
 *  ALi (Zhuhai) Corporation, All Rights Reserved. 2011 Copyright (C)
 *
 *  File: ali_smc.h
 *
 *  Description: This file contains all globe micros and functions declare
 *		             of smartcard reader ioctl commands.
 *
 *  History:
 *      Date            Author            Version   Comment
 *      ====        ======      =======  =======
 *     
 ****************************************************************************/

#ifndef _ALI_SMC_COMMON_H_
#define _ALI_SMC_COMMON_H_

#include <ali_basic_common.h>

/* Constant to be used */
#define ATR_MAX_SIZE 		33	/* Maximum size of ATR byte array */

/* For error status */
typedef enum smc_error_e {
	SMART_NO_ERROR,
	SMART_WRONG_ATR,
	SMART_TOO_MANY_RETRIES,
	SMART_OVERRUN_ERROR,
	SMART_FRAME_ERROR,
	SMART_PTS_NOT_SUPPORTED,
	SMART_INVALID_STATUS_BYTES_SEQUENCE,
	SMART_INVALID_CLASS,
	SMART_INVALID_CODE,
	SMART_INCORRECT_REFERENCE,
	SMART_INCORRECT_LENGTH,
	SMART_NOT_INSERTED,
	SMART_NOT_RESETED,
	SMART_INVALID_PROTOCOL,
	SMART_USER_ABORT,
	SMART_BAD_COMMAND,
	SMART_WRITE_ERROR ,
	SMART_READ_ERROR,
	SMART_NO_ANSWER,
	SMART_PARITY_ERROR,
	SMART_UNKNOWN_ERROR,
} smc_error_t;

/* Message from kernel to application */
#define SMC_MSG_MAX_LEN 32

/* Board class definition */
#define BOARD_SUPPORT_CLASS_A		(1<<0)
#define BOARD_SUPPORT_CLASS_B		(1<<1)
#define BOARD_SUPPORT_CLASS_C		(1<<2)

typedef struct smc_notification_param_t {
    uint8 smc_msg_tag;
    uint8 smc_msg_len;
    uint8 smc_msg_buf[SMC_MSG_MAX_LEN];
}smc_notification_param_t;

typedef enum smc_notification_e {
	SMC_MSG_CARD_STATUS,
} smc_notification_t;

/* Card status */
#define SMC_STATUS_OK			0
#define SMC_STATUS_NOT_EXIST	1
#define SMC_STATUS_NOT_RESET	2
/* ........ */
#define SMC_IO_ON		1
#define SMC_IO_OFF		0

/* ATR read status */
enum smc_atr_result
{
	SMC_ATR_NONE = 0,
	SMC_ATR_WRONG,
	SMC_ATR_OK
};

/* Parameter for reset command */
typedef struct smc_atr_t {
    uint8 atr_buf[ATR_MAX_SIZE];
    unsigned short atr_size;
}smc_atr_t;

/* Parameter for ISO transfer command */
typedef struct smc_iso_transfer_t {
    uint8 *command;
    int32 num_to_write; 
    uint8 *response; 
    int32 num_to_read; 
    int32 actual_size;
    int32 transfer_err;
}smc_iso_transfer_t;

/* Parameter for Historical Byte of ATR */
typedef struct smc_hb_t
{
	uint8 *hb;
	uint8 hbn;
}smc_hb_t;

/* Card class parameter */
enum class_selection
{
	SMC_CLASS_NONE_SELECT = 0,
	SMC_CLASS_A_SELECT,
	SMC_CLASS_B_SELECT,
	SMC_CLASS_C_SELECT	
};

/* Smart card attach config parameter */
struct smc_dev_cfg			//Struct for smc driver configure
{
	uint32	init_clk_trigger : 1;	/*0, use default initial clk 3.579545MHz. 
								1, use configed initial clk.*/
	uint32	def_etu_trigger : 1;	/*0, use HW detected ETU as initial ETU. 
								1, use configed ETU as initial ETU.*/
	uint32	sys_clk_trigger : 1; 	/*Currently, useless*/
	uint32	gpio_cd_trigger : 1;	/*Current down detecting, , while power off, a gpio int will notify
								CPU to do deactivation*/
	uint32	gpio_cs_trigger : 1;	/*Currently, useless*/
	uint32  	force_tx_rx_trigger: 1; /*Support TX/RX timely switch*/
	uint32	parity_disable_trigger: 1; /*0, disable parity check while get ATR. 
									1, enable parity check while get ATR.*/
	uint32	parity_odd_trigger: 1; /*0, use even parity while get ATR. 
									1, use odd parity while get ATR.*/
	uint32	apd_disable_trigger: 1;/*0, enable auto pull down function while get ATR. 
									1, disable auto pull down while get ATR.*/
	uint32	type_chk_trigger : 1;		/*0, don't care card type check, 1, check card type
									is A, B or AB type according to interface device setting*/	
	uint32 	warm_reset_trigger: 1;	/*0, all the reset are cold reset. 1, all the reset are warm 
									reset except the first one.*/	
	uint32	gpio_vpp_trigger : 1;		/*Use a gpio pin to provide Vpp signal*/
	uint32 	disable_pps: 1;		
	uint32	invert_power: 1;
	uint32	invert_detect: 1;	
	uint32	class_selection_supported: 1;	 /*indicate current board support more than one class*/
	uint32 	board_supported_class: 6;	/*indicate classes supported by current board*/
	uint32 	en_power_open_drain:1;
	uint32 	en_clk_open_drain:1;
	uint32 	en_data_open_drain:1;
	uint32 	en_rst_open_drain:1;		
	uint32	reserved : 6;									
	uint32	init_clk_number;
	uint32  *init_clk_array;
	uint32	default_etu;
	uint32	smc_sys_clk;
	uint32 	gpio_cd_pol:1;		/* Polarity of GPIO, 0 or 1 active */
	uint32 	gpio_cd_io:1;		/* HAL_GPIO_I_DIR or HAL_GPIO_O_DIR in hal_gpio.h */
	uint32 	gpio_cd_pos: 14;	
	uint32 	gpio_cs_pol:1;		/* Polarity of GPIO, 0 or 1 active */
	uint32 	gpio_cs_io:1;		/* HAL_GPIO_I_DIR or HAL_GPIO_O_DIR in hal_gpio.h */
	uint32 	gpio_cs_pos: 14;	
	uint8   force_tx_rx_cmd;
	uint8   force_tx_rx_cmd_len;
	uint8   intf_dev_type;
	uint8   reserved1;
	uint32 	gpio_vpp_pol:1;		/* Polarity of GPIO, 0 or 1 active */
	uint32 	gpio_vpp_io:1;		/* HAL_GPIO_I_DIR or HAL_GPIO_O_DIR in hal_gpio.h */
	uint32 	gpio_vpp_pos: 14;	
	uint32	ext_cfg_tag;
	void			*ext_cfg_pointer;
	void			(*class_select)(enum class_selection );	/*call back function for class selection operation*/
	int32				use_default_cfg;
};
/* T1 transfer parameter */
typedef struct smc_t1_trans_t {
    uint8 dad;
    void *send_buf; 
    uint32 send_len; 
    void *rcv_buf;
    uint32 rcv_len;
}smc_t1_trans_t;

/* T1 transfer parameter */
typedef struct smc_t1_xcv_t {
    uint8 *sblock;
    uint32 slen;
    uint8 *rblock;
    uint32 rmax;
    uint32 actual_size;
}smc_t1_xcv_t;

/* T1 negotiate ifsd */
typedef struct smc_t1_nego_ifsd_t {
    uint32 dad;
    int32 ifsd;
}smc_t1_nego_ifsd_t;

/* Encode I/O command */
#define SMC_CMD_GET_CARD_STATUS     _IOR('o', 526, unsigned short)      /* get if card inserted: 0 not; 1 yes */
#define SMC_CMD_SET_TRANSPORT_ID    _IOW('o', 527, uint32)       /* set port for app / kernel communication */
#define SMC_CMD_RESET               _IOWR('o', 528, smc_atr_t)          /* reset smart card reader */
#define SMC_CMD_DEACTIVE            _IO('o', 529)                       /* deactive the smart card reader */
#define SMC_CMD_ISO_TRANS           _IOWR('o', 530, smc_iso_transfer_t) /* iso 7816 transferation command */
#define SMC_CMD_ISO_TRANS_T1        _IOWR('o', 531, smc_iso_transfer_t) /* iso 7816 transferation command */
#define SMC_CMD_SET_IO_ONOFF        _IOW('o', 533, int32)                 /* enable / disable smart card reader */
#define SMC_CMD_SET_ETU			    _IOW('o', 534, uint32)       /* set working etu */
#define SMC_CMD_SET_WWT			    _IOW('o', 535, uint32)       /* set block waiting time, in unit of ms */			
#define SMC_CMD_SET_GUARDTIME	    _IOW('o', 536, int32)                 /* to do */
#define SMC_CMD_SET_BAUDRATE		_IOW('o', 537, int32)                 /* to do */
#define SMC_CMD_CHECK_STATUS		_IOR('o', 538, int32) 
#define SMC_CMD_CLKCHG_SPECIAL	    _IOW('o', 539, int32)                 /* to do */
#define SMC_CMD_FORCE_SETTING	    _IOW('o', 540, int32)                 /* to do */
#define SMC_CMD_SET_CWT			    _IOW('o', 541, uint32)       /* set character waiting time, in unit of ms */
#define SMC_CMD_GET_F				_IOR('o', 542, uint32)       /* get F factor value */
#define SMC_CMD_GET_D				_IOR('o', 543, uint32)       /* get D factor value */
#define SMC_CMD_GET_ATR_RESULT 	    _IOR('o', 544, int32)                 /* check ATR status */
#define SMC_CMD_GET_HB				_IOR('o', 545, smc_hb_t)            /* get History Bytes */
#define SMC_CMD_GET_PROTOCOL		_IOR('o', 546, uint32)       /* get card current protocol */
#define SMC_CMD_SET_WCLK			_IOW('o', 547, uint32)       /* set the working clock of smc,  */
									                                    /* the new setting value will be used from */
									                                    /* next time reset */
#define SMC_CMD_GET_CLASS			_IOR('o', 548, int32)                 /* return the currently selected classs */
#define SMC_CMD_SET_CLASS			_IOW('o', 549, int32)                 /* setting new class selection if previous select fail */
#define SMC_CMD_T1_TRANS			_IOWR('o', 550, smc_t1_trans_t)     /* t1 communication */
#define SMC_CMD_T1_XCV              _IOWR('o', 551, smc_t1_xcv_t)       /* t1 xcv */
#define SMC_CMD_T1_NEGO_IFSD        _IOW('o', 552, smc_t1_nego_ifsd_t)  /* t1 xcv */
#define SMC_CMD_CONFIG			    _IOW('o', 553, struct smc_dev_cfg)  /* config smartcard */
#define SMC_CMD_DECONFIG			_IO('o', 554)						/* de-config smartcard */
#define SMC_CMD_SEND_PPS			_IOW('o', 555, uint32) 
#define SMC_CMD_SET_OPEN_DRAIN		_IOW('o', 556, uint32) 
#define SMC_CMD_SET_DEBUG_LEVEL		_IOW('o', 557, uint32) 


#endif
