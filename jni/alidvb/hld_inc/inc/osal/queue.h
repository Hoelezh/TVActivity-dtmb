#ifndef _WDVD_TDS_QUEUE_HEADER_
#define _WDVD_TDS_QUEUE_HEADER_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct queue
{
        struct queue* next;
        struct queue* prev;
} QUEUE;

#if 0
void queue_initialize(QUEUE *);
void queue_insert(QUEUE *, QUEUE *);
void queue_delete(QUEUE *);
BOOL queue_empty_p(QUEUE *);

void queue_insert_tpri(QUEUE* entry, QUEUE* queue);
#endif
#ifdef __cplusplus
}
#endif

#endif /* _QUEUE_ */
