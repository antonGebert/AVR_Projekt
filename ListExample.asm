/*
 * ListExample.asm
 *
 *  Created: 16/06/2019 11:00:29
 *   Author: Anton Gebert
 */ 


 .INCLUDE "m8def.inc"
 .INCLUDE "roundRobinList.inc"

.CSEG
start:
	; Initalize stack pointer
	LDI		R16,HIGH(RAMEND)
	OUT		SPH,R16
	LDI		R16,LOW(RAMEND)
	OUT		SPL,R16
	; Initalize list pointer
	LDI		YH,HIGH(List)
	LDI		YL,LOW(List)
	LDI		R16, 5
Loop:
	RCALL	addToList
	; Get data 
	LDI		R16,5			; 5th row
	LDI		R17,3			; 3rd column
	RCALL   getFromList
	LDI		R16,5			; 5th row
	RCALL	getProgramFromList
	LDI		R16,5			; 5th row
	RCALL	getValueFromList
	LDI		R16,5			; 5th row
	RCALL	getCounterFromList
	RJMP	loop




