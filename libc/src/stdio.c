#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <syscall.h>

int putchar(int c) {
    return sys_puts(&c, sizeof(char));
}
int puts(const char* str) {
    return sys_puts(str, strlen(str));
}

int getc(void) {
    char c;
    sys_gets(&c, sizeof(char));
    return c;
}

char* gets(char* str, unsigned int size) {
    sys_gets(str, size);
    return str;
}