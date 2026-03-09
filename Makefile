LD = ld
CFLAGS= -m32 -ffreestanding -fno-stack-protector -fno-builtin -Wall -Wextra -I src/include 
SRC_DIR ?= src
BUILD_DIR ?= build
KERNEL_DIR ?= kernel
USERLAND_DIR ?= userland
LOOP := $(shell losetup -f)

PHONY: all clean always

all: clean always $(BUILD_DIR)/phasma.img

$(BUILD_DIR)/phasma.img:
	make -C $(KERNEL_DIR)
	make -C $(USERLAND_DIR)

	mkdir mnt
	
	# Create image
	dd if=/dev/zero of=$@ bs=1M count=64
	
	parted $@ mklabel msdos
	parted -a minimal $@ mkpart primary fat32 1MiB 100%

	# Mount
	sudo losetup -fP $@
	sudo mkfs.fat -F 32 -n phasma $(LOOP)p1
	sudo mount -t vfat $(LOOP)p1 mnt

	# Copy files
	sudo mkdir -p mnt/boot/grub
	sudo mkdir -p mnt/etc
	sudo mkdir -p mnt/bin

	sudo cp $(KERNEL_DIR)/build/phasma.bin mnt/boot/
	sudo cp $(USERLAND_DIR)/build/shell.elf mnt/bin/
	sudo cp $(USERLAND_DIR)/build/motd.elf mnt/bin/
	sudo cp $(USERLAND_DIR)/build/echo.elf mnt/bin/
	sudo cp $(USERLAND_DIR)/build/clear.elf mnt/bin/
	sudo cp $(USERLAND_DIR)/build/ls.elf mnt/bin/
	
	sudo cp rootfs/boot/grub/grub.cfg mnt/boot/grub/
	sudo cp rootfs/etc/system.cfg mnt/etc/

	# GRUB install
	sudo grub-install --target=i386-pc --boot-directory=mnt/boot --recheck $(LOOP)

	# Unmount
	sudo umount mnt
	sudo losetup -d $(LOOP)

	sudo chmod 777 $@

always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -f -r $(BUILD_DIR)
	rm -f -r mnt

run:
	qemu-system-x86_64 -drive format=raw,file=$(BUILD_DIR)/phasma.img,if=ide,index=0