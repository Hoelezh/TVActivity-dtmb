#ifndef __SI_DESC_SAT_DELIVERY_H__
#define __SI_DESC_SAT_DELIVERY_H__

#include <adr_sys_config.h>
#include "si_module.h"
#include "si_nit.h"


/**
 * DVB Spec defined polarity value in delivery system descriptor.
 */
enum {
	SAT_POL_LINEAR_HORIZONAL		= 0x00,
	SAT_POL_LINEAR_VERTICAL		= 0x01,
	SAT_POL_CIRCLE_LEFT			= 0x02,
	SAT_POL_CIRCLE_RIGHT			= 0x03,
};

/**
 * name		: satellite_delivery_system_descriptor<struct>
 * description	: Satellite delivery system data defined in EN 468 300 6.2.13.2
 * tag		: 0x43
 */
struct satellite_delivery_system_descriptor {
	UINT8 descriptor_tag;
	UINT8 descriptor_length;
	UINT8 frequency[4];
	UINT8 orbital_position[2];
#if (SYS_CPU_ENDIAN == ENDIAN_LITTLE)	
	UINT8 modulation			: 5;
	UINT8 polarization			: 2;
	UINT8 west_east_flag			: 1;
#elif (SYS_CPU_ENDIAN == ENDIAN_BIG)	
	UINT8 west_east_flag			: 1;
	UINT8 polarization			: 2;
	UINT8 modulation			: 5;
#else
#error "please check your SYS_CPU_ENDIAN setting in <adr_sys_config.h>"
#endif	
	UINT8 symbol_rate[3];
#if (SYS_CPU_ENDIAN == ENDIAN_LITTLE)	
	UINT8 FEC_inner				: 4;
	UINT8 symbol_rate_lo			: 4;
#elif (SYS_CPU_ENDIAN == ENDIAN_BIG)	
	UINT8 symbol_rate_lo			: 4;
	UINT8 FEC_inner				: 4;
#endif
}__attribute__((packed));




#ifdef __cplusplus
extern "C"
#endif

INT32 si_on_sat_delivery_desc(UINT8 tag, UINT8 length, UINT8 *data, void *priv);

#ifdef __cplusplus
}
#endif

#endif /* __SI_DESC_SAT_DELIVERY_H__ */

