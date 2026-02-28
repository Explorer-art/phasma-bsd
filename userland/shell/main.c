#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer[256];
    puts("> ");
    gets(buffer, sizeof(buffer));
    puts(buffer);
    puts("\n");
    
    return 0;
}