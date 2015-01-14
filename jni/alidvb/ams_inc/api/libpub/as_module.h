/*
 * AS_MODULE.H
 *
 * autoscan module internal structure definition file.
 *
 * revision history
 * 1. 2006.07.08	Zhengdao Li	0.01	Initialization.
 */
#ifndef __AS_MODULE_H__
#define __AS_MODULE_H__
#include <adr_sys_config.h>

#include <hld/adr_hld_dev.h>
#include <hld/dmx/adr_dmx_dev.h>
#include <hld/nim/adr_nim_dev.h>
#include <hld/nim/adr_nim.h>
#include <api/libtsi/db_3l.h>

#include <api/libpub/lib_frontend.h>
#include <api/libpub/lib_as.h>

enum
{
	AS_MODULE_MAX_P_NUM		= 256,
	AS_MODULE_MAX_T_NUM		= 1024,
	AS_MODULE_MAX_S_NUM		= 256,
	AS_MODULE_SLEEP_SLICE	= 50,
	AS_TUNE_TIMEOUT_S			= 350,
	AS_TUNE_TIMEOUT_C			= 1000,
	AS_MIN_SAT_DL_FREQUENCY	= 2000,
	AS_MAX_SAT_DL_FREQUENCY	= 16000,
	AS_MIN_CAB_FREQUENCY		= 4800,
	AS_MAX_CAB_FREQUENCY	= 86200,
};

enum
{
	ATP_TYPE_DBASE,		/* database based */
	ATP_TYPE_STEP,			/* step based*/
};

struct as_tuning_param
{
	UINT32 start;
	UINT32 limit;
	UINT32 step;
	UINT32 pos;
	UINT32 tp_id;
	UINT32 nit_enable;
	UINT32 timeout;
	BOOL finish;
 	UINT8 ft_type;//front end type in lib_frontend.h       
#if (SYS_PROJECT_FE == PROJECT_FE_DVBT) || (SYS_PROJECT_FE == PROJECT_FE_ISDBT)
 	UINT32 band_count;
 	UINT32 cur_band;
	Band_param	*band_group_param;//[MAX_BAND_COUNT];	/*pointer array to store the parameters of a group of continuous bands.*/
#endif
};


#if 0
struct as_module_info
{
	UINT32 stop_scan_signal;	/* stop signal */
	struct dmx_device *dmx;
	struct nim_device *nim;
	S_NODE cur_sat;
	T_NODE cur_tp;
	T_NODE xp;
	struct as_service_param param;

	//DVB-S nim operation related section.
	BOOL voltage_ctrl;
	UINT32 polar;
	UINT32 dual_LNB;
	struct ft_antenna antenna;
	union ft_xpond xponder;
	struct NIM_Auto_Scan nim_para;
	
	struct as_tuning_param atp;
	INT32 tp_nr;
	INT32 sat_nr;
		
	UINT32 tp_id[AS_MODULE_MAX_T_NUM];
	UINT8 tp_nit[AS_MODULE_MAX_T_NUM];
	UINT16 sat_id[AS_MODULE_MAX_S_NUM];
};
#else
struct as_module_info
{
	amsas_service_param as_param;
	UINT32 time_out; //tuning timeout
	UINT16 cur_band;
	UINT32 cur_freq;
	UINT32 tp_cnt; //total tp
	INT32   cur_tp; //current scaning tp
	UINT8   reset_flag;  //reset the band parm if necessary when nit got

#if 0
	S_NODE cur_sat;
	T_NODE cur_tp;
	T_NODE xp;
	struct as_service_param param;
	BOOL voltage_ctrl;
	UINT32 polar;
	UINT32 dual_LNB;
	struct ft_antenna antenna;
	union ft_xpond xponder;
	struct as_tuning_param atp;
	INT32 tp_nr;
	INT32 sat_nr;
	UINT32 tp_id[AS_MODULE_MAX_T_NUM];
	UINT8 tp_nit[AS_MODULE_MAX_T_NUM];
	UINT16 sat_id[AS_MODULE_MAX_S_NUM];
#else
	BOOL voltage_ctrl;
	UINT32 polar;
	UINT32 dual_LNB;
	INT32 sat_nr;
	UINT16 sat_id[AS_MODULE_MAX_S_NUM];
	INT32 tp_nr;
	UINT32 tp_id[AS_MODULE_MAX_T_NUM];
#endif
	amssearch_notify_t search_notify_ap;
	amssearch_get_table_info_t get_table_info;
};
#endif
#endif /* __AS_MODULE_H__ */

