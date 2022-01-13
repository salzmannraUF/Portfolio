/*
 * KEYPAD.h
 *
 *  Created on: Apr 17, 2019
 *      Author: Raymond Salzmann & Madison Breese
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <msp430.h>
#include "msp430fr2355.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "FONTS.h"
#include "OLED.h"
#include "CONFIGURATIONS.h"

uint8_t getKey_MENU(void);
uint8_t getKey_BMI(void);

#endif /* KEYPAD_H_ */
