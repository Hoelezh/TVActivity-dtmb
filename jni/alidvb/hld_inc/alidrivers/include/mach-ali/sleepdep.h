/*
 * sleep dependnecy.h
 * This file contains all the sleep hardware dependencies.
 *
 */
#ifndef __ALI_M36_SLEEP_DEPENDENCY_INCLUDE____H__
#define __ALI_M36_SLEEP_DEPENDENCY_INCLUDE____H__

#include <linux/suspend.h>
#include <linux/delay.h>

#include <asm/io.h>

#define ALI_IRC_BASE				  0x18018100      /* Memory base for ALI_M3602_IRC */
#define INFRA_IRCCFG				  (ALI_IRC_BASE + 0x00)
#define INFRA_FIFOCTRL			  (ALI_IRC_BASE + 0x01)
#define INFRA_TIMETHR				  (ALI_IRC_BASE + 0x02)
#define INFRA_NOISETHR        (ALI_IRC_BASE + 0x03)
#define INFRA_IER					    (ALI_IRC_BASE + 0x06)
#define INFRA_ISR					    (ALI_IRC_BASE + 0x07)
#define INFRA_RLCBYTE				  (ALI_IRC_BASE + 0x08)
#define INTV_REPEAT				    250     /* in mini second */
#define INTV_REPEAT_FIRST			300     /* in mini second */
#define PAN_KEY_INVALID			  0xFFFFFFFF

#define VALUE_TOUT			      24000   /* Timeout threshold, in uS */
#define VALUE_CLK_CYC		      8       /* Work clock cycle, in uS */
#define VALUE_NOISETHR		    80      /* Noise threshold, in uS */
#define IR_RLC_SIZE			      256
#define IO_BASE_ADDR          0x18000000
#define AUDIO_IO_BASE_ADDR    0x18002000
#define USB_IO_BASE_ADDR      0x1803d800
#define HDMI_PHY 	            0x1800006c
#define SYS_IC_NB_BASE_H		  0x1800
#define SYS_IC_NB_CFG_SEQ0    0x74
#define SYS_IC_NB_BIT1033     0x1033
#define SYS_IC_NB_BIT1031     0x1031

/*
 * Useful MACROs
 */
#define SYNC() \
    do { \
        asm volatile ("sync; ehb"); \
    } while (0)
#define SDBBP() \
    do { \
        asm volatile (".word 0x7000003f; nop"); \
    } while (0)

static inline void suspend_step(char c)
{/*
 //#define PM_SUSPEND_STEP_DBG
#ifdef PM_SUSPEND_STEP_DBG
    unsigned char *d_t = (unsigned char *)0xb8018300;
    int i = 10000;
    
    *d_t = c;
    while (i-- > 0) ;
    i = 10000;
    *d_t = c;
    while (i-- > 0) ;
#endif*/
}

#define PM_ENABLE_DEVICE 1
#define PM_DISABLE_DEVICE 0

#define PM_ENTER_STANDBY 1
#define PM_EXIT_STANDBY 0

void operate_device(int enable);
void pm_standby_prepare(int enter);
void operate_time_count(unsigned long timeout);


#endif

