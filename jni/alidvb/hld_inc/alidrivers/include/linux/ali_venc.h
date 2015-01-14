/*******************************************************************************

File name   : ali_venc.h

Description : Video driver stack LINUX platform OS driver header file

Author      : Vic Zhang <Vic.Zhang@Alitech.com>

Create date : Oct 18, 2013

COPYRIGHT (C) ALi Corporation 2013

Revision history:
--------------------------------------------------------------------------------
Date                        Modification           Revision              Name
-------------               ------------          ----------         -----------
Oct 18, 2013                   Created               V0.1             Vic.Zhang

*******************************************************************************/

/* Define to prevent recursive inclusion */

#ifndef __ALI_VIDENC_H__
#define __ALI_VIDENC_H__


/** The total memory of Encoder is 16M. */
/*  The initial allocated memeory table:
    Y buffer start address is 0xA4000000 and its size is 2M.
    C buffer start address is 0xA4200000 and its size is 1M.
   Bitstream start address is 0xA4300000 and its size is 3M.
     Encoder start address is 0xA4600000 and its size is 10M.
*/
/*
#define _MM_VENC_PRIVATE_BUFFER_            0xA4000000
#define _MM_VENC_PRIVATE_BUFFER_SIZE_       0x1000000
*/

/** The total memory of Encoder is 6M. */
/*  2M 1M 3M-1K 1K  */
/*
#define _MM_VENC_SBM_BUFFER_                0xA5000000
#define _MM_VENC_SBM_BUFFER_SIZE_           0x600000
*/

#define VENC_NUM                    4

#define VENC_REQ_OK	                0
#define VENC_REQ_FAIL	            1
#define VENC_REQ_BUSY	            2

#define VENC_MUTEX_LOCK             0
#define VENC_SPIN_LOCK              1

struct videnc_config {
    unsigned int buffer_addr;
    unsigned int buffer_size;
};

struct videnc_desc{
    struct videnc_config *venc_cfg_p;
    unsigned char status;
    unsigned int valid_size;
	unsigned int read_pos;
	unsigned int write_pos;
	int mutex;
};

struct videnc_trigger_para{
    unsigned int frm_width;
    unsigned int frm_height;
    unsigned int Y_length;
    unsigned int C_length;
    unsigned int encoder_ID;
    unsigned int job_status;
};

struct videnc_see_config {
    unsigned int buffer_addr;
    unsigned int buffer_size;
    int y_sbm_idx;
    int c_sbm_idx;
    int status_idx;
    int yuv_width;
    int yuv_height;
};

#define VENC_MAGIC                  'v'
#define VENC_IOWR_CREATE           _IOW(VENC_MAGIC, 0, struct videnc_see_config)
#define VENC_IOWR_RELEASE          _IO(VENC_MAGIC, 1)
#define VENC_IOWR_STOP             _IOW(VENC_MAGIC, 2, unsigned int)
#define VENC_IOWR_ENCODE           _IOW(VENC_MAGIC, 3, struct videnc_trigger_para)
#define VENC_IOWR_SBMMEM           _IOR(VENC_MAGIC, 4, struct videnc_config)
#define VENC_IOWR_SELFMEM          _IOR(VENC_MAGIC, 5, struct videnc_config)
#define VENC_IOWR_BS_MAPADDR       _IOW(VENC_MAGIC, 6, unsigned long)
#define VENC_IOWR_START            _IOW(VENC_MAGIC, 7, struct videnc_see_config)


#endif

