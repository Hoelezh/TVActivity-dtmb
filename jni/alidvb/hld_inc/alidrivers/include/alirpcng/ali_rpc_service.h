#ifndef __ALI_RPC_SERVICE_H
#define __ALI_RPC_SERVICE_H

#include "ali_rpc_type.h"
#include "ali_rpc_cfg.h"
#include "ali_rpc_osdep.h"
#include "ali_rpc_debug.h"

//#include <rpc_hld/ali_rpc_pe.h>  // ADD BY Michael chen
#if defined(__ALI_TDS__)
  #include <hld/gma/gma.h>
  #include <bus/hdmi/m36/hdmi_api.h>
#elif defined(__ALI_LINUX_KERNEL__)
  #include <rpc_hld/ali_rpc_hld_gma.h>
  #include <ali_hdmi_common.h>
#endif

typedef enum _ParamId {
	PARAM_VOID,
	PARAM_INT32,
	PARAM_UINT32,
	PARAM_LONG,
	PARAM_ULONG,
	PARAM_INT16,
	PARAM_UINT16,
	PARAM_BOOL,
	PARAM_ENUM,
	PARAM_ARRAY,
	PARAM_BYTES,
	PARAM_OPAQUE,
	PARAM_STRING,
	PARAM_UNION,
	PARAM_CHAR,
	PARAM_UCHAR,
	PARAM_VECTOR,
	PARAM_FLOAT,
	PARAM_DOUBLE,
	PARAM_REFERENCE,
	PARAM_POINTER,
	PARAM_WRAPSTRING,
	PARAM_STRARRAY,
	PARAM_RPCDBGINFO,
/*User specific data type id: START*/
	PARAM_TESTSTRUCT, /*sample struct*/
    
/************ Audio playback example ******/
    PARAM_Deca_feature_config_rpc,
    PARAM_Snd_feature_config_rpc,
    PARAM_Snd_output_cfg_rpc,
    PARAM_Hld_device_rpc,
    PARAM_Pcm_output_rpc,
    PARAM_Control_block_rpc,
    PARAM_Pe_music_cfg_rpc,
    PARAM_MusicInfo_rpc,
    PARAM_DecoderInfo_rpc,
    PARAM_Image_info_rpc,
    PARAM_Image_init_config_rpc,
    PARAM_Image_hw_info_rpc,
    PARAM_Pe_image_cfg_rpc,
    PARAM_Image_info_pe_rpc,
    PARAM_Imagedec_frm_rpc,
    PARAM_Pe_video_cfg_rpc,
    PARAM_DEC_CHAPTER_INFO_RPC,
    PARAM_Fileinfo_video_rpc,
    PARAM_Pe_cache_ex_rpc,
    PARAM_Pe_cache_cmd_rpc,
    PARAM_Rect_rpc,
    PARAM_Audio_config_rpc,
    PARAM_Snd_dev_status_rpc,
    PARAM_Spec_param_rpc,
    PARAM_Spec_step_table_rpc,
    PARAM_Snd_spdif_scms_rpc,
    PARAM_Snd_sync_param_rpc,
    PARAM_Isdbtcc_config_par_rpc,
    PARAM_Atsc_subt_config_par_rpc,
    PARAM_Sdec_feature_config_rpc,
    PARAM_Subt_config_par_rpc,
    PARAM_AUDIO_INFO_rpc,
    PARAM_Reverb_param_rpc,
    PARAM_Pl_ii_param_rpc,
    PARAM_Io_param_rpc,
    PARAM_Cur_stream_info_rpc,
    PARAM_Deca_buf_info_rpc,
    PARAM_Ase_str_play_param_rpc, //add by jacket
    PARAM_Position_rpc,
    PARAM_RectSize_rpc,
    PARAM_YCbCrColor_rpc,
    PARAM_AdvSetting_rpc,
    PARAM_VDecPIPInfo_rpc,
    PARAM_VDec_StatusInfo_rpc,
	
	PARAM_Imagedec_show_shutters_rpc,
    PARAM_Imagedec_show_brush_rpc,
    PARAM_Imagedec_show_slide_rpc,
    PARAM_Imagedec_show_show_random_rpc,
    PARAM_Imagedec_show_fade_rpc,
    PARAM_Image_slideshow_effect_rpc,
    PARAM_Image_config_rpc,
    PARAM_Image_engine_config_rpc,
    PARAM_Image_display_rpc,

    /* Video Encoder added by Vic_Zhang_on_20131005. */
    PARAM_VidencSeeConfig,
    PARAM_VidencTriggerPara,

/**************** decv *******************/
    PARAM_Vdec_adpcm_rpc,
    PARAM_Vdec_sml_frm_rpc,
    PARAM_Vdec_mem_map_rpc,
    PARAM_Vdec_config_par_rpc,
    PARAM_Vdec_avs_memmap_rpc,
    PARAM_Vdec_avc_memmap_rpc,
    PARAM_Vdec_avc_config_par_rpc,
    PARAM_Vdec_dvrconfigparam_rpc,
    PARAM_Vdecpipinfo_rpc,
    PARAM_Mpsource_callback_rpc,
    PARAM_Pipsource_callback_rpc,
    PARAM_Vdec_statusinfo_rpc, 
    PARAM_Vdec_decore_status_rpc, 
    PARAM_Vdec_io_get_frm_para_rpc,
    PARAM_Ycbcrcolor_rpc,
    PARAM_Vdec_io_reg_callback_para_rpc,
    PARAM_Vdec_picture_rpc,
    PARAM_Vdec_io_dbg_flag_info_rpc,
    PARAM_Video_rect_rpc,
    PARAM_OutputFrmManager_rpc,
    PARAM_Vdecinit_rpc,
    
/***************** Avs ********************/
    PARAM_Avsync_cfg_param_t_rpc,
    PARAM_Avsync_adv_param_t_rpc,
    PARAM_Avsync_status_t_rpc,
    PARAM_Avsync_statistics_t_rpc,
    PARAM_Avsync_smoothly_play_cfg_t_rpc,
    PARAM_Avsync_get_stc_en_t_rpc,
    
/**************** dmx *******************/
    PARAM_Io_param_ex_rpc,
    PARAM_Pes_pkt_param_rpc,
    
/**************** vbi *******************/    
    PARAM_Vbi_config_par_rpc,
    PARAM_Ttx_config_par_rpc,
    PARAM_Ttx_page_info_rpc,
    
/**************** ce *******************/
    PARAM_Ce_data_info_rpc,
    PARAM_Otp_param_rpc,
    PARAM_Data_param_rpc,
    PARAM_Des_param_rpc,
    PARAM_Ce_key_param_rpc,
    PARAM_Ce_debug_key_info_rpc,
    PARAM_Ce_pos_status_param_rpc,
    PARAM_Ce_found_free_pos_param_rpc,
    PARAM_Ce_pvr_key_param_rpc,
    
/**************** dsc ******************/    
    PARAM_DeEncrypt_config_rpc,
    PARAM_Sha_init_param_rpc,
    PARAM_Aes_init_param_rpc,
    PARAM_Des_init_param_rpc,
    PARAM_Pid_param_rpc,
    PARAM_Csa_init_param_rpc,
    PARAM_Dsc_pvr_key_param_rpc,
    PARAM_Key_param_rpc,
    PARAM_Sha_hash_rpc,
    PARAM_Trng_data_rpc,
	
/*************** dis *******************/
    PARAM_Vp_feature_config_rpc,
    PARAM_Tve_feature_config_rpc,
    PARAM_Osd_driver_config_rpc,
    PARAM_Vp_win_config_para_rpc,
    PARAM_Vpo_io_ttx_rpc,
    PARAM_Vpo_io_cc_rpc,
    PARAM_Dacindex_rpc,
    PARAM_Vp_dacinfo_rpc,
    PARAM_Vp_io_reg_dac_para_rpc,
    PARAM_Vp_initinfo_rpc,
    PARAM_Vpo_io_set_parameter_rpc,
    PARAM_Vpo_io_video_enhance_rpc,    
    PARAM_Vpo_io_get_info_rpc,
    PARAM_De2Hdmi_video_infor_rpc,
    PARAM_Vpo_io_cgms_info_rpc,
    PARAM_Vp_io_afd_para_rpc,
    PARAM_Vpo_io_get_picture_info_rpc,
    PARAM_Vpo_osd_show_time_rpc,
    PARAM_Vpo_io_cutline_pars_rpc,
    PARAM_Alifbio_3d_pars_rpc,
    PARAM_Alifbio_set_3d_enh_rpc,


    PARAM_GMA_SIZE,
    PARAM_GMA_LAYER_PARS,
    PARAM_GMA_ENH_PARS,
    PARAM_GMA_DMEM_PARS,
    PARAM_GMA_SCALE_PARS,
    PARAM_GMA_PAL_PARS,
    PARAM_GMA_RECT,
    PARAM_GMA_REGION_PARS,
    PARAM_DE2HDMI_VIDINF,
    PARAM_SND2HDMI_AUDINF,
/*User specific data type id: END*/
	PARAM_ID_MAX
}ParamId;

typedef Bool (*XdrOpFunc)();

typedef struct _XdrOpTable XdrOpTable;
struct _XdrOpTable {
	ParamId id;
	XdrOpFunc op;
};

/*Create Param usage*/
#define RPC_PARAM_CREATE(param_name, param_type, param_id, param_len, data_ptr) \
			Param param_name; \
			param_name.type = param_type; \
			param_name.paramId = param_id;\
			param_name.len = param_len; \
			param_name.pData = data_ptr;


#define RPC_PARAM_UPDATE(param_name, param_type, param_id, param_len, data_ptr) \
                        param_name.type = param_type; \
                        param_name.paramId = param_id;\
                        param_name.len = param_len; \
                        param_name.pData = data_ptr;


#endif

/************************************************************
*
*              User self define struct area
*
************************************************************/
typedef struct _TestStruct{
        Int32  ii;
        Uint32 uii;
        char   cc;
        Uchar  ucc;
        Long   ll;
        Ulong  ull;
        Bool   bb;
}TestStruct;

typedef struct deca_feature_config_rpc
{
	Uchar detect_sprt_change;/*=1: if sample rate changed, audio decoder can detected it and re-config sound HW.*/
	Uchar bs_buff_size;      // power of bs buffer size = (1024 * 8) * (2^n)
	Uchar support_desc;
	Uchar reserved;
	Uint16 reserved16;
}Deca_feature_config_rpc;

typedef struct snd_output_cfg_rpc
{
	Uchar mute_num;
	Uchar mute_polar; 
	Uchar dac_precision;
	Uchar dac_format;
	Uchar is_ext_dac;
	Uchar reserved8;
	Uint16 gpio_mute_circuit; 
	Uint16 ext_mute_mode;
	Uint16 enable_hw_accelerator; 	
									
    Uchar chip_type_config; 
    Uint16 reserved;
}Snd_output_cfg_rpc;

typedef struct snd_feature_config_rpc
{
	Uchar support_spdif_mute;
	Uchar swap_lr_channel;
	Uchar conti_clk_while_ch_chg;
    Uchar support_desc;
}Snd_feature_config_rpc;



typedef struct hld_device_rpc
{
    Uint32              HLD_DEV;
	Uint32				type;						/* Device type */
	Char				name[16];	/* Device name */
}Hld_device_rpc;


typedef struct pcm_output_rpc
{
	Uint32 ch_num ;
	Uint32 ch_mod;
	Uint32 samp_num ;
	Uint32 sample_rata_id;
    
	Uint32 inmode;
	Uint32 ch_left ;
	Uint32 ch_right ;
	Uint32 ch_sl ;
    
	Uint32 ch_sr ;
	Uint32 ch_c ;
	Uint32 ch_lfe ;
	Uint32 ch_dl ;
	Uint32 ch_dr ;

	Uint32 raw_data_start;
	Uint32 raw_data_len;
	Uint32 iec_pc;
	
	Uint32 raw_data_ddp_start;
	Uint32 raw_data_ddp_len;
	Uchar iec_pc_ddp;
}Pcm_output_rpc;


typedef struct control_block_rpc
{
    Uchar stc_id_valid;
    Uchar pts_valid;
    Uchar data_continue;
    Uchar ctrlblk_valid;
    Uchar instant_update;
    Uchar vob_start;
    
    Uchar bstream_run_back;
    Uchar reserve;
    Uchar stc_id;
    Uchar stc_offset_idx;
    Uint32 pts;
}Control_block_rpc;


typedef struct pe_music_cfg_rpc
{
    Uint32 pcm_out_buff;
    Uint32 pcm_out_buff_size;
    Uint32 processed_pcm_buff;
    Uint32 processed_pcm_buff_size;
    Uint32 mp_cb;
}Pe_music_cfg_rpc;


typedef struct musicinfo_rpc
{
	char title[30];			
	char artist[30];		
	char album[30];		
	char year[4];	
    
	char comment[30];		
	char genre;			
	char track;
	unsigned long time;
	unsigned long file_length;
}MusicInfo_rpc;


/* Video Encoder added by Vic_Zhang_on_20131005. */
typedef struct VidencSeeConfig
{
    unsigned int buffer_addr;
    unsigned int buffer_size;
    int y_sbm_idx;
    int c_sbm_idx;
    int status_idx;
    int yuv_width;
    int yuv_height;
}VidencSeeConfig_t;

typedef struct VidencTriggerPara
{
    unsigned int frm_width;
    unsigned int frm_height;
    unsigned int Y_length;
    unsigned int C_length;
    unsigned int encoder_ID;
    unsigned int job_status;
}VidencTriggerPara_t;


typedef struct _DECODER_INFO_rpc
{
	unsigned long	bit_rate;				//bps
	unsigned long	sample_rate;			//KHz
	unsigned long	channel_mode;
}DecoderInfo_rpc;



typedef struct image_info_rpc
{
	Ulong	fsize;
	Ulong	width;
	Ulong	height;
	Ulong	bbp;
       Ulong      type;
}Image_info_rpc;

typedef struct image_init_config_rpc
{
	
	// dst frame info
	Uint32 frm_y_addr;
	Uint32 frm_y_size;
	Uint32 frm_c_addr;
	Uint32 frm_c_size;
    
	Uint32 frm2_y_addr;
	Uint32 frm2_y_size;
	Uint32 frm2_c_addr;
	Uint32 frm2_c_size;
    
	Uint32 frm_mb_type;
	Uint32 frm3_y_addr;
	Uint32 frm3_y_size;
	Uint32 frm3_c_addr;
    
	Uint32 frm3_c_size;
	Uint32 frm4_y_addr;
	Uint32 frm4_y_size;
	Uint32 frm4_c_addr;
    
	Uint32 frm4_c_size;
	Uint32 decoder_buf;
	Uint32 decoder_buf_len;

       Uint32 vbv_buf;
       Uint32 vbv_buf_len;
	
	Int32 img_fmt;     //enum IMAGE_FORMAT img_fmt;

	Int32 pkt_sbm_idx;
	Int32 info_sbm_idx;
       Int32 info_end_idx;	
}Image_init_config_rpc;	


typedef struct image_hw_info_rpc
{
    Uint32  y_addr;
    Uint32  y_size;
    Uint32  c_addr;
    Uint32  c_size;

    Uint32  width;
    Uint32  height;
    Uint32  w_stride;
    Uchar   sample_format;
}Image_hw_info_rpc;


typedef struct pe_image_cfg_rpc
{
	
	// dst frame info
	Uint32 frm_y_addr;
	Uint32 frm_y_size;
	Uint32 frm_c_addr;
	Uint32 frm_c_size;
    
	Uint32 frm2_y_addr;
	Uint32 frm2_y_size;
	Uint32 frm2_c_addr;
	Uint32 frm2_c_size;
    
	Uint32 frm_mb_type;
	Uint32 frm3_y_addr;
	Uint32 frm3_y_size;
	Uint32 frm3_c_addr;
    
	Uint32 frm3_c_size;
	Uint32 frm4_y_addr;
	Uint32 frm4_y_size;
	Uint32 frm4_c_addr;
    
	Uint32 frm4_c_size;
	Uint32 decoder_buf;
	Uint32 decoder_buf_len;
    
	Int32 mp_cb; 

}Pe_image_cfg_rpc;


typedef struct image_info_pe_rpc
{
	Ulong	fsize;
	Ulong	width;
	Ulong	height;
	Ulong	bbp;
}Image_info_pe_rpc;


typedef struct imagedec_frm_rpc
{
	Uint32 frm_y_addr;
	Uint32 frm_y_len;
	Uint32 frm_c_addr;
	Uint32 frm_c_len;
	Uint32 busy;
}Imagedec_frm_rpc;


typedef struct pe_video_cfg_rpc
{
	Ulong mp_cb;
	Uint32 decoder_buf;
	Uint32 decoder_buf_len;
	Uint32 mm_vbv_len;
	Int32   disable_seek;
	Uint32 reserved;    // struct pe_video_cfg_extra *. set to 0 if no pe_video_cfg_extra
}Pe_video_cfg_rpc;



typedef struct _DEC_CHAPTER_INFO_RPC
{
    Ulong nb_chapter;
    Int32 cur_chapter;    
    Int32 cur_start_time;     
    Int32 cur_end_time; 
    
    Char  cur_title[10];      
    Int32 dst_chapter;       
    Int32 dst_start_time;     
    Int32 dst_end_time;  
    
    Uint32 reserved;           
}DEC_CHAPTER_INFO_RPC;



typedef struct fileinfo_video_rpc
{
	Char VideoDec[10]; //the name of the video codec. For now, we support below video codec:
	                   //"XD3", "XD4", "mp43", "XD", "XIV1", "XIV2", "DX50", "XVID", "unknown"
	Char AudioDec[10]; //the name of the audio codec. For now, we support below audio codec:
	                   //"PCM", "MP3", "AC3", "DTS", "unknown"
	Ulong AudioStreamNum; //The audio track number in the media stream
	Ulong SubStreamNum; //The subtitle stream number in the media stream

       Ulong TotalFrameNum; //The total frame number of the media stream
	Ulong FramePeriod; //The frame period of the media stream
	Ulong TotalTime; //Total play time of the media stream
	Int32   width; //The width of the media stream. The maximum width the video decoder can support is 720.

       Int32   height; //The height of the media stream. The maximum height the video decoder can support is 576.
	Ulong VideoBitrate;
	Ulong AudioBitrate;
	Ulong AudioChannelNum;

       Uint32 fsize;
	Int32 AudioSampleRate;
	Int32 video_codec_tag;
	Int32 cur_audio_stream_id;

       Int32 cur_sub_stream_id;
	Int32 cur_prog_id;
	Ulong ProgNum;
}Fileinfo_video_rpc;



typedef struct pe_cache_ex_rpc
{
	Uchar status;
	Uchar sub_status;
	Uchar mutex;
	Uint32 cache_buff;
	Uint32 cache_size;
	Uint32 data_len;
	Uint32 rd_pos;
	Uint32 wr_pos;
	 Int32  file_offset;	
}Pe_cache_ex_rpc;

typedef struct pe_cache_cmd_rpc
{
    Uint32 status; 
    Uint32 type;
    Uint32 reserved;
    Uint32 param[4];
}Pe_cache_cmd_rpc;


typedef struct rect_rpc
{
#if (defined(_MHEG5_ENABLE_) || defined(_MHEG5_V20_ENABLE_) )
	Int16	uStartX;	// Horizontal start point.
	Int16	uStartY;	// Vertical start point.
#else
	Uint16	uStartX;	// Horizontal start point.
	Uint16	uStartY;	// Vertical start point.
#endif
	Uint16	uWidth;	// Horizontal size.
	Uint16	uHeight;	// Vertical size.
}Rect_rpc;


typedef struct audio_config_rpc
{
    Int32 decode_mode;
    Int32 sync_mode;
    Int32 sync_unit;
    Int32 deca_input_sbm;
    
    Int32 deca_output_sbm;
    Int32 snd_input_sbm;
    Int32 pcm_sbm;
    Int32 codec_id;
    
    Int32 bits_per_coded_sample;
    Int32 sample_rate;
    Int32 channels;
    Int32 bit_rate;
    
    Uint32 pcm_buf;
    Uint32 pcm_buf_size;
    Int32 block_align;
    //Uchar extra_data[512];
    Uint32 codec_frame_size;
    Uint32 extradata_size;
    Uchar extradata_mode;
    Uchar cloud_game_prj;
}Audio_config_rpc;





typedef struct snd_dev_status_rpc
{
    Uchar flags;
    Uint32 volume;
    Uint32 in_mute;
    Uchar spdif_out;
    Uchar trackmode;
    
    Uint32 samp_rate;
    Uint32 samp_num;
    Uint32 ch_num;

    
    Uint32 drop_cnt;
    Uint32 play_cnt;
    Uint32 pcm_out_frames;
    
    Uint32 pcm_dma_base;
    Uint32 pcm_dma_len;
    Uint32 pcm_rd;
    Uint32 pcm_wt;
    Uint32 underrun_cnts;
    
    Uint32 pcm_dump_addr;
    Uint32 pcm_dump_len;
}Snd_dev_status_rpc;    



typedef struct spec_param_rpc
{
	Uint32 spec_call_back;
	Uint32 collumn_num;
}Spec_param_rpc;


typedef struct spec_step_table_rpc
{
    Uint32 column_num;
    Uchar ptr_table;
}Spec_step_table_rpc;


typedef struct snd_spdif_scms_rpc
{
	Uchar copyright;
	Uchar reserved;
	Uchar l_bit;
	Uchar category_code;
	Uint16 reserved16;
}Snd_spdif_scms_rpc;


typedef struct snd_sync_param_rpc
{
    Uint32 drop_threshold;
    Uint32 wait_threshold;
    Uint32 delay_video_sthreshold;
}Snd_sync_param_rpc;


typedef struct isdbtcc_config_par_rpc
{
	Uint32 g_buf_addr;
	Uint32 g_buf_len;
	
	Uint16 max_isdbtcc_height;
	Uchar isdbtcc_osd_layer_id;
	Uint16 isdbtcc_width;
	Uint16 isdbtcc_height;
	Uint16 isdbtcc_hor_offset;
	Uint16 isdbtcc_ver_offset;

       Uint32 osd_isdbtcc_enter;
	Uint32 osd_isdbtcc_leave;
}Isdbtcc_config_par_rpc;



typedef struct atsc_subt_config_par_rpc
{
   Uint32 bs_buf_addr;
   Uint16 bs_buf_len;
   Uint32 sec_buf_addr;
   Uint16 sec_buf_len;
   Uchar Outline_thickness_from_stream;
   
   Uchar DropShadow_right_from_stream;   
   Uchar DropShadow_bottom_from_stream;      
   Uchar Outline_thickness;
   Uchar DropShadow_right;
   Uchar DropShadow_bottom;   
}Atsc_subt_config_par_rpc;


typedef struct sdec_feature_config_rpc
{
	Uint32 temp_buf;
	Uint32 temp_buf_len;
	Uint32 bs_buf;
	Uint32 bs_buf_len;
    
	Uint32 bs_hdr_buf;
	Uint32 bs_hdr_buf_len;
	Uint32 pixel_buf;
	Uint32 pixel_buf_len;
    
	Uchar tsk_qtm;
	Uchar tsk_pri;
	Uchar transparent_color;
	Uchar support_hw_decode;
    
	Uint32 sdec_hw_buf;
	Uint16 sdec_hw_buf_len;
	Uint32 subt_draw_pixelmap;
	Uint32 subt_draw_pixel;
    
	Uint32 region_is_created;
	Uint32 subt_create_region;
	Uint32 subt_region_show;
	Uint32 subt_delete_region;
    
	Uint32 subt_get_region_addr;
	Uint32 draw_obj_hardware;
	Uint32 subt_display_define;
}Sdec_feature_config_rpc;


typedef struct subt_config_par_rpc
{
   Uchar cc_by_vbi;
   Uchar cc_by_osd;
   Uchar osd_blocklink_enable;
   Uint32 g_ps_buf_addr;
   
   Uint32 g_ps_buf_len;
   Uchar sys_sdram_size;
   Uint16 max_subt_height;
   Uchar speed_up_subt_enable;
   
   Uchar osd_layer_id;
   Uchar hd_subtitle_support;
   Uint16 subt_width;
   Uint16 subt_height;
   
   Uint16 subt_hor_offset;
   Uint16 subt_ver_offset;
   Uint32 osd_subt_enter;
   Uint32 osd_subt_leave;
   
   Uint32 osd_get_scale_para;
}Subt_config_par_rpc;


typedef struct Audio_info_rpc
{
	Uint32 bit_rate;
	Uint32 sample_freq;
	Uint32 mode;
	Uchar layer;
    
	Uchar id;
	Uchar mpeg25;
	Uint16 frm_size;
	
}AUDIO_INFO_rpc;


typedef struct reverb_param_rpc
{
	Uint16 enable;
	Uint16 reverb_mode;
}Reverb_param_rpc;


typedef struct  pl_ii_param_rpc
{
	Uint16 enable;
	
	Int16 abaldisable;
	Int16 chanconfig;
	Int16 dimset;
	Int16 surfiltenable;
	Int16 modeselect;
	Int16 panoramaenable;
	Int16 pcmscalefac;
	Int16 rsinvenable;
	Int16 cwidthset;

}Pl_ii_param_rpc;


typedef struct io_param_rpc
{
     Uint32 io_buff_in;
     Uint32 buff_in_len;
     Uint32 io_buff_out;
     Uint32 buff_out_len;
}Io_param_rpc;


typedef struct cur_stream_info_rpc
{
       Uchar str_type;
	Uchar bit_depth;
    	Uint32 sample_rate;
    	Uint32 samp_num;
        
    	Uint32 chan_num;
	Uint32 frm_cnt;
	Uint32 reserved1;
	Uint32 reserved2;
    
	Uint32 input_ts_cnt;
	Uint32 sync_error_cnt;
	Uint32 sync_success_cnt;
       Uint32 sync_frm_len;
       
	Uint32 decode_error_cnt;
      Uint32 decode_success_cnt;
      Uint32 cur_frm_pts;
}Cur_stream_info_rpc;


typedef struct deca_buf_info_rpc
{
    Uint32 buf_base_addr;
    Uint32 buf_len;
    Uint32 used_len;
    Uint32 remain_len;
    
    Uint32 cb_rd;
    Uint32 cb_wt;
    Uint32 es_rd;
    Uint32 es_wt;   
}Deca_buf_info_rpc;

typedef struct ase_str_play_param_rpc
{
	UINT8 * src;
	UINT32 len;
	UINT32 loop_cnt; //!<play the stream (loop_cnt+1) time(s)
	UINT32 loop_interval; //!<play the stream repeatedly with the
						//!<interval (loop_interval)ms 
	UINT32 async_play; //!<=1, call stream play and return immediately
	UINT32 reserved;
	UINT32 need_notify;  //!<1: stream play finished, audio decoder
					   //!<	will call the call_back_function to notify up layer.
	void (*registered_cb)(void);
}Ase_str_play_param_rpc;

typedef struct Position_rpc
{
	Uint16	uX;	// Horizontal position .
	Uint16	uY;	// Vertical position.
}Position_rpc;

typedef struct Rectsize_rpc
{
	Uint16	uWidth; 	// Horizontal size.
	Uint16	uHeight;// Vertical size.
}RectSize_rpc;

#if 0
typedef struct  Ycbcrcolor_rpc
{
	Uchar 	uY;
	Uchar	uCb;
	Uchar	uCr;
}YCbCrColor_rpc;
#endif

typedef struct Advsetting_rpc
{
	Uchar init_mode;
	Int32 out_sys;
    
	Int32 bprogressive;
       Uchar switch_mode;   

}AdvSetting_rpc;

#if 0
typedef struct Vdecpipinfo_rpc
{

	struct Position_rpc pipStaPos;
	RectSize_rpc pipSize;
	RectSize_rpc mpSize;
	Int32 bUseBgColor;
	YCbCrColor_rpc bgColor;

	Int32 buse_sml_buf;
    
	struct rect_rpc		src_rect;
	struct rect_rpc	dst_rect;

	AdvSetting_rpc adv_setting;
}VDecPIPInfo_rpc;
#endif
#if 0
typedef struct vdec_statusinfo_rpc
{
	Int32 uCurStatus;
	Int32 uFirstPicShowed;
	Int32 bFirstHeaderGot;
	Uint16 pic_width;
    
	Uint16	pic_height;
	Uint16	status_flag;
	Uint32	read_p_offset;
	Uint32	write_p_offset;
    
	Uint32	display_idx;
	Int32	use_sml_buf;
	Int32       output_mode;
	
#ifdef VIDEO_SECOND_B_MONITOR
	Uchar	mb_x;
	Uchar	mb_y;
	Uint32	decoding_head_idx;
#endif	
	Uint32	valid_size;
	Uint32  MPEG_format;
	Int32 aspect_ratio;
	Uint16 frame_rate;
    
	Uint32 bit_rate;
	Int32 	hw_dec_error;
	Int32      display_frm;
	Uchar     top_cnt;
    
	Uchar	play_direction;
	Uchar	play_speed;
	Uchar	api_play_direction;
	Uchar	api_play_speed;

	Int32	is_support;
	Uint32 	vbv_size;
       Uchar   cur_dma_ch;
}VDec_StatusInfo_rpc;
#endif


typedef struct imagedec_show_shutters_rpc
{
	Uchar direction; //0 : horizontal 1: vertical
	Uchar type;
	Uint16 time; // ms
}Imagedec_show_shutters_rpc;


typedef struct imagedec_show_brush_rpc
{
	Uchar direction; //0 : from left to right 1: from top to bottom
	Uchar type;
	Uint16 time; // ms
}Imagedec_show_brush_rpc;


typedef struct imagedec_show_slide_rpc
{
	Uchar direction; //0 : from left to right 1: from top to bottom
	Uchar type;
	Uint16 time; // ms	
}Imagedec_show_slide_rpc;

typedef struct imagedec_show_random_rpc
{
	Uchar type;	// 0: random block operation
	Uchar res;
	Uchar time; // ms
}Imagedec_show_show_random_rpc;

typedef struct imagedec_show_fade_rpc
{
	Uchar type;
	Uchar res;
	Uint16 time; // ms
}Imagedec_show_fade_rpc;



typedef struct image_slideshow_effect_rpc
{
	
	Int32 mode;

	Imagedec_show_shutters_rpc shuttles_param;
	Imagedec_show_brush_rpc brush_param;
	Imagedec_show_slide_rpc 	slide_param;
    
	Imagedec_show_show_random_rpc  random_param;
	Imagedec_show_fade_rpc 		fade_param;
}Image_slideshow_effect_rpc;


typedef struct image_config_rpc
{
	Int32 file_name;

	Uchar	decode_mode;		
	Uchar	show_mode;
	Uchar	vpo_mode;
       Uchar	rotate;

	//rect for source
	Uint16	src_left;
	Uint16     src_top;
	Uint16	src_width;
	Uint16	src_height;

	//rect for display
	Uint16	dest_left;
	Uint16	dest_top;
	Uint16	dest_width;
	Uint16	dest_height;

	Int32 mp_cb;
}Image_config_rpc;



typedef struct image_engine_config_rpc
{
	Uchar	decode_mode;		
	Uchar	show_mode;
	Uchar	vpo_mode;
	Uchar	rotate;

	//rect for source
	Uint16	src_left;
	Uint16	src_top;
	Uint16	src_width;
	Uint16	src_height;

	//rect for display
	Uint16	dest_left;
	Uint16	dest_top;
	Uint16	dest_width;
	Uint16	dest_height;


	Uint32  img_fmt;
}Image_engine_config_rpc;


typedef struct image_display_rpc
{
	Uchar	decode_mode;		
	Uchar	show_mode;
	Uchar	vpo_mode;
	Uchar	rotate;

	//rect for source
	Uint16	src_left;
	Uint16	src_top;
	Uint16	src_width;
	Uint16	src_height;

	//rect for display
	Uint16	dest_left;
	Uint16	dest_top;
	Uint16	dest_width;
	Uint16	dest_height;


	Uint32  img_fmt;

	Uint32	y_addr;
	Uint32	y_len; 
	Uint32 	c_addr;
	Uint32	c_len;

	Uint32	width;
	Uint32	height;

	Uint32	sample_format;

	Uint32	mp_cb; 

}Image_display_rpc;







/********************* decv *****************************/
typedef struct vdec_adpcm_rpc
{
	Uchar adpcm_mode;
	Uchar adpcm_ratio;
}Vdec_adpcm_rpc;

typedef struct vdec_sml_frm_rpc
{
	Uchar sml_frm_mode;
	Uint32 sml_frm_size;
}Vdec_sml_frm_rpc;

typedef struct vdec_mem_map_rpc
{
	//frm addr
	Uint32	frm0_Y_size;
	Uint32	frm0_C_size;
	Uint32	frm1_Y_size;
	Uint32	frm1_C_size;
	Uint32	frm2_Y_size;
	Uint32	frm2_C_size;
	
	Uint32	frm0_Y_start_addr;
	Uint32	frm0_C_start_addr;
	Uint32	frm1_Y_start_addr;
	Uint32	frm1_C_start_addr;
	Uint32	frm2_Y_start_addr;
	Uint32	frm2_C_start_addr;

	Uint32	dvw_frm_size;
	Uint32	dvw_frm_start_addr;

	//MAF addr
	Uint32	maf_size;
	Uint32	maf_start_addr;

	//VBV addr
	Uint32	vbv_size;
	Uint32	vbv_start_addr;
	Uint32	vbv_end_addr;

	//frame buffer 3 allocated for pip application
	Uint32	frm3_Y_size;
	Uint32 	frm3_C_size;
	Uint32 	frm3_Y_start_addr;
	Uint32 	frm3_C_start_addr;

	Uint32   frm_num;//3 // 3 or 4 frames can be choosed for the main device. It is unactive for the second device
	Uint32   res_bits;
	Uint32   res_pointer;
}Vdec_mem_map_rpc;

typedef struct vdec_config_par_rpc
{	
	//feature entrys
	Uchar user_data_parsing;
	Uchar dtg_afd_parsing;
	Uchar drop_freerun_pic_before_firstpic_show;
	Uchar reset_hw_directly_when_stop;
	Uchar show_hd_service;
	Uchar still_frm_in_cc;//only work in 2M mode
	Uchar extra_dview_window;
	Uchar not_show_mosaic;// now's feature just work rightly at Dview & MP mode
	Uchar return_multi_freebuf;
	Uchar advance_play;
    
	Uchar lm_shiftthreshold;////only for the project of dongqi( digisat)
	Uchar vp_init_phase;//according to macro DEFAULT_MP_FILTER_ENABLE
	Uchar preview_solution;
	
	Uint32 res_bits;
	Uint32 res_pointer;
}Vdec_config_par_rpc;

typedef struct vdec_avs_memmap_rpc
{
	Bool support_multi_bank;

	Uint32 frame_buffer_base;
	Uint32 frame_buffer_len;

	Uint32 dv_frame_buffer_base;
	Uint32 dv_frame_buffer_len;

	Uint32 mv_buffer_base;
	Uint32 mv_buffer_len;

	Uint32 mb_col_buffer_base;
	Uint32 mb_col_buffer_len;

	Uint32 mb_neighbour_buffer_base;
	Uint32 mb_neighbour_buffer_len;

	Uint32 cmd_queue_buffer_base;
	Uint32 cmd_queue_buffer_len;

	Uint32 vbv_buffer_base;
	Uint32 vbv_buffer_len;

	Uint32 laf_rw_buf;
	Uint32 laf_rw_buffer_len;

	Uint32 laf_flag_buf;
	Uint32 laf_flag_buffer_len;

	Bool   support_conti_memory;
	Uint32 avs_mem_addr;
	Uint32 avs_mem_len;
}Vdec_avs_memmap_rpc;

typedef struct vdec_avc_memmap_rpc
{
	Bool support_multi_bank;

	Uint32 frame_buffer_base;
	Uint32 frame_buffer_len;

	Uint32 dv_frame_buffer_base;
	Uint32 dv_frame_buffer_len;

	Uint32 mv_buffer_base;
	Uint32 mv_buffer_len;

	Uint32 mb_col_buffer_base;
	Uint32 mb_col_buffer_len;

	Uint32 mb_neighbour_buffer_base;
	Uint32 mb_neighbour_buffer_len;

	Uint32 cmd_queue_buffer_base;
	Uint32 cmd_queue_buffer_len;

	Uint32 vbv_buffer_base;
	Uint32 vbv_buffer_len;

	Uint32 laf_rw_buf;
	Uint32 laf_rw_buffer_len;

	Uint32 laf_flag_buf;
	Uint32 laf_flag_buffer_len;

	Bool   support_conti_memory;
	Uint32 avc_mem_addr;
	Uint32 avc_mem_len;
}Vdec_avc_memmap_rpc;

typedef struct vdec_avc_config_par_rpc
{	
    Uint32 max_additional_fb_num;
#ifdef VIDEO_SEAMLESS_SWITCHING
	Uchar seamless_enable;
#endif
	Uchar dtg_afd_parsing;
}Vdec_avc_config_par_rpc;

typedef struct vdec_dvrconfigparam_rpc
{
	Bool is_scrambled;
}Vdec_dvrconfigparam_rpc;

typedef struct  ycbcrcolor_rpc
{
	Uchar 	uY;
	Uchar	uCb;
	Uchar	uCr;
}Ycbcrcolor_rpc;
typedef enum tvsystem_rpc
{
	PAL_r		= 0	, 
	NTSC_r		, 
	PAL_M_r		, 
	PAL_N_r		, 
	PAL_60_r		, 
	NTSC_443_r	, 	
	SECAM_r		,
	MAC_r			,
	LINE_720_25_r,	
	LINE_720_30_r,	
	LINE_1080_25_r,	
	LINE_1080_30_r	
}Tvsystem_rpc;

typedef struct advsetting_rpc
{
	Uchar init_mode;
	Tvsystem_rpc out_sys;
	Bool bprogressive;
    Uchar switch_mode;    
}Advsetting_rpc;

typedef struct vdecpipinfo_rpc
{
    Position_rpc pipStaPos;
    Rect_rpc pipSize;
    Rect_rpc mpSize;
    Bool    bUseBgColor;
    Ycbcrcolor_rpc bgColor;
    Bool buse_sml_buf;
    Rect_rpc src_rect;
    Rect_rpc dst_rect;
    Advsetting_rpc adv_setting;
}Vdecpipinfo_rpc;

typedef struct mpsource_callback_rpc
{
	Uint32 handler;
	Uint32 RequestCallback;
	Uint32 ReleaseCallback;
	Uint32 vblanking_callback;
}Mpsource_callback_rpc;

typedef struct pipsource_callback_rpc
{
	Uint32	RequestCallback;
	Uint32	ReleaseCallback;
	Uint32  vblanking_callback;
    Uint32  handler;
}Pipsource_callback_rpc; 

typedef enum vdec_status_rpc 
{
	VDEC27_ATTACHED_r,
	VDEC27_STARTED_r,
	VDEC27_STOPPED_r,
	VDEC27_PAUSED_r,
}Vdec_status_rpc;

typedef enum vdecoutputmode_rpc
{
	MP_MODE_r,	// main picture
	PIP_MODE_r,		// picture in picture
	PREVIEW_MODE_r,
//changed for s3601-6/5
	HSCALE_MODE_r,
	DVIEW_MODE_r,
	//MP_HSCALE_MODE,
	MP_DVIEW_MODE_r,
	HSCALE_DVIEW_MODE_r,
	AUTO_MODE_r,
//- changed end
	DUAL_MODE_r,
	DUAL_PREVIEW_MODE_r,
	IND_PIP_MODE_r,
	SW_PASS_MODE_r,
	HW_DEC_ONLY_MODE_r,
	RESERVE_MODE_r
}Vdecoutputmode_rpc;

typedef enum aspratio_rpc
{
	DAR_FORBIDDEN_r = 0,  
	SAR_r, 				 
	DAR_4_3_r,			 
	DAR_16_9_r,			 
	DAR_221_1_r			 
}Apratio_rpc; 

typedef struct vdec_statusinfo_rpc
{
	Vdec_status_rpc	uCurStatus;
	Bool	uFirstPicShowed;
	Bool	bFirstHeaderGot;
	Uint16	pic_width;
	Uint16	pic_height;
	Uint16	status_flag;
	Uint32	read_p_offset;
	Uint32	write_p_offset;
	Uint32	display_idx;
	Bool	use_sml_buf;
	Vdecoutputmode_rpc	 output_mode;
	
#ifdef VIDEO_SECOND_B_MONITOR
	Uchar	mb_x;
	Uchar	mb_y;
	Uint32	decoding_head_idx;
#endif	
	Uint32	valid_size;
	Uint32  MPEG_format;
	Apratio_rpc aspect_ratio;
	Uint16 frame_rate;
	Uint32 bit_rate;
	Bool 	hw_dec_error;
	Bool      display_frm;
	Uchar     top_cnt;
	Uchar	play_direction;
	Uchar	play_speed;
	Uchar	api_play_direction;
	Uchar	api_play_speed;

	Bool	is_support;
	Uint32 	vbv_size;
    Uchar   cur_dma_ch;
}Vdec_statusinfo_rpc;

typedef struct vdec_decore_status_rpc
{
    Uint32 decode_status;
    Uint32 pic_width;
    Uint32 pic_height;
    Uint32 sar_width;
    Uint32 sar_heigth;
    Uint32 frame_rate;
    Int32 interlaced_frame;
    Int32 top_field_first;
    Int32 first_header_got;
    Int32 first_pic_showed;
    Uint32 frames_decoded;
    Uint32 frames_displayed;
    Int64 frame_last_pts;
    Uint32 buffer_size;
    Uint32 buffer_used;
    Uint32 decode_error;
    Uint32 decoder_feature;
    Uint32 under_run_cnt;
    Int32 first_pic_decoded;
    Int32 output_mode;
    Uint32 frame_angle;
}Vdec_decore_status_rpc;

typedef struct vdec_frm_info_api_rpc
{
	Uint32 uY_Addr;
	Uint32 uC_Addr;
	Uint16 uWidth;
	Uint16 uHeight;
	Uint32 uY_Size;
	Uint32 uC_Size;
}Vdec_frm_info_api_rpc;

typedef struct vdec_io_get_frm_para_rpc
{
	Uchar ufrm_mode;
	Vdec_frm_info_api_rpc tFrmInfo;
}Vdec_io_get_frm_para_rpc;

typedef enum vdeccbtype_rpc
{
	VDEC_CB_SETTING_CHG_r = 0,
	VDEC_CB_REQ_DATA_r,
	VDEC_CB_STOP_r,
	VDEC_CB_FINISH_CUR_PIC_r,
	VDEC_CB_FINISH_I_FRAME_r,
	VDEC_CB_FINISH_TARGET_FRAME_r,
	VDEC_CB_FIRST_SHOWED_r,
	VDEC_CB_MODE_SWITCH_OK_r,
	VDEC_CB_BACKWARD_RESTART_GOP_r,
	VDEC_CB_OUTPUT_MODE_CHECK_r,
	VDEC_CB_FIRST_HEAD_PARSED_r,
	VDEC_CB_MONITOR_FRAME_VBV_r,

}Vdeccbtype_rpc;

typedef struct vdec_io_reg_callback_para_rpc
{
	Vdeccbtype_rpc eCBType;
	Uint32 pCB;
}Vdec_io_reg_callback_para_rpc;

typedef enum vdec_out_pic_type_rpc
{
	VDEC_PIC_IMC1_r,
	VDEC_PIC_IMC2_r,
	VDEC_PIC_IMC3_r,
	VDEC_PIC_IMC4_r,
	VDEC_PIC_YV12_r
}Vdec_out_pic_type_rpc;

typedef struct vdec_picture_rpc
{
	Vdec_out_pic_type_rpc type; // only support 4:2:0 IMC3 now
	Uint32 out_data_buf;
	Uint32 out_data_buf_size;
	Uint32 out_data_valid_size;
	Uint32 pic_width;
	Uint32 pic_height;
}Vdec_picture_rpc;

typedef enum vdec_dbg_flag_rpc
{
	VDEC_DBG_NONE_r,
	VDEC_DBG_DEFAULT_r,	
}Vdec_dbg_flag_rpc;

typedef struct vdec_io_dbg_flag_info_rpc
{
	Vdec_dbg_flag_rpc dbg_flag;
	Int32 active_flag;
	Int32 unique_flag;
}Vdec_io_dbg_flag_info_rpc;

typedef struct video_rect_rpc
{
	Int32 x;	
	Int32 y;	
	Int32 w;	
	Int32 h;	
}Video_rect_rpc;

typedef enum vdecFrmArrayType_rpc
{
	VDEC_FRM_ARRAY_MP_r = 0x01,
	VDEC_FRM_ARRAY_DV_r = 0x02,

	VDEC_FRM_ARRAY_INVALID_r = 0xff,
}VdecFrmArrayType_rpc;

typedef struct outputFrmManager_rpc
{
	Uint32	display_index[2];

	VdecFrmArrayType_rpc de_last_request_frm_array[2];
	VdecFrmArrayType_rpc de_last_release_frm_array[2];
	Uchar  de_last_request_idx[2];
	Uchar  de_last_release_idx[2];
    
	Int32 last_output_pic_released[2];
	Int32 de_last_release_poc[2];
	Int32 de_last_request_poc[2];

	Uchar frm_number;
	Uchar pip_frm_number;
}OutputFrmManager_rpc;

typedef struct vdecFormatInfo_rpc
{
    Ulong fourcc;
    Int32 bits_per_pixel;
    Int32 pic_width;
    Int32 pic_height;
    Int32 pic_inverted;
    Int32 pixel_aspect_x;
    Int32 pixel_aspect_y;
    Int32 frame_rate;
    Int32 frame_period;
    Bool frame_period_const;
}Vdecformatinfo_rpc;

typedef struct VdecFBConfig_rpc
{
    Uint32 FBStride;
    Uint32 FBMaxHeight;
    Uint32  FrmBuf;     //used only for SW_DECODE
    Uint32  DispBuf;    //In HW_DISPLAY mode, first 4 bytes store frame buffer addr, last 4 byte stor dv buffer addr
}Vdecfbconfig_rpc;

typedef struct VdecHWMemConfig_rpc
{
    Uint32 fb_y[6];
    Uint32 fb_c[6];
    Uint32 dv_y[6];
    Uint32 dv_c[6];
    Uint32 fb_max_stride;
    Uint32 fb_max_height;
    Uint32 dv_max_stride;
    Uint32 dv_max_height;
    Uint32 fb_num;
    Uint32 neighbor_mem;
    Uint32 colocate_mem;
    Uint32 cmdq_base;
    Uint32 cmdq_len;
    Uint32 vbv_start;
    Uint32 vbv_len;
}Vdechwmemconfig_rpc;

typedef struct vdecInit_rpc
{
    Vdecformatinfo_rpc fmt_out;
    Vdecformatinfo_rpc fmt_in;
    Vdecfbconfig_rpc pfrm_buf;
    Vdechwmemconfig_rpc phw_mem_cfg;
    Uint32 on_decode_event;
    Uint32 pfn_decore_de_request;
    Uint32 pfn_decore_de_release;
    Uint32 decoder_flag;
    Uint32 decode_mode;
    Uint32 preview;
}Vdecinit_rpc;
    
/***************** Avs ********************/
typedef enum avsync_mode_e
{
	AVSYNC_MODE_PCR_r, 
	AVSYNC_MODE_AUDIO_r, 
	AVSYNC_MODE_VIDEO_r, 
	AVSYNC_MODE_V_FREERUN_r, 
	AVSYNC_MODE_A_FREERUN_r, 
	AVSYNC_MODE_AV_FREERUN_r, 
}Avsync_mode_e_rpc;

typedef enum avsync_srctype_e
{
	AVSYNC_SRC_TURNER_r, 
	AVSYNC_SRC_SWDMX_r, 
	AVSYNC_SRC_HDD_MP_r, 
	AVSYNC_SRC_NETWORK_MP_r, 
}Avsync_srctype_e_rpc;

typedef struct Avsync_cfg_param_t_rpc
{
	Uint32 vhold_thres; 
	Uint32 vdrop_thres; 
	Uint32 ahold_thres; 
	Uint32 adrop_thres; 
	Avsync_mode_e_rpc sync_mode; 
	Avsync_srctype_e_rpc src_type; 
}Avsync_cfg_param_t_rpc;

typedef struct avsync_adv_param_t_rpc
{
	Uint32 afreerun_thres; 
	Uint32 vfreerun_thres; 
	Uchar  disable_monitor; 
	Uchar  disable_first_video_freerun; 
	Uint16  dual_output_sd_delay; 
	Uint32 rsvd1; 
	Uint32 rsvd2; 
	Uint32 rsvd3;
}Avsync_adv_param_t_rpc;

typedef enum avsync_dev_status_rpc
{
	AVSYNC_ATTACHED_r, 
	AVSYNC_OPENED_r,    
	AVSYNC_CLOSED_r,    
	AVSYNC_STARTED_r,  
	AVSYNC_STOPPED_r,	
}Avsync_dev_status_rpc;

typedef struct avsync_status_t_rpc
{
	Avsync_dev_status_rpc device_status;
	Uint32 vpts_offset; 
	Uint32 apts_offset;
	Uchar v_sync_flg; 
	Uchar a_sync_flg; 
	Uchar rsvd0; 
	Uchar rsvd1; 
}Avsync_status_t_rpc;

typedef struct avsync_statistics_t_rpc
{
	Uint32 total_v_play_cnt;
	Uint32 total_v_drop_cnt;
	Uint32 total_v_hold_cnt;
	Uint32 total_v_freerun_cnt;
	Uint32 total_a_play_cnt;
	Uint32 total_a_drop_cnt;
	Uint32 total_a_hold_cnt;
	Uint32 total_a_freerun_cnt;
}Avsync_statistics_t_rpc;

typedef enum avsync_video_smooth_level_rpc
{
	AVSYNC_VIDEO_SMOOTH_LEVEL1_r,
	AVSYNC_VIDEO_SMOOTH_LEVEL2_r
}Avsync_video_smooth_level_rpc;

typedef struct avsync_smoothly_play_cfg_t_rpc 
{
	Uchar onoff;
	Uchar interval;
	Avsync_video_smooth_level_rpc level; 
}Avsync_smoothly_play_cfg_t_rpc;

typedef struct avsync_get_stc_en_t_rpc
{
	Uint32 sharem_addr;
	Uchar enable;
}Avsync_get_stc_en_t_rpc;

/***************** DMX ********************/
typedef struct io_param_ex_rpc
{
     Uint32 io_buff_in;
     Uint32 buff_in_len;
     Uint32 io_buff_out;
     Uint32 buff_out_len;
	 Uint32 hnd;
	 Uchar h264_flag;
	 Uchar is_scrambled;
     Uchar record_all;
}Io_param_ex_rpc;

typedef struct pes_pkt_param_rpc
{
    Uchar stream_id;
    Uint16 pes_pkt_len;
    Uchar filled_byte_3;
    Uchar pes_scramb_ctrl;
    Uchar marker_10;
    Uchar filled_byte_4;
    Uchar pts_dts_flags;

    Uchar pes_header_data_len;
    Uint16 pes_data_len;
    Uint32 dmx_state;
    Uint32 stream_type;        
    Uint32 head_buf_pos;
    Uint32 av_buf;
    Uint32 av_buf_pos;
    Uint32 av_buf_len;
    Control_block_rpc ctrl_blk;
    Uint32 device;
    Uint32 request_write;
    Uint32 update_write;
    Uchar   get_pkt_len;
    Uchar   get_header_data_len;
    Uchar   get_pts;
    Uchar   str_confirm;
    Uchar   reserved;
    Uchar   conti_conter;
    Uint32   head_buf;
    Uchar   ch_num;
    Uint32 channel;
    Uchar   cw_parity_num;                          
    Uchar   xfer_es_by_dma;
    Uchar   dma_ch_num;
    Uint32  last_dma_xfer_id;
    Uchar   ts_err_code; 
    Uint32  ovlp_cnt;
    Uint32  discont_cnt;    
    Uint32  LastTsAdaCtrl;
	Uint32  unlock_cnt;

	Uint32 new_vbv_method_enable;
	Uint32 new_vbv_request;
	Uint32 new_vbv_update;	
}Pes_pkt_param_rpc;


/***************** VBI ********************/
typedef struct vbi_mem_map_rpc
{
	/*stream buffer info*/
	Uint32	sbf_start_addr;
	Uint32	sbf_size;

	/*control buffer info*/
	Uint32	data_hdr;
	
	/*page buffer info*/
	Uint32	pbf_start_addr;
	Uint32	pbf_size;

	/*ttx sub page mem info*/
	Uint32	sub_page_start_addr;
	Uint32	sub_page_size;

	/*packet26 mem info*/
	Uint32	p26_nation_buf_start_addr;
	Uint32	p26_nation_buf_size;
	Uint32	p26_data_buf_start_addr;
	Uint32	p26_data_buf_size;

}Vbi_mem_map_rpc;

typedef struct vbi_config_par_rpc
{
	Uchar	ttx_by_vbi;
	Uchar 	cc_by_vbi;
	Uchar 	vps_by_vbi;
	Uchar	wss_by_vbi;

	Uchar 	hamming_8_4_enable;
	Uchar	hamming_24_16_enable;
	
	Uchar 	erase_unknown_packet;
	Uchar	parse_packet26_enable;
	Uchar	ttx_sub_page;
	Uchar	user_fast_text;
	
	Vbi_mem_map_rpc mem_map;
}Vbi_config_par_rpc;

typedef struct ttx_config_par_rpc
{
	Uchar erase_unknown_packet;
	Uchar ttx_sub_page;
	Uchar parse_packet26_enable;
	Uchar user_fast_text;
	Uchar no_ttx_descriptor;
	Uchar sys_sdram_size_2m; //true:2M,false:other
	Uchar hdtv_support_enable;
	Uchar ttx_vscrbuf;
	Uchar ttx_pallette;

	Uchar ttx_cyrillic_1_support;
	Uchar ttx_cyrillic_2_support;
	Uchar ttx_cyrillic_3_support;
	Uchar ttx_greek_support;
	Uchar ttx_arabic_support;
	Uchar ttx_hebrew_support;
	Uchar ttx_cyrillic_g2_support;
	Uchar ttx_greek_g2_support;
	Uchar ttx_arabic_g2_support;
	Uchar ttx_g3_support;

	Uint16  ttx_color_number;

	Uint32  ttx_subpage_addr;

	Uchar osd_layer_id;

	Uint32  get_ttxchar_from_cyrillic_1;
	Uint32  get_ttxchar_from_cyrillic_2;
	Uint32  get_ttxchar_from_cyrillic_3;
	Uint32  get_ttxchar_from_greek;
	Uint32  get_ttxchar_from_arabic;
	Uint32  get_ttxchar_from_hebrew;
	Uint32  get_ttxchar_from_g2;
	Uint32  get_ttxchar_from_cyrillic_g2;
	Uint32  get_ttxchar_from_greek_g2;
	Uint32  get_ttxchar_from_arabic_g2;
	Uint32  get_ttxchar_from_g3;
	Uint32  ttx_drawchar;
	Uint32  osd_get_scale_para;
}Ttx_config_par_rpc;

typedef struct ttx_page_info_rpc
{
    Uchar num;
    Uint32 page_addr;
}Ttx_page_info_rpc;

/***************** CE ********************/
typedef enum CE_OTP_KEY_SEL_rpc
{
    OTP_KEY_0_0_r=0,
    OTP_KEY_0_1_r=1,
    OTP_KEY_0_2_r=2,
    OTP_KEY_0_3_r=3

}Ce_otp_key_sel_rpc;

typedef struct otp_param_rpc
{
    Uchar otp_addr;
    Ce_otp_key_sel_rpc  otp_key_pos;   
}Otp_param_rpc;

typedef struct data_param_rpc
{
	Uint32 crypt_data[4] ; 
	Uint32 data_len ;
}Data_param_rpc;

typedef enum CE_CRYPT_SELECT_rpc
{  
    CE_IS_DECRYPT_r = 1,
    CE_IS_ENCRYPT_r=0
}Ce_crypt_select_rpc;

typedef enum CE_MODULE_SELECT_rpc
{  
    CE_SELECT_AES_r = 1,
    CE_SELECT_DES_r=0
}Ce_module_select_rpc;

typedef struct  des_param_rpc
{
	Ce_crypt_select_rpc  crypt_mode;
	Ce_module_select_rpc aes_or_des;
	Uchar des_low_or_high;
}Des_param_rpc;

typedef enum CE_KEY_rpc
{
    KEY_0_0_r=0,
    KEY_0_1_r=1,
    KEY_0_2_r=2,
    KEY_0_3_r=3,
    KEY_1_0_r=4,
    KEY_1_1_r=5,
    KEY_1_2_r=6,
    KEY_1_3_r=7,
    KEY_2_0_r=8,
    KEY_2_1_r=9,
    KEY_2_2_r=0xa,
    KEY_2_3_r=0xb,
    KEY_2_4_r=0xc,
    KEY_2_5_r=0xd,
    KEY_2_6_r=0xe,
    KEY_2_7_r=0xf

}Ce_key_rpc;

typedef enum CE_CRYPT_TARGET_rpc
{
    CRYPT_KEY_1_0_r=0x4,
    CRYPT_KEY_1_1_r=0x5,
    CRYPT_KEY_1_2_r=0x6,
    CRYPT_KEY_1_3_r=0x7,

    CRYPT_KEY_2_0_r=0x8,
    CRYPT_KEY_2_1_r=0x9,
    CRYPT_KEY_2_2_r=0xa,
    CRYPT_KEY_2_3_r=0xb,
    CRYPT_KEY_2_4_r=0xc,
    CRYPT_KEY_2_5_r=0xd,
    CRYPT_KEY_2_6_r=0xe,
    CRYPT_KEY_2_7_r=0xf,

    CRYPT_KEY_3_0_r=0x10,
    CRYPT_KEY_3_1_r=0x11,
    CRYPT_KEY_3_2_r=0x12,
    CRYPT_KEY_3_3_r=0x13,
    CRYPT_KEY_3_4_r=0x14,
    CRYPT_KEY_3_5_r=0x15,
    CRYPT_KEY_3_6_r=0x16,
    CRYPT_KEY_3_7_r=0x17,
    CRYPT_KEY_3_8_r=0x18,
    CRYPT_KEY_3_9_r=0x19,
    CRYPT_KEY_3_10_r=0x1a,
    CRYPT_KEY_3_11_r=0x1b,
    CRYPT_KEY_3_12_r=0x1c,
    CRYPT_KEY_3_13_r=0x1d,
    CRYPT_KEY_3_14_r=0x1e,
    CRYPT_KEY_3_15_r=0x1f,

    HDCP_KEY_0_r=0x10,
    HDCP_KEY_1_r=0x11,
    HDCP_KEY_2_r=0x12,
    HDCP_KEY_3_r=0x13,
    HDCP_KEY_4_r=0x14,
    HDCP_KEY_5_r=0x15,
    HDCP_KEY_6_r=0x16,
    HDCP_KEY_7_r=0x17,
    HDCP_KEY_8_r=0x18,
    HDCP_KEY_9_r=0x19,
    HDCP_KEY_10_r=0x1a,
    HDCP_KEY_11_r=0x1b,
    HDCP_KEY_12_r=0x1c,
    HDCP_KEY_13_r=0x1d,
    HDCP_KEY_14_r=0x1e,
    HDCP_KEY_15_r=0x1f,
    HDCP_KEY_16_r=0x0f,
}Ce_crypt_target_rpc;

typedef enum  HDCP_DECRYPT_MODE_rpc
{
   NOT_FOR_HDCP_r=0,
   TARGET_IS_HDCP_KEY_SRAM_r=(1<<14)

}Hdcp_decrypt_mode_rpc;

typedef struct ce_key_param_rpc
{
	Ce_key_rpc first_key_pos;
	Ce_crypt_target_rpc second_key_pos;
	Hdcp_decrypt_mode_rpc hdcp_mode ;
}Ce_key_param_rpc;

typedef struct ce_data_info_rpc
{
	Otp_param_rpc otp_info;
	Data_param_rpc data_info;
	Des_param_rpc des_aes_info;
	Ce_key_param_rpc key_info; 
}Ce_data_info_rpc;

typedef enum HDCP_KEY_SELECT_rpc
{
   CE_KEY_READ_r=0,
   HDCP_KEY_READ_r=1
}Hdcp_key_select_rpc;

typedef struct ce_debug_key_info_rpc
{
    Hdcp_key_select_rpc sel; 
    Uint32 buffer[4];  
    Uint32 len;      
}Ce_debug_key_info_rpc;

typedef struct ce_pos_status_param_rpc
{
    Uint32 pos;
    Uint32 status; 
}Ce_pos_status_param_rpc;

typedef enum ce_key_level_rpc
{
    SKIP_LEVEL_r = 0 ,
    ONE_LEVEL_r,
    TWO_LEVEL_r,
    THREE_LEVEL_r
}Ce_key_level_rpc;

typedef struct ce_found_free_pos_param_rpc
{
    Uint32 pos;
    Ce_key_level_rpc ce_key_level_r; 
    Uchar number;
    Ce_otp_key_sel_rpc root;  
}Ce_found_free_pos_param_rpc;

typedef struct ce_pvr_key_param_rpc
{
    Uchar input_addr;
    Uint32 second_pos;  
    Uint32 first_pos;   
}Ce_pvr_key_param_rpc;

/******************* dsc ********************/
typedef struct deEncrypt_config_rpc
{
	Uint32 do_encrypt;
	Uint32 dec_dev;                /*Decrypt device for stream*/
    Uchar Decrypt_Mode;
	Uint16 dec_dmx_id;
    Uint32 do_decrypt ;
	Uint32 enc_dev;                /*Encrypt device for stream*/
    Uchar Encrypt_Mode;
	Uint16 enc_dmx_id;
}DeEncrypt_config_rpc;

typedef enum SHA_MODE_rpc
{
SHA_SHA_1_r= 0,
SHA_SHA_224_r=(1<<29),
SHA_SHA_256_r=  (2<<29),
SHA_SHA_384_r = (3<<29),
SHA_SHA_512_r  =(4<<29),
}Sha_mode_rpc_r;

typedef enum SHA_DATA_SOURCE_rpc
{
    SHA_DATA_SOURCE_FROM_DRAM_r =0,
    SHA_DATA_SOURCE_FROM_FLASH_r =1,
}Sha_data_source_rpc;

typedef struct sha_init_param_rpc
{
    Sha_mode_rpc_r sha_work_mode; 
    Sha_data_source_rpc sha_data_source;
    Uint32 sha_buf;
}Sha_init_param_rpc;

typedef enum PARITY_MODE_rpc
{
    EVEN_PARITY_MODE_r =0,
    ODD_PARITY_MODE_r =1,
    AUTO_PARITY_MODE0_r = 2,  /*for ts*/
    AUTO_PARITY_MODE1_r =3,
    OTP_KEY_FROM_68_r = 4,
    OTP_KEY_FROM_6C_r = 5,
}Parity_mode_rpc;

typedef enum KEY_TYPE_rpc
{
    KEY_FROM_REG_r=0,
    KEY_FROM_SRAM_r=1,
    KEY_FROM_CRYPTO_r=2,
    KEY_FROM_OTP_r= 3,
}Key_type_rpc;

typedef enum KEY_MAP_MODE_rpc
{
   CSA_MODE_r=0,
   DES_MODE_r=0,
   CSA3_MODE_r=1,
   AES_128BITS_MODE_r=1,
   TDES_ABA_MODE_r=1,
   AES_192BITS_MODE_r=2,
   TDES_ABC_MODE_r=2,
   AES_256BITS_MODE_r=3
}Key_map_mode_rpc;

typedef enum DMA_MODE_rpc
{
    PURE_DATA_MODE_r=0,
    TS_MODE_r=(1<<24),
}Dma_mode_rpc;

typedef enum RESIDUE_BLOCK_rpc
{
    RESIDUE_BLOCK_IS_NO_HANDLE_r = 0,
    RESIDUE_BLOCK_IS_AS_ATSC_r = (1 << 12),
    RESIDUE_BLOCK_IS_HW_CTS_r = (2 << 12),
    RESIDUE_BLOCK_IS_RESERVED_r = (3 << 12),
}Residue_block_rpc;

typedef enum WORK_MODE_rpc
{
    WORK_MODE_IS_CBC_r=  0,
    WORK_MODE_IS_ECB_r =   (1<<4),
    WORK_MODE_IS_OFB_r=  (2<<4),
    WORK_MODE_IS_CFB_r  =(3<<4),   
    WORK_MODE_IS_CTR_r  =(4<<4),  
}Work_mode_rpc;

typedef struct aes_init_param_rpc 
{
    Parity_mode_rpc parity_mode;    
    Key_type_rpc key_from;
    Uint32 scramble_control;
    Key_map_mode_rpc key_mode;
    Uint32 stream_id; 
    Dma_mode_rpc dma_mode;
    Residue_block_rpc  residue_mode;
    Work_mode_rpc work_mode;
    Uint32 cbc_cts_enable ;  
}Aes_init_param_rpc;

typedef struct des_init_param_rpc 
{
    Parity_mode_rpc parity_mode;    
    Key_type_rpc key_from;
    Uint32 scramble_control;
    Key_map_mode_rpc key_mode;
    Uint32 stream_id; 
    Dma_mode_rpc dma_mode;
    Residue_block_rpc  residue_mode;
    Work_mode_rpc work_mode;
    Uint32 cbc_cts_enable ;  
}Des_init_param_rpc;

typedef struct pid_param_rpc
{  
   Uint32 dmx_id ;
   Uint16 pid;
   Uint16 pos;
   Uchar key_addr;
}Pid_param_rpc;

typedef enum CSA_VERSION_rpc
{
    CSA1_r=1,
    CSA2_r=0,
    CSA3_r=2
}Csa_version_rpc;

typedef struct csa_init_param_rpc 
{
    Csa_version_rpc version;
    Dma_mode_rpc dma_mode;
    Uint32 Dcw[4];
    Uint32 pes_en;  

    Parity_mode_rpc  parity_mode;    
    Key_type_rpc key_from;
    Uint32 scramble_control;
    Uint32 stream_id;
    
}Csa_init_param_rpc;

typedef struct Dsc_pvr_key_param_rpc
{
	Uint32 input_addr;
    Uint32 valid_key_num;
    Uint32 current_key_num;
    Uint32 pvr_key_length;
	Uchar pvr_user_key_pos;
    Uint32 total_quantum_number; 
    Uint32 current_quantum_number;
    Uint32 ts_packet_number;
    Uchar pvr_key_change_enable;
    Uint16 stream_id;
}Dsc_pvr_key_param_rpc;

typedef struct AES_256Bit_KEY_rpc 
{
    Uchar even_key[32];
    Uchar odd_key[32];
}Aes_256bit_key_rpc;

typedef struct CSA3_KEY_rpc
{
   Uchar OddKey[16];
   Uchar EvenKey[16];
}Csa3_key_rpc;

typedef struct  DES_192BITS_KEY_INFO_rpc
{
   Uchar oddKey[24];
   Uchar EvenKey[24];
}Des_192bits_key_info_rpc;

typedef struct aes_iv_info_rpc
{
  Uchar even_iv[16];
  Uchar odd_iv[16];
}Aes_iv_info_rpc;

typedef struct des_iv_info_rpc
{
  Uchar even_iv[8];
  Uchar odd_iv[8];
}Des_iv_info_rpc;

typedef struct key_param_rpc
{
    Uint32 handle;
    Uint16 *pid_list;
    Uint16 pid_len;  
    void *p_aes_key_info;
    void *p_csa_key_info;
    void *p_des_key_info;
    Uint32 key_length;
    void *p_aes_iv_info;
    void *p_des_iv_info;
    Uint16 stream_id;
    
    Uchar *init_vector;
    Uchar *ctr_counter;
    Uchar force_mode;
    Uchar pos ;
    Uchar no_even;
    Uchar no_odd;
    Uchar not_refresh_iv;    
}Key_param_rpc;

typedef struct trng_data_rpc
{
    Uchar data[128];
}Trng_data_rpc;

typedef struct sha_hash_rpc
{
    Uchar hash[64];
}Sha_hash_rpc;


/*************** dis ***************/
typedef struct VP_Feature_Config_rpc
{
	Bool bOsdMulitLayer;
	Bool bMHEG5Enable;
	Bool bAvoidMosaicByFreezScr;
	Bool bSupportExtraWin;
	Bool bOvershootSolution;
	Bool bP2NDisableMAF;
	Bool bADPCMEnable;
	Uint32 pMPGetMemInfo;	
	Uint32	pSrcAspRatioChange_CallBack;
}Vp_feature_config_rpc;

typedef struct tve_adjust_data_rpc
{
	Bool valid;
	Uint32 value;
}Tve_adjust_data_rpc;




typedef struct Tve_Feature_Config_rpc
{
	Uint32 config;
    
    Uchar type_tve_adj;
    Uchar sys_tve_adj;
    Uint32 value_tve_adj;
    //struct tve_adjust *tve_adjust;

	Uchar type_tve_tbl;
	Tve_adjust_data_rpc tve_data_tbl[8];  
	//struct tve_adjust_tbl *tve_tbl;
	
	Uint32 index_tve_tbl_all;
	Uint32 index_tve_tbl_all_1;
	Uint32 val_tve_tbl_all;
    //T_TVE_ADJUST_TABLE *tve_tbl_all;

    Uchar type_tve_adj_adv;
    Uchar sys_tve_adj_adv;
    Uint32 value_tve_adj_adv;    
	//struct tve_adjust *tve_adjust_adv;
}Tve_feature_config_rpc;

/*
typedef struct Tve_Feature_Config_rpc
{
	Uint32 config;
	Uint32 tve_adjust;
	Uint32 tve_tbl;
       Uint32 tve_tbl_all;
	Uint32 tve_adjust_adv;
}Tve_feature_config_rpc;
*/


typedef struct OSD_AF_PAR_rpc
{
	Uchar id;
	Uchar vd;
	Uchar af;
	Uchar res;
}Osd_af_par_rpc;

typedef struct _OSD_DRIVER_CONFIG_rpc
{
	Uint32 uMemBase;        
	Uint32 uMemSize;		
							
	Uchar bStaticBlock;		
	Uchar bDirectDraw;
	Uchar bCacheable;

	Uchar bVFilterEnable;   		
	Uchar bP2NScaleInNormalPlay;
	Uchar bP2NScaleInSubtitlePlay;
	Uint16 uDViewScaleRatio[2][2];
	Osd_af_par_rpc af_par[4];
	Uint32 uSDMemBase; 
	Uint32 uSDMemSize;	

}Osd_driver_config_rpc;

typedef struct vp_source_info_rpc
{
	Uint32 src_module_devide_handle;
	//struct source_callback	src_callback;
    Uint32 handler;
	Uint32 request_callback;
	Uint32 release_callback;
	Uint32 vblanking_callback;
    
	Uchar src_path_index;
	Uchar attach_source_index;
}Vp_source_info_rpc;

typedef struct vp_src_dst_rect_rpc
{
	Rect_rpc src_rect;
	Rect_rpc dst_rect;
}Vp_src_dst_rect_rpc;

typedef struct vp_win_config_rpc
{
	Uchar source_index;//changed for s3601-6/5
	Uint32	display_layer;

	Uint32 src_module_devide_handle;
    
    Uint32 handler;
	Uint32 request_callback;
	Uint32 release_callback;
	Uint32 vblanking_callback;
	//struct source_callback	src_callback;
	
	Vp_src_dst_rect_rpc rect;	
}Vp_win_config_rpc;

typedef struct vp_win_config_para_rpc
{
	Uchar source_number;
	Vp_source_info_rpc source_info[4];

	Uchar control_source_index;
	Uchar mainwin_source_index;

	Uchar window_number;
	Vp_win_config_rpc window_parameter[4];
}Vp_win_config_para_rpc;

typedef struct vpo_io_ttx_rpc
{
        Uchar LineAddr;
        Uchar Addr;
        Uchar Data;
}Vpo_io_ttx_rpc;

typedef struct vpo_io_cc_rpc
{
		Uchar FieldParity;
		Uint16 Data;
}Vpo_io_cc_rpc;

typedef struct DacIndex_rpc
{
	Uchar uDacFirst;
	Uchar uDacSecond;
	Uchar uDacThird;   
}Dacindex_rpc;

typedef struct VP_DacInfo_rpc
{
	Bool					bEnable;	
	Dacindex_rpc			tDacIndex;
	Uint32			        eVGAMode;
	Bool					bProgressive;
}Vp_dacinfo_rpc;

typedef struct vp_io_reg_dac_para_rpc
{
	Uint32 eDacType;
	Vp_dacinfo_rpc DacInfo;
}Vp_io_reg_dac_para_rpc;

typedef struct VP_InitInfo_rpc
{
	Ycbcrcolor_rpc		tInitColor;
	//set advanced control
	Uchar 					bBrightnessValue;
	Bool 					fBrightnessValueSign;
	Uint16 					wContrastValue;
	Bool 					fContrastSign;
    
	Uint16 					wSaturationValue;
	Bool					fSaturationValueSign;
	Uint16					wSharpness;
	Bool 					fSharpnessSign;
    
	Uint16 					wHueSin;
	Bool 					fHueSinSign;
	Uint16					wHueCos;
	Bool					fHueCosSign;

	Int32 			eTVAspect;
	Int32 		eDisplayMode;
	Uchar 					uNonlinearChangePoint;	//Increment change point for nonlinear 16:9 to 4:3 conversion
	Uchar 					uPanScanOffset;			//Offset in source picture for Pan & scan mode

	Vp_dacinfo_rpc		pDacConfig[23];
	Int32 			eTVSys;

	Bool						bWinOnOff;
	Uchar						uWinMode;
	Rect_rpc					tSrcRect;
	Rect_rpc					DstRect;

	Mpsource_callback_rpc	tMPCallBack;
	Pipsource_callback_rpc	tPIPCallBack;
	Uint32			pSrcChange_CallBack;

       Uchar						device_priority;//changed for s3601-6/5
	Bool bCCIR656Enable;	
}Vp_initinfo_rpc;


typedef struct vpo_io_set_parameter_rpc
{
	Uchar	changed_flag;
	Bool	fetch_mode_api_en;
	Int32	fetch_mode;
	Bool	dit_enable;
	Bool	vt_enable;
	Bool	vertical_2tap;
	Bool	edge_preserve_enable;
}Vpo_io_set_parameter_rpc;

typedef struct vpo_io_video_enhance_rpc
{
	Uchar	changed_flag;
	Uint16   grade;
}Vpo_io_video_enhance_rpc;


typedef struct vpo_io_get_info_rpc
{
	Uint32 display_index;
	Uint32	api_act;
	Bool	bprogressive;
	Uint32	tvsys;
    
	Bool	fetch_mode_api_en;
	Uint32	fetch_mode;
	Bool	dit_enable;
	Bool	vt_enable;
    
	Bool	vertical_2tap;
	Bool	edge_preserve_enable;
	Uint16	source_width;
	Uint16	source_height;
    
	Uint16    des_width;
	Uint16	des_height;
	Bool	preframe_enable;
	Bool	gma1_onoff;
    
	Uint32	reg90;
}Vpo_io_get_info_rpc;


typedef struct de2Hdmi_video_infor_rpc
{
	Uint32			    tv_mode;
	Uint16					    width;
	Uint16					    height;
	Uint32				    format;
    
	Bool					    scan_mode;
	Bool					    afd_present;
	Uint32			        output_aspect_ratio;
	Uchar					    active_format_aspect_ratio;
    
	Uint32	    av_chg_ste;
	Uint32      ext_video_format;	//add for 3d function
	Uint32      _4K_VIC_3D_structure;
	Uint32		ext_data;

}De2Hdmi_video_infor_rpc;


typedef struct vpo_io_cgms_info_rpc
{
	Uchar cgms;
	Uchar aps;
}Vpo_io_cgms_info_rpc;


typedef struct vp_io_afd_para_rpc
{
	Bool bSwscaleAfd;
	Int32  afd_solution;
	Int32  protect_mode_enable;
}Vp_io_afd_para_rpc;

typedef struct vpo_io_get_picture_info_rpc
{
    Uchar   de_index;
    Uchar   sw_hw;
    Uchar   status;
    Uint32  top_y;
    
    Uint32  top_c;
    Uint32  maf_buffer;
    Uint32  y_buf_size;
    Uint32  c_buf_size;
    
    Uint32  maf_buf_size;
    Uint32  reserved[10];
}Vpo_io_get_picture_info_rpc;

typedef struct vpo_osd_show_time_rpc
{
    Uchar  show_on_off;     // true or false
    Uchar  layer_id;        // 0 or 1
    Uchar  reserved0;
    
    Uchar  reserved1;
    Uint32 time_in_ms;      // in ms
} Vpo_osd_show_time_rpc;


typedef struct vpo_io_cutline_pars_rpc
{
    	Uchar top_bottom;             //0: cut line from top 1: cut line from bottom
    	Uchar cut_line_number;
}Vpo_io_cutline_pars_rpc;


typedef struct alifbio_3d_pars_rpc
{
    Int32 display_3d_enable;
    Int32 side_by_side;
    Int32 top_and_bottom;
    Int32 display_2d_to_3d;
    
    Int32 depth_2d_to_3d;
    Int32 mode_2d_to_3d;
    Int32 red_blue;
   // Int32 mvc_flag;
    Int32 eInputFormat;
}Alifbio_3d_pars_rpc;

typedef struct alifbio_3d_enhance_rpc
{
    Int32 enable_3d_enhance;
    Int32 use_enhance_default;
    Int32 set_3d_enhance;
    Uchar eye_protect_shift;
	Int32 user_true3d_enhance;
	Int32 user_true3d_constant_shift;
	Int32 ver_gradient_ratio;
	Int32 hor_gradient_ratio;
	Int32 pop_for_reduction_ratio;
	Int32 parallax_sign_bias;
}Alifbio_3d_enhance_rpc;


