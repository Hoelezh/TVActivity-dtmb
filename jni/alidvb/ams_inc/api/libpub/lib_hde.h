/****************************************************************************
 *
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2004 (C)
 *
 *  File: lib_hde.h
 *
 *  Description: This file implement the hardware display engine on
 *               ALi M3327 chip.
 *
 *  History:
 *      Date		Author		Version  	Comment
 *      ==========	==========  =======		=============================		
 *  1.  2004.10.21	Tom Gao		0.1.000		Initial
 ****************************************************************************/

#ifndef __LIB_PUB27_HDE_H__
#define __LIB_PUB27_HDE_H__

#include <adr_basic_types.h>

/*! @addtogroup ALi中间件
 *  @{
 */

/*! @addtogroup AMSCC
 *  @{
 */

#define VIEW_MODE_FULL			0
#define VIEW_MODE_PREVIEW		1
#define VIEW_MODE_MULTI		2
#define VIEW_MODE_SML			3

/*!
@brief 设置背景色。
@details 设置VPO的单色背景色。在VPO Window Off之前需要先设置VPO Off后的背景色。一般都是设置为黑色。
@param[in] bY 灰度分量取值，黑色可赋值16(不是0) 。
@param[in] bCb Cb分量取值，黑色可赋值中间值128。
@param[in] bCr Cr分量取值，黑色可赋值中间值128。
*/
void hde_back_color(UINT8 bY, UINT8 bCb, UINT8 bCr);

/*!
@brief 设置背景色。
@details 设置VPO的单色背景色。在VPO Window Off之前需要先设置VPO Off后的背景色。一般都是设置为黑色。
@param[in] bY 灰度分量取值，黑色可赋值16(不是0) 。
@param[in] bCb Cb分量取值，黑色可赋值中间值128。
@param[in] bCr Cr分量取值，黑色可赋值中间值128。
*/
void hde_set_mode(UINT32);

/*!
@brief 设置preview位置及大小。
@details 设置preview窗口的位置和大小。在真正掉hde_set_mode() preview之前，需要先设置位置参数。
@param[in] x preview窗口起始坐标位置。取值范围：0-720(不含720)。
@param[in] y preview窗口起始坐标位置。取值范围：对PAL制，0-576(不含576)。对NTSC制，0-480(不含480)。
@param[in] w preview窗口的大小。取值范围：0-720。如果大于720，则表示放大宽度。
@param[in] h preview窗口的大小。取值范围：对PAL制，0-576。对NTSC制，0-480。如果h大于576(480)，则表示放大高度。
@param[in] IsPAL 当前播放的节目是否是PAL制的节目， 对于PAL制和NTSC制的节目，preview需要配置不同的scale参数。
@note 如果x，y的值超过720x576(480)，则在屏幕上看不到任何画面。如果w和h任意一个为0的话，则不会显示任何画面。对x，y，w，h没有对齐的要求，可以是任意奇数或偶数。
*/
void hde_config_preview_window(UINT16 x, UINT16 y, \
      UINT16 w, UINT16 h, BOOL IsPAL);

/*!
@brief 获取当前VPO窗口的显示模式。
@details 获取当前VPO窗口的显示模式。
@retval 0 VIEW_MODE_FULL
@retval 1 VIEW_MODE_PREVIEW
@retval 2 VIEW_MODE_MULTI
@retval 3 VIEW_MODE_SML
*/
UINT32 hde_get_mode(void);


/*!
 * @}
 */

/*!
@}
*/

#endif /* __LIB_PUB27_HDE_H__ */

