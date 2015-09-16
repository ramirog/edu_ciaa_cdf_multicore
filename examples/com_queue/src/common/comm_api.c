

#include "comm_types.h"
#include "comm_api.h"
#include "queue32.h"
#include "shmem.h"

extern sharedindex_t sharedIndex;

/**
 * Sends a command to other core.
 */
ICStatus async_send_command(uint8_t DestinationCore, uint8_t Command,  uint16_t Parameter, uint32_t Timeout) {
	uint32_t elapsed_time = 0;
	Message msg = {.command = Command, .parameter = Parameter, .core = CURRENT_CORE_NUMBER};
	QOPStatus status;
	do {
		status = enqueue(&(sharedIndex.queues[DestinationCore]), msg.value);
		elapsed_time += 1;	// TODO - Use real time
	} while (status != IPC_OK && elapsed_time < Timeout);

	if (status == IPC_OK)
		return IC_OK;
	else
		return IC_ERROR;
}

/**
 * Sends a command to other core. Wait for ack
 */
ICStatus send_command(uint8_t DestinationCore, uint8_t Command,  uint16_t Parameter, uint16_t *Result, uint32_t Timeout) {
	uint32_t elapsed_time = 0;
	Message msg = {.command = Command, .parameter = Parameter, .core = CURRENT_CORE_NUMBER};
	QOPStatus status;
	do {
		status = enqueue(&(sharedIndex.queues[DestinationCore]), msg.value);
		elapsed_time += 1;	// TODO - Use real time
	} while (status != IPC_OK && elapsed_time < Timeout);

	if (status == IPC_OK)
		// TODO WAIT ACK - Use one uint32_t for each core in system.
		// TODO Update Result.
		return IC_OK;

	return IC_ERROR;
}
