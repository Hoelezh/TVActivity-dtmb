#ifndef	_ALI_HDMI_COMMON_H_
#define	_ALI_HDMI_COMMON_H_


#include <alidefinition/adf_basic.h>
#include <alidefinition/adf_media.h>


#define ALI_HDMI_MSG_EDID		1
#define ALI_HDMI_MSG_PLUGIN		2
#define ALI_HDMI_MSG_PLUGOUT	3
#define ALI_HDMI_MSG_CEC		4

/**@brief HDMI Link Status*/
typedef enum
{
	HDMI_STATUS_UNLINK = 0x01,				/**< HDMI not link */
	HDMI_STATUS_LINK_HDCP_SUCCESSED = 0x02,
	HDMI_STATUS_LINK_HDCP_FAILED = 0x04,
	HDMI_STATUS_LINK_HDCP_IGNORED = 0x08,
	HDMI_STATUS_MAX = 0x10,
	HDMI_STATUS_LINK = 0x20,
}HDMILinkStatus_E;

typedef enum TV_SYS_TYPE
{
//SD
	TV_MODE_AUTO = 0,	// switch by source
	TV_MODE_PAL,
	TV_MODE_PAL_M,		// PAL3.58
	TV_MODE_PAL_N,
	TV_MODE_NTSC358,	// NTSC3.58
	TV_MODE_NTSC443,
	TV_MODE_SECAM,
//HD
	TV_MODE_576P,
	TV_MODE_480P,
	TV_MODE_720P_50,
	TV_MODE_720P_60,
	TV_MODE_1080I_25,
	TV_MODE_1080I_30,
	TV_MODE_BY_EDID,
	TV_MODE_1080P_50,
	TV_MODE_1080P_60,	
	TV_MODE_1080P_25,
	TV_MODE_1080P_30,	
	TV_MODE_1080P_24,
	TV_MODE_4096X2160_24,
	TV_MODE_3840X2160_24,
	TV_MODE_3840X2160_25,
	TV_MODE_3840X2160_30
}TV_SYS_TYPE;

enum _3D_STRUCTURE
{
	FRAME_PACKING_3D	   = 0,
	FIELD_ALTERNATIVE_3D   = 1,
	LINE_ALTERNATIVE_3D    = 2,
	SIDE_BY_SIDE_FULL_3D   = 3,
	L_DEPTH_3D             = 4,
	L_DEPTH_GRAPHICS_3D    = 5,
	TOP_AND_BOTTOM_3D      = 6,
	SIDE_BY_SIDE_HALF_3D   = 8,
};

enum EXT_VIDEO_FORMAT
{
	NO_ADDITIONAL_VIDEO_FORMAT_PRESENTED	= 0,
	EXT_RESOLUTION_FORMAT_PRESENTED			= 1,
	_3D_FORMAT_INDICATION_PRESENTED			= 2,
};

enum EXT_DATA_FIELD
{
	HORIZONTAL_SUB_SAMPLING	= 0,
	ODD_LEFT_ODD_RIGHT	= 4,
	ODD_LEFT_EVEN_RIGHT	= 5,
	EVEN_LEFT_ODD_RIGHT	= 6,
	EVEN_LEFT_EVEN_RIGHT	= 7,
};

typedef struct
{    
	TV_SYS_TYPE					resolution;         // Output Resolution
	enum PicFmt					color_format;       // Color Format
	enum TVMode					aspect_ratio;       // 4:3, 16:9
 	BOOL						afd_present;        //
	unsigned char				afd;                //
	enum 	EXT_VIDEO_FORMAT	ext_video_format;	//add for 3d function
	enum	_3D_STRUCTURE		_4K_VIC_3D_structure;
	enum	EXT_DATA_FIELD		ext_data;
} FB2HDMI_INFO;

enum AUDIO_USER_SETTING{
	AUD_USR_BITSTREAM_OUT       = 0,  
	AUD_USR_LPCM_OUT            = 1,     
	AUD_USR_AUTO                = 2, // By EDID
};

enum AUDIO_CODING_TYPE{
	AUD_CODING_PCM 				= 0x01,
	AUD_CODING_AC3 				= 0x02,
	AUD_CODING_MPEG1_L12 		= 0x03,
	AUD_CODING_MPEG1_L3 		= 0x04,
	AUD_CODING_MEPG2	  		= 0x05,
	AUD_CODING_AAC				= 0x06,
	AUD_CODING_DTS				= 0x07,
	AUD_CODING_ATRAC			= 0x08,
	AUD_CODING_ONEBITAUDIO		= 0x09,
	AUD_CODING_DD_PLUS			= 0x0A,
	AUD_CODING_DTS_HD			= 0x0B,
	AUD_CODING_MAT_MLP			= 0x0C,
	AUD_CODING_DST				= 0x0D,	
	AUD_CODING_WMAPRO			= 0x0E,
};

enum AUDIO_SAMPLE_RATE{
    AUD_SAMPLERATE_32KHZ        = 0,  
	AUD_SAMPLERATE_44_1KHZ      = 1, 
	AUD_SAMPLERATE_48KHZ        = 2,	
	AUD_SAMPLERATE_88_2KHZ      = 3,
	AUD_SAMPLERATE_96KHZ        = 4,	
    AUD_SAMPLERATE_176_4KHZ     = 5,  
	AUD_SAMPLERATE_192KHZ       = 6,
	AUD_SAMPLERATE_768KHZ       = 7,
	AUD_SAMPLERATE_UNKNOWN      = 8,	
};

enum I2S_FMT_TYPE{
	I2S_FMT_LEFT_JUSTIFIED      = 0,  
	I2S_FMT_RIGHT_JUSTIFIED     = 1,     
	I2S_FMT_I2S	                = 2,
};

enum I2S_FMT_WORD_LENGTH{
	I2S_FMT_WLENGTH_24          = 0,  
	I2S_FMT_WLENGTH_16          = 1,     
	I2S_FMT_WLENGTH_28          = 2, // One-bit audio
};

//****************** HDMI deep color definition ***********************
enum HDMI_API_DEEPCOLOR
{	
	HDMI_DEEPCOLOR_24 = 0,	
	HDMI_DEEPCOLOR_30,	
	HDMI_DEEPCOLOR_36,	
	HDMI_DEEPCOLOR_48,
};

//****************** HDMI color space definition ***********************
enum HDMI_API_COLOR_SPACE
{
	HDMI_RGB = 0,
	HDMI_YCBCR_422,
	HDMI_YCBCR_444,
};



typedef union
{    
    struct
    {
        unsigned int    profession_flag     :1;      // [0]		Professional flag
        unsigned int    audio_content_flag  :1;      // [1]		Audio content flag
        unsigned int    copyright           :1;      // [2]		Copyright
        unsigned int    emphasis            :3;      // [5:3]	Emphasis
        unsigned int    mode                :2;      // [7:6]	Mode
        unsigned int    l_and_category      :8;      // [15:8]	L & Category
        unsigned int    source_number       :4;      // [19:16]	Source Numberg
        unsigned int    channel_number      :4;      // [23:20]	Channel Number
        unsigned int    sample_rate         :4;      // [27:24]	Sample rate
        unsigned int    clock_accuracy      :2;      // [29:28]	Clock Accuracy        
        unsigned int    reserved            :2;      // [31:30]	Reserved      	   
    };
    unsigned int data_uint32;
    unsigned char databyte[4];

} I2S_CHANNEL_STATUS;
    
typedef struct
{    
    enum AUDIO_USER_SETTING     user_audio_out;		// User Setting 2: Auto (By EDID) 1: PCM 0: BIT STREAM
	enum AUDIO_CODING_TYPE      coding_type;        // SPO buffer bit stream coding type
	unsigned int                channel_count;		// 2, 6(5.1), 8(down-mixed + 5.1 channel)	    
    enum AUDIO_SAMPLE_RATE      sample_rate;		// 48000, 44100, 32000 ...
    
	enum I2S_FMT_TYPE           i2s_format;	        // I2S, Left Justify and Right Justify			
	BOOL                        lrck_hi_left;		// true: lrck high send left channel, false: otherwise
	enum I2S_FMT_WORD_LENGTH    word_length;		// 16bits, 24bits, or 28bits(one-bit audio)
    I2S_CHANNEL_STATUS          channel_status;	
} ALSA2HDMI_INFO;

enum HDMI_API_RES
{
	HDMI_RES_INVALID = 0,
	HDMI_RES_480I,
	HDMI_RES_480P,
	HDMI_RES_576I,
	HDMI_RES_576P,
	HDMI_RES_720P_50,
	HDMI_RES_720P_60,
	HDMI_RES_1080I_25,
	HDMI_RES_1080I_30,	
	HDMI_RES_1080P_24,
	HDMI_RES_1080P_25,
	HDMI_RES_1080P_30,
	HDMI_RES_1080P_50,
	HDMI_RES_1080P_60,	
	HDMI_RES_4096X2160_24,
	HDMI_RES_3840X2160_24,
	HDMI_RES_3840X2160_25,
	HDMI_RES_3840X2160_30,	
};

enum EDID_AUD_FMT_CODE
{
	EDID_AUDIO_LPCM 				= 0x0001,
	EDID_AUDIO_AC3					= 0x0002,
	EDID_AUDIO_MPEG1				= 0x0004,
	EDID_AUDIO_MP3					= 0x0008,
	EDID_AUDIO_MPEG2				= 0x0010,
	EDID_AUDIO_AAC					= 0x0020,
	EDID_AUDIO_DTS					= 0x0040,
	EDID_AUDIO_ATRAC				= 0x0080,
	EDID_AUDIO_ONEBITAUDIO			= 0x0100,
	EDID_AUDIO_DD_PLUS				= 0x0200,
	EDID_AUDIO_DTS_HD				= 0x0400,
	EDID_AUDIO_MAT_MLP				= 0x0800,
	EDID_AUDIO_DST					= 0x1000,
	EDID_AUDIO_WMAPRO				= 0x2000,
};


enum HDMI_AV_CHG_STE
{
	HDMI_CB_NOTHING 	 = 0x00,
	HDMI_CB_CLK_RDY2CHG  = 0x01,
	HDMI_CB_AV_INFO_CHG  = 0x02,
	HDMI_CB_CLK_CHG_DONE = 0x04,
	HDMI_CB_CLR_RDY2CHG  = 0x08,
};



typedef struct snd2Hdmi_audio_infor
{
	/* INFO by user setting */
	unsigned int user_def_ch_num;				/* 2 or 8								*/
	unsigned int pcm_out;						/* 2:AUTO  1: PCM 0: BIT STREAM 		*/

	/* AUDIO stream status */
	enum AUDIO_CODING_TYPE coding_type;
	unsigned int max_bit_rate;				/* maximum bit rate 					*/
	unsigned int ch_count;					/* 2, 6(5.1), 8							*/
	unsigned int sample_rate;					/* 48000, 44100, 32000 etc				*/
	unsigned int level_shift;					/* level shift after down-mixing		*/

	/* S/PDIF config dynamic setting */
	unsigned int spdif_edge_clk;				/*0: rising edge latch data, 1: falling edge latch data	*/

	/* I2S config dynamic setting */
	unsigned int ch_status;					/*	31:30	Reserved
											29:28	Clock Accuracy
											27:24	Sample rate
											23:20	Channel Number
											19:16	Source Number
											15:8	L & Category
											7:6		Channel Status Mode
											5:3		Emphasis;
											2		Copyright Information; 0: has copyright; 1: no copyright
											1		Audio content flag; 0:audio PCM; 1: not audio PCM 
											0		Professional flag;  0: consumer mode; 1: professional mode */
	unsigned char   ch_position[8];				/* ch_position[i] 
										bit0~bit3: speaker(CH_FL, CH_FC etc)
										bit4~bit6: channel position(0~7, the position in I2S dma buffer)
										bit7: speaker enable(1:enable, 0:disable)				*/
											  
	/* I2S config fixed setting */
	unsigned int bclk_lrck;					/* 32, 64												*/
	unsigned int word_length;					/* 16bits, 24bits										*/
	unsigned int i2s_edge_clk;				/* 0:rising edge latch data, 1:falling edge latch data	*/
	enum I2S_FMT_TYPE i2s_format;		/* I2S, Left Justify and Right Justify					*/
	unsigned int lrck_hi_left;				/* 1: lrck high for left channel, 0: reverse			*/
	enum HDMI_AV_CHG_STE	av_chg_ste;
}SND2HDMI_AUDINF;


typedef struct de2Hdmi_video_infor
{
	enum TVSystem			    tv_mode;
	UINT16					    width;
	UINT16					    height;
	enum PicFmt				    format;
	BOOL					    scan_mode;
	BOOL					    afd_present;
	enum TVMode			        output_aspect_ratio;
	UINT8					    active_format_aspect_ratio;
	enum HDMI_AV_CHG_STE	    av_chg_ste;
	enum 	EXT_VIDEO_FORMAT	ext_video_format;	//add for 3d function
	enum	_3D_STRUCTURE		_4K_VIC_3D_structure;
	enum	EXT_DATA_FIELD		ext_data;
}DE2HDMI_VIDINF;



#endif

