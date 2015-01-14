
#ifndef _ALI_DMA_H_

#define _ALI_DMA_H_

#if defined(CONFIG_ARM)

/* CPU physical address -> DMA address */
#define __CTDADDRALI(x)		(((unsigned long)x) & 0x7FFFFFFF)

/* DMA address -> CPU physical address*/
#define __DTCADDRALI(x)		(((unsigned long)x) | 0x80000000)

#else


/* CPU physical address -> DMA address */
#define __CTDADDRALI(x)		(((unsigned long)x) & 0x7FFFFFFF)


/* DMA address -> CPU physical address*/
#define __DTCADDRALI(x)		((unsigned long)x)	

#endif

#endif

