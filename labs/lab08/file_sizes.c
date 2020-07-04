#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    struct stat s;
    long total = 0;
    for (int arg = 1; arg < argc; arg++) {
        if (stat(argv[arg], &s) != 0) {
            perror(argv[arg]);
            exit(1);
        }
        printf("%s: %ld bytes\n", argv[arg], (long)s.st_size);
        total += (long)s.st_size;    
    }
    printf("Total: %ld bytes\n", total);    
    return 0;
}

