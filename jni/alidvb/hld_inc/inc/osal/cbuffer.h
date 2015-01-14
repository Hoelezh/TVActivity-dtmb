#ifndef _C_BUFFER_H__
#define _C_BUFFER_H__

#ifdef __cplusplus
extern "C" {
#endif


#if 1 //default config
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>


//malloc/free define
#define CBUFFER_MALLOC(s)          malloc(s)
#define CBUFFER_FREE(p)            free(p)
#define CBUFFER_MEMSET(p,s,n)      memset(p,s,n)

//mutex define
#define CBUFFER_MUTEX(m)           pthread_mutex_t m
#define CBUFFER_MUTEX_INIT(m)      pthread_mutex_init(&(m), NULL)
#define CBUFFER_MUTEX_DELETE(m)    pthread_mutex_destroy(&(m))
#define CBUFFER_MUTEX_LOCK(m)      pthread_mutex_lock(&(m))
#define CBUFFER_MUTEX_UNLOCK(m)    pthread_mutex_unlock(&(m))

//wait flag define
#define CBUFFER_FLAG(f)            waitflag f
#define CBUFFER_FLAG_INIT(f)       wait_flag_init(&(f))
#define CBUFFER_FLAG_WAIT(f,to)    wait_flag_timeout(&(f), to)
#define CBUFFER_FLAG_SET(f)        wait_flag_set(&(f))
#define CBUFFER_FLAG_DELETE(f)     wait_flag_delete(&(f))

#define DEF_WAIT_FLAG
typedef struct
{
    pthread_cond_t _cond;
    pthread_mutex_t _mutex;
} waitflag;
extern int wait_flag_init(waitflag *flag);
extern int wait_flag_delete(waitflag *flag);
extern int wait_flag_timeout(waitflag *flag, int timeout_ms);
extern int wait_flag_set(waitflag *flag);

#endif

#if 0 //don't synchronous between get and put
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CBUFFER_DEBUG(frm, args...)


//malloc/free define
#define CBUFFER_MALLOC(s)         malloc(s)
#define CBUFFER_FREE(p)           free(p)
#define CBUFFER_MEMSET(p,s,n)     memset(p,s,n)

//mutex define
#define CBUFFER_MUTEX(m)
#define CBUFFER_MUTEX_INIT(m)      0
#define CBUFFER_MUTEX_DELETE(m)    0
#define CBUFFER_MUTEX_LOCK(m)      0
#define CBUFFER_MUTEX_UNLOCK(m)    0

//wait flag define
#define CBUFFER_FLAG(f)
#define CBUFFER_FLAG_INIT(f)       0
#define CBUFFER_FLAG_WAIT(f,to)    0
#define CBUFFER_FLAG_SET(f)        0
#define CBUFFER_FLAG_DELETE(f)     0

#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//circle buffer. support FIFO
//Note:
//     do not change it's fields, only can use it's functions
//
struct cbuffer
{
    CBUFFER_MUTEX(wmutex);            //mutex for write
    CBUFFER_MUTEX(rmutex);            //mutex for read
    CBUFFER_FLAG(wflag);              //wait flag for write
    CBUFFER_FLAG(rflag);              //wait flag for read
    unsigned int  *qbuf;              //buffer
    unsigned int  size;               //buffer size
    unsigned int  wwr;                //will write point
    unsigned int  ard;                //already read point
    unsigned int  count;              //values count
    int           sync;               //synchronized flag
    int           overlap;            //overlap flag, when buffer is full,
    //clear circle buffer,remove all values
    void (*clear)(struct cbuffer *cbuf);

    /* get a value from the circle buffer and remove the value from buffer.
     * notify the writter to put values.
     * Input:
     *    cbuf       : circle buffer pointer
     *    timeout_ms : wait time out. 0: wait forever.
     * Returns:
     *   return a value get from buffer if success ,else return 0.
     */
    unsigned int (*get)(struct cbuffer *cbuf, int timeout_ms);

    /* pre-get a value from the circle buffer and not remove the value from buffer.
     * so the buffer values count will not be changed and also not notify the writter.
     * Input:
     *    cbuf       : circle buffer pointer
     *    timeout_ms : wait time out. 0: wait forever.
     * Returns:
     *   return a value get from buffer if success ,else return 0.
     */
    unsigned int (*preget)(struct cbuffer *cbuf, int timeout_ms);

    /* put a value into the circle buffer, and notify the reader to read
     * Input:
     *    cbuf       : circle buffer pointer
     *    val        : a value that will be put into the buffer. it CAN not be zero.
     *    timeout_ms : wait time out. 0: wait forever.
     * Returns:
     *   return 1 if success ,else return 0.
     */
    unsigned int (*put)(struct cbuffer *cbuf, unsigned int val, int timeout_ms);
};

/******************************************************************************
 * iqueue_create - create a new circle buffer
 * DESCRIPTION: -
 *    create a new circle buffer
 * Input:
 *    size : buffer size
 *    sync : synchronous flag
 *           0: don't synchronous between get and put,
 *           1: do synchronous between get and put
 * overlap : overlap flag
 *           0: don't remove the head data when buffer is full,
 *           1: remove the head data when buffer is full.
 * Output:
 * Returns:
 *   return the new circle buffer address if success, else return NULL
 ******************************************************************************/
struct cbuffer *iqueue_create(int size, int sync, int overlap);

/******************************************************************************
 * iqueue_delete - delete circle buffer and release resource
 * DESCRIPTION: -
 *    delete circle buffer and release resource
 * Input:
 * Output:
 * Returns:
 ******************************************************************************/
extern void iqueue_delete(struct cbuffer *cbuf);
#ifdef __cplusplus
}
#endif

#endif
