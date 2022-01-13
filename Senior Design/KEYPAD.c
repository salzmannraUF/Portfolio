/*
 * KEYPAD.c
 *
 *  Created on: Apr 17, 2019
 *      Author: Raymond Salzmann & Madison Breese
 */

#include "KEYPAD.h"

uint8_t getKey_MENU(void){
    //Scan Row 0
    P6OUT &= ~(BIT4);
    P6OUT |= (BIT5);
    P6OUT |= (BIT6);
    P5OUT |= (BIT3);

    if(COL3 == PRESS){
        //delay_ms(50);
        return 0x41;                                                //A
    }

    //Scan Row 1
    P6OUT |= (BIT4);
    P6OUT &= ~(BIT5);
    P6OUT |= (BIT6);
    P5OUT |= (BIT3);

    if(COL3 == PRESS){
        //delay_ms(50);
        return 0x42;                                                //B
    }

    //Scan Row 2
    P6OUT |= (BIT4);
    P6OUT |= (BIT5);
    P6OUT &= ~(BIT6);
    P5OUT |= (BIT3);

    if(COL3 == PRESS){
        //delay_ms(50);
        return 0x43;                                                //C
    }

    //Scan Row 3
    P6OUT |= (BIT4);
    P6OUT |= (BIT5);
    P6OUT |= (BIT6);
    P5OUT &= ~(BIT3);

    if(COL3 == PRESS){
        //delay_ms(50);
        return 0x44;                                                //D
    }

    P6OUT |= (BIT4);
    P6OUT |= (BIT5);
    P6OUT |= (BIT6);
    P5OUT |= (BIT3);
    return 0x00;                                                    //NULL
}

uint8_t getKey_BMI(void){
//    //Scan Row 0
    P6OUT &= ~(BIT4);
    P6OUT |= (BIT5);
    P6OUT |= (BIT6);
    P5OUT |= (BIT3);

    if(COL0 == PRESS){
        //delay_ms(50);
        return 0x31;                                                //1
    }

    else if(COL1 == PRESS){
        //delay_ms(50);
        return 0x32;                                                //2
    }

    else if(COL2 == PRESS){
        //delay_ms(50);
        return 0x33;                                                //3
    }

//    //Scan Row 1
    P6OUT |= (BIT4);
    P6OUT &= ~(BIT5);
    P6OUT |= (BIT6);
    P5OUT |= (BIT3);

    if(COL0 == PRESS){
        //delay_ms(50);
        return 0x34;                                                //4
    }

    else if(COL1 == PRESS){
        //delay_ms(50);
        return 0x35;                                                //5
    }

    else if(COL2 == PRESS){
        //delay_ms(50);
        return 0x36;                                                //6
    }

//    //Scan Row 2
    P6OUT |= (BIT4);
    P6OUT |= (BIT5);
    P6OUT &= ~(BIT6);
    P5OUT |= (BIT3);

    if(COL0 == PRESS){
        //delay_ms(50);
        return 0x37;                                                //7
    }

    else if(COL1 == PRESS){
        //delay_ms(50);
        return 0x38;                                                //8
    }

    else if(COL2 == PRESS){
        //delay_ms(50);
        return 0x39;                                                //9
    }

    //Scan Row 3
    P6OUT |= (BIT4);
    P6OUT |= (BIT5);
    P6OUT |= (BIT6);
    P5OUT &= ~(BIT3);

    if(COL0 == PRESS){
        //delay_ms(50);
        return 0x2A;                                                //star
    }

    else if(COL1 == PRESS){
        //delay_ms(50);
        return 0x30;                                                //0
    }

    else if(COL2 == PRESS){
        //delay_ms(50);
        return 0x23;                                                //#
    }

    P6OUT |= (BIT4);
    P6OUT |= (BIT5);
    P6OUT |= (BIT6);
    P5OUT |= (BIT3);
    return 0x00;                                                    //NULL
}


