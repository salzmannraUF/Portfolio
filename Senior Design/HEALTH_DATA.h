/*
 * HEALTH_DATA.h
 *
 *  Created on: Apr 17, 2019
 *      Author: Raymond Salzmann & Madison Breese
 */

#ifndef HEALTH_DATA_H_
#define HEALTH_DATA_H_

#include <msp430.h>
#include "msp430fr2355.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include"CONFIGURATIONS.h"
#include"KEYPAD.h"
#include "FONTS.h"
#include "OLED.h"

//Heart Rate Functions
void getHR(void);
void displayECG(void);
void getAge(void);

//BMI Functions
void getBMI(void);
void checkBMI(uint8_t BMI);

//Thermometer Functions
void getTemp(void);

#endif /* HEALTH_DATA_H_ */
