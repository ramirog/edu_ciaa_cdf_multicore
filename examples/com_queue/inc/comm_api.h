

#include <stdint.h>

/**
 * Core api operatin result
 */
typedef enum {IC_OK = 0, IC_ERROR = 1, IC_TIMEOUT = 2} ICStatus;


/**
 * Sends a command to other core. Dont wait for ack
 */
ICStatus async_send_command(uint8_t DestinationCore, uint8_t Command,  uint16_t Parameter, uint32_t Timeout);

/**
 * Sends a command to other core. Wait for ack
 */
ICStatus send_command(uint8_t DestinationCore, uint8_t Command,  uint16_t Parameter, uint16_t *Result, uint32_t Timeout);

