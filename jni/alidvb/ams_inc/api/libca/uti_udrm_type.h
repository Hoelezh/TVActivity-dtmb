#ifndef _UTI_UDRM_TYPE_H_
#define _UTI_UDRM_TYPE_H_

#include "unitend.h"
typedef struct _udrm_mail_
{
	UTI_UINT8 displayType;
	UTI_UINT32 utc;
	UTI_UINT8 title[20];		// end with '\0'
	UTI_UINT8 content[255];	// end with '\0'
}UDRM_MAIL;

typedef struct _udrm_osd_
{
	UTI_UINT8 displayType;	// include message
	UTI_UINT32 utc;
	UTI_UINT16 during;
	UTI_UINT8 content[255];
}UDRM_OSD;

typedef struct _udrm_service_status_notify_
{
	UTI_UINT16 tunerID;
	UTI_UINT16 serviceId;
	UTI_UINT8 sectorIndex;
	UTI_UINT8 stringErrorIndex;
}UDRM_SERVICE_NOTIFY;

typedef struct _udrm_ippv_notify_
{
	UTI_UINT16 tunerID;
	UTI_UINT16 serviceId;
	UTI_UINT8 sectorIndex;
	UTI_UINT32 eventID;
	UTI_UINT8 eventInfo[64];
	UTI_UINT32 price;
	UTI_UINT32 utcStartTime;
	UTI_UINT32 utcEndTime;
}UDRM_IPPV_NOTIFY;

typedef struct _udrm_ppt_notify_
{
	UTI_UINT16 tunerID;
	UTI_UINT16 serviceId;
	UTI_UINT8 sectorIndex;
	UTI_UINT32 eventID;
	UTI_UINT8 eventInfo[64];
	UTI_UINT32 price;
	UTI_UINT32 payUnit;
	UTI_UINT32 utcStartTime;
	UTI_UINT32 utcEndTime;
}UDRM_PPT_NOTIFY;

typedef struct _udrm_finger_notify_
{
	UTI_UINT16 tunerID;
	UTI_UINT32 fingerID;
}UDRM_FINGER_NOTIFY;


typedef struct _udrm_loader_notify_
{
	UTI_UINT8 u8EMMTriggerType;
	UTI_UINT16 u16ManufactureId;
	UTI_UINT32 u32ModuleId;
	UTI_UINT32 u32LoaderVersion;
	UTI_UINT32 u32SoftwareVersion;
	UTI_UINT16 u16ServiceId;
	UTI_UINT8 u8GlobalTriggerValid;		// 0 - u16GlobalTriggerType无效，此时u8EMMTriggerType有效；1 - u16GlobalTriggerType有效，此时u8EMMTriggerType无效
	UTI_UINT32 u16GlobalTriggerType;
	UTI_UINT8 u8OperatorIdMatchValid;
	UTI_UINT16 u16OperatorId;
	UTI_UINT8 u8AreaIdMatchValid;
	UTI_UINT32 u32AreaId;
	UTI_UINT8 u8SoftwareVersionMatchValid;
	UTI_UINT32 u32CertainSoftwareVersion;
}UDRM_LOADER_NOTIFY;

/*
type:
		1 - mail
		2 - osd
		3 - IPPV
		4 - PPT
		5 - service status
		6 - finger
		7 - loader
*/
typedef struct _ca_notify_
{
	UTI_UINT32 notifyType;

	union
	{
		UDRM_MAIL mail;
		UDRM_OSD osd;
		UDRM_IPPV_NOTIFY ippv;
		UDRM_PPT_NOTIFY ppt;
		UDRM_SERVICE_NOTIFY service;
		UDRM_FINGER_NOTIFY finger;
		UDRM_LOADER_NOTIFY loader;
	}notify;

}UDRM_NOTIFY;

#endif

