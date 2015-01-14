#include <adr_sys_config.h>
#include <adr_retcode.h>

#include <osal/osal.h>

#include <hld/adr_hld_dev.h>
#include <hld/dmx/adr_dmx_dev.h>
#include <hld/dmx/adr_dmx.h>

#include <hld/nim/adr_nim_dev.h>
#include <hld/nim/adr_nim_tuner.h>
#include <hld/nim/adr_nim.h>

#include <api/libc/string.h>
#include <api/libc/log.h>
#include <api/libchar/lib_char.h>

#include <api/libpub/lib_pub.h>
#include <api/libpub/lib_as.h>
#include <api/libpub/as_engine.h>

#include <api/libtsi/si_types.h>
#include <api/libtsi/si_section.h>

#include <api/libsi/si_search.h>
#include <api/libsi/si_parser.h>
#include <api/libsi/si_module.h>
#include <api/libsi/si_service_type.h>
#include <api/libsi/lib_epg.h>

#include <android/log.h>

#include "../alidvb_search.h"
#include "../alidvb_channelnode.h"

#define LOG_TAG    "ALiDVB_Search"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define SEARCH_DEBUG	LOGD
#define SEARCH_NOTICE	LOGI
#define SEARCH_ERROR	LOGE

#define FUNCTION_ENTER()		 //SEARCH_NOTICE("	ENTER!\n")
#define FUNCTION_LEAVE()		 //SEARCH_NOTICE("	LEAVE!\n")

#define VALID_PID(pid) (pid > 0 && pid < 8191)

#define SEARCH_CALLBACK(a, b)	do {if (search_notify_callback != NULL) search_notify_callback(a, b);} while(0)

static UINT8 *search_workspace = NULL;
static ALiDVB_SearchNotifyFn search_notify_callback = NULL;

static UINT8 search_store_FTA_Oly;
static UINT8 search_store_Pro_Type;
static __inline__ INT32 psi_convert_string(UINT16 *dest, UINT8 *src, INT32 length)
{
	UINT32 refcode=0;
/*TODO*/
#ifdef GB2312_SUPPORT
	refcode = 2312;//GB2312 coding
#endif

#ifdef CHINESE_SUPPORT
	refcode = 0x15; //UTF-8
#endif
	return dvb_to_unicode(src, length, dest, MAX_SERVICE_NAME_LENGTH, refcode);
}

static void DUMP_PNODE(P_NODE *p_node)
{
	UINT32 i;
	SEARCH_DEBUG("dump p node: 0x%X\n", p_node);
	SEARCH_DEBUG("prog id: 0x%X\n", p_node->prog_id);
	SEARCH_DEBUG("prog number: %d\n", p_node->prog_number);
	SEARCH_DEBUG("video_pid: 0x%X\n", p_node->video_pid);
	SEARCH_DEBUG("pcr_pid: 0x%X\n", p_node->pcr_pid);
	SEARCH_DEBUG("ca_mode: 0x%X\n", p_node->ca_mode);
	SEARCH_DEBUG("pmt_pid: 0x%X\n", p_node->pmt_pid);
	SEARCH_DEBUG("video_type: 0x%X\n", p_node->video_type);
	SEARCH_DEBUG("service_type: 0x%X\n", p_node->service_type);

	SEARCH_DEBUG("audio_count: 0x%X\n", p_node->audio_count);
	for (i=0;i<p_node->audio_count;i++)
	{
		SEARCH_DEBUG("(%d) audio_pid: 0x%X\n", i, p_node->audio_pid[i]);
		SEARCH_DEBUG("(%d) audio_lang: 0x%X\n", i, p_node->audio_lang[i]);
		SEARCH_DEBUG("(%d) audio_type: 0x%X\n", i, p_node->audio_type[i]);
	}
	SEARCH_DEBUG("name_len: 0x%X\n", p_node->name_len);
	SEARCH_DEBUG("service_name: 0x");
	for (i=0;i<p_node->name_len/2;i++)
	{
		SEARCH_DEBUG("%04X ", p_node->service_name[i]);
	}
	SEARCH_DEBUG("\n");
}

static void psi_fake_name(UINT16 *service_name, UINT16 program_number)
{
	extern int sprintf (char *s, const char *format, ...);
	char name[33];

	sprintf(name, "Ch-%d", (int)program_number);
	psi_convert_string(service_name, name, STRLEN(name));
}

static int psi_adjust_node(UINT32 pos, P_NODE *p_node)
{
	INT32 ret;
	P_NODE *db_prog = p_node+1;

	FUNCTION_ENTER();

	ret = amsdb_get_node_at(TYPE_PROG_NODE, pos, (UINT8 *)db_prog, sizeof(P_NODE));
	if( ret == DB_SUCCES)
	{
		if (MEMCMP(p_node, db_prog, sizeof(P_NODE)))
		{
			SEARCH_DEBUG("modify node\n");
			ret = amsdb_modify_node(TYPE_PROG_NODE, p_node->prog_id, (UINT8 *)p_node, sizeof(P_NODE));
			if (ret != DB_SUCCES)
			{
				SEARCH_NOTICE("amsdb_modify_node error!\n");
				return SI_PERROR;
			}
		}
	}

	FUNCTION_LEAVE();

	return SI_SUCCESS;
}

static INT32 psi_install_prog(P_NODE *p_node, amssearch_notify_t search_callback)
{
	UINT16 pos = INVALID_POS_NUM;
	INT32 result = FALSE;
	INT32 ret;

	FUNCTION_ENTER();	 
	SEARCH_NOTICE( "psi_install_prog::video pid=%d,p_node->ca_mode=%d,service_type=%d\n",p_node->video_pid,p_node->ca_mode,p_node->service_type);
	if( search_store_FTA_Oly == 1)
	{
		SEARCH_NOTICE("Only store FTA!!!\n");
		if(p_node->ca_mode==1)
		{
			FUNCTION_LEAVE();
			return SI_SUCCESS;
		}
	}
	if( search_store_Pro_Type == 1)//only tv
	{
		SEARCH_NOTICE("Only store TV!!!\n");
		if( p_node->video_pid ==8191 )
		{
			FUNCTION_LEAVE();
			return SI_SUCCESS;
		}
	}
	else if( search_store_Pro_Type == 2 )//only Radio
	{
		SEARCH_NOTICE("Only store Radio!!!\n");
		if( p_node->video_pid!=8191 )
		{
			FUNCTION_LEAVE();
			return SI_SUCCESS;
		}
	}
	//add fake name here
	if (p_node->name_len == 0)
	{
		psi_fake_name(p_node->service_name, p_node->prog_number);
		p_node->name_len = DB_STRLEN(p_node->service_name)*sizeof(UINT16);
	}

	ret = amsdb_lookup_node(TYPE_PROG_NODE, p_node->tp_id, (UINT8*)p_node, sizeof(P_NODE));
	if (SUCCESS != ret) /*not found*/
	{
		ret = amsdb_add_node(TYPE_PROG_NODE, p_node->tp_id, (UINT8*)p_node, sizeof(P_NODE));
		if ((DBERR_FLASH_FULL==ret) || (DBERR_MAX_LIMIT)==ret) 
		{
			SEARCH_NOTICE("SI_STOFULL!\n");
			if(search_callback != NULL)
			{
				result = search_callback(0, SI_NOTIFY_PROGRAM_FULL, 0);
			}
			return SI_STOFULL;
		}

		DUMP_PNODE(p_node);
	}
	else
	{
		P_NODE old_node;
		pos = amsdb_get_node_pos(TYPE_PROG_NODE, p_node->prog_id);
		if(DB_SUCCES == amsdb_get_node_at(TYPE_PROG_NODE, pos, (UINT8*)&old_node, sizeof(P_NODE)))
		{
			p_node->fav_grp = old_node.fav_grp;
			p_node->lock_flag = old_node.lock_flag;
			p_node->skip_flag = old_node.skip_flag;
			p_node->provider_lock = old_node.provider_lock;
		}
		psi_adjust_node(pos, p_node);
	}

	if(search_callback != NULL)
	{
		pos = amsdb_get_node_pos(TYPE_PROG_NODE, p_node->prog_id);
		result = search_callback(0, SI_NOTIFY_PROGRAM_ADDED, &pos);
	}

	FUNCTION_LEAVE();

	return SI_SUCCESS;
}

// *****************************************************************
// Summary:
//	   get si table's private info.
// Description:
//	   The function specifies si table's private info.
// Returns:
//	   The return values are enumerated in adr_retcode.h.
// Parameters:
//	   table :				[in] table.
//	   table_spec : 	 [out] table info's buffer.
// 
// See Also:
// *****************************************************************
static INT32 search_get_table_info(UINT32 handle, amssearch_table_e table, amssearch_spec_section_info_t *table_spec)
{
	if(!table_spec)
		return ERR_FAILURE;

	switch(table)
	{
		case SI_SEARCH_SDT_ACTUAL:
		case SI_SEARCH_SDT_OTHER:
	//		  table_spec->pid = ;
	//		  table_spec->table_id = ;
			break;

		case SI_SEARCH_NIT_ACTUAL:
			break;

		case SI_SEARCH_BAT:
			break;		  
	}
	
	return SUCCESS;
}

// *****************************************************************
// Summary:
//		store program to DB.
// Description:
//		step 1: construct P_NODE <- search result(PAT/SDT/PMT...),
//		step 2: store P_NODE into DB.
// Returns:
//	   The return values are enumerated in adr_retcode.h.
// Parameters:
//	   info :	   [in] carries program information(PAT/SDT/PMT...).
//	   cfg :	  [in] carries sat_id, tp_id, search_callback.
// 
// See Also:
// *****************************************************************
static INT32 search_store_program(UINT32 handle, amssearch_result_t *info, amssearch_store_info_t *cfg)
{
	P_NODE *p_node = info->program;
	UINT32 i, j, k, m, n, actual_index;
	amsret_e err_code;
	INT32 ret = SI_SUCCESS;

	FUNCTION_ENTER();

	SEARCH_ERROR("pat.prog_count - 0x%X\n", info->pat.prog_count);
	SEARCH_ERROR("pat.ts_id - 0x%X\n", info->pat.ts_id);
	SEARCH_ERROR("sdt.cur_ts_id - 0x%X\n", info->sdt.cur_ts_id);	

	//sdt Traversal actual ts_id
	for (i=0; i<info->sdt.ts_cnt; i++)
	{
		if (info->sdt.cur_ts_id == info->sdt.ts_id[i])
			break;
	}
	if(i < info->sdt.ts_cnt)
		actual_index = i;
	else
		actual_index = 0xffffffff;
	
	//sdt Traversal ts_id
	for (i=0; i<info->sdt.ts_cnt; i++)
	{
		if (info->pat.ts_id == info->sdt.ts_id[i])
			break;
	}

	if (i >= info->sdt.ts_cnt)
	{
		SEARCH_NOTICE("sdt ts id != pat ts id 0x%X\n", info->pat.ts_id);
		err_code = SIS_ERR_TS_ID;
		if (cfg->search_callback)
		{					 
			cfg->search_callback(0, SI_NOTIFY_ERROR, &err_code);
		}
	}	

	//delete invalid programs
	{
		UINT16 node_cnt;
		P_NODE node;

		INT32 jj, kk;
		node_cnt = amsdb_get_node_cnt(TYPE_PROG_NODE, VIEW_ALL|PROG_ALL_MODE, 0);
		for(jj=node_cnt-1; jj>=0; jj--)
		{
			ret = amsdb_get_node_at(TYPE_PROG_NODE, jj, (UINT8 *)&node, sizeof(P_NODE));
			if(ret == DB_SUCCES)
			{
				if(node.tp_id != cfg->tp_id)
					continue;
				
				for(kk=0; kk<info->pat.prog_count; kk++)
				{
					if(info->pat.prog_number[kk] == node.prog_number)
						break;
				}
				
			   if(kk >= info->pat.prog_count)
				{
					epg_service_t service;
					service.tp_id = node.tp_id;
					service.service_id = node.prog_number;
					ret = amsepg_del_service(&service, 1, EQUAL);
					ret = amsdb_del_node_at(TYPE_PROG_NODE, jj);				  
				}
			}
		}  
	}	 

	//pat Traversal
	for (j=0; j<info->pat.prog_count; j++)
	{
		//pmt
		for (k=0; k<info->pmt_count; k++)
		{
			if (info->pat.prog_number[j] == info->pmt[k].prog_number)
				break;
		}

		if (k >= info->pmt_count)
		{
			SEARCH_NOTICE("program %d no pmt!\n", info->pat.prog_number[j]);
			continue;
		}
		
		//sdt Traversal service_id
		if((i >= info->sdt.ts_cnt) && (actual_index != 0xffffffff))
		{
			i = actual_index;
		}
		
		if (i<info->sdt.ts_cnt)
		{
			for (m=0; m<info->sdt.service[i].service_cnt; m++)
			{
				if (info->pat.prog_number[j] == info->sdt.service[i].service_id[m])
					break;
			}
			if (m >= info->sdt.service[i].service_cnt)
			{
				SEARCH_NOTICE("program %d is not in sdt!\n", info->pat.prog_number[j]);
			}
		}

		//P_NODE set value
		MEMSET(p_node, 0, sizeof(P_NODE));

		p_node->sat_id = cfg->sat_id;
		p_node->tp_id = cfg->tp_id;
		p_node->prog_number = info->pat.prog_number[j];
		p_node->pmt_pid = info->pat.pmt_pid[j]; //andy 20140620

		//pmt
		if (k < info->pmt_count)
		{
			UINT32 db_audio_cnt = 0, audio_lang_cnt = 0;			
		 /*   if (info->pmt[k].audio_count > MAX_AUDIO_CNT)
				p_node->audio_count = MAX_AUDIO_CNT;
			else
				p_node->audio_count = info->pmt[k].audio_count;
		*/
			p_node->audio_volume = AUDIO_DEFAULT_VOLUME;

			for (db_audio_cnt=0,n=0; n<info->pmt[k].audio_count && db_audio_cnt<MAX_AUDIO_CNT; n++)
			{
				audio_lang_cnt = 0;
				do
				{
					p_node->audio_pid[db_audio_cnt] = info->pmt[k].audio_pid[n];
					p_node->audio_type[db_audio_cnt] = info->pmt[k].audio_stream_type[n];
					get_audio_lang2b(info->pmt[k].audio_lang[n][audio_lang_cnt], (UINT8 *)&p_node->audio_lang[db_audio_cnt]);					 
					db_audio_cnt++;
					audio_lang_cnt++;
				}while((db_audio_cnt<MAX_AUDIO_CNT) && (info->pmt[k].audio_lang[n][audio_lang_cnt][0] != 0));
			}
			p_node->audio_count = db_audio_cnt;

			/* check CA descriptor */
			if (info->pmt[k].ca_count > 0)
			{
				p_node->ca_mode = 1;
				p_node->cas_count = info->pmt[k].ca_count;
				for (n=0; n<info->pmt[k].ca_count; n++)
				{
					p_node->cas_sysid[i] = info->pmt[k].ca_info[n].ca_system_id;
				}
			}

			p_node->pcr_pid = info->pmt[k].pcr_pid;
			p_node->video_pid = info->pmt[k].video_pid;
			p_node->video_type = info->pmt[k].video_stream_type;

			/*TODO*/
			//@@@@@@@@@ need delete
			if (p_node->video_type == H264_VIDEO_STREAM)
				p_node->h264_flag = 1;
		}

		//sdt
		if ((i < info->sdt.ts_cnt) && (m < info->sdt.service[i].service_cnt))
		{
			p_node->service_type = info->sdt.service[i].service_type[m];
			p_node->nvod_ref_sid = info->sdt.service[i].ref_service_id[m];

			p_node->name_len = psi_convert_string((UINT16 *)p_node->service_name, info->sdt.service[i].service_name[m], info->sdt.service[i].name_len[m]);
			p_node->name_len *= sizeof(UINT16);

			p_node->prd_name_len = psi_convert_string((UINT16 *)p_node->service_provider_name, info->sdt.service[i].provider_name[m], info->sdt.service[i].provider_name_len[m]);
			p_node->prd_name_len *= sizeof(UINT16);
		}

		//no sdt or bad sdt, fix service_type
		if (p_node->service_type == 0 || p_node->service_type >= SERVICE_TYPE_USER_DEFINED/*user defined*/)
		{
			//nvod timeshift: no service descriptor or service type != SERVICE_TYPE_NVOD_TS,
			//but has Time shifted service descriptor
			if (p_node->nvod_ref_sid)
			{
				p_node->service_type = SERVICE_TYPE_NVOD_TS;
			}
			/*else if ()
			{
				//no service descriptor or service type != SERVICE_TYPE_NVOD_REF,
				//but has NVOD reference descriptor
				p_node->service_type = SERVICE_TYPE_NVOD_REF;
			}*/
			else
			{
				if (VALID_PID(p_node->video_pid))
				{
					switch (p_node->video_type)
					{
						case MPEG1_VIDEO_STREAM:
						case MPEG2_VIDEO_STREAM:
						case AVS_VIDEO_STREAM:						
							p_node->service_type = SERVICE_TYPE_DTV;
							break;
						/*TODO:*/		 
						/*case xxx:
							p_node->service_type = SERVICE_TYPE_HD_MPEG2;
							break;*/
						case MPEG4_VIDEO_STREAM:
							p_node->service_type = SERVICE_TYPE_SD_MPEG4;
							/*TODO:*/ 
							//or
							//p_node->service_type = SERVICE_TYPE_HD_MPEG4;
							break;
						case H264_VIDEO_STREAM:
							p_node->service_type = SERVICE_TYPE_DTV;
							break;
						/*TODO: 	  
						case AVS:
							break;
						*/ 
						default:
							p_node->service_type = SERVICE_TYPE_DTV;
							break;
					}
				}
				else if (p_node->audio_count)
					p_node->service_type = SERVICE_TYPE_DRADIO;
				else
				{
					//not sure...
				}
			}
		}

		if (p_node->service_type == 0 || p_node->service_type >= SERVICE_TYPE_USER_DEFINED/*user defined*/)
		{
			continue;
		}

		//@@@@av_flag tobe delete
		switch(p_node->service_type)
		{
			case SERVICE_TYPE_DTV:
			case SERVICE_TYPE_HD_MPEG2:
			case SERVICE_TYPE_SD_MPEG4:
			case SERVICE_TYPE_HD_MPEG4:
				p_node->av_flag = 1;
				break;
		}

		//private: shall assigned by AP
		//p_node->logical_channel_num

		ret = psi_install_prog(p_node, cfg->search_callback);
		if (SI_STOFULL == ret)
		{
			SEARCH_NOTICE("SI_STOFULL!\n");
			return SI_STOFULL;
		}
		else if (SI_SUCCESS != ret) 
		{
			SEARCH_NOTICE("install prog failed!\n");
		}

		MEMSET(p_node, 0, sizeof(P_NODE));
	}

	//if pat's ts_id is invalid, use the cur sdt ts_id...
	if (i >= info->sdt.ts_cnt)
	{
		for (i=0; i<info->sdt.ts_cnt; i++)
		{
			if (info->sdt.cur_ts_id == info->sdt.ts_id[i])
				break;
		}
	}	 

	//sdt Traversal
	for (m=0; m<info->sdt.service[i].service_cnt; m++)
	{
		for (j=0; j<info->pat.prog_count; j++)
		{
			if (info->pat.prog_number[j] == info->sdt.service[i].service_id[m])
				break;
		}

		//service in sdt, but not in pat
		if (j >= info->pat.prog_count)
		{
			SEARCH_DEBUG("service_id %d no program!\n", info->sdt.service[i].service_id[m]);

			MEMSET(p_node, 0, sizeof(P_NODE));

			p_node->sat_id = cfg->sat_id;
			p_node->tp_id = cfg->tp_id;

			p_node->prog_number = info->sdt.service[i].service_id[m];

			p_node->service_type = info->sdt.service[i].service_type[m];
			p_node->nvod_ref_sid = info->sdt.service[i].ref_service_id[m];
			//fix service type
			if (p_node->service_type == 0|| p_node->service_type >= SERVICE_TYPE_USER_DEFINED/*user defined*/)
			{
				//nvod timeshift: no service descriptor or service type != SERVICE_TYPE_NVOD_TS,
				//but has Time shifted service descriptor
				if (p_node->nvod_ref_sid)
				{
					p_node->service_type = SERVICE_TYPE_NVOD_TS;
				}
				/*else if ()
				{
					//no service descriptor or service type != SERVICE_TYPE_NVOD_REF,
					//but has NVOD reference descriptor
					p_node->service_type = SERVICE_TYPE_NVOD_REF;
				}*/
			}

			if (p_node->service_type == 0 || p_node->service_type == SERVICE_TYPE_DTV || p_node->service_type == SERVICE_TYPE_DRADIO
				|| p_node->service_type >= SERVICE_TYPE_USER_DEFINED/*user defined*/)
			{
				continue;
			}

			p_node->name_len = psi_convert_string((UINT16 *)p_node->service_name, info->sdt.service[i].service_name[m], info->sdt.service[i].name_len[m]);
			p_node->name_len *= sizeof(UINT16);

			p_node->prd_name_len = psi_convert_string((UINT16 *)p_node->service_provider_name, info->sdt.service[i].provider_name[m], info->sdt.service[i].provider_name_len[m]);
			p_node->prd_name_len *= sizeof(UINT16);

			ret = psi_install_prog(p_node, cfg->search_callback);
			if (SI_STOFULL == ret)
			{
				SEARCH_NOTICE("SI_STOFULL!\n");
				err_code = SIS_ERR_PROGRAM_FULL;
				if (cfg->search_callback)
				{
					cfg->search_callback(0, SI_NOTIFY_ERROR, &err_code);
				}
				return SI_STOFULL;
			}
			else if (SI_SUCCESS != ret)
			{
				SEARCH_NOTICE("install prog failed!\n");
			}
		}
	}

	FUNCTION_LEAVE();

	return ret;
}

/* TV->radio->nvod->data */
static UINT32 search_sort_key(UINT16 service_type, UINT16 prog_number)
{
    UINT32 key;

    switch (service_type)
    {
    case SERVICE_TYPE_DTV:
        key = 0x10;
        break;
    case SERVICE_TYPE_HD_MPEG2:
        key = 0x11;
        break;
    case SERVICE_TYPE_SD_MPEG4:
        key = 0x12;        
        break;
    case SERVICE_TYPE_HD_MPEG4:
        key = 0x13;        
        break;
    case SERVICE_TYPE_NVOD_TS:
        key = 0x30;                
        break;
    case SERVICE_TYPE_NVOD_TS_SD_MPEG4:
        key = 0x31;                
        break;
    case SERVICE_TYPE_NVOD_TS_HD_MPEG4:
        key = 0x32;        
        break;
    case SERVICE_TYPE_DATABROAD:
        key = 0x40;        
        break;
    default:
        key = 0x20; 
        break;
    }

    key = (key<<16)|prog_number;

    return key;
}

static INT32 search_add_program(UINT16 idx, ALiDVB_ChannelNode *node)
{
	int i;
    P_NODE p_node;

    if (amsdb_get_node_at(TYPE_PROG_NODE, idx, (UINT8 *)(&p_node), sizeof(P_NODE)) != SUCCESS)
    {
        SEARCH_ERROR("get pnode @%d failed!\n", idx);
        return !SUCCESS;
    }

	if (node == NULL)
		return !SUCCESS;

	memset(node, 0, sizeof(ALiDVB_ChannelNode));
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
	memcpy(node->service_name, p_node.service_name, MAX_SERVICE_NAME_LENGTH*sizeof(node->service_name[0]));

	node->sat_id = p_node.sat_id;
	node->tp_id = p_node.tp_id;
	node->prog_id = p_node.prog_id;

	return SUCCESS;
}

static INT32 search_callback(UINT32 handle, amssearch_notify_e type, void *param)
{
	switch(type)
	{
		case SI_NOTIFY_PROGRESS:
		{
			UINT32 progress = *(UINT32 *)param;
			SEARCH_DEBUG("%s(SI_NOTIFY_PROGRESS, %d)\n", __FUNCTION__, progress);
			SEARCH_CALLBACK(SEARCH_NOTIFY_PROGRESS, &progress);
			break;
		}
		case SI_NOTIFY_TP_TUNING:
		{
			T_NODE *tNode = (T_NODE *)(param);
			ALiDVB_Frontend fe;

			fe.type = tNode->ft_type;
			if( fe.type == FRONTEND_TYPE_S )
				fe.frequency = (tNode->frq*100);
			else
			fe.frequency = tNode->frq;
			fe.symbol_rate = tNode->sym;
			fe.modulation = tNode->FEC_inner;
			SEARCH_DEBUG("%s(SI_NOTIFY_TP_TUNING, %d)\n", __FUNCTION__, tNode->frq);
			
			SEARCH_CALLBACK(SEARCH_NOTIFY_TP_TUNING, &fe);
			break;
		}
		case SI_NOTIFY_TP_LOCK:
		{
			UINT8 lock = *(UINT8 *)param;
			SEARCH_DEBUG("%s(SI_NOTIFY_TP_LOCK, %d)\n", __FUNCTION__, lock);
			SEARCH_CALLBACK(SEARCH_NOTIFY_TP_LOCK, &lock);
			break;
		}
		case SI_NOTIFY_PROGRAM_ADDED:
		{
			UINT16 pos = *(UINT16 *)param;
			ALiDVB_ChannelNode node;
			SEARCH_DEBUG("%s(SI_NOTIFY_PROGRAM_ADDED, %d)\n", __FUNCTION__, pos);
			search_add_program(pos, &node);
			SEARCH_CALLBACK(SEARCH_NOTIFY_PROGRAM_ADDED, &node);
			break;
		}
		case SI_NOTIFY_TP_FULL:
			SEARCH_DEBUG("%s(SI_NOTIFY_TP_FULL)\n", __FUNCTION__);
			SEARCH_CALLBACK(SEARCH_NOTIFY_TP_FULL, 0);
			break;
		case SI_NOTIFY_PROGRAM_FULL:
			SEARCH_DEBUG("%s(SI_NOTIFY_PROGRAM_FULL)\n", __FUNCTION__);
			SEARCH_CALLBACK(SEARCH_NOTIFY_PROGRAM_FULL, 0);
			break;
		case SI_NOTIFY_ASCOMPLETE:
			SEARCH_ERROR("%s(SI_NOTIFY_ASCOMPLETE)\n", __FUNCTION__);
			{
				P_NODE p_node;
				UINT32 *key;
				INT32 cnt;
				INT32 i;

				/* sort prog by service_type & prog_number*/
				cnt = amsdb_get_node_cnt(TYPE_PROG_NODE, VIEW_ALL | PROG_ALL_MODE, 0);
				key = (UINT32*)MALLOC(cnt<<2);

				for (i=0; i<cnt; i++)
				{
					amsdb_get_node_at(TYPE_PROG_NODE, i, &p_node, sizeof(P_NODE));
					//key[i] = p_node.service_type|p_node.prog_number;
					key[i] = search_sort_key(p_node.service_type,p_node.prog_number);
				}
				amsdb_sort_node(TYPE_PROG_NODE, DB_SORT_ORDER_ASCEND, key, cnt);
				FREE(key);
			}
                    
			amsdb_update_data();
			SEARCH_ERROR("Update_data 1\n");
			SEARCH_CALLBACK(SEARCH_NOTIFY_ASCOMPLETE, 0);			
			if (search_workspace)
			{
				free(search_workspace);
				search_workspace = NULL;
			}
			break;
		case SI_NOTIFY_ASSTOP:
			SEARCH_ERROR("%s(SI_NOTIFY_ASSTOP)\n", __FUNCTION__);
			SEARCH_CALLBACK(SEARCH_NOTIFY_ASSTOP, 0);
			amsdb_update_data();
			SEARCH_ERROR("Update_data 2\n");
			if (search_workspace)
			{
				free(search_workspace);
				search_workspace = NULL;
			}
			break;
		case SI_NOTIFY_NIT:
			SEARCH_DEBUG("%s(SI_NOTIFY_NIT)\n", __FUNCTION__);					  
			return RESET_SEARCH;
			break;	   
		default:
			;
	}

	return SUCCESS;
}

static INT32 search_param_init(amsas_service_param *asp)
{
    if (search_workspace == NULL)
    {
    	amssearch_compability_t com;
    	amssearch_get_compability(&com);
    	search_workspace = (UINT8 *)malloc(com.buffer_size);
    	if (search_workspace == NULL)
    	{
			SEARCH_ERROR("malloc workspace for search failed!\n");
			return !SUCCESS;
		}
    }

   // asp->as_frontend_type = FRONTEND_TYPE_C;

    asp->nim_id = 0;
    asp->sat_id = asp->sat_ids[0];

    asp->turning_timeout = 2000;//1000;

    asp->search_config.dmx_handle = 0;
    asp->search_config.workspace = search_workspace;
    asp->search_config.size = 2048 * 1024;
    asp->search_config.search_callback = search_callback;
	asp->search_config.store_callback = search_store_program;
	asp->search_config.get_table_info = search_get_table_info;
    asp->search_config.table_bitmap |= SI_SEARCH_PAT_MASK|SI_SEARCH_PMT_MASK|SI_SEARCH_SDT_ACTUAL_MASK;
    asp->search_config.timeout[SI_SEARCH_PAT] = 2500;
    asp->search_config.timeout[SI_SEARCH_PMT] = 2500;
    asp->search_config.timeout[SI_SEARCH_SDT_ACTUAL] = 2500;

	return SUCCESS;
}
static BOOL alloc_transponder_dvbs( amsas_service_param asp,UINT32 *tp_id )
{
	INT32 ret;
	T_NODE tp;

	FUNCTION_ENTER();
	MEMSET(&tp, 0, sizeof(T_NODE));
	tp.sat_id = asp.sat_ids[0];
	tp.ft_type = FRONTEND_TYPE_S;
	tp.frq = asp.band[0].as_from;
	tp.sym = asp.band[0].ft_param.s_info.sym;
	tp.pol= asp.band[0].ft_param.s_info.por;
	ret = amsdb_lookup_node(TYPE_TP_NODE, tp.sat_id, (UINT8 *)&tp, sizeof(T_NODE));
	if ( ret != SUCCESS)
	{
		ret = amsdb_add_node(TYPE_TP_NODE, tp.sat_id, (UINT8 *)&tp, sizeof(T_NODE));
		if (ret == DBERR_FLASH_FULL)
		{
			return FALSE;
		}
		else if (ret != DB_SUCCES)
		{
			LOGD("alloc_transponder_dvbs::ret=%d\n",ret);
			return FALSE;
		}
		amsdb_update_data();
		LOGD("alloc_transponder_dvbs::add::tp.tp_id=%d\n",tp.tp_id);
	}
	else
		LOGD("alloc_transponder_dvbs::tp.tp_id=%d\n",tp.tp_id);
	*tp_id = tp.tp_id;
	FUNCTION_LEAVE();
	return TRUE;
}
int ALiDVB_SearchStart(ALiDVB_SearchParam *param, ALiDVB_SearchNotifyFn callback)
{
	amsas_service_param asp;
	int count = 0,i=0;
	ALiDVB_SatelliteNode snode;
	S_NODE sat;

	memset(&asp, 0, sizeof(amsas_service_param));
	memset(&snode, 0, sizeof(ALiDVB_SatelliteNode));
	memset(&sat, 0, sizeof(S_NODE));
	asp.as_frontend_type = param->frontend_type;//FRONTEND_TYPE_C;

	if( asp.as_frontend_type == FRONTEND_TYPE_S )
	{
		count = amsdb_get_node_cnt(TYPE_SAT_NODE, VIEW_ALL, 0);
		asp.band[0].as_from = (param->frequency_from/100);
	asp.band[0].as_to = param->frequency_to;
	asp.band[0].bandwidth = param->bandwidth;
		asp.band[0].ft_param.s_info.sym = param->symbol_rate;
		asp.band[0].ft_param.s_info.por = param->modulation;
		if( param->nit_search )
			asp.search_config.nit_method = NIT_METHOD_EXCLUED_MAIN_FREQ;
		else
		asp.search_config.nit_method = NIT_METHOD_NONE;
		search_store_FTA_Oly = param->FTA_only;
		search_store_Pro_Type = param->program_type;
		switch(param->search_method)
		{
			case SEARCH_METHOD_TP_SCAN:
		asp.band_cnt = 1;
		asp.as_sat_cnt = 1;
				for( i=0;i<count;i++)
				{
					ALiDVB_GetSatNode(i, &snode);
					if(snode.select)
					{
						asp.sat_ids[0] = snode.sat_id;
						LOGD("%s::cur search sat id=%d\n",__FUNCTION__,snode.sat_id);
						break;
					}
				}
				if( asp.sat_ids[0] == 0 )
				{
					LOGD("%s::(default)cur search sat id=%d\n",__FUNCTION__,asp.sat_ids[0]);
		asp.sat_ids[0] = 1;
				}
				asp.as_method = AS_METHOD_TP;
				alloc_transponder_dvbs( asp,&asp.band[0].as_from );
				asp.band[0].as_to = asp.band[0].as_from;
				break;
			case SEARCH_METHOD_SAT_SCAN:
				asp.band_cnt = 1;
				asp.as_sat_cnt = 1;
				for( i=0;i<count;i++)
				{
					ALiDVB_GetSatNode(i, &snode);
					if(snode.select)
					{
						asp.sat_ids[0] = snode.sat_id;
						LOGD("%s::cur search sat id=%d\n",__FUNCTION__,snode.sat_id);
						break;
					}
				}
				if( asp.sat_ids[0] == 0 )
				{
					LOGD("%s::(default)cur search sat id=%d\n",__FUNCTION__,asp.sat_ids[0]);
					asp.sat_ids[0] = 1;
				}
				asp.as_method = AS_METHOD_SAT_TP;
				break;
			case SEARCH_METHOD_BLIND_SCAN:
			case SEARCH_METHOD_ACCURATEBLIND_SCAN:
				asp.band_cnt = 1;
				asp.as_sat_cnt = 1;
				for( i=0;i<count;i++)
				{
					ALiDVB_GetSatNode(i, &snode);
					if(snode.select)
					{
						asp.sat_ids[0] = snode.sat_id;
						LOGD("%s::cur search sat id=%d\n",__FUNCTION__,snode.sat_id);
						break;
					}
				}
				if( asp.sat_ids[0] == 0 )
				{
					LOGD("%s::(default)cur search sat id=%d\n",__FUNCTION__,asp.sat_ids[0]);
					asp.sat_ids[0] = 1;
				}
				asp.as_method = AS_METHOD_FFT;
				asp.band[0].as_from = AS_FREQ_MIN;
				asp.band[0].as_to = AS_FREQ_MAX;
				amsdb_get_node_byid(TYPE_SAT_NODE, snode.sat_id, &sat, sizeof(S_NODE));
				if (sat.lnb_type == LNB_CTRL_22K)
				{
					asp.band[0].as_from = 950;
					asp.band[0].as_to = 2150;
				}
				break;
		}
	}
	else if( asp.as_frontend_type == FRONTEND_TYPE_C )
	{
		asp.band[0].as_from = param->frequency_from;
		asp.band[0].as_to = param->frequency_to;
		asp.band[0].bandwidth = param->bandwidth;
		asp.band[0].ft_param.c_info.sym = param->symbol_rate;
		asp.band[0].ft_param.c_info.modulation = param->modulation;
		asp.search_config.nit_method = NIT_METHOD_NONE;
		asp.band_cnt = 1;
		asp.as_sat_cnt = 1;
		asp.sat_ids[0] = 1;
	}
	else if( asp.as_frontend_type == FRONTEND_TYPE_T )
	{
		asp.band[0].as_from = param->frequency_from;
		asp.band[0].as_to = param->frequency_to;
		asp.band[0].bandwidth = param->bandwidth;
		asp.search_config.nit_method = NIT_METHOD_NONE;
		asp.band_cnt = 1;
		asp.as_sat_cnt = 1;
		asp.sat_ids[0] = 1;
	}

	

	if (param->nit_search)
	{
		asp.search_config.table_bitmap = SI_SEARCH_NIT_ACTUAL_MASK;
		asp.search_config.timeout[SI_SEARCH_NIT_ACTUAL] = 3000;
		asp.search_config.nit_method = NIT_METHOD_INCLUED_MAIN_FREQ;
	}

	if (SUCCESS != search_param_init(&asp))
		return SEARCH_FAILED;

	LOGD("%s,asp.as_frontend_type=%d,sizeof(amsas_service_param)=%d,asp.band[0].as_from\n", __FUNCTION__,asp.as_frontend_type,sizeof(amsas_service_param),asp.band[0].as_from);
	search_notify_callback = callback;

	return (amsas_service_start(&asp) == SUCCESS ? SEARCH_SUCCESS : SEARCH_FAILED);
}

int ALiDVB_SearchStop(void)
{
	return (amsas_service_stop() == SUCCESS ? SEARCH_SUCCESS : SEARCH_FAILED);
}

