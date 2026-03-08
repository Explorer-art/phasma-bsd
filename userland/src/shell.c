#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void exec_cmd(char* buffer);
bool check_file(const char* buffer, char* path);

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

    char* arg = strtok(buffer, " ");
    if (!arg) return;

    char* argv[256];
    char** argv_tmp = argv;

    while (arg) {
        int length = strlen(arg);
        if (length > 0 && arg[length - 1] == '\n') {
            arg[length - 1] = '\0';
        }
        
        *argv_tmp = arg;
        argv_tmp++;
        arg = strtok(NULL, " ");
    }

    *argv_tmp = NULL;
    char path[PATH_MAX_SIZE];

    if (!check_file(argv[0], path)) {
        puts("error: Unknown file!");
        return;
    }

    exec(path, argv);
}

bool check_file(const char* buffer, char* path) {
    strcpy(path, buffer);

    FILE* fp = fopen(path);
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
    }

    fp = fopen(path);
    if (fp) {
        fclose(fp);
        return true;
    }

    return false;
}