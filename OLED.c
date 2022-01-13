 /*
 * OLED.c
 *
 *  Created on: Apr 9, 2019
 *      Author: Raymond Salzmann & Madison Breese
 */

#include "OLED.h"
#include "FONTS.h"

void spi_init(){
    P4SEL0 |= BIT5 | BIT6 | BIT7;

    UCB1CTLW0 |= UCSWRST;
    UCB1CTLW0 |= UCCKPH + UCMSB + UCMST + UCSYNC + UCMODE_0;
    UCB1CTLW0 |= UCSSEL_1;
    UCB1BR0 |= 0x15;
    UCB1BR1 = 0;
    UCB1CTLW0 &= ~UCSWRST;

    PM5CTL0 &= ~LOCKLPM5;
}

void oled_init(){
    P4SEL0 &= (~BIT4);
    P4DIR |= BIT4; // /CS Output

    P3SEL0 &= (~BIT2) + (~BIT1);
    P3DIR |= BIT2 + BIT1; // 3.2(/RES) and 3.1(D/C)

    P3OUT &= (~BIT2); //active low reset
    delay_ms(10);
    P3OUT |= BIT2;

    P4OUT &= (~BIT4);

    SetCommandLock(0xFD, 0x12); //unlock basic commands
    SleepMode(0xAE); //display off, sleep mode on
    SetColumnAddress(0x15,0x1C,0x5B); //range for screen is 1C to 5B
    SetRowAddress(0x75,0x00,0x3F); // range for screen is 00 to 3F
    ClockSet(0xB3, 0x91); //set clock as 80 frames/sec
    MultiplexRatio(0xCA, 0x3F); // 1/64 Duty
    DisplayOffset(0xA2, 0x00); //No Display Offset
    DisplayStartLine(0xA1, 0x00); //Start Line at address 0x00
    Remap(0xA0, 0x07);
    SetGPIO(0xB5,0x00);
    VDDRegulator(0xAB, 0x01); //Enable Internal VDD Regulator
    Contrast(0xC1, 0x9F); // pretty high contrast
    MasterContrast(0xC7, 0x0F); //no change through master contrast control
    LinearGrayscale(0xB9); //linear grayscale
    PhaseLength(0xB1, 0xE2);
    PrechargeVoltage(0xBB, 0x1F);
    PrechargePeriod(0xB6, 0x08);
    VCOMH(0xBE, 0x07);
    DisplayMode(0xA6); //Normal Display
    ExitPartialDisplay(0xA9);
    SleepMode(0xAF);

    P4OUT |= BIT4;
}

void SetCommandLock(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void SleepMode(uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void ClockSet(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void MultiplexRatio(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void DisplayOffset(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void DisplayStartLine(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void Remap(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void VDDRegulator(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void Contrast(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void MasterContrast(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void LinearGrayscale(uint8_t cmd){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

}

void PhaseLength(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void PrechargeVoltage(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void PrechargePeriod(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void VCOMH(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void DisplayMode(uint8_t cmd){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

}

void ExitPartialDisplay(uint8_t cmd){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

}

void SetColumnAddress(uint8_t cmd, uint8_t data1, uint8_t data2){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data2;
    while(UCB1STAT & UCBUSY);
}

void SetRowAddress(uint8_t cmd, uint8_t data1, uint8_t data2){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data2;
    while(UCB1STAT & UCBUSY);
}

void SetGPIO(uint8_t cmd, uint8_t data1){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);

    P3OUT |= (BIT1); //Data Mode
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);

}

void PrepRAM(uint8_t cmd){
    P3OUT &= (~BIT1); //Command Mode

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = cmd;
    while(UCB1STAT & UCBUSY);
}

void SendRAMData(uint8_t data1){
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = data1;
    while(UCB1STAT & UCBUSY);
}

void ClearRAM (void){
    uint8_t i,j;
    SetColumnAddress(0x15,0x1C,0x5B); //range for screen is 1C to 5B
    SetRowAddress(0x75,0x00,0x3F); // range for screen is 00 to 3F
    PrepRAM(0x5C); // Send Command to begin writing to screen
    P3OUT |= (BIT1); //Data Mode
    for(i=0;i<64;i++)
    {
        for(j=0;j<64;j++)
        {
            SendRAMData(0x00);
            SendRAMData(0x00);
        }
    }
}

void ClearRAM_ECG (void){
    uint8_t i,j;
    SetColumnAddress(0x15,0x1C,0x5B); //range for screen is 1C to 5B
    SetRowAddress(0x75,0x00,0x3F); // range for screen is 00 to 3F
    PrepRAM(0x5C); // Send Command to begin writing to screen
    P3OUT |= (BIT1); //Data Mode
    for(i=0;i<48;i++)
    {
        for(j=0;j<64;j++)
        {
            SendRAMData(0x00);
            SendRAMData(0x00);
        }
    }
}

void erase(uint8_t colstart, uint8_t colend, uint8_t rowstart){
    uint8_t i,j;
    SetColumnAddress(0x15,colstart,colend);
    SetRowAddress(0x75,rowstart,rowstart+7);
    PrepRAM(0x5C); // Send Command to begin writing to screen
    P3OUT |= BIT1;
    for(i=0;i<64;i++)
    {
        for(j=0;j<64;j++)
        {
            SendRAMData(0x00);
            SendRAMData(0x00);
        }
    }
}

void delay_ms(unsigned int ms){
    while(ms){
        __delay_cycles(1000);
        ms--;
    }
}

void FirstScreen(void){
    P4OUT &= (~BIT4); //Select Chip
    ClearRAM();

    //PORTABLE VITALS
    P(0x2A,0x00); O(0x2C,0x00); R(0x2E,0x00); T(0x30,0x00); A(0x32,0x00); B(0x34,0x00); L(0x36,0x00); E(0x38,0x00);

    V_(0x3D,0x00); I(0x3F,0x00); T(0x41,0x00); A(0x43,0x00); L(0x45,0x00); S(0x47,0x00);

    //A: ECG AND HEARTRATE
    A(0x1C, 0x0E); COLON(0x1E,0x0E);

    E(0x20, 0x0E); C_(0x22,0x0E); G(0x24,0x0E);

    A(0x28,0x0E); N_(0x2A,0x0E); D(0x2D,0x0E);

    H(0x31,0x0E); E(0x33,0x0E); A(0x35,0x0E); R(0x37,0x0E); T(0x39,0x0E); R(0x3B,0x0E); A(0x3D,0x0E); T(0x3F,0x0E); E(0x41,0x0E);

    //B: THERMOMETER
    B(0x1C, 0x1A); COLON(0x1E,0x1A);

    T(0x20, 0x1A); H(0x22,0x1A); E(0x24,0x1A); R(0x26,0x1A); M(0x28,0x1A); O(0x2A,0x1A); M(0x2C,0x1A); E(0x2E,0x1A); T(0x30,0x1A); E(0x32,0x1A); R(0x34,0x1A);

    //C: BMI CALCULATOR
    C_(0x1C,0x26); COLON(0x1E,0x26);

    B(0x20,0x26); M(0x22,0x26); I(0x24,0x26);

    C_(0x28,0x26); A(0x2A,0x26); L(0x2C,0x26); C_(0x2E,0x26); U(0x30,0x26); L(0x32,0x26); A(0x34,0x26); T(0x36,0x26); O(0x38,0x26); R(0x3A,0x26);

    //D: RETURN TO MENU
    D(0x1C,0x32); COLON(0x1E,0x32);

    R(0x20,0x32); E(0x22,0x32); T(0x24,0x32); U(0x26,0x32); R(0x28,0x32); N_(0x2A,0x32);

    T(0x2E,0x32); O(0x30,0x32);

    M(0x34,0x32); E(0x36,0x32); N_(0x38,0x32); U(0x3B,0x32);

    P4OUT |= BIT4; // De-Select Chip
}

void ThermometerScreen(void){
    P4OUT &= (~BIT4); //Select Chip
    ClearRAM();

    //THERMOMETER
    T(0x30, 0x00); H(0x32,0x00); E(0x34,0x00); R(0x36,0x00); M(0x38,0x00); O(0x3A,0x00); M(0x3C,0x00); E(0x3E,0x00); T(0x40,0x00); E(0x42,0x00); R(0x44,0x00);

    //BODY TEMP:
    B(0x2A,0x1B); O(0x2C,0x1B); D(0x2E,0x1B); Y(0x30,0x1B);

    T(0x33,0x1B); E(0x35,0x1B); M(0x37,0x1B); P(0x39,0x1B); COLON(0x3B,0x1B);

    P4OUT |= BIT4; // De-Select Chip
}

void HeartrateScreen(void){
    P4OUT &= (~BIT4); //Select Chip
    ClearRAM();

    uint8_t i;
    SetColumnAddress(0x15,0x4F,0x4F); //range for screen is 1C to 5B
    SetRowAddress(0x75,0x00,0x3F); // range for screen is 00 to 3F
    PrepRAM(0x5C); // Send Command to begin writing to screen
    P3OUT |= BIT1;
    for(i=0;i<64;i++)
    {
        SendRAMData(0xF0);
        SendRAMData(0x00);
    }

    H(0x54,0x15);
    R(0x56,0x15);
    COLON(0x58,0x15);

    P4OUT |= BIT4;
}

void BMIScreen(void){
    P4OUT &= (~BIT4); //Select Chip
    ClearRAM();

    //BMI CALCULATOR
    B(0x23,0x00); M(0x25,0x00); I(0x27,0x00);

    C_(0x2B,0x00); A(0x2D,0x00); L(0x2F,0x00); C_(0x31,0x00); U(0x33,0x00); L(0x35,0x00); A(0x37,0x00); T(0x39,0x00); O(0x3B,0x00); R(0x3D,0x00);

    //1. HEIGHT IN INCHES:
    ONE(0x1C,0x0E); PERIOD(0x1E,0x0E);

    H(0x20,0x0E); E(0x22,0x0E); I(0x24,0x0E); G(0x26,0x0E); H(0x28,0x0E); T(0x2A,0x0E);

    I(0x2D,0x0E); N_(0x2F,0x0E);

    I(0x33,0x0E); N_(0x35,0x0E); C_(0x38,0x0E); H(0x3A,0x0E); E(0x3C,0x0E); S(0x3E,0x0E); COLON(0x40,0x0E);

    //2. WEIGHT IN POUNDS:
    TWO(0x1C,0x1D); PERIOD(0x1E,0x1D);

    W(0x20,0x1D); E(0x22,0x1D); I(0x24,0x1D); G(0x26,0x1D); H(0x28,0x1D); T(0x2A,0x1D);

    I(0x2D,0x1D); N_(0x2F,0x1D);

    P(0x33,0x1D); O(0x35,0x1D); U(0x37,0x1D); N_(0x39,0x1D); D(0x3C,0x1D); S(0x3E,0x1D); COLON(0x40,0x1D);

    //#: ENTER
    POUND(0x1C,0x37); COLON(0x1E,0x37);

    E(0x20,0x37); N_(0x22,0x37); T(0x25,0x37); E(0x27,0x37); R(0x29,0x37);

    //AST: BKSP
    A(0x38,0x37); S(0x3A,0x37); T(0x3C,0x37); COLON(0x3E,0x37);

    B(0x40,0x37); K(0x42,0x37); S(0x44,0x37); P(0x46,0x37);

    uint8_t i;

    SetColumnAddress(0x15,0x48,0x48); //range for screen is 1C to 5B
    SetRowAddress(0x75,0x00,0x3F); // range for screen is 00 to 3F
    PrepRAM(0x5C); // Send Command to begin writing to screen
    P3OUT |= BIT1;
    for(i=0;i<64;i++){
        SendRAMData(0xF0);
        SendRAMData(0x00);
    }

    //BMI:
    B(0x4F,0x08); M(0x51,0x08); I(0x53,0x08); COLON(0x55,0x08);

    //LB/SQ. IN
    L(0x4E,0x13); B(0x50,0x13); SLASH(0x52,0x13);

    S(0x54,0x13); Q(0x56,0x13); PERIOD(0x58,0x13); I(0x59,0x13); N_(0x5A,0x13);

    P4OUT |= BIT4;
}

uint8_t valueToDisplay(uint8_t value, uint8_t colstart, uint8_t rowstart){
    P4OUT &= (~BIT4); //Select Chip

       if(value == 0x30){
            //delay_ms(50);
            P4OUT &= (~BIT4); //Select Chip
            ZERO(colstart,rowstart);              //0
            P4OUT |= BIT4;
            return 0x44;
        }

       else if(value == 0x31){
           //delay_ms(50);
           P4OUT &= (~BIT4); //Select Chip
           ONE(colstart,rowstart);                //1
           P4OUT |= BIT4;
           return 0x44;
           }

       else if(value == 0x32){
           //delay_ms(50);
           P4OUT &= (~BIT4); //Select Chip
           TWO(colstart,rowstart);                //2
           P4OUT |= BIT4;
           return 0x44;
       }

       else if(value == 0x33){
           //delay_ms(50);
           P4OUT &= (~BIT4); //Select Chip
           THREE(colstart,rowstart);              //3
           P4OUT |= BIT4;
           return 0x44;
       }

       else if(value == 0x34){
           //delay_ms(50);
           P4OUT &= (~BIT4); //Select Chip
           FOUR(colstart,rowstart);               //4
           P4OUT |= BIT4;
           return 0x44;
       }

       else if(value == 0x35){
           //delay_ms(50);
           P4OUT &= (~BIT4); //Select Chip
           FIVE(colstart,rowstart);               //5
           P4OUT |= BIT4;
           return 0x44;
       }

       else if(value == 0x36){
           //delay_ms(50);
           P4OUT &= (~BIT4); //Select Chip
           SIX(colstart,rowstart);                //6
           P4OUT |= BIT4;
           return 0x44;
       }

       else if(value == 0x37){
           //delay_ms(50);
           P4OUT &= (~BIT4); //Select Chip
           SEVEN(colstart,rowstart);              //7
           P4OUT |= BIT4;
           return 0x44;
       }

       else if(value == 0x38){
           //delay_ms(50);
           P4OUT &= (~BIT4); //Select Chip
           EIGHT(colstart,rowstart);              //8
           P4OUT |= BIT4;
           return 0x44;
       }

       else if(value == 0x39){
           //delay_ms(50);
           P4OUT &= (~BIT4); //Select Chip
           NINE(colstart,rowstart);               //9
           P4OUT |= BIT4;
           return 0x44;
       }

       return 0x56;
}

void TempResults(uint8_t result){
    P4OUT &= (~BIT4); //Select Chip

    //Hypothermia = 0x00
    //Normal = 0x01
    //Fever = 0x02

    if(result == 0x00){
        //HYPOTHERMIA
        H(0x32,0x2A); Y(0x34,0x2A); P(0x36,0x2A); O(0x38,0x2A); T(0x3A,0x2A); H(0x3C,0x2A); E(0x3E,0x2A); R(0x40,0x2A); M(0x42,0x2A); I(0x44,0x2A); A(0x46,0x2A);
    }

    if(result == 0x01){
        //NORMAL
        N_(0x37, 0x2A); O(0x3A, 0x2A); R(0x3C, 0x2A); M(0x3E, 0x2A); A(0x40, 0x2A); L(0x42, 0x2A);
    }

    if(result == 0x02){
        //FEVER
        F(0x38, 0x2A); E(0x3A, 0x2A); V_(0x3C, 0x2A); E(0x3E, 0x2A); R(0x40, 0x2A);
    }

    P4OUT |= BIT4;
}

void BMIResults(uint8_t result){
    P4OUT &= (~BIT4); //Select Chip

    uint8_t i,j;
    SetColumnAddress(0x15,0x4C,0x5B); //range for screen is 1C to 5B
    SetRowAddress(0x75,0x24,0x3F); // range for screen is 00 to 3F
    PrepRAM(0x5C); // Send Command to begin writing to screen
    P3OUT |= BIT1;
    for(i=0;i<64;i++)
    {
        for(j=0;j<64;j++)
        {
            SendRAMData(0x00);
            SendRAMData(0x00);
        }
    }

    //Under weight = 0x00
    //Healthy = 0x01
    //Overweight = 0x02

    if(result == 0x00){
        //UNDER WEIGHT
        U(0x4D,0x25); N_(0x4F,0x25); D(0x52,0x25); E(0x54,0x25); R(0x56,0x25);

        W(0x4D,0x2E); E(0x4F,0x2E); I(0x51,0x2E); G(0x53,0x2E); H(0x55,0x2E); T(0x57,0x2E);

        delay_ms(1000);
        return;
    }

    else if(result == 0x01){
        //HEALTHY
        H(0x4D,0x28); E(0x4F,0x28); A(0x51,0x28); L(0x53,0x28); T(0x55,0x28); H(0x57,0x28); Y(0x59,0x28);

        delay_ms(1000);
        return;
    }

    else if(result == 0x02){
        //OVER WEIGHT
        O(0x4E,0x25); V_(0x50,0x25); E(0x52,0x25); R(0x54,0x25);

        W(0x4C,0x2E); E(0x4E,0x2E); I(0x50,0x2E); G(0x52,0x2E); H(0x54,0x2E); T(0x56,0x2E);

        delay_ms(1000);
        return;
    }

    P4OUT |= BIT4;
    return;
}

void AgeScreen(void){
    P4OUT &= ~BIT4;                                     //Select chip
    ClearRAM();

    //Column Range: 1C-5B
    //Row Range: 00-3F

    //HEART DATA AND ECG GRAPH
    H(0x1C,0x00); E(0x1E,0x00); A(0x20,0x00); R(0x22,0x00); T(0x24,0x00);

    D(0x28,0x00); A(0x2A,0x00); T(0x2C,0x00); A(0x2E,0x00);

    A(0x32,0x00); N_(0x34,0x00); D(0x37,0x00);

    E(0x3B,0x00); C_(0x3D,0x00); G(0x3F,0x00);

    G(0x43,0x00); R(0x45,0x00); A(0x47,0x00); P(0x49,0x00); H(0x4B,0x00);

    //ENTER AGE:
    E(0x1C,0x0E); N_(0x1E,0x0E); T(0x21,0x0E); E(0x23,0x0E); R(0x25,0x0E);

    A(0x29,0x0E); G(0x2B,0x0E); E(0x2D,0x0E);

    COLON(0x2F,0x0E);

    //MAX HR:
    M(0x1C,0x1D); A(0x1E,0x1D); X_(0x20,0x1D);

    H(0x24,0x1D); R(0x26,0x1D);

    COLON(0x28,0x1D);

    //#: ENTER
    POUND(0x1C,0x37);

    COLON(0x1E,0x37);

    E(0x20,0x37); N_(0x22,0x37); T(0x25,0x37); E(0x27,0x37); R(0x29,0x37);

    P4OUT |= BIT4;                                      //De-select chip
}

void HeartDataScreen(void){
    //Column Range: 1C-5B
    //Row Range: 04-3F
    P4OUT &= ~BIT4;                                     //Select chip
    ClearRAM();

    //Heartrate Training Zones
    //Zone 1: Healthy Heart Zone: 50%-59% of max HR
    //Zone 2: Temperate Zone: 60%-69% of max HR
    //Zone 3: Aerobic Zone: 70%-79% of max HR
    //Zone 4: Threshold Zone: 80%-89% of max HR
    //Zone 5: Performance Redline Zone: 90%-99% of max HR

    //HEARTRATE TRAINING ZONES:
    H(0x1C,0x00); E(0x1E,0x00); A(0x20,0x00); R(0x22,0x00); T(0x24,0x00); R(0x26,0x00); A(0x28,0x00); T(0x2A,0x00); E(0x2C,0x00);

    T(0x30,0x00); R(0x32,0x00); A(0x34,0x00); I(0x36,0x00); N_(0x38,0x00); I(0x3B,0x00); N_(0x3D,0x00); G(0x40,0x00);

    Z_(0x44,0x00); O(0x47,0x00); N_(0x49,0x00); E(0x4C,0x00); S(0x4E,0x00);

    //Z1: HEALTHY:
    Z_(0x1C,0x0B); ONE(0x1E,0x0B); COLON(0x20,0x0B);

    H(0x22,0x0B); E(0x24,0x0B); A(0x26,0x0B); L(0x28,0x0B); T(0x2A,0x0B); H(0x2C,0x0B); Y(0x2E,0x0B); COLON(0x30,0x0B);

    //Z2: TEMPERATE:
    Z_(0x1C,0x16); TWO(0x1E,0x16); COLON(0x20,0x16);

    T(0x22,0x16); E(0x24,0x16); M(0x26,0x16); P(0x28,0x16); E(0x2A,0x16); R(0x2C,0x16); A(0x2E,0x16); T(0x30,0x16); E(0x32,0x16); COLON(0x34,0x16);

    //Z3: AEROBIC:
    Z_(0x1C,0x21); THREE(0x1E,0x21); COLON(0x20,0x21);

    A(0x22,0x21); E(0x24,0x21); R(0x26,0x21); O(0x28,0x21); B(0x2A,0x21); I(0x2C,0x21); C_(0x2E,0x21); COLON(0x30,0x21);

    //Z4: THRESHOLD
    Z_(0x1C,0x2C); FOUR(0x1E,0x2C); COLON(0x20,0x2C);

    T(0x22,0x2C); H(0x24,0x2C); R(0x26,0x2C); E(0x28,0x2C); S(0x2A,0x2C); H(0x2C,0x2C); O(0x2E,0x2C); L(0x30,0x2C); D(0x32,0x2C); COLON(0x34,0x2C);

    //Z5: REDLINE
    Z_(0x1C,0x37); FIVE(0x1E,0x37); COLON(0x20,0x37);

    R(0x22,0x37); E(0x24,0x37); D(0x26,0x37); L(0x28,0x37); I(0x2A,0x37); N_(0x2C,0x37); E(0x2F,0x37); COLON(0x31,0x37);

    P4OUT |= BIT4;                                      //De-select chip
}
