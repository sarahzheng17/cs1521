// If you use C library functions add includes here.
#include <stdlib.h> 
#include <string.h>
#include <stdio.h>
#include "emu.h"
#include "ram.h"
#include "registers.h"

 
/*
 * print a MIPS instruction (no newline)
 * run reference implementation if unsure what to print
 */
void print_instruction(uint32_t instruction) {
    //int sect(uint32_t instruction, int high, int low);
    // We want to break down the 32-bit instruction given into:
    // Opcode : ThE first 6 bits from 31-25
    // Registers: The 15 bits between 25 - 10
    // Num: The last 10 bits 10-0 which determine type of instruction
    //char *type; 
    uint32_t opcode_val = (instruction >> 26);
    uint32_t s = (instruction << 6) >> 27;
    uint32_t t = (instruction << 11) >> 27;
    uint32_t d = (instruction << 16) >> 27;
    uint32_t i = (instruction << 22) >> 22;
    // For sll and srl
    uint32_t end = (instruction << 26) >> 26;
    
    uint32_t b = (instruction << 6) >> 27;
    uint32_t o = (instruction << 16) >> 16;    
    if (opcode_val == 0){
        if (i == 32){
            printf("add $%d, $%d, $%d", d, s, t);
        }
        else if (i == 36) {
            printf("and $%d, $%d, $%d", d, s, t);        
        }
        else if (i == 8) {
            printf("jr $%d", s);        
        }
        else if (i == 37) {
            printf("or $%d, $%d, $%d", d, s, t);        
        }
        else if (i == 34) {
            printf("sub $%d, $%d, $%d", d, s, t);        
        }        
        else if (i == 38) {
            printf("xor $%d, $%d, $%d", d, s, t);        
        }                
        else if (i == 4) {
            printf("sllv $%d, $%d, $%d", d, t, s);        
        }   
        else if (i == 6) {
            printf("srlv $%d, $%d, $%d", d, t, s);        
        }
        else if (end == 0) {
            uint32_t I = (instruction << 21) >> 27;
            printf("sll $%d, $%d, %d", d, t, I);        
        }
        else if (end == 2) {
            uint32_t I = (instruction << 21) >> 27;
            printf("srl $%d, $%d, %d", d, t, I);        
        }        
        else if (i == 42) {
            printf("slt $%d, $%d, $%d", d, s, t);        
        } else {
            printf("syscall ");
        }
        }
    else if (opcode_val > 0){
        int16_t I = (instruction << 16) >> 16;
        uint32_t X = (instruction << 6) >> 6;
        if (opcode_val == 8){
            printf("addi $%d, $%d, %d", t, s, I);        
        }
        else if (opcode_val == 12){
            printf("andi $%d, $%d, %d", t, s, I);        
        }                       
        else if (opcode_val == 13){
            printf("ori $%d, $%d, %d", t, s, I);        
        }            
        else if (opcode_val == 14){
            printf("xori $%d, $%d, %d", t, s, I);        
        }            
        else if (opcode_val == 10){
            printf("slti $%d, $%d, %d", t, s, I);        
        }            
        else if (opcode_val == 15){
            int16_t l_I = (instruction << 16) >> 16;
            printf("lui $%d, %d", t, l_I);        
        }
        else if (opcode_val == 4){
            printf("beq $%d, $%d, %d", s, t, I);        
        }
        else if (opcode_val == 5){
            printf("bne $%d, $%d, %d", s, t, I);        
        } 
        else if (opcode_val == 6){
            printf("blez $%d, %d", s, I);        
        } 
        else if (opcode_val == 7){
            printf("bgtz $%d, %d", s, I);        
        }  
        else if (opcode_val == 1){
            int16_t b_I = (instruction << 16) >> 16;
            if((((instruction << 15) >> 31)&1) == 1){ //negative
                printf("bgez $%d, %d", s, b_I);        
            } else {
                printf("bltz $%d, %d", s, b_I);        
            }
        }
        else if (opcode_val == 2){
            printf("j 0x%x", X);                
        }            
        else if (opcode_val == 3){
            printf("jal 0x%x", X);                
        }
        else if (opcode_val == 28){
            printf("mul $%d, $%d, $%d", d, s, t);                
        }      
        else if (opcode_val == 32){
            printf("lb $%d, %d($%d)", t, o, b);                
        }        
        else if (opcode_val == 33){
            printf("lh $%d, %d($%d)", t, o, b);                
        }
        else if (opcode_val == 35){
            printf("lw $%d, %d($%d)", t, o, b);                
        } 
        else if (opcode_val == 40){
            printf("sb $%d, %d($%d)", t, o, b);                
        }        
        else if (opcode_val == 41){
            printf("sh $%d, %d($%d)", t, o, b);                
        }
        else if (opcode_val == 43){
            printf("sw $%d, %d($%d)", t, o, b);                
        }
    }      
}
            
// PUT YOUR FUNCTIONS HERE
// Obtain sections of 32-bit instruction





