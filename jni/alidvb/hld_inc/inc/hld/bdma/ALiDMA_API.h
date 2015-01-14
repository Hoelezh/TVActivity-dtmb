#ifndef __ALIDMA_API_H
#define __ALIDMA_API_H

#ifdef __cplusplus
extern "C" {
#endif

#define THREAD_NUM 5
typedef enum {
    DRV_NO_ERROR      = 0,
    DRV_ERROR         = 1
} DRV_Result;

typedef enum {
    DMAPI_NO_ERROR      = 0,
    DMAPI_ERROR         = 1
} DMAPI_Result;

#define ALiDMAGetThreadID() \
	pthread_t getthread = pthread_self();\
	int id;\
	for(id = 0; id<THREAD_NUM; id++){\
		if(threads_bdma[id].thread_id == getthread){\
			break;\
		}\
	}

int  ALiDMAOpen(void);
void ALiDMAReset(void);
void ALiDMAClose(void);
void ALiDMA_regDump(void);

DMAPI_Result ALiDMA_memset(unsigned int* buf_data, unsigned char val, unsigned int length, int mmu_mode);
DMAPI_Result ALiDMA_memcpy(void* buf_src, void* buf_dest, unsigned int length, int mmu_mode);
DMAPI_Result ALiOVG_blit(void* buf_src, void* buf_dest, unsigned int length, int mmu_mode);
DMAPI_Result ALiDMA_memcpr(char* buf_src, char* buf_dest, unsigned int length);
DMAPI_Result ALiDMA_2D_memcpr(char* buf_src, char* buf_dest
													, unsigned int sx, unsigned int sy
													, unsigned int dx, unsigned int dy
													, unsigned int sstride, unsigned int dstride
													, unsigned int w, unsigned int h
													, unsigned int byte_pixel);
DMAPI_Result ALiDMA_2D_blit(void* buf_src, void* buf_dest
													, unsigned int src_x, unsigned int src_y
													, unsigned int dst_x, unsigned int dst_y
													, unsigned int src_stride, unsigned int dst_stride
													, unsigned int width, unsigned int height
													, unsigned int bits_pixel, int mmu_mode);
DMAPI_Result ALiDMA_memset_RGBA(unsigned int* buf_data, unsigned int val, unsigned int length, int mmu_mode);
DMAPI_Result ALiDMA_memset_RGB(unsigned int* buf_data, unsigned short val, unsigned int length, int mmu_mode);
DMAPI_Result ALiDMA_2D_memset_RGBA(unsigned int* buf_data, unsigned int val
															 , unsigned int dst_x, unsigned int dst_y
															 , unsigned int dst_stride
															 , unsigned int width, unsigned int height
															 , unsigned int bits_pixel, int mmu_mode);
DMAPI_Result ALiDMA_2D_memset_RGB(unsigned int* buf_data, unsigned short val
															, unsigned int dst_x, unsigned int dst_y
															, unsigned int dst_stride
															, unsigned int width, unsigned int height
															, unsigned int bits_pixel, int mmu_mode);	
DMAPI_Result ALiDMA_2D_memset_A8(unsigned int* buf_data, unsigned char val
															 , unsigned int dst_x, unsigned int dst_y
															 , unsigned int dst_stride
															 , unsigned int width, unsigned int height
															 , unsigned int bits_pixel, int mmu_mode);															
DMAPI_Result ALiDMA_2D_mem_val_cpr(char* buf_dest
													, unsigned int value
													, unsigned int dst_x, unsigned int dst_y
													, unsigned int dst_stride
													, unsigned int width, unsigned int height
													, unsigned int byte_pixel);			
DMAPI_Result ALiDMA_2D_mem_val_cpr_a8(char* buf_dest
													, unsigned char value
													, unsigned int dst_x, unsigned int dst_y
													, unsigned int dst_stride
													, unsigned int width, unsigned int height
													, unsigned int byte_pixel);
DMAPI_Result ALiDMA_2D_mem_val_cpr_rgb(char* buf_dest
													, unsigned short value
													, unsigned int dst_x, unsigned int dst_y
													, unsigned int dst_stride
													, unsigned int width, unsigned int height
													, unsigned int byte_pixel);


DMAPI_Result ALiDMA_debug(unsigned int* buf_data, unsigned int ctl);
																																																																 

DMAPI_Result ALiDMA_set_block_mode(/*bool*/unsigned int enable);
DMAPI_Result ALiDMA_wait_finish(unsigned int timeout);
DMAPI_Result ALiDMA_syncOVG(void);
#ifdef __cplusplus 
}// extern "C"
#endif

#endif
