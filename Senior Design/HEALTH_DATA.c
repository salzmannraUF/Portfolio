/*
 * HEALTH_DATA.c
 *
 *  Created on: Apr 17, 2019
 *      Author: Raymond Salzmann & Madison Breese
 */

#include"HEALTH_DATA.h"

void getHR(void){
    __bis_SR_register(GIE);                         //Enter LPM3 with interrupt
    P6OUT &= ~(BIT4);
    P6OUT &= ~(BIT5);
    P6OUT &= ~(BIT6);
    P5OUT &= ~(BIT3);

    AgeScreen();
    getAge();

    uint8_t hr_max_col[6] = {0x2A,0x2C,0x2E,0x31,0x33,0x35};
    uint8_t hr_max_row[6] = {0x1D,0x1D,0x1D,0x1D,0x1D,0x1D};

    uint8_t Z_col[55] = {0x32,0x34,0x36,0x3A,0x3C,0x40,0x42,0x44,0x48,0x4A,0x4C,
                         0x36,0x38,0x3A,0x3E,0x40,0x44,0x46,0x48,0x4C,0x4E,0x50,
                         0x32,0x34,0x36,0x3A,0x3C,0x40,0x42,0x44,0x48,0x4A,0x4C,
                         0x36,0x38,0x3A,0x3E,0x40,0x44,0x46,0x48,0x4C,0x4E,0x50,
                         0x33,0x35,0x37,0x3B,0x3D,0x41,0x43,0x45,0x49,0x4B,0x4D};

    uint8_t Z_row[55] = {0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,
                         0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
                         0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x21,
                         0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,
                         0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37};

    uint8_t heartrate_max;
    uint8_t heartrate_max_temp;
    uint8_t heartrate_max_L;
    uint8_t heartrate_max_M;
    uint8_t heartrate_max_H;

    float Z1_L, Z2_L, Z3_L, Z4_L, Z5_L;
    float Z1_H, Z2_H, Z3_H, Z4_H, Z5_H;

    float Z1_L_temp, Z2_L_temp, Z3_L_temp, Z4_L_temp, Z5_L_temp;
    float Z1_H_temp, Z2_H_temp, Z3_H_temp, Z4_H_temp, Z5_H_temp;

    float Z1_L_L, Z2_L_L, Z3_L_L, Z4_L_L, Z5_L_L;
    float Z1_H_L, Z2_H_L, Z3_H_L, Z4_H_L, Z5_H_L;

    float Z1_L_M, Z2_L_M, Z3_L_M, Z4_L_M, Z5_L_M;
    float Z1_H_M, Z2_H_M, Z3_H_M, Z4_H_M, Z5_H_M;

    float Z1_L_H, Z2_L_H, Z3_L_H, Z4_L_H, Z5_L_H;
    float Z1_H_H, Z2_H_H, Z3_H_H, Z4_H_H, Z5_H_H;

    uint8_t Z1_L_L_, Z2_L_L_, Z3_L_L_, Z4_L_L_, Z5_L_L_;
    uint8_t Z1_H_L_, Z2_H_L_, Z3_H_L_, Z4_H_L_, Z5_H_L_;

    uint8_t Z1_L_M_, Z2_L_M_, Z3_L_M_, Z4_L_M_, Z5_L_M_;
    uint8_t Z1_H_M_, Z2_H_M_, Z3_H_M_, Z4_H_M_, Z5_H_M_;

    uint8_t Z1_L_H_, Z2_L_H_, Z3_L_H_, Z4_L_H_, Z5_L_H_;
    uint8_t Z1_H_H_, Z2_H_H_, Z3_H_H_, Z4_H_H_, Z5_H_H_;

    //Calculate max HR based on age and display on screen
    heartrate_max = (220 - total_age[0]);
    float heartrate_max_f = (float)heartrate_max;

    heartrate_max_temp = (heartrate_max);
    heartrate_max_L = (heartrate_max_temp % 10);
    heartrate_max_temp= (heartrate_max_temp / 10);
    heartrate_max_M= (heartrate_max_temp % 10);
    heartrate_max_temp = (heartrate_max_temp / 10);
    heartrate_max_H = (heartrate_max_temp % 10);

    heartrate_max_L = UintToASCII(heartrate_max_L);
    heartrate_max_M = UintToASCII(heartrate_max_M);
    heartrate_max_H = UintToASCII(heartrate_max_H);

    valueToDisplay(heartrate_max_H, hr_max_col[0], hr_max_row[0]);
    valueToDisplay(heartrate_max_M, hr_max_col[1], hr_max_row[1]);
    valueToDisplay(heartrate_max_L, hr_max_col[2], hr_max_row[2]);

    P4OUT &= ~(BIT4);
    B(hr_max_col[3], hr_max_row[3]);
    P(hr_max_col[4], hr_max_row[4]);
    M(hr_max_col[5], hr_max_row[5]);
    P4OUT |= BIT4;

    while(getKey_BMI() != '#');

    HeartDataScreen();

    //ZONE 1
    Z1_L = (heartrate_max_f * 0.50);
    Z1_H = (heartrate_max_f * 0.59);

    Z1_L_temp = Z1_L;
    Z1_H_temp = Z1_H;

    Z1_L_L = fmod(Z1_L_temp,10);
    Z1_H_L = fmod(Z1_H_temp,10);

    Z1_L_temp = (Z1_L_temp / 10);
    Z1_H_temp = (Z1_H_temp / 10);

    Z1_L_M = fmod(Z1_L_temp,10);
    Z1_H_M = fmod(Z1_H_temp,10);

    Z1_L_temp = (Z1_L_temp / 10);
    Z1_H_temp = (Z1_H_temp / 10);

    Z1_L_H = fmod(Z1_L_temp,10);
    Z1_H_H = fmod(Z1_H_temp,10);

    Z1_L_L_ = trunc(Z1_L_L);
    Z1_H_L_ = trunc(Z1_H_L);

    Z1_L_M_ = trunc(Z1_L_M);
    Z1_H_M_ = trunc(Z1_H_M);

    Z1_L_H_ = trunc(Z1_L_H);
    Z1_H_H_ = trunc(Z1_H_H);

    Z1_L_L_ = UintToASCII(Z1_L_L_);
    Z1_L_M_ = UintToASCII(Z1_L_M_);
    Z1_L_H_ = UintToASCII(Z1_L_H_);

    Z1_H_L_ = UintToASCII(Z1_H_L_);
    Z1_H_M_ = UintToASCII(Z1_H_M_);
    Z1_H_H_ = UintToASCII(Z1_H_H_);

    valueToDisplay(Z1_L_H_, Z_col[0], Z_row[0]);
    valueToDisplay(Z1_L_M_, Z_col[1], Z_row[1]);
    valueToDisplay(Z1_L_L_, Z_col[2], Z_row[2]);

    P4OUT &= ~BIT4;
    T(Z_col[3],Z_row[3]);
    O(Z_col[4],Z_row[4]);
    P4OUT |= BIT4;

    valueToDisplay(Z1_H_H_, Z_col[5], Z_row[5]);
    valueToDisplay(Z1_H_M_, Z_col[6], Z_row[6]);
    valueToDisplay(Z1_H_L_, Z_col[7], Z_row[7]);

    P4OUT &= ~BIT4;
    B(Z_col[8],Z_row[8]);
    P(Z_col[9],Z_row[9]);
    M(Z_col[10],Z_row[10]);
    P4OUT |= BIT4;

    //ZONE 2
    Z2_L = (heartrate_max_f * 0.60);
    Z2_H = (heartrate_max_f * 0.69);

    Z2_L_temp = Z2_L;
    Z2_H_temp = Z2_H;

    Z2_L_L = fmod(Z2_L_temp,10);
    Z2_H_L = fmod(Z2_H_temp,10);

    Z2_L_temp = (Z2_L_temp / 10);
    Z2_H_temp = (Z2_H_temp / 10);

    Z2_L_M = fmod(Z2_L_temp,10);
    Z2_H_M = fmod(Z2_H_temp,10);

    Z2_L_temp = (Z2_L_temp / 10);
    Z2_H_temp = (Z2_H_temp / 10);

    Z2_L_H = fmod(Z2_L_temp,10);
    Z2_H_H = fmod(Z2_H_temp,10);

    Z2_L_L_ = trunc(Z2_L_L);
    Z2_H_L_ = trunc(Z2_H_L);

    Z2_L_M_ = trunc(Z2_L_M);
    Z2_H_M_ = trunc(Z2_H_M);

    Z2_L_H_ = trunc(Z2_L_H);
    Z2_H_H_ = trunc(Z2_H_H);

    Z2_L_L_ = UintToASCII(Z2_L_L_);
    Z2_L_M_ = UintToASCII(Z2_L_M_);
    Z2_L_H_ = UintToASCII(Z2_L_H_);

    Z2_H_L_ = UintToASCII(Z2_H_L_);
    Z2_H_M_ = UintToASCII(Z2_H_M_);
    Z2_H_H_ = UintToASCII(Z2_H_H_);

    valueToDisplay(Z2_L_H_, Z_col[11], Z_row[11]);
    valueToDisplay(Z2_L_M_, Z_col[12], Z_row[12]);
    valueToDisplay(Z2_L_L_, Z_col[13], Z_row[13]);

    P4OUT &= ~BIT4;
    T(Z_col[14],Z_row[14]);
    O(Z_col[15],Z_row[15]);
    P4OUT |= BIT4;

    valueToDisplay(Z2_H_H_, Z_col[16], Z_row[16]);
    valueToDisplay(Z2_H_M_, Z_col[17], Z_row[17]);
    valueToDisplay(Z2_H_L_, Z_col[18], Z_row[18]);

    P4OUT &= ~BIT4;
    B(Z_col[19],Z_row[19]);
    P(Z_col[20],Z_row[20]);
    M(Z_col[21],Z_row[21]);
    P4OUT |= BIT4;

    //Zone 3
    Z3_L = (heartrate_max_f * 0.70);
    Z3_H = (heartrate_max_f * 0.79);

    Z3_L_temp = Z3_L;
    Z3_H_temp = Z3_H;

    Z3_L_L = fmod(Z3_L_temp,10);
    Z3_H_L = fmod(Z3_H_temp,10);

    Z3_L_temp = (Z3_L_temp / 10);
    Z3_H_temp = (Z3_H_temp / 10);

    Z3_L_M = fmod(Z3_L_temp,10);
    Z3_H_M = fmod(Z3_H_temp,10);

    Z3_L_temp = (Z3_L_temp / 10);
    Z3_H_temp = (Z3_H_temp / 10);

    Z3_L_H = fmod(Z3_L_temp,10);
    Z3_H_H = fmod(Z3_H_temp,10);

    Z3_L_L_ = trunc(Z3_L_L);
    Z3_H_L_ = trunc(Z3_H_L);

    Z3_L_M_ = trunc(Z3_L_M);
    Z3_H_M_ = trunc(Z3_H_M);

    Z3_L_H_ = trunc(Z3_L_H);
    Z3_H_H_ = trunc(Z3_H_H);

    Z3_L_L_ = UintToASCII(Z3_L_L_);
    Z3_L_M_ = UintToASCII(Z3_L_M_);
    Z3_L_H_ = UintToASCII(Z3_L_H_);

    Z3_H_L_ = UintToASCII(Z3_H_L_);
    Z3_H_M_ = UintToASCII(Z3_H_M_);
    Z3_H_H_ = UintToASCII(Z3_H_H_);

    valueToDisplay(Z3_L_H_, Z_col[22], Z_row[22]);
    valueToDisplay(Z3_L_M_, Z_col[23], Z_row[23]);
    valueToDisplay(Z3_L_L_, Z_col[24], Z_row[24]);

    P4OUT &= ~BIT4;
    T(Z_col[25],Z_row[25]);
    O(Z_col[26],Z_row[26]);
    P4OUT |= BIT4;

    valueToDisplay(Z3_H_H_, Z_col[27], Z_row[27]);
    valueToDisplay(Z3_H_M_, Z_col[28], Z_row[28]);
    valueToDisplay(Z3_H_L_, Z_col[29], Z_row[29]);

    P4OUT &= ~BIT4;
    B(Z_col[30],Z_row[30]);
    P(Z_col[31],Z_row[31]);
    M(Z_col[32],Z_row[32]);
    P4OUT |= BIT4;

    //ZONE 4
    Z4_L = (heartrate_max_f * 0.80);
    Z4_H = (heartrate_max_f * 0.89);

    Z4_L_temp = Z4_L;
    Z4_H_temp = Z4_H;

    Z4_L_L = fmod(Z4_L_temp,10);
    Z4_H_L = fmod(Z4_H_temp,10);

    Z4_L_temp = (Z4_L_temp / 10);
    Z4_H_temp = (Z4_H_temp / 10);

    Z4_L_M = fmod(Z4_L_temp,10);
    Z4_H_M = fmod(Z4_H_temp,10);

    Z4_L_temp = (Z4_L_temp / 10);
    Z4_H_temp = (Z4_H_temp / 10);

    Z4_L_H = fmod(Z4_L_temp,10);
    Z4_H_H = fmod(Z4_H_temp,10);

    Z4_L_L_ = trunc(Z4_L_L);
    Z4_H_L_ = trunc(Z4_H_L);

    Z4_L_M_ = trunc(Z4_L_M);
    Z4_H_M_ = trunc(Z4_H_M);

    Z4_L_H_ = trunc(Z4_L_H);
    Z4_H_H_ = trunc(Z4_H_H);

    Z4_L_L_ = UintToASCII(Z4_L_L_);
    Z4_L_M_ = UintToASCII(Z4_L_M_);
    Z4_L_H_ = UintToASCII(Z4_L_H_);

    Z4_H_L_ = UintToASCII(Z4_H_L_);
    Z4_H_M_ = UintToASCII(Z4_H_M_);
    Z4_H_H_ = UintToASCII(Z4_H_H_);

    valueToDisplay(Z4_L_H_, Z_col[33], Z_row[33]);
    valueToDisplay(Z4_L_M_, Z_col[34], Z_row[34]);
    valueToDisplay(Z4_L_L_, Z_col[35], Z_row[35]);

    P4OUT &= ~BIT4;
    T(Z_col[36],Z_row[36]);
    O(Z_col[37],Z_row[37]);
    P4OUT |= BIT4;

    valueToDisplay(Z4_H_H_, Z_col[38], Z_row[38]);
    valueToDisplay(Z4_H_M_, Z_col[39], Z_row[39]);
    valueToDisplay(Z4_H_L_, Z_col[40], Z_row[40]);

    P4OUT &= ~BIT4;
    B(Z_col[41],Z_row[41]);
    P(Z_col[42],Z_row[42]);
    M(Z_col[43],Z_row[43]);
    P4OUT |= BIT4;

    //Zone 5
    Z5_L = (heartrate_max_f * 0.90);
    Z5_H = (heartrate_max_f * 0.99);

    Z5_L_temp = Z5_L;
    Z5_H_temp = Z5_H;

    Z5_L_L = fmod(Z5_L_temp,10);
    Z5_H_L = fmod(Z5_H_temp,10);

    Z5_L_temp = (Z5_L_temp / 10);
    Z5_H_temp = (Z5_H_temp / 10);

    Z5_L_M = fmod(Z5_L_temp,10);
    Z5_H_M = fmod(Z5_H_temp,10);

    Z5_L_temp = (Z5_L_temp / 10);
    Z5_H_temp = (Z5_H_temp / 10);

    Z5_L_H = fmod(Z5_L_temp,10);
    Z5_H_H = fmod(Z5_H_temp,10);

    Z5_L_L_ = trunc(Z5_L_L);
    Z5_H_L_ = trunc(Z5_H_L);

    Z5_L_M_ = trunc(Z5_L_M);
    Z5_H_M_ = trunc(Z5_H_M);

    Z5_L_H_ = trunc(Z5_L_H);
    Z5_H_H_ = trunc(Z5_H_H);

    Z5_L_L_ = UintToASCII(Z5_L_L_);
    Z5_L_M_ = UintToASCII(Z5_L_M_);
    Z5_L_H_ = UintToASCII(Z5_L_H_);

    Z5_H_L_ = UintToASCII(Z5_H_L_);
    Z5_H_M_ = UintToASCII(Z5_H_M_);
    Z5_H_H_ = UintToASCII(Z5_H_H_);

    valueToDisplay(Z5_L_H_, Z_col[44], Z_row[44]);
    valueToDisplay(Z5_L_M_, Z_col[45], Z_row[45]);
    valueToDisplay(Z5_L_L_, Z_col[46], Z_row[46]);

    P4OUT &= ~BIT4;
    T(Z_col[47],Z_row[47]);
    O(Z_col[48],Z_row[48]);
    P4OUT |= BIT4;

    valueToDisplay(Z5_H_H_, Z_col[49], Z_row[49]);
    valueToDisplay(Z5_H_M_, Z_col[50], Z_row[50]);
    valueToDisplay(Z5_H_L_, Z_col[51], Z_row[51]);

    P4OUT &= ~BIT4;
    B(Z_col[52],Z_row[52]);
    P(Z_col[53],Z_row[53]);
    M(Z_col[54],Z_row[54]);
    P4OUT |= BIT4;

    while(getKey_BMI() != '#');


    HeartrateScreen();
    displayECG();
}

void getTemp(void){
    __bis_SR_register(GIE);                         //Enter LPM3 with interrupt
    P6OUT &= ~(BIT4);
    P6OUT &= ~(BIT5);
    P6OUT &= ~(BIT6);
    P5OUT &= ~(BIT3);

    ThermometerScreen();
    uint8_t t_col[4] = {0x3D, 0x3F, 0x41, 0x43};
    uint8_t t_row[4] = {0x1B, 0x1B, 0x1B, 0x1B};

    ADCCTL0 |= ADCENC | ADCSC;          //Sampling and conversion start
    //while(!ADCBUSY);
    ADC_Result = ADCMEM0;
    ADCCTL0 &= ~(ADCENC + ADCSC);

    ADC_Result = (ADC_Result * 0.00080566);
    ADC_Result = (ADC_Result - 0.455);
    ADC_Result = (ADC_Result / 0.01);
    ADC_Result_F = (ADC_Result * 1.8) + 32;

    ADC_Result_Temp = (ADC_Result_F * 10);
    ADC_Result_D = fmod(ADC_Result_Temp,10);
    ADC_Result_Temp = (ADC_Result_Temp / 10.0);
    ADC_Result_L = fmod(ADC_Result_Temp,10);
    ADC_Result_Temp = (ADC_Result_Temp / 10);
    ADC_Result_H = fmod(ADC_Result_Temp,10);

    ADC_Result_D1 = trunc(ADC_Result_D);
    ADC_Result_L1 = trunc(ADC_Result_L);
    ADC_Result_H1 = trunc(ADC_Result_H);

    ADC_Result_D1 = UintToASCII(ADC_Result_D1);
    ADC_Result_L1 = UintToASCII(ADC_Result_L1);
    ADC_Result_H1 = UintToASCII(ADC_Result_H1);

    valueToDisplay(ADC_Result_H1,t_col[0],t_row[0]);
    valueToDisplay(ADC_Result_L1,t_col[1],t_row[1]);

    P4OUT &= (~BIT4); //Select Chip
    PERIOD(t_col[2],t_row[2]);
    P4OUT |= (BIT4);
    valueToDisplay(ADC_Result_D1,t_col[3],t_row[3]);

    P4OUT &= (~BIT4); //Select Chip

    D(0x46,0x1B);
    E(0x48,0x1B);
    G(0x4A,0x1B);

    F(0x4D,0x1B);

    P4OUT |= (BIT4);

    //checkTemp(ADC_Result_F);
}

void getBMI(void){
    BMIScreen();

    __bis_SR_register(GIE);                         //Enter LPM3 with interrupt
    P6OUT &= ~(BIT4);
    P6OUT &= ~(BIT5);
    P6OUT &= ~(BIT6);
    P5OUT &= ~(BIT3);

    uint8_t i = 0x00;
    uint8_t j = 0x00;
    uint8_t done_h = 0x00;
    uint8_t done_w = 0x00;
    uint8_t input[1] = {};
    uint8_t check[1] = {};

    uint16_t height[2] = {};
    uint16_t weight[3] = {};
    uint16_t total_height[1] = {};
    uint32_t total_height_sq[1] = {};
    uint32_t total_weight[1] = {};
    uint32_t BMI[1] = {};

    uint8_t h_col[2] = {0x42,0x44};
    uint8_t w_col[3] = {0x42, 0x44, 0x46};
    uint8_t b_col[2] = {0x4A, 0x4C};
    uint8_t h_row[2] = {0x0E,0x0E};
    uint8_t w_row[3] = {0x1D, 0x1D, 0x1D};
    uint8_t b_row[2] = {0x13,0x13};

    //ENTER HEIGHT IN INCHES:
     while(done_h != 0x01){
        input[0] = getKey_BMI();

        P6OUT &= ~(BIT4);
        P6OUT &= ~(BIT5);
        P6OUT &= ~(BIT6);
        P5OUT &= ~(BIT3);

        if(input[0] == '*'){
            erase(h_col[i-1], h_col[i-1], h_row[i-1]);
            i--;
            delay_ms(100);
        }
        else if(input[0] == '#'){
            done_h = 0x01;
            delay_ms(100);
        }
        else{
            height[i] = input[0];
            check[0] = valueToDisplay(height[i], h_col[i], h_row[i]);
            if(check[0] == 0x44) i++;
            if(i == HEIGHT){
                while(getKey_BMI() != '#');
                done_h = 0x01;
                delay_ms(100);
            }
            delay_ms(300);
        }
    }

    height[0] = ASCIItoUint(height[0]);
    height[1] = ASCIItoUint(height[1]);

    height[0] = (height[0] << 3) + (height[0] << 1);
    total_height[0] = (height[0] + height[1]);
    total_height_sq[0] = total_height[0] * total_height[0];

    //ENTER WEIGHT IN POUNDS
    while(done_w != 0x01){
        input[0] = getKey_BMI();

        P6OUT &= ~(BIT4);
        P6OUT &= ~(BIT5);
        P6OUT &= ~(BIT6);
        P5OUT &= ~(BIT3);

        if(input[0] == '*'){
            erase(w_col[i-1], w_col[i-1], w_row[i-1]);
                j--;
                delay_ms(100);
        }
        else if(input[0] == '#'){
            done_w = 0x01;

            if(j < WEIGHT){
                weight[2] = 0x44;
                delay_ms(150);
            }
        }
        else{
            weight[j] = input[0];
            check[0] = valueToDisplay(weight[j], w_col[j], w_row[j]);
            if(check[0] == 0x44) j++;
            if(j == WEIGHT){
                while(getKey_BMI() != '#');
                done_w = 0x01;
                delay_ms(100);
            }
            delay_ms(300);
        }
    }

    weight[0] = ASCIItoUint(weight[0]);
    weight[1] = ASCIItoUint(weight[1]);

    if(weight[2] != 0x44){
        weight[2] = ASCIItoUint(weight[2]);
        weight[0] = (weight[0] << 6) + (weight[0] << 5) + (weight[0] << 2);
        weight[1] = (weight[1] << 3) + (weight[1] << 1);
        total_weight[0] = (weight[0] + weight[1] + weight[2]);
    }

    else{
    weight[0] = (weight[0] << 3) + (weight[0] << 1);
    total_weight[0] = (weight[0] + weight[1]);
    }

    BMI[0] = (0x2BF * total_weight[0]);
    BMI[0] = (BMI[0] / total_height_sq[0]);

    BMI[0] = (uint8_t) BMI[0];

    uint8_t BMI_H[1] = {(BMI[0] / 0x0A)};
    uint8_t BMI_L[1] = {(BMI[0] % 10)};

    BMI_H[0] = UintToASCII(BMI_H[0]);
    BMI_L[0] = UintToASCII(BMI_L[0]);

    valueToDisplay(BMI_H[0], b_col[0],b_row[0]);
    valueToDisplay(BMI_L[0], b_col[1],b_row[1]);
    checkBMI(BMI[0]);
}



void checkBMI(uint8_t BMI){
    if(BMI >= 25){                              //OVERWEIGHT
        BMIResults(0x02);
    }

    if((BMI >= 19) && (BMI <= 24)){             //HEALTHY
        BMIResults(0x01);
    }

    if(BMI <= 18){                              //UNDERWEIGHT
        BMIResults(0x00);
    }
}

void displayECG(void){
    __bis_SR_register(GIE);                         //Enter LPM3 with interrupt
    P6OUT &= ~(BIT4);
    P6OUT &= ~(BIT5);
    P6OUT &= ~(BIT6);
    P5OUT &= ~(BIT3);

    uint8_t p = 0;
    uint8_t diff1 = 0;
    uint8_t diff2 = 0;
    uint8_t diff_avg = 0;
    float peak_period = 0;
    float heartrate_temp;
    float heartrate_L,heartrate_M,heartrate_H;
    uint8_t heartrate_L1,heartrate_M1,heartrate_H1;
    float heartrate;
    float peak[3] = {};

    uint8_t count = 0;
    uint8_t i,j,k;
    P4OUT &= (~BIT4);

        while(1){
        for(i=0;i<48;i++){
            for(j=0;j<4;j++){
                ADCCTL0 |= ADCENC | ADCSC;  // Sampling and conversion start
                ECG_Result[j] = ADCMEM0;
                ECG_Result[j] = ECG_Result[j]/64;
                ECG_Total[k] = ECG_Result[j];
                ADCCTL0 &= (~ADCENC) | (~ADCSC);
                k++;
                __delay_cycles(10000);

            }

        if((ECG_Result[0] == ECG_Result[1]) && (ECG_Result[0] == ECG_Result[2]) && (ECG_Result[0] == ECG_Result[3])){
            //write 0 1 2 3
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0xFF);
            SendRAMData(0xFF);
        }

        else if((ECG_Result[0] == ECG_Result[1]) && (ECG_Result[0] == ECG_Result[2])){
            //write 0 1 2
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0xFF);
            SendRAMData(0xF0);

            //write 3
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[3],ECG_Result[3]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0x00);
            SendRAMData(0x0F);
        }

        else if((ECG_Result[0] == ECG_Result[1]) && (ECG_Result[0] == ECG_Result[3])){
            //write 0 1 3
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0xFF);
            SendRAMData(0x0F);

            //write 2
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[2],ECG_Result[2]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0x00);
            SendRAMData(0xF0);
        }

        else if((ECG_Result[0] == ECG_Result[2]) && (ECG_Result[0] == ECG_Result[3])){
            //write 0 2 3
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0xF0);
            SendRAMData(0xFF);

            //write 1
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[1],ECG_Result[1]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0x0F);
            SendRAMData(0x00);
        }

        else if((ECG_Result[1] == ECG_Result[2]) && (ECG_Result[1] == ECG_Result[3])){
            //write 1 2 3
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[1],ECG_Result[1]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0x0F);
            SendRAMData(0xFF);

            //write 0
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0xF0);
            SendRAMData(0x00);
        }

        else if((ECG_Result[0] == ECG_Result[1])){
            //write 0 1
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0xFF);
            SendRAMData(0x00);

            if(ECG_Result[2] == ECG_Result[3]){
                //write 2 3
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[2],ECG_Result[2]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x00);
                SendRAMData(0xFF);
            } else{
                //write 2
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[2],ECG_Result[2]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x00);
                SendRAMData(0xF0);

                //write 3
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[3],ECG_Result[3]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x00);
                SendRAMData(0x0F);
            }
        }

        else if((ECG_Result[0] == ECG_Result[2])){
            //write 0 2
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0xF0);
            SendRAMData(0xF0);

            if(ECG_Result[1] == ECG_Result[3]){
                //write 1 3
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[1],ECG_Result[1]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x0F);
                SendRAMData(0x0F);
            } else{
                //write 1
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[1],ECG_Result[1]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x0F);
                SendRAMData(0x00);

                //write 3
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[3],ECG_Result[3]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x00);
                SendRAMData(0x0F);
            }
        }

        else if((ECG_Result[0] == ECG_Result[3])){
            //write 0 3
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0xF0);
            SendRAMData(0x0F);

            if(ECG_Result[1] == ECG_Result[2]){
                //write 1 2
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[2],ECG_Result[2]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x0F);
                SendRAMData(0xF0);
            } else{
                //write 1
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[1],ECG_Result[1]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x0F);
                SendRAMData(0x00);

                //write 2
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[2],ECG_Result[2]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x00);
                SendRAMData(0xF0);
            }
        }

        else if((ECG_Result[1] == ECG_Result[2])){
            //write 1 2
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[1],ECG_Result[1]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0x0F);
            SendRAMData(0xF0);

            if(ECG_Result[0] == ECG_Result[3]){
                //write 0 3
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0xF0);
                SendRAMData(0x0F);
            } else{
                //write 0
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0xF0);
                SendRAMData(0x00);

                //write 3
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[3],ECG_Result[3]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x00);
                SendRAMData(0x0F);
            }
        }

        else if((ECG_Result[1] == ECG_Result[3])){
            //write 1 3
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[1],ECG_Result[1]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0x0F);
            SendRAMData(0x0F);

            if(ECG_Result[0] == ECG_Result[2]){
                //write 0 2
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[2],ECG_Result[2]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0xF0);
                SendRAMData(0xF0);
            } else{
                //write 0
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0xF0);
                SendRAMData(0x00);

                //write 2
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[2],ECG_Result[2]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x00);
                SendRAMData(0xF0);
            }
        }

        else if((ECG_Result[2] == ECG_Result[3])){
            //write 2 3
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[2],ECG_Result[2]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0x00);
            SendRAMData(0xFF);

            if(ECG_Result[0] == ECG_Result[1]){
                //write 0 1
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0xFF);
                SendRAMData(0x00);
            } else{
                //write 0
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0xF0);
                SendRAMData(0x00);

                //write 1
                SetColumnAddress(0x15,i+0x1C,i+0x1C);
                SetRowAddress(0x75,ECG_Result[1],ECG_Result[1]);

                PrepRAM(0x5C);
                P3OUT |= BIT1;

                SendRAMData(0x0F);
                SendRAMData(0x00);
            }
        }

        else{
            //write 0
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[0],ECG_Result[0]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0xF0);
            SendRAMData(0x00);

            //write 1
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[1],ECG_Result[1]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0x0F);
            SendRAMData(0x00);

            //write 2
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[2],ECG_Result[2]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0x00);
            SendRAMData(0xF0);

            //write 3
            SetColumnAddress(0x15,i+0x1C,i+0x1C);
            SetRowAddress(0x75,ECG_Result[3],ECG_Result[3]);

            PrepRAM(0x5C);
            P3OUT |= BIT1;

            SendRAMData(0x00);
            SendRAMData(0x0F);
        }
        }

    //ADC sampling frequency = 83.3 samples/seconds = 0.012ms
    //Peak = index values of ECG_Total[] where peak values are stored
    //Peak period = (average of distance between two peaks) * (ADC sampling frequency)
    //Heartrate = (2 * 62.5 * 60) / peak period
    for(k=0;k<192;k++){
        count++;
        if(ECG_Total[k] < 14 && count > 10){
            count = 0;
            peak[p] = k;
            p++;

            if(p == 2){
                p = 0;

                diff1 = peak[1] - peak[0];
                diff2 = peak[2] - peak[1];
                diff_avg = ((diff1 + diff2) / 2);
                peak_period = (diff_avg * 0.016);
                heartrate = (7500 / peak_period);

                heartrate_temp = trunc(heartrate/100);
                heartrate_L = fmod(heartrate_temp,10);
                heartrate_temp = (heartrate_temp / 10);
                heartrate_M = fmod(heartrate_temp,10);

                if(heartrate < 9999) heartrate_H = 0;

                else{
                heartrate_temp = (heartrate_temp / 10);
                heartrate_H = fmod(heartrate,10);
                }

                heartrate_L1 = trunc(heartrate_L);
                heartrate_M1 = trunc(heartrate_M);
                heartrate_H1 = trunc(heartrate_H);

                heartrate_L1 = UintToASCII(heartrate_L1);
                heartrate_M1 = UintToASCII(heartrate_M1);
                heartrate_H1 = UintToASCII(heartrate_H1);

                //0x58,0x15
                valueToDisplay(heartrate_H1,0x54,0x21);
                valueToDisplay(heartrate_M1,0x56,0x21);
                valueToDisplay(heartrate_H1,0x58,0x21);

                P4OUT &= ~BIT4;
                B(0x54,0x2D);
                P(0x56,0x2D);
                M(0x58,0x2D);
            }
        }
   }
    ClearRAM_ECG();
 }
}

void getAge(void){
    __bis_SR_register(GIE);                         //Enter LPM3 with interrupt
    P6OUT &= ~(BIT4);
    P6OUT &= ~(BIT5);
    P6OUT &= ~(BIT6);
    P5OUT &= ~(BIT3);

    uint8_t i = 0x00;
    uint8_t done = 0x00;
    uint8_t input[1] = {};
    uint8_t check[1] = {};

    //(0x2F,0x0E)
    uint8_t a_col[2] = {0x33,0x35};
    uint8_t a_row[2] = {0x0E,0x0E};

    //ENTER AGE
     while(done != 0x01){
        input[0] = getKey_BMI();
        if(input[0] == '*'){
            erase(a_col[i-1], a_col[i-1], a_row[i-1]);
            i--;
            delay_ms(100);
        }
        else if(input[0] == '#'){
            done = 0x01;
            delay_ms(100);
        }
        else{
            age[i] = input[0];
            check[0] = valueToDisplay(age[i], a_col[i], a_row[i]);
            if(check[0] == 0x44) i++;
            if(i == 0x02){
                while(getKey_BMI() != '#');
                done = 0x01;
                delay_ms(100);
            }
            delay_ms(300);
        }
    }

    age[0] = ASCIItoUint(age[0]);
    age[1] = ASCIItoUint(age[1]);

    age[0] = (age[0] << 3) + (age[0] << 1);
    total_age[0] = (age[0] + age[1]);
}

