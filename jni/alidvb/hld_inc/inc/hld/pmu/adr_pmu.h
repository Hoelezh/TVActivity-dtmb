#ifndef _ALI_PMU_H_#define _ALI_PMU_H_#ifdef __cplusplusextern "C" {#endif
/*ALi PMU driver io command**********************************/
#define ALI_PMU_IO_COMMAND_BASE_KERNEL		           (0x60<<8)
#define ALI_PMU_EN                       ALI_PMU_IO_COMMAND_BASE_KERNEL
#define ALI_PMU_IR_PROTOL_NEC			          (ALI_PMU_IO_COMMAND_BASE_KERNEL+1)
#define ALI_PMU_IR_PROTOL_RC5_X             (ALI_PMU_IO_COMMAND_BASE_KERNEL+2)

#define ALI_PMU_RTC_SET_VAL                  (ALI_PMU_IO_COMMAND_BASE_KERNEL+10)
#define ALI_PMU_RTC_SET_MIN_ALARM            (ALI_PMU_IO_COMMAND_BASE_KERNEL+11)
#define  ALI_PMU_RTC_SET_MS_ALARM            (ALI_PMU_IO_COMMAND_BASE_KERNEL+12)

#define  ALI_PMU_RTC_EN_ALARM                (ALI_PMU_IO_COMMAND_BASE_KERNEL+13)
#define  ALI_PMU_RTC_RD_VAL                  (ALI_PMU_IO_COMMAND_BASE_KERNEL+14)
#define ALI_PMU_RTC_RD_MS_VAL                (ALI_PMU_IO_COMMAND_BASE_KERNEL+15)
#define ALI_PMU_EXIT_STANDBY_STATUS           (ALI_PMU_IO_COMMAND_BASE_KERNEL+16)
//for C3701C PMU MCU 
 
#define  ALI_PMU_MCU_RST                           (ALI_PMU_IO_COMMAND_BASE_KERNEL+17)
 
#define  ALI_PMU_MCU_ENTER_STANDBY                 (ALI_PMU_IO_COMMAND_BASE_KERNEL+18)
#define ALI_PMU_MCU_SET_TIME                       (ALI_PMU_IO_COMMAND_BASE_KERNEL+19)

#define ALI_PMU_MCU_READ_TIME                      (ALI_PMU_IO_COMMAND_BASE_KERNEL+20)
 
#define ALI_PMU_MCU_WAKEUP_TIME                    ALI_PMU_RTC_SET_MIN_ALARM
 
#define ALI_PMU_PANEL_POWKEY_EN                     (ALI_PMU_IO_COMMAND_BASE_KERNEL+22) #define ALI_PMU_SHOW_TIME_EN                  (ALI_PMU_IO_COMMAND_BASE_KERNEL+23)

 #define ALI_PMU_IRX_POWER_KEY	0x01 #define ALI_PMU_CEC_POWER_KEY	0x02 
struct rtc_time_pmu
{
     	unsigned int  year;
    	unsigned char month;
	unsigned char date;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
};

struct min_alarm
{
	unsigned char en_month;
	unsigned char en_date;
	unsigned char en_sun;
	unsigned char en_mon;
	unsigned char en_tue;
	unsigned char en_wed;
	unsigned char en_thr;
	unsigned char en_fri;
	unsigned char en_sat;

	unsigned char month;
	unsigned char date;
	unsigned char hour;
	unsigned char min;
};

struct ms_alarm
{
	unsigned char en_hour;
	unsigned char en_min;
	unsigned char en_sec;
	unsigned char en_ms;

	unsigned char hour;
    	unsigned char min;
	unsigned char sec;
	unsigned char ms;
};

struct min_alarm_num
{
	struct min_alarm min_alm;
	unsigned char num;  //rtc alarm number,from 0~7
};
struct ms_alarm_num
{
	struct ms_alarm ms_alm;
	unsigned char num;//rtc alarm number,from 8~9
};void set_ali_pmu_standby_ir_power_key(unsigned long * ir_power_key);void set_ali_pmu_standby_panel_power_key(unsigned long panel_power_key);void set_ali_pmu_standby_timeout(struct rtc_time_pmu *current_time,struct rtc_time_pmu *wakeup_time);void enter_ali_pmu_standby(void);unsigned char  get_ali_pmu_wakeup_status(void);
#ifdef __cplusplus}#endif
#endif /*_ALI_PMU_H_*/
