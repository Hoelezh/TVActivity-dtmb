/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 Copyright (C)
*
*    File:    pan.h
*
*    Description:    This file contains all functions definition
*		             of Front panel driver.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Apr.21.2003      Justin Wu       Ver 0.1    Create file.
* 	2.  Dec.19.2003		 Justin Wu		 Ver 0.2    Add ESC CMD macros.
*	3.  Sep.23.2005		 Justin Wu		 Ver 0.3    Add pan information.
*****************************************************************************/

#ifndef __ADR_HLD_SOC_H__
#define __ADR_HLD_SOC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <ali_soc_common.h>

/*! @addtogroup soc
 *  @{
 */

/*! @enum VDecOutputMode
@brief soc模块的系统共享内存类型
*/
enum SOC_SYS_SHM
{
	SYS_SHM_AUTO,
	SYS_SHM_OSD2,	
};

INT32 soc_open(void);
INT32 soc_close(void);
INT32 soc_otp_m33_lock(UINT32 offset, INT32 len);
INT32 soc_reboot_get_timer(unsigned long *time_exp, unsigned long *time_cur);
void soc_enter_standby(unsigned int time_exp, unsigned int time_cur);
void soc_get_bonding(void);
unsigned long soc_get_product_id(void);
unsigned long soc_get_c3603_product(void);
unsigned long soc_get_chip_id(void);
unsigned long soc_get_rev_id(void);
unsigned long soc_get_cpu_clock(void);
unsigned long soc_get_dram_clock(void);
unsigned long soc_get_dram_size(void);
INT32 soc_get_usb_num(void);
INT32 soc_get_ci_num(void);
INT32 soc_get_tuner_num(void);
INT32 soc_get_mac_num(void);
INT32 soc_dram_scramble_enabled(void);
INT32 soc_io_security_enabled(void);
INT32 soc_split_enabled(void);
INT32 soc_uart_enabled(void);
INT32 soc_ejtag_enabled(void);
INT32 soc_mv_is_enabled(void);
INT32 soc_ac3_is_enabled(void);
INT32 soc_ddplus_is_enabled(void);
INT32 soc_XD_is_enabled(void);
INT32 soc_XDplus_is_enabled(void);
INT32 soc_aac_is_enabled(void);
INT32 soc_h264_is_enabled(void);
INT32 soc_mp4_is_enabled(void);
INT32 soc_get_hd_enabled(void);
INT32 soc_hd_is_enabled(void);
INT32 soc_usb_port_enabled(unsigned long port);
INT32 soc_sata_enable(void);
INT32 soc_nim_support(void);
INT32 soc_nim_m3501_support(void);
INT32 soc_check_addr(UINT32 addr, UINT32 len);
INT32 soc_read8(UINT32 addr, UINT8 *buf, UINT32 len);
INT32 soc_read16(UINT32 addr, UINT8 *buf, UINT32 len);
INT32 soc_read32(UINT32 addr, UINT8 *buf, UINT32 len);
INT32 soc_write8(UINT32 addr, UINT8 *buf, UINT32 len);
INT32 soc_write16(UINT32 addr, UINT8 *buf, UINT32 len);
INT32 soc_write32(UINT32 addr, UINT8 *buf, UINT32 len);
INT32 soc_per_read32(UINT32 addr, UINT8 *buf, UINT32 len);
INT32 soc_per_write32(UINT32 addr, UINT8 *buf, UINT32 len);
INT32 soc_get_memory_map(struct soc_memory_map *smm);
INT32 soc_set_level(unsigned long level);
INT32 soc_get_see_ver(UINT8 *buf);
INT32 soc_hit_see_heart(void);
INT32 soc_enable_see_exception(void);
INT32 soc_reboot();
INT32 soc_dsc_access_ce_disable(void);

/*!
@brief 读取板子相关的配置内存
@param[out] buf_addr内存地址 。
@param[out] buf_size内存大小。
*/
void soc_get_reserved_men_buf(UINT32 *buf_addr, UINT32 *buf_size);

/*!
@brief 读取media player 相关的配置内存
@param[out] buf_addr内存地址 。
@param[out] buf_size内存大小。
*/
void soc_get_media_buf(UINT32 *buf_addr, UINT32 *buf_size);

/*!
@brief 打开或者关闭see cpu的printf输出
@param[in] enable标志信息。0 -- 关闭，1 -- 打开。
*/
INT32 soc_set_see_printf(INT32 enable);


/*!
@brief 读取系统的share内存空间
@par
*/
INT32 soc_get_share_mem(enum SOC_SYS_SHM type, void **buf_addr, INT32 *buf_size);

/*!
@brief 关闭不需要的IP clk/dac ,用于HDMI DONGLE节省功耗
@par
*/
INT32 soc_enable_power_down(INT32 power_down);	

INT32 soc_show_see_plugin_info();

	
/*!
 @}
 */
#ifdef __cplusplus
}
#endif
#endif /* __ADR_HLD_SOC_H__ */
