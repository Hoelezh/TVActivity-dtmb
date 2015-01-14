/****************************************************************************
 *
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2002 Copyright (C)
 *
 *  File: tsi.h
 *
 *  Description: This file provide MPEG-2 transport stream interface functions.
 *
 *  History:
 *      Date            Author            Version       	Comment
 *      ====          ======        =======  	=======
 *  1.  2005.4.22	Justin Wu	       0.1.000  		Create.
 *  2.  2005.8.19	Goliath Peng   0.1.001		Support S3601 TSI
 *  3.  2007.12.19	Eric Li		0.1.002 		Support M3329E TSI
 ****************************************************************************/

#ifndef	__LLD_TSI_H__
#define __LLD_TSI_H__

#ifdef __cplusplus
extern "C" {
#endif


//#include <adr_sys_config.h>

/* For TS input interface */
#define TSI_SPI_0		0		/* The ID of SPI_TS 0 */
#define	TSI_SPI_1		1		/* The ID of SPI_TS 1 */
#define	TSI_SPI_2		2		/* The ID of SPI_ATA  */
#define	TSI_SRC_REVD	3		/* The ID of reserved */
#define	TSI_SSI_0		4		/* The ID of SSI 0 */
#define	TSI_SSI_1		5		/* The ID of SSI 1 */
#if(SYS_CHIP_MODULE==ALI_S3602F)
#define	TSI_SSI_2		12		/* The ID of SSI 2 */
#define	TSI_SSI_3		13		/* The ID of SSI 3 */
#define PARA_MODE_SRC   6       /* The mode is TSCI_PARALLEL_MODE,and sourc from CARD B*/
#else
#define	TSI_SSI_2		6		/* The ID of SSI 2 */
#define	TSI_SSI_3		7		/* The ID of SSI 3 */
#define PARA_MODE_SRC   12       /* The mode is TSCI_PARALLEL_MODE,and sourc from CARD B*/
#endif
#define TSI_SSI2B_0		8		/* The ID of TSI_SSI  2Bit 0*/
#define TSI_SSI2B_1		9		/* The ID of TSI_SSI  2Bit 1*/
#define TSI_SSI4B_0		10		/* The ID of TSI_SSI  4Bit 0*/
#define TSI_SSI4B_1		11		/* The ID of TSI_SSI  4Bit 1*/

#define TSI_CI_SRC      7       /*for dmx 3 ,data from ci, ts select by tsa_source_sel*/

#if(SYS_CHIP_MODULE==ALI_S3602)
#define TSI_SPI_QPSK 	0 		/*SPI input from QPSK*/
#define TSI_SPI_EX1		0 		/*1st SPI input from DVB-C/T NIM*/
#define TSI_SPI_TSG 		2 		/*SPI input from TSG*/
#else
#define TSI_SPI_QPSK 	0 		/*SPI input from QPSK*/
#define TSI_SPI_EX1		1 		/*1st SPI input from DVB-C/T NIM*/
#define TSI_SPI_EX2 		2 		/*2nd SPI input from DVB-C/T NIM*/
#define TSI_SPI_TSG 		3 		/*SPI input from TSG*/
#endif
#define CI_PARA_MODE_SRC 	6 	/*CI_PARA_MODE_SOURCE can feed to DMX through TSB*/

/*TSI output*/
#define TSI_TS_A 		0x01 	/*TS_A is default output to DMX 0*/
#define TSI_TS_B 		0x02 	/*TS_B is default output to DMX 1*/

#define MODE_PARALLEL	1		
#define MODE_CHAIN		0

/* For DeMUX output */
#define	TSI_DMX_0		0x01	/* The ID of DMX 0 */
#define	TSI_DMX_1		0x02	/* The ID of DMX 1 */
#define	TSI_DMX_3		0x04	/* The ID of DMX 2 */

/* For the TSI attribute byte:
 * bit7: Enable flag: 0 for disable; 1 for enable.
 * bit5-6: Reserved.
 * bit4: CLOCK polarity: 0 for normal; 1 for invert.
 * bit3: SSI bit order: 0 for MSB first; 1 for LSB first.
 * bit2: ERROR polarity: 0 for active low; 1 for active high.
 * bit1: SYNC polarity: 0 for active low; 1 for active high.
 * bit0: VALID polarity: 0 for active low; 1 for active high.
 */

#if(SYS_CHIP_MODULE==ALI_S3602)

/***********************************************************************************************
* Declaration: 
*			tsi_mode_set(tsiid, attrib)
* Function:
*     		This function specify the TS Input attribute.
*
* Input Parameters:
* 	tsiid : TSI_SPI_0       //Internal SPI input from internal QAM
*      	  	TSI_SPI_1       //External SPI input from NIM
*      	 	TSI_SPI_2     	//SPI input from TSG
*      	  	TSI_SSI_0       //1st SSI input from DVB-C/T NIM
*      	  	TSI_SSI_1       //2nd SSI input from DVB-C/T NIM
*			TSI_SSI2B_0		//1st ASSI input 
*      	  	......
*
* 	attrib:	The specific value for different TSI. The rules are as following:
*			1)For SPI and SPI_TSG attribute-------
* 				bit7: Enable flag: 0 for disable; 1 for enable. 
* 				bit3-6: Reserved. 
* 				bit2: ERROR polarity: 0 for active low; 1 for active high.
*						 	(bit2 is only for SPI. The bit is reserved for SPI_TSG)
* 				bit1: SYNC polarity: 0 for active low; 1 for active high.
* 				bit0: VALID polarity: 0 for active low; 1 for active high.
* 			2)SSI and ASSI attribute
* 				bit7: Enable flag: 0 for disable; 1 for enable. 
* 				bit5-6: Reserved. 
* 				bit4: CLOCK polarity: 0 for normal; 1 for invert.
* 				bit3: Bit order: 0 for MSB first; 1 for LSB first.
* 				bit2: ERROR polarity: 0 for active low; 1 for active high.
* 				bit1: SYNC polarity: 0 for active low; 1 for active high.
* 				bit0: VALID polarity: 0 for active low; 1 for active high.
************************************************************************************************/
#define tsi_mode_set(tsiid, attrib)			tsi_s3602_mode_set(tsiid, attrib)

/***********************************************************************************************
 * Declaration:
 * 			tsi_select(ts_id, tsiid)
 *
 * Function:
 *     		1.Select TS input source for TS_A or TS_B. 
 * 			2.TS_A could be the source for CI A, TS B could be the sorce for CI B.
 *
 * Input Parameters:
 * ts_id :  TSI_TS_A 	// TS A
 *            TSI_TS_B 	// TS B
 *
 * tsiid :   TSI_SPI_0       //Internal SPI input from internal QAM
 *           TSI_SPI_1       //External SPI input from NIM
 *           TSI_SPI_2       //SPI input from TSG
 *           TSI_SSI_0       //1st SSI input from DVB-C/T NIM
 *           TSI_SSI_1       //2nd SSI input from DVB-C/T NIM
 *           TSI_SSI2B_0     //1st ASSI input 
 *           ......
 ***********************************************************************************************/
#define tsi_select(ts_id, tsiid)		tsi_s3602_select(ts_id, tsiid)

/***********************************************************************************************
 * Declaration:
 * 			tsi_dmx_src_select(dmxid, ts_id)
 *
 * Function:
 * 			Select TS chanel(TS_A or TS_B) for DMX_0 or DMX_1.
 *
 * Input Parameters:
 * dmxid : TSI_DMX_0    // The ID of DMX 0
 *             TSI_DMX_1    // The ID of DMX 1
 *
 * ts_id :  TSI_TS_A 	// TS A
 *            TSI_TS_B 	// TS B
 ***********************************************************************************************/
#define tsi_dmx_src_select(dmxid, ts_id) 	tsi_s3602_dmx_src_select(dmxid, ts_id)

/***********************************************************************************************
 * Declaration:
 * 				tsi_check_dmx_src(dmxid, p_ts_id, p_tsi_id, p_ci_mode)
 *
 * Function:
 * 				1.This function is used to check dmx's Input TS Source, Input TS Stream and CI mode.
 * 				2.The input TS id can be TSI_TS_A or TSI_TS_B, the input TS stream can be any TSI input stream.
 *
 * Input Parameters:
 * 	dmx_id : 	TSI_DMX_0    // The ID of DMX 0
 *          	TSI_DMX_1    // The ID of DMX 1
 *
 * Output Parameters: ( the type of the following 3 parameters should be  UINT8*  )
 * 	channel_id :TSI_TS_A 	// TS A
 *            	TSI_TS_B 	// TS B
 *
 * input_id: 	 TSI_SPI_0       //Internal SPI input from internal QAM
 *           TSI_SPI_1       //External SPI input from NIM
 *           TSI_SPI_2       //SPI input from TSG
 *           TSI_SSI_0       //1st SSI input from DVB-C/T NIM
 *           TSI_SSI_1       //2nd SSI input from DVB-C/T NIM
 *           TSI_SSI2B_0     //1st ASSI input 
 *           ......
 *
 * p_ci_mode:	MODE_PARALLEL	//Parallel CI mode, TS_A pass CI card A; TS_B pass CI card B.
 * 			MODE_CHAIN		//Serial CI mode, TS_A pass CI card A and CI card B.
 ***********************************************************************************************/
#define tsi_check_dmx_src(dmx_id, channel_id, input_id, ci_mode) tsi_s3602_check_dmx_src(dmx_id, channel_id, input_id, ci_mode)


/***********************************************************************************************
 * Declaration:
 * 				tsi_chg_tsiid(raw_tsi,chg_tsi,chg_en)
 *
 * Function:
 * 				1.Control the swap of SPI_0 and SPI_1
 *
 * Input Parameters:
 * 	raw_tsi : 	No used
 *	chg_tsi : 	No used
 *  chg_en :	0, disable swap; 1, enable swap
 ***********************************************************************************************/
#define tsi_chg_tsiid(raw_tsi,chg_tsi,chg_en)	tsi_s3602_chg_tsiid(raw_tsi,chg_tsi,chg_en)//do{}while(0)//tsi_s3602_chg_tsiid(raw_tsi,chg_tsi,chg_en)


/***********************************************************************************************
 * Declaration:
 * 			tsi_parallel_mode_set(para)
 *
 * Function:
 * 			1.Set the work mode of CI_A and CI_B
 *
 * Input Parameters:
 * 	para : 	MODE_CHAIN, CI_A and CI_B work in daisy chain; 
 *			MODE_PARALLEL, CI_A and CI_B work in parallel mode
 ***********************************************************************************************/
#define tsi_parallel_mode_set(para)  		tsi_s3602_parallel_mode_set(para)//do{}while(0)//tsi_s3602_parallel_mode_set(para)

/***********************************************************************************************
* Declaration:
*          tsi_para_src_select(ci_id,chg_en)
*
* Function:
*          1.Select the CI bypass for TSA and TSB 
*
* Input Parameters:
*  ci_id : 	CI_Card_0 	// CI_Card_0 is for TSA
*           CI_Card_1 	// 3701C have no CI_Card_1
*  chg_en : 0, TS pass CI; 1, TS not pass CI
***********************************************************************************************/
#define tsi_para_src_select(ci_id,chg_en) 		tsi_s3602_para_src_select(ci_id,chg_en)


#elif(SYS_CHIP_MODULE==ALI_M3329E)

#define tsi_parallel_mode_set(para)  		tsi_m3329e_parallel_mode_set(para) // 0: serial mode; 1: parallel mode
#define tsi_mode_set(tsiid, attrib)			tsi_m3329e_mode_set(tsiid, attrib)

/***********************************************************************************************
 * tsi_select(ts_id, tsiid)
 *
 *     This function select source for TS_A or TS_B. TS_A is default output to DMX 0,  TS_B is default output to DMX 1.
 * TS A is the source for Cam card A, TS B is the sorce for Cam card B.
 *
 * Parameters:
 * ts_id :  TSI_TS_A 	// TS A
 *            TSI_TS_B 	// TS B
 *
 * tsiid: 	TSI_SPI_QPSK 	//SPI input from QPSK
 * 		TSI_SPI_EX1 		//1st SPI input from DVB-C/T NIM
 * 		TSI_SSI_0 		//1st SSI input from DVB-C/T NIM
 * 		TSI_SSI_1 		//2nd SSI input from DVB-C/T NIM
 * 		TSI_SPI_TSG 		//SPI input from TSG
 ***********************************************************************************************/
#define tsi_select(ts_id, tsiid)				tsi_m3329e_select(ts_id, tsiid)

/***********************************************************************************************
 * tsi_dmx_src_select(dmxid, ts_id)
 *
 * This function select input TS for DMX_0 or DMX_1, the input TS id can be TSI_TS_A or TSI_TS_B
 *
 * Parameters:
 * dmxid : TSI_DMX_0    // The ID of DMX 0
 *             TSI_DMX_1    // The ID of DMX 1
 *
 * ts_id :  TSI_TS_A 	// TS A
 *            TSI_TS_B 	// TS B
 ***********************************************************************************************/
#define tsi_dmx_src_select(dmxid, ts_id) 	tsi_m3329e_dmx_src_select(dmxid, ts_id)

/***********************************************************************************************
 * tsi_check_dmx_src(dmxid, p_ts_id, p_tsi_id, p_ci_mode)
 *
 * This function is used to check dmx's input source, input TS stream and CI mode.
 * The input TS id can be TSI_TS_A or TSI_TS_B, the input TS stream can be any TSI input stream.
 *
 * Input Parameters:
 * dmxid : TSI_DMX_0    // The ID of DMX 0
 *             TSI_DMX_1    // The ID of DMX 1
 *
 * Output Parameters: ( the type of the following 3 parameters should be  UINT8*  )
 * p_ts_id :	TSI_TS_A 	// TS A
 *            	TSI_TS_B 	// TS B
 *
 * p_tsi_id: 	TSI_SPI_QPSK 	//SPI input from QPSK
 * 			TSI_SPI_EX1 		//1st SPI input from external DVB-C/T NIM
 * 			TSI_SSI_0 		//1st SSI input from external DVB-C/T NIM
 * 			TSI_SSI_1 		//2nd SSI input from external DVB-C/T NIM
 * 			TSI_SPI_TSG 		//SPI input from TSG
 *
 * p_ci_mode:	MODE_PARALLEL	//Parallel CI mode, TS_A pass CI card A; TS_B pass CI card B.
 * 			MODE_CHAIN		//Serial CI mode, TS_A pass CI card A and CI card B.
 ***********************************************************************************************/
#define tsi_check_dmx_src(dmxid, p_ts_id, p_tsi_id, p_ci_mode) tsi_m3329e_check_dmx_src(dmxid, p_ts_id, p_tsi_id, p_ci_mode)
#else
#define tsi_parallel_mode_set(para)  		do{}while(0)
#define tsi_card_src_select(tsiid) 			do{}while(0)
#define tsi_mode_set(tsiid, attrib)			tsi_m3202_mode_set(tsiid, attrib)
#define tsi_select(dmxid, tsiid)			tsi_m3202_select(dmxid, tsiid)
#define tsi_dmx_src_select(dmxid, ts_id)	do{}while(0)

#endif

#ifdef __cplusplus
}
#endif

#endif	/* __LLD_TSI_H__ */



