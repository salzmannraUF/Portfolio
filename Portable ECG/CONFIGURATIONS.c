/*
 * CONFIGURATIONS.c
 *
 *  Created on: Apr 17, 2019
 *      Author: Raymond Salzmann & Madison Breese
 */

#include "CONFIGURATIONS.h"

void configureGPIO(void){

    P1DIR = 0xFF; P2DIR = 0xFF; P3DIR = 0xFF;
    P4DIR = 0xFF; P5DIR = 0xFF; P6DIR = 0xFF;

    P1OUT = 0xFF; P2OUT = 0xFF; P3OUT = 0xFF;                  //Set outputs high
    P4OUT = 0xFF; P5OUT = 0xFF; P6OUT = 0xFF;

    P6DIR &= ~(BIT0 + BIT1 + BIT2);                            //Set P6.0-P6.3 as input (C0,C1,C2)
    P6REN |= (BIT0 + BIT1 + BIT2);                             //Enable pull-up
    P6OUT |= (BIT0 + BIT1 + BIT2);                             //Pull high

    P1SEL0 &= ~(BIT3);
    P1DIR &= ~(BIT3);                                          //Set P1.3 as input (C3)
    P1OUT |= BIT3;                                             //Configure P1.3 as pull-up
    P1REN |= BIT3;                                             //P1.3 pull-up register enable
    P1IES |= BIT3;                                             //P1.3 high/low edge
    P1IE |= BIT3;                                              //P1.3 interrupt enabled

    P6DIR |= (BIT4 + BIT5 + BIT6);                             //Set P6.4-P6.5 as output (R0,R1,R2)
    P6OUT |= (BIT4 + BIT5 + BIT6);                             //Set outputs high

    P5DIR |= (BIT3);                                           //Set P5.3 as output (R3)
    P5OUT |= (BIT3);                                           //Set output high

    P3DIR |= (BIT7);                                           //Set speaker as output
    P3OUT &= ~(BIT7);                                          //Set output low

    P1SEL0 |= (BIT2);
    P1SEL1 |= (BIT2);

    PM5CTL0 &= ~LOCKLPM5;
}

uint16_t ASCIItoUint(uint16_t ASCII){
    if(ASCII == 0x30){                                                    //0
        return 0x00;
    }

    else if(ASCII == 0x31){                                               //1
        return 0x01;
    }

    else if(ASCII == 0x32){                                               //2
        return 0x02;
    }

    else if(ASCII == 0x33){                                               //3
        return 0x03;
    }

    else if(ASCII == 0x34){                                               //4
        return 0x04;
    }

    else if(ASCII == 0x35){                                               //5
        return 0x05;
    }

    else if(ASCII == 0x36){                                               //6
        return 0x06;
    }

    else if(ASCII == 0x37){                                               //7
        return 0x07;
    }

    else if(ASCII == 0x38){                                               //8
        return 0x08;
    }

    else if(ASCII == 0x39){                                               //9
        return 0x09;
    }

    return 0x44;
}

uint8_t UintToASCII(uint8_t uint){
    if(uint == 0x00){                                                     //0
         return 0x30;
     }

     else if(uint == 0x01){                                               //1
         return 0x31;
     }

     else if(uint == 0x02){                                               //2
         return 0x32;
     }

     else if(uint == 0x03){                                               //3
         return 0x33;
     }

     else if(uint == 0x04){                                               //4
         return 0x34;
     }

     else if(uint == 0x05){                                               //5
         return 0x35;
     }

     else if(uint == 0x06){                                               //6
         return 0x36;
     }

     else if(uint == 0x07){                                               //7
         return 0x37;
     }

     else if(uint == 0x08){                                               //8
         return 0x38;
     }

     else if(uint == 0x09){                                               //9
         return 0x39;
     }

     return 0x44;
 }


void ConfigureADC_temp(void){
    ADCCTL0 |= ADCSHT_2 | ADCON;            //ADCON, S&H = 14 ADC clocks
    ADCCTL1 |= ADCSHP;                      //ADCCLK = MODOSC; sampling timer
    ADCCTL2 &= ~ADCRES;                     //Clear ADCRES in ADCCTL
    ADCCTL2 |= ADCRES_2;                    //12-bit conversion results
    ADCMCTL0 |= ADCINCH_2;                  //A2 ADC input select; Vref = AVCC
}

void ConfigureADC_HR(void){
    // Configure ADC A1 pin
    P1SEL0 |= BIT1;
    P1SEL1 |= BIT1;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure ADC12
    ADCCTL0 |=  ADCON;                             // ADCON, S&H=16 ADC clks
    ADCCTL1 |= ADCSHP | ADCDIV_7;                  // ADCCLK = MODOSC; sampling timer
    ADCCTL2 &= ~ADCRES;                            // clear ADCRES in ADCCTL
    ADCCTL2 |=  ADCRES_2 | ADCSR;                  // 12-bit conversion results
    ADCMCTL0 |= ADCINCH_1;                         // A1 ADC input select; Vref=AVCC
}
