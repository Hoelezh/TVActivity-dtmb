#ifndef _ALI_PMU_COMMON_H_
#define _ALI_PMU_COMMON_H_
/*ALi PMU driver io command**********************************/
#define ALI_PMU_IO_COMMAND_BASE		           (0x60<<8)
#define ALI_PMU_EN                       ALI_PMU_IO_COMMAND_BASE
#define ALI_PMU_IR_PROTOL_NEC			          (ALI_PMU_IO_COMMAND_BASE+1)
#define ALI_PMU_IR_PROTOL_RC5_X             (ALI_PMU_IO_COMMAND_BASE+2)

#define ALI_PMU_RTC_SET_VAL                  (ALI_PMU_IO_COMMAND_BASE+10)
#define ALI_PMU_RTC_SET_MIN_ALARM            (ALI_PMU_IO_COMMAND_BASE+11)
#define  ALI_PMU_RTC_SET_MS_ALARM            (ALI_PMU_IO_COMMAND_BASE+12)

#define  ALI_PMU_RTC_EN_ALARM                (ALI_PMU_IO_COMMAND_BASE+13)
/*when normer mode use south rtc*/
#define  ALI_PMU_RTC_RD_VAL                  (ALI_PMU_IO_COMMAND_BASE+14)  //for C3701C PMU MCU 
#define ALI_PMU_RTC_RD_MS_VAL                (ALI_PMU_IO_COMMAND_BASE+15)
#define ALI_PMU_EXIT_STANDBY_STATUS           (ALI_PMU_IO_COMMAND_BASE+16)

 #define  ALI_PMU_MCU_RST                           (ALI_PMU_IO_COMMAND_BASE+17)  //for C3701C PMU MCU 

 #define  ALI_PMU_MCU_ENTER_STANDBY                 (ALI_PMU_IO_COMMAND_BASE+18)  //for C3701C PMU MCU 

/*through mailbox set system time,when enter standby mode*/
 #define ALI_PMU_MCU_SET_TIME                       (ALI_PMU_IO_COMMAND_BASE+19)  //for C3701C PMU MCU 

/* from standy mode -->normer mode,read mcu rtc init value*/
 #define ALI_PMU_MCU_READ_TIME                      (ALI_PMU_IO_COMMAND_BASE+20)  //for C3701C PMU MCU 

 #define ALI_PMU_MCU_WAKEUP_TIME                    ALI_PMU_RTC_SET_MIN_ALARM     //for C3701C PMU MCU 

 #define ALI_PMU_PANEL_I2C_EN                     (ALI_PMU_IO_COMMAND_BASE+22)
  #define ALI_PMU_SHOW_TIME_EN                  (ALI_PMU_IO_COMMAND_BASE+23)

#define ALI_PMU_RTC_TIMER3_SET_VAL              (ALI_PMU_IO_COMMAND_BASE+24)

#define ALI_PMU_RTC_TIMER3_GET_VAL              (ALI_PMU_IO_COMMAND_BASE+25)
 #define ALI_PMU_GET_SET_LOGADDR              (ALI_PMU_IO_COMMAND_BASE+26)

struct rtc_time_pmu
{
//	unsigned char year;//year mod 4
    unsigned int year;
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
};

struct rtc_base_time
{
    unsigned char rtc_sec;
    unsigned char rtc_min;
    unsigned char rtc_hour;
    unsigned char rtc_date;
    unsigned char rtc_month;
    unsigned int  rtc_year; 
    unsigned char g_year_h;
    unsigned char g_year_l;
    unsigned int  g_year;
    unsigned char g_month;
    unsigned char g_day;
    unsigned char g_hour;
    unsigned char g_min;
    unsigned char g_sec;
};
  enum MCU_SHOW_PANNEL
  {
	MCU_SHOW_NOTHING = 0,
	MCU_SHOW_OFF,
	MCU_SHOW_TIME
  };
#endif /*_ALI_PMU_H_*/
