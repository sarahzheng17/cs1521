/* 
Write a C program, is_var_set.c, which takes one argument, the name of environment variable

If the environment variable is set to a non-empty string, it should print 1, otherwise it should print 0.
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){;
    if(getenv(argv[1]) && strlen(argv[1]) != 0){
        printf("1\n");
    } else {  
        printf("0\n");
    }
    return 0;
}
