/****************************************************************************
 *
 *  ALi (Zhuhai) Corporation, All Rights Reserved. 2011 Copyright (C)
 *
 *  File: ali_fake.h
 *
 *  Description: This file contains all globe micros and functions declare
 *		             of fake trace reader ioctl commands.
 *
 *  History:
 *      Date            Author            Version   Comment
 *      ====        ======      =======  =======
 *     
 ****************************************************************************/
#ifndef __ADR_HLD_FAKE_TRACE_H_
#define __ADR_HLD_FAKE_TRACE_H_

#ifdef __cplusplus
extern "C" {
#endif

RET_CODE fake_kft_stop(void);
unsigned long fake_get_tick(const char *);

#ifdef __cplusplus
}
#endif

#endif