#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#include "com_dvb_DvbSearch.h"
#include "channelNode.h"
#include "alidvb_channelnode.h"
#include "alidvb_search.h"

#include "com_alitech_dvbcls_path.h"

#define  LOG_TAG    "libdvbsearch"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

JavaVM *gJavaVM;
jobject gDvbSearchObject;

jmethodID MID_DvbSearch_callback;

jfieldID FID_DvbSearchParam_mFrequencyFrom;
jfieldID FID_DvbSearchParam_mFrequencyTo;
jfieldID FID_DvbSearchParam_mBandwidth;
jfieldID FID_DvbSearchParam_mSymbolRate;
jfieldID FID_DvbSearchParam_mQam;
jfieldID FID_DvbSearchParam_mNitSearch;
jfieldID FID_DvbSearchParam_mFrontendType;
jfieldID FID_DvbSearchParam_mSearchMethod;
jfieldID FID_DvbSearchParam_mFTAonly;
jfieldID FID_DvbSearchParam_mProgramType;

jclass getClass_DvbSearchParam(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbSearchParam);
	LOGD("getClass_DvbSearchParam, env:0x%x, cls:0x%x",env, cls);

	return cls;
}

/*
 * Class:     com_dvb_DvbSearch
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_DvbSearch_initIDs
  (JNIEnv *env, jclass cls) {

	LOGD("Java_com_ali_dvbdemo_DvbSearch_initIDs");       
        
	MID_DvbSearch_callback = (*env)->GetMethodID(env, cls,
			"callback", "(ILjava/lang/Object;)V");
	if (MID_DvbSearch_callback == NULL) {
		return;
	}

	jclass CLS_DvbSearchParam = getClass_DvbSearchParam(env);

	FID_DvbSearchParam_mFrequencyFrom = (*env)->GetFieldID(env, CLS_DvbSearchParam, "mFrequencyFrom", "I");
	if (FID_DvbSearchParam_mFrequencyFrom == NULL) {
		return;
	}
	FID_DvbSearchParam_mFrequencyTo = (*env)->GetFieldID(env, CLS_DvbSearchParam, "mFrequencyTo", "I");
	if (FID_DvbSearchParam_mFrequencyTo == NULL) {
		return;
	}
	FID_DvbSearchParam_mBandwidth = (*env)->GetFieldID(env, CLS_DvbSearchParam, "mBandwidth", "I");
	if (FID_DvbSearchParam_mBandwidth == NULL) {
		return;
	}
	FID_DvbSearchParam_mSymbolRate = (*env)->GetFieldID(env, CLS_DvbSearchParam, "mSymbolRate", "I");
	if (FID_DvbSearchParam_mSymbolRate == NULL) {
		return;
	}
	FID_DvbSearchParam_mQam = (*env)->GetFieldID(env, CLS_DvbSearchParam, "mQam", "I");
	if (FID_DvbSearchParam_mQam == NULL) {
		return;
	}
	FID_DvbSearchParam_mNitSearch = (*env)->GetFieldID(env, CLS_DvbSearchParam, "mNitSearch", "Z");
	if (FID_DvbSearchParam_mNitSearch == NULL) {
		return;
	}

	FID_DvbSearchParam_mFrontendType = (*env)->GetFieldID(env, CLS_DvbSearchParam, "mFrontendType", "I");
	if (FID_DvbSearchParam_mFrontendType == NULL) {
		return;
	}
	FID_DvbSearchParam_mSearchMethod = (*env)->GetFieldID(env, CLS_DvbSearchParam, "mSearchMethod", "I");
	if (FID_DvbSearchParam_mSearchMethod == NULL) {
		return;
	}
	FID_DvbSearchParam_mFTAonly = (*env)->GetFieldID(env, CLS_DvbSearchParam, "mFTAOnly", "I");
	if (FID_DvbSearchParam_mFTAonly == NULL) {
		return;
	}
	FID_DvbSearchParam_mProgramType = (*env)->GetFieldID(env, CLS_DvbSearchParam, "mProgramType", "I");
	if (FID_DvbSearchParam_mProgramType == NULL) {
		return;
	}
	LOGD("Java_com_ali_dvbdemo_DvbSearch_initIDs end");
}

int getSearchParam(JNIEnv *env, jobject objParam, ALiDVB_SearchParam *searchParam) {
	int i;

	memset(searchParam, 0, sizeof(ALiDVB_SearchParam));

	/* frq_from */
	searchParam->frequency_from = (*env)->GetIntField(env, objParam, FID_DvbSearchParam_mFrequencyFrom);

	/* frq_to */
	searchParam->frequency_to = (*env)->GetIntField(env, objParam, FID_DvbSearchParam_mFrequencyTo);

	/* bandwidth */
	searchParam->bandwidth = (*env)->GetIntField(env, objParam, FID_DvbSearchParam_mBandwidth);

	/* sym */
	searchParam->symbol_rate = (*env)->GetIntField(env, objParam, FID_DvbSearchParam_mSymbolRate);

	/* qam */
	searchParam->modulation = (*env)->GetIntField(env, objParam, FID_DvbSearchParam_mQam);

	/* nit_search */
	jboolean isNit = (*env)->GetBooleanField(env, objParam, FID_DvbSearchParam_mNitSearch);
	if (isNit)
		searchParam->nit_search = 1;
	else
		searchParam->nit_search = 0;

	searchParam->frontend_type = (*env)->GetIntField(env, objParam, FID_DvbSearchParam_mFrontendType);
	searchParam->search_method = (*env)->GetIntField(env, objParam, FID_DvbSearchParam_mSearchMethod);
	searchParam->FTA_only = (*env)->GetIntField(env, objParam, FID_DvbSearchParam_mFTAonly);
	searchParam->program_type = (*env)->GetIntField(env, objParam, FID_DvbSearchParam_mProgramType);
	LOGD("%s,%d type:%d,method=%d\n",__FUNCTION__,__LINE__, searchParam->frontend_type,searchParam->search_method);
	return 0;
}

int jni_searchCallback(int type, void *param)
{
	int ret = 0;
	int exit = 0;
	int isAttached = 0;
	int status;
	JNIEnv *env = NULL;
	int jni_type = -1;

	LOGD("%s,%d type:0x%x",__FUNCTION__,__LINE__, type);

	status = (*gJavaVM)->GetEnv(gJavaVM, &env, JNI_VERSION_1_4);
	if(status < 0) {
		status = (*gJavaVM)->AttachCurrentThread(gJavaVM, &env, NULL);
		if(status < 0) {
			LOGE("%s,%d,callback_handler: failed to attach current thread",__FUNCTION__,__LINE__);
			return -1;
		}
		isAttached = 1;
		//LOGD("%s,%d AttachCurrentThread",__FUNCTION__,__LINE__);
	}

	jobject objParam = NULL;

	if (type == SEARCH_NOTIFY_PROGRESS) {
		LOGD("%s,%d com_dvb_DvbSearch_SEARCH_PROGRESS",__FUNCTION__,__LINE__);

		int progress = *(int*)param;

		jclass CLS_INT = (*env)->FindClass(env, "java/lang/Integer");
		if (CLS_INT == NULL) {
			LOGE("%s,%d,failed to find Integer class",__FUNCTION__,__LINE__);
			ret = -1;
			goto EXIT;
		}
		jmethodID MID_INT_constructor = (*env)->GetMethodID(env, CLS_INT,
				"<init>", "(I)V");
		if (MID_INT_constructor == NULL) {
			LOGE("%s,%d,failed to find Integer constructor",__FUNCTION__,__LINE__);
			ret = -1;
			goto EXIT;
		}

		objParam = (*env)->NewObject(env, CLS_INT, MID_INT_constructor,	progress);
		if (objParam == NULL) {
			LOGE("%s,%d,failed to new Integer",__FUNCTION__,__LINE__);
			ret = -1;
			goto EXIT;
		}
		jni_type = com_dvb_DvbSearch_SEARCH_PROGRESS;
	}
	else if (type == SEARCH_NOTIFY_TP_TUNING) {
		LOGD("%s,%d com_dvb_DvbSearch_SEARCH_TP_TUNING",__FUNCTION__,__LINE__);

		ALiDVB_Frontend *sfe = (ALiDVB_Frontend *)param;
		struct DvbFrontend frontend;

		frontend.ft_type = sfe->type;
		frontend.frq = sfe->frequency;
		frontend.sym = sfe->symbol_rate;
		frontend.qam = sfe->modulation;

		objParam = getFrontendObject(env, &frontend);
		if (objParam == NULL) {
			LOGE("%s,%d,failed to new FrontendObject",__FUNCTION__,__LINE__);
			ret = -1;
			goto EXIT;
		}

		jni_type = com_dvb_DvbSearch_SEARCH_TP_TUNING;
	}
	else if (type == SEARCH_NOTIFY_PROGRAM_ADDED) {
		LOGD("%s,%d com_dvb_DvbSearch_SEARCH_PROGRAM_ADDED",__FUNCTION__,__LINE__);

		ALiDVB_ChannelNode *snode = (ALiDVB_ChannelNode *)param;
		struct DvbChannelNode node;
		int i;

		memset(&node, 0, sizeof(struct DvbChannelNode));
		node.pcr.pcr_pid = snode->pcr_pid;
		node.video.video_pid = snode->video_pid;
		node.video.video_type = snode->video_type;
		node.audio.audio_channel = snode->audio_channel;
		node.audio.audio_volume = snode->audio_volume;
		node.audio.audio_current = snode->audio_current;
		node.audio.audio_count = snode->audio_count;

		for (i=0;i<snode->audio_count;i++)
		{
			node.audio.audio_track[i].audio_pid = snode->audio_track[i].audio_pid;
			node.audio.audio_track[i].audio_type = snode->audio_track[i].audio_type;
			memcpy(node.audio.audio_track[i].audio_lang, snode->audio_track[i].audio_lang, 4);
		}
		node.bouquet.bouquet_count = snode->bouquet_count;
		memcpy(node.bouquet.bouquet_id, snode->bouquet_id, snode->bouquet_count * sizeof(short));
		node.service_id = snode->service_id;
		node.service_type = snode->service_type;
		memcpy(node.service_name, snode->service_name, (MAX_SERVICE_NAME_LENGTH+1)*sizeof(snode->service_name[0]));

		node.sat_id = snode->sat_id;
		node.tp_id = snode->tp_id;
		node.prog_id = snode->prog_id;
		
		objParam = getChannelObject(env, 0, &node);
		if (objParam == NULL) {
			LOGE("%s,%d,failed to new ChannelObject",__FUNCTION__,__LINE__);
			ret = -1;
			goto EXIT;
		}
		jni_type = com_dvb_DvbSearch_SEARCH_PROGRAM_ADDED;
	}
	else if (type == SEARCH_NOTIFY_TP_FULL) {
		LOGD("%s,%d com_dvb_DvbSearch_SEARCH_TP_FULL",__FUNCTION__,__LINE__);

		jni_type = com_dvb_DvbSearch_SEARCH_TP_FULL;
	}
	else if (type == SEARCH_NOTIFY_PROGRAM_FULL) {
		LOGD("%s,%d com_dvb_DvbSearch_SEARCH_PROGRAM_FULL",__FUNCTION__,__LINE__);

		jni_type = com_dvb_DvbSearch_SEARCH_PROGRAM_FULL;
	}
	else if (type == SEARCH_NOTIFY_ASCOMPLETE) {
		LOGD("com_dvb_DvbSearch_SEARCH_COMPLETE");
		exit = 1;

		jni_type = com_dvb_DvbSearch_SEARCH_COMPLETE;
	}
	else if (type == SEARCH_NOTIFY_ASSTOP) {
		LOGD("com_dvb_DvbSearch_SEARCH_STOP");
		exit = 1;

		jni_type = com_dvb_DvbSearch_SEARCH_STOP;
	}

      if(jni_type >= 0)
      {
        	jclass CLS_DvbSearch = (*env)->GetObjectClass(env, gDvbSearchObject);
        	if(CLS_DvbSearch == NULL){
        		LOGE("%s,%d,callback_handler: failed to get class reference",__FUNCTION__,__LINE__);
        		goto EXIT;
        	}

                LOGD("####%s,%d CallStaticVoidMethod...",__FUNCTION__,__LINE__);
                
        	(*env)->CallVoidMethod(env, gDvbSearchObject, MID_DvbSearch_callback, jni_type, objParam);
      }

EXIT:
	if (exit) {
              LOGD("%s,%d try to exit...",__FUNCTION__,__LINE__);		

		(*env)->DeleteGlobalRef(env, gDvbSearchObject);
		//releaseChannelGlobalReference(env);

              LOGD("%s,%d exit done!,isAttached=%d",__FUNCTION__,__LINE__,isAttached);
	}

	if(isAttached)	{
		LOGD("%s,%d DetachCurrentThread",__FUNCTION__,__LINE__);
		(*gJavaVM)->DetachCurrentThread(gJavaVM);
	}

	return ret;
}

/*
 * Class:     com_dvb_DvbSearch
 * Method:    start
 * Signature: (Lcom/dvb/DvbSearchParam;)I
 */
JNIEXPORT jint JNICALL Java_DvbSearch_start
  (JNIEnv *env, jobject obj, jobject objParam) {
	int ret;
	ALiDVB_SearchParam searchParam;
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	getSearchParam(env, objParam, &searchParam);

	gDvbSearchObject = (*env)->NewGlobalRef(env, obj);
	//getChannelGlobalReference(env);

	LOGD("%s(%d, %d, %d, %d, %d, %d)\n", __FUNCTION__, searchParam.frequency_from, searchParam.frequency_to, searchParam.bandwidth, searchParam.symbol_rate ,searchParam.modulation, searchParam.nit_search);

	ret = ALiDVB_SearchStart(&searchParam, jni_searchCallback);

	return ret;
}

/*
 * Class:     com_dvb_DvbSearch
 * Method:    stop
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_DvbSearch_stop
  (JNIEnv *env, jclass obj) {
	int ret;
LOGD("%s,%d",__FUNCTION__,__LINE__);
	ret = ALiDVB_SearchStop();

	return ret;
}

