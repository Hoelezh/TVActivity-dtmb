/****************************************************************************(I)(S)
 *  (C)
 *  ALi (Shanghai) Corporation. 2010 Copyright (C)
 *  (C)
 *  File: m36_gpio.h
 *  (I)
 *  Description:
 *  (S)
 *  History:(M)
 *      	Date        			Author         	Comment
 *      	====        			======		=======
 * 0.		2010.06.03			Sam			Create

*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version
* 2 of the License, or (at your option) any later version.
*

 ****************************************************************************/
 
#ifndef __M36_GPIO_H
#define __M36_GPIO_H

#include "typedef.h"
#include <asm/errno.h>
#include <linux/ali_reg.h>

#ifdef CONFIG_GPIOLIB

#include <asm-generic/gpio.h>

#define	SYS_GPIO_GET_VAL	1
#define	SYS_GPIO_SET_VAL	2
#define	SYS_GPIO_DIR_IN	3
#define	SYS_GPIO_DIR_OUT	4


//int gpio_to_irq(unsigned gpio);
//int irq_to_gpio(unsigned irq);
void gpio_irq_type(unsigned offset, unsigned trigger);
void gpio_irq_enable(unsigned offset);
void gpio_irq_disable(unsigned offset);
void gpio_irq_clear(unsigned offset);
int gpio_irq_get_status(unsigned offset);

#endif //CONFIG_GPIOLIB


#define GPIO_GROUP_MAX 	 5
#define GPIO_PORT_MAX		169
#define GPIO_CTL_REG        __REGALIRAW(0x18000430)  /* GPIO  */
#define GPIOA_CTL_REG       __REGALIRAW(0x18000434)  /* GPIO2 */
#define GPIOB_CTL_REG       __REGALIRAW(0x18000438)  /* GPIO3 */
#define GPIOC_CTL_REG       __REGALIRAW(0x1800043c)  /* GPIO4 */
#define GPIOD_CTL_REG		__REGALIRAW(0x18000440)	/* GPIO5 */

#define HAL_GPIO_IER_REG    __REGALIRAW(0x18000044)
#define HAL_GPIO_REC_REG    __REGALIRAW(0x18000048)
#define HAL_GPIO_FEC_REG    __REGALIRAW(0x1800004c)
#define HAL_GPIO_ISR_REG    __REGALIRAW(0x1800005c)
#define HAL_GPIO_DIR_REG    __REGALIRAW(0x18000058)
#define HAL_GPIO_DI_REG     __REGALIRAW(0x18000050)
#define HAL_GPIO_DO_REG     __REGALIRAW(0x18000054)

#define HAL_GPIO1_IER_REG	__REGALIRAW(0x180000c4)
#define HAL_GPIO1_REC_REG	__REGALIRAW(0x180000c8)
#define HAL_GPIO1_FEC_REG	__REGALIRAW(0x180000cc)
#define HAL_GPIO1_ISR_REG	__REGALIRAW(0x180000dc)
#define HAL_GPIO1_DIR_REG	__REGALIRAW(0x180000d8)
#define HAL_GPIO1_DI_REG		__REGALIRAW(0x180000d0)
#define HAL_GPIO1_DO_REG	__REGALIRAW(0x180000d4)

#define HAL_GPIO2_IER_REG	__REGALIRAW(0x180000e4)
#define HAL_GPIO2_REC_REG	__REGALIRAW(0x180000e8)
#define HAL_GPIO2_FEC_REG	__REGALIRAW(0x180000ec)
#define HAL_GPIO2_ISR_REG	__REGALIRAW(0x180000fc)
#define HAL_GPIO2_DIR_REG	__REGALIRAW(0x180000f8)
#define HAL_GPIO2_DI_REG	__REGALIRAW(0x180000f0)
#define HAL_GPIO2_DO_REG	__REGALIRAW(0x180000f4)

#define HAL_GPIO3_IER_REG   __REGALIRAW(0x18000344)
#define HAL_GPIO3_REC_REG   __REGALIRAW(0x18000348)
#define HAL_GPIO3_FEC_REG   __REGALIRAW(0x1800034c)
#define HAL_GPIO3_ISR_REG   __REGALIRAW(0x1800035c)
#define HAL_GPIO3_DIR_REG   __REGALIRAW(0x18000358)
#define HAL_GPIO3_DI_REG    __REGALIRAW(0x18000350)
#define HAL_GPIO3_DO_REG    __REGALIRAW(0x18000354)

#define HAL_GPIO4_IER_REG   __REGALIRAW(0x18000444)
#define HAL_GPIO4_REC_REG   __REGALIRAW(0x18000448)
#define HAL_GPIO4_FEC_REG   __REGALIRAW(0x1800044c)
#define HAL_GPIO4_ISR_REG   __REGALIRAW(0x1800045c)
#define HAL_GPIO4_DIR_REG   __REGALIRAW(0x18000458)
#define HAL_GPIO4_DI_REG    __REGALIRAW(0x18000450)
#define HAL_GPIO4_DO_REG    __REGALIRAW(0x18000454)


#define HAL_GPIO_I_DIR      0
#define HAL_GPIO_O_DIR      1
#define HAL_GPIO_INT_EN     0
#define HAL_GPIO_INT_DIS    1
#define HAL_GPIO_EDG_EN     1
#define HAL_GPIO_EDG_DIS    0
#define HAL_GPIO_ENABLE     1
#define HAL_GPIO_DISABLE     0



/* The first set of GPIO */

#define HAL_GPIO_READ()             (*(volatile DWORD *)HAL_GPIO_DI_REG)
#if 1
#define HAL_GPIO_WRITE(val)         (*(volatile DWORD *)HAL_GPIO_DO_REG = (val))
#define HAL_GPIO_DIR_GET()          (*(volatile DWORD *)HAL_GPIO_DIR_REG)
#define HAL_GPIO_DIR_SET(mode)      (*(volatile DWORD *)HAL_GPIO_DIR_REG = (mode))
#define HAL_GPIO_IER_SET(val)       (*(volatile DWORD *)HAL_GPIO_IER_REG = (val))
#define HAL_GPIO_RER_SET(val)       (*(volatile DWORD *)HAL_GPIO_REC_REG = (val))
#define HAL_GPIO_FER_SET(val)       (*(volatile DWORD *)HAL_GPIO_FEC_REG = (val))
#define HAL_GPIO_ISR_GET()          (*(volatile DWORD *)HAL_GPIO_ISR_REG)
#define HAL_GPIO_ISR_SET(val)       (*(volatile DWORD *)HAL_GPIO_ISR_REG = (val))

#define HAL_GPIO1_READ()            (*(volatile DWORD *)HAL_GPIO1_DI_REG)
#define HAL_GPIO1_WRITE(val)        (*(volatile DWORD *)HAL_GPIO1_DO_REG = (val))
#define HAL_GPIO1_DIR_GET()         (*(volatile DWORD *)HAL_GPIO1_DIR_REG)
#define HAL_GPIO1_DIR_SET(mode)     (*(volatile DWORD *)HAL_GPIO1_DIR_REG = (mode))
#define HAL_GPIO1_IER_SET(val)      (*(volatile DWORD *)HAL_GPIO1_IER_REG = (val))
#define HAL_GPIO1_RER_SET(val)      (*(volatile DWORD *)HAL_GPIO1_REC_REG = (val))
#define HAL_GPIO1_FER_SET(val)      (*(volatile DWORD *)HAL_GPIO1_FEC_REG = (val))
#define HAL_GPIO1_ISR_GET()         (*(volatile DWORD *)HAL_GPIO1_ISR_REG)
#define HAL_GPIO1_ISR_SET(val)      (*(volatile DWORD *)HAL_GPIO1_ISR_REG = (val))


#define HAL_GPIO2_READ()            (*(volatile DWORD *)HAL_GPIO2_DI_REG)
#define HAL_GPIO2_WRITE(val)        (*(volatile DWORD *)HAL_GPIO2_DO_REG = (val))
#define HAL_GPIO2_DIR_GET()         (*(volatile DWORD *)HAL_GPIO2_DIR_REG)
#define HAL_GPIO2_DIR_SET(mode)     (*(volatile DWORD *)HAL_GPIO2_DIR_REG = (mode))
#define HAL_GPIO2_IER_SET(val)      (*(volatile DWORD *)HAL_GPIO2_IER_REG = (val))
#define HAL_GPIO2_RER_SET(val)      (*(volatile DWORD *)HAL_GPIO2_REC_REG = (val))
#define HAL_GPIO2_FER_SET(val)      (*(volatile DWORD *)HAL_GPIO2_FEC_REG = (val))
#define HAL_GPIO2_ISR_GET()         (*(volatile DWORD *)HAL_GPIO2_ISR_REG)
#define HAL_GPIO2_ISR_SET(val)      (*(volatile DWORD *)HAL_GPIO2_ISR_REG = (val))

#define HAL_GPIO3_READ()            (*(volatile DWORD *)HAL_GPIO3_DI_REG)
#define HAL_GPIO3_WRITE(val)        (*(volatile DWORD *)HAL_GPIO3_DO_REG = (val))
#define HAL_GPIO3_DIR_GET()         (*(volatile DWORD *)HAL_GPIO3_DIR_REG)
#define HAL_GPIO3_DIR_SET(mode)     (*(volatile DWORD *)HAL_GPIO3_DIR_REG = (mode))
#define HAL_GPIO3_IER_SET(val)      (*(volatile DWORD *)HAL_GPIO3_IER_REG = (val))
#define HAL_GPIO3_RER_SET(val)      (*(volatile DWORD *)HAL_GPIO3_REC_REG = (val))
#define HAL_GPIO3_FER_SET(val)      (*(volatile DWORD *)HAL_GPIO3_FEC_REG = (val))
#define HAL_GPIO3_ISR_GET()         (*(volatile DWORD *)HAL_GPIO3_ISR_REG)
#define HAL_GPIO3_ISR_SET(val)      (*(volatile DWORD *)HAL_GPIO3_ISR_REG = (val))

#define HAL_GPIO4_READ()            (*(volatile DWORD *)HAL_GPIO4_DI_REG)
#define HAL_GPIO4_WRITE(val)        (*(volatile DWORD *)HAL_GPIO4_DO_REG = (val))
#define HAL_GPIO4_DIR_GET()         (*(volatile DWORD *)HAL_GPIO4_DIR_REG)
#define HAL_GPIO4_DIR_SET(mode)     (*(volatile DWORD *)HAL_GPIO4_DIR_REG = (mode))
#define HAL_GPIO4_IER_SET(val)      (*(volatile DWORD *)HAL_GPIO4_IER_REG = (val))
#define HAL_GPIO4_RER_SET(val)      (*(volatile DWORD *)HAL_GPIO4_REC_REG = (val))
#define HAL_GPIO4_FER_SET(val)      (*(volatile DWORD *)HAL_GPIO4_FEC_REG = (val))
#define HAL_GPIO4_ISR_GET()         (*(volatile DWORD *)HAL_GPIO4_ISR_REG)
#define HAL_GPIO4_ISR_SET(val)      (*(volatile DWORD *)HAL_GPIO4_ISR_REG = (val))
#endif
/*  End  */

// get input gpio value
#define HAL_GPIO_BIT_GET(pos)			\
			((pos < 32) ? ((HAL_GPIO_READ() >> (pos)) & 1) \
			: ((pos < 64) ? ((HAL_GPIO1_READ() >> (pos - 32)) & 1) \
			: ((pos < 96) ? ((HAL_GPIO2_READ() >> (pos - 64)) & 1) \
			: ((pos < 128) ? ((HAL_GPIO3_READ() >> (pos - 96)) & 1) \
			: ((HAL_GPIO4_READ() >> (pos - 128)) & 1)))))

#define HAL_GPIO_BIT_DIR_GET(pos)		\
			((pos < 32) ? ((HAL_GPIO_DIR_GET() >> (pos)) & 1) \
			: ((pos < 64) ? ((HAL_GPIO1_DIR_GET() >> (pos - 32)) & 1) \
			: ((pos < 96) ? ((HAL_GPIO2_DIR_GET() >> (pos - 64)) & 1) \
			: ((pos < 128) ? ((HAL_GPIO3_DIR_GET() >> (pos - 96)) & 1) \
			: ((HAL_GPIO4_DIR_GET() >> (pos - 128)) & 1))))

#define HAL_GPIO_BIT_DIR_SET(pos, val)	\
		do { \
			((pos < 32) ? HAL_GPIO_DIR_SET((HAL_GPIO_DIR_GET() & ~(1 << (pos))) | ((val) << (pos))) \
			: ((pos < 64) ? HAL_GPIO1_DIR_SET((HAL_GPIO1_DIR_GET() & ~(1 << (pos - 32))) | ((val) << (pos - 32))) \
			: ((pos < 96) ? HAL_GPIO2_DIR_SET((HAL_GPIO2_DIR_GET() & ~(1 << (pos - 64))) | ((val) << (pos - 64))) \
			: ((pos < 128) ? HAL_GPIO3_DIR_SET((HAL_GPIO3_DIR_GET() & ~(1 << (pos - 96))) | ((val) << (pos - 96))) \
			: HAL_GPIO4_DIR_SET((HAL_GPIO4_DIR_GET() & ~(1 << (pos - 128))) | ((val) << (pos - 128)))))));\
		} while (0)

#define HAL_GPIO_BIT_SET(pos, val)		\
		do { \
			((pos < 32)	? HAL_GPIO_WRITE(((*(volatile DWORD *)HAL_GPIO_DO_REG) & ~(1 << (pos))) | ((val) << (pos))) \
			: ((pos < 64) ? HAL_GPIO1_WRITE(((*(volatile DWORD *)HAL_GPIO1_DO_REG) & ~(1 << (pos - 32))) | ((val) << (pos - 32))) \
			: ((pos < 96) ? HAL_GPIO2_WRITE(((*(volatile DWORD *)HAL_GPIO2_DO_REG) & ~(1 << (pos - 64))) | ((val) << (pos - 64))) \
			: ((pos < 128) ? HAL_GPIO3_WRITE(((*(volatile DWORD *)HAL_GPIO3_DO_REG) & ~(1 << (pos - 96))) | ((val) << (pos - 96))) \
			: HAL_GPIO4_WRITE(((*(volatile DWORD *)HAL_GPIO4_DO_REG) & ~(1 << (pos - 128))) | ((val) << (pos - 128))))))); \
		} while (0)

#define HAL_GPIO_INT_SET(pos, en)		\
		do { \
			((pos < 32)					\
			? HAL_GPIO_IER_SET(((*(volatile DWORD *)HAL_GPIO_IER_REG) & ~(1 << (pos))) | ((en) << (pos))) \
			: ((pos < 64) 				\
			? HAL_GPIO1_IER_SET(((*(volatile DWORD *)HAL_GPIO1_IER_REG) & ~(1 << (pos - 32))) | ((en) << (pos - 32))) \
			: ((pos < 96) 				\
			? HAL_GPIO2_IER_SET(((*(volatile DWORD *)HAL_GPIO2_IER_REG) & ~(1 << (pos - 64))) | ((en) << (pos - 64))) \
			: ((pos < 128) 				\
			? HAL_GPIO3_IER_SET(((*(volatile DWORD *)HAL_GPIO3_IER_REG) & ~(1 << (pos - 96))) | ((en) << (pos - 96))) \
			: HAL_GPIO4_IER_SET(((*(volatile DWORD *)HAL_GPIO4_IER_REG) & ~(1 << (pos - 128))) | ((en) << (pos - 128))))))); \
		} while (0)

#define HAL_GPIO_INT_REDG_SET(pos, rise)	\
		do { \
			((pos < 32)					\
			? HAL_GPIO_RER_SET(((*(volatile DWORD *)HAL_GPIO_REC_REG) & ~(1 << (pos))) | ((rise) << (pos))) \
			: ((pos < 64) 				\
			? HAL_GPIO1_RER_SET(((*(volatile DWORD *)HAL_GPIO1_REC_REG) & ~(1 << (pos - 32))) | ((rise) << (pos - 32))) \
			: ((pos < 96) 				\
			? HAL_GPIO2_RER_SET(((*(volatile DWORD *)HAL_GPIO2_REC_REG) & ~(1 << (pos - 64))) | ((rise) << (pos - 64))) \
			: ((pos < 128) 				\
			? HAL_GPIO3_RER_SET(((*(volatile DWORD *)HAL_GPIO3_REC_REG) & ~(1 << (pos - 96))) | ((rise) << (pos - 96))) \
			: HAL_GPIO4_RER_SET(((*(volatile DWORD *)HAL_GPIO4_REC_REG) & ~(1 << (pos - 128))) | ((rise) << (pos - 128))))))); \
		} while (0)

#define HAL_GPIO_INT_FEDG_SET(pos, fall)	\
		do { \
			((pos < 32)					\
			? HAL_GPIO_FER_SET(((*(volatile DWORD *)HAL_GPIO_FEC_REG) & ~(1 << (pos))) | ((fall) << (pos))) \
			: ((pos < 64)				\
			? HAL_GPIO1_FER_SET(((*(volatile DWORD *)HAL_GPIO1_FEC_REG) & ~(1 << (pos - 32))) | ((fall) << (pos - 32))) \
			: ((pos < 96) 				\
			? HAL_GPIO2_FER_SET(((*(volatile DWORD *)HAL_GPIO2_FEC_REG) & ~(1 << (pos - 64))) | ((fall) << (pos - 64))) \
			: ((pos < 128) 				\
			? HAL_GPIO3_FER_SET(((*(volatile DWORD *)HAL_GPIO3_FEC_REG) & ~(1 << (pos - 96))) | ((fall) << (pos - 96))) \
			: HAL_GPIO4_FER_SET(((*(volatile DWORD *)HAL_GPIO4_FEC_REG) & ~(1 << (pos - 128))) | ((fall) << (pos - 128))))))); \
		} while (0)

#define HAL_GPIO_INT_EDG_SET(pos, rise, fall)	\
		do { \
			((pos < 32)					\
			? (HAL_GPIO_RER_SET(((*(volatile DWORD *)HAL_GPIO_REC_REG) & ~(1 << (pos))) | ((rise) << (pos))), \
			  HAL_GPIO_FER_SET(((*(volatile DWORD *)HAL_GPIO_FEC_REG) & ~(1 << (pos))) | ((fall) << (pos)))) \
			: ((pos < 64)				\
			? (HAL_GPIO1_RER_SET(((*(volatile DWORD *)HAL_GPIO1_REC_REG) & ~(1 << (pos - 32))) | ((rise) << (pos - 32))), \
			  HAL_GPIO1_FER_SET(((*(volatile DWORD *)HAL_GPIO1_FEC_REG) & ~(1 << (pos - 32))) | ((fall) << (pos - 32)))) \
			: ((pos < 96)				\
			?  (HAL_GPIO2_RER_SET(((*(volatile DWORD *)HAL_GPIO2_REC_REG) & ~(1 << (pos - 64))) | ((rise) << (pos - 64))), \
			  HAL_GPIO2_FER_SET(((*(volatile DWORD *)HAL_GPIO2_FEC_REG) & ~(1 << (pos - 64))) | ((fall) << (pos - 64)))) \
			  : ((pos < 128)				\
			?  (HAL_GPIO3_RER_SET(((*(volatile DWORD *)HAL_GPIO3_REC_REG) & ~(1 << (pos - 96))) | ((rise) << (pos - 96))), \
			  HAL_GPIO3_FER_SET(((*(volatile DWORD *)HAL_GPIO3_FEC_REG) & ~(1 << (pos - 96))) | ((fall) << (pos - 96)))) \
			:  (HAL_GPIO4_RER_SET(((*(volatile DWORD *)HAL_GPIO4_REC_REG) & ~(1 << (pos - 128))) | ((rise) << (pos - 128))), \
			  HAL_GPIO4_FER_SET(((*(volatile DWORD *)HAL_GPIO4_FEC_REG) & ~(1 << (pos - 128))) | ((fall) << (pos - 128)))))))); \
		} while (0)

#define HAL_GPIO_INT_STA_GET(pos)		\
			((pos < 32) ? ((HAL_GPIO_ISR_GET() >> (pos)) & 1) \
			: ((pos < 64) ? ((HAL_GPIO1_ISR_GET() >> (pos - 32)) & 1) \
			: ((pos < 96) ? ((HAL_GPIO2_ISR_GET() >> (pos - 64)) & 1) \
			: ((pos < 128) ? ((HAL_GPIO3_ISR_GET() >> (pos - 96)) & 1) \
			: ((HAL_GPIO4_ISR_GET() >> (pos - 128)) & 1)))))

#define HAL_GPIO_INT_CLEAR(pos)		\
			((pos < 32) ? (HAL_GPIO_ISR_SET(1 << (pos))) \
			: ((pos < 64) ? (HAL_GPIO1_ISR_SET(1 << (pos-32))) \
			: ((pos < 96) ? (HAL_GPIO2_ISR_SET(1 << (pos-64))) \
			: ((pos < 128) ? (HAL_GPIO2_ISR_SET(1 << (pos-96))) \
			: (HAL_GPIO4_ISR_SET(1 << (pos-128)))))))


/*add by martin.zhu 2011-06-29 */
/*Some pinmux pin default value is 0, some is 1, define the  enable value .
  Use to enable other Function ( GPIO)
*/
#define HAL_PINMUX_DEFALT_VALUE        0x4E461CD3
#define HAL_PINMUX1_DEFALT_VALUE       0x100793C8

#define HAL_PINMUX_CTRL_REG            __REGALIRAW(0x18000088)
#define HAL_PINMUX_CTRL1_REG           __REGALIRAW(0x1800008c)
// PINMUX REG4 is revert

#define HAL_PINMUX_SET(val)           (*(volatile DWORD *)HAL_PINMUX_CTRL_REG = (val))
#define HAL_PINMUX1_SET(val)          (*(volatile DWORD *)HAL_PINMUX_CTRL1_REG = (val))

#define GET_PINMAX_BIT(val, pos)      (((val >> (pos)) & 1) << pos)
#define GET_BYTE(addr)            		 (*(volatile unsigned char *)(addr))
#define SET_BITE(addr, pos, val)       *(volatile unsigned long *)(addr) = (((*(volatile DWORD *)addr) & ~(1 << (pos))) | ((val) << (pos)))
#define WRITE_DATA_OR(add, val)        *(volatile unsigned long *)(add) |= (unsigned long)(val)
#define WRITE_DATA_AND(add, val)       *(volatile unsigned long *)(add) &= (unsigned long)(val)
#define WRITE_DATA_EQUAL(addr, val)    *(volatile unsigned long *)(addr)= (unsigned long)(val)


#define HAL_PINMUX_GPIO_ENABLE(pos)       \
    do { \
        ((pos < 32)                 \
        ? HAL_PINMUX_SET(((*(volatile DWORD *)HAL_PINMUX_CTRL_REG) & ~(1 << (pos))) | (GET_PINMAX_BIT(HAL_PINMUX_DEFALT_VALUE , pos) )) \
        : ((pos < 64)               \
        ? HAL_PINMUX1_SET(((*(volatile DWORD *)HAL_PINMUX_CTRL1_REG) & ~(1 << (pos - 32))) | (GET_PINMAX_BIT(HAL_PINMUX1_DEFALT_VALUE , pos))) \
        : 1) );\
    } while (0)

#define HAL_GPIO_CTL_SET(val)       (*(volatile DWORD *)GPIO_CTL_REG = (val))
#define HAL_GPIOA_CTL_SET(val)       (*(volatile DWORD *)GPIOA_CTL_REG = (val))
#define HAL_GPIOB_CTL_SET(val)       (*(volatile DWORD *)GPIOB_CTL_REG = (val))
#define HAL_GPIOC_CTL_SET(val)       (*(volatile DWORD *)GPIOC_CTL_REG = (val))
#define HAL_GPIOD_CTL_SET(val)       (*(volatile DWORD *)GPIOD_CTL_REG = (val))

//enable/disable  GPIO function
#define HAL_GPIO_FUNC_ENABLE(pos, en)       \
        do { \
            ((pos < 32)                 \
            ? HAL_GPIO_CTL_SET(((*(volatile DWORD *)GPIO_CTL_REG) &~(1<<(pos))) | (en << (pos))) \
            : ((pos < 64)               \
            ? HAL_GPIOA_CTL_SET(((*(volatile DWORD *)GPIOA_CTL_REG) &~(1<<(pos - 32)))  | (en << (pos - 32))) \
            : ((pos < 96)               \
            ? HAL_GPIOB_CTL_SET(((*(volatile DWORD *)GPIOB_CTL_REG) &~(1<<(pos - 64))) | (en << (pos - 64))) \
             : ((pos < 128)               \
            ? HAL_GPIOC_CTL_SET(((*(volatile DWORD *)GPIOC_CTL_REG) &~(1<<(pos - 96)))  | (en << (pos - 96))) \
		: HAL_GPIOD_CTL_SET(((*(volatile DWORD *)GPIOD_CTL_REG) &~(1<<(pos - 128))) | (en << (pos - 128))))))); \
		} while (0)
        

#define HAL_GPIO_POINT_INT_CLEAR(pos)		\
			((pos < 32) ? (HAL_GPIO_ISR_SET(HAL_GPIO_ISR_GET())) \
			: ((pos < 64) ? (HAL_GPIO1_ISR_SET(HAL_GPIO1_ISR_GET())) \
			: ((pos < 96) ? (HAL_GPIO2_ISR_SET(HAL_GPIO2_ISR_GET())) \
			: ((pos < 128) ? (HAL_GPIO2_ISR_SET(HAL_GPIO3_ISR_GET())) \
			: (HAL_GPIO4_ISR_SET(HAL_GPIO4_ISR_GET()))))))		



#ifndef CONFIG_GPIOLIB
#define ARCH_NR_GPIOS 128

static inline int gpio_is_valid(int gpio)
{
    return (gpio) < ARCH_NR_GPIOS;
}
#endif

static inline int gpio_enable_pin(int number)
{
    if( !gpio_is_valid(number))
        return -1;
//    HAL_PINMUX_GPIO_ENABLE(number);
	HAL_GPIO_FUNC_ENABLE(number, HAL_GPIO_ENABLE);
	return 0;
}

static inline int gpio_disable_pin(int number)
{
    if( !gpio_is_valid(number))
        return -1;
//    HAL_PINMUX_GPIO_ENABLE(number);
	HAL_GPIO_FUNC_ENABLE(number, HAL_GPIO_DISABLE);
	return 0;
}


static inline int enable_gpio_interrupt_pin(int number)
{
    if( !gpio_is_valid(number))
        return -1;
    HAL_GPIO_INT_SET(number, 1);
	return 0;
}		

static inline int disable_gpio_interrupt_pin(int number)
{
    if( !gpio_is_valid(number))
        return -1;
    HAL_GPIO_INT_SET(number, 0);
	return 0;
}	

//set gpio interrupt as rising edge
static inline int set_gpio_rising_ir_pin(int number, int val)
{
    if( !gpio_is_valid(number))
        return -1;
    HAL_GPIO_INT_REDG_SET(number, val);
	return 0;
}	

//set gpio interrupt as falling edge
static inline int set_gpio_falling_ir_pin(int number, int val)
{
    if( !gpio_is_valid(number))
        return -1;
    HAL_GPIO_INT_FEDG_SET(number, val);
	return 0;
}	

//clear interrupt status
static inline int clear_gpio_interrupt_status(int number)
{
    if( !gpio_is_valid(number))
        return -1;
    HAL_GPIO_INT_CLEAR(number);
	return 0;
}

static inline int clear_gpio_point_isr(int number)
{
    if( !gpio_is_valid(number))
        return -1;
    return HAL_GPIO_POINT_INT_CLEAR(number);
}

//get interrupt status
static inline int get_gpio_interrupt_status(int number)
{
    if( !gpio_is_valid(number))
        return -1;
    return HAL_GPIO_INT_STA_GET(number);
}

static inline int gpio_set_output(unsigned char gpio)
{
    if( !gpio_is_valid(gpio))
		return -1;

    HAL_GPIO_BIT_DIR_SET(gpio, HAL_GPIO_O_DIR);
    return 0;
}


/*  End  martin.zhu 2011-06-29  */
static inline int ali_gpio_direction_input(unsigned char gpio)
{
    if( !gpio_is_valid(gpio))
		return -1;

	/* fix IC bug */
	if ((68 == gpio) || (69 == gpio) || (70 == gpio) || (145 == gpio) || (146 == gpio))
	{
		HAL_GPIO_BIT_DIR_SET(gpio, HAL_GPIO_O_DIR);
	}
	else
	{
		HAL_GPIO_BIT_DIR_SET(gpio, HAL_GPIO_I_DIR);
	}
    
    return 0;
}


static inline int ali_gpio_direction_output(unsigned char gpio, int value)
{
    if( !gpio_is_valid(gpio))
		return -1;

	/* fix IC bug */
	if ((68 == gpio) || (69 == gpio) || (70 == gpio) || (145 == gpio) || (146 == gpio))
	{
		HAL_GPIO_BIT_DIR_SET(gpio, HAL_GPIO_I_DIR);
	}
	else
	{
		HAL_GPIO_BIT_DIR_SET(gpio, HAL_GPIO_O_DIR);
	}
    
    HAL_GPIO_BIT_SET(gpio, (value)? 1 : 0);
    return 0;
}


static inline int ali_gpio_get_value(unsigned char gpio)
{	
	
    	if( !gpio_is_valid(gpio))
		return -1;

	/* fix IC bug */
	if ((68 == gpio) || (69 == gpio) || (70 == gpio) || (145 == gpio) || (146 == gpio))
	{
		HAL_GPIO_BIT_DIR_SET(gpio, HAL_GPIO_O_DIR);
	}
	else
	{
		HAL_GPIO_BIT_DIR_SET(gpio, HAL_GPIO_I_DIR);
	}
	
    
    	/* GPIO can never have been requested or set as {in,out}put */
    	return HAL_GPIO_BIT_GET(gpio);
}


static  inline int ali_gpio_set_value(unsigned char gpio, int value)
{	
    	if( !gpio_is_valid(gpio))
		return -1;

	/* fix IC bug */
	if ((68 == gpio) || (69 == gpio) || (70 == gpio) || (145 == gpio) || (146 == gpio))
	{
		HAL_GPIO_BIT_DIR_SET(gpio, HAL_GPIO_I_DIR);
	}
	else
	{
		HAL_GPIO_BIT_DIR_SET(gpio, HAL_GPIO_O_DIR);
	}
    	
    	/* GPIO can never have been requested or set as output */
    	HAL_GPIO_BIT_SET(gpio, (value)? 1 : 0);    

	 return 0;
}


#ifndef CONFIG_GPIOLIB
static inline int gpio_request(unsigned gpio, const char *label)
{
    printk(KERN_ALERT "gpio_request: GPIO number(%d), label %s\n", gpio, label);
    return 0;
}

static inline void gpio_free(unsigned gpio)
{

}
#endif


#endif /* __M36_GPIO_H */

