/*========================================================================================
 *
 * Copyright (C) 2011 ALi Shanghai Corp.
 *
 * Description:
 *
 * History
 *
 *   Date	    Author		Comment
 *   ========	===========	========================================
 *
 *=========================================================================================*/

#ifndef __LIB_EPG_H__
#define  __LIB_EPG_H__

#include <adr_sys_config.h>
#include <api/libsi/si_tdt.h>

/*! @addtogroup ALi中间件
 *  @{
 */

typedef INT32 (*EitCallback) (UINT32  CbParam,//!<用户注册的回调参数。
                            INT32  ErrCode,//!<错误码。
                            UINT8  *SecBuf,//!<section数据的起始地址。
                            UINT32  SecLen);//!<section的长度。

/*! @addtogroup AMSEPG
 *  @{
 */

//! @enum COMPARE_MODE
//! @brief 	用于amsepg_del_service在需要删除service的时候，判断是删除等于一个节目列表里的节目的EPG，还是删除不等于一个节目列表的节目的EPG。
//! @see amsepg_del_service
enum COMPARE_MODE
{
	EQUAL,          //!< 删除等于一个节目列表里的节目的EPG
	NOT_EQUAL,      //!< 删除不等于一个节目列表的节目的EPG。
};

//! @enum EPG_NODE_STATUS
//! @brief 	Event Node的状态。
//! @details Event更新或者被删除的时候，会被置成,<b>EPG_NODE_DIRTY</b>状态。
//!   当有新的<b>Event</b>需要添加的时候，总是先从<b>EPG_NODE_FREE</b>列表顺序分配；当<b>EPG_NODE_FREE</b>列表被用完的时候，才会去查找EPG_NODE_DIRTY状态的Node并替换之。
//! @see struct EPG_DB_NODE
enum EPG_NODE_STATUS
{
	EPG_NODE_FREE	= 0,
	EPG_NODE_ACTIVE = 1,
	EPG_NODE_DIRTY	= 2, //!< event node deleted
};

//! @enum EPG_DB_EVENT_TYPE
//! @brief EPG模块通过callback传给应用层的消息类型。
//! @see typedef EIT_CALL_BACK
enum EPG_DB_EVENT_TYPE
{
	PRESENT_EVENT 	= 0,
	FOLLOWING_EVENT = 1,
	SCHEDULE_EVENT 	= 2,

	EPG_PF_VERSION_UPDATE = 101,
	EPG_SCH_VERSION_UPDATE,
	EPG_SERVICE_SECTION_HIT_ALL,
	EPG_SERVICE_NOT_EXIST,
	EPG_SERVICE_EXIST,
	EPG_TP_OVERFLOW,
	EPG_SERVICE_OVERFLOW,
	EPG_EVENT_OVERFLOW,
	EPG_MEM_OVERFLOW,
};

//! @struct TIME
//! @brief Event起始时间和持续时间的定义。
//! @see struct EPG_DB_NODE
struct TIME
{
	UINT8 hour: 5;		//!< 0-23
	UINT8 minute: 6;	//!< 0-59
	UINT8 second: 6;	//!< 0-59
} __attribute__((packed));

//! @struct EPG_DB_NODE
//! @brief EPG Event的定义。
struct EPG_DB_NODE
{
#ifdef EPG_MULTI_TP
	UINT32 tp_id;
#endif
	UINT16 service_id;
	UINT16 event_id;

#ifdef NVOD_FEATURE
	UINT16 ref_service_id;		//!< Add for NVOD time shifted event
	UINT16 ref_event_id;
#endif

	UINT8 tab_num: 4;		//!< Table_id & 0x0F

	UINT8 event_type: 2;		//!< see enum EPG_DB_EVENT_TYPE
	UINT8 status: 2;		//!< see enum EPG_NODE_STATUS

	UINT8  nibble: 4;		//!< Content descriptor: content_nibble1
#ifdef EPG_NIBBLE2_SUPPORT
	UINT8  nibble2: 4;		//!< Content descriptor: content_nibble2
#endif

#ifdef EPG_PARENTAL_SUPPORT
//	struct EPG_MULTI_RATING
//	{
//		UINT8 country_code[3];	//ISO 3166
		UINT8 rating: 4;		//!< 0-0xF, Parent Rating Descriptor: rating & 0x0F
//	} parental[1];
#endif

#ifdef EPG_COMPONENT_SUPPORT
	//!< video/audio stream componet type, see EN300468 "Component descriptor"
	struct STREAM_COMPONENT
	{
		UINT8 stream_content: 4;	//!< see Component descriptor
		UINT8 component_type;
	} stream_component[2];
#endif

	UINT16 mjd_num;
	struct TIME time;
	struct TIME duration;

	struct EPG_MULTI_LANG
	{
		UINT8 *text_char;	//!< [event name] + [short event text char] + [ext event text char]
		UINT16 text_length;
//		UINT8 lang_code[3];	//!< ISO_639_language_code of event name, etc.
		UINT16 lang_code2;	//!< converted from 3 byte of ISO_639_language_code
	}lang[EPG_LANGUAGE_COUNT];
	/*
	{
		UINT8 event_name_length;
		UINT8 event_name[0];
		UINT8 short_text_length;
		UINT8 short_text_char[0];
		UINT16 extend_text_length;
		UINT8 extend_text_char[0];
	}
	*/
} __attribute__((packed));

//! @typedef eit_event_info_t
//! @brief 旧的code还在使用eit_event_info_t结构定义。
typedef struct EPG_DB_NODE eit_event_info_t;

//! @typedef epg_db_filter_t
//! @brief EPG View的过滤函数的定义。
//! @see amsepg_create_view
typedef BOOL (*epg_db_filter_t)(struct EPG_DB_NODE *, void *);

//! @struct epg_service_t
//! @brief Active Service的定义。
//! @see amsepg_set_active_service
typedef struct ACTIVE_SERVICE_INFO
{
	UINT32 tp_id;
	UINT16 service_id;

} epg_service_t;

//! @typedef EIT_CALL_BACK
//! @brief EPG模块Callback的定义。
//! @see struct epg_config_t
typedef void (*EIT_CALL_BACK)(UINT32 tp_id, UINT16 service_id, enum EPG_DB_EVENT_TYPE event_type);

//! @enum epg_eit_mode_e
//! @brief EIT Filter的配置选项，缺省配置是在amsepg_on的时候，拿当前频点所有节目的PF和SCH表的数据。
//! @see amsepg_on
typedef enum
{
	EIT_SINGLE_SERVICE = 0x01,		//!< single service id's mask/value enabled
	EIT_OTHER_PF_SCH   = 0x02,		//!< Table ID: 0x4F, 0x60~0x60+EPG_SCHEDULE_TABLE_ID_NUM-1 enabled

} epg_eit_mode_e;

//! @struct epg_config_t
//! @brief 应用层调用amsepg_init()初始化EPG模块时，传入的EPG模块的配置参数。
//! @see amsepg_init
typedef struct
{
	UINT16 max_tp_count;		//!< TP(即频点)的最大个数，一般cable的频率范围是48-859MHz，带宽8M，所以最多也就(859-48)/8+1=103个频点。这个配置项也可以参考数据库的TP个数配置。
	UINT16 max_service_count;	//!< 节目的最大个数，一般300-500个，包括TV/Radio/NVOD等等所有类型的节目。
	UINT32 max_event_count;		/*!<  最大的EPG Event的个数。这个需要根据各个地方的实际情况来进行，一般一个频点的Event最多可能有2000-3000个，而要支持存储所有频点的Event的话，至少需                                  要支持12000个以上的Event。
                                    当然需要存储的Event越多，需要的buffer也就越多。
                                    对于buffer只有1M的情况，建议配置为3000-5000个；对于2M的buffer，则可以配置为10000-12000个。*/

	UINT32 max_view_event_count;

	EIT_CALL_BACK call_back;

} epg_config_t;


#ifdef __cplusplus
extern "C"{
#endif


/*!
@brief 初始化EPG模块，主要是buffer和一些配置项的设置。
@param[in] buf EPG模块使用的buffer。<br>
如果buf == NULL，表示是由EPG模块自己负责分配一块buffer，并且在release的时候负责释放该buffer。
如果buf != NULL，表示是由外部传入给EPG模块使用的buffer，在release EPG的时候，EPG模块不负责释放该buffer，需要由外部自己释放该buffer。

@param[in] len buffer的大小。一般对于EPG不是特别多的地方，可以置为1M即可；但是对于EPG非常多的地方，则可能需要2M以上的buffer。
@param[in] cfg 配置参数

@retval SUCCESS 成功
@retval ERR_XXX 失败，参数错误，或者状态错误，或者buffer不足。

*/
INT32 amsepg_init(UINT8* buf, UINT32 len, epg_config_t *cfg);


/*!
@brief 释放EPG模块的所有资源，包括buffer、Event等等。
@note 如果buffer是由EPG模块自己申请的，则会释放该buffer，否则需要外部在调用该函数之后，自行释放。
@note 该函数只能在EPG OFF的状态下调用，也就是只能在amsepg_off()之后调用。
*/
INT32 amsepg_unreg_callback();

/*!
@brief 向EPG模块注册callback。
@details 该函数可以在任意时刻调用，调用之后，新的callback立刻生效。但是如果在amsepg_init()之前调用，其注册的callback函数会被amsepg_init()冲掉。amsepg_init()如果已经传了callback函数，则不需要再调用该函数注册callback。除非在进入NVOD节目菜单的时候，NVOD需要另外注册自己的callback，替换原来的callback，可以调用该函数。
@param[in] callback 需要注册的callback函数。
@retval SUCCESS 总是成功
*/
INT32 amsepg_reg_callback(EIT_CALL_BACK callback);

/*!
@brief 取消注册的callback函数，并立刻生效。
@details 在进NVOD的时候，应当按正常流程先调用amsepg_unreg_callback()取消原来注册的callback，再调用amsepg_reg_callback()注册自己的callback。同样，在退出NVOD的时候，也应当按正常流程先调用amsepg_unreg_callback()取消其注册的callback，再调用amsepg_reg_callback()恢复注册原有的callback。
@retval SUCCESS 总是成功
@see amsepg_reg_callback
*/
INT32 amsepg_release();

/*!
@brief 重置EPG模块，清除所有的Event、Service列表、TP列表，重置memory等。
@details 在用户load default或者删除所有节目的时候需要调用该函数。或者在用户切换到其它模式，比如NVOD，不需要其它Service的Event，只需要重新拿NVOD节目的Event，也可以调用该函数重置一下EPG模块。该函数只能在EPG OFF的状态下调用。
@retval SUCCESS 成功
@retval ERR_XXX 失败，状态错误。
*/
INT32 amsepg_reset(void);

/*!
@brief 向EPG模块的Service列表添加多个Service
@details EPG模块除了在amsepg_on()的时候，可以根据数据库的当前TV/Radio/NVOD等节目列表，更新EPG的Service列表；也可以在EPG OFF的状态下，外部通过调用该函数向EPG模块添加新的不在当前节目列表的Service。
比如对NVOD，在TV/Radio等Channel list下都看不到NVOD的节目，NVOD只有自己通过数据库先得到NVOD的节目列表，再调用该函数将这些NVOD的节目也添加到EPG的Service列表，从而达到EPG模块也去拿取NVOD节目的EIT数据的目的。

@param[in] service_list 需要添加的Service列表。具体类型请参考epg_service_t的定义。
@param[in] cnt   Service的个数。

@retval SUCCESS 	成功
@retval ERR_XXX	    失败，参数错误或者状态错误
*/
INT32 amsepg_add_service(epg_service_t *service_list, INT32 cnt);


/*!
@brief 初始化SIM。
@details 此函数用于初始化SI monitor库。Si monitor模块通过此函数创建内部需要的资源。
@param[in] service_list Service列表。具体类型请参考epg_service_t的定义。
@param[in] count   Service的个数
@param[in] mode 删除模式。有2种模式，请参考COMPARE_MODE的定义
@retval SUCCESS 成功
@retval ERR_XXX 失败，状态错误。
*/
INT32 amsepg_del_service(epg_service_t *service_list, INT32 count, enum COMPARE_MODE mode);

/*!
@brief Switch On EPG模块，也即是向DMX申请并打开一个EIT的filter，抓取EIT的actual/other present/following/schedule等数据。
@details 该函数会先根据当前用户正在观看的TV或者Radio等的节目列表，在EPG模块内部创建一个Service列表，以及各个Service的EIT section hitmap。EPG模块会根据这个Service列表和hitmap过滤从     DMX收到的EIT section数据，只有在这个Service列表的并且hitmap没有命中的section数据才需要给Parser做分析，并保存到数据库。
    如果需要支持other的EIT数据的话，还需要创建一个所有TP的列表，通过TS ID来判断收到的other EIT section数据是属于哪个TP的Service的数据。

@param[in] dmx_id   向哪个DMX申请filter的DMX ID。一般是0，如果是多个DMX的话， 可能会用到DMX 1/DMX 2等等。
@param[in] sat_id   虚拟Satellite的ID。在节目数据库有一个虚拟Satellite的概念，所有频点和节目都从属于这个Satellite。对Cable而言，总是1。
@param[in] tp_id    当前播放的频点的ID，这个ID是由数据库给每一个频点分配的唯一的ID，与码流的TS ID不是同一个含义，请注意区分。<br>
                    在DVB-S市场，一个或多个卫星有多个转发器，而各个转发器是租给不同的使用方，这些转发器所播放的码流的TS ID等等完全有可能重叠，所以无法用TS ID唯一区分一个频点，只能用数据库的TP ID来区分它们。<br>
                    但在Cable市场，一般就没有这个问题，在一个地方(比如县)，用TS ID也可以唯一区分其是哪一个频点。

@param[in] service_id   当前正在播放的节目ID。如果是只要拿某个service的EIT数据，需要传正确的service_id下来，以实现在向DMX申请filter时配置正确的service ID的mask和value参数；
                    如果是拿整个频点所有节目的EIT，甚至还要拿other的EIT，则service_id没有用处。
@param[in] mode     参考epg_eit_mode_e的定义。缺省值是EIT_DEFAULT，表示要拿所有当前频点节目的present/following/schedule EIT数据，也即是table ID为0x4E和0x50~0x5x的所有service的                      EIT数据。
*/
void amsepg_on(UINT32 dmx_id, UINT16 sat_id, UINT32 tp_id, UINT16 service_id, epg_eit_mode_e mode, UINT8 ignore_crc);

/*!
@brief 停止拿EIT数据，并释放DMX的filter。
@details amsepg_off()和amsepg_on()需要配对使用。在拿所有service的EIT数据的模式下，换台的时候，可以不用调用amsepg_off()和amsepg_on()，只需要在换频点的时候调用一下amsepg_off()和            amsepg_on()即可。但是即使是在同频点换台之前，EPG模块也不知道用户做了什么操作，比如添加或者删除了节目等等，如果不调用amsepg_off()和amsepg_on()的话，EPG模块不知道节目有了更新         ，也无法响应更新。因为EPG模块现在都是通过在amsepg_on()函数内更新当前的节目列表和TP列表。所以从这点来说，还是建议每次换台的时候，都需要调用一次amsepg_off()和amsepg_on()。
@see amsepg_on
*/
void amsepg_off(void);

/*!
@brief 从EPG数据库创建View，并获取某个service的preset/following/schedule、某个时间段的Event。这个函数提供了常用的获取单个service某个时间段的Event的接口，其将创建View和获取Event这两个动作都包含在内了。
@param[in] tp_id 节目所在的TP ID。
@param[in] service_id   节目的Service ID。
@param[in] type 所要获取的Event的类型，参考EPG_DB_EVENT_TYPE的定义，但是在这个函数，只能使用以下3种类型：<br>
	- PRESENT_EVENT,
	- FOLLOWING_EVENT,
	- SCHEDULE_EVENT<br>
    即该函数只能获取Service的present/following/schedule类型的Event。
@param[in] start_dt Event的起始时间限制，含该时间。
@param[in] end_dt   Event的结束时间限制，含该时间。
@param[out] num     符合条件的View的Event个数。数目受amsepg_init()的cfg配置参数的max_view_event_count最大数限制。
@param[in] force_update 当创建Event View，Service、时间等条件一样的时候，是否强制更新View。
    - TRUE 强制更新View。
    - FALSE  不更新View。<br>
    应用层在多次反复调用该函数获取Event的时候，可能service、时间等条件完全没有改变，那么EPG数据库可以不需要更新View，直接将前一次的结果返回给应用。<br>
    但是在EPG模块收到某个Service的新的Event并通过callback通知应用的时候，应用要拿到该Service这些新的Event，而其它条件都完全一样，则需要通过将force_update置为TRUE，强制EPG数据库更新View。

@return 返回一个struct EPG_DB_NODE结构指针
@retval 非NULL  表示EPG数据库有符合条件的Event，并创建了View，传回第一个Event。
@retval NULL 表示没有符合条件的Event，View也为空。
*/
struct EPG_DB_NODE *amsepg_get_service_event(UINT32 tp_id, UINT16 service_id, UINT32 type,
							date_time *start_dt, date_time *end_dt,
							INT32 *num,
							BOOL force_update);

/*!
@brief EPG数据库创建符合某个条件的Event View。
@details 不管是amsepg_create_view()还是amsepg_get_service_event()，EPG模块目前都是只支持创建1个View，不支持同时创建多个View。多个View的问题在于底层EPG Event数据更新的时候，View难以同步更新。
@param[in] filter  参考epg_db_filter_t的定义
@param[in] priv 私有数据，EPG数据库在创建View的时候，会将其传递给filter，具体类型定义和使用方式都是由Filter决定的。
@return INT32：View Event的个数，同样受到amsepg_init()的cfg配置参数的max_view_event_count最大数限制。
@note EPG数据库在创建View的时候，会遍历存储的每一个Event Node，并将其和私有数据传递给filter，由filter判断是否是符合View的条件。如果返回TRUE，表示符合条件，EPG数据库就会将其加入到View；否则，则不会加入View。
*/
INT32 amsepg_create_view(epg_db_filter_t filter, void *priv);

/*!
@brief 读取View里的Event。
@details 在amsepg_get_service_event()和amsepg_create_view()成功之后，可以通过该函数逐个读取View里的Event。
@param[in] index    Event在View的位置，从0开始，直到View Event个数-1。
@return 返回一个EPG_DB_NODE结构指针
@retval 非NULL  表示读取到该Index的Event。
@retval	NULL    表示没有读到该index的Event，可能index不合法等等原因。
@note EPG数据库内部有一个缺省的Event Node的buffer，amsepg_get_event()和amsepg_get_service_event()会将Event从EPG数据库拷贝到该buffer，这样，EPG数据库底层如果正好在更新该Event的话     ，不会影响到外部用户。<br>
    但是这个buffer只有一个，外部用户在获取到这个Event之后，需要尽快显示和使用其中的信息；在调用amsepg_get_event()读取下一个Event之后，前一个Event就不存在了。<br>
    Present/Following Event各自占用4k的buffer，可以并存；但是Schedule Event会占用整个8k的buffer，与其它Present/Following/Schedule Event不能并存。<br>
    amsepg_get_event()和amsepg_get_event2()需要跟amsepg_get_service_event()和amsepg_create_view()结合起来使用，在amsepg_get_service_event()和amsepg_create_view()创建好一个View之后，可以反复使用amsepg_get_event()和amsepg_get_event2()读取View里的各个Event。

*/
struct EPG_DB_NODE *amsepg_get_event(INT32 index);

/*!
@brief 读取View里的Event。
@details 在amsepg_get_service_event()和amsepg_create_view()成功之后，可以通过该函数逐个读取View里的Event。
@param[in] buf  用于存放Event的buffer。<br>
                这个buffer由外部传入，EPG数据库会将Event拷贝到这个buffer。如果外部每次传的buffer各自独立，则这些Event就可以长时间保存在外部。
@param[in] len  buffer的大小。<br>
                EPG数据库在将Event拷贝到这个buffer的时候，会判断这个buffer的大小是否够用。首先会将Event Node固定长度的部分拷贝过来，接着继续拷贝不定长度的Event Name、short detail和extend detail等。如果buffer大小不够，则可能没有Event Name、short detail和extend detail等信息。
@param[in] index    Event在View的位置，从0开始，直到View Event个数-1。
@retval SUCCESS	    成功
@retval ERR_XXX	    失败，View为空，或者buffer为NULL等
*/
INT32 amsepg_get_event2(UINT8 *buf, INT32 len, INT32 index);

/*!
@brief 获取Event的起始时间。
@details 在EPG Event Node结构里，Event的时间是MJD Number和时分秒，需要将MJD Number转化为年月日。
@param[in] event    Event Node
@param[out] start_dt    起始时间，具体结构定义参考date_time的定义。
@return 获得的起始时间，也即是传入的start_dt地址。
*/
date_time *amsget_event_start_time(struct EPG_DB_NODE *event, date_time *start_dt);

/*!
@brief 获取Event的结束时间。
@details 在EPG Event Node结构里，Event的起始时间是MJD Number和时分秒。没有结束时间，只有持续时间，需要将起始时间加上持续时间，才是结束时间。
@param[in] event    Event Node
@param[out] end_dt    结束时间，具体结构定义参考date_time的定义。
@return 获得的结束时间，也即是传入的end_dt地址。
*/
date_time *amsget_event_end_time(struct EPG_DB_NODE *event, date_time *end_dt);

/*!
@brief 将2个字节的language code转换成3个字节的ISO 639 language code。
@details
DVB SI一般都是使用3个字节ISO 639 language code来表示语言类型，比如”chi”,”eng”等等。在Event Node结构里为了节省一个字节的存储空间，将3个字节的ISO 639 language code转换成了2个字节的code，转换格式如下：<br>
 @code Lang2 = ((lang3[0]-’a’)<<10)  |  ( (lang3[1] -’a’)<<5)  |  (lang3[2] -’a’);@endcode <br>
反之，在应用层则需要将其转换为3个字节的ISO 639 language code以便显示，转换格式如下：<br>
@code
	Lang3[0] = (lang_code2>>10) + 'a';
	Lang3[1] = ((lang_code2>>5) & 0x1F) + 'a';
	Lang3[2] = (lang_code2 & 0x1F) + 'a';
@endcode

@param[in] lang_code2   2个字节的language code。
@return 3个字节的ISO 639 language code。
*/
UINT8* lang2tolang3(UINT16 lang_code2);
UINT8* lang2tolang3_2(UINT16 lang_code2, UINT8 *lang3);	//2 byte to 3 byte

/*!
@brief 设置Active Service列表。
@details Active Service的含义，参看第3章宏EPG_ACTIVE_SERVICE_CNT的说明。每次换台的时候，或者在EPG菜单里查看一个或多个节目的EPG信息的时候，需要调用该函数设置Active Service。
@param[in] service   Active Service列表。
@param[in] cnt      Service个数。
@return 实际设置成功的Active Service的个数。如果cnt > EPG_ACTIVE_SERVICE_CNT，则最多只能设置前面EPG_ACTIVE_SERVICE_CNT个Active Service。
*/
INT32 amsepg_set_active_service(epg_service_t *service, INT32 cnt);

/*!
@brief 检查某个Service是否是Active Service列表里的节目。
@details 这个函数一般用于callback里，先检查Service是不是Active Service。如果是，才需要向应用层发送消息。
@param[in] tp_id    该Service所在的TP ID。
@param[in] service_id   Service ID。
@retval TRUE	是Active Service
@retval FALSE   非Active Service
*/
BOOL  amsepg_check_active_service(UINT32 tp_id, UINT16 service_id);

/*!
@brief 打印出EPG模块的状态。
@details 包括使用的buffer的地址和大小，最大TP支持个数，实际TP个数，最大Service个数，实际Service个数，最大Event个数，实际Event个数和memory剩余大小。必须在amsepg_init()之后才能调用。
*/
INT32 amsepg_get_module_status(void);

/*!
@brief 获取某个Service的状态，主要是该Service所有section是否有命中。
@param[in] tp_id 该Service所在的TP ID。
@param[in] service_id Service ID。
@retval 1 该Service的所有EIT section都命中了。
@retval 0 该Service的EIT section数据还没有完全命中。
@retval EPG_SERVICE_NOT_EXIST 该Service不存在。
*/
INT32 amsepg_get_service_status(UINT32 tp_id, UINT16 service_id);


#ifdef __cplusplus
}
#endif



/*!
 * @}
 */

/*!
@}
*/

#endif //__LIB_EPG_H__

