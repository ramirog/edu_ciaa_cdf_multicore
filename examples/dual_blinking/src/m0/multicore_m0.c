

#include "chip.h"
#include "gpio_18xx_43xx.h"

#define PORT_ID 1
#define PIN_ID 12

void delay_ms() {
    uint32_t msTicks = 0;
    while (msTicks < 2000000)
    	msTicks++;
}

int main(void) {
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, PORT_ID, PIN_ID);

    while(1) {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, PORT_ID, PIN_ID);
		delay_ms(1000);
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_ID, PIN_ID);
		delay_ms(1000);
    }
    return 0;
}
