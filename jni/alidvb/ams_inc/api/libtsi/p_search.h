/*
 * Copyright (C) ALi Shanghai Corp. 2005
 *
 * File name	: p_search.h
 * Description	: program search via service informations declarations.
 *
 * History:
 *	...
 * 1. 20050519	0.5	Zhengdao Li	Add NIT parsing support.
 */
#ifndef __P_SEARCH_H__
#define __P_SEARCH_H__

#include <adr_sys_config.h>
#include <api/libsi/si_config.h>
#include <api/libtsi/sec_pmt.h>
#include <api/libtsi/sec_sdt.h>
#include <api/libtsi/db_3l.h>


#define P_SEARCH_BUFF_SIZE    		64
#define P_MAX_AUDIO_NUM		  	MAX_AUDIO_CNT
//138-a14, has 9 ecm
#define P_MAX_CA_NUM		  	16

enum {
	P_SEARCH_FTA		  	= 0x0001,
	P_SEARCH_SCRAMBLED		= 0x0002,
	P_SEARCH_RADIO			= 0x0004,
	P_SEARCH_TV			= 0x0008,
	P_SEARCH_DOMTESTIC_PATCH	= 0x0010,
	P_SEARCH_NIT			= 0x0020,
	P_SEARCH_BAT			= 0x0040,
	P_SEARCH_SATTP			= 0x0080,
	P_SEARCH_NVOD			= 0x0100,
	P_SEARCH_ALL			= 0x000F,
	P_SEARCH_DATA			= 0x0200,
};

#define SECTION_TABLE_LEN		4096

#ifdef AUTO_OTA
typedef struct {
	UINT16 hw_model;
	UINT16 hw_ver;
	UINT32 oui;
	UINT16 sw_model;
	UINT16 ota_sw_version;
}AUTO_OTA_INFO;

typedef struct
{
	UINT8 stream_type;//set by manufacture  ref to DigiTAG Handbook on DVB-SSU :
                      //   Implementing System Software Updates on the terrestrial television platform Page15
	UINT16 ssu_pid;
//    UINT32 pmt_oui;
	UINT8 update_type;
    //UINT8 update_versioning_flag;
    //UINT8 update_version;
	AUTO_OTA_INFO m_otainfo;
}PMTSSU_INFO;

typedef struct//now, this structure is only used to store ssu updated info. It will be extended in future.
{
	UINT32 descriptors_parse_stat;
	PMTSSU_INFO pmt_ssu_info;
}PMT_ESLOOP_INFO;
#endif

/* define a struct for hold data from program searching */
typedef struct prog_info
{
	UINT16	prog_number;

	UINT8	service_type;
	UINT8	audio_count;
	UINT16  audio_pid[P_MAX_AUDIO_NUM];
	UINT8	audio_lang[P_MAX_AUDIO_NUM][3];
	UINT16	video_pid;
    UINT32  cur_audio;//audio idx selection

	UINT16  teletext_pid;
	UINT16  subtitle_pid;

	UINT8	av_flag;
	UINT8   EIT_flag;

	CA_INFO CA_info[P_MAX_CA_NUM];
	UINT8 CA_count;

	UINT16 pcr_pid;
	UINT16 pmt_pid;
	UINT8 pmt_version;
	UINT8 pmt_status;
	UINT8 sdt_status;
	UINT16 sat_id;
	UINT32 	tp_id;
#ifdef DB_USE_UNICODE_STRING
	UINT8 service_name[2*(MAX_SERVICE_NAME_LENGTH + 1)];
#if (SERVICE_PROVIDER_NAME_OPTION>0)
	UINT8 service_provider_name[2*(MAX_SERVICE_NAME_LENGTH + 1)];
#endif
#else
	UINT8 service_name [ MAX_SERVICE_NAME_LENGTH + 1 ];
#if (SERVICE_PROVIDER_NAME_OPTION>0)
	UINT8 service_provider_name[MAX_SERVICE_NAME_LENGTH + 1];
#endif
#endif

#if (SYS_PROJECT_FE == PROJECT_FE_DVBC)
	UINT16 ref_sid;
	UINT16 bouquet_id;
	UINT16 logical_channel_num;
	UINT16 volume;
	UINT16 track;
#endif

#if (SYS_PROJECT_FE == PROJECT_FE_DVBT) || (SYS_PROJECT_FE == PROJECT_FE_ATSC) || (SYS_PROJECT_FE == PROJECT_FE_ISDBT)
	UINT16  logic_channel_number;   //for LCN
#endif
#if (SYS_PROJECT_FE == PROJECT_FE_DVBT) || (SYS_PROJECT_FE == PROJECT_FE_ATSC) || (SYS_PROJECT_FE == PROJECT_FE_ISDBT)
#if (MPEG4_DEFINITION==SYS_FUNC_ON)
	UINT8    mpeg_4_video_exist;
        UINT8    mpeg_4_audio_exist;
	UINT16   mpeg_4_audio_pid[MAX_AUDIO_CNT];
	UINT16   mpeg4_audio_count;
#endif
#endif

#ifdef SUBTITLE_SELECT_MENU
	UINT8	subtitle_lang[3];
#endif
#ifdef SCAN_CHECK_SDT
	UINT8 sdt_check_valid;
#endif
#if(defined(DTTM_DB) || defined(DTG_AUDIO_SELECT) || defined(AUDIO_DESCRIPTION_SUPPORT))
	UINT8  audio_type[P_MAX_AUDIO_NUM];
#endif
#if (defined(_ISDBT_ENABLE_))
	UINT8	audio_com_tag[P_MAX_AUDIO_NUM];
#endif
#if(defined( _MHEG5_ENABLE_) ||defined(_LCN_ENABLE_) || defined(_MHEG5_V20_ENABLE_))
	UINT8 mheg5_exist;
	UINT16 lcn;
	UINT8 lcn_true;
#ifdef  SUPPORT_FRANCE_HD	
	UINT16 hd_lcn;
	UINT8 hd_lcn_true;
#endif	
#endif
#ifdef _SERVICE_ATTRIBUTE_ENABLE_
	UINT8 numeric_selection_flag;//get from NIT service_attribute_descriptor, private descriptor defined in UKDTT
	UINT8 visible_service_flag;
#endif
#if (SYS_PROJECT_FE == PROJECT_FE_DVBS)
	UINT8 avc_video_exist;
	UINT8 mpeg_4_video_exist;
#endif

#ifdef AUTO_OTA
	PMT_ESLOOP_INFO p_esloopinfo;
#endif

#if(defined(SUPPORT_MTILINGUAL_SERVICE_NAME))
	UINT16   mtl_name_count;
	UINT8   mtl_iso639_code[MAX_MTL_NAME_CNT][3];
	UINT8   mtl_service_name[MAX_MTL_NAME_CNT][2*(MAX_SERVICE_NAME_LENGTH + 1)];	
#endif
#ifdef VIDEO_SEAMLESS_SWITCHING
	UINT8 video_control;//bit[0-1] not used in spec and here use for exist flag,bit[2-5] encode format,bit[6] sequence end flag, big[7]still picture flag
#endif
}PROG_INFO;

typedef struct stream_info
{
	UINT16 nit_pid;
	UINT16 transport_stream_id;
#if(SYS_PROJECT_FE == PROJECT_FE_DVBT && (SYS_SDRAM_SIZE != 2 || defined(_MHEG5_ENABLE_) || defined(_MHEG5_V20_ENABLE_))) \
	||(SYS_PROJECT_FE == PROJECT_FE_ATSC) || (SYS_PROJECT_FE == PROJECT_FE_ISDBT)
#if (defined(_MHEG5_ENABLE_) || defined(_MHEG5_V20_ENABLE_))
	UINT16 network_id;
#endif
	UINT16 original_network_id;
#endif
}STREAM_INFO;

typedef union {
	struct {
		UINT16 tsid;
		UINT16 onid;
#if (SYS_PROJECT_FE == PROJECT_FE_DVBT)
#if defined(AS_SUPPORT_NIT)	
		UINT8 info_type;
#endif
#endif
	} common;
	
	struct {
		UINT16 tsid;
		UINT16 onid;
#if (SYS_PROJECT_FE == PROJECT_FE_DVBT)
#if defined(AS_SUPPORT_NIT)	
		UINT8 info_type;
#endif
#endif
		UINT16 frequency;
		UINT16 symbol_rate;
		UINT16 position;
		UINT8 polarity;
		UINT8 FEC_inner;
	}s_info;
	
	struct {
		UINT16 tsid;
		UINT16 onid;
#if (SYS_PROJECT_FE == PROJECT_FE_DVBT)
#if defined(AS_SUPPORT_NIT)	
		UINT8 info_type;
#endif
#endif
		UINT32 frequency;
		UINT16 symbol_rate;
		UINT16 modulation;
		UINT8 FEC_outer;
		UINT8 FEC_inner;
	}c_info;

#if (SYS_PROJECT_FE == PROJECT_FE_DVBT)
#if defined(AS_SUPPORT_NIT)	
	struct {
		UINT16 tsid;
		UINT16 onid;
		UINT8 info_type;
		UINT32 frequency;
		UINT8 bandwidth;
		UINT8 modulation;
		UINT8 guard_interval;
		UINT8 FFT;
	}t_info;
#endif
#endif
}TP_INFO;

typedef UINT8 (*prog_search_progress_callback)(UINT8 progress, void *node);

#if (SYS_PROJECT_FE == PROJECT_FE_DVBT) || (SYS_PROJECT_FE == PROJECT_FE_ATSC) || (SYS_PROJECT_FE == PROJECT_FE_ISDBT)
#define P_SEARCH_LCN_INVALID	0xFFFF
typedef UINT8 (*prog_search_pid_check_callback)(PROG_INFO *p_info);
#endif


typedef void (*check_nim_t)();

#ifdef __cplusplus
extern "C"{
#endif

INT32 get_section(UINT8 *buff,INT16 buff_len,UINT16 pid, UINT32 *crc);

INT32 parse_pat_section(UINT8 *buff,INT16 buff_len);

INT32 parse_pmt_section(UINT8 *buff,INT16 buff_len,PROG_INFO *p_info);

INT32 parse_sdt_section(UINT8 *buff,INT16 buff_len,PROG_INFO *p_info,UINT8 node_cnt);

void stop_prog_search();

void info2db(PROG_INFO *p_info, P_NODE *p_node);

#if (SYS_PROJECT_FE == PROJECT_FE_DVBT) || (SYS_PROJECT_FE == PROJECT_FE_ATSC) || (SYS_PROJECT_FE == PROJECT_FE_ISDBT)
INT32 async_prog_search(UINT16 sat_id, UINT32 tp_id, UINT8 search_type, 
	prog_search_progress_callback progress_callbck, UINT8 add_flag,
	check_nim_t check_nim, prog_search_pid_check_callback pid_check_callback);
#else
INT32 async_prog_search(UINT16 sat_id, UINT32 tp_id, UINT8 search_type,
	prog_search_progress_callback progress_callbck, UINT8 add_flag, check_nim_t check_nim);
#endif

#ifdef BOU_AND_LOGIC_NUM_SUPPORT
INT32 get_si_section(UINT8 *buff, INT16 *buf_length, UINT16 pid, UINT8 tb_id, UINT16 spec_id);
INT32 check_service_and_logical(UINT16 ser_id, PROG_INFO *p_info);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __P_SEARCH_H__ */

