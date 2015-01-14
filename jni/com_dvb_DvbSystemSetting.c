#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#include <adr_mediatypes.h>
#include <hld/adr_hld_dev.h>

#include "com_dvb_DvbSystemSetting.h"
#include "com_alitech_dvbcls_path.h"


#define  LOG_TAG    "libdvbSystemSetting"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


/*
 * Class:     com_dvb_DvbSystemSetting
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_DvbSystemSetting_initIDs
  (JNIEnv *env, jclass cls) {

	LOGD("%s,%d",__FUNCTION__,__LINE__);

}


/*
 * Class:     com_dvb_DvbSystemSetting
 * Method:    setAspect
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_DvbSystemSetting_setAspect
  (JNIEnv *env, jclass cls, jint value) {
	LOGD("%s,%d value = %d ",__FUNCTION__,__LINE__, value);

	enum TVMode eTVAspect;
	enum DisplayMode e169DisplayMode;

	if (value == 2) {
		eTVAspect = TV_16_9;
		e169DisplayMode = NORMAL_SCALE;
	}
	else if( value == 1 ) {
		e169DisplayMode = VERTICALCUT;
		eTVAspect = TV_4_3;
	}
	else {
		e169DisplayMode = PILLBOX;
		eTVAspect = TV_4_3;
	}


	if(vpo_aspect_mode( (struct vpo_device *)dev_get_by_id(HLD_DEV_TYPE_DIS, 0), eTVAspect, e169DisplayMode) == 0)
		return 1;
	else
		return 0;

}

/*
 * Class:     com_dvb_DvbSystemSetting
 * Method:    setBrightness
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_DvbSystemSetting_setBrightness
  (JNIEnv *env, jclass cls, jint value) {
	LOGD("%s,%d value = %d ",__FUNCTION__,__LINE__, value);

	struct vpo_io_video_enhance vp_ve_par;
	struct vpo_device * vp_dev;

	vp_dev= (struct vpo_device *)dev_get_by_id(HLD_DEV_TYPE_DIS, 0);
	if(value > 100)
            value  = 100;
       else if(value < 0)
        value =50;
	vp_ve_par.grade=value ;//42+2*value;
	vp_ve_par.changed_flag=VPO_IO_SET_ENHANCE_BRIGHTNESS;
	
	if(NULL==vp_dev)
	{
           return 0;
	}
	else if( vpo_ioctl(vp_dev,VPO_IO_VIDEO_ENHANCE, (UINT32)&vp_ve_par) == 0)
	{
		return 1;
	}
	else
		return 0;

}

/*
 * Class:     com_dvb_DvbSystemSetting
 * Method:    setSndChn
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_DvbSystemSetting_setSndChn
  (JNIEnv *env, jclass cls, jint value) {
	LOGD("%s,%d value = %d ",__FUNCTION__,__LINE__, value);
	struct snd_device *snd = dev_get_by_id(HLD_DEV_TYPE_SND, 0);
	jint audio_ch = 0;
	
	if(value == 0)
		audio_ch = 2;
	else if(value == 1)
		audio_ch = 0;
	else if(value == 2)
		audio_ch = 1;

	chchg_switch_audio_chan(snd,audio_ch);
	return 1;
}


