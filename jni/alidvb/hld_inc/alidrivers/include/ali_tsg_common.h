#ifndef _ALI_TSG_COMMON_H_
#define _ALI_TSG_COMMON_H_

#include <linux/types.h>

struct tsg_fast_copy_param
{
#ifdef __CHECKER__
    const char __user  *data;
#else
	const char *data;
#endif
    __s32 len;
};

#define ALI_TSG_IOC_MAGIC  0xA3

#define ALI_TSG_OUTPUT_CLK_SET _IOW(ALI_TSG_IOC_MAGIC, 41, __u8)

#define ALI_TSG_GET_CUR_DATA_LEN _IOR(ALI_TSG_IOC_MAGIC, 42, __u32)

#define ALI_TSG_NULL_PKT_INSERTION_START _IOW(ALI_TSG_IOC_MAGIC, 43, __u32)

#define ALI_TSG_NULL_PKT_INSERTION_STOP _IO(ALI_TSG_IOC_MAGIC, 44)

#define ALI_TSG_WRITE_FSTCPY   _IOW(ALI_TSG_IOC_MAGIC, 45, __u32)

#endif

