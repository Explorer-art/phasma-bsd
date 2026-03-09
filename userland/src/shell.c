#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <syscall.h>

void exec_cmd(char* buffer);
bool check_file(const char* buffer, char* path, const char* dir);

char current_dir[PATH_MAX_SIZE];

int main(void) {
    char buffer[PATH_MAX_SIZE];
    
    sys_getcd(current_dir);
    printf("%s # ", current_dir);

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

    if (!strcmp(argv[0], "cd")) {
        if (!argv[1])
            sys_setcd("/");
        else
            change_directory(argv[1]);

        return;
    }

    char path[PATH_MAX_SIZE];

    /*
    TODO:
    Implement support for absolute and relative paths.
    */

    if (!check_file(argv[0], path, "/bin/") && !check_file(argv[0], path, "/")) {
        puts("error: Unknown file!");
        return;
    }

    exec(path, argv);
}

bool check_file(const char* buffer, char* path, const char* dir) {
    char* p = strcpy(path, dir);
    strcpy((p + 1), buffer);

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

void change_directory(const char* new_dir) {
    if (!strcmp(new_dir, "..")) {
        char* str = strrchr(current_dir, '/');
        *str = '\0';
        
        if (current_dir[0] != '/') {
            current_dir[0] = '/';
            current_dir[1] = '\0';
        }

        sys_setcd(current_dir);
        return;
    }

    int curr_dir_len = strlen(current_dir);
    int new_dir_len = strlen(new_dir);
    int offset = curr_dir_len;

    if (curr_dir_len + new_dir_len + 2 >= PATH_MAX_SIZE) {
        printf("error: Path too long\n");
        return;
    }

    if (current_dir[curr_dir_len - 1] != '/') {
        current_dir[curr_dir_len] = '/';
        offset++;
    }

    strcpy((current_dir + offset), new_dir);
    sys_setcd(current_dir);
}