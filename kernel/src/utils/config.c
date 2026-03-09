#include <utils/config.h>
#include <utils/kprintf.h>
#include <string.h>
#include <limits.h>

int atoi(const char *str) {
    if (!str) return 0;

    int sign = 1;
    int result = 0;

    while (*str == ' ' || *str == '\t' || *str == '\n' ||
           *str == '\v' || *str == '\f' || *str == '\r') {
        str++;
    }

    if (*str == '+' || *str == '-') {
        if (*str == '-') sign = -1;
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        int digit = *str - '0';
        
        if (result > (INT_MAX - digit) / 10) {
            return sign == 1 ? INT_MAX : INT_MIN;
        }

        result = result * 10 + digit;
        str++;
    }

    return sign * result;
}

bool config_get_str(fat32_file_t* file, const char* key, char* out, size_t size) {
    char buffer[512];
    size_t bytes_read;

    while ((bytes_read = fat32_read_line(file, buffer, sizeof(buffer))) > 0) {
        char* current_key = strtok(buffer, "=");
        char* value_str = strtok(NULL, "=");

        if (current_key && value_str && strcmp(current_key, key) == 0) {
            strncpy(out, value_str, size - 1);

            char* new_line_char = strchr(out, '\n');
            
            if (new_line_char) {
                *new_line_char = '\0';
            }

            out[size - 1] = '\0';
            return true;
        }
    }

    return false;
}

bool config_get_int(fat32_file_t* file, const char* key, int* value) {
    char buffer[512];
    size_t bytes_read;

    while ((bytes_read = fat32_read_line(file, buffer, sizeof(buffer))) > 0) {
        char* current_key = strtok(buffer, "=");
        char* value_str = strtok(NULL, "=");

        if (current_key && value_str && strcmp(current_key, key) == 0) {
            *value = atoi(value_str);
            return true;
        }
    }

    return false;
}