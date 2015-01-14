#ifndef  _SEC_TDT_H_
#define  _SEC_TDT_H_

#include <hld/adr_hld_dev.h>
#include <hld/dmx/adr_dmx_dev.h>
//#include <api/libtsi/sec_psi.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define TDT_PID 0x0014
#define TDT_TABLE_ID  0x70
#define TOT_TABLE_ID 0x73

#define DONT_UPDATE_STC	0
#define UPDATE_STC			0x1
#define NOT_SPECIFIED		0xff

typedef struct 
{
	UINT32 gps_sec;
	UINT16 year;
	UINT8   month;
	UINT8   day;
	UINT8   weekday;
	UINT8   hour;
	UINT8   min;
	UINT8   sec;
}date_time;

struct daylight_savings_param{
	BOOL DS_status;
	UINT8 DS_day_of_month;
	UINT8 DS_hour;
};

typedef void (* time_callback)(void);

#define SEC_PER_DAY	86400
void get_stream_UTC_time(date_time*dt);

void init_UTC(date_time* dt);
void get_UTC(date_time *dt);
void set_STC_time(date_time* dt);
void set_STC_offset(INT32 hour, INT32 min, INT32 sec);
void get_STC_time(date_time *dt);
void get_STC_offset(INT32 *hour_off,INT32* min_off,INT32 *sec_off);
INT32 eit_compare_time(date_time* t1, date_time* t2);
void get_local_time(date_time *dt);
UINT32 dt2utc(date_time *dt);
void utc2dt(UINT32 utc, date_time * dt);
INT32 init_clock(time_callback callback);
INT32 is_time_inited(void);
void enable_time_parse(UINT8 gmt);
void disable_time_parse(void);

BOOL init_time_from_stream(UINT8* buff);
void get_time_offset(date_time*d1,date_time*d2,INT32*day,INT32*hour, INT32*min, INT32*sec);
void convert_time_by_offset (date_time *des,date_time *src,INT32 hoff, INT32 moff);
void convert_time_by_offset2 (date_time *des,date_time *src,INT32 hoff, INT32 moff, INT32 soff);

//sunny yin
//this function is added for real standby
void adjust_time_by_offset (date_time *des,date_time *src,INT32 hoff, INT32 moff);



#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _SEC_TDT_H_ */
