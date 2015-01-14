/*
 * Copyright (C) ALi Shanghai Corp. 2004
 *
 * File: lib_autoscan.h
 *
 * Content: auto-scan service implementation for M3327 chip based IRD.
 *
 * History:
 *    Date	Version		Author		Comment
 *    ========	======= 	========	========
 */
#ifndef _AS_EGINE_H
#define _AS_EGINE_H

#include <adr_sys_config.h>
#include <api/libsi/si_search.h>

/*! @addtogroup ALi中间件
 *  @{
 */

/*! @addtogroup AMSSIS
 *  @{
 */
 
enum as_state_e
{
	AS_ON_IDLE = 0,
	AS_ON_SEARCH = 1,
	AS_ON_STOPING = 2
};


typedef union
{
    struct
    {
		UINT32 sym;
        UINT8 modulation;        
    }c_info;
    struct //reserve for -T
    {
        UINT32 sym;
    }t_info;
	struct //reserve for -S
    {
        UINT32 sym;
	UINT8 por;
    }s_info;
}amsas_frontend_param;

typedef struct
{
	UINT32 as_from;
	UINT32 as_to;
	UINT32 bandwidth;
	amsas_frontend_param ft_param;
}amsas_band_param;


typedef struct
{
    UINT8 as_frontend_type;
	UINT8 nim_id;
	UINT16 sat_id;
	UINT32 band_cnt; //0 blind scan
	INT32 as_method;//dvv-s
	UINT16 as_sat_cnt;//dvv-s
	UINT16 sat_ids[256];//dvv-s
	amsas_band_param band[AS_BAND_MAX_CNT];
	UINT32 turning_timeout;//ms
    amssearch_config_t search_config;
}amsas_service_param;

enum nit_notify_retval_e
{
	GO_ON_SEARCH,
	RESET_SEARCH	
};


#ifdef __cplusplus
extern "C"{
#endif

/*!
@brief AS service注册。
@details 注册AS service。
@retval SUCCESS 总是成功
@retval ERR_XXX 失败
*/
INT32 amsas_service_register(void);

/*!
@brief AS service开始。
@details 开始搜索，该函数为异步函数，只是向AS(PUB)的task发送一个搜台的消息。AS收到这个消息之后，就会根据用户的输入参数，搜索单个频点或多个频点的节目。搜索节目的过程中，会通过上层传递的callback通知各个步骤的信息，应用层做相应的处理，比如显示进度、过滤节目等等。
一般在搜台的时候，需要停止CA、EPG、TDT等，释放宝贵的DMX硬件filter，以加快搜台的速度。
对搜台的处理，各个地方会有一些不同的规范要求，比如有的要求单频点搜台的时候，先要把该频点的节目先删除；全频段搜台的时候，需要先把所有的节目删除；搜完台之后，节目需要过滤和排序，并由用户决定是否需要保存到数据库，等等。这些定制化的工作都可以由应用层或porting层来处理，AMS中间件内部不做处理。
SI Search模块现在只处理DVB规范的数据及Descriptor，如果需要处理私有的Descriptor，在搜台之前，还得先向SI Psearch传递其私有的Descriptor的配置信息，搜台过程中会调用其私有的Descriptor parser分析数据，并将结果挂在section_info的priv数据域，最后通过si_porting_store_program()传递给应用程序。(具体用法可以参考SI Parser的说明和as_test.c)
@param[in] asp 参考as_engine.h和si_search.h的定义。
@retval SUCCESS 总是成功
@retval ERR_XXX 失败
*/
INT32 amsas_service_start(amsas_service_param *asp);

/*!
@brief AS service停止。
@details 停止搜索，该函数为同步函数，直到AS和SI Search都已停止搜台。
@retval SUCCESS 总是成功
@retval ERR_XXX 失败
*/
INT32 amsas_service_stop(void);

/*!
@brief 获取Search状态。
@details 获取Search状态，APP某些情况下需要获取搜台的状态来判断是否处理一些消息的响应。比如收到CA或其它的消息，但是正好又在搜台，那么有些消息就不能显示了。
@retval SUCCESS 总是成功
@retval ERR_XXX 失败
*/
INT32 amsas_service_query_stat(void);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

/*!
@}
*/

#endif /* _LIB_AS_H */
