
#include "helper.h"

#include "chip.h"
#include "gpio_18xx_43xx.h"

// CODE USED TO SHOW THE PROGRAM IS RUNNING

void init_blink(uint8_t PinId) {
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, PORT_ID, PinId);
}

void blink(uint8_t PinId) {
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, PORT_ID, PinId);
}

void init_systick(uint32_t Frecuency) {
    SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/Frecuency);
}

void init_dac(void){
	Chip_SCU_DAC_Analog_Config(); //select DAC function
	Chip_DAC_Init(LPC_DAC); //initialize DAC
	Chip_DAC_SetBias(LPC_DAC, DAC_MAX_UPDATE_RATE_400kHz);
	Chip_DAC_SetDMATimeOut(LPC_DAC, 0xFFFF);
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, (DAC_CNT_ENA | DAC_DMA_ENA));
}

// END CODE BLINKING

