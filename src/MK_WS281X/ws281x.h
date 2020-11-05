/*
 * ws281x    attiny85    F_CPU = 16000000 Hz
 * 
 * Source code generated with MkAvrCalculator
 * https://atnel.pl/mkavrcalculator.html
 *
 * Created on: 1/12/2020
 *     Author: Miroslaw Kardas
*/

#ifndef WS281X_
#define WS281X_

#include "../kmCommon/kmCommon.h"

#include <stdint.h>

// Byte value of the control signal pin
#define WS_PIN_NO_BV	_BV(WS_PIN_NO)

typedef struct {
	uint8_t g;
	uint8_t r;
	uint8_t b;
} WSRGB_t;

void ws281x_asm_send(void *data, uint16_t datlen, uint8_t pin);

#endif  /* WS281X_ */
