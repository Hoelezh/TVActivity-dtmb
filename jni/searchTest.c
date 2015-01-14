#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include<pthread.h>

#include "com_dvb_DvbSearch.h"
#include "search.h"

#include "channelNode.h"

#define  LOG_TAG    "libdvbsearch"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

search_notify_t search_callback = NULL;

int search_status = 0;

void *search_process(void *param)
{
	LOGD("%s,%d\n", __FUNCTION__,__LINE__);

	if (search_callback) {
		int num=28;
		search_callback(com_dvb_DvbSearch_SEARCH_PROGRESS,(void *)&num);

		struct DvbFrontend frontend;
		frontend.ft_type = 1;
		frontend.qam = 2;
		frontend.frq = 3;
		frontend.sym = 4;
		search_callback(com_dvb_DvbSearch_SEARCH_TP_TUNING,(void *)&frontend);

		struct DvbChannelNode node;
		chan_get_channel(0, &node);
		search_callback(com_dvb_DvbSearch_SEARCH_PROGRAM_ADDED,(void *)&node);

		search_callback(com_dvb_DvbSearch_SEARCH_TP_FULL,NULL);

		search_callback(com_dvb_DvbSearch_SEARCH_PROGRAM_FULL,NULL);

		//search_callback(com_dvb_DvbSearch_SEARCH_COMPLETE,NULL);

		while (search_status) {
			;
		}

		if (search_callback) {
			LOGD("process:com_dvb_DvbSearch_SEARCH_STOP",num);
			search_callback(com_dvb_DvbSearch_SEARCH_STOP,NULL);
		}
	}

	return NULL;
}

int search_register(search_notify_t callback) {
	LOGD("search_register, 0x%x",callback);
	search_callback = callback;
}

int search_unregister() {
	LOGD("search_unregister");
	search_callback = NULL;
}

int search_start(struct DvbSearchParam *param) {
	int err;
	pthread_t ntid;

	LOGD("search_start");

	search_status = 1;

	//create task for test
	err = pthread_create(&ntid, NULL, search_process, NULL);
    if (err != 0)
	{
		LOGE("%s,%d,can't create thread: %s\n", __FUNCTION__,__LINE__,strerror(err));
    }

	return 0;
}

int search_stop() {
	LOGD("search_stop");

	search_status = 0;

	return 0;
}
