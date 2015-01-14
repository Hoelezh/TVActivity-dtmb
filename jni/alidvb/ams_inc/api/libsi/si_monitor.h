/*
 * Copyright (C) ALi Shanghai Corp. 2005.
 *
 * si_monitor.h
 *
 * a SI information tracking utility header file.
 */
#ifndef __SI_MONITOR_H__
#define __SI_MONITOR_H__

#include <adr_sys_config.h>

#define AMSSIM_MONIT_SDT_OTHER	0x00000001
#define AMSSIM_MONIT_BAT		0x00000002
#define AMSSIM_MONIT_NIT_CUR	0x00000004
#define AMSSIM_MONIT_NIT_OTHER	0x00000008
#define AMSSIM_MONIT_PMT_OTHER	0x00000010
#define AMSSIM_MONIT_DEFAULT	0x80000000

#define SIM_MSG_PAT				0x0
#define SIM_MSG_PMT				0x1
#define SIM_MSG_SDT				0x2
#define SIM_MSG_SDT_OTH			0x3
#define SIM_MSG_BAT				0x4
#define SIM_MSG_NIT				0x5
#define SIM_MSG_NIT_OTH			0x6
#define SIM_MSG_DYNAMIC_PID		0x7


/*! @addtogroup ALi中间件
 *  @{
 */

/*! @addtogroup AMSSIM
 *  @{
 */

//! @enum AMSSIM_TABLE_TYPE
//! @brief 定义表的类型。
typedef enum
{
    AMSSIM_TABLE_PAT = 0,
    AMSSIM_TABLE_PMT,
    AMSSIM_TABLE_SDT,
    AMSSIM_TABLE_SDT_OTH,
    AMSSIM_TABLE_BAT,
    AMSSIM_TABLE_NIT,
    AMSSIM_TABLE_NIT_OTH
}AMSSIM_TABLE_TYPE;
 
//! @struct si_monitor_msg
//! @brief SI Monitor message的定义。
typedef struct
{
    UINT16 cmd_type;
	UINT8 table_id;
	UINT32 ext_id;
	UINT8 sec_num;
	UINT32 crc;
	UINT8 handle;
}si_monitor_msg;

#ifdef __cplusplus
extern "C"{
#endif

typedef void(*sim_notify_t)(si_monitor_msg *msg, UINT32 param);

/*!
@brief 初始化SIM。
@details 此函数用于初始化SI monitor库。Si monitor模块通过此函数创建内部需要的资源。
@retval SUCCESS 成功
@retval ERR_XXX 失败，状态错误。
*/
INT32 amssim_init(void);

/*!
@brief 释放SIM资源。
@details Si monitor模块通过此函数释放由amssim_init()函数所创建的资源。
@retval SUCCESS 成功
@retval ERR_XXX 失败，状态错误。
*/
INT32 amssim_uninit(void);

/*!
@brief 打开SI监视。
@param[in] dmx_id DMX的index号。
@param[in] prog_num 当前节目的program number。
@param[in] table 监视哪些表，参考相关宏定义。
@retval SUCCESS 成功
@retval ERR_XXX 失败，状态错误。
*/
INT32 amssim_open_monitor(UINT8 dmx_id, UINT16 prog_num, UINT32 table, UINT8 ignore_crc);

/*!
@brief 关闭SI监视。
@retval SUCCESS 成功
@retval ERR_XXX 失败，状态错误。
*/
INT32 amssim_close_monitor(void);

/*!
@brief 打开SI监视。
@param[in] func 回调函数指针。
*/
void  amssim_reg_callback(sim_notify_t func);

/*!
@brief 打开SI监视。
@param[in] table_id 表的table id。
@param[in] extension_id 子表的id。
@param[in] sec_num 表的 section number。
@param[in] crc Section数据的CRC值。
@param[in] buf 输出数据的存放空间。
@param[in/out] len 输入最大值，输出有效值。
@retval SUCCESS 成功
@retval ERR_XXX 失败，状态错误。
*/
INT32 amssim_get_section(AMSSIM_TABLE_TYPE table_type, UINT32 extension_id, UINT8 sec_num, UINT32 crc, UINT8 *buf, UINT16 *len);

/*!
@brief 获得Monitor当前的handle。
@retval SUCCESS 成功
@retval ERR_XXX 失败，状态错误。
*/
UINT8 amssim_get_handle(void);

/*!
@brief 设置监控表的私有pid、table_id。
@param[in] table_type 表的类型。
@param[in] pid 表的pid。
@param[in] table_id 表的table id。
@retval SUCCESS 成功
@retval ERR_XXX 失败，状态错误。
*/
INT32 amssim_set_table_priv_parm(AMSSIM_TABLE_TYPE table_type, UINT16 pid, UINT8 table_id);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

/*!
@}
*/

#endif /* __DVB_SIE_MONITOR_H__ */

