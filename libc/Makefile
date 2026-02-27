ASM = nasm
CC = gcc
LD = ld
CFLAGS = -m32 -ffreestanding -fno-stack-protector -fno-builtin -Wall -Wextra -I include
SRC_DIR ?= src
BUILD_DIR ?= build

OBJECTS = \
$(BUILD_DIR)/ctype.o \
$(BUILD_DIR)/string.o \
$(BUILD_DIR)/memory.o \
$(BUILD_DIR)/syscall.o \
$(BUILD_DIR)/stdio.o \

PHONY: all clean always

all: clean always $(OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	$(ASM) -f elf32 $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -f -r $(BUILD_DIR)