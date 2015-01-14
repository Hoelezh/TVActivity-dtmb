#ifndef __ALI_RPC_OSDEP_H
#define __ALI_RPC_OSDEP_H

#include "ali_rpc_type.h"
#include "ali_rpc_cfg.h"

/*Here we reuse the mcapi header defination codes*/
#include "pr.h"

Int32 PR_CondVarWait_Safe(CondVar *cvar, Uint32 timeout);
Int32 PR_CondVarNotify_Safe(CondVar *cvar);

#endif
