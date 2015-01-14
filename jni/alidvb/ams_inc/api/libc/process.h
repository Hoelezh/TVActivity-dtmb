#ifndef __LIB_C_PROCESS_H__
#define __LIB_C_PROCESS_H__

#ifdef __cplusplus
extern "C"
{
#endif


/* run command in shell with timeout
 * Return value
 *            0 - run command sucessfully with timeout(Unit:ms)
 *           -1 - failed to run command
 */
int amsprc_system_timeout(char *command, unsigned int timeout);

/* run command in shell
 * Return value
 *            0 - run command sucessfully
 *           -1 - failed to run command
 */
int amsprc_system(char *command);


#ifdef __cplusplus
}
#endif

#endif /* __LIB_C_PROCESS_H__ */
