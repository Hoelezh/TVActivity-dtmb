#ifndef __DB_CONFIG_H__
#define __DB_CONFIG_H__
#include <stdlib.h>
#include <api/libc/log.h>
#include <api/libc/string.h>
#include <api/libdb/db_interface.h>


/*! @addtogroup ALi中间件
 *  @{
 */

/*! @addtogroup AMSDB
 *  @{
 */
 
/***********************************************************************/
#define DB_PRINTF(args...)	amslog_error(LOG_DB,args)
#define DB_NOTICE(args...)	amslog_notice(LOG_DB,args)
#define DB_DEBUG(args...)	amslog_debug(LOG_DB,args)

#define DB_MALLOC			malloc//amsmem_malloc(size)
#define DB_FREE				free//amsmem_free(ptr)

#define DB_MEMCPY(dest, src, len)		MEMCPY(dest, src, len)
#define DB_MEMCMP(buf1,buf2, len)		MEMCMP(buf1,buf2, len)
#define DB_MEMSET(dest, c, len)			MEMSET(dest, c, len)
#define DB_MEMMOVE(dest, c, len)			MEMMOVE(dest, c, len)


/***********************************************************************/
#define DB_SECTOR_SIZE (64 * 1024)
#define DB_NODE_MAX_SIZE	256
#define DB_TABLE_NUM	3

/*db node type*/
enum
{
	TYPE_PROG_NODE = 0,
	TYPE_TP_NODE =	1,
	TYPE_SAT_NODE = 2,
	TYPE_UNKNOWN_NODE = 0xFF,
};

/*db node id size(byte) and bit field assignment*/
#define NODE_ID_SIZE	4
#define NODE_ID_PG_BIT	10
#define NODE_ID_TP_BIT	10
#define NODE_ID_SET_BIT	8

#define PG_BIT_MASK		0x000003FF
#define TP_BIT_MASK		0x000FFC00
#define SET_BIT_MASK	0x0FF00000

#define NODE_ID_PG_MASK	0x0FFFFFFF
#define NODE_ID_TP_MASK	0x0FFFFC00
#define NODE_ID_SET_MASK	0x0FF00000
#define NODE_ID_INVAL_MASK	0xF0000000


/*db node address size and assignment*/
#define NODE_ADDR_SIZE		4
#define NODE_ADDR_OFFSET_BIT	16

/*db reclaim mode*/
#define DB_RECLAIM_HEADER	0x01
#define DB_RECLAIM_DATA	0x02


/*view node flag, 	total 32bit, high 16bit reserved for db internal */
//low 16bit for application
#define V_NODE_FIND_FLAG	0x01
#define V_NODE_DEL_FLAG	0x02

//high 16bit reserved for db internal
#define V_NODE_ADD_FLAG	0x10000
#define V_NODE_EDIT_FLAG	0x20000
#define V_NODE_INVALID_FLAG	0x80000000
#define V_NODE_FLAG_RESERVE_MASK	0xFFFF0000


//! @brief table node index param。
typedef struct 
{
	UINT32 node_id;
	//node rom addr
	UINT32 node_romaddr;
	//node ram addr
	UINT32 node_ramaddr;
	
}TABLE_NODE_PARAM;

//! @struct t_attr_t
//! @brief db table属性。
typedef struct t_attr_t
{
	UINT8 type;
	
	UINT16 max_cnt;
	//byte of one node 
	UINT16 node_len;

	UINT16 node_num;
	TABLE_NODE_PARAM *table_buf;
}DB_TABLE;

//! @brief view node index param。
typedef struct 
{
	UINT32 node_id;
	//node ram addr
	UINT32 node_addr;
	//node rom addr
	UINT32 node_romaddr;
	UINT32 node_flag;
}VIEW_NODE_PARAM;

//! @struct v_attr_t
//! @brief db view属性。
typedef struct v_attr_t
{
	//view type
	UINT8 type;
	//if node sorted, order changed
	UINT8 sort_flag;
		
	UINT16 cur_filter_mode;
	UINT16 pre_filter_mode;
	UINT32 view_param;
	UINT32 pre_param;
	
	amsdb_filter_func filter;
		
	UINT16 max_cnt;
	//byte of one node 
	UINT16 node_len;
	
	UINT16 node_num;
	VIEW_NODE_PARAM *node_buf;
}DB_VIEW;

/*db command buffer define*/
#define DB_CMD_MAX_CNT	128
#define OP_VALID_FLAG	0xA5

typedef struct
{
	UINT8 node_type;
	UINT32 node_id;
	UINT32 node_ramaddr;
	UINT8 valid_flag;
}OP_PARAM;

//! @brief db command buf。
typedef struct 
{
	UINT16 max_cnt;
	UINT16 cmd_cnt;
	OP_PARAM buf[DB_CMD_MAX_CNT];
}DB_CMD_BUF;

/*!
 * @}
 */

/*!
@}
*/

#endif
