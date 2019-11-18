/*
 * Tarning.inc
 * R16 contains the dice value on return
 * Author: Jimmy Åkesson and Linus Forsberg 171214
 */

	.DEF				RVAL = R24
 ;------------------------------------------------------------------
 ; Strings used in program
 ;------------------------------------------------------------------
rolling_str:
	.DB					"ROLLING..",			0
value_str:
	.DB					"VALUE:",0,0

;-------------------------------------------------------------------
; Read keyboard input
; R24			Input/output
; R20			Have dice value
;-------------------------------------------------------------------
keyboard_input_loop:	
	RCALL				read_keyboard
	CPI					R24,						4
	BRNE				keyboard_input_loop
	RCALL				lcd_clear
	PRINTSTRING			rolling_str
	RCALL				roll_dice
	RCALL				lcd_clear
	PRINTSTRING			value_str
	MOV					R24,						R20
	RCALL				convert_to_ASCII
	LCD_WRITE_CHR

	RET

;-----------------------------------------------------------------------------
; Roll dice subroutine
; R20		Value of dice
; R24		Read keyboard value
;-----------------------------------------------------------------------------
roll_dice:
			LDI			R20,				6		;dice have 6 values
test:
			NOP
			NOP
			RCALL		read_keyboard				;key-value in RVAL
			CPI			RVAL,				4
			BREQ		roll						;yes, key 2 is still pressed
			RET										;no, key is released
roll:
			DEC			R20
			BREQ		roll_dice					;R16 is zero, start agn at 6
			RJMP		test						;no, keep rolling

