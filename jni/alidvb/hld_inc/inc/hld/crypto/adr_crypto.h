#ifndef  _ADR_CRYPTO_H_
#define  _ADR_CRYPTO_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <adr_basic_types.h>
#include <ali_ce_common.h>


#define ALI_CE_LINUX_DEV_PATH "/dev/ali_ce_0"
#define ALI_CE_HLD_DEV_NAME "ali_ce_0"

//#define ALI_CE_HLD_TDS_DBG
//#define ALI_CE_HLD_COMN_DBG
//#define ALI_CE_HLD_BASIC_DBG
//#define ALI_CE_HLD_UTILS_DBG

#ifndef HLD_DEV_TYPE_CE
#define HLD_DEV_TYPE_CE         0x011f0000   /*CE module*/
#endif

int ce_api_attach(void);
int ce_api_detach(void);

int ce_ioctl(pCE_DEVICE pCeDev,UINT32 cmd,UINT32 param);

int ce_key_generate(pCE_DEVICE pCeDev,pCE_DATA_INFO pCe_data_info);
int ce_key_load(pCE_DEVICE pCeDev,pOTP_PARAM pCe_opt_info);

int ce_generate_cw_key(UINT8 *in_cw_data,UINT8 mode, \
							UINT8 first_pos,UINT8 second_pos);

int ce_generate_single_level_key(pCE_DEVICE pCeDev, \
									pCE_DATA_INFO pCe_data_info);

int aes_generate_key_with_multi_keyladder(pAES_KEY_LADDER_BUF_PARAM pCeAesparam, UINT8 *key_pos);
int ce_load_otp_key(UINT32 key_pos); //load root key from fix otp address
int ce_generate_key_by_aes(UINT8 *key, UINT32 first_key_pos, UINT32 second_key_pos,UINT32 ce_crypt_select);
int tdes_decrypt_key_to_ce_one_level(UINT8 *eck, UINT8 level_one, enum CE_CRYPT_TARGET level_gen);
int tdes_decrypt_to_ce_two_level(UINT8 *input,UINT8 level_root,UINT8 *key_pos);
int aes_decrypt_setup_kl_three_level(UINT8 *input,UINT8 root_pos,UINT8 *key_pos);
int tdes_decrypt_setup_kl_three_level(UINT8 *input,UINT8 root_pos,UINT8 *key_pos);
#ifdef __cplusplus
}
#endif
#endif  /*_CRYPTO_H_*/
