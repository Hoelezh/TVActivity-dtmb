#ifndef __ALI_RPC_CFG_H
#define __ALI_RPC_CFG_H

#include "ali_rpc_type.h"

#define RPC_VERSION		101 /*V1.01*/
#define RPC_OS_TDS          0x01
#define RPC_OS_LINUX       0x00


#if defined(__ALI_TDS__)
	#define RPC_OS_TAG	 RPC_OS_TDS
#else
	#define RPC_OS_TAG	 RPC_OS_LINUX
#endif



#define BITS_PER_BYTE			8
#define BITS_CPU				(BITS_PER_BYTE * sizeof(long))
#ifndef BYTE_ORDER
#define LITTLE_ENDIAN			1234
#define BIG_ENDIAN				4321
#define BYTE_ORDER				BIG_ENDIAN
#endif

/** system is unusable */
#define LOG_EMERG       0
/** error conditions */
#define LOG_ERR         1
/** informational */
#define LOG_INFO        2
/** debug-level messages */
#define LOG_DEBUG       3

//#define DEBUG_LEVEL				LOG_DEBUG
#define DEBUG_LEVEL				LOG_ERR

/* RPC Communication Configuration */
#define RPC_CHANNEL_MAX			2

/* This RPC node identifier assignment, user can specify more remote nodes */
/* !!Changed by tony*/
//#define RPC_NODE_ID				1
//#define RPC_REMOTE_NODE_ID			2
#define  RPC_TDS_NODE_ID		1
#define  RPC_LINUX_NODE_ID		0

/* RPC channel 1, local send port to the remote receive port, vise vesa. */
/* User can specify the asymetric communication ports as well, such as:
   #define RPC_LOCAL_SEND_PORT1		2000
   #define RPC_LOCAL_RECV_PORT1		2001
   #define RPC_REMOTE_SEND_PORT1		3000
   #define RPC_REMOTE_RECV_PORT1		3001
 */
#define RPC_SEND_PORT1			1000
#define RPC_RECV_PORT1			1001

/* RPC channel 2, local send port to the remote receive port, vise versa */
#define RPC_SEND_PORT2			1002
#define RPC_RECV_PORT2			1003


/*Ensure this RETURN_BUFFER_MAX is same with peer SVC_QUEUE_SIZE*/
#if defined(__ALI_TDS__)
	#define RETURN_BUFFER_MAX		32
	#define SVC_QUEUE_SIZE                  128
	#define RPC_INVOKER_MAX                 8
#else
	#define RETURN_BUFFER_MAX		128
	#define SVC_QUEUE_SIZE                  32
	#define RPC_INVOKER_MAX                 4
#endif



#define RETRUN_BITMAP_LEN		((RETURN_BUFFER_MAX + BITS_CPU - 1)/BITS_PER_BYTE)

#if defined(__ALI_TDS__) && defined(CONFIG_ALI_RPCNG) && defined(CONFIG_ALI_MINIRPC)
#define ARG_MAX_LEN     2048
#else
#define ARG_MAX_LEN     512
#endif

#define ARG1_LEN	ARG_MAX_LEN 
#define ARG2_LEN	ARG_MAX_LEN 
#define ARG3_LEN	ARG_MAX_LEN 
#define ARG4_LEN	ARG_MAX_LEN 
#define ARG5_LEN	ARG_MAX_LEN 
#define ARG6_LEN	ARG_MAX_LEN
#define ARG7_LEN	ARG_MAX_LEN
#define ARG8_LEN	ARG_MAX_LEN 

#define PARAM1_LEN	(ARG1_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM2_LEN	(ARG2_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM3_LEN	(ARG3_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM4_LEN	(ARG4_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM5_LEN	(ARG5_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM6_LEN	(ARG6_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM7_LEN	(ARG7_LEN + sizeof(Long) + sizeof(Size_t))
#define PARAM8_LEN	(ARG8_LEN + sizeof(Long) + sizeof(Size_t))

/* Definiton to enbale RPC hash table look up table */
#define RPC_HASHTABLE_ENABLE	1

/*Endian Swap Interface*/
#if BYTE_ORDER == LITTLE_ENDIAN
#define SWAP16(x)		__bswap_16(x)
#define SWAP32(x)		__bswap_32(x)
#define SWAP64(x)		__bswap_64(x)
#elif BYTE_ORDER == BIG_ENDIAN
#define SWAP16(x)		(x)
#define SWAP32(x)		(x)
#define SWAP64(x)		(x)
#else
#error "Wrong byte order setting"
#endif

#define MAX_SERVICE_HASHTB_BUCKET_SIZE	128
/*This interface constructs the static RPC look up table.*/
Int32 CfgInit();

/*This interface destructs the RPC look up table, including statically built table and dynamicaly built table. */
Int32 CfgDeinit();


/*Below interface just is for Service symbol  hash table usage*/
Uint32 HashFunctionImt(const void *key);
Bool  HashComparatorKey(void *op1, void *op2);
Bool  HashComparatorValue(void *op1, void *op2);


#endif
