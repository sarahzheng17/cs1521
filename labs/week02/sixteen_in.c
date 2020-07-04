//
// Sample solution for COMP1521 lab exercises
//
// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h> 
#define N_BITS 16


int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a strings of binary digits ('1' and '0')
// return corresponding signed 16 bit integer
//
//Print binary representation of char bits 
int16_t sixteen_in(char *bits) {
    int i = 0;
    int binary = 0;
    while(i < N_BITS){
        if(bits[i] == '0'){
            binary += 0;
        }
        if(bits[i] == '1'){
            binary += pow(2,(15-i));
        }
        i++;
    }
    return binary;
}

