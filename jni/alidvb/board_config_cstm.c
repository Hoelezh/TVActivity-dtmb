

#include "board_config_cstm.h"

/*!DO NOT Remove Macro CSTM_CONFIG_KERNEL*/
//#define CSTM_CONFIG_KERNEL
//#define CSTM_CONFIG_RECOVERY

#ifdef CSTM_CONFIG_KERNEL

#define PRINT_DEBUG(fmt, args...)		printk(fmt, ##args)
#define PRINT_INFO(fmt, args...)			printk(fmt, ##args)
#define PRINT_ERROR(fmt, args...)		printk(fmt, ##args)

#elif defined(CSTM_CONFIG_RECOVERY)
#include <osal/osal.h>
#include <hld/dmx/Ali_DmxLib.h>

#define PRINT_DEBUG		OTA_DEBUG
#define PRINT_INFO		OTA_DEBUG
#define PRINT_ERROR		OTA_DEBUG

#else

#include <osal/osal.h>
#include <hld/dmx/Ali_DmxLib.h>

#include <android/log.h>

#define LOG_TAG    "Board_Config"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define PRINT_DEBUG		LOGD
#define PRINT_INFO		LOGI
#define PRINT_ERROR		LOGE

#endif

//#define TS_NOT_LOOP_OUT

static int g_board_type = -1;



void delay_ms(unsigned long ms)
{
#ifdef CSTM_CONFIG_KERNEL

	//msleep(ms);

#else
	osal_task_sleep(ms);
#endif
}

#ifdef CSTM_CONFIG_KERNEL

inline int _soc_reg_val_set8(unsigned int reg_addr, unsigned int value) 
{
	PRINT_DEBUG("%s, 0x%08x ==> 0x%08x !\n", __FUNCTION__, reg_addr, value);

	__REG8ALI(reg_addr) = (unsigned char )(value & 0xff);
	
	return 0;
}

inline int _soc_reg_val_set32(unsigned int reg_addr, unsigned int value) 
{

	PRINT_DEBUG("%s, 0x%08x ==> 0x%08x !\n", __FUNCTION__, reg_addr, value);


	__REG32ALI(reg_addr) = (value);
	
	return 0;
}

inline int _soc_reg_bits_set8(unsigned int reg_addr, unsigned int bits_clear, unsigned int bits_set) 
{

	unsigned char reg8_val;

	reg8_val = __REG8ALI(reg_addr);
	
	PRINT_DEBUG("%s, 0x%08x = 0x%08x, bits_clear = 0x%08x, bits_set = 0x%08x !\n", __FUNCTION__, reg_addr, reg8_val, bits_clear, bits_set);
	
	reg8_val &= (unsigned char )(~(bits_clear & 0xff));
	reg8_val |= (unsigned char )(bits_set & 0xff);
	__REG8ALI(reg_addr) = reg8_val;

	return 0;
	
}

inline int _soc_reg_bits_set32(unsigned int reg_addr, unsigned int bits_clear, unsigned int bits_set) 
{

	unsigned int reg32_val;

	reg32_val = __REG32ALI(reg_addr);
	PRINT_DEBUG("%s, 0x%08x = 0x%08x, bits_clear = 0x%08x, bits_set = 0x%08x !\n", __FUNCTION__, reg_addr, reg32_val, bits_clear, bits_set);
	reg32_val &= (~(bits_clear));
	reg32_val |= (bits_set);
	__REG32ALI(reg_addr) = reg32_val;

	return 0;
	
}

inline int _soc_reg_bit_set(unsigned int reg_addr,unsigned int bit, unsigned int param)
{
	unsigned int reg32_val;

	reg32_val = __REG32ALI(reg_addr);
	
	PRINT_DEBUG("%s, 0x%08x = 0x%08x, bit = 0x%08x, param = 0x%08x !\n", __FUNCTION__, reg_addr, reg32_val, bit, param);

	if(param) reg32_val |= (1<<bit);
	else reg32_val &= (~(1<<bit));
	__REG32ALI(reg_addr) = reg32_val;

}


inline int _soc_reg_bit_get(unsigned int reg_addr,unsigned int bit, unsigned int *param)
{
	unsigned int reg32_val;

	reg32_val = __REG32ALI(reg_addr);
	PRINT_DEBUG("%s, 0x%08x = 0x%08x, bit = 0x%08x, param = 0x%08x !\n", __FUNCTION__, reg_addr, reg32_val, bit, param);
	if(param)
	{
		*param = (reg32_val & (1<<bit)) ? 1:0;
	}

	return 0;
}

#else
inline int _soc_reg_val_set8(unsigned int reg_addr, unsigned int value) 
{
	unsigned char reg8_val;

	if (0 == soc_read8(reg_addr, (unsigned char *) (&reg8_val), 1)) 
	{
		PRINT_DEBUG("%s, before, 0x%08x = 0x%08x !\n", __FUNCTION__, reg_addr, reg8_val);
		reg8_val = (unsigned char )(value & 0xff);
		soc_write8(reg_addr, (unsigned char *) (&reg8_val), 1);
		soc_read8(reg_addr, (unsigned char *) (&reg8_val), 1);
		PRINT_DEBUG("%s, after, 0x%08x = 0x%08x!\n", __FUNCTION__, reg_addr, reg8_val);

	}
	else 
	{
		PRINT_ERROR("%s, RegAdr[0x%08x] fail \n", __FUNCTION__, reg_addr);
		return 1;
	}

	return 0;

}

inline int _soc_reg_val_set32(unsigned int reg_addr,unsigned int value) 
{
	unsigned int reg32_val;

	if (0 == soc_read32(reg_addr, (unsigned char *) (&reg32_val), 1)) 
	{
		PRINT_DEBUG("[%s]before, 0x%08x = 0x%08x, !\n", __FUNCTION__, reg_addr, reg32_val);
		reg32_val = value;
		soc_write32(reg_addr, (unsigned char *) (&reg32_val), 1);
		soc_read32(reg_addr, (unsigned char *)(&reg32_val), 1);
		PRINT_DEBUG("[%s]after, 0x%08x = 0x%08x!\n", __FUNCTION__, reg_addr, reg32_val);

	} else {
		PRINT_ERROR("%s, RegAdr[0x%08x] fail \n", __FUNCTION__, reg_addr);
		return 1;
	}

	return 0;

}


inline int _soc_reg_bits_set8(unsigned int reg_addr, unsigned int bits_clear, unsigned int bits_set) 
{
	unsigned char reg8_val;

	if (0 == soc_read8(reg_addr, (unsigned char *) (&reg8_val), 1)) 
	{
		PRINT_DEBUG("%s, before, 0x%08x = 0x%08x, bits_clear = 0x%08x, bits_set = 0x%08x !\n", __FUNCTION__, reg_addr, reg8_val, bits_clear, bits_set);
		reg8_val &= (~(bits_clear & 0xff));
		reg8_val |= (bits_set & 0xff);
		soc_write8(reg_addr, (unsigned char *) (&reg8_val), 1);
		soc_read8(reg_addr, (unsigned char *) (&reg8_val), 1);
		PRINT_DEBUG("%s, after, 0x%08x = 0x%08x!\n", __FUNCTION__, reg_addr, reg8_val);

	}
	else 
	{
		PRINT_ERROR("%s, RegAdr[0x%08x] fail \n", __FUNCTION__, reg_addr);
		return 1;
	}

	return 0;

}

inline int _soc_reg_bits_set32(unsigned int reg_addr,unsigned int bits_clear, unsigned int bits_set) 
{
	unsigned int reg32_val;

	if (0 == soc_read32(reg_addr, (unsigned char *) (&reg32_val), 1)) 
	{
		PRINT_DEBUG("[%s]before, 0x%08x = 0x%08x, bits_clear = 0x%08x, bits_set = 0x%08x !\n", __FUNCTION__, reg_addr, reg32_val, bits_clear, bits_set);
		reg32_val &= (~bits_clear);
		reg32_val |= bits_set;
		soc_write32(reg_addr, (unsigned char *) (&reg32_val), 1);
		soc_read32(reg_addr, (unsigned char *)(&reg32_val), 1);
		PRINT_DEBUG("[%s]after, 0x%08x = 0x%08x!\n", __FUNCTION__, reg_addr, reg32_val);

	} else {
		PRINT_ERROR("%s, RegAdr[0x%08x] fail \n", __FUNCTION__, reg_addr);
		return 1;
	}

	return 0;

}


inline int _soc_reg_bit_set(unsigned int reg_addr,unsigned int bit, unsigned int param)
{
	unsigned int reg32_val;

	if (0 == soc_read32(reg_addr, (unsigned char *) (&reg32_val), 1)) 
	{
		PRINT_DEBUG("[%s]before, 0x%08x = 0x%08x\n", __FUNCTION__, reg_addr, reg32_val);
		if(param) reg32_val |= (1<<bit);
		else reg32_val &= (~(1<<bit));
		soc_write32(reg_addr, (unsigned char *) (&reg32_val), 1);
		soc_read32(reg_addr, (unsigned char *)(&reg32_val), 1);
		PRINT_DEBUG("[%s]after, 0x%08x = 0x%08x!\n", __FUNCTION__, reg_addr, reg32_val);

	} else {
		PRINT_ERROR("%s, RegAdr[0x%08x] fail \n", __FUNCTION__, reg_addr);
		return 1;
	}

	return 0;

}


inline int _soc_reg_bit_get(unsigned int reg_addr,unsigned int bit, unsigned int *param)
{
	unsigned int reg32_val;

	if (0 == soc_read32(reg_addr, (unsigned char *) (&reg32_val), 1)) 
	{
		PRINT_DEBUG("[%s]0x%08x = 0x%08x\n", __FUNCTION__, reg_addr, reg32_val);
		if(param)
		{
			*param = (reg32_val & (1<<bit)) ? 1:0;
		}

	} else {
		PRINT_ERROR("%s, RegAdr[0x%08x] fail \n", __FUNCTION__, reg_addr);
		return 1;
	}

	return 0;
}

#endif


inline int _gpio_enable(unsigned int gpio_num, unsigned int param)
{
	unsigned int reg_addr;
	unsigned int bit = 0;

	PRINT_DEBUG("[%s]gpio_num %u, param %u\n", __FUNCTION__, gpio_num, param);

	if(gpio_num == GPIO_NULL)
	{
		return 1;
	}
	
	if(gpio_num < 32)
	{
		reg_addr = HAL_GPIO_EN_REG;
		bit = gpio_num;
	}
	else if(gpio_num < 64)
	{
		reg_addr = HAL_GPIO1_EN_REG;
		bit = gpio_num - 32;
	}
	else if(gpio_num < 96)
	{
		reg_addr = HAL_GPIO2_EN_REG;
		bit = gpio_num - 64;
	}
	else if(gpio_num < 128)
	{
		reg_addr = HAL_GPIO3_EN_REG;
		bit = gpio_num - 96;
	}
	else
	{
		return 1;
	}

	if(_soc_reg_bit_set(reg_addr, bit, param) != 0)
	{
		PRINT_ERROR("%s, RegAdr[0x%08x] fail \n", __FUNCTION__, reg_addr);
		return 1;
	}

	return 0;
	
	
}

inline int _gpio_set_dir(unsigned int gpio_num, unsigned int param)
{
	unsigned int reg_addr;
	unsigned int bit = 0;

	PRINT_DEBUG("[%s]gpio_num %u, param %u\n", __FUNCTION__, gpio_num, param);

	if(gpio_num == GPIO_NULL)
	{
		return 1;
	}
	
	if(gpio_num < 32)
	{
		reg_addr = HAL_GPIO_DIR_REG;
		bit = gpio_num;
	}
	else if(gpio_num < 64)
	{
		reg_addr = HAL_GPIO1_DIR_REG;
		bit = gpio_num - 32;
	}
	else if(gpio_num < 96)
	{
		reg_addr = HAL_GPIO2_DIR_REG;
		bit = gpio_num - 64;
	}
	else if(gpio_num < 128)
	{
		reg_addr = HAL_GPIO3_DIR_REG;
		bit = gpio_num - 96;
	}
	else
	{
		return 1;
	}

	if(_soc_reg_bit_set(reg_addr, bit, param) != 0)
	{
		PRINT_ERROR("%s, RegAdr[0x%08x] fail \n", __FUNCTION__, reg_addr);
		return 1;
	}

	return 0;

}

inline int _gpio_set_output(unsigned int gpio_num, unsigned int param)
{
	unsigned int reg_addr;
	unsigned int bit = 0;

	PRINT_DEBUG("[%s]gpio_num %u, param %u\n", __FUNCTION__, gpio_num, param);

	if(gpio_num == GPIO_NULL)
	{
		return 1;
	}
	
	if(gpio_num < 32)
	{
		reg_addr = HAL_GPIO_DO_REG;
		bit = gpio_num;
	}
	else if(gpio_num < 64)
	{
		reg_addr = HAL_GPIO1_DO_REG;
		bit = gpio_num - 32;
	}
	else if(gpio_num < 96)
	{
		reg_addr = HAL_GPIO2_DO_REG;
		bit = gpio_num - 64;
	}
	else if(gpio_num < 128)
	{
		reg_addr = HAL_GPIO3_DO_REG;
		bit = gpio_num - 96;
	}
	else
	{
		return 1;
	}

	if(_soc_reg_bit_set(reg_addr, bit, param) != 0)
	{
		PRINT_ERROR("%s, RegAdr[0x%08x] fail \n", __FUNCTION__, reg_addr);
		return 1;
	}

	return 0;

}

inline int _gpio_get_input(unsigned int gpio_num, unsigned int *param)
{
	unsigned int reg_addr;
	unsigned int bit = 0;

	PRINT_DEBUG("[%s]gpio_num %u, param 0x%0x\n", __FUNCTION__, gpio_num, param);

	if(NULL == param)
	{
		return 1;
	}

	if(gpio_num == GPIO_NULL)
	{
		return 1;
	}
	
	if(gpio_num < 32)
	{
		reg_addr = HAL_GPIO_DI_REG;
		bit = gpio_num;
	}
	else if(gpio_num < 64)
	{
		reg_addr = HAL_GPIO1_DI_REG;
		bit = gpio_num - 32;
	}
	else if(gpio_num < 96)
	{
		reg_addr = HAL_GPIO2_DI_REG;
		bit = gpio_num - 64;
	}
	else if(gpio_num < 128)
	{
		reg_addr = HAL_GPIO3_DI_REG;
		bit = gpio_num - 96;
	}
	else
	{
		return 1;
	}

	if(_soc_reg_bit_get(reg_addr, bit, param) != 0)
	{
		PRINT_ERROR("%s, RegAdr[0x%08x] fail \n", __FUNCTION__, reg_addr);
		return 1;
	}

	return 0;

}


/*
USB host mode :5V enable
USB device mode: 5V disable
*/
void usb_p0_5v_setting(char value)
{

	_gpio_enable(GPIO_USB0_POWER, HAL_GPIO_ENABLE);
	_gpio_set_dir(GPIO_USB0_POWER, HAL_GPIO_O_DIR);
	if(value)
	{
		_gpio_set_output(GPIO_USB0_POWER, 1);
	}
	else
	{
		_gpio_set_output(GPIO_USB0_POWER, 0);
	}
	
}


#ifdef SUPPORT_GOSPELL_BOARD
#if 0
/*
h_v ==0: V, 13V; ==1: H, 18V
*/
void lnb_set_h_v(UINT32 h_v)
{
	PRINT_DEBUG("lnb_set_h_v::h_v=%d\n",h_v);
	if(h_v)
		_gpio_set_output(UTI_GPIO_LNB, 0);
	else
		_gpio_set_output(UTI_GPIO_LNB, 1);
		
}
#else//
void set_lnb_power(UINT32 onoff)
{
	PRINT_DEBUG("set_lnb_power::onoff=%d\n",onoff);
	if(onoff)
		_gpio_set_output(UTI_GPIO_LNB_POWER, 1);
	else
		_gpio_set_output(UTI_GPIO_LNB_POWER, 0);
		
}
#endif
void uti_reset()
{
		PRINT_DEBUG("%s +++++++++++++++\n", __FUNCTION__);
	_gpio_set_output(UTI_GPIO_POWERON, 1);
	_gpio_set_output(UTI_GPIO_RESET, 0);
	delay_ms(100);
	_gpio_set_output(UTI_GPIO_RESET, 1);
		PRINT_DEBUG("%s --------------------------\n", __FUNCTION__);
}

void uti_init()
{
	unsigned int reg_adr;
	unsigned int bits_clear;
	unsigned int bits_set;

	PRINT_DEBUG("%s +++++++++++++++\n", __FUNCTION__);

	
	_gpio_enable(UTI_GPIO_RESET, HAL_GPIO_ENABLE);
	_gpio_enable(UTI_GPIO_POWERON, HAL_GPIO_ENABLE);
	_gpio_enable(UTI_GPIO_LNB_POWER, HAL_GPIO_ENABLE);
	_gpio_enable(UTI_GPIO_DETECT0, HAL_GPIO_ENABLE);
	_gpio_enable(UTI_GPIO_DETECT1, HAL_GPIO_ENABLE);
	_gpio_enable(UTI_GPIO_INT, HAL_GPIO_ENABLE);

	_gpio_set_dir(UTI_GPIO_RESET, HAL_GPIO_O_DIR);
	_gpio_set_dir(UTI_GPIO_POWERON, HAL_GPIO_O_DIR);
	_gpio_set_dir(UTI_GPIO_LNB_POWER, HAL_GPIO_O_DIR);
	_gpio_set_dir(UTI_GPIO_DETECT0, HAL_GPIO_I_DIR);
	_gpio_set_dir(UTI_GPIO_DETECT1, HAL_GPIO_I_DIR);
	_gpio_set_dir(UTI_GPIO_INT, HAL_GPIO_I_DIR);

	/*uti i2c init*/
	reg_adr = PINMUX_CTRL_REG0;
	bits_set = 0;
	bits_clear = 0;
	bits_set |= (1 << XI2C_1_SEL_BIT);
	bits_clear |= (1 << QAM256_PCM_SEL_BIT);
	_soc_reg_bits_set32(reg_adr, bits_clear, bits_set);

	/*disable GPIO:91,92, for i2c*/
	_gpio_enable(91, HAL_GPIO_DISABLE);
	_gpio_enable(92, HAL_GPIO_DISABLE);

	uti_reset();

	PRINT_DEBUG("%s --------------------------\n", __FUNCTION__);
	
}





unsigned int gospell_board_detect()
{
	unsigned int dectect0 = 1, dectect1 = 1;
	unsigned int board_type = BOARD_NULL;

	_gpio_get_input(UTI_GPIO_DETECT0, &dectect0);
	_gpio_get_input(UTI_GPIO_DETECT1, &dectect1);

	if((dectect0 == 0) && (dectect1 == 0))
	{
		board_type = BOARD_DVBS2;
	}
	else if((dectect0 == 0) && (dectect1 == 1))
	{
		board_type = BOARD_DTMB;
	}
	else if((dectect0 == 1) && (dectect1 == 0))
	{
		board_type = BOARD_DVBC;
	}

	PRINT_DEBUG("<0>[%s]board_type %d\n", __FUNCTION__, board_type);

	return board_type;

}

inline unsigned int gospell_get_board_type()
{
#if (GOSPELL_NIM == BY_DETECT)
	if(g_board_type == -1) g_board_type = gospell_board_detect();
	return g_board_type;
#else
	PRINT_DEBUG("[%s]board_type %d\n", __FUNCTION__, GOSPELL_NIM);
	return GOSPELL_NIM;
#endif
}


void gospell_tuner_config()
{
	unsigned int reg_adr;
	unsigned int bits_clear;
	unsigned int bits_set;
	unsigned int board_type = gospell_get_board_type();
	PRINT_DEBUG("%s +++++++++++++++\n", __FUNCTION__);

	if(board_type == BOARD_DVBC)
	{
		/*dvbc tuner use AGC1*/
		/*config pinmux ctrl reg0*/
		reg_adr = PINMUX_CTRL_REG0;
		bits_set = 0;
		bits_clear = 0;
		bits_set |= (1 << XIF_AGC_PDM_SEL2_BIT);
		bits_clear |= ((1 << IR_TX_SEL_BIT) | (1 << TVENC_SYNC_SEL3_BIT));
		_soc_reg_bits_set32(reg_adr, bits_clear, bits_set);

		_gpio_enable(127, HAL_GPIO_DISABLE);
	}

	PRINT_DEBUG("%s --------------------------\n", __FUNCTION__);
	
}

void gospell_tso_config()
{
	unsigned int reg_adr, reg8_val;
	unsigned int bits_clear;
	unsigned int bits_set;
	unsigned int board_type = gospell_get_board_type();


	PRINT_DEBUG("%s +++++++++++++++\n", __FUNCTION__);
	if (board_type == BOARD_DVBC)
	{
		/*use qam ssi*/
		/*config pinmux ctrl reg0*/
		reg_adr = PINMUX_CTRL_REG0;
		bits_set = 0;
		bits_clear = 0;
		bits_clear |= (1 << TVENC_SYNC_SEL3_BIT);
		bits_clear |= (1 << XUART2_SEL1_BIT);
		bits_clear |= (1 << AUD_I2SIO_SEL_BIT);
		_soc_reg_bits_set32(reg_adr, bits_clear, bits_set);

		/*config pinmux ctrl reg1*/
		reg_adr = PINMUX_CTRL_REG1;
		bits_set = 0;
		bits_clear = 0;
		bits_set |= (1 << QAM_SSI_256_SEL2_BIT);
		bits_clear |= (1 << ALISSI_SEL2_BIT);
		bits_clear |= (1 << USB_DEBUG_SEL_BIT);
		_soc_reg_bits_set32(reg_adr, bits_clear, bits_set);


		/*disable GPIO: 7, 8, 118, 119, for tso*/
		_gpio_enable(7, HAL_GPIO_DISABLE);
		_gpio_enable(8, HAL_GPIO_DISABLE);
		_gpio_enable(118, HAL_GPIO_DISABLE);
		_gpio_enable(119, HAL_GPIO_DISABLE);

		/*config pmu gpio pad driving to fix dvbc mosaic issue*/
		reg_adr = 0x1805c0e0;
		reg8_val = 0x55;
		_soc_reg_val_set8(reg_adr, reg8_val);

		reg_adr = 0x1805c0e1;
		reg8_val = 0x55;
		_soc_reg_val_set8(reg_adr, reg8_val);

		reg_adr = 0x1805c0e2;
		reg8_val = 0x55;
		_soc_reg_val_set8(reg_adr, reg8_val);

		
	}

	PRINT_DEBUG("%s --------------------------\n", __FUNCTION__);
}

void gospell_tsi_config()
{

	unsigned int reg_adr;
	unsigned int bits_clear;
	unsigned int bits_set;
	PRINT_DEBUG("%s +++++++++++++++\n", __FUNCTION__);

	/*config pinmux ctrl reg0*/
	reg_adr = PINMUX_CTRL_REG0;
	bits_set = 0;
	bits_clear = 0;

	bits_clear |= (1 << AUD_I2SIO_SEL_BIT);
	bits_clear |= (1 << EMMC_SEL3_BIT);	
	bits_clear |= (1 << XIF_AGC_PDM_SEL_BIT);	
	_soc_reg_bits_set32(reg_adr, bits_clear, bits_set);

	/*config pinmux ctrl reg1*/
	reg_adr = PINMUX_CTRL_REG1;
	bits_set = 0;
	bits_clear = 0;
	bits_set |= (1 << ALISSI4_SEL_BIT);
	bits_clear |= (1 << XSC1_SEL2_BIT);
	bits_clear |= (1 << AUD_I2SIO2_SEL_BIT);
	bits_clear |= (1 << NF_DQS_SEL_BIT);
	bits_clear |= (1 << USB_DEBUG_SEL_BIT);
	_soc_reg_bits_set32(reg_adr, bits_clear, bits_set);


	/*disable GPIO:0,3,10,11,86 for tsi*/

	_gpio_enable(0, HAL_GPIO_DISABLE);
	_gpio_enable(3, HAL_GPIO_DISABLE);
	_gpio_enable(10, HAL_GPIO_DISABLE);
	_gpio_enable(11, HAL_GPIO_DISABLE);
	_gpio_enable(86, HAL_GPIO_DISABLE);

	PRINT_DEBUG("%s --------------------------\n", __FUNCTION__);
}


#ifndef CSTM_CONFIG_KERNEL
void gospell_get_tsi_dmx_config(struct Ali_DmxSrcCtrlStreamParam  *DmxSrcCtrl)
{
	unsigned int board_type = gospell_get_board_type();


	if(DmxSrcCtrl)
	{
#ifdef TS_NOT_LOOP_OUT
		PRINT_DEBUG("TS_NOT_LOOP_OUT\n");
		memset(DmxSrcCtrl, 0, sizeof(struct Ali_DmxSrcCtrlStreamParam));
		DmxSrcCtrl->InPutPortId = 	ALI_DMX_INPUT_PORT_SPI_0;
		DmxSrcCtrl->InputPathId = ALI_DMX_INPUT_PATH_0;
		DmxSrcCtrl->InputPortAttr = 0x83;
		
#else

		memset(DmxSrcCtrl, 0, sizeof(struct Ali_DmxSrcCtrlStreamParam));
		DmxSrcCtrl->InPutPortId = ALI_DMX_INPUT_PORT_SSI_3;
		DmxSrcCtrl->InputPathId = ALI_DMX_INPUT_PATH_0;
		
		if (board_type == BOARD_DVBC)
		{
			DmxSrcCtrl->InputPortAttr = 0x8f;
		}
		else if (board_type == BOARD_DVBS2)
		{
			DmxSrcCtrl->InputPortAttr = 0x8f;
		}
		else if (board_type == BOARD_DTMB)
		{
			DmxSrcCtrl->InputPortAttr = 0x8f;
		}

		else
		{
			DmxSrcCtrl->InputPortAttr = 0x8f;
			PRINT_ERROR("%s  unknown board_type\n", __FUNCTION__);
		}

#endif

	}
}

static void gospell_nim_rest(unsigned int pin)
{
    
    _gpio_enable(pin, HAL_GPIO_ENABLE);
    _gpio_set_dir(pin, HAL_GPIO_O_DIR);
    
    _gpio_set_output(pin, 0);
    delay_ms(100);
    _gpio_set_output(pin, 1);
    delay_ms(20);
    PRINT_DEBUG("%s()%d: nim rest finish!!\n",__FUNCTION__,__LINE__);
}

void gospell_nim_init(void)
{
	unsigned int board_type = gospell_get_board_type();

	if (board_type == BOARD_DVBC)
	{
		PRINT_DEBUG("Select GOSPELL DVBC Nim\n");
		qam_init_tuner(0, 1);

	}
	else if (board_type == BOARD_DVBS2)
	{
        PRINT_DEBUG("Select GOSPELL DVBS2 Nim\n");
        gospell_nim_rest(GPIO_DVBS_NIM_REST);
        nim_init_s2(0);
	}
	else if (board_type == BOARD_DTMB)
	{
        PRINT_DEBUG("Select GOSPELL DTMB Nim\n");
		qam_init_tuner(2, 1);
	}
	else
	{
		PRINT_ERROR("%s  unknown board_type\n", __FUNCTION__);
	}

}

#endif

void change_qam_to_ssi_mode()
{
	unsigned int board_type = gospell_get_board_type();

#ifdef TS_NOT_LOOP_OUT
	PRINT_DEBUG("TS_NOT_LOOP_OUT\n");
	return;
#endif

	if (board_type == BOARD_DVBC)
	{
		/*change qam to ssi mode*/
		unsigned char reg8_val = 0x0;
		unsigned int reg_adr;
		unsigned int bits_clear;
		unsigned int bits_set;

		PRINT_DEBUG("change qam to ssi mode\n");

		reg_adr = 0x18028406;
		bits_set = 0x01;
		bits_clear = 0;
		_soc_reg_bits_set8(reg_adr, bits_clear, bits_set);

		/*Reset qam to active changed*/
		
		reg_adr = 0x18028000;
		reg8_val = 0x80;
		_soc_reg_val_set8(reg_adr, reg8_val);
		reg8_val = 0x60;
		_soc_reg_val_set8(reg_adr, reg8_val);

	}
	
}

#ifdef CSTM_CONFIG_KERNEL

void gospell_board_init()
{

	_gpio_enable(GPIO_FP_CLK, HAL_GPIO_ENABLE);
	_gpio_enable(GPIO_FP_KEY, HAL_GPIO_ENABLE);
	_gpio_enable(GPIO_FP_DATA, HAL_GPIO_ENABLE);
	_gpio_enable(GPIO_USB0_POWER, HAL_GPIO_ENABLE);
	usb_p0_5v_setting(1);

	 g_enet_link_gpio = GPIO_NET_SPEED;
    g_enet_speed_gpio = GPIO_NET_LINK;
    g_snd_mute_gpio = GPIO_MUTE;

    _gpio_enable(g_enet_link_gpio, HAL_GPIO_ENABLE);
    _gpio_set_dir(g_enet_link_gpio, HAL_GPIO_O_DIR);
    _gpio_set_output(g_enet_link_gpio, 1);
    _gpio_enable(g_enet_speed_gpio, HAL_GPIO_ENABLE);
    _gpio_set_dir(g_enet_speed_gpio, HAL_GPIO_O_DIR);
    _gpio_set_output(g_enet_speed_gpio, 1);

	_gpio_enable(UTI_GPIO_DETECT0, HAL_GPIO_ENABLE);
	_gpio_enable(UTI_GPIO_DETECT1, HAL_GPIO_ENABLE);
	_gpio_set_dir(UTI_GPIO_DETECT0, HAL_GPIO_I_DIR);
	_gpio_set_dir(UTI_GPIO_DETECT1, HAL_GPIO_I_DIR);
	gospell_board_detect();



#if 0
	uti_init();
	gospell_board_dectect();
	gospell_tuner_config();
	gospell_tso_config();
	gospell_tsi_config();

#endif

	
}

#else

void gospell_board_init()
{
#if 0
	_gpio_enable(GPIO_FP_CLK, HAL_GPIO_ENABLE);
	_gpio_enable(GPIO_FP_KEY, HAL_GPIO_ENABLE);
	_gpio_enable(GPIO_FP_DATA, HAL_GPIO_ENABLE);
	_gpio_enable(GPIO_USB0_POWER, HAL_GPIO_ENABLE);
#endif

	uti_init();
	gospell_board_detect();
	
	gospell_tuner_config();
	gospell_tso_config();
	gospell_tsi_config();	
	
}

#endif

#else
/*
h_v ==0: V, 13V; ==1: H, 18V
*/
void lnb_set_h_v(char h_v)
{
#if 0
	if(h_v)
		_gpio_set_output(UTI_GPIO_LNB, 1);
	else
		_gpio_set_output(UTI_GPIO_LNB, 0);
#endif
		
}


inline unsigned int gospell_get_board_type()
{
	//return BOARD_DVBC;
	//return BOARD_DTMB;
	return BOARD_DVBC;
}


#endif /*SUPPORT_GOSPELL_BOARD end*/



