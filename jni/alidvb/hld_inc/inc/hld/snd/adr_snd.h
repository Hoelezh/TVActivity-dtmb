#ifndef __ADR_SND_H_
#define __ADR_SND_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <hld/snd/adr_snd_dev.h>
 

#define SND_SUPPORT_AD      0x01
#define SND_SUPPORT_DDPLUS  0x02


struct snd_callback
{
    void (*phdmi_snd_cb)(UINT32);
    void (*spec_call_back)(INT32 *);
};


struct snd_hld_private
{
    UINT8 volume;
    UINT16 stc_divisor;
    enum ASndOutSpdifType spdif_type;

#ifdef ADR_IPC_ENABLE
    int opened;
    int inited;

    int shmid;
#endif
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

void snd_m36_attach(struct snd_feature_config *config);
void snd_m36_dettach(struct snd_device *dev);
RET_CODE snd_set_duplicate(struct snd_device *dev, enum SndDupChannel channel);



/** Remove all debug output lines
 */
#define DBG_SND_NO_OUTPUT  0
#define DBG_SND_API                     0x00000001 
#define DBG_SND_ERROR                   0x00000002
#define DBG_SND_BUF     0x00000004
#define DBG_SND_AVSYNC  0x00000008
#define DBG_LEV_ALL   0xFFFFFFFF



/** \def DEBUG_LEVEL is the current level do debug output on standard err */
extern UINT32 g_snd_dbg_option;

#define DBG_SND_PRINTF(option, fmt,args...) \
{                                           \
    if (option & g_snd_dbg_option )         \
        ibc_printf(fmt,args);               \
}



#ifdef __cplusplus
}
#endif


#endif /*_SND_H_*/



