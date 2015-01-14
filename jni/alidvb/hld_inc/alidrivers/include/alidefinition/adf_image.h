#ifndef __ADF_IMAGE__
#define __ADF_IMAGE__

#ifdef __cplusplus
extern "C" {
#endif

enum IMAGE_DIS_MODE
{
	IMAGEDEC_FULL_SRN = 1,
	IMAGEDEC_REAL_SIZE,
	IMAGEDEC_THUMBNAIL,
	IMAGEDEC_AUTO,
	IMAGEDEC_SIZEDEFINE,
	IMAGEDEC_MULTI_PIC,
	IMAGEDEC_NOT_DIS,
	IMAGEDEC_NOT_DISTHUM,
	RESERVED_MODE,
};

enum IMAGE_ANGLE
{
	ANG_ORI,
	ANG_90_A ,	/*Along the clock with 90*/
	ANG_180,
	ANG_90_C,	/*Counter the clock with 90*/	
};

enum IMAGE_SHOW_MODE
{
	M_NORMAL,
	M_SHUTTERS,
	M_BRUSH,
	M_SLIDE,
	M_RANDOM,
	M_FADE,
};

/*handle point to the jpeg file*/
typedef unsigned long file_h;

typedef struct Imagedec_Init_Config_t
{
	/*dst frame info*/
	UINT32 frm_y_addr;
	UINT32 frm_y_size;
	UINT32 frm_c_addr;
	UINT32 frm_c_size;
	UINT32 frm2_y_addr;
	UINT32 frm2_y_size;
	UINT32 frm2_c_addr;
	UINT32 frm2_c_size;
	UINT32 frm_mb_type;/*reserved for 36XX series with different MB width. 33XX : 16  36XX : 32*/

	/*buf for dec internal usage*/
	UINT8 *decoder_buf;
	UINT32 decoder_buf_len;

	UINT8 *vbv_buf;
	UINT32 vbv_buf_len;
	
	/*file operation callback function*/
	int (*fread_callback)(file_h fh,UINT8 *buf, UINT32 size);
	BOOL (*fseek_callback)(file_h fh,INT32 offset, UINT32 origin);
	int (*ftell_callback)(file_h fh);
	/*external status info callback function*/
	UINT32 (*imagedec_status)(void *value);

	//backup the old frame buffer
	UINT32 frm3_y_addr;
	UINT32 frm3_y_size;
	UINT32 frm3_c_addr;
	UINT32 frm3_c_size;

	UINT32 frm4_y_addr;
	UINT32 frm4_y_size;
	UINT32 frm4_c_addr;
	UINT32 frm4_c_size;

	int pkt_sbm_idx;
	int info_sbm_idx;
    int info_end_idx;
    int type; //0 --- sbm mode
}Imagedec_Init_Config , *pImagedec_Init_Config;

typedef struct Imagedec_show_shutters_t
{
	UINT8 direction; //0 : horizontal 1: vertical
	UINT8 type;
	UINT16 time; // ms
}Imagedec_show_shutters,*pImagedec_show_shutters;

typedef struct Imagedec_show_brush_t
{
	UINT8 direction; //0 : from left to right 1: from top to bottom
	UINT8 type;
	UINT16 time; // ms
}Imagedec_show_brush,*pImagedec_show_brush;

typedef struct Imagedec_show_slide_t
{
	UINT8 direction; //0 : from left to right 1: from top to bottom
	UINT8 type;
	UINT16 time; // ms	
}Imagedec_show_slide,*pImagedec_show_slide;

typedef struct Imagedec_show_random_t
{
	UINT8 type;	// 0: random block operation
	UINT8 res;
	UINT16 time; // ms
}Imagedec_show_show_random,*pImagedec_show_random;

typedef struct Imagedec_show_fade_t
{
	UINT8 type;
	UINT8 res;
	UINT16 time; // ms
}Imagedec_show_fade,*pImagedec_show_fade;

typedef struct Imagedec_Mode_Par_t
{
	struct Rect src_rect;	/*source rectangule, only used in Real_size mode*/
	struct Rect dis_rect;	/*display rectangule,only used in ThumbNail mode*/
	BOOL pro_show;	/*whether show the part of the pic when decoding it*/
	BOOL vp_close_control;	/*whether close vp once*/
	enum IMAGE_SHOW_MODE show_mode;
	UINT8 *show_mode_par;
	UINT8	need_logo;
	UINT32 reserved;
}Imagedec_Mode_Par,*pImagedec_Mode_Par;

//slideshow effect
struct image_slideshow_effect
{
	
	enum IMAGE_SHOW_MODE mode;
	union 
	{
		Imagedec_show_shutters 	shuttles_param;
		Imagedec_show_brush 	brush_param;
		Imagedec_show_slide 	slide_param;
		Imagedec_show_show_random
								random_param;
		Imagedec_show_fade 		fade_param;
	}mode_param;
	
};

enum IMAGE_FORMAT
{
	IMG_JPEG = 1,
	IMG_PNG,
	IMG_BMP,
};

struct image_engine_config
{
	//char *file_name;

	unsigned char	decode_mode;		
	unsigned char	show_mode;
	unsigned char	vpo_mode;
	unsigned char	rotate;

	//rect for source
	unsigned short	src_left;
	unsigned short	src_top;
	unsigned short	src_width;
	unsigned short	src_height;

	//rect for display
	unsigned short	dest_left;
	unsigned short	dest_top;
	unsigned short	dest_width;
	unsigned short	dest_height;

	//slide show mode 
	struct image_slideshow_effect *effect;

	enum IMAGE_FORMAT img_fmt;
	//callback function
	//mp_callback_func mp_cb;
};

struct image_init_config
{
	
	// dst frame info
	unsigned int frm_y_addr;
	unsigned int frm_y_size;
	unsigned int frm_c_addr;
	unsigned int frm_c_size;
	unsigned int frm2_y_addr;
	unsigned int frm2_y_size;
	unsigned int frm2_c_addr;
	unsigned int frm2_c_size;
	unsigned int frm_mb_type;
	unsigned int frm3_y_addr;
	unsigned int frm3_y_size;
	unsigned int frm3_c_addr;
	unsigned int frm3_c_size;
	unsigned int frm4_y_addr;
	unsigned int frm4_y_size;
	unsigned int frm4_c_addr;
	unsigned int frm4_c_size;

	// buf for dec internal usage
	unsigned char *decoder_buf;
	unsigned int decoder_buf_len;

    unsigned char *vbv_buf;
    unsigned int vbv_buf_len;

	enum IMAGE_FORMAT img_fmt;

	int pkt_sbm_idx;
	int info_sbm_idx;
    int info_end_idx;
	//callback function for application
	//mp_callback_func mp_cb;		
};

struct image_display_t 
{
	unsigned char	decode_mode;		
	unsigned char	show_mode;
	unsigned char	vpo_mode;
	unsigned char	rotate;

	//rect for source
	unsigned short	src_left;
	unsigned short	src_top;
	unsigned short	src_width;
	unsigned short	src_height;

	//rect for display
	unsigned short	dest_left;
	unsigned short	dest_top;
	unsigned short	dest_width;
	unsigned short	dest_height;

	struct image_slideshow_effect *effect;

    enum IMAGE_FORMAT img_fmt;

	unsigned int	y_addr;
	unsigned int	y_len; 
	unsigned int 	c_addr;
	unsigned int	c_len;

	unsigned int	width;
	unsigned int	height;

	unsigned char	sample_format;

	void *mp_cb;
};

struct image_hw_info
{
    unsigned int  y_addr;
    unsigned int  y_size;
    unsigned int  c_addr;
    unsigned int  c_size;

    unsigned int  width;
    unsigned int  height;
    unsigned int  w_stride;
    unsigned char   sample_format;
};

struct image_info
{
	unsigned long	fsize;
	unsigned long	width;
	unsigned long	height;
	unsigned long	bbp;
    unsigned long   type;
};

struct info_end
{
	unsigned long magic_num;
	unsigned long flag_end:1;
	unsigned long reserved:31;
};

struct head_data
{
	unsigned long magic_num;     // special symbol
	unsigned long buf_size;          // size of raw data
	unsigned long offset;              // data offset from start address
	unsigned long flag_end:1;      // flag for EOF
	unsigned long reserved:31;    // reserved
};

#ifdef __cplusplus
}
#endif

#endif

