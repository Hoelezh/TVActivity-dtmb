/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 Copyright (C)
*
*    File:    pan_dev.h
*
*    Description:    This file contains pan_device structure define in HLD.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Apr.21.2003      Justin Wu       Ver 0.1    Create file.
*****************************************************************************/

#ifndef __ADR_HLD_PAN_DEV_H__
#define __ADR_HLD_PAN_DEV_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <hld/adr_hld_dev.h>

/*! @addtogroup pan
 *  @{
 */

/*! @enum pan_device_panel_ioctrl_command
    @brief 前面板IO命令集。
*/
enum pan_device_panel_ioctrl_command
{	
	PAN_DRIVER_ATTACH	= 0,			//!<Front panel driver attach command 	
	PAN_DRIVER_SUSPEND	= 1,			//!<Front panel driver suspend command 
	PAN_DRIVER_RESUME	= 2,			//!<Front panel driver resume command 		
	PAN_DRIVER_DETACH	= 3,			//!<Front panel driver detach command 
	PAN_DRIVER_READ_LNB_POWER = 4,		//!<Front panel driver NIM LNB power protect status 
	PAN_DRIVER_WRITE_LED_ONOFF =5,
	PAN_DRIVER_UART_SELECT = 6,
	PAN_DRIVER_SET_GPIO	= 7,			//!<Front panel driver set gpio command 
	PAN_DRIVER_GET_GPIO = 8,			//!<Front panel driver get gpio value 
	PAN_DRIVER_STANDBY  = 9,        	//!<Front panel driver enter low power mode 
	PAN_DRIVER_SK_DETECT_POLAR = 10,			//!<Front panel driver set key detect polor, only enable for shadow scan 
	PAN_DRIVER_SET_HW_INFO	= 11,		//!<Front panel driver set hw info command 
	PAN_DRIVER_GET_HW_INFO	= 12,		//!<Front panel driver get hw info command 
	PAN_DRIVER_WRITE_REG	= 13,		//!<Front panel driver write register command 
	PAN_DRIVER_READ_REG	= 14,			//!<Front panel driver read register command 	
	PAN_DRIVER_SET_I2C	= 15,			//!<Front panel driver set command, byte0, I2C ID; byte1, 1 gpio_i2c, 0 i2c byte2, SDA; byte3, SCL; 
	PAN_DRIVER_SET_DIG_ADDR = 16,	//!<Front panel driver set command, byte0, dig0_addr; byte1, dig1_addr; byte2, dig2_addr; byte3, dig3_addr.
	PAN_DRIVER_SET_LED_BITMAP = 17,	//!<Front panel driver set command, set led bit map.
};

/*! @enum pan_device_ir_ioctrl_command
    @brief 前面板IO命令集。
*/
enum pan_device_ir_ioctrl_command
{
	PAN_DRIVER_IR_SET_STANDBY_KEY	= 0xfff0,		//!<Remote controller driver set standby key command 	
	PAN_DRIVER_IR_SET_ENDIAN			,			//!<Remote controller driver set endian command 
	PAN_DRIVER_IR_SET_RESUME_KEY		,		//!<Remote controller driver set resume key command 
	PAN_DRIVER_IR_SET_EMOUSE		    ,		//!<Remote controller driver set emulate mouse speed...
};

/*! @enum pan_key_type
    @brief 前面板按键类型。
*/
typedef enum pan_key_type
{
	PAN_KEY_TYPE_INVALID	= 0,	//!<Invalid key type 
	PAN_KEY_TYPE_REMOTE	= 1,	//!<Remote controller 
	PAN_KEY_TYPE_PANEL	= 2,	//!<Front panel 
	PAN_KEY_TYPE_JOYSTICK	= 3,	//!<Game joy stick 
	PAN_KEY_TYPE_KEYBOARD	= 4	//!<Key board 
}pan_key_type_e;

/*! @enum pan_key_press
    @brief 前面板按键状态。
*/
typedef enum pan_key_press
{
	PAN_KEY_RELEASE		= 0,
	PAN_KEY_PRESSED		= 1,
	PAN_KEY_REPEAT		= 2
}pan_key_press_e;

/*! @enum pan_ir_protocol
    @brief 支持的红外遥控协议。
*/
typedef enum pan_ir_protocol
{
	IR_TYPE_NEC = 0,
	IR_TYPE_LAB,
	IR_TYPE_50560,
	IR_TYPE_KF,
	IR_TYPE_LOGIC,
	IR_TYPE_SRC,
	IR_TYPE_NSE,
	IR_TYPE_RC5,
	IR_TYPE_RC6,
	IR_TYPE_UNDEFINE
}pan_ir_protocol_e;

/*! @enum pan_device_status
    @brief 前面板设备状态。
*/
typedef enum pan_device_status
{
	PAN_DEV_ATTACH = 0,
	PAN_DEV_OPEN,
	PAN_DEV_CLOSE,
	PAN_DEV_DETACH	
}pan_device_status_e;

/*! @struct pan_device_stats
    @brief 前面板设备状态。
*/
struct pan_device_stats
{
	UINT16	display_num;		//!<Number of display data 
};

/*!@struct pan_key
   @brief 前面板按键信息。
*/
struct pan_key
{
	UINT8  type;			//!<The key type 
	UINT8  state;			//!<The key press state 
	UINT16 count;			//!<The key counter 
	UINT32 code;			//!<The value 
};

/*!@struct pan_key_index
   @brief 前面板按键信息及其索引。
*/
struct pan_key_index
{
	struct pan_key  key_value;	//!<The pan key 	
	UINT16 key_index;		//!<The key index 	
};

/*!@struct pan_key_info
   @brief 前面板按键信息。
*/
struct pan_key_info
{
	UINT32  code_high;			//!<The key value of high
	UINT32  code_low;				//!<The key value of low
	pan_ir_protocol_e protocol;		//!<The ir protocol 
	pan_key_press_e state;			//!<The key press state
	pan_key_type_e type;			//!<The key press type
};

/*!@struct pan_standby_key
   @brief 前面板待机按键信息。
*/
struct pan_standby_key{
	unsigned char enable;
	unsigned long key;
};

/*!@struct pan_ir_endian
   @brief 前面板红外协议大小端模式。
*/
struct pan_ir_endian{
	unsigned int enable;
	pan_ir_protocol_e protocol;
	unsigned int bit_msb_first;
	unsigned int byte_msb_first;	
};

/*!@struct pan_device
   @brief 前面板驱动模块设备节点。
*/
struct pan_device
{
	struct hld_device   *next;			//!<Next device structure 
	UINT32		type;				//!<Interface hardware type 
	INT8		name[HLD_MAX_NAME_SIZE];	//!<Device name 

	UINT16		flags;				//!<Interface flags, status and ability 

	UINT16		led_num;			//!<Number of LED 
	UINT16		key_num;			//!<Number of input keys in Front panel 

	/* Hardware privative structure */
	void		*priv;				//!<pointer to private data 

	/*
	 *  Functions of this panel device
	 */
	INT32	(*init)();

	INT32	(*open)(struct pan_device *dev);

	INT32	(*stop)(struct pan_device *dev);

	void	(*display)(struct pan_device *dev, char *data, UINT32 len);

	INT32	(*send_data)(struct pan_device *dev, UINT8 *data, UINT32 len, UINT32 timeout);

	INT32	(*receive_data)(struct pan_device *dev, UINT8 *data, UINT32 len, UINT32 timeout);

	INT32	(*do_ioctl)(struct pan_device *dev, INT32 cmd, UINT32 param);

	struct pan_device_stats* (*get_stats)(struct pan_device *dev);
};

/*!
 @}
 */
#ifdef __cplusplus
	}
#endif

#endif  /* __HLD_PAN_DEV_H__ */
