

#include "core_api.h"
#include "queue32.h"
#include "shmem.h"

#define PRE_PACK
#define POST_PACK	__attribute__((__packed__))

extern sharedindex_t sharedIndex;

typedef union {
	PRE_PACK struct POST_PACK  {
		uint8_t command;
		uint16_t parameter;
		uint8_t sourcecore;
	};
	uint32_t value;
} Message;

/**
 * Sends a command to other core.
 */
COPStatus async_send_command(uint8_t DestinationCore, uint8_t Command,  uint16_t Parameter, uint32_t Timeout) {
	uint32_t elapsed_time = 0;
	Message msg = {.command = Command, .parameter = Parameter, .sourcecore = CURRENT_CORE_NUMBER};
	QOPStatus status;
	do {
		status = enqueue(&(sharedIndex.queues[DestinationCore]), msg.value);
		elapsed_time += 1;	// TODO - Use real time
	} while (status != IPC_OK && elapsed_time < Timeout);

	if (status == IPC_OK)
		return COP_OK;
	else
		return COP_ERROR;
}

/**
 * Sends a command to other core. Wait for ack
 */
COPStatus send_command(uint8_t DestinationCore, uint8_t Command,  uint16_t Parameter, uint32_t Timeout) {
	// TODO
	return COP_ERROR;
}

/** Reads an element from its queue */
COPStatus read_command(uint8_t *SourceCore, uint8_t *Command,  uint16_t *Parameter, uint32_t Timeout) {
	uint32_t elapsed_time = 0;
	Message msg;
	QOPStatus status;
	do {
		status = dequeue(&(sharedIndex.queues[CURRENT_CORE_NUMBER]), (uint32_t*)&msg);
		elapsed_time += 1;	// TODO - Use real time
	} while (status != IPC_OK && elapsed_time < Timeout);

	if (status == IPC_OK) {
		*Command = msg.command;
		*Parameter = msg.parameter;
		*SourceCore = msg.sourcecore;
		return COP_OK;
	} else {
		return COP_ERROR;
	}
}

/** Sends an ack to the destination core */
COPStatus send_ack(uint8_t DestinationCore, uint32_t Timeout) {
	// TODO
	return COP_ERROR;
}
