#ifndef  _ADF_CE_H_
#define  _ADF_CE_H_

#define IO_CE_BASE                                                            (0x52<<8)
#define  IO_OTP_ROOT_KEY_GET           					(IO_CE_BASE + 0)
#define  IO_SECOND_KEY_GENERATE        					(IO_CE_BASE + 1)
#define  IO_CRYPT_DATA_INPUT           						(IO_CE_BASE + 2)
#define  IO_CRYPT_PARAM_SET            						(IO_CE_BASE + 3)
#define  IO_CRYPT_SECOND_KEY_CONFIG    				(IO_CE_BASE + 4)
#define  IO_CRYPT_DEBUG_GET_KEY        					(IO_CE_BASE + 5)  
#define  IO_CRYPT_POS_IS_OCCUPY        					(IO_CE_BASE + 6)
#define  IO_CRYPT_POS_SET_USED         					(IO_CE_BASE + 7)
#define  IO_CRYPT_POS_SET_IDLE         					(IO_CE_BASE + 8)
#define  IO_CRYPT_FOUND_FREE_POS       					(IO_CE_BASE + 9)
#define  IO_DECRYPT_PVR_USER_KEY       					(IO_CE_BASE + 10)

#define CE_IO_CMD(cmd)  (cmd & 0xFF)

#define INVALID_ALI_CE_KEY_POS 0xff
#define AES_HW_KEY_LEN         16
#define HLD_MAX_NAME_SIZE      16 

#ifndef RET_SUCCESS
#define RET_SUCCESS ((int)0)
#define RET_FAILURE	((int)1)
#endif

#define AES_CE_KEY_LEN  16
#define TDES_CE_KEY_LEN  8

#define OTP_ADDESS_1 0x4d
#define OTP_ADDESS_2 0x51
#define OTP_ADDESS_3 0x55
#define OTP_ADDESS_4 0x59
#define OTP_ADDESS_5 0x60
#define OTP_ADDESS_6 0x64
#define OTP_ADDESS_7 0x68
#define OTP_ADDESS_8 0x6c

enum ce_status
{
	CE_INIT_SUCCESS = RET_SUCCESS,
	CE_INIT_FAILED,
	CE_ALREADY_INITIALIZED,
	CE_NOT_INIT,
};

enum CE_OTP_KEY_SEL
{
	OTP_KEY_0_0=0,
	OTP_KEY_0_1=1,
	OTP_KEY_0_2=2,
	OTP_KEY_0_3=3
};

enum  HDCP_DECRYPT_MODE
{
	NOT_FOR_HDCP=0,
	TARGET_IS_HDCP_KEY_SRAM=(1<<14)
};

enum CE_CRYPT_TARGET
{
	CRYPT_KEY_1_0=0x4,
	CRYPT_KEY_1_1=0x5,
	CRYPT_KEY_1_2=0x6,
	CRYPT_KEY_1_3=0x7,

	CRYPT_KEY_2_0=0x8,
	CRYPT_KEY_2_1=0x9,
	CRYPT_KEY_2_2=0xa,
	CRYPT_KEY_2_3=0xb,
	CRYPT_KEY_2_4=0xc,
	CRYPT_KEY_2_5=0xd,
	CRYPT_KEY_2_6=0xe,
	CRYPT_KEY_2_7=0xf,

	CRYPT_KEY_3_0=0x10,
	CRYPT_KEY_3_1=0x11,
	CRYPT_KEY_3_2=0x12,
	CRYPT_KEY_3_3=0x13,
	CRYPT_KEY_3_4=0x14,
	CRYPT_KEY_3_5=0x15,
	CRYPT_KEY_3_6=0x16,
	CRYPT_KEY_3_7=0x17,
	CRYPT_KEY_3_8=0x18,
	CRYPT_KEY_3_9=0x19,
	CRYPT_KEY_3_10=0x1a,
	CRYPT_KEY_3_11=0x1b,
	CRYPT_KEY_3_12=0x1c,
	CRYPT_KEY_3_13=0x1d,
	CRYPT_KEY_3_14=0x1e,
	CRYPT_KEY_3_15=0x1f,

	CRYPT_KEY_3_16=0x20,
	CRYPT_KEY_3_17=0x21,
	CRYPT_KEY_3_18=0x22,
	CRYPT_KEY_3_19=0x23,
	CRYPT_KEY_3_20=0x24,
	CRYPT_KEY_3_21=0x25,
	CRYPT_KEY_3_22=0x26,
	CRYPT_KEY_3_23=0x27,
	CRYPT_KEY_3_24=0x28,
	CRYPT_KEY_3_25=0x29,
	CRYPT_KEY_3_26=0x2a,
	CRYPT_KEY_3_27=0x2b,
	CRYPT_KEY_3_28=0x2c,
	CRYPT_KEY_3_29=0x2d,
	CRYPT_KEY_3_30=0x2e,
	CRYPT_KEY_3_31=0x2f,

	CRYPT_KEY_3_32=0x30,
	CRYPT_KEY_3_33=0x31,
	CRYPT_KEY_3_34=0x32,
	CRYPT_KEY_3_35=0x33,
	CRYPT_KEY_3_36=0x34,
	CRYPT_KEY_3_37=0x35,
	CRYPT_KEY_3_38=0x36,
	CRYPT_KEY_3_39=0x37,

	CRYPT_KEY_3_40=0x38,
	CRYPT_KEY_3_41=0x39,
	CRYPT_KEY_3_42=0x3a,
	CRYPT_KEY_3_43=0x3b,
	CRYPT_KEY_3_44=0x3c,
	CRYPT_KEY_3_45=0x3d,
	CRYPT_KEY_3_46=0x3e,
	CRYPT_KEY_3_47=0x3f,	
	
	HDCP_KEY_0=0x10,
	HDCP_KEY_1=0x11,
	HDCP_KEY_2=0x12,
	HDCP_KEY_3=0x13,
	HDCP_KEY_4=0x14,
	HDCP_KEY_5=0x15,
	HDCP_KEY_6=0x16,
	HDCP_KEY_7=0x17,
	HDCP_KEY_8=0x18,
	HDCP_KEY_9=0x19,
	HDCP_KEY_10=0x1a,
	HDCP_KEY_11=0x1b,
	HDCP_KEY_12=0x1c,
	HDCP_KEY_13=0x1d,
	HDCP_KEY_14=0x1e,
	HDCP_KEY_15=0x1f,
	HDCP_KEY_16=0x0f,
};

enum CE_KEY
{
	KEY_0_0=0,
	KEY_0_1=1,
	KEY_0_2=2,
	KEY_0_3=3,
	KEY_1_0=4,
	KEY_1_1=5,
	KEY_1_2=6,
	KEY_1_3=7,
	KEY_2_0=8,
	KEY_2_1=9,
	KEY_2_2=0xa,
	KEY_2_3=0xb,
	KEY_2_4=0xc,
	KEY_2_5=0xd,
	KEY_2_6=0xe,
	KEY_2_7=0xf,
	KEY_3_0=0x10,
	KEY_3_1=0x11,
	KEY_3_2=0x12,
	KEY_3_3=0x13,
	KEY_3_4=0x14,
	KEY_3_5=0x15,
	KEY_3_6=0x16,
	KEY_3_7=0x17,
	KEY_3_8=0x18,
	KEY_3_9=0x19,
	KEY_3_10=0x1a,
	KEY_3_11=0x1b,
	KEY_3_12=0x1c,
	KEY_3_13=0x1d,
	KEY_3_14=0x1e,
	KEY_3_15=0x1f,
};

enum CE_IV_SELECT
{  
	IV_AS_ZERO = 0,
	IV_FROM_REGISTER=1
};

enum CE_CRYPT_SELECT
{  
	CE_IS_DECRYPT = 1,
	CE_IS_ENCRYPT=0
};

enum CE_MODULE_SELECT
{  
	CE_SELECT_DES= 0,
	CE_SELECT_AES = 1,    
};

enum HDCP_KEY_SELECT
{
	CE_KEY_READ=0,
	HDCP_KEY_READ=1
};

enum ce_key_level
{
	SKIP_LEVEL = 0 ,
	ONE_LEVEL,
	TWO_LEVEL,
	THREE_LEVEL
};

typedef struct aes_key_ladder_param 
{ 
	unsigned int key_ladder;      // 1,2,3 
	unsigned int root_key_pos;
	unsigned char r[256];           //16 groups key
}AES_KEY_LADDER_BUF_PARAM, *pAES_KEY_LADDER_BUF_PARAM; 


typedef struct ce_pvr_key_param
{
	unsigned char *input_addr;
	unsigned int second_pos;  
	unsigned int first_pos;   
}CE_PVR_KEY_PARAM, *pCE_PVR_KEY_PARAM;

typedef struct otp_param
{
	unsigned char otp_addr;
	enum CE_OTP_KEY_SEL  otp_key_pos;   
}OTP_PARAM, *pOTP_PARAM;

typedef struct data_param
{
	unsigned int crypt_data[4] ; /*for des 2 words, for aes 4 words*/
	unsigned int data_len ;
}DATA_PARAM, *pDATA_PARAM;

typedef struct  des_param
{
	enum CE_CRYPT_SELECT  crypt_mode;
	enum CE_MODULE_SELECT aes_or_des;
	unsigned char des_low_or_high;
}DES_PARAM, *pDES_PARAM;

typedef struct ce_key_param
{
	enum CE_KEY first_key_pos;
	enum CE_CRYPT_TARGET second_key_pos;
	enum  HDCP_DECRYPT_MODE hdcp_mode ;
}CE_KEY_PARAM, *pCE_KEY_PARAM;

typedef struct ce_debug_key_info
{
    enum HDCP_KEY_SELECT sel;
    unsigned int buffer[4]; 
    unsigned int len;      
}CE_DEBUG_KEY_INFO, *pCE_DEBUG_KEY_INFO;

typedef struct ce_data_info
{
	OTP_PARAM otp_info;
	DATA_PARAM data_info;
	DES_PARAM des_aes_info;
	CE_KEY_PARAM key_info; 
}CE_DATA_INFO, *pCE_DATA_INFO;

typedef struct ce_pos_status_param
{
	unsigned int pos;
	unsigned int status; 
}CE_POS_STS_PARAM, *pCE_POS_STS_PARAM;

typedef struct ce_found_free_pos_param
{
	unsigned int pos;
	enum ce_key_level ce_key_level; 
	unsigned char number;
	enum CE_OTP_KEY_SEL root;
}CE_FOUND_FREE_POS_PARAM, *pCE_FOUND_FREE_POS_PARAM;


typedef struct ce_device
{
	struct ce_device  *next;  /*next device */
	/*struct module *owner;*/
	int type;
	char name[HLD_MAX_NAME_SIZE];

	void *pCePriv;		/* Used to be 'private' but that upsets C++ */
	unsigned int base_addr;
	unsigned int interrupt_id;

	unsigned short semaphore_id;
	unsigned short semaphore_id2;

	void      (*attach)(void);
	void      (*detach)( struct ce_device *);
	int	(*open)( struct ce_device *);
	int   	(*close)( struct ce_device *);
	int  (*ioctl)(struct ce_device *,unsigned int ,unsigned int );
	int (*key_generate)(struct ce_device *,pCE_DATA_INFO );
	int (*key_load)(struct ce_device *,pOTP_PARAM);	
	int fd;
}CE_DEVICE, *pCE_DEVICE;

typedef struct ce_genarate_cw
{
	unsigned char *in;
	unsigned char aes_or_des;
	unsigned char lowlev_pos;
	unsigned char highlev_pos;
} ALI_CE_GEN_CW, *pALI_CE_GEN_CW;

#endif 

