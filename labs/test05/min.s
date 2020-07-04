#  print the minimum of two integers
main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0       # t0 = x;

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0       # t1 = y;
    
    bge $t0, $t1, printy# (if x >= y) break;    
    
printx: 

    move $a0, $t0         # printf("%d", x);
    li $v0, 1
    syscall 
    
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall  
    j end
      
printy:

    move $a0, $t1         # printf("%d", x);
    li $v0, 1
    syscall 
    
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    j end
    #li $a0, 42          #   printf("%d\n", 42);
    #li $v0, 1
    #syscall

end:

    li $v0, 0           # return 0
    jr $31
