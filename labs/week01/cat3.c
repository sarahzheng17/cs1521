// COMP1521 19T3 ... lab 1
// cat3: Copy input to output

#include <stdio.h>
#include <stdlib.h>

static void copy(FILE *, FILE *);

int main(void) {
    copy (stdin, stdout);
    return EXIT_SUCCESS;
}

// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode
static void copy (FILE *input, FILE *output) {

    // PUT YOUR CODE HERE
    char buffer[BUFSIZ];
    while(fgets(buffer, BUFSIZ, input) != NULL){
        fputs(buffer, output);
    }
}
