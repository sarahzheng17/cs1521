// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return how many 1 bits value contains
int bit_count(uint64_t value) {
    unsigned int count = 0;
    while(value){
        count += value & 1;
        value = value >> 1;
    }
    return count;
}
