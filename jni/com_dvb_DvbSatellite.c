#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#include "com_dvb_DvbSatellite.h"
#include "com_alitech_dvbcls_path.h"

#include "alidvb_channelnode.h"

#define  LOG_TAG    "libdvbSatellite"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


#define TYPE_TP_NODE	1
#define TYPE_SAT_NODE	2

jmethodID MID_DVBSatelliteNode_constructor;
jmethodID MID_DVBTpNode_constructor;

jfieldID FID_DVBSatelliteNode_mSatId;
jfieldID FID_DVBSatelliteNode_mSatName;
jfieldID FID_DVBSatelliteNode_mSatOrbit;
jfieldID FID_DVBSatelliteNode_mSatSelect;
jfieldID FID_DVBSatelliteNode_mSatTuner1;
jfieldID FID_DVBSatelliteNode_mSatTuner2;

jfieldID FID_DVBSatelliteNode_mLnbtype;
jfieldID FID_DVBSatelliteNode_mLnblow;
jfieldID FID_DVBSatelliteNode_mLnbhigh;
jfieldID FID_DVBSatelliteNode_mLnbpower;
jfieldID FID_DVBSatelliteNode_mDiSEqC_type;
jfieldID FID_DVBSatelliteNode_mDiSEqC_port;
jfieldID FID_DVBSatelliteNode_mDiSEqC11_type;
jfieldID FID_DVBSatelliteNode_mDiSEqC11_port;
jfieldID FID_DVBSatelliteNode_mPol;
jfieldID FID_DVBSatelliteNode_mK22;

jfieldID FID_DVBTpNode_mSatId;
jfieldID FID_DVBTpNode_mTpId;
jfieldID FID_DVBTpNode_mTpFreq;
jfieldID FID_DVBTpNode_mTpSymbol;
jfieldID FID_DVBTpNode_mTppol;


jclass getClass_DvbSatelliteNode(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbSatelliteNodePath);
	if (cls == NULL) {
		LOGE("%s,%d,DvbChannelNode: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}

jclass getClass_DvbTpNode(JNIEnv *env) {
	jclass cls = (*env)->FindClass(env, Class_DvbTpNodePath);
	if (cls == NULL) {
		LOGE("%s,%d,DvbChannelNode: failed to find class",__FUNCTION__,__LINE__);
		return NULL;
	}
	return cls;
}


jclass CLS_DvbSatelliteNode = NULL;
jclass CLS_DvbTpNode = NULL;

int getSatelliteGlobalReference(JNIEnv *env) {
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	jclass cls = getClass_DvbSatelliteNode(env);
	if (cls == NULL) {
		return -1;
	}
	CLS_DvbSatelliteNode = (*env)->NewGlobalRef(env, cls);
	if (CLS_DvbSatelliteNode == NULL) {
		LOGE("%s,%d,CLS_DvbChannelNode: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}

	cls = getClass_DvbTpNode(env);
	if (cls == NULL) {
		return -1;
	}
	CLS_DvbTpNode = (*env)->NewGlobalRef(env, cls);
	if (CLS_DvbTpNode == NULL) {
		LOGE("%s,%d,CLS_DvbChannelNode: failed to new global reference",__FUNCTION__,__LINE__);
		return -1;
	}
	
	LOGD("%s,%d ok",__FUNCTION__,__LINE__);

	return 0;
}

int releaseSatelliteGlobalReference(JNIEnv *env) {

	LOGD("%s,%d",__FUNCTION__,__LINE__);

	if(CLS_DvbSatelliteNode)
		(*env)->DeleteGlobalRef(env, CLS_DvbSatelliteNode);

	if(CLS_DvbTpNode)
		(*env)->DeleteGlobalRef(env, CLS_DvbTpNode);

	return 0;
}


/*
 * Class:     com_dvb_DvbChannel
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_DvbSatellite_initIDs
  (JNIEnv *env, jclass cls) {

	LOGD("%s,%d",__FUNCTION__,__LINE__);

	jclass CLS_DvbSatelliteNode = getClass_DvbSatelliteNode(env);
	if (CLS_DvbSatelliteNode == NULL) {
              LOGE("%s,%d:get CLS_DvbChannelNode null",__FUNCTION__,__LINE__);
		return;
	}

	MID_DVBSatelliteNode_constructor = (*env)->GetMethodID(env, CLS_DvbSatelliteNode,
			"<init>", Class_Sig_Con_DvbSatelliteNode);
    
	if (MID_DVBSatelliteNode_constructor == NULL) {
		return;
	}
	jclass CLS_DvbTpNode = getClass_DvbTpNode(env);
	if (CLS_DvbTpNode == NULL) {
              LOGE("%s,%d:get CLS_DvbChannelNode null",__FUNCTION__,__LINE__);
		return;
	}
	
	MID_DVBTpNode_constructor = (*env)->GetMethodID(env, CLS_DvbTpNode,
			"<init>", Class_Sig_Con_DvbTpNode);
    
	if (MID_DVBTpNode_constructor == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mSatId = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "sat_id", "I");
	if (FID_DVBSatelliteNode_mSatId == NULL) {
		return;
	}
	
	FID_DVBSatelliteNode_mSatName = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "sat_name", "Ljava/lang/String;");
	if (FID_DVBSatelliteNode_mSatName == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mSatOrbit = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "sat_orbit", "I");
	if (FID_DVBSatelliteNode_mSatOrbit == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mSatSelect = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "select_flag", "Z");
	if (FID_DVBSatelliteNode_mSatSelect == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mSatTuner1 = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "tuner1_valid", "Z");
	if (FID_DVBSatelliteNode_mSatTuner1 == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mSatTuner2 = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "tuner2_valid", "Z");
	if (FID_DVBSatelliteNode_mSatTuner2 == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mLnbtype = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "lnb_type", "I");
	if (FID_DVBSatelliteNode_mLnbtype == NULL) {
		return;
	}
	
	FID_DVBSatelliteNode_mLnblow = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "lnb_low", "I");
	if (FID_DVBSatelliteNode_mLnblow == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mLnbhigh = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "lnb_high", "I");
	if (FID_DVBSatelliteNode_mLnbhigh == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mLnbpower = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "lnb_power", "I");
	if (FID_DVBSatelliteNode_mLnbpower == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mDiSEqC_type = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "DiSEqC_type", "I");
	if (FID_DVBSatelliteNode_mDiSEqC_type == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mDiSEqC_port = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "DiSEqC_port", "I");
	if (FID_DVBSatelliteNode_mDiSEqC_port == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mDiSEqC11_type = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "DiSEqC11_type", "I");
	if (FID_DVBSatelliteNode_mDiSEqC11_type == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mDiSEqC11_port = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "DiSEqC11_port", "I");
	if (FID_DVBSatelliteNode_mDiSEqC11_port == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mPol = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "pol", "I");
	if (FID_DVBSatelliteNode_mPol == NULL) {
		return;
	}

	FID_DVBSatelliteNode_mK22 = (*env)->GetFieldID(env, CLS_DvbSatelliteNode, "k22", "I");
	if (FID_DVBSatelliteNode_mK22 == NULL) {
		return;
	}



	FID_DVBTpNode_mSatId = (*env)->GetFieldID(env, CLS_DvbTpNode, "sat_id", "I");
	if (FID_DVBTpNode_mSatId == NULL) {
		return;
	}
	
	FID_DVBTpNode_mTpId = (*env)->GetFieldID(env, CLS_DvbTpNode, "tp_id", "I");
	if (FID_DVBTpNode_mTpId == NULL) {
		return;
	}

	FID_DVBTpNode_mTpFreq = (*env)->GetFieldID(env, CLS_DvbTpNode, "freq", "I");
	if (FID_DVBTpNode_mTpFreq == NULL) {
		return;
	}

	FID_DVBTpNode_mTpSymbol = (*env)->GetFieldID(env, CLS_DvbTpNode, "symbol", "I");
	if (FID_DVBTpNode_mTpSymbol == NULL) {
		return;
	}

	FID_DVBTpNode_mTppol = (*env)->GetFieldID(env, CLS_DvbTpNode, "pol", "I");
	if (FID_DVBTpNode_mTppol == NULL) {
		return;
	}

}


jobject getSatelliteObject(JNIEnv *env, int index, ALiDVB_SatelliteNode *node) {
	//LOGD("%s,%d",__FUNCTION__,__LINE__);

       unsigned short uniname[MAX_SERVICE_NAME_LENGTH+1];
       int unilen;
       
       unilen = getUnicodeString(node->sat_name, uniname);
	   //LOGD("%s,%d, %s",__FUNCTION__,unilen, uniname);
	 LOGD("%s,%d, %x,%x,%x,%x",__FUNCTION__,unilen, node->sat_name[0],node->sat_name[1],node->sat_name[2],node->sat_name[4]);
	jstring name = (*env)->NewString(env, uniname, unilen);

	/* number */
	char buf[10];
	//sprintf(buf, "s%d",index+1);
	jstring number = (*env)->NewStringUTF(env, buf);
	
	jobject channel = (*env)->NewObject(env, CLS_DvbSatelliteNode, MID_DVBSatelliteNode_constructor,
			node->sat_id, name, number,node->sat_orbit, node->select, node->tuner1_valid, node->tuner2_valid, node->lnb_type, node->lnb_low, 
			node->lnb_high, node->DiSEqC_type, node->DiSEqC_port, node->DiSEqC11_type, node->DiSEqC11_port, node->lnb_power, node->pol, node->k22);

	(*env)->DeleteLocalRef(env, name);

	(*env)->DeleteLocalRef(env, number);

	return channel;
}

int getSatelliteNode(JNIEnv *env, jobject channel, ALiDVB_SatelliteNode *node) {
	LOGD("%s,%d",__FUNCTION__,__LINE__);

       node->sat_id= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mSatId);
	node->sat_orbit= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mSatOrbit);
	LOGD("%s,sat_orbit = %d",__FUNCTION__,node->sat_orbit);

	node->select= (*env)->GetBooleanField(env, channel, FID_DVBSatelliteNode_mSatSelect);
	node->tuner1_valid= (*env)->GetBooleanField(env, channel, FID_DVBSatelliteNode_mSatTuner1);
	node->tuner2_valid= (*env)->GetBooleanField(env, channel, FID_DVBSatelliteNode_mSatTuner2);

	node->lnb_type= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mLnbtype);
	node->lnb_low= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mLnblow);
	node->lnb_high= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mLnbhigh);
	node->lnb_power= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mLnbpower);
	node->DiSEqC_type= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mDiSEqC_type);
	node->DiSEqC_port= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mDiSEqC_port);
	node->DiSEqC11_type= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mDiSEqC11_type);
	node->DiSEqC11_port= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mDiSEqC11_port);
	node->pol= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mPol);
	node->k22= (*env)->GetIntField(env, channel, FID_DVBSatelliteNode_mK22);

	jstring name = (*env)->GetObjectField(env, channel, FID_DVBSatelliteNode_mSatName);
//	int name_len = (*env)->GetStringUTFLength(env, name);
	int name_len = (*env)->GetStringLength(env, name);
	
//	(*env)->GetStringUTFRegion(env, name, 0, name_len, (char *)node->sat_name);
	(*env)->GetStringRegion(env, name, 0, name_len, (char *)node->sat_name);
	node->sat_name[name_len] = 0;
	LOGD("%s,%d, %x,%x,%x,%x",__FUNCTION__,name_len, node->sat_name[0],node->sat_name[1],node->sat_name[2],node->sat_name[4]);
	//node->sat_name[name_len] = 0;

	return 0;
}


jobject getTpObject(JNIEnv *env, int index, ALiDVB_TpNode *node) {
	//LOGD("%s,%d",__FUNCTION__,__LINE__);

       unsigned short uniname[MAX_SERVICE_NAME_LENGTH+1];
       int unilen;
       
       unilen = getUnicodeString(node->tp_name, uniname);
	   LOGD("%s,%d, %s",__FUNCTION__,unilen, uniname);
	   // LOGD("%s,%d, %x,%x,%x,%x",__FUNCTION__,unilen, uniname[0],uniname[1],uniname[2],uniname[4]);
	jstring name = (*env)->NewString(env, uniname, unilen);

	/* number */
	char buf[10];
	sprintf(buf, "s%d",index+1);
	jstring number = (*env)->NewStringUTF(env, buf);
	
	jobject channel = (*env)->NewObject(env, CLS_DvbTpNode, MID_DVBTpNode_constructor,
			node->tp_id, name, number,node->sat_id, node->freq, node->symbol, node->pol);

	(*env)->DeleteLocalRef(env, name);

	(*env)->DeleteLocalRef(env, number);

	return channel;
}

int getTpNode(JNIEnv *env, jobject channel, ALiDVB_TpNode *node) {
	LOGD("%s,%d",__FUNCTION__,__LINE__);

       node->sat_id= (*env)->GetIntField(env, channel, FID_DVBTpNode_mSatId);
	node->tp_id= (*env)->GetIntField(env, channel, FID_DVBTpNode_mTpId);
	node->freq= (*env)->GetIntField(env, channel, FID_DVBTpNode_mTpFreq);
	node->symbol= (*env)->GetIntField(env, channel, FID_DVBTpNode_mTpSymbol);
	node->pol= (*env)->GetIntField(env, channel, FID_DVBTpNode_mTppol);
	LOGD("%s,%d, %d, %d, %d, %d",__FUNCTION__,node->sat_id, node->tp_id, node->freq, node->symbol, node->pol);
	return 0;
}



/*
 * Class:     com_dvb_DvbSatellite
 * Method:    loadSatelliteNodes
 * Signature: (I)[Lcom/dvb/DVBSatelliteNode;
 */
JNIEXPORT jobjectArray JNICALL Java_DvbSatellite_loadSatelliteNodes
  (JNIEnv *env, jclass cls) {
	int count;

	//LOGD("%s,%d",__FUNCTION__,__LINE__);

	count = ALiDVB_CreateSatView();
	if (count <= 0) {
		return NULL;
	}

	//getChannelGlobalReference(env);
	
	jobjectArray result = (*env)->NewObjectArray(env, count, CLS_DvbSatelliteNode, NULL);
	if (result == NULL) {
		LOGE("new objectarray fail.");
		return NULL;
	}
	
	int i;
	for (i=0; i<count; i++) {
		ALiDVB_SatelliteNode snode;
		if (ALiDVB_GetSatNode(i, &snode) ) {
			continue;			
		}

		jobject channel = getSatelliteObject(env, i, &snode);

		(*env)->SetObjectArrayElement(env, result, i, channel);
		(*env)->DeleteLocalRef(env, channel);
	}

EXIT:
	//releaseChannelGlobalReference(env);//��ͬ�߳̿���ͬʱ���ã��ŵ�soж��ʱ���
	LOGD("%s,%d:end...",__FUNCTION__,__LINE__);
	return result;
}

/*
 * Class:     com_dvb_DvbSatellite
 * Method:    updateSatellite
 * Signature: (Lcom/dvb/DVBSatelliteNode;)I
 */
JNIEXPORT jint JNICALL Java_DvbSatellite_updateSatellite
  (JNIEnv *env, jclass cls, jobject channel) {
	//struct DVBSatelliteNode node;
	ALiDVB_SatelliteNode snode;
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	getSatelliteNode(env, channel, &snode);
	ALiDVB_SaveSatNode(snode);
}

/*
 * Class:     com_dvb_DvbSatellite
 * Method:    loadTpNodes
 * Signature: (I)[Lcom/alitech/dvb/DvbTpNode;
 */
JNIEXPORT jobjectArray JNICALL Java_DvbSatellite_loadTpNodes
  (JNIEnv *env, jclass cls, jint sat_id) {
  	int count;

	count = ALiDVB_CreateTpView(sat_id);
	if (count <= 0) {
		return NULL;
	}

	jobjectArray result = (*env)->NewObjectArray(env, count, CLS_DvbTpNode, NULL);
	if (result == NULL) {
		LOGE("new objectarray fail.");
		return NULL;
	}
	
	int i;
	for (i=0; i<count; i++) {
		ALiDVB_TpNode tpnode;
		if (ALiDVB_GetTpNode(i, &tpnode) ) {
			continue;			
		}

		jobject channel = getTpObject(env, i, &tpnode);

		(*env)->SetObjectArrayElement(env, result, i, channel);
		(*env)->DeleteLocalRef(env, channel);
	}

	return result;

}

/*
 * Class:     com_dvb_DvbSatellite
 * Method:    updateTpNode
 * Signature: (Lcom/alitech/dvb/DvbTpNode;)I
 */
JNIEXPORT jint JNICALL Java_DvbSatellite_updateTpNode
  (JNIEnv *env, jclass cls, jobject tp) {
  	ALiDVB_TpNode tnode;
	jint ret = 0;
	LOGD("%s,%d",__FUNCTION__,__LINE__);

	getTpNode(env, tp, &tnode);
	ret = ALiDVB_SaveTpNode(tnode);
	return ret;
}

/*
 * Class:     com_dvb_DvbSatellite
 * Method:    deleteSatellite
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_DvbSatellite_deleteSatellite
  (JNIEnv *env, jclass cls, jint sat_id) {
  	int ret = 0;

	ret = ALiDVB_DeleteNode(TYPE_SAT_NODE ,sat_id);

	if(ret)
		return 0;
	else
		return 1;
}

/*
 * Class:     com_dvb_DvbSatellite
 * Method:    deleteTpNode
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_DvbSatellite_deleteTpNode
  (JNIEnv *env, jclass cls, jint sat_id, jint tp_id) {
  	jint ret;
	
	ret = ALiDVB_DeleteNode(TYPE_TP_NODE ,tp_id);

	if(ret)
		return 0;
	else
		return 1;
}

