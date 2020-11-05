/*
 * Application.c
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

#include "common.h"

#include "Application.h"
#include "kmDebug/kmDebug.h"
#include "kmSwtTimer/kmSoftwareTimer.h"
#include "kmLedBar/kmLedBar.h"
#include "kmColorTools/kmColorTools.h"
#include "kmButtons/kmButtons.h"
#include "kmLCD/kmLiquidCrystal.h"

// "private" definitions
#define KM_AVR_JOY_TIMER_START 1
#define KM_AVR_JOY_TIMER_INTERVAL 100 // 100ms

#define KM_AVR_LB_TIMER_KEYBOARD KM_SWT_TIMER_2
#define KM_AVR_LB_TIMER_EFFECT_BASIC KM_SWT_TIMER_3
#define KM_AVR_LB_TIMER_EFFECT_JOYSTICK KM_SWT_TIMER_4
#define KM_AVR_LB_JOYSTICK_NORTH 8
#define KM_AVR_LB_JOYSTICK_LEDS_PER_DIRECTION 2

#define KM_LB_EFFECT_BASIC_INTERVAL_MAX 256
#define KM_LB_EFFECT_BASIC_INTERVAL_MIN 128

#define KM_JOY_BUTTON_DIR DDRC
#define KM_JOY_BUTTON_PORT PORTC
#define KM_JOY_BUTTON_IN_PORT PINC

#define KM_JOY_DIRECTION_NORTH _BV(PC2)
#define KM_JOY_DIRECTION_EAST _BV(PC3)
#define KM_JOY_DIRECTION_SOUTH _BV(PC4)
#define KM_JOY_DIRECTION_WEST _BV(PC5)
#define KM_JOY_BUTTON_FIRE _BV(PC6)

#define KM_JOY_DIRECTION_MASK \
			  KM_JOY_DIRECTION_NORTH \
			| KM_JOY_DIRECTION_EAST \
			| KM_JOY_DIRECTION_SOUTH \
			| KM_JOY_DIRECTION_WEST

typedef enum {
	  KM_JOY_NONE = 0
	, KM_JOY_N = 1
	, KM_JOY_NE = 2
	, KM_JOY_E = 3
	, KM_JOY_SE = 4
	, KM_JOY_S = 5
	, KM_JOY_SW = 6
	, KM_JOY_W = 7
	, KM_JOY_NW = 8
} JoyDirection;

typedef enum {
	  KM_JOY_BUTTON_NONE = 0
	, KM_JOY_FIRE = 1
} JoyButtons;

#define KM_JOY_BUTTON_MASK KM_JOY_BUTTON_FIRE

static uint8_t _joyPreviousDirection = 0;
static uint8_t _joyPreviousButtons = 0;
static bool _testEffectEnabled = false;

// "private" functions
void callbackEffectBasic(void *userData, kmSwtValueType *newTimerValue)  {

	if (true == btnPressed()) {

		_testEffectEnabled = !_testEffectEnabled;
		btnReset();
	}
	if (false == _testEffectEnabled) {
		*newTimerValue = 20;
		return;
	} else {
		*newTimerValue = (rand() % KM_LB_EFFECT_BASIC_INTERVAL_MAX) + KM_LB_EFFECT_BASIC_INTERVAL_MIN;
	}
	
	HsvColor8_t hsvColor;
	hsvColor.h = rand() % 0xFF;
	hsvColor.s = 0xFF;
	hsvColor.v = 0xFF;

	LedBarEffect_t effect;
	effect.hsvColor = hsvColor;
	effect.currentStepsLeft = (rand() % 16 * 16)+ 128;
	effect.modPos = 0;
	effect.mirror = rand() % 2 ? true : false;
	effect.origPos = 0;
	effect.colorDecay = rand() % 2;
	effect.posChange = 2;
	effect.origPos = rand() % WS_LED_CNT;
	effect.posChange = (rand() % 8 - 4);

	lbAddEffect(effect);
}

void effectInit(void) {
	static const HsvColor8_t colorInit = {0x00, 0xFF, 0xFF}; // red

	HsvColor8_t hsvColor = colorInit;

	LedBarEffect_t effect;
	effect.hsvColor = hsvColor;
	effect.currentStepsLeft = 512;
	effect.modPos = 0;
	effect.mirror = false;
	effect.colorDecay = 1;
	effect.posChange = 4;
	effect.origPos = 0;
	for (int i = 0; i < 8; i++) {
		lbAddEffect(effect);
		effect.hsvColor.h += 0x20;
		effect.origPos += (KM_AVR_LB_JOYSTICK_LEDS_PER_DIRECTION);
	}
}

void joyInit(void) {
	// button pins set as input
	KM_JOY_BUTTON_DIR |= (KM_JOY_DIRECTION_MASK | KM_JOY_BUTTON_MASK);
	// pull-up joy button pins
	KM_JOY_BUTTON_PORT |= (KM_JOY_DIRECTION_MASK | KM_JOY_BUTTON_MASK);
}

JoyDirection joyGetDirection(void) {
	// get current status of ports
	// 0 on the input port means button/direction pressed, so logic reversed
	uint8_t joyCurrentDirection = ~KM_JOY_BUTTON_IN_PORT;
	// AND with mask, to get only bits responsible for direction
	joyCurrentDirection &= KM_JOY_DIRECTION_MASK;
	// AND with negation of previous bits, 
	// so these are set to 1 which were not previously
	joyCurrentDirection &= ~_joyPreviousDirection;
	_joyPreviousDirection = ~KM_JOY_BUTTON_IN_PORT;

	JoyDirection result = KM_JOY_NONE;
	if (joyCurrentDirection & KM_JOY_DIRECTION_NORTH) {
		result = KM_JOY_N;
		if (joyCurrentDirection & KM_JOY_DIRECTION_EAST) {
			result = KM_JOY_NE;
		} else if (joyCurrentDirection & KM_JOY_DIRECTION_WEST) {
			result = KM_JOY_NW;
		}
	} else if (joyCurrentDirection & KM_JOY_DIRECTION_SOUTH) {
		result = KM_JOY_S;
		if (joyCurrentDirection & KM_JOY_DIRECTION_EAST) {
			result = KM_JOY_SE;
			} else if (joyCurrentDirection & KM_JOY_DIRECTION_WEST) {
			result = KM_JOY_SW;
		}
	} else if (joyCurrentDirection & KM_JOY_DIRECTION_EAST) {
		result = KM_JOY_E;
	} else if (joyCurrentDirection & KM_JOY_DIRECTION_WEST) {
		result = KM_JOY_W;
	}
	return result;
}

JoyButtons joyGetButtons(void) {
	// get current status of ports
	// 0 on the port means button pressed, so logic inverted
	uint8_t joyCurrentButtons = ~KM_JOY_BUTTON_IN_PORT;
	// AND with mask, to get only bits responsible for direction
	joyCurrentButtons &= KM_JOY_BUTTON_MASK;
	// AND with negation of previous bits,
	// so these are set to 1 which were not previously
	joyCurrentButtons &= ~_joyPreviousButtons;
	_joyPreviousButtons = ~KM_JOY_BUTTON_IN_PORT;

	JoyButtons result = KM_JOY_BUTTON_NONE;

	if (joyCurrentButtons & KM_JOY_BUTTON_FIRE) {
		result = KM_JOY_FIRE;
	}
	return result;
}

void callbackEffectJoystick(void *userData, kmSwtValueType *newTimerValue)  {
	*newTimerValue = KM_AVR_JOY_TIMER_INTERVAL;
#ifndef KM_NO_DEBUG
#endif
	static const HsvColor8_t colorDirectionStatic = {0xAA, 0xFF, 0xFF}; // blue
	static const HsvColor8_t colorDirectionMoving = {0x55, 0xFF, 0xFF}; // green
	static const HsvColor8_t colorFire = {0x00, 0xFF, 0x80}; // dark red

	uint8_t direction = joyGetDirection();

	LedBarEffect_t effect;
	effect.currentStepsLeft = 128;
	effect.modPos = 0;
	effect.mirror = true;
	effect.posChange = 2;
	if (0 != direction) {
		// in case direction is not 0
		effect.hsvColor = colorDirectionStatic;
		effect.origPos = direction * KM_AVR_LB_JOYSTICK_LEDS_PER_DIRECTION + KM_AVR_LB_JOYSTICK_NORTH;
		lbAddEffect(effect);
		effect.hsvColor = colorDirectionMoving;
		effect.colorDecay = 2;
		effect.posChange = 5;
		lbAddEffect(effect);
	}

	if (joyGetButtons() & KM_JOY_FIRE) {
		effect.currentStepsLeft = 128;
		effect.origPos = 0;
		effect.hsvColor = colorFire;
		effect.mirror = true;
		effect.colorDecay = 0;
		effect.posChange = 16;
		lbAddEffect(effect);
	}
}

// Implementation
void appInit(void) {
	// Initialize all available ports as pull-up inputs
	dbPullUpAllPorts();
#ifndef KM_NO_DEBUG
	lcdInit(16, 2, LCD_5x8DOTS);
	lcdBegin();
	lcdBacklight();
	lcdClear();
	lcdPrint(APP_NAME);
	lcdSetCursor(0, 1);
	lcdPrint(APP_VERSION);
	lcdPrint(" ");
	lcdPrint(APP_YEAR);
#endif
#ifndef KM_NO_DEBUG
	// In case basic debug enabled - initialize it
	dbInit();
#endif
	lbInit();
	btnInit(KM_BUTTON_PIN);

	effectInit();
	joyInit();
	swtRegisterCallback(KM_AVR_LB_TIMER_EFFECT_BASIC, KM_SWT_USER_DATA(0), callbackEffectBasic);
	swtRegisterCallback(KM_AVR_LB_TIMER_EFFECT_JOYSTICK, KM_SWT_USER_DATA(0), callbackEffectJoystick);
	swtStart(KM_AVR_LB_TIMER_EFFECT_BASIC, KM_AVR_JOY_TIMER_START);
	swtStart(KM_AVR_LB_TIMER_EFFECT_JOYSTICK, KM_AVR_JOY_TIMER_START);
}

void appLoop(void) {
	// Loop Software Interrupts
	lbLoop();
	btnLoop();
}
