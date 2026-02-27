#include <exec.h>
#include <fat32.h>
#include <kernel.h>
#include <utils/kmalloc.h>
#include <x86.h>
#include <elf.h>
#include <string.h>
#include <memory.h>

uint8_t is_elf(uint8_t* ident) {
    uint8_t magic[4] = { 0x7F, 'E', 'L', 'F' };
    return !memcmp(ident, magic, sizeof(magic));
}

uint8_t exec(const char* path) {
    fat32_file_t file;
    if (!fat32_open_file(&kinfo.ctx, &file, path)) return 0;

    elf32_hdr_t elf32_hdr;

    if (!fat32_read(&file, &elf32_hdr, sizeof(elf32_hdr_t))) {
        fat32_close(&file);
        return 0;
    }

    if (!is_elf(elf32_hdr.e_ident)) return 0;

    elf32_phdr_t elf32_phdr;
    fat32_seek(&file, elf32_hdr.e_phoff);

    // Find PH_LOAD
    for (int i = 0; i < elf32_hdr.e_phnum; i++) {
        if (!fat32_read(&file, &elf32_phdr, sizeof(elf32_phdr_t))) {
            fat32_close(&file);
            return 0;
        }

        if (elf32_phdr.p_type == PH_LOAD_TYPE)
            break;

        if (elf32_phdr.p_vaddr == USER_START_ADDR)
            break;
    }

    fat32_seek(&file, elf32_phdr.p_offset);

    if (!fat32_read(&file, USER_START_ADDR, elf32_phdr.p_filesz)) {
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