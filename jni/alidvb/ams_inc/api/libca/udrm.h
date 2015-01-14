/******************************************************************************
 Copyright(C), 2005-2011, Unitend Technologies Inc. 
 �ļ���:		udrm.h
 ����:			
 �汾:			1.0
 ��������:		2008-2-20
 ����:			���ⲿ���ŵĽӿ�
 �޸ļ�¼: 
	<����>		<ʱ��>       	<�汾>       	<����>
******************************************************************************/


#ifndef _UDRM_H_
#define _UDRM_H_

#include "uti_udrm_type.h"

UTI_SINT32 UDRMInit(void);

UTI_SINT32 UDRMTestModeInit(void);

UTI_SINT32 UDRMTestModeInitGetNormalSN(UTI_UINT8 *pu8NormalSN);

UTI_SINT32 UDRMArea(UTI_UINT32 u32IndexOfSector, UTI_UINT32 *pu32Area);

UTI_SINT32 UDRMGetSectorNumber(UTI_UINT32 *numberOfSector);

UTI_SINT32 UDRMProductGetNumber(UTI_UINT32 indexOfSector, UTI_UINT32 *numberOfProduct);

UTI_SINT32 UDRMProductGetInfo(UTI_UINT32 indexOfSector, UTI_UINT32 index, UTI_UINT16 *productId);

UTI_SINT32 UDRMEventPPVGetNumber(UTI_UINT32 indexOfSector, UTI_UINT32 *numberOfPPV);


UTI_SINT32 UDRMEventPPVGetInfo(UTI_UINT32 indexOfSector, UTI_UINT32 index, UTI_UINT32 *eventId, UTI_UINT8 *eventName, UTI_UINT32 *UTCStartTime, UTI_UINT32 *UTCEndTime);


UTI_SINT32 UDRMEventIPPVOrder(UTI_UINT32 indexOfSector, UTI_UINT32 eventId);


UTI_SINT32 UDRMEventIPPVGetNumber(UTI_UINT32 indexOfSector, UTI_UINT32 *numberOfIPPV);


UTI_SINT32 UDRMEventIPPVGetInfo(UTI_UINT32 indexOfSector, UTI_UINT32 index, UTI_UINT32 *eventId, UTI_UINT16 *price, UTI_UINT32 *UTCStartTime, UTI_UINT32 *UTCEndTime);

UTI_SINT32 UDRMEventPPTOrder(UTI_UINT32 indexOfSector, UTI_UINT32 eventId);

UTI_SINT32 UDRMEventPPTGetNumber(UTI_UINT32 indexOfSector, UTI_UINT32 *numberOfPPT);


UTI_SINT32 UDRMEventPPTGetInfo(UTI_UINT32 indexOfSector, UTI_UINT32 index, UTI_UINT32 *eventId, UTI_UINT16 *price, UTI_UINT32 *payUnit, UTI_UINT32 *UTCStartTime, UTI_UINT32 *UTCEndTime);

UTI_SINT32 UDRMSectorViewLevelGet(UTI_UINT32 indexOfSector, UTI_UINT32 *level);

UTI_SINT32 UDRMSectorViewLevelSet(UTI_UINT32 indexOfSector, UTI_UINT32 level, UTI_UINT8 *pin, UTI_UINT8 *result);

UTI_SINT32 UDRMServiceViewLevelDisableTemp(UTI_UINT16 tunerID, UTI_UINT16 service_id, UTI_UINT8 *pin, UTI_UINT8 *result);


UTI_SINT32 UDRMSectorPinSet(UTI_UINT32 indexOfSector, const UTI_UINT8 *oldPIN, UTI_UINT8 *newPIN, UTI_UINT8 *result);

UTI_SINT32 UDRMSectorPinCheck(UTI_UINT32 indexOfSector, UTI_UINT8 *pin, UTI_UINT8 *result);

UTI_SINT32 UDRMWalletGet(UTI_UINT32 indexOfSector, UTI_UINT32 *value);

UTI_SINT32 UDRMCASystemIDCheck(UTI_UINT16 CASystemID);

UTI_SINT32 UDRMServiceStart(UTI_UINT16 tunerID, UTI_UINT16 PMTpid, UTI_UINT16 service_id);

UTI_SINT32 UDRMServiceDelete(UTI_UINT16 tunerID, UTI_UINT16 serviceId);

UTI_SINT32 UDRMServiceDeleteTs(UTI_UINT16 tunerID);

UTI_SINT32 UDRMUserSerialNumber(UTI_UINT8 *pu8NumberString);

UTI_SINT32 UDRMAppInfoSet(UTI_UINT16 u16ManufactureId, UTI_UINT32 u32ModuleId, UTI_UINT32 u32LoaderVersion);

UTI_SINT32 UDRMLoaderStatus(UDRM_LOADER_NOTIFY *pstLoaderStatus);

UTI_SINT32 UDRMBuildInformation(UTI_UINT8 *pu8String);
typedef void (*java_notify_callback)(UTI_UINT32 msg_type,UTI_UINT32 msg_code,UTI_UINT32 utc, UTI_UINT8* title, UTI_UINT8*  contend);
void jni_set_udrm_callback(java_notify_callback callfunc);
UTI_SINT32 gos_del_email(int  idx);
void gos_get_email(int  idx,void * email);



#endif

