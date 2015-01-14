#ifndef __PSI_PMT_H__
#define __PSI_PMT_H__
#include <adr_sys_config.h>

#include <api/libtsi/p_search.h>

enum {
	ES_DTS_EXIST_BIT		= 0,
	ES_CA_EXIST_BIT			= 1,
	ES_ISO639_EXIST_BIT		= 2,
	ES_MPEG4_VIDEO_EXIST_BIT	= 3,
	ES_MPEG4_AUDIO_EXIST_BIT	= 4,
	ES_AVC_VIDEO_EXIST_BIT		= 5,
	ES_TTX_EXIST_BIT		= 6,
	ES_SUB_EXIST_BIT		= 7,
	ES_AC3_EXIST_BIT		= 8,
	ES_AAC_EXIST_BIT		= 9,

#if defined(_MHEG5_V20_ENABLE_)
	ES_CAROUSEL_ID_EXIST_BIT = 10,
	ES_DATA_BROADCASTID_EXIST_BIT = 11,
#endif

#ifdef _SERVICE_MOVE_ENABLE_
	ES_SERVICE_MOVE_EXIST_BIT = 12,
#endif
	ES_EAC3_EXIST_BIT         = 13,		
#ifdef VIDEO_SEAMLESS_SWITCHING
	ES_V_CTRL_EXIST_BIT         = 14,
#endif
#if (defined(_ISDBT_ENABLE_))
	ES_COM_TAG_EXIST_BIT	= 15,
	ES_PR_EXIST_BIT	= 16,
#if (defined(ISDBT_CC)&&ISDBT_CC == 1)
	ES_STREAM_ID_EXIST_BIT	= 17,
	ES_DATA_COMP_EXIST_BIT	= 18,
#endif
#endif
};

enum {
	ES_DTS_EXIST			= 1<<ES_DTS_EXIST_BIT,
	ES_CA_EXIST			= 1<<ES_CA_EXIST_BIT,
	ES_ISO639_EXIST			= 1<<ES_ISO639_EXIST_BIT,
	ES_MPEG4_VIDEO_EXIST		= 1<<ES_MPEG4_VIDEO_EXIST_BIT,
	ES_MPEG4_AUDIO_EXIST		= 1<<ES_MPEG4_AUDIO_EXIST_BIT,
	ES_AVC_VIDEO_EXIST		= 1<<ES_AVC_VIDEO_EXIST_BIT,
	ES_TTX_EXIST			= 1<<ES_TTX_EXIST_BIT,
	ES_SUB_EXIST			= 1<<ES_SUB_EXIST_BIT,
	ES_AC3_EXIST			= 1<<ES_AC3_EXIST_BIT,
	ES_AAC_EXIST			= 1<<ES_AAC_EXIST_BIT,
#ifdef _SERVICE_MOVE_ENABLE_
	ES_SERVICE_MOVE_EXIST = 1<<ES_SERVICE_MOVE_EXIST_BIT,
#endif
	ES_EAC3_EXIST			= 1<<ES_EAC3_EXIST_BIT, 
#if (defined(ISDBT_CC)&&ISDBT_CC == 1)	
	ES_STREAM_ID_EXIST	= 1<<ES_STREAM_ID_EXIST_BIT, 	
	ES_DATA_COMP_EXIST	= 1<<ES_DATA_COMP_EXIST_BIT, 	
#endif

};

#ifdef AUDIO_DESCRIPTION_SUPPORT
enum {	// refer to ISO 639 language descriptor
	AUDIO_TYPE_UNDEFINED 			= 0x00, // Undefined (main audio)
	AUDIO_TYPE_CLEAN_EFFECTS 		= 0x01, // Clean effects
	AUDIO_TYPE_HEARING_IMPAIRED 	= 0x02, // Hearing impaired (clean audio)
	AUDIO_TYPE_VISUAL_IMPAIRED 		= 0x03, // Visual impaired commentary (audio description)
};

#define AUDIO_TYPE_IS_AUD_DESC(a)	((a) == AUDIO_TYPE_VISUAL_IMPAIRED)
#endif

//#if ((SYS_PROJECT_SM&PROJECT_SM_CI)!=0)	
//#define MAX_ES_CA_DESC_LEN		0x40
//#endif
#define ES_INFO_MAX_LANG_SIZE       64  // MAX 21 audio languages in one descriptor
struct pmt_es_info {
	UINT16 pid;
	UINT8 stream_type;
#if (defined(DTG_AUDIO_SELECT) || defined(AUDIO_DESCRIPTION_SUPPORT))
	UINT8 audio_type[2];
	UINT8 track_count;
#endif
	UINT8 lang[ES_INFO_MAX_LANG_SIZE];
	UINT32 stat;
#if (defined(_ISDBT_ENABLE_))
	UINT8 audio_com_tag;
#endif

	UINT8 cas_count;
	UINT16 cas_sysid[P_MAX_CA_NUM];
	UINT16 cas_pid[P_MAX_CA_NUM];
#if 0
	//for subtitle and ttx
	UINT8 subt_lang_num;
	struct t_subt_lang subt_lang[SUBTITLE_LANG_NUM];

	UINT8 ttx_lang_num;
	struct t_ttx_lang init_page[TTX_SUBT_LANG_NUM];
	UINT8 ttx_subt_lang_num;
	struct t_ttx_lang ttx_subt_page[TTX_SUBT_LANG_NUM];
#endif
//#if ((SYS_PROJECT_SM&PROJECT_SM_CI)!=0)	
//	UINT8 ca_len;
//	UINT8 ca_data[MAX_ES_CA_DESC_LEN];
//#endif

#if (defined( _MHEG5_V20_ENABLE_))
	UINT32 carousel_id;

	BOOL got_NB;
	UINT8 NB_version;
	UINT8 boot_info_length;
	UINT8 NB_action;
	UINT8 *boot_info_start_byte;
#endif

#ifdef AUTO_OTA
	UINT32 descriptors_parse_stat;
	PMTSSU_INFO pmt_ssu_info;
#endif
#ifdef VIDEO_SEAMLESS_SWITCHING
	UINT8 video_control; //bit[0-1] not used in spec and here use for exist flag,bit[2-5] encode format,bit[6] sequence end flag, big[7]still picture flag
#endif
};

#ifdef __cplusplus
extern "C"{
#endif

INT32 psi_pmt_parser(UINT8 *pmt, PROG_INFO *p_info, INT32 max_es_nr);

#ifdef AUTO_OTA
INT32 get_ssuinfo_from_pmt(struct program_map *psi_info, UINT16 *pssu_pid, UINT16 pmtpid);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __PSI_PMT_H__ */
