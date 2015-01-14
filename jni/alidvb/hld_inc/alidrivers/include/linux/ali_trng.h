#ifndef  _ALI_TRNG_H_
#define  _ALI_TRNG_H_

#include <linux/types.h>
#include <ali_trng_common.h>

int ali_trng_generate_byte( __u8 *data );
int ali_trng_generate_64bits( __u8 *data );
int ali_trng_get_64bits(__u8 *data,__u32 n);

#endif 

