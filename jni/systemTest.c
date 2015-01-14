#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#include "system.h"

#define  LOG_TAG    "libdvbsystem"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

int dvbsystem_init() {
	LOGD("%s,%d",__FUNCTION__,__LINE__);
	return 0;
}

int dvbsystem_exit() {
	LOGD("%s,%d",__FUNCTION__,__LINE__);
	return 0;
}

int dvbsystem_loadDefault() {
	LOGD("%s,%d",__FUNCTION__,__LINE__);
	return 0;
}
