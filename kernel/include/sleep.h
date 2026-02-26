#ifndef SLEEP_H
#define SLEEP_H

#include <kernel.h>
#include <stdint.h>

extern kernel_info_t kinfo;

void sleep(uint32_t seconds);

#endif