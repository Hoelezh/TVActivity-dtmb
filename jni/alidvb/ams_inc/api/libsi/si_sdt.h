/*
 * SI_SDT.H
 *
 * SI SDT parser declaration file
 *
 * 1. 2006.07.10	Zhengdao Li	0.01		Initialize.
 */
#ifndef __SI_SDT_H__
#define __SI_SDT_H__
#include <adr_sys_config.h>

#include "si_module.h"
#if (SYS_PROJECT_FE == PROJECT_FE_DVBC)	
#include <api/libsi/lib_nvod.h>


struct sdt_private_data{
	UINT16 logic_chan_number;
	UINT16 reserve1;
	UINT8 volumn_set;
	UINT8 audio_track;
	UINT8 reserve2;
	UINT8 reserve3;
};

#endif

#if(defined(SUPPORT_MTILINGUAL_SERVICE_NAME))
#define MAX_MTL_CNT      10
#define MAX_MTL_NAME_LEN	512

struct mtl_service_name_info{
	//UINT32 ISO_639_language_code:24;
	UINT8 ISO_639_language_code[3];
	UINT8 service_provider_name_length;
	UINT8 *service_provider_name;
	UINT8 service_name_length;
	UINT8 *service_name;
};

struct mtl_service_data{
	UINT16 program_number;	
	UINT8 mult_name_count;
	struct mtl_service_name_info mtl_name[MAX_MTL_CNT];
	INT32 name_pos;
	UINT8 names[MAX_MTL_NAME_LEN];
};
#endif

struct sdt_section_info {
	UINT16 sid;
	UINT16 t_s_id;
	UINT16 onid;

	UINT8 service_type;
	UINT8 sdt_version;

	INT32 max_name_len;
	INT32 name_pos;

	INT16 max_sd_nr;
	INT16 sd_nr;

	INT16 max_nd_nr;
	INT16 nd_nr;

	INT16 max_lcn_nr;
	INT16 lcn_nr;
	
	struct extension_info ext[1];
	UINT8 names[PSI_MODULE_NAME_SIZE];	
	UINT8 service_name[PSI_SERVICE_NAME_SIZE];
	UINT8 service_provider_name[PSI_SERVICE_NAME_SIZE];
	
	struct service_data sd[PSI_MODULE_MAX_PROGRAM_NUMBER];
#if (SYS_PROJECT_FE == PROJECT_FE_DVBC)	
	struct nvod_sdt_info nvod;
	
	struct sdt_private_data private[PSI_MODULE_MAX_PROGRAM_NUMBER];
#elif ((SYS_PROJECT_FE == PROJECT_FE_DVBT)&&(defined(STAR_PROG_SEARCH_NIT_SDT_SUPPORT)))
	UINT8 media_service_flag;
	UINT8 media_service_code[STAR_SDT_SERVICE_CODE_LEN+1];
#endif
#if(defined(SUPPORT_MTILINGUAL_SERVICE_NAME))
	struct mtl_service_data mtl_s_data[PSI_MODULE_MAX_PROGRAM_NUMBER];
#endif

};


#ifdef SUPPORT_FRANCE_HD
struct link_descriptor
{
	UINT8 transport_stream_id[2];
	UINT8 original_network_id[2];
	UINT8 service_id[2];
	UINT8 link_type;
	UINT8 private_data[0];
};

struct link_s_info
{
	UINT16 transport_stream_id;
	UINT16 original_network_id;
	UINT16 service_id;	
	UINT8* private_data;
	UINT8 private_len;
};
#endif

#ifdef DYNAMIC_SERVICE_SUPPORT
struct sdt_service_info
{
	UINT16 service_id;
};

struct sdt_info
{
	UINT16 t_s_id;
	UINT16 onid;
	UINT8  sdt_version;
	UINT8  service_cnt;
	struct sdt_service_info ssi[PSI_MODULE_MAX_PROGRAM_NUMBER];
};
#endif

#ifdef __cplusplus
extern "C"{
#endif

INT32 si_sdt_parser(UINT8 *sdt, INT32 len, struct section_parameter *param);

INT32 psi_get_service(struct sdt_section_info *info,
	UINT16 program_number, 	UINT8 *service_name, UINT8 *provider_name);

#if ((SYS_PROJECT_FE == PROJECT_FE_DVBT)&&defined(STAR_PROG_SEARCH_NIT_SDT_SUPPORT))
INT32 psi_get_star_service_code(struct sdt_section_info *info, UINT16 program_number, UINT8 *service_flag);
#endif

#if 0//(SYS_PROJECT == PROJECT_HDTV)
INT32 si_sdt_get_info(struct sdt_section_info *info, PROG_INFO *pg);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __SI_SDT_H__ */
