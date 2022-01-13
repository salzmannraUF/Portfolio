/*
 * FONTS.c
 *
 *  Created on: Apr 9, 2019
 *      Author: Raymond Salzmann & Madison Breese
 */

#include "FONTS.h"

void PERIOD(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C);
    P3OUT |= BIT1;

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0x00);
}

void POUND(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart+1);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0x0F);
    SendRAMData(0x0F);

    SendRAMData(0x0F);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x0F);
    SendRAMData(0x0F);

    SendRAMData(0x0F);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x0F);
    SendRAMData(0x0F);

    SendRAMData(0x0F);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);
}

void COLON(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C);
    P3OUT |= BIT1;

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);
}

void SLASH(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C);
    P3OUT |= BIT1;

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);
}

void ZERO(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C);
    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void ONE(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C);
    P3OUT |= BIT1;

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);
}

void TWO(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C);
    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void THREE(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C);
    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void FOUR(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C);
    P3OUT |= BIT1;

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);
}

void FIVE(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C);
    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void SIX(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void SEVEN(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);
}

void EIGHT(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void NINE(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);
}

void A(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);
}

void B(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;
    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xF0);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void C_(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void D(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xF0);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xF0);
}

void E(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void F(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);
}

void G(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void H(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);
}

void I(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xF0);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xF0);
}

void J(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0x0F);
    SendRAMData(0xFF);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0xFF);
    SendRAMData(0xF0);
}

void K(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart+1);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0xF0);

    SendRAMData(0xFF);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0xF0);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);
}

void L(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;
    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

}

void M(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart+1);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;
    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0xF0);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);
}

void N_(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart+1);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0xF0);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0xF0);
    SendRAMData(0xF0);

    SendRAMData(0x0F);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);
}

void O(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void P(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);
}

void Q(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C);
    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0x0F);
}

void R(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart+1);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xFF);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0xF0);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);
}

void S(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void T(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xF0);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);
}

void U(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x0F);

    SendRAMData(0xFF);
    SendRAMData(0xFF);
}

void V_(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart+1);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);
}

void W(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart+1);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0xF0);

    SendRAMData(0xFF);
    SendRAMData(0x0F);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);
}

void X_(uint8_t colstart,uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart+1);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0x00);
}

void Y(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart+1);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x0F);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);
}

void Z_(uint8_t colstart, uint8_t rowstart){
    SetColumnAddress(0x15,colstart,colstart+1);
    SetRowAddress(0x75,rowstart,rowstart+7);

    PrepRAM(0x5C); // Send Command to begin writing to screen

    P3OUT |= BIT1;

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x0F);

    SendRAMData(0x00);
    SendRAMData(0xF0);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xFF);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xF0);

    SendRAMData(0x0F);
    SendRAMData(0x00);

    SendRAMData(0xF0);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0x00);
    SendRAMData(0x00);

    SendRAMData(0xFF);
    SendRAMData(0xF0);

    SendRAMData(0x00);
    SendRAMData(0x00);
}



