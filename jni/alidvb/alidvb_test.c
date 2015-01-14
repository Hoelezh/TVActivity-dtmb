#include <adr_sys_config.h>
#include <adr_retcode.h>

#include <osal/osal.h>

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

#include "alidvb_channelnode.h"

#include "alidvb_test.h"

#define LOG_TAG    "ALiDVB_Test"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define SYSTEM_DEBUG	LOGD
#define SYSTEM_NOTICE	LOGI
#define SYSTEM_ERROR	LOGE



unsigned short ComStrToUnicode(UINT16* uni, char* str, UINT16 maxcount)
{

	UINT16 i;

	if (uni == NULL)
		return 0;

	if (str == NULL || maxcount == 0)
	{
		uni[0]=(UINT16)'\0';
		return 1;
	}

	for(i=0; (0!=str[i])&&(i<maxcount); i++)
	{
#if (SYS_CPU_ENDIAN==ENDIAN_LITTLE)
       uni[i]=(UINT16)(str[i]<<8);
#else
       uni[i]=(UINT16)str[i];
#endif
	}
	uni[i]=(UINT16)'\0';

	return i+1;
}



int ALiDVB_satellitetest(void)
{
	INT32 ret = 0;
	S_NODE set;
	T_NODE tp;
	char* s_name1 = "C ASIASAT";
	char* s_name2 = "KU ASIASAT";

	amsdb_create_view(TYPE_SAT_NODE, VIEW_ALL, 0);
#if 1
	if(amsdb_get_node_cnt(TYPE_SAT_NODE,VIEW_ALL,0) > 1)
	{
		return ret;
	}
	else
	{
		osal_task_sleep(50);
		if(amsdb_get_node_cnt(TYPE_SAT_NODE,VIEW_ALL,0) > 1)
		{
			return ret;
		}
		osal_task_sleep(50);
	}
#endif
	amsdb_create_view(TYPE_TP_NODE, VIEW_ALL, 0);
	memset(&set, 0, sizeof(S_NODE));
	set.sat_id = 1;
	set.sat_orbit = 1055;
	set.name_len = ComStrToUnicode(set.sat_name, s_name1, 17)*sizeof(UINT16);
	//set.sat_name = 
	set.tuner1_valid= 1;
	set.lnb_type = 1;
	set.pol = 0;
	set.lnb_low = 5150;
	set.lnb_high = 5750;

	//add this node to db
	ret = amsdb_add_node(TYPE_SAT_NODE, 1, (UINT8 *)&set, sizeof(S_NODE) );
	//ret = DO_add_node(TYPE_SAT_NODE, set.sat_id<<(NODE_ID_PG_BIT+NODE_ID_TP_BIT), (UINT8 *)&set, sizeof(S_NODE));
	if(0!=ret)
	{
		return -1;
	}

	memset(&set, 0, sizeof(S_NODE));
	set.sat_id = 2;
	set.sat_orbit = 1055;
	set.name_len = ComStrToUnicode(set.sat_name, s_name2, 17)*sizeof(UINT16);

	set.tuner1_valid= 0;
	set.lnb_type = 1;
	set.pol = 0;
	set.lnb_low = 9750;
	set.lnb_high = 10600;
	//add this node to db
	ret = amsdb_add_node(TYPE_SAT_NODE, 1, (UINT8 *)&set, sizeof(S_NODE) );
	//ret = DO_add_node(TYPE_SAT_NODE, set.sat_id<<(NODE_ID_PG_BIT+NODE_ID_TP_BIT), (UINT8 *)&set, sizeof(S_NODE));
	if(0!=ret)
	{
		return -1;
	}

	MEMSET(&tp, 0, sizeof(T_NODE));
	tp.sat_id = 1;
	tp.ft_type = FRONTEND_TYPE_S;
	tp.frq = 3680;
	tp.sym = 26666;
	ret = amsdb_add_node(TYPE_TP_NODE, tp.sat_id, (UINT8 *)&tp, sizeof(T_NODE) );
	//ret = DO_add_node(TYPE_SAT_NODE, set.sat_id<<(NODE_ID_PG_BIT+NODE_ID_TP_BIT), (UINT8 *)&set, sizeof(S_NODE));
	if(0!=ret)
	{
		return -2;
	}
	MEMSET(&tp, 0, sizeof(T_NODE));
	tp.sat_id = 1;
	tp.ft_type = FRONTEND_TYPE_S;
	tp.frq = 3700;
	tp.sym = 27500;
	tp.pol = 1;
	ret = amsdb_add_node(TYPE_TP_NODE, tp.sat_id, (UINT8 *)&tp, sizeof(T_NODE) );
	//ret = DO_add_node(TYPE_SAT_NODE, set.sat_id<<(NODE_ID_PG_BIT+NODE_ID_TP_BIT), (UINT8 *)&set, sizeof(S_NODE));
	if(0!=ret)
	{
		return -2;
	}

	MEMSET(&tp, 0, sizeof(T_NODE));
	tp.sat_id = 1;
	tp.ft_type = FRONTEND_TYPE_S;
	tp.frq = 3706;
	tp.sym = 6000;
	ret = amsdb_add_node(TYPE_TP_NODE, tp.sat_id, (UINT8 *)&tp, sizeof(T_NODE) );
	//ret = DO_add_node(TYPE_SAT_NODE, set.sat_id<<(NODE_ID_PG_BIT+NODE_ID_TP_BIT), (UINT8 *)&set, sizeof(S_NODE));
	if(0!=ret)
	{
		return -2;
	}

	MEMSET(&tp, 0, sizeof(T_NODE));
	tp.sat_id = 1;
	tp.ft_type = FRONTEND_TYPE_S;
	tp.frq = 3840;
	tp.sym = 27490;
	ret = amsdb_add_node(TYPE_TP_NODE, tp.sat_id, (UINT8 *)&tp, sizeof(T_NODE) );
	if(0!=ret)
	{
		return -2;
	}
	MEMSET(&tp, 0, sizeof(T_NODE));
	tp.sat_id = 2;
	tp.ft_type = FRONTEND_TYPE_S;
	tp.frq = 12652;
	tp.sym = 6930;
	ret = amsdb_add_node(TYPE_TP_NODE, tp.sat_id, (UINT8 *)&tp, sizeof(T_NODE) );
	//ret = DO_add_node(TYPE_SAT_NODE, set.sat_id<<(NODE_ID_PG_BIT+NODE_ID_TP_BIT), (UINT8 *)&set, sizeof(S_NODE));
	if(0!=ret)
	{
		return -2;
	}

	MEMSET(&tp, 0, sizeof(T_NODE));
	tp.sat_id = 2;
	tp.ft_type = FRONTEND_TYPE_S;
	tp.frq = 12660;
	tp.sym = 40000;
	tp.pol = 1;
	ret = amsdb_add_node(TYPE_TP_NODE, tp.sat_id, (UINT8 *)&tp, sizeof(T_NODE) );
	//ret = DO_add_node(TYPE_SAT_NODE, set.sat_id<<(NODE_ID_PG_BIT+NODE_ID_TP_BIT), (UINT8 *)&set, sizeof(S_NODE));
	if(0!=ret)
	{
		return -2;
	}

	MEMSET(&tp, 0, sizeof(T_NODE));
	tp.sat_id = 2;
	tp.ft_type = FRONTEND_TYPE_S;
	tp.frq = 12663;
	tp.sym = 5992;
	ret = amsdb_add_node(TYPE_TP_NODE, tp.sat_id, (UINT8 *)&tp, sizeof(T_NODE) );
	//ret = DO_add_node(TYPE_SAT_NODE, set.sat_id<<(NODE_ID_PG_BIT+NODE_ID_TP_BIT), (UINT8 *)&set, sizeof(S_NODE));
	if(0!=ret)
	{
		return -2;
	}



	//update
	ret = amsdb_update_data();
	if(0!=ret)
	{
		return -3;
	}

	return ret;

}

