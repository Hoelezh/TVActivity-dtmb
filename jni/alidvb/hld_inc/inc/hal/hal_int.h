/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    hal_int.h
*
*    Description:    This file contains all functions about interrupt
*					 controler operations. Current suport M6303,
*					 M3325 CPU only.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Jun.17.2003       Justin Wu       Ver 0.1    Create file.
*	2.
*****************************************************************************/

#ifndef	__HAL_INT_H__
#define __HAL_INT_H__

#ifdef __cplusplus
extern "C" {
#endif

//#include <adr_sys_config.h>
#include <hal/mips.h>
#include <hal/machine.h>

#define HAL_INT_MASK_BIT_SET(num, val)							\
	({int __temp;												\
	__temp = read_32bit_cp0_register(C0_STATUS);				\
	if (num >= 8)												\
	{															\
		write_32bit_cp0_register(C0_STATUS, __temp | 0x0800);	\
		if((sys_ic_get_chip_id() != ALI_S3602)&&(sys_ic_get_chip_id() != ALI_S3602F)){								\
		if (val) {												\
			*((UINT32 *)(0xb800003c)) = (*((UINT32 *)(0xb800003c)) | (1 << (num - 8)));		\
		} else {												\
			*((UINT32 *)(0xb800003c)) = (*((UINT32 *)(0xb800003c)) & ~(1 << (num - 8)));	\
		}}else if(sys_ic_get_chip_id() == ALI_S3602){			\
		if (num >= 40 )											\
		{														\
			if (val) {											\
				*((UINT32 *)(0xb800002c)) = (*((UINT32 *)(0xb800002c)) | (1 << (num - 32 - 8)));	\
				*((UINT32 *)(0xb800003c)) = (*((UINT32 *)(0xb800003c)) | (1 << (num - 32 - 8)));	\
			} else {											\
				*((UINT32 *)(0xb800003c)) = (*((UINT32 *)(0xb800003c)) & ~(1 << (num - 32 - 8)));	\
			}													\
		} else {												\
			if (val) {											\
				*((UINT32 *)(0xb8000028)) = (*((UINT32 *)(0xb8000028)) | (1 << (num - 8)));		\
				*((UINT32 *)(0xb8000038)) = (*((UINT32 *)(0xb8000038)) | (1 << (num - 8)));		\
			} else {											\
				*((UINT32 *)(0xb8000038)) = (*((UINT32 *)(0xb8000038)) & ~(1 << (num - 8)));	\
			}													\
		}														\
		}else if(sys_ic_get_chip_id() == ALI_S3602F){			\
		if (num >= 40 )											\
		{														\
			if (val) {											\
				/* *((UINT32 *)(0xb800002c)) = (*((UINT32 *)(0xb800002c)) | (1 << (num - 32 - 8)));	*/ \
				*((UINT32 *)(0xb800003c)) = (*((UINT32 *)(0xb800003c)) | (1 << (num - 32 - 8)));	\
			} else {											\
				*((UINT32 *)(0xb800003c)) = (*((UINT32 *)(0xb800003c)) & ~(1 << (num - 32 - 8)));	\
			}													\
		} else {												\
			if (val) {											\
				/* *((UINT32 *)(0xb8000028)) = (*((UINT32 *)(0xb8000028)) | (1 << (num - 8))); */ \
				*((UINT32 *)(0xb8000038)) = (*((UINT32 *)(0xb8000038)) | (1 << (num - 8)));		\
			} else {											\
				*((UINT32 *)(0xb8000038)) = (*((UINT32 *)(0xb8000038)) & ~(1 << (num - 8)));	\
			}													\
		}														\
		}														\
	} else {													\
		if (val) {												\
			write_32bit_cp0_register(C0_STATUS,__temp | (1 << (num + 8)));	\
		} else {												\
			write_32bit_cp0_register(C0_STATUS,__temp & ~(1 << (num + 8)));	\
	}}})

#ifdef __cplusplus
		}
#endif

#endif	/* __HAL_INT_H__ */
