
#include "queue32.h"
#include "chip.h"


unsigned int next_position(queue32_t* Queue, unsigned int CurrentPosition) {
	if (CurrentPosition < Queue->size)
		return CurrentPosition + 1;
	else
		return 0;
}


/** Write an element to other processor queue */
QOPStatus enqueue(queue32_t* Queue, uint32_t Value) {
	unsigned int next_write_position = next_position(Queue, Queue->write);
	if (next_write_position == Queue->read)
		return ICP_QUEUE_FULL;

	Queue->queue[Queue->write] = Value;
	Queue->write = next_write_position;

	__DSB();
	__SEV();

	return IPC_OK;
}

/** Reads an element from its queue */
QOPStatus dequeue(queue32_t* Queue, uint32_t *Value) {
	if (Queue->read == Queue->write)
		return ICP_QUEUE_EMTPY;

	*Value = Queue->queue[Queue->read];
	Queue->read = next_position(Queue, Queue->read);

	return IPC_OK;
}

