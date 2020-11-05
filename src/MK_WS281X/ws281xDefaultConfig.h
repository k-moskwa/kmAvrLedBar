/** @file
 * @brief Default configuration options that can be overrided in main config file
 * kmSerialDefaultConfiguration.h
 *
 *
 *  Created on: Aug 10, 2020
 *      Author: Krzysztof Moskwa
 *      License: GPL-3.0-or-later
 *
 *  MK_WS281X library for AVR MCUs
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

#ifndef MK_WS281X_DEFAULT_CONFIG_H_
#define MK_WS281X_DEFAULT_CONFIG_H_

#include "../kmCommon/kmCommon.h"

// Number of LEDs
#define WS_LED_CNT		16
// Direction Port of the control signal
#define WS_DIR			DDRC
// Port of the control signal
#define WS_PORT			PORTC
// Pin of the control signal
#define WS_PIN_NO		PC0

#endif /* MK_WS281X_DEFAULT_CONFIG_H_ */
