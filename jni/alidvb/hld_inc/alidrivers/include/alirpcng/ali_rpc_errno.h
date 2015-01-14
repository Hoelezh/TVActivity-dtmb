#ifndef __ALI_RPC_ERRNO_H
#define __ALI_RPC_ERRNO_H

#define RPC_OS_OK	 PR_OS_OK       //0
#define RPC_OS_ERR	 PR_OS_ERR      //-1
#define RPC_OS_TIMEOUT   PR_OS_TIMEOUT  //62

#define  RPC_SUCCESS_VALUE   	0
#define  RPC_ERROR_VALUE     	-1

#define  RPC_OS_ERR_MUTEX    	-100
#define  RPC_OS_ERR_COND     	-101
#define  RPC_OS_ERR_THREAD   	-102

#define  RPC_INVOKER_ERR     	-200
#define  RPC_INVOKER_ERR_QFULL  -201   //task Q is full
#define  RPC_INVOKER_ERR_NOFUNC -202   //not found function pointer in service table

#define  RPC_SERVICE_ERR     	-300

#define  RPC_ARGS_ERR	     	-400

#define  RPC_MCAPI_ERR       	-500

#define  RPC_UTIL_ERR        	-600

#define  RPC_XDR_ERR         	-700


#endif
