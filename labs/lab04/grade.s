# read a mark and print the corresponding UNSW grade

main:
    la $a0, prompt      # printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", mark);
    syscall
    
    bge $v0, 50, else1     # branch if (mark > 50)
                           # if(mark < 50)                           
    la $a0, fl             # printf("FL\n"); 
    li $v0, 4
    syscall
    j end               # jump over elses 
    
else1:        
    bge $v0, 65, else2     # branch else if(mark >= 65)
                           # else if(mark < 65)                               
    la $a0, ps             # printf("PS\n");
    li $v0, 4
    syscall
    j end               # jump over elses 
      
else2:        
    bge $v0, 75, else3     # branch else if(mark >= 75)
                           # else if(mark < 75)                                   
    la $a0, cr             # printf("CR\n");
    li $v0, 4
    syscall
    j end               # jump over elses    
         
else3:        
    bge $v0, 85, else4     # branch else if(mark >= 85)
                           # else if(mark < 85)                                       
    la $a0, dn             # printf("DN\n");
    li $v0, 4
    syscall
    j end               # jump over elses  
    
else4:        
                           # else {
    la $a0, hd
    li $v0, 4
    syscall                #printf("HD\n");
    j end               # jump over elses      
    
end:       
    jr $ra              # return

    .text
FL: 
    la $a0, fl
    li $v0, 4
    syscall
PS: 
    la $a0, ps
    li $v0, 4
    syscall
CR: 
    la $a0, cr
    li $v0, 4
    syscall
DN: 
    la $a0, dn
    li $v0, 4
    syscall
HD:     
    la $a0, hd
    li $v0, 4
    syscall    
            
    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"
