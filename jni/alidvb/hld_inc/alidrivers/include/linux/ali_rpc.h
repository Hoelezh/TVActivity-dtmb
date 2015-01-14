#ifndef __ALI_RPC_H
#define __ALI_RPC_H

#define ALI_RPC_MAX_TIMEOUT		(-1)

/* rpc apis */

/* Name : 
			ali_rpc_mutex_create
    Description :
			create the rpc mutex for the communication during the dual CPUs
    Arguments : 
    			void
    Return value:
    			<= 0 	---> fail
    			others 	---> mutex id
*/
int ali_rpc_mutex_create(void);

/* Name : 
			ali_rpc_mutex_delete
    Description :
			delete the rpc mutex
    Arguments : 
    			void
    Return value:
    			<= 0 	---> fail
    			others 	---> ok
*/
int ali_rpc_mutex_delete(int mutex_id);

/* Name : 
			ali_rpc_mutex_lock
    Description :
			lock the rpc mutex
    Arguments : 
    			int mutex_id ---> id of the rpc mutex
    			int timeout   ---> timeout value. the unit is ms
    Return value:
    			<= 0 	---> fail
    			others 	---> ok
*/
int ali_rpc_mutex_lock(int mutex_id, int timeout);

/* Name : 
			ali_rpc_mutex_unlock
    Description :
			unlock the rpc mutex
    Arguments : 
    			int mutex_id ---> id of the rpc mutex
    Return value:
    			<= 0 	---> fail
    			others 	---> ok
*/
int ali_rpc_mutex_unlock(int mutex_id);

/* Name : 
			ali_rpc_malloc_shared_mm
    Description :
			malloc the shared memory for the comminuction during the dual CPUs
    Arguments : 
    			unsigned long size ---> size of the needed buffer
    Return value:
    			<= 0 	---> fail
    			others 	---> the shared memory buffer start address 
*/
void *ali_rpc_malloc_shared_mm(unsigned long size);

/* Name : 
			ali_rpc_free_shared_mm
    Description :
			free the malloced shared memory
    Arguments : 
    			void *buf ---> the shared memory buffer start address
    			unsigned logn size ---> size of the buffer
    Return value:
    			<= 0 	---> fail
    			others 	---> ok
*/
void ali_rpc_free_shared_mm(void *buf, unsigned long size);

/* Name : 
			ali_rpc_call
    Description :
			rpc call entry
    Arguments : 
    			void *msg ---> massage buffer start address
    			void *func_p ---> function routine pointer
    			unsinged long func_desc ---> function routine description
    			void *arg_desc ---> argument structure description
    Return value:
    			the return value of the func_p routine
*/
unsigned long ali_rpc_call(void *msg, void *func_p, unsigned long func_desc, void *arg_desc);

/* Name : 
			ali_rpc_ret
    Description :
			rpc ret entry
    Arguments : 
    			void *msg ---> massage buffer start address
			unsigned long entry_func ---> function entry
    Return value:
    			none
*/
void ali_rpc_ret(unsigned long entry_func, void *msg);

void ali_rpc_spinlock(int mutex_id);

void ali_rpc_spinunlock(int mutex_id);
enum REMOTE_MODULES{
	HLD_BASE_MODULE,
	HLD_DECA_MODULE,
	HLD_SND_MODULE,
	HLD_VP_MODULE,
	LIB_ISDBTCC_MODULE,
	LIB_SUBT_MODULE,
	LIB_TTX_MODULE,
	HLD_SDEC_MODULE,
	HLD_VBI_MODULE,
	LLD_DECA_M36_MODULE,
	LLD_SND_M36_MODULE,
	LLD_VP_M36F_MODULE,
	LLD_ISDBTCC_MODULE,
	LLD_SDEC_SW_MODULE,
	LLD_VBI_M33_MODULE,
	LLD_DMX_M36F_MODULE,
	LLD_DSC_M36F_MODULE,
	LLD_CRYPTO_M36F_MODULE,
	HLD_DSC_MODULE,
	HLD_CRYPTO_MODULE,
	HLD_DECV_MODULE,
	LLD_DECV_M36_MODULE,
	LLD_DECV_AVC_MODULE,
	LIB_PE_ADV_VIDEO_ENGINE_MODULE,
	LIB_PE_MUSIC_ENGINE_MODULE,
	LIB_PE_IMAGE_ENGINE_MODULE,
	LLD_TRNG_M36F_MODULE,
	HLD_GMA_MODULE,
	LLD_GMA_M36F_MODULE,	
	LLD_DECV_AVS_MODULE,
	LLD_SBM_MODULE,
	LIB_MP4DEC_MODULE,
	HLD_AVSYNC_MODULE,
	LLD_AVSYNC_MODULE,
	LIB_MJPGDEC_MODULE,
	LIB_RVDEC_MODULE,
	LIB_VP8DEC_MODULE,
	LIB_VC1DEC_MODULE,//add by phil for vc1
	LIB_IMAGE_ENGINE_MODULE,
	BOOT_MEDIA_MODULE = 41//add by phil for boot-media
};

#define DESC_P_PARA(ind, pind, sind)       ((pind<<16)|(sind<<24))
#define DESC_P_STRU(ind, pind, sind, poff) ((pind<<16)|(sind<<24)|(poff<<2)|1)
#define DESC_STATIC_STRU(ind, size)        (size), 0, 0
#define DESC_OUTPUT_STRU(ind, size)        (size|0x10000), 0, 0
#define DESC_DYNAMIC_STRU(ind, flag, off)    ((flag)<<16|size), off, 0
#define DESC_STATIC_STRU_SET_SIZE(desc, ind, size) ((UINT32 *)desc)[1 + 3*ind]=size 
#define DESC_OUTPUT_STRU_SET_SIZE(desc, ind, size) ((UINT32 *)desc)[1 + 3*ind]=0x10000|size      
/*For example para0->xxx->yyy->zzz
//UINT32 desc_pointer_func1[] = 
//{ 
//  3, DESC_STRU(sizeof(struct), DESC_STRU(sizeof(struct)), DESC_STRU(sizeof(struct)) \
//  3, DESC_P_PARA(0, 0),        DESC_P_STRU(0, 1, off0),   DESC_P_STRU(1, 2, off1)  \
//  0, 
// };
//DESC_DYNAMIC_STRU(0, TYPE_OUTPUT|TYPE_LIST|TYPE_SIZE_UB, offset)
//  jump to void module_caller(msg, fp, funcdesc, desc)
//  return;
//  call_para_serialize(msg,desc,fp, funcdesc)  
//  void OS_RemoteCall(msg, size)
//  return;
*/
#define normal_para_serialize(x)   asm volatile ("sw $5, 4(%0); sw $6, 8(%0); sw $7, 12(%0);"::"r"(x))
#define normal_ret_unserialize(x)  asm volatile ("lw $2, 4(%0);"::"r"(x)) 

//Save all parameters into frame stack and then call function to serialize all into call msg
/*#define jump_to_func(msg, func, para0,funcdesc,desc)  \
                                   do{     \
                                        volatile unsigned long null; \
                                        register unsigned long *fp asm ("$8") = (unsigned long *)&para0; \
	                                 asm volatile ("sw $5, 4(%0); sw $6, 8(%0); sw $7, 12(%0);"::"r"(fp));\
	                                 func(msg, fp,funcdesc,desc);       \
	                                 null = 0; \

                                  }while(0)*/
/*
#define jump_to_func(msg, func, para0,funcdesc,desc)  \
                                   do{     \
                                        volatile unsigned long null[4]; \
                                        	register unsigned long a0 asm ("$4"); \
                                          register unsigned long a1 asm ("$5"); \
                                          register unsigned long a2 asm ("$6"); \
                                          register unsigned long a3 asm ("$7"); \
                                          unsigned long * fp = (unsigned long *)&para0; \
                                          fp[0] =  a0; \
                                          fp[1] =  a1; \
                                          fp[2] =  a2; \
                                          fp[3] =  a3; \
                                          func(msg, fp,funcdesc,desc);       \
                                          null[0] = 0; \
                                  }while(0)
*/

/*Added by tony on 2013/06/13 for support old/new RPC*/
#if defined(CONFIG_ALI_RPCNG)

	#define jump_to_func(msg, func, para0,funcdesc,desc)  do{}while(0)

#else

	#define jump_to_func(msg, func, para0,funcdesc,desc)  \
                                   do{     \
                                        unsigned long *fp = __builtin_apply_args();\
                                        unsigned long ret; \
                                        ret = func(msg, fp,funcdesc,desc);       \
                                         __builtin_return(&ret);            \
                                  }while(0)


#endif

#define RPC_MSG_NORMAL    0
#define RPC_MSG_RETURN    1
#define RPC_MSG_WAIT      2
#define RPC_MSG_FAILURE   3

#endif
