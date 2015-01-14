#ifndef _Included_player
#define _Included_player

#include "channelNode.h"

int player_start(struct DvbChannelNode *node, int blkScrn);
int player_stop(int blkScrn);

int player_pauseVideo();
int player_resumeVideo();

int player_switchAudioTrack(int audioTrackIdx);
int player_switchAudioChannel(int audioChannel);

#endif // _Included_player
