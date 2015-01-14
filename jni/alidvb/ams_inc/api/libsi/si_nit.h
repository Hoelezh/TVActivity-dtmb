#ifndef __SI_NIT_H__
#define __SI_NIT_H__
#include <adr_sys_config.h>
#include <api/libtsi/p_search.h>

#include "si_module.h"
#include "desc_loop_parser.h"

struct nit_service_info {
	UINT16 onid;
	UINT16 tsid;
	UINT16 sid;
	UINT16 lcn;		//MHEG need LCN in NIT
#ifdef SUPPORT_FRANCE_HD
	UINT16 hd_lcn;	
#endif
	
#ifdef BASE_TP_HALF_SCAN_SUPPORT
	UINT8 service_type;
	UINT8 name_len;
	UINT8 *service_name;
#endif
};

#ifdef _ISDBT_ENABLE_
struct nit_ews_info {
	UINT16 sid;
	UINT8 start_end_flag;		
	UINT8 signal_level;
	UINT8 area_code[64];	
};

#endif

struct service_attrib_info {
	UINT16 onid;
	UINT16 tsid;
	UINT16 sid;
	UINT8 nsf;
	UINT8 vsf;
};

#if (defined(AUTO_OTA)||defined(_ISDBT_ENABLE_))	

struct NITSSU_INFO {
	UINT8 linkage_type;//0x09:local, 0x0A:another ts
	UINT8 table_type;//ref to ETSI TS 102 006 Page10, used by linkagetype 0x0A of cur ts, indicate in other TSs,which table in that ts contain linkage desc
	UINT16 des_tsid;
	UINT16 des_orig_netid;
	UINT16 des_serviceid;
	UINT32 OUI;
};

struct NIT_FIRSTLOOP_INFO {
	UINT32* descriptors_parse_stat;
	struct NITSSU_INFO ssu_location_info;
};

#endif

struct nit_section_info {
	UINT16 xp_nr;
	UINT16 nvod_nr;
	
	UINT16 onid;
	UINT16 tsid;
		
	INT32 lp1_nr;
	INT32 lp2_nr;
	struct desc_table *loop1;
	struct desc_table *loop2;

	struct extension_info ext[1];
	
	TP_INFO xp[PSI_MODULE_MAX_TP_NUMBER];
	UINT16 nvod_tsid[PSI_MODULE_MAX_TP_NUMBER];

#if(defined(_SERVICE_ATTRIBUTE_ENABLE_) || defined(_LCN_ENABLE_))
	UINT32 priv_spec;
#endif

#if(defined( _MHEG5_ENABLE_) ||defined(_LCN_ENABLE_) || defined( _MHEG5_V20_ENABLE_) || defined(NETWORK_ID_ENABLE))
	UINT16 net_id;	/* network_id */
	UINT16 s_nr;	//count of s_info
	struct nit_service_info s_info[PSI_MODULE_MAX_NIT_SINFO_NUMBER];
#endif

#if defined(STAR_PROG_SEARCH_NIT_SDT_SUPPORT)
	UINT16 net_id;
	UINT32 switch_code_flag:8;
	UINT32 switch_code_value:24;
#endif

#ifdef BASE_TP_HALF_SCAN_SUPPORT
	UINT32 name_pos;
	UINT8 names[PSI_MODULE_NAME_SIZE];
	UINT16 name_nr;
#endif

#ifdef SUPPORT_FRANCE_HD
UINT16 hd_nr;	
struct nit_service_info hd_info[PSI_MODULE_MAX_NIT_SINFO_NUMBER];
#endif

#ifdef _SERVICE_ATTRIBUTE_ENABLE_	
	UINT16 attrib_nr;
	struct service_attrib_info attrib_info[PSI_MODULE_MAX_NIT_SINFO_NUMBER];
#endif

#ifdef SUPPORT_FRANCE_HD
	UINT8 version_num;
#endif

#if (defined(_ISDBT_ENABLE_))
	UINT8 remote_control_key_id;
UINT16 system_manage_id;
UINT16 ews_nr;	
UINT8 network_sel[PSI_MODULE_MAX_NIT_SINFO_NUMBER];
struct nit_ews_info ews_info[PSI_MODULE_MAX_NIT_SINFO_NUMBER];

#endif

#if (defined(AUTO_OTA)||defined(_ISDBT_ENABLE_))	
	struct NIT_FIRSTLOOP_INFO p_firstloopinfo;
#endif
};

#ifdef __cplusplus
extern "C"{
#endif

INT32 si_nit_parser(UINT8 *nit, INT32 len, struct section_parameter *param);

//to get LCN from NIT
#if(defined( _MHEG5_ENABLE_) ||defined(_LCN_ENABLE_))
INT32 si_on_lcn_desc(UINT8 tag, UINT8 length, UINT8 *data, void *priv);
INT32 si_nit_get_info(struct nit_section_info *nsi, UINT16 onid, UINT16 tsid, 
	PROG_INFO *pg);
#endif

#if(defined(_LCN_ENABLE_) ||defined(_SERVICE_ATTRIBUTE_ENABLE_))
INT32 si_on_priv_spec_desc(UINT8 tag, UINT8 length, UINT8 *data, void *priv);
#endif
#ifdef _SERVICE_ATTRIBUTE_ENABLE_
INT32 si_on_attribute_desc(UINT8 tag, UINT8 length, UINT8 *data, void *priv);
#endif

#ifdef SUPPORT_FRANCE_HD
INT32 si_on_service_list_desc(UINT8 tag, UINT8 length, UINT8 *data, void *priv);
INT32 si_on_HDsimulLCN_desc(UINT8 tag, UINT8 length, UINT8 *data, void *priv);
#endif

#if (defined(_ISDBT_ENABLE_))
INT32 si_on_TS_information_desc(UINT8 tag, UINT8 length, UINT8 *data, void *priv);
#endif

#ifdef AUTO_OTA
INT32 get_otaservice_linkage_from_nit(struct nit_section_info *nit_info, INT8 *plink_exist, UINT16 cur_tsid);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __SI_NIT_H__ */
