#ifndef __DRIVERS_ALI_RPC_SBM_H
#define __DRIVERS_ALI_RPC_SBM_H

#include "ali_rpc_hld.h"
#include <ali_sbm_common.h>

enum LLD_SBM_FUNC{
    FUNC_SBM_SEE_CREATE = 0, 
    FUNC_SBM_SEE_DESTROY,
};

int ali_rpc_sbm_create(int sbm_idx, struct sbm_config sbm_init);
int ali_rpc_sbm_destroy(int sbm_idx, int sbm_mode);
int ali_rpc_sbm_request_read(int sbm_idx, void **buf_start, int *buf_size);
void ali_rpc_sbm_update_read(int sbm_idx, int update_size);
int ali_rpc_sbm_request_write(int sbm_idx, void **buf_start, int *buf_size);
void ali_rpc_sbm_update_write(int sbm_idx, int update_size);
int ali_rpc_sbm_write_pkt(int sbm_idx, const char *buf_start, size_t buf_size);
int ali_rpc_sbm_show_valid_size(int sbm_idx, int sbm_mode, unsigned int *valid_size);
int ali_rpc_sbm_show_free_size(int sbm_idx, int sbm_mode, unsigned int *free_size);
int ali_rpc_sbm_reset(int sbm_idx, int sbm_mode);

#endif
