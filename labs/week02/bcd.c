#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {
    //First convert to binary representation
    /*int c, k, bin_total = 0;
    
    for (c = 15; c >= 0; c--){
        k = bcd_value >> c;
        if(k & 1){
            bin_total += pow(2,(15 - c)); 
        } else {
            bin_total += 0; 
        }
    }
        printf("\n"); */
        
        int up,low, total;
        low = bcd_value & 0xFF;
        up = bcd_value & 0xFF00;
        up = up>>8;
        total = low + 10*up;
        
        
        
    
        return total;
}

