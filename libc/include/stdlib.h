#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

void exec(const char* path, const char** argv);
void exit(uint32_t status);

#endif