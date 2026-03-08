bits 32

%define STACK_POINT 0x200000

section .text
	; multiboot spec
	align 4
	dd 0x1BADB002					; magic
	dd 0x00000000					; flags
	dd -(0x1BADB002 + 0x00000000)	; checksum

global start
extern kmain

start:
	cli
	mov esp, STACK_POINT
	push ebx
	push eax
	call kmain
	hlt

section .bss