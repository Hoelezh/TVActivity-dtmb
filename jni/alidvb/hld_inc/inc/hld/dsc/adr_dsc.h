#ifndef __ADR_DSC_H_
#define  __ADR_DSC_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <adr_basic_types.h>
#include <ali_dsc_common.h>

/*
#define ALI_DSC_HLD_TDS_DBG
#define ALI_DSC_HLD_COM_DBG
#define ALI_DSC_HLD_CA_DBG
#define ALI_DSC_HLD_BASIC_DBG
*/

#ifndef HLD_DEV_TYPE_DSC
#define HLD_DEV_TYPE_DSC        0x011e0000   /*DSC module*/
#define HLD_DEV_TYPE_DES         0x01200000   /*DSC module*/
#define HLD_DEV_TYPE_AES         0x01210000   /*DSC module*/
#define HLD_DEV_TYPE_SHA         0x01220000   /*DSC module*/
#define HLD_DEV_TYPE_CSA         0x01230000   /*DSC module*/
#define HLD_DEV_TYPE_MASK		0xFFFF0000	/* Device type mask */
#define HLD_MAX_DEV_NUMBER		32			/* Max device number */
#endif

#define ALI_CSA_LINUX_DEV_PATH "/dev/ali_csa_0"
#define ALI_AES_LINUX_DEV_PATH "/dev/ali_aes_0"
#define ALI_DES_LINUX_DEV_PATH "/dev/ali_des_0"
#define ALI_SHA_LINUX_DEV_PATH "/dev/ali_sha_0"
#define ALI_DSC_LINUX_DEV_PATH "/dev/ali_dsc_0"


#define MEM_ALLOC_UNIT 128*1024
#define DSC_U_MEM_SIZE 1024*1024

extern UINT32 g_sha_ex_buf;

//1  API
int dsc_api_attach(void);
int dsc_api_detach(void);
int des_decrypt(pDES_DEV pDesDev,UINT16 dmx_id,  UINT8 *input, \
				UINT8 *output, UINT32 total_length);
int des_encrypt(pDES_DEV pDesDev,UINT16 dmx_id,  UINT8 *input, \
				UINT8 *output, UINT32 total_length);
int des_ioctl( pDES_DEV pDesDev ,UINT32 cmd , UINT32 param);

int aes_decrypt(pAES_DEV pAesDev,UINT16 dmx_id,  UINT8 *input, \
					UINT8 *output, UINT32 total_length);
int aes_encrypt(pAES_DEV pAesDev,UINT16 dmx_id,  UINT8 *input, \
				UINT8 *output, UINT32 total_length);
int aes_ioctl( pAES_DEV pAesDev ,UINT32 cmd , UINT32 param);

int csa_decrypt(pCSA_DEV pCsaDev,UINT16 dmx_id,  UINT8 *input, \
				UINT8 *output, UINT32 total_length);
int csa_ioctl( pCSA_DEV pCsaDev ,UINT32 cmd , UINT32 param);

int sha_ioctl( pSHA_DEV pShaDev ,UINT32 cmd , UINT32 param);
int sha_digest(pSHA_DEV pShaDev, UINT8 *input, UINT8 *output,UINT32 data_length);

int dsc_ioctl( pDSC_DEV pDscDev,UINT32 cmd , UINT32 param);
int trig_ram_mon(UINT32 start_addr,UINT32 end_addr, UINT32 interval, \
					enum SHA_MODE sha_mode,int DisableOrEnable);
int DeEncrypt(pDEEN_CONFIG p_DeEn,UINT8 *input, \
				UINT8 *output,UINT32 total_length);
UINT16 dsc_get_free_stream_id(enum DMA_MODE dma_mode);
UINT32 dsc_get_free_sub_device_id(enum WORK_SUB_MODULE sub_mode);
int dsc_set_sub_device_id_idle(enum WORK_SUB_MODULE sub_mode, \
									UINT32 device_id);
int dsc_set_sub_device_id_used(enum WORK_SUB_MODULE sub_mode, \
									UINT32 device_id);
int dsc_set_stream_id_idle(UINT32 pos); 
void dsc_set_stream_id_used(UINT32 pos); 
int dsc_operate_mem(pDSC_DEV pDscDev ,UINT32 cmd , UINT32 param);
void *dsc_get_mem(struct ali_dsc_krec_mem *krec_mem);
void dsc_put_mem(void *addr, UINT32 size);

int aes_pure_ecb_crypt(UINT8 *key, UINT8 *input, UINT8 *output, \
							UINT32 length, UINT8 crypt_mode ); 
int aes_pure_cbc_crypt( UINT8 *key, UINT8 *iv, UINT8 *input, \
						UINT8 *output, UINT32 length, UINT8 crypt_mode );
int aes_pure_ctr_crypt( UINT8 *key, UINT8 *ctr, UINT8 *input, UINT8 *output, \
						UINT32 length, UINT8 crypt_mode );


#ifdef __cplusplus
}
#endif

#endif 

