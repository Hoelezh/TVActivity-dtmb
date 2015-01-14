#ifndef _ALI_SOC_COMMON_H_
#define _ALI_SOC_COMMON_H_

#include <alidefinition/adf_boot.h>
#include <alidefinition/adf_sysdef.h>
#include <alidefinition/adf_basic.h>

 
#define SYS_CPU_CLOCK                   (ali_sys_ic_get_cpu_clock() * 1000 * 1000)

struct soc_op_paras {
    unsigned char * to;
    unsigned char *from;
    int len;
};                    

struct reboot_timer{
    unsigned long *time_exp;
    unsigned long *time_cur;    
};

struct boot_timer{
    unsigned long time_exp;
    unsigned long time_cur;  
};
struct soc_usb_port {
    unsigned long usb_port;
};

struct soc_opt_paras8 {
    unsigned long addr;
    unsigned char data;    
};      

struct soc_opt_paras16 {
    unsigned long addr;
    unsigned short data;    
};      

struct soc_opt_paras32 {
    unsigned long addr;
    unsigned long data;    
};      

struct debug_level_paras {
    unsigned long level;   
};      


struct soc_memory_map
{	
	unsigned long main_start;		
	unsigned long main_end;	
	unsigned long fb_start;
	unsigned long osd_bk;	
	unsigned long see_dmx_src_buf_start;
	unsigned long see_dmx_src_buf_end;
	unsigned long see_dmx_decrypto_buf_start;
	unsigned long see_dmx_decrypto_buf_end;
	unsigned long dmx_start;
	unsigned long dmx_top;
	unsigned long see_start;
	unsigned long see_top;
	unsigned long video_start;
	unsigned long video_top;
	unsigned long frame;
	unsigned long frame_size;
	unsigned long vcap_fb;
	unsigned long vcap_fb_size;
	unsigned long vdec_vbv_start;
	unsigned long vdec_vbv_len;
	unsigned long shared_start;
	unsigned long shared_top;	

	unsigned long reserved_mem_addr;
	unsigned long reserved_mem_size;

	unsigned long media_buf_addr;
	unsigned long media_buf_size;

	unsigned long mcapi_buf_addr;
	unsigned long mcapi_buf_size;
};

struct soc_opt_see_ver {
    unsigned char *buf;
};      
enum boot_type {
    ALI_SOC_BOOT_TYPE_NOR,
    ALI_SOC_BOOT_TYPE_NAND,    
};

#define ALI_SOC_CHIP_ID       _IO('S', 3)
#define ALI_SOC_PRODUCT_ID    _IO('S', 4)
#define ALI_SOC_GET_BONDING   _IO('S', 5)
#define ALI_SOC_REV_ID        _IO('S', 6)
#define ALI_SOC_CPU_CLOCK     _IO('S', 7)
#define ALI_SOC_DRAM_CLOCK    _IO('S', 8)
#define ALI_SOC_HD_ENABLED    _IO('S', 9)
#define ALI_SOC_C3603_PRODUCT _IO('S', 10)
#define ALI_SOC_USB_NUM       _IO('S', 11)
#define ALI_SOC_USB_PORT_ENABLED   _IOR('S', 12, unsigned long)
#define ALI_SOC_NIM_M3501_SUPPORT  _IO('S' ,13)
#define ALI_SOC_NIM_SUPPORT   _IO('S', 14)
#define ALI_SOC_CI_NUM        _IO('S', 15)
#define ALI_SOC_MAC_NUM       _IO('S', 16)
#define ALI_SOC_TUNER_NUM     _IO('S', 17)
#define ALI_SOC_HD_IS_ENABLED    _IO('S', 18)
#define ALI_SOC_SATA_EANBLE   _IO('S', 19)
#define ALI_SOC_SCRAM_ENABLE  _IO('S', 20)
#define ALI_SOC_SECU_ENABLE   _IO('S', 21)
#define ALI_SOC_SPL_ENABLE    _IO('S', 22)
#define ALI_SOC_UART_ENABLE   _IO('S', 23)
#define ALI_SOC_ETJT_ENABLE   _IO('S', 24)
#define ALI_SOC_MV_ENABLE     _IO('S', 25)
#define ALI_SOC_AC3_ENABLE    _IO('S', 26)
#define ALI_SOC_DDP_ENABLE    _IO('S', 27)
#define ALI_SOC_XD_ENABLE    _IO('S', 28)
#define ALI_SOC_XDP_ENABLE   _IO('S', 29)
#define ALI_SOC_AAC_ENABLE    _IO('S', 30)
#define ALI_SOC_H264_ENABLE   _IO('S', 31)
#define ALI_SOC_MP4_ENABLE    _IO('S', 32)
#define ALI_SOC_REBOOT_GET_TIMER   _IOR('S', 33, struct reboot_timer)
#define ALI_SOC_ENTER_STANDBY      _IOW('S', 34 , struct boot_timer)
#define ALI_SOC_SET_DEBUG_LEVEL _IOW('S', 35, struct debug_level_paras)
#define ALI_SOC_GET_MEMORY_MAP _IOW('S', 36, struct soc_memory_map)
#define ALI_SOC_READ8  _IOR('S', 37, struct soc_opt_paras8)
#define ALI_SOC_WRITE8 _IOW('S', 38, struct soc_opt_paras8)
#define ALI_SOC_READ16  _IOR('S', 39, struct soc_opt_paras16)
#define ALI_SOC_WRITE16 _IOW('S', 40, struct soc_opt_paras16)
#define ALI_SOC_READ32  _IOR('S', 41, struct soc_opt_paras32)
#define ALI_SOC_WRITE32 _IOW('S', 42, struct soc_opt_paras32)
#define ALI_SOC_GET_SEE_VER _IOW('S', 43, struct soc_opt_see_ver)
#define ALI_SOC_DISABLE_SEE_PRINTF _IOR('S', 44, unsigned long)
#define ALI_SOC_HIT_SEE_HEART	_IO('S', 45)
#define ALI_SOC_ENABLE_SEE_EXCEPTION	_IO('S', 46)
#define ALI_SOC_PER_READ32  _IOR('S', 47, struct soc_opt_paras32)
#define ALI_SOC_PER_WRITE32 _IOW('S', 48, struct soc_opt_paras32)

#define ALI_SOC_READ  		_IOR('S', 48,struct soc_op_paras)
#define ALI_SOC_WRITE 		_IOW('S', 49,struct soc_op_paras)
#define ALI_SOC_REBOOT   	_IOR('S', 50, struct reboot_timer)
#define ALI_DSC_ACC_CE_DIS   _IO('S', 51)
#define ALI_SOC_MS10_ENABLE  _IO('S', 52)
#define ALI_SOC_MS11_ENABLE  _IO('S', 53)
#define ALI_SOC_RMVB_ENABLE  _IO('S', 54)
#define ALI_SOC_VC1_ENABLE   _IO('S', 55)
#define ALI_SOC_AVS_ENABLE   _IO('S', 56)
#define ALI_SOC_VP8_ENABLE   _IO('S', 57)
#define ALI_SOC_FLV_ENABLE   _IO('S', 58)
#define ALI_SOC_MG_ENABLE    _IO('S', 59)
#define ALI_SOC_GET_BOOT_TYPE   _IO('S', 60)
#define ALI_SOC_ENABLE_POWER_DOWN  _IO('S',61) 
#define ALI_SOC_SHOW_SEE_PLUGIN_INFO _IO('S',62) 
#define ALI_SOC_DRAM_SIZE   _IO('S', 63)




/********************************************** 
*******  CHIP MACRO FROM  ********
**********************************************/

#define SYS_DEFINE_NULL			0x00000000	/* NULL define */
#if defined(CONFIG_ARM)
#define ALI_SOC_BASE            0x18000000 
#elif defined(CONFIG_MIPS)
#define ALI_SOC_BASE            0xb8000000
#endif
void ali_sys_ic_get_bonding(void);
void sys_ic_enter_standby(unsigned int time_exp, unsigned int  time_cur);
void ali_sys_ic_enter_standby(unsigned long time_exp, unsigned long  time_cur);

int ali_sys_ic_get_ci_num(void);
int ali_sys_ic_get_mac_num(void);
int ali_sys_ic_get_usb_num(void);
int ali_sys_ic_get_tuner_num(void);
int ali_sys_ic_nim_m3501_support(void);
int ali_sys_ic_nim_support(void);
int ali_sys_ic_hd_is_enabled(void);
int ali_sys_ic_usb_port_enabled(unsigned long port);
int ali_sys_ic_get_hd_enabled(void);
int ali_sys_ic_sata_enable(void);
int ali_sys_ic_dram_scramble_enabled(void);
int ali_sys_ic_io_security_enabled(void);
int ali_sys_ic_split_enabled(void);
int aii_sys_ic_uart_enabled(void);
int ali_sys_ic_ejtag_enabled(void);
int ali_sys_ic_mv_is_enabled(void);
int ali_sys_ic_ac3_is_enabled(void);
int ali_sys_ic_ddplus_is_enabled(void);
int ali_sys_ic_XD_is_enabled(void);
int ali_sys_ic_XDplus_is_enabled(void);
int ali_sys_ic_aac_is_enabled(void);
int ali_sys_ic_h264_is_enabled(void);
int ali_sys_ic_mp4_is_enabled(void);
int ali_sys_ic_ms10_is_enabled(void);
int ali_sys_ic_ms11_is_enabled(void);
int ali_sys_ic_rmvb_is_enabled(void);
int ali_sys_ic_vc1_is_enabled(void);    
int ali_sys_ic_avs_is_enabled(void);
int ali_sys_ic_vp8_is_enabled(void);
int ali_sys_ic_flv_is_enabled(void);
int sys_reboot_get_timer(unsigned long *time_exp, unsigned long *time_cur);
int ali_sys_reboot_get_timer(unsigned long *time_exp, unsigned long *time_cur);
int ali_sys_ic_mg_is_enabled(void);
unsigned long ali_sys_ic_get_c3603_product(void);
unsigned long ali_sys_ic_get_product_id(void);
unsigned long ali_sys_ic_get_chip_id(void);
unsigned long ali_sys_ic_get_rev_id(void);
unsigned long ali_sys_ic_get_cpu_clock(void);
unsigned long ali_sys_ic_get_dram_clock(void); 
unsigned long ali_sys_ic_get_dram_size(void);
ADF_BOOT_BOARD_INFO * ali_get_user_data(void);
int ali_sys_ic_change_boot_type(unsigned int type);
int ali_sys_ic_revert_boot_type(void);

#endif 
