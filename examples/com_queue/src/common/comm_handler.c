
#include "chip.h"
#include "shmem.h"
#include "comm_handler.h"
#include "comm_types.h"
#include "comm_api.h"
#include "comm_defines.h"

extern sharedindex_t sharedIndex;


typedef enum {RCV_OK = 0, RCV_NO_COMMAND = 1} RCVStatus;


/**
 * Reads a command from the cores input queue
 */
RCVStatus read_command(uint8_t *SourceCore, uint8_t *Command,  uint16_t *Parameter);

/**
 * Sends an ack to the destination core
 */
void send_ack(uint8_t DestinationCore, uint16_t Result);


void CORE_IRQ_NAME(void) {
	CLEAR_CORE_IRQ = 0;

	uint8_t core = 0;
	uint8_t command = 0;
	uint16_t parameter = 0;

	RCVStatus receivestatus = read_command(&core, &command, &parameter);
	while (receivestatus != RCV_NO_COMMAND) {
		uint16_t result = execute_command(command, parameter);
		send_ack(core, result);
		receivestatus = read_command(&core, &command, &parameter);
	}
}

/** Reads an element from its queue */
RCVStatus read_command(uint8_t *SourceCore, uint8_t *Command, uint16_t *Parameter) {
	Message msg;
	QOPStatus status;
	status = dequeue(&(sharedIndex.queues[CURRENT_CORE_NUMBER]), (uint32_t*)&msg);

	if (status == IPC_OK) {
		*Command = msg.command;
		*Parameter = msg.parameter;
		*SourceCore = msg.core;
		return RCV_OK;
	} else {
		return RCV_NO_COMMAND;
	}
}

/** Sends an ack to the destination core */
void send_ack(uint8_t Core, uint16_t Result) {
	// TODO - Cada core tiene un word ack por cada core. No puede tener comunicaciones concurrentes con 2 cores.
	// Luego de enviar un comando espera ack. -> Siempre se genera ACK, el core generador puede no leerlo.
}

