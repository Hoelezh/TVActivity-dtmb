#ifndef __ALI_DVB_PLAYER_H__
#define __ALI_DVB_PLAYER_H__

#include "alidvb_channelnode.h"

int ALiDVB_PlayerStart(ALiDVB_ChannelNode *node, BOOL black_screen);
int ALiDVB_PlayerStop(int black_screen);
int ALiDVB_PlayerPauseVideo(void);
int ALiDVB_PlayerResumeVideo(void);
int ALiDVB_PlayerSwitchAudioTrack(int index);
int ALiDVB_PlayerSwitchAudioChannel(int channel);
int ALiDVB_PlayerSetVol(int vol);
int  ALiDVB_PlayerGetVol(void);
int ALiDVB_PlayerVolGetMute(void);
int ALiDVB_PlayerVolMute(int mute);


#endif /* __ALI_DVB_PLAYER_H__ */

