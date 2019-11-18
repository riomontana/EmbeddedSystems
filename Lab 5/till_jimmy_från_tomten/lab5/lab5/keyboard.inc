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
 *
 * Edited by Linus Forsberg och Jimmy Åkesson 171207
 * Added functionality to read_keyboard_num returning character when keyboard is pressed. 
 */

;==============================================================================
; Table of characters, for mapping with keys
;==============================================================================
keys:
	.DB				"0123456", NO_KEY

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
read_keyboard:
	LDI				R19,			0			; Reset counter
	CBI				PORTG,			5			; CLEAR BIT COLUMN 1
	CBI				PORTE,			3			; CLEAR BIT COLUMN 2
	CLR_IO_BIT		PORTH,			BIT3_LOW	; CLEAR BIT COLUMN 3
	CLR_IO_BIT		PORTH,			BIT4_LOW	; CLEAR BIT COLUMN 4
	LDI				R24,			2
	RCALL			delay_micros

	SBI				PORTG,			5			; SET BIT COLUMN 1
	LDI				R24,			2
	RCALL			delay_micros
	SBIC			PINF,			5			; ROW 1 (1)
	RJMP			return_key		
	INC				R19							; 1
	SBIC			PINF,			4			; ROW 2 (4)
	RJMP			return_key
	INC				R19							; 2
	SBIC			PINE,			4			; ROW 3 (7)
	RJMP			return_key
	INC				R19							; 3
	SBIC			PINE,			5			; ROW 4 (*)
	RJMP			return_key
	INC				R19							; 4
	CBI				PORTG,			5			; CLEAR BIT COLUMN 1

	SBI				PORTE,			3			; SET BIT COLUMN 2
	LDI				R24,			2
	RCALL			delay_micros
	SBIC			PINF,			5			; ROW 1 (2)
	RJMP			return_key		
	INC				R19							; 5
	SBIC			PINF,			4			; ROW 2 (5)
	RJMP			return_key
	INC				R19							; 6
	SBIC			PINE,			4			; ROW 3 (8)
	RJMP			return_key
	INC				R19							; 7
	SBIC			PINE,			5			; ROW 4 (0)
	RJMP			return_key
	INC				R19							; 8
	CBI				PORTE,			3			; CLEAR BIT COLUMN 2

	SET_IO_BIT		PORTH,			BIT3_HIGH	; SET BIT COLUMN 3
	LDI				R24,			2
	RCALL			delay_micros
	SBIC			PINF,			5			; ROW 1 (3)
	RJMP			return_key		
	INC				R19							; 9
	SBIC			PINF,			4			; ROW 2 (6)
	RJMP			return_key
	INC				R19							; 10
	SBIC			PINE,			4			; ROW 3 (9)
	RJMP			return_key
	INC				R19							; 11
	SBIC			PINE,			5			; ROW 4 (#)
	RJMP			return_key
	INC				R19							; 12
	CLR_IO_BIT		PORTH,			BIT3_LOW	; CLEAR BIT COLUMN 3

	SET_IO_BIT		PORTH,			BIT4_HIGH	; SET BIT COLUMN 4
	LDI				R24,			2
	RCALL			delay_micros
	SBIC			PINF,			5			; ROW 1 (A)
	RJMP			return_key		
	INC				R19							; 13
	SBIC			PINF,			4			; ROW 2 (B)
	RJMP			return_key
	INC				R19							; 14
	SBIC			PINE,			4			; ROW 3 (C)
	RJMP			return_key
	INC				R19							; 15
	SBIC			PINE,			5			; ROW 4 (D)
	RJMP			return_key
	INC				R19							; 16 (NO_KEY)
	CLR_IO_BIT		PORTH,			BIT4_LOW	; CLEAR BIT COLUMN 4
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