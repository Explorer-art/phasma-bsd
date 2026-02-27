bits 32


global sys_puts

sys_puts:
    push ebp
    mov ebp, esp

    mov eax, 0
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_getchar

sys_getchar:
    push ebp
    mov ebp, esp

    mov eax, 1
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_open

sys_open:
    push ebp
    mov ebp, esp

    mov eax, 2
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_read

sys_read:
    push ebp
    mov ebp, esp

    mov eax, 3
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
    mov edx, [ebp + 16]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_write

sys_write:
    push ebp
    mov ebp, esp

    mov eax, 4
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
    mov edx, [ebp + 16]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_close

sys_close:
    push ebp
    mov ebp, esp

    mov eax, 5
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_exec

sys_exec:
    push ebp
    mov ebp, esp

    mov eax, 6
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_exit

sys_exit:
    push ebp
    mov ebp, esp

    mov eax, 7
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_sleep

sys_sleep:
    push ebp
    mov ebp, esp

    mov eax, 8
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_ioctl

sys_ioctl:
    push ebp
    mov ebp, esp

    mov eax, 9
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
    int 0x80

    mov esp, ebp
    pop ebp
    ret