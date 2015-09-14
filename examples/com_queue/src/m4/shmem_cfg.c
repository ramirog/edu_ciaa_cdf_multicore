
#include "shmem.h"


#define LPC43XX_QUEUE_SIZE 16


__attribute__ ((used,section(".shareddata"))) uint32_t M4queue[LPC43XX_QUEUE_SIZE];
__attribute__ ((used,section(".shareddata"))) uint32_t M0queue[LPC43XX_QUEUE_SIZE];

__attribute__ ((used,section(".sharedindex"))) sharedindex_t sharedIndex = {.queues={
				         {.size = LPC43XX_QUEUE_SIZE, .read = 0, .write = 0, .queue = M4queue},
		                 {.size = LPC43XX_QUEUE_SIZE, .read = 0, .write = 0, .queue = M0queue}}};
