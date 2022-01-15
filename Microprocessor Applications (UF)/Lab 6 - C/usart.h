/*
 * usart.h
 *
 * Created: 11/14/2017 6:40:44 PM
 *  Author: Raymond Salzmann
 */ 


#ifndef USART_H_
#define USART_H_

void USART_INIT(void)
{
	PORTD_DIRCLR = 0x04;
	PORTD_DIRSET = 0x08;
	
	USARTD0_BAUDCTRLA = 0x01; //sets baud rate to 1 MHz
	USARTD0_BAUDCTRLB = 0x00;
	
	//sets up control C register for the USART
	USARTD0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc |
	USART_SBMODE_bp | USART_CHSIZE_8BIT_gc;
	
	//set up transmit and receive enable
	USARTD0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
	
	return;
}

void OUT_CHAR(char character)
{
	while (!(USARTD0_STATUS & USART_DREIF_bm));
	
	USARTD0_DATA = character;
	return;
}

char IN_CHAR(void)
{
	while (!(USARTD0_STATUS & USART_RXCIF_bm));
	
	return USARTD0_DATA;
}

void OUT_STRING(char* string)
{
	while(*string)
	{
		OUT_CHAR(*string);
		string++;
	}
	return;
}

void DISPLAY_DATA(uint8_t x_low, uint8_t x_high, uint8_t y_low, uint8_t y_high, uint8_t z_low, uint8_t z_high)
{
	OUT_CHAR(0x03);	//start
	
	OUT_CHAR(x_low);
	OUT_CHAR(x_high);
	
	OUT_CHAR(y_low);
	OUT_CHAR(y_high);
	
	OUT_CHAR(z_low);
	OUT_CHAR(z_high);
	
	OUT_CHAR(0xFC); // stop

	return;
}

#endif /* USART_H_ */