
#ifndef __MISC_ADR_IPC_H__
#define __MISC_ADR_IPC_H__

#ifdef __cplusplus
extern "C" {
#endif


#define ADR_IPC_DEV_SEM_MAX	20
#define ADR_IPC_DEV_SHM_MAX	64

enum adr_ipc_dev
{
	ADR_IPC_HLD,
	ADR_IPC_APE,
	ADR_IPC_DECV,
	ADR_IPC_VPO,
	ADR_IPC_DECA,
	ADR_IPC_SND,
	ADR_IPC_OSD,
	ADR_IPC_AVSYNC,
	ADR_IPC_DBG_TOOL,
	ADR_IPC_CIC,
	ADR_IPC_HDMI,
	
	ADR_IPC_MAX
};

/* adr ipc key definition */
#define ADR_IPC_KEY_BASE		0x830755CC

/* adr ipc semphore operation */
int adr_ipc_semget(enum adr_ipc_dev dev, int idx, int init_val);
int adr_ipc_semlock(int sem_id);
int adr_ipc_semunlock(int sem_id);

/* adr ipc share memory operation */
int adr_ipc_shmget(enum adr_ipc_dev dev, int idx, void **buffer, int size);

#ifdef __cplusplus
}
#endif

#endif

