#include <adr_sys_config.h>

#include <errno.h>  
#include <fcntl.h>  
#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/stat.h>  
#include <sys/wait.h>  
#include <fcntl.h>

#include <assert.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#include <adr_basic_types.h>

#include <hld/adr_hld_dev.h>
#include <hld/deca/adr_deca_dev.h>
#include <hld/deca/adr_deca.h>
#include <hld/snd/adr_snd_dev.h>
#include <hld/snd/adr_snd.h>
#include <hld/vbi/adr_vbi.h>
#include <hld/sdec/adr_sdec.h>
#include <hld/dis/adr_vpo.h>
#include <hld/decv/adr_vdec_driver.h>
#include <hld/decv/adr_decv_avc.h>
#include <hld/osd/adr_osddrv.h>
#include <hld/avsync/adr_avsync.h>
#include <hld/nim/adr_nim.h>
#include <hld/nim/adr_nim_tuner.h>
#include <hld/dmx/adr_dmx.h>
#include <hld/dmx/Ali_DmxLib.h>
#include <hld/dis/adr_vpo.h>

#include <api/libc/log.h>
#include <api/libpub/lib_pub.h>
#include <api/libpub/lib_frontend.h>
#include <api/libsi/si_parser.h>
#include <api/libsi/si_service_type.h>
#include <api/libsi/si_monitor.h>
#include <api/libsi/lib_epg.h>
#include <api/libsi/si_tdt.h>
#include <api/libpub/lib_hde.h>

#include <android/log.h>

#include "alidvb_player.h"

#include "alidvb_test.h"

#define LOG_TAG    "ALiDVB_Player"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define PLAYER_DEBUG	LOGD
#define PLAYER_NOTICE	LOGI
#define PLAYER_ERROR	LOGE

static ALiDVB_ChannelNode current_node;
static int player_state = 0;
static struct cc_logo_info logoInfo;

/* Map audio stream type to audio type */
static enum AudioStreamType get_audio_type(UINT16 type)
{
	switch (type)
	{
		case AC3_AUDIO_STREAM:
		case PRIVATE_AC3_AUDIO:
			return AUDIO_AC3;
			break;
		case MPEG_AAC_STREAM:
			return AUDIO_MPEG_AAC;
			break;
		case MPEG_ADTS_AAC_STREAM:
			return AUDIO_MPEG_ADTS_AAC;
			break;
		case PRIVATE_EAC3_AUDIO:
			return AUDIO_EC3;
			break;
		default:
			return AUDIO_MPEG2;
			break;
	}
}

/* cc set xpond parameters */
static void channel_change_set_xpond_param(ALiDVB_ChannelNode *node, struct ft_frontend *ft)
{
	T_NODE t_node;
	S_NODE s_node;

	ft->nim = dev_get_by_id(HLD_DEV_TYPE_NIM, 0);
	
	
	if(node->frontend.type == FRONTEND_TYPE_S )
	{
		ft->xpond.s_info.type = node->frontend.type;//FRONTEND_TYPE_C;
		ft->xpond.s_info.tp_id = node->tp_id;
		ft->xpond.s_info.frq = node->frontend.frequency;
		ft->xpond.s_info.sym = node->frontend.symbol_rate;
		ft->xpond.s_info.modulation = node->frontend.modulation;
		if(SUCCESS!=amsdb_get_node_byid(TYPE_TP_NODE, node->tp_id, (UINT8 *)(&t_node), sizeof(T_NODE)) )
		{
			LOGE("channel_change_set_xpond_param::amsdb_get_node_byid fail\n");
			return;
		}
		if(SUCCESS!=amsdb_get_node_byid(TYPE_SAT_NODE, t_node.sat_id, (UINT8 *)(&s_node), sizeof(S_NODE)) )
		{
			LOGE("channel_change_set_xpond_param::amsdb_get_node_byid fail\n");
			return;
		}
		ft->xpond.s_info.pol = t_node.pol;
		ft->xpond.s_info.fec_inner = t_node.FEC_inner;
		sat2antenna(&s_node, &ft->antenna);
	}
	else
	{
		ft->xpond.c_info.type = node->frontend.type;//FRONTEND_TYPE_C;
		ft->xpond.c_info.tp_id = node->tp_id;
		ft->xpond.c_info.frq = node->frontend.frequency;
		ft->xpond.c_info.sym = node->frontend.symbol_rate;
		ft->xpond.c_info.modulation = node->frontend.modulation;
	}
	LOGD("%s,%d,type %d,tp id %d,frq %d,sym %d,qam %d",__FUNCTION__,__LINE__,node->frontend.type,\
		node->tp_id, node->frontend.frequency, node->frontend.symbol_rate, node->frontend.modulation);
}

/* cc set cc parameters */
static void channel_change_set_cc_param(ALiDVB_ChannelNode *node, struct cc_param *param)
{
    memset(param, 0, sizeof(struct cc_param));

	param->dev_list.vpo = dev_get_by_id(HLD_DEV_TYPE_DIS, 0);
	param->dev_list.vdec = dev_get_by_id(HLD_DEV_TYPE_DECV, 0);
	param->dev_list.vdec_hdtv = dev_get_by_name("DECV_AVC_0");
	if (node->video_type == H264_VIDEO_STREAM)
		param->dev_list.vdec = param->dev_list.vdec_hdtv;
	param->dev_list.vdec_stop = get_selected_decoder();
	param->dev_list.deca = dev_get_by_id(HLD_DEV_TYPE_DECA, 0);
	param->dev_list.snd_dev = dev_get_by_id(HLD_DEV_TYPE_SND, 0);
	param->dev_list.dmx = dev_get_by_id(HLD_DEV_TYPE_DMX, 0);

	param->es.prog_id = node->prog_id;
	param->es.sat_id = node->sat_id;
	param->es.tp_id = node->tp_id;
	param->es.service_id = node->service_id;
	param->es.service_type = node->service_type;
	param->es.pcr_pid = node->pcr_pid;
	param->es.v_type = node->video_type;

	if(node->service_type == SERVICE_TYPE_DTV \
      || node->service_type == SERVICE_TYPE_HD_MPEG2 \
      || node->service_type == SERVICE_TYPE_SD_MPEG4 \
      || node->service_type == SERVICE_TYPE_HD_MPEG4 \
      || node->service_type == SERVICE_TYPE_NVOD_TS \
      || node->service_type == SERVICE_TYPE_NVOD_TS_SD_MPEG4 \
      || node->service_type == SERVICE_TYPE_NVOD_TS_HD_MPEG4)
	{
		param->es.v_pid = node->video_pid;
	}
	else
	{
		param->es.v_pid = INVALID_PID;
	}

#if 0
	// This for default language is not the first langusge. BUG17206 
	if (!node->audio_select)
	{
		UINT16 audioPID = 0;
		UINT32 audioIdx = 0;
		get_channel_pids(&p_node,&audioPID,&audioIdx,0,0);

		if(p_node->cur_audio != audioIdx)
		{
			p_node->cur_audio = audioIdx;
			amsdb_modify_node(TYPE_PROG_NODE, p_node->prog_id, (UINT8 *)p_node, sizeof(P_NODE));
		}
	}
#endif

	param->es.a_pid = (node->audio_count) ? node->audio_track[node->audio_current].audio_pid : INVALID_PID;		
	param->es.audio_no_act = 0;
	param->es.a_ch = node->audio_channel;
	param->es.a_volumn = node->audio_volume;
	param->es.a_type = get_audio_type(node->audio_track[node->audio_current].audio_type);	
	param->es.spdif_enable = 0;
#if(AC3DEC == 0)
	param->es.spdif_enable = 1;
#endif
	param->es.dmx_2play = 0;//dmx_2play;
}

/* cc set stop cc parameters */
static void channel_change_set_stop_cc_param(ALiDVB_ChannelNode *node, struct cc_param *param)
{
    memset(param, 0, sizeof(struct cc_param));

    /* stop video */
    param->es.v_pid = (node->service_type == SERVICE_TYPE_DTV || node->service_type == SERVICE_TYPE_NVOD_TS) ? node->video_pid : INVALID_PID;
    param->dev_list.vdec_stop = get_selected_decoder();

    /* stop audio */
//    param->es.a_pid = (p_node->audio_count) ? p_node->audio_pid[p_node->cur_audio] : INVALID_PID;		
//    param->dev_list.deca = dev_get_by_id(HLD_DEV_TYPE_DECA, 0);

    /* stop dmx */
//    param->dev_list.dmx = dev_get_by_id(HLD_DEV_TYPE_DMX, 0);	
}

/* Preprare information for play channel and stop play channel */
static BOOL channel_change_prepare_info(ALiDVB_ChannelNode *node, struct ft_frontend *ft, struct cc_param *param)
{
	if (node == NULL || ft == NULL || param == NULL)
	{
		PLAYER_ERROR("bad parameters!\n");
		return FALSE;
	}

	/* Fill xpond parameters */
	memset(ft, 0, sizeof(struct ft_frontend));
	channel_change_set_xpond_param(node, ft);

	/* Fill es parameters */
	memset(param, 0, sizeof(struct cc_param));
	channel_change_set_cc_param(node, param);

	return TRUE;
}

int ALiDVB_PlayerStart(ALiDVB_ChannelNode *node, int black_screen)
{
	int ret = 0;
    struct ft_frontend fe;
    struct cc_param ccp;
PLAYER_ERROR("ALiDVB_PlayerStart::0\n");
    if (TRUE != channel_change_prepare_info(node, &fe, &ccp))
    {
        PLAYER_ERROR("channel_change_prepare_info failed!\n");
		return -1;
    }
PLAYER_ERROR("ALiDVB_PlayerStart::1\n");
    if (SUCCESS != chchg_play_channel(&fe, &ccp, black_screen))
    {
        PLAYER_ERROR("chchg_play_channel failed!\n");
		return -1;
    }
PLAYER_ERROR("ALiDVB_PlayerStart::2\n");
	memcpy(&current_node, node, sizeof(ALiDVB_ChannelNode));

	player_state = 1;

	return ret;
}

int ALiDVB_PlayerStop(int black_screen)
{
	int ret = 0;
    struct cc_param ccp;

	if (player_state == 0)
		return 0;

    channel_change_set_cc_param(&current_node, &ccp);

    if (SUCCESS != chchg_stop_channel(&ccp.es, &ccp.dev_list, black_screen))
    {
    	PLAYER_ERROR("chchg_stop_channel failed!\n");
    	ret = -1;
    }

	player_state = 0;

    return ret;
}

int ALiDVB_PlayerPauseVideo(void)
{

}

int ALiDVB_PlayerResumeVideo(void)
{

}

int ALiDVB_PlayerSwitchAudioTrack(int index)
{

}

int ALiDVB_PlayerSwitchAudioChannel(int channel)
{

}

//for logo show
static int LoadLogo(char *file)
{
	int fd;
	int size;
	UINT8 * logoBuf=0;

	fd = open(file, O_RDONLY);
        if (fd < 0)
        {
            printf("open logo file:%s fail\n",file);
            return 0;
        }

        size = lseek(fd,0,SEEK_END);

        if (logoBuf)
            FREE(logoBuf);
        
        logoBuf = MALLOC(size);
        if (logoBuf == 0)
        {
            printf("logo_load_data malloc logoBuf fail, size:0x%x",size);
            return 0;
        }        
        lseek(fd,0,SEEK_SET);   
        read(fd, logoBuf, size);
        close(fd);

        MEMSET(&logoInfo, 0, sizeof(logoInfo));
        logoInfo.addr = logoBuf;
        logoInfo.size = size;

	return size;
}

int ALiDVB_ShowLogo(char *file)
{
	struct cc_device_list dev_list;

	if(LoadLogo(file) <= 0)
		return -1;

	dev_list.vdec = dev_get_by_id(HLD_DEV_TYPE_DECV, 0);
	dev_list.deca = dev_get_by_id(HLD_DEV_TYPE_DECA, 0);
	dev_list.snd_dev = dev_get_by_id(HLD_DEV_TYPE_SND, 0);
	dev_list.dmx = dev_get_by_id(HLD_DEV_TYPE_DMX, 0);
	dev_list.vpo = dev_get_by_id(HLD_DEV_TYPE_DIS, 0);
	dev_list.vdec_stop = get_selected_decoder();

	chchg_show_logo(&logoInfo, &dev_list);

	return 0;
}


int range_check(int *val, int min, int max)
{
    if(*val < min)
        *val = min;
    else
    if(*val > max)
        *val = max;

        return 0;
}

int ALiDVB_PlayerSetPos(int left, int top, int right, int bottom)
{
    struct vpo_device *pDisDevice = (struct vpo_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_DIS);
    LOGD("ALiDVB_PlayerSetPos: [%d, %d] - [%d, %d]", left, top, right, bottom);

    //get the current resolution
    int h_mul = 1280, v_mul = 720;

    struct Rect	rectSrcFull = {0,0,720,2880};
    range_check(&left, 0, 1279);
    range_check(&top, 0, 719);
    range_check(&right, 1, 1280);
    range_check(&bottom, 1, 720);
	    
    int x = left;
    int y = top;
    int w = (right - left);
    int h = (bottom - top);
	
    //to check if the in scale mode
    char scale[16];
    property_get("persist.sys.scaleratio", scale, "100");
    int iscale = atoi(scale);
    LOGD("ALiDVB_PlayerSetPos: scale = %d", iscale);

    x = 1280 * (100 - iscale) / 200  + x * iscale / 100;
    y = 720 * (100 - iscale) / 200 + y * iscale / 100;
    w = w * iscale / 100;
    h = h * iscale / 100;

    LOGD("ALiDVB_PlayerSetPos: rect osd [%d, %d] - [%d, %d]", x, y, w, h);

    x = x * 720 / 1280;
    y = y * 2880 / 720;
    w = w * 720 / 1280;
    h = h *  2880 / 720;
    LOGD("ALiDVB_PlayerSetPos: rect video [%d, %d] - [%d, %d]", x, y, w, h);

    struct Rect	rectScrnPreview = {x, y, w, h};

    vpo_zoom(pDisDevice, &rectSrcFull, &rectScrnPreview);

    return 0;
}

int ALiDVB_PlayerSetFullScr(void)
{
	int ret = 0;
	
	return ret;
}

int ALiDVB_PlayerSetVol(int vol)
{
	int ret;

	if(vol < 0)
		vol = 0;
	if(vol > 100)
		vol = 100;

	ret = snd_set_volume(dev_get_by_id(HLD_DEV_TYPE_SND, 0), SND_SUB_OUT, vol);

	return ret;
}

int  ALiDVB_PlayerGetVol(void)
{
	int vol = 0;

	vol = snd_get_volume(dev_get_by_id(HLD_DEV_TYPE_SND, 0));

	return vol;
}

int ALiDVB_PlayerVolGetMute(void)
{
    int ret=0;
    if(0==snd_io_control(dev_get_by_id(HLD_DEV_TYPE_SND, 0), IS_SND_MUTE, 0)){
        ret =1;
    }
    return ret;
}

int ALiDVB_PlayerVolMute(int mute)
{
    int ret=0;
    if(mute)
        mute =1;
    else
        mute =0;
    snd_set_mute(dev_get_by_id(HLD_DEV_TYPE_SND, 0), SND_SUB_OUT, mute);
    return ret;
}

int ALiDVB_CreateGroup(int view_type, int service_type, int param) 
{
	int count;

	if (view_type < VIEW_ALL || view_type > VIEW_FAV_GROUP_ALL)
		view_type = VIEW_ALL;
	if (service_type < PROG_RADIO_MODE || service_type > PROG_MOSAIC_MODE)
		service_type = PROG_TV_MODE;

	//if(DB_SUCCES != amsdb_create_view(TYPE_TP_NODE, VIEW_SINGLE_SAT, 1))
	if(DB_SUCCES != amsdb_create_view(TYPE_SAT_NODE, VIEW_ALL, 0))
	{
		LOGE("%s,%d:create sat view err!", __FUNCTION__, __LINE__);
	}
	if(DB_SUCCES != amsdb_create_view(TYPE_TP_NODE, VIEW_ALL, 0))
	{
		LOGE("%s,%d:create tp view err!", __FUNCTION__, __LINE__);
	}
	if(DB_SUCCES != amsdb_create_view(TYPE_PROG_NODE, view_type | service_type, param))
	{
		LOGE("%s,%d:create program view err!", __FUNCTION__, __LINE__);
	}	

	count = amsdb_get_node_cnt(TYPE_PROG_NODE, view_type | service_type, param);
	
	return count;
}

int ALiDVB_CreateSatView() 
{
	int count;

	//ALiDVB_satellitetest();

	if(DB_SUCCES != amsdb_create_view(TYPE_SAT_NODE, VIEW_ALL, 0))
	{
		LOGE("%s,%d:create view err!", __FUNCTION__, __LINE__);
	}
	count = amsdb_get_node_cnt(TYPE_SAT_NODE, VIEW_ALL, 0);
	LOGE("%s,%d:count = %d \n", __FUNCTION__, __LINE__,count);
	return count;
}

int ALiDVB_CreateTpView(int sat_id) 
{
	int count;

	if(DB_SUCCES != amsdb_create_view(TYPE_TP_NODE, VIEW_SINGLE_SAT, sat_id))
	{
		LOGE("%s,%d:create view err!", __FUNCTION__, __LINE__);
	}

	//count = amsdb_get_node_cnt(TYPE_TP_NODE, VIEW_ALL, 0);
	count = amsdb_get_node_cnt( TYPE_TP_NODE, VIEW_SINGLE_SAT,sat_id );
	return count;
}

int ALiDVB_DeleteNode(int type ,int node_id) 
{
	int count;
	if(type == TYPE_SAT_NODE)
	{
		amsdb_del_child(TYPE_PROG_NODE, TYPE_SAT_NODE,  node_id);
		amsdb_del_child(TYPE_TP_NODE, TYPE_SAT_NODE,  node_id);
	}
	else if(type == TYPE_TP_NODE)
	{
		amsdb_del_child(TYPE_PROG_NODE, TYPE_TP_NODE,  node_id);
	}

	if(DB_SUCCES == amsdb_del_node_byid(type, node_id))
	{
		return amsdb_update_data();
	}

	return !DB_SUCCES;
	
}


int ALiDVB_GetSatNode(int pos, ALiDVB_SatelliteNode *node)
{
	S_NODE s_node;
	if (node == NULL)
	{
		LOGE("get pnode @%d failed!node is null\n", pos);
		return !SUCCESS;
	}

	if (amsdb_get_node_at(TYPE_SAT_NODE, pos, (UINT8 *)(&s_node), sizeof(S_NODE)) != SUCCESS)
	{
		LOGE("get pnode @%d failed!\n", pos);
		return !SUCCESS;
	}

	memset(node, 0, sizeof(ALiDVB_SatelliteNode));

	node->sat_id = s_node.sat_id;
	node->sat_orbit = s_node.sat_orbit;
	node->select = s_node.selected_flag;
	node->tuner1_valid = s_node.tuner1_valid;
	node->tuner2_valid = s_node.tuner2_valid;

	node->lnb_type = s_node.lnb_type;
	node->lnb_low = s_node.lnb_low;
	node->lnb_high = s_node.lnb_high;
	node->DiSEqC_type = s_node.DiSEqC_type;
	node->DiSEqC_port = s_node.DiSEqC_port;
	node->DiSEqC11_type = s_node.DiSEqC11_type;
	node->DiSEqC11_port = s_node.DiSEqC11_port;
	node->lnb_power = s_node.lnb_power;
	node->pol = s_node.pol;
	node->k22 = s_node.k22;

	memcpy(node->sat_name, s_node.sat_name, MAX_SATELLITE_NAME_LENGTH*sizeof( s_node.sat_name[0]));
	return SUCCESS;
}

int ALiDVB_SaveSatNode(ALiDVB_SatelliteNode node)
{
	S_NODE s_node;
	int ret;
	int i = 0;

	memset(&s_node, 0, sizeof(S_NODE));

	s_node.sat_id = node.sat_id;
	s_node.sat_orbit = node.sat_orbit;
	s_node.selected_flag = node.select;
	s_node.tuner1_valid = node.tuner1_valid;
	s_node.tuner2_valid = node.tuner2_valid;

	s_node.DiSEqC_type= node.DiSEqC_type;
	s_node.DiSEqC_port= node.DiSEqC_port;
	s_node.DiSEqC11_type= node.DiSEqC11_type;
	s_node.DiSEqC11_port= node.DiSEqC11_port;
	s_node.lnb_high= node.lnb_high;
	s_node.lnb_low= node.lnb_low;
	s_node.lnb_power= node.lnb_power;
	s_node.lnb_type= node.lnb_type;
	s_node.pol= node.pol;
	s_node.k22= node.k22;

 	s_node.name_len = getUnicodeString(node.sat_name, s_node.sat_name)*2;
	//memcpy(s_node.sat_name, node.sat_name, MAX_SATELLITE_NAME_LENGTH*sizeof( s_node.sat_name[0]));

	//s_node.name_len = 0;
	LOGE("ALiDVB_SaveSatNode (%d ) orbit = %d!l\n", s_node.sat_id, s_node.sat_orbit);
	//while(s_node.sat_name[i] != 0)
	//{
	//	i++;
	//	s_node.name_len++;
	//}

	if(s_node.sat_id > 0)
	{
		ret = amsdb_modify_node(TYPE_SAT_NODE, s_node.sat_id, &s_node, sizeof(S_NODE));
		if(ret != SUCCESS)
		{
			LOGE("ALiDVB_SaveSatNode failed!l\n");
			return -1;
		}
		
	}
	else 
	{
		ret = amsdb_add_node(TYPE_SAT_NODE, 1, &s_node, sizeof(S_NODE));
		if(ret != SUCCESS)
		{
			LOGE("ALiDVB_SaveSatNode add failed!l\n");
			return -1;
		}
	}
	ret = amsdb_update_data();
	if(SUCCESS != ret)
	{
		LOGE("ALiDVB_SaveSatNode failed!l\n");
		return -2;
	}
	return SUCCESS;
}


int ALiDVB_GetTpNode(int pos, ALiDVB_TpNode *node)
{
	T_NODE t_node;
	if (node == NULL)
	{
		LOGE("get pnode @%d failed!node is null\n", pos);
		return !SUCCESS;
	}

	if (amsdb_get_node_at(TYPE_TP_NODE, pos, (UINT8 *)(&t_node), sizeof(T_NODE)) != SUCCESS)
	{
		LOGE("get pnode @%d failed!\n", pos);
		return !SUCCESS;
	}

	memset(node, 0, sizeof(ALiDVB_TpNode));

	node->sat_id = t_node.sat_id;
	node->tp_id= t_node.tp_id;
	node->freq= t_node.frq;
	node->symbol= t_node.sym;
	node->pol= t_node.pol;

	memcpy(node->tp_name, t_node.net_name, MAX_SATELLITE_NAME_LENGTH*sizeof( t_node.net_name[0]));
	return SUCCESS;
}


int ALiDVB_SaveTpNode(ALiDVB_TpNode node)
{
	T_NODE t_node;
	int ret;
	int i = 0;

	memset(&t_node, 0, sizeof(T_NODE));

	t_node.sat_id = node.sat_id;
	t_node.tp_id= node.tp_id;
	t_node.frq= node.freq;
	t_node.sym= node.symbol;
	t_node.pol= node.pol;

	LOGE("ALiDVB_SaveTpNode freq=%d, sym=%d, pol=%d\n", t_node.frq, t_node.sym, t_node.pol);

	if(t_node.tp_id > 0)
	{
		ret = amsdb_modify_node(TYPE_TP_NODE, t_node.tp_id, &t_node, sizeof(T_NODE));
		if(ret != SUCCESS)
		{
			return -1;
		}
	}
	else
	{
		ret = amsdb_add_node(TYPE_TP_NODE, t_node.sat_id, &t_node, sizeof(T_NODE));
		if(ret != SUCCESS)
		{
			return -1;
		}
	}

	ret = amsdb_update_data();
	if(SUCCESS != ret)
	{
		return -2;
	}
	return SUCCESS;
}


void get_audio_lang3b(char *src,char *des)
{
	if(src[0] == 0&&src[1] == 0)
		return;
	des[0] = (src[0] >> 3) + 0x61;
	des[1] = (((src[0] << 2)&0x1C) |(src[1] >> 6)) + 0x61;
	des[2] = ((src[1] >> 1)&0x1F) + 0x61;

}

int ALiDVB_GetChannel(int pos, ALiDVB_ChannelNode *node)
{
	int ret = 0;
	int i;
	P_NODE p_node;
	T_NODE t_node;

	if (node == NULL)
		return !SUCCESS;

	if (amsdb_get_node_at(TYPE_PROG_NODE, pos, (UINT8 *)(&p_node), sizeof(P_NODE)) != SUCCESS)
	{
		LOGE("%s,%d get pnode @%d failed!\n", __FUNCTION__, __LINE__,pos);
		return -1;
	}
	LOGE("%s,%d get pnode: sad=%d,tp=%d,pro=%d,vid=%d,audio=%d,pcr=%d\n", __FUNCTION__, __LINE__,
		p_node.sat_id,p_node.tp_id,p_node.prog_id,p_node.video_pid,p_node.audio_pid[0],p_node.pcr_pid);
	if (amsdb_get_node_byid(TYPE_TP_NODE, p_node.tp_id, (UINT8 *)(&t_node), sizeof(T_NODE)) != SUCCESS)
	{
		LOGE("%s,%d get tnode @%d failed!\n", __FUNCTION__, __LINE__,p_node.tp_id);
		return -1;
	}


	memset(node, 0, sizeof(ALiDVB_ChannelNode));
	node->frontend.type = t_node.ft_type;
	node->frontend.frequency = t_node.frq;
	node->frontend.symbol_rate = t_node.sym;
	node->frontend.modulation = t_node.FEC_inner;	
	node->video_type = p_node.video_type;
	node->video_pid = p_node.video_pid;
	node->audio_channel = p_node.audio_channel;
	node->audio_volume = p_node.audio_volume;
	node->audio_current = 0;
	node->audio_count = p_node.audio_count;

	char lang[4];
	for (i = 0; i < node->audio_count; i++)
	{
		node->audio_track[i].audio_pid = p_node.audio_pid[i];
		node->audio_track[i].audio_type = p_node.audio_type[i];
		memcpy(lang, &p_node.audio_lang[i], 4);
		get_audio_lang3b(lang , node->audio_track[i].audio_lang);
	}
	node->pcr_pid = p_node.pcr_pid;
	node->bouquet_count = p_node.bouquet_cnt;
	for (i = 0; i < node->bouquet_count; i++)
	{
		node->bouquet_id[i] = p_node.bouquet_id[i];
	}
	node->service_id = p_node.prog_number;
	node->service_type = p_node.service_type;
	memcpy(node->service_name, p_node.service_name, MAX_SERVICE_NAME_LENGTH*sizeof(p_node.service_name[0]));

	node->sat_id = p_node.sat_id;
	node->tp_id = p_node.tp_id;
	node->prog_id = p_node.prog_id;

	//LOGD("%s,%d,node prog_id:%d, ret %d", __FUNCTION__, __LINE__, node->prog_id, ret);
	return ret;
}

