#ifndef __ALI_RPC_UTIL_H
#define __ALI_RPC_UTIL_H

#include "ali_rpc_type.h"
#include "ali_rpc_cfg.h"
#include "ali_rpc_osdep.h"
#include "ali_rpc_debug.h"

/*We will select the AP hash to enahnce it by tony on 2013/12/13*/
/*static inline Uint32
  hash(const char* __s)
  {
    Uint32 __h = 0;
    for ( ; *__s; ++__s)
      __h = 5 * __h + *__s;
    return (__h);
  }
*/
static inline Uint32 hash(const char *str)
{
  unsigned int hash = 0;
	int i;
 
	for (i=0; *str; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		}
	}
 
	return (hash & 0x7FFFFFFF);
  	
}

#define  MAX_QUEUE_CAPACITY_SIZE  1024

typedef struct _Queue Queue;
struct _Queue {
	void *head;          /* queue head           */
	Uint32 elemsize;     /* element size         */
	Uint32 nelts;	        /* number of elements   */
	Uint32 in;           /* next empty location  */
	Uint32 out;          /* next filled location, the last filled element */
	Uint32 first;		/*The first filled element*/	
	Uint32 bounds;       /* max size of queue    */
};

/*Detects if the specific queue is full or not.*/
#define QueueFull(queue) ((queue)->nelts == (queue)->bounds)

/*Detects if the specific queue is empty or not.*/
#define QueueEmpty(queue) ((queue)->nelts == 0)

/*Initializes an array as a queue, and sets all elements of it.*/
Int32 QueueInit(void *q, Uint32 elemsize, Uint32 capacity);

/*Drops all the elements stored in the queue.*/
void QueueDeinit(void *q);

/*Push the specific element into the queue.*/
Int32 QueuePush(Queue *q, void *element);

/*Refers to the front element of the queue, in other words it is the first element of the queue. Returns NULL if the queue is empty.*/
void *QueueFront(Queue *q);

/*Refers to the back element of the queue, in other words it is the last elements of the queue. Returns NULL if the queue is empty.*/
void *QueueBack(Queue *q);

/*Pops the front element of the queue, the popped element room in the queue is empty then.*/
void QueuePop(Queue *q);

/*A circular doubly linked list manages the running invoker threads and sleep invoker threads.*/
typedef struct _CList CList;
struct _CList {
    	CList	*next;
   	CList	*prev;
//	void		*data;		/*Here we store the Invoker handle pointer, Added by tony*/
};

/*This list interface is implemented in macro prototype.*/
#define BEGIN_MACRO		do {
#define END_MACRO		} while (0)

/*
** Insert element "_e" into the list, before "_l".
*/
#define LIST_INSERT_BEFORE(_e,_l)	 \
    BEGIN_MACRO		 \
	(_e)->next = (_l);	 \
	(_e)->prev = (_l)->prev; \
	(_l)->prev->next = (_e); \
	(_l)->prev = (_e);	 \
    END_MACRO

/*
** Insert element "_e" into the list, after "_l".
*/
#define LIST_INSERT_AFTER(_e,_l)	 \
    BEGIN_MACRO		 \
	(_e)->next = (_l)->next; \
	(_e)->prev = (_l);	 \
	(_l)->next->prev = (_e); \
	(_l)->next = (_e);	 \
    END_MACRO

/*
** Return the element following element "_e"
*/
#define LIST_NEXT_LINK(_e)	 \
    	((_e)->next)
/*
** Return the element preceding element "_e"
*/
#define LIST_PREV_LINK(_e)	 \
    	((_e)->prev)

/*
** Append an element "_e" to the end of the list "_l"
*/
#define LIST_APPEND_LINK(_e,_l) LIST_INSERT_BEFORE(_e,_l)

/*
** Insert an element "_e" at the head of the list "_l"
*/
#define LIST_INSERT_LINK(_e,_l) LIST_INSERT_AFTER(_e,_l)

/* Return the head/tail of the list */
#define LIST_HEAD(_l) (_l)->next
#define LIST_TAIL(_l) (_l)->prev

/*
** Remove the element "_e" from it's circular list.
*/
#define LIST_REMOVE_LINK(_e)	       \
    BEGIN_MACRO		       \
	(_e)->prev->next = (_e)->next; \
	(_e)->next->prev = (_e)->prev; \
    END_MACRO

/*
** Remove the element "_e" from it's circular list. Also initializes the
** linkage.
*/
#define LIST_REMOVE_AND_INIT_LINK(_e)    \
    BEGIN_MACRO		       \
	(_e)->prev->next = (_e)->next; \
	(_e)->next->prev = (_e)->prev; \
	(_e)->next = (_e);	       \
	(_e)->prev = (_e);	       \
    END_MACRO

/*
** Return non-zero if the given circular list "_l" is empty, zero if the
** circular list is not empty
*/
#define LIST_IS_EMPTY(_l) \
    ((_l)->next == (_l))

/*
** Initialize a circular list
*/
#define LIST_INIT(_l)  \
    BEGIN_MACRO	   \
	(_l)->next = (_l); \
	(_l)->prev = (_l); \
    END_MACRO

#define LIST_INIT_STATIC(_l) \
    {(_l), (_l)}


/*---------------------------------------------------------
*                       Hash Table 
*----------------------------------------------------------*/
/** HASHMETER to measure hash table performance.
 */
//#define HASHMETER

//#define HASHDEBUG

#define HASH_BITS               32      /* Number of bits in HashNumber */

/* Flag bits in HashEnumerator's return value */
#define HT_ENUMERATE_NEXT       0       /* continue enumerating entries */
#define HT_ENUMERATE_STOP       1       /* stop enumerating entries */
#define HT_ENUMERATE_REMOVE     2       /* remove and free the current entry */
#define HT_ENUMERATE_UNHASH     4       /* just unhash the current entry */

#define HT_FREE_VALUE           0       /* just free the entry's value */
#define HT_FREE_ENTRY           1       /* free value and entire entry */

typedef Uint32                  HashNumber;

typedef struct _HashEntry       HashEntry;
struct _HashEntry {
    HashEntry           *next;          /* hash chain linkage */
    HashNumber          keyHash;        /* key hash function result */
    const void          *key;           /* ptr to opaque key */
    void                *value;         /* ptr to opaque value */
};

typedef HashNumber (*HashFunction)(const void *key);
typedef Int32 (*HashComparator)(const void *v1, const void *v2);
typedef Int32 (*HashEnumerator)(HashEntry *he, Int32 i);

typedef struct _HashAllocOps {
    void *              (*allocTable)(void *pool, Size_t size);
    void                (*freeTable)(void *pool, void *item);
    HashEntry *         (*allocEntry)(void *pool, const void *key);
    void                (*freeEntry)(void *pool, HashEntry *he, Uint32 flag);
} HashAllocOps;

typedef struct _HashTable  HashTable;
struct _HashTable {
    HashEntry           **buckets;      /* vector of hash buckets */
    Uint32              nentries;       /* number of entries in table */
    Uint32              nbuckets;       /* number of buckets in table */
    HashFunction        keyHash;        /* key hash function */
    HashComparator      keyCompare;     /* key comparison function */
    HashComparator      valueCompare;   /* value comparison function */
    const HashAllocOps  *allocOps;      /* allocation operations */
    void                *allocPriv;     /* allocation private data */
#ifdef HASHMETER
    Uint32              nlookups;       /* total number of lookups */
    Uint32              nsteps;         /* number of hash chains traversed */
    Uint32              ngrows;         /* number of table expansions */
    Uint32              nshrinks;       /* number of table contractions */
#endif
};



HashTable *HashTableCreate(Uint32 numBuckets, HashFunction keyHash,
                HashComparator keyCompare, HashComparator valueCompare,
                const HashAllocOps *allocOps, void *allocPriv);

void HashTableDestroy(HashTable *ht);

HashEntry *HashTableAdd(HashTable *ht, const void *key, void *value);

Bool HashTableRemove(HashTable *ht, const void *key);

void *HashTableLookup(HashTable *ht, const void *key);

void *HashTableLookupConst(HashTable *ht, const void *key);

Int32 HashTableEnumerateEntries(HashTable *ht, HashEnumerator f);
Int32 HashTableDump(HashTable *ht, HashEnumerator dump);

/** General-purpose C string hash function.
 */
HashNumber HashString(const void *key);

/** Compare strings using strcmp(), return true if equal.
 */
Int32 CompareStrings(const void *v1, const void *v2);

/** Stub function just returns v1 == v2.
 */
Int32 CompareValues(const void *v1, const void *v2);

/*Rid util*/
int Rid_test_and_set_bit(int offset, void *addr);

void Rid_clear_bit(int offset, void *addr);

int Rid_find_next_zero_bit(void *addr, int size, int offset);

int Rid_test_bit(int offset, void *addr);

#endif
