#include <cpu/syscall.h>
#include <drivers/tty.h>
#include <drivers/keyboard.h>
#include <fat32.h>
#include <utils/kmalloc.h>
#include <kernel.h>
#include <stddef.h>

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
Put string syscall

uint32_t sys_puts(const uint8_t* buffer, uint32_t size);
*/

uint32_t sys_puts(registers_t* regs) {
	const char* buffer = regs->ebx;
	uint32_t size = regs->ecx;

	tty_puts(buffer, size);
	return 1;
}

/*
Get char syscall

uint32_t sys_getchar(void);
*/

uint32_t sys_getchar(registers_t* regs) {
	return (uint32_t)keyboard_getchar();
}

/*
Open file syscall

uint32_t* sys_open(const char* path);
*/

uint32_t sys_open(registers_t* regs) {
	const char* path = regs->ebx;
	fat32_file_t* fp = kmalloc(sizeof(fat32_file_t));

	if (!fat32_open_file(&kinfo.ctx, fp, path)) return 0;

	return fp;
}

/*
Read file syscall

uint32_t sys_read(file_t* fp, const char* buffer, uint32_t size);
*/

uint32_t sys_read(registers_t* regs) {
	uint32_t bytes_read = 0;

	fat32_file_t* fp = regs->ebx;
	const char* buffer = regs->ecx;
	uint32_t size = regs->edx;

	return bytes_read;
}

/*
Write file syscall

uint32_t sys_write(file_t* fp, char* buffer, uint32_t size);
*/

uint32_t sys_write(registers_t* regs) {
	uint32_t bytes_write = 0;

	fat32_file_t* fp = regs->ebx;
	char* buffer = regs->ecx;
	uint32_t size = regs->edx;

	return bytes_write;
}

/*
Close file syscall

uint32_t* sys_close(uint32_t* fp);
*/

uint32_t sys_close(registers_t* regs) {
	uint32_t* fp = regs->ebx;

	fat32_close((fat32_file_t*)fp);
	kfree(fp);

	return 1;
}

/*
Exec syscall

uint32_t sys_exec(char* path);
*/

uint32_t sys_exec(registers_t* regs) {
	char* path = regs->ebx;
	
	return exec(path);
}

/*
Exit syscall

uint32_t sys_exit(uint32_t status);
*/

uint32_t sys_exit(registers_t* regs) {
	return exit();
}

static syscall_t syscalls[SYSCALL_COUNT] = {
	sys_puts,
	sys_getchar,
	sys_open,
	sys_read,
	sys_write,
	sys_close,
	sys_exec,
	sys_exit
};

void syscall_handler(registers_t* regs) {
	if (regs->eax >= SYSCALL_COUNT)
		return;

	syscall_t syscall = syscalls[regs->eax];

	syscall(regs);
}
