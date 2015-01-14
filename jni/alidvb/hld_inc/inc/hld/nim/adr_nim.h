/*****************************************************************************
*    Copyright (C)2003 Ali Corporation. All Rights Reserved.
*
*    File:    nim.c
*
*    Description:    This file contains mt312 basic function in HLD.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Feb.16.2003      Justin Wu       Ver 0.1    Create file.
*	2.	Jun.12.2003      George jiang    Ver 0.2    Porting NIM.
*   3.  Aug.22.2003      Justin Wu       Ver 0.3    Update.
*	4. July 17.2006	Joey Gao		Ver 0.4 		Add Diseqc 2.X support.
*****************************************************************************/


#ifndef	__ADR_HLD_NIM_H__
#define __ADR_HLD_NIM_H__

#include <hld/nim/adr_nim_dev.h>
#include <hld/nim/adr_nim_tuner.h>

/*! @addtogroup nim
 *  @{
 */

/* DiSEqC mode */
#define NIM_DISEQC_MODE_22KOFF		0	/* 22kHz off */
#define	NIM_DISEQC_MODE_22KON		1	/* 22kHz on */
#define	NIM_DISEQC_MODE_BURST0		2	/* Burst mode, on for 12.5mS = 0 */
#define	NIM_DISEQC_MODE_BURST1		3	/* Burst mode, modulated 1:2 for 12.5mS = 1 */
#define	NIM_DISEQC_MODE_BYTES		4	/* Modulated with bytes from DISEQC INSTR */
#define	NIM_DISEQC_MODE_ENVELOP_ON	5	/* Envelop enable*/
#define	NIM_DISEQC_MODE_ENVELOP_OFF	6	/* Envelop disable, out put 22K wave form*/
#define	NIM_DISEQC_MODE_OTHERS		7	/* Undefined mode */
#define	NIM_DISEQC_MODE_BYTES_EXT_STEP1		8	/*Split NIM_DISEQC_MODE_BYTES to 2 steps to improve the speed,*/
#define	NIM_DISEQC_MODE_BYTES_EXT_STEP2		9	/*(30ms--->17ms) to fit some SPEC */

/* Polarization */
#define NIM_PORLAR_HORIZONTAL	0x00
#define NIM_PORLAR_VERTICAL		0x01
#define NIM_PORLAR_LEFT			0x02
#define NIM_PORLAR_RIGHT		0x03

#define NIM_PORLAR_REVERSE		0x01
#define NIM_PORLAR_SET_BY_22K	0x02

#define DISEQC2X_ERR_NO_REPLY			0x01
#define DISEQC2X_ERR_REPLY_PARITY		0x02
#define DISEQC2X_ERR_REPLY_UNKNOWN	0x03
#define DISEQC2X_ERR_REPLY_BUF_FUL	0x04

/* QAM Mode */
//for DVB-C
#define QAM16	4
#define QAM32	5
#define QAM64	6
#define QAM128	7
#define QAM256	8

#ifdef __cplusplus
extern "C"
{
#endif

/* Socket management functions */
/*!
@brief open nim device
@param[in]  dev  pointer to nim device
@retval  SUCCESS     open success
@retval  !SUCCESS    open failure
*/
INT32 nim_open(struct nim_device *dev);

/*!
@brief close nim device
@param[in]  dev  pointer to nim device
@retval  SUCCESS     close success
@retval  !SUCCESS    close failure
*/
INT32 nim_close(struct nim_device *dev);

INT32 nim_io_control(struct nim_device *dev, INT32 cmd, UINT32 param);

/*!
@brief get nim lock status
@param[in]   dev  pointer to nim device
@param[out]  lock  get nim lock status: 1 lock; 0 not lock
@retval  SUCCESS     get success
@retval  !SUCCESS    get failure
*/
INT32 nim_get_lock(struct nim_device *dev, UINT8 *lock);

/*!
@brief get nim freqence
@param[in]   dev  pointer to nim device
@param[out]  freq  get nim frequency
@retval  SUCCESS     get success
@retval  !SUCCESS    get failure
*/
INT32 nim_get_freq(struct nim_device *dev, UINT32 *freq);

/*!
@brief get nim fec
@param[in]   dev  pointer to nim device
@param[out]  fec  get nim fec
@retval  SUCCESS      get success
@retval  !SUCCESSi    get failure
*/
INT32 nim_get_FEC(struct nim_device *dev, UINT8 *fec);

/*!
@brief get nim snr
@param[in]   dev  pointer to nim device
@param[out]  snr  get nim snr
@retval  SUCCESS     get success
@retval  !SUCCESS    get failure
*/
INT32 nim_get_SNR(struct nim_device *dev, UINT8 *snr);

/*!
@brief interface for nim ioctl extention of DVBC
@param[in]  dev  pointer to nim device
@param[in]  cmd  command type
@param[in]  param parameters
@return  RET_CODE
@retval  SUCCESS     call success
@retval  !SUCCESS    call failure
@note  ioctl cmds supported by nim module as belows:
<table class="doxtable" width="800" border="1" style="border-collapse:collapse;table-layout:fixed;word-break:break-all;">
  <tr>
    <th width="200">NIM IO COMMANDS</th>
    <th width="200">PARAM</th>
    <th width="400">COMMENT</th>
  </tr>

  <tr align="center">
    <td>NIM_DRIVER_CHANNEL_CHANGE</td>    <td>struct NIM_Channel_Change</td>    <td align="left">
	                                                                                <p>key channel change params:</p>
                                                                                    <p>freq</p>
                                                                                    <p>sys</p>
                                                                                    <p>modulation</p>
                                                                                </td>
  </tr>

  <tr align="center">
    <td>NIM_DRIVER_GET_CN_VALUE</td>    <td>null</td>    <td align="left"><p>Get NIM signal CNR</p></td>  
  </tr>

  <tr align="center">
    <td>NIM_DRIVER_GET_RF_LEVEL</td>    <td>null</td>    <td align="left"><p>Get NIM signal RSSI</p></td>  
  </tr>

  <tr align="center">
    <td>NIM_DRIVER_GET_BER_VALUE</td>    <td>null</td>    <td align="left"><p>Get NIM Bit Error Rate</p></td>  
  </tr>
</table>
*/
INT32 nim_ioctl_ext(struct nim_device *dev, INT32 cmd, void * param_list);


/*****************************************************/
/*               dedicate for DVB-S                  */
/*****************************************************/
INT32 nim_set_polar(struct nim_device *dev, UINT8 polar);
INT32 nim_set_12v(struct nim_device *dev, UINT8 flag);
//INT32 nim_channel_change_s(struct nim_device *dev, UINT32 freq, UINT32 sym, UINT8 fec);
INT32 nim_channel_search(struct nim_device *dev, UINT32 freq);
INT32 nim_DiSEqC_operate(struct nim_device *dev, UINT32 mode, UINT8* cmd, UINT8 cnt);
INT32 nim_DiSEqC2X_operate(struct nim_device *dev, UINT32 mode, UINT8* cmd, UINT8 cnt, UINT8 *rt_value, UINT8 *rt_cnt);

//INT32 nim_get_sym_s(struct nim_device *dev, UINT32 *sym);
//INT32 nim_get_BER_s(struct nim_device *dev, UINT32 *ber);
//INT32 nim_get_AGC_s(struct nim_device *dev, UINT8 *agc);
INT32 nim_get_fft_result(struct nim_device *dev, UINT32 freq, UINT32* start_adr);

/*****************************************************/
/*               dedicate for DVB-T                  */
/*****************************************************/
INT32 nim_disable(struct nim_device *dev);//Sam_chen 20050616
INT32 nim_channel_change_t(struct nim_device *dev, UINT32 freq, UINT32 bandwidth, UINT8 guard_interval, \
		UINT8 fft_mode, UINT8 modulation, UINT8 fec, UINT8 usage_type, UINT8 inverse, UINT8 priority);
INT32 nim_channel_search_t(struct nim_device *dev, UINT32 freq, UINT32 bandwidth, UINT8 guard_interval, \
		UINT8 fft_mode, UINT8 modulation, UINT8 fec, UINT8 usage_type, UINT8 inverse, \
		UINT16 freq_offset, UINT8 priority);
INT32 nim_get_gi(struct nim_device *dev, UINT8 *guard_interval);
INT32 nim_get_fftmode(struct nim_device *dev, UINT8 *fft_mode);
INT32 nim_get_modulation(struct nim_device *dev, UINT8 *modulation);
INT32 nim_get_spec_inv(struct nim_device *dev, UINT8 *inv);
//INT32 nim_get_AGC_t(struct nim_device *dev, UINT16 *agc);
INT32 nim_get_HIER_mode(struct nim_device *dev, UINT8 *hier);
INT8 nim_get_priority(struct nim_device *dev, UINT8 *priority);

/*****************************************************/
/*               dedicate for DVB-C                  */
/*****************************************************/
/*!
@brief get nim sym
@param[in]   dev  pointer to nim device
@param[out]  sym  get nim sym
@retval  SUCCESS     get success
@retval  !SUCCESS    get failure
*/
INT32 nim_get_sym(struct nim_device *dev, UINT32 *sym);

/*!
@brief get nim bit error rate
@param[in]   dev  pointer to nim device
@param[out]  ber  get nim ber
@retval  SUCCESS     get success
@retval  !SUCCESS    get failure
*/
INT32 nim_get_BER(struct nim_device *dev, UINT32 *ber);

/*!
@brief nim DiSEqC operation
@param[in]   dev  pointer to nim device
@param[out]  agc  get nim agc
@retval  SUCCESS     get success
@retval  !SUCCESS    get failure
 */
INT32 nim_get_AGC(struct nim_device *dev, UINT8 *agc);

/*!
@brief channel change tp settings
@param[in]  dev  pointer to nim device
@param[in]  freq  set nim freqence
@param[in]  sym  set nim sym
@param[in]  fec  set nim fec
@retval  SUCCESS     success
@retval  !SUCCESS    failure
*/
INT32 nim_channel_change(struct nim_device *dev, UINT32 freq, UINT32 sym, UINT8 fec);

/*!
@brief quick channel change settings
@param[in]  dev  pointer to nim device
@param[in]  freq  set nim freqence
@param[in]  sym  set nim sym
@param[in]  fec  set nim fec
@retval  SUCCESS     success
@retval  !SUCCESS    failure
*/
INT32 nim_quick_channel_change(struct nim_device *dev, UINT32 freq, UINT32 sym, UINT8 fec);

/*!
@brief register nim device and allocate resource
@param[in]  ptrQAM_Tuner  pointer to nim QAM_Tuner settings
@retval  SUCCESS     attach success
@retval  !SUCCESS    attach failure
*/
INT32 nim_s3202_attach(struct QAM_TUNER_CONFIG_API * ptrQAM_Tuner);

/*!
@brief unregister nim device 
@param[in]  dev  pointer to nim device
@retval  SUCCESS     dettach success
@retval  !SUCCESS    dettach failure
*/
INT32 nim_s3202_dettach(struct nim_device *dev);

/*!
@brief read nim register
@param[in]   dev  pointer to nim device
@param[in]   RegAddr  register offset
@param[out]  pData  pointer to read buffer
@param[in]   bLen  expected read lendth in byte
@retval  SUCCESS     success
@retval  !SUCCESS    failure
*/
INT32 nim_reg_read_ext(struct nim_device *dev, UINT32 RegAddr, UINT8 *pData, UINT8 bLen);
INT32 nim_reg_read(struct nim_device *dev, UINT8 RegAddr, UINT8 *pData, UINT8 bLen);

/*!
@brief write nim register
@param[in]   dev  pointer to nim device
@param[in]   RegAddr  register offset
@param[out]  pData  pointer to write buffer
@param[in]   bLen  expected write lendth in byte
@retval  SUCCESS     success
@retval  !SUCCESS    failure
*/
INT32 nim_reg_write_ext(struct nim_device *dev, UINT32 RegAddr, UINT8 *pData, UINT8 bLen);
INT32 nim_reg_write(struct nim_device *dev, UINT8 RegAddr, UINT8 *pData, UINT8 bLen);

/*!
@brief tuners recognized by i2c address
@param[in]   addr_list  tuners registered to recognize
@retval  tuner index recognized in addr_list, negative if failure
*/
INT32 nim_tunerself_adaption(struct nim_device *dev);

/*!
@brief allow tuner to enter standby or active mode if tuner supports
@param[in]   dev  pointer to nim device
@param[in]   standby  non-0 standby while 0 recover active
@retval  SUCCESS     success
@retval  !SUCCESS    failure
*/  
INT32 nim_tuner_isenter_standby(struct nim_device *dev, UINT32 standby);

/*****************************************************************************
 * INT32 nim_try_qammode(struct nim_device *dev, UINT32 *pmode) 
 *
 * set and get NIM work mode
 *
 * Arguments:
 * Parameter1: struct nim_device *dev   : Device
 * Parameter2: UINT32 *pmode            : pmode[0]   0 for J83A, 1 for J83B, 2 for J83C
 *                                        pmode[4:7] if_freq
 *
 * Return Value: INT32 real nim work mode 0 or 1
******************************************************************************/
INT32 nim_try_qammode(struct nim_device *dev, UINT32 *pmode);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif  /* __HLD_NIM_H__ */
