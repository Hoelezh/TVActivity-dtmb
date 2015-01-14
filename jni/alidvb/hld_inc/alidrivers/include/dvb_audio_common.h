#ifndef _DVB_AUDIO_COMMON_H_
#define _DVB_AUDIO_COMMON_H_

#include "ali_basic_common.h"
#include "ali_audio_common.h"

#define AUDIO_SET_VOLUME		         _IOW('o', 21, unsigned char)
#define AUDIO_GET_INPUT_CALLBACK_ROUTINE _IOR('o', 22, struct ali_dec_input_callback_routine_pars)
#define AUDIO_DECA_IO_COMMAND            _IOWR('o', 23, struct ali_audio_ioctl_command)
#define AUDIO_SND_IO_COMMAND             _IOWR('o', 24, struct ali_audio_ioctl_command)
#define AUDIO_DECORE_COMMAND             _IOWR('o', 25, struct ali_audio_rpc_pars)
#define AUDIO_GET_VOLUME		         _IOR('o', 26, unsigned char)

#define AUDIO_ASE_INIT                       _IO('o', 27)
#define AUDIO_ASE_STR_STOP                   _IO('o', 28)
#define AUDIO_ASE_DECA_BEEP_INTERVAL         _IOW('o', 29,unsigned int)
#define AUDIO_ASE_STR_PLAY                   _IOW('o', 30,struct ase_str_play_param)

#define AUDIO_GEN_TONE_VOICE _IOW('o', 31, unsigned long)
#define AUDIO_STOP_TONE_VOICE _IO('o', 32)
#define AUDIO_SND_ENABLE_EQ _IOW('o',33,struct ali_audio_rpc_pars)


#define  AUDIO_EMPTY_BS_SET _IO('o', 34)
#define  AUDIO_ADD_BS_SET _IO('o', 35)
#define  AUDIO_DEL_BS_SET _IO('o', 36)
#define AUDIO_SND_START _IO('o', 37)
#define AUDIO_SND_STOP _IO('o', 38)
#define AUDIO_SND_STC_INVALID     _IO('o', 39)
#define AUDIO_SND_STC_VALID       _IO('o', 40)
#define AUDIO_RPC_CALL_ADV       _IO('o', 41)
#define AUDIO_SND_GET_STC        _IO('o', 42)
#define AUDIO_SND_SET_STC        _IO('o', 43)
#define AUDIO_SND_PAUSE_STC      _IO('o', 44)
#define AUDIO_SND_SET_SUB_BLK    _IO('o', 45)
#define AUDIO_DECA_IO_COMMAND_ADV    _IOWR('o', 46, struct ali_audio_rpc_pars)
#define AUDIO_SND_IO_COMMAND_ADV     _IOWR('o', 47, struct ali_audio_rpc_pars)
#define AUDIO_DECA_PROCESS_PCM_SAMPLES _IO('o', 48)
#define AUDIO_DECA_PROCESS_PCM_BITSTREAM _IO('o', 49)
#define AUDIO_DECA_SET_DBG_LEVEL              _IO('o', 50)
#define AUDIO_SND_SET_DBG_LEVEL              _IO('o', 51)

#define AUDIO_SET_CTRL_BLK_INFO _IOW('o',52,ali_audio_ctrl_blk)

struct ali_audio_ioctl_command
{
	unsigned long ioctl_cmd;
	unsigned long param;
};

#endif
