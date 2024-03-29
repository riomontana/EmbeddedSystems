/*
 * delay.inc
 *
 * This file contains delay routines.
 *
 * Created by Mathias Beckius, 25 June 2015, for the course DA346A at
 * Malmo University.
 */

;==============================================================================
; Delay of 1 �s (including RCALL)
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
; Delay of X �s
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R24				Input parameter data (X �s)
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

	; UPPGIFT: implementera subrutinen
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

	; UPPGIFT: implementera subrutinen

	RET