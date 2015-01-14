#ifndef  _LIB_MULTIFEED_H_
#define  _LIB_MULTIFEED_H_



struct FEED_INFO
{
	struct FEED_INFO *next;
	UINT16 transport_stream_id;
	UINT16 original_network_id;
	UINT16 service_id;
	UINT8 name[32];
	UINT8 is_known;
	P_NODE p_node;

};

struct MULTIFEED_INFO
{
	struct MULTIFEED_INFO *next;
	UINT32 prog_id;
	UINT32 tp_id;
	UINT16 sat_id;
	UINT16 service_id;
	UINT8 idx;	//0 is masterfeed
	UINT8 num;
	struct FEED_INFO *feed_head;
	struct FEED_INFO *feed_tail;

};

typedef void (*MULTIFEED_CALL_BACK)(UINT32 prog_id);

void multifeed_register(MULTIFEED_CALL_BACK cb);
INT32 multifeed_get_feed_name(UINT32 prog_id, UINT32 idx, UINT8* name);
INT32 multifeed_get_info(UINT32 prog_id, struct MULTIFEED_INFO *info);
INT32 multifeed_set_value(struct MULTIFEED_INFO *info, UINT16 sat_id, UINT32 prog_id);
INT32 multifeed_change_feed(UINT16 cur_channel, UINT32 idx);
INT32 multifeed_modify_node(UINT32 prog_id, P_NODE *p_node, BOOL rel);

#endif /* _LIB_MULTIFEED_H_ */

