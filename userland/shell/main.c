#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buffer[256];
    puts("\n# ");

    gets(buffer, sizeof(buffer));
    if (!(*buffer)) return;

    char* path = strtok(buffer, " ");
    int length = strlen(path);

    if (path[length - 1] == '\n') {
        path[length - 1] = '\0';
    }

    if (!path) return;

    exec(path);
    puts("\n");
    
    return 0;
}