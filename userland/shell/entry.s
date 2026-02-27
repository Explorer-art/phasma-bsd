bits 32

global start
extern main

section .text

start:
	call main

	mov eax, 7
	int 0x80