#ifndef  _ALI_CE_COMMON_H_
#define  _ALI_CE_COMMON_H_

#include <alidefinition/adf_ce.h>


#define ALI_CE_HLD_PARAM_MAX_SIZE 8
struct ali_ce_hld_param
{
	int p[ALI_CE_HLD_PARAM_MAX_SIZE];    
};

#define  IO_CE_KEY_GENERATE            						(IO_CE_BASE + 11)     
#define  IO_CE_KEY_LOAD                                     			(IO_CE_BASE + 12)
#define  IO_CE_DES_KEY_GENERATE_TWO_LEVEL                    (IO_CE_BASE + 13)
#define  IO_CE_AES_KEY_GENERATE_TWO_LEVEL                    (IO_CE_BASE + 14)
#define  IO_CE_GENERATE_CW_KEY                              		(IO_CE_BASE + 15)
#define  IO_CE_GENERATE_SINGLE_LEVEL_KEY                    	(IO_CE_BASE + 16)
#define  IO_CE_GET_DEV_HLD                                  		(IO_CE_BASE + 17)

#endif 

