#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>

#define KEY_ENTER           	10

typedef uint32_t file_t;

int putchar(int c);
int puts(const char* str);
int getchar(void);
char* gets(char* str, unsigned int size);

#endif