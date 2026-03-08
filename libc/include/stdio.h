#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>

#define PATH_MAX_SIZE 256

#define PRINTF_STATE_NORMAL 0
#define PRINTF_STATE_LENGTH 1
#define PRINTF_STATE_LENGTH_SHORT 2
#define PRINTF_STATE_LENGTH_LONG 3
#define PRINTF_STATE_SPEC 4

#define PRINTF_LENGTH_DEFAULT 0
#define PRINTF_LENGTH_SHORT 1
#define PRINTF_LENGTH_SHORT_SHORT 2
#define PRINTF_LENGTH_LONG 3
#define PRINTF_LENGTH_LONG_LONG 4

typedef uint32_t file_t;

int putchar(int c);
int puts(const char* str);
void printf(const char* fmt, ...);
int getchar(void);
char* gets(char* str, unsigned int size);
file_t* fopen(const char* path);
void fclose(file_t* fp);

#endif