/** @file
 * @brief Main application routines.
 * kmLedBar.h
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


#ifndef KM_LEDBAR_H_
#define KM_LEDBAR_H_

#include <stdbool.h>

#include "../kmCommon/kmCommon.h"
#include "../kmColorTools/kmColorTools.h"

typedef struct {
	bool active;
	HsvColor8_t hsvColor;
	uint8_t colorDecay;
	uint16_t currentStepsLeft;
	int16_t origPos; // position divided by256 ( >> 8)
	int16_t modPos; // position divided by256 ( >> 8)
	bool mirror;
	int8_t posChange;
} LedBarEffect_t;

/**
Led Bar initialization routine.
To be issued at the beginning of main function.
*/
void lbInit(void);

/**
Led Bar loop routine to be issued periodically without delay.
*/
void lbLoop(void);

/**
@param effect definition of the effect
@result reference to to the created effect
*/
int8_t lbAddEffect(LedBarEffect_t effect);


#endif /* KM_LEDBAR_H_ */