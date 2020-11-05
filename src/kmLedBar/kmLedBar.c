/*
 * kmLedBar.c
 *
 *  Created on: Jan 16, 2020
 *      Author: Krzysztof Moskwa
 *      License: GPL-3.0-or-later
 *
 *  kmAvrLedBar application for controlling WS281X chain of LEDs
 *  Copyright (C) 2020  Krzysztof Moskwa
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "kmLedBar.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../MK_WS281X/ws281x.h"
#include "../kmSwtTimer/kmSoftwareTimer.h"
#include "../kmColorTools/kmColorTools.h"
#include "../kmDebug/kmDebug.h"

// private definitions
#define KM_AVR_LB_INITIAL_TIMER_START 1
#define KM_LB_LED_UPDATE_INTERVAL 10
#define KM_LB_LED_DIM_INTERVAL 10
#define KM_LB_LED_DIM_RATE 4
//#define KM_LB_LED_USE_EXPLICIT_COLOR
#define KM_LB_TIMER_UPDATE_LEDS KM_SWT_TIMER_0
#define KM_LB_TIMER_DIM_LEDS KM_SWT_TIMER_1

#define KM_LB_MAX_EFFECTS 32

// private data & structures
static WSRGB_t _wsLeds[WS_LED_CNT];
static LedBarEffect_t _wsEffects[KM_LB_MAX_EFFECTS];

// "private" functions
void setLedColor(int8_t ledNumber, WSRGB_t rgbColor);
void dimLedColor(int8_t ledNumber, uint8_t dimRate);
void processEffects(void);

void setLedColor(int8_t ledNumber, WSRGB_t rgbColor) {

	while (ledNumber < 0) {
		ledNumber = WS_LED_CNT + ledNumber;
	}
	ledNumber %= WS_LED_CNT;

#ifdef KM_LB_LED_USE_EXPLICIT_COLOR
	_wsLeds[ledNumber] = rgbColor;
#else
	_wsLeds[ledNumber].r = _wsLeds[ledNumber].r > rgbColor.r ? _wsLeds[ledNumber].r - rgbColor.r : 0;
	_wsLeds[ledNumber].g = _wsLeds[ledNumber].g > rgbColor.g ? _wsLeds[ledNumber].g - rgbColor.g : 0;
	_wsLeds[ledNumber].b = _wsLeds[ledNumber].b > rgbColor.b ? _wsLeds[ledNumber].b - rgbColor.b : 0;

	_wsLeds[ledNumber].r = _wsLeds[ledNumber].r + rgbColor.r;
	_wsLeds[ledNumber].g = _wsLeds[ledNumber].g + rgbColor.g;
	_wsLeds[ledNumber].b = _wsLeds[ledNumber].b + rgbColor.b;

#endif
}

void dimLedColor(int8_t ledNumber, uint8_t dimRate) {
	_wsLeds[ledNumber].r = _wsLeds[ledNumber].r > dimRate ? _wsLeds[ledNumber].r - dimRate : 0;
	_wsLeds[ledNumber].g = _wsLeds[ledNumber].g > dimRate ? _wsLeds[ledNumber].g - dimRate : 0;
	_wsLeds[ledNumber].b = _wsLeds[ledNumber].b > dimRate ? _wsLeds[ledNumber].b - dimRate : 0;
}

int8_t lbAddEffect(LedBarEffect_t effect) {
	int8_t result = -1;
	for (int i = 0; i < KM_LB_MAX_EFFECTS; i++) {
		if (false == _wsEffects[i].active) {
			_wsEffects[i] = effect;
			_wsEffects[i].origPos <<= 8;
			_wsEffects[i].active = true;
			result = i;
			return result;
		}
	}
	return result;
}

void processEffects(void) {
	for (int i = 0; i < KM_LB_MAX_EFFECTS; i++) {
		if (true == _wsEffects[i].active) {
			WSRGB_t wsColor;
			RgbColor8_t rgbColor = colorHsvToRgb(_wsEffects[i].hsvColor);
			wsColor.r = rgbColor.r;
			wsColor.g = rgbColor.g;
			wsColor.b = rgbColor.b;

			setLedColor((_wsEffects[i].origPos + _wsEffects[i].modPos)>> 8, wsColor);
			if (true == _wsEffects[i].mirror) {
				setLedColor((_wsEffects[i].origPos - _wsEffects[i].modPos)>> 8, wsColor);
			}
			_wsEffects[i].modPos += _wsEffects[i].posChange;
			if (_wsEffects[i].hsvColor.v > _wsEffects[i].colorDecay) {
				_wsEffects[i].hsvColor.v -= _wsEffects[i].colorDecay;
			}
			if (0 == _wsEffects[i].currentStepsLeft) {
				_wsEffects[i].active = false;
			}
			else {
				_wsEffects[i].currentStepsLeft--;
			}
		}
	}
}

// callbacks
void callbackUpdateAllLeds(void *userData, kmSwtValueType *newTimerValue)  {
	ws281x_asm_send(_wsLeds, WS_LED_CNT, WS_PIN_NO_BV);
	*newTimerValue = KM_LB_LED_UPDATE_INTERVAL;
}

void callbackDimAllLeds(void *userData, kmSwtValueType *newTimerValue)  {
	// with used data types max number of LEDs is 85
	for (int i = 0; i < WS_LED_CNT; i++) {
		dimLedColor(i, KM_LB_LED_DIM_RATE);
		processEffects();
	}
	*newTimerValue = KM_LB_LED_DIM_INTERVAL;
}

// Implementation
void lbInit(void) {
    memset(_wsLeds, 0x00, WS_LED_CNT * 3);

	swtInit(KM_SWT_INTERVAL_10MS);

	swtRegisterCallback(KM_LB_TIMER_UPDATE_LEDS, KM_SWT_USER_DATA(0), callbackUpdateAllLeds);
	swtRegisterCallback(KM_LB_TIMER_DIM_LEDS, KM_SWT_USER_DATA(0), callbackDimAllLeds);

	swtStart(KM_LB_TIMER_UPDATE_LEDS, KM_AVR_LB_INITIAL_TIMER_START);
	swtStart(KM_LB_TIMER_DIM_LEDS, KM_AVR_LB_INITIAL_TIMER_START);
}

void lbLoop(void) {
	swtLoop();
}
