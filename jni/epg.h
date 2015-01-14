#ifndef _Included_epg
#define _Included_epg

#include "channelNode.h"

#define EPG_ACTIVE_SERVICE_CNT 5
#define EPG_LANGUAGE_COUNT 3

#define EPG_TITLE_LEN	32
#define EPG_BTIEF_LEN	1024
#define EPG_DETIAL_LEN	1024

struct date_time {
       int mjd;
	short year;
	char   month;
	char   day;
	char   weekday;
	char   hour;
	char   min;
	char   sec;
};

struct EpgDetail {
	char *title;
	char *brief;
	char *detail;
	char lang[4];
};

struct EpgEvent {
	int tp_id;
	int service_id;

	int event_id;
	int event_type;

	struct date_time  start_time;
	struct date_time  end_time;

	int detail_count;
	struct EpgDetail epg_info[EPG_LANGUAGE_COUNT];

	int nibble; // (content_nibble1<4) | content_nibble2
	int rating; //!< 0-0xF, Parent Rating Descriptor: rating & 0x0F
};

int epg_setActiveService(struct DvbChannelNode *nodes, int count);

int epg_delService(struct DvbChannelNode *node);

//int epg_getPresentEvent(struct DvbChannelNode *node, struct EpgEvent *present, int forceUpdate);
//int epg_getFollowingEvent(struct DvbChannelNode *node, struct EpgEvent *following, int forceUpdate);

//int epg_loadScheduleEvent(struct DvbChannelNode *node, struct DateTime *start, struct DateTime *end, int forceUpdate);
int epg_loadScheduleEvent(int tp_id, int service_id, struct date_time *start, struct date_time *end, int forceUpdate);
int epg_loadPresentEvent(int tp_id, int service_id, struct EpgEvent *epgEvent, int forceUpdate);
int epg_loadFollowingEvent(int tp_id, int service_id, struct EpgEvent *epgEvent, int forceUpdate);


int epg_getScheduleEvent(int index, struct EpgEvent *schEvent);

#endif // _Included_epg
