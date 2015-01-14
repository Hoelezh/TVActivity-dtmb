/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 Copyright (C)
*
*    File:    cic.h
*
*    Description:    This file contains all functions definition
*		             of DVB CI controler driver.
*    History:
*           Date            Athor        Version          Reason
*	    ============	=============	=========	=================
*	1.	Mar.10.2004      Justin Wu       Ver 0.1    Create file.
*
*****************************************************************************/

#ifndef __ADR_HLD_CIC_H__
#define __ADR_HLD_CIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CIC_PRINTF(...)	do{}while(0)
/* define for CI command register */
enum ci_command_register {
	CI_REG_RE				= 0x01,
	CI_REG_WE				= 0x02,
	CI_REG_IIR				= 0x10, /* CI+ */
	CI_REG_FR				= 0x40,
	CI_REG_DA				= 0x80,
	CI_REG_HC				= 0x01,
	CI_REG_SW				= 0x02,
	CI_REG_SR				= 0x04,
	CI_REG_RS				= 0x08
};

enum cic_device_ioctrl_command
{
	CIC_DRIVER_READMEM	= 0,	/* CIC driver read attribute memory command*/
	CIC_DRIVER_WRITEMEM,		/* CIC driver write attribute memory command */
	CIC_DRIVER_READIO,			/* CIC driver read byte from I/O command */
	CIC_DRIVER_WRITEIO,			/* CIC driver write byte to I/O command  */
	CIC_DRIVER_TSIGNAL,			/* CIC driver test a hardware PC card signal */
	CIC_DRIVER_SSIGNAL,			/* CIC driver set or clear a PC card pin */
	CIC_DRIVER_REQMUTEX		/*When CI and ATA share pin, they need mutex protection*/
};

enum cic_device_io_register
{
	CIC_DATA	= 0,			/* CI data register */
	CIC_CSR,					/* CI command/stauts register */
	CIC_SIZELS,					/* CI size register low bytes */
	CIC_SIZEMS,					/* CI size register high bytes */
	CIC_MEMORY,				/* CI memory space*/
	CIC_BLOCK,					/* CI block data Read/Write */
};

enum cic_device_signal
{
	CIC_EMSTREAM	= 0,		/* Emanciption stream (bypass stream to CAM) */
	CIC_ENSLOT,					/* Enable slot */
	CIC_RSTSLOT,				/* Reset slot */
	CIC_IOMEM,					/* Enable IO & memory space */
	CIC_SLOTSEL,				/* Select slot */
	CIC_CARD_DETECT,			/* CD information */
	CIC_CARD_READY				/* Ready/busy information */
};

struct cic_io_command_memrw
{
	int		slot;				/* Slot */
	UINT16  addr;				/* Attribute memory address */
	UINT16  size;				/* Number of bytes of buffer */
	UINT8  *buffer;				/* Pointer of the data buffer */
	UINT16 *rsize;				/* Number of bytes actually in data buffer */
};

struct cic_io_command_iorw
{
	int		slot;				/* Slot */
	UINT16  reg;				/* CI register */
	UINT8  *buffer;				/* CI register value */
};

struct cic_io_command_signal
{
	int		slot;				/* Slot */
	UINT8	signal;				/* CI signal */
	UINT8	status;				/* CI signal status */
};

struct cic_config_param
{
	UINT32	bus_addr;			/* CIC device control bus base address */
	UINT32	bus_id;				/* CIC device control bus id (I2C)*/
};

struct cic_req_mutex
{
	void (*cic_enter_mutex)(void);
	void (*cic_exit_mutex)(void);
};
/*
 *  Structure cic_device, the basic structure between HLD and LLD of CI
 *	controler device.
 */

struct cic_device
{
	struct hld_device   *next;		/* Next device structure */
	UINT32		type;				/* Interface hardware type */
	INT8		name[HLD_MAX_NAME_SIZE];	/* Device name */

	UINT16		flags;				/* Interface flags, status and ability */
	UINT32		base_addr;			/* Device IO base addr */

	/* Hardware privative structure */
	void		*priv;				/* pointer to private data */

/*
 *  Functions of this net device
 */
	INT32	(*init)();

	INT32	(*open)(struct cic_device *dev, void (*callback)(int slot));

	INT32	(*close)(struct cic_device *dev);

	INT32	(*read)(struct cic_device *dev, int slot, UINT16 size, UINT8 *buffer);

	INT32	(*write)(struct cic_device *dev, int slot, UINT16 size, UINT8 *buffer);

	INT32	(*do_ioctl)(struct cic_device *dev, INT32 cmd, UINT32 param);

	void	(*callback)(int slot);
};

INT32 cic_open (struct cic_device *dev, void (*callback)(int slot));
INT32 cic_close(struct cic_device *dev);
INT32 cic_read (struct cic_device *dev, int slot, UINT16 size, UINT8 *buffer);
INT32 cic_write(struct cic_device *dev, int slot, UINT16 size, UINT8 *buffer);
INT32 cic_io_control(struct cic_device *dev, INT32 cmd, UINT32 param);
INT32 cic_m3602_attach(void);

#ifdef __cplusplus
}
#endif
#endif /* __HLD_CIC_H__ */
