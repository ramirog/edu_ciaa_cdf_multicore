
#include "helper.h"

#include "chip.h"
#include "gpio_18xx_43xx.h"

// CODE USED TO SHOW THE PROGRAM IS RUNNING

/** Initializes leds and buttons for board */
void init_board_leds_and_buttons() {

    Chip_GPIO_Init(LPC_GPIO_PORT);

    Chip_SCU_PinMux(2,0,MD_PUP,FUNC4);  /* RGB R */
    Chip_SCU_PinMux(2,1,MD_PUP,FUNC4);  /* RGB G */
    Chip_SCU_PinMux(2,2,MD_PUP,FUNC4);  /* RGB B */

    Chip_SCU_PinMux(2,10,MD_PUP,FUNC0); /* LED1 */
    Chip_SCU_PinMux(2,11,MD_PUP,FUNC0); /* LED2 */
    Chip_SCU_PinMux(2,12,MD_PUP,FUNC0); /* LED3 */

    Chip_SCU_PinMux(1,0,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* TEC 1 */
    Chip_SCU_PinMux(1,1,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* TEC 2 */
    Chip_SCU_PinMux(1,2,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* TEC 3 */
    Chip_SCU_PinMux(1,6,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* TEC 4 */

    Chip_GPIO_SetDir(LPC_GPIO_PORT, 5,(1<<0)|(1<<1)|(1<<2),1);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 0,(1<<14),1);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 1,(1<<11)|(1<<12),1);

    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 5,(1<<0)|(1<<1)|(1<<2));
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 0,(1<<14));
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 1,(1<<11)|(1<<12));
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

