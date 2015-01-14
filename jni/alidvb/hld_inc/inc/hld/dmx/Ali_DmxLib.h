/* DO NOT modify this header file!!!! */
#ifndef _ALI_DMX_LIB_H_
#define _ALI_DMX_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <adr_basic_types.h>
/*! @addtogroup dmxlib
 *  @{
 */

#define ALI_DMX_SEC_MATCH_MAX_LEN     32 //!<section mask深度，请勿改动。
#define ALI_DMX_TS_STREAM_MAX_PID_CNT 96 //!<一个TS stream最多可以同时收取的TS PID个数，请勿改动。


/*! @enum ALI_DMX_ERR_CODE
@brief ALI DMX LIB的错误码，调用ALI DMX LIB的接口时，请注意检查返回值，
       根据返回值可以判断接口调用是否出现问题以及出现的问题原因。
*/
enum ALI_DMX_ERR_CODE
{
    ALI_ERR_DMX_OK = 0,//!<OK

	//ALI_ERR_DMX_TIMEOUT = 0,//!<超时

    ALI_ERR_DMX_NOT_EXIST = -5000,//!<指定的DMX不存在
    ALI_ERR_DMX_NOT_INITILAIZED = -5001,//!<指定的DMX未初始化
    ALI_ERR_DMX_HW_FLT_EXHAUST = -5002,//!<指定的DMX硬件过滤器用完
    ALI_ERR_DMX_PTHREAD_CREATE_FAIL = -5003,
    ALI_ERR_DMX_INVALID_ID = -5004,//!<DMX ID超出范围
    ALI_ERR_DMX_OPER_DENIED = -5005,//!<对DMX非法操作
    ALI_ERR_DMX_INVALID_PID = -5006,//!<PID超出合理范围。(0 ~ 0x1FFF)
	ALI_ERR_DMX_INVALID_PARAM = -5007,//!<非法的配置参数

    ALI_ERR_DMX_SEC_STREAM_EXHAUST = -5100,//!<section stream用完
    ALI_ERR_DMX_SEC_STREAM_INVALID_ID = -5101,//!<section stream ID超出范围
    ALI_ERR_DMX_SEC_STREAM_MASK_INVALID = -5102,//!<section stream mask配置错误
    ALI_ERR_DMX_SEC_STREAM_TIMEOUT = -5103,//!<section接收超时
    ALI_ERR_DMX_SEC_STREAM_OPER_DENIED = -5104,//!<section stream接口非法操作
	ALI_ERR_DMX_SEC_STREAM_CRC_FAILED = -5105,//!<section stream数据CRC校验失败

    ALI_ERR_DMX_SEC_SLOT_EXHAUST = -5200,//!<section slot用完
    ALI_ERR_DMX_SEC_SLOT_INVALID_ID = -5201,//!<section slot ID超出范围
    ALI_ERR_DMX_SEC_SLOT_NO_BUF = -5202,//!<section slot分配内存失败
	ALI_ERR_DMX_SEC_SLOT_OPER_DENIED = -5203,//!<section slot接口非法操作

    ALI_ERR_DMX_SEC_CH_EXHAUST = -5300,//!<section channel用完
    ALI_ERR_DMX_SEC_CH_INVALID_ID = -5301,//!<section channel ID超出范围
    ALI_ERR_DMX_SEC_CH_OPER_DENIED = -5302,//!<section channel接口非法操作
	ALI_ERR_DMX_SEC_CH_DUPED_PID = -5303,//!<不允许配置相同的PID到不同的channel。

    ALI_ERR_DMX_SEC_FLT_EXHAUST = -5400,//!<section filter用完
    ALI_ERR_DMX_SEC_FLT_INVALID_ID = -5401,//!<section filter ID超出范围
    ALI_ERR_DMX_SEC_FLT_OPER_DENIED = -5402,//!<section filter接口非法操作

    ALI_ERR_DMX_VIDEO_STREAM_EXHAUST = -5500,//!<Video stream用完
    ALI_ERR_DMX_VIDEO_STREAM_INVALID_ID = -5501,//!<Video stream ID超出范围
    ALI_ERR_DMX_VIDEO_STREAM_OPER_DENIED = -5502,//!<Video stream接口非法操作

    ALI_ERR_DMX_AUDIO_STREAM_EXHAUST = -5600,//!<Audio stream用完
    ALI_ERR_DMX_AUDIO_STREAM_INVALID_ID = -5601,//!<Audio stream ID超出范围
    ALI_ERR_DMX_AUDIO_STREAM_OPER_DENIED = -5602,//!<Audio stream接口非法操作

    ALI_ERR_DMX_PCR_STREAM_EXHAUST = -5700,//!<Audio stream用完
    ALI_ERR_DMX_PCR_STREAM_INVALID_ID = -5701,//!<Audio stream ID超出范围
    ALI_ERR_DMX_PCR_STREAM_OPER_DENIED = -5702,//!<Audio stream接口非法操作

    ALI_ERR_DMX_TS_STREAM_EXHAUST = -5800,//!<TS stream用完
    ALI_ERR_DMX_TS_STREAM_INVALID_ID = -5801,//!<TS stream ID超出范围
    ALI_ERR_DMX_TS_STREAM_OPER_DENIED = -5802,//!<TS stream接口非法操作

    ALI_ERR_DMX_TS_IN_RAM_STREAM_EXHAUST = -5900,//!<TS in stream用完(从RAM输入TS包格式到DMX)
    ALI_ERR_DMX_TS_IN_RAM_STREAM_INVALID_ID = -5901,//!<TS in stream ID超出范围
    ALI_ERR_DMX_TS_IN_RAM_STREAM_OPER_DENIED = -5902,//!<TS in stream接口非法操作

    ALI_ERR_DMX_SRC_CTRL_STREAM_EXHAUST = -6000,//!<DMX的源节点配置流用完
    ALI_ERR_DMX_SRC_CTRL_STREAM_INVALID_ID = -6001,//!<DMX的源节点配置流ID超出范围
    ALI_ERR_DMX_SRC_CTRL_STREAM_OPER_DENIED = -6002,//!<DMX的源节点配置流接口非法操作

    ALI_ERR_DMX_DESCRAM_KEY_INVALID = -6100,//!<非法的CW字。
    ALI_ERR_DMX_DESCRAM_KEY_STREAM_EXHAUST = -6101,//!<Deacrambler Key stream用完
    ALI_ERR_DMX_DESCRAM_DRV_ERR = -6102,//!<内部Deacrambler Driver出错
    ALI_ERR_DMX_DESCRAM_KEY_STREAM_OPER_DENIED = -6103,//!<Deacrambler Key stream接口非法操作

    ALI_ERR_DMX_TP_STREAM_EXHAUST = -6200,//!<TP stream用完
    ALI_ERR_DMX_TP_STREAM_INVALID_ID = -6201,//!<TP stream ID超出范围
    ALI_ERR_DMX_TP_STREAM_OPER_DENIED = -6202,//!<TP stream接口非法操作
};


/*! @enum ALI_DMX_STREAM_STATE
@brief ALI DMX LIB的stream状态机。
*/
enum ALI_DMX_STREAM_STATE
{
    ALI_DMX_STREAM_STATE_IDLE = 0,
    ALI_DMX_STREAM_STATE_CFG = 1,
    ALI_DMX_STREAM_STATE_STOP = 2,
    ALI_DMX_STREAM_STATE_RUN = 3,
};


/*! @struct Ali_DmxTsStreamParam
@brief 配置从DMX读取TS流的参数。一个TS流可以同时接收多个PID的TS包。用户可以
       在参数中指定需要接收的TS流PID。
*/
struct Ali_DmxTsStreamParam
{  
    UINT32 PidList[ALI_DMX_TS_STREAM_MAX_PID_CNT]; //!< PID数组，一个单元对应一个需要接收的TS流的PID。
    INT32  PidCnt; //!<需要接收的PID的个数。
    UINT32 NeedDiscramble[ALI_DMX_TS_STREAM_MAX_PID_CNT]; //!<每一个单元对应PidList中的一个PID，表示这个PID的数据是否需要解扰。非0，需要; 0,不需要。
	UINT32 TsFltId[ALI_DMX_TS_STREAM_MAX_PID_CNT]; //!<每一个单元对应一个PID过滤器器索引。
};


/*! @struct Ali_DmxAudioStreamParam
@brief 配置ALI DMX Audio stream的参数。
*/
struct Ali_DmxAudioStreamParam
{  
    UINT32 Pid;//!<Audio stream的PID。
	UINT32 NeedDiscramble;//!Audio数据是否需要解扰。1，需要; 0,不需要。
};


/*! @struct Ali_DmxVideoStreamParam
@brief 配置ALI DMX Audio stream的参数。
*/
struct Ali_DmxVideoStreamParam
{  
    UINT32 Pid;//!<Video stream的PID。
	UINT32 NeedDiscramble;//!Video数据是否需要解扰。1，需要; 0,不需要。
};


/*! @struct Ali_DmxPcrStreamParam
@brief 配置ALI DMX PCR stream的参数。
*/
struct Ali_DmxPcrStreamParam
{  
    UINT32 Pid;//!<PCR stream的PID。
	UINT32 NeedDiscramble;//!PCR数据是否需要解扰。1，需要; 0,不需要。
};


/*! @struct Ali_DmxSecMaskFlag
@brief 配置ALI DMX section Mask的过滤后处理参数。
*/
enum Ali_DmxSecMaskFlag
{
    ALI_DMX_SEC_MASK_FLAG_CRC_EN = 0x1,//!<最终命中的Section数据是否需要CRC校验，未通过CRC校验的Section会被丢弃。1，需要; 0,不需要。
};


/*! @struct Ali_DmxSecMaskInfo
@brief 配置ALI DMX section stream的MASK参数。

       过滤规则:
       FOR (i = 0; i < MatchLen; i++)
       {
           IF (Negate[i] == 0)
           {
               IF ((Section[i] & Mask [i]) != (Match[i] & Mask[i]))
               {
                   BREAK;
               }
           }
           ELSE
           {
               IF (Section[i] & Mask [i] == Match[i] &   Mask[i])
               {
                   BREAK;
               }
           }
       }
    
       IF (i >= MatchLen)
       {
           //整个section通过过滤条件，上送给用户。
       }
       ELSE
       {
           //section未通过过滤条件，丢弃整个包。
       }
*/
struct Ali_DmxSecMaskInfo
{
    UINT8 Mask[ALI_DMX_SEC_MATCH_MAX_LEN];//!<Section stream的Mask。
    UINT8 Match[ALI_DMX_SEC_MATCH_MAX_LEN];//!<Section stream的Match。
    UINT8 Negate[ALI_DMX_SEC_MATCH_MAX_LEN];//!<Section stream的Negate。
    UINT32 MatchLen;//!<Section stream的MatchLen。
    enum Ali_DmxSecMaskFlag Flags;//!<Section stream的过滤后处理参数。
};



/*! @struct Ali_DmxSecStreamParam
@brief 配置ALI DMX section stream的PID及过滤参数
*/
struct Ali_DmxSecStreamParam
{
    UINT32 Pid;//!<Section stream的PID。    

    struct Ali_DmxSecMaskInfo SecMask;//!<Section stream的Mask。  

	UINT32 NeedDiscramble;//!section TS包数据是否需要解扰。1，需要; 0,不需要。	
};


/*! @struct Ali_DmxPesStreamParam
@brief 配置ALI DMX PES stream的参数。
*/
struct Ali_DmxPesStreamParam
{  
    UINT32 Pid;//!<PES stream的PID。
	UINT32 NeedDiscramble;//!<PES数据是否需要解扰。1，需要; 0,不需要。
}; 



/*! @struct Ali_DmxSecSlotParam
@brief 配置ALI DMX section slot的参数
*/
struct Ali_DmxSecSlotParam
{
    UINT32 Pid;//!<Section slot的PID。  

    struct Ali_DmxSecMaskInfo SecMask;//!<Section Slot的Mask。

    UINT32 Timeout;//!<超时时间，以毫秒为单位。

    INT32 (*SecRcvCallback)(UINT32  CbParam,//!<用户注册的回调参数。
                            INT32  ErrCode,//!<错误码。
                            UINT8  *SecBuf,//!<section数据的起始地址。
                            UINT32  SecLen);//!<section的长度。

    UINT32 CbParam;//!<回调函数SecRcvCallback的第一个参数。

    UINT32 NeedDiscramble;//!section TS包数据是否需要解扰。1，需要; 0,不需要。	
};


/*! @struct Ali_DmxSecChParam
@brief 配置ALI DMX section channel的参数
*/
struct Ali_DmxSecChParam
{
    UINT32 Pid;//!<Section channel的PID。 
    
	UINT32 NeedDiscramble;//!section TS包数据是否需要解扰。1，需要; 0,不需要。

    UINT32 NeedNoDupPidCheck; //!判断是否需要执行检测重复PID的操作；1，不需要检查；0，需要检查
};


/*! @struct Ali_DmxSecFltParam
@brief 配置ALI DMX section fiter的参数
*/
struct Ali_DmxSecFltParam
{
    struct Ali_DmxSecMaskInfo SecMask;//!<Section Filter的Mask。

    UINT32 Timeout;//!<超时时间，以毫秒为单位。

    INT32 (*SecRcvCallback)(UINT32  CbParam,//!<用户注册的回调参数。
                            INT32  ErrCode,//!<错误码。
                            UINT8  *SecBuf,//!<section数据的起始地址。
                            UINT32  SecLen);//!<section的长度。

    UINT32 CbParam;//!<回调函数SecRcvCallback的第一个参数。
};


/*! @struct Ali_DmxTpStreamParam
@brief 配置录制整个TP数据的参数
*/
struct Ali_DmxTpStreamParam
{
    UINT32 Reserved;//!<保留，目前无实际用途。
};



/*! @struct Ali_DmxSubStreamParam
@brief 配置subttile TS包的PID
*/
struct Ali_DmxSubtStreamParam
{
    UINT32 Pid;//!<subtitle TS包的PID。 
};



/*! @struct Ali_DmxTsInRamStreamParam
@brief 配置ALI DMX TS IN RAM的参数
*/
struct Ali_DmxTsInRamStreamParam
{
    UINT32 Reserved;//!<保留，目前无实际用途。
};


/*! @struct Ali_DmxStreamPollInfo
@brief 配置stream poll的参数
*/
struct Ali_DmxStreamPollInfo
{
    INT32 StreamId;//!<需要查询的Stream的ID。

    INT32 StreamStatus;//!<需要查询的Stream是否有数据可供读或者有空间可供写。1，可以读/写；0,还未为读/写准备好
};


/*! @enum ALI_DMX_INPUT_PORT_ID
@brief ALI硬DMX数据源端口。
*/
enum ALI_DMX_INPUT_PORT_ID
{    
    ALI_DMX_INPUT_PORT_SPI_0   = 0x0,//!<硬DMX的输入端口为SPI 0.
    ALI_DMX_INPUT_PORT_SPI_1   = 0x1,//!<硬DMX的输入端口为SPI 1.

    ALI_DMX_INPUT_PORT_TSG     = 0x2,//!<硬DMX的输入端口为TSG.

    ALI_DMX_INPUT_PORT_SSI_0   = 0x4,//!<硬DMX的输入端口为SSI 0.
    ALI_DMX_INPUT_PORT_SSI_1   = 0x5,//!<硬DMX的输入端口为SSI 1.

    ALI_DMX_INPUT_PORT_PARA    = 0x6,//!<保留.

    ALI_DMX_INPUT_PORT_SPI2B_0 = 0x8,//!<硬DMX的输入端口为ASSI 0.
    ALI_DMX_INPUT_PORT_SPI2B_1 = 0x9,//!<硬DMX的输入端口为ASSI 1.

    ALI_DMX_INPUT_PORT_SPI4B_0 = 0xA,//!<保留.
    ALI_DMX_INPUT_PORT_SPI4B_1 = 0xB,//!<保留.

    ALI_DMX_INPUT_PORT_SSI_2   = 0xC,//!<硬DMX的输入端口为SSI 2.
    ALI_DMX_INPUT_PORT_SSI_3   = 0xD,//!<硬DMX的输入端口为SSI 3.

    ALI_DMX_INPUT_PORT_SPI2B_2 = 0xE,//!<硬DMX的输入端口为ASSI 2.
    ALI_DMX_INPUT_PORT_SPI2B_3 = 0xF,//!<硬DMX的输入端口为ASSI 3.

    ALI_DMX_INPUT_PORT_SPI4B_2 = 0x10,//!<保留.
    ALI_DMX_INPUT_PORT_SPI4B_3 = 0x11,//!<保留.

    
};



/*! @enum ALI_DMX_INPUT_PORT_ID
@brief ALI硬DMX数据源数据通道。
*/
enum ALI_DMX_INPUT_PATH_ID
{    
    ALI_DMX_INPUT_PATH_0   = 0x0,//!<硬DMX的输入数据源数据通道PATH A.
    ALI_DMX_INPUT_PATH_1   = 0x1,//!<硬DMX的输入数据源数据通道PATH B.
    ALI_DMX_INPUT_PATH_2   = 0x2,//!<硬DMX的输入数据源数据通道PATH C.
    ALI_DMX_INPUT_PATH_3   = 0x3,//!<硬DMX的输入数据源数据通道PATH D.    
};


/*! @struct Ali_DmxSrcCtrlStreamParam
@brief ALI硬DMX数据源配置。
*/
struct Ali_DmxSrcCtrlStreamParam
{
    UINT32                     DmxId;//!<硬DMX的ID。
    
    enum ALI_DMX_INPUT_PORT_ID InPutPortId;//!<硬DMX的数据源端口号，请参见enum ALI_DMX_INPUT_PORT_ID。
    UINT32                     InputPortAttr;//!<硬DMX的数据源端口的控制寄存器配置;(bit0~bit7)，请参考硬件TSI SPEC; (bit8), 控制SPI/SSI Error Signal Disable Control.
    
    enum ALI_DMX_INPUT_PATH_ID InputPathId;//!<硬DMX的源数据通道，请参考enum ALI_DMX_INPUT_PATH_ID。
};


/*! @struct Ali_DmxDescramKeyStreamParam
@brief 配置CSA解扰参数。
*/
struct Ali_DmxDescramKeyStreamParam
{
    UINT16 Pid;
};



/*! @struct ALi_DmxSysInfo
@brief ALI DMX的全局信息。
*/
struct ALi_DmxSysInfo
{
    INT32 HwDmxCntTotal;//!<硬DMX的总个数。
	INT32 SwDmxCntTotal;//!<软DMX的总个数。

    INT32 SecStreamCntTotal;//!<Section stream的总个数。
    INT32 SecStreamCntFree;//!<尚未被占用，可供使用的Section stream的个数。

    INT32 SecSlotCntTotal;//!<Section slot的总个数。
    INT32 SecSlotCntFree;//!<尚未被占用，可供使用的Section slot的个数。

    INT32 SecChCntTotal;//!<Section channel的总个数。
    INT32 SecChCntFree;//!<尚未被占用，可供使用的Section channel的个数。

    INT32 SecFltCntTotal;//!<Section filter的总个数。
    INT32 SecFltCntFree;//!<尚未被占用，可供使用的Section filter的个数。

	INT32 VideoStreamCntTotal;//!<Video filter的总个数。
    INT32 VideoStreamCntFree;//!<尚未被占用，可供使用的Video filter的个数。

	INT32 AudioStreamCntTotal;//!<Audio stream的总个数。
    INT32 AudioStreamCntFree;//!<尚未被占用，可供使用的Audio stream的个数。

    INT32 PcrStreamCntTotal;//!<Pcr stream的总个数。
    INT32 PcrStreamCntFree;//!<尚未被占用，可供使用的Pcr stream的个数。

    INT32 TsStreamCntTotal;//!<TS stream的总个数。
    INT32 TsStreamCntFree;//!<尚未被占用，可供使用的TS stream的个数。

    INT32 TsInRamStreamCntTotal;//!<TS in ram stream的总个数。
    INT32 TsInRamStreamCntFree;//!<尚未被占用，可供使用的TS in ram stream stream的个数。

    INT32 SrcCtrlStreamCntTotal;//!<Source control stream的总个数。
    INT32 SrcCtrlStreamCntFree;//!<尚未被占用，可供使用的Source control stream的个数。
};

/*! @struct ALi_DmxDevInfo
@brief 一个DMX的状态及配置信息。
*/
struct ALi_DmxDevInfo
{
    UINT32 OutputDevTsRcvCnt;//!<输出设收到的TS包的总个数。
};


/*! @struct Ali_DmxSecStreamInfo
@brief ALI DMX Section stream的信息。
*/
struct Ali_DmxSecStreamInfo
{
    enum ALI_DMX_STREAM_STATE State;//!<Section stream的状态。

	UINT32 DmxId;//!<Section stream对应的DMX的ID。

    INT32 Idx;//!<Section stream在内部数组中的Index。	

    INT32 Fd;//!<Section stream对应的linux DMX driver的文件描述符。 

    struct Ali_DmxSecStreamParam StreamParam;//!<用户配置的Section stream参数。 

	UINT32 InByteCnt;//!<Section stream总共收到的byte总数。	
};



/*! @struct Ali_DmxSecSlotInfo
@brief ALI DMX Section slot的信息。
*/
struct Ali_DmxSecSlotInfo
{
    enum ALI_DMX_STREAM_STATE State;//!<Section slot的状态。

	UINT32 DmxId;//!<Section slot对应的DMX的ID。

    INT32 Idx;//!<Section slot在内部数组中的Index。

    INT32 SecStreamId;//!<Section slot对应的secton stream的ID。

    INT8 *SecBuf;//!<Section slot内部使用的缓存buffer的地址。

    UINT32 StartTime;//!<Section slot最后一次从callback返回时的时间。

    struct Ali_DmxSecSlotParam SlotParam;//!<用户配置的Section slot参数。 

    //pthread_t WorkThreadId;//!<ALI DMX lib内部用以调用callback函数的thread的ID。 

	UINT32 InByteCnt;//!<Section slot总共收到的byte总数。		
};



/*! @struct Ali_DmxSecChInfo
@brief ALI DMX Section channel的信息。
*/
struct Ali_DmxSecChInfo
{
    enum ALI_DMX_STREAM_STATE State;//!<Section channel的状态。 

    UINT32 DmxId;//!<Section channel对应的DMX的ID。

    INT32 Idx;//!<Section channel在内部数组中的Index。

    struct Ali_DmxSecChParam ChParam;//!<用户配置的Section channel参数。

	UINT32 InByteCnt;//!<Section channel总共收到的byte总数.
};





/*! @struct Ali_DmxSecFltInfo
@brief ALI DMX Section filter的信息。
*/
struct Ali_DmxSecFltInfo
{
    enum ALI_DMX_STREAM_STATE State;//!<Section filter的状态。

    INT32 Idx; //!<Section filter在内部数组中的Index。	

    INT32 ChIdx;//!<Section filter属于的的Section channel的IDX。

    INT32 SecSlotId;//!<Section filter使用的Section slot的IDX。

    struct Ali_DmxSecFltParam FltParam;//!<用户配置的Section filter参数。

    UINT32 InByteCnt;//!<Section filter总共收到的byte总数.
};




/*! @struct Ali_DmxVideoStreamInfo
@brief ALI DMX Video stream的信息。
*/
struct Ali_DmxVideoStreamInfo
{
    enum ALI_DMX_STREAM_STATE State;//!<Video stream的状态.

	UINT32 DmxId;//!<Video stream对应的DMX的ID。	

    UINT32 Idx; //!<Video stream在内部数组中的Index。	

    INT32 Fd;//!<Video stream对应的linux DMX driver的文件描述符。  

    struct Ali_DmxVideoStreamParam StreamParam;//!<用户配置的Video stream参数。

    UINT32 InByteCnt;//!<Video Stream总共收到的byte总数.	
    
	UINT32 DmaChannelId;//!<Driver内部使用的传送VIDEO数据的DMA Channel的ID.	

    /* TS layer info.
	*/
    UINT32 TsInCnt;
    UINT32 TsScrmbCnt;
    UINT32 TsSyncByteErrCnt;
	UINT32 TsDupCnt;
	UINT32 TsLostCnt;
    UINT32 TsErrCnt;
};




/*! @struct Ali_DmxAudioStreamInfo
@brief ALI DMX Audio stream的信息。
*/
struct Ali_DmxAudioStreamInfo
{
    enum ALI_DMX_STREAM_STATE State;//!<Audio stream的状态.

	UINT32 DmxId;//!<Audio stream对应的DMX的ID。	

    UINT32 Idx;//!<Audio stream在内部数组中的Index。

    INT32 Fd;//!<Audio stream对应的linux DMX driver的文件描述符。 

    struct Ali_DmxAudioStreamParam StreamParam;//!<用户配置的Audio stream参数。

    UINT32 InByteCnt;//!<Audio Stream总共收到的byte总数. 

    /* TS layer info.
	*/
    UINT32 TsInCnt;
    UINT32 TsScrmbCnt;
    UINT32 TsSyncByteErrCnt;
	UINT32 TsDupCnt;
	UINT32 TsLostCnt;
    UINT32 TsErrCnt;
};




/*! @struct Ali_DmxPcrStreamInfo
@brief ALI DMX Pcr stream的信息。
*/
struct Ali_DmxPcrStreamInfo
{
    enum ALI_DMX_STREAM_STATE State;//!<Pcr stream的状态.

	UINT32 DmxId;//!<Pcr stream对应的DMX的ID。	

    UINT32 Idx;//!<Pcr stream在内部数组中的Index。	

    INT32 Fd;//!<Pcr stream对应的linux DMX driver的文件描述符。 

    struct Ali_DmxPcrStreamParam StreamParam;//!<用户配置的Pcr stream参数。 

    UINT32 InByteCnt;//!<Pcr Stream总共收到的byte总数.	
};



/*! @struct Ali_DmxTsStreamInfo
@brief ALI DMX TS stream的信息。
*/
struct Ali_DmxTsStreamInfo
{
    enum ALI_DMX_STREAM_STATE State;//!<TS stream的状态.

	UINT32 DmxId;//!<TS stream对应的DMX的ID。	

    UINT32 Idx; //!<TS stream在内部数组中的Index。

    INT32 Fd;//!<TS stream对应的linux DMX driver的文件描述符.

    struct Ali_DmxTsStreamParam StreamParam;//!<用户配置的TS stream参数。  

    UINT32 InByteCnt;//!<TS Stream总共收到的byte总数.	
};




/*! @struct Ali_DmxTsInRamStreamInfo
@brief ALI DMX TS IN RAM stream的信息。
*/
struct Ali_DmxTsInRamStreamInfo
{
    enum ALI_DMX_STREAM_STATE State;//!<TS IN RAM stream的状态.

	UINT32 DmxId;//!<TS IN RAM stream对应的DMX的ID。

    UINT32 Idx; //!<TS IN RAM stream在内部数组中的Index。	

    INT32 Fd;//!<TS IN RAM stream对应的linux DMX driver的文件描述符.

    struct Ali_DmxTsInRamStreamParam StreamParam;//!<用户配置的TS IN RAM stream参数.

    UINT32 InByteCnt;//!<TS IN RAM Stream总共收到的用户写入的byte总数.
};




/*! @struct Ali_DmxSrcCtrlStreamInfo
@brief ALI DMX source control stream的信息。
*/
struct Ali_DmxSrcCtrlStreamInfo
{
    enum ALI_DMX_STREAM_STATE State;//!<source control stream的状态.

	UINT32 DmxId;//!<source control stream对应的DMX的ID。

    UINT32 Idx;//!<source control stream在内部数组中的Index。	

    INT32 Fd;//!<source control stream对应的linux DMX driver的文件描述符.

    struct Ali_DmxSrcCtrlStreamParam StreamParam;//!<用户配置的source control stream参数. 
};




/*!
@brief 用户通过此接口向DMX申请一个SECTION类型的数据通道。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] DmxId 目标DMX的ID，DMX 0的ID为0，DMX 1的ID为1，以此类推。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,打开的Section stream的ID。
*/
INT32 Ali_DmxSecStreamOpen(UINT32 DmxId);


/*!
@brief 用户通过此接口配置一个申请得到的section Stream。

       用户需要以参数形式传递给DMX一个过滤参数。
       
       Section stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxSecStreamOpen()得到。
@param[in] StreamParam是一个指向结构体struct Ali_DmxSecStreamParam的指针，
           用户通过这个指针告知DMX需要收取的SECTON数据的配置。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecStreamCfg(INT32 StreamId, struct Ali_DmxSecStreamParam *StreamParam);


/*!
@brief 用户通过此接口使能一个SECTION类型的数据通道。

       使能成功后，DEMUX会根据用户的配置过滤出SECTION数据，
       
       用户可以通过Ali_DmxSecStreamRead()接口读取通过过滤的SECTION。
       
       Section stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxSecStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,使能成功。
*/
INT32 Ali_DmxSecStreamStart(INT32 StreamId);


/*!
@brief 用户通过此接口停止一个section stream。

       Stream关闭后，DMX停止收取这个stream的数据，而与这个stream相关的资源不会
       被释放，用户可以调用Ali_DmxSecStreamCfg()接口重新配置这个stream。
       
       请注意这个接口在stream为RUN的状态下才有效。
       
       Section stream的操作流程请参考ALI_DMX_MES.doc。
@param[in] StreamId，此值由调用Ali_DmxSecStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecStreamStop(INT32 StreamId);


/*!
@brief 用户通过此接口关闭一个section stream。

       用户可以在除IDLE之外的任何状态下调用这个接口。
       
       Stream被Close后，所有与这个stream相关的资源都会被释放，
       这个stream会空闲下来等待下一次重新被open使用。
       
       Section stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxSecStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecStreamClose(INT32 StreamId);


/*!
@brief 用户通过此接口向DEMUX读取一个已经打开的Section stream的数据。

       如果需要读取的stream暂无数据，用户可以通过Ali_DmxStreamPoll()接口实现
       数据等待。
       
	   用户需要提供一个用以保存Section数据的缓冲区的地址给DMX，这个地址的长度需
	   要足够保存一个完整的Section包，推荐的值为4K，否则有可能出现因为缓冲区长度
	   不够而无法得到数据的错误。
	   
	   用户可以调用Ali_DmxStreamPoll()接口实现对多个stream的等待，请参见
	   Ali_DmxStreamPoll()接口说明。
	   
	   注意read操作只有在section stream为RUN的状态下才有效。
	   
       Section stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxSecStreamOpen()得到。
@param[out] Buf，用户提供的用以存储Section的缓冲地址。
@param[in] BufLen，用户提供缓冲长度。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,读取到的数据的长度，以byte为单位。
*/
INT32 Ali_DmxSecStreamRead(INT32 StreamId, UINT8 *Buf, UINT32 BufLen);


/*!
@brief 用户通过此接口向DMX查询一个section stream的状态。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] StreamId 需要查询的section stream的ID。
@param[out] SecStreamInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct Ali_DmxSecStreamInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 Ali_DmxSecStreamInfoGet(INT32 StreamId, struct Ali_DmxSecStreamInfo *SecStreamInfo);




/*!
@brief 用户通过此接口向DMX申请分配一个section slot。

       如果成功，DMX会返回一个 slot ID，此后可以通过这个slot ID来操作这个slot。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。

       Section slot的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] DmxId 目标DMX的ID，DMX 0的ID为0，DMX 1的ID为1，以此类推。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,打开的section slot的ID。
*/
INT32 Ali_DmxSecSlotOpen(UINT32 DmxId);



/*!
@brief 用户通过此接口配置一个申请得到的section slot。

	   用户同时需要以参数形式传递给DMX一个过滤参数。
	   
	   DMX收到section数据后，会根据这个过滤条件对数据进行过滤，只有符合过滤
	   条件的section数据才会被上送给用户。
	   
	   用户同时需要以参数形式传递给DMX一个callback函数，DMX收到通过过滤条件的
	   section数据后会调用这个callback函数通知用户收到的数据地址及长度.
	   
	   用户也需要配置一个Timeout参数，如果在Timeout时间段内未收到数据，DMX会
	   调用callback函数通知用户，DMX会把callback函数的ErrCode
	   域置为ALI_ERR_DMX_SEC_STREAM_TIMEOUT来通知用户超时事件的发生。
	   
	   超时时间，0为立刻超时，0xFFFFFFFF为永远不超时，否则为超时等待时间，
	   以毫秒为单位。
	   
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section slot的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] SlotId，此值由调用Ali_DmxSecSlotOpen()得到。
@param[in] SecSlotParam指向数据结构struct Ali_DmxSecSlotParam的指针，用户
           通过这个指针配置Section Slot的参数。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecSlotCfg(INT32 SlotId, struct Ali_DmxSecSlotParam *SecSlotParam);


/*!
@brief 用户通过此接口开启一个section slot。

       slot开启后，如果接收到符合过滤条件的section，就会通过调用
       SecRcvCallback()向用户传送数据。
       
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section slot的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] SlotId，此值由调用Ali_DmxSecSlotOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,开启成功。
*/
INT32 Ali_DmxSecSlotStart(INT32 SlotId);


/*!
@brief 用户通过此接口停止一个section slot。

       Slot关闭后，与这个slot相关的资源不会被释放，用户可以调用
       Ali_DmxSecSlotCfg()接口重新配置这个slot。
       
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section slot的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] SlotId，此值由调用Ali_DmxSecSlotOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,Slot停止成功。
*/
INT32 Ali_DmxSecSlotStop(INT32 SlotId);


/*!
@brief 用户通过此接口释放一个section slot。

       Slot释放后，所有与这个slot相关的资源都会被释放，这个slot会空闲下来等待
       下一次重新分配使用。
       
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section slot的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] SlotId，此值由调用Ali_DmxSecSlotOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecSlotClose(INT32 SlotId);



/*!
@brief 用户通过此接口向DMX查询一个section slot的状态。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section slot的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] SlotId 需要查询的section slot的ID。
@param[out] SecSlotInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct Ali_DmxSecSlotInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 Ali_DmxSecSlotInfoGet(INT32 SlotId, struct Ali_DmxSecSlotInfo * SecSlotInfo);


/*!
@brief 用户通过此接口向DMX申请分配一个section channel。

       如果成功，DMX会返回一个channel ID，此后可以通过这个channel ID来操作这个
       channel。
       
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section channel的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] DmxId 目标DMX的ID，DMX 0的ID为0，DMX 1的ID为1，以此类推。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,打开的section channel的ID。
*/
INT32 Ali_DmxSecChOpen(UINT32 DmxId);

/*!
@brief 用户通过此接口配置一个申请得到的section channel。

	   用户需要以参数形式传递给channel一个参数,这个参数是一个指向
	   数据结构struct Ali_DmxSecChParam的指针，DMX会根据用户输入的这个参数来配置
	   这个channel。
	   
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section Channel的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] ChId，此值由调用Ali_DmxSecChOpen()得到。
@param[in] ChParam指向数据结构struct Ali_DmxSecChParam的指针，用户
           通过这个指针配置Section Channel的参数。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecChCfg(INT32 ChId, struct Ali_DmxSecChParam *ChParam);

/*!
@brief 用户通过此接口开启一个section Channel。

       Channel开启后，用户才能在这个channel上开启section filter，通过
       section filter收取数据。
       
	   请特别注意，只有在channel处于RUN的状态下，挂载在这个channel上的filter才
	   能收到数据。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section Channel的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] ChId，此值由调用Ali_DmxSecChOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecChStart(INT32 ChId);

/*!
@brief 用户通过此接口停止一个section Channel。

       调用此接口成功后，所有挂在在这个Channel上的Filter都不能接受到数据，一直到
       这个channel被重新start后才可以继续接收到数据。
       
       调用此接口成功后，用户可以调用Ali_DmxSecChCfg()接口重新配置这个Channel。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section Channel的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] ChId，此值由调用Ali_DmxSecChOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecChStop(INT32 ChId);

/*!
@brief 用户通过此接口释放一个section Channel。

       Channel释放后，所有与这个Channel相关的资源都会被释放，这个Channel会空闲
       下来等待下一次重新分配使用。
       
	   请注意，Channel释放时，只要还存在挂载在这个Channel上没被close掉的Filter，
	   就会返回失败值ALI_ERR_DMX_SEC_CH_OPER_DENIED，用户必须在close掉挂载在一
	   个Channel上的所有Filter后，才能close掉这个Channel。
	   
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section Channel的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] ChId，此值由调用Ali_DmxSecChOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecChClose(INT32 ChId);


/*!
@brief 用户通过此接口向DMX查询一个section channel的状态。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section channel的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] ChId是需要查询的section channel的ID。
@param[out] SecChInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct Ali_DmxSecChInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 Ali_DmxSecChInfoGet(INT32 ChId, struct Ali_DmxSecChInfo *SecChInfo);


/*!
@brief 用户通过此接口向一个已打开的channel申请分配一个section Filter。

       如果成功，DMX会返回一个Filter ID，此后可以通过这个Filter ID来操作这个
       Filter。
       
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section Filter的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] ChId 目标Channel的ID。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,打开的section Filter的ID。
*/
INT32 Ali_DmxSecFltOpen(INT32 ChId);

/*!
@brief 用户通过此接口配置一个申请得到的Filter slot。

	   用户同时需要以参数形式传递给DMX一个过滤参数。
	   
	   用户同时需要以参数形式传递给DMX一个callback函数，DMX收到section数据通过
	   过滤条件后会调用这个callback函数通知用户收到的数据地址及长度。
	   
	   用户也需要配置一个Timeout参数，如果在Timeout时间段内未收到数据，DMX会调用
	   callback函数通知用户。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section Filter的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] FltId，此值由调用Ali_DmxSecFltOpen()得到。
@param[in] FltParam指向数据结构struct Ali_DmxSecFltParam的指针，用户
           通过这个指针配置Section Filter的参数。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecFltCfg(INT32 FltId, struct Ali_DmxSecFltParam *FltParam);


/*!
@brief 用户通过此接口开启一个section Filter。

       Filter开启成功后，如果接收到符合过滤条件的section，
       就会通过调用DmxSecFltCfg()接口注册的SecRcvCallback()函数向用户传送数据。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section Filter的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] FltId，此值由调用Ali_DmxSecFltOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecFltStart(INT32 FltId);


/*!
@brief 用户通过此接口停止一个section Filter。

       Filter停止后，与这个filter相关的资源不会被释放，用户可以调用
       Ali_DmxSecFltCfg()接口重新配置这个Filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section Filter的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] FltId，此值由调用Ali_DmxSecFltOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecFltStop(INT32 FltId);


/*!
@brief 用户通过此接口释放一个section Filter。

       Filter释放后，所有与这个Filter相关的资源都会被释放，这个Filter会空闲下
       来等待下一次重新分配使用。同时这个filter也会从被挂载的channel上取走而不
       再从属于这个channel。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section Filter的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] FltId，此值由调用Ali_DmxSecFltOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxSecFltClose(INT32 FltId);



/*!
@brief 用户通过此接口向DMX查询一个section filiter的状态。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Section filiter的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] FltId是需要查询的section filiter的ID。
@param[out] SecFltInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct Ali_DmxSecFltInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 Ali_DmxSecFltInfoGet(INT32 FltId, struct Ali_DmxSecFltInfo * SecFltInfo);




/*!
@brief 用户通过该API来创建一个抓取Video PID的filter。

       该filter得到的数据直接传输到Video Decoder，Video filter过滤出的TS包不会
       被送到用户空间。
       
       请注意目前ALI DMX支持一路Video filter。
       
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Video Stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] DmxId 目标DMX的ID，DMX 0的ID为0，DMX 1的ID为1，以此类推。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,打开的Video stream的ID。
*/
INT32 Ali_DmxVideoStreamOpen(UINT32 DmxId);

/*!
@brief 用户通过此接口配置一个申请得到的Video Stream。

       请注意目前ALI DMX支持一路Video filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Video Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的Video Stream的ID. 
           此值由调用Ali_DmxVideoStreamOpen()得到。
@param[in] StreamParam，指向数据结构struct Ali_DmxVideoStreamParam的指针，用户
           通过这个指针配置Video Stream的参数。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxVideoStreamCfg(INT32 StreamId, struct Ali_DmxVideoStreamParam *StreamParam);

/*!
@brief 用户通过此接口使能一个Video Stream的数据通道。

       使能成功后，DMX会根据用户的配置过滤出Video Stream数据，直接传输给
       Video Decoder。
       
       请注意目前ALI DMX支持一路Video filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       Video Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的Video Stream的ID. 
           此值由调用Ali_DmxVideoStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxVideoStreamStart(INT32 StreamId);

/*!
@brief 用户通过此接口停止一个Video Stream。

       Stream关闭后，DMX停止收取这个Video Stream的数据，但与这个Stream相关的资
       源不会被释放，可以调用Ali_DmxVideoStreamCfg()接口重新配置这个stream。

       请注意目前ALI DMX支持一路Video filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       Video Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的Video Stream的ID. 
           此值由调用Ali_DmxVideoStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxVideoStreamStop(INT32 StreamId);

/*!
@brief 用户通过此接口关闭一个Video Stream。

       可以在除IDLE之外的任何状态下调用这个接口。
       
       Video Stream被Close后，所有与这个stream相关的资源都会被释放，这个
       stream会空闲下来等待下一次重新被open使用。

       请注意目前ALI DMX支持一路Video filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Video Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的Video Stream的ID. 
           此值由调用Ali_DmxVideoStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxVideoStreamClose(INT32 StreamId);



/*!
@brief 用户通过此接口向DMX查询一个Video stream的状态。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Video stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] StreamId 需要查询的Video stream的ID。
@param[out] VideoStreamInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct Ali_DmxVideoStreamInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 Ali_DmxVideoStreamInfoGet(INT32 StreamId, struct Ali_DmxVideoStreamInfo * VideoStreamInfo);



/*!
@brief 用户通过此接口来创建一个抓取Audio PID的filter。

       该filter得到的数据直接传输到Audio Decoder，Audio filter过滤出的TS包不会
       被送到用户空间。
       
       请注意目前ALI DMX支持一路Audio filter。
       
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Audio stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] DmxId 目标DMX的ID，DMX 0的ID为0，DMX 1的ID为1，以此类推。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,打开的Audio stream的ID。
*/
INT32 Ali_DmxAudioStreamOpen(UINT32 DmxId);

/*!
@brief 用户通过此接口配置一个申请得到的Audio Stream。

       请注意目前ALI DMX支持一路Audio filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Audio Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的Audio Stream的ID. 
           此值由调用Ali_DmxAudioStreamOpen()得到。
@param[in] StreamParam，指向数据结构struct Ali_DmxAudioStreamParam的指针，用户
           通过这个指针配置Audio Stream的参数。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxAudioStreamCfg(INT32 StreamId, struct Ali_DmxAudioStreamParam *StreamParam);

/*!
@brief 用户通过此接口使能一个Audio Stream的数据通道。

       使能成功后，DMX会根据用户的配置过滤出Audio Stream数据，直接传输给
       Audio Decoder。
       
       请注意目前ALI DMX支持一路Audio filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Audio Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的Audio Stream的ID. 
           此值由调用Ali_DmxAudioStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxAudioStreamStart(INT32 StreamId);

/*!
@brief 用户通过此接口停止一个Audio Stream。

       Stream关闭后，DMX停止收取这个Audio Stream的数据，但与这个Stream相关的资
       源不会被释放，可以调用Ali_DmxAudioStreamCfg()接口重新配置这个stream。

       请注意目前ALI DMX支持一路Audio filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Audio Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的Audio Stream的ID. 
           此值由调用Ali_DmxAudioStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxAudioStreamStop(INT32 StreamId);


/*!
@brief 用户通过此接口关闭一个Audio Stream。

       可以在除IDLE之外的任何状态下调用这个接口。
       
       Audio Stream被Close后，所有与这个stream相关的资源都会被释放，这个
       stream会空闲下来等待下一次重新被open使用。

       请注意目前ALI DMX支持一路Audio filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Video Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的Audio Stream的ID. 
           此值由调用Ali_DmxVideoStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxAudioStreamClose(INT32 StreamId);


/*!
@brief 用户通过此接口向DMX查询一个Audio stream的状态。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Audio stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] StreamId，需要查询的Audio stream的ID。
@param[out] AudioStreamInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct Ali_DmxAudioStreamInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 Ali_DmxAudioStreamInfoGet(INT32 StreamId, struct Ali_DmxAudioStreamInfo * AudioStreamInfo);


/*!
@brief 用户通过此接口来创建一个抓取PCR PID的filter。

       该filter得到的数据信息会被直接传输到ALI AVSYNC模块，用以作为ALI内部
       做AV sync的参考信息，PCR filter过滤出的TS包不会被送到用户空间。
       
       用户在播放Audio/Video时，需要调用此接口指定AV sync所需的PCR PID信息。
       
       请注意目前ALI DMX支持一路PCR filter。
       
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       PCR stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] DmxId 目标DMX的ID，DMX 0的ID为0，DMX 1的ID为1，以此类推。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,打开的PCR stream的ID。
*/
INT32 Ali_DmxPcrStreamOpen(UINT32 DmxId);

/*!
@brief 用户通过此接口配置一个申请得到的PCR Stream。

       请注意目前ALI DMX支持一路PCR filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       PCR Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的PCR Stream的ID. 
           此值由调用Ali_DmxPcrStreamOpen()得到。
@param[in] StreamParam，指向数据结构struct Ali_DmxPcrStreamParam的指针，用户
           通过这个指针配置PCR Stream的参数。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxPcrStreamCfg(INT32 StreamId, struct Ali_DmxPcrStreamParam *StreamParam);


/*!
@brief 用户通过此接口使能一个PCR Stream的数据通道。

       使能成功后，DMX会根据用户的配置过滤出PCR Stream数据，直接传输给
       ALI AVSYNC模块。
       
       请注意目前ALI DMX支持一路PCR  filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       PCR  Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的PCR  Stream的ID. 
           此值由调用Ali_DmxPcrStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxPcrStreamStart(INT32 StreamId);

/*!
@brief 用户通过此接口停止一个PCR Stream。

       Stream关闭后，DMX停止收取这个PCR Stream的数据，但与这个Stream相关的资
       源不会被释放，可以调用Ali_DmxPcrStreamCfg()接口重新配置这个stream。

       请注意目前ALI DMX支持一路Audio filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Ali_DmxPcrStreamCfg Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的Ali_DmxPcrStreamCfg Stream的ID. 
           此值由调用Ali_DmxPcrStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxPcrStreamStop(INT32 StreamId);

/*!
@brief 用户通过此接口关闭一个PCR Stream。

       可以在除IDLE之外的任何状态下调用这个接口。
       
       PCR Stream被Close后，所有与这个stream相关的资源都会被释放，这个
       stream会空闲下来等待下一次重新被open使用。

       请注意目前ALI DMX支持一路PCR filter。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       PCR Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的PCR Stream的ID. 
           此值由调用Ali_DmxPcrStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxPcrStreamClose(INT32 StreamId);


/*!
@brief 用户通过此接口向DMX查询一个Pcr stream的状态。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       Pcr stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] StreamId 需要查询的Pcr stream的ID。
@param[out] PcrStreamInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct Ali_DmxPcrStreamInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 Ali_DmxPcrStreamInfoGet(INT32 StreamId, struct Ali_DmxPcrStreamInfo * PcrStreamInfo);


/*!
@brief 用户通过此接口来创建一个抓取TS流的filter。

       抓取到的TS包被放入DMX内部的buffer中缓存，用户可以通过
       Ali_DmxTsStreamRead()接口读取filter接收到的TS流数据。

       对于同一个TS stream,用户可以配置多个PID，DMX会把所有符合配置条件的TS包
       都放入同一内部缓存中等待用户读取。这个特性对PVR应用比较方便。
       
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       PCR stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] DmxId 目标DMX的ID，DMX 0的ID为0，DMX 1的ID为1，以此类推。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,打开的TS stream的ID。
*/
INT32 Ali_DmxTsStreamOpen(UINT32 DmxId);


/*!
@brief 用户通过此接口配置一个申请得到的TS Stream。

       对于同一个TS stream,用户可以配置多个PID，DMX会把所有符合配置条件的TS包
       都放入同一内部缓存中等待用户读取。这个特性对PVR应用比较方便。

       PID列表及PID个数需要通过参数StreamParam传递给DMX。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       PCR Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的TS Stream的ID. 
           此值由调用Ali_DmxPcrStreamOpen()得到。
@param[in] StreamParam，指向数据结构struct Ali_DmxTsStreamParam的指针，用户
           通过这个指针配置TS Stream的参数。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxTsStreamCfg(INT32 StreamId, struct Ali_DmxTsStreamParam *StreamParam);


/*!
@brief 用户通过此接口使能一个TS类型的数据通道。

       使能成功后，DEMUX会根据用户的配置过滤出TS数据，
       
       用户可以通过Ali_DmxTsStreamRead()接口读取通过过滤的TS包。
       
       TS stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxSecStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,使能成功。
*/
INT32 Ali_DmxTsStreamStart(INT32 StreamId);



/*!
@brief 用户通过此接口停止一个TS stream。

       Stream关闭后，DMX停止收取这个stream的数据，而与这个stream相关的资源不会
       被释放，用户可以调用Ali_DmxTsStreamCfg()接口重新配置这个stream。
       
       请注意这个接口在stream为RUN的状态下才有效。
       
       Section stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxTsStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxTsStreamStop(INT32 StreamId);



/*!
@brief 用户通过此接口关闭一个TS stream。

       用户可以在除IDLE之外的任何状态下调用这个接口。
       
       TS Stream被Close后，所有与这个stream相关的资源都会被释放，这个TS stream
       会空闲下来等待下一次重新被open使用。
       
       Section stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxTsStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxTsStreamClose(INT32 StreamId);


/*!
@brief 用户通过此接口向DEMUX读取一个已经打开的TS stream的数据。

       如果需要读取的stream暂无数据，用户可以通过Ali_DmxStreamPoll()接口实现
       数据等待。
       
	   用户需要提供一个用以保存TS数据的缓冲区的地址给DMX，这个地址的长度需
	   要足够保存一个完整的TS包(188 bytes)，推荐的值为47K。过短则可能需要更多
       的系统调用而影响系统性能。
	   
	   用户可以调用Ali_DmxStreamPoll()接口实现对多个stream的等待，请参见
	   Ali_DmxStreamPoll()接口说明。
	   
	   注意read操作只有在TS stream为RUN的状态下才有效。
	   
       TS stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxTsStreamOpen()得到。
@param[out] Buf，用户提供的用以存储TS的缓冲地址。
@param[in] BufLen，用户提供缓冲长度。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,读取到的数据的长度，以byte为单位。
*/
INT32 Ali_DmxTsStreamRead(INT32 StreamId, UINT8 *Buf, UINT32 BufLen);




/*!
@brief 用户通过此接口向DMX查询一个TS stream的状态。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       TS stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] StreamId 需要查询的TS stream的ID。
@param[out] TsStreamInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct Ali_DmxTsStreamInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 Ali_DmxTsStreamInfoGet(INT32 StreamId, struct Ali_DmxTsStreamInfo * TsStreamInfo);




/*!
@brief 用户通过此接口来创建一个通过内存输入软DMX的输入流(TS格式)。

       用户可以通过这个打开的Stream ID向软DMX输入TS格式的数据流，软DMX需要从
       输入TS流中得到数据做后续处理。
       
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       TS stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] DmxId 目标DMX的ID，DMX 0的ID为0，DMX 1的ID为1，以此类推。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,打开的TS IN RAM stream的ID。
*/
INT32 Ali_DmxTsInRamStreamOpen(UINT32 DmxId);


/*!
@brief 用户通过此接口配置一个申请得到的TS IN RAM Stream。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       TS IN RAM Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的TS IN RAM Stream的ID. 
           此值由调用Ali_DmxTsInRamStreamOpen()得到。
@param[in] StreamParam，指向数据结构struct Ali_DmxTsStreamParam的指针，用户
           通过这个指针配置TS Stream的参数。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxTsInRamStreamCfg(INT32 StreamId, struct Ali_DmxTsInRamStreamParam *StreamParam);


/*!
@brief 用户通过此接口使能一个TS IN RAM类型的数据通道。

       使能成功后，用户可以向打开的TS IN RAM stream写入TS格式的数据。 对应的软
       DMX会处理输入的TS流为用户提供服务。

       用户可以通过Ali_DmxTsInRamStreamWrite()接口向数据通道写入数据。
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       TS IN RAM stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxTsInRamStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,使能成功。
*/
INT32 Ali_DmxTsInRamStreamStart(INT32 StreamId);



/*!
@brief 用户通过此接口停止一个TS IN RAM stream。

       Stream关闭后，DMX停止收取这个stream的数据，而与这个stream相关的资源不会
       被释放，用户可以调用Ali_DmxTsInRamStreamCfg()接口重新配置这个stream。
       
       请注意这个接口在stream为RUN的状态下才有效。
       
       TS IN RAM stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxTsInRamStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxTsInRamStreamStop(INT32 StreamId);



/*!
@brief 用户通过此接口关闭一个TS IN RAM stream。

       用户可以在除IDLE之外的任何状态下调用这个接口。
       
       Stream被Close后，所有与这个stream相关的资源都会被释放，这个stream会空闲
       下来等待下一次重新被open使用。
       
       TS IN RAM stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxTsInRamStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxTsInRamStreamClose(INT32 StreamId);


/*!
@brief 用户通过此接口向一个软DMX写入TS格式的数据。

       如果软DMX内部buffer已满，用户可以通过Ali_DmxStreamPoll()接口实现
       数据等待。或者等待一段时间等buffer的数据消耗一段时间后再继续写入。

       用户可以调用Ali_DmxStreamPoll()接口实现对多个stream的等待，请参见
      	   Ali_DmxStreamPoll()接口说明。
       
	   用户需要提供一个保存TS数据的地址给DMX，这个地址的长度需
	   要是一个TS包长度(188 bytes)的整数倍，推荐的值为47K。过短则可能需要更多
       的系统调用而影响系统性能。
	   
	   注意read操作只有在TS stream为RUN的状态下才有效。
	   
       TS stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxTsInRamStreamOpen()得到。
@param[in] Buf，用户提供的用以存储TS的缓冲地址。
@param[in] BufLen，用户提供缓冲长度。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,读取到的数据的长度，以byte为单位。
*/
INT32 Ali_DmxTsInRamStreamWrite(INT32 StreamId, UINT8 *Buf, UINT32 BufLen);



/*!
@brief 用户通过此接口向DMX查询一个TS IN RAM stream的状态。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       TS IN RAM stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] StreamId 需要查询的TS IN RAM stream的ID。
@param[out] TsInRamStreamInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct Ali_DmxTsInRamStreamInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 Ali_DmxTsInRamStreamInfoGet(INT32 StreamId, struct Ali_DmxTsInRamStreamInfo * TsInRamStreamInfo);

/*!
@brief 用户通过此接口来创建一个控制硬DMX前端输入源设置的控制端口。

       同一DMX同时只能存在一个输入源控制stream。

       注意此Source control stream不能在Ali_DmxStreamPoll()中被poll。

       用户可以通过这个接口设置硬件DMX数据源。在ALI DMX中硬件DMX数据源由硬件
       TSI管理，用户可参考ALI TSI的硬件SPEC确定具体配置值。
       
@param[in] DmxId 目标DMX的ID，DMX 0的ID为0，DMX 1的ID为1，以此类推。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,打开的dmx source control stream的ID。
*/
INT32 ALi_DmxSrcCtrlStreamOpen(UINT32 DmxId);


/*!
@brief 用户通过此接口来关闭一个控制硬DMX前端输入源设置的控制端口。

       注意此Source control stream不能在Ali_DmxStreamPoll()中被poll。

       关闭成功后，用户不能再通过这个端口来配置DMX数据源。如果需要再次配置，
       需要调用ALi_DmxSrcCtrlStreamOpen()重新打开配置端口。

       用户可以通过这个接口设置硬件DMX数据源。在ALI DMX中硬件DMX数据源由硬件
       TSI管理，用户可参考ALI TSI的硬件SPEC确定具体配置值。
       
@param[in] StreamId，此值由调用ALi_DmxSrcCtrlStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 等于0,操作成功。
*/
INT32 Ali_DmxSrcCtrlStreamClose(INT32 StreamId);


/*!
@brief 用户通过此接口来设置硬DMX前端输入源。

	   在ALI DMX中硬件DMX数据源由硬件TSI管理，用户可参考ALI TSI的硬件SPEC确定
	   具体配置值。

       注意此Source control stream不能在Ali_DmxStreamPoll()中被poll。


       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。

@param[in] StreamId，此值由调用ALi_DmxSrcCtrlStreamOpen()得到。
@param[in] Param，用户提供的用以储存TSI配置的指针，指向数据结构
           struct Ali_DmxSrcCtrlStreamInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 等于0,操作成功。
*/
INT32 Ali_DmxSrcCtrlStreamWrite(INT32 StreamId, struct Ali_DmxSrcCtrlStreamParam *Param);


/*!
@brief 用户通过此接口来读取硬DMX前端输入源的配置信息。

	   在ALI DMX中硬件DMX数据源由硬件TSI管理，用户可参考ALI TSI的硬件SPEC。

       注意此Source control stream不能在Ali_DmxStreamPoll()中被poll。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。

@param[in] StreamId，此值由调用ALi_DmxSrcCtrlStreamOpen()得到。
@param[out] Param，用户提供的用以储存TSI配置的指针，指向数据结构
            struct Ali_DmxSrcCtrlStreamInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 等于0,操作成功。
*/
INT32 Ali_DmxSrcCtrlStreamRead(INT32 StreamId, struct Ali_DmxSrcCtrlStreamParam *Param);



/*!
@brief 用户通过此接口向DMX查询一个DMX source control stream的状态。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       source control stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] StreamId 需要查询的source control stream的ID。
@param[out] SrcCtrlStreamInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct Ali_DmxSrcCtrlStreamInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 Ali_DmxSrcCtrlStreamInfoGet(INT32 StreamId, struct Ali_DmxSrcCtrlStreamInfo *SrcCtrlStreamInfo);



/*!
@brief 用户通过此接口来查询指定的Stream是否有数据可供读出或者有空间可供写入。

	   当用户想同时查询多个Stream是否数据可供读出或者有空间可供写入时，可使用本
       接口得到所需信息。

       用户在参数PollList中填入需要查询的Stream的ID列表，用参数PollUnitCnt告知
       DMX需要查询的Stream的个数，用参数Timeout告知DMX超时时间，以毫秒为单位。

       成功时，Ali_DmxStreamPoll()返回PollList中有数据可读/写的Stream；
       如果在超时前没有任何事件发生，Ali_DmxStreamPoll()返回ALI_ERR_DMX_TIMEOUT；
       失败时，Ali_DmxStreamPoll()返回错误码。

       当Ali_DmxStreamPoll()返回时，每个Ali_DmxStreamPollInfo的域StreamStatus
       标示着对应的stream是否可读/写。

@param[out] PollList，struct Ali_DmxStreamPollInfo结构体数组，每一个单元代表一个
            需要查询的Stream。
@param[in] PollUnitCnt，需要查询的Stream的个数。
@param[in] Timeout，超时时间，以毫秒为单位。

@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 等于0,操作成功。
*/
INT32 Ali_DmxStreamPoll(struct Ali_DmxStreamPollInfo * PollList, UINT32 PollUnitCnt, INT32 Timeout);


/*!
@brief 用户通过此接口查询DMX模块全局配置及运行信息。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
@param[out] DmxSysInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct ALi_DmxSysInfo，DMX会向这个地址写入查询结果。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 ALi_DmxSysInfoGet(struct ALi_DmxSysInfo *DmxSysInfo);


/*!
@brief 用户通过此接口查询每个DMX模块具体配置及运行信息。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
@param[in] DmxId是用户指定的需要查询的DMX。       
@param[out] DmxDevInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct ALi_DmxDevInfo，查询结果会写人这个地址。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 ALi_DmxDevInfoGet(UINT32 DmxId, struct ALi_DmxDevInfo *DmxDevInfo);


/*!
@brief 用户通过此接口向一个Descrambler解扰通道配置偶控制字。
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。

       所有DMX都支持配置控制字。

@param[in] KeyStreamId是用户指定的需要配置控制字的Key Stream的Id，这个ID必须
           调用Ali_DmxDescramKeyOpen()得到。       
@param[in] EvenKey是指向需要配置的偶控制字的指针,长度必须是8个byte。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,配置成功。
*/
INT32 Ali_DmxDescramKeySetEven(UINT32 KeyStreamId, UINT8 * EvenKey);


/*!
@brief 用户通过此接口向一个Descrambler解扰通道配置奇控制字。
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。

       所有DMX都支持配置控制字。

@param[in] KeyStreamId是用户指定的需要配置控制字的Key Stream的Id，这个ID必须
           调用Ali_DmxDescramKeyOpen()得到。       
@param[in] OddKey是指向需要配置的奇控制字的指针,长度必须是8个byte。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,配置成功。
*/
INT32 Ali_DmxDescramKeySetOdd(UINT32 KeyStreamId, UINT8 * OddKey);


/*!
@brief 用户通过此接口向Descrambler模块申请一个解扰控制字通道

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。所有DMX都支持配置控制字。

       所有DMX都支持配置控制字。

@param[in] DmxId是用户指定的需要解扰的TS流所在的DMX。       
@param[in] Param是用户指定的需要解扰的TS流的配置信息，包括TS流的PID。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于0，成功分配得到的解扰控制通道的ID，用户通过这个ID配置后续控制字。
*/
INT32 Ali_DmxDescramKeyOpen(UINT32 DmxId, struct Ali_DmxDescramKeyStreamParam * Param);


/*!
@brief 用户通过此接口向Descrambler模块释放一个解扰控制字通道

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。所有DMX都支持配置控制字。

       所有DMX都支持配置控制字。

@param[in] KeyStreamId,用户指定的需要释放的解扰通道的ID。      
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 等于0，释放成功
*/
INT32 Ali_DmxDescramKeyClose(INT32 KeyStreamId);




/*!
@brief 用户通过此接口向Descrambler模块配置默认控制字。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。所有DMX都支持配置控制字。
       
       所有DMX都支持配置控制字。

@param[in] DmxId,用户指定的需要解扰的TS流所在的DMX。      
@param[in] Pid是用户指定的需要解扰的TS流的PID。
@param[in] DefaultKey是指向需要配置的默认控制字的指针。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
INT32 Ali_DmxDescramDefaultKeySet(UINT32 DmxId, UINT32 Pid, UINT8 *DefaultKey);

/*!
@brief 用户通过此接口向Descrambler模块查询对应的DSC Channel是否已经work.

       如果已经打开相应的DSC Channel，则返回相应的StreamID;否则返回-1.
     
@param[in] KeyStreamInfo中的Pid是用户指定的需要解扰的TS流的PID。
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 其他值:已经使用的StreamIDx
*/
INT32 Ali_DmxDescramKeyInfoGet(struct Ali_DmxDescramKeyStreamParam  KeyStreamInfo);


/*!
@brief 用户通过此接口来创建一个可以读取整个TP的流。

       TS流被放入DMX内部的buffer中缓存，用户可以通过
       Ali_DmxTpStreamRead()接口读取DMX接收到的TP流数据。
       
       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       TP stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] DmxId 目标DMX的ID，DMX 0的ID为0，DMX 1的ID为1，以此类推。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,打开的TS stream的ID。
*/
INT32 Ali_DmxTpStreamOpen(UINT32 DmxId);


/*!
@brief 用户通过此接口配置一个申请得到的TP Stream。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       TP Stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，需要操作的TS Stream的ID. 
           此值由调用Ali_DmxTpStreamOpen()得到。
@param[in] StreamParam，指向数据结构struct Ali_DmxTsStreamParam的指针，用户
           通过这个指针配置TS Stream的参数。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxTpStreamCfg(INT32 StreamId, struct Ali_DmxTpStreamParam *StreamParam);


/*!
@brief 用户通过此接口使能一个TP类型的数据通道。
       
       用户可以通过Ali_DmxTpStreamRead()接口读取TP流。
       
       TP stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxTpStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,使能成功。
*/
INT32 Ali_DmxTpStreamStart(INT32 StreamId);



/*!
@brief 用户通过此接口停止一个TP stream。

       Stream关闭后，DMX停止收取这个stream的数据，而与这个stream相关的资源不会
       被释放，用户可以调用Ali_DmxTpStreamCfg()接口重新配置这个stream。
       
       请注意这个接口在stream为RUN的状态下才有效。
       
       TP stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxTsStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxTpStreamStop(INT32 StreamId);



/*!
@brief 用户通过此接口关闭一个TS stream。

       用户可以在除IDLE之外的任何状态下调用这个接口。
       
       TS Stream被Close后，所有与这个stream相关的资源都会被释放，这个TP stream
       会空闲下来等待下一次重新被open使用。
       
       TP stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxTsStreamOpen()得到。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,操作成功。
*/
INT32 Ali_DmxTpStreamClose(INT32 StreamId);


/*!
@brief 用户通过此接口向DEMUX读取一个已经打开的TP stream的数据。

       如果需要读取的stream暂无数据，用户可以通过Ali_DmxStreamPoll()接口实现
       数据等待。
       
	   用户需要提供一个用以保存TS数据的缓冲区的地址给DMX，这个地址的长度需
	   要足够保存一个完整的TS包(188 bytes)，推荐的值为470K。过短则可能需要更多
       的系统调用而影响系统性能。
	   
	   用户可以调用Ali_DmxStreamPoll()接口实现对多个stream的等待，请参见
	   Ali_DmxStreamPoll()接口说明。
	   
	   注意read操作只有在TS stream为RUN的状态下才有效。
	   
       TP stream的操作流程请参考ALI_DMX_MES.doc。
       
@param[in] StreamId，此值由调用Ali_DmxTpStreamOpen()得到。
@param[out] Buf，用户提供的用以存储TS的缓冲地址。
@param[in] BufLen，用户提供缓冲长度。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 大于等于0,读取到的数据的长度，以byte为单位。
*/
INT32 Ali_DmxTpStreamRead(INT32 StreamId, UINT8 *Buf, UINT32 BufLen);



/*!
@brief 用户通过此接口向DMX查询一个TP stream的状态。

       ALI DMX支持2个硬件DMX(DmxId 0 ~ 1)和2个软DMX(DmxId 3 ~ 4),
       只有软DMX支持TS_IN_RAM_STREAM。
       
       TP stream的操作流程请参考文档ALI_DMX_MES.doc。
       
@param[in] StreamId 需要查询的TS stream的ID。
@param[out] TsStreamInfo是用户提供的用以储存查询结果的指针，指向数据结构
            struct Ali_DmxTpStreamInfo。
@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 0,查询成功。
*/
//INT32 Ali_DmxTpStreamInfoGet(INT32 StreamId, struct Ali_DmxTpStreamInfo * TpStreamInfo);


INT32 Ali_DmxSubtStreamOpen(UINT32 DmxId);
INT32 Ali_DmxSubtStreamCfg(INT32 StreamId, struct Ali_DmxSubtStreamParam * StreamParam);
INT32 Ali_DmxSubtStreamStart(INT32 StreamId);
INT32 Ali_DmxSubtStreamStop(INT32 StreamId);
INT32 Ali_DmxSubtStreamClose(INT32 StreamId);



/*!
@brief ALI DMX LIB释放接口

       如果用户不再需要使用ALI DMX LIB，调用本接口会释放所有ALI DMX LIB占用
       的资源。

@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 等于0,操作成功。
*/
INT32 Ali_DmxLibExit(void);


/*!
@brief ALI DMX LIB初始化接口。

       要使用ALI DMX LIB，必须在使用任何其他LI DMX LIB接口之前，先调用本接口。

       本接口不能重复调用。

@return ALI_DMX_ERR_CODE
@retval 小于0,错误码。错误码定义请参考enum ALI_DMX_ERR_CODE。
@retval 等于0,操作成功。
*/
INT32 Ali_DmxLibInit(void);

/*!
@}
*/

#ifdef __cplusplus
}
#endif

#endif
