/****************************************************************************
 *
 *  ALi (shenzhen) Corporation, All Rights Reserved. 2012 Copyright (C)
 *
 *  File: pr_types.h
 *
 *  Description: Portable runtime unified types definition header file.
 *
 *  History:
 *      Date            Author          Version         Comment
 *      ====            ======          =======         =======
 *  1.  2013.01.25      David.L         0.1.000         Initial
 ****************************************************************************/

#ifndef  __PR_TYPES_H__
#define  __PR_TYPES_H__

typedef int                 Int32;
#if defined(__ALI_LINUX__)
	typedef long            Int64;
#else
	typedef long long           Int64;
#endif
typedef unsigned char       Uint8;
typedef char                Int8;
typedef unsigned char       Uchar;
typedef char                Char;
typedef unsigned short      Uint16;
typedef short               Int16;
typedef unsigned int        Uint32;
#if defined(__ALI_LINUX__)
	typedef unsigned long  Uint64;
#else
	typedef unsigned long long  Uint64;
#endif
typedef signed int          Char32;
#if defined(__ALI_LINUX__)
	typedef unsigned int        Long;
        typedef unsigned int        Ulong;
        typedef unsigned int        Size_t;
        typedef unsigned int        SSize_t;
#else
	typedef long                Long;
	typedef unsigned long       Ulong;
	typedef unsigned long       Size_t;
	typedef long                SSize_t;
#endif

typedef int                 Enum;
typedef char*               Array;
typedef char*               Bytes;
typedef char*               Opaque;
typedef char*               String;
typedef char*               Wrapstring;
typedef char **             Strarray;
typedef char*               Union;
typedef char*               Vector;
typedef float               Float;
typedef double              Double;
typedef char*               Pointer;
typedef char*               Reference;


#ifndef Bool
typedef Long                Bool;
#endif

#ifndef False
#define False               (0)
#endif

#ifndef True
#define True                (!False)
#endif

#endif // __PR_TYPES_H__

