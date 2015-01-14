/****************************************************************************
 *
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2009 Copyright (C)
 *
 *  File: otp.h
 *
 *  Description: This file provide common otp interface.
 *
 *  History:
 *      Date        	Author      	Version  		Comment
 *      ====        	======      	=======  	=======
 *  1.  2009.8.25   	Goliath Peng   0.1.000  		Initial
 ****************************************************************************/

#ifndef	__OTP_H__
#define __OTP_H__

#ifdef __cplusplus
extern "C" {
#endif


#define OTP_ERR_NOSUPPORT		(-1)
#define OTP_ERR_LOCKTMO		(-2)

#define OTP_VOLTAGE_6V5 65    //OTP voltage 6.5V
#define OTP_VOLTAGE_1V8 18    //OTP voltage 1.8V

#define BL_VER    0
#define UB_VER    2 
#define SW_VER    1
#define APP_VER   3  
#define OTP_ADDESS_BL_VER    0x74
#define OTP_ADDESS_UB_VER    0x70   
#define OTP_ADDESS_SW_VER   0x78
#define OTP_ADDESS_APP_VER  0x7c
#define MAX_VERSION_NUM        128


/*voltage control callback function, OTP driver will tell APP the correct voltage by 
* OTP_VOLTAGE_6V5 or OTP_VOLTAGE_6V5*/
typedef void(*OTP_VOLTAGE_CONTROL)(UINT32 voltage);

/* APP must make OTP driver to control programming voltage to guarantee program timming.
* So App can choose to register GPIO to OTP driver or register voltage control callback function to OTP driver*/
typedef struct {
	UINT16	vpp_by_gpio: 1;		/*1: we need use one GPIO control vpp voltage.*/
								/*0: we use Jumper to switch vpp voltage.*/
	UINT16	reserved1: 15;		/*reserved for future usage*/
	UINT16	vpp_polar	: 1;		/* Polarity of GPIO, 0 or 1 active to set VPP to 6.5V*/
	UINT16	vpp_io		: 1;		/* HAL_GPIO_I_DIR or HAL_GPIO_O_DIR in hal_gpio.h */
	UINT16	vpp_position: 14;	/* GPIO Number*/
	OTP_VOLTAGE_CONTROL volctl_cb;		/*OTP program voltage control callback*/
										/*OTP_VOLTAGE_6V5 for 6.5V,OTP_VOLTAGE_1V8 for 1.8V*/
}OTP_CONFIG;

int ali_otp_read(unsigned long offset, unsigned char *buf, int len);
int ali_otp_write(unsigned char *buf, unsigned long offset, int len);
int ali_otp_lock(UINT32 offset, INT32 len);

#define otp_init(cfg)				do{}while(0)
#define otp_read(offset, buf, len)	ali_otp_read(offset, buf, len)
#define otp_write(buf, offset, len)	ali_otp_write(buf, offset, len)
#define otp_lock(offset, len)		ali_otp_lock(offset, len)

UINT32 ali_stb_ver_get();
INT32 ali_stb_ver_check();

#ifdef __cplusplus
}
#endif

#endif	/* __OTP_H__ */

