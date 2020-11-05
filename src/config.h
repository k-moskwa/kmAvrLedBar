/** @file
 * @brief Project configuration definitions.
 * config.h
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

#ifndef CONFIG_H_
#define CONFIG_H_

// This line is commented cause default configuration options are override, left here as reference. 

// Enable this definition for using ATNEL ATB development kit
#define KM_USE_ATB
// This definition disables debug functionalities used in the application
//#define KM_NO_DEBUG
// Define port and direction register for debug functionalities
#define KM_DEBUG_DDR DDRC
#define KM_DEBUG_PORT PORTC
// Define debug pin of the MCU
#define KM_DEBUG_PIN_0 PC7

//#include "kmDebug/kmDebugDefaultConfig.h"
#include "kmButtons/kmButtonsDefaultConfig.h"
#include "kmSwtTimer/kmSoftwareTimerDefaultConfig.h"
#include "kmLedBar/kmLedBarDefaultConfig.h"
#include "kmLCD/kmLiquidCrystalDefaultConfig.h"
#include "MK_WS281X/ws281xDefaultConfig.h"

#endif /* CONFIG_H_ */
