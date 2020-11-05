 /** @file
 * @brief Common definitions for Timers.
 * kmTimerDefs.h
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


#ifndef KM_TIMERDEFS_H_
#define KM_TIMERDEFS_H_

#include "../kmCommon/kmCommon.h"
#include "kmTimer0Defs.h"
#include "kmTimer1Defs.h"
#include "kmTimer2Defs.h"

#include <avr/io.h>

/// Timers top value (255)
#define TCC_TOP_1		0xFF
/// Timers top value (4095)
#define TCC_TOP_2		0x0FFF
/// Timers top value (65535)
#define TCC_TOP_3		0xFFFF
/// Timers top value (1023)
#define TCC_TOP_4		0x03FF
/// Timers top value (511)
#define TCC_TOP_5		0x01FF

/// Timers bottom value
#define TCC_BOTOM		0x00

#endif /* KM_TIMERDEFS_H_ */