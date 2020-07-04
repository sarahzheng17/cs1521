// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    uint64_t up, down;
    for (int i = 0; i < 8; i+=2){
        up = value & ((uint64_t)0xFF << (4*(i)));
        down = value & ((uint64_t)0xFF00 >> (4*(i)));
        up = up >> (4*(i)); 
        down = down << (4*(i));
    }
    return (up|down);
}
