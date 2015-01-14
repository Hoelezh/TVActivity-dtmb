#ifndef _ADF_DSC_H_
#define _ADF_DSC_H_

//for AES/DES/CSA/SHA
#define IO_DSC_BASE                                (0x53<<8)
#define IO_INIT_CMD                          		(IO_DSC_BASE + 0)
#define IO_CREAT_CRYPT_STREAM_CMD       (IO_DSC_BASE + 1)
#define IO_DELETE_CRYPT_STREAM_CMD     (IO_DSC_BASE + 2)
#define IO_KEY_INFO_UPDATE_CMD             (IO_DSC_BASE + 3)

//for DSC
#define IO_PARSE_DMX_ID_SET_CMD            (IO_DSC_BASE + 0) 
#define IO_PARSE_DMX_ID_GET_CMD            (IO_DSC_BASE + 1)                                              
#define IO_DSC_GET_DES_HANDLE                (IO_DSC_BASE + 2)  
#define IO_DSC_GET_AES_HANDLE                (IO_DSC_BASE + 3)  
#define IO_DSC_GET_CSA_HANDLE                (IO_DSC_BASE + 4)  
#define IO_DSC_GET_SHA_HANDLE                (IO_DSC_BASE + 5)  
#define IO_DSC_SET_PVR_KEY_PARAM          (IO_DSC_BASE + 6)  
#define IO_DSC_ENCRYTP_BL_UK                  (IO_DSC_BASE + 7) 
#define IO_DSC_SET_PVR_KEY_IDLE             (IO_DSC_BASE + 8) 
#define IO_DSC_VER_CHECK                        (IO_DSC_BASE + 9)
#define IO_DSC_SET_ENCRYPT_PRIORITY      (IO_DSC_BASE + 10)
#define IO_DSC_GET_DRIVER_VERSION         (IO_DSC_BASE + 11)
#define IO_DSC_SET_CLR_CMDQ_EN             (IO_DSC_BASE + 12)
#define IO_DSC_DELETE_HANDLE_CMD         (IO_DSC_BASE + 13)

#define IO_DSC_FIXED_DECRYPTION            (IO_DSC_BASE + 30)
#define IO_DSC_SYS_UK_FW                       (IO_DSC_BASE + 31)

#define VIRTUAL_DEV_NUM 4

#define SHA1_HASH_SIZE 		20
#define SHA224_HASH_SIZE 	28
#define SHA256_HASH_SIZE 	32
#define SHA384_HASH_SIZE 	48
#define SHA512_HASH_SIZE 	64

#define DSC_IO_CMD(cmd)  (cmd & 0xFF)

#define CHECK_HEAD 0x1000
#define CHECK_END  0x0001 
/*just for version check caller*/
#define CHUNKID_UBOOT        0x01FE0101
#define CHUNKID_KERNEL       0x06F90101
#define CHUNKID_FW           0x06F90101   
#define CHUNKID_SEE          0x00FF0100
#define CHUNKID_BL           0x10000123   

#define HMAC_OUT_LENGTH   32
#define HASH_BLOCK_LENGTH   64
#define FIRST_KEY_LENGTH   16
	
#define PURE_DATA_MAX_SIZE  0x100000	
#define TS_MAX_SIZE_TDS  0x10000  //64k packets
#define PURE_DATA_MAX_SIZE_TDS  0x4000000  //64MBytes

#define DSC_TIMEOUT_FORVER		 0xFFFFFFFF
#define RAM_MON_SET_FLAG         0x00000002
#define RAM_MON_CLEAR_FLAG       0x00000001

#ifndef RET_SUCCESS
#define RET_SUCCESS ((int)0)
#define RET_FAILURE	((int)1)
#endif

#define ALI_INVALID_CRYPTO_STREAM_HANDLE  0xffffffff
#define ALI_INVALID_CRYPTO_KEY_POS			0xff
#define ALI_INVALID_CRYPTO_STREAM_ID		0xff
#define ALI_INVALID_DSC_SUB_DEV_ID          0xff
#define INVALID_DSC_SUB_DEV_ID			0xff
#define INVALID_DSC_STREAM_ID			0xff
#define INVALID_CE_KEY_POS 0xff

#define AES_BLOCK_LEN 16
#define DES_BLOCK_LEN 8

enum CSA_VERSION
{
	CSA1=1,
	CSA2=0,
	CSA3=2
};

enum SHA_MODE
{
	SHA_SHA_1= 0,
	SHA_SHA_224=(1<<29),
	SHA_SHA_256=  (2<<29),
	SHA_SHA_384 = (3<<29),
	SHA_SHA_512  =(4<<29),
};

enum SHA_DATA_SOURCE
{
	SHA_DATA_SOURCE_FROM_DRAM =0,
	SHA_DATA_SOURCE_FROM_FLASH =1,
};

enum PARITY_MODE
{
	EVEN_PARITY_MODE  =0,
	ODD_PARITY_MODE =1,
	AUTO_PARITY_MODE0= 2,  /*for ts*/
	AUTO_PARITY_MODE1=3,
	OTP_KEY_FROM_68 = 4,
	OTP_KEY_FROM_6C = 5,
};

enum KEY_TYPE
{
	KEY_FROM_REG=0,
	KEY_FROM_SRAM=1,
	KEY_FROM_CRYPTO=2,
	KEY_FROM_OTP = 3,
};

enum KEY_MAP_MODE
{
	CSA_MODE=0,
	DES_MODE=0,
	CSA3_MODE=1,
	AES_128BITS_MODE=1,
	CRYPTO_128BITS_MODE=1,
	TDES_ABA_MODE=1,
	AES_192BITS_MODE=2,
	TDES_ABC_MODE=2,
	AES_256BITS_MODE=3
};

enum DMA_MODE
{
	PURE_DATA_MODE=0,
	TS_MODE=(1<<24),
};

enum RESIDUE_BLOCK
{
	RESIDUE_BLOCK_IS_NO_HANDLE=0,
	RESIDUE_BLOCK_IS_AS_ATSC=(1<<12),
	RESIDUE_BLOCK_IS_HW_CTS = (2 << 12),
	RESIDUE_BLOCK_IS_RESERVED = (3 << 12),
};


enum WORK_MODE
{
	WORK_MODE_IS_CBC=  0,
	WORK_MODE_IS_ECB =   (1<<4),
	WORK_MODE_IS_OFB=  (2<<4),
	WORK_MODE_IS_CFB  =(3<<4),   
	WORK_MODE_IS_CTR  =(4<<4),  /*only for aes*/
};

enum WORK_SUB_MODULE
{
	DES=0,
	TDES=3,
	AES=1,
	SHA=2,
	CSA=4,
};

enum CRYPT_SELECT
{//change: same with keyladder
	DSC_DECRYPT=1,
	DSC_ENCRYPT=0
};

enum dsc_init_status
{
	DSC_INIT_SUCCESS = RET_SUCCESS,
	DSC_INIT_FAILED,
	DSC_ALREADY_INITIALIZED,
	DSC_NOT_INIT,
};


//1 DES INIT PARAM
typedef struct des_init_param 
{
	enum PARITY_MODE  parity_mode;    
	enum KEY_TYPE key_from;
	unsigned int scramble_control;
	enum KEY_MAP_MODE key_mode;
	unsigned int stream_id;
	enum DMA_MODE dma_mode;
	enum RESIDUE_BLOCK  residue_mode;
	enum WORK_MODE work_mode;
	enum WORK_SUB_MODULE sub_module;
	unsigned int cbc_cts_enable ;  
}DES_INIT_PARAM, *pDES_INIT_PARAM;


//1 AES INIT PARAM
typedef struct aes_init_param 
{
	enum PARITY_MODE  parity_mode;    
	enum KEY_TYPE key_from;
	unsigned int scramble_control;
	enum KEY_MAP_MODE key_mode;
	unsigned int stream_id; /**which stream id is working*/
	enum DMA_MODE dma_mode;
	enum RESIDUE_BLOCK  residue_mode;
	enum WORK_MODE work_mode;
	unsigned int cbc_cts_enable ;  /*for pure data*/
}AES_INIT_PARAM, *pAES_INIT_PARAM;


//1 CSA INIT PARAM
typedef struct csa_init_param 
{
	enum CSA_VERSION version;
	enum DMA_MODE dma_mode;/*pure_data, or ts*/	 
	unsigned int Dcw[4];  /*for csa only used Dcw[0]Dcw[1], for csa3 used all*/
	unsigned int pes_en;  

	enum PARITY_MODE  parity_mode;    
	enum KEY_TYPE key_from;
	unsigned int scramble_control;
	unsigned int stream_id; /**which stream id is working*/  
}CSA_INIT_PARAM, *pCSA_INIT_PARAM;


//1 SHA INIT PARAM
typedef struct sha_init_param
{
  enum SHA_MODE sha_work_mode; 
  enum SHA_DATA_SOURCE sha_data_source;
  unsigned int sha_buf;           
} SHA_INIT_PARAM, *pSHA_INIT_PARAM;


typedef struct crypto_128bit_key{
	unsigned char even_key[16];
	unsigned char odd_key[16];
}CRYPTO_128BITS_KEY;

typedef struct crypto_128bit_iv{
	unsigned char even_iv[16];
	unsigned char odd_iv[16];
}CRYPTO_128BITS_IV;

struct AES_128Bit_KEY 
{
	unsigned char even_key[16];
	unsigned char odd_key[16];
};

typedef struct AES_128Bit_KEY AES_128BITS_KEY;

struct AES_192Bit_KEY 
{
	unsigned char even_key[24];
	unsigned char odd_key[24];
};

struct AES_256Bit_KEY 
{
	unsigned char even_key[32];
	unsigned char odd_key[32];
};

typedef union aes_key_param
{
	struct AES_128Bit_KEY aes_128bit_key ;
	struct AES_192Bit_KEY aes_192bit_key ;
	struct AES_256Bit_KEY aes_256bit_key ;
}AES_KEY_PARAM;

typedef struct aes_iv_info
{
	unsigned char even_iv[16];
	unsigned char odd_iv[16];
}AES_IV_INFO;

struct  AES_KEY
{
	unsigned char OddKey[16];
	unsigned char EvenKey[16];
};

struct  CSA_KEY
{
	unsigned char OddKey[8];
	unsigned char EvenKey[8];
};

typedef struct CSA_KEY CSA_64BITS_KEY;

struct  CSA3_KEY
{
	unsigned char OddKey[16];
	unsigned char EvenKey[16];
};

typedef struct CSA3_KEY CSA3_128BITS_KEY;

typedef union csa_key_param
{
	struct  CSA_KEY csa_key ;
	struct  CSA3_KEY csa3_key ;
}CSA_KEY_PARAM;

struct  DES_64BITS_KEY_INFO
{
	unsigned char OddKey[8];
	unsigned char EvenKey[8];
};

struct  DES_128BITS_KEY_INFO
{
	unsigned char OddKey[16];
	unsigned char EvenKey[16];
};

typedef struct DES_128BITS_KEY_INFO TDES_128BITS_KEY;

struct  DES_192BITS_KEY_INFO
{
	unsigned char OddKey[24];
	unsigned char EvenKey[24];
};

typedef union des_key_param
{
	struct  DES_64BITS_KEY_INFO  des_64bits_key ;
	struct  DES_128BITS_KEY_INFO des_128bits_key ;
	struct  DES_192BITS_KEY_INFO des_192bits_key ;
}DES_KEY_PARAM;

typedef struct des_iv_info
{
	unsigned char even_iv[8];
	unsigned char odd_iv[8];
}DES_IV_INFO;

//1 KEY INFO PARAM
typedef struct  
{
	unsigned int handle ;  /* out parameter*/
	unsigned short *pid_list;
	unsigned short pid_len;  
	AES_KEY_PARAM *p_aes_key_info; /*for ts data mode*/
	CSA_KEY_PARAM *p_csa_key_info;
	DES_KEY_PARAM *p_des_key_info;
	unsigned int key_length;
	AES_IV_INFO *p_aes_iv_info;
	DES_IV_INFO *p_des_iv_info;
	unsigned short stream_id;

	unsigned char *init_vector; /*for pure data mode*/
	unsigned char *ctr_counter;
	unsigned char force_mode; /*user point the fix position*/
	unsigned char pos;
	unsigned char no_even;
	unsigned char no_odd;
	unsigned char not_refresh_iv;
}KEY_PARAM, *pKEY_PARAM;
//1 PID INFO PARAM
typedef struct pid_param
{  
   unsigned int dmx_id ;
   unsigned short pid;
   unsigned short pos; //pid pos
   unsigned char  key_addr;
}PID_POS_PARAM,*pPID_POS_PARAM ;

typedef struct ram_monitor_param
{
	unsigned int start_addr;
	unsigned int len;
	unsigned int interval;
	enum SHA_MODE sha_mode;
	int   flag;
	unsigned int ram_flg_id;
}RAM_MONITOR_PARAM,*pRAM_MONITOR_PARAM;

typedef struct crypt_init_nos
{
    enum PARITY_MODE  parity_mode;    
    enum KEY_TYPE key_from;
    unsigned int scramble_control;
    enum KEY_MAP_MODE key_mode;
    unsigned int stream_id; /**which stream id is working*/
    enum DMA_MODE dma_mode;
    enum RESIDUE_BLOCK  residue_mode;
    enum WORK_MODE work_mode;
    enum WORK_SUB_MODULE sub_module;
	unsigned int cbc_cts_enable ;  /*for pure data*/
	
	pKEY_PARAM pkeyParam;
}INIT_PARAM_NOS, *pINIT_PARAM_NOS;

//1 SHA DEVICE
typedef struct sha_device
{
	struct sha_device  *next;  /*next device */
	int type;
	char name[16];	//HLD_MAX_NAME_SIZE
	void *pRoot;
	void *priv ; 
	void (*open)(struct sha_device *);
	void (*close)(struct sha_device *);
	int (*digest)(struct sha_device * , unsigned char *, unsigned char *,unsigned int );
	int  (*Ioctl)( struct sha_device * ,unsigned int cmd , unsigned int param);
	unsigned char id_number;	
	int fd;
}SHA_DEV,*pSHA_DEV;

//1 AES DEVICE
typedef struct aes_device
{
	struct aes_device  *next;  /*next device */
	int type;
	char name[16]; //HLD_MAX_NAME_SIZE
	void *pRoot;		
	void *priv ;
	void (*open)(struct aes_device *);
	void (*close)(struct aes_device *);
	int (*Encrypt)(struct aes_device * ,unsigned short, unsigned char *, unsigned char *, unsigned int );
	int (*Decrypt)(struct aes_device * ,unsigned short, unsigned char *, unsigned char *, unsigned int);
	int (*Ioctl)(struct aes_device *,unsigned int cmd,unsigned int param);
	unsigned char id_number;
	int fd;
}AES_DEV,*pAES_DEV;


//1 DES DEVICE
typedef struct des_device
{
	struct des_device  *next;  /*next device */
	int type;
	char name[16]; //HLD_MAX_NAME_SIZE
	void *pRoot;		
	void *priv ;
	void (*open)(struct des_device * );
	void (*close)(struct des_device *);
	int (*Encrypt)(struct des_device *, unsigned short,unsigned char *, unsigned char *, unsigned int );
	int (*Decrypt)(struct des_device *, unsigned short,unsigned char *, unsigned char *, unsigned int );
	int (*Ioctl)(struct des_device *,unsigned int cmd,unsigned int param);
	unsigned char id_number;      
	int fd;
}DES_DEV,*pDES_DEV;


//1 CSA DEVICE
typedef struct csa_device
{
	struct csa_device  *next;  /*next device */
	int type;
	char name[16]; //HLD_MAX_NAME_SIZE
	void *pRoot;		
	void *priv;
	void (*open)(struct csa_device*);
	void (*close)(struct csa_device*);
	int (*Decrypt)(struct csa_device*,unsigned short, unsigned char*, unsigned char*, unsigned int );
	int (*Ioctl)(struct csa_device *,unsigned int cmd,unsigned int param);
	unsigned char id_number;
	int fd;
}CSA_DEV,*pCSA_DEV;


//1 DSC DEVICE
typedef struct descrambler_device
{
	struct descrambler_device  *next;  /*next device */
	int type;
	char name[16]; //HLD_MAX_NAME_SIZE
	void *priv;		
	unsigned int base_addr;
	unsigned int  interrupt_id;

	void      (*attach)(void);
	void      (*detach)( struct descrambler_device *);
	int	(*open)( struct descrambler_device *);
	int   	(*close)( struct descrambler_device *);
	int   (*ioctl)(struct descrambler_device *, unsigned int , unsigned int );
	int fd;
	void *user_base;
}DSC_DEV, *pDSC_DEV;

typedef struct DSC_PVR_KEY_PARAM
{
	unsigned int input_addr;
	unsigned int valid_key_num;
	unsigned int current_key_num;
	unsigned int pvr_key_length;
	unsigned char pvr_user_key_pos;
	unsigned int total_quantum_number; 
	unsigned int current_quantum_number;
	unsigned int ts_packet_number;
	unsigned char pvr_key_change_enable;
	unsigned short stream_id;
}DSC_PVR_KEY_PARAM,*pDSC_PVR_KEY_PARAM;

typedef struct DSC_BL_UK_PARAM
{
	unsigned char *input_key;
	unsigned char *r_key;
	unsigned char *output_key;
	unsigned int crypt_type;
}DSC_BL_UK_PARAM,*pDSC_BL_UK_PARAM;


typedef struct HW_CHECK_USER_NODE
{
    unsigned int startaddr;
    unsigned int length;    
}HW_CHK_NODE, *pHW_CHK_NODE;

typedef struct HW_CHECK_USER_CONFIG
{
    unsigned int nodecount; // for SC mode only, should <= 65536
    pHW_CHK_NODE pnodelist;  // nodes list 
}HW_CHK_USER_CFG, *pHW_CHK_USER_CFG;


typedef struct DSC_VER_CHK_PARAM
{
	unsigned int input_mem;
    unsigned int len;
    unsigned int chk_mode; 
    unsigned int chk_id ;
}DSC_VER_CHK_PARAM,*pDSC_VER_CHK_PARAM;

typedef struct DeEncrypt_config
{
	unsigned int do_encrypt ;
	void *dec_dev;                /*Decrypt device for stream*/
	unsigned char Decrypt_Mode;
	unsigned short dec_dmx_id;
	unsigned int do_decrypt ;
	void *enc_dev;                /*Encrypt device for stream*/
	unsigned char Encrypt_Mode;
	unsigned short enc_dmx_id;
}DEEN_CONFIG,*pDEEN_CONFIG;

typedef struct dsc_en_priority
{
	enum WORK_SUB_MODULE sub_module;
	enum PARITY_MODE priority;
    unsigned int dev_ptr; 
}DSC_EN_PRIORITY,*pDSC_EN_PRIORITY;


typedef struct dsc_fixed_cryption_param
{
	unsigned char *input;
	unsigned int length; 
	unsigned int pos;
}DSC_FIXED_CRYPTION,*pDSC_FIXED_CRYPTION;

typedef struct dsc_deal_sys_fw
{
	unsigned char *input;
	unsigned char *output;
	unsigned int length; 
	unsigned char ck[16];
	unsigned char pos;
	enum CRYPT_SELECT mode;
}DSC_SYS_UK_FW,*pDSC_SYS_UK_FW;

typedef struct hmac_param
{
	unsigned char key[FIRST_KEY_LENGTH];
	unsigned char k0[HASH_BLOCK_LENGTH];
	unsigned char ipad[HASH_BLOCK_LENGTH];
	unsigned char opad[HASH_BLOCK_LENGTH];
	unsigned char hout[HASH_BLOCK_LENGTH];
}HMAC_PARAM, *PHMAC_PARAM;

#endif 

