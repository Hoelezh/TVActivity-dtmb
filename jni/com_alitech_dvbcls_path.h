#ifndef _COM_ALITECH_DVDCLS_PATH_
#define _COM_ALITECH_DVDCLS_PATH_

#define Class_DvbChannelPath    "com/alitech/dvb/DvbChannel"
#define Class_DvbChannelNodePath    "com/alitech/dvb/DvbChannelNode"
#define Class_DvbSatellitePath    "com/alitech/dvb/DVBSatellite"  
#define Class_DvbSatelliteNodePath    "com/alitech/dvb/DVBSatelliteNode"
#define Class_DvbTpNodePath    "com/alitech/dvb/DvbTpNode"
#define Class_DvbFrontendPath   "com/alitech/dvb/DvbChannelNode$DvbFrontend"
#define Class_DvbPcrPath    "com/alitech/dvb/DvbChannelNode$DvbPcr"
#define Class_DvbVideoPath  "com/alitech/dvb/DvbChannelNode$DvbVideo"
#define Class_DvbAudioPath  "com/alitech/dvb/DvbChannelNode$DvbAudio"
#define Class_DvbAudioTrackPath "com/alitech/dvb/DvbChannelNode$DvbAudio$DvbAudioTrack"
#define Class_DvbBouquetPath  "com/alitech/dvb/DvbChannelNode$DvbBouquet"
#define Class_DvbSearchParam  "com/alitech/dvb/DvbSearchParam"
#define Class_DvbSearchPath "com/alitech/dvb/DvbSearch"
#define Class_DvbDvbPlayerPath "com/alitech/dvb/DvbPlayer"
#define Class_DvbDvbSystemPath "com/alitech/dvb/DvbSystem"
#define Class_DvbEpgDetailPath "com/nmp/dvbplayer/tv/data/EpgItem"
#define Class_DvbDvbEpgEventPath "com/alitech/dvb/DvbEpgEvent"
#define Class_DvbDvbTimePath "com/alitech/dvb/DvbTime"
#define Class_DvbDvbEpgPath		"com/alitech/dvb/DvbEpg"
#define Class_DvbSystemSettingPath		"com/alitech/dvb/DvbSyetemSetting"
#define Class_DvbUdrmPath "com/alitech/dvb/DvbUdrm"
#define Class_DvbPropertyPath "com/alitech/dvb/DvbProperty"


#define Class_Sig_DvbFrontend "Lcom/alitech/dvb/DvbChannelNode$DvbFrontend;"
#define Class_Sig_DvbPcr  "Lcom/alitech/dvb/DvbChannelNode$DvbPcr;"
#define Class_Sig_DvbVideo  "Lcom/alitech/dvb/DvbChannelNode$DvbVideo;"
#define Class_Sig_DvbAudio  "Lcom/alitech/dvb/DvbChannelNode$DvbAudio;"
#define Class_Sig_DvbBouquet  "Lcom/alitech/dvb/DvbChannelNode$DvbBouquet;"
#define Class_Sig_DvbAudioTrack  "[Lcom/alitech/dvb/DvbChannelNode$DvbAudio$DvbAudioTrack;"

#define Class_Sig_Con_DvbChannelNode  "(ILjava/lang/String;Ljava/lang/String;" \
			"Lcom/alitech/dvb/DvbChannelNode$DvbFrontend;Lcom/alitech/dvb/DvbChannelNode$DvbPcr;" \
			"Lcom/alitech/dvb/DvbChannelNode$DvbVideo;Lcom/alitech/dvb/DvbChannelNode$DvbAudio;" \
			"Lcom/alitech/dvb/DvbChannelNode$DvbBouquet;IIIZZZ)V"
#define Class_Sig_Con_DvbAudio  "(SSS[Lcom/alitech/dvb/DvbChannelNode$DvbAudio$DvbAudioTrack;)V"

#define Class_Sig_Con_DvbSatelliteNode  "(ILjava/lang/String;Ljava/lang/String;IZZZIIIIIIIIII)V"
#define Native_Sig_DvbSatellite_loadSatelliteNodes "()[Lcom/alitech/dvb/DVBSatelliteNode;"
#define Native_Sig_DvbSatellite_updateSatellite "(Lcom/alitech/dvb/DVBSatelliteNode;)I"
#define Native_Sig_DvbSatellite_deleteSatellite "(I)Z"

#define Class_Sig_Con_DvbTpNode  "(ILjava/lang/String;Ljava/lang/String;IIII)V"
#define Native_Sig_DvbSatellite_loadTpNodes "(I)[Lcom/alitech/dvb/DvbTpNode;"
#define Native_Sig_DvbSatellite_updateTpNode "(Lcom/alitech/dvb/DvbTpNode;)I"
#define Native_Sig_DvbSatellite_deleteTpNode "(II)Z"


#define Native_Sig_DvbChannel_loadChannels "(I)[Lcom/alitech/dvb/DvbChannelNode;"
#define Native_Sig_DvbChannel_updateChannel "(Lcom/alitech/dvb/DvbChannelNode;)I"
#define Native_Sig_DvbSearch_start "(Lcom/alitech/dvb/DvbSearchParam;)I"

#define Native_Sig_DvbPlayer_Start  "(Lcom/alitech/dvb/DvbChannelNode;Z)I"

#define Native_Sig_DvbEpg_setActiveService			"([Lcom/alitech/dvb/DvbChannelNode;)I"
#define Native_Sig_DvbEpg_delService					"(Lcom/alitech/dvb/DvbChannelNode;)I"
#define Native_Sig_DvbEpg_getPresentEvent			"(Lcom/alitech/dvb/DvbChannelNode;Z)Lcom/alitech/dvb/DvbEpgEvent;"
#define Native_Sig_DvbEpg_getFollowingEvent		"(Lcom/alitech/dvb/DvbChannelNode;Z)Lcom/alitech/dvb/DvbEpgEvent;"
#define Native_Sig_DvbEpg_loadScheduleEvent		"(Lcom/alitech/dvb/DvbChannelNode;Lcom/alitech/dvb/DvbTime;Lcom/alitech/dvb/DvbTime;Z)I"	
#define Native_Sig_DvbEpg_getScheduleEvent		"(I)Lcom/alitech/dvb/DvbEpgEvent;"


#endif
