#ifndef _DB_NODE_H_
#define _DB_NODE_H_


//@@@@tobe delete
enum {
	LNB_CTRL_STD				= 0x00,	/* standard non dual-LNB	*/
	LNB_CTRL_POL				= 0x10,	/* dual LNB controlled by polar	*/
	LNB_CTRL_22K				= 0x20,	/* dual LNB controlled by 22k	*/
	LNB_CTRL_UNICABLE			= 0x30,	/* dual LNB controlled from unicable */
	LNB_CTRL_RESERVED			= 0x70	/* reserved control method	*/
};


/******************************************************************************
此头文件只包含与DB NODE定义有关的内容

******************************************************************************/

#define INVALID_POS_NUM	0xFFFF

#define MAX_SERVICE_NAME_LENGTH		17
#define MAX_SATELLITE_NAME_LENGTH		17

/*max audio pid cnt for earch prog node*/
#define MAX_AUDIO_CNT	8
/*max bouquet id cnt for earch prog node*/
#define MAX_BOUQUET_CNT 8
/*max cas cnt for earch prog node*/
#define MAX_CAS_CNT	4

/*audio channel define for prog node*/
#define AUDIO_DEFAULT_VOLUME		66
#define AUDIO_CH_L				0x00
#define AUDIO_CH_R				0x01
#define AUDIO_CH_STEREO		0x02
#define AUDIO_CH_MONO			0x03



/******************************************************************************
db node define
每个结构定义分为三部分:ID+定长数据+变长数据
ID部分存储到ROM时会压缩为4byte，
定长数据长度由XXX_NODE_FIX_LEN定义，数据定义注意字节对齐，
变长数据在定长数据之后，每个子部分都是名字长度或数据个数+数据的形式。

修改node结构定义的规则是：对于定长数据部分和变长数据部分，
分别只能在尾部添加新的数据域，而不能在中间插入，也不能
删除原来的数据域。

*******************************************************************************/

/*fixed data len for sat node*/
#define S_NODE_FIX_LEN	24///2
/*fixed data len for tp node*/
#define T_NODE_FIX_LEN	36//16
/*fixed data len for prog node*/
#define P_NODE_FIX_LEN	40 ///26

typedef struct antena_t
{
	UINT8 lnb_power			: 1;
	UINT8 lnb_type			: 7;

	UINT8 pol				: 2;
	UINT8 k22				: 1;
	UINT8 v12				: 1;
	UINT8 toneburst			: 2;
	UINT8 unicable_pos		: 1;
	UINT8 reserve_1		: 1;            //2

	UINT16 lnb_low;
	UINT16 lnb_high;                    //4

	UINT8 DiSEqC_type		: 4;
	UINT8 DiSEqC_port		: 4;

	UINT8 DiSEqC11_type		: 4;
	UINT8 DiSEqC11_port		: 4;

	UINT16 positioner_type	: 3;
	UINT16 position			: 8;
	UINT16 reserve_2		: 5;        //4
}ANTENA;

typedef struct
{
	/*ID*/
	UINT16 sat_id;
	UINT16 reserve_id;              //4

//start fix len
	UINT16 sat_orbit;               //2

	UINT16 selected_flag	: 1;
	UINT16 tuner1_valid		: 1;
	UINT16 tuner2_valid		: 1;
	UINT16 sat2ip_flag		: 1;     //2   
	UINT16 reserve_1		: 12;     //2   

	//tuner1 antenna setting*****
	UINT8 lnb_power			: 1;
	UINT8 lnb_type			: 7;

	UINT8 pol				: 2;
	UINT8 k22				: 1;
	UINT8 v12				: 1;
	UINT8 toneburst			: 2;
	UINT8 unicable_pos		: 1;
	UINT8 reserve_2			: 1;       //2

	UINT16 lnb_low;
	UINT16 lnb_high;                    //4

	UINT8 DiSEqC_type		: 4;
	UINT8 DiSEqC_port 		: 4;
	
	UINT8 DiSEqC11_type		: 4;
	UINT8 DiSEqC11_port 	: 4;
		
	UINT16 positioner_type	: 3;	
	UINT16 position			: 8;
	UINT16 reserve_3		: 5;        //4////12
	//*************************
	
	ANTENA tuner2_antena;               //10
 
	//end of fix len 24
	
	UINT8 name_len;
	UINT16 sat_name[MAX_SATELLITE_NAME_LENGTH + 1];
}S_NODE;


typedef struct
{
	/*ID*/
	UINT16 sat_id;
	UINT32 tp_id;

	/*fix len data*/
	UINT32 frq;
	UINT32 sym;

	UINT16 pol					: 2;
	UINT16 FEC_inner			: 4; 	//T: 0:1/2, 1:2/3, 2:3/4, 3:5/6, 4:7/8  //T2: 5:3/5, 6:4/5 //0xF:unknown
	UINT16 universal_22k_option	: 1;
	UINT16 Big5_indicator		: 1; 
	UINT16 ft_type				: 2;//front end type,check lib_frontend.h  
	UINT16 inverse				: 1;
	UINT16 band_type			: 1;
	UINT16 priority			    : 2;    //for DVB-T HIERARCHY mode
	UINT16 hier				    : 2;
///10
	UINT16 preset_flag			: 2;
	UINT16 usage_status			: 1;
	UINT16 nit_pid				:13;
		
	UINT16 t_s_id;
	UINT16 network_id;	//original_network_id

	UINT16 net_id;    //network_id
	UINT16 t2_signal			: 1;    //0:DVB-T signal, 1:DVB-T2 signal. (when ft_type==FRONTEND_TYPE_T)
	UINT16 plp_index            : 8;
	UINT16 nvod_flg		: 1;
	UINT16 reserved			    : 6;
////20    
	UINT8 sdt_version;
	UINT16 t2_system_id;
	UINT8 plp_id;

	UINT8 guard_interval; 	//4: 1/4, 8: 1/8, 16: 1/16, 32:1/32  //T2: 128:1/128, (19+128):19/128, 19:19/256, //0xFF:unknown
	UINT8 FFT;	//2:2k, 8:8k //T2: 1:1k, 4:4k, 16:16k, 32:32k, //0xFF:unknown
	UINT8 modulation	;	//2:DQPSK 4:QPSK, 16:16 QAM, 64:64 QAM //T2: (64+1):256 QAM, //0xFF:unknown
	UINT8 bandwidth;

    //SUPPORT_TP_QUALITY
	UINT32 intensity			:16;
	UINT32 quality				: 8;
    #ifdef AUTO_UPDATE_TPINFO_SUPPORT
	UINT32 crc_h8   			: 8;
    #else
	UINT32 reserved2			: 8;
    #endif
//32	
	UINT32 remote_control_key_id: 8;
    #ifdef AUTO_UPDATE_TPINFO_SUPPORT
    UINT32 crc_t24  			:24;
    #else
	UINT32 reserved3			:24;
    #endif
	/*end of fix len data   len = 36 */

	/*variable len data*/
	UINT8 name_len;
	UINT16 net_name[MAX_SERVICE_NAME_LENGTH + 1];
} T_NODE;



typedef struct program
{
	/*ID*/
	UINT16 sat_id;
	UINT32 tp_id;
	UINT32 prog_id;


	/*fix len data*/
	//prog feature
	UINT32 level				: 2;
	UINT32 preset_flag 			: 2;
	UINT32 av_flag				: 1;
	UINT32 ca_mode				: 1;
	UINT32 video_pid			:13;
	UINT32 pcr_pid			:13;
	
	//@@@@av_flag tobe delete
	UINT32 prog_number		:16;
	UINT32 pmt_pid			:13;
	UINT32 tuner1_valid		: 1;
	UINT32 tuner2_valid		: 1;
	UINT32 h264_flag    		: 1;

	//@@@@av_flag tobe delete

	//favorite group, each bit for one group
	UINT32 fav_grp;
//12
	//video stream type
	UINT8 video_type;

	UINT16 pmt_version		: 5;
	UINT16 service_type		: 8;
	UINT16 audio_channel   	: 2;
	UINT16 audio_select		: 1;
	

	//UINT16 cur_audio			: 4;
	UINT16 user_modified_flag: 1;
	UINT16 lock_flag	    		: 1;
	UINT16 provider_lock		:1;
	UINT16 skip_flag			: 1;
	UINT16 audio_volume		: 8;
	UINT16 reserve_2			: 4;

	//@@@@tobe delete

	UINT8 mpeg4_flag		: 1;
	UINT8 shunning_protected	: 1;
	//logic channel number
	UINT8 mheg5_exist		: 1;  
	UINT8  num_sel_flag    	: 1;
	UINT8  visible_flag 		: 1;
	UINT8 LCN_true			: 1;
	UINT8 reserve			: 2;
///18	
	UINT16 orig_LCN;
	UINT16 LCN;
	UINT16 default_index; //for returning to default sorting


	UINT32 user_order;                      //4
	//@@@@tobe delete
	UINT16 teletext_pid;
	UINT16 subtitle_pid;

	
	UINT16 cur_audio			: 5;	/* any new fixed param shall added before cur_audio!!! */
	UINT16 hd_lcn_ture		: 1;
	UINT16 reserve_3		: 10;
	UINT16 hd_lcn;

	UINT16 nvod_ref_sid;
	UINT16 logical_channel_num;
	/*end of fix len data len = 36*/

	
	/*variable len data*/
	//bouquet id
	UINT8 bouquet_cnt;
	UINT16 bouquet_id[MAX_BOUQUET_CNT];

	UINT8 cas_count;
	UINT16 cas_sysid[MAX_CAS_CNT];

	UINT8 audio_count;
	UINT16 audio_pid[MAX_AUDIO_CNT];
	UINT16 audio_lang[MAX_AUDIO_CNT];
	//audio stream type
	UINT16 audio_type[MAX_AUDIO_CNT];

	UINT8 name_len;
	UINT16 service_name[MAX_SERVICE_NAME_LENGTH + 1];

	//provider name
	UINT8 prd_name_len;
	UINT16 service_provider_name[MAX_SERVICE_NAME_LENGTH + 1];
	
	UINT8 audio_com_tag[MAX_AUDIO_CNT];                             //20
}P_NODE;


#endif

