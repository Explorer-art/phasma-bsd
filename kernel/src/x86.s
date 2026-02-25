global gdt_flush

gdt_flush:
	mov eax, [esp + 4]
	lgdt [eax]

	mov eax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp 0x08:.flush

.flush:
	ret

global idt_flush

idt_flush:
	mov eax, [esp + 4]
	lidt [eax]
	ret

global inb

inb:
	mov edx, [esp + 4]
	in al, dx
	ret

global outb

outb:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	out dx, al
	ret

global inw

inw:
	mov edx, [esp + 4]
	in ax, dx
	ret

global outw

outw:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	out dx, ax
	ret