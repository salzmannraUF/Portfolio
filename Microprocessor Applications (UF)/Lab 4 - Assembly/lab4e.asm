; Lab 4 Part E
; Name: Raymond Salzmann
; Section #: 2B04
; TA Name: Keith Fitzgerald
; Description: CHARACTER INPUT

.include "ATxmega128A1Udef.inc"
.org 0x0000
	rjmp MAIN

.org 0x200
MAIN:
	call CLOCK_32MHz_SETUP
	call USART_INIT

LOOP:
	call IN_CHAR
	call OUT_CHAR
	rjmp MAIN
	
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

;***********************************************************
USART_INIT:
	push r16

	ldi r16, 0x08
	sts PORTD_DIRSET, r16

	ldi r16, 0x06
	sts PORTD_DIRCLR, r16

	ldi r16, 0b00110011			
	sts USARTD0_CTRLC, r16

	ldi r16, 0b10101100				;lower byte of the Baud Select value			
	sts USARTD0_BAUDCTRLA, r16		

	ldi r16, 0b10010001				;high nibble to 1001 for two's comp of -7, top of BSEL to 0001		
	sts USARTD0_BAUDCTRLB, r16

	ldi r16, 0b00001000				;Transmit enable
	sts USARTD0_CTRLB, r16

	pop r16

	ret

;*************************************************************

OUT_CHAR:
	push r16
	push r17

OUT_CHAR_WAIT:
	lds  r16, USARTD0_STATUS
	sbrs r16, 5						;check if DATA is ready to recieve new empty
	rjmp OUT_CHAR_WAIT				;loop to wait for DATA to be ready

	sts USARTD0_DATA, r17			;write the character into the data register

	pop r17
	pop r16

	ret

;**************************************************************
IN_CHAR:
	push r16

IN_CHAR_WAIT:
	lds  r16, USARTD0_STATUS
	sbrs r16, 5						;check if DATA is ready to recieve new empty
	rjmp IN_CHAR_WAIT				;loop to wait for DATA to be ready

	ldi r16, 0b00011000				;Receive enable
	sts USARTD0_CTRLB, r16

TEST:
	lds r17, USARTD0_DATA
	cpi r17, 0x00
	breq TEST				;check if DATA is ready to recieve new empty

DONE:
	ldi r16, 0b00001000				;Receive disable
	sts USARTD0_CTRLB, r16

	pop r16

	ret