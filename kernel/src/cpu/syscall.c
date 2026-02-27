#include <cpu/syscall.h>
#include <drivers/tty.h>
#include <drivers/keyboard.h>
#include <fat32.h>
#include <utils/kmalloc.h>
#include <exec.h>
#include <sleep.h>
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

void sys_puts(registers_t* regs) {
	const char* buffer = regs->ebx;
	uint32_t size = regs->ecx;

	tty_puts(buffer, size);
	regs->eax = 1;
}

/*
Get char syscall

uint32_t sys_getchar(void);
*/

void sys_getchar(registers_t* regs) {
	regs->eax = keyboard_getchar();
}

/*
Open file syscall

uint32_t* sys_open(const char* path);
*/

void sys_open(registers_t* regs) {
	const char* path = regs->ebx;
	fat32_file_t* fp = kmalloc(sizeof(fat32_file_t));

	if (!fat32_open_file(&kinfo.ctx, fp, path)) {
		regs->eax = 0;
		return;
	}

	regs->eax = fp;
}

/*
Read file syscall

uint32_t sys_read(uint32_t* fp, const char* buffer, uint32_t size);
*/

void sys_read(registers_t* regs) {
	fat32_file_t* fp = regs->ebx;
	const char* buffer = regs->ecx;
	uint32_t size = regs->edx;

	regs->eax = fat32_read(fp, buffer, size);
}

/*
Write file syscall

uint32_t sys_write(uint32_t* fp, char* buffer, uint32_t size);
*/

void sys_write(registers_t* regs) {
	fat32_file_t* fp = regs->ebx;
	char* buffer = regs->ecx;
	uint32_t size = regs->edx;

	regs->eax = fat32_write(fp, buffer, size);
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
Ioctl syscall

uint32_t sys_ioctl(const char* id, uint32_t cmd);
*/

void sys_ioctl(registers_t* regs) {
	regs->eax = 1;
}

/*
Exec syscall

uint32_t sys_exec(const char* path);
*/

void sys_exec(registers_t* regs) {
	const char* path = regs->ebx;
	
	regs->eax = exec(path);
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

static syscall_t syscalls[SYSCALL_COUNT] = {
	sys_puts,
	sys_getchar,
	sys_open,
	sys_read,
	sys_write,
	sys_close,
	sys_exec,
	sys_exit,
	sys_sleep,
	sys_ioctl
};

void syscall_handler(registers_t* regs) {
	if (regs->eax >= SYSCALL_COUNT)
		return;

	syscall_t syscall = syscalls[regs->eax];

	syscall(regs);
}
