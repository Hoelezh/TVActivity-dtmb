#ifndef _ALI_DSC_COMMON_H_
#define _ALI_DSC_COMMON_H_

#include <alidefinition/adf_dsc.h>

enum ALI_CSA_PROTOC_VERSION
{
	CSA_1 = 1,
	CSA_2 = 0,
	CSA_3 = 2
};

/* record the device handle in SEE */
struct dsc_see_dev_hld 
{
	unsigned int dsc_dev_hld;  /*The device handle address in SEE*/
	unsigned int dsc_dev_id;   /*The id number of the dsc_dev_id*/ 
};

//Define this struct in DSC instead of DMX
struct dec_parse_param
{  
	void *dec_dev;   
	unsigned int type;
};


#define ALI_DSC_HLD_PARAM_MAX_SIZE 8
struct ali_dsc_hld_param
{
	unsigned int p[ALI_DSC_HLD_PARAM_MAX_SIZE];    
};

typedef struct ali_dsc_krec_mem
{
	unsigned int size;
	void *pa_mem;
	void *va_mem;
} ALI_DSC_KREC_MEM;

/* For new DSC IOC */
typedef struct cryption_dsc
{
	void *dev;
	unsigned int stream_id;
	unsigned char *input;
	unsigned char *output;
	unsigned int length;
} ALI_DSC_CRYPTION, *pALI_DSC_CRYPTION;

typedef struct io_param_dsc
{
	void *dev;
	void *ioc_param;
} ALI_DSC_IO_PARAM, *pALI_DSC_IO_PARAM;

typedef struct sha_digest_dsc
{
	void *dev;
	unsigned char *input;
	unsigned char *output;
	unsigned int length;
} ALI_SHA_DIGEST, *pALI_SHA_DIGEST;

typedef struct ram_mon_dsc
{
	unsigned int start_addr;
	unsigned int end_addr;
	unsigned int interval;
	enum SHA_MODE sha_mode;
	int dis_or_en;
} ALI_DSC_RAM_MON, *pALI_DSC_RAM_MON;


typedef struct reencrypt_dsc
{
	pDEEN_CONFIG p_deen;
	unsigned char *input;
	unsigned char *output;
	unsigned int length;
} ALI_RE_ENCRYPT, *pALI_RE_ENCRYPT;


typedef struct dsc_id_info
{
	unsigned int mode;
	unsigned int id_number;
} ALI_DSC_ID_INFO, *pALI_DSC_ID_INFO;


//for AES/DES/CSA/SHA
#define ALI_DSC_IO_DECRYPT								_IOW(IO_DSC_BASE, 5, ALI_DSC_CRYPTION)
#define ALI_DSC_IO_ENCRYPT								_IOW(IO_DSC_BASE, 6, ALI_DSC_CRYPTION)
#define ALI_DSC_IO_SHA_DIGEST							_IOW(IO_DSC_BASE, 7, ALI_SHA_DIGEST)

//for DSC
#define ALI_DSC_IO_TRIG_RAM_MON						_IOW(IO_DSC_BASE, 9, ALI_DSC_RAM_MON) 
#define ALI_DSC_IO_DEENCRYPT							_IOW(IO_DSC_BASE, 10, ALI_RE_ENCRYPT)  
#define ALI_DSC_IO_GET_FREE_STREAM_ID               		_IOWR(IO_DSC_BASE, 11, ALI_DSC_ID_INFO)   
#define ALI_DSC_IO_GET_FREE_SUB_DEVICE_ID          		_IOWR(IO_DSC_BASE, 12, ALI_DSC_ID_INFO)  
#define ALI_DSC_IO_SET_SUB_DEVICE_ID_IDLE				_IOW(IO_DSC_BASE, 13, ALI_DSC_ID_INFO)  
#define ALI_DSC_IO_SET_STREAM_ID_IDLE					_IO(IO_DSC_BASE, 14)
#define ALI_DSC_IO_SET_STREAM_ID_USED					_IO(IO_DSC_BASE, 15) 
#define ALI_DSC_IO_SET_SUB_DEVICE_ID_USED				_IOW(IO_DSC_BASE, 16, ALI_DSC_ID_INFO) 

#define IO_GET_DEV_HLD									_IO(IO_DSC_BASE, 17)
#define IO_REQUEST_KREC_SPACE							_IO(IO_DSC_BASE, 18)
#define IO_RELEASE_KREC_SPACE							_IO(IO_DSC_BASE, 19)
#define IO_REQUEST_KREC_ADDR							_IO(IO_DSC_BASE, 20)

#endif 
