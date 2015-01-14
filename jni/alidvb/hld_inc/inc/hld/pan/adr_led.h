#ifndef __ADR_HLD_LED_H__
#define __ADR_HLD_LED_H__

#ifdef __cplusplus
extern "C" {
#endif


#include <linux/ioctl.h>
/*
 * Ioctl definitions
 */

/* Use 'K' as magic number */
#define NMP_LED_IOC_MAGIC  'K'

/*
 * S means "Set" through a ptr,
 * G means "Get" (to a pointed var)
 */
#define NMP_LED_IOC_NET_ON _IOW(NMP_LED_IOC_MAGIC,   1, int)
#define NMP_LED_IOC_NET_OFF _IOW(NMP_LED_IOC_MAGIC,  2, int)

#define NMP_LED_IOC_STANDBY_ON _IOW(NMP_LED_IOC_MAGIC,  3, int)
#define NMP_LED_IOC_STANDBY_OFF _IOW(NMP_LED_IOC_MAGIC,  4, int)

#define NMP_LED_IOC_STOR_ON _IOW(NMP_LED_IOC_MAGIC,  5, int)
#define NMP_LED_IOC_STOR_OFF _IOW(NMP_LED_IOC_MAGIC,  6, int)

#define NMP_LED_IOC_MAXNR 7

#ifdef __cplusplus
}
#endif

#endif /* __ADR_HLD_LED_H__ */
