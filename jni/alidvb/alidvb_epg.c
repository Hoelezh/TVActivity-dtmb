#include <adr_sys_config.h>
#include <adr_retcode.h>

#include <osal/osal.h>

#include <hld/adr_hld_dev.h>
#include <hld/dmx/adr_dmx_dev.h>
#include <hld/dmx/adr_dmx.h>

#include <api/libc/string.h>
#include <api/libc/log.h>
#include <api/libchar/lib_char.h>

#include <api/libsi/si_module.h>
#include <api/libsi/si_service_type.h>

#include <android/log.h>

#include "alidvb_epg.h"

#define LOG_TAG    "ALiDVB_EPG"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define SEARCH_DEBUG	LOGD
#define SEARCH_NOTICE	LOGI
#define SEARCH_ERROR	LOGE

#define FUNCTION_ENTER()		 //SEARCH_NOTICE("	ENTER!\n")
#define FUNCTION_LEAVE()		 //SEARCH_NOTICE("	LEAVE!\n")

#define EPG_CALLBACK(a, b)	do {if (epg_notify_callback != NULL) epg_notify_callback(a, b);} while(0)

static ALiDVB_EPGNotifyFn epg_notify_callback = NULL;

void epg_callback(UINT32 tp_id, UINT16 service_id, UINT16 event_type)
{

	if(event_type <= SCHEDULE_EVENT && amsepg_check_active_service(tp_id, service_id))
	{
		if(epg_notify_callback != NULL)
		{
			epg_notify_callback(event_type, &service_id);
		}
	}
}

void epg_set_notify(ALiDVB_EPGNotifyFn callback)
{
	epg_notify_callback = callback;
}

int ALiDVB_EPGInit(epg_config_t *param)
{
	param->call_back = epg_callback;
	return amsepg_init(NULL, 0x180000, param);
}

UINT16 *epg_get_event_name(struct EPG_DB_NODE *ep, INT32 epg_lang_select, INT32 max_len)
{
	UINT8 len;
	UINT16 *name = NULL;
	UINT8 name_utf = NULL;

	if (ep==NULL)	return NULL;

	if (ep->lang[epg_lang_select].text_char == NULL)	return NULL;

	len = ep->lang[epg_lang_select].text_char[0];
	LOGD("epg_get_event_name: %d, %d, %d", epg_lang_select, len, ep->lang[epg_lang_select].text_char);
	if (len > 0)
	{
		name = MALLOC(max_len*2);
		memset(name, 0, max_len*2);
		len = dvb_to_unicode(ep->lang[epg_lang_select].text_char+1, len, (UINT16 *)name, max_len,
				get_iso639_refcode(lang2tolang3(ep->lang[epg_lang_select].lang_code2)));
		LOGD("epg_get_event_name: end len = %d", len);
		return name;
	}
	else
		return NULL;
}

UINT8 *epg_get_event_language(struct EPG_DB_NODE *ep, UINT8 epg_lang_select)
{
	if (NULL == ep)
		return NULL;

	return lang2tolang3(ep->lang[epg_lang_select].lang_code2);
}

UINT16 *epg_get_event_all_short_detail(eit_event_info_t *ep, UINT8 epg_lang_select, UINT32 maxLen)
{
	UINT8 *text;
	UINT16 len;
	UINT16 *short_buf;

	if (ep==NULL)	return NULL;

	if (ep->lang[epg_lang_select].text_char == NULL)	return NULL;

	

	len = ep->lang[epg_lang_select].text_char[0]; //event name
	text = ep->lang[epg_lang_select].text_char + len + 1; //short text char
	len = text[0];
	if (len > 0)
	{
		short_buf = MALLOC(maxLen*2);
		if(short_buf == NULL) 
		{
			LOGD("epg_convert_event, malloc fail");

		}
		memset(short_buf, 0, maxLen*2);

		dvb_to_unicode(text+1, len, short_buf, maxLen,
							get_iso639_refcode(lang2tolang3(ep->lang[epg_lang_select].lang_code2)));
		return short_buf;
	}
	else
		return NULL;
}

UINT32 epg_get_event_all_extented_detail(eit_event_info_t *ep, UINT8 epg_lang_select, UINT32 maxLen)
{
	UINT8 *text;
	UINT16 len;
	UINT16 *extented_buf;
	
	if (ep==NULL)	return 0;

	if (ep->lang[epg_lang_select].text_char == NULL)	return 0;

	len = ep->lang[epg_lang_select].text_char[0]; //event name
	text = ep->lang[epg_lang_select].text_char + len + 1; //short text char
	len = text[0];
	text += (len + 1); //extended text char
	len = (text[0] << 8) | text[1];
	if (len > 0)
	{
		extented_buf = MALLOC(maxLen*2);
		memset(extented_buf, 0, maxLen*2);
		dvb_to_unicode(text+2, len, extented_buf, maxLen,
							get_iso639_refcode(lang2tolang3(ep->lang[epg_lang_select].lang_code2)));
		return extented_buf;
	}
	else
		return 0;
}


int epg_convert_event(struct EPG_DB_NODE *db_event, struct EpgEvent *epgEvent)
{
	if(db_event == NULL || epgEvent == NULL)
		return 1;
	INT32 i = 0;
	UINT8 *lang_code;
	
	memset(epgEvent, 0, sizeof(struct EpgEvent));

	epgEvent->tp_id = db_event->tp_id;
	epgEvent->service_id = db_event->service_id;
	epgEvent->event_id = db_event->event_id;
	epgEvent->event_type = db_event->event_type;

	amsget_event_start_time(db_event, &epgEvent->start_time);
	amsget_event_end_time(db_event, &epgEvent->end_time);

	#if 0
	//mjd_to_ymd(db_event->mjd_num, &year, &month, &day, &weekday);
	epgEvent->start_time.year = 2014;
	epgEvent->start_time.month = 6;
	epgEvent->start_time.day = 10;
	epgEvent->start_time.hour = 1;
	epgEvent->start_time.min = 20;
	epgEvent->start_time.sec = 0;

	epgEvent->end_time.year = 2014;
	epgEvent->end_time.month = 6;
	epgEvent->end_time.day = 10;
	epgEvent->end_time.hour =2;
	epgEvent->end_time.min = 20;
	epgEvent->end_time.sec = 0;

	epgEvent->start_time.mjd = ymd_to_mjd(2014, 6, 10);
	epgEvent->end_time.mjd = ymd_to_mjd(2014, 6, 10);
#endif
	for(i = 0; i< EPG_LANGUAGE_COUNT; i++)
	{
		LOGD("epg_convert_event, text len %d", db_event->lang[i].text_length);
		if(db_event->lang[i].text_length > 0)
		{
			LOGD("epg_convert_event, i=%d, text[0] = %d", i,  db_event->lang[i].text_char[0] );
			epgEvent->epg_info[i].title = epg_get_event_name(db_event, i, EPG_TITLE_LEN);
			if(epgEvent->epg_info[i].title == NULL) {
				LOGD("epg_convert_event, name is null");
				break;

			}
			#if 1//EPG_DETAIL_EN
			lang_code = epg_get_event_language(db_event, i);
			epgEvent->epg_info[i].lang[0] = lang_code[0];
			epgEvent->epg_info[i].lang[1] = lang_code[1];
			epgEvent->epg_info[i].lang[2] = lang_code[2];
			epgEvent->epg_info[i].lang[3] = 0;

			epgEvent->epg_info[i].brief = epg_get_event_all_short_detail(db_event, i, EPG_BTIEF_LEN);
			epgEvent->epg_info[i].detail = epg_get_event_all_extented_detail(db_event, i, EPG_DETIAL_LEN);
			#endif
			epgEvent->detail_count++;
		}
		LOGD("epg_convert_event, get name end  i=%d", i);
	}
	LOGD("epg_convert_event, end  i=%d", i);
//	epgEvent->detail_count = 1;
//	epgEvent->epg_info[0].title = "schEvent";
//	epgEvent->epg_info[0].brief = "schEventbrief";
//	epgEvent->epg_info[0].detail = "detail";

	

	epgEvent->nibble = db_event->nibble<<4|db_event->nibble2;
	epgEvent->rating = db_event->rating;
	LOGD("epg_convert_event, end  i=%d", i);

}

int epg_loadScheduleEvent(int tp_id, int service_id, struct date_time *start, struct date_time *end, int forceUpdate)
{
	INT32 event_num = 0;

	amsepg_get_service_event(tp_id, service_id, SCHEDULE_EVENT, start,end, &event_num, forceUpdate);

	return event_num;

}

int epg_loadPresentEvent(int tp_id, int service_id, struct EpgEvent *epgEvent, int forceUpdate)
{
	if(epgEvent == NULL)
		return 1;

	struct EPG_DB_NODE *epg_db;
	
	epg_db = amsepg_get_service_event(tp_id, service_id, PRESENT_EVENT, NULL,NULL, NULL, forceUpdate);
	if(epg_db == NULL)
		return 2;
	epg_convert_event(epg_db, epgEvent);
	return 0;
}

int epg_loadFollowingEvent(int tp_id, int service_id, struct EpgEvent *epgEvent, int forceUpdate)
{
	if(epgEvent == NULL)
		return 1;
	
	struct EPG_DB_NODE *epg_db;
	
	epg_db = amsepg_get_service_event(tp_id, service_id, FOLLOWING_EVENT, NULL,NULL, NULL, forceUpdate);
	if(epg_db == NULL)
		return 2;

	epg_convert_event(epg_db, epgEvent);
	return 0;
}

int epg_del_service(struct DvbChannelNode node)
{
	epg_service_t service;

	service.service_id = node.service_id;
	service.tp_id = node.tp_id;
	
	return amsepg_del_service(&service, 1, EQUAL);

}


