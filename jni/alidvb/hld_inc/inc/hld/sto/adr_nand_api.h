#ifndef __ADR_HLD_NANDAPI_H__
#define __ADR_HLD_NANDAPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/*!@struct NAND_INFO
@brief nand basic info
 */
typedef struct
{
	UINT32 size;	     //!<total size of the NAND
	UINT32 erasesize;    //!<equal a blcok size
	UINT32 writesize;    //!<equal a page size
	UINT32 startAddr;    //!<kernel start address
}NAND_INFO;


/*!@struct mtd_part_info
@brief nand mtd info
 */
struct mtd_part_info {
	UINT32 size;	     //!<total size of the MTD
	UINT32 erasesize;    //!<equal a blcok size
	UINT32 writesize;    //!<equal a page size
};

/*!
@brief align size to pagesize
@param[in]  part_idx  partition index
@param[in]  size  need align value
@retval  align size
*/
UINT32 NF_align_to_page(UINT32 part_idx, UINT32 size);

/*!
@brief get a partition info
@param[in]  part_idx  partition index
@param[out]  info  pointer to mtd_part_info
@retval  >=0    get success
@retval  <0     get failure
*/
INT32 NF_get_part_info(UINT32 part_idx, struct mtd_part_info *info);

/*!
@brief save buf to a partition, must erase the partition first and be sure align size to pagesize
@will skip bad block
@param[in]  part_idx  partition index
@param[in]  buf  data to save
@param[in]  size  data size
@retval  >=0    save success/actual saved length
@retval  <0     save failure
*/
INT32 NF_save_partition(UINT32 part_idx, UINT8 *buf, UINT32 size);

/*!
@brief load a partition data to buf, be sure align size to pagesize
@will skip bad block
@param[in]   part_idx  partition index
@param[in]   buf  buffer for load
@param[out]  size  need to load size
@retval  >=0    load success/actual loaded length
@retval  <0     load failure
*/
INT32 NF_load_partition(UINT32 part_idx, UINT8 *buf, UINT32 size);

/*!
@brief erase a partition
@param[in]  part_idx  partition index
@retval  >=0    erase success
@retval  <0     erase failure
*/
INT32 NF_erase_partition(UINT32 part_idx);

/*!
@brief save buf data to a block of a partition, must erase the block first
@param[in]  part_idx  partition index
@param[in]  block_idx  block index in the partition (not include bad block)
@param[in]  buf  data to save, a block size
@retval  >=0    save success/actual saved length
@retval  <0     save failure
*/
INT32 NF_save_block(UINT32 part_idx,UINT32 block_idx, UINT8 *buf);

/*!
@brief load a block data of a partition to buf
@param[in]   part_idx  partition index
@param[in]   block_idx  block index in the partition (not include bad block)
@param[out]  buf  buffer for load, a block size
@retval  >=0    load success/actual loaded length
@retval  <0     load failure
*/
INT32 NF_load_block(UINT32 part_idx,UINT32 block_idx, UINT8 *buf);

/*!
@brief erase a block of a partition
@param[in]   part_idx  partition index
@param[in]   block_idx  block index in the partition (not include bad block)
@retval  >=0    erase success
@retval  <0     erase failure
*/
INT32 NF_erase_block(UINT32 part_idx,UINT32 block_idx);

/*!
@brief write buf data to a page in a block of a partition, must be sure this page is free and can not skip page to write
       (e.g. must write page0->page1->page2, forbidden page0->page2->page1)
@param[in]  part_idx  partition index
@param[in]  block_idx  block index in the partition (not include bad block)
@param[in]  page_idx  page index in the block
@param[in]  buf  data to write, a page size
@retval  >=0    write success/actual writed length
@retval  <0     write failure
*/
INT32 NF_write_page(UINT32 part_idx,UINT32 block_idx, UINT32 page_idx,UINT8 *buf);

/*!
@brief read a page data in a block of a partition to buf
@param[in]   part_idx  partition index
@param[in]   block_idx  block index in the partition (not include bad block)
@param[in]   page_idx  page index in the block
@param[out]  buf  buffer for read, a page size
@retval  >=0    read success/actual read length
@retval  <0     read failure
*/
INT32 NF_read_page(UINT32 part_idx,UINT32 block_idx, UINT32 page_idx,UINT8 *buf);

/*!
@brief write buf data to a sector in a block of a partition, must be sure the sector is free and can not skip sector to write
       1 sector = n pages (n=1,2,3...)
@param[in]  part_idx  partition index
@param[in]  block_idx  block index in the partition (not include bad block)
@param[in]  sector_idx  sector index in the block
@param[in]  sector  data to write, a sector size
@param[in]  sector_size  sector size, align to pagesize
@retval  >=0    write success/actual writed length
@retval  <0     write failure
*/
INT32 NF_write_sector(UINT32 part_idx,UINT32 block_idx, UINT32 sector_idx,UINT8 *sector, UINT32 sector_size);

/*!
@brief read a sector data in a block of a partition to buf
       1 sector = n pages (n=1,2,3...)
@param[in]   part_idx  partition index
@param[in]   block_idx  block index in the partition (not include bad block)
@param[in]   sector_idx  sector index in the block
@param[out]  sector  buffer for read, a sector size
@param[in]   sector_size  sector size, align to pagesize
@retval  >=0    read success/actual read length
@retval  <0     read failure
*/
INT32 NF_read_sector(UINT32 part_idx,UINT32 block_idx, UINT32 sector_idx,UINT8 *sector, UINT32 sector_size);

/*!
@brief write buf data to the specific area of a partition,
       it will not check and erase primitive data and caller must be sure this area is free
@will skip bad block       
@param[in]  part_idx  partition index
@param[in]  to  start offset in the partition
@param[in]  len  write data length
@param[in]  buf  data to write
@retval  >=0    write success/actual writed length
@retval  <0     write failure
*/
INT32 NF_write_part(UINT32 part_idx,UINT32 to, UINT32 len,UINT8 *buf);

/*!
@brief write buf data to the specific area of a partition, the function may erase block before write
       it will cost extra time to read block and erase block
@will skip bad block       
@param[in]  part_idx  partition index
@param[in]  to start offset in the partition
@param[in]  len write data length
@param[in]  buf  data to write
@retval  >=0    write success/actual writed length
@retval  <0     write failure
*/
INT32 NF_write_part_erase(UINT32 part_idx,UINT32 to, UINT32 len,UINT8 *buf);

/*!
@brief read the specific area data of a partition to buf
@will skip bad block
@param[in]   part_idx  partition index
@param[in]   from  start offset in the partition
@param[in]   len  read data length
@param[in]   buf  buffer for read
@retval  >=0    read success/actual read length
@retval  <0     read failure
*/
INT32 NF_read_part(UINT32 part_idx,UINT32 from, UINT32 len,UINT8 *buf);

/*!
@brief erase  physical block of a partition
@will not skip bad block
@param[in]   part_idx  partition index
@param[in]   block_idx  physical block index in the partition
@retval  >=0    erase success
@retval  <0     erase failure
*/
INT32 NF_erase_block_physical(UINT32 part_idx,UINT32 block_idx);

/*!
@brief read the specific area data of a partition in physical address to buf
@will not skip bad block
@param[in]   part_idx  partition index
@param[in]   from  start offset in the partition(physical address)
@param[in]   len  read data length
@param[in]   buf  buffer for read
@retval  >=0    read success/actual read length
@retval  <0     read failure
*/
INT32 NF_read_part_physical(UINT32 part_idx,UINT32 from, UINT32 len,UINT8 *buf);

/*!
@brief write buf data to the specific area of a partition by physical address,
       it will not check and erase primitive data and caller must be sure this area is free
@will not skip bad block       
@param[in]  part_idx  partition index
@param[in]  to  start offset in the partition (physical address)
@param[in]  len  write data length
@param[in]  buf  data to write
@retval  >=0    write success/actual writed length
@retval  <0     write failure
*/
INT32 NF_write_part_physical(UINT32 part_idx,UINT32 to, UINT32 len,UINT8 *buf);

/*!
@brief write buf data to the specific area of a partition by physical address, 
       the function may erase block before write, it will cost extra time to read block and erase block
@will not skip bad block
@param[in]  part_idx  partition index
@param[in]  to start offset in the partition (physical address)
@param[in]  len write data length
@param[in]  buf  data to write
@retval  >=0    write success/actual writed length
@retval  <0     write failure
*/
INT32 NF_write_part_physical_erase(UINT32 part_idx,UINT32 to, UINT32 len,UINT8 *buf);

/*!
@brief  get mtd(nand) device valid len
@param[in]   part_idx  partition index
@retval  >=0     get success/mtd valid length
@retval  <0    get failure
 */
int NF_get_part_valid_len(UINT32 part_idx);

/*!
@brief erase a space of a partition
@will skip bad block
@param[in]   part_idx  partition index
@param[in]   from  start erase address, need align to blocksize
@param[in]   len  erase length, need align to blocksize
@retval  >=0    erase success
@retval  <0     erase failure
*/
INT32 NF_erase_part(UINT32 part_idx,UINT32 from, UINT32 len);

/*!
@brief get a nand info
@param[in]  part_idx  partition index
@param[out]  info  pointer to mtd_part_info
@retval  !=0    get success
@retval  =0     get failure
*/
NAND_INFO * NF_get_nand_info(void);

/*!
@brief get first valid PMI data
@param[in]  PMI_buf  buffer pointer
@param[in]  pmi_len  PMI data len
@retval  >=0    get success
@retval  <0     get failure
*/
INT32 NF_get_PMI(UINT8* PMI_buf, UINT32 pmi_len);

/*!
@brief write PMI partition(part0)
@if PMI count(good block) < 2, forbidden update PMI partition
@param[in]  buffer_in  buffer pointer
@param[in]  buf_len  data len
@retval  >=0    get success
@retval  <0     get failure
*/
INT32 NF_write_PMI_partition(UINT8 *buffer_in, UINT32 buf_len);

/*!
@brief get part index in PMI by part name
@param[in]  part_name  part name
@retval  >= 0    part index
@retval  < 0     get failure
*/
INT32 NF_get_PMI_part_by_name(char *part_name);

/*!
@brief get nand flash size
@retval  >= 0    nand flash size
@retval  < 0     get failure
*/
INT32 NF_get_nand_size(void);

/*!
@brief get nand total mtd size
@retval  >= 0    total mtd size
@retval  < 0     get failure
*/
unsigned long long nand_get_mtds_size(void);

/*!
@brief get nand flash size for new ic
@retval  >= 0    nand flash size
@retval  < 0     get failure
*/
unsigned long long nand_get_size(void);
/*!
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif/* __HLD_NANDAPI_H__ */
