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

uint8_t exec(const char* path, const char** argv) {
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

    int argc = 0;
    char** argv_tmp = argv;

    while (*argv_tmp != NULL) {
        argc++;
        argv_tmp++;
    }

    uint32_t esp = STACK_POINT;
    uint32_t* addrs = kmalloc(argc * sizeof(uint32_t));

    for (int i = 0; *argv != NULL; i++, argv++) {
        uint32_t length = strlen(*argv);
        esp -= length + 1;
        addrs[i] = esp;
        strcpy((char*)esp, *argv);
    }

    esp -= sizeof(uint32_t);
    *(uint32_t*)esp = 0;

    for (int i = argc - 1; i >= 0; i--) {
        esp -= sizeof(uint32_t);
        *(uint32_t*)esp = addrs[i];
    }

    kfree(addrs);

    uint32_t argv_ptr = esp;

    jmp_to_entry(USER_START_ADDR, esp, argc, argv_ptr);

    return 1;
}

uint8_t exit(void) {
    switch_stack_and_jmp_to(KERNEL_START_ADDR, STACK_POINT);
    return 1;
}