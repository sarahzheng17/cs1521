// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    uint16_t low = (value & 0xFF)<<8;
    uint16_t high = (value & 0xFF00)>>8; 
    uint16_t swap = (low | high);
    return swap;
}
