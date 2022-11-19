; Author: Mai Tran
; Course: COSC 2425
; Program Set 4
; Reference: I got help from Mr. C

.386
.model flat, stdcall,c
.stack  4096

; include C libraries
includelib libucrt.lib
includelib libvcruntime.lib
includelib libcmt.lib
includelib legacy_stdio_definitions.lib

.data

	; string prompt
	userPrompt byte 'Please enter a number to calculate sum: ', 0
	outputPrompt1 byte 'The sum of 1 to ', 0
	outputPrompt2 byte ' is: ', 0

	; variable
	userChoice dword 0,0
	sum	dword 0
	sumLength dword 0
	sumTemp dword 0

; include c function
.code
	extrn printf:near
	extrn gets:near
	extrn atoi:near
	extrn exit:near


public  main
main    proc
	
	; prompt for user input
	push offset userPrompt;
	call printf
	push offset userChoice
	call gets
	push offset userChoice
	call atoi

	mov ebx, userChoice
	mov eax, sum

	; Adds up all of the digits
	sumLoop:
	add sum,ecx
	loop sumLoop ; Loops once for each digit
	
	; copy sum to eax
	mov eax, sum			; copy sum to eax

	; get number of digit in sum
	lengthLoop:
	mov edx, 0				; reset edx to 0 before perfrom division
	mov ebx, 10				; set ebx to 10
	div ebx					; divied eax by 10
	inc sumLength			; increase sumLength

	mov ecx, eax			; copy eax to counter
	inc ecx					; incease counter by 1, so that only eax value control the loop
	loop lengthLoop			;loop until eax is 0, where there are no digits left

	;display output prompt
	push offset outputPrompt1
	call printf
	push offset userChoice
	call printf
	push offset outputPrompt2
	call printf


	; loop through each digit and output
	outputLoop:
	mov eax, sum			;copy sum to eax
	mov ecx, sumLength		;set counter to sumLength
	currentdigitLoop:
	mov	edx, 0				;reset edx to 0 before perfrom division
	mov ebx, 10				; set ebx to 10
	div ebx					; divide eax by 10
	loop currentdigitLoop	; loop until the most significant bit is in edx

	mov sumTemp, edx		; temp to hold current diti
	add sumTemp, 48			;adjust current digit to ascii value
	push offset sumTemp	
	call printf				; print current digit to the screen

	mov ecx, sumLength
	dec sumLength
	loop outputLoop			;loop until there displayed all digits

	push 0
	call exit
main    endp
end