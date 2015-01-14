/***************************************************************************************
*    Ali Corp. All Rights Reserved. 2008 Copyright (C)
*
*    File:    ethtool.h
*
*    Description:     Defines for ethernet mac tool.
*    History:
*           Date				Athor		Version          Reason
*	    ============================================================
*	1.	02.25.2008		Mao Feng	      Ver 0.1		Create file.
*	
***************************************************************************************/


#ifndef __ADR_ETHTOOL_H
#define __ADR_ETHTOOL_H

#include <hld/adr_hld_dev.h>
#include <adr_basic_types.h>
#include <adr_basic_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* This should work for both 32 and 64 bit userland. */
struct ethtool_cmd {
	UINT32	supported;	/* Features this interface supports */
	UINT32	advertising;	/* Features this interface advertises */
	UINT16	speed;		/* The forced speed, 10Mb, 100Mb, gigabit */
	UINT8	duplex;		/* Duplex, half or full */
	UINT32	phy_address;
	UINT8	autoneg;	/* Enable or disable autonegotiation */
};


/* wake-on-lan settings */
struct ethtool_wolinfo {
	UINT32	supported;
	UINT32	wolopts;
};


/* Indicates what features are supported by the interface. */
#define SUPPORTED_10baseT_Half		(1 << 0)
#define SUPPORTED_10baseT_Full		(1 << 1)
#define SUPPORTED_100baseT_Half	(1 << 2)
#define SUPPORTED_100baseT_Full		(1 << 3)
#define SUPPORTED_1000baseT_Half	(1 << 4)
#define SUPPORTED_1000baseT_Full	(1 << 5)
#define SUPPORTED_Autoneg			(1 << 6)
#define SUPPORTED_TP				(1 << 7)
#define SUPPORTED_AUI				(1 << 8)
#define SUPPORTED_MII				(1 << 9)
#define SUPPORTED_FIBRE			(1 << 10)
#define SUPPORTED_BNC				(1 << 11)
#define SUPPORTED_10000baseT_Full	(1 << 12)

/* Indicates what features are advertised by the interface. */
#define ADVERTISED_10baseT_Half		(1 << 0)
#define ADVERTISED_10baseT_Full		(1 << 1)
#define ADVERTISED_100baseT_Half	(1 << 2)
#define ADVERTISED_100baseT_Full	(1 << 3)
#define ADVERTISED_1000baseT_Half	(1 << 4)
#define ADVERTISED_1000baseT_Full	(1 << 5)
#define ADVERTISED_Autoneg			(1 << 6)
#define ADVERTISED_TP				(1 << 7)
#define ADVERTISED_AUI				(1 << 8)
#define ADVERTISED_MII				(1 << 9)
#define ADVERTISED_FIBRE			(1 << 10)
#define ADVERTISED_BNC				(1 << 11)
#define ADVERTISED_10000baseT_Full	(1 << 12)

/* The following are all involved in forcing a particular link
 * mode for the device for setting things.  When getting the
 * devices settings, these indicate the current mode and whether
 * it was foced up into this mode or autonegotiated.
 */

/* The forced speed, 10Mb, 100Mb, gigabit, 10GbE. */
#define SPEED_10		10
#define SPEED_100		100
#define SPEED_1000		1000
#define SPEED_10000		10000

/* Duplex, half or full. */
#define DUPLEX_HALF		0x00
#define DUPLEX_FULL		0x01


/* Enable or disable autonegotiation.  If this is set to enable,
 * the forced link modes above are completely ignored.
 */
#define AUTONEG_DISABLE		0x00
#define AUTONEG_ENABLE		0x01

/* Wake-On-Lan options. */
#define WAKE_PHY			(1 << 0)
#define WAKE_UCAST			(1 << 1)
#define WAKE_MCAST			(1 << 2)
#define WAKE_BCAST			(1 << 3)
#define WAKE_ARP			(1 << 4)
#define WAKE_MAGIC			(1 << 5)
#define WAKE_MAGICSECURE	(1 << 6) /* only meaningful if WAKE_MAGIC */
#define WAKE_SAMPLE		(1 << 7)


/* ioctl cmds.*/
#define MAC_G_MII_PHY	0x1000		/* Get address of MII PHY in use. */
#define MAC_G_MII_REG	0x1001		/* Read MII PHY register.	*/
#define MAC_S_MII_REG	0x1002		/* Write MII PHY register.	*/


#ifdef __cplusplus
}
#endif
#endif /* _ETHTOOL_H */

