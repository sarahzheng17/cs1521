// COMP1521 19T3 ... lab 1
// cat4: Copy input to output

#include <stdio.h>
#include <stdlib.h>


static void copy(FILE *, FILE *);

int main(int argc, char *argv[]) {
    //If no command line arguments
    if(argc == 1){
        copy (stdin, stdout);
    } else {
        int i;
        for(i = 1;i < argc; i++){  
            FILE * fp = fopen(argv[i], "r"); 
            if(fp == NULL){
                printf("Can't read name-of-file\n");
            } else {
                copy (fp, stdout);
                fclose(fp);
            }
        }
    }
    return EXIT_SUCCESS;
}


// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode
static void copy (FILE *input, FILE *output) {

    char buffer[BUFSIZ];
    while(fgets(buffer, BUFSIZ, input) != NULL){
        fputs(buffer, output);
    }

}
