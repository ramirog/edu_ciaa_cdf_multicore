

#include "chip.h"
#include "gpio_18xx_43xx.h"
#include "core_api.h"

#define LED1_PORT_ID 0
#define LED1_PIN_ID 14

#define LED2_PORT_ID 1
#define LED2_PIN_ID 11

#define LED3_PORT_ID 1
#define LED3_PIN_ID 12

volatile int i=0;

void M0_M4CORE_IRQHandler(void) {
	// TODO - Corregir. En caso que se acumulen varios mensajes en el queue este codigo solo lee el primero

	LPC_CREG->M4TXEVENT = 0; 	/* ACK */
	uint8_t sourcecore = 0;
	uint8_t command = 0;
	uint16_t parameter = 0;
	read_command(&sourcecore, &command, &parameter, 0);

	if (command == 30)
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED1_PORT_ID, LED1_PIN_ID);
	if (command == 31)
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED2_PORT_ID, LED2_PIN_ID);
	if (command == 32)
		async_send_command(0, 22, 0, 0);
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
