#ifndef _ALI_DMX_LIB_INTERNAL_H_
#define _ALI_DMX_LIB_INTERNAL_H_

#include <linux/types.h>


/* HW DMX linux output inerface dev name, used by kernel.
*/
#define ALI_HWDMX0_OUTPUT_NAME "ali_hwdmx0_output"
#define ALI_HWDMX1_OUTPUT_NAME "ali_hwdmx1_output"
#define ALI_HWDMX2_OUTPUT_NAME "ali_hwdmx2_output"
#define ALI_HWDMX3_OUTPUT_NAME "ali_hwdmx3_output"
#define ALI_HWDMX4_OUTPUT_NAME "ali_hwdmx4_output"
#define ALI_HWDMX5_OUTPUT_NAME "ali_hwdmx5_output"
#define ALI_HWDMX6_OUTPUT_NAME "ali_hwdmx6_output"
#define ALI_HWDMX7_OUTPUT_NAME "ali_hwdmx7_output"

/* SW DMX linux output inerface dev name, used by kernel.
*/
#define ALI_SWDMX0_OUTPUT_NAME "ali_swdmx0_output"
#define ALI_SWDMX1_OUTPUT_NAME "ali_swdmx1_output"
#define ALI_SWDMX2_OUTPUT_NAME "ali_swdmx2_output"
#define ALI_SWDMX3_OUTPUT_NAME "ali_swdmx3_output"
#define ALI_SWDMX4_OUTPUT_NAME "ali_swdmx4_output"
#define ALI_SWDMX5_OUTPUT_NAME "ali_swdmx5_output"
#define ALI_SWDMX6_OUTPUT_NAME "ali_swdmx6_output"
#define ALI_SWDMX7_OUTPUT_NAME "ali_swdmx7_output"


/* SW DMX linux input inerface dev name, used by kernel.
*/
#define ALI_SWDMX0_INPUT_NAME "ali_swdmx0_input"
#define ALI_SWDMX1_INPUT_NAME "ali_swdmx1_input"
#define ALI_SWDMX2_INPUT_NAME "ali_swdmx2_input"
#define ALI_SWDMX3_INPUT_NAME "ali_swdmx3_input"
#define ALI_SWDMX4_INPUT_NAME "ali_swdmx4_input"
#define ALI_SWDMX5_INPUT_NAME "ali_swdmx5_input"
#define ALI_SWDMX6_INPUT_NAME "ali_swdmx6_input"
#define ALI_SWDMX7_INPUT_NAME "ali_swdmx7_input"


/* HW DMX linux output inerface dev path, used by user space.
*/
#define ALI_HWDMX0_OUTPUT_PATH "/dev/ali_hwdmx0_output"
#define ALI_HWDMX1_OUTPUT_PATH "/dev/ali_hwdmx1_output"
#define ALI_HWDMX2_OUTPUT_PATH "/dev/ali_hwdmx2_output"
#define ALI_HWDMX3_OUTPUT_PATH "/dev/ali_hwdmx3_output"
#define ALI_HWDMX4_OUTPUT_PATH "/dev/ali_hwdmx4_output"
#define ALI_HWDMX5_OUTPUT_PATH "/dev/ali_hwdmx5_output"
#define ALI_HWDMX6_OUTPUT_PATH "/dev/ali_hwdmx6_output"
#define ALI_HWDMX7_OUTPUT_PATH "/dev/ali_hwdmx7_output"

/* SW DMX linux output inerface dev name, used by user space.
*/
#define ALI_SWDMX0_OUTPUT_PATH "/dev/ali_swdmx0_output"
#define ALI_SWDMX1_OUTPUT_PATH "/dev/ali_swdmx1_output"
#define ALI_SWDMX2_OUTPUT_PATH "/dev/ali_swdmx2_output"
#define ALI_SWDMX3_OUTPUT_PATH "/dev/ali_swdmx3_output"
#define ALI_SWDMX4_OUTPUT_PATH "/dev/ali_swdmx4_output"
#define ALI_SWDMX5_OUTPUT_PATH "/dev/ali_swdmx5_output"
#define ALI_SWDMX6_OUTPUT_PATH "/dev/ali_swdmx6_output"
#define ALI_SWDMX7_OUTPUT_PATH "/dev/ali_swdmx7_output"


/* SW DMX linux input inerface dev name, used by user space.
*/
#define ALI_SWDMX0_INPUT_PATH "/dev/ali_swdmx0_input"
#define ALI_SWDMX1_INPUT_PATH "/dev/ali_swdmx1_input"
#define ALI_SWDMX2_INPUT_PATH "/dev/ali_swdmx2_input"
#define ALI_SWDMX3_INPUT_PATH "/dev/ali_swdmx3_input"
#define ALI_SWDMX4_INPUT_PATH "/dev/ali_swdmx4_input"
#define ALI_SWDMX5_INPUT_PATH "/dev/ali_swdmx5_input"
#define ALI_SWDMX6_INPUT_PATH "/dev/ali_swdmx6_input"
#define ALI_SWDMX7_INPUT_PATH "/dev/ali_swdmx7_input"

/* DMX hw inerface ID, data source from tuner, used by kernel.
*/
#define ALI_HWDMX0_OUTPUT_HWIF_ID 0
#define ALI_HWDMX1_OUTPUT_HWIF_ID 1
#define ALI_HWDMX2_OUTPUT_HWIF_ID 2
#define ALI_HWDMX3_OUTPUT_HWIF_ID 3

/* DMX hw inerface ID, data source from user space, used by kernel.
*/
#define ALI_SWDMX0_OUTPUT_HWIF_ID 4
#define ALI_SWDMX1_OUTPUT_HWIF_ID 5

/* DMX hw inerface ID, data source from SEE, used by kernel.
*/
#define ALI_SEETOMAIN_BUF_HWIF_ID 6


/* HW DMX data engine task name.
*/
#define ALI_HWDMX0_ENGINE_NAME "ali_hwdmx0_engine"
#define ALI_HWDMX1_ENGINE_NAME "ali_hwdmx1_engine"
#define ALI_HWDMX2_ENGINE_NAME "ali_hwdmx2_engine"
#define ALI_HWDMX3_ENGINE_NAME "ali_hwdmx3_engine"
#define ALI_HWDMX4_ENGINE_NAME "ali_hwdmx4_engine"
#define ALI_HWDMX5_ENGINE_NAME "ali_hwdmx5_engine"
#define ALI_HWDMX6_ENGINE_NAME "ali_hwdmx6_engine"
#define ALI_HWDMX7_ENGINE_NAME "ali_hwdmx7_engine"

/* SW DMX data engine task name.
*/
#define ALI_SWDMX0_ENGINE_NAME "ali_swdmx0_engine"
#define ALI_SWDMX1_ENGINE_NAME "ali_swdmx1_engine"
#define ALI_SWDMX2_ENGINE_NAME "ali_swdmx2_engine"
#define ALI_SWDMX3_ENGINE_NAME "ali_swdmx3_engine"
#define ALI_SWDMX4_ENGINE_NAME "ali_swdmx4_engine"
#define ALI_SWDMX5_ENGINE_NAME "ali_swdmx5_engine"
#define ALI_SWDMX6_ENGINE_NAME "ali_swdmx6_engine"
#define ALI_SWDMX7_ENGINE_NAME "ali_swdmx7_engine"


/* SEE to main data engine task name.
*/
#define ALI_DMX_SEE2MAIN0_ENGINE_NAME "ali_dmx_see2main0_engine"
#define ALI_DMX_SEE2MAIN1_ENGINE_NAME "ali_dmx_see2main1_engine"
#define ALI_DMX_SEE2MAIN2_ENGINE_NAME "ali_dmx_see2main2_engine"
#define ALI_DMX_SEE2MAIN3_ENGINE_NAME "ali_dmx_see2main3_engine"
#define ALI_DMX_SEE2MAIN4_ENGINE_NAME "ali_dmx_see2main4_engine"
#define ALI_DMX_SEE2MAIN5_ENGINE_NAME "ali_dmx_see2main5_engine"
#define ALI_DMX_SEE2MAIN6_ENGINE_NAME "ali_dmx_see2main6_engine"
#define ALI_DMX_SEE2MAIN7_ENGINE_NAME "ali_dmx_see2main7_engine"


struct Ali_DmxKernGlobalStatInfo
{
	__u32 TotalTsInCnt;
	__u32 DmxBufEmptyCnt;
	__u32 OverlapCnt;
	__u32 PlayBusyCnt;
	__u32 NobodyCareCnt;
	__u32 RealTimePrintEn;
};

struct Ali_DmxDrvTsStrmStatInfo
{
	__u32 TsFltIdx;
	__u32 TsInCnt;
	__u32 StrTypeErrCnt;
	__u32 StatErrCnt;
	__u32 WrByteErrCnt;
	__u32 RdByteErrCnt;
	__u32 CopyErrCnt;
	__u32 CloseFailCnt;
	__u32 CfgFailCnt;
	__u32 StartFailCnt;
	__u32 StopFailCnt;
	__u32 NoPidCnt;
};

struct Ali_DmxDrvTsInRamStrmStatInfo
{
	__u32 StatErrCnt;
	__u32 CopyErrCnt;
};

struct Ali_DmxDrvVideoStrmStatInfo
{
	__u32 TsInCnt;
	__u32 StrTypeErrCnt;
	__u32 StatErrCnt;
	__u32 CopyErrCnt;
	__u32 CloseFailCnt;
	__u32 CfgFailCnt;
	__u32 StartFailCnt;
	__u32 StopFailCnt;
};

struct Ali_DmxDrvAudioStrmStatInfo
{
	__u32 TsInCnt;
	__u32 StrTypeErrCnt;
	__u32 StatErrCnt;
	__u32 CopyErrCnt;
	__u32 CloseFailCnt;
	__u32 CfgFailCnt;
	__u32 StartFailCnt;
	__u32 StopFailCnt;
};

struct Ali_DmxDrvPcrStrmStatInfo
{
	__u32 TsInCnt;
	__u32 PcrInCnt;
	__u32 LastPcrVal;
	__u32 StrTypeErrCnt;
	__u32 StatErrCnt;
	__u32 RdByteErrCnt;
	__u32 RdBufShortCnt;
	__u32 CopyErrCnt;
	__u32 CloseFailCnt;
	__u32 CfgFailCnt;
	__u32 StartFailCnt;
	__u32 StopFailCnt;
};

struct Ali_DmxDrvSecStrmStatInfo
{
	__u32 TsInCnt;
	__u32 ByteInCnt;
	__u32 SecInCnt;
	__u32 SecOutCnt;
	__u32 CbTypeErrCnt;
	__u32 StrTypeErrCnt;
	__u32 StatErrCnt;
	__u32 WrByteErrCnt;
	__u32 RdBufShortCnt;
	__u32 CopyErrCnt;
	__u32 CloseFailCnt;
	__u32 CfgFailCnt;
	__u32 StartFailCnt;
	__u32 StopFailCnt;
};

struct Ali_DmxDrvPesStrmStatInfo
{
	__u32 TsInCnt;
	__u32 PesInCnt;
	__u32 PesOutCnt;
	__u32 CbTypeErrCnt;
	__u32 StrTypeErrCnt;
	__u32 StatErrCnt;
	__u32 WrByteErrCnt;
	__u32 RdBufShortCnt;
	__u32 CopyErrCnt;
	__u32 CloseFailCnt;
	__u32 CfgFailCnt;
	__u32 StartFailCnt;
	__u32 StopFailCnt;
};


struct Ali_DmxDrvTpStrmStatInfo
{
	__u32 TsInCnt;
	__u32 ByteInCnt;
	__u32 StrTypeErrCnt;
	__u32 StatErrCnt;
	__u32 WrByteErrCnt;
	__u32 RdByteErrCnt;
	__u32 RdBufShortCnt;
	__u32 CopyErrCnt;
	__u32 CloseFailCnt;
	__u32 CfgFailCnt;
	__u32 StartFailCnt;
	__u32 StopFailCnt;
};


struct Ali_DmxDrvTsFltStatInfo
{
	__u32 TsFltIdx;
    __u32 TsInCnt;
    __u32 TsScrmbCnt;
    __u32 TsSyncByteErrCnt;
	__u32 TsDupCnt;
	__u32 TsLostCnt;
    __u32 TsErrCnt;
};

struct Ali_DmxDrvSecFltStatInfo
{
	__u32 SecFltIdx;
	__u32 SecInCnt;
	__u32 SecOutCnt;
	__u32 SecTsNoPayloadCnt;
	__u32 SecTsScrmbCnt;
	__u32 SecTsDupCnt;
	__u32 SecTsLostCnt;
	__u32 SecPtErrCnt;
	__u32 SecHdrTooShortCnt;
	__u32 SecDataNotFullCnt;
	__u32 SecDataTooShortCnt;
	__u32 SecMaskTooLongCnt;
	__u32 SecMaskMismatchCnt;
	__u32 SecBufOverflowCnt;
};

struct Ali_DmxDrvPesFltStatInfo
{
	__u32 PesFltIdx;
	__u32 PesInCnt;
	__u32 PesOutCnt;
	__u32 PesHdrErrCnt;
	__u32 PesTsNoPayloadCnt;
	__u32 PesTsScrmbCnt;
	__u32 PesTsDupCnt;
	__u32 PesTsLostCnt;
	__u32 PesBufOverflowCnt;
};


struct Ali_DmxSubtStreamInfo
{
	__s32 StreamIdx;
	__s32 StreamState;
};



/* SEE dmx statistics.
 */
struct Ali_DmxSeeGlobalStatInfo
{
	__u32 TotalTsInCnt;
	__u32 TsOddCnt;
	__u32 TsDecrySucCnt;
	__u32 TsDecryFailCnt;
	__u32 TsDecryEmptyCnt;
	__u32 TsRetToMainCnt;
	__u32 TsSyncErrCnt;
};

struct Ali_DmxSeePlyChStatInfo 
{
    __u32 TsInCnt;
    __u32 TsPlayBusyCnt;
    __u32 TsScrmbCnt;
	__u32 TsErrCnt;
	
	__u32 PesTsErrCnt;
	__u32 PesTsScrmbCnt;
    __u32 PesTsDupCnt;
    __u32 PesTsLostCnt;
    __u32 PesHdrLenErrCnt;
    __u32 PesHdrScErrCnt;
    __u32 PesHdrCnt;
    __u32 PesScrmbCnt;
    __u32 PesStreamIdErrCnt;
    __u32 PesHdrPayloadLenErrCnt;
    __u32 PesCallbackNobufCnt;
    __u32 PesReqBufBusyCnt;
    __u32 PesReqDecStateErrCnt;
    __u32 PesTsNoPayloadCnt;
    __u32 PesBufOverflowCnt;
    __u32 PesBufUpdateCnt;
    __u32 PesBufReqCnt;

	__u16 PlyChPid;
};

/* SEE dmx statistics.
*  Must keep compartible with TDS struct Ali_DmxSeeStatistics.
*/
struct Ali_DmxSeeStatistics
{
	/* Video stream statistics
	*/
	__u32 VideoTsInCnt;
	__u32 VideoTsLostCnt;
	__u32 VideoTsDupCnt;
	__u8 VideoTsSrcScramFlag;
	__u8 VideoTsCurScramFlag;
	__u8 VideoTsPusiMismatchFlag;
	__u8 VideoReserved;

	/* Audio stream statistics
	*/
	__u32 AudioTsInCnt;
	__u32 AudioTsLostCnt;
	__u32 AudioTsDupCnt;
	__u8 AudioTsSrcScramFlag;
	__u8 AudioTsCurScramFlag;
	__u8 AudioTsPusiMismatchFlag;
	__u8 AudioReserved;

	/* PCR.
	*/
	__u32 Pcr;

	/* Realtime Enable.
	*/
	__u32 RealTimePrintEn;
};

struct Ali_DmxLibTsStrmStatInfo
{
	UINT32 StatErrCnt;
	UINT32 InvPathCnt;
	UINT32 IoOpenFailCnt;
	UINT32 IoCfgFailCnt;
	UINT32 IoStartFailCnt;
	UINT32 IoStopFailCnt;
};

struct Ali_DmxLibTsInRamStrmStatInfo
{
	UINT32 StatErrCnt;
};

struct Ali_DmxLibVideoStrmStatInfo
{
	UINT32 StatErrCnt;
	UINT32 InvPathCnt;
	UINT32 IoOpenFailCnt;
	UINT32 IoCfgFailCnt;
	UINT32 IoStartFailCnt;
	UINT32 IoStopFailCnt;
};

struct Ali_DmxLibAudioStrmStatInfo
{
	UINT32 StatErrCnt;
	UINT32 InvPathCnt;
	UINT32 IoOpenFailCnt;
	UINT32 IoCfgFailCnt;
	UINT32 IoStartFailCnt;
	UINT32 IoStopFailCnt;
};

struct Ali_DmxLibPcrStrmStatInfo
{
	UINT32 StatErrCnt;
	UINT32 InvPathCnt;
	UINT32 IoOpenFailCnt;
	UINT32 IoCfgFailCnt;
	UINT32 IoStartFailCnt;
	UINT32 IoStopFailCnt;
};

struct Ali_DmxLibSecStrmStatInfo
{
	UINT32 StatErrCnt;
	UINT32 InvPathCnt;
	UINT32 CrcErrCnt;
	UINT32 IoOpenFailCnt;
	UINT32 IoCfgFailCnt;
	UINT32 IoStartFailCnt;
	UINT32 IoStopFailCnt;
};

struct Ali_DmxLibSecSlotStatInfo
{
	UINT32 CallbackCnt;
	UINT32 CbTimeOutCnt;
	UINT32 StatErrCnt;
	UINT32 NoSecBufCnt;
	UINT32 CallbackErrCnt;
	UINT32 ThreadCreatErrCnt;
	UINT32 StrmOpenFailCnt;
	UINT32 StrmCfgFailCnt;
	UINT32 StrmStartFailCnt;
	UINT32 StrmStopFailCnt;
	UINT32 StrmCloseFailCnt;
};

struct Ali_DmxLibSecFltStatInfo
{
	UINT32 CallbackCnt;
	UINT32 StatErrCnt;
	UINT32 SlotOpenFailCnt;
	UINT32 SlotCfgFailCnt;
	UINT32 SlotStartFailCnt;
	UINT32 SlotStopFailCnt;
	UINT32 SlotCloseFailCnt;
};

struct Ali_DmxLibSecChStatInfo
{
	UINT32 StatErrCnt;
	UINT32 DupPidCnt;
	UINT32 DupFltCnt;
};


struct Ali_DmxLibTpStrmStatInfo
{
	UINT32 StatErrCnt;
	UINT32 InvPathCnt;
	UINT32 IoOpenFailCnt;
	UINT32 IoCfgFailCnt;
	UINT32 IoStartFailCnt;
	UINT32 IoStopFailCnt;
};


struct Ali_DmxSlotSecStatInfo
{
	UINT32 IoOpenFailCnt;
	UINT32 IoStartFailCnt;
	UINT32 SecMaskMissCnt;
	UINT32 SecCrcErrCnt;
	UINT32 SecCallbackCnt;
};

struct Ali_DmxSlotPesStatInfo
{
	UINT32 IoOpenFailCnt;
	UINT32 IoStartFailCnt;
	UINT32 PesHdrErrCnt;
	UINT32 PesBufReqCnt;
	UINT32 PesBufRetCnt;
	UINT32 PesBufEmptyCnt;
	UINT32 PesReqFailCnt;
};

#define ALI_DMX_IOC_MAGIC  0xA1


/* Main line IO commands.
 */
#define ALI_DMX_SEC_STREAM_CFG _IOW(ALI_DMX_IOC_MAGIC, 500, struct Ali_DmxSecStreamParam)

#define ALI_DMX_SEC_STREAM_START _IO(ALI_DMX_IOC_MAGIC, 501)

#define ALI_DMX_SEC_STREAM_STOP _IO(ALI_DMX_IOC_MAGIC, 502)

#define ALI_DMX_SEC_STREAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 503, struct Ali_DmxDrvSecStrmStatInfo)

#define ALI_DMX_SEC_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 504, struct Ali_DmxDrvSecFltStatInfo)


#define ALI_DMX_TS_STREAM_CFG _IOW(ALI_DMX_IOC_MAGIC, 510, struct Ali_DmxTsStreamParam)

#define ALI_DMX_TS_STREAM_START _IO(ALI_DMX_IOC_MAGIC, 511)

#define ALI_DMX_TS_STREAM_STOP _IO(ALI_DMX_IOC_MAGIC, 512)

#define ALI_DMX_TS_STREAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 513, struct Ali_DmxDrvTsStrmStatInfo)

#define ALI_DMX_TS_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 514, struct Ali_DmxDrvTsFltStatInfo)


#define ALI_DMX_AUDIO_STREAM_CFG _IOW(ALI_DMX_IOC_MAGIC, 520, struct Ali_DmxAudioStreamParam)

#define ALI_DMX_AUDIO_STREAM_START _IO(ALI_DMX_IOC_MAGIC, 521)

#define ALI_DMX_AUDIO_STREAM_STOP _IO(ALI_DMX_IOC_MAGIC, 522)

#define ALI_DMX_AUDIO_STREAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 523, struct Ali_DmxDrvAudioStrmStatInfo)

#define ALI_DMX_AUDIO_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 524, struct Ali_DmxDrvTsFltStatInfo)

#define ALI_DMX_AUDIO_SEE_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 525, struct Ali_DmxSeePlyChStatInfo)


#define ALI_DMX_VIDEO_STREAM_CFG _IOW(ALI_DMX_IOC_MAGIC, 530, struct Ali_DmxVideoStreamParam)

#define ALI_DMX_VIDEO_STREAM_START _IO(ALI_DMX_IOC_MAGIC, 531)

#define ALI_DMX_VIDEO_STREAM_STOP _IO(ALI_DMX_IOC_MAGIC, 532)

#define ALI_DMX_VIDEO_STREAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 533, struct Ali_DmxDrvVideoStrmStatInfo)

#define ALI_DMX_VIDEO_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 534, struct Ali_DmxDrvTsFltStatInfo)

#define ALI_DMX_VIDEO_SEE_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 535, struct Ali_DmxSeePlyChStatInfo)


#define ALI_DMX_PCR_STREAM_CFG _IOW(ALI_DMX_IOC_MAGIC, 540, struct Ali_DmxPcrStreamParam)

#define ALI_DMX_PCR_STREAM_START _IO(ALI_DMX_IOC_MAGIC, 541)

#define ALI_DMX_PCR_STREAM_STOP _IO(ALI_DMX_IOC_MAGIC, 542)

#define ALI_DMX_PCR_STREAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 543, struct Ali_DmxDrvPcrStrmStatInfo)

#define ALI_DMX_PCR_FILTER_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 544, struct Ali_DmxDrvTsFltStatInfo)


#define ALI_DMX_TS_IN_RAM_STREAM_CFG _IOW(ALI_DMX_IOC_MAGIC, 550, struct Ali_DmxTsInRamStreamParam)

#define ALI_DMX_TS_IN_RAM_STREAM_START _IO(ALI_DMX_IOC_MAGIC, 551)

#define ALI_DMX_TS_IN_RAM_STREAM_STOP _IO(ALI_DMX_IOC_MAGIC, 552)

#define ALI_DMX_TS_IN_RAM_STREAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 553, struct Ali_DmxDrvTsInRamStrmStatInfo)


#define ALI_DMX_HW_REG_STREAM_CFG _IO(ALI_DMX_IOC_MAGIC, 560)

#define ALI_DMX_HW_REG_STREAM_START _IO(ALI_DMX_IOC_MAGIC, 561)

#define ALI_DMX_HW_REG_STREAM_STOP _IO(ALI_DMX_IOC_MAGIC, 562)

#define ALI_DMX_HW_REG_STREAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 563, __u32)


#define ALI_DMX_KERN_GLB_STREAM_CFG _IO(ALI_DMX_IOC_MAGIC, 570)

#define ALI_DMX_KERN_GLB_STREAM_START _IO(ALI_DMX_IOC_MAGIC, 571)

#define ALI_DMX_KERN_GLB_STREAM_STOP _IO(ALI_DMX_IOC_MAGIC, 572)

#define ALI_DMX_KERN_GLB_STREAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 573, struct Ali_DmxKernGlobalStatInfo)

#define ALI_DMX_KERN_GLB_STREAM_REALTIME_SET _IOW(ALI_DMX_IOC_MAGIC, 574, struct Ali_DmxKernGlobalStatInfo)


#define ALI_DMX_SEE_GLB_STREAM_CFG _IO(ALI_DMX_IOC_MAGIC, 580)

#define ALI_DMX_SEE_GLB_STREAM_START _IO(ALI_DMX_IOC_MAGIC, 581)

#define ALI_DMX_SEE_GLB_STREAM_STOP _IO(ALI_DMX_IOC_MAGIC, 582)

#define ALI_DMX_SEE_GLB_STREAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 583, struct Ali_DmxSeeGlobalStatInfo)

#define ALI_DMX_SEE_GLB_STREAM_REALTIME_SET _IOW(ALI_DMX_IOC_MAGIC, 584, struct Ali_DmxSeeGlobalStatInfo)


#define ALI_DMX_TP_STREAM_CFG _IOW(ALI_DMX_IOC_MAGIC, 590, struct Ali_DmxTpStreamParam)

#define ALI_DMX_TP_STREAM_START _IO(ALI_DMX_IOC_MAGIC, 591)

#define ALI_DMX_TP_STREAM_STOP _IO(ALI_DMX_IOC_MAGIC, 592)

#define ALI_DMX_TP_STREAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 593, struct Ali_DmxDrvTpStrmStatInfo)


#define ALI_DMX_SUBT_STREAM_CFG _IOW(ALI_DMX_IOC_MAGIC, 600, struct Ali_DmxSubtStreamParam)

#define ALI_DMX_SUBT_STREAM_START _IO(ALI_DMX_IOC_MAGIC, 601)

#define ALI_DMX_SUBT_STREAM_STOP _IO(ALI_DMX_IOC_MAGIC, 602)

#define ALI_DMX_SUBT_STREAM_INFO_GET _IOR(ALI_DMX_IOC_MAGIC, 603, struct Ali_DmxSubtStreamInfo)


enum ALI_DMX_IN_OUT
{
    ALI_DMX_OUTPUT,
    ALI_DMX_INPUT
};

enum ALI_DMX_STREAM_TYPE
{
    ALI_DMX_STREAM_TYPE_SEC = 0x0,
	ALI_DMX_STREAM_TYPE_TS = 0x1000,
	ALI_DMX_STREAM_TYPE_PES = 0x2000,
	ALI_DMX_STREAM_TYPE_PCR = 0x3000,
	ALI_DMX_STREAM_TYPE_AUDIO = 0x4000,
	ALI_DMX_STREAM_TYPE_VIDEO = 0x5000,
	ALI_DMX_STREAM_TYPE_TS_IN_RAM = 0x6000,	
    ALI_DMX_STREAM_TYPE_SEC_SLOT = 0x7000,
    ALI_DMX_STREAM_TYPE_SEC_CH = 0x8000,
    ALI_DMX_STREAM_TYPE_SEC_FLT = 0x9000,
    ALI_DMX_STREAM_TYPE_SRC_CTRL = 0xA000,
    ALI_DMX_STREAM_TYPE_DESCRAM_KEY = 0xB000,   
    ALI_DMX_STREAM_TYPE_TP = 0xC000,
    ALI_DMX_STREAM_TYPE_SUBT = 0xD000,
};


enum ALI_DMX_STREAM_ID_RANGE
{
    ALI_DMX_STREAM_ID_SEC_START = 0x0,
	ALI_DMX_STREAM_ID_SEC_END = 0x1000,

    ALI_DMX_STREAM_ID_TS_START = 0x1000,
	ALI_DMX_STREAM_ID_TS_END = 0x2000,

    ALI_DMX_STREAM_ID_PES_START = 0x2000,
	ALI_DMX_STREAM_ID_PES_END = 0x3000,

    ALI_DMX_STREAM_ID_PCR_START = 0x3000,
	ALI_DMX_STREAM_ID_PCR_END = 0x4000,

    ALI_DMX_STREAM_ID_AUDIO_START = 0x4000,
	ALI_DMX_STREAM_ID_AUDIO_END = 0x5000,

    ALI_DMX_STREAM_ID_VIDEO_START = 0x5000,
	ALI_DMX_STREAM_ID_VIDEO_END = 0x6000,

    ALI_DMX_STREAM_ID_IN_TS_RAM_START = 0x6000,
	ALI_DMX_STREAM_ID_IN_TS_RAM_END = 0x7000,

    ALI_DMX_STREAM_ID_SEC_SLOT_START = 0x7000,
	ALI_DMX_STREAM_ID_SEC_SLOT_END = 0x8000,

    ALI_DMX_STREAM_ID_SEC_CH_START = 0x8000,
	ALI_DMX_STREAM_ID_SEC_CH_END = 0x9000,

    ALI_DMX_STREAM_ID_SEC_FLT_START = 0x9000,
	ALI_DMX_STREAM_ID_SEC_FLT_END = 0xA000,

    ALI_DMX_STREAM_ID_SRC_CTRL_START = 0xA000,
	ALI_DMX_STREAM_ID_SRC_CTRL_END = 0xB000,

    ALI_DMX_STREAM_ID_DESCRAM_KEY_START = 0xB000,
	ALI_DMX_STREAM_ID_DESCRAM_KEY_END = 0xC000,	

    ALI_DMX_STREAM_ID_TP_START = 0xC000,
	ALI_DMX_STREAM_ID_TP_END = 0xD000,	

    ALI_DMX_STREAM_ID_SUBT_START = 0xD000,
	ALI_DMX_STREAM_ID_SUBT_END = 0xE000,
};


#endif
