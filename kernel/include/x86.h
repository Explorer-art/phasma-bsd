#ifndef X86_H
#define X86_H

#include <stdint.h>

static inline void cli(void) {
    asm volatile("cli");
}

static inline void sti(void) {
    asm volatile("sti");
}

static inline void hlt(void) {
    asm volatile("hlt");
}

static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    asm volatile("inb %1, %0" : "=a"(value) : "d"(port));
    return value;
}

static inline uint16_t inw(uint16_t port) {
    uint16_t value;
    asm volatile("inw %1, %0" : "=a"(value) : "d"(port));
    return value;
}

static inline void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" : : "a"(value), "d"(port));
}

static inline void outw(uint16_t port, uint16_t value) {
    asm volatile("outw %0, %1" : : "a"(value), "d"(port));
}

static inline void lcr3(uintptr_t addr) {
    asm volatile("mov %0,%%cr3" : : "r" (addr));
}

static inline uint32_t get_eax(void) {
    uint32_t value;
    asm volatile("movl %%eax, %0" : "=r"(value) : : "eax");
    return value;
}

static inline uint32_t get_ebx(void) {
    uint32_t value;
    asm volatile("movl %%ebx, %0" : "=r"(value) : : "ebx");
    return value;
}

static inline uint32_t get_ecx(void) {
    uint32_t value;
    asm volatile("movl %%ecx, %0" : "=r"(value) : : "ecx");
    return value;
}

static inline uint32_t get_edx(void) {
    uint32_t value;
    asm volatile("movl %%edx, %0" : "=r"(value) : : "edx");
    return value;
}

static inline uint32_t get_edi(void) {
    uint32_t value;
    asm volatile("movl %%edi, %0" : "=r"(value) : : "edi");
    return value;
}

static inline uint32_t get_esi(void) {
    uint32_t value;
    asm volatile("movl %%esi, %0" : "=r"(value) : : "esi");
    return value;
}

static inline uint32_t get_ebp(void) {
    uint32_t value;
    asm volatile("movl %%ebp, %0" : "=r"(value) : : "eax");
    return value;
}

static inline uint32_t get_esp(void) {
    uint32_t value;
    asm volatile("movl %%esp, %0" : "=r"(value) : : "eax");
    return value;
}

static inline void jmp_to_entry(uint32_t entry_point, uint32_t stack_point, uint32_t argc, uint32_t argv) {
    __asm__ volatile (
        "mov %1, %%esp\n\t"
        "push %3\n\t"
        "push %2\n\t"
        "push 0x100000\n\t"
        "jmp *%0"
        : : "r"(entry_point), "r"(stack_point), "r"(argc), "r"(argv) : "esp"
    );
}

static inline void switch_stack_and_jmp_to(uint32_t entry_point, uint32_t stack_point) {
    __asm__ volatile (
        "mov %1, %%esp\n\t"
        "jmp *%0"
        : : "r"(entry_point), "r"(stack_point)
    );
}

void gdt_flush(uint32_t addr);
void idt_flush(uint32_t addr);

#endif