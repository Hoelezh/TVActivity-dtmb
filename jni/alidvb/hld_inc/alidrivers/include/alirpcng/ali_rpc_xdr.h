#ifndef __ALI_RPC_XDR_H
#define __ALI_RPC_XDR_H

#include "ali_rpc_type.h"
#include "ali_rpc_cfg.h"
#include "ali_rpc_osdep.h"
#include "ali_rpc_debug.h"
#include "ali_rpc_util.h"

#define XDR_FALSE	((Long) 0)
#define XDR_TRUE	((Long) 1)
#define LASTUNSIGNED	((Uint32) 0-1)
#define FALSE   XDR_FALSE
#define TRUE     XDR_TRUE

#define mem_alloc(size)	PR_Malloc(size)
#define mem_free(ptr, bsize)	PR_Free(ptr)

#define BigLittleSwap32(A)  ((((Uint32)(A) & 0xff000000) >> 24) | \
                                                 (((Uint32)(A) & 0x00ff0000) >> 8) | \
                                                 (((Uint32)(A) & 0x0000ff00) << 8) | \
                                                 (((Uint32)(A) & 0x000000ff) << 24))

enum XDR_OP {
	XDR_ENCODE=0,
	XDR_DECODE=1,
	XDR_FREE=2
};

/*
 * This is the number of bytes per unit of external data.
 */
#define BYTES_PER_XDR_UNIT	(4)
#define RNDUP(x)  ((((x) + BYTES_PER_XDR_UNIT - 1) / BYTES_PER_XDR_UNIT) \
		    * BYTES_PER_XDR_UNIT)


typedef	Bool (*XDRPROC_t)();

struct XDR_OPS {
		Bool  	(*x_getlong)();	/* get a long from underlying stream */
		Bool 	(*x_putlong)();	/* put a long to " */
		Bool		(*x_getbytes)();/* get some bytes from " */
		Bool		(*x_putbytes)();/* put some bytes to " */
		Uint32	(*x_getpostn)();/* returns bytes off from beginning */
		Bool		  (*x_setpostn)();/* lets you reposition the stream */
		Long *	(*x_inline)();	/* buf quick ptr to buffered data */
		void	(*x_destroy)();	/* free privates of this xdr_stream */
};

typedef struct _XDR XDR;
struct _XDR {
	enum XDR_OP	x_op;		/* operation; fast additional param */
	struct XDR_OPS  *x_ops;
	Char * 	x_public;	/* users' data */
	Char *	x_private;	/* pointer to private data */
	Char * 	x_base;		/* private used for position info */
	Int32	x_handy;	/* extra private word */
};

/*
 * Operations defined on a XDR handle
 *
 * XDR		*xdrs;
 * long		*longp;
 * caddr_t	 addr;
 * u_int	 len;
 * u_int	 pos;
 */
#define XDR_GETLONG(xdrs, longp)			\
	(*(xdrs)->x_ops->x_getlong)(xdrs, longp)

#define XDR_PUTLONG(xdrs, longp)			\
	(*(xdrs)->x_ops->x_putlong)(xdrs, longp)

#define XDR_GETBYTES(xdrs, addr, len)			\
	(*(xdrs)->x_ops->x_getbytes)(xdrs, addr, len)

#define XDR_PUTBYTES(xdrs, addr, len)			\
	(*(xdrs)->x_ops->x_putbytes)(xdrs, addr, len)

#define XDR_GETPOS(xdrs)				\
	(*(xdrs)->x_ops->x_getpostn)(xdrs)

#define XDR_SETPOS(xdrs, pos)				\
	(*(xdrs)->x_ops->x_setpostn)(xdrs, pos)

#define	XDR_INLINE(xdrs, len)				\
	(*(xdrs)->x_ops->x_inline)(xdrs, len)

#define	XDR_DESTROY(xdrs)				\
	if ((xdrs)->x_ops->x_destroy) 			\
		(*(xdrs)->x_ops->x_destroy)(xdrs)

	
#define NULL_xdrproc_t ((XDRPROC_t)0)
struct _XDRDiscrim {
	Int32	value;
	XDRPROC_t proc;
};

/*The XDR handle could be created as Encoder or Decoder.*/
void XDR_Create(XDR *xdrs, Char *addr, Uint32 size, enum XDR_OP op);

/*We have implemented the most basic types XDR representations as below.*/
Bool XDR_Void();
Bool XDR_Int32(XDR *xdrs, Int32 *ip);
Bool XDR_Uint32(XDR *xdrs, Uint32 *up);
Bool XDR_Long(XDR *xdrs, Long *lp);
Bool XDR_Ulong(XDR *xdrs, Ulong *ulp);
Bool XDR_Int16(XDR *xdrs, Int16 *sp);
Bool XDR_UInt16(XDR *xdrs, Uint16 *usp);
Bool XDR_Bool(XDR *xdrs, Bool *bp);
Bool XDR_Enum(XDR *xdrs, Enum *ep);
Bool XDR_Array(XDR *xdrs, Array *addrp, Uint32 *sizep, Uint32 maxsize, Uint32 elsize, XDRPROC_t elproc);
Bool XDR_Bytes(XDR *xdrs, Bytes* cpp, Uint32 *sizep, Uint32 maxsize);
Bool XDR_Opaque(XDR *xdrs, Opaque cp, Uint32 cnt);
Bool XDR_String(XDR *xdrs, String *cpp, Uint32 maxsize);
Bool XDR_Union(XDR *xdrs, Enum *dscmp, Char *unp, struct _XDRDiscrim *choices, XDRPROC_t dfault);
Bool XDR_Char(XDR *xdrs, Char *cp);
Bool XDR_Uchar(XDR *xdrs, Uchar *cp);
Bool XDR_Vector(XDR *xdrs, Char *basep, Uint32 nelem, Uint32 elemsize, XDRPROC_t xdr_elem);
Bool XDR_Float(XDR *xdrs, Float *fp);
Bool XDR_Double(XDR *xdrs, Double *dp);
Bool XDR_Reference(XDR *xdrs, Reference *pp, Uint32 size, XDRPROC_t proc);
Bool XDR_Pointer(XDR *xdrs, Pointer *objpp, Uint32 obj_size, XDRPROC_t xdr_obj);
Bool XDR_Wrapstring(XDR *xdrs, Wrapstring *cpp);
Bool XDR_Strarray(XDR *xdrs, Strarray *addrp, Uint32 *sizep, Uint32 maxsize);
void XDR_Free(XDRPROC_t proc, Char *objp);



#endif
