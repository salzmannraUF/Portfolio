/* Lab 6 Part B
 * Name: Raymond Salzmann
 * Section #: 2B04
 * TA Name: Keith Fitzgerald
 * Description: SPI Communication Testing
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void CLK_INIT(void);
uint8_t SPI_SETUP(void);
uint8_t spiRead(void);
uint8_t spiWrite(uint8_t data);


int main(void)
{
   CLK_INIT(); //initialize clock to 32MHz	
   SPI_SETUP(); //initialize the SPI
    
	while (1){
		
	spiWrite(0x53); //constantly write 53 using SPiwrite
    
	}
}

void CLK_INIT(void){
	OSC_CTRL = 0x02;
	
	while(!(OSC_STATUS & 0x01));
	
	CPU_CCP = 0xD8;
	
	CLK_CTRL = 0x01;
	
	return;
}

uint8_t SPI_SETUP(void){
	
	PORTF_DIRSET = 0xB0;
	
	PORTF_DIRCLR = 0x40;
	
	SPIF_CTRL =  0x5C;
	
	return;
}

uint8_t spiWrite(uint8_t data){
	
	SPIF_DATA = data; //put data into the data register
	
	while(!(SPIF_STATUS |= 0x80)); //wait until cleared
	
	return SPIF_DATA; //return data register
}

uint8_t spiRead(void){

	return spiWrite(0xFF);
}
