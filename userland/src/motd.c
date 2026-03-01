#include <stdio.h>

int main(void) {
    puts("\033[H\033[J"); // Clear screen
    puts("Welcome to Phasma BSD!\n\nType 'help' to get about the commands\n");
    return 0;
}