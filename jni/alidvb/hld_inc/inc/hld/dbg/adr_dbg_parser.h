#ifndef __ADR_DBG_PARSER_H__
#define __ADR_DBG_PARSER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <adr_basic_types.h>

#include "list.h"

#define DBG_ARG_INVALID	(0)
#define DBG_ARG_VALID	(1)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef unsigned char	ARG_CHK;
typedef void (*PARSE_CMD_FP)(int, char **);
typedef ARG_CHK (*PREVIEW_CMD_FP)(int, char **, char *);

typedef struct _PARSE_COMMAND_LIST
{
	struct list_head list;	// List of this structor.

	PARSE_CMD_FP parse_func;	// Real ommand executor.
	PREVIEW_CMD_FP preview_func;	// Preview all the options and arguments and change the valid indicator.

	const char *lg_cmd;	// Long command name as an option. Ex. "--help".
	const char *sh_cmd;	// Short command name as an option. Ex. "-h".

	unsigned char enable;	// Indicator of which command to be executed.
	unsigned char arg_valid;	// Indicator of whether argument(s) valid or not.
	
	char *arg_buf;	// Buffer to store argument(s).
	int arg_buf_siz;
	int arg_len;	// Argument buffer length.
	char **p_arg;
	int p_arg_siz;
	int arg_cnt;
} PARSE_COMMAND_LIST;

typedef INT32 (*GET_CMD_FP)(PARSE_COMMAND_LIST**, INT32 *);

typedef struct _DEBUG_MODULE_LIST
{
	struct list_head list;	// List of this structor.
	const char *name;	// Debug module name.
	unsigned char registered;
	const GET_CMD_FP get_cmd_list;
	struct list_head command_list;	// List head of sub-list of command.
} DEBUG_MODULE_LIST;

extern struct list_head dbg_mod_list;	// Module list head.
extern struct list_head app_mod_list;	// debug module list when Dbgtool as APP.

extern int dbg_cmd_parse(int , char** );
extern INT32 soc_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 ir_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 pan_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern int dmx_dbg_cmd_get(PARSE_COMMAND_LIST **, int *);
extern int dmx0_dbg_cmd_get(PARSE_COMMAND_LIST **, int *);
extern INT32 deca_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 snd_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 decv_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 dis_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 fb_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 tun_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 avsync_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 bw_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 osd2_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 adc_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 smc_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 ape_dbg_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
	
extern struct list_head *find_in_mod_list(const char *);
extern struct list_head *find_in_app_mod_list(const char *);
extern int cmd_list_parse_opt(struct list_head *, char *);
extern void cmd_list_parse_arg(struct list_head *, char *, char *);
extern int cmd_list_preview(struct list_head *, char *);
extern void cmd_list_exec(struct list_head *);
extern int soc_dbg_get_num(int, char **, int *, char *);
extern ARG_CHK soc_dbg_no_param_preview(int, char **, char *);
extern ARG_CHK soc_dbg_one_param_preview(int, char **, char *);
extern ARG_CHK soc_dbg_two_param_preview(int, char **, char *);
extern struct list_head *debug_module_add(const char *, PARSE_COMMAND_LIST *, int);
extern void debug_module_delete(const char *);
extern void dbg_mod_list_init(void);

extern INT32 soc_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 ir_app_cmd_get(PARSE_COMMAND_LIST **,INT32 *);
extern INT32 pan_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern int dmx_app_cmd_get(PARSE_COMMAND_LIST **, int *);
extern int dmx0_app_cmd_get(PARSE_COMMAND_LIST **, int *);
extern INT32 deca_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 snd_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 decv_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 dis_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 fb_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 tun_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 avsync_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 bw_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 osd2_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 adc_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern INT32 smc_app_cmd_get(PARSE_COMMAND_LIST **, INT32 *);
extern int debug_parser(int, char **);

#ifdef __cplusplus
}
#endif

#endif /* __ADR_DBG_PARSER_H__ */

