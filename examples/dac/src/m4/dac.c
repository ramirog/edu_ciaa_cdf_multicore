

#include "helper.h"
#include "chip.h"
#include "dac_18xx_43xx.h"
#include "gpio_18xx_43xx.h"

volatile uint32_t msTicks = 0;
uint8_t i = 0;

void SysTick_Handler(void) {
    msTicks++;
    i++;
    if (i > 20)
    	i = 0;
    Chip_DAC_UpdateValue(LPC_DAC, i*50);
}

void blink_if_time(uint8_t PinId) {
	if (msTicks > 100000) {
		blink(PIN_ID1);
		msTicks = 0;
	}
}

int main(void)
{
	init_dac();
	init_blink(PIN_ID1);
	init_systick(100000); // A sample every 10 us.

    while(1)
	{
    	blink_if_time(PIN_ID1);
	}
}


