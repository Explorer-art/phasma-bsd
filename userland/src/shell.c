#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void exec_cmd(char* buffer);
bool check_file(char* path);

int main(void) {
    char buffer[PATH_MAX_SIZE];
    puts("\n# ");

    gets(buffer, sizeof(buffer));
    exec_cmd(buffer);
    puts("\n");
    
    exit(0);
}

void exec_cmd(char* buffer) {
    if (!(*buffer)) return;

    char* path = strtok(buffer, " ");
    int length = strlen(path);

    if (path[length - 1] == '\n') {
        path[length - 1] = '\0';
    }

    if (!path) return;

    if (!check_file(path)) {
        puts("error: Unknown file!");
        return;
    }

    exec(path);
}

bool check_file(char* path) {
    file_t* fp;

    fp = fopen(path);
    if (fp) {
        fclose(fp);
        return true;
    }

    int length = strlen(path);

    if (length + 5 < PATH_MAX_SIZE) {
        path[length] = '.';
        path[length + 1] = 'e';
        path[length + 2] = 'l';
        path[length + 3] = 'f';
        path[length + 4] = '\0';

        fp = fopen(path);
        if (fp) {
            fclose(fp);
            return true;
        }
    }

    return false;
}