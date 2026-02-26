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

void kmain(uint32_t magic) {
    if (kinfo.initialized)
        goto autoexec;

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

    sti();

    fat32_file_t file;
    int bytes_read = 0;

    if (!fat32_open_file(&kinfo.ctx, &file, "/etc/system.cfg")) {
        kpanic("error: Cannot open system.cfg");
    }

    if (!config_get_str(&file, "AUTOEXEC", kinfo.autoexec_path, sizeof(kinfo.autoexec_path))) {
        kpanic("error: Key 'AUTOEXEC' not found");
    }
    
    fat32_close(&file);

    kprintf("AUTOEXEC = %s\n", kinfo.autoexec_path);

    kinfo.initialized = 1;

autoexec:
    if (!exec(kinfo.autoexec_path)) {
        kpanic("error: load autoexec program failed");
    }

    kprintf("System halted!\n");

pause:
    for (;;);
}
