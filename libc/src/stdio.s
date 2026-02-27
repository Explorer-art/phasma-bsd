bits 32

global put

put:
    push ebp
    mov ebp, esp

    mov eax, 0
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
    int 0x80

    mov esp, ebp
    pop ebp
    ret

global getchar

getchar:
    push ebp
    mov ebp, esp

    mov eax, 1
    int 0x80

    mov esp, ebp
    pop ebp
    ret