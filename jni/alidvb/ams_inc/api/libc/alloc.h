
#ifndef __LIB_C_ALLOC_H__
#define __LIB_C_ALLOC_H__

#include <stdio.h>
#include "adr_basic_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

void *MALLOC(UINT32 size);
void FREE(void *buf);
void *CALLOC(UINT32 nmemb, UINT32 size);
void *REALLOC(void *ptr, UINT32 size);
char *STRDUP(const char *s);
char *STRNDUP(const char *s, UINT32 n);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_C_ALLOC_H__ */
