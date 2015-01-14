#ifndef _ALI_BASIC_COMMON_H_
#define _ALI_BASIC_COMMON_H_

#include <linux/ioctl.h>

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint16
#define uint16 unsigned short
#endif

#ifndef uint32
#define uint32 unsigned long
#endif

#ifndef uint64
#define uint64 unsigned long long;
#endif
#ifndef int8
#define int8 char
#endif

#ifndef int16
#define int16 short
#endif

#ifndef int32
#define int32 long
#endif

#ifndef int64
#define int64 long long 
#endif

/* Must sync wiht TDS: struct ctrl_blk. */
struct ctrl_blk{
       unsigned char stc_id_valid:1; // 1: valid, 0: invalid  
       unsigned char pts_valid:1; // 1:valid, 0:invalid  
       unsigned char data_continue:1; // 1:not continue, 0: continue
       unsigned char ctrlblk_valid:1; // 1:valid, 0: invalid	
       unsigned char instant_update:1; //provided by dec, 1:need update instantly, 0: NOT	
       unsigned char vob_start: 1;
	unsigned char reserve:2;
	unsigned char stc_id;
	unsigned long pts;
};



typedef int (*ali_dec_request_buf)(void *handle, void **buf_start, int *buf_size, struct ctrl_blk *blk);
typedef void (*ali_dec_update_buf)(void *handle, int buf_size);


struct ali_dec_input_callback_routine_pars
{
	void *handle;
	ali_dec_request_buf request_buf;
	ali_dec_update_buf update_buf;
};

#if 0
enum dmx_ts2sec_serv_err_code
{
    DMX_SEC_ERR_CODE_OK,
    DMX_SEC_ERR_CODE_EMPTY_BUF,
    DMX_SEC_ERR_CODE_BAD_POINTER_FIELD,
    DMX_SEC_ERR_CODE_MASK_MISSMATCH,
    DMX_SEC_ERR_CODE_DATA_LOST,
    DMX_SEC_ERR_CODE_CRC_FAIL,
    DMX_SEC_ERR_CODE_TS_SCRAMBLED,
};

typedef unsigned char* (*ali_dmx_sec_req_buf)(unsigned int para, unsigned int sec_len);
typedef int (*ali_dmx_sec_ret_buf)(unsigned int para, enum dmx_ts2sec_serv_err_code err_code, unsigned int sec_len);

//typedef INT32 (*ali_dmx_sec_cb)(struct dmx_device *dev, struct dmx_ts_pkt_inf *pkt_inf, UINT32 param);


#endif

#endif
