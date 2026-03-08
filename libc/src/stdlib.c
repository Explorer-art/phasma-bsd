#include <stdlib.h>
#include <syscall.h>

void exec(const char* path, const char** argv) {
    sys_exec(path, argv);
}

void exit(uint32_t status) {
    sys_exit(status);
}