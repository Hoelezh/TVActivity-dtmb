#ifndef __ADR_DBG_H__
#define __ADR_DBG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DBG_FIFO_DIR				"/data"
#define DBG_FIFO_USR_TO_SERVER_PATH "/data/DBG_FIFO_USR_TO_SERVER_PATH"
#define DBG_FIFO_LEN 4096
#define DBG_FIFO_PERMS 0666

#define DBG_CMD_CNT		16
#define DBG_CMD_LEN		16
#define DBG_MSG_MAX_SIZ	(DBG_CMD_CNT * DBG_CMD_LEN)

typedef struct adr_dbg_info {
	long	arg_cnt;
	char	arg_val[DBG_MSG_MAX_SIZ];
} ADR_DBG_INFO;

#ifdef __cplusplus
}
#endif

#endif /* __ADR_DBG_H__ */
