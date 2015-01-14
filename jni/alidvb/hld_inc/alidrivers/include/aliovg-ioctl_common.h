#ifndef _LINUX_ALI_OVG_IOCTL_COMMON_H
#define _LINUX_ALI_OVG_IOCTL_COMMON_H

#define ALI_OVG_IOC_MAGIC 'A'
   
typedef enum {
    ali_Q_TYPE_HIGH,
    ali_Q_TYPE_MED,
    ali_Q_TYPE_LOW
} ali_Q_TYPE;

struct ali_enableQParam{
	/*In parameter*/
	ali_Q_TYPE qtype;
	unsigned int qAddr;
	int cmdSize;
};

// Allen Added for set specific register value 20110329
struct ali_regParam{
	unsigned int rAddr;
	unsigned int rValue;
} ;

struct ali_addressGen{
	unsigned int virtual_address;
	unsigned int size;
} ;

struct ali_memAllocParam{
	/*In parameter*/
	int size;
	/*Out parameter when call ALI_OPENVG_MemoryAlloc
	, In  parameter when call ALI_OPENVG_MemoryFree   */
	unsigned int phy_addr;
	/*Out parameter*/
	unsigned int virt_addr;	
        /* [20110505] for memory pool*/
        void *desc;
        const char *name;	
} ;

struct ali_setDataParam{
	unsigned int destination; /* destination address (in physical for SetData, virtual for GetData)*/
	unsigned int source; /* source data address (in virtual for SetData, phsical for GetData)*/
	int size; /* Size of source data buffer (bytes) */
} ; 

struct ali_pfnMap{
	unsigned int mapped_size;		/*Input mapped size*/
	unsigned int virt_startAddr; 	/*Input virtual address*/
	unsigned int tblAddr;    		/*Input PFN mapping table virtual address*/
} ;

struct ali_memMMUAlloc{
	/*Buffer size*/
	unsigned int size;			 	
	/*Input, for realloc case, for malloc case, min_mapped_size=size*/
	unsigned int min_mapped_size;	
	/*Input, for HW internal buffer (CPU won't access), but ALI_VIRTUAL must be valid*/
	int is_cpu_mapped_need;
	/*Input, ALI_VIRTUAL*/
	unsigned int ali_virt_addr; 
	/*Output virtual address(cpuptr+ovg addr*/
	unsigned int virt_addr; 

} ;

#define ALI_OPENVG_EnableCMDQ			_IOWR(ALI_OVG_IOC_MAGIC, 1, struct ali_enableQParam*)
#define ALI_OPENVG_TessWaitTessFinish	_IO(ALI_OVG_IOC_MAGIC, 2)
#define ALI_OPENVG_RastWaitRastFinish	_IO(ALI_OVG_IOC_MAGIC, 3)
#define ALI_OPENVG_ImageWaitImageFinish	_IO(ALI_OVG_IOC_MAGIC, 4)
#define ALI_OPENVG_MemoryAlloc				_IOWR(ALI_OVG_IOC_MAGIC, 5,struct ali_memAllocParam*)
#define ALI_OPENVG_MemoryFree				_IOW(ALI_OVG_IOC_MAGIC, 6,struct ali_memAllocParam*)
#define ALI_OPENVG_SetData				_IOW(ALI_OVG_IOC_MAGIC, 7,struct ali_setDataParam*)
#define ALI_OPENVG_GetData				_IOWR(ALI_OVG_IOC_MAGIC, 8,struct ali_setDataParam*)
#define ALI_OPENVG_Reset				_IO(ALI_OVG_IOC_MAGIC, 9)
#define ALI_OPENVG_GetHWRegister		_IOWR(ALI_OVG_IOC_MAGIC, 10, unsigned int*)
#define ALI_OPENVG_Virt2Phy				_IOWR(ALI_OVG_IOC_MAGIC, 11, struct ali_memAllocParam*)
#define ALI_OPENVG_HWWaitHWFinish		_IO(ALI_OVG_IOC_MAGIC, 12)
#define ALI_OPENVG_SetHWRegister		_IOWR(ALI_OVG_IOC_MAGIC, 13, struct ali_regParam*)
#define ALI_OPENVG_PFNMapTable			_IOWR(ALI_OVG_IOC_MAGIC, 14, struct ali_pfnMap*)
#define ALI_OPENVG_DestroyAllMemory			_IO(ALI_OVG_IOC_MAGIC, 15)
/*Below are for 3701 OpenVG HW with MMU support*/
#define ALI_OPENVG_GetPDTBaseAddr				_IOWR(ALI_OVG_IOC_MAGIC, 16, unsigned int*)
#define ALI_OPENVG_GEN_PageTable				_IOW(ALI_OVG_IOC_MAGIC, 17, struct ali_addressGen*)
/*Below are for C3701 OpenVG HW with MMU support(realloc)*/
#define ALI_OPENVG_Realloc							_IOWR(ALI_OVG_IOC_MAGIC, 18, struct ali_memMMUAlloc* )
#define ALI_OPENVG_DumpMemory				_IO(ALI_OVG_IOC_MAGIC, 19)

#endif
