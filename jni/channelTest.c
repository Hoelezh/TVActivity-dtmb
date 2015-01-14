#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#include "channelNode.h"

#define  LOG_TAG    "libdvbchannel"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

void print_channelnode(struct DvbChannelNode *node) {
	int i;

	LOGD("dumping channel node info\n\n");

	LOGD("\tsat_id:		0x%x\n",node->sat_id);
	LOGD("\ttp_id:		0x%x\n",node->tp_id);
	LOGD("\tprog_id:		0x%x\n",node->prog_id);
	LOGD("\tservice_id:		0x%x\n",node->service_id);
	LOGD("\tservice_type:		0x%x\n",node->service_type);
	LOGD("\tservice_name:		%s\n",node->service_name);
	LOGD("\tfavorite:		0x%x\n",node->favorite);
	LOGD("\tscramble:		0x%x\n",node->scramble);
	LOGD("\tlock:		0x%x\n",node->lock);
	LOGD("\tfrontend.ft_type:		0x%x\n",node->frontend.ft_type);
	LOGD("\tfrontend.qam:		0x%x\n",node->frontend.qam);
	LOGD("\tfrontend.frq:		0x%x\n",node->frontend.frq);
	LOGD("\tfrontend.sym:		0x%x\n",node->frontend.sym);
	LOGD("\tpcr.pcr_pid:		0x%x\n",node->pcr.pcr_pid);
	LOGD("\tvideo.video_type:		0x%x\n",node->video.video_type);
	LOGD("\tvideo.video_pid:		0x%x\n",node->video.video_pid);
	LOGD("\taudio.audio_channel:		0x%x\n",node->audio.audio_channel);
	LOGD("\taudio.audio_volume:		0x%x\n",node->audio.audio_volume);
	LOGD("\taudio.audio_current:		0x%x\n",node->audio.audio_current);
	LOGD("\taudio.audio_count:		0x%x\n",node->audio.audio_count);
	for (i=0; i<node->audio.audio_count; i++) {
		LOGD("\n");
		LOGD("\t\taudio.audio_pid:		0x%x\n",node->audio.audio_track[i].audio_pid);
		LOGD("\t\taudio.audio_type:		0x%x\n",node->audio.audio_track[i].audio_type);
		LOGD("\t\taudio.audio_lang:		%s\n",node->audio.audio_track[i].audio_lang);

	}
	LOGD("\tbouquet.bouquet_count:		0x%x\n",node->bouquet.bouquet_count);
	for (i=0; i<node->bouquet.bouquet_count; i++) {
		LOGD("\t %d",node->bouquet.bouquet_id[i]);
	}
	LOGD("\n\n");
}


int chan_load_channels(int view_type, int service_type, int param) {
	int count = 3;

	LOGD("channel count:%d", count);

	return count;
}

int chan_get_channel(int index, struct DvbChannelNode *node) {
	int i;

	node->sat_id = 0x0100 + index;;
	node->tp_id = 0x0200 + index;;
	node->prog_id = 0x300 + index;
	node->service_id =0x400 + index;
	node->service_type =0x500 + index;
	sprintf(node->service_name, "prog%d", index);
	node->favorite =0;
	node->scramble =0;
	node->lock =0;

	node->frontend.ft_type = 0x1100+index;
	node->frontend.qam = 0x1100+index;
	node->frontend.frq = 0x1100+index;
	node->frontend.sym = 0x1100+index;

	node->pcr.pcr_pid = 0x2100+index;

	node->video.video_type = 0x3100+index;
	node->video.video_pid = 0x3200+index;

	node->audio.audio_channel = 0x4100+index;
	node->audio.audio_volume = 0x4200+index;
	node->audio.audio_current = 0;
	node->audio.audio_count = index;
	for (i=0; i<node->audio.audio_count; i++) {
		node->audio.audio_track[i].audio_pid = 0x4500+index+i;
		node->audio.audio_track[i].audio_type = 0x4500+index+i;
		sprintf(node->audio.audio_track[i].audio_lang, "L%d", index+i);
	}

	node->bouquet.bouquet_count = index+2;
	for (i=0; i<node->bouquet.bouquet_count; i++) {
		node->bouquet.bouquet_id[i] = i;
	}

	LOGD("chan_get_channel: get node %d\n", index);
	//print_channelnode(node);

	return 0;
}

int chan_update_channel(struct DvbChannelNode *node) {
	LOGD("chan_update_channel: save channel node\n");
	print_channelnode(node);
	return 0;
}
