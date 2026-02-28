bits 32

global start
extern main

section .text

start:
	call main

	mov ebx, eax

	mov eax, 7
	int 0x80