#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <alidvb/ams_inc/api/libca/udrm.h>

#include "com_alitech_dvbcls_path.h"
#include "com_dvb_DvbChannel.h"
#include "com_dvb_DvbSearch.h"
#include "com_dvb_DvbSystem.h"
#include "com_dvb_DvbPlayer.h"
#include "com_dvb_DvbEpg.h"
#include "com_dvb_DvbSatellite.h"
#include "com_dvb_DvbSystemSetting.h"
#include "com_dvb_DvbUdrm.h"
#include "com_property.h"

#include "system.h"
#include "alidvb_system.h"
#include "alidvb/board_config_cstm.h"

#define  LOG_TAG    "libdvbsystem"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
extern void Java_DvbUdrm_callback(UTI_UINT32 msg_type,UTI_UINT32 msg_code,UTI_UINT32 utc, UTI_UINT8* title, UTI_UINT8*  contend);

JavaVM *gJavaVM = NULL;

static JNINativeMethod g_DvbChannel_Methods[] = {
        {"initIDs", "()V",(void*)Java_DvbChannel_initIDs},
        {"loadChannels", Native_Sig_DvbChannel_loadChannels, (void*)Java_DvbChannel_loadChannels},
        {"updateChannel", Native_Sig_DvbChannel_updateChannel, (void *)Java_DvbChannel_updateChannel},
 };

static JNINativeMethod g_DvbSearch_Methods[] = {
        {"initIDs", "()V",(void*)Java_DvbSearch_initIDs},
        {"start", Native_Sig_DvbSearch_start, (void*)Java_DvbSearch_start},
        {"stop", "()I", (void *)Java_DvbSearch_stop},
 };

static JNINativeMethod g_DvbUdrm_Methods[] = {

		{"getUdrmPpcNum","()I",(void*)Java_DvbUdrm_getUdrmPpcNum},
		{"getUdrmPpcId","(I)I",(void*)Java_DvbUdrm_getUdrmPpcId},
		{"getUdrmEmailInfo","()[Lcom/alitech/dvb/DvbUdrmInfo$Email;",(void*)Java_DvbUdrm_getUdrmEmailInfo},
		{"deleteUdrmEmail","(I)Z",(void*)Java_DvbUdrm_deleteUdrmEmail},
		{"setUdrmWatchClass","(ILjava/lang/String;)Z",(void*)Java_DvbUdrm_setUdrmWatchClass},
		{"getUdrmWatchClass","()I",(void*)Java_DvbUdrm_getUdrmWatchClass},
		{"setUdrmPassword","(Ljava/lang/String;Ljava/lang/String;)Z",(void*)Java_DvbUdrm_setUdrmPassword},
		{"checkUdrmPassword","(Ljava/lang/String;)Z",(void*)Java_DvbUdrm_checkUdrmPassword},
		{"getUdrmInfo","()Lcom/alitech/dvb/DvbUdrmInfo;",(void*)Java_DvbUdrm_getinfo},

};


static JNINativeMethod g_DvbEpg_Methods[] = {
        {"initIDs", "()V",(void*)Java_com_dvb_DvbEpg_initIDs},
        {"getStreamTime", "(I)Lcom/alitech/dvb/DvbTime;",(void*)Java_com_dvb_DvbEpg_getStreamTime},
        {"setActiveService", Native_Sig_DvbEpg_setActiveService, (void*)Java_com_dvb_DvbEpg_setActiveService},
        {"delService", Native_Sig_DvbEpg_delService, (void*)Java_com_dvb_DvbEpg_delService},
        {"getPresentEvent", Native_Sig_DvbEpg_getPresentEvent, (void*)Java_com_dvb_DvbEpg_getPresentEvent},
        {"getFollowingEvent", Native_Sig_DvbEpg_getFollowingEvent, (void*)Java_com_dvb_DvbEpg_getFollowingEvent},
        {"loadScheduleEvent", Native_Sig_DvbEpg_loadScheduleEvent, (void*)Java_com_dvb_DvbEpg_loadScheduleEvent},
        {"getScheduleEvent", Native_Sig_DvbEpg_getScheduleEvent, (void*)Java_com_dvb_DvbEpg_getScheduleEvent},
 };

static JNINativeMethod g_DvbSatellite_Methods[] = {
        {"initIDs", "()V",(void*)Java_DvbSatellite_initIDs},
        {"loadSatelliteNodes", Native_Sig_DvbSatellite_loadSatelliteNodes, (void*)Java_DvbSatellite_loadSatelliteNodes},
        {"updateSatellite", Native_Sig_DvbSatellite_updateSatellite, (void *)Java_DvbSatellite_updateSatellite},
        {"loadTpNodes", Native_Sig_DvbSatellite_loadTpNodes, (void*)Java_DvbSatellite_loadTpNodes},
        {"updateTpNode", Native_Sig_DvbSatellite_updateTpNode, (void *)Java_DvbSatellite_updateTpNode},
        {"deleteSatellite", Native_Sig_DvbSatellite_deleteSatellite, (void*)Java_DvbSatellite_deleteSatellite},
        {"deleteTpNode", Native_Sig_DvbSatellite_deleteTpNode, (void *)Java_DvbSatellite_deleteTpNode},
 };



static JNINativeMethod g_DvbPlayer_Methods[] = {
       {"start", Native_Sig_DvbPlayer_Start,(void*)Java_DvbPlayer_start},
       {"stop", "(Z)I", (void*)Java_DvbPlayer_stop},
       {"pauseVideo", "()I", (void *)Java_DvbPlayer_pauseVideo},
	{"resumeVideo", "()I", (void *)Java_DvbPlayer_resumeVideo},
	{"switchAudioTrack", "(I)I", (void *)Java_DvbPlayer_switchAudioTrack},
	{"switchAudioChannel", "(I)I", (void *)Java_DvbPlayer_switchAudioChannel},
	{"configNim", "(I)I", (void *)Java_DvbPlayer_configNim},
       {"showlogo","(Ljava/lang/String;)I",(void *)Java_DvbPlayer_showlogo},
       {"setPos", "(IIII)I", (void *)Java_DvbPlayer_setPos},
       {"GetVol", "()I", (void *)Java_DvbPlayer_GetVol},
	{"SetVol", "(I)I", (void *)Java_DvbPlayer_SetVol}, 
      {"GetVolMute", "()I", (void *)Java_DvbPlayer_GetVolMute},
	{"SetVolMute", "(I)I", (void *)Java_DvbPlayer_SetVolMute}, 
 };

static JNINativeMethod g_DvbSystemSetting_Methods[] = {
	  {"initIDs", "()V",(void*)Java_DvbSystemSetting_initIDs},
	  {"setAspect", "(I)Z", (void*)Java_DvbSystemSetting_setAspect},
        {"setBrightness", "(I)Z", (void *)Java_DvbSystemSetting_setBrightness},
        {"setSndChn", "(I)Z", (void*)Java_DvbSystemSetting_setSndChn},
};


static JNINativeMethod g_DvbSystem_Methods[] = {
	{"loadDefault","()I",(void *)Java_DvbSystem_loadDefault},
	{"getboardType","()I",(void *)Java_com_ali_dvbdemo_DvbSystem_getboardType},
	{"LockFreq","(II)I",(void *)Java_com_ali_dvbdemo_DvbSystem_LockFreq},
	{"getTunerLock","()I",(void *)Java_com_ali_dvbdemo_DvbSystem_getTunerLock},
	{"getTunerSNR","()I",(void *)Java_com_ali_dvbdemo_DvbSystem_getTunerSNR},
	{"getTunerAGC","()I",(void *)Java_com_ali_dvbdemo_DvbSystem_getTunerAGC},
	{"PanelShow", "(Ljava/lang/String;I)I", (void *)Java_com_DvbPanelShow},
};

static JNINativeMethod g_DvbPropery_Methods[] = {
	{"getSS","(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;",(void *)Java_DvbProperty_getSS},
	{"get_int","(Ljava/lang/String;I)I",(void *)Java_DvbProperty_get_int},
	{"set","(Ljava/lang/String;Ljava/lang/String;)V",(void *)Java_DvbProperty_set},

};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv* env = NULL;
	jint result = -1;

	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		return -1;
	}

	gJavaVM = vm;

         jclass cls = (*env)->FindClass(env, Class_DvbChannelPath);
         if (cls == NULL)
         {
             LOGE("%s,%d:get cls err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }
         jint nRes = (*env)->RegisterNatives(env, cls, g_DvbChannel_Methods, sizeof(g_DvbChannel_Methods)/sizeof(g_DvbChannel_Methods[0]));
         if (nRes < 0)
         {
             LOGE("%s,%d:register method err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }

         cls = (*env)->FindClass(env, Class_DvbSatellitePath);
         if (cls == NULL)
         {
             LOGE("%s,%d:get cls err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }
         nRes = (*env)->RegisterNatives(env, cls, g_DvbSatellite_Methods, sizeof(g_DvbSatellite_Methods)/sizeof(g_DvbSatellite_Methods[0]));
         if (nRes < 0)
         {
             LOGE("%s,%d:register method err!(%d)",__FUNCTION__,__LINE__, nRes);
             return JNI_ERR;
         }

         cls = (*env)->FindClass(env, Class_DvbSearchPath);
         if (cls == NULL)
         {
             LOGE("%s,%d:get cls err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }
         nRes = (*env)->RegisterNatives(env, cls, g_DvbSearch_Methods, sizeof(g_DvbSearch_Methods)/sizeof(g_DvbSearch_Methods[0]));
         if (nRes < 0)
         {
             LOGE("%s,%d:register method err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }

	cls = (*env)->FindClass(env, Class_DvbUdrmPath);
	if (cls == NULL)
	{
		LOGE("%s,%d:get cls err!",__FUNCTION__,__LINE__);
		return JNI_ERR;
	}

	nRes = (*env)->RegisterNatives(env, cls, g_DvbUdrm_Methods, sizeof(g_DvbUdrm_Methods)/sizeof(g_DvbUdrm_Methods[0]));
	if (nRes < 0)
	{
		LOGE("%s,%d:register method err!",__FUNCTION__,__LINE__);
		return JNI_ERR;
	}


         cls = (*env)->FindClass(env, Class_DvbDvbEpgPath);
         if (cls == NULL)
         {
             LOGE("%s,%d:get cls err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }
         nRes = (*env)->RegisterNatives(env, cls, g_DvbEpg_Methods, sizeof(g_DvbEpg_Methods)/sizeof(g_DvbEpg_Methods[0]));
         if (nRes < 0)
         {
             LOGE("%s,%d:register method err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }

	 cls = (*env)->FindClass(env, Class_DvbDvbPlayerPath);
         if (cls == NULL)
         {
             LOGE("%s,%d:get cls err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }
         nRes = (*env)->RegisterNatives(env, cls, g_DvbPlayer_Methods, sizeof(g_DvbPlayer_Methods)/sizeof(g_DvbPlayer_Methods[0]));
         if (nRes < 0)
         {
             LOGE("%s,%d:register method err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }

	 cls = (*env)->FindClass(env, Class_DvbDvbSystemPath);
         if (cls == NULL)
         {
             LOGE("%s,%d:get cls err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }
         nRes = (*env)->RegisterNatives(env, cls, g_DvbSystem_Methods, sizeof(g_DvbSystem_Methods)/sizeof(g_DvbSystem_Methods[0]));
         if (nRes < 0)
         {
             LOGE("%s,%d:register method err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }

	   cls = (*env)->FindClass(env, Class_DvbSystemSettingPath);
         if (cls == NULL)
         {
             LOGE("%s,%d:get cls err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }
         nRes = (*env)->RegisterNatives(env, cls, g_DvbSystemSetting_Methods, sizeof(g_DvbSystemSetting_Methods)/sizeof(g_DvbSystemSetting_Methods[0]));
         if (nRes < 0)
         {
             LOGE("%s,%d:register method err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }

         cls = (*env)->FindClass(env, Class_DvbPropertyPath);
         if (cls == NULL)
         {
        	 LOGE("%s,%d:get cls err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }
         nRes = (*env)->RegisterNatives(env, cls, g_DvbPropery_Methods, sizeof(g_DvbPropery_Methods)/sizeof(g_DvbPropery_Methods[0]));
         if (nRes < 0)
         {
             LOGE("%s,%d:register method err!",__FUNCTION__,__LINE__);
             return JNI_ERR;
         }
        
        cls = (*env)->FindClass(env, Class_DvbSearchPath);
        
        Java_DvbSearch_initIDs(env, cls);

        cls = (*env)->FindClass(env, Class_DvbChannelPath);

        Java_DvbChannel_initIDs(env, cls);

	 getChannelGlobalReference(env);

	 cls = (*env)->FindClass(env, Class_DvbSatellitePath);

	 Java_DvbSatellite_initIDs(env, cls);

	 getSatelliteGlobalReference(env);
	getUdrmGlobalReference(env);

        ALiDVB_SystemInit();
	jni_set_udrm_callback(Java_DvbUdrm_callback);

	/* success -- return valid version number */
	result = JNI_VERSION_1_4;

       LOGD("%s,%d:called", __FUNCTION__, __LINE__);
       
	return result;
}


JNIEXPORT void JNICALL JNI_OnUnLoad(JavaVM *jvm, void *reserved)
 {
	JNIEnv *env = NULL;
	set_lnb_power(0);
	LOGD("%s,%d:called", __FUNCTION__, __LINE__);
	if ((*jvm)->GetEnv(jvm, (void**)&env, JNI_VERSION_1_4))
	{
		LOGE("%s,%d:ver check err!",__FUNCTION__,__LINE__);
		return;
	}

	jclass cls = (*env)->FindClass(env, Class_DvbChannelPath);
	if (cls == NULL)
	{
		return;
	}
	jint nRes = (*env)->UnregisterNatives(env, cls);

	releaseChannelGlobalReference(env);
	releaseSatelliteGlobalReference(env);
     
	return;
 }

/*
 * Class:     com_dvb_DvbSystem
 * Method:    init
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ali_dvbdemo_DvbSystem_init
  (JNIEnv *env, jclass cls) {
	//dvbsystem_init();
	return 0;
}

/*
 * Class:     com_dvb_DvbSystem
 * Method:    exit
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ali_dvbdemo_DvbSystem_exit
  (JNIEnv *env, jclass cls) {
	//dvbsystem_exit();
	return 0;
}

/*
 * Class:     com_dvb_DvbSystem
 * Method:    loadDefault
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_DvbSystem_loadDefault
  (JNIEnv *env, jclass cls) {

	ALiDVB_SystemLoadDefault();
	
	return 0;
}

/*
 * Class:     com_dvb_DvbSystem
 * Method:    getboardType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ali_dvbdemo_DvbSystem_getboardType
  (JNIEnv *env, jclass cls) {
	jint type = 0;
	type = gospell_get_board_type();
	if( type == BOARD_NULL)
		type = BOARD_DVBC;
	return type;
}


/*
 * Class:     com_dvb_DvbSystem
 * Method:    LockFreq
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_ali_dvbdemo_DvbSystem_LockFreq
 (JNIEnv *env, jclass cls, jint sat_id, jint tp_id) {

 	return ALiDVB_LockFreq(sat_id, tp_id);
}



/*
 * Class:     com_dvb_DvbSystem
 * Method:    getTunerLock
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ali_dvbdemo_DvbSystem_getTunerLock
  (JNIEnv *env, jclass cls) {

 	return ALiDVB_getTunerLock();
  
}

/*
 * Class:     com_dvb_DvbSystem
 * Method:    getTunerSNR
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ali_dvbdemo_DvbSystem_getTunerSNR
  (JNIEnv *env, jclass cls) {

 	return ALiDVB_getTunerSNR();
  
}

/*
 * Class:     com_dvb_DvbSystem
 * Method:    getTunerAGC
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ali_dvbdemo_DvbSystem_getTunerAGC
  (JNIEnv *env, jclass cls) {

 	return ALiDVB_getTunerAGC();

}

JNIEXPORT jint JNICALL Java_com_DvbPanelShow
 (JNIEnv *env, jclass cls, jstring show, jint len) {

	if(len == 12 || len == 11) {
		//len = 11:lock led on
		//len = 12: lock len off
		LOGD("%s:len = %d, ", __FUNCTION__, len);
		return ALiDVB_PannelShow(NULL, len);
		
	}
	else if(len > 0 && len <=10) {
	 	char *showbuff = (*env)->GetStringUTFChars(env, show, NULL);

		LOGD("%s:showbuff = %d, %d, %d, %d ", __FUNCTION__, showbuff[0], showbuff[1],showbuff[2],showbuff[3]);

		ALiDVB_PannelShow(showbuff, len);
		(*env)->ReleaseStringUTFChars(env, show, showbuff);
		return 0;
	}

	return 0;
	
}



