/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2005 Copyright (C)
*
*    File:    nim_tuner.h
*
*    Description:    This file contains QPSK Tuner Configuration AP Functions
*
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Aug.25.2005       Jun Zhu       Ver 0.1    Create file.
*****************************************************************************/

#ifndef __ADR_NIM_TUNER_H_
#define __ADR_NIM_TUNER_H_
/*
Nim_xxxx_attach
Function: INT32 nim_xxxx_attach (QPSK_TUNER_CONFIG_API * ptrQPSK_Tuner)
Description: QPSK Driver Attach function
Parameters:  QPSK_TUNER_CONFIG_API * ptrQPSK_Tuner, pointer to structure QPSK_TUNER_CONFIG_API
Return:         INT32, operation status code; configuration successful return with SUCCESS

Nim_Tuner _Init
Function: INT32 nim_Tuner_Init (UINT32* tuner_id,struct QPSK_TUNER_CONFIG_EXT * ptrTuner_Config);
Description: API function for QPSK Tuner Initialization
Parameters:  UINT32* tuner_id, return allocated tuner id value in same tuner type to demod driver.
		      struct QPSK_TUNER_CONFIG_EXT * ptrTuner_Config, parameter for tuner config
Return:         INT32, operation status code; configuration successful return with SUCCESS

Nim_Tuner_Control
Function: INT32 nim_Tuner _Control (UINT32 tuenr_id, UINT32 freq, UINT32 sym)
Description: API function for QPSK Tuner's Parameter Configuration
Parameters:  	UINT32 tuner_id, tuner device id in same tuner type
			UINT32 freq, Channel Frequency
			UINT32 sym, Channel Symbol Rate
Return:         INT32, operation status code; configuration successful return with SUCCESS

Nim_Tuner_Status
Function: INT32 nim_Tuner _Status (UINT32 tuner_id, UINT8 *lock)
Description: API function for QPSK Tuner's Parameter Configuration
Parameters:  UINT32 tuner_id, tuner device id in same tuner type
			UINT8 *lock, pointer to the place to write back the Tuner Current Status
Return:         INT32, operation status code; configuration successful return with SUCCESS
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <dvb_frontend_common.h>
/*! @addtogroup nim
 *  @{
 */

#define MAX_TUNER_SUPPORT_NUM	2
#define FAST_TIMECST_AGC	1
#define SLOW_TIMECST_AGC	0

#define Tuner_Chip_SANYO        9
#define Tuner_Chip_CD1616LF_GIH	8
#define Tuner_Chip_NXP		7
#define Tuner_Chip_MAXLINEAR	6
#define Tuner_Chip_MICROTUNE	5
#define Tuner_Chip_QUANTEK	4
#define Tuner_Chip_RFMAGIC  3
#define Tuner_Chip_ALPS		2	//60120-01Angus
#define Tuner_Chip_PHILIPS	1
#define Tuner_Chip_INFINEON	0
/****************************************************************************/
#define Tuner_Chip_MAXLINEAR 6
#define Tuner_Chip_EN4020      9     

#define _1st_i2c_cmd		0
#define _2nd_i2c_cmd		1

/*Front End State*/
#define TUNER_INITIATING	0
#define TUNER_INITIATED		1
#define TUNER_TUNING		2
#define TUNER_TUNED		3

//For TSI select
typedef enum
{
	NIM_0_SPI_0 = 0,
	NIM_0_SPI_1,
	NIM_1_SPI_0,
	NIM_1_SPI_1,
	NIM_0_SSI_0,
	NIM_0_SSI_1,
	NIM_1_SSI_0,
	NIM_1_SSI_1,	
} NIM_TSI_Setting;


/*****************************************************/
/*               dedicate for DVB-T                  */
/*****************************************************/
/*external demodulator config parameter*/


#define LNB_CMD_BASE		0xf0
#define LNB_CMD_ALLOC_ID	(LNB_CMD_BASE+1)
#define LNB_CMD_INIT_CHIP	(LNB_CMD_BASE+2)
#define LNB_CMD_SET_POLAR	(LNB_CMD_BASE+3)
#define LNB_CMD_POWER_EN	(LNB_CMD_BASE+4)
/*external lnb controller config parameter*/


/*****************************************************/
/*               dedicate for DVB-C                  */
/*****************************************************/
/*!@struct QAM_TUNER_CONFIG_DATA
@brief QAM_TUNER_CONFIG_DATA config parameter
*/


struct DEMOD_CONFIG_ADVANCED
{
    UINT32  qam_config_advanced; //bit0: demode_mode 0:j83b 1:j83ac;
                                 //bit1: ad sample clock 0: 27m, 1:54m;
    UINT32 qam_buffer_len;
    UINT32 qam_buffer_addr;
};



/*!@struct QAM_TUNER_CONFIG_API
@brief QAM_TUNER_CONFIG_API config parameter
*/

struct QAM_TUNER_CONFIG_API
{
	/* struct for QAM Configuration */
	struct QAM_TUNER_CONFIG_DATA tuner_config_data;

	/* Tuner Initialization Function */
	INT32 (*nim_Tuner_Init)(UINT32 * ptrTun_id, struct QAM_TUNER_CONFIG_EXT * ptrTuner_Config);

	/* Tuner Parameter Configuration Function */
	INT32 (*nim_Tuner_Control)(UINT32 Tun_id, UINT32 freq, UINT32 sym, UINT8 AGC_Time_Const, UINT8 _i2c_cmd);//since there will no bandwidth demand, so pass "sym" for later use.

	/* Get Tuner Status Function */
	INT32 (*nim_Tuner_Status)(UINT32 Tun_id, UINT8 *lock);

	/* Extension struct for Tuner Configuration */
	struct QAM_TUNER_CONFIG_EXT tuner_config_ext;
	
	struct EXT_DM_CONFIG ext_dem_config;
	struct DEMOD_CONFIG_ADVANCED dem_config_advanced;

	UINT32 qam_mode;                                         //!<J83A/J83B/J83C and Sample CLK select
    UINT32 demod_index;                                       // poe add

	
	UINT32 tuner_id;// kent, for defferent tuner
};



struct tuner_model
{
    UINT8 dev_ids;
    UINT8 dev_name[16];
};

#define NIM_MODE_MASK   0x0F
#define NIM_SAMP_MASK   0xF0



/*!
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // _NIM_TUNER_H_
