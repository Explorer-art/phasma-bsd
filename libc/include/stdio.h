#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>
#include <stddef.h>

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

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define FILE uint32_t

int putchar(int c);
int puts(const char* str);
void printf(const char* fmt, ...);
int getchar(void);
char* gets(char* str, unsigned int size);
FILE* fopen(const char* path);
void fclose(FILE* fp);
size_t fread(void* buffer, size_t size, size_t n, FILE* fp);
size_t fwrite(const void* buffer, size_t size, size_t n, FILE* fp);
int fseek(FILE* fp, uint32_t offset, int mode);

#endif