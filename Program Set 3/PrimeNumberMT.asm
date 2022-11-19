; Author: Mai Tran
; Course: COSC 2425
; Program Set 3 EC
; Reference: Modified version from SumNum program

.386
.model flat, stdcall, c
.stack 4096

.data
userChoice word 0,0					; hold user input
sum dword 0							; temporary variable to hold user input
sumTemp dword 0	
sumLength dword 0
counter dword 2						; counter varible, used as denominator
count dword 0						; count variable to hold total number of times the remainer equal to 0

userPrompt byte 'Please enter the number to check for prime: ', 0
notPrime byte ' is not a prime number', 0
prime byte ' is a prime number', 0

.code
includelib libucrt.lib
includelib libvcruntime.lib
includelib libcmt.lib
includelib legacy_stdio_definitions.lib

extrn printf:near
extrn gets:near
extrn atoi:near
extrn exit:near

public main
main proc

push offset userPrompt				; Prompts the user for their number
call printf							
push offset userChoice				; Receives the input from the user
call gets							


checkLoop:							; check for prime number

push offset userChoice				; Converts the input from a string to an integer 
call atoi							; store in eax

.if counter == eax					; compare counter and user input
	loop exitCheck					; exit loop if counter euqal user input
.endif

mov edx, 0;							; set edx to 0 before perform division
mov ebx, counter					; set ebx to counter
div ebx								; devide userChoice by ebx

.if edx == 0						; increase count if devisible
	inc count
.else								; if not divisible 
	inc counter						; increase denominator by one
	loop checkLoop					; loop until denominator equal user input number
.endif								
exitCheck:							; exit loop


push offset userChoice				; display user input
call printf

.if count != 0						; is not prime number message
push offset notPrime
call printf
.else								; prime number message
push offset prime
call printf
.endif								; end if condition

push 0
call exit

main endp
end