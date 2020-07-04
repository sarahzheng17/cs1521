// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    // Need to analyse bit pattern for an addi instruction
    // Obtain the 32-bit immediate code instruction code format 
    // addi has an opcode of 001000
    
    uint32_t addi_num = (1 << 29)|(t << 16)|(s << 21)|(i);   
    if(i < 0){
        uint32_t new_i = ((uint32_t)i << 16)>>16;
        addi_num = (1 << 29)|(t << 16)|(s << 21)|(new_i);

    } else {
    addi_num = (1 << 29)|(t << 16)|(s << 21)|(i);   
    }
        
    return addi_num; // REPLACE WITH YOUR CODE

}
