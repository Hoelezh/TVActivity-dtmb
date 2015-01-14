/**********************************************************************
*    Copyright (C)2011 Ali Corporation. All Rights Reserved.
*
*    File:    si_parser.h
*
*    Description:    Header file in XXX.
*    History:
*       Date            Athor        Version          Reason
*    ============   =============   =========    =================
*     1. Oct.30.2011   Guoping.Chen	Ver 0.1			Creat file
*     2. Dec.05.2011   Linge.Chen        Ver 0.2                  Review file
************************************************************************/


#ifndef __SI_PARSER_H_
#define __SI_PARSER_H_

#include <api/libtsi/si_descriptor.h>


/*! @addtogroup ALi中间件
 *  @{
 */

/*! @addtogroup AMSSIP
 *  @{
 */

//#define SI_PARSER_DEBUG

//! @enum amssip_front_type_e
//! @brief 定义ts前端类型。DVB-C使用AMSSIP_CABLE类型。
typedef enum
{
	AMSSIP_CABLE			= 0,
	AMSSIP_SATTLITE			= 1,
	AMSSIP_TERRITIAL		= 2,
}amssip_front_type_e;

//! @enum amspmt_es_type_e
//! @brief 定义PMT表中的es类型。
typedef enum 
{
	MPEG1_VIDEO_STREAM				= 0x01,
	MPEG2_VIDEO_STREAM				= 0x02,
	MPEG1_AUDIO_STREAM				= 0x03,
	MPEG2_AUDIO_STREAM				= 0x04,
	PRIVATE_DATA_STREAM				= 0x06,

	ISO13818_6_TYPE_A				= 0x0a,
	ISO13818_6_TYPE_B				= 0x0b,
	ISO13818_6_TYPE_C				= 0x0c,
	ISO13818_6_TYPE_D				= 0x0d,

    MPEG_ADTS_AAC_STREAM            = 0x0F,//!< ADTS_AAC
	MPEG4_VIDEO_STREAM				= 0x10, //!< (ISO/IEC 14496-2 Visual)
	MPEG_AAC_STREAM					= 0x11, //!< (ISO/IEC 14496-3 Audio withe LATM transport syntax)
	H264_VIDEO_STREAM				= 0x1b, //!< (AVC video as define in ITU Rec. H.264 |ISO/IEC 14496-10 Video)
	DC_II_VIDEO_STREAM				= 0x80,
	AC3_AUDIO_STREAM				= 0X81,

	AVS_VIDEO_STREAM				= 0x42, //AVS Video
	AVS_AUDIO_STREAM				= 0x43, //AVS Audio	

	//for private stream
	PRIVATE_EAC3_AUDIO				= (PRIVATE_DATA_STREAM<<8)|ENHANCED_AC3_DESCRIPTOR,	//!< 0x0106,
	PRIVATE_AC3_AUDIO				= (PRIVATE_DATA_STREAM<<8)|AC3_DESCRIPTOR,	//!< 0x8106,
}amspmt_es_type_e;

//type define for descripter parser function
typedef INT32 (*amssip_descripter_t)(UINT8 tag, UINT8 len, UINT8* buf, UINT32 param1, UINT32 param2);

//! @struct sip_descripter_vector_t
//! @brief 定义私有描述子相关结构。
typedef struct
{
	UINT8 tag;		        //!< descripter tag
	UINT32 bit;
	amssip_descripter_t func;	//!< 定义私有描述符解析函数类型。
	UINT8 loop;
	UINT8* buffer;
	UINT32 buf_size;
}sip_descripter_vector_t;

//! @struct amssip_pat_info_t
//! @brief 定义PAT表信息存储结构。
typedef struct
{
	UINT16 ts_id;
	UINT16 nit_pid;
	UINT32 prog_count;
	UINT16 prog_number[AMSSIP_TP_MAX_PROG_NUM];
	UINT16 pmt_pid[AMSSIP_TP_MAX_PROG_NUM];
	UINT8  version_number;
	UINT8  last_sec_numb;
}amssip_pat_info_t;

//! @struct amssip_cat_info_t
//! @brief 定义CAT表信息存储结构。
typedef struct
{
	UINT8 emm_count;
	UINT16 ca_sysid [AMSSIP_CAT_EMM_MAX_CNT];
	UINT16 emm_pid [AMSSIP_CAT_EMM_MAX_CNT];
	UINT8  version_number;
	UINT8  last_sec_numb;
	sip_descripter_vector_t priv_desc[AMSSIP_PRIV_DESC_MAX_CNT];
	UINT8 desc_cnt;
}amssip_cat_info_t;

//! @struct amssip_ca_info_t
//! @brief 定义PMT表信息存储结构。只包含一个子表的信息。其中，ca_pid为ecm pid。
typedef struct
{
	UINT16 ca_system_id;  //!< CA system id
	UINT16 ca_pid;        //!< ECM PID
}amssip_ca_info_t;

//! @struct amssip_pmt_info_t
//! @brief store PMT parser
typedef struct
{
	UINT16	prog_number; //!< 节目program number
	UINT8	audio_count; //!< 节目包含的音频流个数
	UINT16  audio_pid[AMSSIP_PMT_MAX_AUDIO_NUM]; //!< 节目包含的音频流PID
	UINT16	audio_stream_type[AMSSIP_PMT_MAX_AUDIO_NUM]; //!< 节目包含的各音频流类型
	UINT8	audio_lang[AMSSIP_PMT_MAX_AUDIO_NUM][AMSSIP_PMT_AUDIO_639LANG_MAX_CNT][3]; //!< 节目各音频流的多语言伴音
	UINT16	video_pid; //!< 节目的视频PID
	UINT16 video_stream_type; //!< 节目的视频流类型
	amssip_ca_info_t ca_info[AMSSIP_PMT_MAX_CA_NUM]; //!< 节目加密信息 
	UINT8 ca_count; //!< 节目同密CA个数
	UINT16 pcr_pid; //!< PCR PID
	//av以外的es stream信息
	UINT16 es_pid_cnt; //!< ES个数
	UINT16 es_pid[AMSSIP_PMT_MAX_ES_CNT]; //!< ES PID
	UINT8 es_type[AMSSIP_PMT_MAX_ES_CNT]; //!< ES类型
	UINT8  version_number; //!< version number
	UINT8  last_sec_numb; //!< last section number
	sip_descripter_vector_t priv_desc[AMSSIP_PRIV_DESC_MAX_CNT]; //!< PMT私有描述子信息
	UINT8 desc_cnt;
}amssip_pmt_info_t;

//! @union amssip_ts_info_t
//! @brief 定义NIT表信息存储结构。包含全部子表的信息。其中，network_service_param记录的是NIT表中携带的SERVICE_LIST_DESCRIPTOR描述子信息(也可能没有)。
typedef union
{
	struct 
    {
        UINT8 type;  //!< amssip_front_type_e
    }common;
    struct
    {
        UINT8 type;
		UINT32 frq;
		UINT8 fec_outer;
        UINT8 modulation;
        UINT32 sym;
		UINT8 fec_inner;
    }c_info;
    struct //reserve for -T
    {
        UINT8 type;
		UINT32 frq;
    }t_info;
	struct //reserve for -S
    {
        UINT8 type;
		UINT32 frq;
    }s_info;
}amssip_ts_info_t;

//! @struct amssip_nit_service_t
//! @brief NIT service
typedef struct
{
	UINT16 org_network_id; //!< 原始网络ID
	UINT16 ts_id;          //!< TS ID
	UINT16 service_id;     //!< Service ID
	UINT8  service_type;   //!< Service Type
}amssip_nit_service_t;

//! @struct amssip_netwrok_ts_param_t
//! @brief Network PMT parser
typedef struct
{
	UINT32 ts_cnt;                                  //!< 网络中的TS个数
	UINT16 ts_id[AMSSIP_NIT_MAX_TS_NUM];            //!< TS ID
	UINT16 org_network_id[AMSSIP_NIT_MAX_TS_NUM];   //!< TS的原始网络ID
	amssip_ts_info_t ts_info[AMSSIP_NIT_MAX_TS_NUM];//!< TS的前端配置信息	
}amssip_netwrok_ts_param_t;

//! @struct amssip_network_service_param_t
//! @brief Network serviceparameter
typedef struct
{
	amssip_nit_service_t nit_service[AMSSIP_MAX_PROG_NUM];//!< 网络中的service，由service_list_descriptor携带 
	UINT16 nit_service_cnt;                               //!< 网络中的service个数
}amssip_network_service_param_t;

//! @struct amssip_nit_info_t
//! @brief store NIT parser
typedef struct
{
	//Network
	UINT32 cur_network_id; //!< 现行网络ID
	UINT32 network_cnt; //!< 网络个数
	UINT16 network_id[AMSSIP_NIT_MAX_NETWORK_NUM]; //!< 网络ID
	UINT8 network_name[AMSSIP_NIT_MAX_NETWORK_NUM][AMSSIP_NET_NAME_MAX_LEN]; //!< 网络名称
	UINT8  version_number[AMSSIP_NIT_MAX_NETWORK_NUM]; //!< version number 
	UINT8  last_sec_numb[AMSSIP_NIT_MAX_NETWORK_NUM]; //!< last section number 
	//TS of network
	amssip_netwrok_ts_param_t network_ts_param[AMSSIP_NIT_MAX_NETWORK_NUM]; //!< 网络中的TS信息
	//Service of network
	amssip_network_service_param_t network_service_param[AMSSIP_NIT_MAX_NETWORK_NUM]; //!< 网络中的Service信息
	sip_descripter_vector_t priv_desc[AMSSIP_PRIV_DESC_MAX_CNT]; //!< NIT私有描述子信息
	UINT8 desc_cnt;
}amssip_nit_info_t;

//! @struct amssip_bat_service_list_t
//! @brief 定义BAT表信息存储结构。包含全部子表的信息。
typedef struct
{
	UINT16 service_cnt; //!< 分组节目个数
	UINT16 ts_id[AMSSIP_BAT_BQT_MAX_PROG_NUM]; //!< 节目所在的TS ID
	UINT16 org_network_id[AMSSIP_BAT_BQT_MAX_PROG_NUM]; //!< 节目所在的原始网络ID
	UINT16 service_id[AMSSIP_BAT_BQT_MAX_PROG_NUM]; //!< 节目的Service ID
	UINT8 service_type[AMSSIP_BAT_BQT_MAX_PROG_NUM]; //!< 节目的Service Type
}amssip_bat_service_list_t;

//structure for store BAT parser
//! @struct amssip_bat_info_t
//! @brief store BAT parser。
typedef struct
{
	//Bouquet
	UINT32 bouquet_cnt; //!< 分组个数
	UINT16 bouquet_id[AMSSIP_BAT_MAX_BQT_NUM]; //!< 分组的Bouquet ID
	UINT16 bouquet_name[AMSSIP_BAT_MAX_BQT_NUM][AMSSIP_BQT_NAME_MAX_LEN]; //!< 分组名称
	UINT8  version_number[AMSSIP_BAT_MAX_BQT_NUM]; //!< version number
	UINT8  last_sec_numb[AMSSIP_BAT_MAX_BQT_NUM]; //!< last section number
	//Service
	amssip_bat_service_list_t service[AMSSIP_BAT_MAX_BQT_NUM]; //!< 分组的节目列表
	sip_descripter_vector_t priv_desc[AMSSIP_PRIV_DESC_MAX_CNT];
	UINT8 desc_cnt;
}amssip_bat_info_t;

//! @struct amssip_sdt_ref_service_t
//! @brief sdt ref service
typedef struct
{
	UINT8 ref_cnt;
	UINT16 ts_id[AMSSIP_SDT_MAX_REF_NUM];
	UINT16 org_network_id[AMSSIP_SDT_MAX_REF_NUM];
	UINT16 service_id[AMSSIP_SDT_MAX_REF_NUM];
}amssip_sdt_ref_service_t;

//! @struct amssip_sdt_service_t
//! @brief 定义SDT表信息存储结构。包含一个ts全部子表的信息。其中，free_addr和char_buff为SiParser内部使用域，用户禁止使用。对于NVOD参考业务，SiParser忽略其nvod_reference_descriptor；对于马赛克业务，也不分析其mosaic_descriptor 。
typedef struct
{
	UINT16 service_cnt; //!< Service个数
	UINT16 service_id[AMSSIP_TP_MAX_PROG_NUM]; //!< Service ID
	UINT16 ref_service_id[AMSSIP_TP_MAX_PROG_NUM];//!< 时移业务所属的参考业务 ID.  (NVOD timeshift service descriptor)
//NOVD need or not NVOD_reference_descriptor???
//	amssip_sdt_ref_service_t refed_service[AMSSIP_TP_MAX_PROG_NUM];//NVOD_reference_descriptor
	UINT8 service_type[AMSSIP_TP_MAX_PROG_NUM]; //!< Service Type
	UINT8 name_len[AMSSIP_TP_MAX_PROG_NUM]; //!< 节目名长度
	UINT8 *service_name[AMSSIP_TP_MAX_PROG_NUM]; //!< 节目名称
	UINT8 provider_name_len[AMSSIP_TP_MAX_PROG_NUM]; //!< 节目供应商名称长度
	UINT8 *provider_name[AMSSIP_TP_MAX_PROG_NUM]; //!< 节目供应商名称
}amssip_sdt_service_t;

//! @struct amssip_sdt_info_t
//! @brief store SDT parser
typedef struct
{
    //TS
	UINT16 ts_cnt; //!< TS个数。 Actual + Other表
	UINT16 cur_ts_id; //!< 现行TS ID
	UINT16 ts_id[AMSSIP_SDT_MAX_TS_NUM]; //!< 全部子表TS ID
	UINT16 org_network_id[AMSSIP_SDT_MAX_TS_NUM]; //!< 全部子表原始网络ID
	UINT8  version_number[AMSSIP_SDT_MAX_TS_NUM]; //!< version number
	UINT8  last_sec_numb[AMSSIP_SDT_MAX_TS_NUM]; //!< last section number
    //Service
	amssip_sdt_service_t service[AMSSIP_SDT_MAX_TS_NUM]; //!< Service信息
	UINT32 free_addr; //!< 空闲的节目名存储地址。Parser内部使用。
	UINT8 char_buff[AMSSIP_SDT_NAME_BUF_LEN]; //!< 节目名称存储地址。Parser内部使用。
	sip_descripter_vector_t priv_desc[AMSSIP_PRIV_DESC_MAX_CNT];
	UINT8 desc_cnt;
}amssip_sdt_info_t;

//! @struct amssip_pmt_es_info
//! @brief 定义PMT子表上下文信息结构。用以在分析PMT携带的描述子时传递section上下文信息。
typedef struct
{
	UINT8 cnt; //!< 多语言伴音个数
	UINT8 lan_639[AMSSIP_PMT_AUDIO_639LANG_MAX_CNT][3]; //!< 多语言伴音描述信息
	UINT8 audio_type[AMSSIP_PMT_AUDIO_639LANG_MAX_CNT]; //!< 伴音类型
}amssip_pmt_es_info;

//! @struct amssip_pmt_context_t
//! @brief PMT context informateion for descripter parser
typedef struct
{
	UINT16	prog_number; //!< 节目program number
	UINT8 version_num; //!< version number
	UINT8 stream_type; //!< ES 类型  (for loop2 descripter)
	UINT16 es_pid; //!< ES PID   (for loop2 descripter)
	amssip_pmt_es_info es; //!< ES 伴音信息
	UINT8 loop; //!< 描述子所在的loop层级
}amssip_pmt_context_t;

//! @struct amssip_nit_context_t
//! @brief 定义NIT子表上下文信息结构。用以在分析NIT携带的描述子时传递section上下文信息。
typedef struct
{
	UINT8 table_id;  //!< Table ID
	UINT16 network_id; //!< Network ID
	UINT16 ts_id; //!< TS ID (给loop2描述子分析使用)
	UINT16 org_network_id; //!< 原始网络ID (给loop2描述子分析使用)
	UINT8 version_num;//!< 版本号
	UINT8 loop; //!< 描述子所在的loop层级
}amssip_nit_context_t;

//! @struct amssip_bat_context_t
//! @brief 定义BAT子表上下文信息结构。用以在分析BAT携带的描述子时传递section上下文信息。
typedef struct
{
	UINT16 table_id; //!< Table ID
	UINT8 version_num; //!< 版本号
	UINT16 bouquet_id; //!< 分组Bouquet ID
	UINT16 ts_id; //!< TS ID (给loop2描述子分析使用)
	UINT16 org_network_id; //!< 原始网络ID (给loop2描述子分析使用)
	UINT8 loop; //!< 描述子所在的loop层级
}amssip_bat_context_t;

//! @struct amssip_sdt_context_t
//! @brief 定义SDT子表上下文信息结构。用以在分析SDT携带的描述子时传递section上下文信息。
typedef struct
{
	UINT8 table_id; //!< Table ID
	UINT16 ts_id; //!< TS ID
	UINT16 org_network_id; //!< 原始网络ID (给loop2描述子分析使用)
	UINT16 service_id;  //!< Service ID (给loop2描述子分析使用)
	UINT8 version_num; //!< 版本号
	UINT8 loop; //!< 描述子所在的loop层级
}amssip_sdt_context_t;


/*!
@brief PAT子表section分析。
@details PAT子表section分析，分析结果存储在info结构中。
@param[in] buf 待分析的PAT section buffer。
@param[in] buf_len 待分析的PAT section buffer长度(byte)。
@param[out] info 用来存放分析结果的buffer。
@retval SUCCESS 总是成功
@retval 其它值 失败，参数错误，节目个数超出支持的最大个数等。
*/
INT32 amssip_pat_section(UINT8 *buf, UINT32 buf_len,  amssip_pat_info_t *info);

/*!
@brief CAT子表section分析。
@details CAT表section分析，分析结果存储在info指向的结构中。
@param[in] buf 待分析的CAT section buffer。
@param[in] buf_len 待分析的CAT section buffer长度(byte)。
@param[in/out] info 用来存放分析结果的buffer。如果要分析私有描述子，那么info中的priv_desc及desc_cnt域须正确填写，请参考sip_descripter_vector_t定义说明和Sample代码。
@retval SUCCESS 总是成功
@retval 其它值 失败，参数错误，节目个数超出支持的最大个数等。
*/
INT32 amssip_cat_section(UINT8 *buf, UINT32 buf_len,  amssip_cat_info_t *info);

/*!
@brief PMT子表section分析。
@details PMT子表section分析，分析结果存储在info结构中。
@param[in] buf 待分析的CAT section buffer。
@param[in] buf_len 待分析的CAT section buffer长度(byte)。
@param[in/out] 用来存放分析结果的buffer。如果要分析私有描述子，那么info中的priv_desc及desc_cnt域须正确填写，请参考sip_descripter_vector_t定义说明和Sample代码。
@retval SUCCESS 总是成功
@retval 其它值 失败，参数错误，节目个数超出支持的最大个数等。
*/
INT32 amssip_pmt_section(UINT8 *buf, UINT32 buf_len,  amssip_pmt_info_t *info);

/*!
@brief NIT子表section分析。
@details NIT子表section分析，分析结果存储在info结构中。
@param[in] buf 待分析的CAT section buffer。
@param[in] buf_len 待分析的CAT section buffer长度(byte)。
@param[in/out] info 用来存放分析结果的buffer。如果要分析私有描述子，那么info中的priv_desc及desc_cnt域须正确填写，请参考sip_descripter_vector_t定义说明和Sample代码。
@retval SUCCESS 总是成功
@retval 其它值 失败，参数错误，节目个数超出支持的最大个数等。
*/
INT32 amssip_nit_section(UINT8 *buf, UINT32 buf_len,  amssip_nit_info_t *info);

/*!
@brief BAT子表section分析。
@details BAT子表section分析，分析结果存储在info结构中。
@param[in] buf 待分析的CAT section buffer。
@param[in] buf_len 待分析的CAT section buffer长度(byte)。
@param[in/out] info 用来存放分析结果的buffer。如果要分析私有描述子，那么info中的priv_desc及desc_cnt域须正确填写，请参考sip_descripter_vector_t定义说明和Sample代码。
@retval SUCCESS 总是成功
@retval 其它值 失败，参数错误，节目个数超出支持的最大个数等。
*/
INT32 amssip_bat_section(UINT8 *buf, UINT32 buf_len,  amssip_bat_info_t *info);

/*!
@brief SDT子表section分析。
@details SDT子表section分析，分析结果存储在info结构中。
@param[in] buf 待分析的CAT section buffer。
@param[in] buf_len 待分析的CAT section buffer长度(byte)。
@param[in/out] info 用来存放分析结果的buffer。如果要分析私有描述子，那么info中的priv_desc及desc_cnt域须正确填写，请参考sip_descripter_vector_t定义说明和Sample代码。
@retval SUCCESS 总是成功
@retval 其它值 失败，参数错误，节目个数超出支持的最大个数等。
*/
INT32 amssip_sdt_section(UINT8 *buf, UINT32 buf_len,  amssip_sdt_info_t *info);

/*!
 * @}
 */

/*!
@}
*/

#endif

