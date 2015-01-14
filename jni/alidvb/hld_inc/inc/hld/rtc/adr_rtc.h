/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    adr_rtc.h
*
*    Description:    This file contains sto_device structure define in HLD.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Aug.20.2012      xuhua huang       Ver 0.1    Create file.
*****************************************************************************/

#ifndef __ADR_HLD_RTC_H__
#define __ADR_HLD_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <adr_basic_types.h>

#define RTC_STATE_DETACH   0
#define RTC_STATE_ATTACH   1

#define RTC_CMD_BASE				0x00
#define RTC_CMD_SET_TIME			(RTC_CMD_BASE	+ 1)//!<设置RTC 时间
#define RTC_CMD_GET_TIME			(RTC_CMD_BASE	+ 2)//!<读取RTC 时间
#define RTC_CMD_SET_ALARM		(RTC_CMD_BASE	+ 3)//!<设置ALARM 时间
#define RTC_CMD_GET_ALARM		(RTC_CMD_BASE	+ 4)//!<读取ALARM 时间
#define RTC_CMD_AIE_OFF			(RTC_CMD_BASE	+ 5)//!<关闭ALARM 
#define RTC_CMD_AIE_ON				(RTC_CMD_BASE	+ 6)//!<开启ALARM 

#define PMU_CMD_BASE				0x00
#define PMU_CMD_SET_TIME					(PMU_CMD_BASE	+ 1)//!<设置standby当前时间
#define PMU_CMD_SET_WAKETIME			(PMU_CMD_BASE	+ 2)//!<设置wakeup 时间
#define PMU_CMD_ENTER_STANDBY		(PMU_CMD_BASE	+ 3)//!<进入standby模式
#define PMU_CMD_SET_POWER_KEY		(PMU_CMD_BASE	+ 4)//!<设置powerkey键值

#define POWER_KEY_NUM			8
struct rtc_time_hld
{
    UINT16  year;        /**< 年*/
    UINT8  month;       /**< 月*/
    UINT8  date;        /**< 日*/
    UINT8  hour;        /**< 时*/
    UINT8  minute;      /**< 分*/
    UINT8  second;      /**< 秒*/
};

struct rtc_wkalrm_hld 
{
	struct rtc_time_hld time;	/**<Alarm设置的时间 */
	UINT8 enabled;	/**< 0 = alarm disabled, 1 = alarm enabled */
	UINT8 pending; /**< 0 = alarm not pending, 1 = alarm pending */
};

struct rtc_device
{
	struct rtc_device  *next; //!< 内部使用。
	UINT32 type; //!< 内部使用。
	INT8 name[16]; //!< 内部使用。
	UINT16		flags;				//!<Interface flags, status and ability 
	INT32 handle;
};

struct pmu_device
{
	struct pmu_device  *next; //!< 内部使用。
	UINT32 type; //!< 内部使用。
	INT8 name[16]; //!< 内部使用。
	UINT16		flags;				//!<Interface flags, status and ability 
	INT32 handle;//!< 内部使用。
	struct rtc_time_hld time;//!< 内部使用。
	UINT32 duration;//!< 内部使用。
};

/*!
@brief 初始化rtc 模块。
*/
RET_CODE rtc_attach(void);

/*!
@brief 释放rtc 模块。
*/
RET_CODE rtc_dettach(struct rtc_device *dev);

/*!
@brief 打开rtc 模块。
@param[in] dev 指向rtc模块 的指针。
@param[in] init 初始化参数。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE rtc_open(struct rtc_device * dev);

/*!
@brief 关闭rtc  模块。
@param[in] dev 指向rtc 模块 的指针。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE rtc_close(struct rtc_device * dev);

/*!
@brief rtc 模块的io contorl 操作。
@param[in] dev 指向rtc 模块 的指针。
@param[in] dwCmd 操作 的命令类型。参考RTC_CMD_XX定义。
@param[in,out] dwParam 操作的参数，根据不同的命令会有不同的参数。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
@note  IO命令dwCmd 介绍:
<table class="doxtable"  width="800" border="1" style="border-collapse:collapse;table-layout:fixed;word-break:break-all;" >
  <tr>
    <th width="200">命令</th>
    <th width="200">参数</th>
    <th width="80">传输特性</th>
    <th width="320">备注</th>
  </tr>

  <tr align="center">
    <td>RTC_CMD_SET_TIME</td>    
    <td>struct  rtc_time_hld *</td>    
    <td>输入</td>
    <td>设置时间</td>
  </tr>

  <tr align="center">
    <td>RTC_CMD_GET_TIME</td>    
    <td>struct rtc_time_hld *</td>    
    <td>输出</td>
    <td>获得时间</td>
  </tr>

  <tr align="center">
    <td>RTC_CMD_SET_ALARM</td>    
    <td>struct rtc_wkalrm_hld *</td>    
    <td>输入</td>
    <td>设置闹钟时间</td>
  </tr>  
  
  <tr align="center">
    <td>RTC_CMD_GET_ALARM</td>    
    <td>struct  rtc_wkalrm_hld *</td>    
    <td>输出</td>
    <td>获取闹钟时间</td>
  </tr>  

  <tr align="center">
    <td>RTC_CMD_AIE_OFF</td>    
    <td>UINT32</td>    
    <td>输入</td>
    <td>关闭闹钟</td>
  </tr>  

  <tr align="center">
    <td>RTC_CMD_AIE_ON</td>    
    <td>UINT32</td>    
    <td>输入</td>
    <td>开启闹钟</td>
  </tr>  
*/
RET_CODE rtc_io_control(struct rtc_device * dev, UINT32 dwCmd, UINT32 dwParam);

/*!
@brief 初始化pmu 模块。
*/
RET_CODE pmu_attach(void);

/*!
@brief 释放pmu 模块。
*/
RET_CODE pmu_dettach(struct pmu_device *dev);

/*!
@brief 打开pmu 模块。
@param[in] dev 指向pmu模块 的指针。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE pmu_open(struct pmu_device *dev);

/*!
@brief 关闭pmu  模块。
@param[in] dev 指向pmu 模块 的指针。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
*/
RET_CODE pmu_close(struct pmu_device * dev);

/*!
@brief pmu 模块的io contorl 操作。
@param[in] dev 指向pmu 模块 的指针。
@param[in] dwCmd 操作 的命令类型。参考PMU_CMD_XX定义。
@param[in,out] dwParam 操作的参数，根据不同的命令会有不同的参数。
@return RET_CODE。
@retval  RET_SUCCESS       申请 成功。
@retval  !RET_SUCCESS     申请 失败，参数错误或状态错误。
@note  IO命令dwCmd 介绍:
<table class="doxtable"  width="800" border="1" style="border-collapse:collapse;table-layout:fixed;word-break:break-all;" >
  <tr>
    <th width="200">命令</th>
    <th width="200">参数</th>
    <th width="80">传输特性</th>
    <th width="320">备注</th>
  </tr>
  <tr align="center">
    <td>PMU_CMD_SET_TIME</td>    
    <td>struct rtc_time_hld *</td>    
    <td>输入</td>
    <td>获得设置系统进入standby的时间</td>
  </tr>
  <tr align="center">
    <td>PMU_CMD_SET_WAKETIME</td>    
    <td>UINT32</td>    
    <td>输入</td>
    <td>设置系统待机持续时间</td>
  </tr>

  <tr align="center">
    <td>PMU_CMD_ENTER_STANDBY</td>    
    <td>UINT32</td>    
    <td>输入</td>
    <td>设置系统进入待机</td>
  </tr>  
  
  <tr align="center">
    <td>PMU_CMD_SET_POWER_KEY</td>    
    <td>UINT32 *</td>    
    <td>输入</td>
    <td>设置系统power键值,输入的参数为数组，共可设POWER_KEY_NUM个键值</td>
  </tr>  

*/
RET_CODE pmu_io_control(struct pmu_device * dev, UINT32 dwCmd, UINT32 dwParam);
#ifdef __cplusplus
}
#endif


#endif  /* __ADR_HLD_RTC_H__ */

