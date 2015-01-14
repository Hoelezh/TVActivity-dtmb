
#ifndef _ALI_CACHE_H_
#define _ALI_CACHE_H_

#if defined(CONFIG_ARM)

#include <linux/dma-direction.h>
#include <asm/cacheflush.h>

/* cache operation for arm arch */
#define __CACHE_FLUSH_ALI(start, len)		dmac_flush_range((const void *)start, (const void *)((unsigned long)start + (unsigned long)len))
#define __CACHE_INV_ALI(start, len)			dmac_map_area((const void *)(start), ((unsigned long)start + (unsigned long)len), DMA_FROM_DEVICE)
#define __CACHE_CLEAN_ALI(start, len)		dmac_map_area((const void *)(start), ((unsigned long)start + (unsigned long)len), DMA_TO_DEVICE)

#define __CACHE_ADDR_ALI(addr)    ((unsigned int)addr)
#define __NONCACHE_ADDR_ALI(addr) ((unsigned int)addr)

#else

#include <asm/io.h>

/* cache operation for mips arch */
#define __CACHE_FLUSH_ALI(start, len)		dma_cache_wback((unsigned long)(start), len)
#define __CACHE_INV_ALI(start, len)		dma_cache_inv((unsigned long)(start), len)
#define __CACHE_CLEAN_ALI(start, len)		dma_cache_wback_inv((unsigned long)(start), len)

#define __CACHE_ADDR_ALI(addr)    ((unsigned int)addr & 0x9FFFFFFF)
#define __NONCACHE_ADDR_ALI(addr) ((unsigned int)addr |0xA0000000)

#endif

#define __CACHE_ADDR_ALI_SEE(addr)    (((unsigned int)addr & 0x1FFFFFFF) | 0x80000000)
#define __NONCACHE_ADDR_ALI_SEE(addr) ((unsigned int)addr |0xA0000000)

#endif

