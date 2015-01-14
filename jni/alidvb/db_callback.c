/**********************************************************************
*    Copyright (C)2011 Ali Corporation. All Rights Reserved.
*
*    File:    db_callback.c
*
*    Description:   this file contains callback functions that registered to database, function prototype listed in db_interface.h
*    History:
*       Date            Athor        Version       Reason
*    ========   ========    ======     ========

*1.  2011.10.16  Robbin Han     0.1.000   	Initial

************************************************************************/
#include <adr_sys_config.h>
#include <hld/sto/adr_sto.h>
#include <hld/sto/adr_sto_dev.h>
#include <osal/osal.h>
#include <api/libdb/db_return_value.h>
#include <api/libdb/db_interface.h>
#include <api/libdb/db_node.h>
#include <api/libdb/db_config.h>
#include <api/libsi/si_service_type.h>
#include <android/log.h>

#define  LOG_TAG    "Db_callback"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

//nim frequency unit is 10k, gap 400=4000K HZ
#define TP_FRQ_GAP_C  400
#define TP_FRQ_GAP_S 2
#define TP_SYM_EDG 19


// *****************************************************************
// Summary:
//     db node create view filter function
// Description:
//     The function is registered to database and called when  create node view.
//     When create node view, database traverse the specific kind type of nodes and select those matching filter function,
//     then put those node into this view.
// Returns:
//     TRUE	-this node match the filter funciton, will be put into the created db view
//     FALSE	-this node not match the filter funciton, will not be put into the created db view
// Parameters:
//     node_type :   [in] TYPE_SAT_NODE, TYPE_TP_NODE or TYPE_PROG_NODE
//     node :           [in] pointer to node data, filter function can use node data to check matching condition
//     filter_mode :   [in] create view mode, high byte is node group flag, low byte is node type flag
//     param :        [in] create view parameters, depends on the view mode
// 
// See Also:
//
// *****************************************************************     
BOOL db_createview_filter(UINT8 node_type, const UINT8 *node, UINT16 filter_mode, UINT32 param)
{
	BOOL ret = TRUE;

	if(node==NULL)
	{
		LOGE("db_createview_filter::node==NULL\n");
		return FALSE;
	}

	if(node_type==TYPE_TP_NODE)
	{
		if ((filter_mode&0xFF00)==VIEW_SINGLE_SAT) 
		{
			T_NODE *tp = (T_NODE*)node;
			LOGE("db_createview_filter::tp->tp_id>>NODE_ID_TP_BIT=%d,param=%d\n",tp->tp_id>>NODE_ID_TP_BIT,param);
			ret = ((tp->tp_id>>NODE_ID_TP_BIT) == param);
		}
	}
	else if(node_type==TYPE_SAT_NODE)
	{
		
	}
	else if(node_type==TYPE_PROG_NODE)
	{
		P_NODE *prog = (P_NODE*)node;
		UINT8 service_type = (UINT8)(filter_mode&0xFF);
		//check group flag
		if ((filter_mode&0xFF00)==VIEW_SINGLE_SAT) 
		{
			ret = ((prog->prog_id&NODE_ID_SET_MASK) == (param<<(NODE_ID_PG_BIT+NODE_ID_TP_BIT)));
		}
		else if ((filter_mode&0xFF00)==VIEW_SINGLE_TP)
		{
			ret = ((prog->prog_id&NODE_ID_TP_MASK)==(param<<NODE_ID_PG_BIT));
		}
		else if ((filter_mode&0xFF00)== VIEW_FAV_GROUP) 
		{
			ret = (((prog->fav_grp>>param)&0x01)==1);
		}
		else if ((filter_mode&0xFF00)== VIEW_FAV_GROUP_ALL) 
		{
			ret = (prog->fav_grp!=0);
		}
		else if((filter_mode&0xFF00)== VIEW_BOUQUIT_ID) 
		{
			UINT16 i = 0;
			for(i=0 ; i< prog->bouquet_cnt; i++)
			{
				if(prog->bouquet_id[i]==param)
				{	
					break;
				}
			}
			if(i==prog->bouquet_cnt)
				ret = FALSE;
		}
		if(ret==FALSE)
			return FALSE;
		
		//check service type flag
		if(service_type== PROG_ALL_MODE)
			return ret;
		else if(service_type==PROG_NVOD_MODE)
			return ret&&((prog->service_type==SERVICE_TYPE_NVOD_TS)||\
			(prog->service_type==SERVICE_TYPE_NVOD_REF));
		else if(service_type==PROG_TVRADIO_MODE)
			return ret&&((prog->service_type==SERVICE_TYPE_DTV) ||\
			                   (prog->service_type==SERVICE_TYPE_DRADIO)||\
			                   (prog->service_type==SERVICE_TYPE_FMRADIO)||\
			                    (prog->service_type==SERVICE_TYPE_HD_MPEG4)||\
				(prog->service_type==SERVICE_TYPE_SD_MPEG4) ||\
				(prog->service_type==SERVICE_TYPE_HD_MPEG2));
		else if(service_type==PROG_TV_MODE)
			return ret&&((prog->service_type==SERVICE_TYPE_DTV)||\
				(prog->service_type==SERVICE_TYPE_HD_MPEG4)||\
				(prog->service_type==SERVICE_TYPE_SD_MPEG4) ||\
				(prog->service_type==SERVICE_TYPE_HD_MPEG2));
		else if(service_type==PROG_RADIO_MODE)
			return ret&&((prog->service_type==SERVICE_TYPE_DRADIO)||\
						(prog->service_type==SERVICE_TYPE_FMRADIO));
		else if(service_type==PROG_DATA_MODE)
			return ret&&(prog->service_type==SERVICE_TYPE_DATABROAD);
		
		else if(service_type == PROG_PRIVATE_MODE)
			return ret&&(prog->service_type==SERVICE_TYPE_PRIVATE);
		else
		{
			ret = FALSE;
		}

	}
	LOGE("db_createview_filter::ret==%d\n",ret);
	return ret;
}

// *****************************************************************
// Summary:
//     db node packing function
// Description:
//     The function is registered to database and called when  node written into ROM.
//      The function packed db node from node structure defined in db_node_c.h to format as follows:
//     ID(4byte)+Total_len(1byte)+[Fix_len(1byte)+Fix_data]+Vary_cnt(1byte)+[Vary_len1(1byte)+Vary_data_1+...Vary_len_n(1byte)+Vary_data_n]
// Returns:
//     DB_SUCCES	-if packing ok
//     DBERR_PACK	-if packing error
// Parameters:
//     node_type :   [in] TYPE_SAT_NODE, TYPE_TP_NODE or TYPE_PROG_NODE
//     src_node :     [in] pointer to source node data
//     src_len :        [in] node length in byte before packing, equals sizeof(node structure)
//     packed_node: [in] pointer to packed node data
//     packed_len:    [in] node length in byte after packing
// 
// See Also:
//
// *****************************************************************                 
INT32 db_node_packer(UINT8 node_type, const UINT8*src_node, UINT32 src_len,UINT8*packed_node,UINT32 *packed_len)
{
	UINT32 offset = 0;
	UINT32 node_id = 0;

	if((src_node==NULL)||(src_len<=0)||(packed_node==NULL)||(packed_len==NULL))
	{

		return DBERR_PARAM;
	}
	
	if(node_type == TYPE_SAT_NODE)
	{
		S_NODE *s_node = (S_NODE *)src_node;
		//id
		node_id = s_node->sat_id;
		node_id = (node_id<<(NODE_ID_PG_BIT+NODE_ID_TP_BIT));
		DB_MEMCPY(packed_node, (UINT8 *)&node_id, NODE_ID_SIZE);
				
		offset += NODE_ID_SIZE+1;
		//fix_len
		packed_node[offset] = S_NODE_FIX_LEN;
		offset += 1;
		//fix data
		DB_MEMCPY(packed_node+offset, &(s_node->sat_orbit), S_NODE_FIX_LEN);
		offset += S_NODE_FIX_LEN;

		//vary cnt
		packed_node[offset] = 1;
		offset += 1;
		//vary data len
		packed_node[offset] = (UINT8)s_node->name_len;
		offset += 1;
		//vary data
		if(s_node->name_len>0)
			DB_MEMCPY((UINT8 *)&packed_node[offset],s_node->sat_name,s_node->name_len);
		offset += s_node->name_len;

		//total data len, including itself byte
		packed_node[NODE_ID_SIZE] = offset-NODE_ID_SIZE;
		
		*packed_len = offset;
	}
	else if(node_type == TYPE_TP_NODE)
	{
		//id
		T_NODE *t_node  = ( T_NODE*)src_node;
		node_id = t_node->tp_id;
		node_id = (node_id<<NODE_ID_PG_BIT);
		DB_MEMCPY(packed_node,(UINT8 *)&node_id,NODE_ID_SIZE);		 
				
		offset += NODE_ID_SIZE+1;
		//fix_len
		packed_node[offset] = T_NODE_FIX_LEN;
		offset += 1;
		//fix data
		DB_MEMCPY(packed_node+offset, &(t_node->frq), T_NODE_FIX_LEN);
		offset += T_NODE_FIX_LEN;

		//vary cnt
		packed_node[offset] = 1;
		offset += 1;
		//vary data len
		packed_node[offset] = (UINT8)t_node->name_len;
		offset += 1;
		//vary data
		if(t_node->name_len>0)
			DB_MEMCPY(packed_node+offset,t_node->net_name, t_node->name_len);
		offset += t_node->name_len;

		//total data len, including itself byte
		packed_node[NODE_ID_SIZE] = offset-NODE_ID_SIZE;
		
		*packed_len = offset;
	}
	else if(node_type == TYPE_PROG_NODE)
	{
		//id
		P_NODE*p_node = ( P_NODE*)src_node;
		DB_MEMCPY(packed_node,(UINT8 *)&p_node->prog_id,NODE_ID_SIZE);
						
		offset += NODE_ID_SIZE+1;
		//fix_len
		packed_node[offset] = P_NODE_FIX_LEN;
		offset += 1;
		//fix data
		DB_MEMCPY(packed_node+offset, (UINT8 *)&(p_node->prog_id)+sizeof(UINT32), P_NODE_FIX_LEN);
		offset += P_NODE_FIX_LEN;

		//vary cnt
		packed_node[offset] = 5;
		offset += 1;
		
		//bouquet cnt
		packed_node[offset] = p_node->bouquet_cnt;
		offset += 1;
		//boutquet id
		if(p_node->bouquet_cnt>0)
			DB_MEMCPY(packed_node+offset, (UINT8 *)&p_node->bouquet_id[0], p_node->bouquet_cnt*sizeof(p_node->bouquet_id[0]));
		offset += p_node->bouquet_cnt*sizeof(p_node->bouquet_id[0]);

		//cas cnt
		packed_node[offset] = p_node->cas_count;
		offset += 1;
		//cas id
		if(p_node->cas_count>0)
			DB_MEMCPY(packed_node+offset,(UINT8 *)&p_node->cas_sysid[0], p_node->cas_count*sizeof(p_node->cas_sysid[0]));
		offset += p_node->cas_count*sizeof(p_node->cas_sysid[0]);

		//audio cnt
		packed_node[offset] = p_node->audio_count;
		offset += 1;
		//audio id
		/*if(p_node->audio_count>0)
			DB_MEMCPY(packed_node+offset,(UINT8 *)&p_node->audio_pid[0], p_node->audio_count
		*(sizeof(p_node->audio_pid[0])+sizeof(p_node->audio_lang[0])+sizeof(p_node->audio_type[0])));
		offset += p_node->audio_count*(sizeof(p_node->audio_pid[0])+sizeof(p_node->audio_lang[0])+sizeof(p_node->audio_type[0]));
        		*/
        		//audio id and lang
		if(p_node->audio_count>0)
			DB_MEMCPY(packed_node+offset,(UINT8 *)&p_node->audio_pid[0],//(UINT8 *)&p_node->audio_pid[0], src_node+offset, 
			p_node->audio_count*sizeof(p_node->audio_pid[0]));
		offset += p_node->audio_count*sizeof(p_node->audio_pid[0]);
		if(p_node->audio_count>0)
			DB_MEMCPY(packed_node+offset,(UINT8 *)&p_node->audio_lang[0],//(UINT8 *)&p_node->audio_lang[0], src_node+offset, 
			p_node->audio_count*sizeof(p_node->audio_lang[0]));		
		offset += p_node->audio_count*sizeof(p_node->audio_lang[0]);
		if(p_node->audio_count>0)
			DB_MEMCPY(packed_node+offset,(UINT8 *)&p_node->audio_type[0],//(UINT8 *)&p_node->audio_type[0], src_node+offset, 
			p_node->audio_count*sizeof(p_node->audio_type[0]));		
		offset += p_node->audio_count*sizeof(p_node->audio_type[0]);

		//name len
		packed_node[offset] = p_node->name_len;
		offset += 1;
		//name
		if(p_node->name_len>0)
			DB_MEMCPY(packed_node+offset, (UINT8 *)&p_node->service_name[0], p_node->name_len);
		offset += p_node->name_len;

		//provider name len
		packed_node[offset] = p_node->prd_name_len;
		offset += 1;
		//provider name
		if(p_node->prd_name_len>0)
			DB_MEMCPY(packed_node+offset, (UINT8 *)&p_node->service_provider_name[0], p_node->prd_name_len);
		offset += p_node->prd_name_len;

		//total data len, including itself byte
		packed_node[NODE_ID_SIZE] = offset-NODE_ID_SIZE;
		
		*packed_len = offset;

	}
	else
	{
		return DBERR_PARAM;
	}
	if(*packed_len > src_len)
	{
		amslog_error(LOG_APP, "node type=%d id=0x%x pack error\n\n",node_type,node_id);
		return DBERR_PACK;
	}
	
	return DB_SUCCES;
}

// *****************************************************************
// Summary:
//     db node unpacking function
// Description:
//     The function is registered to database and called when  node read from ROM.
//      The function unpacked db node from format as follows to node structure defined in db_node.h:
//     ID(4byte)+Total_len(1byte)+[Fix_len(1byte)+Fix_data]+Vary_cnt(1byte)+[Vary_len1(1byte)+Vary_data_1+...Vary_len_n(1byte)+Vary_data_n]
// Returns:
//     DB_SUCCES	-if unpacking ok
//     DBERR_PACK	-if unpacking error
// Parameters:
//     node_type :   [in] TYPE_SAT_NODE, TYPE_TP_NODE or TYPE_PROG_NODE
//     src_node :     [in] pointer to source node data
//     src_len :        [in] node length in byte before packing, equals sizeof(node structure)
//     packed_node: [in] pointer to packed node data
//     packed_len:    [in] node length in byte after packing
// 
// See Also:
//
// *****************************************************************        
INT32 db_node_unpacker( UINT8 node_type,const UINT8 *src_node,UINT32 src_len, UINT8 *unpack_node, UINT32 unpack_len)
{
	UINT32 node_id = 0;
	UINT32 offset = 0;
	UINT32 fix_len = 0;
	UINT32 vary_cnt = 0;

	if((src_node==NULL)||(src_len<=0)||(unpack_node==NULL)||(unpack_len<=0)||(src_len>unpack_len))
	{

		return DBERR_PARAM;
	}
	//id
	DB_MEMSET(unpack_node, 0, unpack_len);
	DB_MEMCPY((UINT8 *)&node_id, src_node,NODE_ID_SIZE);

	if(node_type == TYPE_SAT_NODE)
	{
		S_NODE *s_node = ( S_NODE *)unpack_node;
		s_node->sat_id = (UINT16)(node_id>>(NODE_ID_PG_BIT+NODE_ID_TP_BIT));

		offset = NODE_ID_SIZE+1;
		//fix len
		fix_len = src_node[offset];
		offset += 1;
		//fix data
		DB_MEMCPY(&(s_node->sat_orbit), src_node+offset, fix_len);
		offset += fix_len;

		//vary cnt
		vary_cnt = src_node[offset];
		offset += 1;

		//name len
		s_node->name_len = src_node[offset];
		offset += 1;
		//name
		if(s_node->name_len>0)
			DB_MEMCPY((UINT8 *)&s_node->sat_name[0], src_node+offset, s_node->name_len);
		offset += s_node->name_len;
		
		
	}
	else if(node_type == TYPE_TP_NODE)
	{
		T_NODE* t_node = ( T_NODE*)unpack_node;
		t_node->sat_id = (UINT16)(node_id>>(NODE_ID_PG_BIT+NODE_ID_TP_BIT));
		t_node->tp_id = (node_id>>NODE_ID_PG_BIT);

		offset = NODE_ID_SIZE+1;
		//fix len
		fix_len = src_node[offset];
		offset += 1;
		//fix data
		DB_MEMCPY((UINT8 *)&(t_node->frq), src_node+offset, fix_len);
		offset += fix_len;

		//vary cnt
		vary_cnt = src_node[offset];
		offset += 1;

		//name len
		t_node->name_len = src_node[offset];
		offset += 1;
		//net name
		if(t_node->name_len>0)
			DB_MEMCPY((UINT8 *)&t_node->net_name[0], src_node+offset, t_node->name_len);
		offset += t_node->name_len;
		
	}
	else if(node_type == TYPE_PROG_NODE)
	{
		P_NODE* p_node = ( P_NODE*)unpack_node;
		p_node->prog_id = node_id;
		p_node->sat_id = (UINT16)(node_id>>(NODE_ID_PG_BIT+NODE_ID_TP_BIT));
		p_node->tp_id = (node_id>>NODE_ID_PG_BIT);
		
		offset = NODE_ID_SIZE+1;
		//fix len
		fix_len = src_node[offset];
		offset += 1;
		//fix data
		DB_MEMCPY((UINT8 *)&(p_node->prog_id)+sizeof(UINT32), src_node+offset, fix_len);
		offset += fix_len;
		
		//vary cnt
		vary_cnt = src_node[offset];
		offset += 1;

		//bouquet cnt
		p_node->bouquet_cnt = src_node[offset];
		offset += 1;
		//bouquet id
		if(p_node->bouquet_cnt>0)
			DB_MEMCPY((UINT8 *)&p_node->bouquet_id[0], src_node+offset, 
			p_node->bouquet_cnt*sizeof(p_node->bouquet_id[0]));
		offset += p_node->bouquet_cnt*sizeof(p_node->bouquet_id[0]);

		//cas cnt
		p_node->cas_count = src_node[offset];
		offset += 1;
		//cas id
		if(p_node->cas_count>0)
			DB_MEMCPY((UINT8 *)&p_node->cas_sysid[0], src_node+offset, 
			p_node->cas_count*sizeof(p_node->cas_sysid[0]));
		offset += p_node->cas_count*sizeof(p_node->cas_sysid[0]);

		//audio cnt
		p_node->audio_count = src_node[offset];
		offset += 1;
		//audio id and lang
		if(p_node->audio_count>0)
			DB_MEMCPY((UINT8 *)&p_node->audio_pid[0], src_node+offset, 
			p_node->audio_count*sizeof(p_node->audio_pid[0]));
		offset += p_node->audio_count*sizeof(p_node->audio_pid[0]);
		if(p_node->audio_count>0)
			DB_MEMCPY((UINT8 *)&p_node->audio_lang[0], src_node+offset, 
			p_node->audio_count*sizeof(p_node->audio_lang[0]));		
		offset += p_node->audio_count*sizeof(p_node->audio_lang[0]);
		if(p_node->audio_count>0)
			DB_MEMCPY((UINT8 *)&p_node->audio_type[0], src_node+offset, 
			p_node->audio_count*sizeof(p_node->audio_type[0]));		
		offset += p_node->audio_count*sizeof(p_node->audio_type[0]);

		//name len
		p_node->name_len = src_node[offset];
		offset += 1;
		//name
		if(p_node->name_len>0)
			DB_MEMCPY((UINT8 *)&p_node->service_name[0], src_node+offset, p_node->name_len);
		offset += p_node->name_len;

		//provider name len
		p_node->prd_name_len = src_node[offset];
		offset += 1;
		//provider name
		if(p_node->prd_name_len>0)
			DB_MEMCPY((UINT8 *)&p_node->service_provider_name[0], src_node+offset, p_node->prd_name_len);
		offset += p_node->prd_name_len;
	
	}
	else
	{
		return DBERR_PARAM;
	}
	if(offset!=src_len)
	{
		amslog_error(LOG_APP, "node type=%d id=0x%x unpack error\n\n",node_type,node_id);
		return DBERR_PACK;
	}
	return SUCCESS;

}


// *****************************************************************
// Summary:
//     compare two node whether same
// Description:
//     The function is registered to database and called when  compare two same type node.
// Returns:
//     TRUE	-two node same
//     FALSE	-two node not same
// Parameters:
//     node_type :   [in] TYPE_SAT_NODE, TYPE_TP_NODE or TYPE_PROG_NODE
//     old_node :     [in] pointer to node1 data
//     new_node: [in] pointer to node2 data
// 
// See Also:
//
// *****************************************************************     
BOOL db_same_node_checker(UINT8 n_type, const void* old_node, const void* new_node)
{
	if(old_node==NULL || new_node==NULL)
	{

		return FALSE;
	}

	if(n_type == TYPE_SAT_NODE)
	{
		S_NODE* s1=( S_NODE*)old_node;
		S_NODE* s2=( S_NODE*)new_node;
		if((s2->sat_id == s1->sat_id) &&( s1->pol == s2->pol) && (s1->sat_orbit == s2->sat_orbit )&&
			(0 == MEMCMP(s1->sat_name,s2->sat_name,s1->name_len)))
			return TRUE;
	}
	else if(n_type == TYPE_TP_NODE)
	{
		 T_NODE* t1=( T_NODE*)old_node;
		 T_NODE* t2=( T_NODE*)new_node;
		 if(t1->ft_type==0)
		{
			if(
			(t1->sat_id == t2->sat_id) &&
			(t1->pol == t2->pol) &&
			(((INT32)(t1->frq - t2->frq)<=TP_FRQ_GAP_S) && ((INT32)(t2->frq - t1->frq)<=TP_FRQ_GAP_S)) &&
			(((INT32)(t1->sym - t2->sym)<=TP_SYM_EDG) && ((INT32)(t2->sym - t1->sym)<=TP_SYM_EDG))
			)
			{
				t2->tp_id = t1->tp_id;
				return TRUE;
			}
		}
		else //dvbc
		{
		if((t1->sat_id==t2->sat_id)
				&&(((INT32)(t1->frq - t2->frq)<=TP_FRQ_GAP_C) && ((INT32)(t2->frq - t1->frq)<=TP_FRQ_GAP_C))
			&&(t1->FEC_inner == t2->FEC_inner))
		{
			t2->tp_id = t1->tp_id;
			return TRUE;
			}
		}
	}
	else if(n_type == TYPE_PROG_NODE)
	{
		 P_NODE* p1=( P_NODE*)old_node;
		 P_NODE* p2=( P_NODE*)new_node;
		if((p1->sat_id == p2->sat_id) && (p1->tp_id == p2->tp_id))
		{
			if(p2->prog_number!=0)
			{
				if(p1->prog_number==p2->prog_number)
				{
					p2->prog_id = p1->prog_id;
					return TRUE;
				}
			}			
			else
			{
				if((p2->av_flag==p1->av_flag)&&(p2->video_pid==p1->video_pid)
					&&(p2->pcr_pid==p1->pcr_pid))
				{
					if( p2->av_flag == 0)
					{
						if(p2->audio_pid[0]==p1->audio_pid[0])
						{
							p2->prog_id = p1->prog_id;
							return TRUE;
						}
					}
					else
					{
						UINT16 i;
						if((p1->audio_count == 0) &&(p2->audio_count ==0))
						{
							p2->prog_id = p1->prog_id;
							return TRUE;
						}
						for( i = 0; i<p1->audio_count; i++)
						{
							if(p2->audio_pid[0] == p1->audio_pid[i])
							{
								p2->prog_id = p1->prog_id;
								return TRUE;
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
}

// *****************************************************************
// Summary:
//     find node that matching specific condition
// Description:
//     The function is registered to database and called when "finding" node if the node match 
//     specific condition.
// Returns:
//     TRUE	-node matching the condition
//     FALSE	-node not matching the condition
// Parameters:
//     node_type :   [in] TYPE_SAT_NODE, TYPE_TP_NODE or TYPE_PROG_NODE
//     node :     [in] pointer to node data
//     len: [in] node data length in byte
// 
// See Also:
//
// *****************************************************************   
BOOL db_node_finder(UINT8 n_type, const void* node, UINT8 *name,UINT32 name_len)
{
	if(node==NULL||name==NULL||name_len==0)
	{

		return FALSE;
	}

	if(n_type == TYPE_PROG_NODE)
	{
		P_NODE *prog = (P_NODE *)node;
		
		return TRUE;
	}
	return FALSE;

}

