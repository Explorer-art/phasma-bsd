#ifndef EXEC_H
#define EXEC_H

#include <stdint.h>

typedef void (*entry_point_t)(void);

uint8_t exec(const char* path);
uint8_t exit(void);

#endif