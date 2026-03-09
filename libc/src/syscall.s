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


global sys_gets

sys_gets:
    push ebp
    mov ebp, esp

    mov eax, 1
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
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


global sys_close

sys_close:
    push ebp
    mov ebp, esp

    mov eax, 3
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_read

sys_read:
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


global sys_read_dir

sys_read_dir:
    push ebp
    mov ebp, esp

    mov eax, 5
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_write

sys_write:
    push ebp
    mov ebp, esp

    mov eax, 6
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
    mov edx, [ebp + 16]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_seek

sys_seek:
    push ebp
    mov ebp, esp

    mov eax, 7
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_getsize

sys_getsize:
    push ebp
    mov ebp, esp

    mov eax, 8
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_rename

sys_rename:
    push ebp
    mov ebp, esp

    mov eax, 9
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_rm

sys_rm:
    push ebp
    mov ebp, esp

    mov eax, 10
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_mkdir

sys_mkdir:
    push ebp
    mov ebp, esp

    mov eax, 11
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_rmdir

sys_rmdir:
    push ebp
    mov ebp, esp

    mov eax, 12
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_getcd

sys_getcd:
    push ebp
    mov ebp, esp

    mov eax, 13
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_chdir

sys_chdir:
    push ebp
    mov ebp, esp

    mov eax, 14
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_exec

sys_exec:
    push ebp
    mov ebp, esp

    mov eax, 15
    mov ebx, [ebp + 8]
    mov ecx, [ebp + 12]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_exit

sys_exit:
    push ebp
    mov ebp, esp

    mov eax, 16
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_sleep

sys_sleep:
    push ebp
    mov ebp, esp

    mov eax, 17
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_alloc

sys_alloc:
    push ebp
    mov ebp, esp

    mov eax, 18
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret


global sys_free

sys_free:
    push ebp
    mov ebp, esp

    mov eax, 19
    mov ebx, [ebp + 8]
    int 0x80

    mov esp, ebp
    pop ebp
    ret