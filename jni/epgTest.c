#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#include "epg.h"

static struct DvbChannelNode epg_active_service[EPG_ACTIVE_SERVICE_CNT];

int epg_setActiveService(struct DvbChannelNode *nodes, int count) {
	return 0;
}

int epg_delService(struct DvbChannelNode *node) {
	return 0;
}

int epg_getPresentEvent(struct DvbChannelNode *node, struct EpgEvent *present, int forceUpdate) {
	memset(present, 0, sizeof(struct EpgEvent));

	present->tp_id = 101;
	present->service_id = 102;
	present->event_id = 103;
	present->event_type = 104;

	present->start_time.year = 2013;
	present->start_time.month = 10;
	present->start_time.day = 11;
	present->start_time.hour = 3;
	present->start_time.min = 40;
	present->start_time.sec = 0;

	present->end_time.year = 2013;
	present->end_time.month = 10;
	present->end_time.day = 11;
	present->end_time.hour = 4;
	present->end_time.min = 10;
	present->end_time.sec = 0;

	present->detail_count = 1;

	present->epg_info[0].title = "present";
	present->epg_info[0].brief = "presentbrief";

	present->nibble = 107;
	present->rating = 108;

	return 0;
}

int epg_getFollowingEvent(struct DvbChannelNode *node, struct EpgEvent *following, int forceUpdate) {

	memset(following, 0, sizeof(struct EpgEvent));

	following->tp_id = 201;
	following->service_id = 202;
	following->event_id = 203;
	following->event_type = 204;

	following->start_time.year = 2013;
	following->start_time.month = 10;
	following->start_time.day = 11;
	following->start_time.hour = 4;
	following->start_time.min = 30;
	following->start_time.sec = 0;

	following->end_time.year = 2013;
	following->end_time.month = 10;
	following->end_time.day = 11;
	following->end_time.hour = 6;
	following->end_time.min = 20;
	following->end_time.sec = 0;

	following->detail_count = 1;

	following->epg_info[0].title = "following";
	following->epg_info[0].detail = "followingdetail";

	following->nibble = 207;
	following->rating = 208;

	return 0;
}

//int epg_loadScheduleEvent(struct DvbChannelNode *node, struct date_time *start, struct date_time *end, int forceUpdate) {
	//return 3;
//}

int epg_getScheduleEvent(int index, struct EpgEvent *schEvent) {

	memset(schEvent, 0, sizeof(struct EpgEvent));

	schEvent->tp_id = 301+index*10;
	schEvent->service_id = 302+index*10;
	schEvent->event_id = 303+index*10;
	schEvent->event_type = 304+index*10;

	schEvent->start_time.year = 2013;
	schEvent->start_time.month = 10;
	schEvent->start_time.day = 11;
	schEvent->start_time.hour = index + 1;
	schEvent->start_time.min = 30;
	schEvent->start_time.sec = 0;

	schEvent->end_time.year = 2013;
	schEvent->end_time.month = 10;
	schEvent->end_time.day = 11;
	schEvent->end_time.hour = index+2;
	schEvent->end_time.min = 20;
	schEvent->end_time.sec = 0;

	schEvent->detail_count = 1;
	schEvent->epg_info[0].title = "schEvent";
	schEvent->epg_info[0].brief = "schEventbrief";
	schEvent->epg_info[0].detail = "detail";

	schEvent->nibble = 307+index*10;
	schEvent->rating = 308+index*10;

	return 0;
}

