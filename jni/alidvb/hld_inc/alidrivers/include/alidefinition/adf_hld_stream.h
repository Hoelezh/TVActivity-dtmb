/*****************************************************************************
    History:
    2004-10-29 Hudson   First Created
*****************************************************************************/

#ifndef __ADF_HLD_STREAM_H
#define __ADF_HLD_STREAM_H


//#include "common.h"

#if 0   // use libyamad.a
struct stream
{
    uint8 *buffer;
    int nbyte_buffer;
    uint8 *next_frame;
    int nbyte_left;
};

void yamad_init_stream(struct stream *stream);
void yamad_stream_in(struct stream *stream, uint8 *buf, int nbyte);
void yamad_stream_out(struct stream *stream, int nbyte);
int yamad_sync_stream(struct stream *stream);


INLINE
int yamad_stream_query(struct stream *stream)
{
    return stream->nbyte_left;
}

#else   // use mpgdec.a ,  ac3dec.a

#define DATA_PRECISION  24  //16
#if(DATA_PRECISION == 24)
    #define SDATA long
#else
    #define SDATA short
#endif


/*------------------------------------------------*/
/*                MPEG2 decoder                   */
/*------------------------------------------------*/

typedef struct
{
    BYTE   *input_rPtr;
    WORD   bs_length;
    SDATA  *output_wPtr;
    //  BYTE   *output_raw;
    BYTE   *extbs_rPtr;
    WORD   extbs_length;
    BYTE   ismpeg1;
} DECINSIP_MPG;


typedef struct
{
    BYTE status;
    BYTE bit_depth;
    WORD sample_rate;
    WORD samp_num;
    WORD left_data;
    WORD left_extdata;
    WORD chan_num;
    WORD samprateid;
    WORD inmod;
} DECOUTSIP_MPG;


void MPGDecodeInit();
DECOUTSIP_MPG  MPGDecodeOneFrame(DECINSIP_MPG mpg_para);

void MPGDecodeInit_ad(void* mpgDecoder);
DECOUTSIP_MPG  MPGDecodeOneFrame_ad(void* mpgDecoder, DECINSIP_MPG mpg_para);

//void SetMPEG2SkipFlag(BYTE);
//void SetMPEG2Lingual(BYTE);
//BYTE GetMPEG2Lingual(void);
//WORD GetMPEG2FrameSize(void);
//WORD GetMPEG2ExtFrameSize(void);


/*------------------------------------------------*/
/*               AC3 decoder                      */
/*------------------------------------------------*/

typedef struct
{
    BYTE   *input_rPtr;
    WORD   bs_length;
    SDATA  *output_wPtr;
    //  BYTE   *output_raw;
} DECINSIP_AC3;


typedef struct
{
    BYTE status;
    BYTE bit_depth;
    WORD sample_rate;
    WORD samp_num;
    WORD left_data;
    WORD chan_num;
    WORD samprateid;
    WORD inmod;
    WORD dsurmod;
} DECOUTSIP_AC3;


void AC3DecodeInit();
DECOUTSIP_AC3 AC3DecodeOneFrame(DECINSIP_AC3 ac3_para);

//BYTE AC3GetBitstrInfo(BYTE *pInfo);
BYTE AC3GetExtBitstrInfo(BYTE *pInfo);
BYTE AC3SetPcmScale(DWORD ac3_pcmscale);
BYTE AC3SetDYNScaleLow(DWORD ac3_scalelow);
BYTE AC3SetDYNScaleHigh(DWORD ac3_scalehigh);
BYTE AC3SetCOMPMOD(BYTE ac3_compmod);
BYTE AC3SetDUALMOD(BYTE ac3_dualmod);
BYTE AC3SetKARAOKEMOD(BYTE ac3_karaokemod);
BYTE AC3SetKCAPABLEMOD(BYTE ac3_kcapablemod);
BYTE AC3SetOUTPUTMOD(BYTE ac3_outputmod);
BYTE AC3SetSTEREOMOD(BYTE ac3_stereomod);
BYTE AC3SetOUTLFE(BYTE ac3_outlfe);
//void SetAC3BitDepth(BYTE bit_depth);
//void SetAC3SkipFlag(BYTE);
//WORD GetAC3FrameSize(void);

#endif



/*------------------------------------------------*/
/*               EAC3 decoder                     */
/*------------------------------------------------*/

typedef struct
{
    BYTE   *input_rPtr;
    WORD    bs_length;
    SDATA  *output_wPtr;
    BYTE   *output_ac3_rPtr;
    BYTE    is_ac3_file;        // added for DD+, indicate if the input bitstream is AC# file. 1=AC3, 0 = EAC3(DD+)
    short   under_run;
    short   diff_dmfac;
} DECINSIP_EAC3;


typedef struct
{
    BYTE    status;
    BYTE    bit_depth;
    WORD    sample_rate;
    WORD    samp_num;
    WORD    left_data;
    WORD    chan_num;
    WORD    samplerateid;
    WORD    inmod;
    WORD    dsurmod;
    WORD    output_ac3_bytes;   // added for DD+. To indicate the size of output ac3 bitstream.
} DECOUTSIP_EAC3;


typedef struct
{
    enum AudioStreamType type;
    
    void (* deca_audio_init)    (void);
    BYTE (* set_comp_mode)      (BYTE);
    BYTE (* set_stereo_mode)    (BYTE);
    BOOL (* frame_decoder)      (void *input, void *output);
    BYTE (* set_dual_mode)      (BYTE);
    BYTE (* set_out_lfe)        (BYTE);
    BYTE (* set_output_mode)    (BYTE);
    BYTE (* set_pcm_scale)      (UINT32);
    BYTE (* set_dyn_scale_low)  (UINT32);
    BYTE (* set_dyn_scale_high) (UINT32);
#ifdef CHIP_3821_IN_USE
    BYTE (* aac_set_drc_params) (void *decoder, unsigned long aac_scalehi, unsigned long aac_scalelo, long aac_reflevel);
#endif
} deca_audiostream_decoder;


typedef struct {
    enum AudioStreamType type;
    
    void (* deca_audio_init)    (void *);
    BYTE (* set_comp_mode)      (void *decoder, BYTE);
    BYTE (* set_stereo_mode)    (void *decoder, BYTE);
    BOOL (* frame_decoder)      (void *input, void *output, void *decoder);
    BYTE (* set_dual_mode)      (void *,BYTE);
    BYTE (* set_out_lfe)        (void *,BYTE);
    BYTE (* set_output_mode)    (void *,BYTE);
    BYTE (* set_pcm_scale)      (void *,UINT32);
    BYTE (* set_dyn_scale_low)  (void *,UINT32);
    BYTE (* set_dyn_scale_high) (void *,UINT32);
#ifdef CHIP_3821_IN_USE
    BYTE (* aac_set_drc_params) (void *decoder, unsigned long aac_scalehi, unsigned long aac_scalelo, long aac_reflevel);
#endif
} deca_audiostream_decoder_ad;


#define _deca_audiostream_decoder(x) const deca_audiostream_decoder x __attribute__ ((section(".deca.init")))
#define _deca_audiostream_decoder_ad(x) const deca_audiostream_decoder_ad x __attribute__ ((section(".deca.init")))

//#if defined(_ATSC_CONVERTER_BOX_E_) || defined(_ATSC_CONVERTER_BOX_D_)
//#define _deca_audiostream_decoder(x) const deca_audiostream_decoder x __attribute__ ((section(".deca.plugin")))


/*------------------------------------------------*/
/*               AAC decoder                     */
/*------------------------------------------------*/

typedef struct
{
    BYTE   *input_rPtr;
    WORD   bs_length;
    SDATA *output_wPtr;
    //  BYTE   *output_raw;
    WORD   samplingFreqencyIndex;
    WORD   channelConfiguration;
    WORD   stream_type;
} DECINSIP_AAC;


typedef struct
{
    BYTE status;
    BYTE bit_depth;
    WORD sample_rate;
    WORD samp_num;
    WORD left_data;
    WORD chan_num;
} DECOUTSIP_AAC;


void AACDecoderInit();
//void SetAACSkipFlag(BYTE);
//WORD GetAACFrameSize(void);
DECOUTSIP_AAC  AACDecoderOneFrame(DECINSIP_AAC aac_para);


#endif /* STREAM_H */

