/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 Copyright (C)
*
*    File:    sto_dev.h
*
*    Description:    This file contains all functions definition
*		             of storage driver.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	May.27.2003      Justin Wu       Ver 0.1    Create file.
*****************************************************************************/

#ifndef __ADR_HLD_STO_H__
#define __ADR_HLD_STO_H__

#include <hld/sto/adr_sto_dev.h>

#ifdef __cplusplus
extern "C" {
#endif

/* lseek origin param */
#define STO_LSEEK_SET		0
#define STO_LSEEK_CUR		1
#define STO_LSEEK_END		2

/*! @addtogroup sto
 *  @{
 */

/*!
@brief  open a storage device
@param[in]  dev  pointer to storage device
@retval  SUCCESS     open success
@retval  !SUCCESS    open failure
*/
INT32 sto_open(struct sto_device *dev);

/*!
@brief  close a storage device
@param[in]  dev  pointer to storage device
@retval  SUCCESS     close success
@retval  !SUCCESS    close failure
*/
INT32 sto_close(struct sto_device *dev);

/*!
@brief  long seek current operation point
@param[in]  dev  pointer to storage device
@param[in]  offset  offset of seek
@param[in]  origin  start base position
@retval  SUCCESS     seek success
@retval  !SUCCESS    seek failure
*/
INT32 sto_lseek(struct sto_device *dev, INT32 offset, int origin);

/*!
@brief  write data into storage
@param[in]  dev  pointer to storage device
@param[in]  data  data to write
@param[in]  len  data length to write 
@retval  SUCCESS     write success
@retval  !SUCCESS    write failure
*/
INT32 sto_write(struct sto_device *dev, UINT8 *data, INT32 len);

/*!
@brief  read data from storage
@param[in]   dev  pointer to storage device
@param[out]  data  buffer for read
@param[in]   len  data length to read
@retval  SUCCESS     read success
@retval  !SUCCESS    read failure
*/
INT32 sto_read(struct sto_device *dev, UINT8 *data, INT32 len);

/*!
@brief  io control cmd
@param[in]  dev  pointer to storage device
@param[in]  cmd  command type
@param[in]  param  parameters
@retval  SUCCESS     success
@retval  !SUCCESS    failure
@note  ioctl cmds supported by sto module as belows:
<table class="doxtable"  width="800" border="1" style="border-collapse:collapse;table-layout:fixed;word-break:break-all;" >
  <tr>
    <th width="200">STO IO COMMANDS</th>
    <th width="200">PARAM</th>
    <th width="400">COMMENT</th>
  </tr>

  <tr align="center">
    <td>STO_DRIVER_SECTOR_ERASE</td>    <td>UINT32</td>    <td align="left"><p>Auto erase sectors</p>
	                                                           <p>Uper 22 bits of MSB is start offset</p>
														       <p>Lower 10 bits of LSB is length in K bytes</p>
	                                                       </td>
  </tr>

  <tr align="center">
    <td>STO_DRIVER_SECTOR_ERASE_EXT</td>    <td>UINT32</td>    <td align="left"><p>Auto erase sectors</p>  
	                                                               <p>Array[0] is start offset</p>
	                                                               <p>Array[1] is length in K bytes</p>
															   </td>
  </tr>

  <tr align="center">
    <td>STO_DRIVER_SET_FLAG</td>    <td>UINT32</td>    <td align="left"><p>Set sflash operation flag</p>
	                                                       <p>STO_FLAG_AUTO_ERASE</p>
	                                                       <p>STO_FLAG_SAVE_REST</p>
													   </td>  
  </tr>
  
  <tr align="center">
    <td>STO_DRIVER_SECTOR_BUFFER</td>    <td>UINT32</td>    <td align="left"><p>Set sflash a sector buffer</p>
	                                                            <p>typical buffer size: 64K</p>
															</td>  
  </tr>
*/
INT32 sto_io_control(struct sto_device *dev, INT32 cmd, UINT32 param);

/*!
@brief  write data into storage with offset
@param[in]  dev  pointer to storage device
@param[in]  offset  offset position to write
@param[in]  data  data to write
@param[in]  len  data length to write
@retval  SUCCESS     write success
@retval  !SUCCESS    write failure
*/
INT32 sto_put_data(struct sto_device *dev, UINT32 offset, UINT8 *data, INT32 len);

/*!
@brief  read data from storage with offset
@param[in]   dev  pointer to storage device
@param[out]  data  buffer for read
@param[in]   offset  offset position to read
@param[in]   len  data length to read
@retval  SUCCESS     read success
@retval  !SUCCESS    read failure
*/
INT32 sto_get_data(struct sto_device *dev, UINT8 *data, UINT32 offset, INT32 len);

/*!
@brief  support Giga sflash extend commands
@param[in]   dev  pointer to storage device
@retval  bit offset in g_ali_sflash_commands_ext_group
*/
INT32 sto_support_giga_ext(struct sto_device *dev);

/*!
@brief  cancel support Giga sflash extend commands
@param[in]   dev  pointer to storage device
@retval  bit offset in g_ali_sflash_commands_ext_group
*/
INT32 sto_cancel_giga_ext(struct sto_device *dev);

/*!
@brief  Giga sflash extend erase command
@param[in]   dev  pointer to storage device
@retval  SUCCESS     erase success
@retval  !SUCCESS    erase failure
*/
INT32 sto_erase_giga_as(struct sto_device *dev);

/*!
@brief  Giga sflash extend read customid command
@param[in]   dev  pointer to storage device
@param[in]   buf  id buffer
@retval  zero for success, else fail
*/
INT32 sto_read_giga_customid(struct sto_device *dev, UINT8 *buf);

/*!
@brief  Giga sflash extend read security registers command
@param[in]   dev  pointer to storage device
@param[in]   gt   pointer of read config
@retval      read byte in fact
*/
INT32 sto_read_giga_as(struct sto_device *dev, UINT32 *gt);

/*!
@brief  Giga sflash extend write security registers command
@param[in]   dev  pointer to storage device
@param[in]   gt   pointer of write config
@retval      write byte in fact
*/
INT32 sto_write_giga_as(struct sto_device *dev, UINT32 *gt);

/*!
@brief  Giga sflash extend lock security registers command
@param[in]   dev  pointer to storage device
@retval  SUCCESS     lock success
@retval  !SUCCESS    lock failure
*/
INT32 sto_lock_giga_as(struct sto_device *dev);

/*!
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /* __HLD_STO_H__ */
