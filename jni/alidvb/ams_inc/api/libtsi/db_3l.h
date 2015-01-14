/****************************************************************************
*
*  ALi (Shanghai) Corporation, All Rights Reserved. 2003 Copyright (C)
*
*  File: db_3l.h
*
*  Description: The head file of program database
*              
*  History:
*      Date        Author         Version   Comment
*      ====        ======         =======   =======
*  1.  2004.07.04  David Wang     0.1.000   Initial
*  2.  2005.03.24  Zhengdao Li	  0.1.001   Add marco for SERVICE_PROVIDER name option field.
*  3.  2005.04.21  Zhengdao Li	  0.1.002   Add support for program sort by dl-frequency by default.
****************************************************************************/
#ifndef __LIB_DB_3L_H__
#define __LIB_DB_3L_H__

#include <adr_sys_config.h>

#if( SYS_PROJECT_FE == PROJECT_FE_DVBT )
	#include <api/libdb/db_return_value.h>
	#include <api/libdb/db_config.h>
	#include <api/libdb/db_node_t.h>
	#include <api/libdb/db_interface.h>
#elif(SYS_PROJECT_FE == PROJECT_FE_ISDBT)
	#include <api/libdb/db_return_value.h>
	#include <api/libdb/db_config.h>
	#include <api/libdb/db_node_isdbt.h>
	#include <api/libdb/db_interface.h>
#elif(SYS_PROJECT_FE == PROJECT_FE_ATSC)
	#include <api/libdb/db_return_value.h>
	#include <api/libdb/db_config.h>
	#include <api/libdb/db_node_atsc.h>
	#include <api/libdb/db_interface.h>
#elif(SYS_PROJECT_FE == PROJECT_FE_DVBS||SYS_PROJECT_FE == PROJECT_FE_DVBS2)
	#include <api/libdb/db_return_value.h>
	#include <api/libdb/db_config.h>
	#include <api/libdb/db_node_s.h>
	#include <api/libdb/db_interface.h>
#elif( SYS_PROJECT_FE == PROJECT_FE_DVBC )
	#include <api/libdb/db_return_value.h>
	#include <api/libdb/db_config.h>
	#include <api/libdb/db_node.h>
	#include <api/libdb/db_interface.h>
#endif


#endif /* __LIB_DB_3L_H__ */

