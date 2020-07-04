#  read numbers until a non-negative number entered
# x in $t0
main:
    
    addi $t1, $t1, 0     # int x;
    addi $t2, $t2, 1
loop1: 
    bltz $t2, end        # while(1)
    
    la $a0, str0         # printf("Enter a number: ");
    li $v0, 4
    syscall    

    li $v0, 5            # scanf("%d", &x);
    syscall              
    move $t0, $v0
    
    bgez $t0, print1 
    
    la $a0, str2         # printf("Enter a positive number ");
    li $v0, 4
    syscall
    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall
    
    j loop1    
print1:   
    la $a0, str1         # printf("You entered: %d");
    li $v0, 4
    syscall 
    move $a0, $t0        # printf("%d", x);
    li $v0, 1
    syscall
    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

end:
    li $v0, 0            # return 0
    jr $31

.data
str0:
    .asciiz "Enter a number: "
str1:
    .asciiz "You entered: "
str2:
    .asciiz "Enter a positive number "
