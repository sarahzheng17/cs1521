main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0       #   t0 = x;

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0       #   t1 = y;
    
    li $t2, 0 
    addi $t2, $t0, 1    #   int i = x + 1;
    
loop1: 
   
    bge $t2, $t1, end   #   if (i >= y) break;
    bne $t2, 13, print  #   if (i != 13) {print}
    beq $t2, 13, increment 
    j loop1
    
print: 

    move $a0, $t2       #   printf("%d\n", i);
    li $v0, 1
    syscall
    
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    addi $t2, $t2, 1
    j loop1
increment:
    addi $t2, $t2, 1
    j loop1

end:

    li $v0, 0           # return 0
    jr $31
