/****************************************************************************
 *
 *  ALi (shenzhen) Corporation, All Rights Reserved. 2012 Copyright (C)
 *
 *  File: shm_comm_device.h
 *
 *  Description: shm_comm device head file.
 *
 *  History:
 *      Date            Author          Version         Comment
 *      ====            ======          =======         =======
 *  1.  2013.01.25      David.L         0.1.000         Initial
 ****************************************************************************/
#ifndef __SHM_COMM_DEVICE_H__
#define __SHM_COMM_DEVICE_H__

#include <hld/hld_dev.h>

typedef struct shm_comm_device SHM_COMM_DEVICE;
struct shm_comm_device {
    struct      hld_device   *next;             /* Next device structure */
    UINT32		type;                           /* Interface hardware type */
    INT8		name[HLD_MAX_NAME_SIZE];        /* Device name */

    UINT16		flags;                          /* Interface flags, status and ability */
    UINT32		base_addr;                      /* Device IO base addr */

    /* Hardware privative structure */
    void		*priv;                          /* pointer to private data */

    INT32       (*init)();

    INT32       (*open)(struct shm_comm_device *);

    INT32       (*close)(struct shm_comm_device *);

    INT32       (*do_ioctl)(struct shm_comm_device *, INT32, void *);
};


/* Do nothing in see. */
#define MCOMM_INIT          0

/* Get hardware-defined number for the current core */
#define MCOMM_LOCAL_CPUID   1

/* Get hardware-defined number for the remote core */
#define MCOMM_REMOTE_CPUID  2

/* Pick up mail box contents. */
#define MCOMM_WAIT_READ     3

/* Notify the specified core that data has been made available to it */
#define MCOMM_SEND          4

/* Send sync ack to peer. */
#define MCOMM_SYNCACK       5

/* Get shared memory size. */
#define MCOMM_SHM_SIZE      6

/* Mapping to shared memory. */
#define MCOMM_MMAP          7

/* Unmapping to shared memory. */
#define MCOMM_MUNMAP        8


#define MCOMM_WAIT_READ_MINIRPC     10


/* MCAPI device type, move to hld_dev.h later */
#define HLD_DEV_TYPE_MCAPI      0x01300000


INT32 mcomm_dev_attach();
INT32 mcomm_open(struct shm_comm_device *dev);
INT32 mcomm_close(struct shm_comm_device *dev);
INT32 mcomm_ioctl(struct shm_comm_device *dev, INT32 cmd, void *arg);


#endif // __SHM_COMM_DEVICE_H__

