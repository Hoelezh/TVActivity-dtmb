#ifndef __DB_INTERFACE_H__
#define __DB_INTERFACE_H__

#include <adr_basic_types.h>

/*! @addtogroup ALi中间件
 *  @{
 */

/*! @addtogroup AMSDB
 *  @{
 */
 
/************************************************************************************************/
/*amsdb function prototype and structure define*/

/*callback function protorype define*/
typedef BOOL (*amsdb_filter_func)(UINT8 node_type, const UINT8 *node, UINT16 filter_mode, UINT32 param);

typedef INT32 (*amsdb_node_pack_func)(UINT8 node_type, const UINT8*src_node, UINT32 src_len,UINT8*packed_node,UINT32 *packed_len);
typedef INT32 (*amsdb_node_unpack_func)( UINT8 node_type,const UINT8 *src_node,UINT32 src_len, UINT8 *unpack_node, UINT32 unpack_len);

typedef BOOL (*amsdb_node_compare_func)(UINT8 n_type, const void* old_node, const void* new_node);

typedef BOOL (*amsdb_node_find_func)(UINT8 n_type, const void* node, UINT8 *name,UINT32 name_len);

typedef struct
{
	UINT16 max_sat_cnt;
	UINT16 sat_node_len;
	UINT16 max_tp_cnt;
	UINT16 tp_node_len;
	UINT16 max_prog_cnt;
	UINT16 prog_node_len;

	amsdb_filter_func filter_callbak;
	amsdb_node_pack_func pack_callbak;
	amsdb_node_unpack_func unpack_callbak;
	amsdb_node_compare_func compare_callbak;
	amsdb_node_find_func find_callbak;	
}amsdb_param_t;

#define DB_INVALID_POS	0xFFFF


/* create view group flag */
#define VIEW_ALL        0x0100
#define VIEW_SINGLE_SAT     0x0200
#define VIEW_SINGLE_TP      0x0300
#define VIEW_FAV_GROUP      0x0400
#define VIEW_BOUQUIT_ID		0x0500
#define VIEW_CAS		0x0600
#define VIEW_PROVIDER		0x0700
#define VIEW_FAV_GROUP_ALL      0x0800

/* create view service type flag */
#define PROG_RADIO_MODE	    0x00
#define PROG_TV_MODE		    0x01
#define PROG_TVRADIO_MODE	    0x02
#define PROG_DATA_MODE		0x03
#define PROG_NVOD_MODE		0x04
#define PROG_ALL_MODE               0x05
#define PROG_PRIVATE_MODE       0x06
#define PROG_TVRADIODATA_MODE       0x07
#define PROG_TVDATA_MODE		0x08
#define PROG_MOSAIC_MODE		0x09

/*load default db node flag*/
#define DEFAULT_DVBC_PROG			0x01
#define DEFAULT_ALL_PROG			0x02

/* for cal program num */
#define SAT_PROG_NUM			0x01
#define FAV_PROG_NUM			0x02
#define TP_PROG_NUM				0x04
#define NVOD_PROG_NUM			0x08
#define DATA_PROG_NUM			0x10

/* flag for sort program */
enum {
	//sort node in view by key value in ascend order
	DB_SORT_ORDER_ASCEND		= 0x01,
	//sort node in view by key value in descend order
	DB_SORT_ORDER_DESCEND	= 0x02,
};

#ifdef __cplusplus
extern "C"{
#endif

/*amsdb external interface*/

/*!
@brief 设置DB预置数据。
@details 此函数设置DB的预置node数据，对DVBC来说，只是建立一个虚拟的根node节点。
@param[in] set_mode 设预置node数据的模式。
@param[in] default_addr 预制DB数据的地址。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_set_default(UINT8 set_mode,UINT32 default_addr);

/*!
@brief 初始化数据库。
@details 此函数初始化数据库。
@param[in] db_addr DB在外部存储器的起始地址，是相对于其基地址的offset偏移。
@param[in] len DB在外部存储器所占的空间长度。<br>
DB5需要的最小flash空间：<br>
 - 当垃圾回收使用内存备份时，最小flash空间为64KB*3；
 - 当垃圾回收不使用内存备份时，最小flash空间需要再增加64KB*2；
@param[in] config DB的配置参数，详细含义见amsdb_param_t类型定义。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_init_db(UINT32 db_addr, UINT32 len, amsdb_param_t *config);

/*!
@brief 擦除DB数据。
@details 此函数擦除DB中已有的所有数据。回复默认预置值。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_clear_db(void);

/*!
@brief 通过位置获得当前节点数据。
@details 此函数通过位置参数获得当前view中的一个node节点数据。
@param[in] type Node的类型。
@param[in] pos Node在当前view中的位置。
@param[in] node 存储node数据的buffer地址。
@param[in] len 存储node数据的buffer大小，以byte为单位。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_get_node_at(UINT8 type ,UINT16 pos,  UINT8* node, INT32 len);

/*!
@brief 通过id获得当前节点数据。
@details 此函数通过id参数获得当前view中的一个node节点数据。
@param[in] type Node的类型。
@param[in] id Node的id。
@param[in] node 存储node数据的buffer地址。
@param[in] len 存储node数据的buffer大小，以byte为单位。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_get_node_byid(UINT8 type ,UINT32 id,  UINT8* node, INT32 len);

/*!
@brief 获得子节点数据。
@details 此函数获得当前view中某一个父节点下位置为pos的一个子node节点数据。该函数常用于获得一个S_NODE下位置为pos的某个T_NODE。
@param[in] type Node的类型。
@param[in] parent_父节点Node的id。
@param[in] pos 子节点在父节点下的位置。
@param[in] node 存储node数据的buffer地址。
@param[in] len 存储node数据的buffer大小，以byte为单位。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_get_node_at2(UINT8 type ,UINT32 parent_id, UINT16 pos, UINT8* node, INT32 len);

/*!
@brief 添加节点数据。
@details 此函数添加一个node节点到DB。
@param[in] type Node的类型。
@param[in] parent_id Node的父节点的id。
@param[in] node 存储node数据的buffer地址。
@param[in] len 存储node数据的buffer大小，以byte为单位。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_add_node(UINT8 type, UINT32 parent_id,UINT8*node, INT32 len);

/*!
@brief 修改节点数据。
@details 此函数根据id参数修改当前view中的一个node节点。
@param[in] type Node的类型。
@param[in] id Node的id。
@param[in] node 存储node数据的buffer地址。
@param[in] len 存储node数据的buffer大小，以byte为单位。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_modify_node(UINT8 type, UINT32 id,  UINT8*node, INT32 len);

/*!
@brief 删除节点数据。
@details 此函数按位置参数删除当前view中的一个node节点。
@param[in] type Node的类型。
@param[in] pos Node在当前view中的位置。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_del_node_at(UINT8 type, UINT16 pos);

/*!
@brief 按id删除节点数据。
@details 此函数按id参数删除当前view中的一个node节点。
@param[in] type Node的类型。
@param[in] id Node的id。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_del_node_byid(UINT8 type, UINT32 id);

/*!
@brief 删除全部子节点。
@details 此函数在当前view中按父节点id删除它的全部子节点。
@param[in] node_type Node的类型。
@param[in] parent_type 父节点Node的类型。
@param[in] parent_id 父节点Node的id。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_del_child(UINT8 node_type, UINT8 parent_type, UINT32 parent_id);

/*!
@brief 移动节点数据。
@details 此函数在当前view中把一个节点从原来位置移动的指定的位置。
@param[in] type 节点Node的类型。
@param[in] dest_pos 该节点的目的位置。
@param[in] src_pos 该节点原来的位置。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_move_node(UINT8 type, UINT16 dest_pos,UINT16 src_pos);

/*!
@brief 获取节点位置。
@details 此函数按id参数返回view中此node节点的位置。
@param[in] type 节点Node的类型。
@param[in] id Node的id。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
UINT16 amsdb_get_node_pos(UINT8 type, UINT32 id);

/*!
@brief 查找节点数量。
@details 此函数在当前view中查找符合某个条件的节点的个数。
@param[in] type 节点Node的类型。
@param[in] filter_mode 分为2部分：高字节表示对节点的group要求，低字节表示对节点的类型要求。
@param[in] param 对应filter_mode的参数。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
UINT16 amsdb_get_node_cnt(UINT8 type, UINT16 filter_mode, UINT32 param);

/*!
@brief 创建view。
@details 此函数对于某种类型的节点按照用户定制的过滤函数创建一个子集，称为view，后续的操作都基于这个view。
@param[in] type 节点Node的类型。
@param[in] create_mode 创建view的模式，分为2部分：高字节表示对节点的group要求，低字节表示对节点的类型要求。具体实现过滤的函数由应用程序的回调函数实现。
@param[in] param 对应于view模式的参数。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_create_view(UINT8 type, UINT16 create_mode, UINT32 param);

/*!
@brief 获得当前view的模式和参数。
@details 此函数获得当前view的模式和参数，以便保存此模式和参数，然后创建新的view进行一些操作，之后再用所保存的模式和参数回复之前的view。
@param[in] type 节点Node的类型。
@param[in] filter_mode 保存返回当前view的模式的buf指针。
@param[in] param 保存返回当前view的模式参数的buf指针。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_get_view_param(UINT8 type, UINT16 *filter_mode, UINT32 *param);

/*!
@brief 查找相同节点。
@details 此函数在当前view中查找是否存在一个相同的节点。
@param[in] type 节点Node的类型。
@param[in] node_id Node的id。
@param[in] node 指向该节点数据的指针，根据节点数据具体内容判断是否相同的函数由应用程序的回调函数实现。
@param[in] len 存储node数据的buffer大小，以byte为单位。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_lookup_node(UINT8 type, UINT32 node_id, UINT8 *node, UINT32 len);

/*!
@brief 保存DB数据。
@details 此函数把之前对当前view中node数据所作的操作保存的外部存储器。这样关机时，node数据不会丢失。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_update_data(void);

/*!
@brief 检查DB数据是否更改。
@details 此函数检查某种类型的node是否做了操作，如修改，删除，添加，排序等，如果有则返回TRUE。应用可以调用此函数来检查是否对某种类型的node做了操作，然后决定是否要把改动保存到flash。。
@param[in] type Node类型。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
BOOL amsdb_check_node_modify(UINT8 type);

/*!
@brief 设置节点标志。
@details 此函数在当前view中对某个位置的节点设置flag标志。
@param[in] type 节点Node的类型。
@param[in] pos 该节点在当前view中的位置。
@param[in] flag 特定的flag，如V_NODE_DEL_FLAG, V_NODE_FIND_FLAG等。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_set_node_flag(UINT8 type, UINT16 pos, UINT16 flag);

/*!
@brief 清除节点标志。
@details 此函数清除当前view中对某个位置的节点的flag标志。
@param[in] type 节点Node的类型。
@param[in] pos 该节点在当前view中的位置。
@param[in] flag 特定的flag，如V_NODE_DEL_FLAG, V_NODE_FIND_FLAG等。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_clear_node_flag(UINT8 type, UINT16 pos, UINT16 flag);

/*!
@brief 检查节点标志。
@details 此函数检查当前view中对某个位置node是否设置了特定的flag标志。
@param[in] type 节点Node的类型。
@param[in] pos 该节点在当前view中的位置。
@param[in] flag 特定的flag，如V_NODE_DEL_FLAG, V_NODE_FIND_FLAG等。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
BOOL amsdb_check_node_flag(UINT8 type, UINT16 pos, UINT16 flag);

/*!
@brief 查找节点。
@details 此函数在当前view中按照某个字符串查找符合的节点，返回其个数。
@param[in] type 节点Node的类型。
@param[in] str 指向一个字符串的指针。具体节点数据的哪个域和该字符串来做比较由应用程序实现的find回调函数来决定。
@param[in] node 存储node数据的buffer地址。
@param[in] len 存储node数据的buffer大小，以byte为单位。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
UINT16 amsdb_find_node(UINT8 type, char *str, UINT8*node, UINT32 len);

/*!
@brief 按照位置获得节点数据。
@details 此函数在查找到节点的基础上，按照位置参数获得节点数据。
@param[in] type 节点Node的类型。
@param[in] pos 查找到的节点位置，即是找到的第几个节点。
@param[in] node 存储node数据的buffer地址。
@param[in] len 存储node数据的buffer大小，以byte为单位。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_get_find_node(UINT8 type, UINT16 pos, UINT8 *node, UINT32 len);

/*!
@brief 排序节点数据。
@details 此函数对当前view中的节点按照某个关键字进行排序。
@param[in] type 节点Node的类型。
@param[in] sort_mode 排序的类型。
@param[in] key 指向排序关键字的数组的指针。调用者需要获得每个节点的关键字，组成一个关键字数组传入。
@param[in] cnt 排序关键字的个数，等于view中节点的个数。
@retval DB_SUCCESS 成功
@retval DBERR_XXX 失败
*/
INT32 amsdb_sort_node(UINT8 type, UINT8 sort_mode, UINT32 *key, INT32 cnt);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

/*!
@}
*/

#endif

