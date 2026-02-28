#include <stdlib.h>
#include <syscall.h>

void exec(const char* path) {
    sys_exec(path);
}

void exit(uint32_t status) {
    sys_exit(status);
}