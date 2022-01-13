/*
 * OLED.h
 *
 *  Created on: Apr 9, 2019
 *      Author: Raymond Salzmann & Madison Breese
 */

#ifndef OLED_H_
#define OLED_H_

#include <msp430.h>
#include "msp430fr2355.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

//OLED
void spi_init();
void oled_init();
void SetCommandLock(uint8_t, uint8_t);
void SleepMode(uint8_t);
void ClockSet(uint8_t, uint8_t);
void MultiplexRatio(uint8_t, uint8_t);
void DisplayOffset(uint8_t, uint8_t);
void DisplayStartLine(uint8_t, uint8_t);
void Remap(uint8_t, uint8_t);
void VDDRegulator(uint8_t, uint8_t);
void Contrast(uint8_t, uint8_t);
void MasterContrast(uint8_t, uint8_t);
void LinearGrayscale(uint8_t);
void PhaseLength(uint8_t, uint8_t);
void PrechargeVoltage(uint8_t, uint8_t);
void PrechargePeriod(uint8_t, uint8_t);
void VCOMH(uint8_t, uint8_t);
void DisplayMode(uint8_t);
void ExitPartialDisplay(uint8_t);
void SendRAMData(uint8_t);
void SetColumnAddress(uint8_t, uint8_t, uint8_t);
void SetRowAddress(uint8_t, uint8_t, uint8_t);
void PrepRAM(uint8_t);
void SetGPIO(uint8_t, uint8_t);
void ClearRAM(void);
void ClearRAM_ECG (void);
void erase(uint8_t,uint8_t,uint8_t);
void delay_ms(unsigned int ms);

//Displays
void FirstScreen(void);
void ThermometerScreen(void);
void BMIScreen(void);
void HeartrateScreen(void);
void AgeScreen(void);
void HeartDataScreen(void);
uint8_t valueToDisplay(uint8_t value, uint8_t colstart, uint8_t rowstart);

//Results
void TempResults(uint8_t result);
void BMIResults(uint8_t result);

#endif /* OLED_H_ */
