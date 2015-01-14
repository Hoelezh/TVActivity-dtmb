#ifndef _ADR_DECA_H_
#define _ADR_DECA_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <adr_mediatypes.h>
#include "adr_deca_dev.h"
#include <ali_audio_common.h>



/*! @addtogroup deca
 *  @{
 */
 
#ifdef AC3DEC
#define DVB_AUDIO_EXT //SUPPORT DVB AUDIO EXTENTION, INCLUDE: AAC, AC3 AND DTS
#endif

#define DECA_STATE_DETACH       0
#define DECA_STATE_ATTACH       1
#define DECA_STATE_IDLE         2
#define DECA_STATE_PLAY         4
#define DECA_STATE_PAUSE        8

#define DECA_SUB_STATE_BUSY     1
#define DECA_SUB_STATE_NO_DATA  2
#define DECA_SUB_STATE_NO_BUFF  4


/** Remove all debug output lines
 */
#define DBG_DECA_NO_OUTPUT      0
#define DBG_DECA_API            0x00000001 
#define DBG_DECA_ERROR          0x00000002
#define DBG_DECA_BUF            0x00000004

#define DBG_LEV_ALL             0xFFFFFFFF



void deca_m36_attach(struct deca_feature_config *config);
void deca_m36_dettach(struct deca_device *dev);



RET_CODE deca_open(struct deca_device *dev,
                   enum AudioStreamType stream_type,
                   enum AudioSampleRate samp_rate,
                   enum AudioQuantization quan,
                   UINT8 channel_num,
                   UINT32 info_struct);
RET_CODE deca_close(struct deca_device *dev);
RET_CODE deca_start(struct deca_device *dev, UINT32 high32_pts);
RET_CODE deca_stop(struct deca_device *dev, UINT32 high32_pts, enum ADecStopMode mode);
RET_CODE deca_pause(struct deca_device *dev);
RET_CODE deca_io_control(struct deca_device *dev, UINT32 cmd, UINT32 param);
RET_CODE deca_set_sync_mode(struct deca_device *dev, enum ADecSyncMode mode);
RET_CODE deca_request_write(void *dev,
                            UINT32 req_size,
                            void **ret_buf,
                            UINT32 *ret_buf_size,
                            struct control_block *ctrl_blk);
RET_CODE deca_request_desc_write(void *device,
                                 UINT32 req_size,
                                 void **ret_buf,
                                 UINT32 *ret_buf_size,
                                 struct control_block *ctrl_blk);
void deca_update_write(void *dev, UINT32 size);
void deca_update_desc_write(void *device, UINT32 size);
void deca_pcm_buf_resume(UINT32 val);
void deca_tone_voice(struct deca_device *dev, UINT32 SNR, UINT8 init);  //tone voice
void deca_stop_tone_voice(struct deca_device *dev);  //tone voice
void deca_init_ase(struct deca_device *dev);
void deca_process_pcm_samples(UINT32 pcm_bytes_len,
                              UINT8 *pcm_raw_buf,
                              UINT32 sample_rate,
                              UINT32 channel_num,
                              UINT32 sample_precision);
void deca_process_pcm_bitstream(UINT32 pcm_bytes_len,
                                UINT8 *pcm_raw_buf,
                                UINT32 bs_length,
                                UINT8 *un_processed_bs,
                                UINT32 sample_rate,
                                UINT32 channel_num,
                                UINT32 sample_precision);
RET_CODE deca_decore_ioctl(struct deca_device *dev, UINT32 cmd, void *param1, void *param2);
RET_CODE deca_set_dbg_level(struct deca_device *dev,UINT32 option);



extern UINT32 g_deca_dbg_option;

//do{if(option & g_deca_dbg_level) libc_printf(fmt,args);} while(0)
#define DBG_DECA_PRINTF(option, fmt, args...)   \
{                                               \
      if (option & g_deca_dbg_option )          \
            ibc_printf(fmt,args);              \
}


#ifdef __cplusplus
    }
#endif



#endif /*_DECA_H_*/



