#ifndef __HELPER_FUNCTIONS_H__
#define __HELPER_FUNCTIONS_H__

#include "chip.h"

#define PORT_ID 1
#define PIN_ID1 11
#define PIN_ID2 12

/** Initializes LED 2 or LED 3 pins for blinking */
void init_board_leds_and_buttons();
/** Blinks LED 2 or LED 3. PRE: Should be initialized */
void blink(uint8_t PinId);

/** Initializes systic to the specified frequency */
void init_systick(uint32_t Frecuency);

/** Initializes DAC to output values */
void init_dac(void);

#endif  // __HELPER_FUNCTIONS_H__
