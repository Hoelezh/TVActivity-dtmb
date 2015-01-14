#ifndef	__ADR_HLD_VBI_DEV_H__
#define __ADR_HLD_VBI_DEV_H__

#include <adr_basic_types.h>
#include <adr_mediatypes.h>	

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*t_TTXDecCBFunc)(UINT16 Param1,UINT8 Param2);

#define  VBI_IO  0x00000000
#define  VBI_CALL		0x00010000

#define IO_VBI_WORK_MODE_SEPERATE_TTX_SUBT              (VBI_IO + 1)
#define IO_VBI_WORK_MODE_HISTORY                        (VBI_IO + 2)
#define IO_VBI_ENGINE_OPEN                              (VBI_IO + 3)
#define IO_VBI_ENGINE_CLOSE                             (VBI_IO + 4)
#define IO_VBI_ENGINE_UPDATE_PAGE                       (VBI_IO + 5)
#define IO_VBI_ENGINE_SHOW_ON_OFF                       (VBI_IO + 6)
#define IO_VBI_ENGINE_SEND_KEY                          (VBI_IO + 7)
#define IO_VBI_ENGINE_GET_STATE                         (VBI_IO + 8)
#define IO_VBI_ENGINE_UPDATE_INIT_PAGE                  (VBI_IO + 9)
#define IO_VBI_ENGINE_UPDATE_SUBT_PAGE                  (VBI_IO + 10)
#define IO_VBI_ENGINE_SET_CUR_LANGUAGE                  (VBI_IO + 11)
#define IO_TTX_USER_DSG_FONT              				(VBI_IO + 12)
#define IO_VBI_SELECT_OUTPUT_DEVICE                     (VBI_IO + 13)   // VBI output to TV Encoder N, N = 0 or 1

#define CALL_VBI_SETOUTPUT				(VBI_CALL+1)
#define CALL_VBI_START					(VBI_CALL+2)
#define CALL_VBI_STOP					(VBI_CALL+3)
#define CALL_TTX_DEFAULT_G0_SET		(VBI_CALL+4)
#define CALL_TTXENG_INIT				(VBI_CALL+5)
#define CALL_TTXENG_ATTACH			(VBI_CALL+6)
#define CALL_ENABLE_VBI_TRANSFER		(VBI_CALL+7)	
#define CALL_GET_INITAL_PAGE			(VBI_CALL+8)	
#define CALL_GET_INITAL_PAGE_STATUS	(VBI_CALL+9)	
#define CALL_GET_FIRST_TTX_PAGE		(VBI_CALL+10)	


/*size of PBF_CB = 32 bytes < 36bytes
    reorder some field to delete the hole and decrease the structure size*/
struct PBF_CB
{
		UINT8   valid; 
		//header
		UINT8 ErasePage : 1; //c4
		UINT8 Newsflash : 1; //c5
		UINT8 Subtitle : 1; // c6
		UINT8 SuppressHeader : 1; //c7
		UINT8 UpdateIndicator : 1; //c8
		UINT8 InterruptedSequence : 1; //c9
		UINT8 InhibitDisplay : 1;  //c10
		UINT8 MagazineSerial : 1; //c11

		UINT8 NationOption; // c14	-c12	
		
		UINT8 G0_set;
		UINT8 Second_G0_set;
		//UINT8 pack24en;
        UINT8 pack24_exist : 1;
        UINT8 reserved : 7;
		
		UINT16 page_id;   //100 ~ 899 

		//link
		UINT16 link_red;		//100 ~ 899
		UINT16 link_green;
		UINT16 link_yellow;
		UINT16 link_cyan;
		UINT16 link_next;
		UINT16 link_index;

		UINT8* buf_start; 
		//UINT8 complete;  //for rd request
		//UINT8 released;       //for wr request 		

		UINT32 complement_line;

		UINT16 sub_page_id; //cloud: 0 ~ 79
		UINT32 page_update_tick;        // store page update time point for some special ts tnntc
} ;	


/*memory info structure of VBI driver*/
struct vbi_mem_map{
	/*stream buffer info*/
	UINT32	sbf_start_addr;
	UINT32	sbf_size;

	/*control buffer info*/
	UINT32	data_hdr;
	
	/*page buffer info*/
	UINT32	pbf_start_addr;
	UINT32	pbf_size;

	/*ttx sub page mem info*/
	UINT32	sub_page_start_addr;
	UINT32	sub_page_size;

	/*packet26 mem info*/
	UINT32	p26_nation_buf_start_addr;
	UINT32	p26_nation_buf_size;
	UINT32	p26_data_buf_start_addr;
	UINT32	p26_data_buf_size;

};

/*feature config structure of VBI driver*/
struct vbi_config_par{
	UINT8	ttx_by_vbi;
	UINT8 	cc_by_vbi;
	UINT8 	vps_by_vbi;
	UINT8	wss_by_vbi;

	UINT8 	hamming_8_4_enable;
	UINT8	hamming_24_16_enable;
	
	UINT8 	erase_unknown_packet;
	UINT8	parse_packet26_enable;
	UINT8	ttx_sub_page;
	UINT8	user_fast_text;
	
	struct vbi_mem_map mem_map;
};

struct ttx_page_info
{
    UINT8 num;
    UINT32 page_addr;
};

struct vbi_device
{
	struct vbi_device  *next;  /*next device */
       INT32  type;
	INT8  name[32];
	INT32  flags;

	INT32 busy;
    
	void *priv;		/* Used to be 'private' but that upsets C++ */
	
	INT32 (*init) ();
	INT32 (*init_ext)(struct vbi_config_par *);
	INT32 (*open) (struct vbi_device *);
	INT32 (*close) (struct vbi_device *);
	INT32 (*ioctl)(struct vbi_device *, UINT32 , UINT32);
	INT32 (*request_write)(struct vbi_device *, UINT32 ,struct control_block* ,UINT8** ,UINT32* );
	void (*update_write)(struct vbi_device *, UINT32);
	void (*setoutput)(struct vbi_device *,T_VBIRequest *);

	INT32 (*start) (struct vbi_device *,t_TTXDecCBFunc);
	INT32 (*stop) (struct vbi_device *);	
	INT32 (*request_page)(struct vbi_device *, UINT16,struct PBF_CB **);
	INT32 (*request_page_up)(struct vbi_device *, UINT16,struct PBF_CB **);
	INT32 (*request_page_down)(struct vbi_device *, UINT16,struct PBF_CB **);
	void (*default_g0_set)(struct vbi_device *, UINT8 );

};

#define CALC_POS(page, line, i) ((page-100)*(25*20)+line*20+(i>>1))
#define SET_P26_NATION_MAP(page, line, i, v) g_ttx_p26_nation[CALC_POS(page, line, i)] = ((g_ttx_p26_nation[CALC_POS(page, line, i)]&(0xf<<(4-(i&1)*4)))|(v<<((i&1)*4)))
#define GET_P26_NATION_MAP(page, line, i) ((g_ttx_p26_nation[CALC_POS(page, line, i)]>>((i&1)*4))&0xf)


#ifdef __cplusplus
}
#endif
#endif /*__HLD_VBI_DEV_H__*/

