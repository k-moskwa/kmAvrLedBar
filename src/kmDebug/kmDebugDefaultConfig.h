/** @file
 * @brief Default configuration options that can be overrided in main config file
 * kmDebugDefaultConfig.h
 *
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

#ifndef KM_DEBUG_DEFAULT_CONFIG_H_
#define KM_DEBUG_DEFAULT_CONFIG_H_

#include "../kmCommon/kmCommon.h"

//#define KM_DEBUG_DISABLE

#define KM_DEBUG_DDR DDRC
#define KM_DEBUG_PORT PORTC

#define KM_DEBUG_PIN_0 PC0
//#define KM_DEBUG_PIN_1 PC1
//#define KM_DEBUG_PIN_2 PC2
//#define KM_DEBUG_PIN_3 PC3
//#define KM_DEBUG_PIN_4 PC4
//#define KM_DEBUG_PIN_5 PC5
//#define KM_DEBUG_PIN_6 PC6
//#define KM_DEBUG_PIN_7 PC7

#endif /* KM_DEBUG_DEFAULT_CONFIG_H_ */
