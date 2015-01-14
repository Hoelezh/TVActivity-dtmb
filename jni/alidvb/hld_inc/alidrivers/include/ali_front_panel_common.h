#ifndef _ALI_FRONT_PANEL_COMMON_H_
#define _ALI_FRONT_PANEL_COMMON_H_

#define HWSCAN_DEV_NAME			    "pan_hwscan"
#define HWSCAN_DEV_INPUT_NAME		HWSCAN_DEV_NAME
#define CH455_DEV_NAME				"pan_ch455"
#define CH455_DEV_INPUT_NAME		CH455_DEV_NAME
#define CS1628_DEV_NAME			"pan_cs1628"
#define CS1628_DEV_INPUT_NAME		CS1628_DEV_NAME
/*ALi IR driver io command**********************************/

#define ALI_FP_IO_COMMAND_BASE						0xf0
#define ALI_FP_CONFIG_KEY_MAP						(ALI_FP_IO_COMMAND_BASE+1)
#define ALI_FP_DATA_TRANSFER						(ALI_FP_IO_COMMAND_BASE+2)
#define ALI_FP_TRANSFER_CHECK						(ALI_FP_IO_COMMAND_BASE+3)
#define ALI_FP_GET_IR_INT_COUNT						(ALI_FP_IO_COMMAND_BASE+4)
#define ALI_FP_GET_IR_KEY_RECEIVED_COUNT			(ALI_FP_IO_COMMAND_BASE+5)
#define ALI_FP_GET_IR_KEY_MAPPED_COUNT			    (ALI_FP_IO_COMMAND_BASE+6)
#define ALI_FP_SET_IR_KEY_DEBUG						(ALI_FP_IO_COMMAND_BASE+7)
#define ALI_FP_GET_PAN_KEY_RECEIVED_COUNT		    (ALI_FP_IO_COMMAND_BASE+8)
#define ALI_FP_GET_PAN_KEY_MAPPED_COUNT			    (ALI_FP_IO_COMMAND_BASE+9)
#define ALI_FP_SET_PAN_KEY_DEBUG					(ALI_FP_IO_COMMAND_BASE+10)
#define ALI_FP_GET_CONFIG_PAN_KEY_MAP				(ALI_FP_IO_COMMAND_BASE+11)
#define ALI_FP_SET_SOCKPORT						    (ALI_FP_IO_COMMAND_BASE+12)
#define ALI_FP_SET_REPEAT_INTERVAL					(ALI_FP_IO_COMMAND_BASE+13)

#define IR_FORMAT_MAX			8
#define IR_FORMAT_NEC		0x0001
#define IR_FORMAT_LAB		0x0002
#define IR_FORMAT_50560		0x0004
#define IR_FORMAT_KF		0x0008
#define IR_FORMAT_LOGIC		0x0010
#define IR_FORMAT_SRC		0x0020
#define IR_FORMAT_NSE		0x0040
#define IR_FORMAT_RC5		0x0080
#define IR_FORMAT_RC6		0x0100

#define PAN_ALI_HKEY_MENU	0xffff0006
#define PAN_ALI_HKEY_RIGHT	0xffff0005
#define PAN_ALI_HKEY_DOWN	0xffff0003
#define PAN_ALI_HKEY_ENTER	0xffff0001
#define PAN_ALI_HKEY_LEFT	0xffff0004
#define PAN_ALI_HKEY_UP     0xffff0002


#define GPIO_NOT_USED 	255

struct ali_fp_key_map_cfg{
	unsigned char * map_entry;
	unsigned long map_len;
	unsigned long unit_len;
	unsigned long unit_num;
	unsigned long phy_code;
	unsigned long reserved;
};

struct ali_fp_key_map_t {
	unsigned long code;
	unsigned short key;
};

struct ali_fp_data_transfer_param{
	unsigned char * tx_buf;
	unsigned long tx_len;
	unsigned char * rx_buf;
	unsigned long rx_len;
	unsigned long tmo;
};

struct ali_fp_bit_map_cfg{
	unsigned char * map_entry;
	unsigned long map_len;	
};
#endif /*_ALI_FRONT_PANEL_COMMON_H_*/
