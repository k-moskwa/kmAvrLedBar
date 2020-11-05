/** @file
 * @brief Default configuration options that can be overrided in main config file
 * kmButtonsDefaultConfig.h
 *
 *  Created on: Jul 10, 2019
 *      Author: Krzysztof Moskwa
 *      License: GPL-3.0-or-later
 *
 *  kmColorTools library for AVR MCUs
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

#ifndef KM_BUTTONS_DEFAULT_CONFIG_H_
#define KM_BUTTONS_DEFAULT_CONFIG_H_

#define KM_BUTTON_DDR DDRC
#define KM_BUTTON_PORT_IN PINC
#define KM_BUTTON_PIN PC1

#endif /* KM_BUTTONS_DEFAULT_CONFIG_H_ */
