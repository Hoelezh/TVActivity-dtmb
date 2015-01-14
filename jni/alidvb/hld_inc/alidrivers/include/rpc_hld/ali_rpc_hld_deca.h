#ifndef __DRIVERS_ALI_RPC_HLD_DECA_H
#define __DRIVERS_ALI_RPC_HLD_DECA_H

#include "ali_rpc_hld.h"

#include <alidefinition/adf_deca.h>



enum LLD_DECA_M36_FUNC
{
    FUNC_DECA_M36_ATTACH = 0,   
    FUNC_DECA_M36_DVR_ENABLE,
    FUNC_DECA_M36_EXT_DEC_ENABLE,
    FUNC_DECA_M36_INIT_TONE_VOICE,
};



enum HLD_DECA_FUNC
{
    FUNC_DECA_PCM_BUF_RESUME = 0,   
    FUNC_DECA_OPEN,
    FUNC_DECA_CLOSE,
    FUNC_DECA_SET_SYNC_MODE,
    FUNC_DECA_START,
    FUNC_DECA_STOP,
    FUNC_DECA_PAUSE,
    FUNC_DECA_IO_CONTROL,
    FUNC_DECA_REQUEST_WRITE,
    FUNC_DECA_UPDATE_WRITE,
    FUNC_DECA_TONE_VOICE,
    FUNC_DECA_STOP_TONE_VOICE,    
    FUNC_DECA_REQUEST_DESC_WRITE,
    FUNC_DECA_UPDATE_DESC_WRITE,
    FUNC_DECA_INIT_ASE_VOICE,
    FUNC_DECA_PROCESS_PCM_SAMPLES,
    FUNC_DECA_PROCESS_PCM_BITSTREAM,
    FUNC_DECA_DECORE_IOCTL,
    FUNC_DECA_STANDBY,
    FUNC_DECA_SET_DBG_LEVEL,
};





typedef struct st_deca_inject
{
    struct deca_device *pst_dev_deca;
    int i_sbm_idx;

} deca_inject, *pdeca_inject;




struct deca_device
{
    struct deca_device  *next;  /* next device */
    /* struct module *owner; */
    INT32 type;
    INT8 name[HLD_MAX_NAME_SIZE];
    INT32 flags;     // This field used to record current running status

    INT32 hardware;
    INT32 busy;      // This field used to record sub state of DECA_STATE_PLAY, could be: busy, no data, no buffer.
    INT32 minor;     // This field used to record previous running status

    void *priv;      // Used to be 'private' but that upsets C++
    UINT32 base_addr;
    INT32 ase_flags; // This field used to record current running status of ASE task

    UINT32 standby_cmd;
    UINT32 ae_standby_status;

    void       (*attach)             (void);
    void       (*detach)             (struct deca_device **);
    RET_CODE   (*open)               (struct deca_device *, enum AudioStreamType, enum AudioSampleRate, enum AudioQuantization, UINT8, UINT32);
    RET_CODE   (*close)              (struct deca_device *);
    RET_CODE   (*start)              (struct deca_device *, UINT32);
    RET_CODE   (*stop)               (struct deca_device *, UINT32, enum ADecStopMode);
    RET_CODE   (*pause)              (struct deca_device *);
    RET_CODE   (*set_sync_mode)      (struct deca_device *, enum ADecSyncMode);
    RET_CODE   (*ioctl)              (struct deca_device *, UINT32 , UINT32);
    RET_CODE   (*request_write)      (struct deca_device *, UINT32, void **, UINT32 *, struct control_block *);
    void       (*update_write)       (struct deca_device *, UINT32);
    void       (*pcm_buf_resume)     (struct deca_device *);
    void       (*tone_voice)         (struct deca_device *, UINT32, UINT8); //tone voice
    void       (*stop_tone_voice)    (struct deca_device *);
    RET_CODE   (*ase_cmd)            (struct deca_device *, UINT32 , UINT32);
    /* add for audio description*/
    RET_CODE   (*request_desc_write) (struct deca_device *, UINT32, void **, UINT32 *, struct control_block *);
    void       (*update_desc_write)  (struct deca_device *, UINT32);
    void       (*ase_init)           (struct deca_device *);
    UINT32     (*standby)            (struct deca_device *, UINT32);
    RET_CODE   (*set_dbg_level)      (struct deca_device *,UINT32);

    // add by jacket for s3921
    RET_CODE   (*ae_decode)          (struct deca_device *, void *, void *);
    RET_CODE   (*ae_reset)           (struct deca_device *);

};



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
UINT32 deca_standby(struct deca_device *dev, UINT32 status);
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

#ifdef CONFIG_ARM
int deca_decore_ioctl(UINT32 cmd, void *param1, void *param2);
#else
RET_CODE deca_decore_ioctl(struct deca_device *dev, UINT32 cmd, void *param1, void *param2);
#endif
RET_CODE deca_set_dbg_level(struct deca_device *dev,UINT32 option);

void deca_m36_attach(struct deca_feature_config *config);
void deca_m36_dvr_enable(struct deca_device *dev);
void deca_m36_ext_dec_enable(struct deca_device *dev, struct deca_feature_config *config);
void deca_m36_init_tone_voice(struct deca_device *dev);


#endif



