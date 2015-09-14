#ifndef ICP_QUEUE_H_
#define ICP_QUEUE_H_

#include <stdint.h>

/**
 * IPC queue comunication status
 */
typedef enum {IPC_OK = 0, ICP_QUEUE_FULL = 1, ICP_QUEUE_EMTPY = 2} QOPStatus;

/*
 * Simple queue structure. The queue array contains 'data' shared
 * between cores
 */
typedef struct {
	unsigned int size;
	volatile unsigned int read;
	volatile unsigned int write;
	uint32_t volatile * queue;
} queue32_t;

/** Write an element to a queue */
QOPStatus enqueue(queue32_t* Queue, uint32_t Value);

/** Reads an element from a queue */
QOPStatus dequeue(queue32_t* Queue, uint32_t *Value);

#endif
