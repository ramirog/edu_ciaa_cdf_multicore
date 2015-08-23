

#include "chip.h"
#include "gpio_18xx_43xx.h"

volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
    msTicks++;
}

void delay_ms(uint32_t ms) {
    uint32_t now = msTicks;
    while ((msTicks-now) < ms)
        ;
}

int main(void) {
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 14);

    while(1) {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, 0, 14);
		delay_ms(1000);
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 14);
		delay_ms(1000);
    }

    return 0 ;
}
