/****************************************************************************
 *
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2002 Copyright (C)
 *
 *  File: adr_retcode.h
 *
 *  Description: This file define the return code for all application.
 *
 *  History:
 *      Date        Author      Version  Comment
 *      ====        ======      =======  =======
 *  1.  2002.11.12  Justin Wu   0.1.000  Initial
 *  2.  2002.11.21  Liu Lan     0.1.001  Add for OSD & Decoder
 *  3.  2003.02.19  Justin Wu   0.1.002  Add for I2C
 ****************************************************************************/

#ifndef	__ADR_RETCODE_H__
#define __ADR_RETCODE_H__

#ifdef __cplusplus
extern "C" {
#endif

/*! @addtogroup OSAL
 *  @{
 */

#define DMX_ERROR_BASE    	-100
#define PROGRAM_CONFIG_EEPROM_BLANK      (DMX_ERROR_BASE - 1) /* no program config info*/
#define PROGRAM_DATABASE_EMPTY           (DMX_ERROR_BASE - 2) /* program database is empty*/
#define PROGRAM_CONFIG_EEPROM_ERROR      (DMX_ERROR_BASE - 3) /* program config error in eeprom*/
#define XPONDER_CONFIG_EEPROM_BLANK      (DMX_ERROR_BASE - 4) /* no transponder config info*/
#define DMX_XPNDR_DATABASE_EMPTY         (DMX_ERROR_BASE - 5) /* tansponder database is empty*/
#define XPONDER_CONFIG_EEPROM_ERROR      (DMX_ERROR_BASE - 6) /* transponder config error in eeprom*/
#define ERR_TS_PACK                      (DMX_ERROR_BASE - 7)
#define ERR_NO_SDT                       (DMX_ERROR_BASE - 8)
#define ERR_PROG_NUM					 (DMX_ERROR_BASE - 9)

#define I2C_ERROR_BASE		-200
#define ERR_I2C_SCL_LOCK	(I2C_ERROR_BASE - 1)	/* I2C SCL be locked */
#define ERR_I2C_SDA_LOCK	(I2C_ERROR_BASE - 2)	/* I2C SDA be locked */
#define ERR_I2C_NO_ACK		(I2C_ERROR_BASE - 3)	/* I2C slave no ack */

#define ERR_FLASH_OFFSET_ERROR  -300
#define ERR_FLASH_NO_BUFFER     -301
#define ERR_FLASH_NEED_ERASE    -302
#define ERR_FLASH_WRITE_FAIL    -303
#define ERR_FLASH_READ_FAIL     -304

#define ERR_TEMPINFO_ID_USED    -310
#define ERR_TEMPINFO_NO_SPACE   -311
#define ERR_TEMPINFO_NO_MEMORY  -312
#define ERR_TEMPINFO_NOT_OPEN   -313
#define ERR_TEMPINFO_WRITE_FAIL -314
#define ERR_TEMPINFO_NEED_ERASE -315

//! @enum amsret_e
//! @brief AMS统一返回值(AMSRET)，取值范围为-99到255。
typedef enum {
    	/* Common return value, and its range from -99 to 0 */
	SUCCESS = 0,  //!< Success return
	ERR_FAILURE     = -1,      //!< Common error, operation not success
	ERR_NO_MEM      = -2,      //!< Not enough memory error
	ERR_LONG_PACK   = -3,      //!< Package too long
	ERR_RUNT_PACK   = -4,      //!< Package too short
	ERR_TX_BUSY     = -5,      //!< TX descriptor full
	ERR_DEV_ERROR   = -6,      //!< Device work status error
	ERR_DEV_CLASH   = -7,      //!< Device clash for same device in queue
	ERR_QUEUE_FULL  = -8,      //!< Queue node count reached the max. val
	ERR_NO_DEV      = -9,      //!< Device not exist on PCI
	ERR_MAX_LIMIT   = -10,     //!< Maximum limit

	ERR_PARA        = -11,     //!< Parameter is invalid
	ERR_ID_FULL     = -12,     //!< No more ID available
	ERR_ID_FREE     = -13,     //!< Specified ID isn't allocated yet

	ERR_OFF_SCRN    = -20,     //!< Block is out off the screen
	ERR_V_OVRLAP    = -21,     //!< Block is overlaped in vertical
	ERR_BAD_CLR     = -22,     //!< Invalid Color Mode code
	ERR_OFF_BLOCK   = -23,     //!< Bitmap is out off the block
	ERR_TIME_OUT    = -24,     //!< Waiting time out
	ERR_BUSY		= -25,     //!< Task busy status
	ERR_STATUS      = -26,     //!< Module status error
	ERR_BUFFER_LEN  = -27,     //!< Buffer length error

    	/* SIP(SI Parser) return value, and its range from 1 to 20 */
	SIP_ERR_PRIVATE_DESCS_OVERFLOW = 1, //!< no more private descriptor handler can be registered
	SIP_ERR_NETWORK_NAME_OVERFLOW,      //!< networkname is too long, not saved
	SIP_ERR_NIT_TS_SERVICES_OVERFLOW,   //!< services number overflow in nit descriptor
	SIP_ERR_NIT_TS_OVERFLOW,            //!< ts number overflow in nit
	SIP_ERR_SECTION_LENGTH_OVERFLOW,    //!< section length is larger than buffer size
	SIP_ERR_NETWORK_CNT_OVERFLOW,       //!< network count overflow
	SIP_ERR_PAT_SERVICES_OVERFLOW,      //!< services number overflow in pat
	SIP_ERR_CA_NUM_OVERFLOW,            //!< too many ca sys in ca descriptor
	SIP_ERR_AUDIO_639LAN_OVERFLOW,      //!< too many audio 638languages
	SIP_ERR_PMT_AUDIO_CNT_OVERFLOW,     //!< too many audio streams in pmt
	SIP_ERR_EMM_CNT_OVERFLOW,           //!< emm count overflow
	SIP_ERR_SDT_NAME_BUF_OVERFLOW,      //!< sdt name buffer overflow
	SIP_ERR_SDT_TS_CNT_OVERFLOW,        //!< sdt actual & other total number overflow
	SIP_ERR_SDT_SERVICES_OVERFLOW,      //!< services number overflow in sdt
	SIP_ERR_BOUQUET_NAME_OVERFLOW,      //!< bouquet name is too long
	SIP_ERR_BAT_SERVICES_OVERFLOW,      //!< services number overflow in bat
	SIP_ERR_BAT_CNT_OVERFLOW,           //!< bat count overflow
	SIP_ERR_STOP_PARSER,                //!< fate error , parser has to be stopped

	/* SIM(SI Monitor) return value, and its range from 21 to 30 */

	/* SIS(SI Search) return value, and its range from 31 to 50 */
	SIS_ERR_WORKSPACE_SIZE = 31,
	SIS_ERR_ALLOC_OBJ_FAIL,
	SIS_ERR_NIT_OTHER_COUNT,
	SIS_ERR_SDT_OTHER_COUNT,
	SIS_ERR_TUNE,
	SIS_ERR_TP_FULL,
	SIS_ERR_PROGRAM_FULL,
	SIS_ERR_TS_ID,
	SIS_ERR_PAT_TIMEOUT,
	SIS_ERR_NIT_TIMEOUT,
	SIS_ERR_PMT_TIMEOUT,
	SIS_ERR_SDT_TIMEOUT,
	SIS_ERR_BAT_TIMEOUT,

	/* NVOD return value, and its range from 51 to 60 */
	NVOD_ERR_DATA_NOT_FOUND = 51, //!< 没有找到相应信息
	NVOD_ERR_PARA           ,     //!< 参数错误
	NVOD_ERR_MAX_LIMIT      ,     //!< 超出最大范围
	NVOD_ERR_NO_MEM		,         //!< 内存分配失败
	NVOD_ERR_DATA           ,     //!< 数据错误
	NVOD_ERR_LOCK           ,     //!< 锁频失败
	NVOD_ERR_FAILURE        ,     //!< 失败

	/* EPG return value, and its range from 61 to 90 */
	EPG_ERR_FLAG_FAIL         = 61, //!< 模块初始化时创建flag失败
	EPG_ERR_SERVICE_NOT_EXIST = 62, //!< 获取service状态时，service不存在
	EPG_ERR_SERVICE_EXIST     = 63, //!< 添加service时，service已经存在了
	EPG_ERR_SERVICE_OVERFLOW  = 64, //!< EPG模块的service列表满了
	EPG_ERR_TP_OVERFLOW       = 65, //!< EPG模块的TP列表满了
	EPG_ERR_DB_FULL           = 66, //!< EPG模块的event个数满了
	EPG_ERR_TP_NOT_EXIST,           //!< 收到other pf/sch section数据时，无法通过其TS_ID列表找到对应的TP
	EPG_ERR_TABLE_ID_OVERFLOW,      //!< sch table id overflow
	EPG_ERR_TABLE_ID,               //!< 错误的table id
	EPG_ERR_PF_SECTION_NUM,         //!< 错误的pf section number
	ERR_ALLOC_FILTER_FAIL,          //!< 向DMX申请filter失败
	EPG_ERR_ENABLE_FILTER_FAIL,     //!< DMX enable filter失败
	EPG_ERR_DEVICE,                 //!< 获取DMX等设备失败
	EPG_ERR_POS_OVERFLOW,           //!< 从event view读取一个event时，position越界
	EPG_ERR_VIEW_NULL,              //!< event view为空
	EPG_ERR_SAME_EVENT,             //!< 有重复相同的event
	EPG_ERR_VIEW_OVERFLOW,          //!< 创建event view时，符合条件的event超过view的最大个数
	EPG_ERR_SHT_DESC_REPEAT,        //!< 重复的short event descriptor
	EPG_ERR_DESC_OVERFLOW,          //!< extend event descriptor的个数超过16（EN300468）个
	EPG_ERR_DESC_LEN          = 80, //!< descriptor的长度错误
	EPG_ERR_PARSE_BUFFER_NULL = 81, //!< EIT Parser的buffer为空
	EPG_ERR_VIEW_BUFFER_NULL  = 82, //!< Event view的buffer为空
	EPG_ERR_EVENT_BUFFER_NULL = 83, //!< 内部的event缓冲区为空
	EPG_ERR_LANG_OVERFLOW     = 84, //!< 支持的多语言个数溢出
	EPG_ERR_SECTION_LEN       = 85, //!< EIT section长度错误
	EPG_ERR_EVENT_LOOP_LEN    = 86, //!< EIT event loop的长度错误

	/* DB return value, and its range is from 91 to 120 */
	DBERR_PARAM = 91,      //!< invalid parameter
	DBERR_RECLAIM,         //!< flash reclaim fail
	DBERR_FLASH_FULL,      //!< flash full of valid data
	DBERR_EXSITS,          //!< node already exist
	DBERR_CMDBUF_FULL,     //!< command buffer full
	DBERR_INIT,            //!< error in init
	DBERR_MAX_LIMIT,       //!< node cnt to max limit
	DBERR_UPDATE,          //!< update data fail
	DBERR_ID_ASSIGN,       //!< fail when assign ID to a new node

	DBERR_BO_WRITE,        //!< flash wirte error
	DBERR_BO_READ,         //!< flash read error
	DBERR_BO_ERASE,        //!< flash erase error
	DBERR_BO_BAD_HEADER,   //!< node header errupted
	DBERR_BO_THRESHOLD,    //!< flash free space to threshold
	DBERR_BO_NEED_RACLAIM, //!< need reclaim
	DBERR_BO_INIT,         //!< addr init failed
	DBERR_BO_FILE_CREAT,   //!< db file not exist, new create

	DBERR_DO_TABLE,        //!< create table failed
	DBERR_DO_VIEW,         //!< create view failed

	DBERR_NOFOUND,         //!< node not found
	DBERR_PACK,            //!< error in node packing and unpacking
	DBERR_MALLOC,          //!< buffer not enough or overflow
	DBERR_DEFAULT,         //!< error when load default
	DBERR_NODEBUF_FULL,    //!< node data  buffer overflow
	DBERR_NEED_UPDATE,     //!< need call update function


	/* PUB return value, and its range from 121 to 130 */
	PUS_ERR_MUTEX_CREATE_FAIL = 121,

} amsret_e;

/*!
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __RETCODE_H__ */

