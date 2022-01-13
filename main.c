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
#include "HEALTH_DATA.h"

//Author: Raymond Salzmann & Madison Breese

//Global variables for keypad
uint8_t key[1] = {0};

int main(void){
    WDTCTL = WDTPW | WDTHOLD;                                       //Stop watch dog timer

    configureGPIO();
    spi_init();
    oled_init();

    P1IFG = 0;                                               //P1.3 IFG cleared

    FirstScreen();

    while(1){
        __bis_SR_register(GIE);                         //Enter LPM3 with interrupt
        __no_operation();                               //For debug

           //Scan Row 0
           P6OUT &= ~(BIT4);
           P6OUT &= ~(BIT5);
           P6OUT &= ~(BIT6);
           P5OUT &= ~(BIT3);

           P6OUT |= (BIT4);
           P6OUT |= (BIT5);
           P6OUT |= (BIT6);
           P5OUT |= (BIT3);
    }
}

//Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1(void)
#else
#error Compiler not supported!
#endif
{
    key[0] = 0;

    P6OUT |= (BIT4);
    P6OUT |= (BIT5);
    P6OUT |= (BIT6);
    P5OUT |= (BIT3);

    key[0] = getKey_MENU();

    P1IFG &= ~(BIT3);                               //Clear P1.3 IFG

    ClearRAM();

     if(key[0] == 'A'){
         ConfigureADC_HR();
         getHR();
     }

     else if(key[0] == 'B'){
         ConfigureADC_temp();
         getTemp();
     }

     else if(key[0] == 'C'){
         getBMI();
     }

     else if(key[0] == 'D'){
         //FirstScreen();
         PMMCTL0 = PMMPW | PMMSWPOR;   // This triggers a Software POR
     }
    __bic_SR_register_on_exit(GIE);
}

