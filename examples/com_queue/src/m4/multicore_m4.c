

#include "chip.h"
#include "gpio_18xx_43xx.h"
#include "start_m0_core.h"
#include "core_api.h"

#define LED1_PORT_ID 0
#define LED1_PIN_ID 14

#define LED2_PORT_ID 1
#define LED2_PIN_ID 11

#define LED3_PORT_ID 1
#define LED3_PIN_ID 12

extern uint32_t __m0_core_isr_vectors_start__;

void M0CORE_IRQHandler(void) {
	// TODO - Corregir. En caso que se acumulen varios mensajes en el queue este codigo solo lee el primero

	LPC_CREG->M0APPTXEVENT = 0; 	/* ACK */
	uint8_t sourcecore = 0;
	uint8_t command = 0;
	uint16_t parameter = 0;
	read_command(&sourcecore, &command, &parameter, 0);

	if (command == 22)
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED3_PORT_ID, LED3_PIN_ID);
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
