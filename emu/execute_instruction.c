// If you use C library functions add includes here.

#include "emu.h"
#include "ram.h"
#include "registers.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

/**
 * execute a MIPS instruction
 *
 * This function should:
 *
 * get register values by calling `get_register(register_type register_number)`
 * change registers by calling `set_register(register_type register_number, uint32_t value)`
 *
 * get memory values by `calling get_byte(uint32_t address)`
 * changes memory by `set_byte(uint32_t address, uint8_t value)`
 *
 * updates program_counter to address of next instruction
 *
 * returns 1 if an exit syscall is executed, 0 otherwise
 */

int execute_instruction(uint32_t instruction, uint32_t *program_counter) {

    /* example code to implement add $4, $14, $12
    uint32_t x = get_register(14);
    uint32_t y = get_register(12);
    uint32_t sum = x + y;
    set_register(4, sum); */
    
    // Extract our bitcode: 
    uint32_t bitcode = instruction >> 26; 
    // For sll and srl
    uint32_t end = (instruction << 26) >> 26;    
    // Get all types of registers and required bit patterns
    uint32_t s = (instruction << 6) >> 27;
    uint32_t t = (instruction << 11) >> 27;
    uint32_t d = (instruction << 16) >> 27;
    uint16_t I = (instruction << 16) >> 16;
    uint32_t o = (instruction << 16) >> 16;    
    if (bitcode == 0){ 
        uint32_t i = (instruction << 22) >> 22;                 
    // Implementing R type instructions 
        // add $d, $s, $t
        if (i == 32){       
            uint32_t sum = get_register(s) + get_register(t);
            set_register(d, sum); 
            (*program_counter) += 4;
        }
        // and $d, $s, $t        
        else if (i == 36) {
            uint32_t and = get_register(s) & get_register(t);  
            set_register(d, and);
            (*program_counter) += 4;      
        }
        // jr $s
        else if (i == 8) {
            (*program_counter) = get_register(s);
        }
        //or $d, $s, $t
        else if (i == 37) {
            uint32_t or = (get_register(s) | get_register(t));   
            set_register(d, or);
            (*program_counter) += 4;     
        }
        //sub $d, $s, $t
        else if (i == 34) {
            uint32_t sub = get_register(s) - get_register(t);   
            set_register(d, sub);
            (*program_counter) += 4; 
        } 
        //xor $d, $s, $t       
        else if (i == 38) {
            uint32_t xor = get_register(s) ^ get_register(t);   
            set_register(d, xor);
            (*program_counter) += 4;
        } 
        //sllv $d, $t, $s	               
        else if (i == 4) {
            uint32_t sllv = get_register(t) << get_register(s);   
            set_register(d, sllv);
            (*program_counter) += 4;    
        } 
        //srlv $d, $t, $s	
        else if (i == 6) {
            uint32_t srlv = get_register(t) >> get_register(s);   
            set_register(d, srlv);
            (*program_counter) += 4; 
        }
        //sll $d, $t, I	
        else if (end == 0) {
            uint32_t sll = (get_register(t) << I);   
            set_register(d, sll);
            (*program_counter) += 4;
        }
        //srl $d, $t, I	
        else if (end == 2) {
            uint32_t srl = (get_register(t) >> I);   
            set_register(d, srl);
            (*program_counter) += 4;
        }
        //slt $d, $s, $t	        
        else if (i == 42) {
            uint32_t slt = (get_register(t) < get_register(s));   
            set_register(d, slt);
            (*program_counter) += 4;
        } 
        // syscall
        else {
            int v = get_register(v0);
            // print integer           
            if(v == 1){
                int32_t number = get_register(a0);
                printf("%d", number);
                (*program_counter) += 4;
            }
            // print string 
            else if (v == 4){
                int j = 0; 
                while(get_byte(get_register(a0) + j) != '\0'){
                    printf("%c", get_byte(get_register(a0) + j));
                    j++;
                }
            (*program_counter) += 4;
            }
            // read integer
            else if(v == 5){
                int32_t number; 
                scanf("%d", &number);
                set_register(get_register(a0), number);
                (*program_counter) += 4;
            }
            // read string 
            else if(v == 8){
                int j = 0;
                char array[a1-1]; 
                while(array[j] != '\n'){
                    scanf("%c", &array[j]);
                    set_byte(get_register(a0) + j, array[j]);
                    j++;
                }
            (*program_counter) += 4;
            }
            // exit
            else if(v == 10){
                return 1;
            }
            // print character (lsb 8 bits)
            else if(v == 11){
                printf("%c",(get_register(a0) << 26) >> 26);
                (*program_counter) += 4;
            } 
            else if(v == 12){
                char c;
                scanf("%c", &c);
                set_register(get_register(a0), c); 
                (*program_counter) += 4;               
            }                   
        }
    }
    else if(bitcode > 0){
        //addi $t, $s, I
        if (bitcode == 8){
            uint32_t addi = get_register(s) + I;
            set_register(t, addi); 
            (*program_counter) += 4;    
        }
        //andi $t, $s, I
        else if (bitcode == 12){
            uint32_t andi = get_register(s) & I;
            set_register(t, andi); 
            (*program_counter) += 4;            
        } 
        //ori $t, $s, I                      
        else if (bitcode == 13){
            uint32_t ori = get_register(s) | I;
            set_register(t, ori); 
            (*program_counter) += 4;
        }   
        //xori $t, $s, I         
        else if (bitcode == 14){
            uint32_t xori = get_register(s) ^ I;
            set_register(t, xori); 
            (*program_counter) += 4;
        }       
        //slti $t, $s, I     
        else if (bitcode == 10){
            uint32_t slti = (get_register(s) < I);
            set_register(t, slti); 
            (*program_counter) += 4;            
        }  
        //lui $t, I          
        else if (bitcode == 15){
            uint32_t lui = I << 16;
            set_register(t, lui); 
            (*program_counter) += 4;
        }
        //beq $s, $t, I
        else if (bitcode == 4){
            if(get_register(s) == get_register(t)){
                (*program_counter) += ((int16_t)I << 2);
            } else {
                *(program_counter) += 4;
            }
        }
        //bne $s, $t, I
        else if (bitcode == 5){
            if(get_register(s) != get_register(t)){
                (*program_counter) += ((int16_t)I << 2);
            } else {
                *(program_counter) += 4;
            }
        } 
        //blez $s, $t, I
        else if (bitcode == 6){
            if(get_register(s) <= 0){
                (*program_counter) += ((int16_t)I << 2);
            } else {
                *(program_counter) += 4;
            }
        } 
        //bgtz $s, $t, I
        else if (bitcode == 7){
            if(get_register(s) > 0){
                (*program_counter) += ((int16_t)I << 2);
            } else {
                *(program_counter) += 4;
            }
        }  
        else if (bitcode == 1){
            if((((instruction << 15) >> 31)&1) == 1){ 
                    //bgez $s, I
            if(get_register(s) >= 0){
                (*program_counter) += ((int16_t)I << 2);
            } else {
                *(program_counter) += 4;
            }                               
            } else {//bltz $s, I 
            if(get_register(s) < 0){
                (*program_counter) += ((int16_t)I << 2);
            } else {
                *(program_counter) += 4;
            }
            }
        }   // j         
        else if (bitcode == 2){
            uint32_t mask = instruction & 0x3FFFFFF;
            *(program_counter) = (*(program_counter) & 0xF0000000) | (mask << 2);
        } 
        // jal
        else if (bitcode == 3){
            uint32_t mask = instruction & 0x3FFFFFF;
            *(program_counter) = (*(program_counter) & 0xF0000000) | (mask << 2);
            set_register(ra,(uint32_t)(*(program_counter) + 4));
        }        
        // mul $s, $t, $d
        else if (bitcode == 28){
            uint32_t mul = get_register(s) * get_register(t);   
            set_register(d, mul);
            (*program_counter) += 4;
        } 
          // lb/sb $t, O($b) - need a single byte at addr 	    
        else if ((bitcode == 32)|(bitcode == 40)){
            uint32_t R = get_register(s) + o;
            uint32_t addr = get_byte(R);
            set_byte(t, addr);  
        } // lh/sh - need bytes at addr and addr + 1       
        else if ((bitcode == 33)|(bitcode == 41)){
            uint32_t R = (get_register(s) + o);
            uint32_t addr= (get_byte(R) << 8)|(get_byte(R + 1));  
            set_byte(t, addr);            
        } // lw/sw - need bytes of addr till addr + 3
        else if ((bitcode == 35)|(bitcode == 43)){
            int32_t R = (get_register(s) + o);
            uint32_t addr = (get_byte(R) << 24)|(get_byte(R + 1) << 16)|
            (get_byte(R + 2) << 8)|(get_byte(R + 3)); 
            set_byte(t, addr);    
        } 
    }        
    // 0 should be returned, unless an exit syscall is executed
    return 0;  
}

