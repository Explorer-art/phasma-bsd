#ifndef SYSCALL_H
#define SYSCALL_H

#include <cpu/irq.h>
#include <stdint.h>

#define SYSCALL_COUNT 20

typedef void (*syscall_t)(registers_t*);

#endif
