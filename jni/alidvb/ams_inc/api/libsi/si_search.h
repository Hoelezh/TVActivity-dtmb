/**********************************************************************
*    Copyright (C)2011 Ali Corporation. All Rights Reserved.
*
*    File:    This file contains SI Program Search functions.
*
*    Description:    Header file in SI Search.
*    History:
*       Date            Author        Version          Reason
*    ============   =============   =========    =================
*
************************************************************************/
#ifndef __SI_SEARCH_H_
#define __SI_SEARCH_H_
#include <api/libdb/db_node.h>
#include <api/libsi/si_parser.h>


/*! @addtogroup ALi中间件
 *  @{
 */

/*! @addtogroup AMSSIS
 *  @{
 */
 
#define MAX_CHAR_LEN	255

//max table count when search program(NIT/PAT/SDT/BAT), except EIT etc.
#define PSI_TABLE_COUNT	                7
#if 0	//only support actual
#define MAX_SDT_OTHER_TS_ID_COUNT       0//AMSSIP_NET_MAX_TS_NUM
#else	//support other
#define MAX_SDT_OTHER_TS_ID_COUNT       (AMSSIP_SDT_MAX_TS_NUM-1)
#endif
#if 0	//only support actual
#define MAX_NIT_OTHER_NETWORK_ID_COUNT  0
#else	//support other
#define MAX_NIT_OTHER_NETWORK_ID_COUNT  (AMSSIP_NIT_MAX_NETWORK_NUM-1)
#endif
#define MAX_BOUQUET_ID_COUNT          AMSSIP_BAT_MAX_BQT_NUM
#define MAX_HITMAP_FLAGS_COUNT      (PSI_TABLE_COUNT+MAX_SDT_OTHER_TS_ID_COUNT+MAX_NIT_OTHER_NETWORK_ID_COUNT+MAX_BOUQUET_ID_COUNT)

//! @struct amssearch_compability_t
//! @brief ams search compability。
typedef struct
{
    char compability[MAX_CHAR_LEN+1];	//!< "PAT|PMT|SDT actual|SDT other|NIT actual|NIT other|BAT", no CAT/EIT
    UINT32 buffer_size;	//!< work space buffer size needed

    UINT32 tp_count;		//!< max tp count can parse & store from NIT
    UINT32 ts_count;		//!< max ts count can parse & store from SDT
    UINT32 bouquet_count;	//!< max bouquet count can parse & store from BAT
    UINT32 program_count;	//!< max program count can parse & store from SDT/PAT/PMT

    UINT32 obj_count;		//!< search object count

} amssearch_compability_t;

//! @enum amssearch_table_e
//! @brief psi/si search table。
typedef enum
{
	SI_SEARCH_PAT				= 0,
	SI_SEARCH_SDT_ACTUAL		= 1,
	SI_SEARCH_SDT_OTHER			= 2,
	SI_SEARCH_BAT				= 3,
	SI_SEARCH_NIT_ACTUAL		= 4,
	SI_SEARCH_NIT_OTHER			= 5,
	SI_SEARCH_PMT				= 6,
	SI_SEARCH_TABLE_NUM

} amssearch_table_e;

//! @enum amssearch_table_mask_e
//! @brief psi/si table mask。
typedef enum
{
	SI_SEARCH_PAT_MASK		    = (1<<SI_SEARCH_PAT),
	SI_SEARCH_SDT_ACTUAL_MASK	= (1<<SI_SEARCH_SDT_ACTUAL),
	SI_SEARCH_SDT_OTHER_MASK	= (1<<SI_SEARCH_SDT_OTHER),
	SI_SEARCH_BAT_MASK		    = (1<<SI_SEARCH_BAT),
	SI_SEARCH_NIT_ACTUAL_MASK	= (1<<SI_SEARCH_NIT_ACTUAL),
	SI_SEARCH_NIT_OTHER_MASK	= (1<<SI_SEARCH_NIT_OTHER),
	SI_SEARCH_PMT_MASK		    = (1<<SI_SEARCH_PMT)

} amssearch_table_mask_e;

//! @enum amssearch_notify_e
//! @brief SI Search Notification MSG type。
typedef enum
{
	SI_NOTIFY_PROGRESS,		//!< AS progress: 0-100

	SI_NOTIFY_TP_TUNING,	//!< tuned to this tp for program search
	SI_NOTIFY_TP_LOCK,		//!< tp lock status
	SI_NOTIFY_TP_ADDED,		//!< if lock, add the tp into db
	SI_NOTIFY_TP_FULL,		//!< DB TP full, can not store any TP

	SI_NOTIFY_TUNE_NEXT,	//!< tune to next tp(SI Search for AS only, not for AP)

    SI_NOTIFY_PMT,
	SI_NOTIFY_SDT,
	SI_NOTIFY_NIT,
	SI_NOTIFY_BAT,

	SI_NOTIFY_PROGRAM,			//!< program got, notify AP if need store into db or not.
	SI_NOTIFY_PROGRAM_ADDED,	//!< stored into db & notify AP.
	SI_NOTIFY_PROGRAM_FULL,			//!< DB stofull, can not store any program

	SI_NOTIFY_ASCOMPLETE,		//!< AS complete
	SI_NOTIFY_ASSTOP,               //!< user stop as
	SI_NOTIFY_ERROR,                 //!< ERROR Message

} amssearch_notify_e;

//SI Search Notification callback
/*  SDT_SECTION_INFO    NIT_SECTION_INFO    BAT_SECTION_INFO
*   amssip_sdt_info_t   amssip_nit_info_t   amssip_bat_info_t
*/
typedef INT32(* amssearch_notify_t)(HANDLE handle, amssearch_notify_e type, void *param);

//! @struct amssearch_result_t
//! @brief Result of the SI Search, all Tables got. Need export to outside。
typedef struct
{
    P_NODE program[3];	//!< see psi_adjust_node(), when save program, need compare with DB P_NODE
    amssip_pat_info_t pat;
    amssip_sdt_info_t sdt;
    amssip_bat_info_t bat;
    amssip_nit_info_t nit;
    amssip_pmt_info_t pmt[AMSSIP_TP_MAX_PROG_NUM];
    UINT16 pmt_count; 

} amssearch_result_t;

//! @struct amssearh_store_info_t
//! @brief Search store info。
typedef struct
{
    UINT32 sat_id;
    UINT32 tp_id; 
    amssearch_notify_t search_callback;
}amssearch_store_info_t;

typedef INT32(* amssearch_store_program_t)(HANDLE handle, amssearch_result_t *info, amssearch_store_info_t *cfg);

//! @struct amssearh_spec_section_info_t
//! @brief Search section info。
typedef struct
{
    UINT16 pid;
    UINT8 table_id;    
    UINT16 buf_len; 
}amssearch_spec_section_info_t;

typedef INT32(* amssearch_get_table_info_t)(HANDLE handle, amssearch_table_e table, amssearch_spec_section_info_t *table_spec);

//! @enum amssearch_nit_method_e
//! @brief NIT search method。
typedef enum
{
    NIT_METHOD_INCLUED_MAIN_FREQ = 0, //main frequence + nit
    NIT_METHOD_EXCLUED_MAIN_FREQ = 1, //nit only
    NIT_METHOD_NONE = 2               //no nit
    
}amssearch_nit_method_e;

//! @struct amssearch_config_t
//! @brief SI Search configuration for work space, table, timeout。
typedef struct
{
    UINT32 dmx_handle;
    UINT32 sat_id;
    UINT32 tp_id;

    UINT8 *workspace;
    UINT32 size;

    UINT32 table_bitmap;		//!< see enum amssearch_table_mask_e
    amssearch_nit_method_e nit_method; 
    UINT32 timeout[SI_SEARCH_TABLE_NUM];	//!< timeout of each table, index: see enum amssearch_table_mask_e

    sip_descripter_vector_t sdt_priv_desc[AMSSIP_PRIV_DESC_MAX_CNT]; //!< priv descriptor config
    UINT8 sdt_desc_cnt;

    sip_descripter_vector_t bat_priv_desc[AMSSIP_PRIV_DESC_MAX_CNT];
    UINT8 bat_desc_cnt;

    sip_descripter_vector_t nit_priv_desc[AMSSIP_PRIV_DESC_MAX_CNT];
    UINT8 nit_desc_cnt;
    
    sip_descripter_vector_t pmt_priv_desc[AMSSIP_PRIV_DESC_MAX_CNT];
    UINT8 pmt_desc_cnt;

	//TS id for SDT other
	UINT32 ts_id_cnt;
	UINT16 ts_id[MAX_SDT_OTHER_TS_ID_COUNT];

	//network id for NIT other
	UINT32 network_id_cnt;
	UINT16 network_id[MAX_NIT_OTHER_NETWORK_ID_COUNT];

	//bouquet id for BAT
	UINT32 bouquet_id_cnt;
	UINT16 bouquet_id[MAX_BOUQUET_ID_COUNT];

    amssearch_notify_t search_callback;
	amssearch_store_program_t store_callback;
	amssearch_get_table_info_t get_table_info;

    UINT8 ignore_crc;
} amssearch_config_t;

extern amsret_e amssearch_err_code;

/*!
@brief 获取SI search的配置信息。
@details 获取SI search的配置信息。
@param[in] pcom amssearch_compability struct。
@retval SUCCESS 总是成功
*/
INT32 amssearch_get_compability(amssearch_compability_t *pcom);
HANDLE amssearch_alloc_obj(void);
INT32 amssearch_config(HANDLE handle, amssearch_config_t *pcfg);

//specific si table's private parms
INT32 amssearch_set_table_info(HANDLE handle, amssearch_table_e table, amssearch_spec_section_info_t *table_spec);

INT32 amssearch_start(HANDLE handle);
INT32 amssearch_stop(HANDLE handle);
INT32 amssearch_free_obj(HANDLE handle);

void sat2antenna(S_NODE *sat, struct ft_antenna *antenna);
#endif

