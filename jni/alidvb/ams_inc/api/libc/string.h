
#ifndef __LIB_C_STRING_H__
#define __LIB_C_STRING_H__

#include <string.h>
#include <stdlib.h>
//#include <adr_basic_types.h>

/* memcpy is more efficient than amsstr_memcpy after testing,
 * so we adopt memcpy of libc.
 */
#define MEMCPY(dest, src, len)			memcpy(dest, src, len)
#define MEMCMP(buf1,buf2, len)			memcmp(buf1,buf2, len)
#define MEMSET(dest, c, len)			memset(dest, c, len)
#define MEMMOVE(dest, src, len)			memmove(dest, src, len)

#define STRCPY(dest,src)				strcpy(dest,src)
#define STRNCPY(dest,src,n)             strncpy(dest,src,n)
#define STRCAT(dest,src)				strcat(dest,src)
#define STRNCAT(dest,src,n)				strncat(dest,src,n) 
#define STRCMP(dest,src)				strcmp(dest,src)
#define STRNCMP(dest,src,n)				strncmp(dest,src,n)
#define STRCASECMP(dest,src)			strcasecmp(dest,src)
#define STRLEN(str)						strlen(str)
#define STRNCASECMP(dest,src,n)         strncasecmp(dest,src,n)
#define STRRCHR(dest,src)               strrchr(dest,src)
#define STRCHR(dest,src)                strchr(dest,src)

#define ATOI(str)				    	atoi(str)
#define ITOA(str, val)					amsstr_itoa(str, val)
#define ATOI16(str)						amsstr_atoi16(str)
#define ATOIEXT(str)					amsstr_atoi_ext(str)
#define RAND(max_val)			        amsstr_rand(max_val)

#define FETCH_LONG(p)  \
	((((*((unsigned char*)(p))) << 24)) \
	| ((*((unsigned char*)(p) + 1)) << 16) \
	| ((*((unsigned char*)(p) + 2)) << 8) \
	| (*((unsigned char*)(p) + 3)))
	
#define STORE_LONG(p, value)  \
	{	\
		(*((unsigned char*)(p))) = (unsigned char)(value >> 24);\
		(*((unsigned char*)(p)+1)) = (unsigned char)(value >> 16);\
		(*((unsigned char*)(p)+2)) = (unsigned char)(value >> 8);\
		(*((unsigned char*)(p)+3)) = (unsigned char)(value >> 0);\
	}

#ifdef __cplusplus
extern "C"
{
#endif

unsigned int amsstr_rand(unsigned int MaxVal);
unsigned long amsstr_atoi_ext(const char * str);
int amsstr_itoa(char * str, unsigned long val);
unsigned long amsstr_atoi16(const char * str);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_C_STRING_H__ */
