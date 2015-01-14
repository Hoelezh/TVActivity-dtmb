/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 - 2003 Copyright (C)
*
*    File:    sto_dev.h
*
*    Description:    This file contains sto_device structure define in HLD.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	May.29.2003      Justin Wu       Ver 0.1    Create file.
*****************************************************************************/

#ifndef __ADR_HLD_STO_DEV_H__
#define __ADR_HLD_STO_DEV_H__

#include <hld/adr_hld_dev.h>
#include <osal/osal.h>
#include <hld/bus/erom/erom.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @addtogroup sto
 *  @{
 */

/*!@struct sto_device_ioctrl_command
@brief IO control commands
*/
enum sto_device_ioctrl_command
{
	STO_DRIVER_ATTACH	= 0,		//!<Driver attach command
	STO_DRIVER_SUSPEND	= 1,		//!<Driver suspend command
	STO_DRIVER_RESUME	= 2,		//!<Driver resume command
	STO_DRIVER_DETACH	= 3,		//!<Driver detach command
	STO_DRIVER_GET_STATUS	= 4,	//!<Driver get status command
	STO_DRIVER_SELECT_SECTOR= 5,	//!<Driver device select sector command
	STO_DRIVER_DEVICE_ERASE	= 6,	//!<Driver device erase command
	STO_DRIVER_SECTOR_ERASE	= 7,	//!<Driver sector erase command
	STO_DRIVER_DEVICE_PROTE	= 8,	//!<Driver device write protect command
	STO_DRIVER_SECTOR_PROTE	= 9,	//!<Driver sector write protect command
	STO_DRIVER_SET_FLAG     = 10,   //!<Sflash operation flag
	STO_DRIVER_SECTOR_BUFFER= 11,   //!<Sfalsh buffer for a sector
	STO_DRIVER_FLASH_CONTROL = 12,      //!<Remote Flash Only! config remote flash writing enable
	STO_DRIVER_UPG_MODE_CONTROL = 13,   //!<Remote Flash Only! config P2P or M2S mode
	STO_DRIVER_UART_SPEED_CONTROL = 14, //!<Remote Flash Only! config UART high speed
	STO_DRIVER_SECTOR_ERASE_EXT = 15,   //!<Driver sector erase command
};

struct sto_device_stats
{
	UINT32 errors;					/* Device operate errors */
};

/*
#if (defined(SYS_OS_TASK_NUM))
#define STO_TASK_SUPPORT_NUM_MAX 	(SYS_OS_TASK_NUM + 1)
#else
#define STO_TASK_SUPPORT_NUM_MAX	16
#endif
*/
#define STO_TASK_SUPPORT_NUM_MAX		256

/*!@struct sto_device
@brief Structure sto_device, the basic structure between HLD and LLD of panel
*/
struct sto_device
{
	struct hld_device   *next;		       //!<Next device structure
	UINT32		type;					   //!<Interface hardware type
	INT8		name[HLD_MAX_NAME_SIZE];   //!<Device name
	UINT16		flags;				       //!<Interface flags, status and ability
	void		*priv;				       //!<Pointer to private data of hardware
	UINT32		base_addr;			       //!<Device base address
	UINT32		curr_addr[STO_TASK_SUPPORT_NUM_MAX];	//!<Current operate address
	UINT32		totol_size;			                    //!<Device totol space size, in K bytes
	unsigned char *sector_buffer;                       //!<Buffer for a sflash sector (64K)
	unsigned long flag;                                 //!<Flag of sflash operation
	OSAL_ID		mutex_id;
};

#define STO_FLAG_AUTO_ERASE     0x80000000    //!<Erase first before write if necessory
#define STO_FLAG_SAVE_REST      0x40000000    //!<Copy post-fix block from flash

/*!@struct sto_flash_info
@brief Structure sto_flash_info sflash settings info
*/
struct sto_flash_info
{
	UINT8	mode;			//!<Remote access P2P or M2S mode
	UINT32  sync_tmo;		//!<Remote access totoal sync interval in mS
	UINT32  flash_ctrl;		//!<Remote write enable
	UINT32  uart_baudrate;	//!<Remote access baudrate
	short	flash_deviceid_num;	//!<ID table length
	UINT8	*flash_deviceid;    //!<ID table
	UINT8	*flash_id;		    //!<Sector index
   	BOOL    enable_soft_protect;
	UINT8	*flash_io;		    //!<For sflash and sqi-flash, record io number: 1, 2 or 4
};

//#define P2P_MODE  DUPLEX_MODE	/* Remote access peer to peer mode */
//#define M2S_MODE  SIMPLEX_MODE	/* Remote access master to slave mode */

//INT32 sto_remote_flash_sync(struct sto_flash_info *param);		/* remote flash */
//INT32 sto_local_flash_attach(struct sto_flash_info *param);		/* local PARALLEL flash init */
//INT32 sto_remote_flash_attach(struct sto_flash_info *param);	/* remote PARALLEL flash init */

/*!
@brief register sto device and allocate resource
@param[in]  param  pointer to sflash sto settings
@retval  SUCCESS     attach success 
@retval  !SUCCESS    attach failure
*/
INT32 sto_local_sflash_attach(struct sto_flash_info *param);	/* local SERIAL flash init */
//INT32 sto_remote_sflash_attach(struct sto_flash_info *param);	/* remote SERIAL flash init */
// for compabile with old version
//#define sto_remote_flash_init    sto_remote_flash_attach

/*
enum remote_flash_ctrl_cmd {
	FLASH_CONTROL ,
	FLASH_SET_CMDADDR,
	FLASH_READ_TMO,
	UPG_MODE_CONTROL,
	UART_BAUDRATE_CONTROL
};
*/
#ifndef STO_PROTECT_BY_MUTEX
	#ifdef PFLASH_CI_SHARE_PIN
		#define STO_PROTECT_BY_MUTEX
	#endif	
#endif

#ifdef STO_PROTECT_BY_MUTEX
#define MUTEX_ENTER()    sto_mutex_enter()
#define MUTEX_LEAVE()    sto_mutex_exit()
#else
#define MUTEX_ENTER    osal_task_dispatch_off
#define MUTEX_LEAVE    osal_task_dispatch_on
#endif

/*!
 * @}
 */
#ifdef __cplusplus
}
#endif
#endif  /* __HLD_STO_DEV_H__ */
