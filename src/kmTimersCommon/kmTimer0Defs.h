 /** @file
 * @brief Common definitions for Timers.
 * kmTimer0Defs.h
 *
 *  Created on: Aug 10, 2019
 *      Author: Krzysztof Moskwa
 *      License: GPL-3.0-or-later
 *
 *  kmTimersCommon library for AVR MCUs
 *  Copyright (C) 2019  Krzysztof Moskwa
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


#ifndef KM_TIMER0DEFS_H_
#define KM_TIMER0DEFS_H_

#include "../kmCommon/kmCommon.h"

#include <avr/io.h>

/// Clock select of Timer0 - No clock source (Timer/Counter stopped).
#define TCC0_STOP		0x00
/// Clock select of Timer0 - Prescaler 1 / 1
#define TCC0_PRSC_1								_BV(CS00)
/// Clock select of Timer0 - Prescaler 1 / 8
#define TCC0_PRSC_8					_BV(CS01)
/// Clock select of Timer0 - Prescaler 1 / 64
#define TCC0_PRSC_64				_BV(CS01) |	_BV(CS00)
/// Clock select of Timer0 - Prescaler 1 / 256
#define TCC0_PRSC_256	_BV(CS02)
/// Clock select of Timer0 - Prescaler 1 / 1024
#define TCC0_PRSC_1024	_BV(CS02) |				_BV(CS00)
/// External clock source on T0 pin. Clock on falling edge.
#define TCC0_EXT_T0_FAL	_BV(CS02) |	_BV(CS01)
/// External clock source on T0 pin. Clock on rising edge.
#define TCC0_EXT_T0_RIS	_BV(CS02) |	_BV(CS01) |	_BV(CS00)
/// Prescaler mask for Timer2 (allows to clear prescaler)
#define TCC0_CS_MASK	TCC0_EXT_T0_RIS

/// Timer0 mode 0 - Normal top value 0xFF
#define TCC_0_MODE_0			0x00
/// Timer0 mode 1 - PWM, Phase Correct top 0xFF
#define TCC_0_MODE_1							_BV(WGM00)
/// Timer0 mode 2 - CTC top value OCR0
#define TCC_0_MODE_2			_BV(WGM01)
/// Timer0 mode 3 - Fast PWM top value 0xFF
#define TCC_0_MODE_3			_BV(WGM01) |	_BV(WGM00)

/// Normal port operation for compare match, OC0 disconnected
#define TCC0_COMP_OUT_NORMAL	0x00
/// Toggle OC0 on compare match
#define TCC0_COMP_OUT_TOGGLE					_BV(COM00)
/// Clear OC0 on compare match
#define TCC0_COMP_OUT_CLEAR		_BV(COM01)
/// Set OC0 on compare match
#define TCC0_COMP_OUT_SET		_BV(COM01) |	_BV(COM00)

/// Normal port operation for compare match, OC0 disconnected
#define TCC0_PWM_COMP_OUT_NORMAL				0x00
/// Reserver
#define TCC0_PWM_COMP_OUT_RESERVED								_BV(COM00)
/// Clear OC0 on compare match when up-counting, set OC0 on down-counting
#define TCC0_PWM_COMP_OUT_CLEAR_UP_SET_DOWN		_BV(COM01)
/// Set OC0 on compare match when down-counting, clear OC0 on up-counting
#define TCC0_PWM_COMP_OUT_SET_UP_CLEAR_DOWN		_BV(COM01) |	_BV(COM00)

#endif /* KM_TIME0RDEFS_H_ */