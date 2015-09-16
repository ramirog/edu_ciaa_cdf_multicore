

#include "chip.h"
#include "gpio_18xx_43xx.h"
#include "start_m0_core.h"
#include "comm_handler.h"
#include "comm_api.h"

#define LED1_PORT_ID 0
#define LED1_PIN_ID 14

#define LED2_PORT_ID 1
#define LED2_PIN_ID 11

#define LED3_PORT_ID 1
#define LED3_PIN_ID 12

extern uint32_t __m0_core_isr_vectors_start__;

#define E_OK 0U
#define E_OS_NOFUNC 5U

uint16_t execute_command(uint8_t Command, uint16_t Parameter) {
	if (Command == 22) {
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED3_PORT_ID, LED3_PIN_ID);
		return E_OK;
	}

	return E_OS_NOFUNC;
}

volatile int i=0;

int main(void) {
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();

	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, LED1_PORT_ID, LED1_PIN_ID);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, LED2_PORT_ID, LED2_PIN_ID);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, LED3_PORT_ID, LED3_PIN_ID);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED3_PORT_ID, LED3_PIN_ID);

	NVIC_EnableIRQ(M0APP_IRQn);

    // Start M0APP slave processor
	StartM0Core(&__m0_core_isr_vectors_start__);

	while(1) {
		async_send_command(1, 30, 0, 0);
		for(i=0; i<0x3FFFFF; i++);
		async_send_command(1, 31, 0, 0);
		for(i=0; i<0x3FFFFF; i++);
		async_send_command(1, 32, 0, 0);
		for(i=0; i<0x3FFFFF; i++);
	}

    return 0 ;
}
