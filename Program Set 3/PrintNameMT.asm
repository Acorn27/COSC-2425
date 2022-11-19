; Author: Mai Tran
; Course: COSC 2425
; Program Set 3-1
; Reference: 
;	+I used the code from this video and change message to my name:
;	https://youtu.be/bpZv5bOi5dE

.386
.model flat, stdcall, c
.stack 4096

.data
; varibale myName store name
myName BYTE 'MAI TRAN', 0

.code
includelib libucrt.lib
includelib legacy_stdio_definitions.lib
includelib libcmt.lib
includelib libvcruntime.lib

extrn printf:near
extrn exit:near

public main
main proc

	push	offset myName	; Pushes the name to the offset
	call	printf			; Prints out the name
	push	0
	call	exit

main endp
end