#ifndef KERNEL_H
#define KERNEL_H

#include <fat32.h>
#include <stdint.h>

#define TIMER_FREQUENCY 20

typedef struct {
    uint32_t ticks;
    char autoexec[PATH_MAX_SIZE];
} __attribute__((packed)) kernel_info_t;

#endif