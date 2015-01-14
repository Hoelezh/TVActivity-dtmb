#ifndef  _ALI_CE_H_
#define  _ALI_CE_H_

#include <linux/types.h>
#include <ali_ce_common.h>

int ali_ce_key_generate(pCE_DEVICE pCeDev, pCE_DATA_INFO pCe_data_info);
int ali_ce_key_load(pCE_DEVICE pCeDev, pOTP_PARAM pCe_opt_info);
int ali_ce_ioctl(CE_DEVICE *pCeDev,__u32 cmd,__u32 param);
int ali_ce_generate_cw_key(__u8 *in_cw_data,__u8 mode, \
							__u8 first_pos,__u8 second_pos);

int ali_ce_load_otp_key(__u32 key_pos);

int ali_ce_generate_key_by_aes(__u8 *key, __u32 first_key_pos, \
									__u32 second_key_pos,__u32 ce_crypt_select);


int ali_ce_generate_single_level_key(pCE_DEVICE pCeDev, pCE_DATA_INFO pCe_data_info);

int ali_aes_generate_key_with_multi_keyladder
(
	pAES_KEY_LADDER_BUF_PARAM pCeAesparam, __u8 *key_pos
);

/*api for kernel load 2 level keys to CE*/
int ali_decrypt_2_level_key(__u8 * pos, __u8 * _r1, __u8* _r2);

#endif  /*_CRYPTO_H_*/

