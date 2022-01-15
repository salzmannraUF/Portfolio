/* Lab 6 Part G
 * Name: Raymond Salzmann
 *Section #: 2B04
 * Description: Real Time Data Plotting
 * TA Name: Keith Fitzgerald
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "LSM330.h"
#include "usart.h"

void	CLK_INIT(void);
uint8_t spiWrite(uint8_t data);
uint8_t spiRead(void);
uint8_t spi_init(void);
uint8_t LSM_read(uint8_t byte1);
uint8_t LSM_write(uint8_t byte1, uint8_t byte2);
uint8_t accel_init(void);
void PWM_init(void);

volatile uint8_t accelReady = 0;

int main(void)
{
	volatile uint8_t accel_x_low;		//initialize variables for accelerometer data
	volatile uint8_t accel_x_high;
	
	volatile uint8_t accel_y_low;
	volatile uint8_t accel_y_high;
	
	volatile uint8_t accel_z_low;
	volatile uint8_t accel_z_high;
	
	CLK_INIT();	//initialize clock
	
	PORTF_DIRSET = 0x18;
	PORTF_OUTSET = 0x18;
	
	PWM_init();
	
	PORTA_DIRSET = 0x10;
	PORTA_OUTCLR = 0x10;
	
	spi_init(); //initialize spi
	
	LSM_write(CTRL_REG4_A, 0x01);
	
	accel_init(); //acceleration initialization
	USART_INIT(); //initialize the baud rate and usart
	
	while(1)
	{
		if(accelReady == 1)
		{
			accel_x_low  = LSM_read(OUT_X_L_A);		//get values for the high and low of x,y, and z
			accel_x_high = LSM_read(OUT_X_H_A);
			
			accel_y_low  = LSM_read(OUT_Y_L_A);
			accel_y_high = LSM_read(OUT_Y_H_A);
			
			accel_z_low  = LSM_read(OUT_Z_L_A);
			accel_z_high = LSM_read(OUT_Z_H_A);
			
			accelReady = 0;						//clear interrupt
			
			uint16_t xval = abs( (accel_x_high << 8) | accel_x_low); //take absolute value as said in lab doc
			uint16_t yval = abs( (accel_y_high << 8) | accel_y_low); //take absolute value as said in lab doc
			uint16_t zval = abs( (accel_z_high << 8) | accel_z_low); //take absolute value as said in lab doc


			
			TCD0_CCA = xval; //red 
			TCD0_CCB = yval; //green
			TCD0_CCC = zval; //blue
		}
	}
	return;
}

uint8_t accel_init(void)
{
	PORTC_PIN7CTRL = 0x01;  //rising edge interrupt port c pin 7
	
	PORTC_DIRCLR = 0x80; //set pin 7 as output
	
	PORTC_INT0MASK = 0x80; //setup pin 7 as an interrupt for port c
	
	PORTC_INTCTRL = 0x01; //low level interrupt
	
	LSM_write(CTRL_REG4_A, 0xC8);		//write to LSM registers
	
	LSM_write(CTRL_REG5_A, 0x97);
	
	PMIC_CTRL = 0x01; //enable all interrupts
	sei();
	
	return;
}

uint8_t LSM_read(uint8_t addr)
{
	
	PORTF_OUTCLR = 0x08; 
	
	PORTF_OUTSET = 0x04; 
	
	spiWrite((addr & 0x3F) | 0x80);	 
	
	uint8_t read_data = spiRead();
	
	PORTF_OUTSET = 0x08;
	
	return read_data;
}

uint8_t LSM_write(uint8_t addr, uint8_t data)
{
	
	PORTF_OUTCLR = 0x08; 
	
	PORTF_OUTSET = 0x04; 
	
	spiWrite(addr);	 //spi write(byte1)
	
	spiWrite(data);	 //spi_write(byte2)
	
	PORTF_OUTSET = 0x08; //slave select signal high
	
	return;
}

void CLK_INIT(void)
{
	//set up clock for 32MHz
	OSC_CTRL			= 0x02;			
	
	while(!(OSC_STATUS & 0x02));		
	

	CPU_CCP				= 0xD8;			
	
	
	CLK_CTRL			= 0x01;			

}

uint8_t spiWrite(uint8_t data)
{
	SPIF_DATA = data; //write to the data register
	
	while(SPIF_STATUS != 0x80);
	
	return SPIF_DATA;
}

uint8_t spiRead(void)
{
	return	spiWrite(0xFF);
}

uint8_t spi_init(void)
{
	PORTF_DIRSET =	0xBC; //set portf direction for spi
	
	SPIF_CTRL =		0x50; //set control for spi
			
	SPIF_INTCTRL = 0x00; //turn off interrupts
	
	return;
}

ISR(PORTC_INT0_vect)
{
	accelReady = 1;
	PORTC_INTFLAGS = 0x01; //clear flag
	return;
}

void PWM_init(void)
{	//initialize the PWM from lab 3

	PORTD_REMAP		= 0x07;		//;remap the three pins to use later

	TCD0_CTRLA = 0x03;
	
	TCD0_CTRLB		= 0x73;		//;make sure the led pins are good

	PORTD_DIRSET	= 0b01110000; //;set all the leds to be outputs
	
	PORTD_PIN6CTRL	= 0x40;		//;invert the pins to make writing easier

	PORTD_PIN5CTRL = 0x40;

	PORTD_PIN4CTRL = 0x40;

	PMIC_CTRL |=  0x01;

	TCD0_PER = 0x3FFF;

	TCD0_CNT = 0x3FFF;

}

