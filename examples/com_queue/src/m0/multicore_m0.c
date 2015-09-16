

#include "chip.h"
#include "gpio_18xx_43xx.h"
#include "comm_handler.h"
#include "comm_api.h"

#define LED1_PORT_ID 0
#define LED1_PIN_ID 14

#define LED2_PORT_ID 1
#define LED2_PIN_ID 11

#define LED3_PORT_ID 1
#define LED3_PIN_ID 12

volatile int i=0;

#define E_OK 0U
#define E_OS_NOFUNC 5U

uint16_t execute_command(uint8_t Command, uint16_t Parameter) {
	if (Command == 30) {
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED1_PORT_ID, LED1_PIN_ID);
		return E_OK;
	} else if (Command == 31) {
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED2_PORT_ID, LED2_PIN_ID);
		return E_OK;
	} else if (Command == 32) {
		async_send_command(0, 22, 0, 0);
		return E_OK;
	}

	return E_OS_NOFUNC;
}


int main(void) {
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, LED1_PORT_ID, LED1_PIN_ID);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, LED2_PORT_ID, LED2_PIN_ID);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, LED3_PORT_ID, LED3_PIN_ID);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED1_PORT_ID, LED1_PIN_ID);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED2_PORT_ID, LED2_PIN_ID);

	NVIC_EnableIRQ(M4_IRQn);

    while(1)
    {
		for(i=0; i < 0x3FFFFF; i++);
    }
    return 0;
}
