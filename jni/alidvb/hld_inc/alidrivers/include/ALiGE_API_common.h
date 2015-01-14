#ifndef __ALIGE_API_COMMON_H
#define __ALIGE_API_COMMON_H

#include "openvg_common.h"

#define COLOR_BA    0x00100000
#define IMAGE_BA_0  0x00200000
#define IMAGE_BA_1  0x00300000
#define IMAGE_BA_2  0x00400000

typedef unsigned int ALiGeHandle;

//20111221	add DFB_blendmode_enum
typedef enum {
  GPGe_DSBF_UNKNOWN                   = 0x0,
  GPGe_DSBF_ZERO                      = 0x1,
  GPGe_DSBF_ONE                       = 0x2,
  GPGe_DSBF_SRCCOLOR                  = 0x3,
  GPGe_DSBF_INVSRCCOLOR               = 0x4,
  GPGe_DSBF_SRCALPHA                  = 0x5,
  GPGe_DSBF_INVSRCALPHA               = 0x6,
  GPGe_DSBF_DESTALPHA                 = 0x7,
  GPGe_DSBF_INVDESTALPHA              = 0x8,
  GPGe_DSBF_DESTCOLOR                 = 0x9,
  GPGe_DSBF_INVDESTCOLOR              = 0xa,
  GPGe_DSBF_SRCALPHASAT               = 0xb,
 
} DFBBlendMode;

typedef enum {  
  GPGe_BLEND_SRC                                = 0x2000,
  GPGe_BLEND_SRC_OVER                           = 0x2001,
  GPGe_BLEND_DST_OVER                           = 0x2002,
  GPGe_BLEND_SRC_IN                             = 0x2003,
  GPGe_BLEND_DST_IN                             = 0x2004,
  GPGe_BLEND_MULTIPLY                           = 0x2005,
  GPGe_BLEND_SCREEN                             = 0x2006,
  GPGe_BLEND_DARKEN                             = 0x2007,
  GPGe_BLEND_LIGHTEN                            = 0x2008,
  GPGe_BLEND_ADDITIVE                           = 0x2009,
// Added for iPanel
  GPGe_BLEND_IPANEL_GLOBAL_ALPHA                = 0x200a,
  GPGe_BLEND_PROGRAMABLE                        = 0x200b,
  
  GPGe_BLEND_MODE_FORCE_SIZE                    = VG_MAX_ENUM
} GPGeBlendMode;



	typedef enum{
		lRGBA			= 0,
		sRGBA			= 1,
		lRGBA_PRE		= 2,
		sRGBA_PRE		= 3,
		lLA				= 4,
		sLA				= 5,
		lLA_PRE			= 6,
		sLA_PRE			= 7
	}  InternalFormat;

	typedef enum {
		NONLINEAR		= (1<<0),
		PREMULTIPLIED	= (1<<1),
		LUMINANCE		= (1<<2)
	} FormatBits;

typedef enum {
	GPGe_LINE	= 0x0,
	GPGe_TRIANGLE	= 0x1,
	GPGe_TRAPEZOID	= 0x2,
	GPGe_SPAN	= 0x3,
	GPGe_TEXTURETRIANGLE = 0x4,
	GPGe_OTHER	= 0x80,
}GPGeGeometryFigureType;


typedef	struct	_GPGeExObjectHandle
{
	void	*obj;
	GPGeGeometryFigureType	type;
	float	span_start_y;
	int	span_num;
	
}GPGeExObjectHandle;


//20111205	yashi add new input info structure
typedef	struct	_GPGeExPrivInfo
{
	ALiGeHandle	dst;
	ALiGeHandle	src;
	ALiGeHandle	msk;
	ALiGeHandle	pat;
	
	DFBBlendMode	src_blend_mode;
	DFBBlendMode	dst_blend_mode;
	
	int	global_alpha; 
	VGImageQuality	img_quality;
	
	VGImageFormat	paint_format;
	
	float	stroke_width;	//set width
	
	//for colorize
	uint	 colorize_AR;	//A(8bits) | R(8 bits)
	uint	 colorize_GB; //G(8bits) | B(8 bits)

	// LUT 8
	unsigned long LUT_color[256]; //input from DFB is ARGB, and then driver will covert it into RGBA internally.
	
	//flags	
	int	color_key_en;
	int	colorize_en;
	int	mask_flags; 
	int	stroke_flags;	// 1 -> stroke; 0 -> fill;
	int	interlaced;
	int	deinterlaced;
        int	color_mask;
	
  int clip_en;
  int clip_sx;
	int clip_sy;
	int clip_ex;
	int clip_ey;


	//HW flags for C3701
	unsigned char blend_coloralpha;
	unsigned char blend_alphachannel;
	
	unsigned char	dst_color_key_en;
	unsigned char	src_premultcolor;
	
	unsigned char	xor_flags;	
	
	unsigned char src_premultiply;
	unsigned char dst_premultiply;
	unsigned char demultiply;
	unsigned char index_translation;
	
	
	
	
}GPGeExPrivInfo;

//for rectangle passing
typedef struct _GPGeExTrapezoid
{								
                  int            x1;  /* X coordinate of first span */								
                  int            y1;  /* Y coordinate of first span  */								
                  int            w1;  /* width of first span */								
                  int            x2;  /* X coordinate of second span */								
                  int            y2;  /* Y coordinate of second span */								
                  int            w2;  /* width of second span */								
						
}GPGeExTrapezoid;								

//for triangle passing
typedef struct _GPGeExTriangle
{								
                  int            x1;  /* X coordinate of first edge */								
                  int            y1;  /* Y coordinate of first edge  */
                  int            x2;  /* X coordinate of second edge */								
                  int            y2;  /* Y coordinate of second edge */							
		  int            x3;  /* X coordinate of third edge */								
                  int            y3;  /* Y coordinate of third edge */				
}GPGeExTriangle;

//for line passing
typedef struct _GPGeExLine
{								
                  int            x1;  /* X coordinate of first edge */								
                  int            y1;  /* Y coordinate of first edge  */
                  int            x2;  /* X coordinate of second edge */								
                  int            y2;  /* Y coordinate of second edge */										
}GPGeExLine;

typedef struct _GPGeExSpan
{
     int            x;   /* X coordinate */
     int            w;   /* width of span */
}GPGeExSpan;

/*
 * Transformed vertex of a textured triangle.
 */
typedef struct {
     float x;   /* Destination X coordinate (in pixels) */
     float y;   /* Destination Y coordinate (in pixels) */
     float z;   /* Z coordinate */
     float w;   /* W coordinate */

     float s;   /* Texture S coordinate */
     float t;   /* Texture T coordinate */
} GPGeExVertex;

/*
 * Way of building triangles from the list of vertices.
 */
typedef enum {
     GPGeEX_DTTF_LIST,  /* 0/1/2  3/4/5  6/7/8 ... */
     GPGeEX_DTTF_STRIP, /* 0/1/2  1/2/3  2/3/4 ... */
     GPGeEX_DTTF_FAN    /* 0/1/2  0/2/3  0/3/4 ... */
} GPGeExTriangleFormation;

typedef struct _GPGeExTextureTriangle
{
     GPGeExVertex	*Vertices;
     int	num;
     GPGeExTriangleFormation  formation;
}GPGeExTextureTriangle;

#endif
