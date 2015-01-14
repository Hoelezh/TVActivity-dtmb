#ifndef _ALI_DSC_H_
#define _ALI_DSC_H_

#include <linux/types.h>
#include <ali_dsc_common.h>


int ali_des_decrypt(DES_DEV *pDesDev,__u16 stream_id, \
					__u8 *input, __u8 *output, \
					__u32 total_length);
int ali_des_encrypt(DES_DEV *pDesDev,__u16 stream_id, \
					__u8 *input, __u8 *output, \
					__u32 total_length);
int ali_des_ioctl(DES_DEV *pDesDev ,__u32 cmd , __u32 param);

int ali_aes_decrypt(AES_DEV *pAesDev,__u16 stream_id, \
					__u8 *input, __u8 *output, \
					__u32 total_length);
int ali_aes_encrypt(AES_DEV *pAesDev,__u16 stream_id, \
					__u8 *input, __u8 *output, \
					__u32 total_length);
int ali_aes_ioctl(AES_DEV *pAesDev ,__u32 cmd ,__u32 param);

int ali_csa_ioctl(CSA_DEV *pCsaDev,__u32 cmd,__u32 param);
int ali_csa_decrypt(CSA_DEV *pCsaDev,__u16 stream_id, \
					__u8 *input, __u8 *output, \
					__u32 total_length);

int ali_dsc_ioctl( DSC_DEV *pDscDev ,__u32 cmd , __u32 param);
int ali_DeEncrypt(DEEN_CONFIG *p_DeEn,__u8 *input, \
					__u8 *output, __u32 total_length);
__u16 ali_dsc_get_free_stream_id(enum DMA_MODE dma_mode);

 __u32 ali_dsc_get_free_sub_device_id(__u8 sub_mode);
int ali_dsc_set_sub_device_id_idle(__u8 sub_mode,__u32 device_id);
int ali_dsc_set_stream_id_idle(__u32 pos); 
void ali_dsc_set_stream_id_used(__u32 pos);
int ali_dsc_set_sub_device_id_used(enum WORK_SUB_MODULE sub_mode, \
										__u32 device_id);
int ali_dsc_deal_quantum_for_mixed_ts(DEEN_CONFIG *p_DeEn, \
											__u32 temp_length);

int ali_sha_ioctl(SHA_DEV *pShaDev, __u32 cmd , __u32 param);
int ali_trig_ram_mon(__u32 start_addr,__u32 end_addr, __u32 interval, \
						__u32 sha_mode, int DisableOrEnable);
int ali_aes_crypt_puredata_with_ce_key(__u8 *input, __u8 *output, \
							__u32 length, __u32 key_pos, enum CRYPT_SELECT sel);
int ali_sha_digest(SHA_DEV *pShaDev, __u8 *input, __u8 *output,__u32 data_length);
int ali_sha_digest_user_s(SHA_DEV *pShaDev, __u8 *input, __u8 *output, \
							__u32 data_length,__u8 *input_s);	

int ali_create_sha_ramdrv(char* input,__u32 len ,__u8 *output);

int ali_calculate_hmac(__u8 *input, __u32 length, \
						__u8 *output, __u8 *key);
int ali_verify_mac_addr(__u8 *mac, __u32 len, __u8 *clear_mac);

int ali_aes_cbc_decrypt_ramdata(__u8 key_pos, __u8 *input, \
									__u8 *output, __u32 data_len);


#endif 
