bits 32
org 0x400000

section .text

start:
	mov eax, 0
	mov ebx, msg
	mov ecx, msg_len
	int 0x80

	mov eax, 1
	int 0x80

	mov eax, 6
	mov ebx, test2_file
	int 0x80

	mov eax, 7
	int 0x80

msg			db "Hello from test1", 0x0A
msg_len		equ $-msg

test2_file	db "test2.bin"