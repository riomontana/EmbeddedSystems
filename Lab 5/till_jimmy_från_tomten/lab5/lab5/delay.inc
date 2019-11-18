/*
 * delay.inc
 *
 * This file contains delay routines.
 *
 * Created by Mathias Beckius, 25 June 2015, for the course DA346A at
 * Malmo University.
 *
 * Edited by Linus Forsberg och Jimmy 흆esson 20171207
 * Is used for when a delay is needed.
 */

;==============================================================================
; Delay of 1 탎 (including RCALL)
;==============================================================================
delay_1_micros:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	RET

;==============================================================================
; Delay of X 탎
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R24				Input parameter data (X 탎)
;==============================================================================
delay_micros:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	DEC				R24
	CPI				R24,			0				; more loops to do?
	BRNE			delay_micros					; continue!
	RET

;==============================================================================
; Delay of X ms
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R18				Copy of parameter data (X ms)
;	R24				Input parameter data (X ms) and
;					also input to 'delay_micros'.
;==============================================================================
delay_ms:
	MOV				R18,			R24
loop_dms:
	LDI				R19,			4
loop_dms2:
	LDI				R24,			250
	RCALL			delay_micros
	DEC				R19
	CPI				R19,			0
	BRNE			loop_dms2
	DEC				R18
	CPI				R18,			0
	BRNE			loop_dms
	RET

;==============================================================================
; Delay of 1 s
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R20				Number of times delay_ms should run
;	R24				Input to 'delay_micros'.
;==============================================================================
delay_1_s:
	LDI				R20,			4
loop_1s:
	LDI				R24,			250
	RCALL			delay_ms
	DEC				R20
	CPI				R20,			0
	BRNE			loop_1s
	RET

;==============================================================================
; Delay of X s
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R17				Copy of parameter data (X s)
;	R24				Input parameter data (X s) and
;					also input to 'delay_micros'.
;==============================================================================
delay_s:
	MOV				R17,			R24
loop_ds:
	LDI				R20,			4
loop_ds2:
	LDI				R24,			250
	RCALL			delay_ms
	DEC				R20
	CPI				R20,			0
	BRNE			loop_ds2
	DEC				R17
	CPI				R17,			0
	BRNE			loop_ds
	RET