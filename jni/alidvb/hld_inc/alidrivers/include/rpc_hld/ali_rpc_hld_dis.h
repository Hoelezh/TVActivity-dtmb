#ifndef __DRIVERS_ALI_RPC_HLD_DIS_H
#define __DRIVERS_ALI_RPC_HLD_DIS_H

#include "ali_rpc_hld.h"

#include <alidefinition/adf_vpo.h>

enum LLD_VP_M36F_FUNC{
	FUNC_VPO_M36_ATTACH = 0,   
	FUNC_VPO_M36_SD_ATTACH,
	FUNC_VPO_M36_VCAP_ATTACH,
	FUNC_TVE_WRITE_WSS,
	FUNC_TVE_WRITE_CC,
	FUNC_TVE_WRITE_TTX,
	FUNC_TVE_SET_VBI_STARTLINE,
    	FUNC_OSD_M36F_ATTACH,	
};

enum HLD_VP_FUNC{
	FUNC_VPO_OPEN = 0,
	FUNC_VPO_CLOSE,
	FUNC_VPO_WIN_ONOFF,
	FUNC_VPO_WIN_MODE,
	FUNC_VPO_ZOOM,
	FUNC_VPO_ASPECT_MODE,
	FUNC_VPO_TVSYS,
	FUNC_VPO_TVSYS_EX,
	FUNC_VPO_IOCTL,
	FUNC_VPO_CONFIG_SOURCE_WINDOW,
	FUNC_VPO_SET_PROGRES_INTERL,
	FUNC_TVENC_OPEN,
	FUNC_TVENC_CLOSE,
	FUNC_TVENC_SET_TVSYS,
	FUNC_TVENC_SET_TVSYS_EX,
	FUNC_TVENC_REGISTER_DAC,
	FUNC_TVENC_UNREGISTER_DAC,
	FUNC_TVENC_WRITE_WSS,
	FUNC_TVENC_WRITE_CC,
	FUNC_TVENC_WRITE_TTX,
	FUNC_TVE_ADVANCE_CONFIG,
	FUNC_VPO_WIN_ONOFF_EXT,
    FUNC_VPO_ZOOM_EXT,
};

enum OSDSys
{
	OSD_PAL = 0,
	OSD_NTSC
};

struct OSD_AF_PAR
{
	UINT8 id;
	UINT8 vd:1;
	UINT8 af:1;
	UINT8 res:6;
};

typedef struct _OSD_DRIVER_CONFIG
{
	UINT32 uMemBase;        //previous defined as __MM_OSD_START_ADDR, 16 bit align
	UINT32 uMemSize;		//previous defined as __MM_OSD_LEN,  usually 720*576/factor
							//and factor = how many pixels that 1 byte maps to

	UINT8 bStaticBlock;		//these three varialbes are only used for M33xxC
	UINT8 bDirectDraw;
	UINT8 bCacheable;

	UINT8 bVFilterEnable;   		//enable/disable osd vertical filter 
	UINT8 bP2NScaleInNormalPlay; 	//enable/disable PAL/NTSC scale in normal play mode
	UINT8 bP2NScaleInSubtitlePlay;	//enable/disable PAL/NTSC scale in subtitle play mode
	UINT16 uDViewScaleRatio[2][2];	//set multi-view scale ratio, only for M33xxC now
	struct OSD_AF_PAR af_par[4];	
	UINT32 uSDMemBase;      // memory addr for SD osd when OSD dual-output is enabled,
	                    	// and SD osd source size is not same with HD side
	UINT32 uSDMemSize;		// memory size for SD osd when OSD dual-output is enabled
	                   		// and  SD osd source size is not same with HD side

}OSD_DRIVER_CONFIG, *POSD_DRIVER_CONFIG;

struct vpo_callback
{
    VP_SRCASPRATIO_CHANGE	pSrcAspRatioChange_CallBack;
	OSAL_T_HSR_PROC_FUNC_PTR	phdmi_callback;
};

void osd_m36f_attach(char *name, OSD_DRIVER_CONFIG *attach_config);



#endif

