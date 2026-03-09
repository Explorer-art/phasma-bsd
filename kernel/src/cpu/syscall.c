#include <cpu/syscall.h>
#include <drivers/tty.h>
#include <drivers/keyboard.h>
#include <fat32.h>
#include <utils/kmalloc.h>
#include <exec.h>
#include <sleep.h>
#include <kernel.h>
#include <stddef.h>
#include <string.h>

/*
Syscalls

eax - syscall number

Parameters:
- ebx: 1 argument
- ecx: 2 argument
- edx: 3 argument
- esi: 4 argument
- edi: 5 argument
*/

/*
Puts string syscall

uint32_t sys_puts(const uint8_t* buffer, uint32_t size);
*/

void sys_puts(registers_t* regs) {
	const char* buffer = (char*)regs->ebx;
	uint32_t size = regs->ecx;

	tty_puts(buffer, size);
	regs->eax = 1;
}

/*
Gets syscall

uint32_t sys_gets(char* buffer, uint32_t size);
*/

void sys_gets(registers_t* regs) {
	char* buffer = (char*)regs->ebx;
	uint32_t size = regs->ecx;

	keyboard_gets(buffer, size);
	regs->eax = 1;
}

/*
Open file syscall

uint32_t* sys_open(const char* path);
*/

void sys_open(registers_t* regs) {
	const char* path = (char*)regs->ebx;
	fat32_file_t* fp = (fat32_file_t*)kmalloc(sizeof(fat32_file_t));

	if (!fat32_open_file(&kinfo.ctx, fp, path)) {
		regs->eax = 0;
		return;
	}

	regs->eax = fp;
}

/*
Close file syscall

uint32_t* sys_close(uint32_t* fp);
*/

void sys_close(registers_t* regs) {
	uint32_t* fp = regs->ebx;

	fat32_close((fat32_file_t*)fp);
	kfree(fp);

	regs->eax = 1;
}

/*
Read file syscall

uint32_t sys_read(uint32_t* fp, const char* buffer, uint32_t size);
*/

void sys_read(registers_t* regs) {
	fat32_file_t* fp = (fat32_file_t*)regs->ebx;
	const char* buffer = (char*)regs->ecx;
	uint32_t size = regs->edx;

	regs->eax = fat32_read(fp, buffer, size);
}

/*
Write file syscall

uint32_t sys_write(uint32_t* fp, char* buffer, uint32_t size);
*/

void sys_write(registers_t* regs) {
	fat32_file_t* fp = (fat32_file_t*)regs->ebx;
	char* buffer = (char*)regs->ecx;
	uint32_t size = regs->edx;

	regs->eax = fat32_write(fp, buffer, size);
}

/*
Get file size

uint32_t sys_seek(uint32_t* fp, uint32_t offset);
*/

void sys_seek(registers_t* regs) {
	fat32_file_t* fp = regs->ebx;
	uint32_t offset = regs->ecx;

	regs->eax = (uint32_t)fat32_seek(fp, offset);
}

/*
Get file size

uint32_t sys_getsize(const char* path);
*/

void sys_getsize(registers_t* regs) {
	const char* path = (char*)regs->ebx;

	fat32_file_t file;
	
	if (!fat32_open_file(&kinfo.ctx, &file, path)) {
		regs->eax = 0;
		return;
	}

	regs->eax = file.size;
	fat32_close(&file);
}

/*
Rename file/directory

uint32_t sys_rename(const char* path, const char* new_name);
*/

void sys_rename(registers_t* regs) {
	const char* path = (char*)regs->ebx;
	const char* new_name = (char*)regs->ecx;

	regs->eax = 1;
}

/*
Remove file

uint32_t sys_rm(const char* path);
*/

void sys_rm(registers_t* regs) {
	const char* path = (char*)regs->ebx;

	regs->eax = fat32_remove(&kinfo.ctx, path);
}

/*
Make directory

uint32_t sys_mkdir(const char* path);
*/

void sys_mkdir(registers_t* regs) {
	const char* path = (char*)regs->ebx;

	regs->eax = fat32_mkdir(&kinfo.ctx, path);
}

/*
Remove directory

uint32_t sys_rmdir(const char* path);
*/

void sys_rmdir(registers_t* regs) {
	const char* path = (char*)regs->ebx;

	regs->eax = fat32_rmdir(&kinfo.ctx, path);
}

/*
Read directory

uint32_t sys_read_dir(fat32_file_t* fp, fat32_dir_entry_t* entry);
*/

void sys_read_dir(registers_t* regs) {
	fat32_file_t* fp = (fat32_file_t*)regs->ebx;
	fat32_dir_entry_t* entry = (fat32_dir_entry_t*)regs->ecx;
	
	regs->eax = fat32_read_dir(fp, entry);
}

/*
Get current directory

uint32_t sys_getcd(char* buffer);
*/

void sys_getcd(registers_t* regs) {
	char* buffer = regs->ebx;
	strcpy(buffer, &kinfo.current_dir);
	regs->eax = 1;
}

/*
Set current directory

uint32_t sys_setcd(const char* new_current_dir);
*/

void sys_setcd(registers_t* regs) {
	const char* new_current_dir = (char*)regs->ebx;
	strcpy(&kinfo.current_dir, new_current_dir);
	regs->eax = 1;
}

/*
Exec syscall

uint32_t sys_exec(const char* path, const char** argv);
*/

void sys_exec(registers_t* regs) {
	const char* path = (char*)regs->ebx;
	const char** argv = (const char**)(uintptr_t)regs->ecx;
	
	regs->eax = exec(path, argv);
}

/*
Exit syscall

uint32_t sys_exit(uint32_t status);
*/

void sys_exit(registers_t* regs) {
	regs->eax = exit();
}

/*
Sleep syscall

uint32_t sys_sleep(uint32_t seconds);
*/

void sys_sleep(registers_t* regs) {
	uint32_t seconds = regs->ebx;
	sleep(seconds);
	regs->eax = 1;
}

/*
Allocate memory

uint32_t* sys_alloc(uint32_t size);
*/

void sys_alloc(registers_t* regs) {
	uint32_t size = regs->ebx;
	regs->eax = 1;
}

/*
Free memory

uint32_t sys_free(uint32_t* ptr);
*/

void sys_free(registers_t* regs) {
	uint32_t ptr = regs->ebx;
	regs->eax = 1;
}

static syscall_t syscalls[SYSCALL_COUNT] = {
	sys_puts,
	sys_gets,
	sys_open,
	sys_close,
	sys_read,
	sys_read_dir,
	sys_write,
	sys_seek,
	sys_getsize,
	sys_rename,
	sys_rm,
	sys_mkdir,
	sys_rmdir,
	sys_getcd,
	sys_setcd,
	sys_exec,
	sys_exit,
	sys_sleep,
	sys_alloc,
	sys_free
};

void syscall_handler(registers_t* regs) {
	if (regs->eax >= SYSCALL_COUNT)
		return;

	syscall_t syscall = syscalls[regs->eax];

	syscall(regs);
}
