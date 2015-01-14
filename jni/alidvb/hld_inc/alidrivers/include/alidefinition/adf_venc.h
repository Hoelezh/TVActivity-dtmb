/*******************************************************************************

File name   : adf_venc.h

Description : Video driver stack LINUX platform OS encoder API header file

Author      : Vic Zhang <Vic.Zhang@Alitech.com>

Create date : Jan 20, 2014

COPYRIGHT (C) ALi Corporation 2013

Revision history:
--------------------------------------------------------------------------------
Date                        Modification           Revision              Name
-------------               ------------          ----------         -----------
Jan 20, 2013                   Created               V0.1             Vic.Zhang

*******************************************************************************/

/* Define to prevent recursive inclusion */

#ifndef __ALI_ADFVENC_H__
#define __ALI_ADFVENC_H__


typedef enum {
	VENC_UNKNOWN    = -1,
    VENC_AVC        = 1,
	VENC_JPEG ,
} VENC_FORMAT;

typedef struct VENC_PARAMS
{
    char *inFile;
    int   nWidth;
    int   nHeight;
    VENC_FORMAT encType;
    char *bitstreams;
} VENC_PARAMS_t;

#if 1
#define osal_printf printf
#else
#define osal_printf(...)	do{}while(0)
#endif

/*
#define VENC_ERROR(args...)     \
                    osal_printf("In %s, func %s, line %d.\n", __FILE__, __FUNCTION__, __LINE__);\
                    osal_printf(args)
*/
#define VENC_ERROR(args...) osal_printf(args)

//#define VENC_ERROR(args...)		amslog_log(LOG_ERR, __FUNCTION__, __LINE__, args)//amslog_error(LOG_IMGDEC, args)
#define VENC_NOTICE VENC_ERROR
#define VENC_DEBUG  VENC_ERROR

int videnc_init(void);
int videnc_uninit(void);
int videnc_encode(const VENC_PARAMS_t *params);




#endif /* __ALI_ADFVENC_H__ */
