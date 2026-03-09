ASM = nasm
CC = gcc
LD = ld
CFLAGS = -m32 -ffreestanding -fno-pic -fno-pie -fno-stack-protector -fno-builtin -Wall -Wextra -I $(LIBC_DIR)/include
SRC_DIR ?= src
BUILD_DIR ?= build
LIBC_DIR ?= ../libc

ELF_FILES = \
$(BUILD_DIR)/motd.elf \
$(BUILD_DIR)/shell.elf \
$(BUILD_DIR)/echo.elf \
$(BUILD_DIR)/clear.elf \
$(BUILD_DIR)/ls.elf \
$(BUILD_DIR)/cat.elf \

LIBC_OBJECTS = \
$(LIBC_DIR)/build/ctype.o \
$(LIBC_DIR)/build/string.o \
$(LIBC_DIR)/build/memory.o \
$(LIBC_DIR)/build/syscall.o \
$(LIBC_DIR)/build/stdio.o \
$(LIBC_DIR)/build/stdlib.o \

PHONY: all clean always

all: clean always libc $(ELF_FILES)

libc:
	make -C $(LIBC_DIR)

$(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.o
	$(LD) -m elf_i386 -T linker.ld -o $@ $< $(LIBC_OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -f -r $(BUILD_DIR)