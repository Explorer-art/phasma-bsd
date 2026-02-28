#include <kernel.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/pic.h>
#include <drivers/pata_pio.h>
#include <drivers/tty.h>
#include <drivers/keyboard.h>
#include <drivers/timer.h>
#include <fat32.h>
#include <x86.h>
#include <utils/kprintf.h>
#include <utils/kmalloc.h>
#include <utils/config.h>
#include <exec.h>

kernel_info_t kinfo = {0};

void init_list(void);
void load_init_list(void);
void load_autoexec(void);

void kmain(uint32_t magic) {
    if (kinfo.full_initialized)
        goto autoexec;
    
    if (!kinfo.pre_initialized && kinfo.base_initialized)
        goto pre_init;

	tty_init();
	gdt_init();
	idt_init();
    pic_remap(0x20, 0x28);

    Drives drives = {0};
    pata_pio_detect_drives(&drives);

    if (!fat32_init(&kinfo.ctx, 2048)) {
        kprintf("error: FAT32 init failed\n");
        goto pause;
    }

    keyboard_init();
    timer_init(TIMER_FREQUENCY);

    load_init_list();
    load_autoexec();

    kinfo.base_initialized = 1;

    sti();

    kprintf("info: starting pre init...\n");

pre_init:
    init_list();
    kinfo.full_initialized = 1;

autoexec:
    if (!exec(kinfo.autoexec_path)) {
        kpanic("error: load autoexec program failed");
    }

    kprintf("System halted!\n");

pause:
    for (;;);
}

void init_list(void) {
    char buffer[256];

    strncpy(buffer, kinfo.init_list, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char* path = strtok(buffer, ",");

    while (path) {
        exec(path);
        kinfo.pre_initialized--;
        path = strtok(NULL, ",");
    }
}

void load_init_list(void) {
    fat32_file_t fp;
    char buffer[256];

    if (!fat32_open_file(&kinfo.ctx, &fp, "/etc/system.cfg")) {
        kpanic("error: Cannot open system.cfg");
    }

    if (!config_get_str(&fp, "INIT_LIST", buffer, sizeof(buffer))) {
        kpanic("error: Key 'AUTOEXEC' not found");
    }

    fat32_close(&fp);
    int length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    }

    strncpy(kinfo.init_list, buffer, sizeof(kinfo.init_list) - 1);
    kinfo.init_list[sizeof(kinfo.init_list) - 1] = '\0';
    char* path = strtok(buffer, ",");

    while (path) {
        kinfo.pre_initialized++;
        path = strtok(NULL, ",");
    }
}

void load_autoexec(void) {
    fat32_file_t fp;

    if (!fat32_open_file(&kinfo.ctx, &fp, "/etc/system.cfg")) {
        kpanic("error: Cannot open system.cfg");
    }

    if (!config_get_str(&fp, "AUTOEXEC", kinfo.autoexec_path, sizeof(kinfo.autoexec_path))) {
        kpanic("error: Key 'AUTOEXEC' not found");
    }

    fat32_close(&fp);
}