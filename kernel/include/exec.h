#ifndef EXEC_H
#define EXEC_H

#include <stdint.h>

typedef void (*entry_point_t)(int argc, char** argv);

uint8_t exec(const char* path, const char** argv);
uint8_t exit(void);

#endif