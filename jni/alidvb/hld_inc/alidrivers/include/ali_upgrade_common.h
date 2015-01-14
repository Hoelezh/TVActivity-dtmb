/****************************************************************************(I)(S)
 *  (C)
 *  ALi  Corporation, All Rights Reserved. 2009 Copyright (C)
 *  (C)
 *  File: ali_upgrade.h
 *  (I)
 *  Description: ali upgrade header
 *  (S)
 *  History:(M)
 *      	Date        			Author         	Comment
 *      	====        			======		=======
 * 0.		2013.3.6				Andy		Create
 ****************************************************************************/

#ifndef __ALI_UPGRADE_COMMON_H
#define __ALI_UPGRADE_COMMON_H


#define UPG_DESC_BOOT_RUN_NONE	0x03
#define UPG_DESC_BOOT_RUN_ENTER	0x00
#define UPG_DESC_BOOT_RUN_START	0x01
#define UPG_DESC_BOOT_RUN_OVER	0x02  

#define UPG_DESC_LOWLEVEL_RUN_NONE	0x03
#define UPG_DESC_LOWLEVEL_RUN_ENTER	0x00
#define UPG_DESC_LOWLEVEL_RUN_START	0x01
#define UPG_DESC_LOWLEVEL_RUN_OVER	0x02

#define UPG_DESC_APPLICATION_RUN_NONE	0x03
#define UPG_DESC_APPLICATION_RUN_ENTER	0x00
#define UPG_DESC_APPLICATION_RUN_START	0x01
#define UPG_DESC_APPLICATION_RUN_OVER	0x02


#define UPG_DESC_BOOT_UPG_NONE	0x07
#define UPG_DESC_BOOT_UPG_NO	0x00
#define UPG_DESC_BOOT_UPG_START	0x01
#define UPG_DESC_BOOT_UPG_OVER	0x02
#define UPG_DESC_BOOT_UPG_MAX	0x06  /* The MAX time to reboot after upgrade */

#define UPG_DESC_LOWLEVEL_UPG_NONE	0x07
#define UPG_DESC_LOWLEVEL_UPG_NO	0x00
#define UPG_DESC_LOWLEVEL_UPG_START	0x01
#define UPG_DESC_LOWLEVEL_UPG_OVER	0x02
#define UPG_DESC_LOWLEVEL_UPG_MAX	0x06  /* The MAX time to reboot after upgrade */

#define UPG_DESC_APPLICATION_UPG_NONE	0x07
#define UPG_DESC_APPLICATION_UPG_NO	    0x00
#define UPG_DESC_APPLICATION_UPG_START	0x01
#define UPG_DESC_APPLICATION_UPG_OVER	0x02
#define UPG_DESC_APPLICATION_UPG_MAX	0x08  /* The MAX time to reboot after upgrade */

typedef enum {
    SM_OP_READ = 0,
    SM_OP_WRITE,
    SM_OP_MAX,
}sm_op_t;

typedef enum {
    SM_TYPE_BOOT_RUN = 0,
    SM_TYPE_LOWLEVEL_RUN,
    SM_TYPE_APPLICATION_RUN,
    SM_TYPE_BOOT_UPG,
    SM_TYPE_LOWLEVEL_UPG,
    SM_TYPE_APPLICATION_UPG,
    SM_TYPE_MAX,
}sm_type_t;


typedef struct state_machine_t{
    unsigned int b_boot_status;
    unsigned int b_lowlevel_status;
    unsigned int b_application_status;
    unsigned int b_bootloader_upgrade;
    unsigned int b_lowlevel_upgrade;
    unsigned int b_application_upgrade;
    unsigned int b_bootloader_run_cnt;
    unsigned int b_lowlevel_run_cnt;
    unsigned int b_application_run_cnt;    
    unsigned int b_reserved1;
    unsigned int b_reserved2;

    //for expand
    unsigned int b_need_upgrade;
    unsigned int b_backup_exist;
    unsigned int b_lowlevel_backup_exist;
    unsigned int b_boot_backup_exist;
    unsigned int b_nor_upgrade;
    unsigned int b_nor_reserved;
    unsigned int b_nor_reserved_upgrade;
    unsigned int b_nand_reserved;
    unsigned int b_nand_reserved_upgrade;
    unsigned int b_nand_whole_upgrade;
}state_machine_t;

#define NAND_WHOLE_PARTITION_COUNT  2
#endif

