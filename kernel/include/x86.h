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

static inline void lcr3(uintptr_t val) {
  asm volatile("mov %0,%%cr3" : : "r" (val));
}

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t value);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t value);
void gdt_flush(uint32_t addr);
void idt_flush(uint32_t addr);

#endif