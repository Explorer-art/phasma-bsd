#include <sleep.h>
#include <x86.h>

void sleep(uint32_t seconds) {
    uint32_t target = kinfo.ticks + seconds * TIMER_FREQUENCY;

    while (kinfo.ticks < target) {
        hlt();
    }
}