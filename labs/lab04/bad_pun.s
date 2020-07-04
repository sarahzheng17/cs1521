main:
    la $a0, str # Place str in that memory address
    li $v0, 4  # Function call for print string 
    syscall # print string 
    jr $ra # Remove stack frame
    
    .data 
str: 
    .asciiz "I MIPS you!\n" 
