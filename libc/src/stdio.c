#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <syscall.h>

void puts(const char* str) {
    sys_puts(str, strlen(str));
}