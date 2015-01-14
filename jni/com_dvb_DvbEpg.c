#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <api/libsi/lib_epg.h>

#include "com_alitech_dvbcls_path.h"

#include "com_dvb_DvbEpg.h"
#include "epg.h"


#define FOR_TEST_EPG
//#define EPG_DETAIL_EN		1

#define  LOG_TAG    "libdvbepg"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

jmethodID MID_DvbEpg_callback;

jmethodID MID_DvbEpgEvent_constructor;
jmethodID MID_DvbEpgEvent_setStartDvbTime;
jmethodID MID_DvbEpgEvent_setEndDvbTime;
jmethodID MID_DvbEpgEvent_setEpgNibble;
jmethodID MID_DvbEpgEvent_addEpgDetail;

jmethodID MID_DvbEpgEvent_setBrief;
jmethodID MID_DvbEpgEvent_setDetail;
jmethodID MID_DvbEpgEvent_setLang;


jmethodID MID_EpgDetail_constructor;
jmethodID MID_EpgDetail_setBrief;
jmethodID MID_EpgDetail_setDetail;
jmethodID MID_EpgDetail_setLang;

jmethodID MID_DvbTime_constructor;

jfieldID FID_DvbTime_mYear;
jfieldID FID_DvbTime_mMonth;
jfieldID FID_DvbTime_mDay;
jfieldID FID_DvbTime_mHour;
jfieldID FID_DvbTime_mMin;
jfieldID FID_DvbTime_mSec;
jfieldID FID_DvbTime_mMjd;


#if 1//EPG_DETAIL_EN
jclass getClass_EpgDetail(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbEpgDetailPath);
	if (cls == NULL) {
		LOGE("%s,%d, failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}
#endif

jclass getClass_DvbEpgEvent(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbDvbEpgEventPath);
	if (cls == NULL) {
		LOGE("%s,%d, failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}

jclass getClass_DvbTime(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbDvbTimePath);
	if (cls == NULL) {
		LOGE("%s,%d, failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}

/*
 * Class:     com_dvb_DvbEpg
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_dvb_DvbEpg_initIDs
  (JNIEnv *env, jclass cls) {
	LOGD("%s,%d\n", __FUNCTION__,__LINE__);

	MID_DvbEpg_callback = (*env)->GetStaticMethodID(env, cls,
			"callback", "(ILjava/lang/Object;)V");
	if (MID_DvbEpg_callback == NULL) {
		return;
	}

	epg_set_notify(MID_DvbEpg_callback);
#if 0//EPG_DETAIL_EN

	jclass CLS_EpgDetail = getClass_EpgDetail(env);
	if (CLS_EpgDetail == NULL) {
		return;
	}

	MID_EpgDetail_constructor = (*env)->GetMethodID(env, CLS_EpgDetail,
			"<init>", "(Ljava/lang/String;)V");
	if (MID_EpgDetail_constructor == NULL) {
		return;
	}

	MID_EpgDetail_setBrief = (*env)->GetMethodID(env, CLS_EpgDetail,
			"setBrief", "(Ljava/lang/String;)V");
	if (MID_EpgDetail_setBrief == NULL) {
		return;
	}
	MID_EpgDetail_setDetail = (*env)->GetMethodID(env, CLS_EpgDetail,
			"setDetail", "(Ljava/lang/String;)V");
	if (MID_EpgDetail_setDetail == NULL) {
		return;
	}
	#if 0
	MID_EpgDetail_setLang = (*env)->GetMethodID(env, CLS_EpgDetail,
			"setLang", "(Ljava/lang/String;)V");
	if (MID_EpgDetail_setLang == NULL) {
		return;
	}
	#endif
	(*env)->DeleteLocalRef(env, CLS_EpgDetail);
#endif

	jclass CLS_DvbEpgEvent = getClass_DvbEpgEvent(env);
	if (CLS_DvbEpgEvent == NULL) {
		return;
	}
	MID_DvbEpgEvent_constructor = (*env)->GetMethodID(env, CLS_DvbEpgEvent,
			"<init>", "(ILjava/lang/String;)V");
	if (MID_DvbEpgEvent_constructor == NULL) {
		return;
	}
	MID_DvbEpgEvent_setEpgNibble = (*env)->GetMethodID(env, CLS_DvbEpgEvent,
			"setEpgNibble", "(I)V");
	if (MID_DvbEpgEvent_setEpgNibble == NULL) {
		return;
	}
	MID_DvbEpgEvent_setStartDvbTime = (*env)->GetMethodID(env, CLS_DvbEpgEvent,
			"setStartDvbTime", "(L"Class_DvbDvbTimePath";)V");
	if (MID_DvbEpgEvent_setStartDvbTime == NULL) {
		return;
	}
	MID_DvbEpgEvent_setEndDvbTime = (*env)->GetMethodID(env, CLS_DvbEpgEvent,
			"setEndDvbTime", "(L"Class_DvbDvbTimePath";)V");
	if (MID_DvbEpgEvent_setEndDvbTime == NULL) {
		return;
	}

	MID_DvbEpgEvent_setBrief = (*env)->GetMethodID(env, CLS_DvbEpgEvent,
			"setEventBrief", "(Ljava/lang/String;)V");
	if (MID_DvbEpgEvent_setBrief == NULL) {
		return;
	}

	MID_DvbEpgEvent_setDetail = (*env)->GetMethodID(env, CLS_DvbEpgEvent,
			"setEventDetail", "(Ljava/lang/String;)V");
	if (MID_DvbEpgEvent_setDetail == NULL) {
		return;
	}

	MID_DvbEpgEvent_setLang = (*env)->GetMethodID(env, CLS_DvbEpgEvent,
			"setEventLang", "(Ljava/lang/String;)V");
	if (MID_DvbEpgEvent_setLang == NULL) {
		return;
	}
	
#if 0// EPG_DETAIL_EN
	MID_DvbEpgEvent_addEpgDetail = (*env)->GetMethodID(env, CLS_DvbEpgEvent,
			"addEpgDetail", "(Lcom/dvb/EpgDetail;)V");
	if (MID_DvbEpgEvent_addEpgDetail == NULL) {
		return;
	}
#endif

	(*env)->DeleteLocalRef(env, CLS_DvbEpgEvent);

	jclass CLS_DvbTime = getClass_DvbTime(env);
	if (CLS_DvbTime == NULL) {
		return;
	}
	MID_DvbTime_constructor = (*env)->GetMethodID(env, CLS_DvbTime,
			"<init>", "(IIIIII)V");
	if (MID_DvbTime_constructor == NULL) {
		return;
	}
	FID_DvbTime_mYear = (*env)->GetFieldID(env, CLS_DvbTime, "mYear", "I");
	if (FID_DvbTime_mYear == NULL) {
		return;
	}
	FID_DvbTime_mMonth = (*env)->GetFieldID(env, CLS_DvbTime, "mMonth", "I");
	if (FID_DvbTime_mMonth == NULL) {
		return;
	}
	FID_DvbTime_mDay = (*env)->GetFieldID(env, CLS_DvbTime, "mDay", "I");
	if (FID_DvbTime_mDay == NULL) {
		return;
	}
	FID_DvbTime_mHour = (*env)->GetFieldID(env, CLS_DvbTime, "mHour", "I");
	if (FID_DvbTime_mHour == NULL) {
		return;
	}
	FID_DvbTime_mMin = (*env)->GetFieldID(env, CLS_DvbTime, "mMin", "I");
	if (FID_DvbTime_mMin == NULL) {
		return;
	}
	FID_DvbTime_mSec = (*env)->GetFieldID(env, CLS_DvbTime, "mSec", "I");
	if (FID_DvbTime_mSec == NULL) {
		return;
	}

	FID_DvbTime_mMjd = (*env)->GetFieldID(env, CLS_DvbTime, "mMjd", "I");
	if (FID_DvbTime_mMjd == NULL) {
		return;
	}
	(*env)->DeleteLocalRef(env, CLS_DvbTime);

}

JNIEXPORT jobject JNICALL Java_com_dvb_DvbEpg_getStreamTime
  (JNIEnv *env, jclass cls, jint day_offset) {
	date_time data;

	if(is_time_inited() == FALSE)
		return NULL;
	get_local_time(&data);
	if(day_offset > 0)
	{
		mjd_to_ymd(data.mjd+day_offset, &data.year, &data.month, &data.day, &data.weekday);
		data.hour = 0;
		data.min = 0;
		data.sec = 0;
	}

	jclass CLS_DvbTime = getClass_DvbTime(env);
	if (CLS_DvbTime == NULL) {
		LOGE("%s,%d",__FUNCTION__,__LINE__);
		return NULL;
	}	
	jobject streamtime = (*env)->NewObject(env, CLS_DvbTime, MID_DvbTime_constructor,
			data.year, data.month, data.day,
			data.hour, data.min, data.sec);
	
	if (streamtime == NULL) {
		LOGE("%s,%d",__FUNCTION__,__LINE__);
		return NULL;
	}  

	(*env)->SetIntField(env, streamtime, FID_DvbTime_mMjd, data.mjd);

	(*env)->DeleteLocalRef(env, CLS_DvbTime);
	return streamtime;
}

jobject getEpgEventObject(JNIEnv *env, int index, struct EpgEvent *event) {
	int i;
	unsigned short uniname[EPG_TITLE_LEN+1];
       int unilen;	
	unsigned short unibrief[EPG_BTIEF_LEN+1];

//	LOGD("%s,%d",__FUNCTION__,__LINE__);

	jclass CLS_DvbEpgEvent = getClass_DvbEpgEvent(env);
	if (CLS_DvbEpgEvent == NULL) {
		LOGE("%s,%d",__FUNCTION__,__LINE__);
		return NULL;
	}

	/* epg event */
	if(event->epg_info[0].title == NULL)
		return NULL;
	
	unilen = getUnicodeString((short *)event->epg_info[0].title, uniname);
#if 1//EPG_DETAIL_EN==0
	FREE(event->epg_info[0].title);
	event->epg_info[0].title = NULL;
#endif

	jstring title = (*env)->NewString(env, uniname, unilen);
	//jstring title = (*env)->NewString(env, "ºº×Ö", 2);
	if (title == NULL) {
		LOGE("%s,%d",__FUNCTION__,__LINE__);
		return NULL;
	}
	jobject eventObj = (*env)->NewObject(env, CLS_DvbEpgEvent, MID_DvbEpgEvent_constructor, index, title);
	if (eventObj == NULL) {
		LOGE("%s,%d",__FUNCTION__,__LINE__);
		return NULL;
	}

	(*env)->DeleteLocalRef(env, title);
	/* start time */
	jclass CLS_DvbTime = getClass_DvbTime(env);
	if (CLS_DvbTime == NULL) {
		LOGE("%s,%d",__FUNCTION__,__LINE__);
		return NULL;
	}
	jobject startTime = (*env)->NewObject(env, CLS_DvbTime, MID_DvbTime_constructor,
			event->start_time.year, event->start_time.month, event->start_time.day,
			event->start_time.hour, event->start_time.min, event->start_time.sec);
	if (startTime == NULL) {
		LOGE("%s,%d",__FUNCTION__,__LINE__);
		return NULL;
	}
	(*env)->CallVoidMethod(env, eventObj, MID_DvbEpgEvent_setStartDvbTime, startTime);
	(*env)->DeleteLocalRef(env, startTime);

	/* end time */
	jobject endTime = (*env)->NewObject(env, CLS_DvbTime, MID_DvbTime_constructor,
			event->end_time.year, event->end_time.month, event->end_time.day,
			event->end_time.hour, event->end_time.min, event->end_time.sec);
	if (endTime == NULL) {
		LOGE("%s,%d",__FUNCTION__,__LINE__);
		return NULL;
	}
	(*env)->CallVoidMethod(env, eventObj, MID_DvbEpgEvent_setEndDvbTime, endTime);
	(*env)->DeleteLocalRef(env, endTime);

	(*env)->DeleteLocalRef(env, CLS_DvbTime);

	/* nibble */
	(*env)->CallVoidMethod(env, eventObj, MID_DvbEpgEvent_setEpgNibble, event->nibble);
#if 1//EPG_DETAIL_EN
	/* detail */
	jclass ClS_EpgDetail = getClass_EpgDetail(env);
	if (ClS_EpgDetail == NULL) {
		LOGE("%s,%d",__FUNCTION__,__LINE__);
		return NULL;
	}
	if(event->detail_count > 0)
	{
		i = 0;
		#if 0
		unilen = getUnicodeString((short *)event->epg_info[i].title, uniname);
		FREE(event->epg_info[i].title);
		event->epg_info[i].title = NULL;
		

		jstring title = (*env)->NewString(env, uniname,unilen);
		if (title == NULL) {
			LOGE("%s,%d",__FUNCTION__,__LINE__);
			return NULL;
		}
		
		//jobject eventinfo = (*env)->NewObject(env, ClS_EpgDetail , MID_EpgDetail_constructor, title);
		//if (eventinfo == NULL) {
		//	LOGE("%s,%d",__FUNCTION__,__LINE__);
		//	return NULL;
		//}
		(*env)->DeleteLocalRef(env, title);
		#endif

		if (event->epg_info[i].brief != NULL) {
			unilen = getUnicodeString((short *)event->epg_info[i].brief, unibrief);
			FREE(event->epg_info[i].brief);
			event->epg_info[i].brief = NULL;

			jstring brief = (*env)->NewString(env, unibrief, unilen);
			if (brief == NULL) {
				LOGE("%s,%d",__FUNCTION__,__LINE__);
				return NULL;
			}
			(*env)->CallVoidMethod(env, eventObj, MID_DvbEpgEvent_setBrief, brief);
			//(*env)->CallVoidMethod(env, eventinfo, MID_EpgDetail_setBrief, brief);
			(*env)->DeleteLocalRef(env, brief);
		}

		if (event->epg_info[i].detail != NULL) {
			unilen = getUnicodeString((short *)event->epg_info[i].detail, unibrief);
			FREE(event->epg_info[i].brief);
			event->epg_info[i].brief = NULL;

			jstring detail = (*env)->NewString(env, unibrief, unilen);
			if (detail == NULL) {
				LOGE("%s,%d",__FUNCTION__,__LINE__);
				return NULL;
			}
			(*env)->CallVoidMethod(env, eventObj, MID_DvbEpgEvent_setDetail, detail);

			//(*env)->CallVoidMethod(env, eventinfo, MID_EpgDetail_setDetail, detail);
			(*env)->DeleteLocalRef(env, detail);
		}

		if (event->epg_info[i].lang[0] != 0) {
			jstring lang = (*env)->NewStringUTF(env, event->epg_info[i].lang);
			if (lang == NULL) {
				LOGE("%s,%d",__FUNCTION__,__LINE__);
				return NULL;
			}
			(*env)->CallVoidMethod(env, eventObj, MID_DvbEpgEvent_setLang, lang);
			(*env)->DeleteLocalRef(env, lang);
		}
		//(*env)->CallVoidMethod(env, eventObj, MID_DvbEpgEvent_addEpgDetail, eventinfo);

		//(*env)->DeleteLocalRef(env, eventinfo);
	}

#else

#endif

	(*env)->DeleteLocalRef(env, CLS_DvbEpgEvent);
	return eventObj;
}

int getDvbTime(JNIEnv *env, jobject timeObj, struct date_time *dateTime) {

	memset(dateTime, 0, sizeof(struct date_time));

	dateTime->year = (*env)->GetIntField(env, timeObj, FID_DvbTime_mYear);
	dateTime->month = (*env)->GetIntField(env, timeObj, FID_DvbTime_mMonth);
	dateTime->day = (*env)->GetIntField(env, timeObj, FID_DvbTime_mDay);
	dateTime->hour = (*env)->GetIntField(env, timeObj, FID_DvbTime_mHour);
	dateTime->min = (*env)->GetIntField(env, timeObj, FID_DvbTime_mMin);
	dateTime->sec = (*env)->GetIntField(env, timeObj, FID_DvbTime_mSec);

	return 0;
}

/*
 * Class:     com_dvb_DvbEpg
 * Method:    setActiveService
 * Signature: ([Lcom/dvb/DvbChannelNode;)I
 */
JNIEXPORT jint JNICALL Java_com_dvb_DvbEpg_setActiveService
  (JNIEnv *env, jobject obj, jobjectArray channels) {
	int ret = 0;
	int i;
	LOGD("%s,%d\n", __FUNCTION__,__LINE__);

	jint count = (*env)->GetArrayLength(env, channels);
	epg_service_t epg_service[EPG_ACTIVE_SERVICE_CNT];
	struct DvbChannelNode epg_active_service;

	if (count > EPG_ACTIVE_SERVICE_CNT) {
		LOGD("%s,%d ACTIVE SERVICE COUNT %d overflow\n", __FUNCTION__,__LINE__,count);
		count  = EPG_ACTIVE_SERVICE_CNT;
	}

	for (i=0; i<count; i++) {
		jobject chan = (*env)->GetObjectArrayElement(env, channels, i);
		if (chan == NULL) {
			LOGE("%s,%d\n", __FUNCTION__,__LINE__);
			return -1;
		}

		getChannelNode(env, chan, &epg_active_service);

		epg_service[i].service_id = epg_active_service.service_id;
		epg_service[i].tp_id= epg_active_service.tp_id;
		
		(*env)->DeleteLocalRef(env, chan);
	}

	//epg_setActiveService(epg_active_service, count);
	amsepg_set_active_service(epg_service, count);

	return ret;
}

/*
 * Class:     com_dvb_DvbEpg
 * Method:    delService
 * Signature: (Lcom/dvb/DvbChannelNode;)I
 */
JNIEXPORT jint JNICALL Java_com_dvb_DvbEpg_delService
  (JNIEnv *env, jobject obj, jobject channel) {
	int ret = 0;
	struct DvbChannelNode node;

	LOGD("%s,%d\n", __FUNCTION__,__LINE__);

	getChannelNode(env, channel, &node);

	ret = epg_del_service(node);
	//epg_delService(&node);

	return ret;
}

/*
 * Class:     com_dvb_DvbEpg
 * Method:    getPresentEvent
 * Signature: (Lcom/dvb/DvbChannelNode;Z)Lcom/dvb/EpgItem;
 */
JNIEXPORT jobject JNICALL Java_com_dvb_DvbEpg_getPresentEvent
  (JNIEnv *env, jobject obj, jobject channel, jboolean forceUpdate) {

	struct DvbChannelNode node;
	struct EpgEvent present;
	jint tp_id;
	jint service_id;
	jint ret = 0;

	LOGD("%s,%d\n", __FUNCTION__,__LINE__);
	getEPGInfo(env, channel, &tp_id, &service_id);


	ret = epg_loadPresentEvent(tp_id, service_id, &present, forceUpdate);
	if(ret != 0)
		return NULL;

	return getEpgEventObject(env, 0, &present);
}

/*
 * Class:     com_dvb_DvbEpg
 * Method:    getFollowingEvent
 * Signature: (Lcom/dvb/DvbChannelNode;Z)Lcom/dvb/EpgItem;
 */
JNIEXPORT jobject JNICALL Java_com_dvb_DvbEpg_getFollowingEvent
  (JNIEnv *env, jobject obj, jobject channel, jboolean forceUpdate) {

	struct DvbChannelNode node;
	struct EpgEvent fowllowing;
	jint tp_id;
	jint service_id;
	jint ret = 0;

	LOGD("%s,%d\n", __FUNCTION__,__LINE__);

	//getChannelNode(env, channel, &node);
	getEPGInfo(env, channel, &tp_id, &service_id);

	//epg_getFollowingEvent(&node, &fowllowing, forceUpdate);
	ret = epg_loadFollowingEvent(tp_id, service_id, &fowllowing, forceUpdate);
	if(ret != 0)
		return NULL;

	return getEpgEventObject(env, 1, &fowllowing);
}

/*
 * Class:     com_dvb_DvbEpg
 * Method:    loadScheduleEvent
 * Signature: (Lcom/dvb/DvbChannelNode;Ljava/lang/String;Ljava/lang/String;Z)I
 */
JNIEXPORT jint JNICALL Java_com_dvb_DvbEpg_loadScheduleEvent
  (JNIEnv *env, jobject obj, jobject channel, jobject startTime, jobject endTime, jboolean forceUpdate) {
	struct DvbChannelNode node;
	struct date_time start, end;

	jint tp_id;
	jint service_id;
	LOGD("%s,%d\n", __FUNCTION__,__LINE__);

	getEPGInfo(env, channel, &tp_id, &service_id);

	getDvbTime(env, startTime, &start);
	getDvbTime(env, endTime, &end);

	return epg_loadScheduleEvent(tp_id, service_id, &start, &end, 1);
}

/*
 * Class:     com_dvb_DvbEpg
 * Method:    getScheduleEvent
 * Signature: (I)Lcom/dvb/EpgItem;
 */
JNIEXPORT jobject JNICALL Java_com_dvb_DvbEpg_getScheduleEvent
  (JNIEnv *env, jobject obj, jint index) {
	struct EpgEvent event;
	struct EPG_DB_NODE *sch_event = NULL;
	LOGD("%s,%d\n", __FUNCTION__,__LINE__);

	//epg_getScheduleEvent(index, &event);
	sch_event = amsepg_get_event(index);
	if(sch_event == NULL)
	{
		return NULL;
	}
	else
		epg_convert_event(sch_event, &event);
		
	return getEpgEventObject(env, index, &event);
}

