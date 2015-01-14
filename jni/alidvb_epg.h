#ifndef __ALI_DVB_EPG_H__
#define __ALI_DVB_EPG_H__

#include <api/libsi/lib_epg.h>
#include "epg.h"

typedef int(* ALiDVB_EPGNotifyFn)(int type, void *param);

int ALiDVB_EPGInit(epg_config_t *param);

#endif /* __ALI_DVB_EPG_H__ */

