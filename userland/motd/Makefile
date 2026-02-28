LIBC_DIR ?= ../../libc
ASM = nasm
CC = gcc
LD = ld
CFLAGS = -m32 -ffreestanding -fno-pic -fno-pie -fno-stack-protector -fno-builtin -Wall -Wextra -I $(LIBC_DIR)/include

OBJECTS = \
main.o \

LIBC_OBJECTS = \
$(LIBC_DIR)/build/ctype.o \
$(LIBC_DIR)/build/string.o \
$(LIBC_DIR)/build/memory.o \
$(LIBC_DIR)/build/syscall.o \
$(LIBC_DIR)/build/stdio.o \
$(LIBC_DIR)/build/stdlib.o \

PHONY: all clean

all: clean motd.elf

motd.elf: $(OBJECTS)
	make -C $(LIBC_DIR)

	$(ASM) -f elf32 ../entry.s -o entry.o

	$(LD) -m elf_i386 -T ../linker.ld -o $@ $(OBJECTS) $(LIBC_OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f *.bin
	rm -f *.elf