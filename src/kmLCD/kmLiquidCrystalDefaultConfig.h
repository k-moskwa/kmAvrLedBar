/** @file
 * @brief Default configuration options that can be overrided in main config file
 * kmDebugDefaultConfig.h
 *
 *
 *  Created on: Aug 10, 2019
 *      Author: Krzysztof Moskwa
 *      License: GPL-3.0-or-later
 *
 *  kmLCD library for AVR MCUs
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

#ifndef KM_LIQUID_CRYSTAL_DEFAULT_CONFIG_H_
#define KM_LIQUID_CRYSTAL_DEFAULT_CONFIG_H_

#include "../kmCommon/kmCommon.h"

#ifndef KM_USE_ATB
#define KM_LCD_DDR DDRC
#define KM_LCD_PORT PORTC
#else
#define KM_LCD_DDR DDRA
#define KM_LCD_PORT PORTA
#endif

#endif /* KM_LIQUID_CRYSTAL_DEFAULT_CONFIG_H_ */
