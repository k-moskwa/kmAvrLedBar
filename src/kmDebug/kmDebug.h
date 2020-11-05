/** @file
 * @brief Debug and troubleshooting functions.
 * kmDebug.h
 *
 *  Created on: Aug 10, 2019
 *      Author: Krzysztof Moskwa
 *      License: GPL-3.0-or-later
 *
 *  kmDebug library for AVR MCUs
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
 *
 *  References:
 * -# https://atnel2.blogspot.com/2014/04/puapki-programowe-debuger-na-jednej.html
 */

#ifndef KM_DEBUG_H_
#define KM_DEBUG_H_

#include "../kmCommon/kmCommon.h"

typedef enum {
	  DB_PIN_0
#ifdef KM_DEBUG_PIN_1
	, DB_PIN_1
#endif
#ifdef KM_DEBUG_PIN_2
	, DB_PIN_2
#endif
#ifdef KM_DEBUG_PIN_3
	, DB_PIN_3
#endif
#ifdef KM_DEBUG_PIN_4
	, DB_PIN_4
#endif
#ifdef KM_DEBUG_PIN_5
	, DB_PIN_5
#endif
#ifdef KM_DEBUG_PIN_6
	, DB_PIN_6
#endif
#ifdef KM_DEBUG_PIN_7
	, DB_PIN_7
#endif
} kmDebugPin;

/**
Initializes all ports to pull-up state.
\b NOTE: This method should be issued first in the main routine
*/
void dbPullUpAllPorts(void);

/**
Initializes the debug routines with specific number of dbStep calls to switch DB_PIN between states.
Following definitions to be set in config.h file @n
#define \b KM_DEBUG_DDR data direction register for debug led (e.g DDRC) @n
#define \b KM_DEBUG_PORT debug led port (e.g PORTC) @n
#define \b KM_DEBUG_PIN_X debug led pin (e.g PC1) @n
to disable debug feature completely - #define \b KM_DEBUG_DISABLE @n
@param number of steps to switch debug pin from high to low and from low to high state
*/
void dbInit(void);

/**
Issues next debug by toggling the led of specific number.
@param pin Pin number from 0 to 7. Note that only pins that have defined DEBUG_PINX are active.
*/
void dbToggle(kmDebugPin pin);

#endif /* KM_DEBUG_H_ */
