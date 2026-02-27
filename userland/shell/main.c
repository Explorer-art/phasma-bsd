#include <syscall.h>
#include <stdio.h>

int main() {
    puts("Hello world!\n");

    sys_getchar();
    puts("\n");
    return 0;
}