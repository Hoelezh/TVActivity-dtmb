/****************************************************************************
 *
 *  ALi (Zhuhai) Corporation, All Rights Reserved. 2002 Copyright (C)
 *
 *  File: ali_stc.h
 *
 *  Description: ali system time clock
 *s
 *  History:
 *      Date             Author         Version      Comment
 *      ======           ======          =====       =======
 *  1.  2011.09.14       Dylan.Yang     0.1.000     First version Created
 ****************************************************************************/
#ifndef __ALI_STC_COMMON_H
#define __ALI_STC_COMMON_H
 
#define STC_NUM                  2

#define STC_MAGIC                0x57
#define STCIO_SET_DIVISOR        _IOW(STC_MAGIC, 0, unsigned int)
#define STCIO_SET_VALID          _IOW(STC_MAGIC, 1, unsigned int)
#define STCIO_PAUSE_STC          _IOW(STC_MAGIC, 2, unsigned int)

#endif
