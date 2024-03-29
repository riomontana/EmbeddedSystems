/*
 * keyboard.inc
 *
 * This file contains a driver for reading the keypad on the
 * "iBridge keypad shield". The driver is adapted for a shield mounted
 * on a Arduino Mega board (ATmega2560).
 *
 * Key mapping:
 *					-----------------
 *					| 1 | 2 | 3 | A |
 *					-----------------
 *					| 4 | 5 | 6 | B |
 *					-----------------
 *					| 7 | 8 | 9 | C |
 *					-----------------
 *					| * | 0 | # | D |
 *					-----------------
 *
 * Created by Mathias Beckius, 25 June 2015, for the course DA346A at
 * Malmo University.
 */

;==============================================================================
; Table of characters, for mapping with keys
;==============================================================================
keys:
	.DB				"XXXXXXXXXXXXXXXX", NO_KEY, 0

;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU			NO_KEY		=	16				; no key was pressed!

;==============================================================================
; Read keyboard
; Returns the corresponding character for the pressed key. If no key is
; pressed, then NO_KEY is returned.
;
; Uses registers:
;	R19			Counter to use as pointer 
;   R24			Register when returning key
;
; Important! A minimum delay of 2 NOP's is necessary after setting port,
; before pin can be read.
;==============================================================================
read_keyboard_num:
	LDI				R19,			0				; Reset counter

	; UPPGIFT: implementera subrutinen

return_key:
	MOV				R24,			R19
	RET

;=======================================================================
; Assume RVAL contains keyboard key number
; Returns ASCII value in RVAL
;=======================================================================
convert_to_ASCII:
	LDI				ZH,				HIGH(keys << 1)	; Init pointer
	LDI				ZL,				LOW(keys << 1)
	ADD				ZL,				R24				; Point to character
	LDI				R24,			0
	ADC				ZH,				R24
	LDI				R24,			50				; Delay of 50 ms
	RCALL			delay_ms
	LPM				R24,			Z				; Return character
	RET