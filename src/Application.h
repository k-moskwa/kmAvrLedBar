/** @file
 * @brief Main application routines.
 * Application.h
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


#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "common.h"

/**
Main application initialization routine.
To be issued at the beginning of main function.
*/
void appInit(void);

/**
Main application loop routine to be issued periodically without delay.
*/
void appLoop(void);

#endif /* APPLICATION_H_ */