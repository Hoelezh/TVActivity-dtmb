#ifndef __DRIVERS_ALI_RPC_HLD_SND_H
#define __DRIVERS_ALI_RPC_HLD_SND_H

#include "ali_rpc_hld.h"

#include <alidefinition/adf_snd.h>


enum LLD_SND_M36_FUNC
{
    FUNC_SND_M36_ATTACH = 0,   
    FUNC_SND_M36_INIT_TONE_VOICE,
    FUNC_SND_INIT_SPECTRUM,
};



enum HLD_SND_FUNC
{
    FUNC_GET_STC,
    FUNC_SET_STC,
    FUNC_GET_STC_DIVISOR,
    FUNC_SET_STC_DIVISOR,
    FUNC_STC_PAUSE,
    FUNC_STC_INVALID,
    FUNC_STC_VALID,
    FUNC_SND_OUTPUT_CONFIG,
    FUNC_SND_OPEN,
    FUNC_SND_CLOSE,
    FUNC_SND_SET_MUTE,
    FUNC_SND_SET_VOLUME,
    FUNC_SND_GET_VOLUME,
    FUNC_SND_DATA_ENOUGH,
    FUNC_SND_REQUEST_PCM_BUFF,
    FUNC_SND_WRITE_PCM_DATA,
    FUNC_SND_WRITE_PCM_DATA2,
    FUNC_SND_IO_CONTROL,
    FUNC_SND_SET_SUB_BLK,
    FUNC_SND_SET_DUPLICATE,
    FUNC_SND_SET_SPDIF_TYPE,
    FUNC_SND_CONFIG,
    FUNC_SND_START,
    FUNC_SND_STOP,
    FUNC_SND_GEN_TONE_VOICE,
    FUNC_SND_STOP_TONE_VOICE,
    FUNC_SND_ENA_PP_8CH,
    FUNC_SND_SET_PP_DELAY,
    FUNC_SND_ENABLE_VIRTUAL_SURROUND,
    FUNC_SND_ENABLE_EQ,
    FUNC_SND_ENABLE_BASS,
    FUNC_SND_SET_DBG_LEVEL,
};

struct snd_callback
{
    OSAL_T_HSR_PROC_FUNC_PTR	phdmi_snd_cb;
    void (*spec_call_back)(INT32 *);
};



struct snd_device
{
    struct snd_device *next; /* next device */
    /* struct module *owner; */
    INT32 type;
    INT8 name[HLD_MAX_NAME_SIZE];
    INT32 flags;

    INT32 hardware;
    INT32 busy;
    INT32 minor;

    void *priv; /* Used to be 'private' but that upsets C++ */
    UINT32 base_addr;

    void       (*attach)                  (void);
    void       (*detach)                  (struct snd_device **);
    RET_CODE   (*open)                    (struct snd_device *);
    RET_CODE   (*close)                   (struct snd_device *);
    RET_CODE   (*set_mute)                (struct snd_device *, enum SndSubBlock, UINT8);
    RET_CODE   (*set_volume)              (struct snd_device *, enum SndSubBlock, UINT8);
    RET_CODE   (*set_sub_blk)             (struct snd_device *, UINT8, UINT8);
    RET_CODE   (*set_duplicate)           (struct snd_device *, enum SndDupChannel);
    RET_CODE   (*request_pcm_buff)        (struct snd_device *, UINT32);
    RET_CODE   (*data_enough)             (struct snd_device *);
    RET_CODE   (*config)                  (struct snd_device *, UINT32, UINT16, UINT8);
    RET_CODE   (*set_spdif_type)          (struct snd_device *, enum ASndOutSpdifType);
    RET_CODE   (*ioctl)                   (struct snd_device *, UINT32, UINT32);
    void       (*write_pcm_data)          (struct snd_device *, struct pcm_output*, UINT32*);
    void       (*write_pcm_data2)         (struct snd_device *, UINT32 *, UINT32 *, UINT32 *, UINT32, UINT32);
    RET_CODE   (*snd_get_stc)             (UINT32, UINT32 *, UINT8);
    void       (*snd_set_stc)             (UINT32, UINT32, UINT8);
    void       (*snd_get_divisor)         (UINT32, UINT16 *, UINT8);
    void       (*snd_set_divisor)         (UINT32, UINT16, UINT8);
    void       (*snd_stc_pause)           (UINT32, UINT8, UINT8);
    void       (*snd_invalid_stc)         (void);
    void       (*snd_valid_stc)           (void);
    void       (*start)                   (struct snd_device *);
    void       (*stop)                    (struct snd_device *);
    UINT8      (*get_volume)              (struct snd_device *);
    RET_CODE   (*ena_pp_8ch)              (struct snd_device *, UINT8);
    RET_CODE   (*set_pp_delay)            (struct snd_device *, UINT8);
    RET_CODE   (*enable_virtual_surround) (struct snd_device *, UINT8);
    RET_CODE   (*enable_eq)               (struct snd_device *, UINT8, enum EQ_TYPE);
    RET_CODE   (*enable_bass)             (struct snd_device *, UINT8);
    int        (*gen_tone_voice)          (struct snd_device *, struct pcm_output *, UINT8); //tone voice
    void       (*stop_tone_voice)         (struct snd_device *);  //tone voice
    void       (*output_config)           (struct snd_device *, struct snd_output_cfg *);
    RET_CODE   (*spectrum_cmd)            (struct snd_device *, UINT32 , UINT32);
    RET_CODE   (*request_desc_pcm_buff)   (struct snd_device *, UINT32);
    void       (*write_desc_pcm_data)     (struct snd_device *, struct pcm_output*,UINT32*);
    RET_CODE   (*set_dbg_level)           (struct snd_device *, UINT32);
    RET_CODE   (*pause)                   (struct snd_device *);
    RET_CODE   (*resume)                  (struct snd_device *); 
    UINT32     (*get_play_time)           (struct snd_device *);
};



RET_CODE snd_open(struct snd_device *dev);
RET_CODE snd_close(struct snd_device *dev);
RET_CODE snd_set_mute(struct snd_device *dev, enum SndSubBlock sub_blk, UINT8 enable);
RET_CODE snd_set_volume(struct snd_device *dev, enum SndSubBlock sub_blk, UINT8 volume);
UINT8 snd_get_volume(struct snd_device *dev);
RET_CODE snd_io_control(struct snd_device *dev, UINT32 cmd, UINT32 param);
RET_CODE snd_request_pcm_buff(struct snd_device *dev, UINT32 size);
RET_CODE snd_s3601_request_pcm_sync_buff(struct snd_device *dev, UINT32 size);
void snd_s3601_send_pcm_to_buff(struct snd_device *dev, struct pcm_output *pcm, UINT32 *frame_header);
RET_CODE snd_data_enough(struct snd_device *dev);
RET_CODE snd_config(struct snd_device *dev, UINT32 sample_rate, UINT16 sample_num, UINT8 precision);
RET_CODE snd_set_spdif_type(struct snd_device *dev, enum ASndOutSpdifType type);
void snd_write_pcm_data(struct snd_device *dev, struct pcm_output *pcm, UINT32 *frame_header);
void snd_write_pcm_data2(struct snd_device *dev, UINT32 *frame_header, UINT32 *left, UINT32 *right, UINT32 number, UINT32 ch_num);
void snd_start(struct snd_device *dev);
void snd_stop(struct snd_device *dev);
RET_CODE snd_pause(struct snd_device *dev);
RET_CODE snd_resume(struct snd_device *dev);
UINT32 snd_get_play_time(struct snd_device *dev);
void patch_hdmi_set_aksv(void);
void patch_write_bksv2hdmi_ex(UINT8 *data);


RET_CODE get_stc(UINT32 *stc_msb32, UINT8 stc_num);
void set_stc(UINT32 stc_msb32, UINT8 stc_num);
void get_stc_divisor(UINT16 *stc_divisor, UINT8 stc_num);
void set_stc_divisor(UINT16 stc_divisor, UINT8 stc_num);
void stc_invalid(void);
void stc_valid(void);
RET_CODE snd_request_desc_pcm_buff(struct snd_device *dev, UINT32 size);
void snd_write_desc_pcm_data(struct snd_device *dev, struct pcm_output *pcm, UINT32 *frame_header);


void snd_gen_tone_voice(struct snd_device *dev, struct pcm_output *pcm, UINT8 init); //tone voice
void snd_stop_tone_voice(struct snd_device *dev); //tone voice


void stc_pause(UINT8 pause, UINT8 stc_num);
RET_CODE snd_set_sub_blk(struct snd_device *dev, UINT8 sub_blk, UINT8 enable);
RET_CODE snd_set_duplicate(struct snd_device *dev, enum SndDupChannel channel);

//eq function
RET_CODE snd_enable_eq(struct snd_device *dev, UINT8 enable, enum EQ_TYPE type);
void snd_m36_attach(struct snd_feature_config *config);
void snd_m36_init_tone_voice(struct snd_device *dev);
void snd_init_spectrum(struct snd_device *dev);
void snd_register_cb_routine(void);

void snd_output_config(struct snd_device *dev, struct snd_output_cfg *cfg_param);
RET_CODE snd_set_dbg_level(struct snd_device *dev,UINT32 option);




#endif



