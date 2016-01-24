#ifndef __HELPER_FUNCTIONS_H__
#define __HELPER_FUNCTIONS_H__

#include "chip.h"

/** ------  SYSTICK ------ */

/** Initializes systick to the specified frequency */
void init_systick(uint32_t Frequency);


/** ------  BLINKING ------ */

/** Leds in board */
#define PIN_ID1 11
#define PIN_ID2 12

/** Initializes LED 2 or LED 3 pins for blinking */
void init_blink(uint8_t PinId);
/** Blinks LED 2 or LED 3. PRE: Should be initialized */
void blink(uint8_t PinId);


/** ------  DAC ------ */

/** Initializes DAC to output values */
void init_dac(void);

/** Set value to DAC */
void set_value_to_dac(uint16_t Value);


/** ------  ADC ------ */

/** ADCs in board */
#define ADC_ID1 0
#define ADC_ID2 1
#define ADC_ID3 2

/** Initializes ADC to pool values */
void init_adc_pool(uint8_t ADCId);
/** Reads value from ADC */
uint16_t read_adc_value(uint8_t ADCId);


#endif  // __HELPER_FUNCTIONS_H__
