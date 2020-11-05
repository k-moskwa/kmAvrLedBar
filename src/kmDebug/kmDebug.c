/*
 * kmDebug.c
 *
 *  Created on: Jul 10, 2019
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
 */

#include "kmDebug.h"

#include <avr/io.h>

void dbPullUpAllPorts(void) {
	// PULL UP all ports
#ifdef PORTA
	PORTA = 0xFF;
#endif
#ifdef PORTB
	PORTB = 0xFF;
#endif
#ifdef PORTC
	PORTC = 0xFF;
#endif
#ifdef PORTD
	PORTD = 0xFF;
#endif
#ifdef PORTE
	PORTE = 0xFF;
#endif
#ifdef PORTF
	PORTF = 0xFF;
#endif
#ifdef PORTG
	PORTG = 0xFF;
#endif
#ifdef PORTH
	PORTH = 0xFF;
#endif
}

void dbInit(void) {
#ifndef KM_DEBUG_DISABLE
	KM_DEBUG_DDR |= _BV(KM_DEBUG_PIN_0);
#ifdef KM_DEBUG_PIN_1
	KM_DEBUG_DDR |= _BV(KM_DEBUG_PIN_1);
#endif
#ifdef KM_DEBUG_PIN_2
	KM_DEBUG_DDR |= _BV(KM_DEBUG_PIN_2);
#endif
#ifdef KM_DEBUG_PIN_3
	KM_DEBUG_DDR |= _BV(KM_DEBUG_PIN_3);
#endif
#ifdef KM_DEBUG_PIN_4
	KM_DEBUG_DDR |= _BV(KM_DEBUG_PIN_4);
#endif
#ifdef KM_DEBUG_PIN_5
	KM_DEBUG_DDR |= _BV(KM_DEBUG_PIN_5);
#endif
#ifdef KM_DEBUG_PIN_6
	KM_DEBUG_DDR |= _BV(KM_DEBUG_PIN_6);
#endif
#ifdef KM_DEBUG_PIN_7
	KM_DEBUG_DDR |= _BV(KM_DEBUG_PIN_7);
#endif
#endif
}

void dbToggle(kmDebugPin pin) {
#ifndef KM_DEBUG_DISABLE
	switch(pin) {
		case DB_PIN_0: {
			KM_DEBUG_PORT ^= _BV(KM_DEBUG_PIN_0);
			break;
		}
#ifdef KM_DEBUG_PIN_1
		case DB_PIN_1: {
			KM_DEBUG_PORT ^= _BV(KM_DEBUG_PIN_1);
			break;
		}
#endif
#ifdef KM_DEBUG_PIN_2
		case DB_PIN_2: {
			KM_DEBUG_PORT ^= _BV(KM_DEBUG_PIN_2);
			break;
		}
#endif
#ifdef KM_DEBUG_PIN_3
		case DB_PIN_3: {
			KM_DEBUG_PORT ^= _BV(KM_DEBUG_PIN_3);
			break;
		}
#endif
#ifdef KM_DEBUG_PIN_4
		case DB_PIN_4: {
			KM_DEBUG_PORT ^= _BV(KM_DEBUG_PIN_4);
			break;
		}
#endif
#ifdef KM_DEBUG_PIN_5
		case DB_PIN_5: {
			KM_DEBUG_PORT ^= _BV(KM_DEBUG_PIN_5);
			break;
		}
#endif
#ifdef KM_DEBUG_PIN_6
		case DB_PIN_6: {
			KM_DEBUG_PORT ^= _BV(KM_DEBUG_PIN_6);
			break;
		}
#endif
#ifdef KM_DEBUG_PIN_7
		case DB_PIN_7: {
			KM_DEBUG_PORT ^= _BV(KM_DEBUG_PIN_7);
			break;
		}
#endif
	}
#endif
}
