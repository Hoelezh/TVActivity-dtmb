#ifndef __ALI_DVB_CHANNEL_NODE_H__
#define __ALI_DVB_CHANNEL_NODE_H__

#define MAX_SERVICE_NAME_LENGTH		17
#define MAX_SATELLITE_NAME_LENGTH		17

/* max audio pid cnt for earch prog node */
#define MAX_AUDIO_CNT	8
/* max bouquet id cnt for earch prog node */
#define MAX_BOUQUET_CNT 8

typedef short bool;

typedef struct
{
	int type; // FRONTEND_TYPE_S, FRONTEND_TYPE_C, FRONTEND_TYPE_T
	int frequency;
	int symbol_rate;
	int modulation;
}ALiDVB_Frontend;

typedef struct
{
	ALiDVB_Frontend frontend;

	short video_type; // MPEG2_VIDEO_STREAM, H264_VIDEO_STREAM, AVS_VIDEO_STREAM...
	short video_pid;

	short audio_channel; // LEFT, RIGHT, STEREO, MONO
	short audio_volume;
	short audio_current;
	short audio_count;
	struct
	{
		short audio_pid;
		short audio_type;	// AUDIO_AC3, AUDIO_MPEG_AAC, AUDIO_MPEG2...
		char audio_lang[4];
	}audio_track[MAX_AUDIO_CNT];

	short pcr_pid;

	short bouquet_count;
	short bouquet_id[MAX_BOUQUET_CNT];

	int sat_id;
	int tp_id;
	int prog_id;

	int service_id;
	int service_type; // RADIO/TV/RADIOTV/DATA/NVOD...

	short service_name[MAX_SERVICE_NAME_LENGTH + 1];

	int favorite;
	int scramble; // scramble channel
	int lock; // parent lock
}ALiDVB_ChannelNode ;


typedef struct 
{
	int sat_id;
	bool select;
	bool tuner1_valid;
	bool tuner2_valid;
	short sat_orbit;
	short sat_name[MAX_SATELLITE_NAME_LENGTH + 1];

	int lnb_type;
	int lnb_low;
	int lnb_high;
	
	int DiSEqC_type;
	int DiSEqC_port;
	
	int DiSEqC11_type;
	int DiSEqC11_port;
	
	int lnb_power;
	int pol;
	int k22;

}ALiDVB_SatelliteNode;

typedef struct 
{
	int sat_id;
	int tp_id;
	int freq;
	int symbol;
	int pol;
	short tp_name[MAX_SATELLITE_NAME_LENGTH + 1];

}ALiDVB_TpNode;

#endif /* __ALI_DVB_CHANNEL_NODE_H__ */

