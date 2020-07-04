//
// Sample solution for COMP1521 lab exercises
//
// Convert a 16-bit signed integer to a string of binary digits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value) {
    int i, dec, count = 0;
    char *p;
    
    p = (char*)malloc(N_BITS + 1);
    
    if(p == NULL){
        exit(EXIT_FAILURE);
    }
    
    for(i = 15; i >= 0 ; i--){
        dec = value >> i;
        
        if(dec & 1){
        //The position of the pointer to char is given by p + count
        //The value of that position is filled up via right side. 
            *(p + count) = 1 +'0';  
        }
        else {
            *(p + count) = 0 + '0';
        }
        count ++;
    }
    //End with a null terminator. 
    *(p + count) = '\0';
    return p;
}

