#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#include "player.h"

#define  LOG_TAG    "libdvbplayer"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

int player_start(struct DvbChannelNode *node, int blkScrn) {
	LOGD("%s,%d ",__FUNCTION__,__LINE__);

	return 0;
}

int player_stop(int blkScrn) {
	LOGD("%s,%d ",__FUNCTION__,__LINE__);

	return 0;
}

int player_pauseVideo() {
	LOGD("%s,%d ",__FUNCTION__,__LINE__);

	return 0;
}

int player_resumeVideo() {
	LOGD("%s,%d ",__FUNCTION__,__LINE__);

	return 0;
}

int player_switchAudioTrack(int audioTrackIdx) {
	LOGD("%s,%d ",__FUNCTION__,__LINE__);

	return 0;
}

int player_switchAudioChannel(int audioChannel) {
	LOGD("%s,%d ",__FUNCTION__,__LINE__);

	return 0;
}
