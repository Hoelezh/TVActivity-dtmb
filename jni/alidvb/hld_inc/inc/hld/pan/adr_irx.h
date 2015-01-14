#ifndef	__ADR_HLD_IRX_H__
#define	__ADR_HLD_IRX_H__

#ifdef __cplusplus
extern "C" {
#endif

/*! @addtogroup pan
 *  @{
 */
 
/*! @enum IR_CODE_FORMAT
    @brief  红外编码格式。
*/
enum IR_CODE_FORMAT{
	IR_NEC_FORMAT = 0,	//!<NEC。
	IR_LAB_FORMAT		//!<LAB。
};

/*! @enum IR_PULSE_POLAR
    @brief  红外脉冲极性。
*/
enum IR_PULSE_POLAR{
	IR_PULSE_STANDARD = 0,
	IR_PULSE_INVERTED
};

/*! @enum IR_CONNECT_MODE
    @brief  红外连接模式。
*/
enum IR_CONNECT_MODE{
	IR_CONNECT_BY_CABLE = 0,
	IR_CONNECT_BY_LED	
};

/*!@struct IRX_CONFIG_PARAM
   @brief 红外配置参数。
*/
struct IRX_CONFIG_PARAM{
	enum IR_CODE_FORMAT format;
	enum IR_PULSE_POLAR polar;
	enum IR_CONNECT_MODE connect;
	UINT32 reserved2;
};

/*!
 @}
 */
#ifdef __cplusplus
	}
#endif

#endif/*__HLD_IRX_H__*/

