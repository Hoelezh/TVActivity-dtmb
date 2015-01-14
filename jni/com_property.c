#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include  <cutils/properties.h>
//#include "cutils/properties.h"
#include "com_property.h"

#define  LOG_TAG    "libproperty"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

//#define PROPERTY_VALUE_MAX 91

JNIEXPORT jstring JNICALL Java_DvbProperty_getSS(JNIEnv *env, jobject clazz,
                                      jstring keyJ, jstring defJ)
{
    int len;
    const char* key;
    char buf[PROPERTY_VALUE_MAX];
    jstring rvJ = NULL;

    if (keyJ == NULL) {
    	LOGE("%s,%d:key must not be null!",__FUNCTION__,__LINE__);
        goto error;
    }

    key = (*env)->GetStringUTFChars(env,keyJ, 0);

    len = property_get(key, buf, "");
    if ((len <= 0) && (defJ != NULL)) {
        rvJ = defJ;
    } else if (len >= 0) {
        rvJ = (*env)->NewStringUTF(env,buf);
    } else {
        rvJ = (*env)->NewStringUTF(env,"");
    }

    (*env)->ReleaseStringUTFChars(env,keyJ, key);

error:
    return rvJ;
}

JNIEXPORT jint JNICALL Java_DvbProperty_get_int(JNIEnv *env, jobject clazz,
                                      jstring keyJ, jint defJ)
{
    int len;
    const char* key;
    char buf[PROPERTY_VALUE_MAX];
    char* end;
    jint result = defJ;

    if (keyJ == NULL) {
    	LOGE("%s,%d:key must not be null!",__FUNCTION__,__LINE__);
        goto error;
    }

    key = (*env)->GetStringUTFChars(env,keyJ, 0);

    len = property_get(key, buf, "");
    if (len > 0) {
        result = strtol(buf, &end, 0);
        if (end == buf) {
            result = defJ;
        }
    }

    (*env)->ReleaseStringUTFChars(env,keyJ, key);

error:
    return result;
}

JNIEXPORT void JNICALL Java_DvbProperty_set(JNIEnv *env, jobject clazz,
                                      jstring keyJ, jstring valJ)
{
    int err;
    const char* key;
    const char* val;

    if (keyJ == NULL) {
    	LOGE("%s,%d:key must not be null!",__FUNCTION__,__LINE__);
 //       jniThrowNullPointerException(env, "key must not be null.");
        return ;
    }
    key = (*env)->GetStringUTFChars(env,keyJ, 0);

    if (valJ == NULL) {
        val = "";       /* NULL pointer not allowed here */
    } else {
        val = (*env)->GetStringUTFChars(env,valJ, 0);
    }

    err = property_set(key, val);
    LOGE("%s,%d:key[%s]%s  %d!",__FUNCTION__,__LINE__,key,val,err);

    (*env)->ReleaseStringUTFChars(env,keyJ, key);

    if (valJ != NULL) {
        (*env)->ReleaseStringUTFChars(env,valJ, val);
    }

    if (err < 0) {
    	LOGE("%s,%d:failed to set system property!",__FUNCTION__,__LINE__);
    }
}

