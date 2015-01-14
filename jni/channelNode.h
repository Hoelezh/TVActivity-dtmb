#ifndef _Included_channelNode
#define _Included_channelNode

#define MAX_SERVICE_NAME_LENGTH		17

/*max audio pid cnt for earch prog node*/
#define MAX_AUDIO_CNT	8
/*max bouquet id cnt for earch prog node*/
#define MAX_BOUQUET_CNT 8

struct DvbFrontend {
	int ft_type; // FRONTEND_TYPE_S，FRONTEND_TYPE_C，FRONTEND_TYPE_T
	int qam;
	int frq;
	int sym;
};

struct DvbPcr {
	short pcr_pid;
};

struct DvbVideo {
	short video_type; // MPEG2_VIDEO_STREAM,H264_VIDEO_STREAM,AVS_VIDEO_STREAM...
	short video_pid;
};

struct DvbAudioTrack {
	short audio_pid;
	short audio_type;	// AUDIO_AC3, AUDIO_MPEG_AAC, AUDIO_MPEG2...
	char audio_lang[4];
};

struct DvbAudio {
	short audio_channel; // LEFT, RIGHT, STEREO, MONO
	short audio_volume;
	short audio_current;
	short audio_count;
	struct DvbAudioTrack audio_track[MAX_AUDIO_CNT];
};

struct DvbBouquet {
	short bouquet_count;
	short bouquet_id[MAX_BOUQUET_CNT]; // 分组的bouquet id
};

struct DvbChannelNode {

	struct DvbFrontend frontend;
	struct DvbPcr pcr;
	struct DvbVideo video;
	struct DvbAudio audio;
	struct DvbBouquet bouquet;

	int sat_id;
	int tp_id;
	int prog_id;

	int service_id;
	int service_type; // RADIO/TV/RADIOTV/DATA/NVOD…

	short service_name[MAX_SERVICE_NAME_LENGTH+1];

	int favorite;
	int scramble; // scramble channel
	int lock; // parent lock
};

int chan_load_channels(int view_type, int service_type, int param);
int chan_get_channel(int index, struct DvbChannelNode *node);
int chan_update_channel(struct DvbChannelNode *node);

#endif // _Included_channelNode
