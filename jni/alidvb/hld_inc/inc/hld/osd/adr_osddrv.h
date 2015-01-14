#ifndef	__ADR_OSDDRV_H_
#define	__ADR_OSDDRV_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <adr_basic_types.h>
#include <hld/adr_hld_dev.h>
#include <alidefinition/adf_osd.h>

/*! @addtogroup osd
 *  @{
 */

/*! @struct osd_device
@brief osd设备类型定义。
*/
struct osd_device
{
	struct osd_device *next;//!< 内部使用。
	UINT32 type; //!< 内部使用。
	INT8 name[HLD_MAX_NAME_SIZE];//!< 内部使用。

	UINT32  flags;//!< 内部使用。
	void	*priv;//!< 内部使用。
};

/*!
@brief 初始化osd 模块。
*/
void HLD_OSDDrv_Attach(void);

/*!
@}
*/

#ifdef __cplusplus
}
#endif

#endif

