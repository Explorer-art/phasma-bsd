#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>

#define PATH_MAX_SIZE 256

typedef uint32_t file_t;

int putchar(int c);
int puts(const char* str);
int getchar(void);
char* gets(char* str, unsigned int size);
file_t* fopen(const char* path);
void fclose(file_t* fp);

#endif