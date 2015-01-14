/****************************************************************************(I)(S)
 *  (C)
 *  ALi (Shanghai) Corporation. 2010 Copyright (C)
 *  (C)
 *  File: m36_irq.h
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
 
#ifndef __M36_IRQ_H
#define __M36_IRQ_H

/* decide the irq block assignment */
#define	M36_NUM_CPU_IRQ	8
#ifdef	CONFIG_M6304
#define	M36_NUM_SYS_IRQ	20
#define	M36_NUM_GPIO_IRQ	20
#elif	defined CONFIG_M6303
#define	M36_NUM_SYS_IRQ	64	/* Now Total 34 */
#define	M36_NUM_GPIO_IRQ	32
#endif

#define	M36_IRQ_BASE		0

#define	M36_CPU_IRQ_BASE	M36_IRQ_BASE
#define	M36_SYS_IRQ_BASE	(M36_CPU_IRQ_BASE + M36_NUM_CPU_IRQ)
#define	M36_GPIO_IRQ_BASE	(M36_SYS_IRQ_BASE + M36_NUM_SYS_IRQ)

/* CPU interrupts */

/* 
   IP0 - Software interrupt 
   IP1 - Software interrupt 
   IP2 - All but battery, high speed modem, and real time clock 
   IP3 - RTC Long1 (system timer) 
   IP4 - RTC Long2 
   IP5 - High Speed Modem (unused on M3602) 
   IP6 - Unused 
   IP7 - Timer interrupt from CPO_COMPARE 
*/

#define M36_IRQ_SW1       (M36_CPU_IRQ_BASE + 0)  
#define M36_IRQ_SW2       (M36_CPU_IRQ_BASE + 1)  
#define M36_IRQ_INT0      (M36_CPU_IRQ_BASE + 2)
#define M36_IRQ_INT1      (M36_CPU_IRQ_BASE + 3)
#define M36_IRQ_INT2      (M36_CPU_IRQ_BASE + 4)
#define M36_IRQ_INT3      (M36_CPU_IRQ_BASE + 5)
#define M36_IRQ_INT4      (M36_CPU_IRQ_BASE + 6)
#define M36_IRQ_TIMER     (M36_CPU_IRQ_BASE + 7)


/* Cascaded from M36_IRQ_INT0 (ICU mapped interrupts) */

/* 
   IP3 - same as M36_IRQ_INT1
   IP8 - This is a cascade to GPIO IRQ's. Do not use.
   IP16 - same as M36_IRQ_INT2
   IP18 - CompactFlash
*/

#define M36_IRQ_SYSGPIO   (M36_SYS_IRQ_BASE + 0)
#define M36_IRQ_VE     (M36_SYS_IRQ_BASE + 1)
#define M36_IRQ_DE     (M36_SYS_IRQ_BASE + 2)
#define M36_IRQ_TS    (M36_SYS_IRQ_BASE + 3)
#define M36_IRQ_GE     (M36_SYS_IRQ_BASE + 4)
#define M36_IRQ_AUDIO       (M36_SYS_IRQ_BASE + 5)
#define M36_IRQ_TSG       (M36_SYS_IRQ_BASE + 6)
#define M36_IRQ_DMX1       (M36_SYS_IRQ_BASE + 7)
#define M36_IRQ_DMX2       (M36_SYS_IRQ_BASE + 8)
#define M36_IRQ_CI       (M36_SYS_IRQ_BASE + 9)
#define M36_IRQ_ATA     (M36_SYS_IRQ_BASE + 10)
#define M36_IRQ_PCI      (M36_SYS_IRQ_BASE + 11)
#define M36_IRQ_SG     (M36_SYS_IRQ_BASE + 12)
#define M36_IRQ_HDMI   (M36_SYS_IRQ_BASE + 13)
#define M36_IRQ_EXT     (M36_SYS_IRQ_BASE + 14)
#define M36_IRQ_DEO     (M36_SYS_IRQ_BASE + 15)
#define M36_IRQ_UART1     (M36_SYS_IRQ_BASE + 16)
#define M36_IRQ_UART2       (M36_SYS_IRQ_BASE + 17)
#define M36_IRQ_SCB       (M36_SYS_IRQ_BASE + 18)
#define M36_IRQ_IR       (M36_SYS_IRQ_BASE + 19)
#define M36_IRQ_SCR1       (M36_SYS_IRQ_BASE + 20)
#define M36_IRQ_SCR2       (M36_SYS_IRQ_BASE + 21)
#define M36_IRQ_RTC       (M36_SYS_IRQ_BASE + 22)
#define M36_IRQ_WDT     (M36_SYS_IRQ_BASE + 23)
#define M36_IRQ_IRTX     (M36_SYS_IRQ_BASE + 24)
#define M36_IRQ_SCB2     (M36_SYS_IRQ_BASE + 25)
#define M36_IRQ_SCB3     (M36_SYS_IRQ_BASE + 26)
#define M36_IRQ_DRAM     (M36_SYS_IRQ_BASE + 27)
#define M36_IRQ_PANEL     (M36_SYS_IRQ_BASE + 28)
#define M36_IRQ_USB     (M36_SYS_IRQ_BASE + 29)
#define M36_IRQ_CPUILB     (M36_SYS_IRQ_BASE + 30)
#define M36_IRQ_BUSSERR     (M36_SYS_IRQ_BASE + 31)
#define M36_IRQ_CI2     (M36_SYS_IRQ_BASE + 32)
#define M36_IRQ_VIN     (M36_SYS_IRQ_BASE + 33)

/* Cascaded from M36_IRQ_GIU */
#define M36_IRQ_GPIO0     (M36_GPIO_IRQ_BASE + 0)
#define M36_IRQ_GPIO1     (M36_GPIO_IRQ_BASE + 1)
#define M36_IRQ_GPIO2     (M36_GPIO_IRQ_BASE + 2)
#define M36_IRQ_GPIO3     (M36_GPIO_IRQ_BASE + 3)
#define M36_IRQ_GPIO4     (M36_GPIO_IRQ_BASE + 4)
#define M36_IRQ_GPIO5     (M36_GPIO_IRQ_BASE + 5)
#define M36_IRQ_GPIO6     (M36_GPIO_IRQ_BASE + 6)
#define M36_IRQ_GPIO7     (M36_GPIO_IRQ_BASE + 7)
#define M36_IRQ_GPIO8     (M36_GPIO_IRQ_BASE + 8)
#define M36_IRQ_GPIO9     (M36_GPIO_IRQ_BASE + 9)
#define M36_IRQ_GPIO10    (M36_GPIO_IRQ_BASE + 10)
#define M36_IRQ_GPIO11    (M36_GPIO_IRQ_BASE + 11)
#define M36_IRQ_GPIO12    (M36_GPIO_IRQ_BASE + 12)
#define M36_IRQ_GPIO13    (M36_GPIO_IRQ_BASE + 13)
#define M36_IRQ_GPIO14    (M36_GPIO_IRQ_BASE + 14)
#define M36_IRQ_GPIO15    (M36_GPIO_IRQ_BASE + 15)
#define M36_IRQ_GPIO16     (M36_GPIO_IRQ_BASE + 16)
#define M36_IRQ_GPIO17     (M36_GPIO_IRQ_BASE + 17)
#define M36_IRQ_GPIO18     (M36_GPIO_IRQ_BASE + 18)
#define M36_IRQ_GPIO19     (M36_GPIO_IRQ_BASE + 19)
#define M36_IRQ_GPIO20    (M36_GPIO_IRQ_BASE + 20)
#define M36_IRQ_GPIO21    (M36_GPIO_IRQ_BASE + 21)
#define M36_IRQ_GPIO22    (M36_GPIO_IRQ_BASE + 22)
#define M36_IRQ_GPIO23    (M36_GPIO_IRQ_BASE + 23)
#define M36_IRQ_GPIO24    (M36_GPIO_IRQ_BASE + 24)
#define M36_IRQ_GPIO25    (M36_GPIO_IRQ_BASE + 25)
#define M36_IRQ_GPIO26     (M36_GPIO_IRQ_BASE + 26)
#define M36_IRQ_GPIO27     (M36_GPIO_IRQ_BASE + 27)
#define M36_IRQ_GPIO28     (M36_GPIO_IRQ_BASE + 28)
#define M36_IRQ_GPIO29     (M36_GPIO_IRQ_BASE + 29)
#define M36_IRQ_GPIO30    (M36_GPIO_IRQ_BASE + 30)
#define M36_IRQ_GPIO31    (M36_GPIO_IRQ_BASE + 31)

// Alternative to above GPIO IRQ defines
#define M36_IRQ_GPIO(pin) ((M36_IRQ_GPIO0) + (pin))

#define M36_IRQ_MAX       (M36_IRQ_BASE + M36_NUM_CPU_IRQ + \
                              M36_NUM_SYS_IRQ)
#endif

