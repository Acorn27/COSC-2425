;author: Mai Tran
;Course: COSC 2425
;Program Set 3 required problem
;Reference: Modified version of SumNums program

.386
.model flat, stdcall, c
.stack 4096

.data
userChoice word 0,0				; hold user input
sum dword 0						; temp variable that hold the same value as user input
sumTemp dword 0					; temp var to hold individual digit in user input
sumLength dword 0				; hold length of number input
counter dword 1					; counter to disply number in reverse

userPrompt byte 'Please enter the number you want to reverse: ', 0
sumOutput1 byte 'The reversed number is: ', 0
errorPrompt byte 'Please enter the 5 digits number only.', 0

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

push offset userPrompt			; display input prompt
call printf						; Prompts the user for their number

push offset userChoice			; get user input from user
call gets

push offset userChoice			; convert input to integer and stored in ecx
call atoi

mov sum, ecx					; asign userChoice into a temp variable
mov eax,sum						; Sets the number in sum to eax, so it can be modified to find the length


lengthLoop:						; Gets the number of digits in the sum
mov edx,0						; Resets edx to 0 to hold the division remainder
mov ebx,10						; set ebx to 10
div ebx							; Divides the sum in eax by 10, reducing the number of digits by 1 (result is stored in eax)
inc sumLength					; Increments sumLength

mov ecx,eax
inc ecx
loop lengthLoop					; Loops until eax is 0, when there are no digits left

.if sumLength != 5				; input validation
	push offset errorPrompt		; display error message
	call printf 
	call exit
.else							; if input is valid
push offset sumOutput1			; display output message
call printf

outputLoop:						; Loops through each digit in the sum and outputs it in reversed order

mov eax,sum						; assign sum to eax
mov ecx,counter					; set counter, begin with 1

currentdigitLoop:				; get current digit, start with the lease significant one
mov edx,0						; Resets edx to 0 to hold the remainder of the division
mov ebx,10
div ebx							; Divides the sum in eax by 10, which moves the remainder to edx
loop currentdigitLoop			; Loops until the current digit is in edx

mov sumTemp,edx					; set current digit to sumTemp
add sumTemp,48					; Adjusts the current digit to its ascii value
push offset sumTemp		
call printf						; Outputs the current digit to the screen

inc counter						; increase counter by one
mov edx, counter				; move counter to edx to make comparasion
cmp edx, sumLength				; if counter less than sumLength, exit loop
	jg bail
loop outputLoop					; Loops until there are no digits left

bail:							; exit loop

.endif							; end of input validation condition


push 0
call exit

main endp
end
