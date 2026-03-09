#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <memory.h>
#include <string.h>

int main(int argc, char** argv) {
    fat32_dir_entry_t entry;
    char current_dir[PATH_MAX_SIZE];

    if (argc < 2)
        sys_getcd(current_dir);
    else
        strcpy(current_dir, argv[1]);

    FILE* fp = fopen(current_dir);
    if (!fp) exit(1);

    char buffer[12];

    while (sys_read_dir((fat32_file_t*)fp, &entry)) {
        memcpy(buffer, entry.name, 11);
        buffer[11] = '\0';
        printf("%s\n", buffer);
    }

    puts("\n");
    exit(0);
}