 /** @file
 * @brief Common definitions for Timers.
 * kmTimer2Defs.h
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


#ifndef KM_TIMER2DEFS_H_
#define KM_TIMER2DEFS_H_

#include "../kmCommon/kmCommon.h"

#include <avr/io.h>

/// Clock select of Timer2 - Disabled
#define TCC2_STOP	0x00
/// Clock select of Timer2 - Prescaler 1 / 1
#define TCC2_PRSC_1								_BV(CS20)
/// Clock select of Timer2 - Prescaler 1 / 8
#define TCC2_PRSC_8					_BV(CS21)
/// Clock select of Timer2 - Prescaler 1 / 32
#define TCC2_PRSC_32				_BV(CS21) |	_BV(CS20)
/// Clock select of Timer2 - Prescaler 1 / 64
#define TCC2_PRSC_64	_BV(CS22)
/// Clock select of Timer2 - Prescaler 1 / 128
#define TCC2_PRSC_128	_BV(CS22) |				_BV(CS20)
/// Clock select of Timer2 - Prescaler 1 / 256
#define TCC2_PRSC_256	_BV(CS22) |	_BV(CS21)
/// Clock select of Timer2 - Prescaler 1 / 1024
#define TCC2_PRSC_1024	_BV(CS22) |	_BV(CS21) |	_BV(CS20)
/// Prescaler mask for Timer2 (allows to clear prescaler)
#define TCC2_CS_MASK	TCC2_PRSC_1024

/// Timer2 mode 0 - Normal top value 0xFF
#define TCC_2_MODE_0			0x00
/// Timer2 mode 1 - PWM, Phase Correct top 0xFF
#define TCC_2_MODE_1							_BV(WGM20)
/// Timer2 mode 2 - CTC top value OCR2 / OCRA
#define TCC_2_MODE_2			_BV(WGM21)
/// Timer2 mode 3 - Fast PWM top value 0xFF
#define TCC_2_MODE_3			_BV(WGM21) |	_BV(WGM20)
#if defined(AVR_CPU_SERIES_48)
#define TCC_2_MODE_1_B			0x00
#define TCC_2_MODE_2_B			0x00
#define TCC_2_MODE_3_B			0x00
#define TCC_2_MODE_4_B			0x00
/// Timer2 mode 5 - PWM, Phase correct, top value OCRA
#define TCC_2_MODE_5_B			_BV(WGM22)
/// Timer2 mode 7 - Fast PWM, top value OCRA
#define TCC_2_MODE_7_B			_BV(WGM22)
#endif

/// Normal port operation for compare match, OC2 disconnected
#define TCC2_COMP_OUT_NORMAL	0x00
/// Toggle OC2 on compare match
#define TCC2_COMP_OUT_TOGGLE					_BV(COM20)
/// Clear OC2 on compare match
#define TCC2_COMP_OUT_CLEAR		_BV(COM21)
/// Set OC2 on compare match
#define TCC2_COMP_OUT_SET		_BV(COM21) |	_BV(COM20)

/// Normal port operation for compare match, OC2 disconnected
#define TCC2_PWM_COMP_OUT_NORMAL				0x00
/// Reserver
#define TCC2_PWM_COMP_OUT_RESERVED								_BV(COM20)
/// Clear OC2 on compare match when up-counting, set OC2 on down-counting
#define TCC2_PWM_COMP_OUT_CLEAR_UP_SET_DOWN		_BV(COM21)
/// Set OC2 on compare match when down-counting, clear OC2 on up-counting
#define TCC2_PWM_COMP_OUT_SET_UP_CLEAR_DOWN		_BV(COM21) |	_BV(COM20)

#endif /* KM_TIMER2DEFS_H_ */