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
#include <sleep.h>

kernel_info_t kinfo = {0};

void kmain(uint32_t magic) {
	tty_init();
	gdt_init();
	idt_init();
    pic_remap(0x20, 0x28);

    Drives drives = {0};
    pata_pio_detect_drives(&drives);

    fat32_ctx_t fat32_ctx = {0};

    if (!fat32_init(&fat32_ctx, 2048)) {
        kprintf("error: FAT32 init failed\n");
        goto pause;
    }

    keyboard_init();
    timer_init(TIMER_FREQUENCY);

    sti();

    fat32_file_t file;
    int bytes_read = 0;

    if (!fat32_open_file(&fat32_ctx, &file, "/etc/system.cfg")) {
        kpanic("error: Cannot open system.cfg");
    }

    if (!config_get_str(&file, "AUTOEXEC", kinfo.autoexec, sizeof(kinfo.autoexec))) {
        kpanic("error: Key 'AUTOEXEC' not found");
    }
    
    fat32_close(&file);

    kprintf("info: kernel init finish\n");

    kprintf("\nPress any key...");
    keyboard_getchar();

    tty_clear();

pause:
    for (;;);
}
