#include "bit_rotate.h"
#define BIT_LIMIT 16
// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {


    if (n_rotations >= 0){
    uint16_t end = (bits & (uint16_t)0xFFFF); //Saves left hand side end
    uint16_t final = ((bits << n_rotations) | (end >> (16 - n_rotations)));
    return final;
    } 
    
    else {       
    uint16_t start = (bits & (uint16_t)0xFFFF); //Saves left hand side end
    uint16_t final = ((bits >> (-1)*n_rotations) | (start << (16 + n_rotations)));
    return final;    
    }
    
}

