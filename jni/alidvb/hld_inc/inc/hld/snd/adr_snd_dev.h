/****************************************************************************
 *
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2002 Copyright (C)
 *
 *  File: snd_dev.h
 *
 *  Description: This file define the struct of sound device.
 *  History:
 *      Date        Author         Version   Comment
 *      ====        ======         =======   =======
 *  1.  2004.07.15  Goliath Peng      0.1.000    Create.
 ****************************************************************************/
#ifndef __ADR_SND_DEV_H_
#define __ADR_SND_DEV_H_


#ifdef __cplusplus
extern "C" {
#endif


#include <hld/adr_hld_dev.h>

#include <alidefinition/adf_snd.h>


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



#ifdef __cplusplus
    }
#endif


#endif /* _SND_DEV_H_ */



