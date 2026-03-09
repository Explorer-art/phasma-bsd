#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define BUFFER_SIZE 256

int main(int argc, char** argv) {
    if (argc < 2) exit(1);

    FILE* fp = fopen(argv[1]);
    if (!fp) {
        puts("error: Unknown file\n\n");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read = 0;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        puts(buffer);
    }

    fclose(fp);

    puts("\n\n");
    exit(0);
}