; Lab 4 Part G
; Name: Raymond Salzmann
; Section #: 2B04
; TA Name: Keith Fitzgerald
; Description: INTERRUPT DRIVEN RECEIVING

.include "ATxmega128A1Udef.inc"
.org 0x0000
	rjmp MAIN

.org USARTD0_RXC_vect
	jmp PART_E_ISR

.org TCE0_OVF_vect
	jmp LOGIC

.cseg

.org 0x200
MAIN:
	call CLOCK_32MHz_SETUP
	call USART_INIT
	call INITIALIZE
	call TIMER_COUNTER

LOOP:
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

	ldi r16, 0b00011000				;Transmit & Receive enable
	sts USARTD0_CTRLB, r16

	ldi r17, 0b00010000
	sts USARTD0_CTRLA, r16

	ldi r16, 0x01					;load PMIC_CTRL with a low level
	sts PMIC_CTRL, r16

	sei

	pop r16
	ret

;*************************************************************
PART_E_ISR:
	push r16
	push r17

	lds r17, USARTD0_DATA

	sts USARTD0_DATA, r17			;write the character into the data register

	ldi r16, 0x80
	sts USARTD0_STATUS, r16

	pop r17
	pop r16

	reti

;***************************************************************
INITIALIZE:
	push r16

	ldi r16, 0b00100000				;enable PORTD as outputs
	sts PORTD_DIRSET, r16

	ldi r18, 0x00

	pop r16
	ret

;**************************************************************
TIMER_COUNTER:
	push r16
	push r17

	ldi r16, 0x00 ;load 00 into the low byte of the PER register
	sts TCE0_PER, r16
	
	ldi r16, 0x45 ;load 02 into the high byte of the PER register
	sts TCE0_PER+1, r16
	
	ldi r16, 0x00 ;initialize the counter at zero
	sts TCE0_CNT, r16

	ldi r16, 0x00 ;initialize the counter at zero
	sts TCE0_CNT+1, r16

	ldi r16, 0x01 ;enable the overflow interrupt
	sts TCE0_INTCTRLA, r16

	ldi r16, 0x07 ;load 7 into r16 for the slowest TC prescaler
	sts TCE0_CTRLA, r16

	pop r17
	pop r16
	ret

;****************************************************************
LOGIC:
	push r16
	push r17
	
	cpi r18, 0x00
	breq ON
	rjmp OFF

ON:
	ldi r16, 0x00
	sts PORTD_OUT, r16
	ldi r18, 0x01
	rjmp CLEAR_FLAG

OFF:
	ldi r16, 0xFF
	sts PORTD_OUT, r16
	ldi  r18, 0x00
	rjmp CLEAR_FLAG

CLEAR_FLAG:

	ldi r16, 0x01			;write a 1 to int0 to reset it
	sts TCE0_INTFLAGS, r16
	
	pop r17
	pop r16


	reti	