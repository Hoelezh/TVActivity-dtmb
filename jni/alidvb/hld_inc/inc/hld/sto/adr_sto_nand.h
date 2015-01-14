#ifndef __ADR_HLD_STONAND_H__
#define __ADR_HLD_STONAND_H__

#ifdef __cplusplus
extern "C" {
#endif

//#define MEMGETPMI         1
#define GETMTDBASICINFO   2

/*! @addtogroup sto
 *  @{
 */

#define MAX_PARTITION_NUM 31

/*!
@brief  open a mtd(nand) device
@param[in]  index  partition index
@param[in]  flags  access permission flags: O_RDONLY/O_RDWR
@retval  0     open success
@retval  !0    open failure
 */
int nand_open(UINT8 index, int flags);

/*!
@brief  get mtd(nand) device valid len
@param[in]   index  partition index
@retval  >=0     get success/mtd valid length
@retval  <0    get failure
 */
int nand_len(UINT8 index);

/*!
@brief  erase a mtd(nand) block
@param[in]  index  partition index
@param[in]  block_no  block number of partition: -1:erase the whole partition; >=0:erase the special block
@retval  0     erase success
@retval  !0    erase failure
 */
int nand_erase(UINT8 index, INT32 block_no);

/*!
@brief  read from mtd(nand) device
@param[in]   index  partition index
@param[out]  buf  buffer for read
@param[in]   size  data length to read
@retval  >=0     read success/actual read length
@retval  <0    read failure
 */
int nand_read(UINT8 index, void* buf, UINT32 size);

/*!
@brief  seek a mtd(nand) device
@param[in]   index  partition index
@param[out]  offset  align to pagesize
@param[in]   whenence  start position: SEEK_SET/SEEK_CUR/SEEK_END
@retval  0     seek success
@retval  !0    seek failure
 */
int nand_lseek(UINT8 index, int offset, int whenence);

/*!
@brief  write into a mtd(nand) device
@param[in]  index  partition index
@param[in]  buf  data to write
@param[in]  size  write size
@retval  >=0     write success/actual writed length
@retval  <0    write failure
 */
int nand_write(UINT8 index, void* buf, UINT32 size);

/*!
@brief  read in physical address from a mtd(nand) device
@param[in]   index  partition index
@param[out]  buf  buffer for read
@param[in]   start  read start address(physical address)
@param[in]   size  data length to read
@retval  >=0     read success/actual read length
@retval  <0    read failure
 */
int nand_physical_read(UINT8 index, void* buf, UINT32 start,UINT32 size);

/*!
@brief  io control cmd of mtd(nand)
@param[in]  index  partition index
@param[in]  cmd  command type
@param[in]  param  parameters
@retval
@note  ioctl cmds supported by nand_ioctl module as belows:
<table class="doxtable"  width="800" border="1" style="border-collapse:collapse;table-layout:fixed;word-break:break-all;" >
  <tr>
    <th width="200">STO IO COMMANDS</th>
    <th width="200">PARAM</th>
    <th width="400">COMMENT</th>
  </tr>

  <tr align="center">
    <td>GETMTDBASICINFO</td>    <td>UINT32</td>    <td align="left"><p>get nand partition info</p></td>  
  </tr>
 */
int nand_ioctl(UINT8 index, INT32 cmd, UINT32 param);

/*!
@brief  close a mtd(nand) device
@param[in]   index  partition index
@retval  0     close success
@retval  !0    close failure
 */
int nand_close(UINT8 index);

/*!
@brief  check nand flash have bad block or not from start address
@param[in]  index  partition index
@param[in]  start  start offset
@param[in]  len    length
@retval  0    have no bad block
@retval  -1   have bad block
 */
int nand_check(UINT8 index, UINT32 start, UINT32 len);

/*!
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif/* __HLD_STONAND_H__ */
