#ifndef __ALI_DVB_PLAYER_H__
#define __ALI_DVB_PLAYER_H__

#include "alidvb_channelnode.h"

int ALiDVB_PlayerStart(ALiDVB_ChannelNode *node, BOOL black_screen);
int ALiDVB_PlayerStop(int black_screen);
int ALiDVB_PlayerPauseVideo(void);
int ALiDVB_PlayerResumeVideo(void);
int ALiDVB_PlayerSwitchAudioTrack(int index);
int ALiDVB_PlayerSwitchAudioChannel(int channel);
int ALiDVB_CreateGroup(int view_type, int service_type, int param) ;
int ALiDVB_GetChannel(int pos, ALiDVB_ChannelNode *node);
int ALiDVB_PlayerSetVol(int vol);
int  ALiDVB_PlayerGetVol(void);

#endif /* __ALI_DVB_PLAYER_H__ */

