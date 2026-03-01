#include <utils/kpanic.h>
#include <x86.h>
#include <utils/kprintf.h>

void kpanic(const char* text) {
	uint32_t eax = get_eax();
    uint32_t ebx = get_ebx();
    uint32_t ecx = get_ecx();
    uint32_t edx = get_edx();
    uint32_t edi = get_edi();
    uint32_t esi = get_esi();
    uint32_t ebp = get_ebp();
    uint32_t esp = get_esp();

	kprintf("kernel panic: %s\n\n", text);
	kprintf(
        "EAX = 0x%x\n"
        "EBX = 0x%x\n"
        "ECX = 0x%x\n"
        "EDX = 0x%x\n"
        "EDI = 0x%x\n"
        "ESI = 0x%x\n"
        "EBP = 0x%x\n"
        "ESP = 0x%x\n", eax, ebx, ecx, edx , edi, esi, ebp, esp);
	for (;;);
}
