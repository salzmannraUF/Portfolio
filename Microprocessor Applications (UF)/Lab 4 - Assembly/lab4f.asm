; Lab 4 Part F
; Name: Raymond Salzmann
; Section #: 2B04
; TA Name: Keith Fitzgerald
; Description: SERIAL MENU

.include "ATxmega128A1Udef.inc"
.equ CR = 0x0D
.equ LF = 0x0A

.org 0x0000
	rjmp MAIN

.org 0x2000
;set up a table for every possible menu/answer
	Input_Table: .db 0x10,"RAYMOND SALZMANN'S FAVORITE:",CR,LF,"1. Food",CR,LF,"2. UF Course",CR,LF,"3. Hobby",CR,LF,"4. Quote",CR,LF,"5. Movie",CR,LF,"6. Re-display menu",CR,LF,"D: Done",CR,LF, 0xFF
	HOBBY: .db "RAYMOND SALZMANN'S FAVORITE HOBBY IS PLAYING VIDEO GAMES",CR,LF,0xFF
	FOOD: .db "RAYMOND SALZMANN'S FAVORITE FOOD IS ONE DANK CHICKEN TACO",CR,LF,0xFF
	COURSE: .db "RAYMOND SALZMANN'S FAVORITE UF COURSE IS SOLID STATE ELECTRONIC DEVICES",CR,LF,0xFF
	QUOTE: .db 0x10, "RAYMOND SALZMANN'S FAVORITE QUOTE IS: THE ONLY THING WE HAVE TO FEAR IS FEAR ITSELF",CR,LF,0xFF
	MOVIE: .db "RAYMOND SALZMANN'S FAVORITE MOVIE IS THE SHINING",CR,LF,0xFF
	DONE_Table: .db "Done!",CR,LF,0xFF

.cseg

.org 0x200
MAIN:
	call CLOCK_32MHz_SETUP
	call USART_INIT
	call RESET
	call MENU_RESET

LOOP:
	call OUT_STRING
	
	cpi r21, 0x01	;if r21 is 1, from the DONE part of the menu, then end the program
	breq DONE
	rjmp LOOP

DONE:
	rjmp DONE
	
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

;**********************************************
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

; ****************************************************
OUT_CHAR:
	push r16
	push r17

OUT_CHAR_WAIT:
	lds  r16, USARTD0_STATUS
	sbrs r16, 5						;check if DATA reg is empty
	rjmp OUT_CHAR_WAIT				;loop to wait for output enable

	sts USARTD0_DATA, r17			;store the character in the data register

	pop r17
	pop r16

	ret

; ****************************************************

OUT_STRING:
	push r16
	push r17

	call CHECK

	cpi r20, 0x01			;check for menu reset
	breq OUT_STRING_END

OUT_STRING_REPEAT:
	elpm r17, Z+			;load r17 with the table data

	cpi  r17, 0xFF			;check for null value
	breq OUT_STRING_END

	call OUT_CHAR			;call OUT_CHAR to output the character
	rjmp OUT_STRING_REPEAT

OUT_STRING_END:
	
	cpi r21, 0x01
	BREQ DONE

	call MENU_RESET

	ldi r16,0x00
	cpse r20, r16			;check if the menu was called and reset to zero
	ldi	 r20, 0x00

	pop r17
	pop r16

	ret

; ****************************************
RESET:
	ldi ZH, High(Input_Table << 1)	;load the high byte of the Table address into ZH register
	ldi ZL, Low(Input_Table << 1)		;load the low byte of the Table address into ZL register

	ret
; *****************************************
CHECK:
	call IN_CHAR

	cpi r17, '1'			;check if 1 is input
	breq CHAR_ONE

	cpi r17, '2'			;check if 2 is input
	breq CHAR_TWO

	cpi r17, '3'			;check if 3 is input
	breq CHAR_THREE

	cpi r17, '4'			;check if 4 is input
	breq CHAR_FOUR

	cpi r17, '5'			;check if 5 is input
	breq CHAR_FIVE

	cpi r17, '6'			;check if 6 is input
	breq CHAR_SIX

	cpi r17, 'D'			;check if D is input
	breq CHAR_DONE

	cpi r17, 'd'			;check if d is input
	breq CHAR_DONE

	jmp LOOP
	
CHAR_ONE:
	ldi ZH, High(FOOD << 1)	;load the high byte of the FOOD Table address into ZH register
	ldi ZL, Low(FOOD << 1)	;load the low byte of the FOOD Table address into ZL register
	rjmp CHAR_CHECK_DONE

CHAR_TWO:
	ldi ZH, High(COURSE << 1) ;load the high byte of the COURSE Table address into ZH register
	ldi ZL, Low(COURSE << 1) ;load the low byte of the COURSE Table address into ZL register
	rjmp CHAR_CHECK_DONE

CHAR_THREE:
	ldi ZH, High(HOBBY << 1) ;load the high byte of the HOBBY Table address into ZH register
	ldi ZL, Low(HOBBY << 1) ;load the low byte of the HOBBY Table address into ZL register
	rjmp CHAR_CHECK_DONE

CHAR_FOUR:
	ldi ZH, High(QUOTE << 1) ;load the high byte of the QUOTE Table address into ZH register
	ldi ZL, Low(QUOTE << 1) ;load the low byte of the QUOTE Table address into ZL register
	rjmp CHAR_CHECK_DONE

CHAR_FIVE:
	ldi ZH, High(MOVIE << 1) ;load the high byte of the MOVIE Table address into ZH register
	ldi ZL, Low(MOVIE << 1)	;load the low byte of the MOVIE Table address into ZL register
	rjmp CHAR_CHECK_DONE

CHAR_SIX:
	ldi r20, 0x01					;load r20 with one to signal menu reload
	rjmp CHAR_CHECK_DONE

CHAR_DONE:
	ldi ZH, High(DONE_Table << 1) ;load the high byte of the DONE_Table address into ZH register
	ldi ZL, Low(DONE_Table << 1) ;load the low byte of the DONE_Table address into ZL register
	ldi r21, 0x01
	rjmp CHAR_CHECK_DONE

CHAR_CHECK_DONE:
	ret

; ********************************************
IN_CHAR:
	push r16

IN_CHAR_WAIT:
	lds  r16, USARTD0_STATUS
	sbrs r16, 5						;check if DATA reg is empty
	rjmp IN_CHAR_WAIT				;loop to wait for output enable

	ldi r16, 0b00011000				;Receive enable
	sts USARTD0_CTRLB, r16

IN_CHAR_CHECK:

	lds r17, USARTD0_DATA			;value to be written
	cpi r17, 0x00
	breq IN_CHAR_CHECK				;check for input, loop if none
	
	ldi r16, 0b00001000				;Receive disable
	sts USARTD0_CTRLB, r16

	pop r16

	ret 

; *********************************************
MENU_RESET:
	push r16
	push r17

	call RESET

MENU_RESET_OUT_STRING_REPEAT:
	elpm r17, Z+			;load r17 with value pointed to by Z

	cpi  r17, 0xFF			;check for EOT Condition
	breq MENU_RESET_OUT_STRING_END

	call OUT_CHAR			;call OUT_CHAR to output the character
	rjmp MENU_RESET_OUT_STRING_REPEAT

MENU_RESET_OUT_STRING_END:
	pop r17
	pop r16

	ret