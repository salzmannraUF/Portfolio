/*
 * CONFIGURATIONS.h
 *
 *  Created on: Apr 17, 2019
 *      Author: Raymond Salzmann & Madison Breese
 */

#ifndef CONFIGURATIONS_H_
#define CONFIGURATIONS_H_

#include <msp430.h>
#include "msp430fr2355.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define COL0 (P6IN & BIT0)
#define COL1 (P6IN & BIT1)
#define COL2 (P6IN & BIT2)
#define COL3 (P1IN & BIT3)

#define PRESS 0x00
#define HEIGHT 0x02
#define WEIGHT 0x03
#define TEMP 0x03

////Global variables for keypad
//uint8_t key[1] = {0};
//uint8_t user[1] = {0};

//Global variables for HR
uint16_t ECG_Result[4] = {};
uint16_t ECG_Total[192] = {};

//Global variables for age
uint8_t age[2] = {};
uint8_t total_age[1] = {};

//Global variables for thermometer
float ADC_Result;
float ADC_Result1;
float ADC_Result_F;
float ADC_Result_D;
float ADC_Result_L;
float ADC_Result_H;
float ADC_Result_Temp;
uint8_t ADC_Result_L1;
uint8_t ADC_Result_H1;
uint8_t ADC_Result_D1;

void configureGPIO(void);
void ConfigureADC_temp(void);
void ConfigureADC_HR(void);

uint16_t ASCIItoUint(uint16_t ASCII);
uint8_t UintToASCII(uint8_t uint);

#endif /* CONFIGURATIONS_H_ */
