
#ifndef __ADF_BOOT__
#define __ADF_BOOT__

#define MEDIA_BLOCK_MAXCOUNT 0x8
#define MEDIA_PLAYLIST_MAXCOUNT 64

#define TVE_SYSTEM_NUM              20
#define TVE_ADJ_FIELD_NUMBER    100
#define TVE_ADJ_REG_NUM             100
#define TVE_ADV_ADJ_REG_NUM        100

typedef struct
{
	unsigned char hdcp[286];
	unsigned short hdcp_disable;
}ADF_BOOT_HDCP;

typedef struct
{
	unsigned char tvSystem;
	unsigned char progressive;
	unsigned char tv_ratio;
	unsigned char display_mode;
	
	unsigned char scart_out;
	unsigned char vdac_out[6];
	unsigned char video_format;
	
	unsigned char audio_output;
	unsigned char brightness;
	unsigned char contrast;
	unsigned char saturation;
	
	unsigned char sharpness;
	unsigned char hue;
	unsigned char resv[10];
}ADF_BOOT_AVINFO;

typedef struct
{
	unsigned char phyaddr1[8];	
	unsigned char phyaddr2[8];	
	unsigned char phyaddr3[8];	
	unsigned char phyaddr4[8];	
}ADF_BOOT_MAC_PHYADDR;

typedef struct
{
    unsigned int memory_size;
    
	unsigned int kernel_start;
	unsigned int kernel_len;

	unsigned int boot_see_start;
	unsigned int boot_see_len;
	
	unsigned int see_start;
	unsigned int see_len;

	unsigned int ae_start;
	unsigned int ae_len;

	unsigned int mcapi_start;
	unsigned int mcapi_len;

	unsigned int decv_fb_start;
	unsigned int decv_fb_len;

	unsigned int decv_raw_start;
	unsigned int decv_raw_len;

	unsigned int osd_fb_start;
	unsigned int osd_fb_len;

	unsigned int boot_media_start;
	unsigned int boot_media_len;
	unsigned int ramdisk_start;
	unsigned int ramdisk_len;

	unsigned int vbv_start_512m;
	unsigned int vbv_len_512m;
	unsigned int vbv_start_1g;
	unsigned int vbv_len_1g;
	
	unsigned int cmd_queue_buffer_start_512m;
	unsigned int cmd_queue_buffer_len_512m;
	unsigned int cmd_queue_buffer_start_1g;
	unsigned int cmd_queue_buffer_len_1g;

	unsigned int video_fb_start_512m;
	unsigned int video_fb_end_512m;
	unsigned int video_fb_start_1g;
	unsigned int video_fb_end_1g;
	
	unsigned int vcap_buffer_start_512m;
	unsigned int vcap_buffer_len_512m;
	unsigned int vcap_buffer_start_1g;
	unsigned int vcap_buffer_len_1g;

	unsigned int reserve[763];
	
}ADF_BOOT_MEMMAPINFO; // maximun is 800X4 bytes

#define MAX_REGISTER_NUM		64
#define REGISTER_VALID_MAGIC		0x78AC88EF

struct REGISTER_SETTING
{
	unsigned int magic;
	unsigned int addr;
	unsigned int bits_offset;
	unsigned int bits_size;
	unsigned int bits_value;
};

typedef struct
{	
	unsigned int valid_count;
	struct REGISTER_SETTING unit[MAX_REGISTER_NUM];
}ADF_REGISTERINFO;


struct tve_adjust_element
{
	unsigned int field_index;
	unsigned int field_value;
};

struct tve_adjust_table
{
	unsigned int index;
	struct tve_adjust_element field_info[TVE_ADJ_FIELD_NUMBER];
};

struct sd_tve_adjust_table 
{
	unsigned char type;
	unsigned char sys;
	unsigned int value;
};

typedef struct
{
	struct tve_adjust_table tve_adjust_table_info[TVE_SYSTEM_NUM];       //804 * 20
	struct sd_tve_adjust_table sd_tve_adj_table_info[TVE_ADJ_REG_NUM];      //8 * 100
	struct sd_tve_adjust_table sd_tve_adv_adj_table_info[TVE_ADV_ADJ_REG_NUM];    // 8 * 100
	unsigned char reserve[8944];
}ADF_BOOT_TVEINFO; // maximun is 26k = 26 X 1024 =  26624 bytes

enum ADF_BOOT_MEDIA_CMD
{
	BOOT_MEDIA_IDLE = 1,
	BOOT_MEDIA_START,
	BOOT_MEDIA_PLAYING,
	BOOT_MEDIA_FINISHED,
};

enum ADF_BOOT_MEDIA_STATUS
{
	MEDIA_FILE_IDLE = 1,
	MEDIA_FILE_START,
	MEDIA_FILE_PLAYING,
	MEDIA_FILE_FINISHED,
};

typedef struct
{
	unsigned int play_enable;
	enum ADF_BOOT_MEDIA_CMD start_cmd;
	enum ADF_BOOT_MEDIA_CMD finish_cmd;	
	enum ADF_BOOT_MEDIA_STATUS jpeg_show_status;
	enum ADF_BOOT_MEDIA_STATUS mpeg2_show_status;
	enum ADF_BOOT_MEDIA_STATUS mkv_show_status;
	unsigned int smart_output_enable;
}ADF_BOOT_MEDIAINFO;


typedef struct
{
	int gma_enable;
	int gma_layer_id;

	int format;//see adf_gma.h enum GMA_FORMAT
	
	int x, y;
	int w, h;

	unsigned int gma_buffer;
	unsigned int gma_pitch;

	unsigned int pallett[256];
	int full_screen;
}ADF_BOOT_GMA_INFO;

typedef struct
{
	int live_flag;
	int live_tick;
}ADF_SEE_HEART_BEAT;

typedef struct
{
	ADF_BOOT_HDCP hdcp;	
	ADF_BOOT_AVINFO avinfo;		
	ADF_BOOT_MEMMAPINFO memmap_info;
	ADF_BOOT_TVEINFO tve_info;
	ADF_REGISTERINFO reg_info;
	ADF_BOOT_MAC_PHYADDR macinfo;
	ADF_BOOT_MEDIAINFO	media_info;
	ADF_BOOT_GMA_INFO gma_info;
ADF_SEE_HEART_BEAT heart_beat;

 }ADF_BOOT_BOARD_INFO; // the maximun size is 128K

#define PRE_DEFINED_ADF_BOOT_START			(0x84000000 - 0x20000)

enum ADF_BOOT_MEDIA_TYPE
{
	BOOT_MEDIA_TYPE_MIN = 10,
		
	// logo
	BOOT_MEDIA_MPEG2_Logo, 
	BOOT_MEDIA_JPEG_Logo,

	// video
	BOOT_MEDIA_MKV_Video = 110,

	BOOT_MEDIA_TYPE_MAX,		
};

#define ADF_BOOT_MEDIA_MAGIC		"adfbootmedia"
#define ADF_BOOT_MEDIA_MAGIC_LEN 	16

typedef struct
{
	unsigned int block_offset;//表示某个媒体文件的偏移
	unsigned int block_len;//此Block媒体文件的长度
	enum ADF_BOOT_MEDIA_TYPE media_type;//标识媒体的类型
	unsigned int play_time; // the default play time is 5 seconds	
}ADF_BOOT_MEDIA_BLOCK_HEADER;

//max 256bytes
typedef struct
{
	unsigned char magic[ADF_BOOT_MEDIA_MAGIC_LEN];
	unsigned short media_block_count;//标识媒体文件中包含的多媒体的个数（mpeg2/jpeg/....）
	unsigned short play_count;//标识实际播放的多媒体的个数
	unsigned char play_select_index[MEDIA_PLAYLIST_MAXCOUNT];//标识选择播放的多媒体的序号
	ADF_BOOT_MEDIA_BLOCK_HEADER block_hdr[MEDIA_BLOCK_MAXCOUNT];//标识每个多媒体block信息
	unsigned char reserve[44];
}ADF_BOOT_MEDIA_HEADER;

#endif

