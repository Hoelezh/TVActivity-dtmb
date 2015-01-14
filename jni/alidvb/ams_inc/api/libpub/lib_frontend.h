#ifndef _LIB_FRONTEND_H_
#define _LIB_FRONTEND_H_

#include <api/libtsi/p_search.h>

/*! @addtogroup ALi中间件
 *  @{
 */

/*! @addtogroup AMSCC
 *  @{
 */

/*front end*/
//type
#define FRONTEND_TYPE_S    0x00
#define FRONTEND_TYPE_C    0x01
#define FRONTEND_TYPE_T    0x02

//! @struct ft_antenna
//! @brief front end(antenna+nim)。
struct ft_antenna
{
    /*if no antenna setting, set this field as 0*/
    UINT8 antenna_enable;
    /*if antenna_enable=1,give the settings*/
    UINT8 lnb_type;
    UINT8	positioner_type;
    UINT8 position;
    UINT32 lnb_high;
    UINT32 lnb_low;
    UINT32 longitude;
        
    UINT8 pol; 
    UINT8	DiSEqC_type;
    UINT8 DiSEqC_port;
    UINT8 DiSEqC11_type;
    UINT8 DiSEqC11_port;
    UINT8	k22;
    UINT8 v12;
    UINT8 toneburst;
    /*add for Unicable LNB*/ 
    UINT8   unicable_pos;   //!< position:A/B(value:0/1)
    UINT8   unicable_ub;    //!< user band(slot) or SCR channel:1~8(value:0~7)
    UINT16  unicable_freq;  //!< centre frequency of user band:1210,1420,...
};

/*only include params related to tuning*/
union ft_xpond
{
    struct 
    {
        UINT8 type;
    } common;
    struct
    {
        UINT8 type;
        UINT8 modulation;
        UINT8 pol;
        UINT8 fec_inner;
        UINT32 frq;
        UINT32 sym;
        UINT32 tp_id;
    } s_info;
    struct
    {
        UINT8 type;
        UINT8 modulation;
        UINT8 fec_inner;
        UINT8 fec_outer;
        UINT32 frq;
        UINT32 sym;
        UINT32 tp_id;
    } c_info;   
    struct
    {
        UINT8 type;
        UINT8 modulation;
        UINT8 fft_mode;
        UINT8 guard_intl;
        UINT8 fec;
        UINT8 usage_type;
        UINT8 inverse;
        UINT8 priority;
        UINT32 band_width;
        UINT32 frq;
        UINT32 sym;
        UINT32 tp_id;
    } t_info;
};

//! @struct ft_ts_route
//! @brief front ts route。
struct ft_ts_route
{
    UINT8 ts_route_enable;
    UINT8 tsiid; //!< TSI_SPI_0, 1... or TSI_SSI_0, 1... etc
    UINT8 tsi_mode;
    UINT8 ts_id; //!< TSI_TS_A or TSI_TS_B
    
    UINT8 ci_enable;
//    UINT8 ci_bypass;
//    UINT8 ci_slot;
    UINT8 ci_slot_mask;	//!< support multi slot

    UINT8 dmx_id;  //!< TSI_DMX_0, 1 or 2
};

//! @struct ft_frontend
//! @brief frontend。
struct ft_frontend
{
    struct nim_device *nim;
    struct ft_antenna antenna;
    union ft_xpond xpond;
    struct ft_ts_route ts_route;
};


/**************************************************************/
/*                channel change struct                       */
/**************************************************************/
//! @struct cc_logo_info
//! @brief channel change logo info。
struct cc_logo_info
{
    UINT8 *addr;
    UINT32 size;
//    struct sto_device *sto; 
};

//! @struct cc_es_info
//! @brief channel change es info, only package info needed by decoder and dmx。
struct cc_es_info
{
	UINT32 prog_id;
	UINT16 sat_id;
	UINT32 tp_id;
	UINT16 service_id;
	UINT16 service_type;

	UINT16 pcr_pid: 13;
	UINT8 v_type; //!< video stream type
	UINT8 a_type; //!< audio stream type defined in meadiatypes.h
	UINT16 v_pid: 13;
	UINT8 a_ch: 2; //!< audio channel defined in PNODE
	UINT8 a_volumn;
	UINT16 a_pid: 13;
	UINT8 spdif_enable: 1;
	UINT16 ttx_pid: 13;
	UINT16 subt_pid: 13;
//	UINT8 blk_enable: 1;

	UINT8 close_vpo_layer; //!< if need close vpo, layer VPO_LAYER_M or VPO_LAYER_PIP
	UINT8 audio_no_act: 1; //!< used for PIP change channel
	UINT8 dmx_2play: 1;
	UINT8 dynamic_pid_chgch: 1;
	UINT8 background_play: 1; //!< used for dual-record timer
	UINT8 not_oprate_subt_ttx: 1;
//	UINT8 sim_onoff_enable: 1; //!<  Enable or Disable SI Monitor On & Off
	UINT32 sim_id; //!< si monitor id
#ifdef AUDIO_DESCRIPTION_SUPPORT
	UINT16 ad_pid;
#endif

};

//! @struct cc_device_list
//! @brief channel change device list。
struct cc_device_list
{
    	struct vpo_device *vpo;
    	struct vdec_device *vdec;
		struct vdec_device *vdec_stop;
    	struct deca_device *deca;
    	struct snd_device *snd_dev;
    	struct dmx_device *dmx;
	struct vdec_device *vdec_hdtv;
	struct avsync_device *avsync;
};

//! @struct cc_param
//! @brief channel change参数。
struct cc_param
{
    struct cc_es_info es;
    struct cc_device_list dev_list;
	UINT32 param;
};


/**************************************************************/
/*               ts route management struct                   */
/**************************************************************/
#define CC_MAX_TS_ROUTE_NUM	5

enum
{
	TS_ROUTE_STATUS_PLAY 		= 1<<0,
	TS_ROUTE_STATUS_RECORD 	= 1<<1,
	TS_ROUTE_STATUS_TMS	 	= 1<<2,
	TS_ROUTE_STATUS_PLAYACK 	= 1<<3,
	
	TS_ROUTE_STATUS_USE_CI_PATCH = 1<<7, // the route using CI patch
};

//! @enum ts_route_type
//! @brief TS route 类型。
enum ts_route_type
{
	TS_ROUTE_MAIN_PLAY = 0,
	TS_ROUTE_PIP_PLAY,
	TS_ROUTE_BACKGROUND,
	TS_ROUTE_PLAYBACK,
};

#define DEV_DMX_SIM_CNT 10

//! @struct dmx_sim
//! @brief demux sim。
struct dmx_sim{
	UINT8 used;
	UINT8 sim_type;		
	UINT16 sim_pid;
	UINT32 sim_id;
	UINT32 channel_id;
	UINT32 callback;
};

//! @struct ts_route_info
//! @brief ts route info。
struct ts_route_info
{
	UINT8 enable;
	UINT32 id; //!< reserved
	enum ts_route_type type;
	UINT8 is_recording;
	UINT8 dmx_id; //!< TSI_DMX_0, 1 or 2, if dmx2 don't care frontend devices! 
	UINT8 dmx_slot_id; //!< 0 or 1
	UINT8 nim_id; //!< 0: tuner1; 1: tuner2
	UINT8 tsi_id; //!< TSI_SPI_QPSK  or TSI_SPI_TSG or TSI_SSI_0
	UINT8 ci_mode; //!< 0: don't care or 1: serial or 2: parallel
	UINT8 ci_num;
	UINT8 cia_included;
	UINT8 cia_used;
	UINT8 cib_included;
	UINT8 cib_used;
	UINT8 ca_info_enable;
	UINT8 ca_slot_ready[2];	//!< num means how much figure matched between cam and pmt 
	enum ts_route_type ca_info_type;
	UINT8	ca_count;
	CA_INFO ca_info[P_MAX_CA_NUM];
	UINT8 ts_id_recover; //!< for 2-CI control, when stop TSG playback, need recover background ts_id
	UINT8 ts_id; //!< TSI_TS_A or TSI_TS_B   there are some default rule between TS and CI
	UINT8 vdec_id;
	UINT8 vpo_id; //!< 0: full screen vpo; 1: pip vpo
	UINT8 state; //!< 1-bit to 1-state
	UINT32 tp_id;
	UINT32 prog_id;
	UINT8 stream_av_mode; //!< 1 TV 0 Radio
	UINT8 stream_ca_mode;
	UINT8 screen_mode; //!< 0: background or 1: main or 2: pip
	UINT8 flag_lock;
	UINT8 flag_scramble;
	UINT8 sim_num;
 	struct dmx_sim dmx_sim_info[DEV_DMX_SIM_CNT>>1];
};

struct nim_config
{
    struct ft_antenna antenna;
    union ft_xpond xpond;
};
struct dmx_config
{
	UINT32 tp_id;
 	struct dmx_sim dmx_sim_info[DEV_DMX_SIM_CNT];
};

/**************************************************************/
/*                    function declaration                    */
/**************************************************************/
//#define frontend_lnb_22k_ctl(plnb)	((LNB_CTRL_22K == (plnb)->lnb_type) ? 1:0)

void frontend_set_unicable(struct nim_device *nim,struct ft_antenna* antenna,union ft_xpond* xpond);

/*!
@brief 设置前端NIM。
@details 设置前端NIM。
@param[in] nim 前端NIM设备的句柄。
@param[in] xpond union ft_xpond在lib_frondend.h中定义。Cable只用到了其Cable类型的参数，一般这些参数都是直接从数据库的T_NODE得到。
@param[in] timeout 设置完NIM，等待其lock的timeout。如果为0，表示不等待其lock。一般如果要等待其lock的话，置为100-200ms左右即可，但是跟具体的前端性能有关。
@retval 0 设置成功并且信号lock
@retval 1 信号还没有lock
*/
UINT32 frontend_set_nim(struct nim_device *nim, struct ft_antenna* antenna, union ft_xpond* xpond, UINT32 timeout);

void frontend_set_antenna(struct nim_device *nim, struct ft_antenna* antenna, 
    union ft_xpond* xpond, UINT8 force_set);

void frontend_tuning(struct nim_device *nim, struct ft_antenna* antenna, 
    union ft_xpond* xpond, UINT8 force_set);

void frontend_set_ts_route(struct nim_device *nim, struct ft_ts_route *route);

BOOL frontend_check_nim_param(struct nim_device *nim, struct ft_antenna* antenna,union ft_xpond* xpond);

UINT32 ts_route_create(struct ts_route_info *ts_route);
RET_CODE ts_route_delete(UINT32 id);
RET_CODE ts_route_get_by_id(UINT32 id, struct ts_route_info *ts_route);
RET_CODE ts_route_get_by_type(UINT32 type, UINT32 *ts_route_id, struct ts_route_info *ts_route);
RET_CODE ts_route_get_record(UINT32 prog_id, UINT32 *ts_route_id, struct ts_route_info *ts_route);
RET_CODE ts_route_update(UINT32 id, struct ts_route_info *ts_route);
INT16 ts_route_check_ci(UINT8 ci_id);
INT16 ts_route_check_ci_route(UINT8 ci_id, UINT8 *route_num, UINT16 *routes);
UINT8 ts_route_check_TS_by_dmx(UINT8 dmx_id);
void ts_route_check_dmx_route(UINT8 dmx_id, UINT8 *route_num, UINT16 *routes);
void chchg_set_local_position(double longtitude,double latitude);
void chchg_get_local_position(double *longtitude,double *latitude);
//typedef void (*v1318set_callback)(UINT32 v1318);
//static v1318set_callback l_v1318set_callback = NULL;
//void UIChChgSet1318VSetCB(v1318set_callback v1318setcb);
/*!
 * @}
 */

/*!
@}
*/

#endif

