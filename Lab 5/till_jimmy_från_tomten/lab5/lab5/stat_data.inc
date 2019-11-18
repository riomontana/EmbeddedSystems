 /* ---------------------------------------------------------------------------------------------------------
  * stat_data.inc
  *
  * Space in the RAM to save the results from dice throws.
  * The following functions are provided:
  * store_stat (R24 contains the dice value) 
  * the function will increment the total number of throws and the number of throws with results equals R24.
  * get_stat (R24 gives the value for which the result is retrieved) 
  * If R24 = 0, the total number of throws shall be returned. The result is returned in R24.
  * clear_stat (no parameters in nor out) 
  * Clears all data.
  * Edited by:Linus Forsberg & Jimmy Åkesson 2017-12-14
  * -------------------------------------------------------------------------------------------------------------*/

		.DSEG								; The following applies to the RAM:
		.ORG		0x200					; Set starting point address of datasegment to 0x200
space: 
		.BYTE		7						; Creating correct amount of space needed
		.CSEG
store_stat:
		LDI			XL,			LOW(space)	; Load imidiate X register with our byte label
		LDI			XH,			HIGH(space) ; Load imidiate X register with our byte label
		
		LD			R19,		X			; Load value of X pointer (0x200) to R20
		INC			R19						; Increace R20 with 1
		ST			X,			R19			; Save value of R20 to X pointer (0x200)

		ADD			XL,			R20			; Move X Low pointer R24 value steps (R24=2, XL=0x202)
		LD			R19,		X			; Load value of X pointer (0x20x) to R20
		INC			R19						; Increase R20 with 1
		ST			X,			R19			; Save value of R20 to X pointer (0x20x)

		RET
get_stat: 
		LDI			XL,			LOW(space)	; Load imidiate X register with our byte label
		LDI			XH,			HIGH(space) ; Load imidiate X register with our byte label

		ADD			XL,			R24			; Move XL pointer R24 value steps
		LD			R24,		X			; Load value of X pointer
		RET
clear_stat:
		LDI			XL,			LOW(space)	; Load imidiate X register with our byte label
		LDI			XH,			HIGH(space) ; Load imidiate X register with our byte label

		LDI			R20,		0			; Set R20 to 0, used for overwrite
		LDI			R24,		7			; Set R24 reg to 7 for looping
clear_loop:		
		ST			X+,			R20			; Load R20 value (0) on X-pointer
		DEC			R24						; Decrement R24
		CPI			R24,		0			; Check if R24 is 0
		BRNE		clear_loop				; If not 0, loop again
		RCALL		delay_1_s
		RET									; If 0 return



