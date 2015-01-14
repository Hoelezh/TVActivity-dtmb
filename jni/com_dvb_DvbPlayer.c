#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#include "com_dvb_DvbPlayer.h"

#include "alidvb_channelnode.h"
#include "channelNode.h"

#define  LOG_TAG    "libdvbplayer"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern void config_tsi(void);

static int ChannelNodeConvert2(struct DvbChannelNode *dnode, ALiDVB_ChannelNode *snode)
{
	int i;

	memset(snode, 0, sizeof(ALiDVB_ChannelNode));

	snode->frontend.type = dnode->frontend.ft_type;
	snode->frontend.frequency = dnode->frontend.frq;
	snode->frontend.symbol_rate = dnode->frontend.sym;
	snode->frontend.modulation = dnode->frontend.qam;
	
	snode->pcr_pid = dnode->pcr.pcr_pid;
	snode->video_pid = dnode->video.video_pid;
	snode->video_type = dnode->video.video_type;
	snode->audio_channel = dnode->audio.audio_channel;
	snode->audio_volume = dnode->audio.audio_volume;
	snode->audio_current = dnode->audio.audio_current;
	snode->audio_count = dnode->audio.audio_count;
	for (i=0;i<snode->audio_count;i++)
	{
		snode->audio_track[i].audio_pid = dnode->audio.audio_track[i].audio_pid;
		snode->audio_track[i].audio_type = dnode->audio.audio_track[i].audio_type;
		memcpy(snode->audio_track[i].audio_lang, dnode->audio.audio_track[i].audio_lang, 4);
	}
	snode->pcr_pid = dnode->pcr.pcr_pid;
	snode->bouquet_count = dnode->bouquet.bouquet_count;
	for (i = 0; i < snode->bouquet_count; i++)
	{
		snode->bouquet_id[i] = dnode->bouquet.bouquet_id[i];
	}
	memcpy(snode->bouquet_id, dnode->bouquet.bouquet_id, snode->bouquet_count * sizeof(short));
	snode->service_id = dnode->service_id;
	snode->service_type = dnode->service_type;
	memcpy(snode->service_name, dnode->service_name, (MAX_SERVICE_NAME_LENGTH+1)*sizeof(snode->service_name[0]));

	snode->sat_id = dnode->sat_id;
	snode->tp_id = dnode->tp_id;
	snode->prog_id = dnode->prog_id;

	return 0;
}

/*
 * Class:     com_dvb_DvbPlayer
 * Method:    start
 * Signature: (Lcom/dvb/DvbChannelNode;Z)I
 */
JNIEXPORT jint JNICALL Java_DvbPlayer_start
  (JNIEnv *env, jobject obj, jobject channel, jboolean blkScrn) {

	int ret;
	struct DvbChannelNode snode;
	ALiDVB_ChannelNode dnode;

	LOGD("%s,%d ",__FUNCTION__,__LINE__);
	getChannelNode(env, channel, &snode);

	ChannelNodeConvert2(&snode, &dnode);

	ret = ALiDVB_PlayerStart(&dnode, blkScrn);

	return ret;
}

/*
 * Class:     com_dvb_DvbPlayer
 * Method:    stop
 * Signature: (Z)I
 */
JNIEXPORT jint JNICALL Java_DvbPlayer_stop
  (JNIEnv *env, jobject obj, jboolean blkScrn) {
	int ret;
	LOGD("%s,%d ",__FUNCTION__,__LINE__);

	ret = ALiDVB_PlayerStop(blkScrn);

	return ret;
}

/*
 * Class:     com_dvb_DvbPlayer
 * Method:    pauseVideo
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_DvbPlayer_pauseVideo
  (JNIEnv *env, jobject obj) {
	int ret;
	LOGD("%s,%d ",__FUNCTION__,__LINE__);

	//ret = player_pauseVideo();

	return ret;
}

/*
 * Class:     com_dvb_DvbPlayer
 * Method:    resumeVideo
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_DvbPlayer_resumeVideo
  (JNIEnv *env, jobject obj) {
	int ret;
	LOGD("%s,%d ",__FUNCTION__,__LINE__);

	//ret = player_resumeVideo();

	return ret;
}

/*
 * Class:     com_dvb_DvbPlayer
 * Method:    switchAudioTrack
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_DvbPlayer_switchAudioTrack
  (JNIEnv *env, jobject obj, jint audioTrackIdx) {
	int ret;
	LOGD("%s,%d ",__FUNCTION__,__LINE__);

	//ret = player_switchAudioTrack(audioTrackIdx);

	return ret;
}

/*
 * Class:     com_dvb_DvbPlayer
 * Method:    switchAudioChannel
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_DvbPlayer_switchAudioChannel
  (JNIEnv *env, jobject obj, jint audioChannel) {
	int ret;
	LOGD("%s,%d,vol=%d ",__FUNCTION__,__LINE__,audioChannel);
	//ret = player_switchAudioChannel(audioChannel);

	return ret;
}

JNIEXPORT jint JNICALL Java_DvbPlayer_configNim
  (JNIEnv *env, jobject obj, jint nim) {
	int ret;
	LOGD("%s,%d,vol=%d ",__FUNCTION__,__LINE__,nim);
	//ret = player_switchAudioChannel(audioChannel);

	config_tsi();

	return ret;
}

JNIEXPORT jint JNICALL Java_DvbPlayer_showlogo
  (JNIEnv *env, jobject obj, jstring path) {
	int ret;

	char *str;
LOGD("%s,%d",__FUNCTION__,__LINE__);
	str = (*env)->GetStringUTFChars(env, path, 0);

	ret = ALiDVB_ShowLogo(str);

	(*env)->ReleaseStringUTFChars(env, path, str);
	
	return ret;
}

JNIEXPORT jint JNICALL Java_DvbPlayer_setPos
  (JNIEnv *env, jobject obj, jint l, jint t, jint r, jint b) {

	int ret;
LOGD("%s,%d",__FUNCTION__,__LINE__);
	ret = ALiDVB_PlayerSetPos(l, t, r-l, b-t);
	
	return ret;
}

JNIEXPORT jint JNICALL Java_DvbPlayer_GetVol
(JNIEnv *env , jobject obj)
{
	int vol;
LOGD("%s,%d",__FUNCTION__,__LINE__);
	vol = ALiDVB_PlayerGetVol();

	return vol;
}

JNIEXPORT jint JNICALL Java_DvbPlayer_SetVol
(JNIEnv *env, jobject obj, jint vol)
{
	int ret;
LOGD("%s,%d",__FUNCTION__,__LINE__);
	ret = ALiDVB_PlayerSetVol(vol);

	return ret;
}

JNIEXPORT jint JNICALL Java_DvbPlayer_GetVolMute
(JNIEnv *env , jobject obj)
{
    int mute;

    LOGD("%s,%d",__FUNCTION__,__LINE__);
    mute = ALiDVB_PlayerVolGetMute();

	return mute;
}

JNIEXPORT jint JNICALL Java_DvbPlayer_SetVolMute
(JNIEnv *env, jobject obj, jint mute)
{
    int ret;
    LOGD("%s,%d",__FUNCTION__,__LINE__);
    ret = ALiDVB_PlayerVolMute(mute);

	return ret;
}