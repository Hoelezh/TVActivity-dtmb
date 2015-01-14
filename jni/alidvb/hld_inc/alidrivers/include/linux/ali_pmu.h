#ifndef _ALI_PMU_H_
#define _ALI_PMU_H_

#include <ali_pmu_common.h>
/*ALi PMU driver io command**********************************/
#define ALI_PMU_IO_COMMAND_BASE_KERNEL		           (0x60<<8)
//#define ALI_PMU_EN                       ALI_PMU_IO_COMMAND_BASE_KERNEL
#define ALI_PMU_IR_PROTOL_NEC			          (ALI_PMU_IO_COMMAND_BASE_KERNEL+1)
#define ALI_PMU_IR_PROTOL_RC5_X             (ALI_PMU_IO_COMMAND_BASE_KERNEL+2)

#define ALI_PMU_RTC_SET_VAL                  (ALI_PMU_IO_COMMAND_BASE_KERNEL+10)
#define ALI_PMU_RTC_SET_MIN_ALARM            (ALI_PMU_IO_COMMAND_BASE_KERNEL+11)
#define  ALI_PMU_RTC_SET_MS_ALARM            (ALI_PMU_IO_COMMAND_BASE_KERNEL+12)

#define  ALI_PMU_RTC_EN_ALARM                (ALI_PMU_IO_COMMAND_BASE_KERNEL+13)
#define  ALI_PMU_RTC_RD_VAL                  (ALI_PMU_IO_COMMAND_BASE_KERNEL+14)
#define ALI_PMU_RTC_RD_MS_VAL                (ALI_PMU_IO_COMMAND_BASE_KERNEL+15)
#define ALI_PMU_EXIT_STANDBY_STATUS           (ALI_PMU_IO_COMMAND_BASE_KERNEL+16)//for C3701C PMU MCU  
#define  ALI_PMU_MCU_RST                           (ALI_PMU_IO_COMMAND_BASE_KERNEL+17) 
#define  ALI_PMU_MCU_ENTER_STANDBY                 (ALI_PMU_IO_COMMAND_BASE_KERNEL+18)
#define ALI_PMU_MCU_SET_TIME                       (ALI_PMU_IO_COMMAND_BASE_KERNEL+19)
#define ALI_PMU_MCU_READ_TIME                      (ALI_PMU_IO_COMMAND_BASE_KERNEL+20) 
#define ALI_PMU_MCU_WAKEUP_TIME                    ALI_PMU_RTC_SET_MIN_ALARM 
#define ALI_PMU_PANEL_POWKEY_EN                     (ALI_PMU_IO_COMMAND_BASE_KERNEL+22)
 #define ALI_PMU_SHOW_TIME_EN                  (ALI_PMU_IO_COMMAND_BASE_KERNEL+23)

 #define ALI_PMU_IRX_POWER_KEY	0x01
 #define ALI_PMU_CEC_POWER_KEY	0x02

#endif /*_ALI_PMU_H_*/
