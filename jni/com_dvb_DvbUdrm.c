#include "com_dvb_DvbUdrm.h"
#include <alidvb/ams_inc/api/libca/udrm.h>
#include <android/log.h>
#define  LOG_TAG    "UdrmSystem"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define PWD_LENGTH		6

typedef struct  {
	jstring udrm_user_sn;
	int udrm_dev_sn;
	int udrm_sw_ver;
	int udrm_factory_id;
	int udrm_model_id;
	int udrm_loder_ver;
	int udrm_operator_id;
	int udrm_area_id;
	int udrm_password;
	int udrm_watch_class;
	int udrm_WalletPoint;
}UdrmInfo;
UdrmInfo systeminfo;


typedef struct 
{
	UTI_UINT8 readstatus; //  1: NOT READ 2: READ  other: 0: NOT USE
	UTI_UINT32 utc;
	UTI_UINT8 title[20];		// end with '\0'
	UTI_UINT8 content[512]; // end with '\0'
}GOS_MAIL;


jclass CLS_DvbUdrm = NULL;
jclass CLS_DvbUdrmInfo = NULL;
jclass CLS_DvbUdrmEmail = NULL;
jmethodID MID_DvbUdrm_Email;
jmethodID MID_DvbUdrm_info;
jmethodID MID_Dvbudrm_callback;

JavaVM *gJavaVM;

int getUdrmGlobalReference(JNIEnv *pJNIEnv) {
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	jclass cls = (*pJNIEnv)->FindClass(pJNIEnv, "com/alitech/dvb/DvbUdrm");
	if (cls == NULL) {
		LOGE("%s,%d,DvbChannelNode: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}

	CLS_DvbUdrm = (*pJNIEnv)->NewGlobalRef(pJNIEnv, cls);
	if (CLS_DvbUdrm == NULL) {
		LOGE("%s,%d,CLS_DvbUdrm: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}

	cls  = (*pJNIEnv)->FindClass(pJNIEnv, "com/alitech/dvb/DvbUdrmInfo");
	if (cls == NULL) {
		LOGE("%s,%d,DvbChannelNode: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	CLS_DvbUdrmInfo = (*pJNIEnv)->NewGlobalRef(pJNIEnv, cls);
	if (CLS_DvbUdrm == NULL) {
		LOGE("%s,%d,CLS_DvbUdrm: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}

	cls = (*pJNIEnv)->FindClass(pJNIEnv, "com/alitech/dvb/DvbUdrmInfo$Email");
	if (cls == NULL) {
		LOGE("%s,%d,DvbChannelNode: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	CLS_DvbUdrmEmail = (*pJNIEnv)->NewGlobalRef(pJNIEnv, cls);
	if (CLS_DvbUdrmEmail == NULL) {
		LOGE("%s,%d,CLS_DvbUdrm: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}
	LOGD("%s,%d ok",__FUNCTION__,__LINE__);

	return 0;
}


JNIEXPORT jobject JNICALL Java_DvbUdrm_getinfo
(JNIEnv *pJNIEnv, jobject obj)
{
	LOGE("%s",__FUNCTION__);
	static jboolean sn_ready = 0 ;
	static jchar sn[32] = {0};
	if(!sn_ready)
	{
		UDRMUserSerialNumber(sn);
		sn_ready= 1;
	}
	LOGE("Java_DvbUdrm_getinfo %s",sn);
	systeminfo.udrm_user_sn = (*pJNIEnv)->NewStringUTF(pJNIEnv,sn);
	UDRMWalletGet(0,&systeminfo.udrm_WalletPoint);
	UDRMSectorViewLevelGet(0,&systeminfo.udrm_watch_class);

	MID_DvbUdrm_info = (*pJNIEnv)->GetMethodID(pJNIEnv, CLS_DvbUdrmInfo,
			"<init>", "(Ljava/lang/String;IIIIIIIIII)V");
	if (MID_DvbUdrm_info == NULL) {
		return;
	}

	jobject info_obj = (*pJNIEnv)->NewObject(pJNIEnv, CLS_DvbUdrmInfo, MID_DvbUdrm_info,
			systeminfo.udrm_user_sn,
			systeminfo.udrm_dev_sn,
			systeminfo.udrm_sw_ver,
			systeminfo.udrm_factory_id,
			systeminfo.udrm_model_id,
			systeminfo.udrm_loder_ver,
			systeminfo.udrm_operator_id,
			systeminfo.udrm_area_id,
			systeminfo.udrm_password,
			systeminfo.udrm_watch_class,
			systeminfo.udrm_WalletPoint
	);

	return info_obj;
}
/*
/*
 * Class:     com_nmp_dvbplayer_udrm_UdrmSystem
 * Method:    getUdrmPpcNum
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_DvbUdrm_getUdrmPpcNum
(JNIEnv *pJNIEnv, jobject obj)
{
	unsigned int number;
	UDRMProductGetNumber(0,&number);
	LOGE("%s %d",__FUNCTION__,number);
	return number;
}
/*
 * Class:     com_nmp_dvbplayer_udrm_UdrmSystem
 * Method:    getUdrmPpcId
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_DvbUdrm_getUdrmPpcId
(JNIEnv *pJNIEnv, jobject obj, jint idx)
{
	unsigned short productId;
	if(idx)
		UDRMProductGetInfo(0, idx,&productId);
	LOGE("%s %04d",__FUNCTION__,productId);
	return productId;

}


/*
 * Class:     com_nmp_dvbplayer_udrm_UdrmSystem
 * Method:    getUdrmEmailInfo
 * Signature: ()[Lcom/alitech/dvb/DvbUdrmInfo/Email;
 */
JNIEXPORT jobjectArray JNICALL Java_DvbUdrm_getUdrmEmailInfo
(JNIEnv *pJNIEnv, jobject obj )
{
	int count = 10 ;

	jobjectArray result = (*pJNIEnv)->NewObjectArray(pJNIEnv, count, CLS_DvbUdrmEmail, NULL);

	MID_DvbUdrm_Email = (*pJNIEnv)->GetMethodID(pJNIEnv, CLS_DvbUdrmEmail,
			"<init>", "([BC[BI)V");


	int i;
	GOS_MAIL email;
	for (i=0; i<count; i++) {
		gos_get_email(i, &email) ;
		jbyteArray jbyteArraytitle = (*pJNIEnv)->NewByteArray(pJNIEnv,20);
		jbyteArray jbyteArraycontend = (*pJNIEnv)->NewByteArray(pJNIEnv,512);

		(*pJNIEnv)->SetByteArrayRegion(pJNIEnv,jbyteArraycontend,0,strlen(email.content),email.content);

		jobject email_obj = (*pJNIEnv)->NewObject(pJNIEnv, CLS_DvbUdrmEmail, MID_DvbUdrm_Email,
				jbyteArraycontend,email.readstatus,jbyteArraytitle,email.utc);

		(*pJNIEnv)->SetObjectArrayElement(pJNIEnv, result, i, email_obj);
		(*pJNIEnv)->DeleteLocalRef(pJNIEnv,jbyteArraytitle);
		(*pJNIEnv)->DeleteLocalRef(pJNIEnv,jbyteArraycontend);
		(*pJNIEnv)->DeleteLocalRef(pJNIEnv, email_obj);
	}


	LOGE("%s",__FUNCTION__);

	return result;
}



/*
 * Class:     com_nmp_dvbplayer_udrm_UdrmSystem
 * Method:    deleteUdrmEmail
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_DvbUdrm_deleteUdrmEmail
(JNIEnv *pJNIEnv, jobject obj , jint idx)
{
	LOGE("%s idx %d",__FUNCTION__ ,idx);
	return gos_del_email(idx);
}
/*
 * Class:     com_nmp_dvbplayer_udrm_UdrmSystem
 * Method:    setUdrmWatchClass
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_DvbUdrm_setUdrmWatchClass
(JNIEnv *pJNIEnv, jobject obj, jint level, jstring password)
{
	LOGE("%s",__FUNCTION__);
	char result;
	const char* pin = (*pJNIEnv)->GetStringUTFChars(pJNIEnv, password, 0);
	UDRMSectorViewLevelSet(0,  level* 3,  pin,  &result);
	(*pJNIEnv)->ReleaseStringUTFChars(pJNIEnv, password, pin);

}

/*
 * Class:     com_nmp_dvbplayer_udrm_UdrmSystem
 * Method:    getUdrmWatchClass
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_DvbUdrm_getUdrmWatchClass
(JNIEnv *pJNIEnv , jobject obj)
{
	unsigned int level;
	UDRMSectorViewLevelGet(0,&level);
	LOGE("%s %d",__FUNCTION__,level);
	return level/3;
}
/*
 * Class:     com_nmp_dvbplayer_udrm_UdrmSystem
 * Method:    setUdrmPassword
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_DvbUdrm_setUdrmPassword
(JNIEnv *pJNIEnv , jobject obj, jstring passwordold,jstring passwordnew  )
{
	LOGE("%s",__FUNCTION__);
	jchar result;
	const char* pinold = (*pJNIEnv)->GetStringUTFChars(pJNIEnv, passwordold, 0);
	const char* pinnew = (*pJNIEnv)->GetStringUTFChars(pJNIEnv, passwordnew, 0);
	LOGE("UDRMSectorPinCheck %s -->>%s",pinold,pinnew);


	UDRMSectorPinSet(0,pinold,pinnew,&result);

	(*pJNIEnv)->ReleaseStringUTFChars(pJNIEnv, passwordold, pinold);
	(*pJNIEnv)->ReleaseStringUTFChars(pJNIEnv, passwordnew, pinnew);

	return   result;

}

/*
 * Class:     com_nmp_dvbplayer_udrm_UdrmSystem
 * Method:    checkUdrmPassword
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_DvbUdrm_checkUdrmPassword
(JNIEnv *pJNIEnv, jobject obj , jstring password)
{
	LOGE("%s",__FUNCTION__);
	jchar result;
	const char* pin = (*pJNIEnv)->GetStringUTFChars(pJNIEnv, password, 0);

	LOGE("UDRMSectorPinCheck %s",pin);
	UDRMSectorPinCheck(0,pin,&result);


	(*pJNIEnv)->ReleaseStringUTFChars(pJNIEnv, password, pin);

	return   result;

}


void Java_DvbUdrm_callback(UTI_UINT32 msg_type,UTI_UINT32 msg_code,UTI_UINT32 utc, UTI_UINT8* title, UTI_UINT8*  contend)
{
	int ret = 0;
	int exit = 0;
	int isAttached = 0;
	int status;
	JNIEnv *pJNIEnv = NULL;
	status = (*gJavaVM)->GetEnv(gJavaVM, &pJNIEnv, JNI_VERSION_1_4);
	if(status < 0) {
		status = (*gJavaVM)->AttachCurrentThread(gJavaVM, &pJNIEnv, NULL);
		if(status < 0) {
			LOGE("%s,%d,callback_handler: failed to attach current thread",__FUNCTION__,__LINE__);
			goto EXIT;
		}
		isAttached = 1;
		//LOGD("%s,%d AttachCurrentThread",__FUNCTION__,__LINE__);
	}

	jmethodID MID_Dvbudrm_callback = (*pJNIEnv)->GetStaticMethodID(pJNIEnv, CLS_DvbUdrm, "callback", "(III[B[B)V");
	if (MID_Dvbudrm_callback == NULL) {
		return;
	}

	LOGD("%s,%d CallStaticVoidMethod... %d %d ",__FUNCTION__,__LINE__ ,msg_type,msg_code);

	jbyteArray jbyteArraytitle = (*pJNIEnv)->NewByteArray(pJNIEnv,20);
	jbyteArray jbyteArraycontend = (*pJNIEnv)->NewByteArray(pJNIEnv,255);

	if(title != NULL && msg_type == 1)
	{
		//(*pJNIEnv)->SetByteArrayRegion(pJNIEnv,jbyteArraytitle,0,strlen(title),title);
	}


	if(contend != NULL )
	{
		(*pJNIEnv)->SetByteArrayRegion(pJNIEnv,jbyteArraycontend,0,strlen(contend),contend);
	}

	(*pJNIEnv)->CallStaticVoidMethod(pJNIEnv,CLS_DvbUdrm,MID_Dvbudrm_callback, msg_type, msg_code,utc,jbyteArraytitle,jbyteArraycontend);

	(*pJNIEnv)->DeleteLocalRef(pJNIEnv,jbyteArraytitle);
	(*pJNIEnv)->DeleteLocalRef(pJNIEnv,jbyteArraycontend);

	EXIT:
	if (exit) {
		LOGD("%s,%d try to exit...",__FUNCTION__,__LINE__);

	}

	if(isAttached)	{
		//LOGD("%s,%d DetachCurrentThread",__FUNCTION__,__LINE__);
		(*gJavaVM)->DetachCurrentThread(gJavaVM);
	}
}




