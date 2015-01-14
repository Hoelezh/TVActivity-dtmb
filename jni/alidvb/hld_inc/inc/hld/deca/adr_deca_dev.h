/****************************************************************************
 *
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2002 Copyright (C)
 *
 *  File: deca_dev.h
 *
 *  Description: This file define the struct of audio decoder device.
 *               
 *  History:
 *      Date        Author         Version   Comment
 *      ====        ======         =======   =======
 *  1.  2004.07.15  Goliath Peng      0.1.000    Create.
 ****************************************************************************/

#ifndef _ADR_DECA_DEV_H_
#define _ADR_DECA_DEV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <alidefinition/adf_deca.h>

#include <adr_mediatypes.h>
#include <hld/adr_hld_dev.h>


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



#ifdef __cplusplus
}
#endif

#endif /* _DECA_DEV_H_ */


