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

    char* arg = strtok(buffer, " ");
    if (!arg) return;
    char* path = arg;

    if (!check_file(arg)) {
        puts("error: Unknown file!");
        return;
    }

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

    exec(path, argv);
}

bool check_file(char* path) {
    file_t* fp;

    fp = fopen(path);
    if (fp) {
        fclose(fp);
        return true;
    }

    return false;
}