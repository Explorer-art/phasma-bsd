bits 32

global start
extern main

section .text

start:
	call main

	mov eax, 0
	mov ebx, msg
	mov ecx, msg_len

	mov eax, 7
	int 0x80

msg			db "Hello from test2!", 0x0A
msg_len		equ $-msg