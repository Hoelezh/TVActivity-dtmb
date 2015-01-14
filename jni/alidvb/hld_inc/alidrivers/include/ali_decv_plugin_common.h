#ifndef _ALI_DECV_PLUGIN_COMMON_H_
#define _ALI_DECV_PLUGIN_COMMON_H_

#include "ali_basic_common.h"

#define MAX_INSTANCE_NUM											20

#define ALI_DECV_FALSE												(0)
#define ALI_DECV_TRUE												(1)

#define ALI_DECV_PROBE_FAIL										(0)
#define ALI_DECV_PROBE_OK											(1)
#define ALI_DECV_PROBE_LACK_DATA									(2)

/* ali video decoder format:
	0  -> NULL,
	1~0x100 -> image decoder,
	0x101~0x200 -> video decoder
*/
enum ali_decv_format
{
	ALI_DECV_NULL = 0,
		
	ALI_DECV_JPEG = 1,
	ALI_DECV_BMP,
	ALI_DECV_GIF,
	ALI_DECV_PNG,
	ALI_DECV_TIFF,

	ALI_DECV_MPEG2 = 0x101,
	ALI_DECV_H264,
	ALI_DECV_MPEG4
};

/* plugin structure definition */
typedef struct
{
	enum ali_decv_format decv_format;
	char *name;

	/* probe the input video data and return the information about the data */
	int (*probe)(void *instance, void *buf, int size, void *info);

	/* create the plugin module by the track info */
	int (*create)(void *instance, void *track_info, void *info);

	/* delete the plugin module of the instance */
	void (*delete)(void *instance);

	/* decode the packet. output the frame if the handle of frame is valid*/
	int (*decode)(void *instance, void *packet, void *frame);

	/* output the frame */
	int (*output)(void *instance, void *frame);

	/* control the plugin module */
	int (*control)(void *instance, unsigned long cmd, unsigned long par);

	void *next;
}AliDecv_Plugin;
#define _AliDecv_Plugin(x) const AliDecv_Plugin x __attribute__ ((section(".alidecv.init")))

enum ali_decv_pallete_type
{
	ALI_DECV_PLT_AYCBCR8888, // 0~7 : V; 8 ~ 15 : Y 16 ~ 23 : U; ; 24 ~ 31 : Alpha
	ALI_DECV_PLT_ARGB8888, //  0~7 : B; 8 ~ 15 : G; 16 ~ 23 : R; 24 ~ 31 : Alpha
};

/* frame disposal method. it means that the way the frame to be treated after being displayed */
enum ali_decv_disposal_method
{
	ALI_DECV_DISMETD_NULL,
	ALI_DECV_DISMETD_DISALBE,
	ALI_DECV_DISMETD_RESTORE_TO_BK, // restore te backgroud color
	ALI_DECV_DISMETD_RESTORE_TO_PREVIOUS, // restore to previous frame
	ALI_DECV_DISMETD_RES
};

enum ali_decv_input_path
{
	ALI_DECV_INPUT_FROM_FILE, // input the data by file handle and operation
	ALI_DECV_INPUT_FROM_MEMORY, // input the data by the buffer address and size
	ALI_DECV_INPUT_FROM_DEMUX // input the data by demux
};

// file seek flag
#define ALI_DECV_SEEK_SET										(0)
#define ALI_DECV_SEEK_CUR    									(1)
#define ALI_DECV_SEEK_END    									(2)

typedef int (*ali_decv_fread)(unsigned long, void *, int);
typedef long long (*ali_decv_fseek)(unsigned long, long long, int);
typedef long long (*ali_decv_ftell)(unsigned long);

typedef struct
{
	ali_decv_fread fread;
	ali_decv_fseek fseek;
	ali_decv_ftell ftell;
	
	unsigned long file_handle;	
}ali_decv_file;

typedef struct
{
	unsigned long emb_valid:1;
	unsigned long med_valid:1;
	unsigned long res:30;

	/* file format */
	enum ali_decv_format format;
		
	/* bits per pixel */
	int bpp; 

	/* video logical resolution */
	unsigned long logical_width;
	unsigned long logical_height;
	
	/* embedded video data */	
	struct
	{
		enum ali_decv_format format;
		void *emb_offset;
		unsigned long emb_size;
	}emb_info;

	/* disposal method information for the lastest output frame
	, such as the GCE in gif89a specification */
	struct
	{
		unsigned long trans_color_valid:1;
		unsigned long bkg_color_valid:1;
		unsigned long res:30;
		
		enum ali_decv_disposal_method	dismeth;
		unsigned long bkg_color; // backgroud color
		unsigned long trans_color; // transparency color
	}dismetd_info;
}ali_decv_video_info;

/* ali decv track info */
typedef struct
{
	
}ali_decv_track_info;

/* ali decv input packet structure */
#define ALI_DECV_NoneTs										(0x00000000)
/* time stamp value. it is counted in some defined ratio */
#define ALI_DECV_PresentationTS								(0x00000001)
#define ALI_DECV_DecodingTS									(0x00000002)
/* absolutely time. value1 count the time by milisecond. value2 count the time by usecond*/
#define ALI_DECV_PresentationTime							(0x00000003)
#define ALI_DECV_DecodingTime								(0x00000004)

typedef struct
{
	void *buffer;
	int size;
	
	/* time stamp info */
	unsigned long timestamp_flag; // type of the time stamp
	unsigned long timestamp_value1; 
	unsigned long timestamp_value2;
}ali_decv_packet;

/* ali decv decompressed frame structure */
enum ali_decv_frame_type
{
	ALI_DECV_FRM_AUTO = 0, // ali decv select the frame type automatically

	/* macro block color format */
	ALI_DECV_FRM_YUV420 = 1,
	ALI_DECV_FRM_YUV411,
	ALI_DECV_FRM_YUV422,

	/* raster color format */
	ALI_DECV_FRM_CLUT8 = 0x101,
	
	ALI_DECV_FRM_ARGB1555 = 0x201,
	ALI_DECV_FRM_RGB565,
	ALI_DECV_FRM_ARGB8888,
	
	ALI_DECV_FRM_AYCBCR8888 = 0x301,
};

enum ali_decv_aspect_ratio
{
	ALI_DECV_DAR_FORBIDDEN = 0, //aspect ratio forbidden
	ALI_DECV_SAR, 				//sample aspect ratio
	ALI_DECV_DAR_4_3,			//Display aspect ratio 3/4
	ALI_DECV_DAR_16_9,			//Display aspect ratio 9/16
	ALI_DECV_DAR_221_1			//Display aspect ratio 1/2.11
}; //P126, value must NOT change!

typedef struct
{
	unsigned long x_offset;
	unsigned long y_offset;
	unsigned long x_size;
	unsigned long y_size;
}ali_decv_rect;

#define	VIDEO_OPEN_WIN_FLAG			0x01
#define	VIDEO_RESET_SRC_DST_FLAG		0x02
#define	VIDEO_INTO_SML_MODE             	0x04
#define	VIDEO_LEAVE_SML_MODE            	0x08
#define	VIDEO_FIRST_PIC_SYNC_FLAG	0x10

/* private information of the video frame */
typedef struct
{
	int index;
	enum ali_decv_frame_type type;
	enum ali_decv_aspect_ratio	aspect_ratio;
	int valid;
	/* bits per pixel */
	int bpp; 

	int progressive_source;
	int topfield_first;
	
	/* logical width and height of the frame */
	unsigned long x_logical_size;
	unsigned long y_logical_size;

	/* rectangle area of this frame in the logical frame*/
	ali_decv_rect rect;

	/* pallete info. it is only active when the color format is ALI_DECV_FRM_CLUT8.
	plt_buffer identify the start address of the pallete data.
	plt_size mean the length of the pallete. the unit is BYTE. plt_size must be 4byte aligned */
	enum ali_decv_pallete_type plt_type;
	void *plt_buffer;
	int plt_size;
	int plt_valid;
	
	/* frame start address and pitch. the unit of pitch is byte.
		1, when the frame format is Macro Block type, buffer1 restores
		  Y data and buffer2 restores C data. 
		2, For raster color format, only buffer1 is valid 
	*/
	void *buffer1;
	void *virtual_buf1;
	int buf1_size;
	unsigned long pitch1;
	void *buffer2;
	void *virtual_buf2;
	int buf2_size;
	unsigned long picth2;

	int laf_enable;
	void *laf_buffer;
	int laf_buf_size;

	unsigned long vpo_act_flag;
	int matrix_confficients;
	int half_mode;
	int h264_decoder;
	int dview;
	int active_format;
	int sar_width;
	int sar_height;
	
	/* display time stamp and duration. the unit is ms */
	unsigned long time_stamp;
	unsigned long time_duration;

	unsigned long frame_rate; 

	/* private information of the frame */
	void *private;

	/* if next is not NULL, get next frame by the next pointer*/
	void *next;
}ali_decv_frame;

/* ali decv io command for plugin control */
#define ALI_DECV_IO_CMD_ROTATE									(0x00000001)
#define ALI_DECV_IO_CMD_SET_INPUT									(0x00000002)
#define ALI_DECV_IO_CMD_GET_INPUT									(0x00000003)
#define ALI_DECV_IO_CMD_SET_OUTPUT								(0x00000004)
#define ALI_DECV_IO_CMD_GET_OUTPUT								(0x00000005)
#define ALI_DECV_IO_CMD_GET_FREE_FRM_ROUTINE 					(0x00000006)
#define ALI_DECV_IO_CMD_RESET_INSTANCE			 				(0x00000007)
#define ALI_DECV_IO_CMD_GET_INPUT_CALLBACK_ROUTINE				(0x00000008)
#define ALI_DECV_IO_CMD_GET_MPG_USER_DATA						(0x00000009)

/* ali decv io command parameters */

/* IO_CMD_ROTATE related parameters */
/* roate angle. it support four rotations with different angle */
enum ali_decv_angle
{
	ALI_DECV_ANG_ORI,
	ALI_DECV_ANG_90_A ,	/* Along the clock with 90 */
	ALI_DECV_ANG_180,
	ALI_DECV_ANG_90_C,	/* Counter the clock with 90 */	
};

/* rotate mode */
enum ali_decv_rotate_mode
{
	ALI_DECV_ROTATE_DECODED_FRMs, /* rotate the frames to be decoded*/
	ALI_DECV_ROTATE_INPUT_FRMs /* rotate the input frames */
};

typedef struct
{
	enum ali_decv_rotate_mode mode;
	enum ali_decv_angle angle;

	/* it is only active when the rotate mode is ALI_DECV_ROTATE_INPUT_FRMs */
	ali_decv_frame *in_frame;
}ali_decv_rotate_pars;

/* IO_CMD_SET_INPUT related parameters */
struct ali_decv_start_code
{
	uint32 	val;		// value of the start code
	uint32	addr;	// address of the start code
};

typedef int (*ali_decv_dma_copy)(unsigned long handle,void *dst, void *src, int size);
typedef int (*ali_decv_dma_get_start_code)(unsigned long handle, struct ali_decv_start_code *start_code);

typedef struct
{
	unsigned long no_support_HIGH_DEFINATION_video:1;
	unsigned long enable_DMA_function:1;
	unsigned long enable_start_code_detection:1;
	unsigned long enable_user_data_parsing:1;
	unsigned long res:28;

	/* DMA info if enable_DMA_function is valid */
	unsigned long DMA_handle;
	ali_decv_dma_copy DMA_copy;
	ali_decv_dma_get_start_code DMA_get_start_code;
}ali_decv_input_pars;

/* IO_CMD_SET_OUTPUT related parameters */
typedef int (*ali_decv_out_frm_callback_routine)(unsigned long handle, ali_decv_frame *frm);

enum ali_decv_out_frame_path
{
	ALI_DECV_OUT_FRAME_TO_KERNEL,	
	ALI_DECV_OUT_FRAME_TO_USER,		
};

enum ali_decv_output_frame_type
{
	ALI_DECV_OUTPUT_FRM_INFO_ONLY,
	ALI_DECV_OUTPUT_FRM_INFO_AND_DATA, // output the frame info and data in the frame buffer
};

enum ali_decv_post_process_type
{
	ALI_DECV_POST_PROCESS_VALID,	 // some post process to the decoded image data
	ALI_DECV_POST_PROCESS_NONE,	
};

typedef struct
{
	unsigned long enable_dual_output:1;
	unsigned long only_parse_header:1;
	unsigned long enable_laf_feature:1;
	unsigned long res:29;
	
	/* define the output frame color type. but if ali decv 
	don't support the defined output type in some plugin module, it will cancel
	this value and generate the output type automatically */
	enum ali_decv_frame_type frm_type;

	/* if the frame type is CLUT8, the out_plt_type is valid */
	enum ali_decv_pallete_type out_plt_type;

	/* output buffer address and size if decoder need detail allocate
	the buffer by itself */
	void *output_frame_buf_start1;
	int output_frame_buf_size1;
	void *output_frame_buf_start2;
	int output_frame_buf_size2;	
	
	/* maximum value of x and y size of output frame.
	if the original video size is bigger than this value, ali decv
	will do scale operation to the frame firstly then output it */	
	unsigned long max_x_size;
	unsigned long max_y_size;

	/* output handle and callback routine */
	unsigned long out_handle;
	ali_decv_out_frm_callback_routine out_callback;

	/* switch the frame output path between kernel and user space */
	enum ali_decv_out_frame_path out_path;

	/* whether need to output the frame data */
	enum ali_decv_output_frame_type output_type;

	/* some operation beside the decode. it supply the user with
	well recognized frame data. other wise it only output the raw 
	decompressed data */
	enum ali_decv_post_process_type post_process_type;
}ali_decv_output_pars;

/* IO_CMD_GET_FREE_FRM_ROUTINE related parameters */
typedef void (*ali_dec_free_frame_routine)(void *handle, ali_decv_frame *frm);


/* IO_CMD_GET_INPUT_CALLBACK_ROUTINE parameters */

#define	ALI_DECV_REQ_RET_FAIL					0
#define	ALI_DECV_REQ_RET_OK					1
#define	ALI_DECV_REQ_RET_ERROR				2

/* IO_CMD_GET_MPG_USER_DATA parameters */
#define MPG_PIC_TYPE_I				1
#define MPG_PIC_TYPE_P				2
#define MPG_PIC_TYPE_B				3
#define MPG_PIC_TYPE_D				3

typedef struct
{
	int pic_type;
	void *buf_start;
	int buf_size;
}mpg_user_data_info;

typedef struct
{
	void *handle;
	ali_dec_request_buf request;
	ali_dec_update_buf update;
}ali_decv_input_callback_pars;

typedef struct
{
	void *handle;
	ali_dec_free_frame_routine free_frm;
}ali_decv_free_frame_pars;

/* ali decv initial parameters */
typedef struct
{
	/* allocated memory info */
	void *buffer;
	int size;
}ali_decv_init_pars;

/* ali decv instance definition and related structure */
typedef struct
{	
	int id; 
	char *name;// short name to describe the related plugin module
	
	volatile unsigned long busy:1;
	volatile unsigned long res:31;
	void *private;
	void *plugin;
	void *plugin_priv;
	void *file;
	
	ali_decv_video_info video_info;

	/* path of the input data. if the path is ALI_DECV_INPUT_FROM_FILE,
	the video data is automatically goten by ali decv module and 
	ali_decv_decode() dont' need the argument packet(it could be NULL) */
	enum ali_decv_input_path in_path;

	ali_decv_input_callback_pars in_callback_pars;
	ali_decv_free_frame_pars free_frame_pars;
	
	void *next;		
}ali_decv_instance;

/* ali decv APIs */

/* init ali decv module with the inital parameters */
int ali_decv_init(ali_decv_init_pars *init, int max_decv_num);

/* create one instance of the ali decv module */
ali_decv_instance *ali_decv_create_instance(void);
/* delete the instance */
void ali_decv_delete_instance(ali_decv_instance *instance);

/* get the right instance by the decoder format. return several instances with the same format*/
ali_decv_instance *ali_decv_get_inst_by_frmt(enum ali_decv_format format);

/* get the right instance by the decoder id */
ali_decv_instance *ali_decv_get_inst_by_id(int id);

/* lock the instance and make it exclusived by the caller*/
int ali_decv_inst_lock(ali_decv_instance *instance);
/* unlock the instance */
void ali_decv_inst_unlock(ali_decv_instance *instance);

/* probe the file and return the result and some imprtant information about the video file */
int ali_decv_probe(ali_decv_instance *instance, void *buf, int size);

/* set the format of the instance. it bind and create the right video plugin to the instance by the decoder format */
int ali_decv_set_frmt(ali_decv_instance *instance, enum ali_decv_format format);

/* set the track info of the instance. it bind and create the right video plugin by the track info */
int ali_decv_set_trak_info(ali_decv_instance *instance, ali_decv_track_info *track_info);

/* decode one packect. if frame is not NULL and prepared already, the instance will directly 
output the decompressed frame. if the path is ALI_DECV_INPUT_FROM_FILE, the video data is 
automatically goten by ali decv module and ali_decv_decode() dont' need the argument packet(it could be NULL) */ 
int ali_decv_decode(ali_decv_instance *instance, ali_decv_packet *packet, ali_decv_frame *frame);

/* output the demcompressed frame. it may output more than one frames once */
int ali_decv_output(ali_decv_instance *instance, ali_decv_frame *frame);

/* free the frame buffer */
void ali_decv_free_frame(ali_decv_instance *instance, ali_decv_frame *frame);

/* request the free input buffer and update the write pointer for the data from DEMUX */
int ali_decv_request_buf(ali_decv_instance *instance,void **buf_start, int *buf_size, struct ctrl_blk *blk);
void ali_decv_update_buf(ali_decv_instance *instance, int buf_size);

/* control the instance with some special application */
int ali_decv_control(ali_decv_instance *instance, unsigned long cmd, unsigned long par);

/* ioctl command list */
#define ALIDECVIO_CREATE_INSTANCE							0x00000001
#define ALIDECVIO_DELETE_INSTANCE							0x00000002
#define ALIDECVIO_GET_INSTANCE_DATA						0x00000003

#define ALIDECVIO_PROBE_FILE								0x00000010
#define ALIDECVIO_SET_FRMT									0x00000020
#define ALIDECVIO_SET_TRAK_INFO							0x00000030
#define ALIDECVIO_SET_INPUT_PATH							0x00000040
#define ALIDECVIO_GET_INPUT_PARS							0x00000050
#define ALIDECVIO_SET_INPUT_PARS							0x00000060
#define ALIDECVIO_GET_OUTPUT_PARS							0x00000070
#define ALIDECVIO_SET_OUTPUT_PARS							0x00000080

#define ALIDECVIO_DECODE									0x00000100
#define ALIDECVIO_OUTPUT									0x00000200
#define ALIDECVIO_FREE_FRM									0x00000300
#define ALIDECVIO_REQUEST_BUF								0x00000400
#define ALIDECVIO_UPDATE_BUF								0x00000500

/* ALIDECVIO_PROBE_FILE */
#define ALI_DECV_PROBE_FAIL										(0)
#define ALI_DECV_PROBE_OK											(1)
#define ALI_DECV_PROBE_LACK_DATA									(2)

typedef struct
{
	void *buf;
	int size;
} ali_decv_probe_pars;

#endif
