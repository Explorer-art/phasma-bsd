#include <exec.h>
#include <fat32.h>
#include <kernel.h>
#include <utils/kmalloc.h>
#include <x86.h>
#include <string.h>

uint8_t exec(const char* path) {
    fat32_file_t file;
    if (!fat32_open_file(&kinfo.ctx, &file, path)) return 0;

    if (!fat32_read(&file, USER_START_ADDR, file.size)) {
        fat32_close(&file);
        return 0;
    }
    
    fat32_close(&file);

    entry_point_t entry = (entry_point_t)USER_START_ADDR;
    entry();

    return 1;
}

uint8_t exit(void) {
    jmp_to(KERNEL_START_ADDR);
    return 1;
}