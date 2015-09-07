

#include "chip.h"
#include "gpio_18xx_43xx.h"
#include "start_m0_core.h"

#define PORT_ID 1
#define PIN_ID 11

extern uint32_t __m0_core_isr_vectors_start__;

volatile int i=0;

void M0CORE_IRQHandler(void)
{
	LPC_CREG->M0APPTXEVENT = 0; 	/* ACK */
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, PORT_ID, PIN_ID);
}


int main(void) {
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();

    // Start M0APP slave processor
	StartM0Core(&__m0_core_isr_vectors_start__);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 1, 11);

	NVIC_EnableIRQ(M0APP_IRQn);

	while(1)
	{
		__DSB(); /* Data Synchronization Barrier, asegura que se completan
		los accesos a memoria antes de ejecutar la próxima instrucción (necesario
		para usar SEV). */
		__SEV(); /* SendEvent -> IRQ to M0 core */
		for(i=0; i<0x3FFFFF; i++);
	}

    return 0 ;
}
