#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#include "com_dvb_DvbChannel.h"
#include "channelNode.h"
#include "com_alitech_dvbcls_path.h"

#include "alidvb_channelnode.h"

#define  LOG_TAG    "libdvbchannel"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

jmethodID MID_DvbChannelNode_constructor;
jmethodID MID_DvbFrontend_constructor;
jmethodID MID_DvbPcr_constructor;
jmethodID MID_DvbVideo_constructor;
jmethodID MID_DvbAudio_constructor;
jmethodID MID_DvbAudioTrack_constructor;
jmethodID MID_DvbBouquet_constructor;

jfieldID FID_DvbPcr_mPcrPid;
jfieldID FID_DvbVideo_mVideoType;
jfieldID FID_DvbVideo_mVideoPid;
jfieldID FID_DvbAudioTrack_mAudioPid;
jfieldID FID_DvbAudioTrack_mAudioType;
jfieldID FID_DvbAudioTrack_mAudioLang;
jfieldID FID_DvbAudio_mAudioChannel;
jfieldID FID_DvbAudio_mAudioVolume;
jfieldID FID_DvbAudio_mAudioTrackIdx;
jfieldID FID_DvbAudio_mAudioTrack;
jfieldID FID_DvbBouquet_mBouquetId;

jfieldID FID_DvbFrontend_mType;
jfieldID FID_DvbFrontend_mQam;
jfieldID FID_DvbFrontend_mFrequency;
jfieldID FID_DvbFrontend_mSymbolRate;

jfieldID FID_DvbChannelNode_mFrontend;
jfieldID FID_DvbChannelNode_mPcr;
jfieldID FID_DvbChannelNode_mVideo;
jfieldID FID_DvbChannelNode_mAudio;
jfieldID FID_DvbChannelNode_mBouquet;
jfieldID FID_DvbChannelNode_mTpId;
jfieldID FID_DvbChannelNode_mServiceId;
jfieldID FID_DvbChannelNode_mServiceType;
jfieldID FID_DvbChannelNode_mScramble;
jfieldID FID_DvbChannelNode_mLock;
jfieldID FID_DvbChannelNode_mFavorite;
jfieldID FID_DvbChannelNode_mObjectId;
jfieldID FID_DvbChannelNode_mObjectName;

jclass getClass_DvbChannelNode(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbChannelNodePath);
	if (cls == NULL) {
		LOGE("%s,%d,DvbChannelNode: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}

jclass getClass_DvbFrontend(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbFrontendPath);
	if (cls == NULL) {
		LOGE("%s,%d,DvbFrontend: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}

jclass getClass_DvbPcr(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbPcrPath);
	if (cls == NULL) {
		LOGE("%s,%d,DvbPcr: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}

jclass getClass_DvbVideo(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbVideoPath);
	if (cls == NULL) {
		LOGE("%s,%d,DvbVideo: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}

jclass getClass_DvbAudio(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbAudioPath);
	if (cls == NULL) {
		LOGE("%s,%d,DvbAudio: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}

jclass getClass_DvbAudioTrack(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbAudioTrackPath);
	if (cls == NULL) {
		LOGE("%s,%d,DvbAudioTrack: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}

jclass getClass_DvbBouquet(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbBouquetPath);
	if (cls == NULL) {
		LOGE("%s,%d,DvbBouquet: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}

/*
 * Class:     com_dvb_DvbChannel
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_DvbChannel_initIDs
  (JNIEnv *env, jclass cls) {

	LOGD("%s,%d",__FUNCTION__,__LINE__);

	jclass CLS_DvbChannelNode = getClass_DvbChannelNode(env);
	if (CLS_DvbChannelNode == NULL) {
              LOGE("%s,%d:get CLS_DvbChannelNode null",__FUNCTION__,__LINE__);
		return;
	}

       FID_DvbChannelNode_mFrontend = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mFrontend",
			Class_Sig_DvbFrontend);
	if (FID_DvbChannelNode_mFrontend == NULL) {
		return;
	}
	FID_DvbChannelNode_mPcr = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mPcr",
			Class_Sig_DvbPcr);
	if (FID_DvbChannelNode_mPcr == NULL) {
		return;
	}
	FID_DvbChannelNode_mVideo = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mVideo",
			Class_Sig_DvbVideo);
	if (FID_DvbChannelNode_mVideo == NULL) {
		return;
	}
	FID_DvbChannelNode_mAudio = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mAudio",
			Class_Sig_DvbAudio);
	if (FID_DvbChannelNode_mAudio == NULL) {
		return;
	}
	FID_DvbChannelNode_mBouquet = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mBouquet",
			Class_Sig_DvbBouquet);
	if (FID_DvbChannelNode_mBouquet == NULL) {
		return;
	}
	FID_DvbChannelNode_mTpId = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mTpId", "I");
	if (FID_DvbChannelNode_mTpId == NULL) {
		return;
	}
	FID_DvbChannelNode_mServiceId = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mServiceId", "I");
	if (FID_DvbChannelNode_mServiceId == NULL) {
		return;
	}
	FID_DvbChannelNode_mServiceType = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mServiceType", "I");
	if (FID_DvbChannelNode_mServiceType == NULL) {
		return;
	}
	FID_DvbChannelNode_mFavorite = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mFavorite", "Z");
	if (FID_DvbChannelNode_mFavorite == NULL) {
		return;
	}
	FID_DvbChannelNode_mScramble = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mScramble", "Z");
	if (FID_DvbChannelNode_mScramble == NULL) {
		return;
	}
	FID_DvbChannelNode_mLock = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mLock", "Z");
	if (FID_DvbChannelNode_mLock == NULL) {
		return;
	}
	FID_DvbChannelNode_mObjectId = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mObjectId", "I");
	if (FID_DvbChannelNode_mObjectId == NULL) {
		return;
	}
	FID_DvbChannelNode_mObjectName = (*env)->GetFieldID(env, CLS_DvbChannelNode, "mObjectName",
			"Ljava/lang/String;");
	if (FID_DvbChannelNode_mObjectName == NULL) {
		return;
	}
	jclass CLS_DvbFrontend = getClass_DvbFrontend(env);
	if (CLS_DvbFrontend == NULL) {
		return;
	}
	jclass CLS_DvbPcr = getClass_DvbPcr(env);
	if (CLS_DvbPcr == NULL) {
		return;
	}
	jclass CLS_DvbVideo = getClass_DvbVideo(env);
	if (CLS_DvbVideo == NULL) {
		return;
	}
	jclass CLS_DvbAudio = getClass_DvbAudio(env);
	if (CLS_DvbAudio == NULL) {
		return;
	}
	jclass CLS_DvbAudioTrack = getClass_DvbAudioTrack(env);
	if (CLS_DvbAudioTrack == NULL) {
		return;
	}
	jclass CLS_DvbBouquet = getClass_DvbBouquet(env);
	if (CLS_DvbBouquet == NULL) {
		return;
	}

	MID_DvbChannelNode_constructor = (*env)->GetMethodID(env, CLS_DvbChannelNode,
			"<init>", Class_Sig_Con_DvbChannelNode);
    
	if (MID_DvbChannelNode_constructor == NULL) {
		return;
	}
	MID_DvbFrontend_constructor = (*env)->GetMethodID(env, CLS_DvbFrontend,
			"<init>", "(IIII)V");
	if (MID_DvbFrontend_constructor == NULL) {
		return;
	}
	MID_DvbPcr_constructor = (*env)->GetMethodID(env, CLS_DvbPcr,
			"<init>", "(S)V");
	if (MID_DvbPcr_constructor == NULL) {
		return;
	}
	MID_DvbVideo_constructor = (*env)->GetMethodID(env, CLS_DvbVideo,
			"<init>", "(SS)V");
	if (MID_DvbVideo_constructor == NULL) {
		return;
	}
	MID_DvbAudio_constructor = (*env)->GetMethodID(env, CLS_DvbAudio,
			"<init>", Class_Sig_Con_DvbAudio);
	if (MID_DvbAudio_constructor == NULL) {
		return;
	}
	MID_DvbAudioTrack_constructor = (*env)->GetMethodID(env, CLS_DvbAudioTrack,
				"<init>", "(SSLjava/lang/String;)V");
	if (MID_DvbAudioTrack_constructor == NULL) {
		return;
	}
	MID_DvbBouquet_constructor = (*env)->GetMethodID(env, CLS_DvbBouquet,
			"<init>", "([S)V");
	if (MID_DvbBouquet_constructor == NULL) {
		return;
	}
	FID_DvbPcr_mPcrPid = (*env)->GetFieldID(env, CLS_DvbPcr, "mPcrPid", "S");
	if (FID_DvbPcr_mPcrPid == NULL) {
		return;
	}
	FID_DvbVideo_mVideoType = (*env)->GetFieldID(env, CLS_DvbVideo, "mVideoType", "S");
	if (FID_DvbVideo_mVideoType == NULL) {
		return;
	}
	FID_DvbVideo_mVideoPid = (*env)->GetFieldID(env, CLS_DvbVideo, "mVideoPid", "S");
	if (FID_DvbVideo_mVideoPid == NULL) {
		return;
	}
	FID_DvbAudioTrack_mAudioPid = (*env)->GetFieldID(env, CLS_DvbAudioTrack, "mAudioPid", "S");
	if (FID_DvbAudioTrack_mAudioPid == NULL) {
		return;
	}
	FID_DvbAudioTrack_mAudioType = (*env)->GetFieldID(env, CLS_DvbAudioTrack, "mAudioType", "S");
	if (FID_DvbAudioTrack_mAudioType == NULL) {
		return;
	}
	FID_DvbAudioTrack_mAudioLang = (*env)->GetFieldID(env, CLS_DvbAudioTrack, "mAudioLang",
			"Ljava/lang/String;");
	if (FID_DvbAudioTrack_mAudioLang == NULL) {
		return;
	}
	FID_DvbAudio_mAudioChannel = (*env)->GetFieldID(env, CLS_DvbAudio, "mAudioChannel", "S");
	if (FID_DvbAudio_mAudioChannel == NULL) {
		return;
	}
	FID_DvbAudio_mAudioVolume = (*env)->GetFieldID(env, CLS_DvbAudio, "mAudioVolume", "S");
	if (FID_DvbAudio_mAudioVolume == NULL) {
		return;
	}
	FID_DvbAudio_mAudioTrackIdx = (*env)->GetFieldID(env, CLS_DvbAudio, "mAudioTrackIdx", "S");
	if (FID_DvbAudio_mAudioTrackIdx == NULL) {
		return;
	}
	FID_DvbAudio_mAudioTrack = (*env)->GetFieldID(env, CLS_DvbAudio, "mAudioTrack",
			Class_Sig_DvbAudioTrack);
	if (FID_DvbAudio_mAudioTrack == NULL) {
		return;
	}
	FID_DvbBouquet_mBouquetId = (*env)->GetFieldID(env, CLS_DvbBouquet, "mBouquetId", "[S");
	if (FID_DvbBouquet_mBouquetId == NULL) {
		return;
	}
	FID_DvbFrontend_mType = (*env)->GetFieldID(env, CLS_DvbFrontend, "mType", "I");
	if (FID_DvbFrontend_mType == NULL) {
		return;
	}
	FID_DvbFrontend_mQam = (*env)->GetFieldID(env, CLS_DvbFrontend, "mQam", "I");
	if (FID_DvbFrontend_mQam == NULL) {
		return;
	}
	FID_DvbFrontend_mFrequency = (*env)->GetFieldID(env, CLS_DvbFrontend, "mFrequency", "I");
	if (FID_DvbFrontend_mFrequency == NULL) {
		return;
	}
	FID_DvbFrontend_mSymbolRate = (*env)->GetFieldID(env, CLS_DvbFrontend, "mSymbolRate", "I");
	if (FID_DvbFrontend_mSymbolRate == NULL) {
		return;
	}

}

jclass CLS_DvbAudioTrack = NULL;
jclass CLS_DvbAudio = NULL;
jclass CLS_DvbBouquet = NULL;
jclass CLS_DvbFrontend = NULL;
jclass CLS_DvbChannelNode = NULL;
jclass CLS_DvbPcr = NULL;
jclass CLS_DvbVideo = NULL;

int getChannelGlobalReference(JNIEnv *env) {
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	jclass cls = getClass_DvbChannelNode(env);
	if (cls == NULL) {
		return -1;
	}
	CLS_DvbChannelNode = (*env)->NewGlobalRef(env, cls);
	if (CLS_DvbChannelNode == NULL) {
		LOGE("%s,%d,CLS_DvbChannelNode: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}

	cls = getClass_DvbFrontend(env);
	if (cls == NULL) {
		return -1;
	}
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	CLS_DvbFrontend = (*env)->NewGlobalRef(env, cls);
	if (CLS_DvbFrontend == NULL) {
		LOGE("%s,%d,CLS_DvbFrontend: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}

	cls = getClass_DvbPcr(env);
	if (cls == NULL) {
		return -1;
	}
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	CLS_DvbPcr = (*env)->NewGlobalRef(env, cls);
	if (CLS_DvbPcr == NULL) {
		LOGE("%s,%d,CLS_DvbPcr: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}

	cls = getClass_DvbVideo(env);
	if (cls == NULL) {
		return -1;
	}
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	CLS_DvbVideo = (*env)->NewGlobalRef(env, cls);
	if (CLS_DvbVideo == NULL) {
		LOGE("%s,%d,CLS_DvbVideo: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}

	cls = getClass_DvbAudio(env);
	if (cls == NULL) {
		return -1;
	}
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	CLS_DvbAudio = (*env)->NewGlobalRef(env, cls);
	if (CLS_DvbAudio == NULL) {
		LOGE("%s,%d,CLS_DvbAudio: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}

	cls = getClass_DvbAudioTrack(env);
	if (cls == NULL) {
		return -1;
	}
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	CLS_DvbAudioTrack = (*env)->NewGlobalRef(env, cls);
	if (CLS_DvbAudioTrack == NULL) {
		LOGE("%s,%d,CLS_DvbAudioTrack: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}

	cls = getClass_DvbBouquet(env);
	if (cls == NULL) {
		return -1;
	}
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	CLS_DvbBouquet = (*env)->NewGlobalRef(env, cls);
	if (CLS_DvbBouquet == NULL) {
		LOGE("%s,%d,CLS_DvbBouquet: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}

	LOGD("%s,%d ok",__FUNCTION__,__LINE__);

	return 0;
}

int releaseChannelGlobalReference(JNIEnv *env) {

	LOGD("%s,%d",__FUNCTION__,__LINE__);

	if(CLS_DvbAudioTrack)
		(*env)->DeleteGlobalRef(env, CLS_DvbAudioTrack);

	if(CLS_DvbAudio)
		(*env)->DeleteGlobalRef(env, CLS_DvbAudio);

	if(CLS_DvbBouquet)
		(*env)->DeleteGlobalRef(env, CLS_DvbBouquet);

	if(CLS_DvbFrontend)
		(*env)->DeleteGlobalRef(env, CLS_DvbFrontend);

	if(CLS_DvbChannelNode)
		(*env)->DeleteGlobalRef(env, CLS_DvbChannelNode);

	if(CLS_DvbPcr)
		(*env)->DeleteGlobalRef(env, CLS_DvbPcr);

	if(CLS_DvbVideo)
		(*env)->DeleteGlobalRef(env, CLS_DvbVideo);

	return 0;
}

jobject getFrontendObject(JNIEnv *env, struct DvbFrontend *frontend) {
	/* frontend */
	jobject obj = (*env)->NewObject(env, CLS_DvbFrontend, MID_DvbFrontend_constructor,
			frontend->ft_type, frontend->qam, frontend->frq, frontend->sym);

	return obj;
}

unsigned short ComMB16ToUINT16(unsigned char* pVal)
{
	unsigned short wRes=0;

	if(pVal == NULL)
		return 0;

 #if(defined(SYS_CPU_ENDIAN) &&  SYS_CPU_ENDIAN==ENDIAN_BIG)
	wRes = *pVal;
#else
	wRes=(unsigned short)((0xff00&(*pVal<<8))|(0x00ff&(*(pVal+1))));
#endif
	return wRes;	
}

int getUnicodeString(short* src, short *dest)
{
    int length = 0;
    while (0 !=( (*dest)=ComMB16ToUINT16((unsigned char*)src)))
    {
        src ++;
        dest ++;
        length++;
    }    
    //LOGD("%s,%d,len %d",__FUNCTION__,__LINE__,length);
    return length;
}

jobject getChannelObject(JNIEnv *env, int index, struct DvbChannelNode *node) {
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	/* audio tracks */
	jobjectArray trackArr = (*env)->NewObjectArray(env, node->audio.audio_count, CLS_DvbAudioTrack, NULL);
	if (trackArr == NULL) {
		LOGE("%s,%d,trackArr: failed to new object array",__FUNCTION__,__LINE__);
		return NULL;
	}

	int i,j;

	for (j=0; j<node->audio.audio_count; j++) {
		jobject audiotrack;
		jstring audiolang;
		
		node->audio.audio_track[j].audio_lang[3] = 0;
		for( i = 0; i < 3; i++) {
			if(node->audio.audio_track[j].audio_lang[i] > 127)
				node->audio.audio_track[j].audio_lang[i] = 0;
		}
		audiolang = (*env)->NewStringUTF(env, node->audio.audio_track[j].audio_lang);
		audiotrack = (*env)->NewObject(env, CLS_DvbAudioTrack, MID_DvbAudioTrack_constructor,
				node->audio.audio_track[j].audio_pid, node->audio.audio_track[j].audio_type, audiolang);

		(*env)->SetObjectArrayElement(env, trackArr, j, audiotrack);

		(*env)->DeleteLocalRef(env, audiolang);
		(*env)->DeleteLocalRef(env, audiotrack);
	}


	/* audio */
	jobject audio = (*env)->NewObject(env, CLS_DvbAudio, MID_DvbAudio_constructor,
			node->audio.audio_channel, node->audio.audio_volume, node->audio.audio_current, trackArr);
	if (trackArr != NULL) {
		(*env)->DeleteLocalRef(env, trackArr);
	}

	/* bouquet */
	jshortArray sarr = (*env)->NewShortArray(env, node->bouquet.bouquet_count);
	if (sarr == NULL) {
		LOGE("%s,%d,sarr: failed to new short array",__FUNCTION__,__LINE__);
		return  NULL;
	}

	(*env)->SetShortArrayRegion(env, sarr,
			0, node->bouquet.bouquet_count,node->bouquet.bouquet_id);
       
	jobject bouquet = (*env)->NewObject(env, CLS_DvbBouquet, MID_DvbBouquet_constructor,
		sarr);
	if (sarr != NULL) {
		(*env)->DeleteLocalRef(env, sarr);
	}

	/* frontend */
	jobject frontend = getFrontendObject(env, &node->frontend);

	/* pcr */
	jobject pcr = (*env)->NewObject(env, CLS_DvbPcr, MID_DvbPcr_constructor,
			node->pcr.pcr_pid);

	/* video */
	jobject video = (*env)->NewObject(env, CLS_DvbVideo, MID_DvbVideo_constructor,
			node->video.video_type, node->video.video_pid);
        
	/* name */
	//node->service_name[MAX_SERVICE_NAME_LENGTH] = 0;
       unsigned short uniname[MAX_SERVICE_NAME_LENGTH+1];
       int unilen;
       
       unilen = getUnicodeString(node->service_name, uniname);
	jstring name = (*env)->NewString(env, uniname, unilen);

	/* number */
	char buf[10];
	sprintf(buf, "%d",index+1);
	jstring number = (*env)->NewStringUTF(env, buf);

	jboolean isFav = (node->favorite == 0)? JNI_FALSE : JNI_TRUE;
	jboolean isLock = (node->lock == 0)? JNI_FALSE : JNI_TRUE;
	jboolean isScramble = (node->scramble == 0)? JNI_FALSE : JNI_TRUE;

	/* channel node */
	jobject channel = (*env)->NewObject(env, CLS_DvbChannelNode, MID_DvbChannelNode_constructor,
			node->prog_id, name, number,
			frontend, pcr, video, audio,
			bouquet, node->tp_id, node->service_id, node->service_type,
			isScramble, isLock, isFav);

	(*env)->DeleteLocalRef(env, name);

	(*env)->DeleteLocalRef(env, number);

	(*env)->DeleteLocalRef(env, frontend);

	(*env)->DeleteLocalRef(env, pcr);

	(*env)->DeleteLocalRef(env, video);

	(*env)->DeleteLocalRef(env, audio);

	(*env)->DeleteLocalRef(env, bouquet);

	return channel;
}

int getChannelNode(JNIEnv *env, jobject channel, struct DvbChannelNode *node) {
	int i;

	memset(node, 0, sizeof(struct DvbChannelNode));

	/* audio */
	jobject audio = (*env)->GetObjectField(env, channel, FID_DvbChannelNode_mAudio);
	node->audio.audio_channel = (*env)->GetShortField(env, audio, FID_DvbAudio_mAudioChannel);
	node->audio.audio_volume = (*env)->GetShortField(env, audio, FID_DvbAudio_mAudioVolume);
	node->audio.audio_current = (*env)->GetShortField(env, audio, FID_DvbAudio_mAudioTrackIdx);

	/* audio tracks */
	jobjectArray trackArr = (*env)->GetObjectField(env, audio, FID_DvbAudio_mAudioTrack);
	node->audio.audio_count = (*env)->GetArrayLength(env, trackArr);
	for (i=0; i<node->audio.audio_count; i++) {
		jobject track = (*env)->GetObjectArrayElement(env, trackArr, i);
		if (track != NULL) {
			node->audio.audio_track[i].audio_pid = (*env)->GetShortField(env, track, FID_DvbAudioTrack_mAudioPid);
			node->audio.audio_track[i].audio_type = (*env)->GetShortField(env, track, FID_DvbAudioTrack_mAudioType);
			jstring audio_lang = (*env)->GetObjectField(env, track, FID_DvbAudioTrack_mAudioLang);
			int len = (*env)->GetStringLength(env, audio_lang);
			(*env)->GetStringUTFRegion(env, audio_lang, 0, len, node->audio.audio_track[i].audio_lang);
		}
		(*env)->DeleteLocalRef(env, track);
	}

	/* bouquet */
	jobject bouquet = (*env)->GetObjectField(env, channel, FID_DvbChannelNode_mBouquet);
	jshortArray sarr = (*env)->GetObjectField(env, bouquet, FID_DvbBouquet_mBouquetId);
	node->bouquet.bouquet_count = (*env)->GetArrayLength(env, sarr);
	(*env)->GetShortArrayRegion(env, sarr, 0, node->bouquet.bouquet_count, node->bouquet.bouquet_id);

	/* frontend */
	jobject frontend = (*env)->GetObjectField(env, channel, FID_DvbChannelNode_mFrontend);
	node->frontend.ft_type = (*env)->GetIntField(env, frontend, FID_DvbFrontend_mType);
	node->frontend.qam = (*env)->GetIntField(env, frontend, FID_DvbFrontend_mQam);
	node->frontend.frq = (*env)->GetIntField(env, frontend, FID_DvbFrontend_mFrequency);
	node->frontend.sym = (*env)->GetIntField(env, frontend, FID_DvbFrontend_mSymbolRate);

	/* pcr */
	jobject pcr = (*env)->GetObjectField(env, channel, FID_DvbChannelNode_mPcr);
	node->pcr.pcr_pid = (*env)->GetShortField(env, pcr, FID_DvbPcr_mPcrPid);

	/* video */
	jobject video = (*env)->GetObjectField(env, channel, FID_DvbChannelNode_mVideo);
	node->video.video_type = (*env)->GetShortField(env, video, FID_DvbVideo_mVideoType);
	node->video.video_pid = (*env)->GetShortField(env, video, FID_DvbVideo_mVideoPid);

	/* service name */
	jstring name = (*env)->GetObjectField(env, channel, FID_DvbChannelNode_mObjectName);
	int name_len = (*env)->GetStringUTFLength(env, name);
	(*env)->GetStringUTFRegion(env, name, 0, name_len, (char *)node->service_name);

	/* sat_id */
	node->sat_id = 1;

	/* tp_id */
	node->tp_id = (*env)->GetIntField(env, channel, FID_DvbChannelNode_mTpId);

	/* prog id */
	node->prog_id = (*env)->GetIntField(env, channel, FID_DvbChannelNode_mObjectId);

	/* servive id */
	node->service_id = (*env)->GetIntField(env, channel, FID_DvbChannelNode_mServiceId);

	/* servive type */
	node->service_type = (*env)->GetIntField(env, channel, FID_DvbChannelNode_mServiceType);

	/* favorite */
	jboolean isFav = (*env)->GetBooleanField(env, channel, FID_DvbChannelNode_mFavorite);
	if (isFav)
		node->favorite = 1;
	else
		node->favorite = 0;

	/* scramble */
	jboolean isScramble = (*env)->GetBooleanField(env, channel, FID_DvbChannelNode_mScramble);
	if (isScramble)
			node->scramble = 1;
		else
			node->scramble = 0;

	/* lock */
	jboolean isLock = (*env)->GetBooleanField(env, channel, FID_DvbChannelNode_mLock);
	if (isLock)
			node->lock = 1;
		else
			node->lock = 0;
	return 0;
}

int getEPGInfo(JNIEnv *env, jobject channel, jint *tp_id, jshort *service_id) 
{

LOGD("%s,tp_id",__FUNCTION__);
	/* tp_id */
	*tp_id = (*env)->GetIntField(env, channel, FID_DvbChannelNode_mTpId);
LOGD("%s,servive id ",__FUNCTION__);
	/* servive id */
	*service_id = (*env)->GetIntField(env, channel, FID_DvbChannelNode_mServiceId);
	return 0;
}

static int ChannelNodeConvert(struct DvbChannelNode *dnode, ALiDVB_ChannelNode *snode)
{
	int i;

	memset(dnode, 0, sizeof(struct DvbChannelNode));

	dnode->frontend.ft_type = snode->frontend.type;
	dnode->frontend.frq = snode->frontend.frequency;
	dnode->frontend.sym = snode->frontend.symbol_rate;
	dnode->frontend.qam = snode->frontend.modulation;

	dnode->pcr.pcr_pid = snode->pcr_pid;
	dnode->video.video_pid = snode->video_pid;
	dnode->video.video_type = snode->video_type;
	dnode->audio.audio_channel = snode->audio_channel;
	dnode->audio.audio_volume = snode->audio_volume;
	dnode->audio.audio_current = snode->audio_current;
	dnode->audio.audio_count = snode->audio_count;
		
	for (i=0;i<snode->audio_count;i++)
	{
		dnode->audio.audio_track[i].audio_pid = snode->audio_track[i].audio_pid;
		dnode->audio.audio_track[i].audio_type = snode->audio_track[i].audio_type;
		memcpy(dnode->audio.audio_track[i].audio_lang, snode->audio_track[i].audio_lang, 4);
	}
	
	dnode->pcr.pcr_pid = snode->pcr_pid;
	dnode->bouquet.bouquet_count = snode->bouquet_count;
	
	for (i = 0; i < snode->bouquet_count; i++)
	{
		dnode->bouquet.bouquet_id[i] = snode->bouquet_id[i];
	}
	
	if(snode->bouquet_count )
	{
		memcpy(dnode->bouquet.bouquet_id, snode->bouquet_id, snode->bouquet_count * sizeof(short));
	}
	
	dnode->service_id = snode->service_id;
	dnode->service_type = snode->service_type;
	memcpy(dnode->service_name, snode->service_name, (MAX_SERVICE_NAME_LENGTH+1)*sizeof(snode->service_name[0]));	
	dnode->sat_id = snode->sat_id;
	dnode->tp_id = snode->tp_id;
	dnode->prog_id = snode->prog_id;

	return 0;
}

/*
 * Class:     com_dvb_DvbChannel
 * Method:    loadChannels
 * Signature: (I)[Lcom/dvb/DvbChannelNode;
 */
JNIEXPORT jobjectArray JNICALL Java_DvbChannel_loadChannels
  (JNIEnv *env, jclass cls, jint group) {
	int view_type = (group&com_dvb_DvbChannel_CHAN_GROUP_MASK);
	int service_type = (group&com_dvb_DvbChannel_CHAN_MODE_MASK);
	int param = (group&com_dvb_DvbChannel_CHAN_GROUP_PARAM_MASK);
	int count;

	LOGD("%s,%d",__FUNCTION__,__LINE__);

	count = ALiDVB_CreateGroup(view_type, service_type, param);
	
	if (count <= 0) 
	{
		LOGD("%s,%d,count=%d\n",__FUNCTION__,__LINE__,count);
		return NULL;
	}

	//getChannelGlobalReference(env);
	
	jobjectArray result = (*env)->NewObjectArray(env, count, CLS_DvbChannelNode, NULL);
	if (result == NULL) {
		LOGE("new objectarray fail.");
		goto EXIT;
	}
	
	int i;
	for (i=0; i<count; i++) {
		struct DvbChannelNode node;
		ALiDVB_ChannelNode snode;
		if (ALiDVB_GetChannel(i, &snode) ) {
			continue;			
		}

		//LOGD("%s,%d",__FUNCTION__,__LINE__);
		ChannelNodeConvert(&node, &snode);

		//LOGD("%s,%d",__FUNCTION__,__LINE__);
		jobject channel = getChannelObject(env, i, &node);
		//LOGD("%s,%d",__FUNCTION__,__LINE__);
		(*env)->SetObjectArrayElement(env, result, i, channel);
		(*env)->DeleteLocalRef(env, channel);
	}

EXIT:
	//releaseChannelGlobalReference(env);//不同线程可能同时调用，放到so卸载时销毁
	LOGD("%s,%d:end...",__FUNCTION__,__LINE__);
	return result;
}

/*
 * Class:     com_dvb_DvbChannel
 * Method:    updateChannel
 * Signature: (Lcom/dvb/DvbChannelNode;)I
 */
JNIEXPORT jint JNICALL Java_DvbChannel_updateChannel
  (JNIEnv *env, jclass cls, jobject channel) {
	struct DvbChannelNode node;

	LOGD("%s,%d",__FUNCTION__,__LINE__);

	getChannelNode(env, channel, &node);

	//chan_update_channel(&node);
}
