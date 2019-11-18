/*
 * lab5.asm
 *
 * This program is a dice thrower-simulator. It scans the keypad of the "iBridge keypad shield".
 * If 2 is pressed and hold down the dice is rolling. When letting go a value between 1 and 6 is returned on the screen 
 * The amount of throws and corresponding values is stored in stats that can be viewed if 3 is pressed on keyboard.
 * The stats can be cleared with a push on key number 8 and a monitor can be viewed by pushing key number 9.
 * For registers in the Extended I/O space, STS must be used instead of
 * OUT, CBI, SBI. The macros SET_IO_BIT and CLR_IO_BIT is written for
 * the purpose of simplifying setting/clearing a specific bit in a I/O
 * register.
 *
 * Created by Mathias Beckius, 25 June 2015, for the course DA346A at
 * Malmo University.
 *
 * Edited by Linus Forsberg och Jimmy Åkesson 171214 and 171221
 */
 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU			RESET		 =	0x0000			; reset vector
	.EQU			PM_START	 =	0x0072			; start of program

	; Bit masks, to be used together with SET_IO_BIT and CLR_IO_BIT
	.EQU			BIT3_HIGH	 =	0x08			; 0b00001000
	.EQU			BIT3_LOW	 =	0xF7			; 0b11110111
	.EQU			BIT4_HIGH	 =	0x10			; 0b00010000
	.EQU			BIT4_LOW	 =	0xEF			; 0b11101111
	.EQU			BIT5_HIGH	 =	0x20			; 0b00100000
	.EQU			BIT5_LOW	 =	0xDF			; 0b11011111
	.EQU			BIT6_HIGH	 =	0x40			; 0b01000000
	.EQU			BIT6_LOW	 =	0xBF			; 0b10111111

;==============================================================================
; Macro for setting a bit in I/O register, located in the extended I/O space.
; Uses registers:
;	R24				Store I/O data
;
; Example: Set bit 6 in PORTH
;	SET_IO_BIT		PORTH,			BIT6_HIGH
;==============================================================================
	.MACRO			SET_IO_BIT
	LDS				R24,		@0
	ORI				R24,		@1
	STS				@0,			R24
	.ENDMACRO

;==============================================================================
; Macro for clearing a bit in I/O register, located in the extended I/O space.
; Uses registers:
;	R24				Store I/O data
;
; Example: Clear bit 6 in PORTH
;	CLR_IO_BIT		PORTH,			BIT6_LOW
;==============================================================================
	.MACRO			CLR_IO_BIT
	LDS				R24,		@0
	ANDI			R24,		@1
	STS				@0,			R24

	.ENDMACRO

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG			RESET
	RJMP			init

	.ORG			PM_START
	.INCLUDE		"delay.inc"
	.INCLUDE		"lcd.inc"				
	.INCLUDE		"keyboard.inc"
	.INCLUDE		"tarning.inc"
	.INCLUDE		"stats.inc"
	.INCLUDE		"monitor.inc"	
	.INCLUDE		"stat_data.inc"

;==============================================================================
; Basic initializations of stack pointer, I/O pins, etc.
;==============================================================================
init:
	LDI				R16,			LOW(RAMEND)		; Set stack pointer
	OUT				SPL,			R16				; at the end of RAM.
	LDI				R16,			HIGH(RAMEND)
	OUT				SPH,			R16
	RCALL			init_pins						; Initialize pins
	RCALL			init_pins_led
	RCALL			lcd_init						; Initialize LCD - avkommenteras i moment 3
	RJMP			main							; Jump to main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:
	; PORT B
	; output:	4, 5 and 6 (LCD command/character, reset, CS/SS)
	LDI				R16,			0x70
	OUT				DDRB,			R16
	; PORT H
	; output:	3 and 4 (keypad col 2 and 3)
	;			5 and 6 (LCD clock and data)
	LDI				R16,			0x78
	STS				DDRH,			R16
	; PORT E
	; output:	3 (keypad col 1)
	; input:	4 and 5 (keypad row 2 and 3)
	LDI				R16,			0x08
	OUT				DDRE,			R16
	; PORT F
	; input:	4 and 5 (keypad row 1 and 0)
	LDI				R16,			0x00
	OUT				DDRF,			R16
	; PORT G
	; output:	5 (keypad col 0)
	LDI				R16,			0x20
	OUT				DDRG,			R16
	RET

init_pins_led:
	SBI				DDRB,			7			; enable LED as output
	RET

;==============================================================================
; Main part of program
; Uses registers:
;	R20				temporary storage of pressed key
;	R24				input / output values
;==============================================================================

main:
	RCALL				lcd_clear							; clear screen
welcome_str:	
	.DB					"WELCOME",				0			; definition of text
	PRINTSTRING			welcome_str							; print welcome string
	RCALL				delay_1_s							; delay 1 sek
	RCALL				lcd_clear							; clear screen
instruction_str:
	.DB					"PRSS 2 TO ROLL",		0,0			; definition of text
	PRINTSTRING			instruction_str						; print instruction string
	RCALL				keyboard_loop						; call label keyboard loop

roll_the_dice:												
	RCALL				keyboard_input_loop					; call label keyboard loop
	RCALL				store_stat							; store stat of dice roll
	RCALL				delay_1_s							; delay 1 sec
	RCALL				lcd_clear							; clear screen
	RCALL				instruction_str						; call label instruction_str
show_stat:
	RCALL				showstat							; call showstat
	RCALL				lcd_clear							; clear screen
	RCALL				instruction_str						; call label instruction_str

clear_stat_data:
	RCALL				clearstat							; clear stats
	RCALL				lcd_clear							; clear screen
	RCALL				instruction_str						; call label instruction_str

show_monitor:
	RCALL				monitor								; call monitor

keyboard_loop:
	RCALL				read_keyboard						; reading keyboard
	CPI					R24,					16			; compare register R24 with 16 (no key)
	BREQ				keyboard_loop						; break if R24 is 16
	CPI					R24,					4			; compare R24 with 4 (2 on keyboard)
	BREQ				roll_the_dice						; then roll the dice if 2 was pressed
	CPI					R24,					8			; compare R24 with 8 (3 on keyboard)
	BREQ				show_stat							; show stats if 3 was pressed
	CPI					R24,					6			; compare R24 with 6 (8 on keyboard)
	BREQ				clear_stat_data						; clear stats if 8 was pressed
	CPI					R24,					10			; compare R24 with 10 (9 on keyboard)
	BREQ				show_monitor						; show monitor if 9 was pressed
	RCALL				keyboard_loop						; run loop again
