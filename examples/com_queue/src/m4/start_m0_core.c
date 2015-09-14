
#include "start_m0_core.h"
#include "chip.h"

#define M0APP_RST 24

// Returns 1(true) if reset bit is 1. Return true until the reset is asserted
#define IS_M0CORE_ACTIVE(var) ((var) & (1u << (M0APP_RST)))


void StartM0Core (uint32_t *pM0VectorStart) {
	// Ver UM10503 - 15.4.1 RGU reset control register
	// Ver UM10503 - 15.4.3 RGU reset active status register
	uint32_t reset_outputs;

	// Deactivate M0 core
	reset_outputs = LPC_RGU->RESET_ACTIVE_STATUS1;
	while (IS_M0CORE_ACTIVE(reset_outputs)) {
		// Bitwise not applied to reset_outputs because of bit convention in datasheet
		LPC_RGU->RESET_CTRL1 = ~reset_outputs | (1 << M0APP_RST);
		reset_outputs = LPC_RGU->RESET_ACTIVE_STATUS1;
	}

	// Set M0 vector position
	Chip_CREG_SetM0AppMemMap((uint32_t) pM0VectorStart);

	// Activate M0 core
	reset_outputs = LPC_RGU->RESET_ACTIVE_STATUS1;
	while(! IS_M0CORE_ACTIVE(reset_outputs)) {
		// Bitwise not applied to reset_outputs because of bit convention in datasheet
		LPC_RGU->RESET_CTRL1 = ~reset_outputs & ~(1 << M0APP_RST);
		reset_outputs = LPC_RGU->RESET_ACTIVE_STATUS1;
	};

}
