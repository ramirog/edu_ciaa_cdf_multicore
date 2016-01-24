
#include "helper.h"
#include "chip.h"
#include "adc_18xx_43xx.h"

volatile uint32_t msTicks=0;
uint16_t LastADCValue = 0;


void SysTick_Handler(void) {
    msTicks++;

    uint16_t out_value = (LastADCValue / 2);
    set_value_to_dac(out_value);
}

void blink_if_time(uint8_t PinId) {
	if (msTicks > 100000) {
		blink(PIN_ID1);
		msTicks = 0;
	}
}

int main(void) {
	init_dac();

	init_adc_pool(ADC_ID1);

	init_blink(PIN_ID1);
	init_systick(100000); // A sample every 10 us.

    while(1)
	{
    	LastADCValue = read_adc_value(ADC_ID1);
		blink_if_time(PIN_ID1);
	}
}
