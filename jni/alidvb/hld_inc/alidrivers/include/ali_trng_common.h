#ifndef  _ALI_TRNG_COMMON_H_
#define  _ALI_TRNG_COMMON_H_

#define ALI_TRNG_HLD_PARAM_MAX_SIZE 4
struct ali_trng_hld_param
{
	unsigned int p[ALI_TRNG_HLD_PARAM_MAX_SIZE];    
};

typedef struct ali_trng_get_64bits
{
	unsigned char *data;
	unsigned int n_group;
}ALI_TRNG_GET_64BITS, *pALI_TRNG_GET_64BITS;


#define ALI_TRNG_MAX_GROUP 16
#define ALI_TRNG_64BITS_SIZE 8

#define ALI_TRNG_BASE	(0x54<<8)
#define ALI_TRNG_GENERATE_BYTE      (ALI_TRNG_BASE + 0)
#define ALI_TRNG_GENERATE_64bits    (ALI_TRNG_BASE + 1)
#define ALI_TRNG_GET_64bits         	(ALI_TRNG_BASE + 2)


#ifndef RET_SUCCESS
#define RET_SUCCESS ((int)0)
#define RET_FAILURE	((int)1)
#endif

#endif  /*_TRNG_H_*/
