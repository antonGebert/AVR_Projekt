;************************************************************************
;*
;*							Round Robin List
;*					Generates a list and adds the functions 
;*					to fetch values from the list and add
;*					data to the list. AVG function is 26 cycles.
;*
;*					By: Anton Gebert, 16/06/2019
;*
;************************************************************************
;
; Functions included in the file is
; addToList, 26 cycles, adds data and moves pointer
; R16: Prog info, R17:R18 Value, R19:R20 Counter
;
; getFromList



; Make a list consisting of 512 bytes
;Program info 8bit | Value 16 bit	| Counter 16bit  |		  |	        |		 |
;------------------------------------------------------------------
;			 0,0   |	0,1	|		|	   |		 |		  |			|	0,8	 |
;			 1,0   |	1,1	|	    |	   |		 |        |			|	1,8	 |
;											.
;											.
;											.
;			63,0  |	  63,1  |
;

.DSEG
List:
.BYTE 512
endlist:
.CSEG
; 22-26 cycles to store data array
addToList:
	; Store
	ST		Y+,R16			; Prog info
	ST		Y+,R17			; Value H
	ST		Y+,R18			; Value L
	ST		Y+,R19			; Count H
	ST		Y+,R20			; Count L
	ADIW	Y,3
	; Check endOfList
	CPI		YH,HIGH(endList)
	BRNE	addToListEnd
	CPI		YL,LOW(endList)
	BRNE	addToListEnd
	LDI		YH,HIGH(List)
	LDI		YL,LOW(List)
addToListEnd:
	RET

; Get value from row R16 and colum R17
; R16 = 0-64 Row
; R17 = 0-8  Column
; 27 Cycles to execute
getFromList:
	PUSH	YH
	PUSH	YL
	; Load pointer to top
	LDI		YH,HIGH(List)
	LDI		YL,LOW(List)
	; Add row
	LDI		R18,8
	MUL		R18,R16		; Ans in R0:R1
	ADD		YL,R0
	ADC		YH,R1
	; Add column
	ADD		YL,R17
	LDI		R17,0
	ADC		YH,R17
	; Get data
	LD		R16,Y
	POP		YL
	POP		YH
	RET

; Input row R16
; Return data in R16
; 28 cycles to execute
getProgramFromList:
	PUSH	YH
	PUSH	YL
	PUSH	R17
	; Load pointer to top
	LDI		YH,HIGH(List)
	LDI		YL,LOW(List)
	; Add row
	LDI		R17,8
	MUL		R17,R16		; Ans in R0:R1
	ADD		YL,R0
	ADC		YH,R1
	; Get data
	LD		R16,Y		; 1st Column
	POP		R17
	POP		YL
	POP		YH
	RET

; Input row R16
; Return data in R16:R17
; 26 Cycles to execute
getValueFromList:
	PUSH	YH
	PUSH	YL
	; Load pointer to top
	LDI		YH,HIGH(List)
	LDI		YL,LOW(List)
	; Add row
	LDI		R17,8
	MUL		R17,R16		; Ans in R0:R1
	ADD		YL,R0
	ADC		YH,R1
	; Get data
	LDD		R16,Y+1		; 2nd column
	LDD		R17,Y+2		; 3rd column
	POP		YL
	POP		YH
	RET

; Input row R16
; Return data in R16:R17
; 26 Cycles to execute 
getCounterFromList:
	PUSH	YH
	PUSH	YL
	; Load pointer to top
	LDI		YH,HIGH(List)
	LDI		YL,LOW(List)
	; Add row
	LDI		R17,8
	MUL		R17,R16		; Ans in R0:R1
	ADD		YL,R0
	ADC		YH,R1
	; Get data
	LDD		R16,Y+3		; 4nd column
	LDD		R17,Y+4		; 5rd column
	POP		YL
	POP		YH
	RET