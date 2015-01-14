#ifndef _ALI_MTD_COMMON_H_
#define _ALI_MTD_COMMON_H_

#define PMIMAXLENTH   512
#define SYSINFOMAXLENTH   4096
#define SHAFILEPATH   32
#define ALI_PART_NUM  32
#define FLASHCMD_EXT_OFFSETBIT_FOR_ANONYMOUS  0
#define FLASHCMD_EXT_OFFSETBIT_FOR_GIGA       1

#define FLASHCMD_EXT_OFFSETBIT_FOR_SEALED     63

struct giga_as_transfer_user
{
	uint32_t op_reg_addr;
	uint32_t op_data_len;
	uint8_t *op_data_buf;
};


#define ALI_FLASH_SECTOR_ALIGN  _IO('M', 24)
#define ALI_FLASH_SECTOR_START  _IO('M', 25)
#define ALI_FLASH_SECTOR_SIZE  _IO('M', 26)
#define MEMGETPMI            _IOR('M',27,struct pmi_info_user)
#define MEMWRITEPMI          _IOW('M',28,struct pmi_info_user)
#define MEMGETSYSINFO            _IOR('M',29,struct sys_info_user)
#define MEMWRITESYSINFO          _IOW('M',30,struct sys_info_user)
#define MEMGETCHECKPART          _IOR('M',31,struct part_check_user)
#define MEMREPLACEPART           _IOR('M',32,struct part_check_user)
#define MEMCOMPAREWITHSHAFILE    _IOR('M',33,struct part_check_user)
#define MEMRESETNANDSTATS        _IOW('M',34,struct part_check_user)
#define ALI_FLASH_SECTOR_OTP_RW       _IO('M', 35)
#define ALI_FLASH_SECTOR_OTP_WRITE        _IO('M', 36)
#define ALI_FLASH_SECTOR_OTP_ERASE        _IO('M', 37)
#define ALI_FALSH_SECTOR_OTP_GET_STATUS   _IO('M', 38)
#define ALI_FALSH_SECTOR_OTP_SET_STATUS   _IO('M', 39)

#define ALI_FLASH_CONFIG_CMD_EXT_GROUP  _IOW('M', 40, unsigned int)
#define ALI_GIGA_FLASH_READ_CSTMID      _IOR('M', 41, unsigned int)
#define ALI_GIGA_FLASH_ESR              _IO('M', 42)
#define ALI_GIGA_FLASH_PSR              _IOW('M', 43, struct giga_as_transfer_user)
#define ALI_GIGA_FLASH_RSR              _IOR('M', 44, struct giga_as_transfer_user)
#define ALI_GIGA_FLASH_LOCKSR           _IO('M', 45)


struct pmi_info_user {
  unsigned char buf_start[PMIMAXLENTH];
  unsigned int offset;
  unsigned int length;
};


struct sys_info_user {
//  unsigned char __user *mac_buf;
    unsigned char sys_buf[SYSINFOMAXLENTH];
    unsigned int offset;
    unsigned int length;
};

struct part_check_user{
   int part_num_1;
   int part_num_2;
   unsigned int index_len;
   char file_path[SHAFILEPATH];
};

struct sys_allkeys_user{
    unsigned char *keybuf;
    unsigned char index; //reserved for future use
};

/*
struct img_info_user {
  unsigned char *img_bin;
  unsigned int img_start;
  unsigned int img_num;
  unsigned int img_size;
};
*/

struct alinand_part_info {
    uint32_t offset;
    uint32_t size;
};

struct part_user_info {
    int totalnum;
    /*
    *  Notice: ali private partition can not 
    *  be re-lay-outed 
    */
    struct alinand_part_info part_info[ALI_PART_NUM]; 
};
#define ALI_UPDATE_MTDINFO          _IOW('M', 60, struct part_user_info)
#define MEMGETALLKEYS     _IOR('M',61,struct sys_allkeys_user)
#define MEMWRITEALLKEYS   _IOW('M',62,struct sys_allkeys_user)
#endif
