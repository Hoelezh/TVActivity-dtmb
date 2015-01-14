#ifndef __ADF_DECA_H
#define __ADF_DECA_H


#define DECA_CMD_BASE                   0x00
#define DECA_SET_STR_TYPE               (DECA_CMD_BASE + 1)
#define DECA_GET_STR_TYPE               (DECA_CMD_BASE + 2)
#define DECA_SET_DOLBY_ONOFF            (DECA_CMD_BASE + 3)
#define DECA_AUDIO_KEY                  (DECA_CMD_BASE + 4) //Don't support anymore, pls use DECA_STR_PLAY
#define DECA_BEEP_START                 (DECA_CMD_BASE + 5) //Don't support anymore, pls use DECA_STR_PLAY
#define DECA_BEEP_STOP                  (DECA_CMD_BASE + 6) //Don't support anymore, pls use DECA_STR_STOP
#define DECA_BEEP_INTERVAL              (DECA_CMD_BASE + 7)
#define DECA_SET_PLAY_SPEED             (DECA_CMD_BASE + 8)
#define DECA_HDD_PLAYBACK               (DECA_CMD_BASE + 9)
#define DECA_STR_PLAY                   (DECA_CMD_BASE + 10) //Play a slice of audio bitstream in SDRAM
#define DECA_SET_MULTI_CH               (DECA_CMD_BASE + 11) //strongly recommend call this command in channel change task.
#define DECA_STR_PAUSE                  (DECA_CMD_BASE + 12)
#define DECA_STR_RESUME                 (DECA_CMD_BASE + 13)
#define DECA_STR_STOP                   (DECA_CMD_BASE + 14)
#define DECA_GET_AUDIO_INFO             (DECA_CMD_BASE + 15)
#define DECA_GET_HIGHEST_PTS            (DECA_CMD_BASE + 16)

#define DECA_MP3DEC_INIT                (DECA_CMD_BASE + 17) //Don't support anymore, pls use DECA_SOFTDEC_INIT
#define DECA_MP3DEC_CLOSE               (DECA_CMD_BASE + 18) //Don't support anymore, pls use DECA_SOFTDEC_CLOSE
#define DECA_MP3_CAN_DECODE             (DECA_CMD_BASE + 19) //Don't support anymore.
#define DECA_MP3_GET_ELAPSE_TIME        (DECA_CMD_BASE + 20) //Don't support anymore.
#define DECA_MP3_JUMP_TIME              (DECA_CMD_BASE + 21) //Don't support anymore, pls use DECA_SOFTDEC_JUMP_TIME
#define DECA_MP3_SET_TIME               (DECA_CMD_BASE + 22) //Don't support anymore, pls use DECA_SOFTDEC_SET_TIME
#define DECA_MP3_IS_PLAY_END            (DECA_CMD_BASE + 23) //Don't support anymore, pls use DECA_SOFTDEC_IS_PLAY_END
#define DECA_PCM_FRM_LATE               (DECA_CMD_BASE + 24)
#define DECA_SET_AV_SYNC_LEVEL          (DECA_CMD_BASE + 25)
#define DECA_SOFTDEC_REGISTER_CB        (DECA_CMD_BASE + 26)
#define DECA_SOFTDEC_INIT               (DECA_CMD_BASE + 27)
#define DECA_SOFTDEC_CLOSE              (DECA_CMD_BASE + 28)
#define DECA_SOFTDEC_JUMP_TIME          (DECA_CMD_BASE + 29)
#define DECA_SOFTDEC_SET_TIME           (DECA_CMD_BASE + 30)
#define DECA_SOFTDEC_IS_PLAY_END        (DECA_CMD_BASE + 31)
#define DECA_SOFTDEC_INIT2              (DECA_CMD_BASE + 32)
#define DECA_SOFTDEC_CLOSE2             (DECA_CMD_BASE + 33)
#define DECA_SOFTDEC_CAN_DECODE2        (DECA_CMD_BASE + 34)
#define DECA_SOFTDEC_GET_ELAPSE_TIME2   (DECA_CMD_BASE + 35)
#define DECA_SOFTDEC_GET_MUSIC_INFO2    (DECA_CMD_BASE + 36)
#define DECA_SOFTDEC_JUMP_TIME2         (DECA_CMD_BASE + 37)
#define DECA_SOFTDEC_IS_PLAY_END2       (DECA_CMD_BASE + 38)
#define DECA_SOFTDEC_REGISTER_CB2       (DECA_CMD_BASE + 39)
#define DECA_PLAY_MEDIA_STR             (DECA_CMD_BASE + 40)
#define DECA_EMPTY_BS_SET               (DECA_CMD_BASE + 41)
#define DECA_ADD_BS_SET                 (DECA_CMD_BASE + 42)
#define DECA_DEL_BS_SET                 (DECA_CMD_BASE + 43)
#define DECA_IS_BS_MEMBER               (DECA_CMD_BASE + 44)
#define DECA_AUDIO_PTS_SYNC_STC         (DECA_CMD_BASE + 45)
#define DECA_REG_PCM_PROCESS_FUNC       (DECA_CMD_BASE + 46)
#define DECA_SYNC_BY_SOFT               (DECA_CMD_BASE + 47)
#define DECA_DOLBYPLUS_CONVERT_ONOFF    (DECA_CMD_BASE + 48)
#define DECA_DOLBYPLUS_CONVERT_STATUS   (DECA_CMD_BASE + 49)
#define DECA_RESET_BS_BUFF              (DECA_CMD_BASE + 50)
#define DECA_REG_PCM_BS_PROCESS_FUNC    (DECA_CMD_BASE + 51)
#define DECA_GET_AUDIO_DECORE           (DECA_CMD_BASE + 52)
#define DECA_DOLBYPLUS_DEMO_ONOFF       (DECA_CMD_BASE + 53)
#define DECA_SET_BUF_MODE               (DECA_CMD_BASE + 54)//for M3105 only
#define DECA_GET_BS_FRAME_LEN           (DECA_CMD_BASE + 55)
#define DECA_INDEPENDENT_DESC_ENABLE    (DECA_CMD_BASE + 56)
#define DECA_GET_DESC_STATUS            (DECA_CMD_BASE + 57)
#define DECA_GET_DECODER_HANDLE         (DECA_CMD_BASE + 58)
#define DECA_SYNC_NEXT_HEADER           (DECA_CMD_BASE + 59)
#define DECA_DO_DDP_CERTIFICATION       (DECA_CMD_BASE + 60)
#define DECA_DYNAMIC_SND_DELAY          (DECA_CMD_BASE + 61)
#define DECA_GET_DDP_INMOD              (DECA_CMD_BASE + 62)
#define DECA_GET_DECA_STATE             (DECA_CMD_BASE + 63)
#define DECA_GET_DDP_PARAM              (DECA_CMD_BASE + 64)
#define DECA_SET_DDP_PARAM              (DECA_CMD_BASE + 65)
#define DECA_CONFIG_BS_BUFFER           (DECA_CMD_BASE + 66)
#define DECA_CONFIG_BS_LENGTH           (DECA_CMD_BASE + 67)
#define DECA_BS_BUFFER_RESUME           (DECA_CMD_BASE + 68)
#define DECA_PTS_DELAY                  (DECA_CMD_BASE + 69) //param [0, 200)
#define DECA_DOLBY_SET_VOLUME_DB        (DECA_CMD_BASE + 70)

#define DECA_GET_PLAY_PARAM             (DECA_CMD_BASE + 71)
#define DECA_MPEG_M8DB_ENABLE           (DECA_CMD_BASE + 72)
#define DECA_PCM_SIGNED_SET             (DECA_CMD_BASE + 73)
#define DECA_GET_ES_BUFF_STATE          (DECA_CMD_BASE + 74)
#define DECA_SET_CACHE_INVALID_FLAG     (DECA_CMD_BASE + 75)
#define DECA_SET_QUICK_PLAY_MODE        (DECA_CMD_BASE + 76)

#define DECA_EABLE_INIT_TONE_VOICE      (DECA_CMD_BASE + 77) // 3281 ADD
#define DECA_EABLE_DVR_ENABLE           (DECA_CMD_BASE + 78) // 3281 ADD

#define DECA_GET_HDD_PLAYBACK           (DECA_CMD_BASE + 79) // for snd driver
#define DECA_PCM_HEAD_INFO_INIT         (DECA_CMD_BASE + 80) // for the init of pcm audio in ts/ps file or stream, only for BlueRay PCM format 
#define SND_GET_DECA_CTRL_BLOCK         (DECA_CMD_BASE + 81) // for the init of pcm audio in ts/ps file or stream, only for BlueRay PCM format 

#define DECA_GET_TS_MP3_INIT            (DECA_CMD_BASE + 82)
#define DECA_IO_REG_CALLBACK            (DECA_CMD_BASE + 83) // for 3281 av eventlisten
#define DECA_CREATE_GET_CPU_DATA_TASK   (DECA_CMD_BASE + 84)
#define DECA_START_GET_CPU_DATA_TASK    (DECA_CMD_BASE + 85)
#define DECA_STOP_GET_CPU_DATA_TASK     (DECA_CMD_BASE + 86)

#define DECA_SET_BYPASS_INFO            (DECA_CMD_BASE + 87)
#define DECA_PCM_DUMP_ON                (DECA_CMD_BASE + 88)
#define DECA_PCM_DUMP_OFF               (DECA_CMD_BASE + 89)
#define DECA_CHK_AUD_ENGINE_STATUS      (DECA_CMD_BASE + 90) // add by jacket for s3921
#define DECA_INIT_AUD_ENGINE            (DECA_CMD_BASE + 91) // add by jacket for s3921
#define DECA_START_AUD_ENGINE           (DECA_CMD_BASE + 92) // add by jacket for s3921
#define DECA_DTS_FALL_BACK              (DECA_CMD_BASE + 93)

#define DECA_ADV_IO                     (DECA_CMD_BASE + 0x200)
#define DECA_SET_REVERB                 (DECA_ADV_IO + 1)
#define DECA_SET_PL_II                  (DECA_ADV_IO + 2)
#define DECA_SET_AC3_MODE               (DECA_ADV_IO + 3)
#define DECA_SET_AC3_STR_MODE           (DECA_ADV_IO + 4)
#define DECA_GET_AC3_BSMOD              (DECA_ADV_IO + 5)
#define SET_PASS_CI                     (DECA_ADV_IO + 6)
#define DECA_CHECK_DECODER_COUNT        (DECA_ADV_IO + 7)
#define DECA_SET_DECODER_COUNT          (DECA_ADV_IO + 8)
#define DECA_SET_AC3_COMP_MODE          (DECA_ADV_IO + 9)
#define DECA_SET_AC3_STEREO_MODE        (DECA_ADV_IO + 10)
#define DECA_SET_AVSYNC_MODE            (DECA_ADV_IO + 11)
#define DECA_GET_FREE_BSBUF_SIZE        (DECA_ADV_IO + 12)
#define DECA_GET_BSBUF_SIZE             (DECA_ADV_IO + 13)
#define DECA_SET_AVSYNC_TEST            (DECA_ADV_IO + 14)
#define DECA_SET_PTS_SHIFT              (DECA_ADV_IO + 15)
#define DECA_IO_GET_INPUT_CALLBACK_ROUTINE (DECA_ADV_IO + 100)

#define DECA_DECORE_IO                  (DECA_CMD_BASE + 0x300)
#define DECA_DECORE_INIT                (DECA_DECORE_IO + 1)
#define DECA_DECORE_RLS                 (DECA_DECORE_IO + 2)
#define DECA_DECORE_SET_BASE_TIME       (DECA_DECORE_IO + 3)
#define DECA_DECORE_GET_PCM_TRD         (DECA_DECORE_IO + 4)
#define DECA_DECORE_PAUSE_DECODE        (DECA_DECORE_IO + 5)
#define DECA_DECORE_FLUSH               (DECA_DECORE_IO + 6)
#define DECA_DECORE_SET_QUICK_MODE      (DECA_DECORE_IO + 7)
#define DECA_DECORE_SET_SYNC_MODE       (DECA_DECORE_IO + 8)
#define DECA_DECORE_GET_CUR_TIME        (DECA_DECORE_IO + 9)
#define DECA_DECORE_GET_STATUS          (DECA_DECORE_IO + 10)



typedef void (*DecaCBFunc)(UINT32 uParam1, UINT32 uParam2);


// Audio decoder stop mode
enum ADecStopMode
{
    ADEC_STOP_IMM = 1,  // Audio decoder stop immediately
    ADEC_STOP_PTS,      // Audio decoder stop according to PTS
    ADEC_STOP_END       // No more data will be sent from parser to decoder,
                        // and decoder will stop automatically after handle
                        // all data
};



enum ADecSyncMode
{
    ADEC_SYNC_FREERUN = 1,  // Audio decoder just decode and send decoded frame to OUTPUT, not caring APTS and STC		
    ADEC_SYNC_PTS           // Audio decoder free run, but it will modify STC frequency according to the 
                            // difference between STC value and APTS at output. 
                            // And decoder need to compare APTS of 1st audio frame and STC to decide 
                            // when to decode and send it to output.
};



enum DecaCBType
{
    DECA_CB_MONITOR_NEW_FRAME = 0,
    DECA_CB_MONITOR_START,
    DECA_CB_MONITOR_STOP,
    DECA_CB_MONITOR_DECODE_ERR,
    DECA_CB_MONITOR_OTHER_ERR,
};



struct deca_callback
{
    DecaCBFunc pcb_output_new_frame;
    DecaCBFunc pcb_deca_start;
    DecaCBFunc pcb_deca_stop;
    DecaCBFunc pcb_deca_decode_err;
    DecaCBFunc pcb_deca_other_err;
};



struct deca_io_reg_callback_para
{
    enum DecaCBType eCBType;
    DecaCBFunc pCB;
    UINT32 monitor_rate;
};



struct deca_av_eventlisten
{
    UINT32 command;
    UINT32 param1;
    UINT32 reserved;
};



#define DATA_LEN_FOR_EXAMINATION        4096 //We need 4096 bytes' mp3 data to examine whether a mp3 file can be decoded.



struct deca_feature_config
{
    UINT8 detect_sprt_change;  /* =1: if sample rate changed, audio decoder can detected it and re-config sound HW. */
    UINT8 bs_buff_size  :3;    // power of bs buffer size = (1024 * 8) * (2^n)
    UINT8 support_desc  :1;
    UINT8 reserved      :4;
    UINT16 reserved16;
};



typedef struct tag_BlueRayPcmHeadInit
{
    UINT32 ulPcmFrameLen;   //the pcm frame length parse from pes pack.it used by audio decoder
    UINT32 ulPcmHead;       //the pcm head,and simulate it act as the sync word
} st_BlueRayPcmHeadInit, *pst_BlueRayPcmHeadInit;



#define DECA_AC3COMMODE_LINE    2
#define DECA_AC3COMMODE_RF      3

#define DECA_AC3_AUTO_MODE      0
#define DECA_AC3_LR_MODE        1
#define DECA_AC3_LORO_MODE      2

#define DEFAULT_BEEP_INTERVAL   (120*11)
#define MAX_ASE_RES_ID          5
#define ASE_ID_0                0x06f90100
#define ASE_ID_1                0x06f90200
#define ASE_ID_2                0x06f90300
#define ASE_ID_3                0x06f90400
#define ASE_ID_4                0x06f90500


struct ase_res_param
{
    UINT8 *src; /* stream start address */
    UINT32 len; /* stream data length */
};



/* 
   A struct define specially for DECA_STR_PLAY, up layer must transfer
   the address of this struct to audio decoder through io control
*/
struct ase_str_play_param
{
    UINT8 * src;
    UINT32 len;
    UINT32 loop_cnt;      /* play the stream (loop_cnt+1) time(s) */
    UINT32 loop_interval; /* play the stream repeatedly with the
                             interval (loop_interval)ms */
    UINT32 async_play: 1; /* =1, call stream play and return immediately */
    UINT32 reserved: 31;
    UINT32 need_notify;   /* 1: stream play finished, audio decoder
                             will call the call_back_function to notify up layer. */
    void (*registered_cb) (void);
};



struct cur_stream_info
{
    UINT8 str_type;
    UINT8 bit_depth;
    UINT32 sample_rate;
    UINT32 samp_num;
    UINT32 chan_num;
    UINT32 frm_cnt;
    UINT32 reserved1;
    UINT32 reserved2;
    UINT32 input_ts_cnt;
    UINT32 sync_error_cnt;
    UINT32 sync_success_cnt;
    UINT32 sync_frm_len;
    UINT32 decode_error_cnt;
    UINT32 decode_success_cnt;
    UINT32 cur_frm_pts;
};



struct deca_buf_info
{
    UINT32 buf_base_addr;
    UINT32 buf_len;
    UINT32 used_len;
    UINT32 remain_len;
    UINT32 cb_rd;
    UINT32 cb_wt;
    UINT32 es_rd;
    UINT32 es_wt;     
};



//for M3105
enum ADecBufMode
{
    ADEC_LIVE_MODE = 0,
    ADEC_PS_MODE
};



enum AudioTypeInternal
{
    AUDIO_MPEG_AAC_2 = 0x2000,
    AUDIO_AC3_2,
    AUDIO_MPEG_ADTS_AAC_2,
    AUDIO_EC3_2,
};



enum ADecDescChannelEnable
{
    ADEC_DESC_CHANNEL_DISABLE = 0,
    ADEC_DESC_CHANNEL_ENABLE
};



// Audio decoder play speed
enum ADecPlaySpeed
{
    ADEC_SPEED_S_32X = 1,  // Audio decoding speed -32x
    ADEC_SPEED_S_16X,      // Audio decoding speed -16x
    ADEC_SPEED_S_8X,       // Audio decoding speed -8x
    ADEC_SPEED_S_4X,       // Audio decoding speed -4x
    ADEC_SPEED_S_2X,       // Audio decoding speed -2x
    ADEC_SPEED_F_1X,       // Audio decoding speed 1x
    ADEC_SPEED_F_2X,       // Audio decoding speed 2x
    ADEC_SPEED_F_4X,       // Audio decoding speed 4x
    ADEC_SPEED_F_8X,       // Audio decoding speed 8x
    ADEC_SPEED_F_16X,      // Audio decoding speed 16x
    ADEC_SPEED_F_32X       // Audio decoding speed 32x
};



enum ADecDownMixType
{
    ADEC_DOWNMIX_TABLE_DV, // DVD- Video
    ADEC_DOWNMIX_TABLE_DA  // DVD- Audio
};



enum AUDIO_MODE
{
    STEREO = 0,
    JOINT_STEREO,
    DUAL_CHANNEL,
    SINGLE_CHANNEL
};



struct ADecDownMixTable
{
    enum ADecDownMixType eType;
    union CoefTable
    {
        UINT8 dvdVideo[24];
        UINT8 dvdAudio[18];
    } coefTable;
};



struct AUDIO_INFO
{
    UINT32 bit_rate;
    UINT32 sample_freq;
    enum AUDIO_MODE mode;
    UINT8 layer;
    UINT8 id:4;
    UINT8 mpeg25:4;
    UINT16 frm_size;
};



typedef struct _SONG_INFO
{
    char title[30];         /* Title */
    char artist[30];        /* Aurthor/Artist */
    char album[30];         /* Album */
    char year[4];           /* republished time(year) */
    char comment[30];       /* comment */
    char genre;             /* type */
    char track;
    char vbr;
    unsigned long time;
    unsigned long bit_rate;             // bps
    unsigned long sample_rate;          // KHz
    unsigned long channel_mode;

    unsigned long wma_packet_size;
    unsigned long wma_total_packet;
    unsigned long wma_data_packet_offset;

    unsigned long bye1_packet_size;
    unsigned long bye1_total_packet;
    unsigned long bye1_data_packet_offset;
    unsigned long bye1_block_align;
    unsigned long format_tag;
} SongInfo;



struct reverb_param
{
    UINT16 enable;
    UINT16 reverb_mode;
};



struct pl_ii_param
{
    UINT16 enable;

    short abaldisable;
    short chanconfig;
    short dimset;
    short surfiltenable;
    short modeselect;
    short panoramaenable;
    short pcmscalefac;
    short rsinvenable;
    short cwidthset;
};



struct ddp_certification_param
{
    UINT32 stream_type_switch;
    UINT32 stream_rollback;
    UINT32 frame_double_write;
};



struct Bypass_Info
{
    // now only keeps dts_core_size variable
    UINT32 dts_core_size; //for dtshd
};



#endif

