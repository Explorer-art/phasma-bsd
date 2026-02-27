#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

void sys_puts(const char* buffer, uint32_t size);
uint8_t sys_getchar(void);
uint32_t* sys_open(const char* path);
uint32_t sys_read(uint32_t* fp, const char* buffer, uint32_t size);
uint32_t sys_write(uint32_t* fp, char* buffer, uint32_t size);
void sys_close(uint32_t* fp);
void sys_exec(char* path);
void sys_exit(uint32_t status);
void sys_sleep(uint32_t seconds);
uint32_t sys_ioctl(const char* id, uint32_t cmd);

#endif