

#include <stdint.h>

/**
 * Core api operatin result
 */
typedef enum {COP_OK = 0, COP_ERROR = 1} COPStatus;

/**
 * Sends a command to other core. Dont wait for ack
 */
COPStatus async_send_command(uint8_t DestinationCore, uint8_t Command,  uint16_t Parameter, uint32_t Timeout);

/**
 * Sends a command to other core. Wait for ack
 */
COPStatus send_command(uint8_t DestinationCore, uint8_t Command,  uint16_t Parameter, uint32_t Timeout);

/**
 * Reads a command from the cores input queue
 */
COPStatus read_command(uint8_t *SourceCore, uint8_t *Command,  uint16_t *Parameter, uint32_t Timeout);

/**
 * Sends an ack to the destination core
 */
COPStatus send_ack(uint8_t DestinationCore, uint32_t Timeout);
