#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {
    
    uint32_t up;
    uint32_t total = 0;
    int power = 1;
    for (int i = 0; i < 8; i++){
        up = packed_bcd_value & ((uint32_t)0xF << (4*(i)));
        up = up >> (4*(i)); 
        if(i >= 1){      
            power = power*10;
        }     
        total = total + up*power;  
    }
    return total;
}
