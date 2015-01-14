#ifndef __ALI_AUDIO_COMMON_H
#define __ALI_AUDIO_COMMON_H

#include  "ali_basic_common.h"

#define RPC_AUDIO_DECORE_IOCTL      1

#define MAX_AUDIO_RPC_ARG_NUM		8
#define MAX_AUDIO_RPC_ARG_SIZE		2048

#define ADEC_PLUGIN_NO_EXIST    4

struct audio_config
{
    int32 decode_mode;
    int32 sync_mode;
    int32 sync_unit;
    int32 deca_input_sbm;
    int32 deca_output_sbm;
    int32 snd_input_sbm;
    int32 pcm_sbm;
    int32 codec_id;
    int32 bits_per_coded_sample;
    int32 sample_rate;
    int32 channels;
    int32 bit_rate;
    uint32 pcm_buf;
    uint32 pcm_buf_size;
    int32 block_align;
    uint8 extra_data[512];
    uint32 codec_frame_size;
    uint32 extradata_size;
    uint8 extradata_mode;
    uint8 cloud_game_prj;
};

struct audio_frame
{
    int64 pts;
    uint32 size;
    uint32 pos;
    uint32 stc_id;
    uint32 delay;
};

struct audio_decore_status
{
    uint32 sample_rate;
    uint32 channels;
    uint32 bits_per_sample;
    int32 first_header_got;
    int32 first_header_parsed;
    uint32 frames_decoded;
};

struct ali_audio_rpc_arg
{
	void *arg;
	int arg_size;
	int out;
};

struct ali_audio_rpc_pars
{
	int API_ID;
	struct ali_audio_rpc_arg arg[MAX_AUDIO_RPC_ARG_NUM];
	int arg_num;
};

typedef struct control_block ali_audio_ctrl_blk;


#endif
