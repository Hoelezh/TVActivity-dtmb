#ifndef __ADF_SND_H
#define __ADF_SND_H



typedef struct
{
    void (*spec_call_back) (INT32 *);
    UINT32 collumn_num;
} spec_param;



typedef struct
{
    UINT32 column_num;
    UINT8 *ptr_table;
} spec_step_table;



typedef struct
{
    UINT32 drop_threshold;
    UINT32 wait_threshold;
    UINT32 delay_video_sthreshold;
    UINT32 hold_threshold;
    UINT32 dma_remain_threshold;
} snd_sync_param;



/* add for CI+ protect spdif output */
struct snd_spdif_scms
{
    UINT8 copyright:1;
    UINT8 reserved:7;
    UINT8 l_bit:1;
    UINT8 category_code:7;
    UINT16 reserved16;
};



#define CODEC_I2S (0x0<<1)
#define CODEC_LEFT (0x1<<1)
#define CODEC_RIGHT (0x2<<1)

#define STC_DELAY                   0x400
#define MUTE_BY_GPIO                0
#define MUTE_BY_SCART               1

#define SND_STATE_DETACH            0
#define SND_STATE_ATTACH            1
#define SND_STATE_IDLE              2
#define SND_STATE_PLAY              4
#define SND_STATE_PAUSE             8

#define SND_SUB_STATE_BUSY          1
#define SND_SUB_STATE_NO_DATA       2
#define SND_SUB_STATE_NO_BUFF       4



/* define the device IO control code for sound */
#define  SND_IO                     0x0000000F

#define IS_SND_RUNNING              (SND_IO + 1)
#define IS_SND_MUTE                 (SND_IO + 2)
#define SND_CC_MUTE                 (SND_IO + 3)
#define SND_CC_MUTE_RESUME          (SND_IO + 4)
#define SND_SET_FADE_SPEED          (SND_IO + 5)
#define IS_PCM_EMPTY                (SND_IO + 6)
#define SND_PAUSE_MUTE              (SND_IO + 7)
#define SND_SPO_ONOFF               (SND_IO + 8)
#define SND_REQ_REM_DATA            (SND_IO + 9)
#define SND_SPECTRUM_START          (SND_IO + 10)
#define SND_SPECTRUM_STOP           (SND_IO + 11)
#define SND_SPECTRUM_CLEAR          (SND_IO + 12)
#define SND_BYPASS_VCR              (SND_IO + 13)
#define FORCE_SPDIF_TYPE            (SND_IO + 14) //strongly recommend call this command in channel change task.
#define SND_DAC_MUTE                (SND_IO + 15)
#define SND_CHK_SPDIF_TYPE          (SND_IO + 16)
#define SND_CHK_DAC_PREC            (SND_IO + 17)
#define SND_CHK_PCM_BUF_DEPTH       (SND_IO + 18)
#define SND_POST_PROCESS_0          (SND_IO + 19)
#define SND_SPECIAL_MUTE_REG        (SND_IO + 20)
#define STEREO_FUN_ON               (SND_IO + 21)
#define SND_REQ_REM_PCM_DATA        (SND_IO + 22)
#define SND_SPECTRUM_STEP_TABLE     (SND_IO + 23)
#define SND_SPECTRUM_VOL_INDEPEND   (SND_IO + 24)
#define SND_SPECTRUM_CAL_COUNTER    (SND_IO + 25)
#define SND_SET_SYNC_DELAY          (SND_IO + 26)
#define SND_REQ_REM_PCM_DURA        (SND_IO + 27)
#define SND_SET_SYNC_LEVEL          (SND_IO + 28)
#define SND_GET_SPDIF_TYPE          (SND_IO + 29) // enum ASndOutSpdifType
#define SND_SET_BS_OUTPUT_SRC       (SND_IO + 30)
#define SND_SET_MUTE_TH             (SND_IO + 31)
#define SND_GET_MUTE_TH             (SND_IO + 32)
#define SND_SET_SPDIF_SCMS          (SND_IO + 33) // struct snd_spdif_scms
#define SND_GET_SAMPLES_REMAIN      (SND_IO + 34)
#define SND_SECOND_DECA_ENABLE      (SND_IO + 35)
#define SND_SET_DESC_VOLUME_OFFSET  (SND_IO + 36)
#define SND_GET_TONE_STATUS         (SND_IO + 37)
#define SND_DO_DDP_CERTIFICATION    (SND_IO + 38)
#define SND_AUTO_RESUME             (SND_IO + 39)
#define SND_SET_SYNC_PARAM          (SND_IO + 40) // snd_sync_param
#define SND_RESET_DMA_BUF           (SND_IO + 41) // TRUE or FALSE. TRUE -- reset sound dma buffer to drop some frames
#define SND_I2S_OUT                 (SND_IO + 42)
#define SND_HDMI_OUT                (SND_IO + 43)
#define SND_SPDIF_OUT               (SND_IO + 44)


/* Add by Joy for implementing an independent A/V sync module.module
 * Date: 2011.10.10.
 */
#define SND_SET_FRAME_SHOW_PTS_CALLBACK (SND_IO + 45)
#define SND_MPEG_M8DB_ENABLE        (SND_IO + 46)   
#define SND_GET_SYNC_PARAM          (SND_IO + 47) 
#define SND_ENABLE_DROP_FRAME       (SND_IO + 48)   
#define SND_REG_GET_SYNC_FLAG_CB    (SND_IO + 49)   
#define SND_SET_HW_HOLD_THRESHOLD   (SND_IO + 50)   
#define SND_GET_RESET_PARAM         (SND_IO + 51)
#define SND_SET_RESET_PARAM         (SND_IO + 52)
#define SND_GET_STATUS              (SND_IO + 53)
#define SND_GET_RAW_PTS             (SND_IO + 54)
#define SND_DMX_SET_VIDEO_TYPE      (SND_IO + 55) // add just for av sync use
#define SND_IO_PAUSE_SND            (SND_IO + 56)
#define SND_IO_RESUME_SND           (SND_IO + 57)

#define SND_HDMI_ENABLE             (SND_IO + 58) // Frank.T switch for  hdmi audio cap reset in snd driver 
#define SND_RESTART                 (SND_IO + 59) // snd_restart
#define SND_STOP_IMMD               (SND_IO + 60) // snd immd stop
#define SND_DO_DDP_CERTIFICATION_EX (SND_IO + 61)
#define SND_BUF_DATA_REMAIN_LEN     (SND_IO + 62)

#define SND_ADV_IO                  (SND_IO + 0x200) //snd advanced io command
#define SND_BASS_TYPE               (SND_ADV_IO + 1)
#define SND_REG_HDMI_CB             (SND_ADV_IO + 2)
#define SND_PCM_DUMP_ON             (SND_ADV_IO + 3)
#define SND_PCM_DUMP_OFF            (SND_ADV_IO + 4)

/*****************************************************/

// SPDIF raw data coding type
#define SPDO_SRC_FLR                0x00
#define SPDO_SRC_SLR                0x01
#define SPDO_SRC_CSW                0x02
#define SPDO_SRC_DMLR               0x03
#define SPDO_SRC_EXLR               0x04
#define SPDO_SRC_BUF                0x07
#define SPDO_SRC_LFEC               0x01


//bass_type
#define BASS_DISABLE                0x00
#define BASS_CON0                   0x01
#define BASS_CON1                   0x02
#define BASS_CON2_NSUB              0x03
#define BASS_CON2_WSUB              0x04
#define BASS_ALT_CON2               0x05
#define BASS_CON3_NSUB              0x06
#define BASS_CON3_WSUB              0x07
#define BASS_SIMP_NSUB              0x08
#define BASS_SIMP_WSUB              0x09



enum SndToneStatus
{
    SND_STREAM_STATUS = 0, // None.
    SND_TONE_STATUS,       // Left channel.
};



enum SndChannel
{
    SND_CH_NONE = 0,    // None.
    SND_CH_L,           // Left channel.
    SND_CH_R,           // Right channel.
    SND_CH_LS,          // Left surround channel.
    SND_CH_RS,          // Right surround channel.
    SND_CH_C,           // Center channel.
    SND_CH_LFE,         // Low frequency effect channel.
    SND_CH_DML,         // downmix L channel.
    SND_CH_DMR          // downmix R channel.
};



enum SndDownMixChannel
{
    SND_DOWNMIXCHANNEL_DM,
    SND_DOWNMIXCHANNEL_LR
};



enum SndDownMixMode
{
    SND_DOWNMIXMODE_51 = 1,
    SND_DOWNMIXMODE_LORO,
    SND_DOWNMIXMODE_LTRT,
    SND_DOWNMIXMODE_VIR
};



enum SndDescOutputChannel
{
    SND_FORWARD_CH = 1,
    SND_SURROUND_CH,
    SND_LFE_C_CH,
    SND_DOWNMIX_CH
};



enum SndEqualizer
{
    SND_EQ_NONE = 0,        // Disable equalizer mode.
    SND_EQ_CLASSIC,         // Classsic mode.
    SND_EQ_ROCK,            // Rock mode.
    SND_EQ_JAZZ,            // Jazz mode.
    SND_EQ_POP,             // Pop mode
    SND_EQ_BASS,            // Bass mode.
    SND_EQ_USER             // User define mode.
};



enum SndReverb
{
    SND_REVERB_OFF = 0,
    SND_REVERB_CHURCH,
    SND_REVERB_CINEMA,
    SND_REVERB_CONCERT,
    SND_REVERB_HALL,
    SND_REVERB_LIVE,
    SND_REVERB_ROOM,
    SND_REVERB_STADIUM,
    SND_REVERB_STANDARD
};



enum SndSpeakerSize
{
    SND_SPEAKER_SIZE_OFF= 0,
    SND_SPEAKER_SIZE_ON,
    SND_SPEAKER_SIZE_SMALL,
    SND_SPEAKER_SIZE_BIG
};



enum SndDRC
{
    SND_DRC_OFF = 0,
    SND_DRC_CUSTOM_A,
    SND_DRC_CUSTOM_D,
    SND_DRC_LINE_OUT,
    SND_DRC_RF_REMOD
};



enum ASndOutMode
{
    SND_OUT_GEN = 0,
    SND_OUT_DIG,
    SND_OUT_DIGGEN
};



enum SndSubBlock
{
    SND_SUB_PP = 0x01,          // Audio post-process.
    SND_SUB_IN = 0x02,          // General audio input interface.
    SND_SUB_OUT = 0x04,         // General audio output interface.
    SND_SUB_MIC0 = 0x08,        // Micro phone 0 input interface.
    SND_SUB_MIC1 = 0x10,        // Micro phone 1 input interface.
    SND_SUB_SPDIFIN = 0x20,     // SPDIF input interface.
    SND_SUB_SPDIFOUT = 0x40,    // SPDIF output interface.
    SND_SUB_SPDIFOUT_DDP = 0x80,
    SND_SUB_ALL = 0xff          // All IO enabled.
};



enum SndDupChannel
{
    SND_DUP_NONE,
    SND_DUP_L,
    SND_DUP_R,
    SND_DUP_MONO
};



enum ASndOutSpdifType
{
    SND_OUT_SPDIF_INVALID = -1, 
    SND_OUT_SPDIF_PCM = 0,
    SND_OUT_SPDIF_BS = 1,
    SND_OUT_SPDIF_FORCE_DD = 2
};



// add for HDMI bs output src select 
enum SndSpoOutputSrcType
{
    SND_OUT_SRC_DDPSPO = 0,
    SND_OUT_SRC_SPO = 1
};



enum EQ_TYPE
{
    EQ_SLIGHT     = 0,
    EQ_CLASSIC    = 1,
    EQ_ELECTRONIC = 2,
    EQ_DANCE      = 3,
    EQ_LIVE       = 4,
    EQ_POP        = 5,
    EQ_ROCK       = 6
};



struct snd_output_cfg
{
    UINT8 mute_num;                     // mute circuit gpio number.
    UINT8 mute_polar;                   // the polarity which will cause circuit mute 
    UINT8 dac_precision;                // 24bit or 16bit 
    UINT8 dac_format;                   // CODEC_I2S (0x0<<1), CODEC_LEFT (0x1<<1), CODEC_RIGHT (0x2<<1)
    UINT8 is_ext_dac;                   // for M3329 serial, always should be 1. 0: means embedded dac.	
    UINT8 reserved8;
    UINT16 gpio_mute_circuit:1;         // FALSE: no mute circuit; TRUE: exists mute circuit controlled by GPIO
    UINT16 ext_mute_mode:2;
    UINT16 enable_hw_accelerator:1;     // FALSE: do not enable M3202 audio HW accelerator;
                                        // TRUE: Enable M3202 audio HW accelerator;
    UINT8 chip_type_config:1;           // 1: QFP; 0: BGA.
    UINT16 reserved:11;
};



struct pcm_output
{
    UINT32 ch_num;
    UINT32 ch_mod;
    UINT32 samp_num;
    UINT32 sample_rata_id;
    UINT32 inmode;
    UINT32 *ch_left;
    UINT32 *ch_right;
    UINT32 *ch_sl;
    UINT32 *ch_sr;
    UINT32 *ch_c;
    UINT32 *ch_lfe;
    UINT32 *ch_dl;
    UINT32 *ch_dr;
    UINT32 *ch_left_m8db; // Added for mpeg pcm data -31db for spdif output in bs out mode
    UINT32 *ch_right_m8db;
    UINT32 *ch_sl_m8db;
    UINT32 *ch_sr_m8db;
    UINT32 *ch_c_m8db;
    UINT32 *ch_lfe_m8db;
    UINT32 *ch_dl_m8db;
    UINT32 *ch_dr_m8db;
    UINT8  *raw_data_start;
    UINT32 raw_data_len;
    UINT32 iec_pc;

    UINT8  *raw_data_ddp_start; //KwunLeung
    UINT32 raw_data_ddp_len;
    UINT8  iec_pc_ddp;
};



struct snd_feature_config
{
    struct snd_output_cfg output_config;
    UINT8 support_spdif_mute;
    UINT8 swap_lr_channel;
    UINT8 conti_clk_while_ch_chg;
    UINT8 support_desc;
};



struct snd_dev_status
{
    UINT8 flags;
    UINT32 volume;
    UINT32 in_mute;
    UINT8 spdif_out;
    UINT8 trackmode;
    
    UINT32 samp_rate;
    UINT32 samp_num;
    UINT32 ch_num;

    
    UINT32 drop_cnt;
    UINT32 play_cnt;
    UINT32 pcm_out_frames;
    
    UINT32 pcm_dma_base;
    UINT32 pcm_dma_len;
    UINT32 pcm_rd;
    UINT32 pcm_wt;
    UINT32 underrun_cnts;
    
    UINT32 pcm_dump_addr;
    UINT32 pcm_dump_len;

    UINT8 spdif_mode;
    UINT32 spdif_user_bit;
};



#endif


