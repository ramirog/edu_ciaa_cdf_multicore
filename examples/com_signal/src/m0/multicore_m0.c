

#include "chip.h"
#include "gpio_18xx_43xx.h"

#define PORT_ID 1
#define PIN_ID 12

volatile int i=0;

void M0_M4CORE_IRQHandler(void)
{
	LPC_CREG->M4TXEVENT = 0; 	/* ACK */
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, PORT_ID, PIN_ID);
}

int main(void) {
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, PORT_ID, PIN_ID);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, PORT_ID, PIN_ID);

	NVIC_EnableIRQ(M4_IRQn);

    while(1)
    {
		__DSB(); /* Data Synchronization Barrier, asegura que se completan
		los accesos a memoria antes de ejecutar la próxima instrucción (necesario
		para usar SEV). */
		__SEV(); /* SendEvent -> IRQ to M4 core */
		for(i=0; i < 0x3FFFFF; i++);
    }
    return 0;
}
