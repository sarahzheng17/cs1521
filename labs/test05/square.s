main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0
    
    li $t1, 0           #   int i = 0;
    
loop1: 
    
    bge $t1, $t0, end2   #   while (i < x) cont;
    
    li $t2, 0           #   int j = 0;
    
loop2: 

    bge $t2, $t0, end1 #   while (j < x) cont;
    
    li   $a0, '*'       #   printf("*");
    li   $v0, 11
    syscall 
    addi $t2, $t2, 1    #   j = j + 1;      
    j loop2
    
end1:
    addi $t1, $t1, 1    #   i = i + 1;
    
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    
    j loop1
    
end2:
    
    li $v0, 0           # return 0
    jr $31
