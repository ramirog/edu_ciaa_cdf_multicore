

#ifndef __SHMEM_H__
#define __SHMEM_H__

#include "queue32.h"

#define QUEUE_COUNT 2

/*
 * Index for shared data.
 */
typedef struct {
	queue32_t queues[QUEUE_COUNT];
} sharedindex_t;



#endif  // __SHMEM_H__
