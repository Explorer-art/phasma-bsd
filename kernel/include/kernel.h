#ifndef KERNEL_H
#define KERNEL_H

#include <fat32.h>
#include <stdint.h>

#define KERNEL_START_ADDR   0x100000
#define USER_START_ADDR     0x400000
#define TIMER_FREQUENCY     20

typedef struct {
    uint8_t base_initialized;
    uint8_t pre_initialized;
    uint8_t full_initialized;
    uint32_t ticks;
    fat32_ctx_t ctx;
    char init_list[PATH_MAX_SIZE];
    char autoexec_path[PATH_MAX_SIZE];
} kernel_info_t;

extern kernel_info_t kinfo;

#endif