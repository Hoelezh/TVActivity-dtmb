/****************************************************************************(I)(S)
 *  (C)
 *  ALi (Shanghai) Corporation. 2010 Copyright (C)
 *  (C)
 *  File: m6303.h
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
 
#ifndef __M6303_H
#define __M6303_H

#define CONFIG_M6303

//#include <asm/addrspace.h>
#include <asm/mach-ali/m36_irq.h>

#define M6303_EXTERNAL_IO_BZSE		0x18000000
#define M6303_EXTERNAL_IO_SIZE		0x00004000

#define M6303_INTERNAL_IO_BASE		0x18000000
#define M6303_INTERNAL_IO_SIZE		0x18000000

#define M630X_IDE_IO_BASE		0x18008000
#define M630X_IDE_IO_SIZE		0x00000fff

#define M6303_PCI_MEM_BASE		0x30000000
#define M6303_PCI_MEM_SIZE		0x0fffffff

//#define M6303_PCI_IO_BASE		0x10000000
//#define M6303_PCI_IO_SIZE		0x003fffff
#define M6303_PCI_IO_BASE		0x1000
#define M6303_PCI_IO_SIZE		0xffff

#define M6303_ROM_BASE			0x1fc00000
#define M6303_ROM_SIZE			0x00200000
#define M6303_LOCAL_IO_PORT_BASE	0x18000000
#define M6303_IO_PORT_BASE		KSEG1ADDR(M6303_LOCAL_IO_PORT_BASE)

#ifndef __ASSEMBLY__
#define __preg8		(volatile unsigned char*)
#define __preg16	(volatile unsigned short*)
#define __preg32	(volatile unsigned int*)
#else
#define __preg8
#define __preg16
#define __preg32
#endif

// Embedded CPU peripheral registers
// Note that many of the registers have different physical address for M6303

// Bus Control Unit (BCU)
#define M6303_BCUCNTREG1	__preg16(KSEG1 + 0x18000000)	/* BCU control register 1 (R/W) */
#define M6303_CMUCLKMSK	__preg16(KSEG1 + 0x18000004)	/* Clock mask register (R/W) */
#define M6303_CMUCLKMSK_MSKCSUPCLK  0x0040
#define M6303_CMUCLKMSK_MSKAIUPCLK  0x0020
#define M6303_CMUCLKMSK_MSKPIUPCLK  0x0010
#define M6303_CMUCLKMSK_MSKADUPCLK  0x0008
#define M6303_CMUCLKMSK_MSKSIU18M   0x0004
#define M6303_CMUCLKMSK_MSKADU18M   0x0002
#define M6303_CMUCLKMSK_MSKUSB      0x0001
#define M6303_CMUCLKMSK_MSKSIU      M6303_CMUCLKMSK_MSKSIU18M
#define M6303_BCUSPEEDREG	__preg16(KSEG1 + 0x1800000C)	/* BCU access time parameter (R/W) */
#define M6303_BCURFCNTREG	__preg16(KSEG1 + 0x18000010)	/* BCU refresh control register (R/W) */
#define M6303_REVIDREG		__preg16(KSEG1 + 0x18000014)	/* Revision ID register (R) */
#define M6303_CLKSPEEDREG	__preg16(KSEG1 + 0x18000018)	/* Clock speed register (R) */
#define M6303_EDOMCYTREG	__preg16(KSEG1 + 0x18000300)	/* Memory cycle timing register (R/W) */
#define M6303_MEMCFG_REG	__preg16(KSEG1 + 0x18000304)	/* Memory configuration register (R/W) */
#define M6303_MODE_REG		__preg16(KSEG1 + 0x18000308)	/* SDRAM mode register (R/W) */
#define M6303_SDTIMINGREG	__preg16(KSEG1 + 0x1800030C)	/* SDRAM timing register (R/W) */

// DMA Control Unit (DCU)
#define M6303_MICDEST1REG1	__preg16(KSEG1 + 0x18000020)	/* Microphone destination 1 address register 1 (R/W) */
#define M6303_MICDEST1REG2	__preg16(KSEG1 + 0x18000022)	/* Microphone destination 1 address register 2 (R/W) */
#define M6303_MICDEST2REG1	__preg16(KSEG1 + 0x18000024)	/* Microphone destination 2 address register 1 (R/W) */
#define M6303_MICDEST2REG2	__preg16(KSEG1 + 0x18000026)	/* Microphone destination 2 address register 2 (R/W) */
#define M6303_SPKRRC1REG1	__preg16(KSEG1 + 0x18000028)	/* Speaker Source 1 address register 1 (R/W) */
#define M6303_SPKRRC1REG2	__preg16(KSEG1 + 0x1800002A)	/* Speaker Source 1 address register 2 (R/W) */
#define M6303_SPKRRC2REG1	__preg16(KSEG1 + 0x1800002C)	/* Speaker Source 2 address register 1 (R/W) */
#define M6303_SPKRRC2REG2	__preg16(KSEG1 + 0x1800002E)	/* Speaker Source 2 address register 2 (R/W) */
#define M6303_DMARSTREG	__preg16(KSEG1 + 0x18000040)	/* DMA Reset register (R/W) */
#define M6303_AIUDMAMSKREG	__preg16(KSEG1 + 0x18000046)	/* Audio DMA mask register (R/W) */
#define M6303_USBDMAMSKREG	__preg16(KSEG1 + 0x18000600)	/* USB DMA Mask register (R/W) */
#define M6303_USBRXS1AREG1	__preg16(KSEG1 + 0x18000602)	/* USB Rx source 1 address register 1 (R/W) */
#define M6303_USBRXS1AREG2	__preg16(KSEG1 + 0x18000604)	/* USB Rx source 1 address register 2 (R/W) */
#define M6303_USBRXS2AREG1	__preg16(KSEG1 + 0x18000606)	/* USB Rx source 2 address register 1 (R/W) */
#define M6303_USBRXS2AREG2	__preg16(KSEG1 + 0x18000608)	/* USB Rx source 2 address register 2 (R/W) */
#define M6303_USBTXS1AREG1	__preg16(KSEG1 + 0x1800060A)	/* USB Tx source 1 address register 1 (R/W) */
#define M6303_USBTXS1AREG2	__preg16(KSEG1 + 0x1800060C)	/* USB Tx source 1 address register 2 (R/W) */
#define M6303_USBTXS2AREG1	__preg16(KSEG1 + 0x1800060E)	/* USB Tx source 2 address register 1 (R/W) */
#define M6303_USBTXS2AREG2	__preg16(KSEG1 + 0x18000610)	/* USB Tx source 2 address register 2 (R/W) */
#define M6303_USBRXD1AREG1	__preg16(KSEG1 + 0x1800062A)	/* USB Rx destination 1 address register 1 (R/W) */
#define M6303_USBRXD1AREG2	__preg16(KSEG1 + 0x1800062C)	/* USB Rx destination 1 address register 2 (R/W) */
#define M6303_USBRXD2AREG1	__preg16(KSEG1 + 0x1800062E)	/* USB Rx destination 2 address register 1 (R/W) */
#define M6303_USBRXD2AREG2	__preg16(KSEG1 + 0x18000630)	/* USB Rx destination 2 address register 2 (R/W) */
#define M6303_USBTXD1AREG1	__preg16(KSEG1 + 0x18000632)	/* USB Tx destination 1 address register 1 (R/W) */
#define M6303_USBTXD1AREG2	__preg16(KSEG1 + 0x18000634)	/* USB Tx destination 1 address register 2 (R/W) */
#define M6303_USBTXD2AREG1	__preg16(KSEG1 + 0x18000636)	/* USB Tx destination 2 address register 1 (R/W) */
#define M6303_USBTXD2AREG2	__preg16(KSEG1 + 0x18000638)	/* USB Tx destination 2 address register 2 (R/W) */
#define M6303_RxRCLENREG	__preg16(KSEG1 + 0x18000652)	/* USB Rx record length register (R/W) */
#define M6303_TxRCLENREG	__preg16(KSEG1 + 0x18000654)	/* USB Tx record length register (R/W) */
#define M6303_MICRCLENREG	__preg16(KSEG1 + 0x18000658)	/* Microphone record length register (R/W) */
#define M6303_SPKRCLENREG	__preg16(KSEG1 + 0x1800065A)	/* Speaker record length register (R/W) */
#define M6303_USBCFGREG	__preg16(KSEG1 + 0x1800065C)	/* USB configuration register (R/W) */
#define M6303_MICDMACFGREG	__preg16(KSEG1 + 0x1800065E)	/* Microphone DMA configuration register (R/W) */
#define M6303_SPKDMACFGREG	__preg16(KSEG1 + 0x18000660)	/* Speaker DMA configuration register (R/W) */
#define M6303_DMAITRQREG	__preg16(KSEG1 + 0x18000662)	/* DMA interrupt request register (R/W) */
#define M6303_DMACLTREG	__preg16(KSEG1 + 0x18000664)	/* DMA control register (R/W) */
#define M6303_DMAITMKREG	__preg16(KSEG1 + 0x18000666)	/* DMA interrupt mask register (R/W) */

// ISA Bridge
#define M6303_ISABRGCTL	__preg16(KSEG1 + 0x180002C0)	/* ISA Bridge Control Register (R/W) */
#define M6303_ISABRGSTS	__preg16(KSEG1 + 0x180002C2)	/* ISA Bridge Status Register (R/W) */
#define M6303_XISACTL		__preg16(KSEG1 + 0x180002C4)	/* External ISA Control Register (R/W) */

// Clocked Serial Interface (CSI)
#define M6303_CSIMODE		__preg16(KSEG1 + 0x18000900)	/* CSI Mode Register (R/W) */
#define M6303_CSIRXDATA	__preg16(KSEG1 + 0x18000902)	/* CSI Receive Data Register (R) */
#define M6303_CSITXDATA	__preg16(KSEG1 + 0x18000904)	/* CSI Transmit Data Register (R/W) */
#define M6303_CSILSTAT		__preg16(KSEG1 + 0x18000906)	/* CSI Line Status Register (R/W) */
#define M6303_CSIINTMSK	__preg16(KSEG1 + 0x18000908)	/* CSI Interrupt Mask Register (R/W) */
#define M6303_CSIINTSTAT	__preg16(KSEG1 + 0x1800090a)	/* CSI Interrupt Status Register (R/W) */
#define M6303_CSITXBLEN	__preg16(KSEG1 + 0x1800090c)	/* CSI Transmit Burst Length Register (R/W) */
#define M6303_CSIRXBLEN	__preg16(KSEG1 + 0x1800090e)	/* CSI Receive Burst Length Register (R/W) */

// Interrupt Control Unit (ICU)
#define M6303_SYSINT1REG	__preg16(KSEG1 + 0x1800003a)	/* Level 1 System interrupt register 1 (R) */
#define M6304_SYSINT1REG	__preg16(KSEG1 + 0x18000038)	/* Level 1 System interrupt register 1 (R) */
#define M6303_MSYSINT1REG	__preg16(KSEG1 + 0x1800003C)	/* Level 1 mask system interrupt register 1 (R/W) */
#define M6303_NMIREG		__preg16(KSEG1 + 0x18000098)	/* NMI register (R/W) */
#define M6303_SOFTINTREG	__preg16(KSEG1 + 0x1800009A)	/* Software interrupt register (R/W) */
#define M6303_SYSINT2REG	__preg16(KSEG1 + 0x18000200)	/* Level 1 System interrupSt register 2 (R) */
#define M6303_MSYSINT2REG	__preg16(KSEG1 + 0x18000206)	/* Level 1 mask system interrupt register 2 (R/W) */
#define M6303_PIUINTREGro	__preg16(KSEG1 + 0x18000082)	/* Level 2 PIU interrupt register (R) */
#define M6303_AIUINTREG	__preg16(KSEG1 + 0x18000084)	/* Level 2 AIU interrupt register (R) */
#define M6303_MPIUINTREG	__preg16(KSEG1 + 0x1800008E)	/* Level 2 mask PIU interrupt register (R/W) */
#define M6303_MAIUINTREG	__preg16(KSEG1 + 0x18000090)	/* Level 2 mask AIU interrupt register (R/W) */
#define M6303_MKIUINTREG	__preg16(KSEG1 + 0x18000092)	/* Level 2 mask KIU interrupt register (R/W) */
#define M6303_KIUINTREG	__preg16(KSEG1 + 0x18000198)	/* Level 2 KIU interrupt register (R) */

#define M6303_IRQ_PCIA	    8
#define M6303_IRQ_PCIB      9
#define M6303_IRQ_RTCL1     10  /* Use M6303_IRQ_INT1 instead. */
#define M6303_IRQ_ETIMER    11
#define M6303_IRQ_RFU12     12
#define M6304_IRQ_USB	    16
#define M6303_IRQ_USB       13
#define M6304_IRQ_IDE	    27
#define M6303_IRQ_RFU14     14
#define M6303_IRQ_RFU15     15
#define M6303_IRQ_GIU       16  /* This is a cascade to IRQs 40-71. Do not use. */
#define M6303_IRQ_SIU       17
#define M6303_IRQ_WRBERR    18
#define M6303_IRQ_SOFT      19
#define M6303_IRQ_RFU20     20
#define M6303_IRQ_DOZEPIU   21
#define M6303_IRQ_RFU22     22
#define M6303_IRQ_RFU23     23
#define M6303_IRQ_RTCL2     24  /* Use M6303_IRQ_INT2 instead. */
#define M6303_IRQ_LED       25
#define M6303_IRQ_HSP       26  /* Use M6303_IRQ_INT3 instead. */
#define M6303_IRQ_TCLK      27
#define M6303_IRQ_FIR       28
#define M6303_IRQ_DSIU      29
#define M6303_IRQ_PCIU      30
#define M6303_IRQ_RFU31     31
#define M6303_IRQ_RFU32     32
#define M6303_IRQ_RFU33     33
#define M6303_IRQ_RFU34     34
#define M6303_IRQ_RFU35     35
#define M6303_IRQ_RFU36     36
#define M6303_IRQ_RFU37     37
#define M6303_IRQ_RFU38     38
#define M6303_IRQ_RFU39     39
#define ALI_IRQ_USB_EHCI     (36+8)
#define ALI_IRQ_USB_OHCI     (50+8)



// Power Management Unit (PMU)
#define M6303_PMUINTREG	__preg16(KSEG1 + 0x180000A0)	/* PMU Status Register (R/W) */
#define M6303_PMUINT_POWERSW  0x1	/* Power switch */
#define M6303_PMUINT_BATT     0x2	/* Low batt during normal operation */
#define M6303_PMUINT_DEADMAN  0x4	/* Deadman's switch */
#define M6303_PMUINT_RESET    0x8	/* Reset switch */
#define M6303_PMUINT_RTCRESET 0x10	/* RTC Reset */
#define M6303_PMUINT_TIMEOUT  0x20	/* HAL Timer Reset */
#define M6303_PMUINT_BATTLOW  0x100	/* Battery low */
#define M6303_PMUINT_RTC      0x200	/* RTC Alarm */
#define M6303_PMUINT_DCD      0x400	/* DCD# */
#define M6303_PMUINT_GPIO0    0x1000	/* GPIO0 */
#define M6303_PMUINT_GPIO1    0x2000	/* GPIO1 */
#define M6303_PMUINT_GPIO2    0x4000	/* GPIO2 */
#define M6303_PMUINT_GPIO3    0x8000	/* GPIO3 */

#define M6303_PMUCNTREG	__preg16(KSEG1 + 0x180000A2)	/* PMU Control Register (R/W) */
#define M6303_PMUWAITREG	__preg16(KSEG1 + 0x180000A8)	/* PMU Wait Counter Register (R/W) */
#define M6303_PMUDIVREG	__preg16(KSEG1 + 0x180000AC)	/* PMU Divide Mode Register (R/W) */
#define M6303_DRAMHIBCTL	__preg16(KSEG1 + 0x180000B2)	/* DRAM Hibernate Control Register (R/W) */

// Real Time Clock Unit (RTC)
#define M6303_ETIMELREG	__preg16(KSEG1 + 0x180000C0)	/* Elapsed Time L Register (R/W) */
#define M6303_ETIMEMREG	__preg16(KSEG1 + 0x180000C2)	/* Elapsed Time M Register (R/W) */
#define M6303_ETIMEHREG	__preg16(KSEG1 + 0x180000C4)	/* Elapsed Time H Register (R/W) */
#define M6303_ECMPLREG		__preg16(KSEG1 + 0x180000C8)	/* Elapsed Compare L Register (R/W) */
#define M6303_ECMPMREG		__preg16(KSEG1 + 0x180000CA)	/* Elapsed Compare M Register (R/W) */
#define M6303_ECMPHREG		__preg16(KSEG1 + 0x180000CC)	/* Elapsed Compare H Register (R/W) */
#define M6303_RTCL1LREG	__preg16(KSEG1 + 0x180000D0)	/* RTC Long 1 L Register (R/W) */
#define M6303_RTCL1HREG	__preg16(KSEG1 + 0x180000D2)	/* RTC Long 1 H Register (R/W) */
#define M6303_RTCL1CNTLREG	__preg16(KSEG1 + 0x180000D4)	/* RTC Long 1 Count L Register (R) */
#define M6303_RTCL1CNTHREG	__preg16(KSEG1 + 0x180000D6)	/* RTC Long 1 Count H Register (R) */
#define M6303_RTCL2LREG	__preg16(KSEG1 + 0x180000D8)	/* RTC Long 2 L Register (R/W) */
#define M6303_RTCL2HREG	__preg16(KSEG1 + 0x180000DA)	/* RTC Long 2 H Register (R/W) */
#define M6303_RTCL2CNTLREG	__preg16(KSEG1 + 0x180000DC)	/* RTC Long 2 Count L Register (R) */
#define M6303_RTCL2CNTHREG	__preg16(KSEG1 + 0x180000DE)	/* RTC Long 2 Count H Register (R) */
#define M6303_RTCINTREG	__preg16(KSEG1 + 0x180001DE)	/* RTC Interrupt Register (R/W) */

// Deadman's Switch Unit (DSU)
#define M6303_DSUCNTREG	__preg16(KSEG1 + 0x180000E0)	/* DSU Control Register (R/W) */
#define M6303_DSUSETREG	__preg16(KSEG1 + 0x180000E2)	/* DSU Dead Time Set Register (R/W) */
#define M6303_DSUCLRREG	__preg16(KSEG1 + 0x180000E4)	/* DSU Clear Register (W) */
#define M6303_DSUTIMREG	__preg16(KSEG1 + 0x180000E6)	/* DSU Elapsed Time Register (R/W) */

// General Purpose I/O Unit (GIU)
#define M6303_GPMD0REG		__preg16(KSEG1 + 0x18000300)	/* GPIO Mode 0 Register (R/W) */
#define M6303_GPMD1REG		__preg16(KSEG1 + 0x18000302)	/* GPIO Mode 1 Register (R/W) */
#define M6303_GPMD2REG		__preg16(KSEG1 + 0x18000304)	/* GPIO Mode 2 Register (R/W) */
#define M6303_GPMD3REG		__preg16(KSEG1 + 0x18000306)	/* GPIO Mode 3 Register (R/W) */
#define M6303_GPDATHREG	__preg16(KSEG1 + 0x18000308)	/* GPIO Data High Register (R/W) */
#define M6303_GPDATHREG_GPIO16  0x0001
#define M6303_GPDATHREG_GPIO17  0x0002
#define M6303_GPDATHREG_GPIO18  0x0004
#define M6303_GPDATHREG_GPIO19  0x0008
#define M6303_GPDATHREG_GPIO20  0x0010
#define M6303_GPDATHREG_GPIO21  0x0020
#define M6303_GPDATHREG_GPIO22  0x0040
#define M6303_GPDATHREG_GPIO23  0x0080
#define M6303_GPDATHREG_GPIO24  0x0100
#define M6303_GPDATHREG_GPIO25  0x0200
#define M6303_GPDATHREG_GPIO26  0x0400
#define M6303_GPDATHREG_GPIO27  0x0800
#define M6303_GPDATHREG_GPIO28  0x1000
#define M6303_GPDATHREG_GPIO29  0x2000
#define M6303_GPDATHREG_GPIO30  0x4000
#define M6303_GPDATHREG_GPIO31  0x8000
#define M6303_GPDATLREG	__preg16(KSEG1 + 0x1800030A)	/* GPIO Data Low Register (R/W) */
#define M6303_GPDATLREG_GPIO0   0x0001
#define M6303_GPDATLREG_GPIO1   0x0002
#define M6303_GPDATLREG_GPIO2   0x0004
#define M6303_GPDATLREG_GPIO3   0x0008
#define M6303_GPDATLREG_GPIO4   0x0010
#define M6303_GPDATLREG_GPIO5   0x0020
#define M6303_GPDATLREG_GPIO6   0x0040
#define M6303_GPDATLREG_GPIO7   0x0080
#define M6303_GPDATLREG_GPIO8   0x0100
#define M6303_GPDATLREG_GPIO9   0x0200
#define M6303_GPDATLREG_GPIO10  0x0400
#define M6303_GPDATLREG_GPIO11  0x0800
#define M6303_GPDATLREG_GPIO12  0x1000
#define M6303_GPDATLREG_GPIO13  0x2000
#define M6303_GPDATLREG_GPIO14  0x4000
#define M6303_GPDATLREG_GPIO15  0x8000
#define M6303_GPINTEN		__preg16(KSEG1 + 0x1800030C)	/* GPIO Interrupt Enable Register (R/W) */
#define M6303_GPINTMSK		__preg16(KSEG1 + 0x1800030E)	/* GPIO Interrupt Mask Register (R/W) */
#define M6303_GPINTTYPH	__preg16(KSEG1 + 0x18000310)	/* GPIO Interrupt Type High Register (R/W) */
#define M6303_GPINTTYPL	__preg16(KSEG1 + 0x18000312)	/* GPIO Interrupt Type Low Register (R/W) */
#define M6303_GPINTSTAT	__preg16(KSEG1 + 0x18000314)	/* GPIO Interrupt Status Register (R/W) */
#define M6303_GPHIBSTH		__preg16(KSEG1 + 0x18000316)	/* GPIO Hibernate Pin State High Register (R/W) */
#define M6303_GPHIBSTL		__preg16(KSEG1 + 0x18000318)	/* GPIO Hibernate Pin State Low Register (R/W) */
#define M6303_GPSICTL		__preg16(KSEG1 + 0x1800031A)	/* GPIO Serial Interface Control Register (R/W) */
#define M6303_KEYEN		__preg16(KSEG1 + 0x1800031C)	/* Keyboard Scan Pin Enable Register (R/W) */
#define M6303_PCS0STRA		__preg16(KSEG1 + 0x18000320)	/* Programmable Chip Select [0] Start Address Register (R/W) */
#define M6303_PCS0STPA		__preg16(KSEG1 + 0x18000322)	/* Programmable Chip Select [0] Stop Address Register (R/W) */
#define M6303_PCS0HIA		__preg16(KSEG1 + 0x18000324)	/* Programmable Chip Select [0] High Address Register (R/W) */
#define M6303_PCS1STRA		__preg16(KSEG1 + 0x18000326)	/* Programmable Chip Select [1] Start Address Register (R/W) */
#define M6303_PCS1STPA		__preg16(KSEG1 + 0x18000328)	/* Programmable Chip Select [1] Stop Address Register (R/W) */
#define M6303_PCS1HIA		__preg16(KSEG1 + 0x1800032A)	/* Programmable Chip Select [1] High Address Register (R/W) */
#define M6303_PCSMODE		__preg16(KSEG1 + 0x1800032C)	/* Programmable Chip Select Mode Register (R/W) */
#define M6303_LCDGPMODE	__preg16(KSEG1 + 0x1800032E)	/* LCD General Purpose Mode Register (R/W) */
#define M6303_MISCREG0		__preg16(KSEG1 + 0x18000330)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG1		__preg16(KSEG1 + 0x18000332)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG2		__preg16(KSEG1 + 0x18000334)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG3		__preg16(KSEG1 + 0x18000336)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG4		__preg16(KSEG1 + 0x18000338)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG5		__preg16(KSEG1 + 0x1800033A)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG6		__preg16(KSEG1 + 0x1800033C)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG7		__preg16(KSEG1 + 0x1800033D)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG8		__preg16(KSEG1 + 0x18000340)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG9		__preg16(KSEG1 + 0x18000342)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG10	__preg16(KSEG1 + 0x18000344)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG11	__preg16(KSEG1 + 0x18000346)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG12	__preg16(KSEG1 + 0x18000348)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG13	__preg16(KSEG1 + 0x1800034A)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG14	__preg16(KSEG1 + 0x1800034C)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_MISCREG15	__preg16(KSEG1 + 0x1800034E)	/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
#define M6303_SECIRQMASKL	M6303_GPINTEN
// No SECIRQMASKH for M6303

// Touch Panel Interface Unit (PIU)
#define M6303_PIUCNTREG	__preg16(KSEG1 + 0x18000122)	/* PIU Control register (R/W) */
#define M6303_PIUCNTREG_PIUSEQEN	0x0004
#define M6303_PIUCNTREG_PIUPWR		0x0002
#define M6303_PIUCNTREG_PADRST		0x0001

#define M6303_PIUINTREG	__preg16(KSEG1 + 0x18000124)	/* PIU Interrupt cause register (R/W) */
#define M6303_PIUINTREG_OVP		0x8000
#define M6303_PIUINTREG_PADCMD		0x0040
#define M6303_PIUINTREG_PADADP		0x0020
#define M6303_PIUINTREG_PADPAGE1	0x0010
#define M6303_PIUINTREG_PADPAGE0	0x0008
#define M6303_PIUINTREG_PADDLOST	0x0004
#define M6303_PIUINTREG_PENCHG		0x0001

#define M6303_PIUSIVLREG	__preg16(KSEG1 + 0x18000126)	/* PIU Data sampling interval register (R/W) */
#define M6303_PIUSTBLREG	__preg16(KSEG1 + 0x18000128)	/* PIU A/D converter start delay register (R/W) */
#define M6303_PIUCMDREG	__preg16(KSEG1 + 0x1800012A)	/* PIU A/D command register (R/W) */
#define M6303_PIUASCNREG	__preg16(KSEG1 + 0x18000130)	/* PIU A/D port scan register (R/W) */
#define M6303_PIUAMSKREG	__preg16(KSEG1 + 0x18000132)	/* PIU A/D scan mask register (R/W) */
#define M6303_PIUCIVLREG	__preg16(KSEG1 + 0x1800013E)	/* PIU Check interval register (R) */
#define M6303_PIUPB00REG	__preg16(KSEG1 + 0x180002A0)	/* PIU Page 0 Buffer 0 register (R/W) */
#define M6303_PIUPB01REG	__preg16(KSEG1 + 0x180002A2)	/* PIU Page 0 Buffer 1 register (R/W) */
#define M6303_PIUPB02REG	__preg16(KSEG1 + 0x180002A4)	/* PIU Page 0 Buffer 2 register (R/W) */
#define M6303_PIUPB03REG	__preg16(KSEG1 + 0x180002A6)	/* PIU Page 0 Buffer 3 register (R/W) */
#define M6303_PIUPB10REG	__preg16(KSEG1 + 0x180002A8)	/* PIU Page 1 Buffer 0 register (R/W) */
#define M6303_PIUPB11REG	__preg16(KSEG1 + 0x180002AA)	/* PIU Page 1 Buffer 1 register (R/W) */
#define M6303_PIUPB12REG	__preg16(KSEG1 + 0x180002AC)	/* PIU Page 1 Buffer 2 register (R/W) */
#define M6303_PIUPB13REG	__preg16(KSEG1 + 0x180002AE)	/* PIU Page 1 Buffer 3 register (R/W) */
#define M6303_PIUAB0REG	__preg16(KSEG1 + 0x180002B0)	/* PIU A/D scan Buffer 0 register (R/W) */
#define M6303_PIUAB1REG	__preg16(KSEG1 + 0x180002B2)	/* PIU A/D scan Buffer 1 register (R/W) */
#define M6303_PIUAB2REG	__preg16(KSEG1 + 0x180002B4)	/* PIU A/D scan Buffer 2 register (R/W) */
#define M6303_PIUAB3REG	__preg16(KSEG1 + 0x180002B6)	/* PIU A/D scan Buffer 3 register (R/W) */
#define M6303_PIUPB04REG	__preg16(KSEG1 + 0x180002BC)	/* PIU Page 0 Buffer 4 register (R/W) */
#define M6303_PIUPB14REG	__preg16(KSEG1 + 0x180002BE)	/* PIU Page 1 Buffer 4 register (R/W) */

// Audio Interface Unit (AIU)
#define M6303_SODATREG		__preg16(KSEG1 + 0x18000166)	/* Speaker Output Data Register (R/W) */
#define M6303_SCNTREG		__preg16(KSEG1 + 0x18000168)	/* Speaker Output Control Register (R/W) */
#define M6303_MIDATREG		__preg16(KSEG1 + 0x18000170)	/* Mike Input Data Register (R/W) */
#define M6303_MCNTREG		__preg16(KSEG1 + 0x18000172)	/* Mike Input Control Register (R/W) */
#define M6303_DVALIDREG	__preg16(KSEG1 + 0x18000178)	/* Data Valid Register (R/W) */
#define M6303_SEQREG		__preg16(KSEG1 + 0x1800017A)	/* Sequential Register (R/W) */
#define M6303_INTREG		__preg16(KSEG1 + 0x1800017C)	/* Interrupt Register (R/W) */
#define M6303_SDMADATREG	__preg16(KSEG1 + 0x18000160)	/* Speaker DMA Data Register (R/W) */
#define M6303_MDMADATREG	__preg16(KSEG1 + 0x18000162)	/* Microphone DMA Data Register (R/W) */
#define M6303_DAVREF_SETUP	__preg16(KSEG1 + 0x18000164)	/* DAC Vref setup register (R/W) */
#define M6303_SCNVC_END	__preg16(KSEG1 + 0x1800016E)	/* Speaker sample rate control (R/W) */
#define M6303_MIDATREG		__preg16(KSEG1 + 0x18000170)	/* Microphone Input Data Register (R/W) */
#define M6303_MCNTREG		__preg16(KSEG1 + 0x18000172)	/* Microphone Input Control Register (R/W) */
#define M6303_MCNVC_END	__preg16(KSEG1 + 0x1800017E)	/* Microphone sample rate control (R/W) */

// Keyboard Interface Unit (KIU)
#define M6303_KIUDAT0		__preg16(KSEG1 + 0x18000180)	/* KIU Data0 Register (R/W) */
#define M6303_KIUDAT1		__preg16(KSEG1 + 0x18000182)	/* KIU Data1 Register (R/W) */
#define M6303_KIUDAT2		__preg16(KSEG1 + 0x18000184)	/* KIU Data2 Register (R/W) */
#define M6303_KIUDAT3		__preg16(KSEG1 + 0x18000186)	/* KIU Data3 Register (R/W) */
#define M6303_KIUDAT4		__preg16(KSEG1 + 0x18000188)	/* KIU Data4 Register (R/W) */
#define M6303_KIUDAT5		__preg16(KSEG1 + 0x1800018A)	/* KIU Data5 Register (R/W) */
#define M6303_KIUSCANREP	__preg16(KSEG1 + 0x18000190)	/* KIU Scan/Repeat Register (R/W) */
#define M6303_KIUSCANREP_KEYEN      0x8000
#define M6303_KIUSCANREP_SCANSTP    0x0008
#define M6303_KIUSCANREP_SCANSTART  0x0004
#define M6303_KIUSCANREP_ATSTP      0x0002
#define M6303_KIUSCANREP_ATSCAN     0x0001
#define M6303_KIUSCANS		__preg16(KSEG1 + 0x18000192)	/* KIU Scan Status Register (R) */
#define M6303_KIUWKS		__preg16(KSEG1 + 0x18000194)	/* KIU Wait Keyscan Stable Register (R/W) */
#define M6303_KIUWKI		__preg16(KSEG1 + 0x18000196)	/* KIU Wait Keyscan Interval Register (R/W) */
#define M6303_KIUINT		__preg16(KSEG1 + 0x18000198)	/* KIU Interrupt Register (R/W) */
#define M6303_KIUINT_KDATLOST       0x0004
#define M6303_KIUINT_KDATRDY        0x0002
#define M6303_KIUINT_SCANINT        0x0001
#define M6303_KIUDAT6		__preg16(KSEG1 + 0x1800018C)	/* Scan Line 6 Key Data Register (R) */
#define M6303_KIUDAT7		__preg16(KSEG1 + 0x1800018E)	/* Scan Line 7 Key Data Register (R) */

// CompactFlash Controller
#define M6303_PCCARDINDEX	__preg8(KSEG1 + 0x180008E0)	/* PC Card Controller Index Register */
#define M6303_PCCARDDATA	__preg8(KSEG1 + 0x180008E1)	/* PC Card Controller Data Register */
#define M6303_INTSTATREG	__preg16(KSEG1 + 0x180008F8)	/* Interrupt Status Register (R/W) */
#define M6303_INTMSKREG	__preg16(KSEG1 + 0x180008FA)	/* Interrupt Mask Register (R/W) */
#define M6303_CFG_REG_1	__preg16(KSEG1 + 0x180008FE)	/* Configuration Register 1 */

// LED Control Unit (LED)
#define M6303_LEDHTSREG	__preg16(KSEG1 + 0x18000240)	/* LED H Time Set register (R/W) */
#define M6303_LEDLTSREG	__preg16(KSEG1 + 0x18000242)	/* LED L Time Set register (R/W) */
#define M6303_LEDCNTREG	__preg16(KSEG1 + 0x18000248)	/* LED Control register (R/W) */
#define M6303_LEDASTCREG	__preg16(KSEG1 + 0x1800024A)	/* LED Auto Stop Time Count register (R/W) */
#define M6303_LEDINTREG	__preg16(KSEG1 + 0x1800024C)	/* LED Interrupt register (R/W) */

// Serial Interface Unit (SIU / SIU1 and SIU2)
#define M6303_SIURB		__preg8(KSEG1 + 0x0C000010)	/* Receiver Buffer Register (Read) DLAB = 0 (R) */
#define M6303_SIUTH		__preg8(KSEG1 + 0x0C000010)	/* Transmitter Holding Register (Write) DLAB = 0 (W) */
#define M6303_SIUDLL		__preg8(KSEG1 + 0x0C000010)	/* Divisor Latch (Least Significant Byte) DLAB = 1 (R/W) */
#define M6303_SIUIE		__preg8(KSEG1 + 0x0C000011)	/* Interrupt Enable DLAB = 0 (R/W) */
#define M6303_SIUDLM		__preg8(KSEG1 + 0x0C000011)	/* Divisor Latch (Most Significant Byte) DLAB = 1 (R/W) */
#define M6303_SIUIID		__preg8(KSEG1 + 0x0C000012)	/* Interrupt Identification Register (Read) (R) */
#define M6303_SIUFC		__preg8(KSEG1 + 0x0C000012)	/* FIFO Control Register (Write) (W) */
#define M6303_SIULC		__preg8(KSEG1 + 0x0C000013)	/* Line Control Register (R/W) */
#define M6303_SIUMC		__preg8(KSEG1 + 0x0C000014)	/* MODEM Control Register (R/W) */
#define M6303_SIULS		__preg8(KSEG1 + 0x0C000015)	/* Line Status Register (R/W) */
#define M6303_SIUMS		__preg8(KSEG1 + 0x0C000016)	/* MODEM Status Register (R/W) */
#define M6303_SIUSC		__preg8(KSEG1 + 0x0C000017)	/* Scratch Register (R/W) */
#define M6303_SIURESET		__preg8(KSEG1 + 0x0C000019)	/* SIU Reset Register (R/W) */
#define M6303_SIUACTMSK	__preg8(KSEG1 + 0x0C00001C)	/* SIU Activity Mask (R/W) */
#define M6303_SIUACTTMR	__preg8(KSEG1 + 0x0C00001E)	/* SIU Activity Timer (R/W) */
#define M6303_SIURB_2		__preg8(KSEG1 + 0x0C000000)	/* Receive Buffer Register (Read) (R) */
#define M6303_SIUTH_2		__preg8(KSEG1 + 0x0C000000)	/* Transmitter Holding Register (Write) (W) */
#define M6303_SIUDLL_2		__preg8(KSEG1 + 0x0C000000)	/* Divisor Latch (Least Significant Byte) (R/W) */
#define M6303_SIUIE_2		__preg8(KSEG1 + 0x0C000001)	/* Interrupt Enable (DLAB = 0) (R/W) */
#define M6303_SIUDLM_2		__preg8(KSEG1 + 0x0C000001)	/* Divisor Latch (Most Significant Byte) (DLAB = 1) (R/W) */
#define M6303_SIUIID_2		__preg8(KSEG1 + 0x0C000002)	/* Interrupt Identification Register (Read) (R) */
#define M6303_SIUFC_2		__preg8(KSEG1 + 0x0C000002)	/* FIFO Control Register (Write) (W) */
#define M6303_SIULC_2		__preg8(KSEG1 + 0x0C000003)	/* Line Control Register (R/W) */
#define M6303_SIUMC_2		__preg8(KSEG1 + 0x0C000004)	/* Modem Control Register (R/W) */
#define M6303_SIULS_2		__preg8(KSEG1 + 0x0C000005)	/* Line Status Register (R/W) */
#define M6303_SIUMS_2		__preg8(KSEG1 + 0x0C000006)	/* Modem Status Register (R/W) */
#define M6303_SIUSC_2		__preg8(KSEG1 + 0x0C000007)	/* Scratch Register (R/W) */
#define M6303_SIUIRSEL_2	__preg8(KSEG1 + 0x0C000008)	/* SIU IrDA Selectot (R/W) */
#define M6303_SIURESET_2	__preg8(KSEG1 + 0x0C000009)	/* SIU Reset Register (R/W) */
#define M6303_SIUCSEL_2	__preg8(KSEG1 + 0x0C00000A)	/* IrDA Echo-back Control (R/W) */
#define M6303_SIUACTMSK_2	__preg8(KSEG1 + 0x0C00000C)	/* SIU Activity Mask Register (R/W) */
#define M6303_SIUACTTMR_2	__preg8(KSEG1 + 0x0C00000E)	/* SIU Activity Timer Register (R/W) */


// USB Module
#define M6303_USBINFIFO	__preg16(KSEG1 + 0x18000780)	/* USB Bulk Input FIFO (Bulk In End Point) (W) */
#define M6303_USBOUTFIFO	__preg16(KSEG1 + 0x18000782)	/* USB Bulk Output FIFO (Bulk Out End Point) (R) */
#define M6303_USBCTLFIFO	__preg16(KSEG1 + 0x18000784)	/* USB Control FIFO (Control End Point) (W) */
#define M6303_USBSTAT		__preg16(KSEG1 + 0x18000786)	/* Interrupt Status Register (R/W) */
#define M6303_USBINTMSK	__preg16(KSEG1 + 0x18000788)	/* Interrupt Mask Register (R/W) */
#define M6303_USBCTLREG	__preg16(KSEG1 + 0x1800078A)	/* Control Register (R/W) */
#define M6303_USBSTPREG	__preg16(KSEG1 + 0x1800078C)	/* USB Transfer Stop Register (R/W) */

// LCD Controller
#define M6303_HRTOTALREG	__preg16(KSEG1 + 0x18000400)	/* Horizontal total Register (R/W) */
#define M6303_HRVISIBREG	__preg16(KSEG1 + 0x18000402)	/* Horizontal Visible Register (R/W) */
#define M6303_LDCLKSTREG	__preg16(KSEG1 + 0x18000404)	/* Load clock start Register (R/W) */
#define M6303_LDCLKNDREG	__preg16(KSEG1 + 0x18000406)	/* Load clock end Register (R/W) */
#define M6303_VRTOTALREG	__preg16(KSEG1 + 0x18000408)	/* Vertical Total Register (R/W) */
#define M6303_VRVISIBREG	__preg16(KSEG1 + 0x1800040A)	/* Vertical Visible Register (R/W) */
#define M6303_FVSTARTREG	__preg16(KSEG1 + 0x1800040C)	/* FLM vertical start Register (R/W) */
#define M6303_FVENDREG		__preg16(KSEG1 + 0x1800040E)	/* FLM vertical end Register (R/W) */
#define M6303_LCDCTRLREG	__preg16(KSEG1 + 0x18000410)	/* LCD control Register (R/W) */
#define M6303_LCDINRQREG	__preg16(KSEG1 + 0x18000412)	/* LCD Interrupt request Register (R/W) */
#define M6303_LCDCFGREG0	__preg16(KSEG1 + 0x18000414)	/* LCD Configuration Register 0 (R/W) */
#define M6303_LCDCFGREG1	__preg16(KSEG1 + 0x18000416)	/* LCD Configuration Register 1 (R/W) */
#define M6303_FBSTAD1REG	__preg16(KSEG1 + 0x18000418)	/* Frame Buffer Start Address 1 Register (R/W) */
#define M6303_FBSTAD2REG	__preg16(KSEG1 + 0x1800041A)	/* Frame Buffer Start Address 2 Register (R/W) */
#define M6303_FBNDAD1REG	__preg16(KSEG1 + 0x18000420)	/* Frame Buffer End Address 1 Register (R/W) */
#define M6303_FBNDAD2REG	__preg16(KSEG1 + 0x18000422)	/* Frame Buffer End Address 2 register (R/W) */
#define M6303_FHSTARTREG	__preg16(KSEG1 + 0x18000424)	/* FLM horizontal Start Register (R/W) */
#define M6303_FHENDREG		__preg16(KSEG1 + 0x18000426)	/* FLM horizontal End Register (R/W) */
#define M6303_PWRCONREG1	__preg16(KSEG1 + 0x18000430)	/* Power Control register 1 (R/W) */
#define M6303_PWRCONREG2	__preg16(KSEG1 + 0x18000432)	/* Power Control register 2 (R/W) */
#define M6303_LCDIMSKREG	__preg16(KSEG1 + 0x18000434)	/* LCD Interrupt Mask register (R/W) */
#define M6303_CPINDCTREG	__preg16(KSEG1 + 0x1800047E)	/* Color palette Index and control Register (R/W) */
#define M6303_CPALDATREG	__preg32(KSEG1 + 0x18000480)	/* Color palette data register (32bits Register) (R/W) */

// physical address spaces
#define M6303_LCD             0x10000000
#define M6303_INTERNAL_IO_2   0x10000000
#define M6303_INTERNAL_IO_1   0x10000000
#define M6303_ISA_MEM         0x10000000
#define M6303_ISA_IO          0x10000000
#define M6303_ROM             0x10000000
/* PCI Interface Unit (PCIU) */
#define M6303_PCIMMAW1REG	KSEG1ADDR(0x18000000)
#define M6303_PCIMMAW2REG	KSEG1ADDR(0x18000004)
#define M6303_PCITAW1REG	KSEG1ADDR(0x18000008)
#define M6303_PCITAW2REG	KSEG1ADDR(0x1800000C)
#define M6303_PCIMIOAWREG	KSEG1ADDR(0x18000010)
#define M6303_PCICONFDREG	KSEG1ADDR(0x18000028)
#define M6303_PCICONFAREG	KSEG1ADDR(0x1800002c)
#define M6303_PCIMAILREG	KSEG1ADDR(0x1800001C)
#define M6303_BUSERRADREG	KSEG1ADDR(0x18000024)
#define M6303_INTCNTSTAREG	KSEG1ADDR(0x18000028)
#define M6303_PCIEXACCREG	KSEG1ADDR(0x1800002C)
#define M6303_PCIRECONTREG	KSEG1ADDR(0x18000030)
#define M6303_PCIENREG		KSEG1ADDR(0x18000034)
#define M6303_PCICLKSELREG	KSEG1ADDR(0x18000038)
#define M6303_PCITRDYVREG	KSEG1ADDR(0x1800003C)
#define M6303_PCICLKRUNREG	KSEG1ADDR(0x18000060)

#define M6303_PCIVENDORIDREG	KSEG1ADDR(0x18000D00)
#define M6303_PCIDEVICEIDREG	KSEG1ADDR(0x18000D02)
#define M6303_PCICOMMANDREG	KSEG1ADDR(0x18000D04)
#define M6303_PCIREVREG		KSEG1ADDR(0x18000D08)
#define M6303_PCICACHELSREG	KSEG1ADDR(0x18000D0C)
#define M6303_PCIMAILBAREG	KSEG1ADDR(0x18000D10)
#define M6303_PCIMBA1REG	KSEG1ADDR(0x18000D14)
#define M6303_PCIMBA2REG	KSEG1ADDR(0x18000D18)
#define M6303_PCIINTLINEREG	KSEG1ADDR(0x18000D3C)
#define M6303_PCIRETVALREG	KSEG1ADDR(0x18000D40)



//nand flash
#ifdef CONFIG_ALI_M3701C
#define ALI_NANDREG_BASE 0x18032000
#else
#define ALI_NANDREG_BASE 0x1803C000
#endif
#define ALI_NANDREG_LEN 0x60
#define ALI_NANDSRAM_BASE (ALI_NANDREG_BASE+0x1000)
#define ALI_NANDSRAM_LEN 0x800
#define ALI_NANDBUF_LEN 0x2000 + 0x400
#define ALI_NANDBUF1_BASE 0xa0100000


// This is the base address for IO port decoding to which the 16 bit IO port address
// is added.  Defining it to 0 will usually cause a kernel oops any time port IO is
// attempted, which can be handy for turning up parts of the kernel that make
// incorrect architecture assumptions (by assuming that everything acts like a PC),
// but we need it correctly defined to use the PCMCIA/CF controller:
#define M6303_PORT_BASE	(KSEG1 + M6303_ISA_IO)
#define M6303_ISAMEM_BASE	(KSEG1 + M6303_ISA_MEM)

//USB HOST (EHCI, OHCI)
#define ALI_USB_OHCI_PCI_PHY_BASE		0x1803A800
#define ALI_USB_OHCI_PCI_LEN			0x100
#define ALI_USB_OHCI_PHY_BASE			0x1803B000
#define ALI_USB_OHCI_LEN				0x100
#define ALI_USB_EHCI_PCI_PHY_BASE		0x1803A000 //0x18022000
#define ALI_USB_EHCI_PCI_LEN			0x100
#define ALI_USB_EHCI_PHY_BASE			0x1803A100 //0x18022100
#define ALI_USB_EHCI_LEN				0x100

#endif /* __M6303_H */

