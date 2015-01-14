#ifndef __SI_DESC_TER_DELIVERY_H__
#define __SI_DESC_TER_DELIVERY_H__

#include <adr_sys_config.h>
#include "si_module.h"
#include "si_nit.h"

/**
 * name		: terrestrial_delivery_system_descriptor<struct>
 * description	: Cable delivery system data defined in EN 468 300 6.2.13.1
 * tag		: 0x44
 */
struct terrestrial_delivery_system_descriptor {
	UINT8 descriptor_tag;
	UINT8 descriptor_length;
	UINT8 centre_frequency[4];
#if (SYS_CPU_ENDIAN == ENDIAN_LITTLE)	
	UINT8 reserved_future_use1				: 2;
	UINT8 MPE_FEC_indicator				: 1;
	UINT8 Time_Slicing_indicator				: 1;
	UINT8 priority							: 1;
	UINT8 bandwidth						: 3;

	UINT8 code_rate_HP_stream				: 3;
	UINT8 hierarchy_information				: 3;
	UINT8 constellation						: 2;

	UINT8 other_frequency_flag				: 1;
	UINT8 transmission_mode				: 2;	
	UINT8 guard_interval					: 2;
	UINT8 code_rate_LP_stream				: 1;	
	
#elif (SYS_CPU_ENDIAN == ENDIAN_BIG)	
	UINT8 bandwidth						: 3;
	UINT8 priority							: 1;
	UINT8 Time_Slicing_indicator				: 1;
	UINT8 MPE_FEC_indicator					: 1;	
	UINT8 reserved_future_use1				: 2;
	
	UINT8 constellation						: 2;
	UINT8 hierarchy_information				: 3;
	UINT8 code_rate_HP_stream				: 3;
	
	UINT8 code_rate_LP_stream				: 3;	
	UINT8 guard_interval						: 2;
	UINT8 transmission_mode					: 2;	
	UINT8 other_frequency_flag				: 1;	
#else
#error "please check your SYS_CPU_ENDIAN setting in <adr_sys_config.h>"
#endif
	UINT8 reserved_future_use2[4];

}__attribute__((packed));



#ifdef __cplusplus
extern "C"
#endif

#if (SYS_PROJECT_FE == PROJECT_FE_DVBT && defined(AS_SUPPORT_NIT))
INT32 si_on_ter_delivery_desc(UINT8 tag, UINT8 length, UINT8 *data, void *priv);
#endif

#if defined(STAR_PROG_SEARCH_NIT_SDT_SUPPORT)
INT32 si_on_search_switch_desc(UINT8 tag, UINT8 length, UINT8 *data, void *priv);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __SI_DESC_CAB_DELIVERY_H__ */

