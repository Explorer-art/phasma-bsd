#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        puts(argv[i]);
        if ((i + 1 < argc)) puts(" ");
    }

    puts("\n\n");
    exit(0);
}