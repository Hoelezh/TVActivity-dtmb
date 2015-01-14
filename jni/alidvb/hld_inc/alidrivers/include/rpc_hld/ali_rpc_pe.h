#ifndef __DRIVERS_ALI_RPC_PE_H
#define __DRIVERS_ALI_RPC_PE_H

#include "ali_rpc_hld.h"
#include "ali_rpc_hld_decv.h"
#include "ali_rpc_hld_snd.h"
#include "ali_rpc_hld_deca.h"
#include "ali_rpc_hld_dis.h"

#include <alidefinition/adf_image.h>

#define IMAGEDEC_MAX_INSTANCE 1

/*status control wait flag ptn*/
#define IMAGEDEC_STOP_PTN			0x00000001
#define IMAGEDEC_DECD_PTN			0x00000002
#define IMAGEDEC_FILL_IN_BUF_PTN   0x00000004

#define IMAGEDEC_TIME_OUT_DECD	(20000)
#define IMAGEDEC_TIME_OUT_STOP	(1000)
#define IMAGEDEC_TIME_OUT_READ	OSAL_WAIT_FOREVER_TIME

/*imagedec io cmd list*/
#define IMAGEDEC_IO_CMD_OPEN_HW_ACCE		0x01
#define IMAGEDEC_IO_CMD_FILL_LOGO  			0x02
#define IMAGEDEC_IO_CMD_CLEAN_FRM			0x03
#define IMAGEDEC_IO_CMD_OSD_SHOW			0x04
#define IMAGEDEC_IO_CMD_COPY_FRM			0x05
#define IMAGEDEC_IO_CMD_DIS_FRM_INFO		0x06
#define IMAGEDEC_IO_CMD_NEED_LOGO			0x07
#define IMAGEDEC_IO_CMD_CFG_DEO_FRM			0x08

#define IMAGEDEC_SHOW_MODE_PAR_LEN 	(4)

enum IMAGE_JPG_CODING_TYPE
{
	SEQUENTIAL_JPEG,
	PROGRESSIVE_JPEG
};

enum FRM_UNIT_TYPE
{
	FRM_UNIT_36_MP2,			// for 3602 series 32*16 memory mapping mode
	FRM_UNIT_27				// for 27   series 16*16 memory mapping mode 
};

enum IMAGE_DEC_ERROR
{
	IMG_ER_FILE = 1,
	IMG_ER_MEM,	
};

/*every image decoder with a device id*/
typedef unsigned long imagedec_id;

typedef enum 
{
	JPEG = 1,
	Bitmap,
	RESERVED_TYPE,
}imagedec_file_format;

typedef struct Image_info_t
{
	imagedec_file_format file_type;		//only support jpeg and BMP 
	int precision;		// bit count of pixel
	int image_width;
	int image_height;
	int scan_type;
	int coding_type;			//progressive or sequential
	int coding_progress;		//for slide show solution know the progress of the decoding. (value>>16) is 0.x of the work
	int reserved;
}Image_info, *pImage_info;

typedef struct Imagedec_Out_Image_t
{
	UINT32 start_buf;
	UINT16 width;
	UINT16 height;
	UINT32 bpp;		// bits per pixel
	UINT32 stride; 	// bytes of every line
}Imagedec_Out_Image,*pImagedec_Out_Image;

typedef struct Imagedec_Osd_Config_t
{
	void *handle;
	UINT32 pic_frmt;
	void (*blt)(void *,pImagedec_Out_Image,struct Rect *);
}Imagedec_Osd_Config,*pImagedec_Osd_Config;

typedef struct Imagedec_Osd_Io_Cmd_t
{
	UINT32 on:1;
	UINT32 res:31;

	struct Rect dis_rect;
	UINT32 bitmap_start; // restore the decompressed picture data
	UINT32 bitmap_size;
}Imagedec_Osd_Io_Cmd,*pImagedec_Osd_Io_Cmd;

typedef struct Imagedec_Io_Cmd_Copy_Frm_t
{
	void *logo_buf;
	UINT32 y_buf_size;
	UINT32 c_buf_size;
	UINT16 width;
	UINT16 height;
}Imagedec_Io_Cmd_Copy_Frm,*pImagedec_Io_Cmd_Copy_Frm;

typedef struct Imagedec_Io_Cmd_Frm_Info_t
{
	UINT32 y_buf;
	UINT32 c_buf;
	UINT32 y_size;
	UINT32 c_size;
}Imagedec_Io_Cmd_Frm_Info,*pImagedec_Io_Cmd_Frm_Info;

#define PE_CACHE_CMD_NULL  0
#define PE_CACHE_CMD_OPEN  1
#define PE_CACHE_CMD_CLOSE 2
#define PE_CACHE_CMD_SEEK  3

#define PE_CACHE_REQ_FAIL	0
#define PE_CACHE_REQ_OK	1
#define PE_CACHE_REQ_BUSY	2

#define PE_CACHE_SEEK_FAIL 0
#define PE_CACHE_SEEK_OK	1
#define PE_CACHE_SEEK_MORE 2

typedef enum 
{
  PEStop      = 0,
  PEPlay      = 1,
  PEPauseStep = 2,
  PEFFx2      = 3,
  PEFFx4      = 4,
  PEFFx8x16x32 = 5,
  PESlow      = 6,
  PERev       = 7,
  PEResumeStop = 8
}AF_PE_PLAY_STATE, *PAF_PE_PLAY_STATE;

typedef struct _DEC_CHAPTER_INFO
{
    DWORD nb_chapter;           /* number of chapters */
    INT32 cur_chapter;          /* current chapter */
    INT32 cur_start_time;       /* current chapter start time in second */
    INT32 cur_end_time;         /* current chapter end time in second */
    char  cur_title[10];        /* current chapter title name */
    INT32 dst_chapter;          /* current chapter */
    INT32 dst_start_time;       /* current chapter start time in second */
    INT32 dst_end_time;         /* current chapter end time in second */

    UINT32 reserved;            /* reserved */
}DEC_CHAPTER_INFO, *PDEC_CHAPTER_INFO;
typedef struct
{
	char VideoDec[10]; //the name of the video codec. For now, we support below video codec:
	                   //"div3", "div4", "mp43", "XIV1", "XIV2", "DX50", "XVID", "unknown"
	char AudioDec[10]; //the name of the audio codec. For now, we support below audio codec:
	                   //"PCM", "MP3", "AC3", "DTS", "unknown"
	DWORD AudioStreamNum; //The audio track number in the media stream
	DWORD SubStreamNum; //The subtitle stream number in the media stream
	DWORD TotalFrameNum; //The total frame number of the media stream
	DWORD FramePeriod; //The frame period of the media stream
	DWORD TotalTime; //Total play time of the media stream
	int   width; //The width of the media stream. The maximum width the video decoder can support is 720.
	int   height; //The height of the media stream. The maximum height the video decoder can support is 576.
	DWORD VideoBitrate;
	DWORD AudioBitrate;
	DWORD AudioChannelNum;
	UINT32 fsize;
	INT32 AudioSampleRate;
	INT32 video_codec_tag;
	INT32 cur_audio_stream_id;
    INT32 cur_sub_stream_id;
	INT32 cur_prog_id;
	DWORD ProgNum;
}fileinfo_video, *p_fileinfo_video;

enum VIDEO_ENGINE_FUNC
{
    FUNC_VIDEO_ENGINE_INIT = 0,   
    FUNC_VIDEO_ENGINE_PE_CACHE_INIT,
    FUNC_VIDEO_ENGINE_DECODE,   
    FUNC_VIDEO_ENGINE_SET_OUTPUT,
    FUNC_VIDEO_ENGINE_CMD_PLAY,
    FUNC_VIDEO_ENGINE_CMD_PAUSE,
    FUNC_VIDEO_ENGINE_CMD_RESUME,
    FUNC_VIDEO_ENGINE_CMD_FF,
    FUNC_VIDEO_ENGINE_CMD_FB,
    FUNC_VIDEO_ENGINE_CMD_SLOW,
    FUNC_VIDEO_ENGINE_CMD_STOP,
    FUNC_VIDEO_ENGINE_CMD_SEARCH,
    FUNC_VIDEO_ENGINE_CMD_CHANGE_AUDIO_TRACK,
    FUNC_VIDEO_ENGINE_CMD_CHANGE_PROG,
    FUNC_VIDEO_ENGINE_GET_STREAM_INFO,
    FUNC_VIDEO_ENGINE_GET_PLAY_TIME,
    FUNC_VIDEO_ENGINE_GET_TOTAL_PLAY_TIME,
    FUNC_VIDEO_ENGINE_PE_CACHE_RELEASE,    
    FUNC_VIDEO_ENGINE_CMD_SEARCH_MS,
    FUNC_VIDEO_ENGINE_CMD_RESUME_STOP,
    FUNC_VIDEO_ENGINE_CMD_CHANGE_SUBTITLE,
    FUNC_VIDEO_ENGINE_GET_CHAPTER_INFO,
    FUNC_VIDEO_ENGINE_DECODER_CONTROL,
    FUNC_VIDEO_ENGINE_GET_NEXT_STATE,
    FUNC_VIDEO_ENGINE_GET_TOTAL_PLAY_TIMEMS,
    FUNC_VIDEO_ENGINE_GET_PLAY_TIMEMS,
    FUNC_VIDEO_ENGINE_SET_AVSYNC_DELAY,
};

enum MUSIC_ENGINE_FUNC
{
    FUNC_MUSIC_ENGINE_INIT = 0,   
    FUNC_MUSIC_ENGINE_RELEASE,
    FUNC_MUSIC_ENGINE_PLAY,
    FUNC_MUSIC_ENGINE_SEEK,
    FUNC_MUSIC_ENGINE_STOP,
    FUNC_MUSIC_ENGINE_PAUSE,
    FUNC_MUSIC_ENGINE_GET_TIME,
    FUNC_MUSIC_ENGINE_SET_EQ,
    FUNC_MUSIC_ENGINE_GET_SONG_INFO,
    FUNC_MUSIC_ENGINE_GET_DECODER_INFO,
};

enum IMAGE_ENGINE_FUNC{
    FUNC_IMAGE_ENGINE_INIT = 0,   
    FUNC_IMAGE_ENGINE_CLEANUP,
    FUNC_IMAGE_ENGINE_ROTATE,
    FUNC_IMAGE_ENGINE_DECODE,
    FUNC_IMAGE_ENGINE_SHOW,
    FUNC_IMAGE_ENGINE_ABORT,
    FUNC_IMAGE_ENGINE_ZOOM,
    FUNC_IMAGE_ENGINE_GET_INFO,
    FUNC_IMAGE_ENGINE_IO_CONTROL,
};

#define UNKNOWN_STREAM 					0
#define MPEG_12_FILE_STREAM             1
#define AVI_STREAM 						2
#define MKV_STREAM 						3

//define the callback function for APP
#define MP_FS_MOUNT				    (1 << 0)
#define MP_FS_UNMOUNT				(1 << 1)
#define MP_MUSIC_PLAYBACK_END		(1 << 2)
#define MP_IMAGE_PLAYBACK_END		(1 << 3)
#define MP_IMAGE_DECODE_PROCESS 	(1 << 4)
#define MP_FS_IDE_MOUNT_NAME		(1 << 5)
#define MP_FS_USB_MOUNT_NAME		(1 << 6)
#define MP_VIDEO_PLAYBACK_END       (1 << 7)
#define MP_IMAGE_DECODER_ERROR		(1 << 8)
#define MP_VIDEO_BUILD_IDX_TBL      (1 << 9)
#define MP_VIDEO_PARSE_END          (1 << 10)
#define MP_VIDEO_DECODER_ERROR		(1 << 11)

// param in mp_callback_func(MP_VIDEO_BUILD_IDX_TBL, param)
#define MP_VIDEO_BUILD_IDX_TBL_BEGIN    0
#define MP_VIDEO_BUILD_IDX_TBL_END      1

/* param in mp_callback_func(MP_VIDEO_DECODER_ERROR, param),
   and in mp_callback_func(MP_VIDEO_PARSE_END, param);  */
#define MP_DERR_OK                      0
#define MP_DERR_UNSUPPORTED_VIDEO_CODEC (1<<0)
#define MP_DERR_UNSUPPORTED_AUDIO_CODEC (1<<1)
#define MP_DERR_UNSUPPORTED_RESOLUTION  (1<<2)
#define MP_DERR_UNSUPPORTED_FRAME_RATE  (1<<3)
#define MP_DERR_TOO_BIG_INTERLEAVE      (1<<4)
#define MP_DERR_MP4_DRM_AUTH            (1<<5)
#define MP_DERR_UNKNOWN                 0xffffffff

#define PE_CACHE_NUM    2

#define PE_CACHE_CLOSED     0
#define PE_CACHE_OPENED     1

#define PE_FILE_READING     0
#define PE_FILE_FAILED      1
#define PE_FILE_EOF         2

#define PE_PREVIOUS_BUFFER_SIZE 10240 //10K

#define PE_NET_FILE_TYPE_URL 0
#define PE_NET_FILE_TYPE_MAX 1
typedef void(*mp_callback_func)(unsigned long type, unsigned long param);
#ifdef PE_CALLBACK_TO_APP_ENABLE		
typedef void(*pccache_callback_func)(UINT8 type, UINT8 param);
#endif

#if 0
//define function point for pe_cache use
typedef  FILE * (* pe_cache_open_fp)(const char *, unsigned char* , unsigned int, unsigned int );//filename, buf, cache length, offset
typedef size_t (* pe_cache_read_fp)(void *, size_t, size_t, FILE *);
typedef int(* pe_cache_seek_fp)(FILE *, off_t, int);
typedef int (* pe_cache_feof_fp)(FILE*);
typedef off_t (* pe_cache_ftell_fp)(FILE *);
typedef int (* pe_cache_fclose_fp)(FILE *);
#endif

typedef struct
{
    UINT16 internal_cache;
#if 0	
    FILE *fp;
#else
    void *fp;
#endif

    UINT32 block_size;
    long long file_size;

#ifdef ENABLE_PE_FLAG
    UINT32 req_size;
    WORD flag;
#endif

#if 0
   //add function point  for pe_cache callback
   pe_cache_read_fp file_read;
   pe_cache_seek_fp file_seek;
   pe_cache_feof_fp file_eof;
   pe_cache_ftell_fp file_tell;
   pe_cache_fclose_fp file_close;
#else
   void *file_read;
   void *file_seek;
   void *file_eof;
   void *file_tell;
   void *file_close;
#endif

#ifdef LOG_PE_CACHE
    UINT32 read_delay;
    UINT32 read_count;
    UINT32 read_tick;
    UINT32 read_size;
#endif
}pe_cache, *p_pe_cache;

typedef struct
{
	UINT8 status;
	UINT8 sub_status;
	WORD mutex;
	UINT8 *cache_buff;
	UINT32 cache_size;
	UINT32 data_len;
	UINT32 rd_pos;
	UINT32 wr_pos;
	long long file_offset;	
}pe_cache_ex;

#if 1//def DUAL_ENABLE
#define PE_CACHE_CMD_NULL  0
#define PE_CACHE_CMD_OPEN  1
#define PE_CACHE_CMD_CLOSE 2
#define PE_CACHE_CMD_SEEK  3

#define PE_CACHE_CMD_STATUS_NEW 1
#define PE_CACHE_CMD_STATUS_IMPLEMENTED 2

typedef struct
{
    UINT32 status     :2; 
    UINT32 type       :2;
    UINT32 reserved   :28;
    UINT32 param[4];
}pe_cache_cmd;
#endif

struct pe_feature_cfg
{
	UINT32 chip;

	UINT32 using_adpcm;
	UINT32 has_dview;  // has divew same as vpo of M3327C 
	UINT32 has_pip;		// has pip same as vpo of M3329E 
	UINT32 has_sca;		// has dview scaler as vpo of M3101C 
};	

struct pe_image_cfg
{
	
	// dst frame info
	UINT32 frm_y_addr;
	UINT32 frm_y_size;
	UINT32 frm_c_addr;
	UINT32 frm_c_size;
	UINT32 frm2_y_addr;
	UINT32 frm2_y_size;
	UINT32 frm2_c_addr;
	UINT32 frm2_c_size;
	UINT32 frm_mb_type;
	UINT32 frm3_y_addr;
	UINT32 frm3_y_size;
	UINT32 frm3_c_addr;
	UINT32 frm3_c_size;
	UINT32 frm4_y_addr;
	UINT32 frm4_y_size;
	UINT32 frm4_c_addr;
	UINT32 frm4_c_size;

	// buf for dec internal usage
	UINT8 *decoder_buf;
	UINT32 decoder_buf_len;
	
	//callback function for application
	mp_callback_func mp_cb;		
};

struct img_callback
{
    mp_callback_func mp_cb;
};

struct pe_music_cfg
{
	//buff
	UINT32 pcm_out_buff;
	UINT32 pcm_out_buff_size;
	UINT32 processed_pcm_buff;
	UINT32 processed_pcm_buff_size;
	
	//callback function for application
	mp_callback_func mp_cb;	
};

struct pe_video_cfg
{
	mp_callback_func mp_cb;
	UINT32 decoder_buf;
	UINT32 decoder_buf_len;
	UINT32 mm_vbv_len;
	BOOL   disable_seek;
	UINT32 reserved;    // struct pe_video_cfg_extra *. set to 0 if no pe_video_cfg_extra
};

struct pe_video_cfg_extra
{
    UINT32 frame_buf_base;
    UINT32 frame_buf_len;
    UINT16 max_width_support, max_height_support;   // if 0, determined by frame_buf_len
    UINT32 reserved[5];    // use in the future, should set to 0
};

typedef struct
{
    struct pe_image_cfg image;
    struct pe_music_cfg music;
    struct pe_video_cfg video;
}PeConfig, *p_pe_config;

#if 0
typedef struct
{
	pe_cache_open_fp file_open;
	pe_cache_read_fp file_read;
	pe_cache_seek_fp file_seek;
	pe_cache_feof_fp file_eof;
	pe_cache_ftell_fp file_tell;
	pe_cache_fclose_fp file_close;
}pe_cache_cb_fp;


//int pe_init(struct pe_music_cfg *music_cfg, struct pe_image_cfg *image_cfg);
int pe_cleanup();
#endif


//============================================================================
// image structure and functions

#if 0
int image_abort();
int image_decode(char *file, int mode, int left, int top, int width, int height, unsigned char rotate);
int image_decode_ex(char *file, int mode, int left, int top, int width, int height, unsigned char rotate, struct image_slideshow_effect *effect);

int image_get_info(char *filename, struct image_info *info );
void image_restore_vpo_rect();
int image_zoom(struct Rect *dstRect, struct Rect *srcRect);
#endif


//============================================================================
// music structure and functions

typedef enum 
{
	Mp3,
	Wma,
	Aac,
	Rm
}MusicType;

typedef struct 
{
	char title[30];			/*标题*/
	char artist[30];		/*作者*/
	char album[30];			/*专集*/
	char year[4];			/*出品年代*/
	char comment[30];		/*备注*/
	char genre;			/*类型*/
	char track;
	unsigned long time;
	unsigned long file_length;
}MusicInfo;


typedef struct _DECODER_INFO {
	unsigned long	bit_rate;				//bps
	unsigned long	sample_rate;			//KHz
	unsigned long	channel_mode;
}DecoderInfo;

#if 0
int music_play(char *filename);
void music_seek(int time);
void music_stop(void);
void music_pause(void);
int music_get_time(void);
void music_set_eq(int on, float preamp, float *bands);
int music_get_song_info(char * filename, MusicInfo *music_info);
int music_get_decoder_info(char * filename, DecoderInfo *decoder_info);

#define PE_CACHE_AUTO_THRESHOLD     0xFFFFFFFF
int pe_cache_init();
int pe_cache_open(char *filename, UINT8 *cache_buff, UINT32 cache_size, UINT32 block_size);
UINT32 pe_cache_close(int cache_id);
UINT32 pe_cache_read(int cache_id, UINT8 *buff, UINT32 size, UINT32 threshold);
UINT32 pe_cache_get(int cache_id, UINT8 **ptr, UINT32 size, UINT32 threshold);
void pe_cache_invalidate(int cache_id, UINT8 *ptr, UINT32 size);
int pe_cache_seek(int cache_id, off_t offset, int where);
int pe_cache_check_eof(int cache_id);
UINT32 pe_cache_get_data_len(int cache_id);
off_t pe_cache_tell(int cache_id);
#endif

int ali_rpc_pe_cache_open_flag(void);
int ali_rpc_pe_cache_get_cmd(unsigned long *par1, unsigned long *par2
	, unsigned long *par3, unsigned long *par4);
void ali_rpc_pe_cache_finish_cmd(unsigned long ret_value);
int ali_rpc_pe_cache_request(int index, void **buf_start, int *buf_size);
void ali_rpc_pe_cache_update(int index, int update_size);
void ali_rpc_pe_cache_file_end(int index);
void ali_rpc_pe_cache_file_fail(int index);
int ali_rpc_pe_cache_open(void *file, long long file_size, void *buf, int size, int block_size, int res_size);
void ali_rpc_pe_cache_close(int index);
int ali_rpc_pe_cache_seek(int index, long long offset, int where);
int ali_rpc_pe_cache_need_new_data(int index);
int ali_rpc_pe_cache_init(int mutex_id);
void ali_rpc_pe_cache_release(void);

struct image_config
{
	char *file_name;

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

	//callback function
	mp_callback_func mp_cb;
};

int image_engine_init(struct pe_image_cfg *pe_image_cfg);
int image_engine_cleanup(void);
int image_engine_rotate(unsigned char rotate_angle);
int image_engine_decode(char *filename, struct image_config *cfg);
int image_engine_show(void);
int image_engine_abort(void);
int image_engine_zoom(struct Rect *dstRect, struct Rect *srcRect);
int image_engine_get_info(char *filename, struct image_info *info);
BOOL imagedec_ioctl(unsigned long id,UINT32 cmd, UINT32 para);

int music_engine_init(struct pe_music_cfg *pe_music_cfg);
void music_engine_release(void);
int music_engine_play(char *filename);
void music_engine_seek(int time);
void music_engine_stop(void);
void music_engine_pause(void);
int music_engine_get_time(void);
void music_engine_set_eq(int on, float preamp, float *bands);
int music_engine_get_song_info(char * filename, MusicInfo *music_info);
int music_engine_get_decoder_info(char * filename, DecoderInfo *decoder_info);

int video_engine_init(struct pe_video_cfg *pe_video_cfg);
int video_engine_pe_cache_init(pe_cache_ex *pe_cache_info, pe_cache_cmd *pe_cache_cmd_buf, int pe_cache_mutex);
int video_engine_decode(char *video_file, UINT8 video_stream_type, enum SndDupChannel audio_channel, BOOL preview);
int video_engine_set_output(enum VDecOutputMode eOutMode, struct VDecPIPInfo *pInitInfo);
int video_engine_pe_cache_release(void);
DWORD mpg_cmd_play_proc(void);
DWORD mpg_cmd_pause_proc(void);
DWORD mpg_cmd_resume_proc(void);
DWORD mpg_cmd_ff_proc(void);
DWORD mpg_cmd_fb_proc(void);
DWORD mpg_cmd_slow_proc(void);
DWORD mpg_cmd_stop_proc(void);
DWORD mpg_cmd_search_proc(DWORD search_time);
DWORD mpg_cmd_search_ms_proc(DWORD search_ms_time);
DWORD mpg_cmd_change_subtitle(INT32 sub_pid);
DWORD mpg_cmd_change_audio_track(INT32 *aud_pid);
DWORD mpg_cmd_change_prog(int prog_id);
DWORD MpgFileGetStreamInfo(p_fileinfo_video pDecStreamInfo);
DWORD MpgFileGetChapterInfo(PDEC_CHAPTER_INFO pDecChapterInfo);
DWORD MPGFileDecoderGetPlayTime(void);
DWORD MPGFileDecoderGetPlayTimeMS(void);
DWORD mpg_cmd_resume_stop_proc(void);
int MPGGetTotalPlayTime(void);
DWORD MPGGetTotalPlayTimeMS(void);
RET_CODE video_decoder_ioctl(unsigned long io_cmd, unsigned long param1, unsigned long param2);
AF_PE_PLAY_STATE get_next_play_state(void);
DWORD MpgSetAVSyncDelay(UINT32 stream_type, INT32 time_ms);
#endif

