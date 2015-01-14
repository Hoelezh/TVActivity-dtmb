/*
 *  Copyright (c) 2012, ALi Corporation.
 *  All rights reserved.
 *
 *      File:           ali_bdma.h
 *      Version:        1.0
 *      Date:           2012-03-09
 *      Description:    ali bdma module interface file.
 */

#ifndef ALI_BDMA_H_
#define ALI_BDMA_H_

typedef float          BDMAfloat;
typedef signed char    BDMAbyte;
typedef unsigned char  BDMAubyte;
typedef signed short   BDMAshort;
typedef signed int     BDMAint;
typedef unsigned int   BDMAuint;
typedef unsigned int   BDMAbitfield;

typedef enum  {
    ALIBDMA_COPY = 0,
    ALIBDMA_SET,
    ALIBDMA_OVG_BLIT,
}operation_type;

typedef enum  {
    MMU_SRC_ON_DST_ON = 0,
    MMU_SRC_ON_DST_OFF,
    MMU_SRC_OFF_DST_ON,
    MMU_SRC_OFF_DST_OFF,
}operation_mode;

typedef enum  {
    ALIBDMA_8_BIT = 1,
    ALIBDMA_16_BIT,
    ALIBDMA_24_BIT,
    ALIBDMA_32_BIT,
}operation_bits_pixel;

typedef struct {
    BDMAuint             source_data;
    BDMAuint             destination_address;
    BDMAuint             copy_length;
    operation_bits_pixel bits_pixel;
    operation_type       type;
    operation_mode       mmu_mode;
    BDMAuint             private_data;	/* can be used to return handle */
    /*bool*/BDMAuint                 ovg_sync;	/* Sync OVG finish 20121102 by Allen */
}ali_hwdma_job;

typedef struct {
    BDMAuint             source_data;
    BDMAuint             destination_address;
    BDMAuint             src_x;
    BDMAuint             src_y;
    BDMAuint             dst_x;
    BDMAuint             dst_y;
    BDMAuint             src_stride;
    BDMAuint             dst_stride;
    BDMAuint             height;
    BDMAuint             width;
    operation_bits_pixel bits_pixel;
    operation_type       type;
    operation_mode       mmu_mode;
    BDMAuint             private_data;	/* can be used to return handle */
    /*bool*/BDMAuint                 ovg_sync;	/* Sync OVG finish 20121102 by Allen */
}ali_hwdma_2Djob;

struct ali_dma_pdtRecord
{
	unsigned int *pdt;
	unsigned int tgid;
	unsigned int ref;
	struct ali_dma_pdtRecord *next;
};

#endif /* ALI_BDMA_H_ */
