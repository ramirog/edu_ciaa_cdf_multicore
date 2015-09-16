#ifndef COMM_TYPES_H_
#define COMM_TYPES_H_

#include <stdint.h>

#define PRE_PACK
#define POST_PACK	__attribute__((__packed__))

typedef union {
	PRE_PACK struct POST_PACK  {
		uint8_t core;
		uint8_t command;
		uint16_t parameter;
	};
	uint32_t value;
} Message;

typedef union {
	PRE_PACK struct POST_PACK  {
		uint8_t core;
		uint8_t command;
		uint8_t result;
		uint8_t unused;
	};
	uint32_t value;
} Ack;

#endif
