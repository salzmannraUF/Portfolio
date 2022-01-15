; Lab 4 Part B
; Name: Raymond Salzmann
; Section #: 2B04
; TA Name: Keith Fitzgerald
; Description: XMEGA USART TRANSMITTER

.include "ATxmega128A1Udef.inc"
.org 0x0000
	rjmp MAIN

.org 0x200
MAIN:
	call CLOCK_32MHz_SETUP
	call USART_INIT

LOOP:
	ldi r17, 85		;ASCII code for 'U'
	call OUT_CHAR
	rjmp LOOP
	
;*******************************************************
CLOCK_32MHz_SETUP:
	push r16

SETUP:
	ldi r16, 0x02	;set bit 1
	sts OSC_CTRL, r16 ;enable OSC_CTRL with the 32 MHz internal Clock

POLL_1:
	lds r16,OSC_STATUS ;load the value of OSC_STATUS to r16
	sbrc r16, 1 ;poll the OSC_STATUS register for stable flag
	rjmp CONTINUE ;continue once bit 1 is set
	rjmp POLL_1 ;loop until bit 1 is set

CONTINUE:
	ldi r16,0xD8 ;load 'D8' to r16 to enable IOREG
	sts CPU_CCP, r16 ;write IOREG to CPU_CCP

	ldi r16, 0x01 ;load '1' to bit 1
	sts CLK_CTRL,r16 ;store '1' in the CLK_CTRL register to enable the 32 MHz clk

	pop r16
	ret

;***************************************************
USART_INIT:
	push r16

	ldi r16, 0x08
	sts PORTD_DIRSET, r16

	ldi r16, 0x06
	sts PORTD_DIRCLR, r16

	ldi r16, 0b00110011				;Asynchronus, Odd Parity Bit, 1 stop bit and 8 data bits
	sts USARTD0_CTRLC, r16

	ldi r16, 0b10101100				;lower byte of the Baud Select value			
	sts USARTD0_BAUDCTRLA, r16		

	ldi r16, 0b10010001				;high nibble to 1001 for two's comp of -7 and top of BSEL to 0001		
	sts USARTD0_BAUDCTRLB, r16

	ldi r16, 0b00001000				;Transmit enable
	sts USARTD0_CTRLB, r16

	pop r16

	ret

;***************************************************

OUT_CHAR:
	push r16
	push r17

OUT_CHAR_WAIT:
	lds  r16, USARTD0_STATUS
	sbrs r16, 5					;check if DATA register is empty so that we can transmit next value
	rjmp OUT_CHAR_WAIT				;loop to wait for output enable

	sts USARTD0_DATA, r17			;store the character in the data register

	pop r17
	pop r16

	ret