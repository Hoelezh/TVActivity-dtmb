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

#ifndef _ALI_FAKE_TRACE_COMMON_H_
#define _ALI_FAKE_TRACE_COMMON_H_

/* Encode I/O command */
#define FAKE_TRACE_KFT_START        _IOR('o', 11, unsigned long)      
#define FAKE_TRACE_KFT_STOP         _IOR('o', 12, unsigned long)   
#define FAKE_TRACE_SHOW_STACK_ALL   _IOR('o', 13, unsigned long)
#define FAKE_TRACE_SHOW_STACK_PID   _IOR('o', 14, unsigned long)
#define FAKE_TRACE_GET_TICK 	    _IOR('o', 15, unsigned long)
#define FAKE_TRACE_SHOW_MEMORY      _IOR('o', 16, unsigned long)
#define FAKE_TRACE_GET_MM_ADDR      _IO('o', 17)
#endif
