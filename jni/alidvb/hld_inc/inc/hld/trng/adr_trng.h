#ifndef  __ADR_TRNG_H_
#define  __ADR_TRNG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <adr_basic_types.h>
#include <ali_trng_common.h>

#define ALI_TRNG_LINUX_DEV_PATH "/dev/ali_trng_0"

int trng_api_attach(void);
int trng_api_detach(void);
int trng_generate_byte(UINT8 *data);
int trng_generate_64bits(UINT8 *data);
int trng_get_64bits(UINT8 *data, UINT32 n);

#ifdef __cplusplus
}
#endif
#endif  /*_TRNG_H_*/
