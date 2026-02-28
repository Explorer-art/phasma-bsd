#include <drivers/keyboard.h>
#include <cpu/irq.h>
#include <x86.h>
#include <drivers/tty.h>
#include <utils/kprintf.h>
#include <memory.h>

static uint8_t caps = 0;
static uint8_t capslock = 0;
static uint32_t index = 0;
static uint8_t current_key;
static uint8_t keyboard_buffer[KEYBOARD_BUFFER_SIZE];

void keyboard_handler(registers_t* regs) {
	uint8_t status = inb(0x64);

    /* Нижний бит статуса будет выставлен, если буфер не пуст */
    if (!(status & 0x01))
        return;

    uint8_t keycode = inb(0x60);
    uint8_t release = keycode & 0x80;
    uint8_t key = keycode & 0x7F;

    switch (key) {
        case KEY_CAPSLOCK:
            if (!release)
                capslock = !capslock;
            return;
        case KEY_LSHIFT:
        case KEY_RSHIFT:
            if (!release)
                caps = 1;
            else
                caps = 0;
            return;
	}

    if (release)
        return;

    current_key = key;
    
    char c;

    if ((caps ^ capslock) != 0)
        c = keyboard_uppercase[key];
    else
        c = keyboard_lowercase[key];

    if (key == KEY_BACKSPACE) {
        if (index > 0) {
            tty_left();
            tty_putchar(' ');
            tty_left();
            index--;
            keyboard_buffer[index] = '\0';
        }
        return;
    }

    tty_putchar(c);
    keyboard_buffer[index] = c;
    index++;
}

uint32_t keyboard_gets(char* buffer, uint32_t size) {
    sti();
    memset(keyboard_buffer, 0, sizeof(keyboard_buffer));

    while (1) {
        if (current_key == KEY_ENTER) break;
    }

    memcpy(buffer, keyboard_buffer, size);
    index = 0;
    current_key = 0;

    cli();
    return 1;
}

void keyboard_init(void) {
	irq_install_handler(1, keyboard_handler);
}
